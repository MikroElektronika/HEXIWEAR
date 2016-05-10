/*! *********************************************************************************
* \addtogroup BLE OTAP Server
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
* \file app.c
* This file is the source file for the BLE OTAP Server application.
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
#include "FunctionLib.h"
#include "fsl_osa_ext.h"
#include "panic.h"
#include "FsciInterface.h"
#include "MemManager.h"

/* BLE Host Stack */
#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gatt_database.h"
#include "gap_interface.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_handles.h"
#include "l2ca_cb_interface.h"

/* Profile / Services */
#include "otap_interface.h"

#include "ApplMain.h"
#include "app.h"
#include "fsci_ble_otap.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/

#define mAppLeCbInitialCredits_c    16384

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

typedef enum appEvent_tag{
    mAppEvt_PeerConnected_c,
    mAppEvt_PairingComplete_c,
    mAppEvt_GattProcComplete_c,
    mAppEvt_GattProcError_c,
    mAppEvt_FsciBleOtapCmdReceived_c,
    mAppEvt_CbConnectionComplete_c,
    mAppEvt_CbConnectionFailed_c,
    mAppEvt_CbDisconnected_c,
}appEvent_t;

typedef enum appState_tag{
    mAppIdle_c,
    mAppExchangeMtu_c,
    mAppPrimaryServiceDisc_c,
    mAppCharServiceDisc_c,
    mAppDescriptorSetup_c,
    mAppCbConnecting_c,
    mAppRunning_c,
}appState_t;

typedef struct appCustomInfo_tag
{
    otapServerConfig_t   otapServerConfig;
    /* Add persistent information here */
}appCustomInfo_t;

typedef struct appPeerInfo_tag
{
    deviceId_t      deviceId;
    appCustomInfo_t customInfo;
    bool_t          isBonded;
    appState_t      appState;
}appPeerInfo_t;

/*! Structure type holding basic information about the images available on an OTAP Server. */
typedef struct imgInfo_tag
{
    uint8_t         imgId[gOtap_ImageIdFieldSize_c];        /*!< Image id. */
    uint8_t         imgVer[gOtap_ImageVersionFieldSize_c];  /*!< Image version. */
    uint32_t        imgSize;                                /*!< Image size. */
} imgInfo_t;

/*! Structure containing the OTAP Server functional data. */
typedef struct otapServerAppData_tag
{
    imgInfo_t                       images[1];                  /*!< Array of images available on this OTAP Server. Only 1 image is supported at thsi time. */
    const otapServerStorageMode_t   storageMode;                /*!< Storage mode used by the OTAP Server. Depends on the storage support available on the platform. */
    otapTransferMethod_t            transferMethod;             /*!< OTAP Image File ransfer method requested by the OTAP Client. */
    uint16_t                        l2capChannelOrPsm;          /*!< L2CAP Channel or PSM used for the transfer of the image file: channel 0x0004 for ATT, application specific PSM for CoC. */
    bool_t                          sentInitialImgNotification; /*!< Boolean flag which is set if an Image Notification is sent ot the OTAP Client on the first connection. */
    otapCmdIdt_t                    lastCmdSentToOtapClient;    /*!< The last command sent to the OTAP Client for which a Write Response is expected. */
    void*                           pLastFsciCmdId;             /*!< Pointer to the Id of the last OTAP command received from the FSCI. */
    void*                           pLastFsciCmdPayload;        /*!< Pointer to the payload of the last OTAP command received from the FSCI. */
    uint32_t                        lastFsciCmdPayloadLen;      /*!< Length of the last OTAP command received from the FSCI. */
    bool_t                          l2capPsmConnected;          /*!< Flag which is set to true if an L2CAP PSM connection is currently established with a peer device. */                         
} otapServerAppData_t;
  

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
static appPeerInfo_t mPeerInformation;
static bleDeviceAddress_t deviceAddress;

/* Scanning variables */
static gapScanningParameters_t scanParams = gGapDefaultScanningParameters_d;
static bool_t   mScanningOn = FALSE;
static bool_t   mFoundDeviceToConnect = FALSE;
static tmrTimerID_t mAppTimerId;

/* Buffer used for Service Discovery */
static gattService_t *mpServiceDiscoveryBuffer = NULL;
static uint8_t  mcPrimaryServices = 0;

/* Buffer used for Characteristic Discovery */
static gattCharacteristic_t *mpCharDiscoveryBuffer = NULL;
static uint8_t mCurrentServiceInDiscoveryIndex;
static uint8_t mCurrentCharInDiscoveryIndex;

/* Buffer used for Characteristic Descriptor Discovery */
static gattAttribute_t *mpCharDescriptorBuffer = NULL;

/* Buffer used for Characteristic related procedures */
static gattAttribute_t      *mpDescProcBuffer = NULL;

/* Timers */

/* FSCI serial configuration structure */
static gFsciSerialConfig_t fsciConfigStruct = 
{
    .interfaceType      = gSerialMgrLpuart_c,
    .interfaceChannel   = 0,
    .baudrate           = gUARTBaudRate115200_c
};

/* Application Data */

/*! OTAP Server data structure.
 *  Contains functional information, available images information and state information
 *  regarding the image download procedure to the OTAp Client. */
static otapServerAppData_t      otapServerData = 
{
    .images =       {
                        {
                            .imgId      = {0xFF, 0xFF}, // No Image
                            .imgVer     = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // No image version initialized
                            .imgSize    = 0,
                        },
                    },
    .storageMode    = gOtapServerStoargeNone_c,
    .transferMethod = gOtapTransferMethodAtt_c, // The default transfer method is ATT
    .l2capChannelOrPsm = gL2capCidAtt_c,  // The default L2CAP channel is the ATT Channel
    .sentInitialImgNotification = TRUE, // Disable the transmission of a New Image Notification immediately after the connection is established
    .lastCmdSentToOtapClient = gOtapCmdIdNoCommand_c,
    .pLastFsciCmdId = NULL,
    .pLastFsciCmdPayload = NULL,
    .lastFsciCmdPayloadLen = 0,
    .l2capPsmConnected = FALSE,
};

/************************************************************************************
*************************************************************************************
* External memory declarations
*************************************************************************************
************************************************************************************/
extern gapPairingParameters_t gPairingParams;
extern gapConnectionRequestParameters_t gConnReqParams;
extern gapSmpKeys_t gSmpKeys;

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/* Host Stack callbacks */
static void BleApp_ScanningCallback 
(
    gapScanningEvent_t* pScanningEvent
);

