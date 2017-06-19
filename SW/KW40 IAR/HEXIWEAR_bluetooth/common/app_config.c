/*! *********************************************************************************
* \addtogroup App Config
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
* \file app_config.c
* This file contains configuration data for the application and stack
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
#include "gap_interface.h"
#include "ble_constants.h"
#include "gatt_db_handles.h"
#include "app.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#define smpEdiv         0x1F99
#define mcEncryptionKeySize_c  16

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/* Scanning and Advertising Data */
static const uint8_t adData0[1] =  { (gapAdTypeFlags_t)(gLeGeneralDiscoverableMode_c | gBrEdrNotSupported_c) };
static const uint8_t adData1[] =   { 0xE0, 0x1C, 0x4B, 0x5E, 0x1E, 0xEB, 0xA1, 0x5C, 0xEE, 0xF4, 0x5E, 0xBA, 0x50, 0x55, 0xFF, 0x01};

const gapAdStructure_t advScanStruct_otap[3] = 
{
    {
        .length = NumberOfElements(adData0) + 1,
        .adType = gAdFlags_c,
        .aData = (void *)adData0
    },  
    {
        .length = NumberOfElements(adData1) + 1,
        .adType = gAdIncomplete128bitServiceList_c,
        .aData = (void *)adData1
    },
    {
        .length = 9,
        .adType = gAdShortenedLocalName_c,
        .aData = "HEXIOTAP"
    }  
};

const gapAdStructure_t advScanStruct_watch[2] = 
{
    {
        .length = NumberOfElements(adData0) + 1,
        .adType = gAdFlags_c,
        .aData = (void *)adData0
    },
    {
        .length = 9,
        .adType = gAdShortenedLocalName_c,
        .aData = "HEXIWEAR"
    }  
};

gapAdvertisingData_t gAppAdvertisingData;

gapScanResponseData_t gAppScanRspData = 
{
    0,
    NULL
};

/* SMP Data */
gapPairingParameters_t gPairingParameters = 
{
    gBondingSupported_d,
    gSecurityMode_1_Level_3_c,
    mcEncryptionKeySize_c,
    gIoDisplayOnly_c,
    TRUE,
     (gapSmpKeyFlags_t)(gIrk_c | gLtk_c), 
    gLtk_c
};

/* LTK */
static const uint8_t smpLtk[gcSmpMaxLtkSize_c] =
{
    0xD6, 0x93, 0xE8, 0xA4, 0x23, 0x55, 0x48, 0x99,
    0x1D, 0x77, 0x61, 0xE6, 0x63, 0x2B, 0x10, 0x8E
};

/* RAND*/
static const uint8_t smpRand[gcSmpMaxRandSize_c] =
{
    0x26, 0x1E, 0xF6, 0x09, 0x97, 0x2E, 0xAD, 0x7E
};

/* IRK */
static const uint8_t smpIrk[gcSmpIrkSize_c] =
{
    0x0A, 0x2D, 0xF4, 0x65, 0xE3, 0xBD, 0x7B, 0x49,
    0x1E, 0xB4, 0xC0, 0x95, 0x95, 0x13, 0x46, 0x73
};

/* CSRK */
static const uint8_t smpCsrk[gcSmpCsrkSize_c] =
{
    0x90, 0xD5, 0x06, 0x95, 0x92, 0xED, 0x91, 0xD7,
    0xA8, 0x9E, 0x2C, 0xDC, 0x4A, 0x93, 0x5B, 0xF9
};

gapSmpKeys_t smpKeys = 
{
    .cLtkSize = mcEncryptionKeySize_c,
    .aLtk = (void *)smpLtk,
    .aIrk = (void *)smpIrk,
    .aCsrk = (void *)smpCsrk,
    .aRand = (void *)smpRand,
    .cRandSize = gcSmpMaxRandSize_c,
    .addressType = gBleAddrTypePublic_c,
    .ediv = smpEdiv,
};

/* Device Security Requirements */
static const gapSecurityRequirements_t        masterSecurity = 
{ 
      /* securityModeLevel */               gSecurityMode_1_Level_3_c, 
      /* authorization */                   FALSE, 
      /* minimumEncryptionKeySize */        gDefaultEncryptionKeySize_d 
};

gapDeviceSecurityRequirements_t deviceSecurityRequirements = 
{
    .pMasterSecurityRequirements    = (void*)&masterSecurity,
    .cNumServices                   = 0,
    .aServiceSecurityRequirements   = NULL
};

