// File: host_mcu_interface_rx.c

// Definitions of rx functionalities of the MCU interface module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////
 
#include <stdint.h>
#include <stddef.h>
#include "host_mcu_interface.h"

#include "HEXIWEAR_info.h"
#include "HEXIWEAR_defs.h"
#include "HEXIWEAR_driver.h"

#include "host_mcu_interface_types.h"
#include "host_mcu_interface_defs.h"

#include "rtc_driver.h"
#include "power_driver.h"

#include "notifications/notifications.h"
#include "settings/bluetooth/bluetooth.h"
#include "settings/wireless_conn/wireless.h"
#include "settings/bootloader/bootloader.h"
#include "settings/buttons_group/buttons_group.h"
#include "watch/watch.h"

#include "gui_driver.h"
#include "gui_defs.h"
#include "error.h"

#include "settings/haptic/haptic.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static uint8_t *rxBuff;

static hostInterface_packet_t hostInterface_rxPacket;

static msg_queue_handler_t hostInterface_rxQueueHnd;

static hostInterface_rxState_t hostInterface_rxState = hostInterface_rxState_idle;

static bool isWakingTouch = false;

static char SSID_password[64];
static char SSID[32];
static char MQTT_username[32];
static char MQTT_password[32];
static char G3_name[32];
static char G3_username[32];
static char G3_password[32];
static int ClickPosition = 0;
static int WiFi_auth = 0;

static int SSID_length = 0;
static int SSID_password_length = 0;
static int SSID_password_pos = 0;
static int G3_name_length = 0;
static int G3_username_length = 0;
static int G3_password_length = 0;

// Message queues.
msg_queue_t *hostInterface_rxQueue = NULL;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////
    