static void BleApp_ConnectionCallback 
(
    deviceId_t peerDeviceId, 
    gapConnectionEvent_t* pConnectionEvent
);

static void BleApp_GattClientCallback 
(
    deviceId_t              serverDeviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
);

static void BleApp_HandleValueWriteConfirmations 
(
    deviceId_t  deviceId
);

static void BleApp_GattIndicationCallback
(
    deviceId_t  serverDeviceId, 
    uint16_t    characteristicValueHandle,
    uint8_t*    aValue,
    uint16_t    valueLength
);

static void BleApp_AttributeIndicated
(
    deviceId_t  deviceId,
    uint16_t    handle,
    uint8_t*    pValue,
    uint16_t    length
);

/* L2CAP LE PSM callbacks */
static void BleApp_L2capPsmDataCallback
(
    deviceId_t  deviceId,
    uint16_t    lePsm,
    uint8_t*    pPacket,
    uint16_t    packetLength
);

static void BleApp_L2capPsmControlCallback
(
    l2capControlMessageType_t   messageType,
    void*                       pMessage
);

static void BleApp_Config();

void BleApp_StateMachineHandler
(
    deviceId_t peerDeviceId,
    uint8_t event
);

static bool_t CheckScanEvent(gapScannedDevice_t* pData);

static void BleApp_StoreServiceHandles
(
    gattService_t   *pService
);

static void BleApp_StoreCharHandles
(
    gattCharacteristic_t   *pChar
);

static void BleApp_StoreDescValues
(
    gattAttribute_t     *pDesc
);

static void BleApp_ServiceDiscoveryErrorHandler(void);

static void ScanningTimeoutTimerCallback(void* pParam);

/* OTAP Server functions */
static void OtapServer_SendCommandToOtapClient (deviceId_t  otapClientDevId,
                                                void*       pCommand,
                                                uint16_t    cmdLength);

static void OtapServer_SendCImgChunkToOtapClient (deviceId_t  otapClientDevId,
                                                  void*       pChunk,
                                                  uint16_t    chunkLength);
/* Connection and Disconnection events */
static void OtapServer_HandleDisconnectionEvent (deviceId_t deviceId);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Initializes application specific functionality before the BLE stack init.
*
********************************************************************************** */
void BleApp_Init(void)
{  
    /* Serial Manager Initialization */
    SerialManager_Init ();
    
    /* FSCI Initialization */
    FSCI_Init (&fsciConfigStruct);
    
    /* Register the BLE OTAP Opcode group with a FSCI interface */
    FsciBleOtap_Register (gBoardBleOtapFsciInterface_c);
}

/*! *********************************************************************************
* \brief    Starts the BLE application.
*
********************************************************************************** */
void BleApp_Start(void)
{
    if (!mScanningOn)
    {
        App_StartScanning(&scanParams, BleApp_ScanningCallback);
    }
}

/*! *********************************************************************************
* \brief        Handles keyboard events.
*
* \param[in]    events    Key event structure.
********************************************************************************** */
void BleApp_HandleKeys(key_event_t events)
{    
    switch (events) {
    case gKBD_EventPressPB1_c:
		LED_StopFlashingAllLeds();
        Led1Flashing();
		BleApp_Start();
        break;
    case gKBD_EventPressPB2_c:
        break;
    case gKBD_EventLongPB1_c:
        Gap_Disconnect(mPeerInformation.deviceId);
        break;
    case gKBD_EventLongPB2_c:
        break;
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
            BleApp_Config();
        }
        break;    
            
        case gPublicAddressRead_c:
        {
            /* Copy address from controller*/
            FLib_MemCpy(deviceAddress, pGenericEvent->eventData.aAddress, sizeof(bleDeviceAddress_t));
        }
        break;
        default: 
            break;
    }
}


