/**
 * Project HEXIWEAR, 2015
 * alerts wrapper routines
 */

#ifndef HG_NOTIFICATIONS
#define HG_NOTIFICATIONS

#include "fsl_os_abstraction.h"

#include "notifications_types.h"

void Notification_SetUnreadCounter( notification_type_t notifType, uint8_t value );
uint8_t Notification_GetUnreadCounter( notification_type_t notifType );

notification_status_t Notification_Init();
notification_status_t Notification_WaitForEvent( notification_type_t* notifType, uint32_t timeout );
notification_status_t Notification_SetEvent( notification_type_t notifType );

#endif
