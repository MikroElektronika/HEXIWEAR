/**
 * Project HEXIWEAR, 2015
 * alerts wrapper routines
 */

#ifndef HG_NOTIFICATIONS_EVENTS
#define HG_NOTIFICATIONS_EVENTS

#include "fsl_os_abstraction.h"

#include "notifications_types.h"

notification_status_t Notification_EventInit(void);
notification_status_t Notification_ArriveEventWait (notification_type_t type, uint32_t timeout);
notification_status_t Notification_ArriveEventClear(notification_type_t type);
notification_status_t Notification_ArriveEventSet(notification_type_t type);


#endif
