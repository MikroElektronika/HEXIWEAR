/**
 *    @file client_ancs.h
 */

#ifndef _CLIENT_ANCS_H_
#define _CLIENT_ANCS_H_

#include "gatt_client_interface.h"


/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/** Service Configuration */
typedef struct ancsConfig_tag
{
    uint16_t    serviceHandle;
} ancsConfig_t;

/** Client Configuration */
typedef struct anccConfig_tag
{
    uint16_t    hService;
    uint16_t    hNotifSource;
    uint16_t    hNotifSourceCccd; 
} anccConfig_t;

/** Category of iOS notification */
typedef enum 
{
    ancCategoryId_other           = 0,
    ancCategoryId_incomingCall    = 1,
    ancCategoryId_missedCall      = 2,
    ancCategoryId_voiceMail       = 3,
    ancCategoryId_social          = 4,
    ancCategoryId_schedule        = 5,
    ancCategoryId_email           = 6,
    ancCategoryId_news            = 7,
    ancCategoryId_healthFitness   = 8,
    ancCategoryId_businessFinance = 9,
    ancCategoryId_location        = 10,
    ancCategoryId_entertainment   = 11  
} ancCategoryId_t;

/** Notification action */
typedef enum 
{
    ancEventId_NontifAdded    = 0,
    ancEventId_NontifModified = 1,
    ancEventId_NontifRemoved  = 2
} ancEventId_t;

/** Application event */
typedef enum appEvent_tag
{
    mAppEvt_PeerConnected_c,
    mAppEvt_PairingComplete_c,
    mAppEvt_EncryptionChg_c,
    mAppEvt_GattProcComplete_c,
    mAppEvt_GattProcError_c
}
appEvent_t;

/** State machine values */
typedef enum appState_tag
{
    mAppIdle_c,
    mAppExchangeMtu_c,
    mAppPrimaryServiceDisc_c,
    mAppCharServiceDisc_c,
    mAppDescriptorSetup_c,
    mAppRunning_c,
}
appState_t;

typedef struct appCustomInfo_tag
{
    anccConfig_t     ancClientConfig;
    // Add persistent information here
}
appCustomInfo_t;

/** Remote peer info */
typedef struct appPeerInfo_tag
{
    deviceId_t      deviceId;
    appCustomInfo_t customInfo;
    bool_t          isBonded;
    appState_t      appState;
}
appPeerInfo_t;

/************************************************************************************
*************************************************************************************
* Extern
*************************************************************************************
************************************************************************************/

extern appPeerInfo_t clientAncsPeerInfo;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

/**
 *    Handles GATT client callback from host stack.
 *
 *    @param   serverDeviceId    GATT Server device ID.
 *    @param   procedureType     Procedure type.
 *    @param   procedureResult   Procedure result.
 *    @param   error             Callback result.
 */
void ClientAncs_GattCallback
(
    deviceId_t              serverDeviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
);

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
);

/**
 *    Handler of client ancs state machine.
 *
 *    @param   peerDeviceId               Peer device ID.
 *    @param   event                      Event.
 */
void ClientAncs_StateMachineHandler
(
    deviceId_t peerDeviceId,
    uint8_t event
);

/**
 *    Service discovery error handler.
 */
void ClientAncs_ServiceDiscoveryErrorHandler(void);

#endif /*_CLIENT_ANCS_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

