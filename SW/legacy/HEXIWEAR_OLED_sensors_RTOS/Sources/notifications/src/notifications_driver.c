/**
 * alerts wrapper routines
 * Project HEXIWEAR, 2015
 */



#include "notifications_driver.h"
#include "notifications_events.h"
#include "notifications_info.h"
#include "notifications_defs.h"

#include "gui_types.h"

#include "error.h"
#include "string.h"

#if defined( HEXIWEAR_DEBUG )
#include "fsl_uart_driver.h"
#include "DEBUG_UART.h"
#endif

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */

static event_t notification_event;

static event_flags_t notification_eventFlag_call  = 1 << 0;
static event_flags_t notification_eventFlag_email = 1 << 1;
static event_flags_t notification_eventFlag_sms   = 1 << 2;

static uint8_t
	notification_sms_unread   = 0,
	notification_email_unread = 0,
	notification_call_unread  = 0;

/*! *********************************************************************************
*************************************************************************************
* Function definitions
*************************************************************************************
********************************************************************************** */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [Notification_Init description]
 */
notification_status_t Notification_Init()
{
	if ( kStatus_OSA_Success == OSA_EventCreate( &notification_event, kEventAutoClear ) )
	{
		return NOTIF_STATUS_SUCCESS;
	}
	else
	{
		return NOTIF_STATUS_ERROR;
	}
}

/**
 * [buttonsGroup_DestroyTasks description]
 * @param param [description]
 */
notification_status_t Notification_WaitForEvent( notification_type_t* notifType, uint32_t timeout )
{
	osa_status_t status;
	event_flags_t setFlags;

	status = OSA_EventWait(
							&notification_event,
							notification_eventFlag_call | notification_eventFlag_email | notification_eventFlag_sms,
							false,
							timeout,
							&setFlags
						  );

	if ( kStatus_OSA_Success != status )
	{
		return NOTIF_STATUS_ERROR;
	}
	else
	{
		if ( 0 != ( setFlags & notification_eventFlag_call ) )
		{
			*notifType = NOTIF_TYPE_CALL;
		}
		else if ( 0 != ( setFlags & notification_eventFlag_email ) )
		{
			*notifType = NOTIF_TYPE_MAIL;
		}
		else if ( 0 != ( setFlags & notification_eventFlag_sms ) )
		{
			*notifType = NOTIF_TYPE_SMS;
		}

		return NOTIF_STATUS_SUCCESS;
	}
}


notification_status_t Notification_SetEvent( notification_type_t notifType )
{
	event_flags_t
		flagsToSet;

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
	}

	osa_status_t
		status = OSA_EventSet( &notification_event, (event_flags_t)flagsToSet );

	if ( kStatus_OSA_Success != status )
	{
		return NOTIF_STATUS_ERROR;
	}
	else
	{
		return NOTIF_STATUS_SUCCESS;
	}
}

void Notification_SetUnreadCounter( notification_type_t notifType, uint8_t value )
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


uint8_t Notification_GetUnreadCounter( notification_type_t notifType )
{
	switch ( notifType )
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


