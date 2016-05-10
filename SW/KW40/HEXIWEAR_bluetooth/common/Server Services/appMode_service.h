
#ifndef _APPMODE_SERVICE_H_
#define _APPMODE_SERVICE_H_

#include "host_mcu_interface.h"

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
bleResult_t Apps_Subscribe(deviceId_t clientDeviceId);
bleResult_t Apps_Unsubscribe(void);
bleResult_t Apps_Stop (void);
bleResult_t Apps_Start (void);
bleResult_t Apps_RecordState(uint8_t * data);

#endif /*_APPMODE_SERVICE */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

