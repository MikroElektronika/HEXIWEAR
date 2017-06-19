/**
 *    @file alert_service.h
 */

#ifndef _ALERT_SERVICE_H_
#define _ALERT_SERVICE_H_

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
bleResult_t Als_Start (void);

/**
 *    Stop service.
 *
 *    @return      gBleSuccess_c
 */
bleResult_t Als_Stop (void);

/**
 *    Subscribe service.
 *
 *    @param    clientDeviceId   Client Device ID.
 *
 *    @return                    gBleSuccess_c
 */
bleResult_t Als_Subscribe(deviceId_t clientDeviceId);

/**
 *    Unsubscribe device.
 *
 *    @return      gBleSuccess_c
 */
bleResult_t Als_Unsubscribe(void);

/**
 *    Record characteristic value.
 *
 *    @param    data   Data to be recorded.
 *
 *    @return          gBleSuccess_c or error
 */
bleResult_t Als_RecordOutAlert(uint8_t *data);

/**
 *    Send received data to host MCU.
 *
 *    @param    data   Received data.
 *
 *    @return          gBleSuccess_c or error
 */
bleResult_t Als_HandleInAlert(uint8_t * data);

#endif /*_ALERT_SERVICE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

