/*!
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file ApplMain.c
* This is a source file for the main application.
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
/* Drv */
#include "LED.h"
#include "Keyboard.h"
#include "KW4xXcvrDrv.h"

/* Fwk */
#include "MemManager.h"
#include "TimersManager.h"
#include "RNG_Interface.h"
#include "Messaging.h"
#include "Flash_Adapter.h"
#include "SecLib.h"
#include "Panic.h"

#if gFsciIncluded_c    
#include "FsciInterface.h"
#include "FsciCommands.h"
#endif

/* KSDK */
#include "board.h"
#include "fsl_device_registers.h"

/* Bluetooth Low Energy */
#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gap_interface.h"
#include "ble_init.h"
#include "l2ca_cb_interface.h"
#include "l2ca_interface.h"

#ifdef cPWR_UsePowerDownMode
#if (cPWR_UsePowerDownMode)
#include "PWR_Interface.h"
#endif
#endif

#ifdef FSL_RTOS_FREE_RTOS
#include "FreeRTOSConfig.h"
#endif

#include "ApplMain.h"


/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#ifndef mAppUseNvm_d
#define mAppUseNvm_d    TRUE
#endif

/* Application Events */
#define gAppEvtMsgFromHostStack_c       (1 << 0)

#define gAppIdleTaskPriority_c          (8)
#define gAppIdleTaskStackSize_c         (400)  

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
/* Host to Application Messages Types */
typedef enum {
    gAppGapGenericMsg_c = 0,
    gAppGapConnectionMsg_c,
    gAppGapAdvertisementMsg_c,
    gAppGapScanMsg_c,
    gAppGattServerMsg_c,
    gAppGattClientProcedureMsg_c,
    gAppGattClientNotificationMsg_c,
    gAppGattClientIndicationMsg_c,
    gAppL2caLeDataMsg_c,
    gAppL2caLeControlMsg_c,
}appHostMsgType_tag;

typedef uint8_t appHostMsgType_t;

/* Host to Application Connection Message */
typedef struct connectionMsg_tag{
    deviceId_t              deviceId;
    gapConnectionEvent_t    connEvent;
}connectionMsg_t;

/* Host to Application GATT Server Message */
typedef struct gattServerMsg_tag{
    deviceId_t          deviceId;
    gattServerEvent_t   serverEvent;
}gattServerMsg_t;

/* Host to Application GATT Client Procedure Message */
typedef struct gattClientProcMsg_tag{
    deviceId_t              deviceId;
    gattProcedureType_t     procedureType;
    gattProcedureResult_t   procedureResult;
    bleResult_t             error;
}gattClientProcMsg_t;

/* Host to Application GATT Client Notification/Indication Message */
typedef struct gattClientNotifIndMsg_tag{
    uint8_t*    aValue;
    uint16_t    characteristicValueHandle;
    uint16_t    valueLength;
    deviceId_t  deviceId;
}gattClientNotifIndMsg_t;

/* L2ca to Application Data Message */
typedef struct l2caLeCbDataMsg_tag{
    deviceId_t  deviceId;
    uint16_t    lePsm;
    uint16_t    packetLength;
    uint8_t     aPacket[0];
}l2caLeCbDataMsg_t;

/* L2ca to Application Control Message */
typedef struct l2caLeCbControlMsg_tag{
    l2capControlMessageType_t   messageType;
    uint16_t                    padding;
    uint8_t                     aMessage[0];
}l2caLeCbControlMsg_t;

typedef struct appMsgFromHost_tag{
    appHostMsgType_t    msgType;
    union {
        gapGenericEvent_t       genericMsg;
        gapAdvertisingEvent_t   advMsg;
        connectionMsg_t         connMsg;
        gapScanningEvent_t      scanMsg;
        gattServerMsg_t         gattServerMsg;
        gattClientProcMsg_t     gattClientProcMsg;
        gattClientNotifIndMsg_t gattClientNotifIndMsg;
        l2caLeCbDataMsg_t       l2caLeCbDataMsg;
        l2caLeCbControlMsg_t    l2caLeCbControlMsg;
    } msgData;
}appMsgFromHost_t;

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
#if (cPWR_UsePowerDownMode)
#ifdef FSL_RTOS_FREE_RTOS
#define AppIdle_TaskInit()
#define App_Idle_Task()
#else
static osaStatus_t AppIdle_TaskInit(void);
static void App_Idle_Task(task_param_t argument);
#endif
#endif

