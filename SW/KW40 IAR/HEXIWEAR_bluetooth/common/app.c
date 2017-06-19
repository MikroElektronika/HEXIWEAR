/**
 *    @file app.c
 */

/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
* \file app.c
* This file is the source file for the Hexiwear application
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
*/

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
/* Framework / Drivers */
#include "RNG_interface.h"
#include "Keyboard.h"
#include "Led.h"
#include "TimersManager.h"
#include "SerialManager.h"
#include "MemManager.h"
#include "FunctionLib.h"
#include "fsl_os_abstraction.h"
#include "panic.h"
#include "board.h"
#include "OtaSupport.h"
#include "PWR_Interface.h"
#include "Flash_Adapter.h"
#include "RNG_Interface.h"

/* BLE Host Stack */
#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gatt_database.h"
#include "gap_interface.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_handles.h"

/* Profile / Services */
#include "otap_interface.h"
#include "battery_interface.h"
#include "device_info_interface.h"
#include "motion_service.h"
#include "weather_service.h"
#include "health_service.h"
#include "alert_service.h"

#include "client_ancs.h"
#include "ApplMain.h"
#include "app.h"
#include "debug.h"
#include "tsi.h"
#include "host_mcu_interface.h"
#include "Eeprom.h"
#include "fsl_power_manager.h"
#include "fsl_llwu_hal.h"
#include "controller_interface.h"
#include "l2ca_interface.h"

/************************************************************************************
*************************************************************************************
* Extern functions
*************************************************************************************
************************************************************************************/
extern void ResetMCU(void);

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/


/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

typedef enum
{
#if gBondingSupported_d
    fastWhiteListAdvState_c,
#endif
    fastAdvState_c,
    slowAdvState_c
}
advType_t;

typedef struct advState_tag{
    bool_t      advOn;
    advType_t   advType;
}
advState_t;

typedef enum otapClientState_tag
{
    mOtapClientStateIdle_c                  = 0x00,
    mOtapClientStateDownloadingImage_c      = 0x01,
    mOtapClientStateImageDownloadComplete_c = 0x02,
} 
otapClientState_t;

/*! Structure containing the OTAP Client functional data. */
typedef struct otapClientAppData_tag
{
    otapClientState_t           state;
    const uint8_t               currentImgId[gOtap_ImageIdFieldSize_c];         /*!< Id of the currently running image on the OTAP Client */
    const uint8_t               currentImgVer[gOtap_ImageVersionFieldSize_c];   /*!< Version of the currently running image on the OTAP Client */
    deviceId_t                  peerOtapServer;                                 /*!< Device id of the OTAP Server a new image is being downloaded from. */
    uint8_t                     imgId[gOtap_ImageIdFieldSize_c];                /*!< Id of the image being downloaded from the OTAP Server */
    uint8_t                     imgVer[gOtap_ImageVersionFieldSize_c];          /*!< Version of the image being downloaded from the OTAP Server */
    uint32_t                    imgSize;                                        /*!< Size of the image file being downloaded from the OTAP Server */
    uint16_t                    imgComputedCrc;                                 /*!< Computed 16 bit CRC of the image file used in this implementation. */
    uint16_t                    imgReceivedCrc;                                 /*!< Received 16 bit CRC of the image file used in this implementation. */
    uint8_t                     imgSectorBitmap[gBootData_SectorsBitmap_Size_c];/*!< Flash sector bitmap for the recieved image for the current implementation. */
    uint32_t                    currentPos;                                     /*!< Current position of the file being downloaded. */
    uint16_t                    chunkSize;                                      /*!< Current chunk size for the image file transfer. */
    uint16_t                    chunkSeqNum;                                    /*!< Current chunk sequence number for the block being transferred. */
    uint16_t                    totalBlockChunks;                               /*!< Total number of chunks for the block being transferred. */
    uint32_t                    totalBlockSize;                                 /*!< Total size of the block which was requested. may be smaller than totalBlockChunks * chunkSize. */
    const otapTransferMethod_t  transferMethod;                                 /*!< Currently used transfer method for the OTAP Image File */
    uint16_t                    l2capChannelOrPsm;                              /*!< L2CAP Channel or PSM used for the transfer of the image file: channel 0x0004 for ATT, application specific PSM for CoC. */
    bool_t                      serverWrittenCccd;                              /*!< The OTAP Server has written the CCCD to receive commands from the OTAp Client. */
    otapCmdIdt_t                lastCmdSentToOtapServer;                        /*!< The last command sent to the OTAP Server for which an Indication is expected. */
} otapClientAppData_t;
  
static deviceState_t deviceState = deviceState_watch;

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/* Host Stack Data*/
static bleDeviceAddress_t   maBleDeviceAddress;
static deviceId_t           mPeerDeviceId = gInvalidDeviceId_c;

/* Adv Parmeters */
static advState_t  mAdvState;

/* Adv mode (on / off) */
static advMode_t advMode = advMode_enable;

static gapAdvertisingParameters_t advParams = gGapDefaultAdvertisingParameters_d;

#if gBondingSupported_d
static bleDeviceAddress_t   maPeerDeviceAddress;
static uint8_t mcBondedDevices = 0;
static bleAddressType_t     mPeerDeviceAddressType;
static uint32_t smpPasskey = 0;
#endif

typedef enum 
{
    kGpioHostWakeup = GPIO_MAKE_PIN(GPIOB_IDX, 0),   
    kGpioHostInt = GPIO_MAKE_PIN(GPIOB_IDX, 18),   
}
bleApp_pins;

/** Wakeup pin configuration. */
static gpio_input_pin_t bleApp_wakeUpPin = 
{
    .isPullEnable = false,
    .pullSelect = kPortPullUp,
    .isPassiveFilterEnabled = false,
    .interrupt = kPortIntEitherEdge,
};

/** Interrupt pin configuration. */
static gpio_input_pin_user_config_t bleApp_intPin =
{
    .pinName = kGpioHostInt,
    .config.isPullEnable = false,
    .config.pullSelect = kPortPullDown,
    .config.isPassiveFilterEnabled = false,
    .config.interrupt = kPortIntLogicZero,
};

/* Service Data*/
static basConfig_t      basServiceConfig    = {service_battery, 100};
static disConfig_t      disServiceConfig    = {service_device_info};
static otapClientConfig_t otapServiceConfig = {service_otap};

static uint16_t otapWriteNotifHandles[]     = {value_otap_control_point, value_otap_data};
static uint16_t writeNotifHandles[]         = {value_alertIn};

/* Application specific data*/
static bool_t mContactStatus = TRUE;

extern uint8_t gAppSerMgrIf;

static tmrTimerID_t goToSleepTimerId;

static bool_t sleepFalg = false;

/*! OTAP Client data structure.
 *  Contains current image information and state informations
 *  regarding the image download procedure. */
static otapClientAppData_t     otapClientData = 
{
    .state = mOtapClientStateIdle_c,
    .currentImgId = {0x00, 0x00},          // Current Running Image Id - should be 0x0000
    .currentImgVer = {0x01, 0x00, 0x00,    // Build Version
                      0x41,                // Stack Version
                      0x11, 0x11, 0x11,    // Hardware Id
                      0x01                 // Manufacturer Id
                     },                    // Current Image Version
    .peerOtapServer = gInvalidDeviceId_c,
    .imgId = {0x00, 0x00},
    .imgVer = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .imgSize = 0,
    .imgComputedCrc = 0,
    .imgReceivedCrc = 0,
    .imgSectorBitmap = {0x00},
    .currentPos = 0,
    .chunkSize = 0,
    .chunkSeqNum = 0,
    .totalBlockChunks = 0,
    .totalBlockSize = 0,
    .transferMethod = gOtapTransferMethodAtt_c,   // The default transfer method is ATT
    .l2capChannelOrPsm = gL2capCidAtt_c,   // The default L2CAP channel is the ATT Channel
    .lastCmdSentToOtapServer = gOtapCmdIdNoCommand_c,
};

static const uint8_t imageIdAll[gOtap_ImageIdFieldSize_c]  = {0x00, 0x00};
static const uint8_t imageIdKW40[gOtap_ImageIdFieldSize_c] = {0x01, 0x00};
static const uint8_t imageIdMK64[gOtap_ImageIdFieldSize_c] = {0x02, 0x00};

uint8_t currentImageVerMK64[gOtap_ImageVersionFieldSize_c] = 
{
    0x01, 0x00, 0x00,    // Build Version
    0x41,                // Stack Version
    0x11, 0x11, 0x11,    // Hardware Id
    0x01                 // Manufacturer Id
};

uint8_t currentImageVerKW40[gOtap_ImageVersionFieldSize_c] = 
{
    0x01, 0x00, 0x00,    // Build Version
    0x41,                // Stack Version
    0x11, 0x11, 0x11,    // Hardware Id
    0x01                 // Manufacturer Id
};

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/* Gatt and Att callbacks */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent);
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);
static void BleApp_Config();
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent);

static void BleApp_CccdWritten (deviceId_t deviceId, uint16_t handle, gattCccdFlags_t cccd);
static void BleApp_AttributeWritten(deviceId_t deviceId, uint16_t handle, uint16_t length, uint8_t *pValue);
static void BleApp_AttributeWrittenWithoutResponse (deviceId_t deviceId, uint16_t handle, uint16_t length, uint8_t* pValue);
static void BleApp_HandleValueConfirmation (deviceId_t deviceId);
static void BatteryMeasurementTimerCallback (void *);
static void BleApp_AddToWhiteList(void);

static void BleApp_Advertise(void);
static void Ble_StartServices(void);

/* OTAP Client functions */
/* Commands received from the OTAP Server */
static void OtapClient_HandleDataChunk (deviceId_t deviceId, uint16_t length, uint8_t* pData);
static void OtapClient_HandleNewImageNotification (deviceId_t deviceId, uint16_t length, uint8_t* pValue);
static void OtapClient_HandleNewImageInfoResponse (deviceId_t deviceId, uint16_t length, uint8_t* pValue);
static void OtapClient_HandleErrorNotification (deviceId_t deviceId, uint16_t length, uint8_t* pValue);
/* Confirmations of commands sent to the OTAP Server */
static void OtapClient_HandleNewImageInfoRequestConfirmation (deviceId_t deviceId);
static void OtapClient_HandleImageBlockRequestConfirmation (deviceId_t deviceId);
static void OtapClient_HandleImageTransferCompleteConfirmation (deviceId_t deviceId);
static void OtapClient_HandleErrorNotificationConfirmation (deviceId_t deviceId);
static void OtapClient_HandleStopImageTransferConfirmation (deviceId_t deviceId);
/* Connection and Disconnection events */
static void OtapClient_HandleConnectionEvent (deviceId_t deviceId);
static void OtapClient_HandleDisconnectionEvent (deviceId_t deviceId);
/* Otap Client operations */
static void OtapClient_ContinueImageDownload (deviceId_t deviceId);
static bool_t OtapClient_IsRemoteImageNewer (uint8_t* pRemoteImgId, uint8_t* pRemoteImgVer);
static bool_t OtapClient_CheckRemoteID(uint8_t* pRemoteImgId);
static otapStatus_t OtapClient_IsImageFileHeaderValid (bleOtaImageFileHeader_t* imgFileHeader);

static void OtapClient_Complete(void);
static void OtapClient_Fail(void);

static void BleApp_SendConnUpdateReq(deviceId_t peerDeviceId);

/* Timer Callbacks */
static void BleApp_GoToSleepTimerCallback (void *);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Disable advertising.
 */

