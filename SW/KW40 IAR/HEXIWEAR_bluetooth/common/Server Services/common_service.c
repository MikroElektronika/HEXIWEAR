/**
 *    @file common_service.c
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
#include "fsl_os_abstraction.h"

#include "common_service.h"

/************************************************************************************
*************************************************************************************
* Private type Definitions
*************************************************************************************
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/


/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

static void CommonService_SendNotifications(deviceId_t deviceId, uint16_t handle);

/************************************************************************************
*************************************************************************************
* Public Functions definitions
*************************************************************************************
********************************************************************************** */

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Record characteristic value.
 *
 *    @param    deviceId        Device ID.
 *    @param    serviceHandle   Service handle.
 *    @param    charUuid16      Characteristics UUID16.
 *    @param    data            Data to be written.
 *    @param    size            Size of data.
 *
 *    @return                   gBleSuccess_c or error.
 */

bleResult_t CommonService_RecordCharValue(deviceId_t deviceId, uint16_t serviceHandle, 
                                          uint16_t charUuid16, uint8_t *data, uint8_t size)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t uuid  = Uuid16(charUuid16);

    
    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(serviceHandle, gBleUuidType16_c, &uuid, &handle);
    if (result != gBleSuccess_c)
    {
        return result;
    }
    
    /* Update characteristic value and send notification */
    result = GattDb_WriteAttribute(handle, size, data);
    if (result != gBleSuccess_c)
    {
        return result;
    }

    CommonService_SendNotifications(deviceId, handle);

    return gBleSuccess_c;
}


/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *    Sends a notification to a peer GATT Client using the Characteristic Value from the GATT Database.
 *
 *    @param   deviceId   Device ID.
 *    @param   handle     Handle of the Value of the Characteristic to be notified.
 */

static void CommonService_SendNotifications(deviceId_t deviceId, uint16_t handle)
{
    uint16_t  handleCccd;
    bool_t isNotifActive;
    
    
    /* Get handle of CCCD */
    if (GattDb_FindCccdHandleForCharValueHandle(handle, &handleCccd) != gBleSuccess_c)
        return;
    
    if (deviceId == gInvalidDeviceId_c)
      return;

    if ( 
         (gBleSuccess_c == Gap_CheckNotificationStatus(deviceId, handleCccd, &isNotifActive)) &&
         (TRUE == isNotifActive)
       )
    {
        OSA_EnterCritical(kCriticalDisableInt);
        GattServer_SendNotification(deviceId, handle);
        OSA_ExitCritical(kCriticalDisableInt);
    }
    
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////