static void App_Thread (uint32_t param);
static void App_KeyboardCallBack(uint8_t events);
static void App_HandleHostMessageInput(appMsgFromHost_t* pMsg);
static void App_GenericCallback (gapGenericEvent_t* pGenericEvent);
static void App_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);
static void App_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent);
static void App_ScanningCallback (gapScanningEvent_t* pAdvertisingEvent);
static void App_GattServerCallback (deviceId_t peerDeviceId, gattServerEvent_t* pServerEvent);
static void App_GattClientProcedureCallback
(
    deviceId_t              deviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
);
static void App_GattClientNotificationCallback
(
    deviceId_t      deviceId,
    uint16_t        characteristicValueHandle,
    uint8_t*        aValue,
    uint16_t        valueLength
);
static void App_GattClientIndicationCallback
(
    deviceId_t      deviceId,
    uint16_t        characteristicValueHandle,
    uint8_t*        aValue,
    uint16_t        valueLength
);

static void App_L2caLeDataCallback
(
    deviceId_t deviceId,
    uint16_t   lePsm,
    uint8_t* pPacket,
    uint16_t packetLength
);

static void App_L2caLeControlCallback
(
    l2capControlMessageType_t  messageType,
    void* pMessage
);

static void BLE_SignalFromISRCallback(void);
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
#if cPWR_UsePowerDownMode
OSA_TASK_DEFINE( IDLE, gAppIdleTaskStackSize_c );
task_handler_t gAppIdleTaskId = 0;
#endif  /* cPWR_UsePowerDownMode */
  
static event_t  mAppEvent;

/* Application input queues */
static anchor_t mHostAppInputQueue;

static uint8_t platformInitialized = 0;

static gapAdvertisingCallback_t pfAdvCallback = NULL;
static gapScanningCallback_t pfScanCallback = NULL;
static gapConnectionCallback_t  pfConnCallback = NULL;
static gattServerCallback_t pfGattServerCallback = NULL;
static gattClientProcedureCallback_t pfGattClientProcCallback = NULL;
static gattClientNotificationCallback_t pfGattClientNotifCallback = NULL;
static gattClientNotificationCallback_t pfGattClientIndCallback = NULL;
static l2caLeCbDataCallback_t           pfL2caLeCbDataCallback = NULL;
static l2caLeCbControlCallback_t        pfL2caLeCbControlCallback = NULL;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
#if gRNG_HWSupport_d == gRNG_NoHWSupport_d
extern uint32_t mRandomNumber;
#endif
extern const uint8_t gUseRtos_c;
extern uint32_t NV_STORAGE_END_ADDRESS[];
uint32_t gNvmStartAddress_c;

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

extern void BleApp_Init(void);
extern void BleApp_HandleKeys(key_event_t events);

#if gUseHciTransportUpward_d
#define BleApp_GenericCallback(param)  
#else
extern void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent);
#endif

extern void (*pfBLE_SignalFromISR)(void);

/*! *********************************************************************************
* \brief  This is the first task created by the OS. This task will initialize 
*         the system
*
* \param[in]  param
*
********************************************************************************** */

extern uint8_t gBDAddress_c[6];

void main_task(uint32_t param)
{  
    uint8_t uniqueID[10];            
    
    // Read unique ID
    FLib_MemCpy(gBDAddress_c, (uint8_t *)&SIM_BASE_PTR->UIDMH, 2);
    FLib_MemCpy(gBDAddress_c + 2, (uint8_t *)&SIM_BASE_PTR->UIDML, 4);
    
    if (!platformInitialized)
    {
        osa_status_t status;
        uint8_t pseudoRNGSeed[20] = {0};
		
        platformInitialized = 1;
        
        hardware_init();
        
        /* Framework init */ 
        MEM_Init();
        TMR_Init();       
        LED_Init();
        SecLib_Init();
        
        RNG_Init();   
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[0])));
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[4])));
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[8])));
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[12])));
        RNG_GetRandomNo((uint32_t*)(&(pseudoRNGSeed[16])));
        RNG_SetPseudoRandomNoSeed(pseudoRNGSeed);
        
        KBD_Init(App_KeyboardCallBack);

