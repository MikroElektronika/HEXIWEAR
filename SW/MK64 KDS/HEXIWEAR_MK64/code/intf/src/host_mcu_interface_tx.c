/**
 * \file host_mcu_interface_tx.c
 * \version 1.00
 * \brief this file contains MCU-to-MCU TX interface functionality
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

/** includes */
#include <stdint.h>
#include <stddef.h>
#include "board.h"
#include "fsl_uart_driver.h"
#include "fsl_interrupt_manager.h"

#include "HEXIWEAR_info.h"

#include "power_driver.h"

#include "host_mcu_interface.h"
#include "host_mcu_interface_defs.h"

#if defined( HEXIWEAR_DEBUG )
#include "DEBUG_UART.h"
#include "flashlight.h"
#endif

#include "error.h"
#include "error_types.h"

/** private memory declarations */
static hostInterface_packet_t
  hostInterface_txPacket;
static msg_queue_handler_t
  hostInterface_txQueueHnd;
static mutex_t
  uartTxAccessMutex;

static hostInterface_packet_t
  hostInterface_okPacket =  {
                              .start1 = 0x55,
                              .start2 = 0xAA,
                              .type   = packetType_OK,
                              .length = 0,
                              .data[0] = gHostInterface_trailerByte
                            };

/** message queues */
MSG_QUEUE_DECLARE( hostInterface_txQueue, gHostInterface_msgNum, sizeof(hostInterface_packet_t) );

/** private prototypes */
static osa_status_t HostInterface_TxQueueMsgGet(hostInterface_packet_t * pHostInterface_packet);
static void         HostInterface_FlushPacket(hostInterface_packet_t * pHostInterface_packet);
static void         HostInterface_TxTask(task_param_t param);
static void         HostInterface_OkTask(task_param_t param);
static void         HostInterface_ConfirmWaitHandler();

/** functions definitions */

/**
 * create RTOS structures for sending data via communication interface
 * @return status flag
 */
osa_status_t HostInterface_TxInit()
{
  osa_status_t
    status = OSA_MutexCreate(&uartTxAccessMutex);

  if( kStatus_OSA_Success != status )
  {
    catch( CATCH_QUEUE ) ;
  }

  // create TX message queue
  hostInterface_txQueueHnd = OSA_MsgQCreate (
                                              hostInterface_txQueue,
                                              gHostInterface_msgNum,
                                              sizeof(hostInterface_packet_t) / sizeof(uint32_t)
                                            );
  if ( NULL == hostInterface_txQueueHnd )
  {
    return kStatus_OSA_Error;
  }

#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( hostInterface_txQueueHnd, (char*)"TxQueue" );
#endif

  // Create Tx-Data Task
  status = OSA_TaskCreate (
                            HostInterface_TxTask,
                            (uint8_t*)"HostInterface_TxTask",
                            gHostInterfaceTxTaskStackSize_c,
                            NULL,
                            gHostInterfaceTxPriority_c,
                            (task_param_t)NULL,
                            false,
                            &hexiwear_intf_TX_handler
                          );


  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_TASK ) ;
  }

  // create Tx-OK Task
  status = OSA_TaskCreate (
                            HostInterface_OkTask,
                            (uint8_t*)"HostInterface_OkTask",
                            gHostInterfaceOkTaskStackSize_c,
                            NULL,
                            gHostInterfaceOkPriority_c,
                            (task_param_t)NULL,
                            false,
                            &hexiwear_intf_OK_handler
                          );

  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_TASK ) ;
  }

  return (osa_status_t)status;
}

/**
 *    This function puts a message to the end of the Tx message queue.
 *
 *    @param    pHostInterface_packet   Packet that will be placed into Tx message queue.
 *
 *    @return                          kStatus_OSA_Success  Message successfully put into the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */
osa_status_t HostInterface_TxQueueMsgPut(
                                          hostInterface_packet_t* pHostInterface_packet,
										                      bool confirmationReq
                                        )
{
	pHostInterface_packet->start1 = gHostInterface_startByte1;
	pHostInterface_packet->start2 = gHostInterface_startByte2;

	if ( true == confirmationReq )
	{
		pHostInterface_packet->start2 |= 1;
	}

    BaseType_t
      status = xQueueSendToBack(hostInterface_txQueueHnd, (hostInterface_packet_t*)pHostInterface_packet, OSA_WAIT_FOREVER );

    if ( pdPASS == status )
    {
        return kStatus_OSA_Success;
    }

    else
    {
        return kStatus_OSA_Error;
    }
}