/*! *********************************************************************************
* \brief        Handles a FSCI BLE OTAP command.
*
* \param[in]    pPacket         Pointer to the packet recieved via the FSCI interface.
* \param[in]    fsciInterface   Interface from whihc the packet was received.
*
********************************************************************************** */
void BleApp_HandleFsciBleOtapCommand (clientPacket_t*   pPacket,
                                      uint32_t          fsciInterface)
{
    /*! Initialize the OTAP Cmd pointer to the location of the payload minus the
     *  Command ID field size because the FSCI command payload only contains the
     *  OTAP command payload and not the OTAP Command opcode which is stored
     *  in the FSCI BLE OTAP packet header.
     *  The OTAP CmdId accessed through this pointer is not valid!!! */
    otapCommand_t*  pOtapCmd = (otapCommand_t*)((uint8_t*)(pPacket->structured.payload) - gOtap_CmdIdFieldSize_c);
    bool_t          sendCmdToStateMachine = TRUE;
    
    switch (pPacket->structured.header.opCode)
    {
    case gOtapCmdIdNewImageNotification_c:
    {
        uint16_t cmdImgId;
        
        /* Check command parameters including length and send a FSCI Error
         * and stop immediately any of them is invalid */
        if (pPacket->structured.header.len != (cmdIdToCmdLengthTable[gOtapCmdIdNewImageNotification_c] - gOtap_CmdIdFieldSize_c))
        {
            /* If the length is not valid send a FSCI Error. */
            FSCI_Error (gFsciError_c, fsciInterface);
            sendCmdToStateMachine = FALSE;
            break;
        }
        /* Save image data in the local app buffer if a valid image id is received.
         * This message can be received via the serial interface even if an OTAP Client
         * was not found yet if the app requests image information via the serial interface. */
        FLib_MemCpy (&cmdImgId,
                     pOtapCmd->cmd.newImgInfoRes.imageId,
                     sizeof(cmdImgId));
        if ((cmdImgId != gBleOtaImageIdCurrentRunningImage_c) &&
            (cmdImgId != gBleOtaImageIdNoImageAvailable_c))
        {
            FLib_MemCpy (otapServerData.images[0].imgId,
                         pOtapCmd->cmd.newImgInfoRes.imageId,
                         sizeof(otapServerData.images[0].imgId));
            FLib_MemCpy (otapServerData.images[0].imgVer,
                         pOtapCmd->cmd.newImgInfoRes.imageVersion,
                         sizeof(otapServerData.images[0].imgVer));
            FLib_MemCpy ((uint8_t*)(&otapServerData.images[0].imgSize),
                         (uint8_t*)(&pOtapCmd->cmd.newImgInfoRes.imageFileSize),
                         sizeof(otapServerData.images[0].imgSize));
        }
        /* This command will be sent to the application state machine. */
        break;
    }
    case gOtapCmdIdNewImageInfoRequest_c:
        /* This should never be sent by an OTAP Server - Ignore */
        sendCmdToStateMachine = FALSE;
        break;
    case gOtapCmdIdNewImageInfoResponse_c:
    {
        uint16_t cmdImgId;
        
        if (pPacket->structured.header.len != (cmdIdToCmdLengthTable[gOtapCmdIdNewImageInfoResponse_c] - gOtap_CmdIdFieldSize_c))
        {
            /* If the length is not valid send a FSCI Error. */
            FSCI_Error (gFsciError_c, fsciInterface);
            sendCmdToStateMachine = FALSE;
            break;
        }
        /* Save image data in the local app buffer if a valid image id is received.
         * This message can be received via the serial interface even if an OTAP Client
         * was not found yet if the app requests image information via the serial interface. */
        FLib_MemCpy (&cmdImgId,
                     pOtapCmd->cmd.newImgNotif.imageId,
                     sizeof(cmdImgId));
        if ((cmdImgId != gBleOtaImageIdCurrentRunningImage_c) &&
            (cmdImgId != gBleOtaImageIdNoImageAvailable_c))
        {
            FLib_MemCpy (otapServerData.images[0].imgId,
                         pOtapCmd->cmd.newImgNotif.imageId,
                         sizeof(otapServerData.images[0].imgId));
            FLib_MemCpy (otapServerData.images[0].imgVer,
                         pOtapCmd->cmd.newImgNotif.imageVersion,
                         sizeof(otapServerData.images[0].imgVer));
            FLib_MemCpy ((uint8_t*)(&otapServerData.images[0].imgSize),
                         (uint8_t*)(&pOtapCmd->cmd.newImgNotif.imageFileSize),
                         sizeof(otapServerData.images[0].imgSize));
        }
        /* This command will be sent to the application state machine. */
        break;
    }    
    case gOtapCmdIdImageBlockRequest_c:
        /* This should never be sent by an OTAP Server - Ignore */
        sendCmdToStateMachine = FALSE;
        break;
    case gOtapCmdIdImageChunk_c:
        if (((otapServerData.transferMethod == gOtapTransferMethodAtt_c)  &&
             (pPacket->structured.header.len > gOtap_ImageChunkDataSizeAtt_c + gOtap_ChunkSeqNumberSize_c)
            ) ||
            ((otapServerData.transferMethod == gOtapTransferMethodL2capCoC_c)  &&
             (pPacket->structured.header.len > gOtap_ImageChunkDataSizeL2capCoc_c + gOtap_ChunkSeqNumberSize_c)
            )
           )
        {
            /* If the length is not valid send a FSCI Error. */
            FSCI_Error (gFsciError_c, fsciInterface);
            sendCmdToStateMachine = FALSE;
            break;
        }
        /* This command will be sent to the application state machine. */
        break;
    case gOtapCmdIdImageTransferComplete_c:
        /* This should never be sent by an OTAP Server - Ignore */
        sendCmdToStateMachine = FALSE;
        break;
    case gOtapCmdIdErrorNotification_c:
        /* This command will be sent to the application state machine. */
        if (pPacket->structured.header.len != (cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c] - gOtap_CmdIdFieldSize_c))
        {
            /* If the length is not valid send a FSCI Error. */
            FSCI_Error (gFsciError_c, fsciInterface);
            sendCmdToStateMachine = FALSE;
            break;
        }
        break;
    case gOtapCmdIdStopImageTransfer_c:
        /* This should never be sent by an OTAP Server - Ignore */
        sendCmdToStateMachine = FALSE;
        break;
    default:
        /* If the Opcode is not recognized send a FSCI Error. */
        FSCI_Error (gFsciUnknownOpcode_c, fsciInterface);
        sendCmdToStateMachine = FALSE;
        break;
    }
    
    if (TRUE == sendCmdToStateMachine)
    {
        /* Notify the application state machine that a command has been received.
         * Depending on it's state it may do something or ignore it. */
        otapServerData.pLastFsciCmdId = &(pPacket->structured.header.opCode);
        otapServerData.pLastFsciCmdPayload = pPacket->structured.payload;
        otapServerData.lastFsciCmdPayloadLen = pPacket->structured.header.len;
        BleApp_StateMachineHandler (mPeerInformation.deviceId, mAppEvt_FsciBleOtapCmdReceived_c);
    }
}


/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief        Configures BLE Stack after initialization. Usually used for
*               configuring advertising, scanning, white list, services, et al.
*
********************************************************************************** */
static void BleApp_Config()
{    
    /* Read the address from the controller */
    Gap_ReadPublicDeviceAddress();
    
    /* Register OTAP L2CAP PSM */
    App_RegisterLePsm (gOtap_L2capLePsm_c,
                       BleApp_L2capPsmDataCallback,
                       BleApp_L2capPsmControlCallback,
                       gOtapCmdImageChunkCocLength_c);  //The negotiated MTU must be higher than the biggest data chunk that will be sent fragmented
    
    /* Register stack callbacks */
    App_RegisterGattClientProcedureCallback (BleApp_GattClientCallback);
    App_RegisterGattClientIndicationCallback (BleApp_GattIndicationCallback);
	
    /* Initialize private variables */
    mPeerInformation.appState = mAppIdle_c;
    mScanningOn = FALSE;
    mFoundDeviceToConnect = FALSE;
    
    /* Allocate scan timeout timer */
    mAppTimerId = TMR_AllocateTimer();
}


