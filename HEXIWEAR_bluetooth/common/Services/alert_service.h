
#ifndef _ALERT_SERVICE_H_
#define _ALERT_SERVICE_H_

#include "host_mcu_interface.h"

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
bleResult_t Als_Subscribe(deviceId_t clientDeviceId);
bleResult_t Als_Unsubscribe(void);
bleResult_t Als_Stop (void);
bleResult_t Als_Start (void);
bleResult_t Als_RecordOutAlert(uint8_t *data);
bleResult_t Als_HandleInAlert(uint8_t * data);

#endif /*_ALERT_SERVICE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

