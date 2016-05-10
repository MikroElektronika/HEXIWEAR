
#ifndef _HEALTH_SERVICE_H_
#define _HEALTH_SERVICE_H_

#include "host_mcu_interface.h"

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
bleResult_t Hes_Subscribe(deviceId_t clientDeviceId);
bleResult_t Hes_Unsubscribe(void);
bleResult_t Hes_Stop (void);
bleResult_t Hes_Start (void);
bleResult_t Hes_RecordMeasurement(hostInterface_packetType_t type, uint8_t * data);

#endif /*_HEALTH_SERVICE */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

