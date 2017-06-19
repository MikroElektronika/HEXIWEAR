/**
 *    @file client_ancs.c
 */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gap_interface.h"
#include "battery_interface.h"
#include "gatt_uuid_decl_x.def"
#include "gatt_db_handles.h"
#include "FunctionLib.h"
#include "fsl_lpuart_driver.h"
#include "MemManager.h"
#include "client_ancs.h"
#include "app.h"
#include "host_mcu_interface.h"

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

appPeerInfo_t clientAncsPeerInfo;

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/** Buffer used for Service Discovery */
static gattService_t *mpServiceDiscoveryBuffer = NULL;
static uint8_t  mcPrimaryServices = 0;

/** Buffer used for Characteristic Discovery */
static gattCharacteristic_t *mpCharDiscoveryBuffer = NULL;
static uint8_t mCurrentServiceInDiscoveryIndex;
static uint8_t mCurrentCharInDiscoveryIndex;

/** Buffer used for Characteristic Descriptor Discovery */
static gattAttribute_t *mpCharDescriptorBuffer = NULL;

/** Buffer used for Characteristic related procedures */
static gattAttribute_t      *mpDescProcBuffer = NULL;

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

static void ClientAncs_StoreCharHandles(gattCharacteristic_t *pChar);
static void ClientAncs_StartServiceDiscovery(deviceId_t peerDeviceId);
static void ClientAncs_ServiceDiscoveryReset();
static void ClientAncs_ServiceDiscoveryCompleted();
static void ClientAncs_StoreServiceHandles(gattService_t *pService);

/************************************************************************************
*************************************************************************************
* Public Functions definitions
*************************************************************************************
********************************************************************************** */

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Handles GATT client callback from host stack.
 *
 *    @param   serverDeviceId    GATT Server device ID.
 *    @param   procedureType     Procedure type.
 *    @param   procedureResult   Procedure result.
 *    @param   error             Callback result.
 */

