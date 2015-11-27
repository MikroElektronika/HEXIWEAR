/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include "EmbeddedTypes.h"
#include "fsl_osa_ext.h"
#include "board.h"
#include "fsl_lpuart_dma_driver.h"
#include "fsl_lpuart_driver.h"
#include "fsl_dma_driver.h"
#include "panic.h"
#include "debug.h"
#include "host_mcu_interface.h"
#include "fsl_interrupt_manager.h"

#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gatt_database.h"
#include "gap_interface.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_handles.h"

#include "battery_interface.h"
#include "motion_service.h"
#include "weather_service.h"
#include "health_service.h"
#include "alert_service.h"

/*! *********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static hostInterface_packet_t   hostInterface_rxPacket;
static task_handler_t           gHostInterface_RxHandlerTaskId;
static msg_queue_handler_t      hostInterface_rxQueueHnd;

typedef enum
{
    hostInterface_rxState_idle          = 0,
    hostInterface_rxState_hederReceived = 3,
    hostInterface_rxState_dataWait      = 4,
    hostInterface_rxState_trailerWait   = 5,

}
hostInterface_rxState_t;
static hostInterface_rxState_t  hostInterface_rxState = hostInterface_rxState_idle;

// Declare the message queue
MSG_QUEUE_DECLARE(hostInterface_rxQueue, gHostInterface_msgNum, sizeof(hostInterface_packet_t));

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

static void HostInterface_RxPacketHandler(hostInterface_packet_t * pHostInterface_packet);
static osaStatus_t HostInterface_RxQueueMsgGet(hostInterface_packet_t * pHostInterface_packet);
static void HostInterface_RxHandlerTask(task_param_t param);
static void HostInterface_RxCallback(uint32_t instance, void *lpuartState);

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function handle packet which is arrived through uart.
 *
 */

