/**
 *    @file weather_service.c
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

#include "weather_service.h"
#include "common_service.h"
#include "host_mcu_interface.h"

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! Weather Service - Subscribed Client*/
static deviceId_t mWes_SubscribedClientId;

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

bleResult_t Wes_Start(void)
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

bleResult_t Wes_Stop(void)
{
    mWes_SubscribedClientId = gInvalidDeviceId_c;
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

bleResult_t Wes_Subscribe(deviceId_t clientDeviceId)
{
    mWes_SubscribedClientId = clientDeviceId;
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

bleResult_t Wes_Unsubscribe(void)
{
    mWes_SubscribedClientId = gInvalidDeviceId_c;
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

bleResult_t Wes_RecordMeasurement(hostInterface_packetType_t type, uint8_t * data)
{
    bleResult_t result;
    
    uint16_t charUuid16;
    uint8_t  length;
    
    switch(type)
    {
        case packetType_ambiLight:
        {
            charUuid16 = gBleCustom_AmbiLightUUID_d;
            length = gBleCustom_AmbiLightLength_d;
        }
        break;
        
        case packetType_temperature:
        {
            charUuid16 = gBleCustom_TemperatureUUID_d;
            length = gBleCustom_TemperatureLength_d;
        }
        break;
        
        case packetType_humidity:
        {   
            charUuid16 = gBleCustom_HumidityUUID_d;
            length = gBleCustom_HumidityLength_d;
        }
        break;
        
        case packetType_pressure:
        {
            charUuid16 = gBleCustom_PressureUUID_d;
            length = gBleCustom_PressureLength_d;
        }
        break;
        
        default :
        {
            ;
        }
    }
    
    result = CommonService_RecordCharValue(mWes_SubscribedClientId, service_weather, charUuid16,  data, length);
    
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
