/**
 * \file host_mcu_interface_rx.c
 * \version 1.00
 * \brief this file contains MCU-to-MCU RX interface functionality
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

#include <stdint.h>
#include <stddef.h>
#include "board.h"
#include "host_mcu_interface.h"
#include "fsl_interrupt_manager.h"

#include "HEXIWEAR_info.h"
#include "HEXIWEAR_driver.h"

#include "fsl_uart_driver.h"
#include "KW40_UART.h"

#if defined( HEXIWEAR_DEBUG )
#include "DEBUG_UART.h"
#endif

#include "host_mcu_interface_types.h"
#include "host_mcu_interface_defs.h"

#include "rtc_driver.h"
#include "power_driver.h"

#include "notifications.h"
#include "bluetooth.h"
#include "bootloader.h"
#include "buttons_group.h"
#include "watch.h"

#include "gui_driver.h"
#include "gui_defs.h"
#include "error.h"

#include "flashlight.h"

#include "haptic.h"

/** private type definitions */
/** private memory declarations */
static hostInterface_packet_t
  hostInterface_rxPacket;

static msg_queue_handler_t
  hostInterface_rxQueueHnd;

static hostInterface_rxState_t
  hostInterface_rxState = hostInterface_rxState_idle;

static bool
  isWakingTouch = false;

/** message queues */
MSG_QUEUE_DECLARE( hostInterface_rxQueue, gHostInterface_msgNum, sizeof(hostInterface_packet_t) );

/** private prototypes */
static void PacketHandler(hostInterface_packet_t * pHostInterface_packet);
osa_status_t HostInterface_RxQueueMsgPut(hostInterface_packet_t * pHostInterface_packet);
static osa_status_t HostInterface_RxQueueMsgGet(hostInterface_packet_t * pHostInterface_packet);
static void HostInterface_RxTask(task_param_t param);
static void HostInterface_RxCallback(uint32_t instance, void *uartState);

/**
 * this function handles the packet arrived via comm interface
 * @param self received packet
 */
static void PacketHandler( hostInterface_packet_t* self )
{
  switch( self->type )
  {
    // buttons
    case packetType_pressUp:
    case packetType_pressDown:
    case packetType_pressLeft:
    case packetType_pressRight:
    {
		RTC_UpdateAlarm();
		//haptic_Vibrate();

//        if ( true == isWakingTouch )
//        {
//            isWakingTouch = false;
            power_TurnScreenON();
//        }
//        else
        {
            GuiDriver_ButtonsHandler( self );
        }

		break;
    }

    case packetType_slide:
    {
        break;
    }

    // alert service
    case packetType_alertIn:
    {
    	RTC_UpdateAlarm();
    	haptic_Vibrate();

    	notification_type_t
	    	notifType;

	  switch(self->data[0])
	  {
		  case alertIn_type_notification:
		  {
				ancCategoryId_t
					categoryID = self->data[1];

				uint8_t
					notifCnt = self->data[2];

				switch ( categoryID )
				{
					case ancCategoryId_missedCall:
					{
						notifType = NOTIF_TYPE_CALL;
						break;
					}
					case ancCategoryId_email:
					{
						notifType = NOTIF_TYPE_MAIL;
						break;
					}
					case ancCategoryId_social:
					{
						notifType = NOTIF_TYPE_SMS;
						break;
					}

					default: {}
				}

				Notification_SetUnreadCounter( notifType, notifCnt );
				watch_SetNotification();
				Notification_SetEvent( notifType );
				break;
		  }

		  case alertIn_type_timeUpdate:
		  {
			  uint32_t
				  timestamp;

			  memcpy((uint8_t *)&timestamp, &self->data[2], 4);
			  RTC_UpdateCurrentTime(timestamp);
			  haptic_Vibrate();
			  break;
		  }
	  }
	  break;
	}

    case packetType_notification:
    {
    	notification_type_t
			notifType;

    	uint8_t
			notifCnt;

    	RTC_UpdateAlarm();
    	haptic_Vibrate();

    	if ( true == isWakingTouch )
    	{
    		isWakingTouch = false;
    	    power_TurnScreenON();
    	}

        ancEventId_t
            eventID = self->data[0];

        ancCategoryId_t
            categoryID = self->data[1];

        switch ( categoryID )
        {
        	case ancCategoryId_missedCall:
        	{
        		notifType = NOTIF_TYPE_CALL;
        		break;
        	}
        	case ancCategoryId_email:
        	{
        		notifType = NOTIF_TYPE_MAIL;
        		break;
        	}
        	case ancCategoryId_social:
        	{
        		notifType = NOTIF_TYPE_SMS;
        		break;
        	}

        	default: {}
        }

        notifCnt = Notification_GetUnreadCounter( notifType );

        switch ( eventID )
        {
        	case ancEventId_NotifAdded:
        	{
        		notifCnt++;
        		break;
        	}
        	case ancEventId_NotifRemoved:
        	{
        		notifCnt--;
        		break;
        	}

        	default: {}
        }

        Notification_SetUnreadCounter( notifType, notifCnt );
        watch_SetNotification();
        break;
    }

    case packetType_passDisplay:
    {
		RTC_UpdateAlarm();
		haptic_Vibrate();

		if ( true == isWakingTouch )
		{
			isWakingTouch = false;
			power_TurnScreenON();
		}

		uint32_t
		  passkey = 0;

		memcpy(&passkey, self->data, 3);
		GuiDriver_Navigation(GUI_NAVIGATION_BOND, (void *)&passkey);
		break;
	}

      case packetType_otapCompleted:
      {
		boootloader_QueueMsgPut( self );
		break;
      }

      case packetType_otapFailed:
      {
		power_ResetKW40();
		boootloader_QueueMsgPut( self );
		break;
      }

      case packetType_buttonsGroupSendActive:
      {
    	  buttonsGroup_ActiveUpdate(self->data[0]);
    	  break;
      }

      case packetType_advModeSend:
      {
		  bluetooth_AdvModeUpdate(self->data[0]);
		  break;
      }

      case packetType_linkStateSend:
		{
			RTC_UpdateAlarm();
			haptic_Vibrate();

			if ( true == isWakingTouch )
			{
			  isWakingTouch = false;
			  power_TurnScreenON();
			}
			watch_LinkStateUpdate(self->data[0]);
			break;
		}

      case packetType_buildVersion:
      {
    	  hexiwear_kw40version.ver_majorNumber = self->data[0];
    	  hexiwear_kw40version.ver_minorNumber = self->data[1];
    	  hexiwear_kw40version.ver_patchNumber = self->data[2];
    	  HEXIWEAR_UpdateVersion();
    	  break;
      }

    default: {}
  }
}