/**
 *    This function gets a message from the head of the Tx message queue.
 *
 *    @param    pHostInterface_packet   Pointer to a memory to save the packet.
 *
 *    @return                          kStatus_OSA_Success  Message successfully obtained from the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */
static osa_status_t HostInterface_TxQueueMsgGet (
                                                  hostInterface_packet_t* pHostInterface_packet
                                                )
{
  osa_status_t
    status = OSA_MsgQGet(hostInterface_txQueueHnd, (hostInterface_packet_t*)pHostInterface_packet, OSA_WAIT_FOREVER);

  if ( kStatus_OSA_Error == status )
  {
    catch(2);
  }

  return (osa_status_t)status;
}

/**
 * push the received data packet through selected comm packet
 * @param param optional parameter
 */
static void HostInterface_TxTask(task_param_t param)
{
    while (1)
    {
        osa_status_t
            status = HostInterface_TxQueueMsgGet(&hostInterface_txPacket);

        if ( kStatus_OSA_Success == status )
        {
        	if ( packetType_accel == hostInterface_txPacket.type )
			    {
        		TOGGLE_PROBE();
			    }
          HostInterface_FlushPacket(&hostInterface_txPacket);

#if gHostInterface_RxConfirmationEnable
            if ( 1 == ( hostInterface_txPacket.start2 & 0x01 ) )
            {
            	  HostInterface_EventConfirmPacketClear();
            	  HostInterface_ConfirmWaitHandler();
            }
#endif
            /**
             * if the current mode is sensor tag sleep mode,
             * go to sleep upon finishing the data packet exchange
             */
            switch ( power_GetCurrentMode() )
            {
            	case POWER_CURRENT_MODE_NORMAL:
            	{
                power_TurnScreenON();
            		break;
            	}

            	case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
            	{
                power_SetSleepSource( POWER_SLEEP_SRC_SENSOR_TAG );
                power_GotoSleep();
            		break;
            	}

            	default:
            	{
            		// for other power modes, do nothing
            		break;
            	}
            }
        }
    }
}

/**
 * send OK packet
 * @param param optional parameter
 */
static void HostInterface_OkTask(task_param_t param)
{
  while (1)
  {
    osa_status_t
      status = HostInterface_EventSendOkPacketWait();

    if ( kStatus_OSA_Success == status )
    {
      HostInterface_FlushPacket(&hostInterface_okPacket );
    }
  }
}

/**
 * handle confirmation wait - timeout
 * if timeout occurs, send the packet again (max "gHostInterface_retransmitCount" times)
 */
static void HostInterface_ConfirmWaitHandler()
{
  for ( uint8_t retransmitCnt = 0; retransmitCnt < gHostInterface_retransmitCount; retransmitCnt++ )
  {
    if( kStatus_OSA_Timeout == HostInterface_EventConfirmPacketWait() )
    {
      HostInterface_FlushPacket(&hostInterface_txPacket);
    }

    else
    {
      break;
    }
  }
}

/**
 * send data packet
 * @param pHostInterface_packet packet to be sent
 */
static void HostInterface_FlushPacket(hostInterface_packet_t * pHostInterface_packet)
{
  osa_status_t
    status = OSA_MutexLock( &uartTxAccessMutex, OSA_WAIT_FOREVER );

  if ( kStatus_OSA_Success == status )
  {
#if defined( SEND_PACKETS_VIA_UART_INT )
    UART_DRV_SendDataBlocking( gHostInterface_instance, (uint8_t*)pHostInterface_packet, pHostInterface_packet->length + gHostInterface_headerSize + 1, UART_TIMEOUT );
#elif defined( SEND_PACKETS_VIA_UART_DMA )
    UART_DRV_EdmaSendDataBlocking( gHostInterface_instance, (uint8_t*)pHostInterface_packet, pHostInterface_packet->length + gHostInterface_headerSize + 1, UART_TIMEOUT );
#endif

#if defined( HEXIWEAR_DEBUG )
//    UART_DRV_SendDataBlocking( HEXIWEAR_DEBUG_UART_INSTANCE, (uint8_t*)pHostInterface_packet, pHostInterface_packet->length + gHostInterface_headerSize + 1, UART_TIMEOUT );
#endif
  }

  OSA_MutexUnlock(&uartTxAccessMutex);
}
