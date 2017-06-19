/**
 *    @file motion_service.c
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

#include "motion_service.h"
#include "common_service.h"

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! Motion Service - Subscribed Client*/
static deviceId_t mMos_SubscribedClientId;

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

bleResult_t Mos_Start (void)
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

bleResult_t Mos_Stop(void)
{
    mMos_SubscribedClientId = gInvalidDeviceId_c;
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

bleResult_t Mos_Subscribe(deviceId_t clientDeviceId)
{
    mMos_SubscribedClientId = clientDeviceId;
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

bleResult_t Mos_Unsubscribe(void)
{
    mMos_SubscribedClientId = gInvalidDeviceId_c;
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

bleResult_t Mos_RecordMeasurement(hostInterface_packetType_t type, uint8_t * data)
{
    bleResult_t result;
    uint16_t charUuid16;
    uint8_t  length;
    
    switch(type)
    {
        case packetType_accel:
        {
            charUuid16 = gBleCustom_AccelUUID_d;
            length = gBleCustom_AccelLength_d;
        }
        break;
        
        case packetType_gyro:
        {
            charUuid16 = gBleCustom_GyroUUID_d;
            length = gBleCustom_GyroLength_d;
        }
        break;
        
        case packetType_magnet:
        {
            charUuid16 = gBleCustom_MagnetUUID_d;
            length = gBleCustom_MagnetLength_d;
        }
        break;
        
        default :
        {
            ;
        }
    }
    result = CommonService_RecordCharValue(mMos_SubscribedClientId, service_motion, charUuid16,  data, length);
    
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
