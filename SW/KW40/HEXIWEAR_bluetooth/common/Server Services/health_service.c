/**
 *    @file health_service.c
 */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gatt_server_interface.h"
#include "gap_interface.h"
#include "battery_interface.h"
#include "gatt_uuid_decl_x.def"
#include "gatt_db_handles.h"

#include "health_service.h"
#include "common_service.h"


/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! Health Service - Subscribed Client*/
static deviceId_t mHes_SubscribedClientId;

/************************************************************************************
*************************************************************************************
* Public Functions definitions
*************************************************************************************
********************************************************************************** */

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Start service.
 *
 *    @return      gBleSuccess_c
 */

bleResult_t Hes_Start (void)
{
    return gBleSuccess_c;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Stop service.
 *
 *    @return      gBleSuccess_c
 */

bleResult_t Hes_Stop(void)
{
    mHes_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Subscribe service.
 *
 *    @param    clientDeviceId   Client Device ID.
 *
 *    @return                    gBleSuccess_c
 */

bleResult_t Hes_Subscribe(deviceId_t clientDeviceId)
{
    mHes_SubscribedClientId = clientDeviceId;
    return gBleSuccess_c;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Unsubscribe device.
 *
 *    @return      gBleSuccess_c
 */

bleResult_t Hes_Unsubscribe(void)
{
    mHes_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Record characteristic value.
 *
 *    @param    type   Type of measurement.
 *    @param    data   Data to be recorded.
 *
 *    @return          gBleSuccess_c or error
 */

bleResult_t Hes_RecordMeasurement(hostInterface_packetType_t type, uint8_t * data)
{
    bleResult_t result;
    uint16_t charUuid16;
    uint8_t  length;
    
    switch(type)
    {
        case packetType_heartRate:
        {
            charUuid16 = gBleCustom_HeartRateUUID_d;
            length = gBleCustom_HeartRateLength_d;
        }
        break;
        
        case packetType_steps:
        {
            charUuid16 = gBleCustom_StepsUUID_d;
            length = gBleCustom_StepsLength_d;
        }
        break;
        
        case packetType_calorie:
        {
            charUuid16 = gBleCustom_CalorieUUID_d;
            length = gBleCustom_CalorieLength_d;
        }
        break;
        
        default :
        {
            ;
        }
    }
    result = CommonService_RecordCharValue(mHes_SubscribedClientId, service_health, charUuid16,  data, length);
    
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
