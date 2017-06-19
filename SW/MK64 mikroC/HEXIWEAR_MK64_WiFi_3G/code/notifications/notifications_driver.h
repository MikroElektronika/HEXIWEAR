// File: notifications_driver.h

// Declarations of main functionalities in the notifications module.

#ifndef _notifications_driver_h_
#define _notifications_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "OSA.h"
#include "notifications_types.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Sets the notifications' counter's value.
void Notification_SetUnreadCounter(
    notification_type_t notifType, uint8_t value );

// Gets the notifications' counter's value.
uint8_t Notification_GetUnreadCounter( notification_type_t notifType );

// Initialises the notification event.
notification_status_t Notification_Init();

// Waits for the notification event.
notification_status_t Notification_WaitForEvent(
    notification_type_t* notifType, uint32_t timeout );

// Sets the notification event.
notification_status_t Notification_SetEvent( notification_type_t notifType );

#endif