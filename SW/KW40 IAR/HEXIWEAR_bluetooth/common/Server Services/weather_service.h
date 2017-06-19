/**
 *    @file weather_service.h
 */

#ifndef _WEATHER_SERVICE_H_
#define _WEATHER_SERVICE_H_

#include "host_mcu_interface.h"

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

/**
 *    Start service.
 *
 *    @return      gBleSuccess_c
 */
bleResult_t Wes_Start (void);

/**
 *    Stop service.
 *
 *    @return      gBleSuccess_c
 */
bleResult_t Wes_Stop (void);

/**
 *    Subscribe service.
 *
 *    @param    clientDeviceId   Client Device ID.
 *
 *    @return                    gBleSuccess_c
 */
bleResult_t Wes_Subscribe(deviceId_t clientDeviceId);

/**
 *    Unsubscribe device.
 *
 *    @return      gBleSuccess_c
 */
bleResult_t Wes_Unsubscribe(void);

/**
 *    Record characteristic value.
 *
 *    @param    type   Type of measurement.
 *    @param    data   Data to be recorded.
 *
 *    @return          gBleSuccess_c or error
 */
bleResult_t Wes_RecordMeasurement(hostInterface_packetType_t type, uint8_t * data);

#endif /*_WEATHER_SERVICE */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