#if mAppUseNvm_d        
        /* Initialize NV module */
        NV_Init();
        
        /* NV_STORAGE_END_ADDRESS from linker file is used as NV Start Address */
        gNvmStartAddress_c = (uint32_t)((uint8_t*)NV_STORAGE_END_ADDRESS);
#endif
        
        pfBLE_SignalFromISR = BLE_SignalFromISRCallback;        
        
#if (cPWR_UsePowerDownMode)
        AppIdle_TaskInit();
        PWR_Init();
        PWR_DisallowDeviceToSleep();
#else    
        Led1Flashing();
        Led2Flashing();
        Led3Flashing();
        Led4Flashing();           
#endif    
       
        /* Initialize peripheral drivers specific to the application */
        BleApp_Init();
        
        /* BLE Radio Init */    
        XcvrInit(BLE);    
            
        /* Create application event */
        status = OSA_EventCreate(&mAppEvent, kEventAutoClear);
        if( kStatus_OSA_Success != status )
        {
            panic(0,0,0,0);
            return;
        }
        
        /* Prepare application input queue.*/
        MSG_InitQueue(&mHostAppInputQueue); 
        
        /* BLE Host Stack Init */
        if (Ble_Initialize(App_GenericCallback) != gBleSuccess_c)
        {
            panic(0,0,0,0);
            return;
        }
    }
    
    /* Call application task */
    App_Thread( param );
}

/*! *********************************************************************************
* \brief  This function represents the Application task. 
*         This task reuses the stack alocated for the MainThread.
*         This function is called to process all events for the task. Events 
*         include timers, messages and any other user defined events.
* \param[in]  argument
*
********************************************************************************** */
void App_Thread (uint32_t param)
{
    event_flags_t event;
    
    while(1)
    { 
        OSA_EventWait(&mAppEvent, 0x00FFFFFF, FALSE, OSA_WAIT_FOREVER, &event);
        
        /* Dequeue the host to app message */
        if (event & gAppEvtMsgFromHostStack_c)
        {
            /* Pointer for storing the messages from host. */
            appMsgFromHost_t *pMsgIn = NULL;  
            
            /* Check for existing messages in queue */
            while(MSG_Pending(&mHostAppInputQueue))
            {
                pMsgIn = MSG_DeQueue(&mHostAppInputQueue);
            
                if (pMsgIn)
                {
                    /* Process it */
                    App_HandleHostMessageInput(pMsgIn);
                    
                    /* Messages must always be freed. */
                    MSG_Free(pMsgIn);
                    pMsgIn = NULL;
                }
            }
        }

        /* For BareMetal break the while(1) after 1 run */
        if( gUseRtos_c == 0 )
        {
            break;
        }
    }
}

#if (cPWR_UsePowerDownMode)

extern void BleApp_LowPowerExitCallback(void);

static void App_Idle(void)
{
    PWRLib_WakeupReason_t wakeupReason;
    
    if( PWR_CheckIfDeviceCanGoToSleep() )
    {
        PORT_HAL_SetPinIntMode(PORTB,0u,kPortIntDisabled);
        
        /* Enter Low Power */
        wakeupReason = PWR_EnterLowPower();
        
        BleApp_LowPowerExitCallback();

#if gFSCI_IncludeLpmCommands_c
        /* Send Wake Up indication to FSCI */
        FSCI_SendWakeUpIndication();
#endif

#if gKeyBoardSupported_d      
        /* Woke up on Keyboard Press */
        if(wakeupReason.Bits.FromKeyBoard)
        {
            KBD_SwitchPressedOnWakeUp();
            PWR_DisallowDeviceToSleep();
        }
#endif   
    }
}

#endif /* cPWR_UsePowerDownMode */

#ifdef FSL_RTOS_FREE_RTOS
void vApplicationIdleHook(void)
{
#if (cPWR_UsePowerDownMode)
    App_Idle();  
#endif  
}
#else /* FSL_RTOS_FREE_RTOS */

#if (cPWR_UsePowerDownMode)

static void App_Idle_Task(task_param_t argument)
{
    while(1)
    {           
        App_Idle();
 
        /* For BareMetal break the while(1) after 1 run */
        if (gUseRtos_c == 0)
        {
            break;
        }
    }
}

