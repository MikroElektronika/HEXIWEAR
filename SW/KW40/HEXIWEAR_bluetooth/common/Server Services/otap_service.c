/*! *********************************************************************************
 * \addtogroup BLE OTAP Custom Profile
 * @{
 ********************************************************************************** */
/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * \file otap_service.c
 * This file contains the source for the BLE OTAP Service/Profile
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
#include "FunctionLib.h"
#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_handles.h" // Include this file for the 128 bit characteristic UUIDs. Do not access the handles directlty!
#include "gatt_server_interface.h"
#include "gap_interface.h"
#include "otap_interface.h"
/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! OTAP Client Service - Subscribed Client*/
static deviceId_t mOtapCS_SubscribedClientId;

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/
static bleResult_t OtapCS_SendControlPointIndication (uint16_t handle);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
bleResult_t OtapCS_Start (otapClientConfig_t *pServiceConfig)
{
    mOtapCS_SubscribedClientId = gInvalidDeviceId_c;
    
    return gBleSuccess_c;
}

bleResult_t OtapCS_Stop (otapClientConfig_t *pServiceConfig)
{
    return OtapCS_Unsubscribe();
}

bleResult_t OtapCS_Subscribe(deviceId_t deviceId)
{
    mOtapCS_SubscribedClientId = deviceId;

    return gBleSuccess_c;
}

bleResult_t OtapCS_Unsubscribe()
{
	mOtapCS_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

bleResult_t OtapCS_SendCommandToOtapServer (uint16_t serviceHandle,
                                            void* pCommand,
                                            uint16_t cmdLength)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t* pUuid = (bleUuid_t*)&uuid_char_otap_control_point;
    
    /* Get handle of OTAP Control Point characteristic */
    result = GattDb_FindCharValueHandleInService(serviceHandle,
                                                 gBleUuidType128_c, pUuid, &handle);
    
    if (result != gBleSuccess_c)
        return result;
    
    /* Write characteristic value */
    result = GattDb_WriteAttribute(handle,
                                   cmdLength,
                                   (uint8_t*)pCommand);

    if (result != gBleSuccess_c)
        return result;
    
    /* Send Command to the OTAP Server via ATT Indication */
    return OtapCS_SendControlPointIndication (handle);
}


/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*!**********************************************************************************
* \brief        Sends an ATT Indications for the specified handle
*               of an OTAP Control Point characteristic.
*
* \param[in]    handle   Characteristic handle.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
static bleResult_t OtapCS_SendControlPointIndication (uint16_t handle)
{
    uint16_t    hCccd;
    bool_t      isIndicationActive;
    bleResult_t result;
    
    /* Get handle of CCCD */
    result = GattDb_FindCccdHandleForCharValueHandle (handle, &hCccd);
    
    if (result != gBleSuccess_c)
    {
        return result;
    }
    
    result = Gap_CheckIndicationStatus (mOtapCS_SubscribedClientId,
                                        hCccd,
                                        &isIndicationActive);
    
    if (result != gBleSuccess_c)
    {
        return result;
    }
    
    if (TRUE == isIndicationActive)
    {
        return GattServer_SendIndication (mOtapCS_SubscribedClientId,
                                          handle);
    }
    else
    {
        return gBleSuccess_c;
    }
}

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