void BleApp_AdvDisable(void)
{
    NV_ReadHWParameters(&gHardwareParameters);
    gHardwareParameters.advMode = (uint8_t) advMode_disable;
    NV_WriteHWParameters(&gHardwareParameters);
    ResetMCU();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Enable advertising.
 */

void BleApp_AdvEnable(void)
{   
    NV_ReadHWParameters(&gHardwareParameters);
    gHardwareParameters.advMode = (uint8_t) advMode_enable;
    NV_WriteHWParameters(&gHardwareParameters);
    ResetMCU();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Get advertising mode.
 *
 *    @return      Current advertising mode.
 */

advMode_t BleApp_GetAdvMode(void)
{
    return advMode;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Get state of link
 *
 *    @return      Current link state:
 *                                    linkState_disconnected
 *                                    linkState_connected
 */

linkState_t BleApp_GetLinkState(void)
{
    return ((mPeerDeviceId == gInvalidDeviceId_c) ? linkState_disconnected : linkState_connected);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Simple checking of content of data readed from flash.
 *
 *    @param    data   Readed data.
 *    @param    size   Size in bytes.
 *
 *    @return          true     Readed data is valid.
 *                     false    Readed data is not valid.
 */

static bool BleApp_VerifyFlashRead(uint8_t * data, uint16_t size)
{
    for(uint16_t cnt = 0; cnt < size; cnt++)
    {
        if(data[cnt] != 0xFF)   
        {
            return true;
        }
    }
    
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Fill the properties of the firmware images (for both MK64 and KW40 MCUs).
 */

static void BleApp_ReadFwImagProps(void)
{
    uint8_t *imgId;
    uint8_t *imgVer;
    
    // Read image version.
    if(BleApp_VerifyFlashRead((uint8_t *)gHardwareParameters.imageVersionMK64, gOtap_ImageVersionFieldSize_c) == true)
    {
        // Read image version from FLASH.
        FLib_MemCpy((uint8_t *) currentImageVerMK64, (uint8_t *) gHardwareParameters.imageVersionMK64, gOtap_ImageVersionFieldSize_c);
    }
    if(BleApp_VerifyFlashRead((uint8_t *)gHardwareParameters.imageVersionKW40, gOtap_ImageVersionFieldSize_c) == true)
    {
        // Read image version from FLASH.
        FLib_MemCpy((uint8_t *) currentImageVerKW40, (uint8_t *) gHardwareParameters.imageVersionKW40, gOtap_ImageVersionFieldSize_c);
    }
    
    if(deviceState != deviceState_watch)
    {
        if(deviceState == deviceState_otapStartedMK64)
        {
            imgId  = (uint8_t *)imageIdMK64;
            imgVer = (uint8_t *)currentImageVerMK64;
        }
        else if(deviceState == deviceState_otapStartedKW40)
        {
            imgId  = (uint8_t *)imageIdKW40;
            imgVer = (uint8_t *)currentImageVerKW40;
        }
        
        // Set current image id base on current device state.
        FLib_MemCpy((uint8_t *) otapClientData.currentImgId, (uint8_t *) imgId, gOtap_ImageIdFieldSize_c);
        
        // Set current image version.
        FLib_MemCpy((uint8_t *) otapClientData.currentImgVer, (uint8_t *) imgVer, gOtap_ImageVersionFieldSize_c);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Initializes application specific functionality before the BLE stack init.
 */

void BleApp_Init(void)
{
    hostInterface_packet_t hostInterface_packet = 
    {
        .length  = 0,
        .data[0] = gHostInterface_trailerByte,
    };
    
    // Get device parameters from FLASH.
    NV_ReadHWParameters(&gHardwareParameters);
    
    // Check if there is valid device state written into FLASH.
    if(BleApp_VerifyFlashRead((uint8_t *)&gHardwareParameters.deviceState, 1) == true)
    {
        // Get state written into FLASH.
        deviceState = (deviceState_t)gHardwareParameters.deviceState;
    }
    else
    {
        // Default state is "deviceState_watch".
        deviceState = deviceState_watch;
    }
    
        
    // If device state is "deviceState_otapCompleted" or "deviceState_otapFailed",
    // set corresponding packet which will be sent through Host Interface and go to "deviceState_watch".
    if(deviceState == deviceState_otapCompleted)
    {
        hostInterface_packet.type = packetType_otapCompleted;
        deviceState = deviceState_watch;
    }
    else if(deviceState == deviceState_otapFailed)
    {
        hostInterface_packet.type = packetType_otapFailed;
        deviceState = deviceState_watch;
    }
   
        
    // Host interface should be active only in "deviceState_watch" state.
    if(deviceState == deviceState_watch)
    {
        HostInterface_Init();
    }
    
    
    // If device state was changed, update it on FLASH, and send 
    // corresponding packet to the host mcu (as information that OTAP was success or fail)
    if(gHardwareParameters.deviceState != deviceState)
    {
        gHardwareParameters.deviceState = (uint8_t) deviceState_watch;
        NV_WriteHWParameters(&gHardwareParameters);
        while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_packet, true) != osaStatus_Success)
        {
            OSA_TimeDelay(10);
        }
    }
    // If this condition met device is in some of "otapStart" modes.
    // Write "otapFailed" state to FLASH to "protect" from unregular reset.
    // If otap success this state will be overwritten.
    else if(deviceState != deviceState_watch)
    {
        gHardwareParameters.deviceState = (uint8_t) deviceState_otapFailed;
        NV_WriteHWParameters(&gHardwareParameters);
    }
    
    // TSI should be active only in "deviceState_watch" state.
    if(deviceState == deviceState_watch)
    {
        TouchSense_Init();
    }
    
    BleApp_ReadFwImagProps();
    
    // Check if there is valid advertise mode written into FLASH.
    if(BleApp_VerifyFlashRead((uint8_t *)&gHardwareParameters.advMode, 1) == true)
    {
        // Get mode written into FLASH.
        advMode = (advMode_t)gHardwareParameters.advMode;
    }
    else
    {
        // Default mode is "advMode_enable".
        advMode = advMode_enable;
    }
    asm("nop");
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Starts the BLE application.
 */

void BleApp_Start(void)
{
    if(advMode == advMode_disable)
    {
        return;
    }
    else
    {
    #if gBondingSupported_d
        if (mcBondedDevices > 0)
        {
            mAdvState.advType = fastWhiteListAdvState_c;
        }
        else
        {
    #endif
            mAdvState.advType = fastAdvState_c;
    #if gBondingSupported_d
        }
    #endif

        BleApp_Advertise();
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Handles BLE generic callback.
 *
 *    @param   pGenericEvent   Pointer to gapGenericEvent_t.
 */

void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent)
{
    switch (pGenericEvent->eventType)
    {
        case gInitializationComplete_c:
        {
            DebugPrint("InitializationComplete");
            
            BleApp_Config();
            BleApp_Start();
        }
        break;    
            
        case gRandomAddressReady_c :
        {
        #if gBondingSupported_d
            /* Use address read from the controller */
            FLib_MemCpyReverseOrder(maBleDeviceAddress, pGenericEvent->eventData.aAddress, sizeof(bleDeviceAddress_t));
            Gap_SetRandomAddress(maBleDeviceAddress);
        #endif
        }
        break;
        
        case gRandomAddressSet_c:
        {
        #if gBondingSupported_d
            /* Use address read from the controller */
            smpKeys.aAddress = maBleDeviceAddress;
        #endif
        }
        break;
        
        case gPublicAddressRead_c:
        {
            /* Use address read from the controller */
            FLib_MemCpyReverseOrder(maBleDeviceAddress, pGenericEvent->eventData.aAddress, sizeof(bleDeviceAddress_t));
        }
        break;            
         
        
        case gWhiteListCleared_c:
        {
            ;
        }
        break;

        case gAdvertisingDataSetupComplete_c:
        {            
            ;
        }
        break;  
        
        case gAdvertisingParametersSetupComplete_c:
        {
            App_StartAdvertising(BleApp_AdvertisingCallback, BleApp_ConnectionCallback);
        }
        break;         

        case gInternalError_c:
        {
            DebugPrint("GenericCallbackInternalError !!!!!");
            ResetMCU();
            panic(0,0,0,0);
        }
        break;

        default: 
            break;
    }
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Start bluetooth services.
 */

static void Ble_StartServices(void)
{
    /* Start services */
    if(deviceState == deviceState_watch)
    {
        Bas_Start(&basServiceConfig);
        Dis_Start(&disServiceConfig);
        Mos_Start();
        Wes_Start();
        Hes_Start();
        Als_Start();
    }
    else
    {
        OtapCS_Start(&otapServiceConfig);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Subscribe to services.
 *
 *    @param   deviceId   Device ID.
 */

static void Ble_Subscribe(deviceId_t deviceId)
{
    if(deviceState == deviceState_watch)
    {
        Bas_Subscribe(deviceId);
        Mos_Subscribe(deviceId);
        Wes_Subscribe(deviceId);
        Hes_Subscribe(deviceId);
        Als_Subscribe(deviceId);
    }
    else
    {
        OtapCS_Subscribe(deviceId);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Unsubscribe from services.
 */

static void Ble_Unsubscribe(void)
{
    if(deviceState == deviceState_watch)
    {
        Bas_Unsubscribe();
        Mos_Unsubscribe();
        Wes_Unsubscribe();
        Hes_Unsubscribe();
        Als_Unsubscribe();
    }
    else
    {
        OtapCS_Unsubscribe();
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Add bonded devices do white list.
 */

static void BleApp_AddToWhiteList(void)
{
#if gBondingSupported_d    
    bleDeviceAddress_t aBondedDevAdds[gcGapMaximumBondedDevices_d];
      
    bleResult_t result = Gap_GetBondedStaticAddresses(aBondedDevAdds, gcGapMaximumBondedDevices_d, &mcBondedDevices);
    
    if (gBleSuccess_c == result && mcBondedDevices > 0)
    {
        for (uint8_t i = 0; i < mcBondedDevices; i++)
        {
            Gap_AddDeviceToWhiteList(gBleAddrTypePublic_c, aBondedDevAdds[i]);
        }
    }
#endif    
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Configures BLE Stack after initialization. Usually used for
 *    configuring advertising, scanning, white list, services, et al.
 */

static void BleApp_Config()
{  
    uint8_t uniqueID[10];
    uint8_t fwRevision[12] = "1.0.0/1.0.0";  // NOTE: Each field into firmware revision must be single digits!
    uint16_t gpioPin;
    
    // Read unique ID
    FLib_MemCpy(uniqueID, (uint8_t *)&SIM_BASE_PTR->UIDL, 4);
    FLib_MemCpy(uniqueID + 4, (uint8_t *)&SIM_BASE_PTR->UIDML, 4);
    FLib_MemCpy(uniqueID + 8, (uint8_t *)&SIM_BASE_PTR->UIDMH, 2);
    
    // Read public static address
    Gap_ReadPublicDeviceAddress();
    
    /* Register for callbacks*/
    
    // Register server callback
    App_RegisterGattServerCallback(BleApp_GattServerCallback);
    
    // Register client callback
    App_RegisterGattClientProcedureCallback(ClientAncs_GattCallback);
    App_RegisterGattClientNotificationCallback(ClientAncs_GattNotificationCallback);
    

    if(deviceState == deviceState_watch)
    {
        GattServer_RegisterHandlesForWriteNotifications (sizeof(writeNotifHandles)/sizeof(writeNotifHandles[0]),
                                                         writeNotifHandles);
    }
    else
    {
        GattServer_RegisterHandlesForWriteNotifications (sizeof(otapWriteNotifHandles)/sizeof(otapWriteNotifHandles[0]),
                                                         otapWriteNotifHandles);
    }
        
    /* Register security requirements */
#if gUseServiceSecurity_d
    //Gap_RegisterDeviceSecurityRequirements(&deviceSecurityRequirements);
#endif

    /* Set local passkey */
#if gBondingSupported_d
    
#endif
    

    /* Setup Advertising and scanning data */
    if(deviceState == deviceState_watch)
    {
        gAppAdvertisingData.cNumAdStructures = 2;
        gAppAdvertisingData.aAdStructures = (void *)advScanStruct_watch;
    }
    else
    {
        gAppAdvertisingData.cNumAdStructures = 3;
        gAppAdvertisingData.aAdStructures = (void *)advScanStruct_otap;
    }
    
    Gap_SetAdvertisingData(&gAppAdvertisingData, &gAppScanRspData);

    /* Add to White List if bonding is supported */
#if gBondingSupported_d
    uint8_t bondedDeviceCnt;
    
    Gap_GetBondedDevicesCount(&bondedDeviceCnt);
    if(bondedDeviceCnt > (gcGapMaximumBondedDevices_d - 1))
    {
        while(Gap_RemoveBond(0) != gBleSuccess_c )
        {
            OSA_TimeDelay(10);
        }
    }

    BleApp_AddToWhiteList();
#endif

    mAdvState.advOn = FALSE;
    clientAncsPeerInfo.appState = mAppIdle_c;

    Ble_StartServices();
    
    // Populate values of Device Service Characteristics with proper values.
    // NOTE: Each field in revision must be single digit.
    fwRevision[0] = currentImageVerMK64[0] + '0';
    fwRevision[2] = currentImageVerMK64[1] + '0';
    fwRevision[4] = currentImageVerMK64[2] + '0';
    fwRevision[6]  = currentImageVerKW40[0] + '0';
    fwRevision[8]  = currentImageVerKW40[1] + '0';
    fwRevision[10] = currentImageVerKW40[2] + '0';
    GattDb_WriteAttribute(value_fw_rev, 11, fwRevision);       // Set firmware revision characteristic.
    GattDb_WriteAttribute(value_serial_num, 10, uniqueID);     // Set serial number characteristic.
    
    // Write current state to corresponding characteristic.
    GattDb_WriteAttribute(value_otap_state, 1, (uint8_t *)&deviceState);

    goToSleepTimerId = TMR_AllocateTimer();
    
#if (cPWR_UsePowerDownMode)    
    if(deviceState == deviceState_watch)
    {
        // Initializes interrupt pin. 
        GPIO_DRV_InputPinInit(&bleApp_intPin);
        // Set deep sleep mode.
        PWR_ChangeDeepSleepMode(1); /* MCU=LLS3, LL=IDLE, wakeup on GPIO/LL */
        // Set gpio pin as wakeup source.
        POWER_SYS_SetWakeupPin(kPowerManagerWakeupPin8, kLlwuExternalPinChangeDetect, &bleApp_wakeUpPin);
    }
    else
    {
    	// In OTAP mode device doesn't go to sleep.
        bleApp_intPin.config.interrupt = kPortIntDisabled;
        GPIO_DRV_InputPinInit(&bleApp_intPin);
    }
#else
    bleApp_intPin.config.interrupt = kPortIntDisabled;
    GPIO_DRV_InputPinInit(&bleApp_intPin);
#endif        
    
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Configures GAP Advertise parameters. Advertise will satrt after
 *    the parameters are set.
 */

static void BleApp_Advertise(void)
{

    advParams.minInterval = gFastConnMinAdvInterval_c;
    advParams.maxInterval = gFastConnMaxAdvInterval_c;
    advParams.filterPolicy = gProcessAll_c;
            
    advParams.ownAddressType = gBleAddrTypePublic_c;
   
    Gap_SetAdvertisingParameters(&advParams);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Requests a set of new connection parameters.
 *
 *    @param   peerDeviceId   Peer device ID.
 */

static void BleApp_SendConnUpdateReq(deviceId_t peerDeviceId)
{
    if(deviceState == deviceState_watch)
    {
        L2ca_UpdateConnectionParameters(peerDeviceId, gWatchConnMinInterval_c, gWatchConnMaxInterval_c,
                                                        gConnSlaveLatency_c, gConnTimeoutMultiplier_c, 0, 0);
    }
    else
    {
        L2ca_UpdateConnectionParameters(peerDeviceId, gOtapConnMinInterval_c, gOtapConnMaxInterval_c,
                                                        gConnSlaveLatency_c, gConnTimeoutMultiplier_c, 0, 0);
    }
}
        
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Handles BLE Advertising callback from host stack.
 *
 *    @param   pAdvertisingEvent   Pointer to gapAdvertisingEvent_t.
 */

static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent)
{
    switch (pAdvertisingEvent->eventType)
    {
        case gAdvertisingStateChanged_c:
        {
            
            mAdvState.advOn = !mAdvState.advOn;
            
            #if (cPWR_UsePowerDownMode)
                if(!mAdvState.advOn)
                {
                    Led1Off();
                }  
                else
                {
                    Led1On();
                }
            #else 
                LED_StopFlashingAllLeds();
                Led1Flashing();
                if(!mAdvState.advOn)
                {
                    DebugPrint("AdvertisingStop");
                    Led2Flashing();
                    Led3Flashing();
                    Led4Flashing();
                }
                else 
                {
                    DebugPrint("AdvertisingStart");
                }
            #endif
        }
        break;

        case gAdvertisingCommandFailed_c:
        {
            DebugPrint("AdvertisingCommandFailed !!!!!");
            
            panic(0,0,0,0);
        }
        break;

        default:
            break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Handles BLE Connection callback from host stack.
 *
 *    @param   peerDeviceId       Peer device ID.
 *    @param   pConnectionEvent   Pointer to gapConnectionEvent_t.
 */

static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
    bleResult_t result;    
    switch (pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
        {
            DebugPrint("ConnEvtConnected");
            
            #if gBondingSupported_d    
                /* Copy peer device address information */
                mPeerDeviceAddressType = pConnectionEvent->eventData.connectedEvent.peerAddressType;
                FLib_MemCpy(maPeerDeviceAddress, pConnectionEvent->eventData.connectedEvent.peerAddress, sizeof(bleDeviceAddress_t));
            #endif  
            
            /* Advertising stops when connected */
            mAdvState.advOn = FALSE;
            mPeerDeviceId = peerDeviceId;
            
            clientAncsPeerInfo.deviceId = peerDeviceId;
            clientAncsPeerInfo.isBonded = FALSE; 
            
            if(advMode == advMode_disable)
            {
                Gap_Disconnect(peerDeviceId);
            }
            else
            {
                /* Subscribe client*/
                Ble_Subscribe(peerDeviceId);
                
                #if gUseServiceSecurity_d            
                {
                    bool_t isBonded = FALSE;
                    if (gBleSuccess_c == Gap_CheckIfBonded(peerDeviceId, &isBonded) &&
                        FALSE == isBonded)
                    {
                        // NOTE: Remote device should be already bonded before try to do OTAP!
                        if(deviceState == deviceState_watch)
                        {
                            Gap_SendSlaveSecurityRequest(peerDeviceId, gBondingSupported_d, gSecurityMode_1_Level_3_c);
                        }
                        // If device state is some of "OTAP states", and remote device is not bonded, just stop OTAP and reset device.
                        else
                        {
                            OtapClient_Fail();
                            ResetMCU();
                        }
                    }
                }
                #endif            

                /* UI */
                LED_StopFlashingAllLeds();
                Led1On();
                
                if(deviceState != deviceState_watch)
                {
                    /* Device does not need to sleep until some information is exchanged with the peer. */
                #if (cPWR_UsePowerDownMode)    
                    PWR_DisallowDeviceToSleep();
                #endif
                    OtapClient_HandleConnectionEvent (peerDeviceId);
                }
                else
                {
                	// Send link state to host MCU.
                    hostInterface_packet_t hostInterface_packet = 
                    {
                        .type    = packetType_linkStateSend,
                        .length  = 1,
                        .data[0] = linkState_connected,
                        .data[1] = gHostInterface_trailerByte,
                    };
                    while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_packet, true) != osaStatus_Success)
                    {
                        OSA_TimeDelay(10);
                    }
                    // Update client state machine.
                    ClientAncs_StateMachineHandler(clientAncsPeerInfo.deviceId, mAppEvt_PeerConnected_c);
                }
            }
        }
        break;
        
        case gConnEvtDisconnected_c:
        {
            uint8_t bondedDeviceCnt;
            DebugPrint("ConnEvtDisconnected");
            
        #if gBondingSupported_d
            // If the number of bonded device is equal to gcGapMaximumBondedDevices_d 
            // then remove oldest one, to make space for next bond request.
            Gap_GetBondedDevicesCount(&bondedDeviceCnt);
            if(bondedDeviceCnt > (gcGapMaximumBondedDevices_d - 1))
            {
                while(Gap_RemoveBond(0) != gBleSuccess_c )
                {
                    OSA_TimeDelay(10);
                }
            }
        #endif
            
            // If disconnect event is detected during OTAP, then declare OTAP process as unsuccessful, and reset device.
            if(deviceState != deviceState_watch)
            {
                OtapClient_Fail();
                ResetMCU();
            }
            // Send link state to host MCU.
            else
            {
                hostInterface_packet_t hostInterface_packet = 
                {
                    .type    = packetType_linkStateSend,
                    .length  = 1,
                    .data[0] = linkState_disconnected,
                    .data[1] = gHostInterface_trailerByte,
                };
                while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_packet, true) != osaStatus_Success)
                {
                    OSA_TimeDelay(10);
                }
            }
            
            // Unsubscribe client.
            Ble_Unsubscribe();

            mPeerDeviceId = gInvalidDeviceId_c;
            clientAncsPeerInfo.deviceId = gInvalidDeviceId_c;
            
            // Reset Service Discovery to be sure.
            ClientAncs_ServiceDiscoveryErrorHandler();
            
            if(advMode == advMode_disable)
            {
                ;
            }
            else if (pConnectionEvent->eventData.disconnectedEvent.reason == gHciConnectionTimeout_c)
            {
                // Link loss detected.
                BleApp_Start();
            }
            else
            {
                // Connection was terminated by peer or application.
                BleApp_Start();
            }
        }
        break;

#if gBondingSupported_d
        
       case gConnEvtAuthenticationRejected_c:
       {
           Gap_RejectPairing(peerDeviceId, gLinkEncryptionFailed_c);
           break;
       }
               
        
        case gConnEvtEncryptionChanged_c:
        {       
            ClientAncs_StateMachineHandler(clientAncsPeerInfo.deviceId, mAppEvt_EncryptionChg_c);
            BleApp_SendConnUpdateReq(peerDeviceId);
            break;
        }
        
        case gConnEvtKeysReceived_c:
        {
            DebugPrint("ConnEvtKeysReceived");    
            
            // Copy peer device address information when IRK is used
            if (pConnectionEvent->eventData.keysReceivedEvent.pKeys->aIrk != NULL)
            {
                mPeerDeviceAddressType = pConnectionEvent->eventData.keysReceivedEvent.pKeys->addressType;
                FLib_MemCpy(maPeerDeviceAddress, pConnectionEvent->eventData.keysReceivedEvent.pKeys->aAddress, sizeof(bleDeviceAddress_t));
            }
        }
        break;

        case gConnEvtPasskeyDisplay_c:
        {
            hostInterface_packet_t hostInterface_packet = 
            {
                .type   = packetType_passDisplay,
                .length = 3,
                .data[3] = gHostInterface_trailerByte
            };

            // Send passkey to be displayed.
            FLib_MemCpy(hostInterface_packet.data, &smpPasskey, 3);
            while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_packet, true) != osaStatus_Success)
            {
                OSA_TimeDelay(10);
            }
        }
        break;
            
        case gConnEvtPairingComplete_c:
        {
            DebugPrint("ConnEvtPairingComplete");    
            
            if (pConnectionEvent->eventData.pairingCompleteEvent.pairingSuccessful &&
                pConnectionEvent->eventData.pairingCompleteEvent.pairingCompleteData.withBonding)
            {
                // If a bond is created, write device address in controller’s White List.
                Gap_AddDeviceToWhiteList(mPeerDeviceAddressType, maPeerDeviceAddress);
                ClientAncs_StateMachineHandler(clientAncsPeerInfo.deviceId, mAppEvt_PairingComplete_c);
                BleApp_SendConnUpdateReq(peerDeviceId);
            }
            else
            {
                Gap_Disconnect (peerDeviceId);
            }
        }
        break; 

        case gConnEvtPairingRequest_c:
        {
        	// Generate and set local passkey.
            if(deviceState == deviceState_watch)
            {
                DebugPrint("ConnEvtPairingRequest");
                
                //Get random passkey
                RNG_GetRandomNo(&smpPasskey);
                
                // Scale it to (100000 - 999999) range
                smpPasskey = (smpPasskey % 900000);
                smpPasskey += 100000;    
                
                // Set as loacal passkey
                Gap_SetLocalPasskey(smpPasskey);
                
                // Accept Pairing Request
                gPairingParameters.centralKeys = pConnectionEvent->eventData.pairingEvent.centralKeys;
                Gap_AcceptPairingRequest(peerDeviceId, &gPairingParameters);
            }
            // Device must be paired and bonded before start OTAP process.
            else
            {
                OtapClient_Fail();
                ResetMCU();
            }
        }    
        break;
        
        case gConnEvtKeyExchangeRequest_c:
        {
            DebugPrint("ConnEvtKeyExchangeRequest");
            
            gapSmpKeys_t sentSmpKeys = smpKeys;
                    
            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gLtk_c))
            {
            	// When the LTK is NULL EDIV and Rand are not sent and will be ignored.
                sentSmpKeys.aLtk = NULL;
            }
            
            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gIrk_c))
            {
            	// When the IRK is NULL the Address and Address Type are not sent and will be ignored.
                sentSmpKeys.aIrk = NULL;
            }
            
            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gCsrk_c))
            {
                sentSmpKeys.aCsrk = NULL;
            }
            
            Gap_SendSmpKeys(peerDeviceId, &sentSmpKeys);
        }
        break;
            
        case gConnEvtLongTermKeyRequest_c:
        {
            bool_t isBonded = FALSE;
               
            DebugPrint("ConnEvtLongTermKeyRequest");
           
            if (gBleSuccess_c == Gap_CheckIfBonded(peerDeviceId, &isBonded) &&
                FALSE == isBonded)
            {
                Gap_DenyLongTermKey(peerDeviceId);
            }
            else if (pConnectionEvent->eventData.longTermKeyRequestEvent.ediv == smpKeys.ediv &&
                pConnectionEvent->eventData.longTermKeyRequestEvent.randSize == smpKeys.cRandSize)
            {
                /* EDIV and RAND both matched */
                Gap_ProvideLongTermKey(peerDeviceId, smpKeys.aLtk, smpKeys.cLtkSize);
            }
            else
            /* EDIV or RAND size did not match */
            {
                Gap_DenyLongTermKey(peerDeviceId);
            }
        }
        break;
#else
        case gConnEvtPairingRequest_c:
        {
            Gap_RejectPairing (peerDeviceId, gPairingNotSupported_c);
        }    
        break;
#endif
               
    default:
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Handles GATT server callback from host stack.
 *
 *    @param   deviceId       Peer device ID.
 *    @param   pServerEvent   Pointer to gattServerEvent_t.
 */

static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent)
{
    uint16_t handle;
    uint8_t status;
    
    switch (pServerEvent->eventType)
    {
        case gEvtCharacteristicCccdWritten_c:
        {
            Gap_SaveCccd (deviceId,
                          pServerEvent->eventData.charCccdWrittenEvent.handle,
                          pServerEvent->eventData.charCccdWrittenEvent.newCccd);
            
            BleApp_CccdWritten (deviceId,
                                pServerEvent->eventData.charCccdWrittenEvent.handle,
                                pServerEvent->eventData.charCccdWrittenEvent.newCccd);
        }
        break;
        
        case gEvtAttributeWritten_c:
        {
            BleApp_AttributeWritten(deviceId,
                                                   pServerEvent->eventData.attributeWrittenEvent.handle,
                                                   pServerEvent->eventData.attributeWrittenEvent.cValueLength,
                                                   pServerEvent->eventData.attributeWrittenEvent.aValue);
            
        }
        break;
        
        case gEvtAttributeWrittenWithoutResponse_c:
        {
            BleApp_AttributeWrittenWithoutResponse (deviceId,
                                                    pServerEvent->eventData.attributeWrittenEvent.handle,
                                                    pServerEvent->eventData.attributeWrittenEvent.cValueLength,
                                                    pServerEvent->eventData.attributeWrittenEvent.aValue);
        }
        break;
        
        case gEvtHandleValueConfirmation_c:
        {
            BleApp_HandleValueConfirmation (deviceId);
        }
        break;
        
    default:
        break;
        
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function called when CCCD was written.
 *
 *    @param   deviceId   Device ID.
 *    @param   handle     Handle of the CCCD attribute.
 *    @param   cccd       Value of the CCCD.
 */

static void BleApp_CccdWritten (deviceId_t deviceId, uint16_t handle, gattCccdFlags_t cccd)
{
    otapCommand_t otapCommand;
    bleResult_t   bleResult;
    
    /*! Check if the OTAP control point CCCD was written. */
    if (
         (handle == cccd_otap_control_point) &&
         (deviceState != deviceState_watch)
        )
    {
        /*! If the state is Idle try to send a New Image Info Request Command to the OTAP Server. */
        otapCommand.cmdId = gOtapCmdIdNewImageInfoRequest_c;
        FLib_MemCpy (otapCommand.cmd.newImgInfoReq.currentImageId,
                     (uint8_t*)imageIdAll,
                     gOtap_ImageIdFieldSize_c);
        FLib_MemCpy (otapCommand.cmd.newImgInfoReq.currentImageVersion,
                     (uint8_t*)otapClientData.currentImgVer,
                     gOtap_ImageVersionFieldSize_c);
        
        bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                    (void*)(&otapCommand),
                                                    cmdIdToCmdLengthTable[gOtapCmdIdNewImageInfoRequest_c]);
        if (gBleSuccess_c == bleResult)
        {
            otapClientData.lastCmdSentToOtapServer = gOtapCmdIdNewImageInfoRequest_c;
            otapClientData.serverWrittenCccd = TRUE;
        }
        else
        {
            /*! A BLE error has occured - Disconnect */
            Gap_Disconnect (deviceId);
            OtapClient_Fail();
            ResetMCU();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function called when an attribute was written.
 *
 *    @param   deviceId   Device ID.
 *    @param   handle     Handle of the attribute.
 *    @param   length     Length of the attribute value array.
 *    @param   pValue     Attribute value array attempted to be written.
 */

static void BleApp_AttributeWritten(deviceId_t deviceId, uint16_t handle, uint16_t length, uint8_t* pValue)
{
    bleResult_t bleResult;
    otapCommand_t otapCommand;
     
   if(
      (handle == value_alertIn) &&
      (deviceState == deviceState_watch)
    )
    {
        if(length == gBleCustom_AlertInLength_d)
        {
            osaStatus_t eventWaitStatus;
            uint8_t     attWriteStatus;
            event_flags_t setFlags;
            
            // Send corresponding data to host MCU.
            Als_HandleInAlert(pValue);
            
        #if gHostInterface_RxConfirmationEnable //..........................................
            HostInterface_EventConfirmAttPacketClear();
            
            // Wait for confirmation packet from host MCU.
            eventWaitStatus = HostInterface_EventConfirmAttPacketWait();
            
            if(eventWaitStatus != osaStatus_Success)
            {
                attWriteStatus = gAttErrCodeUnlikelyError_c;
            }
            else
        #endif //...........................................................................                
            {
                attWriteStatus = gAttErrCodeNoError_c;
            }
            
            // Responds to an intercepted attribute write operation.
            GattServer_SendAttributeWrittenStatus(deviceId, handle, attWriteStatus);
        }
    }
    else if(
             (handle == value_otap_control_point) &&
             (deviceState != deviceState_watch)
           )
    {
        // Handle all OTAP Server to Client Commands Here.
        switch(((otapCommand_t*)pValue)->cmdId)
        {
        case gOtapCmdIdNewImageNotification_c:
            bleResult = GattServer_SendAttributeWrittenStatus (deviceId,
                                                               value_otap_control_point,
                                                               gAttErrCodeNoError_c);
            if (gBleSuccess_c == bleResult)
            {
                OtapClient_HandleNewImageNotification (deviceId,
                                                       length,
                                                       pValue);
            }
            else
            {
                // A BLE error has occurred - Disconnect.
                Gap_Disconnect (deviceId);
                OtapClient_Fail();
                ResetMCU();
            }
            break;
        case gOtapCmdIdNewImageInfoResponse_c:
            bleResult = GattServer_SendAttributeWrittenStatus (deviceId,
                                                               value_otap_control_point,
                                                               gAttErrCodeNoError_c);
            if (gBleSuccess_c == bleResult)
            {
                OtapClient_HandleNewImageInfoResponse (deviceId,
                                                       length,
                                                       pValue);
            }
            else
            {
                // A BLE error has occurred - Disconnect.
                Gap_Disconnect (deviceId);
                OtapClient_Fail();
                ResetMCU();
            }
            break;
        case gOtapCmdIdErrorNotification_c:
            bleResult = GattServer_SendAttributeWrittenStatus (deviceId,
                                                               value_otap_control_point,
                                                               gAttErrCodeNoError_c);
            if (gBleSuccess_c == bleResult)
            {
                OtapClient_HandleErrorNotification (deviceId,
                                                    length,
                                                    pValue);
            }
            else
            {
                // A BLE error has occurred - Disconnect.
                Gap_Disconnect (deviceId);
                OtapClient_Fail();
                ResetMCU();
            }
            break;
            
        default:
            otapCommand.cmdId = gOtapCmdIdErrorNotification_c;
            otapCommand.cmd.errNotif.cmdId = pValue[0];
            otapCommand.cmd.errNotif.errStatus = gOtapStatusUnexpectedCommand_c;
    
            bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                        (void*)(&otapCommand),
                                                        cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
            if (gBleSuccess_c == bleResult)
            {
                otapClientData.lastCmdSentToOtapServer = gOtapCmdIdErrorNotification_c;
            }
            else
            {
                // A BLE error has occurred - Disconnect.
                Gap_Disconnect (deviceId);
                OtapClient_Fail();
                ResetMCU();
            }
            break;
        };
    }
    else
    {
        // A GATT Server is trying to GATT Write an unknown attribute value.
        //  This should not happen. Disconnect the link.
        Gap_Disconnect (deviceId);
        OtapClient_Fail();
        ResetMCU();
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function called when an attribute was written without response (with ATT Write Command).
 *
 *    @param   deviceId   Device ID.
 *    @param   handle     Handle of the attribute.
 *    @param   length     Length of the attribute value array.
 *    @param   pValue     Attribute value array attempted to be written.
 */

static void BleApp_AttributeWrittenWithoutResponse (deviceId_t deviceId,
                                                    uint16_t handle,
                                                    uint16_t length,
                                                    uint8_t* pValue)
{
    otapCommand_t otapCommand;
    otapStatus_t otapStatus = gOtapStatusSuccess_c;
    bleResult_t bleResult;
    
    // Only the OTAP Data attribute is expected to be written using the
    // ATT Write Without Response Command. 
    if (
        (handle == value_otap_data) &&
        (deviceState != deviceState_watch)
       )
    {
        if (otapClientData.state == mOtapClientStateDownloadingImage_c)
        {
            if (otapClientData.transferMethod == gOtapTransferMethodAtt_c)
            {
                if (((otapCommand_t*)pValue)->cmdId == gOtapCmdIdImageChunk_c)
                {
                    OtapClient_HandleDataChunk (deviceId,
                                                length,
                                                pValue);
                }
                else
                {
                    // If the OTAP Client received an unexpected command on the data channel send an error to the OTAP Server.
                    otapStatus = gOtapStatusUnexpectedCmdOnDataChannel_c;
                }
            }
            else
            {
                // If the OTAP Client is not expecting image file chunks via ATT send an error to the OTAP Server.
                otapStatus = gOtapStatusUnexpectedTransferMethod_c;
            }
        }
        else
        {
            // If the OTAP Client is not expecting image file chunks send an error to the OTAP Server.
            otapStatus = gOtapStatusImageDataNotExpected_c;
        }
        
        if (otapStatus != gOtapStatusSuccess_c)
        {
            otapCommand.cmdId = gOtapCmdIdErrorNotification_c;
            otapCommand.cmd.errNotif.cmdId = pValue[0];
            otapCommand.cmd.errNotif.errStatus = otapStatus;
    
            bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                        (void*)(&otapCommand),
                                                        cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
            if (gBleSuccess_c == bleResult)
            {
                otapClientData.lastCmdSentToOtapServer = gOtapCmdIdErrorNotification_c;
            }
            else
            {
                // A BLE error has occurred - Disconnect.
                Gap_Disconnect (deviceId);
                OtapClient_Fail();
                ResetMCU();                
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function called when receive a Handle Value Confirmation from the Client.
 *
 *    @param   deviceId   Device ID.
 */

static void BleApp_HandleValueConfirmation (deviceId_t deviceId)
{
    otapCommand_t otapCommand;
    bleResult_t   bleResult;
    
    // Check for which command sent to the OTAP Server the confirmation has been received.
    if(deviceState != deviceState_watch)
    {
        switch (otapClientData.lastCmdSentToOtapServer)
        {
            case gOtapCmdIdNewImageInfoRequest_c:
                OtapClient_HandleNewImageInfoRequestConfirmation (deviceId);
                break;
                
            case gOtapCmdIdImageBlockRequest_c:
                OtapClient_HandleImageBlockRequestConfirmation (deviceId);
                break;
                
            case gOtapCmdIdImageTransferComplete_c:
                OtapClient_HandleImageTransferCompleteConfirmation (deviceId);
                break;
                
            case gOtapCmdIdErrorNotification_c:
                OtapClient_HandleErrorNotificationConfirmation (deviceId);
                break;
                
            case gOtapCmdIdStopImageTransfer_c:
                OtapClient_HandleStopImageTransferConfirmation (deviceId);
                break;
                
            default:
                otapCommand.cmdId = gOtapCmdIdErrorNotification_c;
                otapCommand.cmd.errNotif.cmdId = gOtapCmdIdNoCommand_c;
                otapCommand.cmd.errNotif.errStatus = gOtapStatusUnexpectedCommand_c;

                bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                            (void*)(&otapCommand),
                                                            cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
                if (gBleSuccess_c == bleResult)
                {
                    otapClientData.lastCmdSentToOtapServer = gOtapCmdIdErrorNotification_c;
                }
                else
                {
                    // A BLE error has occurred - Disconnect.
                    Gap_Disconnect (deviceId);
                    OtapClient_Fail();
                    ResetMCU();
                    
                }
                break;
        };
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleDataChunk (deviceId_t deviceId, uint16_t length, uint8_t* pData)
{
    otapCommand_t otapCommand;
    bleResult_t   bleResult;
    otapStatus_t otapStatus = gOtapStatusSuccess_c;
    
    otapCmdImgChunkCoc_t* pDataChunk = (otapCmdImgChunkCoc_t*)(&((otapCommand_t*)pData)->cmd); // Use the CoC Data Chunk type but observe the length.
    uint16_t dataLen = length - gOtap_CmdIdFieldSize_c - gOtap_ChunkSeqNumberSize_c;           // Calculate length.
    
    // Variables for the local image file parsing state machine.
    static uint32_t currentImgElemRcvdLen = 0;      /*!< Contains the number of received bytes for th current image element (header or othe sub element).
                                                    *   This is needed because the */
    static bleOtaImageFileHeader_t imgFileHeader;   /*!< Saved image file header. */
    static uint32_t elementEnd = 0;                 /*!< Current image file element expected end. */
    static subElementHeader_t subElemHdr;
    otaResult_t otaStatus;
    
    if (deviceId == otapClientData.peerOtapServer)
    {
        /* Check if the command length is as expected. */
        if ((length > (gOtap_CmdIdFieldSize_c + gOtap_ChunkSeqNumberSize_c)) &&
            (((otapClientData.transferMethod == gOtapTransferMethodAtt_c) && (length <= cmdIdToCmdLengthTable[gOtapCmdIdImageChunk_c])) ||
             ((otapClientData.transferMethod == gOtapTransferMethodL2capCoC_c) && (length <= gOtapCmdImageChunkCocLength_c))
            )
           )
        {
            /* Check if the chunk (sequence number) is as expected */
            if ((pDataChunk->seqNumber == otapClientData.chunkSeqNum) &&
                (pDataChunk->seqNumber < otapClientData.totalBlockChunks))
            {
                /*  Check if the data length is as expected. */
                if (((dataLen == otapClientData.chunkSize) && ((pDataChunk->seqNumber < (otapClientData.totalBlockChunks - 1)) || (otapClientData.totalBlockSize % otapClientData.chunkSize == 0))) ||
                    ((dataLen < otapClientData.chunkSize) && (pDataChunk->seqNumber == (otapClientData.totalBlockChunks - 1)) && (dataLen == otapClientData.totalBlockSize % otapClientData.chunkSize))
                   )
                {
                    /* Do more checks here if necessary. */
                }
                else
                {
                    otapStatus = gOtapStatusUnexpectedDataLength_c;
                }
            }
            else
            {
                otapStatus = gOtapStatusUnexpectedSequenceNumber_c;
            }
        }
        else
        {
            otapStatus = gOtapStatusInvalidCommandLength_c;
        }
    }
    else
    {
        otapStatus = gOtapStatusUnexpectedOtapPeer_c;
    }

    /*! If all checks were successful then parse the current data chunk, else send an error notification. */
    if (otapStatus == gOtapStatusSuccess_c)
    {
        pData = (uint8_t*)(&pDataChunk->data);
        
        /* If the Current position is 0 then reset the received length for the current image element
         * and the current image CRC to the initialization value which is 0.
         * The current position should be 0 only at the start of the image file transfer. */
        if (otapClientData.currentPos == 0)
        {
            currentImgElemRcvdLen = 0; 
            otapClientData.imgComputedCrc = 0;
        }
        
        /* Parse all the bytes in the data payload. */
        while (dataLen)
        {
            /* Wait for the header to arrive and check it's contents
             * then handle the elements of the image. */
            if (otapClientData.currentPos < sizeof(bleOtaImageFileHeader_t))
            {
                if ((otapClientData.currentPos + dataLen) >= sizeof(bleOtaImageFileHeader_t))
                {
                    uint16_t residualHeaderLen = sizeof(bleOtaImageFileHeader_t) - otapClientData.currentPos;
                    
                    /* There is enough information in the data payload to complete the header. */
                    FLib_MemCpy ((uint8_t*)(&imgFileHeader) + otapClientData.currentPos, pData, residualHeaderLen);
                    otapClientData.currentPos += residualHeaderLen;
                    pData += residualHeaderLen;
                    dataLen -= residualHeaderLen;
                    
                    /* Check header contents, and if it is not valid return and error and reset the image download position. */
                    otapStatus = OtapClient_IsImageFileHeaderValid (&imgFileHeader);
                    if (otapStatus != gOtapStatusSuccess_c)
                    {
                        otapClientData.currentPos = 0;
                        break;
                    }
                    
                    /* If the header is valid then update the CRC over the header part of the image. */
                    otapClientData.imgComputedCrc = OTA_CrcCompute ((uint8_t*)(&imgFileHeader),
                                                                    sizeof(bleOtaImageFileHeader_t),
                                                                    otapClientData.imgComputedCrc);
                    
                    currentImgElemRcvdLen = 0;
                    
                    /* If the remaining data length is not 0 then the loop will continue with the parsing of the next element. */
                }
                else
                {
                    /* Not enough data to complete the header.
                     * Copy all the data into the temporary header and
                     * increment the current image position. */
                    FLib_MemCpy((uint8_t*)(&imgFileHeader) + otapClientData.currentPos, pData, dataLen);
                    otapClientData.currentPos += dataLen;
                    dataLen = 0;
                }
            }
            else
            {
                /* The parsing has reached the sub-elements portion of the image. 
                 * Wait for each sub-element tag to arrive or parse it if it is known. */
                if (currentImgElemRcvdLen < sizeof(subElementHeader_t))
                {
                    if ((currentImgElemRcvdLen + dataLen) >= sizeof(subElementHeader_t))
                    {
                        uint16_t residualSubElemHdrLen = sizeof(subElementHeader_t) - currentImgElemRcvdLen;
                        
                        /* There is enough information in the data payload to complete the sub-element header. */
                        FLib_MemCpy ((uint8_t*)(&subElemHdr) + currentImgElemRcvdLen, pData, residualSubElemHdrLen);
                        otapClientData.currentPos += residualSubElemHdrLen;
                        currentImgElemRcvdLen += residualSubElemHdrLen;
                        pData += residualSubElemHdrLen;
                        dataLen -= residualSubElemHdrLen;
                        
                        /* Update the CRC over the sub-element header only if it is not the CRC Sub-Element header. */
                        if (subElemHdr.tagId != gBleOtaSubElemTagIdImageFileCrc_c)
                        {
                            otapClientData.imgComputedCrc = OTA_CrcCompute ((uint8_t*)(&subElemHdr),
                                                                            sizeof(subElementHeader_t),
                                                                            otapClientData.imgComputedCrc);
                        }
                        
                        elementEnd = otapClientData.currentPos + subElemHdr.dataLen;
                        
                        /* If the remaining data length is not 0 then the loop will
                        continue with the parsing of the sub-element. */
                    }
                    else
                    {
                        /* Not enough data to complete the sub-element header.
                         * Copy all the data into the temporary sub-element header
                         * and increment the current image position. */
                        FLib_MemCpy ((uint8_t*)(&subElemHdr) + currentImgElemRcvdLen, pData, dataLen);
                        otapClientData.currentPos += dataLen;
                        currentImgElemRcvdLen += dataLen;
                        dataLen = 0;
                    }
                }
                else
                {
                    uint32_t    elementChunkLength = 0;
                    
                    /* Make sure we do not pass the current element boundary. */
                    if ((otapClientData.currentPos + dataLen) >= elementEnd)
                    {
                        elementChunkLength = elementEnd - otapClientData.currentPos;
                    }
                    else
                    {
                        elementChunkLength = dataLen;
                    }
                    
                    /* Handle sub-element payload. */
                    switch (subElemHdr.tagId)
                    {
                    case gBleOtaSubElemTagIdUpgradeImage_c:
                        /* Immediately after receiving the header check if the image sub-element length is valid
                         * by trying to start the image upgrade procedure. */
                        if (currentImgElemRcvdLen == sizeof(subElementHeader_t))
                        {
                            uint32_t maxImageLnegth;
                                
                                
                            if(deviceState == deviceState_otapStartedKW40)
                            {
                                maxImageLnegth = gFlashParams_MaxImageLength_c;
                            }
                            else
                            {
                                maxImageLnegth = (1000 * 1024);
                            }
                            
                            if (gOtaSucess_c != OTA_StartImage(subElemHdr.dataLen, maxImageLnegth))
                            {
                                /* The sub-element length is invalid, set an error status and reset
                                 * the image file download process. */
                                otapStatus = gOtapStatusImageSizeTooLarge_c;
                                otapClientData.currentPos = 0;
                                break;
                            }
                        }
                        
                        /* Upgrade Image Tag - compute the CRC and try to push the chunk to the storage. */
                        otapClientData.imgComputedCrc = OTA_CrcCompute (pData,
                                                                        elementChunkLength,
                                                                        otapClientData.imgComputedCrc);
                        otaStatus = OTA_PushImageChunk (pData, elementChunkLength, NULL);
                        if (gOtaSucess_c != otaStatus)
                        {
                            otapStatus = gOtapStatusImageStorageError_c;
                            otapClientData.currentPos = 0;
                            OTA_CancelImage();
                            break;
                        }
                        break;
                        
                    case gBleOtaSubElemTagIdSectorBitmap_c:
                        /* Immediately after receiving the header check if the sub-element length is valid. */
                        if (currentImgElemRcvdLen == sizeof(subElementHeader_t))
                        {
                            if (subElemHdr.dataLen != sizeof(otapClientData.imgSectorBitmap))
                            {
                                /* The sub-element length is invalid, set an error status and reset
                                 * the image file download process. */
                                otapStatus = gOtapStatusInvalidSubElementLength_c;
                                otapClientData.currentPos = 0;
                                OTA_CancelImage();
                                break;
                            }
                        }
                        
                        /* Sector Bitmap Tag - Compute the CRC and copy the received bitmap to the buffer. */
                        otapClientData.imgComputedCrc = OTA_CrcCompute (pData,
                                                                        elementChunkLength,
                                                                        otapClientData.imgComputedCrc);
                        
                        FLib_MemCpy ((uint8_t*)otapClientData.imgSectorBitmap + (currentImgElemRcvdLen - sizeof(subElementHeader_t)),
                                     pData,
                                     elementChunkLength);
                        break;
                        
                    case gBleOtaSubElemTagIdImageFileCrc_c:
                        /* Immediately after receiving the header check if the sub-element length is valid. */
                        if (currentImgElemRcvdLen == sizeof(subElementHeader_t))
                        {
                            if (subElemHdr.dataLen != sizeof(otapClientData.imgReceivedCrc))
                            {
                                /* The sub-element length is invalid, set an error status and reset
                                 * the image file download process. */
                                otapStatus = gOtapStatusInvalidSubElementLength_c;
                                otapClientData.currentPos = 0;
                                OTA_CancelImage();
                                break;
                            }
                        }
                        
                        /* CRC Tag - Just copy the received CRC to the buffer. */
                        FLib_MemCpy ((uint8_t*)(&otapClientData.imgReceivedCrc) + (currentImgElemRcvdLen - sizeof(subElementHeader_t)),
                                     pData,
                                     elementChunkLength);
                        break;
                        
                    default:
                        /* Unknown sub-element type, just compute the CRC over it. */
                        otapClientData.imgComputedCrc = OTA_CrcCompute (pData,
                                                                        elementChunkLength,
                                                                        otapClientData.imgComputedCrc);
                        break;
                    };
                    
                    if (otapStatus != gOtapStatusSuccess_c)
                    {
                        /* If an error has occurred then break the loop. */
                        break;
                    }
                    
                    otapClientData.currentPos += elementChunkLength;
                    currentImgElemRcvdLen += elementChunkLength;
                    pData += elementChunkLength;
                    dataLen -= elementChunkLength;
                    
                    /* If this element has been completely received then reset the current element
                     * received length to trigger the reception of the next sub-element. */
                    if (otapClientData.currentPos >= elementEnd)
                    {
                        currentImgElemRcvdLen = 0;
                    }
                }
            }
        } /* while (dataLen) */
    }
    
    if (otapStatus == gOtapStatusSuccess_c)
    {
        /* If the chunk has been successfully processed increase the expected sequence number. */
        otapClientData.chunkSeqNum += 1;
        
        /* Check if the block and/or image transfer is complete */
        if (otapClientData.chunkSeqNum >= otapClientData.totalBlockChunks)
        {
            /* If the image transfer is complete check the image CRC then
             * commit the image and set the bootloader flags. */
            if (otapClientData.currentPos >= otapClientData.imgSize)
            {
                if (otapClientData.imgComputedCrc != otapClientData.imgReceivedCrc)
                {
                    otapStatus = gOtapStatusInvalidImageCrc_c;
                    otapClientData.currentPos = 0;
                    OTA_CancelImage();
                }
                else if (gOtaSucess_c != OTA_CommitImage(otapClientData.imgSectorBitmap))
                {
                    otapStatus = gOtapStatusImageStorageError_c;
                    otapClientData.currentPos = 0;
                    OTA_CancelImage();
                }
                else
                {
                    /* The new image was successfully committed, set the bootloader new image flags,
                     * set the image transfer state as downloaded and send an image transfer complete
                     * message to the peer. */
                    
                    OtapClient_Complete();
                    
                    otapClientData.state = mOtapClientStateImageDownloadComplete_c;
                    otapCommand.cmdId = gOtapCmdIdImageTransferComplete_c;
                    FLib_MemCpy((uint8_t*)otapCommand.cmd.imgTransComplete.imageId, otapClientData.imgId, sizeof(otapCommand.cmd.imgTransComplete.imageId));
                    otapCommand.cmd.imgTransComplete.status = gOtapStatusSuccess_c;
                    
                    bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                                (void*)(&otapCommand),
                                                                cmdIdToCmdLengthTable[gOtapCmdIdImageTransferComplete_c]);
                    if (gBleSuccess_c == bleResult)
                    {
                        otapClientData.lastCmdSentToOtapServer = gOtapCmdIdImageTransferComplete_c;
                    }
                    else
                    {
                        /*! A BLE error has occurred - Trigger the bootloader and reset now.
                         *  Do not wait for the Image Transfer Complete Confirmation. */                        
                        Gap_Disconnect(deviceId);
                        ResetMCU ();
                    }
                }
            }
            else
            {
                /* If just the current block is complete ask for another block. */
                OtapClient_ContinueImageDownload (deviceId);
            }
        }
    }
    
    if (otapStatus != gOtapStatusSuccess_c)
    {        
        otapCommand.cmdId = gOtapCmdIdErrorNotification_c;
        otapCommand.cmd.errNotif.cmdId = gOtapCmdIdImageChunk_c;
        otapCommand.cmd.errNotif.errStatus = otapStatus;

        bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                    (void*)(&otapCommand),
                                                    cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
        if (gBleSuccess_c == bleResult)
        {
            otapClientData.lastCmdSentToOtapServer = gOtapCmdIdErrorNotification_c;
        }
        else
        {
            /*! A BLE error has occurred - Disconnect */
            Gap_Disconnect (deviceId);
            OtapClient_Fail();
            ResetMCU();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleNewImageNotification (deviceId_t deviceId, uint16_t length, uint8_t* pValue)
{
    otapCommand_t otapCommand;
    bleResult_t   bleResult;
    otapStatus_t otapStatus = gOtapStatusSuccess_c;
    otapCommand_t*  pRemoteCmd = (otapCommand_t*)pValue;
    
    /* Check the command length and parameters. */
    if (length != cmdIdToCmdLengthTable[gOtapCmdIdNewImageNotification_c])
    {
        otapStatus = gOtapStatusInvalidCommandLength_c;
    }
    else if (pRemoteCmd->cmd.newImgNotif.imageFileSize <= (sizeof(bleOtaImageFileHeader_t) + sizeof(subElementHeader_t)))
    {
        otapStatus = gOtapStatusInvalidImageFileSize_c;
    }
    else
    {
        switch (otapClientData.state)
        {
        case mOtapClientStateIdle_c:
            //if (OtapClient_IsRemoteImageNewer(pRemoteCmd->cmd.newImgNotif.imageId, pRemoteCmd->cmd.newImgNotif.imageVersion))
            if(OtapClient_CheckRemoteID(pRemoteCmd->cmd.newImgNotif.imageId))
            {
                /* If a response for a New Image Info Request is expected from the OTAP Server simply ignore the
                 * New Image Notification. */
                if (otapClientData.lastCmdSentToOtapServer != gOtapCmdIdNewImageInfoRequest_c)
                {
                    /* Set up the Client to receive the image file. */
                    otapClientData.peerOtapServer = deviceId;
                    FLib_MemCpy(otapClientData.imgId, pRemoteCmd->cmd.newImgNotif.imageId, gOtap_ImageIdFieldSize_c);
                    FLib_MemCpy(otapClientData.imgVer, pRemoteCmd->cmd.newImgNotif.imageVersion, gOtap_ImageVersionFieldSize_c);
                    otapClientData.imgSize = pRemoteCmd->cmd.newImgNotif.imageFileSize;
                    otapClientData.currentPos = 0;
                    otapClientData.chunkSize = 0;
                    otapClientData.chunkSeqNum = 0;
                    otapClientData.totalBlockChunks = 0;
                    otapClientData.totalBlockSize = 0;
                    
                    /* Change the Client state to Downloading and trigger the download. */
                    otapClientData.state = mOtapClientStateDownloadingImage_c;
                    OtapClient_ContinueImageDownload (deviceId);
                }
            }
            else
            {
                OtapClient_Fail();
                ResetMCU();
            }
            /* If the remote image is not newer than the current image simply ignore the New Image Notification */
            break;
     
        case mOtapClientStateDownloadingImage_c:            /* Fallthrough */
        case mOtapClientStateImageDownloadComplete_c:
            /* Simply ignore the message if an image is being downloaded or
             * an image download is complete. */
            break;
            
        default:
            /* Some kind of internal error has occurred. Reset the
             * client state to Idle and act as if the state was Idle. */
            otapClientData.state = mOtapClientStateIdle_c;
            //if (OtapClient_IsRemoteImageNewer(pRemoteCmd->cmd.newImgNotif.imageId, pRemoteCmd->cmd.newImgNotif.imageVersion))
            if(OtapClient_CheckRemoteID(pRemoteCmd->cmd.newImgNotif.imageId))
            {
                /* If a response for a New Image Info Request is expected from the OTAp Server simply ignore the
                 * New Image Notification. */
                if (otapClientData.lastCmdSentToOtapServer != gOtapCmdIdNewImageInfoRequest_c)
                {
                    /* Set up the Client to receive the image file. */
                    otapClientData.peerOtapServer = deviceId;
                    FLib_MemCpy(otapClientData.imgId, pRemoteCmd->cmd.newImgNotif.imageId, gOtap_ImageIdFieldSize_c);
                    FLib_MemCpy(otapClientData.imgVer, pRemoteCmd->cmd.newImgNotif.imageVersion, gOtap_ImageVersionFieldSize_c);
                    otapClientData.imgSize = pRemoteCmd->cmd.newImgNotif.imageFileSize;
                    otapClientData.currentPos = 0;
                    otapClientData.chunkSize = 0;
                    otapClientData.chunkSeqNum = 0;
                    otapClientData.totalBlockChunks = 0;
                    otapClientData.totalBlockSize = 0;
                    
                    /* Change the Client state to Downloading and trigger the download. */
                    otapClientData.state = mOtapClientStateDownloadingImage_c;
                    OtapClient_ContinueImageDownload (deviceId);
                }
            }
            else
            {
                OtapClient_Fail();
                ResetMCU();
            }
            /* If the remote image is not newer than the current image simply ignore the New Image Notification */
            break;
        };
    }
        
    if (otapStatus != gOtapStatusSuccess_c)
    {
        otapCommand.cmdId = gOtapCmdIdErrorNotification_c;
        otapCommand.cmd.errNotif.cmdId = pValue[0];
        otapCommand.cmd.errNotif.errStatus = otapStatus;

        bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                    (void*)(&otapCommand),
                                                    cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
        if (gBleSuccess_c == bleResult)
        {
            otapClientData.lastCmdSentToOtapServer = gOtapCmdIdErrorNotification_c;
        }
        else
        {
            /*! A BLE error has occured - Disconnect */
            Gap_Disconnect (deviceId);
            OtapClient_Fail();
            ResetMCU();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleNewImageInfoResponse (deviceId_t deviceId, uint16_t length, uint8_t* pValue)
{
    otapCommand_t otapCommand;
    bleResult_t   bleResult;
    otapStatus_t otapStatus = gOtapStatusSuccess_c;
    otapCommand_t*  pRemoteCmd = (otapCommand_t*)pValue;
    
    /* Check the command length and parameters. */
    if (length != cmdIdToCmdLengthTable[gOtapCmdIdNewImageInfoResponse_c])
    {
        otapStatus = gOtapStatusInvalidCommandLength_c;
    }
    else if (pRemoteCmd->cmd.newImgInfoRes.imageFileSize <= (sizeof(bleOtaImageFileHeader_t) + sizeof(subElementHeader_t)))
    {
        otapStatus = gOtapStatusInvalidImageFileSize_c;
    }
    else
    {
        switch (otapClientData.state)
        {
        case mOtapClientStateIdle_c:
            if(OtapClient_CheckRemoteID(pRemoteCmd->cmd.newImgInfoRes.imageId))
            {
                /* Set up the Client to receive the image file. */
                otapClientData.peerOtapServer = deviceId;
                FLib_MemCpy(otapClientData.imgId, pRemoteCmd->cmd.newImgInfoRes.imageId, gOtap_ImageIdFieldSize_c);
                FLib_MemCpy(otapClientData.imgVer, pRemoteCmd->cmd.newImgInfoRes.imageVersion, gOtap_ImageVersionFieldSize_c);
                otapClientData.imgSize = pRemoteCmd->cmd.newImgInfoRes.imageFileSize;
                otapClientData.currentPos = 0;
                otapClientData.chunkSize = 0;
                otapClientData.chunkSeqNum = 0;
                otapClientData.totalBlockChunks = 0;
                otapClientData.totalBlockSize = 0;
                
                /* Change the Client state to Downloading and trigger the download. */
                otapClientData.state = mOtapClientStateDownloadingImage_c;
                OtapClient_ContinueImageDownload (deviceId);
            }
            else
            {
                OtapClient_Fail();
                ResetMCU();
            }
            /* If the remote image is not newer than the current image simply ignore the New Image Info Response */
            break;
     
        case mOtapClientStateDownloadingImage_c:            /* Fallthrough */
        case mOtapClientStateImageDownloadComplete_c:
            /* Simply ignore the message if an image is being downloaded or
             * an image download is complete. */
            break;
            
        default:
            /* Some kind of internal error has occurred. Reset the
             * client state to Idle and act as if the state was Idle. */
            otapClientData.state = mOtapClientStateIdle_c;
            //if (OtapClient_IsRemoteImageNewer(pRemoteCmd->cmd.newImgInfoRes.imageId, pRemoteCmd->cmd.newImgInfoRes.imageVersion))
            if(OtapClient_CheckRemoteID(pRemoteCmd->cmd.newImgInfoRes.imageId))
            {
                /* Set up the Client to receive the image file. */
                otapClientData.peerOtapServer = deviceId;
                FLib_MemCpy(otapClientData.imgId, pRemoteCmd->cmd.newImgInfoRes.imageId, gOtap_ImageIdFieldSize_c);
                FLib_MemCpy(otapClientData.imgVer, pRemoteCmd->cmd.newImgInfoRes.imageVersion, gOtap_ImageVersionFieldSize_c);
                otapClientData.imgSize = pRemoteCmd->cmd.newImgInfoRes.imageFileSize;
                otapClientData.currentPos = 0;
                otapClientData.chunkSize = 0;
                otapClientData.chunkSeqNum = 0;
                otapClientData.totalBlockChunks = 0;
                otapClientData.totalBlockSize = 0;
                
                /* Change the Client state to Downloading and trigger the download. */
                otapClientData.state = mOtapClientStateDownloadingImage_c;
                OtapClient_ContinueImageDownload (deviceId);
            }
            else
            {
                OtapClient_Fail();
                ResetMCU();
            }
            /* If the remote image is not newer than the current image simply ignore the New Image Info Response */
            break;
        };
    }
        
    if (otapStatus != gOtapStatusSuccess_c)
    {
        otapCommand.cmdId = gOtapCmdIdErrorNotification_c;
        otapCommand.cmd.errNotif.cmdId = gOtapCmdIdNewImageInfoResponse_c;
        otapCommand.cmd.errNotif.errStatus = otapStatus;

        bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                    (void*)(&otapCommand),
                                                    cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
        if (gBleSuccess_c == bleResult)
        {
            otapClientData.lastCmdSentToOtapServer = gOtapCmdIdErrorNotification_c;
        }
        else
        {
            /*! A BLE error has occured - Disconnect */
            Gap_Disconnect (deviceId);
            OtapClient_Fail();
            ResetMCU();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleErrorNotification (deviceId_t deviceId, uint16_t length, uint8_t* pValue)
{
    otapCommand_t otapCommand;
    bleResult_t   bleResult;
    otapStatus_t otapStatus = gOtapStatusSuccess_c;
    otapCommand_t*  pRemoteCmd = (otapCommand_t*)pValue;
    
    /* Check the command length and parameters. */
    if (length == cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c])
    {
        /*! Handle remote error statuses here. */
        if (pRemoteCmd->cmd.errNotif.errStatus < gOtapNumberOfStatuses_c)
        {
            /* Handle all errors in the same way, disconnect to restart the download process. */
            Gap_Disconnect (deviceId);
            OtapClient_Fail();
            ResetMCU();
        }
        else
        {
            otapStatus = gOtapStatusInvalidCommandParameter_c;
        }
    }
    else
    {
        otapStatus = gOtapStatusInvalidCommandLength_c;
    }
        
    if (otapStatus != gOtapStatusSuccess_c)
    {
        otapCommand.cmdId = gOtapCmdIdErrorNotification_c;
        otapCommand.cmd.errNotif.cmdId = gOtapCmdIdNewImageInfoResponse_c;
        otapCommand.cmd.errNotif.errStatus = otapStatus;

        bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                    (void*)(&otapCommand),
                                                    cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
        if (gBleSuccess_c == bleResult)
        {
            otapClientData.lastCmdSentToOtapServer = gOtapCmdIdErrorNotification_c;
        }
        else
        {
            /*! A BLE error has occured - Disconnect */
            Gap_Disconnect (deviceId);
            OtapClient_Fail();
            ResetMCU();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleNewImageInfoRequestConfirmation (deviceId_t deviceId)
{
    /* Clear the last command sent to the OTAP Server for which a Confirmation is expected. */
    otapClientData.lastCmdSentToOtapServer = gOtapCmdIdNoCommand_c;
    
    /* Nothing more to do here. If the New Image Info Request Command has reached
     * the OTAP Server then the OTAP Client expects a New Image Info Response */
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleImageBlockRequestConfirmation (deviceId_t deviceId)
{
    /* Clear the last command sent to the OTAP Server for which a Confirmation is expected. */
    otapClientData.lastCmdSentToOtapServer = gOtapCmdIdNoCommand_c;
    
    /* Nothing more to do here. If the Image Block Request Command has reached
     * the OTAP Server then the OTAP Client expects the requested image chunks
     * or an Error Notification. */
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleImageTransferCompleteConfirmation (deviceId_t deviceId)
{
    otapCommand_t otapCommand;
    bleResult_t   bleResult;
    
    /* Clear the last command sent to the OTAP Server for which a Confirmation is expected. */
    otapClientData.lastCmdSentToOtapServer = gOtapCmdIdNoCommand_c;
    
    /* If the image transfer was not successful then the image download state should be Idle.
     * If it is, try to trigger a new download.
     * If the Image Transfer Complete Command has reached the OTAP Server and the transfer was succesful 
     * then the OTAP Client will just wait for the restart and the
     * bootloader to flash the new image. */
    if (otapClientData.state == mOtapClientStateIdle_c)
    {
        otapCommand.cmdId = gOtapCmdIdNewImageInfoRequest_c;
        FLib_MemCpy (otapCommand.cmd.newImgInfoReq.currentImageId,
                     (uint8_t*)otapClientData.currentImgId,
                     gOtap_ImageIdFieldSize_c);
        FLib_MemCpy (otapCommand.cmd.newImgInfoReq.currentImageVersion,
                     (uint8_t*)otapClientData.currentImgVer,
                     gOtap_ImageVersionFieldSize_c);
        
        bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                    (void*)(&otapCommand),
                                                    cmdIdToCmdLengthTable[gOtapCmdIdNewImageInfoRequest_c]);
        if (gBleSuccess_c == bleResult)
        {
            otapClientData.lastCmdSentToOtapServer = gOtapCmdIdNewImageInfoRequest_c;
        }
        else
        {
            /*! A BLE error has occured - Disconnect */
            Gap_Disconnect (deviceId);
            OtapClient_Fail();
            ResetMCU();
        }
    }
    else if (otapClientData.state == mOtapClientStateImageDownloadComplete_c)
    {
        /* If the image transfer is complete trigger the bootloader and reset the device. */
        Gap_Disconnect (deviceId);
        ResetMCU ();
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleErrorNotificationConfirmation (deviceId_t deviceId)
{
    /* Clear the last command sent to the OTAP Server for which a Confirmation is expected. */
    otapClientData.lastCmdSentToOtapServer = gOtapCmdIdNoCommand_c;
    
    /* Reset block download parameters to safe values. */
    otapClientData.chunkSize = 0;
    otapClientData.chunkSeqNum = 0;
    otapClientData.totalBlockChunks = 0;
    otapClientData.totalBlockSize = 0;
    
    /* If an error has occured try to continue the image download from a "safe" point. */
    OtapClient_ContinueImageDownload (deviceId);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleStopImageTransferConfirmation (deviceId_t deviceId)
{
    /* Clear the last command sent to the OTAP Server for which a Confirmation is expected. */
    otapClientData.lastCmdSentToOtapServer = gOtapCmdIdNoCommand_c;
    
    /* Reset block download parameters to safe values. */
    otapClientData.chunkSize = 0;
    otapClientData.chunkSeqNum = 0;
    otapClientData.totalBlockChunks = 0;
    otapClientData.totalBlockSize = 0;
    
    /* If an error has occured try to continue the image download from a "safe" point. */
    OtapClient_ContinueImageDownload (deviceId);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleConnectionEvent (deviceId_t deviceId)
{
    switch (otapClientData.state)
    {
    case mOtapClientStateIdle_c:
        /*! If the OTAP Server has written the CCCD to receive commands fromt he OTAp Client then send a
         *  new image info request. */
        if (otapClientData.serverWrittenCccd == TRUE)
        {
            otapCommand_t otapCommand;
            bleResult_t   bleResult;
    
            otapCommand.cmdId = gOtapCmdIdNewImageInfoRequest_c;
            FLib_MemCpy (otapCommand.cmd.newImgInfoReq.currentImageId,
                         (uint8_t*)imageIdAll,
                         gOtap_ImageIdFieldSize_c);
            FLib_MemCpy (otapCommand.cmd.newImgInfoReq.currentImageVersion,
                         (uint8_t*)otapClientData.currentImgVer,
                         gOtap_ImageVersionFieldSize_c);
            
            bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                        (void*)(&otapCommand),
                                                        cmdIdToCmdLengthTable[gOtapCmdIdNewImageInfoRequest_c]);
            if (gBleSuccess_c == bleResult)
            {
                otapClientData.lastCmdSentToOtapServer = gOtapCmdIdNewImageInfoRequest_c;
                otapClientData.serverWrittenCccd = TRUE;
            }
            else
            {
                /*! A BLE error has occured - Disconnect */
                Gap_Disconnect (deviceId);
                OtapClient_Fail();
                ResetMCU();
            }
        }
        break;
    case  mOtapClientStateDownloadingImage_c:
        /*! If the state is Downloading try to continue the download from where it was left off.
         *  Check if the appropriate server is connected first. */
        if (otapClientData.peerOtapServer == deviceId)
        {
            /* Reset block download parameters to safe values. */
            otapClientData.chunkSize = 0;
            otapClientData.chunkSeqNum = 0;
            otapClientData.totalBlockChunks = 0;
            otapClientData.totalBlockSize = 0;
            
            OtapClient_ContinueImageDownload (deviceId);
        }
        break;
    case mOtapClientStateImageDownloadComplete_c:
        /*! If the image download is complete try to set the new image flag
         *  and reset the MCU for the bootloader ot kick in. */
        Gap_Disconnect (deviceId);
        OTA_SetNewImageFlag ();
        ResetMCU ();
        break;
    default:
        /* Some kind of internal error has occurred. Reset the
         * client state to Idle and act as if the state was Idle. */
        otapClientData.state = mOtapClientStateIdle_c;
        break;
    };
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_HandleDisconnectionEvent(deviceId_t deviceId)
{
    /* Check if the peer OTAP server was disconnected and if so reset block download
     * parameters to safe values. */
    if (otapClientData.peerOtapServer == deviceId)
    {
        otapClientData.chunkSize = 0;
        otapClientData.chunkSeqNum = 0;
        otapClientData.totalBlockChunks = 0;
        otapClientData.totalBlockSize = 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static void OtapClient_ContinueImageDownload (deviceId_t deviceId)
{
    otapCommand_t   otapCommand;
    bleResult_t     bleResult;
    uint32_t        bytesToDownload;
    uint32_t        maxBlockSize;
    
    switch (otapClientData.state)
    {
    case mOtapClientStateIdle_c:
        /* If the state is Idle do nothing. No need to continue the transfer of an image. */
        break;
    case mOtapClientStateDownloadingImage_c:
        /* If the last received chunk sequence number is equal to the total block
         * chunks or they are both zero then ask for a new block from the server. */
        if (otapClientData.chunkSeqNum == otapClientData.totalBlockChunks)
        {
            /* Ask for another block only if the image transfer was not completed. */
            if (otapClientData.currentPos < otapClientData.imgSize)
            {
                bytesToDownload = otapClientData.imgSize - otapClientData.currentPos;
                
                if (otapClientData.transferMethod == gOtapTransferMethodAtt_c)
                {
                    maxBlockSize = gOtap_ImageChunkDataSizeAtt_c * gOtap_MaxChunksPerBlock_c;
                    otapClientData.l2capChannelOrPsm = gL2capCidAtt_c;
                    otapClientData.chunkSize = gOtap_ImageChunkDataSizeAtt_c;
                }
                else if (otapClientData.transferMethod == gOtapTransferMethodL2capCoC_c)
                {
                    if (otapClientData.l2capChannelOrPsm == gOtap_L2capLePsm_c)
                    {
                        maxBlockSize = gOtap_ImageChunkDataSizeL2capCoc_c * gOtap_MaxChunksPerBlock_c;
                        otapClientData.chunkSize = gOtap_ImageChunkDataSizeL2capCoc_c;
                    }
                    else
                    {
                        /* If the L2CAP CoC is not valid then some kind of error or missconfiguration has
                         * occurred. Send a proper error notification to the peer and
                         * reset the download state machine to Idle. */
                        otapClientData.state = mOtapClientStateIdle_c;
                        
                        otapCommand.cmdId = gOtapCmdIdErrorNotification_c;
                        otapCommand.cmd.errNotif.cmdId = gOtapCmdIdNoCommand_c;
                        otapCommand.cmd.errNotif.errStatus = gOtapStatusUnexpectedL2capChannelOrPsm_c;

                        bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                                    (void*)(&otapCommand),
                                                                    cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
                        if (gBleSuccess_c == bleResult)
                        {
                            otapClientData.lastCmdSentToOtapServer = gOtapCmdIdErrorNotification_c;
                        }
                        else
                        {
                            /*! A BLE error has occured - Disconnect */
                            Gap_Disconnect (deviceId);
                            OtapClient_Fail();
                            ResetMCU();
                        }
                        
                        return;
                    }
                }
                else
                {
                    /* If the transfer method is not recognized then this image has been missconfigured
                     * or a critical error has occurred. Send a proper error notification to the peer and
                     * reset the download state machien to Idle. */
                    otapClientData.state = mOtapClientStateIdle_c;
                    
                    otapCommand.cmdId = gOtapCmdIdErrorNotification_c;
                    otapCommand.cmd.errNotif.cmdId = gOtapCmdIdNoCommand_c;
                    otapCommand.cmd.errNotif.errStatus = gOtapStatusUnexpectedTransferMethod_c;

                    bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                                (void*)(&otapCommand),
                                                                cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
                    if (gBleSuccess_c == bleResult)
                    {
                        otapClientData.lastCmdSentToOtapServer = gOtapCmdIdErrorNotification_c;
                    }
                    else
                    {
                        /*! A BLE error has occured - Disconnect */
                        Gap_Disconnect (deviceId);
                        OtapClient_Fail();
                        ResetMCU();
                    }
                    
                    return;
                }
                
                if (bytesToDownload >= maxBlockSize)
                {
                    /* If there are more bytes to download than the maximum block size then
                     * ask a full block from the server on the selected tansfer method and set up
                     * the client to recieve the chunks.*/
                    otapClientData.chunkSeqNum = 0;
                    otapClientData.totalBlockChunks = gOtap_MaxChunksPerBlock_c;
                    otapClientData.totalBlockSize = maxBlockSize;
                }
                else
                {
                    /* If there are fewer bytes to download than the maximum block size then compute the
                    *  number of chunks expected and set the expected block size to the number of 
                    *  bytes to download. */
                    otapClientData.chunkSeqNum = 0;
                    /* Compute number of full chunks. Integer division. */
                    otapClientData.totalBlockChunks = bytesToDownload / otapClientData.chunkSize;
                    /* Add an extra chunk if the chunk size is not a divisor of the number of bytes to download. */
                    otapClientData.totalBlockChunks += (bytesToDownload % otapClientData.chunkSize) ? 1 : 0;
                    otapClientData.totalBlockSize = bytesToDownload;
                }

                /* Send the Block request Command with teh determined parameters. */
                otapCommand.cmdId = gOtapCmdIdImageBlockRequest_c;
                
                FLib_MemCpy(otapCommand.cmd.imgBlockReq.imageId, otapClientData.imgId, gOtap_ImageIdFieldSize_c);
                otapCommand.cmd.imgBlockReq.startPosition = otapClientData.currentPos;
                otapCommand.cmd.imgBlockReq.blockSize = otapClientData.totalBlockSize;
                otapCommand.cmd.imgBlockReq.chunkSize = otapClientData.chunkSize;
                otapCommand.cmd.imgBlockReq.transferMethod = otapClientData.transferMethod;
                otapCommand.cmd.imgBlockReq.l2capChannelOrPsm = otapClientData.l2capChannelOrPsm;
                
                bleResult = OtapCS_SendCommandToOtapServer (service_otap,
                                                            (void*)(&otapCommand),
                                                            cmdIdToCmdLengthTable[gOtapCmdIdImageBlockRequest_c]);
                if (gBleSuccess_c == bleResult)
                {
                    otapClientData.lastCmdSentToOtapServer = gOtapCmdIdImageBlockRequest_c;
                }
                else
                {
                    /*! A BLE error has occured - Disconnect */
                    Gap_Disconnect (deviceId);
                    OtapClient_Fail();
                    ResetMCU();
                }
            }
        }
        break;
    case mOtapClientStateImageDownloadComplete_c:
        /*! If the image download is complete try to set the new image flag
         *  and reset the MCU for the bootloader ot kick in. */
        Gap_Disconnect (deviceId);
        OTA_SetNewImageFlag ();
        ResetMCU ();
        break;
    default:
        /* This code should never be reached in normal running conditions.
        Do nothing here, no need to continue the transfer of an image. */
        break;
    };
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static bool_t OtapClient_CheckRemoteID(uint8_t* pRemoteImgId)
{
    /* Check the Image Id. */
    if (!FLib_MemCmp((void*)(pRemoteImgId), (void*)otapClientData.currentImgId, 2))
    {
        return FALSE;
    }
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static bool_t OtapClient_IsRemoteImageNewer (uint8_t* pRemoteImgId, uint8_t* pRemoteImgVer)
{
    uint32_t    remoteBuildVer;
    uint32_t    localeBuildVer;
    
    /* Check the Manufacturer Id */
    if (pRemoteImgVer[7] != otapClientData.currentImgVer[7])
    {
        return FALSE;
    }
    
    /* Check Hardware Id */
    if (!FLib_MemCmp((void*)(&(pRemoteImgVer[4])), (void*)(&(otapClientData.currentImgVer[4])), 3))
    {
        return FALSE;
    }
    
    /* Check Stack Version */
    if (pRemoteImgVer[3] < otapClientData.currentImgVer[3])
    {
        return FALSE;
    }
    
    /* Check Build Version */
    remoteBuildVer = (uint32_t)pRemoteImgVer[0] + ((uint32_t)(pRemoteImgVer[1]) << 8) + ((uint32_t)(pRemoteImgVer[2]) << 16);
    localeBuildVer = (uint32_t)otapClientData.currentImgVer[0] + ((uint32_t)(otapClientData.currentImgVer[1]) << 8) + ((uint32_t)(otapClientData.currentImgVer[2]) << 16);
    if (remoteBuildVer <= localeBuildVer)
    {
        return FALSE;
    }
    
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

static otapStatus_t OtapClient_IsImageFileHeaderValid (bleOtaImageFileHeader_t* imgFileHeader)
{
    if (imgFileHeader->fileIdentifier != gBleOtaFileHeaderIdentifier_c)
    {
        return gOtapStatusUnknownFileIdentifier_c;
    }
    
    if (imgFileHeader->headerVersion != gbleOtapHeaderVersion0100_c)
    {
        return gOtapStatusUnknownHeaderVersion_c;
    }
    
    if (imgFileHeader->headerLength != sizeof(bleOtaImageFileHeader_t))
    {
        return gOtapStatusUnexpectedHeaderLength_c;
    }
    
    if (imgFileHeader->fieldControl != gBleOtaFileHeaderDefaultFieldControl_c)
    {
        return gOtapStatusUnexpectedHeaderFieldControl_c;
    }
    
    if (imgFileHeader->companyId != gBleOtaCompanyIdentifier_c)
    {
        return gOtapStatusUnknownCompanyId_c;
    }
    
    if (FALSE == FLib_MemCmp (imgFileHeader->imageId, otapClientData.imgId, sizeof(imgFileHeader->imageId)))
    {
        return gOtapStatusUnexpectedImageId_c;
    }
    
    if (FALSE == FLib_MemCmp (imgFileHeader->imageVersion, otapClientData.imgVer, sizeof(imgFileHeader->imageVersion)))
    {
        return gOtapStatusUnexpectedImageVersion_c;
    }
    
    if (imgFileHeader->totalImageFileSize != otapClientData.imgSize)
    {
        return gOtapStatusUnexpectedImageFileSize_c;
    }
    
    return gOtapStatusSuccess_c;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Set corresponding params when image successfully loaded.
 */

static void OtapClient_Complete(void)
{
    uint8_t *imgVer;
        
    if(deviceState == deviceState_otapStartedMK64)
    {
        imgVer = gHardwareParameters.imageVersionMK64;
    }
    else
    {
        imgVer = gHardwareParameters.imageVersionKW40;
        OTA_SetNewImageFlag ();
    }
    
    // Get device parameters from FLASH.
    NV_ReadHWParameters(&gHardwareParameters);
    
    // Write image version to hw params.
    FLib_MemCpy (imgVer, (uint8_t*)otapClientData.imgVer, gOtap_ImageVersionFieldSize_c);
    
    // Write device state to hw params.
    gHardwareParameters.deviceState = (uint8_t) deviceState_otapCompleted;
    
    NV_WriteHWParameters(&gHardwareParameters);
    OSA_TimeDelay(100u);
}
        
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Set corresponding params when image loading fail.
 */

static void OtapClient_Fail(void)
{
    ;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void NMI_Handler(void)
{
    asm ("nop");
    ResetMCU();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void DefaultISR(void)
{
    ResetMCU();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void HardFault_Handler(void)
{
    ResetMCU();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// Power management functions

/**
 *    Callback for "goToSleepTimerId".
 *
 *    @param   pParam   Param.
 */

static void BleApp_GoToSleepTimerCallback (void *pParam)
{
#if (cPWR_UsePowerDownMode)
    if(deviceState == deviceState_watch)
    {
        PWR_AllowDeviceToSleep();
    }
#endif
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function called after exit from Low Power.
 */

void BleApp_LowPowerExitCallback(void)
{
#if (cPWR_UsePowerDownMode)

    OSA_EnterCritical(kCriticalDisableInt);
    
    PORT_HAL_SetMuxMode(PORTB,0u,kPortMuxAsGpio);
    PORT_HAL_SetMuxMode(PORTB,18u,kPortMuxAsGpio);
    
    // Check if wakeup by TSI/Push button interrupt?
    if(PWRLib_MCU_WakeupReason.Bits.FromKeyBoard)
    {
        PWR_DisallowDeviceToSleep();
        
        // Start timer to go to sleep after 20ms.
        TMR_StartLowPowerTimer(goToSleepTimerId, gTmrLowPowerSingleShotMillisTimer_c,
                 TmrMilliseconds(20), BleApp_GoToSleepTimerCallback, NULL);
    }
    else
    {
        PORT_HAL_SetPinIntMode(PORTB,0u,kPortIntEitherEdge);
    }
    
    OSA_ExitCritical(kCriticalDisableInt);

#endif    
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Interrupt handler for PORTB and PORTC pins.
 */

void PORTB_PORTC_IRQHandler(void)
{
#if (cPWR_UsePowerDownMode)
    
    OSA_EnterCritical(kCriticalDisableInt);
    
    // Check if interrupt from wakeup-pin occurred.
    if(GPIO_DRV_IsPinIntPending(kGpioHostWakeup) != 0)
    {
        PWR_DisallowDeviceToSleep();
        
        // Start timer to go to sleep after 20ms.
        TMR_StartLowPowerTimer(goToSleepTimerId, gTmrLowPowerSingleShotMillisTimer_c,
                 TmrMilliseconds(20), BleApp_GoToSleepTimerCallback, NULL);
        
        GPIO_DRV_ClearPinIntFlag(kGpioHostWakeup);
    }
    
    // Check if interrupt from host-int pin occurred.
    if(GPIO_DRV_IsPinIntPending(kGpioHostInt) != 0)
    {
    	// Check level on host-int pin.
        if(GPIO_DRV_ReadPinInput(kGpioHostInt) != 0)
        {
        	// Disallow sleep.
            sleepFalg = false;
            bleApp_intPin.config.interrupt = kPortIntLogicZero;
            GPIO_DRV_InputPinInit(&bleApp_intPin);
            PWR_DisallowDeviceToSleep();
        }
        else
        {
        	// Allow sleep.
            sleepFalg = true;
            bleApp_intPin.config.interrupt = kPortIntLogicOne;
            GPIO_DRV_InputPinInit(&bleApp_intPin);
            while(PWR_CheckIfDeviceCanGoToSleep() == false)
            {
                PWR_AllowDeviceToSleep();
            }
        }

        GPIO_DRV_ClearPinIntFlag(kGpioHostInt);
    }
    
    OSA_ExitCritical(kCriticalDisableInt);
    
#endif
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Return value of sleepFlag.
 *
 *    @return      Value of sleepFlag.
 */

bool_t BleApp_GetSleepFlag(void)
{
    return sleepFalg;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