/*! *********************************************************************************
* \brief        Handles BLE Scanning callback from host stack.
*
* \param[in]    pScanningEvent    Pointer to gapScanningEvent_t.
********************************************************************************** */
static void BleApp_ScanningCallback (gapScanningEvent_t* pScanningEvent)
{
    switch (pScanningEvent->eventType)
    {
        case gDeviceScanned_c:
        {
            mFoundDeviceToConnect = CheckScanEvent(&pScanningEvent->eventData.scannedDevice);
            if (mFoundDeviceToConnect)
            {        
                gConnReqParams.peerAddressType = pScanningEvent->eventData.scannedDevice.addressType;
                FLib_MemCpy(gConnReqParams.peerAddress, 
                            pScanningEvent->eventData.scannedDevice.aAddress,
                            sizeof(bleDeviceAddress_t));
                
                Gap_StopScanning();
            }
        }        
        break;
        
        case gScanStateChanged_c:
        {
            mScanningOn = !mScanningOn;
            
            /* Node starts scanning */
            if (mScanningOn)
            { 
                mFoundDeviceToConnect = FALSE;
                /* Start advertising timer */
                TMR_StartLowPowerTimer(mAppTimerId, 
                           gTmrLowPowerSecondTimer_c,
                           TmrSeconds(gScanningTime_c),
                           ScanningTimeoutTimerCallback, NULL);              

                LED_StopFlashingAllLeds();
                Led1Flashing();           
            }
            /* Node is not scanning */
            else
            {                
                TMR_StopTimer(mAppTimerId);
                
                if (mFoundDeviceToConnect)
                {
                    Gap_Connect(&gConnReqParams, BleApp_ConnectionCallback);
                }
                else
                {
                    Led1Flashing();
                    Led2Flashing();
                    Led3Flashing();
                    Led4Flashing();           
                }
            }
        }
        break;
        
        case gScanCommandFailed_c:
        {
			panic(0,0,0,0);
			break;
        }
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
    switch (pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
        {
            /* UI */
            LED_StopFlashingAllLeds();
            Led1On();
                        
            mPeerInformation.deviceId = peerDeviceId;
            mPeerInformation.isBonded = FALSE; 
                       
#ifdef gBondingSupported_d            
            Gap_CheckIfBonded(peerDeviceId, &mPeerInformation.isBonded);
            
            if ((mPeerInformation.isBonded) &&
                (gBleSuccess_c == Gap_LoadCustomPeerInformation(peerDeviceId,
                    (void*) &mPeerInformation.customInfo, 0, sizeof (appCustomInfo_t))))
            {              

                /* Restored custom connection information. Encrypt link */
                Gap_EncryptLink(peerDeviceId);
            }
#endif
            BleApp_StateMachineHandler(mPeerInformation.deviceId, mAppEvt_PeerConnected_c);
        }
        break;
        
        case gConnEvtDisconnected_c:
        {
            mPeerInformation.deviceId = gInvalidDeviceId_c;
            
            /* Reset Service Discovery to be sure*/
            BleApp_ServiceDiscoveryErrorHandler();
            
            /* Notify application */
            OtapServer_HandleDisconnectionEvent (peerDeviceId);
            
            /* UI */
            LED_TurnOffAllLeds();
            Led1Flashing();
            
            /* Restart application */
            BleApp_Start();
        }
        break;
        
#ifdef gBondingSupported_d
        case gConnEvtPasskeyRequest_c:
            Gap_EnterPasskey(peerDeviceId, 999999);
            break;
            
        case gConnEvtPasskeyDisplay_c:
            /* Display on a screen or simply ignore */
            break;
            
        case gConnEvtPairingRequest_c:
        {
            Gap_AcceptPairingRequest(peerDeviceId, &pConnectionEvent->eventData.pairingEvent);
        }
        break;
        
        case gConnEvtKeyExchangeRequest_c:
        {
            gapSmpKeys_t sentSmpKeys = gSmpKeys;
            
            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gLtk_c))
            {
                sentSmpKeys.aLtk = NULL;
                /* When the LTK is NULL EDIV and Rand are not sent and will be ignored. */
            }
            
            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gIrk_c))
            {
                sentSmpKeys.aIrk = NULL;
                /* When the IRK is NULL the Address and Address Type are not sent and will be ignored. */
            }
            
            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gCsrk_c))
            {
                sentSmpKeys.aCsrk = NULL;
            }
            
            Gap_SendSmpKeys(peerDeviceId, &sentSmpKeys);
            break;
        }
            
        case gConnEvtLongTermKeyRequest_c:
            if (pConnectionEvent->eventData.longTermKeyRequestEvent.ediv == gSmpKeys.ediv &&
                pConnectionEvent->eventData.longTermKeyRequestEvent.randSize == gSmpKeys.cRandSize)
            {
                Gap_LoadEncryptionInformation(peerDeviceId, gSmpKeys.aLtk, &gSmpKeys.cLtkSize);
                /* EDIV and RAND both matched */
                Gap_ProvideLongTermKey(peerDeviceId, gSmpKeys.aLtk, gSmpKeys.cLtkSize);
            }
            else
            /* EDIV or RAND size did not match */
            {
                Gap_DenyLongTermKey(peerDeviceId);
            }
            break;
        case gConnEvtPairingComplete_c:
        {
            if (pConnectionEvent->eventData.pairingCompleteEvent.pairingSuccessful)
            {
                BleApp_StateMachineHandler(mPeerInformation.deviceId, mAppEvt_PairingComplete_c);
            }
        }
          break;
        case gConnEvtEncryptionChanged_c:
        {

        }
        break;
#endif
        
    default:
        break;
    }
}

static void BleApp_StoreServiceHandles
(
    gattService_t   *pService
)
{
    uint8_t i;
      
    if ((pService->uuidType == gBleUuidType128_c) &&
        FLib_MemCmp(pService->uuid.uuid128, uuid_service_otap, 16))
    {
        /* Found OTAP Service */
        mPeerInformation.customInfo.otapServerConfig.hService = pService->startHandle;
        for (i = 0; i < pService->cNumCharacteristics; i++)
        {
            if ((pService->aCharacteristics[i].value.uuidType == gBleUuidType128_c) &&
                (TRUE == FLib_MemCmp (pService->aCharacteristics[i].value.uuid.uuid128, uuid_char_otap_control_point, sizeof(pService->aCharacteristics[i].value.uuid.uuid128))))
            {
                /* Found OTAP Control Point Char */
                mPeerInformation.customInfo.otapServerConfig.hControlPoint = pService->aCharacteristics[i].value.handle;
            }
            
            if ((pService->aCharacteristics[i].value.uuidType == gBleUuidType128_c) &&
                (TRUE == FLib_MemCmp (pService->aCharacteristics[i].value.uuid.uuid128, uuid_char_otap_data, sizeof(pService->aCharacteristics[i].value.uuid.uuid128))))
            {
                /* Found OTAP Data Char */
                mPeerInformation.customInfo.otapServerConfig.hData = pService->aCharacteristics[i].value.handle;
            }
        }
    }
}

