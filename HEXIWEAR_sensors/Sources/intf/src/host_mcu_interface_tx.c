/************************************************************************************
*************************************************************************************

* Include
*************************************************************************************
************************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include "board.h"
#include "fsl_uart_driver.h"
#include "fsl_interrupt_manager.h"

#include "HEXIWEAR_info.h"

#include "host_mcu_interface.h"

#if defined( HEXIWEAR_DEBUG )
#include "uartCom2.h"
#endif

#include "error.h"


/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static hostInterface_packet_t
  hostInterface_txPacket;

static msg_queue_handler_t
  hostInterface_txQueueHnd;

static mutex_t
  uartTxAccessMutex;

/**
 * message queues
 */
MSG_QUEUE_DECLARE( hostInterface_txQueue, gHostInterface_msgNum, sizeof(hostInterface_packet_t) );

/**
 * tasks
 */
OSA_TASK_DEFINE( HostInterface_TxTask, gHostInterfaceTxTaskStackSize_c );
OSA_TASK_DEFINE( HostInterface_OkTask, gHostInterfaceOkTaskStackSize_c );

static hostInterface_packet_t
  hostInterface_okPacket =  {
                              .start1 = 0x55,
                              .start2 = 0xAA,
                              .type   = packetType_OK,
                              .length = 0,
                              .data[0] = gHostInterface_trailerByte
                            };

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

static osa_status_t HostInterface_TxQueueMsgGet(hostInterface_packet_t * pHostInterface_packet);
static void         HostInterface_FlushPacket(hostInterface_packet_t * pHostInterface_packet);
static void         HostInterface_TxTask(task_param_t param);
static void         HostInterface_OkTask(task_param_t param);
static void         HostInterface_ConfirmWaitHandler();

/*! *********************************************************************************
*************************************************************************************
* Functions definitions
*************************************************************************************
********************************************************************************** */

/**
 * create RTOS structures for sending data via communication interface
 */
osa_status_t HostInterface_TxInit()
{
  osa_status_t
    status = OSA_MutexCreate(&uartTxAccessMutex);

  if( kStatus_OSA_Success != status )
  {
    catch(3);
  }

  // Create Tx Message Queue
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
  vQueueAddToRegistry( hostInterface_txQueueHnd, (signed char*)"TxQueue" );
#endif

  // Create Tx-Data Task
  status = OSA_TaskCreate (
                            HostInterface_TxTask,
                            (uint8_t*)"HostInterface_TxTask",
                            gHostInterfaceTxTaskStackSize_c,
                            HostInterface_TxTask_stack,
                            gHostInterfaceTxPriority_c,
                            (task_param_t)NULL,
                            false,
                            &HostInterface_TxTask_task_handler
                          );

  if ( kStatus_OSA_Success != status )
  {
    catch(3);
  }

  // create Tx-OK Task
  status = OSA_TaskCreate (
                            HostInterface_OkTask,
                            (uint8_t*)"HostInterface_OkTask",
                            gHostInterfaceOkTaskStackSize_c,
                            HostInterface_OkTask_stack,
                            gHostInterfaceOkPriority_c,
                            (task_param_t)NULL,
                            false,
                            &HostInterface_OkTask_task_handler
                          );

  if ( kStatus_OSA_Success != status )
  {
    catch(3);
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
                                          hostInterface_packet_t* pHostInterface_packet
                                        )
{
  osa_status_t
    status = kStatus_OSA_Success;

  while (1)
  {
    status = OSA_MsgQPut(hostInterface_txQueueHnd, (hostInterface_packet_t*)pHostInterface_packet);

    if ( kStatus_OSA_Success == status )
    {
      break;
    }

    else
    {
      catch(2);
    }
  }

  return (osa_status_t)status;
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
 * send data packet
 * @param param [description]
 */
static void HostInterface_TxTask(task_param_t param)
{
  while (1)
  {
    osa_status_t
      status = HostInterface_TxQueueMsgGet(&hostInterface_txPacket);

    if ( kStatus_OSA_Success == status )
    {
      HostInterface_FlushPacket(&hostInterface_txPacket);

#if gHostInterface_RxConfirmationEnable

      HostInterface_EventConfirmPacketClear();
      HostInterface_ConfirmWaitHandler();

#endif
    }
  }
}

/**
 * send OK packet
 * @param param [description]
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
 * @param pHostInterface_packet [description]
 */
static void HostInterface_FlushPacket(hostInterface_packet_t * pHostInterface_packet)
{
  osa_status_t
    status = OSA_MutexLock(&uartTxAccessMutex, OSA_WAIT_FOREVER );

  if ( kStatus_OSA_Success == status )
  {
#if defined( SEND_VIA_UART_INT )

    GPIO_DRV_TogglePinOutput( PROBE_PIN );
    UART_DRV_SendDataBlocking( gHostInterface_instance, (uint8_t*)pHostInterface_packet, pHostInterface_packet->length + gHostInterface_headerSize + 1, 10 );

#elif defined( SEND_VIA_UART_DMA )
    UART_DRV_EdmaSendDataBlocking( gHostInterface_instance, (uint8_t*)pHostInterface_packet, pHostInterface_packet->length + gHostInterface_headerSize + 1, 100 );
#endif

#if defined( HEXIWEAR_DEBUG )
      UART_DRV_SendDataBlocking( HEXIWEAR_DEBUG_INSTANCE, (uint8_t*)pHostInterface_packet, pHostInterface_packet->length + gHostInterface_headerSize + 1, 100 );
    }
#endif

    OSA_MutexUnlock(&uartTxAccessMutex);
  }
}