// Handles the packets received via comm interface.
static void PacketHandler( hostInterface_packet_t *pHostInterface_packet )
{
    switch( pHostInterface_packet->type )
    {
        // buttons
        case packetType_pressUp:
        case packetType_pressDown:
        case packetType_pressLeft:
        case packetType_pressRight:
            RTC_UpdateAlarm();
            power_TurnScreenOn();
            GuiDriver_ButtonsHandler( pHostInterface_packet );
            break;

        case packetType_slide:
            break;

        // alert service
        case packetType_alertIn:
        {
            notification_type_t notifType;
            
            RTC_UpdateAlarm();
            haptic_Vibrate();
                
            switch( pHostInterface_packet->_data[0] )
            {
                case alertIn_type_notification:
                {
                    ancCategoryId_t categoryID =
                        pHostInterface_packet->_data[1];
                    uint8_t notifCnt = pHostInterface_packet->_data[2];
                    
                    switch( categoryID )
                    {
                        case ancCategoryId_missedCall:
                            notifType = NOTIF_TYPE_CALL;
                            break;

                        case ancCategoryId_email:
                            notifType = NOTIF_TYPE_MAIL;
                            break;

                        case ancCategoryId_social:
                            notifType = NOTIF_TYPE_SMS;
                            break;

                        default:
                            break;
                    }
                     
                     Notification_SetUnreadCounter( notifType, notifCnt );
                     watch_SetNotification();
                     Notification_SetEvent( notifType );
                     break;
                } // case alertIn_type_notification:

                case alertIn_type_timeUpdate:
                {
                    uint32_t timestamp;
                    
                    memcpy( ( uint8_t* )&timestamp, &pHostInterface_packet->_data[2], 4 );
                    RTC_UpdateCurrentTime( timestamp );
                    haptic_Vibrate();
                    
                    wifi_SendBluetoothParameters();
                    g3_SendBluetoothParameters();
                    
                    break;
                }
                case alertIn_type_wifiSSID:
                {
                    int dataLength;
                    int maxDataLength = 17;

                    if(pHostInterface_packet->_data[1] == 1)
                    {
                        SSID_length = pHostInterface_packet->_data[2];
                        dataLength = SSID_length < maxDataLength ? SSID_length : maxDataLength;
                        memcpy( SSID, &pHostInterface_packet->_data[3], dataLength );
                        
                        if(dataLength <= pHostInterface_packet->_data[2])
                        {
                            wifi_setSSID(SSID);
                            memset(SSID, 0, 32);
                        }
                    }
                    else if(pHostInterface_packet->_data[1] == 2)
                    {
                        dataLength = SSID_length - maxDataLength;
                        memcpy( &SSID[maxDataLength], &pHostInterface_packet->_data[2], dataLength );
                        wifi_setSSID(SSID);
                        memset(SSID, 0, 32);
                    }

                    break;
                }
                case alertIn_type_wifiPass:
                {
                    int dataLength;
                    int maxStartDataLength = 17;
                    int maxContinueDataLength = 18;
                    
                    if(pHostInterface_packet->_data[1] == 1)
                    {

                        SSID_password_length = pHostInterface_packet->_data[2];
                        dataLength = SSID_password_length < maxStartDataLength ? SSID_password_length : maxStartDataLength;
                        memcpy( SSID_password, &pHostInterface_packet->_data[3], dataLength );

                        if(dataLength <= pHostInterface_packet->_data[2])
                        {
                            wifi_setSSIDPassword(SSID_password);
                            memset(SSID_password, 0, 64);
                        }
                        SSID_password_pos = dataLength;
                    }
                    else if(pHostInterface_packet->_data[1] == 2)
                    {

                        if(SSID_password_length < SSID_password_pos + maxContinueDataLength)
                        {
                            dataLength = SSID_password_length - SSID_password_pos;
                        }
                        else
                        {
                            dataLength = maxContinueDataLength;
                        }
                        memcpy( &SSID_password[SSID_password_pos], &pHostInterface_packet->_data[2], dataLength );
                        SSID_password_pos += dataLength;
                        if(SSID_password_pos >= SSID_password_length)
                        {
                            wifi_setSSIDPassword(SSID_password);
                            memset(SSID_password, 0, 64);
                        }

                    }
                     break;
                }
                case alertIn_type_wifiAuth:
                {
                     WiFi_auth = pHostInterface_packet->_data[3];
                     if(WiFi_auth >= 0 && WiFi_auth <= 2)
                     {
                         wifi_setWiFiAuth(WiFi_auth);
                     }
                     break;
                }
                case alertIn_type_mqttUsername:
                {
                    int dataLength = pHostInterface_packet->_data[2];
                    memcpy( MQTT_username, &pHostInterface_packet->_data[3], dataLength );
                    wifi_setMQTTUsername(MQTT_username);
                    memset(MQTT_username, 0, 32);
                    break;
                }
                case alertIn_type_mqttPass:
                {
                    int dataLength = pHostInterface_packet->_data[2];
                    memcpy( MQTT_password, &pHostInterface_packet->_data[3], dataLength );
                    wifi_setMQTTPassword(MQTT_password);
                    memset(MQTT_password, 0, 32);
                    break;
                }
                case alertIn_type_3GName:
                {
                    int dataLength;
                    int maxDataLength = 17;

                    if(pHostInterface_packet->_data[1] == 1)
                    {
                        G3_name_length = pHostInterface_packet->_data[2];
                        dataLength = G3_name_length < maxDataLength ? G3_name_length : maxDataLength;
                        memcpy( G3_name, &pHostInterface_packet->_data[3], dataLength );

                        if(dataLength <= pHostInterface_packet->_data[2])
                        {
                            g3_setName(G3_name);
                            memset(G3_name, 0, 32);
                        }
                    }
                    else if(pHostInterface_packet->_data[1] == 2)
                    {
                        dataLength = G3_name_length - maxDataLength;
                        memcpy( &G3_name[maxDataLength], &pHostInterface_packet->_data[2], dataLength );
                        g3_setName(G3_name);
                        memset(G3_name, 0, 32);
                    }

                    break;
                }
                case alertIn_type_3GUsername:
                {
                    int dataLength;
                    int maxDataLength = 17;

                    if(pHostInterface_packet->_data[1] == 1)
                    {
                        G3_username_length = pHostInterface_packet->_data[2];
                        dataLength = G3_username_length < maxDataLength ? G3_username_length : maxDataLength;
                        memcpy( G3_username, &pHostInterface_packet->_data[3], dataLength );

                        if(dataLength <= pHostInterface_packet->_data[2])
                        {
                            g3_setUsername(G3_username);
                            memset(G3_username, 0, 32);
                        }
                    }
                    else if(pHostInterface_packet->_data[1] == 2)
                    {
                        dataLength = G3_username_length - maxDataLength;
                        memcpy( &G3_username[maxDataLength], &pHostInterface_packet->_data[2], dataLength );
                        g3_setUsername(G3_username);
                        memset(G3_username, 0, 32);
                    }

                    break;
                }
                case alertIn_type_3GPassword:
                {
                    int dataLength;
                    int maxDataLength = 17;

                    if(pHostInterface_packet->_data[1] == 1)
                    {
                        G3_password_length = pHostInterface_packet->_data[2];
                        dataLength = G3_password_length < maxDataLength ? G3_password_length : maxDataLength;
                        memcpy( G3_password, &pHostInterface_packet->_data[3], dataLength );

                        if(dataLength <= pHostInterface_packet->_data[2])
                        {
                            g3_setPassword(G3_password);
                            memset(G3_password, 0, 32);
                        }
                    }
                    else if(pHostInterface_packet->_data[1] == 2)
                    {
                        dataLength = G3_password_length - maxDataLength;
                        memcpy( &G3_password[maxDataLength], &pHostInterface_packet->_data[2], dataLength );
                        g3_setPassword(G3_password);
                        memset(G3_password, 0, 32);
                    }

                    break;
                }
                case alertIn_type_WiFiClick:
                {
                     ClickPosition = pHostInterface_packet->_data[3];

                     if(ClickPosition >= 1 && ClickPosition <= 3)
                     {
                         wifi_setClickPosition(ClickPosition);
                         setConnStatus (1);
                     }

                     break;
                }
                case alertIn_type_3GClick:
                {
                     ClickPosition = pHostInterface_packet->_data[3];

                     if(ClickPosition >= 1 && ClickPosition <= 3)
                     {
                         wifi_setClickPosition(ClickPosition);
                         setConnStatus (2);
                     }
                     break;
                }
            } // switch( pHostInterface_packet->_data[0] )
                
            break;
        } // case packetType_alertIn:

        case packetType_notification:
        {
            notification_type_t notifType;
            uint8_t notifCnt;
            ancEventId_t eventID = pHostInterface_packet->_data[0];
            ancCategoryId_t categoryID = pHostInterface_packet->_data[1];
            
            RTC_UpdateAlarm();
            haptic_Vibrate();
            
            if( isWakingTouch == true )
            {
                isWakingTouch = false;
                power_TurnScreenOn();
            }
            
            switch( categoryID )
            {
                case ancCategoryId_missedCall:
                    notifType = NOTIF_TYPE_CALL;
                    break;

                case ancCategoryId_email:
                    notifType = NOTIF_TYPE_MAIL;
                    break;

                case ancCategoryId_social:
                    notifType = NOTIF_TYPE_SMS;
                    break;

                default:
                    break;
            } // switch( categoryID )
            
            notifCnt = Notification_GetUnreadCounter( notifType );
            
             switch ( eventID )
             {
                 case ancEventId_NotifAdded:
                     notifCnt++;
                     break;

                 case ancEventId_NotifRemoved:
                     notifCnt--;
                     break;

                default:
                    break;
             }
             
             Notification_SetUnreadCounter( notifType, notifCnt );
             watch_SetNotification();
             break;
        } // case packetType_notification:

        case packetType_passDisplay:
        {
            uint32_t passkey = 0;
            
            RTC_UpdateAlarm();
            haptic_Vibrate();
            
            if ( isWakingTouch == true )
            {
                isWakingTouch = false;
                power_TurnScreenOn();
            }
            
            memcpy( &passkey, pHostInterface_packet->_data, 3 );
            GuiDriver_Navigation( GUI_NAVIGATION_BOND, ( void* )&passkey );
            break;
        } // case packetType_passDisplay:

        case packetType_otapCompleted:
            boootloader_QueueMsgPut( pHostInterface_packet );
            break;

        case packetType_otapFailed:
            power_ResetKW40();
            boootloader_QueueMsgPut( pHostInterface_packet );
            break;

        case packetType_buttonsGroupSendActive:
            buttonsGroup_ActiveUpdate( pHostInterface_packet->_data[0] );
            break;

        case packetType_advModeSend:
            bluetooth_AdvModeUpdate( pHostInterface_packet->_data[0] );
            break;

        case packetType_linkStateSend:
            RTC_UpdateAlarm();
            haptic_Vibrate();
            
            if ( isWakingTouch == true )
            {
                isWakingTouch = false;
                power_TurnScreenOn();
            }
            
            watch_LinkStateUpdate( pHostInterface_packet->_data[0] );
            break;

        case packetType_buildVersion:
            hexiwear_kw40version.ver_majorNumber
                = pHostInterface_packet->_data[0];
            hexiwear_kw40version.ver_minorNumber
                = pHostInterface_packet->_data[1];
            hexiwear_kw40version.ver_patchNumber
                = pHostInterface_packet->_data[2];
            HEXIWEAR_UpdateVersion();
            break;

        default:
            break;
    }
}

