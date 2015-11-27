/*! *********************************************************************************
* \addtogroup Heart Rate Sensor
* @{
********************************************************************************** */
/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
* \file app.c
* This file is the source file for the Heart Rate Sensor application
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

/* BLE Host Stack */
#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gatt_database.h"
#include "gap_interface.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_handles.h"

/* Profile / Services */
#include "battery_interface.h"
#include "device_info_interface.h"
#include "motion_service.h"
#include "weather_service.h"
#include "health_service.h"
#include "alert_service.h"


#include "ApplMain.h"
#include "app.h"
#include "debug.h"
#include "tsi.h"
#include "host_mcu_interface.h"

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
}advType_t;

typedef struct advState_tag{
    bool_t      advOn;
    advType_t   advType;
}advState_t;

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

const gapAdvertisingParameters_t gAppAdvParams = {
    /* minInterval */         800 /* 500 ms */, \
    /* maxInterval */         1600 /* 1 s */, \
    /* advertisingType */     gAdvNonConnectable_c, \
    /* addressType */         gBleAddrTypePublic_c, \
    /* directedAddressType */ gBleAddrTypePublic_c, \
    /* directedAddress */     {0, 0, 0, 0, 0, 0}, \
    /* channelMap */          (gapAdvertisingChannelMapFlags_t) (gAdvChanMapFlag37_c | gAdvChanMapFlag38_c | gAdvChanMapFlag39_c), \
    /* filterPolicy */        gProcessAll_c \
};

static gapAdvertisingParameters_t advParams = gGapDefaultAdvertisingParameters_d;

#if gBondingSupported_d
static bleDeviceAddress_t   maPeerDeviceAddress;
static uint8_t mcBondedDevices = 0;
static bleAddressType_t     mPeerDeviceAddressType;
#endif

/* Service Data*/

static basConfig_t      basServiceConfig = {service_battery, 100};
static disConfig_t      disServiceConfig = {service_device_info};

static uint16_t writeNotifHandles[]      = {value_alertIn};

/* Application specific data*/
static bool_t mToggle16BitHeartRate = FALSE;
static bool_t mContactStatus = TRUE;

static tmrTimerID_t mAdvTimerId;
static tmrTimerID_t mMeasurementTimerId;

extern uint8_t gAppSerMgrIf;

/* Buffer used for Characteristic related procedures */
static gattAttribute_t      *mpDescProcBuffer = NULL;

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
static void BleApp_AttributeWritten(deviceId_t deviceId, uint16_t handle, uint16_t length, uint8_t *pValue);

/* Timer Callbacks */
static void AdvertisingTimerCallback (void *);
static void TimerMeasurementCallback (void *);

static void BleApp_Advertise(void);

/* Uart Rx Callback*/
static void Uart_RxCallBack(void *pData);

static void Ble_StartServices(void);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Initializes application specific functionality before the BLE stack init.
*
********************************************************************************** */

gpio_output_pin_user_config_t gpioPin = 
    {
        .pinName = GPIO_MAKE_PIN(GPIOC_IDX, 2),
        .config.outputLogic = 1,
        .config.slewRate = kPortSlowSlewRate,
        .config.driveStrength = kPortLowDriveStrength,
    };
    
void BleApp_Init(void)
{       
    /* UI */
    
    HostInterface_Init();
    
    /* Initialize module, and creates the TouchSense's task */
    TouchSense_Init();
    
    //GPIO_DRV_OutputPinInit(&gpioPin);
}

/*! *********************************************************************************
* \brief    Starts the BLE application.
*
********************************************************************************** */
void BleApp_Start(void)
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

/*! *********************************************************************************
* \brief        Handles keyboard events.
*
* \param[in]    events    Key event structure.
********************************************************************************** */
void BleApp_HandleKeys(key_event_t events)
{
    switch (events)
    {
        case gKBD_EventPressPB1_c:
        {
            BleApp_Start();
            break;
        }
        case gKBD_EventPressPB2_c:
        {
            mToggle16BitHeartRate = (mToggle16BitHeartRate)?FALSE:TRUE;
        }
        break;
        case gKBD_EventLongPB1_c:
        {
            if (mPeerDeviceId != gInvalidDeviceId_c)
                Gap_Disconnect(mPeerDeviceId);
            break;
        }
        case gKBD_EventLongPB2_c:
        {
             
            break;
        }
    default:
         break;
    }
}

