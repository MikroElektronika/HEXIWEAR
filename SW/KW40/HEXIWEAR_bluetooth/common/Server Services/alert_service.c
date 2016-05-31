/**
 *    @file alert_service.c
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
#include "FunctionLib.h"
#include "fsl_lpuart_driver.h"

#include "alert_service.h"
#include "common_service.h"


/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! Alert Service - Subscribed Client*/
static deviceId_t mAls_SubscribedClientId;

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

bleResult_t Als_Start (void)
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

bleResult_t Als_Stop(void)
{
    mAls_SubscribedClientId = gInvalidDeviceId_c;
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

bleResult_t Als_Subscribe(deviceId_t clientDeviceId)
{
    mAls_SubscribedClientId = clientDeviceId;
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

bleResult_t Als_Unsubscribe(void)
{
    mAls_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Record characteristic value.
 *
 *    @param    data   Data to be recorded.
 *
 *    @return          gBleSuccess_c or error
 */

bleResult_t Als_RecordOutAlert(uint8_t * data)
{
    bleResult_t result;
    
    result = CommonService_RecordCharValue(mAls_SubscribedClientId, service_alert, gBleCustom_AlertOutUUID_d,  data, gBleCustom_AlertOutLength_d);
    
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Send received data to host MCU.
 *
 *    @param    data   Received data.
 *
 *    @return          gBleSuccess_c or error
 */

bleResult_t Als_HandleInAlert(uint8_t * data)
{
    static hostInterface_packet_t tmpPacket;
    
    tmpPacket.type = packetType_alertIn;
    tmpPacket.length = gBleCustom_AlertInLength_d;
    tmpPacket.data[gBleCustom_AlertInLength_d] = gHostInterface_trailerByte;
    
    FLib_MemCpy(tmpPacket.data, data, gBleCustom_AlertInLength_d);
    
    return (bleResult_t)HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&tmpPacket, true);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
