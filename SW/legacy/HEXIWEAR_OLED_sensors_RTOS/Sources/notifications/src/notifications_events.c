/**
 * alerts wrapper routines
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

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

//static notification_status_t Notification_EventWait (event_flags_t flagsToWait, uint32_t timeout, event_flags_t* setFlags);

/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */
static const event_flags_t
	notification_eventSmsArriveMask  = 1 << 1,
	notification_eventMailArriveMask = 1 << 2,
	notification_eventCallArriveMask = 1 << 3;

static event_t notification_event;

/*! *********************************************************************************
*************************************************************************************
* Function definitions
*************************************************************************************
********************************************************************************** */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [Notification_EventInit description]
 */

notification_status_t Notification_EventInit(void)
{
	if(OSA_EventCreate(&notification_event, kEventAutoClear) != kStatus_OSA_Success)
	{
		return NOTIF_STATUS_ERROR;
	}

	return NOTIF_STATUS_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [Notification_EventWait description]
 * @param notification [description]
 */

notification_status_t Notification_ArriveEventWait (notification_type_t type, uint32_t timeout)
{
	event_flags_t setFlags;
	if(OSA_EventWait(&notification_event, (event_flags_t)type, false, timeout, &setFlags) != kStatus_OSA_Success)
	{
		return NOTIF_STATUS_ERROR;
	}

	return NOTIF_STATUS_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [Notification_ArriveEventClear description]
 * @param type [description]
 */

notification_status_t Notification_ArriveEventClear(notification_type_t type)
{
	if(OSA_EventClear(&notification_event, (event_flags_t)type) != kStatus_OSA_Success)
	{
		return NOTIF_STATUS_ERROR;
	}

	return NOTIF_STATUS_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [Notification_ArriveEventSet description]
 * @param type [description]
 */

notification_status_t Notification_ArriveEventSet(notification_type_t type)
{
	if(OSA_EventSet(&notification_event, (event_flags_t)type) != kStatus_OSA_Success)
	{
		return NOTIF_STATUS_ERROR;
	}

	return NOTIF_STATUS_SUCCESS;
}