static osaStatus_t AppIdle_TaskInit(void)
{	  
    osa_status_t status;
    
    if(gAppIdleTaskId)
    {      
        return osaStatus_Error;
    }
   
    /* Task creation */
    status = OSA_TaskCreate(App_Idle_Task, "IDLE_Task", gAppIdleTaskStackSize_c, IDLE_stack,
                            gAppIdleTaskPriority_c, (task_param_t)NULL, FALSE, &gAppIdleTaskId);
    
    if( kStatus_OSA_Success != status )
    {
        panic(0,0,0,0);
        return osaStatus_Error;
    }

    return osaStatus_Success;
}
#endif /* cPWR_UsePowerDownMode */

#endif /* FSL_RTOS_FREE_RTOS */



void App_StartAdvertising(
    gapAdvertisingCallback_t    advertisingCallback,
    gapConnectionCallback_t     connectionCallback
)
{
    pfAdvCallback = advertisingCallback;
    pfConnCallback = connectionCallback;
    
    Gap_StartAdvertising(App_AdvertisingCallback, App_ConnectionCallback);
}

void App_StartScanning(
    gapScanningParameters_t*    pScanningParameters,
    gapScanningCallback_t       scanningCallback
)
{
    pfScanCallback = scanningCallback;
    
    Gap_StartScanning(pScanningParameters, App_ScanningCallback);
}

void App_RegisterGattServerCallback(gattServerCallback_t  serverCallback)
{
    pfGattServerCallback = serverCallback;
    
    GattServer_RegisterCallback(App_GattServerCallback);
}

void App_RegisterGattClientProcedureCallback(gattClientProcedureCallback_t  callback)
{
    pfGattClientProcCallback = callback;

    GattClient_RegisterProcedureCallback(App_GattClientProcedureCallback);
}

void App_RegisterGattClientNotificationCallback(gattClientNotificationCallback_t  callback)
{
    pfGattClientNotifCallback = callback;

    GattClient_RegisterNotificationCallback(App_GattClientNotificationCallback);
}

void App_RegisterGattClientIndicationCallback(gattClientIndicationCallback_t  callback)
{
    pfGattClientIndCallback = callback;

    GattClient_RegisterIndicationCallback(App_GattClientIndicationCallback);
}

void App_RegisterLePsm
(
    uint16_t                    lePsm,
    l2caLeCbDataCallback_t      pCallback,
    l2caLeCbControlCallback_t   pCtrlCallback,
    uint16_t                    lePsmMtu      
)
{
    pfL2caLeCbDataCallback = pCallback;
    pfL2caLeCbControlCallback = pCtrlCallback;

    L2ca_RegisterLePsm(lePsm,
                       App_L2caLeDataCallback,
                       App_L2caLeControlCallback,
                       lePsmMtu);
}

void App_RegisterL2caControlCallback
(
    l2caControlCallback_t       pCallback    
)
{
    pfL2caLeCbControlCallback = pCallback;

    L2ca_RegisterControlCallback(App_L2caLeControlCallback);
}

void App_NvmErase
(
    uint32_t nvmStartAddress,
    uint32_t nvmSize
)
{
#if mAppUseNvm_d  

   (void)nvmSize;
    
    NV_FlashEraseSector(&gFlashConfig, nvmStartAddress, 
                        gcReservedFlashSizeForBondedDevicesData_c, gFlashLaunchCommand);
#endif    
}

void App_NvmWrite
(
    uint32_t nvmDestinationAddress,
    void*    pvRamSource,
    uint32_t cDataSize
)
{
#if mAppUseNvm_d  
    NV_FlashProgramUnaligned(&gFlashConfig, nvmDestinationAddress, cDataSize, pvRamSource, gFlashLaunchCommand);
#endif
}

void App_NvmRead
(
    uint32_t nvmSourceAddress,
    void*    pvRamDestination,
    uint32_t cDataSize
)
{
#if mAppUseNvm_d  
    NV_FlashRead(nvmSourceAddress, pvRamDestination, cDataSize);
#endif    
}
/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*****************************************************************************
* Handles all key events for this device.
* Interface assumptions: None
* Return value: None
*****************************************************************************/
static void App_KeyboardCallBack
  (
  uint8_t events  /*IN: Events from keyboard module  */
  )
{
#if gKBD_KeysCount_c > 0 
    BleApp_HandleKeys(events);
#endif
}