static void BleApp_StoreCharHandles
(
    gattCharacteristic_t   *pChar
)
{
    uint8_t i;
    
    if ((pChar->value.uuidType == gBleUuidType128_c) &&
        (TRUE == FLib_MemCmp (pChar->value.uuid.uuid128, uuid_char_otap_control_point, sizeof(pChar->value.uuid.uuid128)))
       )
    {    
        for (i = 0; i < pChar->cNumDescriptors; i++)
        {
            if (pChar->aDescriptors[i].uuidType == gBleUuidType16_c)
            {
                switch (pChar->aDescriptors[i].uuid.uuid16)
                {
                    case gBleSig_CCCD_d:
                    {
                        mPeerInformation.customInfo.otapServerConfig.hControlPointCccd = pChar->aDescriptors[i].handle;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
}

static void BleApp_StoreDescValues
(
    gattAttribute_t     *pDesc
)
{
/* No descriptor values are stored in this application. */
}

static void BleApp_GattClientCallback(
    deviceId_t              serverDeviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
)
{
    if (procedureResult == gGattProcError_c)
    {    
        attErrorCode_t attError = (attErrorCode_t) (error & 0xFF);
        if (attError == gAttErrCodeInsufficientEncryption_c     ||
            attError == gAttErrCodeInsufficientAuthorization_c  ||
            attError == gAttErrCodeInsufficientAuthentication_c)
        {
            /* Start Pairing Procedure */    
            Gap_Pair(serverDeviceId, &gPairingParams);
        }
        
        BleApp_StateMachineHandler(serverDeviceId, mAppEvt_GattProcError_c);
    }
    
    else if (procedureResult == gGattProcSuccess_c)
    {        
        switch(procedureType)
        {
            case gGattProcExchangeMtu_c:                        /* Fallthrough */
            case gGattProcDiscoverAllPrimaryServices_c:         /* Fallthrough */
            case gGattProcWriteCharacteristicDescriptor_c:      
                break;
                
            
            case gGattProcDiscoverAllCharacteristics_c:
            {
                BleApp_StoreServiceHandles(mpServiceDiscoveryBuffer + mCurrentServiceInDiscoveryIndex);
                break;
            }
            
            case gGattProcDiscoverAllCharacteristicDescriptors_c:
            {
                BleApp_StoreCharHandles(mpCharDiscoveryBuffer + mCurrentCharInDiscoveryIndex);
                
                /* Move on to the next characteristic */
                mCurrentCharInDiscoveryIndex++; 
                break;
            }
            
            case gGattProcReadCharacteristicDescriptor_c:
            {
                if (mpDescProcBuffer != NULL)
                {
                    BleApp_StoreDescValues(mpDescProcBuffer);
                }
                break;
            }
            
            case gGattProcWriteCharacteristicValue_c:
                BleApp_HandleValueWriteConfirmations (serverDeviceId);
                break;
            
            default:
                break;
        }  
        
        BleApp_StateMachineHandler(serverDeviceId, mAppEvt_GattProcComplete_c);
    }
}

static void BleApp_HandleValueWriteConfirmations (deviceId_t  deviceId)
{
    /* Handle all command confirmations here - only for commands sent form
     * the OTAP Server to the OTAP Client. */
    switch (otapServerData.lastCmdSentToOtapClient)
    {
    case gOtapCmdIdNewImageNotification_c:      /* Fallthrough */
    case gOtapCmdIdNewImageInfoResponse_c:      /* Fallthrough */
    case gOtapCmdIdErrorNotification_c:         /* Fallthrough */
    default:
        /* Do nothing here at the moment.
         * All actions on the OTAP Server are trigerred by requests made by the
         * OTAP Client. Also the OTAP Client may choose to not respond to a
         * command received from the OTAP Server. */
        break;
    };
}

static void BleApp_GattIndicationCallback
(
    deviceId_t  serverDeviceId, 
    uint16_t    characteristicValueHandle,
    uint8_t*    aValue,
    uint16_t    valueLength
)
{
    BleApp_AttributeIndicated (serverDeviceId,
                               characteristicValueHandle,
                               aValue,
                               valueLength);
}

static void BleApp_AttributeIndicated 
(
    deviceId_t  deviceId,
    uint16_t    handle,
    uint8_t*    pValue,
    uint16_t    length
)
{
    if (handle == mPeerInformation.customInfo.otapServerConfig.hControlPoint)
    {
        if (otapServerData.storageMode == gOtapServerStoargeNone_c)
        {
            otapCommand_t*  pOtaCmd = (otapCommand_t*)pValue;
            /* If this a is an OTAP Block Request then save the transfer method and channel in the
             * application data structure. This information is needed when forwarding data chunks
             * to the device which requested them. */
            if (pOtaCmd->cmdId == gOtapCmdIdImageBlockRequest_c)
            {
                FLib_MemCpy ((uint8_t*)(&otapServerData.transferMethod),
                             (uint8_t*)(&pOtaCmd->cmd.imgBlockReq.transferMethod),
                             sizeof(pOtaCmd->cmd.imgBlockReq.transferMethod));
                FLib_MemCpy ((uint8_t*)(&otapServerData.l2capChannelOrPsm),
                             (uint8_t*)(&pOtaCmd->cmd.imgBlockReq.l2capChannelOrPsm),
                             sizeof(pOtaCmd->cmd.imgBlockReq.l2capChannelOrPsm));
                
                if (otapServerData.transferMethod == gOtapTransferMethodL2capCoC_c)
                {
                    if (otapServerData.l2capChannelOrPsm != gOtap_L2capLePsm_c)
                    {
                        /* An invalid L2CAP PSM was received in the image block request,
                         * transform the received command into an error notification and send it to the peer.
                         * It will also be forwarded via the serial interface to the image server. */
                        pOtaCmd->cmdId = gOtapCmdIdErrorNotification_c;
                        pOtaCmd->cmd.errNotif.cmdId = gOtapCmdIdImageBlockRequest_c;
                        pOtaCmd->cmd.errNotif.errStatus = gOtapStatusUnexpectedL2capChannelOrPsm_c;
                        
                        OtapServer_SendCommandToOtapClient (deviceId,
                                                            pOtaCmd,
                                                            cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
                    }
                    else if (otapServerData.l2capPsmConnected == FALSE)
                    {
                        /* An image block request was made with a CoC transfer method but the
                         * L2CAP Psm is not connected. Transform the received command into an
                         * error notification and send it to the peer.
                         * It will also be forwarded via the serial interface to the image server. */
                        pOtaCmd->cmdId = gOtapCmdIdErrorNotification_c;
                        pOtaCmd->cmd.errNotif.cmdId = gOtapCmdIdImageBlockRequest_c;
                        pOtaCmd->cmd.errNotif.errStatus = gOtapStatusNoL2capPsmConnection_c;
                        
                        OtapServer_SendCommandToOtapClient (deviceId,
                                                            pOtaCmd,
                                                            cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
                        
                        length = cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c];
                    }
                }   
            }
            /* If the OTAP Server does not have internal storage then all commands must be forwarded
             *  via the serial interface. */
            FsciBleOtap_SendPkt (&(pOtaCmd->cmdId),
                                 (uint8_t*)(&(pOtaCmd->cmd)),
                                 length - gOtap_CmdIdFieldSize_c);
        }
    }
    else
    {
        /*! A GATT Client is trying to GATT Indicate an unknown attribute value.
         *  This should not happen. Disconnect the link. */
        Gap_Disconnect (deviceId);
    }
}


static void BleApp_L2capPsmDataCallback (deviceId_t     deviceId,
                                         uint16_t       lePsm,
                                         uint8_t*       pPacket,
                                         uint16_t       packetLength)
{
    /* Do nothing here. No L2CAP PSM packets are expected by the OTAp server demo application. */
}


static void BleApp_L2capPsmControlCallback(l2capControlMessageType_t    messageType,
                                           void*                        pMessage)
{
    switch (messageType)
    {
        case gL2ca_LePsmConnectRequest_c:
        {
            l2caLeCbConnectionRequest_t *pConnReq = (l2caLeCbConnectionRequest_t *)pMessage;
            
            /* Respond to the peer L2CAP CB Connection request - send a connection response. */
            L2ca_ConnectLePsm (gOtap_L2capLePsm_c,
                               pConnReq->deviceId,
                               mAppLeCbInitialCredits_c);
            
            /* Set the application L2CAP PSM Connection flag to TRUE beacuse there is no gL2ca_LePsmConnectionComplete_c
             * event on the responder of the PSM connection. */
            otapServerData.l2capPsmConnected = TRUE;
            
            break;
        }
        case gL2ca_LePsmDisconnectNotification_c:
        {
            l2caLeCbDisconnection_t *pCbDisconnect = (l2caLeCbDisconnection_t *)pMessage;
            
            /* Call App State Machine */
            BleApp_StateMachineHandler (pCbDisconnect->deviceId, mAppEvt_CbDisconnected_c);
            
            otapServerData.l2capPsmConnected = FALSE;
            break;
        }
        case gL2ca_NoPeerCredits_c:
        {
            l2caLeCbNoPeerCredits_t *pCbNoPeerCredits = (l2caLeCbNoPeerCredits_t *)pMessage;
            L2ca_SendLeCredit (gOtap_L2capLePsm_c,
                               pCbNoPeerCredits->deviceId,
                               mAppLeCbInitialCredits_c);
            break;
        }
        case gL2ca_LocalCreditsNotification_c:
        {
            l2caLeCbLocalCreditsNotification_t *pMsg = (l2caLeCbLocalCreditsNotification_t *)pMessage;

            break;
        }
        default:
            break;
    }
}


static bool_t MatchDataInAdvElementList(gapAdStructure_t *pElement, void *pData, uint8_t iDataLen)
{ 
    uint8_t i;
    
    for (i=0; i < pElement->length; i+=iDataLen)
    {
        if (FLib_MemCmp(pData, &pElement->aData[i], iDataLen))
        {
            return TRUE;
        } 
    }
    
    return FALSE;
}

static bool_t CheckScanEvent(gapScannedDevice_t* pData)
{
    uint8_t index = 0;
    uint8_t name[10];
    uint8_t nameLength;
    bool_t foundMatch = FALSE;
    
    while (index < pData->dataLength)
    {
        gapAdStructure_t adElement;
        
        adElement.length = pData->data[index];
        adElement.adType = (gapAdType_t)pData->data[index + 1];
        adElement.aData = &pData->data[index + 2];
      
         /* Search for OTAP Custom Service */
        if ((adElement.adType == gAdIncomplete128bitServiceList_c) ||
            (adElement.adType == gAdComplete128bitServiceList_c))
        {
            foundMatch = MatchDataInAdvElementList(&adElement, &uuid_service_otap, 16);
        }
        
        if ((adElement.adType == gAdShortenedLocalName_c) ||
          (adElement.adType == gAdCompleteLocalName_c))
        {
            nameLength = MIN(adElement.length, 10);
            FLib_MemCpy(name, adElement.aData, nameLength);
        }
        
        /* Move on to the next AD elemnt type */
        index += adElement.length + sizeof(uint8_t);
    }
    return foundMatch;
}

static void BleApp_ServiceDiscoveryReset()
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

static void BleApp_ServiceDiscoveryErrorHandler()
{
   mPeerInformation.appState = mAppIdle_c;   
   BleApp_ServiceDiscoveryReset();
}

static void BleApp_ServiceDiscoveryCompleted()
{
    mPeerInformation.appState = mAppDescriptorSetup_c;   
    BleApp_ServiceDiscoveryReset();
   
    if (mPeerInformation.customInfo.otapServerConfig.hControlPointCccd)
    {
        mpDescProcBuffer = MEM_BufferAlloc(sizeof(gattAttribute_t) + 23);
                                        
        if (!mpDescProcBuffer)
        {
            panic(0,0,0,0);
            return;
        }
        mpDescProcBuffer->handle = mPeerInformation.customInfo.otapServerConfig.hControlPointCccd;
        mpDescProcBuffer->paValue = (uint8_t*)(mpDescProcBuffer + 1);
        GattClient_ReadCharacteristicDescriptor(mPeerInformation.deviceId, mpDescProcBuffer ,23);
    }
}

void BleApp_StateMachineHandler(deviceId_t peerDeviceId, uint8_t event)
{
    switch (mPeerInformation.appState)
    {
        case mAppIdle_c:
        {
            if (event == mAppEvt_PeerConnected_c)
            {
                /* Check if required service characteristic descoveries by the client app have been done
                 * and change the client application state accordingly. */
                if ((mPeerInformation.customInfo.otapServerConfig.hControlPoint == gGattDbInvalidHandle_d) ||
                    (mPeerInformation.customInfo.otapServerConfig.hControlPointCccd == gGattDbInvalidHandle_d) ||
                    (mPeerInformation.customInfo.otapServerConfig.hData == gGattDbInvalidHandle_d))
                {
                    otapCommand_t   otaCmd;
                    
                    /* Moving to Exchange MTU State */
                    mPeerInformation.appState = mAppExchangeMtu_c;          
                    GattClient_ExchangeMtu(peerDeviceId);
                    
                    /*! When a new unknown peer connects send a New Image Info request via FSCI
                     *  with the image version set to request info about all available images. */
                    otaCmd.cmdId = gOtapCmdIdNewImageInfoRequest_c;
                    /* Set the image ID to all zeroes representing current running image ID. */
                    FLib_MemSet (otaCmd.cmd.newImgInfoReq.currentImageId,
                                 0x00,
                                 sizeof(otaCmd.cmd.newImgInfoReq.currentImageId));\
                    /* Set the image version to all 0x00 representing a request for all available images. */
                    FLib_MemSet (otaCmd.cmd.newImgInfoReq.currentImageVersion,
                                 0x00,
                                 sizeof(otaCmd.cmd.newImgInfoReq.currentImageVersion));
                    FsciBleOtap_SendPkt (&otaCmd.cmdId,
                                         (uint8_t*)(&otaCmd.cmd.newImgInfoReq),
                                         sizeof(otapCmdNewImgInfoReq_t));
                }
                else
                {
                    /* Moving to Running State */
                    mPeerInformation.appState = mAppRunning_c;
                }
            }
        }
        break;
        
        case mAppExchangeMtu_c:
        {
            if (event == mAppEvt_GattProcComplete_c)
            {
              
                /* Allocate memory for Service Discovery */
                mpServiceDiscoveryBuffer = MEM_BufferAlloc(sizeof(gattService_t) * gMaxServicesCount_d);
                mpCharDiscoveryBuffer = MEM_BufferAlloc(sizeof(gattCharacteristic_t) * gMaxServiceCharCount_d);
                mpCharDescriptorBuffer = MEM_BufferAlloc(sizeof(gattAttribute_t) * gMaxCharDescriptorsCount_d);
                  
                if (!mpServiceDiscoveryBuffer || !mpCharDiscoveryBuffer || !mpCharDescriptorBuffer)
                    return;
                
                /* Moving to Primary Service Discovery State*/
                mPeerInformation.appState = mAppPrimaryServiceDisc_c;

                /* Start Service Discovery*/
//                GattClient_DiscoverAllPrimaryServices(
//                                            peerDeviceId,
//                                            mpServiceDiscoveryBuffer,
//                                            gMaxServicesCount_d,
//                                            &mcPrimaryServices);
                
                GattClient_DiscoverPrimaryServicesByUuid(
                                            peerDeviceId,
                                            gBleUuidType128_c,
                                            (bleUuid_t*)(&uuid_service_otap),
                                            mpServiceDiscoveryBuffer,
                                            1,
                                            &mcPrimaryServices
                                        );
                
            }
            else if (event == mAppEvt_GattProcError_c) 
            {
               BleApp_ServiceDiscoveryErrorHandler();
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
                    mPeerInformation.appState = mAppCharServiceDisc_c;

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
            }
            else if (event == mAppEvt_GattProcError_c) 
            {
                BleApp_ServiceDiscoveryErrorHandler();
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
                    BleApp_ServiceDiscoveryCompleted();
                }
            }
            else if (event == mAppEvt_GattProcError_c) 
            {
                BleApp_ServiceDiscoveryErrorHandler();
            }
        }
        break;      
        
        case mAppDescriptorSetup_c:
        {
            if (event == mAppEvt_GattProcComplete_c)
            {
                if (mPeerInformation.customInfo.otapServerConfig.hControlPointCccd)
                {
                    /* Set indication bit for a CCCD descriptor.  */
                    uint16_t value = gCccdIndication_c;
                    if (!mpDescProcBuffer)
                    {
                        panic(0,0,0,0);
                        return;
                    }
                    
                    /* Moving to Running State*/
                    mPeerInformation.appState = mAppRunning_c;
                    /* Enable indications for the OTAP Control point characteristic. */
                    mpDescProcBuffer->handle = mPeerInformation.customInfo.otapServerConfig.hControlPointCccd;
                    mpDescProcBuffer->uuid.uuid16 = gBleSig_CCCD_d;
                    GattClient_WriteCharacteristicDescriptor(peerDeviceId, mpDescProcBuffer, sizeof(uint16_t),
                                                             (uint8_t*)&value);
                }
            }
            else if (event == mAppEvt_PairingComplete_c)
            {
                /* Continue after pairing is complete */
                GattClient_ReadCharacteristicDescriptor(mPeerInformation.deviceId, mpDescProcBuffer ,23);
            }            
            break;
        }
      
        
        case mAppRunning_c:
        {
            if (event == mAppEvt_GattProcComplete_c)
            {
                /* Write data in NVM */
                Gap_SaveCustomPeerInformation(mPeerInformation.deviceId, 
                                              (void*) &mPeerInformation.customInfo, 0, 
                                              sizeof (appCustomInfo_t));
                
                if (FALSE == otapServerData.sentInitialImgNotification)
                {
                    uint16_t avaialbleImgId;
                    
                    FLib_MemCpy (&avaialbleImgId,
                                 otapServerData.images[0].imgId,
                                 sizeof(avaialbleImgId));
                    if ((avaialbleImgId != gBleOtaImageIdCurrentRunningImage_c) &&
                        (avaialbleImgId != gBleOtaImageIdNoImageAvailable_c))
                    {
                        otapCommand_t otapCommand;
                        
                        otapCommand.cmdId = gOtapCmdIdNewImageNotification_c;
                        FLib_MemCpy (otapCommand.cmd.newImgNotif.imageId,
                                     otapServerData.images[0].imgId,
                                     gOtap_ImageIdFieldSize_c);
                        FLib_MemCpy (otapCommand.cmd.newImgNotif.imageVersion,
                                     otapServerData.images[0].imgVer,
                                     gOtap_ImageVersionFieldSize_c);
                        FLib_MemCpy (&otapCommand.cmd.newImgNotif.imageFileSize,
                                     (uint8_t*)(&otapServerData.images[0].imgSize),
                                     sizeof(otapCommand.cmd.newImgNotif.imageFileSize));
                        otapServerData.sentInitialImgNotification = TRUE;
                        
                        OtapServer_SendCommandToOtapClient (peerDeviceId,
                                                            &otapCommand,
                                                            cmdIdToCmdLengthTable[gOtapCmdIdNewImageNotification_c]);
                        
                        otapServerData.sentInitialImgNotification = TRUE;
                    }
                }
            }
            else if (event == mAppEvt_FsciBleOtapCmdReceived_c)
            {
                if (*((otapCmdIdt_t*)(otapServerData.pLastFsciCmdId)) == gOtapCmdIdImageChunk_c)
                {
                    if (otapServerData.transferMethod == gOtapTransferMethodAtt_c)
                    {
                        otapCommand_t otapCommand;
                            
                        otapCommand.cmdId = gOtapCmdIdImageChunk_c;
                        FLib_MemCpy ((uint8_t*)(&otapCommand.cmd),
                                     otapServerData.pLastFsciCmdPayload,
                                     otapServerData.lastFsciCmdPayloadLen);
                        
                        OtapServer_SendCImgChunkToOtapClient (peerDeviceId,
                                                              &otapCommand,
                                                              otapServerData.lastFsciCmdPayloadLen + gOtap_CmdIdFieldSize_c);
                    }
                    else if (otapServerData.transferMethod == gOtapTransferMethodL2capCoC_c)
                    {
                        uint8_t         cmdBuffer[gOtapCmdImageChunkCocLength_c];
                        otapCommand_t*  pOtapCommand = (otapCommand_t*)cmdBuffer;
                        
                        if (otapServerData.l2capPsmConnected == TRUE)
                        {
                            pOtapCommand->cmdId = gOtapCmdIdImageChunk_c;
                            FLib_MemCpy ((uint8_t*)(&pOtapCommand->cmd),
                                         otapServerData.pLastFsciCmdPayload,
                                         otapServerData.lastFsciCmdPayloadLen);
                            
                            OtapServer_SendCImgChunkToOtapClient (peerDeviceId,
                                                                  pOtapCommand,
                                                                  otapServerData.lastFsciCmdPayloadLen + gOtap_CmdIdFieldSize_c);
                        }
                        else
                        {
                            /* If the L2CAP PSM channel is not connected then send an error notification to the server
                             * via the serial interface and to the client over the air. */
                            pOtapCommand->cmdId = gOtapCmdIdErrorNotification_c;
                            pOtapCommand->cmd.errNotif.cmdId = gOtapCmdIdNoCommand_c;
                            pOtapCommand->cmd.errNotif.errStatus = gOtapStatusNoL2capPsmConnection_c;
                            
                            OtapServer_SendCommandToOtapClient (peerDeviceId,
                                                                pOtapCommand,
                                                                cmdIdToCmdLengthTable[gOtapCmdIdErrorNotification_c]);
                            
                            FsciBleOtap_SendPkt (&(pOtapCommand->cmdId),
                                                 (uint8_t*)(&(pOtapCommand->cmd)),
                                                 sizeof(otapErrNotification_t));
                        }
                    }
                    
                }
                else
                {
                    otapCommand_t otapCommand;
                        
                    otapCommand.cmdId = *((uint8_t*)(otapServerData.pLastFsciCmdId));
                    FLib_MemCpy ((uint8_t*)(&otapCommand.cmd),
                                 otapServerData.pLastFsciCmdPayload,
                                 otapServerData.lastFsciCmdPayloadLen);
                    
                    OtapServer_SendCommandToOtapClient (peerDeviceId,
                                                        &otapCommand,
                                                        otapServerData.lastFsciCmdPayloadLen + gOtap_CmdIdFieldSize_c);
                }
            }
        }
        break;
    }
}

static void ScanningTimeoutTimerCallback(void* pParam)
{
    /* Stop scanning */
    if (mScanningOn)
    {
        Gap_StopScanning();
    }
}

static void OtapServer_SendCommandToOtapClient (deviceId_t  otapClientDevId,
                                                void*       pCommand,
                                                uint16_t    cmdLength)
{
    /* GATT Characteristic to be written - OTAP Client Control Point */
    gattCharacteristic_t    otapCtrlPointChar;
    bleResult_t             bleResult;
    
    /* Only the value handle element of this structure is relevant for this operation. */
    otapCtrlPointChar.value.handle = mPeerInformation.customInfo.otapServerConfig.hControlPoint;
    
    bleResult = GattClient_SimpleCharacteristicWrite (mPeerInformation.deviceId,
                                                      &otapCtrlPointChar,
                                                      cmdLength,
                                                      pCommand);
    
    if (gBleSuccess_c == bleResult)
    {
        otapServerData.lastCmdSentToOtapClient = (otapCmdIdt_t)(((otapCommand_t*)pCommand)->cmdId);
    }
    else
    {
        /*! A BLE error has occured - Disconnect */
        Gap_Disconnect (otapClientDevId);
    }
}

static void OtapServer_SendCImgChunkToOtapClient (deviceId_t  otapClientDevId,
                                                  void*       pChunk,
                                                  uint16_t    chunkCmdLength)
{
    bleResult_t     bleResult = gBleSuccess_c;
    
    if (otapServerData.transferMethod == gOtapTransferMethodAtt_c)
    {
        /* GATT Characteristic to be written without response - OTAP Client Data */
        gattCharacteristic_t    otapDataChar;
        
        /* Only the value handle element of this structure is relevant for this operation. */
        otapDataChar.value.handle = mPeerInformation.customInfo.otapServerConfig.hData;
        
        bleResult = GattClient_CharacteristicWriteWithoutResponse (mPeerInformation.deviceId,
                                                                   &otapDataChar,
                                                                   chunkCmdLength,
                                                                   pChunk);
    }
    else if (otapServerData.transferMethod == gOtapTransferMethodL2capCoC_c)
    {
        bleResult =  L2ca_SendLeCbData (gOtap_L2capLePsm_c,
                                        mPeerInformation.deviceId,
                                        pChunk,
                                        chunkCmdLength);
    }
    
    if (gBleSuccess_c != bleResult)
    {
        /*! A BLE error has occured - Disconnect */
        Gap_Disconnect (otapClientDevId);
    }
}

static void OtapServer_HandleDisconnectionEvent (deviceId_t deviceId)
{
    otapCommand_t   otaCmd;

    /* On the disconnection of the peer OTAP Client send a Stop Image Transfer
     * command via the FSCI interface. */
    otaCmd.cmdId = gOtapCmdIdStopImageTransfer_c;
    /* Set the image ID to all zeroes. */
    FLib_MemSet (otaCmd.cmd.stopImgTransf.imageId,
                 0x00,
                 sizeof(otaCmd.cmd.stopImgTransf.imageId));
    FsciBleOtap_SendPkt (&otaCmd.cmdId,
                         (uint8_t*)(&otaCmd.cmd.stopImgTransf),
                         sizeof(otapCmdStopImgTransfer_t));
}
/*! *********************************************************************************
* @}
********************************************************************************** */
