// File: notifications_events.c

// Definitions of events functionalities in the notifications module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "notifications_driver.h"
#include "notifications_info.h"
#include "notifications_defs.h"

#include "error.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// private memory declarations
static const event_flags_t notification_eventSmsArriveMask  = 1 << 1;
static const event_flags_t notification_eventMailArriveMask = 1 << 2;
static const event_flags_t notification_eventCallArriveMask = 1 << 3;

static event_t notification_event;

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////
 
// Initialises the notification event.
notification_status_t Notification_EventInit()
{
    if( OSA_EventCreate( &notification_event, kEventAutoClear )
        != kStatus_OSA_Success )
    {
        return NOTIF_STATUS_ERROR;
    }

    return NOTIF_STATUS_SUCCESS;
}

// Waits for the notification event.
notification_status_t Notification_ArriveEventWait(
    notification_type_t type, uint32_t timeout )
{
    event_flags_t setFlags;
    if( OSA_EventWait(
        &notification_event, ( event_flags_t )type, false, timeout, &setFlags )
        != kStatus_OSA_Success )
    {
        return NOTIF_STATUS_ERROR;
    }

    return NOTIF_STATUS_SUCCESS;
}

// Clears the notification event.
notification_status_t Notification_ArriveEventClear( notification_type_t type )
{
    if( OSA_EventClear( &notification_event, ( event_flags_t )type )
        != kStatus_OSA_Success )
    {
        return NOTIF_STATUS_ERROR;
    }

    return NOTIF_STATUS_SUCCESS;
}

// Sets the notification event.
notification_status_t Notification_ArriveEventSet( notification_type_t type )
{
    if( OSA_EventSet( &notification_event, ( event_flags_t )type )
        != kStatus_OSA_Success )
    {
        return NOTIF_STATUS_ERROR;
    }

    return NOTIF_STATUS_SUCCESS;
}