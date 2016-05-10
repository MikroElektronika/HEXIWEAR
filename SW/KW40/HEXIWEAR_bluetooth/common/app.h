/*! *********************************************************************************
 * \defgroup Heart Rate Sensor
 * @{
 ********************************************************************************** */
/*!
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * \file app.h
 * This file is the interface file for the Heart Rate Sensor application
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

#ifndef _APP_H_
#define _APP_H_

#include "gap_interface.h"
     
/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/
     
typedef enum
{
    deviceState_watch           = 0,
    deviceState_otapStartedKW40 = 1,
    deviceState_otapStartedMK64 = 2,
    deviceState_otapCompleted   = 3,
    deviceState_otapFailed      = 4,
} deviceState_t;
    
typedef enum
{
    advMode_disable  = 0,
    advMode_enable   = 1,
} advMode_t;    
    
typedef enum
{
    linkState_disconnected = 0,
    linkState_connected    = 1,
} linkState_t;    
     

/*************************************************************************************
**************************************************************************************
* Public macros
**************************************************************************************
*************************************************************************************/
/* App Configuration */
#define gMaxServicesCount_d         1
#define gMaxServiceCharCount_d      3
#define gMaxCharDescriptorsCount_d  2

/* Connection Parameters */
#define gWatchConnMinInterval_c     32 /* 20 ms */
#define gWatchConnMaxInterval_c     40 /* 25 ms */
#define gOtapConnMinInterval_c      12 /* 7.5 ms */
#define gOtapConnMaxInterval_c      40 /* 25 ms */
#define gConnSlaveLatency_c         0
#define gConnTimeoutMultiplier_c    0x03E8

/*! Enable/disable bonding capability */
#define gBondingSupported_d    TRUE

/*! Enable/disable service security */
#define gUseServiceSecurity_d  TRUE


/* Profile Parameters */

#define gFastConnMinAdvInterval_c       (64)   /* 40 ms */
#define gFastConnMaxAdvInterval_c       (80)   /* 50 ms */

#define gReducedPowerMinAdvInterval_c   1600 /* 1 s */
#define gReducedPowerMaxAdvInterval_c   4000 /* 2.5 s */


#define gFastConnAdvTime_c              30 /* 30 s*/
#define gReducedPowerAdvTime_c          300 /* 300 s*/


#if gBondingSupported_d
#define gFastConnWhiteListAdvTime_c     10 /* s */
#else
#define gFastConnWhiteListAdvTime_c     0
#endif

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
extern gapAdvertisingData_t     gAppAdvertisingData;
extern gapScanResponseData_t    gAppScanRspData;
extern const gapAdStructure_t   advScanStruct_otap[];
extern const gapAdStructure_t   advScanStruct_watch[];
extern uint8_t currentImageVerMK64[];
extern uint8_t currentImageVerKW40[];

#if gBondingSupported_d
extern gapSmpKeys_t smpKeys;
extern gapPairingParameters_t gPairingParameters;
#endif

extern gapDeviceSecurityRequirements_t deviceSecurityRequirements;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void BleApp_Init(void);
void BleApp_Start(void);
void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent);
void BleApp_AdvDisable(void);
void BleApp_AdvEnable(void);
advMode_t BleApp_GetAdvMode(void);
linkState_t BleApp_GetLinkState(void);
void BleApp_LowPowerExitCallback(void);
bool_t BleApp_GetSleepFlag(void);

#ifdef __cplusplus
}
#endif 


#endif /* _APP_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