static void HostInterface_RxPacketHandler(hostInterface_packet_t * pHostInterface_packet)
{
    switch(pHostInterface_packet->type)
    {
            
        /////////////////////////////////////////////////////////////////////////////
        // Batterry Service
        case packetType_batteryLevel:
        {
            Bas_RecordBatteryMeasurement (service_battery, pHostInterface_packet->data[0]);
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Motion Service
        case packetType_accel:
        case packetType_gyro:
        case packetType_magnet:
        {
            
            Mos_RecordMeasurement(pHostInterface_packet->type, pHostInterface_packet->data);
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Weather Service
        case packetType_ambiLight:
        case packetType_temperature:
        case packetType_humidity:
        case packetType_pressure:
        {
            Wes_RecordMeasurement(pHostInterface_packet->type, pHostInterface_packet->data);
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Health Service
        case packetType_heartRate:
        case packetType_steps:
        case packetType_activityTime:
        {
            Hes_RecordMeasurement(pHostInterface_packet->type, pHostInterface_packet->data);
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Alert Service
        case packetType_alertOut:
        {
            Als_RecordOutAlert(pHostInterface_packet->data);
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        default :  
        {
            ;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function is called when data is received though UART.
 *
 *    @param    param
 *
 */

osaStatus_t HostInterface_RxInit(void)
{
    osa_status_t status;
    
    LPUART_DRV_InstallRxCallback(gHostInterface_instance, HostInterface_RxCallback, (uint8_t *)&hostInterface_rxPacket, 0, true);
    
    // Create Rx Message Queue
    hostInterface_rxQueueHnd = OSA_MsgQCreate(hostInterface_rxQueue, gHostInterface_msgNum, sizeof(hostInterface_packet_t) / 4);
    if(hostInterface_rxQueueHnd == 0)
    {
        panic(0,0,0,0);
        return osaStatus_Error;
    }
    
    // Create Rx Handler Task
    status = OSA_TaskCreate(HostInterface_RxHandlerTask, "HostInterface_RxHandlerTask", gHostInterfaceRxTaskStackSize_c, 0,
                            gHostInterfaceRxHandlerPriority_c, (task_param_t)NULL, FALSE, &gHostInterface_RxHandlerTaskId); 
    if( kStatus_OSA_Success != status )
    {
        panic(0,0,0,0);
        return (osaStatus_t)status;
    }
  
    return (osaStatus_t)status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void HostInterface_RxCallback(uint32_t instance, void *lpuartState)
{
    lpuart_status_t status;
    uint32_t        bytesRemaining;
    lpuart_state_t *tmpLpuartState = (lpuart_state_t*)lpuartState;
    static uint8_t  dataBytesCnt;
    
    switch(hostInterface_rxState)
    {
        case hostInterface_rxState_idle:
        {
            if(hostInterface_rxPacket.start1 == gHostInterface_startByte1)
            {
                hostInterface_rxState++;
                tmpLpuartState->rxBuff++;
            }
        }
        break;
        
        case hostInterface_rxState_hederReceived:
        {
            if(
                (hostInterface_rxPacket.start1 != gHostInterface_startByte1) ||
                (hostInterface_rxPacket.start2 != gHostInterface_startByte2) ||
                (hostInterface_rxPacket.length > gHostInterface_dataSize)
               )
            {
                hostInterface_rxState = hostInterface_rxState_idle;
                tmpLpuartState->rxBuff = (uint8_t *) &hostInterface_rxPacket;
            }
            else
            {
                tmpLpuartState->rxBuff++;
                hostInterface_rxState++;
                if(hostInterface_rxPacket.length == 0)
                {
                    hostInterface_rxState++;
                }
                else
                {
                    dataBytesCnt = 0;
                }
            }
        }
        break;
        
        case hostInterface_rxState_dataWait:
        {
            dataBytesCnt++;
            tmpLpuartState->rxBuff++;
            if(dataBytesCnt == hostInterface_rxPacket.length)
            {
                hostInterface_rxState++;
            }
        }
        break;
        
        case hostInterface_rxState_trailerWait:
        {
            if(*(tmpLpuartState->rxBuff) == gHostInterface_trailerByte)
            {
#if  gHostInterface_RxConfirmationEnable //..........................
                if(hostInterface_rxPacket.type == packetType_OK) 
                {
                    HostInterface_EventConfirmPacketSet();
                    HostInterface_EventConfirmAttPacketSet();
                }
                else
#endif //............................................................
                {
                    HostInterface_RxQueueMsgPut((hostInterface_packet_t *)&hostInterface_rxPacket);
                }
            }
            hostInterface_rxState = hostInterface_rxState_idle;
            tmpLpuartState->rxBuff = (uint8_t *) &hostInterface_rxPacket;
        }
        break;
        
        default:
        {
            hostInterface_rxState++;
            tmpLpuartState->rxBuff++;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function puts a message to the end of the Tx message queue.
 *
 *    @param    pHostInterface_packet   Packet that will be placed into Tx message queue.
 *
 *    @return                          osaStatus_Success  Message successfully put into the queue.
 *                                     osaStatus_Error    Process fail.
 */

osaStatus_t HostInterface_RxQueueMsgPut(hostInterface_packet_t * pHostInterface_packet)
{
    osa_status_t status;
    
    status = OSA_MsgQPut(hostInterface_rxQueueHnd, (hostInterface_packet_t *)pHostInterface_packet);
    if(status == kStatus_OSA_Error)
    {
        panic(0,0,0,0);
    }
    
    return (osaStatus_t) status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    This function gets a message from the head of the Tx message queue.
 *
 *    @param    pHostInterface_packet   Pointer to a memory to save the packet.
 *
 *    @return                          osaStatus_Success  Message successfully obtained from the queue.
 *                                     osaStatus_Error    Process fail.
 */

static osaStatus_t HostInterface_RxQueueMsgGet(hostInterface_packet_t * pHostInterface_packet)
{
    osa_status_t status;
    
    status = OSA_MsgQGet(hostInterface_rxQueueHnd, (hostInterface_packet_t *)pHostInterface_packet, gHostInterface_waitTimeout);
    if(status == kStatus_OSA_Error)
    {
        panic(0,0,0,0);
    }
    return (osaStatus_t) status;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Host MCU Interface Tx task.
 *
 *    @param   param   initialData
 */

hostInterface_packet_t tmpHostInterface_packet;
static void HostInterface_RxHandlerTask(task_param_t param)
{
    
    osaStatus_t status;
    
    
    while(1)
    {
        status = HostInterface_RxQueueMsgGet(&tmpHostInterface_packet);
        if(status == osaStatus_Success)
        {
#ifdef gHostInterface_TxConfirmationEnable //.....................
            HostInterface_EventSendOkPacketSet();
#endif //..........................................................
            HostInterface_RxPacketHandler(&tmpHostInterface_packet);
        }
    }
    
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

