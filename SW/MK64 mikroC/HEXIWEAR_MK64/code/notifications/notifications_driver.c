// File: notifications_driver.c

// Definitions of main functionalities in the notifications module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "notifications.h"

#include "gui_types.h"

#include "error.h"
#include "string.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static event_t notification_event;
static event_flags_t notification_eventFlag_call  = 1 << 0;
static event_flags_t notification_eventFlag_email = 1 << 1;
static event_flags_t notification_eventFlag_sms   = 1 << 2;
static uint8_t notification_sms_unread   = 0;
static uint8_t notification_email_unread = 0;
static uint8_t notification_call_unread  = 0;

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the notification event.
notification_status_t Notification_Init()
{
    if( OSA_EventCreate( &notification_event, kEventAutoClear )
        == kStatus_OSA_Success )
    {
        return NOTIF_STATUS_SUCCESS;
    }
    else
    {
        return NOTIF_STATUS_ERROR;
    }
}

// Waits for the notification event.
notification_status_t Notification_WaitForEvent(
    notification_type_t* notifType, uint32_t timeout )
{
    osa_status_t status;
    event_flags_t setFlags;

    status = OSA_EventWait(
                            &notification_event,
                            notification_eventFlag_call |
                            notification_eventFlag_email |
                            notification_eventFlag_sms,
                            false,
                            timeout,
                            &setFlags
                          );

    if( status != kStatus_OSA_Success )
    {
        return NOTIF_STATUS_ERROR;
    }
    else
    {
        if( ( setFlags & notification_eventFlag_call ) != 0 )
        {
            *notifType = NOTIF_TYPE_CALL;
        }
        else if ( ( setFlags & notification_eventFlag_email ) != 0 )
        {
            *notifType = NOTIF_TYPE_MAIL;
        }
        else if ( ( setFlags & notification_eventFlag_sms ) != 0 )
        {
            *notifType = NOTIF_TYPE_SMS;
        }

        return NOTIF_STATUS_SUCCESS;
    }
}

// Sets the notification event.
notification_status_t Notification_SetEvent( notification_type_t notifType )
{
    event_flags_t flagsToSet;
    osa_status_t status;

    switch( notifType )
    {
        case NOTIF_TYPE_CALL:
        {
            flagsToSet = notification_eventFlag_call;
            break;
        }
        case NOTIF_TYPE_MAIL:
        {
            flagsToSet = notification_eventFlag_email;
            break;
        }
        case NOTIF_TYPE_SMS:
        {
            flagsToSet = notification_eventFlag_sms;
            break;
        }

        default:
        {
            // bypass the warning
            flagsToSet = 1 << 3;
        }
    }

    status = OSA_EventSet( &notification_event, ( event_flags_t )flagsToSet );

    if( status != kStatus_OSA_Success )
    {
        return NOTIF_STATUS_ERROR;
    }
    else
    {
        return NOTIF_STATUS_SUCCESS;
    }
}

// Sets the notifications' counter's value.
void Notification_SetUnreadCounter(
    notification_type_t notifType, uint8_t value )
{
    if ( value >= 0 )
    {
        switch ( notifType )
        {
            case NOTIF_TYPE_CALL:
            {
                notification_call_unread = value;
                break;
            }
            case NOTIF_TYPE_MAIL:
            {
                notification_email_unread = value;
                break;
            }
            case NOTIF_TYPE_SMS:
            {
                notification_sms_unread = value;
                break;
            }
        }
    }
}

// Gets the notifications' counter's value.
uint8_t Notification_GetUnreadCounter( notification_type_t notifType )
{
    switch( notifType )
    {
        case NOTIF_TYPE_CALL:
        {
            return notification_call_unread;
        }
        case NOTIF_TYPE_MAIL:
        {
            return notification_email_unread;
        }
        case NOTIF_TYPE_SMS:
        {
            return notification_sms_unread;
        }
    }
    return 0xFF;
}