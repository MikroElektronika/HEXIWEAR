
#ifndef _WEATHER_SERVICE_H_
#define _WEATHER_SERVICE_H_

#include "host_mcu_interface.h"

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
bleResult_t Wes_Subscribe(deviceId_t clientDeviceId);
bleResult_t Wes_Unsubscribe(void);
bleResult_t Wes_Stop (void);
bleResult_t Wes_Start (void);
bleResult_t Wes_RecordMeasurement(hostInterface_packetType_t type, uint8_t * data);

#endif /*_WEATHER_SERVICE */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