/*****************************************************************************
* Handles all messages received from the host task.
* Interface assumptions: None
* Return value: None
*****************************************************************************/
static void App_HandleHostMessageInput(appMsgFromHost_t* pMsg)
{
    switch ( pMsg->msgType ) 
    { 
        case gAppGapGenericMsg_c:
        {
            BleApp_GenericCallback(&pMsg->msgData.genericMsg);
            break;
        }
        case gAppGapAdvertisementMsg_c:
        {
            if (pfAdvCallback)
                pfAdvCallback(&pMsg->msgData.advMsg);
            break;
        }
        case gAppGapScanMsg_c:
        {
            if (pfScanCallback)
                pfScanCallback(&pMsg->msgData.scanMsg);
            break;
        }
        case gAppGapConnectionMsg_c:
        {
            if (pfConnCallback)
                pfConnCallback(pMsg->msgData.connMsg.deviceId, &pMsg->msgData.connMsg.connEvent);
            break;
        }
        case gAppGattServerMsg_c:
        {
            if (pfGattServerCallback)
                pfGattServerCallback(pMsg->msgData.gattServerMsg.deviceId, &pMsg->msgData.gattServerMsg.serverEvent);
            break;
        }
        case gAppGattClientProcedureMsg_c:
        {
            if (pfGattClientProcCallback)
                pfGattClientProcCallback(
                    pMsg->msgData.gattClientProcMsg.deviceId,
                    pMsg->msgData.gattClientProcMsg.procedureType,
                    pMsg->msgData.gattClientProcMsg.procedureResult,
                    pMsg->msgData.gattClientProcMsg.error);
            break;
        }
        case gAppGattClientNotificationMsg_c:
        {
            if (pfGattClientNotifCallback)
                pfGattClientNotifCallback(
                    pMsg->msgData.gattClientNotifIndMsg.deviceId,
                    pMsg->msgData.gattClientNotifIndMsg.characteristicValueHandle,
                    pMsg->msgData.gattClientNotifIndMsg.aValue,
                    pMsg->msgData.gattClientNotifIndMsg.valueLength);
            break;
        }
        case gAppGattClientIndicationMsg_c:
        {
            if (pfGattClientIndCallback)
                pfGattClientIndCallback(
                    pMsg->msgData.gattClientNotifIndMsg.deviceId,
                    pMsg->msgData.gattClientNotifIndMsg.characteristicValueHandle,
                    pMsg->msgData.gattClientNotifIndMsg.aValue,
                    pMsg->msgData.gattClientNotifIndMsg.valueLength);
            break;
        }
        case gAppL2caLeDataMsg_c:
        {
            if (pfL2caLeCbDataCallback)
                pfL2caLeCbDataCallback(
                    pMsg->msgData.l2caLeCbDataMsg.deviceId,
                    pMsg->msgData.l2caLeCbDataMsg.lePsm,                    
                    pMsg->msgData.l2caLeCbDataMsg.aPacket,
                    pMsg->msgData.l2caLeCbDataMsg.packetLength);
            break;
        }
        case gAppL2caLeControlMsg_c:
        {
            if (pfL2caLeCbControlCallback)
                pfL2caLeCbControlCallback(
                    pMsg->msgData.l2caLeCbControlMsg.messageType,
                    pMsg->msgData.l2caLeCbControlMsg.aMessage);
            break;
        }
        default:
        {
            break;
        }
    }   
}