/*! *********************************************************************************
* \brief        Handles BLE generic callback.
*
* \param[in]    pGenericEvent    Pointer to gapGenericEvent_t.
********************************************************************************** */
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
            
        case gPublicAddressRead_c:
        {
            /* Use address read from the controller */
            FLib_MemCpyReverseOrder(maBleDeviceAddress, pGenericEvent->eventData.aAddress, sizeof(bleDeviceAddress_t));
        }
        break;            
            
        case gAdvertisingDataSetupComplete_c:
        {            
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


static void Ble_StartServices(void)
{
    /* Start services */
    Bas_Start(&basServiceConfig);
    Dis_Start(&disServiceConfig);
    Mos_Start();
    Wes_Start();
    Hes_Start();
    Als_Start();
}


static void Ble_Subscribe(deviceId_t deviceId)
{
    Bas_Subscribe(deviceId);
    Mos_Subscribe(deviceId);
    Wes_Subscribe(deviceId);
    Hes_Subscribe(deviceId);
    Als_Subscribe(deviceId);
}


static void Ble_Unsubscribe(void)
{
    Bas_Unsubscribe();
    Mos_Unsubscribe();
    Wes_Unsubscribe();
    Hes_Unsubscribe();
    Als_Unsubscribe();
}


/*! *********************************************************************************
* \brief        Configures BLE Stack after initialization. Usually used for
*               configuring advertising, scanning, white list, services, et al.
*
********************************************************************************** */
static void BleApp_Config()
{  
    /* Read public address from controller */
    Gap_ReadPublicDeviceAddress();

    /* Register for callbacks*/
    
    // Register server callback
    App_RegisterGattServerCallback(BleApp_GattServerCallback);
    GattServer_RegisterHandlesForWriteNotifications (sizeof(writeNotifHandles)/sizeof(writeNotifHandles[0]),
                                                     writeNotifHandles);
    
    /* Register security requirements */
#if gUseServiceSecurity_d
    Gap_RegisterDeviceSecurityRequirements(&deviceSecurityRequirements);
#endif

    /* Set local passkey */
#if gBondingSupported_d
    Gap_SetLocalPasskey(gPasskeyValue_c);
#endif

    /* Setup Advertising and scanning data */
    Gap_SetAdvertisingData(&gAppAdvertisingData, &gAppScanRspData);

    /* Populate White List if bonding is supported */
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

    mAdvState.advOn = FALSE;

    Ble_StartServices();
    
    /* Allocate application timers */
    mAdvTimerId = TMR_AllocateTimer();
    mMeasurementTimerId = TMR_AllocateTimer();
}

/*! *********************************************************************************
* \brief        Configures GAP Advertise parameters. Advertise will satrt after
*               the parameters are set.
*
********************************************************************************** */
static void BleApp_Advertise(void)
{
    uint32_t timeout;

    switch (mAdvState.advType)
    {
#if gBondingSupported_d
        case fastWhiteListAdvState_c:
        {
            advParams.minInterval = gFastConnMinAdvInterval_c;
            advParams.maxInterval = gFastConnMaxAdvInterval_c;
            advParams.filterPolicy = (gapAdvertisingFilterPolicyFlags_t)(gProcessConnWhiteListFlag_c | gProcessScanWhiteListFlag_c);
            timeout = gFastConnWhiteListAdvTime_c;
        }
        break;
#endif
        case fastAdvState_c:
        {
            advParams.minInterval = gFastConnMinAdvInterval_c;
            advParams.maxInterval = gFastConnMaxAdvInterval_c;
            advParams.filterPolicy = gProcessAll_c;
            timeout = gFastConnAdvTime_c - gFastConnWhiteListAdvTime_c;
        }
        break;

        case slowAdvState_c:
        {
            advParams.minInterval = gReducedPowerMinAdvInterval_c;
            advParams.maxInterval = gReducedPowerMinAdvInterval_c;
            advParams.filterPolicy = gProcessAll_c;
            timeout = gReducedPowerAdvTime_c;
        }
        break;
    }

    /* Set advertising parameters */
    Gap_SetAdvertisingParameters(&advParams);

    /* Start advertising timer */
    TMR_StartLowPowerTimer(mAdvTimerId,gTmrLowPowerSecondTimer_c,
               TmrSeconds(timeout), AdvertisingTimerCallback, NULL);
}

/*! *********************************************************************************
* \brief        Handles BLE Advertising callback from host stack.
*
* \param[in]    pAdvertisingEvent    Pointer to gapAdvertisingEvent_t.
********************************************************************************** */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent)
{
    switch (pAdvertisingEvent->eventType)
    {
        case gAdvertisingStateChanged_c:
        {
            
            mAdvState.advOn = !mAdvState.advOn;
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

/*! *********************************************************************************
* \brief        Handles BLE Connection callback from host stack.
*
* \param[in]    peerDeviceId        Peer device ID.
* \param[in]    pConnectionEvent    Pointer to gapConnectionEvent_t.
********************************************************************************** */
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
    bleResult_t result;    
    switch (pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
        {        
            DebugPrint("ConnEvtConnected");
            
            mPeerDeviceId = peerDeviceId;
            
            /* Advertising stops when connected */
            mAdvState.advOn = FALSE;

            #if gBondingSupported_d    
                /* Copy peer device address information */
                mPeerDeviceAddressType = pConnectionEvent->eventData.connectedEvent.peerAddressType;
                FLib_MemCpy(maPeerDeviceAddress, pConnectionEvent->eventData.connectedEvent.peerAddress, sizeof(bleDeviceAddress_t));
            #endif  
            
            #if gUseServiceSecurity_d            
            {
                bool_t isBonded = FALSE ;
                
                if (gBleSuccess_c == Gap_CheckIfBonded(peerDeviceId, &isBonded) &&
                    FALSE == isBonded) 
                {
                      Gap_SendSlaveSecurityRequest(peerDeviceId, TRUE, gSecurityMode_1_Level_3_c);
                }
            }
            #endif            

            /* Subscribe client*/
            Ble_Subscribe(peerDeviceId);
            

            /* UI */
            LED_StopFlashingAllLeds();
            Led1On();
            
            /* Stop Advertising Timer*/
            mAdvState.advOn = FALSE;
            TMR_StopTimer(mAdvTimerId);
            
            /* Start measurements */
            TMR_StartLowPowerTimer(mMeasurementTimerId, gTmrLowPowerIntervalMillisTimer_c,
                       TmrSeconds(1), TimerMeasurementCallback, NULL);
        }
        break;
        
        case gConnEvtDisconnected_c:
        {
            DebugPrint("ConnEvtDisconnected");
            
            /* Unsubscribe client */
            Ble_Unsubscribe();

            peerDeviceId = gInvalidDeviceId_c;

            if (pConnectionEvent->eventData.disconnectedEvent.reason == gHciConnectionTimeout_c)
            {
                /* Link loss detected*/
                BleApp_Start();
            }
            else
            {
              /* Connection was terminated by peer or application */
                BleApp_Start();
            }
        }
        break;

#if gBondingSupported_d
        case gConnEvtKeysReceived_c:
        {
            DebugPrint("ConnEvtKeysReceived");    
            
            /* Copy peer device address information when IRK is used */
            if (pConnectionEvent->eventData.keysReceivedEvent.pKeys->aIrk != NULL)
            {
                mPeerDeviceAddressType = pConnectionEvent->eventData.keysReceivedEvent.pKeys->addressType;
                FLib_MemCpy(maPeerDeviceAddress, pConnectionEvent->eventData.keysReceivedEvent.pKeys->aAddress, sizeof(bleDeviceAddress_t));
            }
        }
        break;

        case gConnEvtPairingComplete_c:
        {
            DebugPrint("ConnEvtPairingComplete");    
            
            if (pConnectionEvent->eventData.pairingCompleteEvent.pairingSuccessful &&
                pConnectionEvent->eventData.pairingCompleteEvent.pairingCompleteData.withBonding)
            {
                /* If a bond is created, write device address in controller’s White List */
                Gap_AddDeviceToWhiteList(mPeerDeviceAddressType, maPeerDeviceAddress);
            }
        }
        break; 

        case gConnEvtPairingRequest_c:
        {
            DebugPrint("ConnEvtPairingRequest");
            
            gPairingParameters.centralKeys = pConnectionEvent->eventData.pairingEvent.centralKeys;
            Gap_AcceptPairingRequest(peerDeviceId, &gPairingParameters);
        }    
        break;
        
        case gConnEvtKeyExchangeRequest_c:
        {
            DebugPrint("ConnEvtKeyExchangeRequest");
            
            Gap_SendSmpKeys(peerDeviceId, &smpKeys);
        }
        break;
            
        case gConnEvtLongTermKeyRequest_c:
        {
            DebugPrint("ConnEvtLongTermKeyRequest");
            
            if (pConnectionEvent->eventData.longTermKeyRequestEvent.ediv == smpKeys.ediv &&
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
#endif
        
    default:
        break;
    }
}

/*! *********************************************************************************
* \brief        Handles GATT server callback from host stack.
*
* \param[in]    deviceId        Peer device ID.
* \param[in]    pServerEvent    Pointer to gattServerEvent_t.
********************************************************************************** */
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent)
{
    uint16_t handle;
    uint8_t status;
    
    switch (pServerEvent->eventType)
    {
        case gEvtAttributeWritten_c:
        {
            osaStatus_t eventWaitStatus;
            uint8_t     attWriteStatus;
            event_flags_t setFlags;
            
            BleApp_AttributeWritten(deviceId,
                                                   pServerEvent->eventData.attributeWrittenEvent.handle,
                                                   pServerEvent->eventData.attributeWrittenEvent.cValueLength,
                                                   pServerEvent->eventData.attributeWrittenEvent.aValue);
            
#if gHostInterface_RxConfirmationEnable //..........................................
            HostInterface_EventConfirmAttPacketClear();
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
            
            GattServer_SendAttributeWrittenStatus(deviceId, pServerEvent->eventData.attributeWrittenEvent.handle, attWriteStatus);
        }
        break;
        
        
        case gEvtCharacteristicCccdWritten_c:
        {
            ;
        }
        break;
        
    default:
        break;
        
    }
}

static void BleApp_AttributeWritten(deviceId_t deviceId, uint16_t handle, uint16_t length, uint8_t* pValue)
{
    switch(handle)
    {
        case value_alertIn:
        {
            if(length == gBleCustom_AlertInLength_d)
            {
                Als_HandleInAlert(pValue);
            }
        }
        break;
        
        default :
        {
            return;
        }
    }
}

/*! *********************************************************************************
* \brief        Handles advertising timer callback.
*
* \param[in]    pParam        Calback parameters.
********************************************************************************** */
static void AdvertisingTimerCallback(void * pParam)
{
    /* Stop and restart advertising with new parameters */
    Gap_StopAdvertising();
    switch (mAdvState.advType)
    {
#if gBondingSupported_d
        case fastWhiteListAdvState_c:
        {
            mAdvState.advType = fastAdvState_c;
        }
        break;
#endif
        case fastAdvState_c:
        {
            mAdvState.advType = slowAdvState_c;
        }
        break;

        default:
        break;
    }
    BleApp_Advertise();
}

/*! *********************************************************************************
* \brief        Handles measurement timer callback.
*
* \param[in]    pParam        Calback parameters.
********************************************************************************** */
static void TimerMeasurementCallback(void * pParam)
{
    uint32_t hr = 0;
    RNG_GetRandomNo(&hr);
    
    ;
}

/*! *********************************************************************************
* @}
********************************************************************************** */
