/**
 *    @file host_mcu_interface_rx.c
 */

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
#include "Flash_Adapter.h"
#include "app.h"

#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gatt_database.h"
#include "gap_interface.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_handles.h"

#include "tsi.h"
#include "battery_interface.h"
#include "motion_service.h"
#include "weather_service.h"
#include "health_service.h"
#include "alert_service.h"
#include "appMode_service.h"
#include "PWR_Interface.h" 

/************************************************************************************
*************************************************************************************
* Extern functions
*************************************************************************************
************************************************************************************/
extern void ResetMCU(void);

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static hostInterface_packet_t   hostInterface_rxPacket;    /**< Rx host interface packet. */
static hostInterface_packet_t   hostInterface_txPacket =   /**< Tx host interface packet. */
{
    .start1 = gHostInterface_startByte1, 
    .start2 = gHostInterface_startByte2,
};

static msg_queue_handler_t      hostInterface_rxQueueHnd;  /**<  Rx queue handler. */

static task_handler_t           gHostInterface_RxHandlerTaskId; /**< Rx task ID. */

/**Possible states of receive driver. */
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

/************************************************************************************
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
 *    @param   pHostInterface_packet   Received packet.
 */

static void HostInterface_RxPacketHandler(hostInterface_packet_t * pHostInterface_packet)
{
    // Check packet type.
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
        case packetType_calorie:
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
        // App Mode Service
        case packetType_appMode:
        {
            Apps_RecordState(pHostInterface_packet->data);
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Start OTAP for KW40 Mcu
        case packetType_otapKW40Started:
        {
            // Get device parameters from FLASH.
            NV_ReadHWParameters(&gHardwareParameters);
            gHardwareParameters.deviceState = (uint8_t) deviceState_otapStartedKW40;
            NV_WriteHWParameters(&gHardwareParameters);
            ResetMCU();
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Start OTAP for MK64 Mcu
        case packetType_otapMK64Started:
        {
            // Get device parameters from FLASH.
            NV_ReadHWParameters(&gHardwareParameters);
            gHardwareParameters.deviceState = (uint8_t) deviceState_otapStartedMK64;
            NV_WriteHWParameters(&gHardwareParameters);
            ResetMCU();
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Send info about active slider.
        case packetType_tsiGroupGetActive:
        {
            hostInterface_txPacket.type    = packetType_tsiGroupSendActive;
            hostInterface_txPacket.length  = 1;
            hostInterface_txPacket.data[0] = TouchSense_GetActiveGroup();
            hostInterface_txPacket.data[1] = gHostInterface_trailerByte;
            
            while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != osaStatus_Success)
            {
                OSA_TimeDelay(5);
            }
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Toggle Active slider.
        case packetType_tsiGroupToggleActive:
        {
            tsiGroup_select_t tsiGroup; 
            
            // Read current active group of electrodes, and toggle it.
            tsiGroup = TouchSense_GetActiveGroup();
            tsiGroup = (tsiGroup == tsiGroup_select_left) ? tsiGroup_select_right : tsiGroup_select_left;
            
            // Get device parameters from FLASH.
            NV_ReadHWParameters(&gHardwareParameters);
            // Save new active to FLASH.
            gHardwareParameters.tsiGroupActive = (uint8_t) tsiGroup;
            NV_WriteHWParameters(&gHardwareParameters);
            
            // Set corresponding group to be active.
            TouchSense_SetActiveGroup(tsiGroup);
            
            // Send packet to host.
            hostInterface_txPacket.type    = packetType_tsiGroupSendActive;
            hostInterface_txPacket.length  = 1;
            hostInterface_txPacket.data[0] = tsiGroup;
            hostInterface_txPacket.data[1] = gHostInterface_trailerByte;
            while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != osaStatus_Success)
            {
                OSA_TimeDelay(5);
            }
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Send info about advertising mode.
        case packetType_advModeGet:
        {
            hostInterface_txPacket.type    = packetType_advModeSend;
            hostInterface_txPacket.length  = 1;
            hostInterface_txPacket.data[0] = BleApp_GetAdvMode();
            hostInterface_txPacket.data[1] = gHostInterface_trailerByte;
            
            while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != osaStatus_Success)
            {
                OSA_TimeDelay(5);
            }
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Toggle advertising mode.
        case packetType_advModeToggle:
        {
            advMode_t advMode; 
            
            // Read current advertising mode, and toggle it.
            advMode = BleApp_GetAdvMode();
            advMode = (advMode == advMode_disable) ? advMode_enable : advMode_disable;
            
            // Send packet to host.
            hostInterface_txPacket.type    = packetType_advModeSend;
            hostInterface_txPacket.length  = 1;
            hostInterface_txPacket.data[0] = advMode;
            hostInterface_txPacket.data[1] = gHostInterface_trailerByte;
            while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != osaStatus_Success)
            {
                OSA_TimeDelay(5);
            }
            
            OSA_TimeDelay(10);
            
            // Enable/Disable adverdising.
            if(advMode == advMode_enable)
            {
                BleApp_AdvEnable();
            }
            else
            {
                BleApp_AdvDisable();
            }
            
            break;   
        }
                
        /////////////////////////////////////////////////////////////////////////////
        // Send info about link state.
        case packetType_linkStateGet:
        {
            hostInterface_txPacket.type    = packetType_linkStateSend;
            hostInterface_txPacket.length  = 1;
            hostInterface_txPacket.data[0] = BleApp_GetLinkState();
            hostInterface_txPacket.data[1] = gHostInterface_trailerByte;
            
            while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != osaStatus_Success)
            {
                OSA_TimeDelay(5);
            }
            break;   
        }
        
        /////////////////////////////////////////////////////////////////////////////
        // Read image version of MK64 and send image version for KW40.
        case packetType_buildVersion:
        {   
            uint8_t fwRevision[12] = "0.0.0/0.0.0";
            
            // Get device parameters from FLASH.
            NV_ReadHWParameters(&gHardwareParameters);
            // Write image version to hw params.
            FLib_MemCpy (gHardwareParameters.imageVersionMK64, (uint8_t*)pHostInterface_packet->data, 3);
            NV_WriteHWParameters(&gHardwareParameters);
            
            // Write image version to current var.
            FLib_MemCpy (currentImageVerMK64, (uint8_t*)pHostInterface_packet->data, 3);
            
            // Send build version for KW40 to host MCU.
            hostInterface_txPacket.type    = packetType_buildVersion;
            hostInterface_txPacket.length  = 3;
            hostInterface_txPacket.data[0] = currentImageVerKW40[0];
            hostInterface_txPacket.data[1] = currentImageVerKW40[1];
            hostInterface_txPacket.data[2] = currentImageVerKW40[2];
            hostInterface_txPacket.data[3] = gHostInterface_trailerByte;
            while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != osaStatus_Success)
            {
                OSA_TimeDelay(5);
            }
            
            // Update database
            fwRevision[0]  = currentImageVerMK64[0] + '0';
            fwRevision[2]  = currentImageVerMK64[1] + '0';
            fwRevision[4]  = currentImageVerMK64[2] + '0';
            fwRevision[6]  = currentImageVerKW40[0] + '0';
            fwRevision[8]  = currentImageVerKW40[1] + '0';
            fwRevision[10] = currentImageVerKW40[2] + '0';
            GattDb_WriteAttribute(value_fw_rev, 11, fwRevision);
            
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
 *    Initialize Rx path of host interface driver.
 *
 *    @return                osaStatus_Success    Success
 *    @return                osaStatus_Error      Failed
 *    @return                osaStatus_Timeout    Timeout occurs while waiting
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
/**
 *    The LPUART receive callback.
 *
 *    @param   instance      The LPUART instance number.
 *    @param   lpuartState   LPUART driver state structure.
 */

static void HostInterface_RxCallback(uint32_t instance, void *lpuartState)
{
    lpuart_status_t status;
    uint32_t        bytesRemaining;
    lpuart_state_t *tmpLpuartState = (lpuart_state_t*)lpuartState;
    static uint8_t  dataBytesCnt;
    
    // Check current state of receiver.
    switch(hostInterface_rxState)
    {
        case hostInterface_rxState_idle:
        {
            // Wait for start1 byte.
            if(hostInterface_rxPacket.start1 == gHostInterface_startByte1)
            {
                hostInterface_rxState++;
                tmpLpuartState->rxBuff++;
            }
        }
        break;
        
        // Complete header received.
        case hostInterface_rxState_hederReceived:
        {
            // Check header.
            if(
                (hostInterface_rxPacket.start1 != gHostInterface_startByte1) ||
                ((hostInterface_rxPacket.start2 & 0xFE) != gHostInterface_startByte2) ||
                (hostInterface_rxPacket.length > gHostInterface_dataSize)
               )
            {
                // Header is incorrect, go to the idle state.
                hostInterface_rxState = hostInterface_rxState_idle;
                tmpLpuartState->rxBuff = (uint8_t *) &hostInterface_rxPacket;
            }
            else
            {
                // Header is correct. If there is data, wait for it.
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
        
        // Receiving bytes of data.
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
        
        // Wait for trailer byte.
        case hostInterface_rxState_trailerWait:
        {
            if(*(tmpLpuartState->rxBuff) == gHostInterface_trailerByte)
            {
#if  gHostInterface_RxConfirmationEnable //..........................
                // If we received confirmation packet, set proper flags.
                if(hostInterface_rxPacket.type == packetType_OK) 
                {
                    HostInterface_EventConfirmPacketSet();
                    HostInterface_EventConfirmAttPacketSet();
                }
                // Put message to corresponding queue.
                else
#endif //............................................................
                {
                    HostInterface_RxQueueMsgPut((hostInterface_packet_t *)&hostInterface_rxPacket);
                }
            }
            
            // Go to idle state.
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
 *    This function puts a message to the end of the Rx message queue.
 *
 *    @param    pHostInterface_packet   Packet that will be placed into Tx message queue.
 *
 *    @return                          osaStatus_Success  Message successfully put into the queue.
 *    @return                          osaStatus_Error    Process fail.
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
 *    This function gets a message from the head of the Rx message queue.
 *
 *    @param    pHostInterface_packet   Pointer to a memory to save the packet.
 *
 *    @return                          osaStatus_Success  Message successfully obtained from the queue.
 *    @return                          osaStatus_Error    Process fail.
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
 *    Host MCU Interface Rx task.
 *
 *    @param   param   initialData
 */

hostInterface_packet_t tmpHostInterface_packet;
static void HostInterface_RxHandlerTask(task_param_t param)
{
    osaStatus_t status;
       
    while(1)
    {
        // Wait for incoming packets.
        status = HostInterface_RxQueueMsgGet(&tmpHostInterface_packet);
        
        if(status == osaStatus_Success)
        {
#ifdef gHostInterface_TxConfirmationEnable //.....................
            // Check if there is need to send confirmation.
            if((tmpHostInterface_packet.start2 & 1) == 1)
            {
                HostInterface_EventSendOkPacketSet();
            }
#endif //..........................................................
            HostInterface_RxPacketHandler(&tmpHostInterface_packet);
        }
    }
    
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