// Gets a message from the rx queue.
static osa_status_t HostInterface_RxQueueMsgGet(
    hostInterface_packet_t * pHostInterface_packet )
{
    osa_status_t status;
    
    status = OSA_MsgQGet( hostInterface_rxQueueHnd, pHostInterface_packet,
        gHostInterface_waitTimeout );

    if( status == kStatus_OSA_Error )
        error_catch(2);
    
    return status;
}

// Host interface rx task.
// Handles the receiving data packet.
static void HostInterface_RxTask( task_param_t param )
{
    hostInterface_packet_t tmpPkt;
    osa_status_t status;
    
    while( 1 )
    {
        status = HostInterface_RxQueueMsgGet( &tmpPkt );
        
        if( status == kStatus_OSA_Success )
        {
#ifdef gHostInterface_TxConfirmationEnable
            // Acknowledge the packet reception.
            if( ( tmpPkt.start2 & 0x01 ) == 1 )
            {
                    HostInterface_EventSendOkPacketSet();
            }
#endif

            // Handle the packet's content.
            PacketHandler( &tmpPkt );
        }
    }
}

// UART4_RX_TX interrupt handler.
void UART4IntHandler() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
{
    if( RIE_UART4_C2_bit && RXEDGIF_UART4_S2_bit )
    {
        // clear the active edge interrupt flag
        RXEDGIF_UART4_S2_bit = 1;

        switch( power_GetCurrentMode() )
        {
            case POWER_CURRENT_MODE_NORMAL:
            {
                // regular work mode, do nothing
                break;
            }

            // if we were in shallow sleep mode, just turn the OLED ON
            case POWER_CURRENT_MODE_SLEEP_SHALLOW:
            {
                HostInterface_SetWakingTouch();
                power_SetCurrentMode( POWER_CURRENT_MODE_NORMAL );
                break;
            }

            case POWER_CURRENT_MODE_SLEEP_TOTAL:
            {
                HostInterface_SetWakingTouch();
                power_SetCurrentMode( POWER_CURRENT_MODE_NORMAL );

                if( power_SetWakeSource( POWER_WAKE_SRC_USER )
                    != POWER_STATUS_SUCCESS )
                {
                    asm NOP;
                }
                break;
            }

            // special consideration is also required
            // for the sensor tag sleep mode, since we might not be
            // actually sleeping when UART interrupt occurs
            case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
            {
                HostInterface_SetWakingTouch();
                power_SetCurrentMode( POWER_CURRENT_MODE_NORMAL );

                if( power_SetWakeSource( POWER_WAKE_SRC_USER )
                    == POWER_STATUS_SUCCESS )
                {
                }
                else
                {
                    asm NOP;
                }
                break;
            }
        }
    }

    if( ( RIE_UART4_C2_bit == 1 ) && ( RDRF_UART4_S1_bit == 1 ) )
        HostInterface_RxCallback();

    if( ( RIE_UART4_C2_bit == 1 ) && ( TDRE_UART4_S1_bit == 1 ) )
        HostInterface_TxCallback();
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises host interface rx.
osa_status_t HostInterface_RxInit()
{
    osa_status_t status;

    rxBuff = ( uint8_t* )&hostInterface_rxPacket;

    // Enable UART4_RX_TX interrupt.
    UART4_bit = 1;
    UART4_C2 |= 1 << 5;
    NVIC_IntEnable( IVT_INT_UART4_RX_TX );
    // Set the interrupt priority level.
    HEXIWEAR_SetIntPriority(IVT_INT_UART4_RX_TX, gHostInterfaceIRQPriority_c);
    
    // Create Rx Message Queue
    hostInterface_rxQueueHnd = OSA_MsgQCreate(
        hostInterface_rxQueue,
        gHostInterface_msgNum,
        sizeof( hostInterface_packet_t ) / sizeof( uint32_t ) );
        
    if( hostInterface_rxQueueHnd == NULL )
    {
        error_catch( 3 );
    }

    // Create Rx Task
    status = OSA_TaskCreate (
        HostInterface_RxTask,
        "HostInterface_RxTask",
        3 * gHostInterfaceRxTaskStackSize_c,
        NULL,
        gHostInterfaceRxPriority_c,
        NULL,
        false,
        &hexiwear_intf_RX_handler );
      
    if( status != kStatus_OSA_Success )
    {
        error_catch( 3 );
    }
    
    return status;
}

// Puts a message to the rx queue.
osa_status_t HostInterface_RxQueueMsgPut(
    hostInterface_packet_t* pHostInterface_packet )
{
    osa_status_t status;
    
    status = OSA_MsgQPut( hostInterface_rxQueueHnd, pHostInterface_packet );
    
    if( status == kStatus_OSA_Error )
    {
        error_catch( 2 );
    }
    
    return status;
}

// Host interface rx callback.
// Implements interface state machine.
void HostInterface_RxCallback()
{
    static uint8_t byteCount;
    uint8_t tmp;

    tmp = UART4_S1;
    *rxBuff = UART4_D;

    switch( hostInterface_rxState )
    {
        case hostInterface_rxState_idle:
            if( hostInterface_rxPacket.start1 == gHostInterface_startByte1 )
            {
                hostInterface_rxState++;
                rxBuff++;
            }
            break;

        case hostInterface_rxState_headerReceived:
            if( ( hostInterface_rxPacket.start1 != gHostInterface_startByte1 )
                || ( gHostInterface_startByte2
                    != ( hostInterface_rxPacket.start2 & 0xFE ) )
                || ( hostInterface_rxPacket.length > gHostInterface_dataSize ) )
            {
                // return to idle state
                hostInterface_rxState = hostInterface_rxState_idle;
                // reset the RX buffer pointer
                rxBuff = ( uint8_t* )&hostInterface_rxPacket;
            }
            else
            {
                // advance the buffer pointer
                rxBuff++;

                if( hostInterface_rxPacket.length == 0 )
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

        case hostInterface_rxState_dataWait:
            byteCount++;
            rxBuff++;

            // if we reached the byte-count
            if( hostInterface_rxPacket.length == byteCount )
            {
                // advance to "wait-trailer-bit" state
                hostInterface_rxState = hostInterface_rxState_trailerWait;
            }

            break;

        case hostInterface_rxState_trailerWait:
            if ( gHostInterface_trailerByte == *rxBuff )
            {

#if defined (gHostInterface_RxConfirmationEnable)
                if( hostInterface_rxPacket.type == packetType_OK )
                {
                    // announce that OK packet is received successfully
                    HostInterface_EventConfirmPacketSet();
                }
                else
#endif
                {
                    // else, put the packet into the RX queue
                    HostInterface_RxQueueMsgPut( &hostInterface_rxPacket );
                }
            }

            // go back to the idle state
            hostInterface_rxState = hostInterface_rxState_idle;
            // reset the RX buffer pointer
            rxBuff = ( uint8_t * )&hostInterface_rxPacket;
            break;

        default:
            hostInterface_rxState++;
            rxBuff++;
            break;
    }
}

// Mark registered touch as the first after wake-up.
void HostInterface_SetWakingTouch()
{
    isWakingTouch = true;
}