void ClientAncs_GattCallback(
    deviceId_t              serverDeviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
)
{
    if (procedureResult == gGattProcError_c)
    {    
        asm ("nop");
        attErrorCode_t attError = (attErrorCode_t) (error & 0xFF);
        if (attError == gAttErrCodeInsufficientEncryption_c ||
          attError == gAttErrCodeInsufficientAuthorization_c ||
          attError == gAttErrCodeInsufficientAuthentication_c)
        {
            /* Start Pairing Procedure */
            
        }
        
        ClientAncs_StateMachineHandler(serverDeviceId, mAppEvt_GattProcError_c);
    }
    
    else if (procedureResult == gGattProcSuccess_c)
    {
        switch(procedureType)
        {
            case gGattProcExchangeMtu_c:
            case gGattProcDiscoverAllPrimaryServices_c:
            case gGattProcWriteCharacteristicDescriptor_c:
                break;
            
            case gGattProcDiscoverAllCharacteristics_c:
            {
                ClientAncs_StoreServiceHandles(mpServiceDiscoveryBuffer + mCurrentServiceInDiscoveryIndex);
                break;
            }
            
            case gGattProcDiscoverAllCharacteristicDescriptors_c:
            {
                ClientAncs_StoreCharHandles(mpCharDiscoveryBuffer + mCurrentCharInDiscoveryIndex);
                
                /* Move on to the next characteristic */
                mCurrentCharInDiscoveryIndex++; 
                break;
            }
            
            case gGattProcReadCharacteristicDescriptor_c:
            {
                if (mpDescProcBuffer != NULL)
                {
                    ;
                }
                break;
            }
            
            default:
                break;
        }
        
        ClientAncs_StateMachineHandler(serverDeviceId, mAppEvt_GattProcComplete_c);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Handles GATT client notification callback from host stack.
 *
 *    @param   serverDeviceId               GATT Server device ID.
 *    @param   characteristicValueHandle    Handle.
 *    @param   aValue                       Pointer to value.
 *    @param   valueLength                  Value length.
 */

void ClientAncs_GattNotificationCallback
(
    deviceId_t          serverDeviceId, 
    uint16_t characteristicValueHandle,
    uint8_t* aValue,
    uint16_t valueLength
)
{
    if (characteristicValueHandle == clientAncsPeerInfo.customInfo.ancClientConfig.hNotifSource)
    {
        if(
           (aValue[2] == ancCategoryId_email) ||
           (aValue[2] == ancCategoryId_missedCall) ||
           (aValue[2] == ancCategoryId_social)
          )
        {
            hostInterface_packet_t hostInterface_packet = 
            {
                .type   = packetType_notification,
                .length = 2,
                .data[2] = gHostInterface_trailerByte
            };
            
            hostInterface_packet.data[0] = aValue[0];       // ancEventId_t
            hostInterface_packet.data[1] = aValue[2];       // ancCategoryId_t
            while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_packet, true) != osaStatus_Success)
            {
                OSA_TimeDelay(10);
            }
        }
        
#if (cPWR_UsePowerDownMode)
        /* Restart Wait For Data timer */
//        TMR_StartLowPowerTimer(mAppTimerId,
//                       gTmrLowPowerSecondTimer_c,
//                       TmrSeconds(gWaitForDataTime_c),
//                       DisconnectTimerCallback, NULL);
#endif 
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function starts discovery of primary services.
 *
 *    @param   peerDeviceId   Peer device ID.
 */

static void ClientAncs_StartServiceDiscovery(deviceId_t peerDeviceId)
{
    bleResult_t discResult;
    
    /* Allocate memory for Service Discovery */
    mpServiceDiscoveryBuffer = MEM_BufferAlloc(sizeof(gattService_t) * 1);
    mpCharDiscoveryBuffer = MEM_BufferAlloc(sizeof(gattCharacteristic_t) * gMaxServiceCharCount_d);
    mpCharDescriptorBuffer = MEM_BufferAlloc(sizeof(gattAttribute_t) * gMaxCharDescriptorsCount_d);
      
    if (!mpServiceDiscoveryBuffer || !mpCharDiscoveryBuffer || !mpCharDescriptorBuffer)
        return;
    
    /* Moving to Primary Service Discovery State*/
    clientAncsPeerInfo.appState = mAppPrimaryServiceDisc_c;

    /* Start Service Discovery*/
    discResult = GattClient_DiscoverPrimaryServicesByUuid(peerDeviceId,
                                             gBleUuidType128_c,
                                             (bleUuid_t*) &uuid_service_ancs,
                                             mpServiceDiscoveryBuffer,
                                             1,
                                             &mcPrimaryServices
                                             );
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Handler of client ancs state machine.
 *
 *    @param   peerDeviceId               Peer device ID.
 *    @param   event                      Event.
 */

void ClientAncs_StateMachineHandler(deviceId_t peerDeviceId, uint8_t event)
{
    switch (clientAncsPeerInfo.appState)
    {
        case mAppIdle_c:
        {
            if (event == mAppEvt_PeerConnected_c)
            {
#if (!gBondingSupported_d)
                ClientAncs_StartServiceDiscovery(peerDeviceId);    
#endif      
            }
            else if (
                      (event == mAppEvt_PairingComplete_c) ||
                      (event == mAppEvt_EncryptionChg_c)
                     )
            {
                ClientAncs_StartServiceDiscovery(peerDeviceId);    
            }
        }
        break;
        
        case mAppPrimaryServiceDisc_c:
        {
            if (event == mAppEvt_GattProcComplete_c)
            {          
                /* We found at least one service */
                if (mcPrimaryServices)
                {
                    /* Moving to Characteristic Discovery State*/
                    clientAncsPeerInfo.appState = mAppCharServiceDisc_c;

                    /* Start characteristic discovery with first service*/
                    mCurrentServiceInDiscoveryIndex = 0;
                    mCurrentCharInDiscoveryIndex = 0;
                    
                    mpServiceDiscoveryBuffer->aCharacteristics = mpCharDiscoveryBuffer;

                    /* Start Characteristic Discovery for current service */
                    GattClient_DiscoverAllCharacteristicsOfService(
                                                peerDeviceId,
                                                mpServiceDiscoveryBuffer,
                                                gMaxServiceCharCount_d);
                }
                else
                {
                    ClientAncs_ServiceDiscoveryErrorHandler();
                }
            }
            else if (event == mAppEvt_GattProcError_c)
            {
                ClientAncs_ServiceDiscoveryErrorHandler();
            }
        }
        break;

        case mAppCharServiceDisc_c:
        {
            if (event == mAppEvt_GattProcComplete_c)
            {
                gattService_t        *pCurrentService = mpServiceDiscoveryBuffer + mCurrentServiceInDiscoveryIndex; 
                gattCharacteristic_t *pCurrentChar = pCurrentService->aCharacteristics + mCurrentCharInDiscoveryIndex;
                                
                if (mCurrentCharInDiscoveryIndex < pCurrentService->cNumCharacteristics)
                {                
                    /* Find next characteristic with descriptors*/
                    while (mCurrentCharInDiscoveryIndex < pCurrentService->cNumCharacteristics - 1)
                    {   
                        /* Check if we have handles available between adjacent characteristics */
                        if (pCurrentChar->value.handle + 2 < (pCurrentChar + 1)->value.handle)
                        {
                            FLib_MemSet(mpCharDescriptorBuffer, 0, sizeof(gattAttribute_t));
                            pCurrentChar->aDescriptors = mpCharDescriptorBuffer;
                            GattClient_DiscoverAllCharacteristicDescriptors(peerDeviceId,
                                                    pCurrentChar,
                                                    (pCurrentChar + 1)->value.handle,
                                                    gMaxCharDescriptorsCount_d);
                            return;
                        }
                        
                        mCurrentCharInDiscoveryIndex++;
                        pCurrentChar = pCurrentService->aCharacteristics + mCurrentCharInDiscoveryIndex;
                    }
                    
                    /* Made it to the last characteristic. Chack against service end handle*/
                    if (pCurrentChar->value.handle < pCurrentService->endHandle)
                    {
			FLib_MemSet(mpCharDescriptorBuffer, 0, sizeof(gattAttribute_t));
                        pCurrentChar->aDescriptors = mpCharDescriptorBuffer;
                        GattClient_DiscoverAllCharacteristicDescriptors(peerDeviceId,
                                                    pCurrentChar,
                                                    pCurrentService->endHandle,
                                                    gMaxCharDescriptorsCount_d);
                         return;

                    }
                }
                
                /* Move on to the next service */
                mCurrentServiceInDiscoveryIndex++;
                
                /* Reset characteristic discovery */
                mCurrentCharInDiscoveryIndex = 0;
                
                if (mCurrentServiceInDiscoveryIndex < mcPrimaryServices)
                {
                    /* Allocate memory for Char Discovery */
                    (mpServiceDiscoveryBuffer + mCurrentServiceInDiscoveryIndex)->aCharacteristics = mpCharDiscoveryBuffer;

                     /* Start Characteristic Discovery for current service */
                    GattClient_DiscoverAllCharacteristicsOfService(peerDeviceId,
                                                mpServiceDiscoveryBuffer + mCurrentServiceInDiscoveryIndex,
                                                gMaxServiceCharCount_d);
                }
                else
                {
                    ClientAncs_ServiceDiscoveryCompleted();
                }
            }
            else if (event == mAppEvt_GattProcError_c) 
            {
                ClientAncs_ServiceDiscoveryErrorHandler();
            }
        }
        break;      
        
        case mAppDescriptorSetup_c:
        {
            if (event == mAppEvt_GattProcComplete_c)
            {
                if (clientAncsPeerInfo.customInfo.ancClientConfig.hNotifSourceCccd)
                {
                    uint16_t value = gCccdNotification_c;
                    if (!mpDescProcBuffer)
                    {
                        //panic(0,0,0,0);
                        return;
                    }
                    
                    /* Moving to Running State*/
                    clientAncsPeerInfo.appState = mAppRunning_c;
                    /* Enable notification */
                    mpDescProcBuffer->handle = clientAncsPeerInfo.customInfo.ancClientConfig.hNotifSourceCccd;
                    mpDescProcBuffer->uuid.uuid16 = gBleSig_CCCD_d;
                    GattClient_WriteCharacteristicDescriptor(peerDeviceId, mpDescProcBuffer, sizeof(uint16_t),
                                                             (uint8_t*)&value);
                }
            }
            else if (event == mAppEvt_PairingComplete_c)
            {
                /* Continue after pairing is complete */
                GattClient_ReadCharacteristicDescriptor(clientAncsPeerInfo.deviceId, mpDescProcBuffer ,23);
            }            
            break;
        }
      
        
        case mAppRunning_c:
        {
            if (event == mAppEvt_GattProcComplete_c)
            {
#if gBondingSupported_d                   
                /* Write data in NVM */
                Gap_SaveCustomPeerInformation(clientAncsPeerInfo.deviceId, 
                                              (void*) &clientAncsPeerInfo.customInfo, 0, 
                                              sizeof (appCustomInfo_t));
#endif                
#if (cPWR_UsePowerDownMode)               
                /* Start Wait For Data timer */
//                TMR_StartLowPowerTimer(mAppTimerId, 
//                               gTmrLowPowerSecondTimer_c,
//                               gConnReqParams.connIntervalMax * 20,
//                               DisconnectTimerCallback, NULL);  
#endif                
            }
        }
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function reset service discovery procedure.
 */

static void ClientAncs_ServiceDiscoveryReset()
{
    if (mpServiceDiscoveryBuffer != NULL)
    {
        MEM_BufferFree(mpServiceDiscoveryBuffer);
        mpServiceDiscoveryBuffer = NULL;
    }
    
    if (mpCharDiscoveryBuffer != NULL)
    {
        MEM_BufferFree(mpCharDiscoveryBuffer);
        mpCharDiscoveryBuffer = NULL;
    }
    
    if (mpCharDescriptorBuffer != NULL)
    {
        MEM_BufferFree(mpCharDescriptorBuffer);
        mpCharDescriptorBuffer = NULL;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Service discovery error handler.
 */

void ClientAncs_ServiceDiscoveryErrorHandler()
{
   clientAncsPeerInfo.appState = mAppIdle_c;   
   ClientAncs_ServiceDiscoveryReset();
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Function called when service discovery procedure is completed.
 */

static void ClientAncs_ServiceDiscoveryCompleted()
{
    clientAncsPeerInfo.appState = mAppDescriptorSetup_c;
    ClientAncs_ServiceDiscoveryReset();
    
    if (clientAncsPeerInfo.customInfo.ancClientConfig.hNotifSourceCccd)
    {
        mpDescProcBuffer = MEM_BufferAlloc(sizeof(gattAttribute_t) + 23);
                                        
        if (!mpDescProcBuffer)
        {
            return;
        }
        mpDescProcBuffer->handle = clientAncsPeerInfo.customInfo.ancClientConfig.hNotifSourceCccd;
        mpDescProcBuffer->paValue = (uint8_t*)(mpDescProcBuffer + 1);
        GattClient_ReadCharacteristicDescriptor(clientAncsPeerInfo.deviceId, mpDescProcBuffer ,23);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Save discovered service  handles.
 *
 *    @param   pService   Gatt service.
 */

static void ClientAncs_StoreServiceHandles
(
    gattService_t   *pService
)
{
    uint8_t i;
      
    if ((pService->uuidType == gBleUuidType128_c) &&
        FLib_MemCmp(pService->uuid.uuid128, uuid_service_ancs, 16))
    {
        /* Found ANC Service */
        clientAncsPeerInfo.customInfo.ancClientConfig.hService = pService->startHandle;
        
        for (i = 0; i < pService->cNumCharacteristics; i++)
        {
            if ((pService->aCharacteristics[i].value.uuidType == gBleUuidType128_c) &&
                FLib_MemCmp(pService->aCharacteristics[i].value.uuid.uuid128, uuid_char_ancs_notif_source, 16))
            {
                /* Found Nofitication Source Char */
                clientAncsPeerInfo.customInfo.ancClientConfig.hNotifSource = pService->aCharacteristics[i].value.handle;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Stores handles for the specified characteristic.
 *    @param   pChar    Pointer to gattCharacteristic_t.
 */

static void ClientAncs_StoreCharHandles
(
    gattCharacteristic_t   *pChar
)
{
    uint8_t i;
    
    if ((pChar->value.uuidType == gBleUuidType128_c) &&
        FLib_MemCmp(pChar->value.uuid.uuid128, uuid_char_ancs_notif_source, 16))
    {    
        for (i = 0; i < pChar->cNumDescriptors; i++)
        {
            if (pChar->aDescriptors[i].uuidType == gBleUuidType16_c)
            {
                switch (pChar->aDescriptors[i].uuid.uuid16)
                {
                    case gBleSig_CCCD_d:
                    {
                        clientAncsPeerInfo.customInfo.ancClientConfig.hNotifSourceCccd = pChar->aDescriptors[i].handle;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