static void App_GenericCallback (gapGenericEvent_t* pGenericEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;   
    
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gapGenericEvent_t));
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGapGenericMsg_c;
    FLib_MemCpy(&pMsgIn->msgData.genericMsg, pGenericEvent, sizeof(gapGenericEvent_t));

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;   
    uint8_t msgLen = GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gapConnectionEvent_t);
    
    if(pConnectionEvent->eventType == gConnEvtKeysReceived_c)
    {
        gapSmpKeys_t    *pKeys = pConnectionEvent->eventData.keysReceivedEvent.pKeys;

        /* Take into account alignment */
        msgLen = GetRelAddr(appMsgFromHost_t, msgData) + GetRelAddr(connectionMsg_t, connEvent) + 
                 GetRelAddr(gapConnectionEvent_t, eventData) + sizeof(gapKeysReceivedEvent_t) + sizeof(gapSmpKeys_t);
                 
        if (pKeys->aLtk != NULL)
        {
            msgLen += 2 * sizeof(uint8_t) + pKeys->cLtkSize + pKeys->cRandSize;
        }

        msgLen += (pKeys->aIrk != NULL) ? (gcSmpIrkSize_c + gcBleDeviceAddressSize_c) : 0;
        msgLen += (pKeys->aCsrk != NULL) ? gcSmpCsrkSize_c : 0;
    }

    pMsgIn = MSG_Alloc(msgLen);
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGapConnectionMsg_c;
    pMsgIn->msgData.connMsg.deviceId = peerDeviceId;

    if(pConnectionEvent->eventType == gConnEvtKeysReceived_c)
    {
        gapSmpKeys_t    *pKeys = pConnectionEvent->eventData.keysReceivedEvent.pKeys;
        uint8_t         *pCursor = (uint8_t*)&pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys;

        pMsgIn->msgData.connMsg.connEvent.eventType = gConnEvtKeysReceived_c;
        pCursor += sizeof(void*);
        pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys = (gapSmpKeys_t* )pCursor;
        
        /* Copy SMP Keys structure */
        FLib_MemCpy(pCursor, pConnectionEvent->eventData.keysReceivedEvent.pKeys, sizeof(gapSmpKeys_t));
        pCursor += sizeof(gapSmpKeys_t);
        
        if (pKeys->aLtk != NULL)
        {
            /* Copy LTK */
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->cLtkSize = pKeys->cLtkSize;
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aLtk = pCursor;
            FLib_MemCpy(pCursor, pKeys->aLtk, pKeys->cLtkSize);
            pCursor += pKeys->cLtkSize;

            /* Copy RAND */
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->cRandSize = pKeys->cRandSize;
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aRand = pCursor;
            FLib_MemCpy(pCursor, pKeys->aRand, pKeys->cRandSize);
            pCursor += pKeys->cRandSize;
        }
        else
          

        if (pKeys->aIrk != NULL)
        {
            /* Copy IRK */
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aIrk = pCursor;
            FLib_MemCpy(pCursor, pKeys->aIrk, gcSmpIrkSize_c);
            pCursor += gcSmpIrkSize_c;

            /* Copy Address*/
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->addressType = pKeys->addressType;
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aAddress = pCursor;
            FLib_MemCpy(pCursor, pKeys->aAddress, gcBleDeviceAddressSize_c);
            pCursor += gcBleDeviceAddressSize_c;
        }

        if (pKeys->aCsrk != NULL)
        {
            /* Copy CSRK */
            pMsgIn->msgData.connMsg.connEvent.eventData.keysReceivedEvent.pKeys->aCsrk = pCursor;
            FLib_MemCpy(pCursor, pKeys->aCsrk, gcSmpCsrkSize_c);
        }
    }
    else
    {
        FLib_MemCpy(&pMsgIn->msgData.connMsg.connEvent, pConnectionEvent, sizeof(gapConnectionEvent_t));
    }

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;   
    
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gapAdvertisingEvent_t));
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGapAdvertisementMsg_c;
    pMsgIn->msgData.advMsg.eventType = pAdvertisingEvent->eventType;
    pMsgIn->msgData.advMsg.eventData = pAdvertisingEvent->eventData;

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_ScanningCallback (gapScanningEvent_t* pScanningEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;  
    
    uint8_t msgLen = GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gapScanningEvent_t);
    
    if (pScanningEvent->eventType == gDeviceScanned_c)
    {
        msgLen += pScanningEvent->eventData.scannedDevice.dataLength;
    }
    
    pMsgIn = MSG_Alloc(msgLen);
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGapScanMsg_c;
    pMsgIn->msgData.scanMsg.eventType = pScanningEvent->eventType;
    
    if (pScanningEvent->eventType == gScanCommandFailed_c)
    {
        pMsgIn->msgData.scanMsg.eventData.failReason = pScanningEvent->eventData.failReason;
    }
    
    if (pScanningEvent->eventType == gDeviceScanned_c)
    {
        FLib_MemCpy(&pMsgIn->msgData.scanMsg.eventData.scannedDevice, 
                    &pScanningEvent->eventData.scannedDevice, 
                    sizeof(gapScanningEvent_t));
        
        /* Copy data after the gapScanningEvent_t structure and update the data pointer*/
        pMsgIn->msgData.scanMsg.eventData.scannedDevice.data = (uint8_t*)&pMsgIn->msgData + sizeof(gapScanningEvent_t);
        FLib_MemCpy(pMsgIn->msgData.scanMsg.eventData.scannedDevice.data, 
                    pScanningEvent->eventData.scannedDevice.data, 
                    pScanningEvent->eventData.scannedDevice.dataLength);
    }

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_GattServerCallback
(
    deviceId_t          deviceId,
    gattServerEvent_t*  pServerEvent)
{
    appMsgFromHost_t *pMsgIn = NULL;   
    uint8_t msgLen = GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gattServerMsg_t);
    
    if (pServerEvent->eventType == gEvtAttributeWritten_c ||
        pServerEvent->eventType == gEvtAttributeWrittenWithoutResponse_c)
    {
        msgLen += pServerEvent->eventData.attributeWrittenEvent.cValueLength;
    }

    pMsgIn = MSG_Alloc(msgLen);
          
    if (!pMsgIn)
      return;
    
    pMsgIn->msgType = gAppGattServerMsg_c;
    pMsgIn->msgData.gattServerMsg.deviceId = deviceId;
    FLib_MemCpy(&pMsgIn->msgData.gattServerMsg.serverEvent, pServerEvent, sizeof(gattServerEvent_t));

    if ((pMsgIn->msgData.gattServerMsg.serverEvent.eventType == gEvtAttributeWritten_c) ||
        (pMsgIn->msgData.gattServerMsg.serverEvent.eventType == gEvtAttributeWrittenWithoutResponse_c))
    {
        /* Copy value after the gattServerEvent_t structure and update the aValue pointer*/
        pMsgIn->msgData.gattServerMsg.serverEvent.eventData.attributeWrittenEvent.aValue = 
          (uint8_t *)&pMsgIn->msgData.gattServerMsg.serverEvent.eventData.attributeWrittenEvent.aValue + sizeof(uint8_t*);
        FLib_MemCpy(pMsgIn->msgData.gattServerMsg.serverEvent.eventData.attributeWrittenEvent.aValue,
                    pServerEvent->eventData.attributeWrittenEvent.aValue,
                    pServerEvent->eventData.attributeWrittenEvent.cValueLength);

    }
    
    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);  
}

