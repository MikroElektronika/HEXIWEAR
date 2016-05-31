/**
 * \file notifications_driver.c
 * \version 1.00
 * \brief this file contains incoming alert routines
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#include "notifications.h"

#include "gui_types.h"

#include "error.h"
#include "string.h"

#if defined( HEXIWEAR_DEBUG )
#include "fsl_uart_driver.h"
#include "DEBUG_UART.h"
#endif

/** private prototypes */
/** private memory declarations */
static event_t notification_event;
static event_flags_t notification_eventFlag_call  = 1 << 0;
static event_flags_t notification_eventFlag_email = 1 << 1;
static event_flags_t notification_eventFlag_sms   = 1 << 2;
static uint8_t
	notification_sms_unread   = 0,
	notification_email_unread = 0,
	notification_call_unread  = 0;

/** public API */

/**
 * initialize the notification event
 * @return  status flag
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
 * wait for the notification event
 * @param  type    notification type
 * @param  timeout timeout value in [ms]
 * @return         status flag
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

/**
 * set the notification event
 * @param type notification type
 * @return     status flag
 */
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

		default:
		{
			// bypass the warning
			flagsToSet = 1 << 3;
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

/**
 * set the notifications' counter's value
 * @param notifType notification type
 * @param value     counter's value
 */
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

/**
 * get the notifications' counter's value
 * @param notifType notification type
 * @return          counter's value
 */
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
