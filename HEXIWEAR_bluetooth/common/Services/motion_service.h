
#ifndef _MOTION_SERVICE_H_
#define _MOTION_SERVICE_H_

#include "host_mcu_interface.h"

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
bleResult_t Mos_Subscribe(deviceId_t clientDeviceId);
bleResult_t Mos_Unsubscribe(void);
bleResult_t Mos_Stop (void);
bleResult_t Mos_Start (void);
bleResult_t Mos_RecordMeasurement(hostInterface_packetType_t type, uint8_t * data);

#endif /*_MOTION_SERVICE */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