/**
 * initialize RX tasks and queues
 * @return  task initialization status
 */
osa_status_t HostInterface_RxInit()
{
  osa_status_t
    status;

  // install the callback
  UART_DRV_InstallRxCallback( gHostInterface_instance, HostInterface_RxCallback, (uint8_t*)&hostInterface_rxPacket, NULL, true );

  // Create Rx Message Queue
  hostInterface_rxQueueHnd = OSA_MsgQCreate (
                                              hostInterface_rxQueue,
                                              gHostInterface_msgNum,
                                              sizeof(hostInterface_packet_t) / sizeof(uint32_t)
                                            );
  if ( NULL == hostInterface_rxQueueHnd )
  {
    catch(3);
  }

#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( hostInterface_rxQueueHnd, (const char*)"RxQueue" );
#endif

  // Create Rx Task
  status = OSA_TaskCreate (
                            HostInterface_RxTask,
                            (uint8_t*)"HostInterface_RxTask",
                            3*gHostInterfaceRxTaskStackSize_c,
                            NULL,
                            gHostInterfaceRxPriority_c,
                            (task_param_t)NULL,
                            false,
                            &hexiwear_intf_RX_handler
                          );

  if  ( kStatus_OSA_Success != status )
  {
    catch(3);
  }

  return (osa_status_t)status;
}


/**
 * IRQ callback which implements the interface state machine
 * @param instance  comm instance number
 * @param uartState comm instance state
 */
