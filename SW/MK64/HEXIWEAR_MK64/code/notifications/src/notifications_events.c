/**
 * \file notifications_events.c
 * \version 1.00
 * \brief this file contains arriving alert event objects
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

#include "notifications_driver.h"
#include "notifications_info.h"
#include "notifications_defs.h"

#include "error.h"

#if defined( HEXIWEAR_DEBUG )
#include "fsl_uart_driver.h"
#include "DEBUG_UART.h"
#endif

/** private prototypes */

//static notification_status_t Notification_EventWait (event_flags_t flagsToWait, uint32_t timeout, event_flags_t* setFlags);

/** private memory declarations */
static const event_flags_t
	notification_eventSmsArriveMask  = 1 << 1,
	notification_eventMailArriveMask = 1 << 2,
	notification_eventCallArriveMask = 1 << 3;

static event_t notification_event;

/** function definitions */

/**
 * initialize the notification event
 * @return  status flag
 */
notification_status_t Notification_EventInit()
{
	if ( kStatus_OSA_Success != OSA_EventCreate( &notification_event, kEventAutoClear ) )
	{
		return NOTIF_STATUS_ERROR;
	}

	return NOTIF_STATUS_SUCCESS;
}

/**
 * wait for the notification event
 * @param  type    notification type
 * @param  timeout timeout value in [ms]
 * @return         status flag
 */
notification_status_t Notification_ArriveEventWait	(
                                                   		notification_type_t type,
                                                                   uint32_t timeout
                                               		)
{
	event_flags_t
        setFlags;
	if ( kStatus_OSA_Success != OSA_EventWait( &notification_event, (event_flags_t)type, false, timeout, &setFlags ) )
	{
		return NOTIF_STATUS_ERROR;
	}

	return NOTIF_STATUS_SUCCESS;
}

/**
 * clear the notification event
 * @param type notification type
 * @return     status flag
 */
notification_status_t Notification_ArriveEventClear(notification_type_t type)
{
	if ( kStatus_OSA_Success != OSA_EventClear( &notification_event, (event_flags_t)type ) )
	{
		return NOTIF_STATUS_ERROR;
	}

	return NOTIF_STATUS_SUCCESS;
}

/**
 * set the notification event
 * @param type notification type
 * @return     status flag
 */
notification_status_t Notification_ArriveEventSet(notification_type_t type)
{
	if ( kStatus_OSA_Success != OSA_EventSet( &notification_event, (event_flags_t)type ) )
	{
		return NOTIF_STATUS_ERROR;
	}

	return NOTIF_STATUS_SUCCESS;
}