static void App_GattClientProcedureCallback
(
    deviceId_t              deviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error)
{
    appMsgFromHost_t *pMsgIn = NULL;

    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gattClientProcMsg_t));

    if (!pMsgIn)
      return;

    pMsgIn->msgType = gAppGattClientProcedureMsg_c;
    pMsgIn->msgData.gattClientProcMsg.deviceId = deviceId;
    pMsgIn->msgData.gattClientProcMsg.procedureType = procedureType;
    pMsgIn->msgData.gattClientProcMsg.error = error;
    pMsgIn->msgData.gattClientProcMsg.procedureResult = procedureResult;

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);
}

static void App_GattClientNotificationCallback
(
    deviceId_t      deviceId,
    uint16_t        characteristicValueHandle,
    uint8_t*        aValue,
    uint16_t        valueLength
)
{
    appMsgFromHost_t *pMsgIn = NULL;

    /* Allocate a buffer with enough space to store also the notified value*/
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gattClientNotifIndMsg_t)
                        + valueLength);

    if (!pMsgIn)
      return;

    pMsgIn->msgType = gAppGattClientNotificationMsg_c;
    pMsgIn->msgData.gattClientNotifIndMsg.deviceId = deviceId;
    pMsgIn->msgData.gattClientNotifIndMsg.characteristicValueHandle = characteristicValueHandle;
    pMsgIn->msgData.gattClientNotifIndMsg.valueLength = valueLength;

    /* Copy value after the gattClientNotifIndMsg_t structure and update the aValue pointer*/
    pMsgIn->msgData.gattClientNotifIndMsg.aValue = (uint8_t*)&pMsgIn->msgData + sizeof(gattClientNotifIndMsg_t);
    FLib_MemCpy(pMsgIn->msgData.gattClientNotifIndMsg.aValue, aValue, valueLength);

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);
}

