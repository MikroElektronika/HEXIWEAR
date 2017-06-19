/**
 *    @file appMode_service.h
 */

#ifndef _APPMODE_SERVICE_H_
#define _APPMODE_SERVICE_H_

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
bleResult_t Apps_Start (void);

/**
 *    Stop service.
 *
 *    @return      gBleSuccess_c
 */
bleResult_t Apps_Stop (void);

/**
 *    Subscribe service.
 *
 *    @param    clientDeviceId   Client Device ID.
 *
 *    @return                    gBleSuccess_c
 */
bleResult_t Apps_Subscribe(deviceId_t clientDeviceId);

/**
 *    Unsubscribe device.
 *
 *    @return      gBleSuccess_c
 */
bleResult_t Apps_Unsubscribe(void);

/**
 *    Record characteristic value.
 *
 *    @param    data   Data to be recorded.
 *
 *    @return          gBleSuccess_c or error
 */
bleResult_t Apps_RecordState(uint8_t * data);

#endif /*_APPMODE_SERVICE */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