static void HostInterface_RxCallback(
                                        uint32_t instance,
                                           void* uartState
                                    )
{
  static uint8_t
    byteCount;

  uart_state_t*
    state = (uart_state_t*)uartState;

  switch ( hostInterface_rxState )
  {
    case hostInterface_rxState_idle:  {
                                        if ( gHostInterface_startByte1 == hostInterface_rxPacket.start1 )
                                        {
                                            hostInterface_rxState++;
                                            state->rxBuff++;
                                        }

                                        break;
                                      }

    case hostInterface_rxState_headerReceived:  {
                                                  if  (
                                                               ( gHostInterface_startByte1 != hostInterface_rxPacket.start1 )
                                                        ||     ( gHostInterface_startByte2 != ( hostInterface_rxPacket.start2 & 0xFE ) )
                                                        || ( hostInterface_rxPacket.length >  gHostInterface_dataSize )
                                                      )
                                                  {
                                                    // return to idle state
                                                    hostInterface_rxState = hostInterface_rxState_idle;
                                                    // reset the RX buffer pointer
                                                    state->rxBuff = (uint8_t*) &hostInterface_rxPacket;
                                                  }

                                                  else
                                                  {
                                                    // advance the buffer pointer
                                                    state->rxBuff++;

                                                    if ( 0 == hostInterface_rxPacket.length )
                                                    {
                                                      // advance to "wait-trailer-bit" state
                                                      hostInterface_rxState = hostInterface_rxState_trailerWait;
                                                    }

                                                    else
                                                    {
                                                      byteCount = 0;
                                                      // advance to "data-wait" state
                                                      hostInterface_rxState = hostInterface_rxState_dataWait;
                                                    }
                                                  }

                                                  break;
                                                }

      case hostInterface_rxState_dataWait:  {
                                              byteCount++;
                                              (state->rxBuff)++;

                                              // if we reached the byte-count
                                              if  ( hostInterface_rxPacket.length == byteCount )
                                              {
                                                // advance to "wait-trailer-bit" state
                                                hostInterface_rxState = hostInterface_rxState_trailerWait;
                                              }

                                              break;
                                            }

      case hostInterface_rxState_trailerWait: {
                                                if ( gHostInterface_trailerByte == *(state->rxBuff) )
                                                {

#if defined (gHostInterface_RxConfirmationEnable)
                                                  if ( packetType_OK == hostInterface_rxPacket.type )
                                                  {
                                                    // announce that OK packet is received successfully
                                                    HostInterface_EventConfirmPacketSet();
                                                  }

                                                  else
#endif
                                                  {
                                                    // else, put the packet into the RX queue
                                                    HostInterface_RxQueueMsgPut( (hostInterface_packet_t *)&hostInterface_rxPacket );
                                                  }
                                                }

                                                // go back to the idle state
                                                hostInterface_rxState = hostInterface_rxState_idle;
                                                // reset the RX buffer pointer
                                                state->rxBuff = (uint8_t *) &hostInterface_rxPacket;
                                                break;
                                              }

      default:  {
                  hostInterface_rxState++;
                  state->rxBuff++;
                }
  }
}

/**
 * This function puts a message to the end of the Tx message queue.
 *
 * @param  pHostInterface_packet Packet that will be placed into Tx message queue.
 *
 * @return kStatus_OSA_Success  Message successfully put into the queue.
 *         kStatus_OSA_Error    Process fail.
 */

osa_status_t HostInterface_RxQueueMsgPut( hostInterface_packet_t* pHostInterface_packet )
{
  osa_status_t
    status = OSA_MsgQPut(hostInterface_rxQueueHnd, (hostInterface_packet_t *)pHostInterface_packet);

  if ( kStatus_OSA_Error == status )
  {
    catch(2);
  }
  return (osa_status_t)status;
}

/**
 * This function gets a message from the head of the Tx message queue.
 *
 * @param  pHostInterface_packet   Pointer to a memory to save the packet.
 *
 * @return kStatus_OSA_Success  Message successfully obtained from the queue.
 *         kStatus_OSA_Error    Process fail.
 */

static osa_status_t HostInterface_RxQueueMsgGet ( hostInterface_packet_t* pHostInterface_packet )
{
  osa_status_t
    status = OSA_MsgQGet(hostInterface_rxQueueHnd, (hostInterface_packet_t *)pHostInterface_packet, gHostInterface_waitTimeout);

  if ( kStatus_OSA_Error == status )
  {
    catch(2);
  }
  return (osa_status_t)status;
}

/**
 * Host MCU Interface RX task charged with handling the received data packet
 * @param  optional parameter
 */
static void HostInterface_RxTask( task_param_t param )
{
  hostInterface_packet_t
    tmpPkt;

  while (1)
  {
    osa_status_t
      status = HostInterface_RxQueueMsgGet( &tmpPkt );

    if ( kStatus_OSA_Success == status )
    {

#ifdef gHostInterface_TxConfirmationEnable
      // acknowledge the packet reception
      if ( 1 == ( tmpPkt.start2 & 0x01 ) )
      {
    	  HostInterface_EventSendOkPacketSet();
      }
#endif

      // handle the packet's content
      PacketHandler( &tmpPkt );
    }
  }
}

/**
 * mark registered touch as the first after wake-up
 */
void HostInterface_SetWakingTouch()
{
  isWakingTouch = true;
}
