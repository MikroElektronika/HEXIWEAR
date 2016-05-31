/**
 *    @file motion_service.h
 */

#ifndef _MOTION_SERVICE_H_
#define _MOTION_SERVICE_H_

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
bleResult_t Mos_Start (void);

/**
 *    Stop service.
 *
 *    @return      gBleSuccess_c
 */
bleResult_t Mos_Stop (void);

/**
 *    Subscribe service.
 *
 *    @param    clientDeviceId   Client Device ID.
 *
 *    @return                    gBleSuccess_c
 */
bleResult_t Mos_Subscribe(deviceId_t clientDeviceId);

/**
 *    Unsubscribe device.
 *
 *    @return      gBleSuccess_c
 */
bleResult_t Mos_Unsubscribe(void);

/**
 *    Record characteristic value.
 *
 *    @param    type   Type of measurement.
 *    @param    data   Data to be recorded.
 *
 *    @return          gBleSuccess_c or error
 */
bleResult_t Mos_RecordMeasurement(hostInterface_packetType_t type, uint8_t * data);

#endif /*_MOTION_SERVICE */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