static void App_GattClientIndicationCallback
(
    deviceId_t      deviceId,
    uint16_t        characteristicValueHandle,
    uint8_t*        aValue,
    uint16_t        valueLength
)
{
    appMsgFromHost_t *pMsgIn = NULL;

    /* Allocate a buffer with enough space to store also the notified value*/
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(gattClientNotifIndMsg_t)
                        + valueLength);

    if (!pMsgIn)
      return;

    pMsgIn->msgType = gAppGattClientIndicationMsg_c;
    pMsgIn->msgData.gattClientNotifIndMsg.deviceId = deviceId;
    pMsgIn->msgData.gattClientNotifIndMsg.characteristicValueHandle = characteristicValueHandle;
    pMsgIn->msgData.gattClientNotifIndMsg.valueLength = valueLength;

    /* Copy value after the gattClientIndIndMsg_t structure and update the aValue pointer*/
    pMsgIn->msgData.gattClientNotifIndMsg.aValue = (uint8_t*)&pMsgIn->msgData + sizeof(gattClientNotifIndMsg_t);
    FLib_MemCpy(pMsgIn->msgData.gattClientNotifIndMsg.aValue, aValue, valueLength);

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);
}

static void App_L2caLeDataCallback
(
    deviceId_t deviceId,
    uint16_t   lePsm,
    uint8_t* pPacket,
    uint16_t packetLength
)
{
    appMsgFromHost_t *pMsgIn = NULL;

    /* Allocate a buffer with enough space to store the packet */
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(l2caLeCbDataMsg_t) 
                        + packetLength);

    if (!pMsgIn)
    {
        return;
    }

    pMsgIn->msgType = gAppL2caLeDataMsg_c;
    pMsgIn->msgData.l2caLeCbDataMsg.deviceId = deviceId;
    pMsgIn->msgData.l2caLeCbDataMsg.lePsm = lePsm;
    pMsgIn->msgData.l2caLeCbDataMsg.packetLength = packetLength;

    FLib_MemCpy(pMsgIn->msgData.l2caLeCbDataMsg.aPacket, pPacket, packetLength);

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);
}

static void App_L2caLeControlCallback
(
    l2capControlMessageType_t  messageType,
    void* pMessage
)
{
    appMsgFromHost_t *pMsgIn = NULL;
    uint8_t messageLength = 0;

    switch (messageType) {
        case gL2ca_LePsmConnectRequest_c:
        {
            messageLength = sizeof(l2caLeCbConnectionRequest_t);
            break;
        }
        case gL2ca_LePsmConnectionComplete_c:
        {
            messageLength = sizeof(l2caLeCbConnectionComplete_t);
            break;
        }
        case gL2ca_LePsmDisconnectNotification_c:
        {
            messageLength = sizeof(l2caLeCbDisconnection_t);
            break;
        }
        case gL2ca_ConnectionParameterUpdateRequest_c:
        {
            messageLength = sizeof(l2caLeCbConnectionParameterUpdateRequest_t);
            break;
        }
        case gL2ca_ConnectionParameterUpdateComplete_c:
        {
            messageLength = sizeof(l2caLeCbConnectionParameterUpdateComplete_t);
            break;
        }
        case gL2ca_NoPeerCredits_c:
        {
            messageLength = sizeof(l2caLeCbNoPeerCredits_t);
            break;
        }
        case gL2ca_LocalCreditsNotification_c:
        {
            messageLength = sizeof(l2caLeCbLocalCreditsNotification_t);
            break;
        }
        default:
            return;
    }


    /* Allocate a buffer with enough space to store the biggest packet */
    pMsgIn = MSG_Alloc(GetRelAddr(appMsgFromHost_t, msgData) + sizeof(l2caLeCbConnectionParameterUpdateRequest_t));

    if (!pMsgIn)
    {
        return;
    }

    pMsgIn->msgType = gAppL2caLeControlMsg_c;
    pMsgIn->msgData.l2caLeCbControlMsg.messageType = messageType;
    
    FLib_MemCpy(pMsgIn->msgData.l2caLeCbControlMsg.aMessage, pMessage, messageLength);

    /* Put message in the Host Stack to App queue */
    MSG_Queue(&mHostAppInputQueue, pMsgIn);

    /* Signal application */
    OSA_EventSet(&mAppEvent, gAppEvtMsgFromHostStack_c);
}

/* Called by BLE when a connect is received */
static void BLE_SignalFromISRCallback(void)
{
#if (cPWR_UsePowerDownMode)  
    PWR_DisallowDeviceToSleep();  
#endif    
}