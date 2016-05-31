/**
 * data-types related to alerts and their communication
 */

#ifndef HG_NOTIFICATIONS_TYPES
#define HG_NOTIFICATIONS_TYPES

#include <stdint.h>
#include "fsl_os_abstraction.h"
#include "fsl_rtc_driver.h"
#include "host_mcu_interface.h"

typedef struct
{
	uint8_t *buffer;
	uint8_t  length;
	uint8_t  currentPos;
} notification_memHandler_t;

typedef struct
{
	notification_memHandler_t sender;
	notification_memHandler_t data;
	rtc_datetime_t            arrivalTime;
	bool		              validFlag;

} notification_t;

typedef enum
{
	NOTIF_TYPE_SMS    = 1 << 1,
	NOTIF_TYPE_MAIL   = 1 << 2,
	NOTIF_TYPE_CALL   = 1 << 3,
} notification_type_t;

typedef enum
{
  NOTIF_STATUS_SUCCESS,     // success
  NOTIF_STATUS_ERROR,       // fail

} notification_status_t;

typedef enum
{
  NOTIF_HANDLER_STATE_WAIT,
  NOTIF_HANDLER_STATE_READ,

} notification_handlerState_t;

typedef struct
{
	hostInterface_alertIn_type_t type;
	uint8_t                      length;
	uint8_t                      data[20];
} notification_packet_t;

/*! Category of iOS notification */
typedef enum
{
    ancCategoryId_other           = 0,
    ancCategoryId_incomingCall    = 1,
    ancCategoryId_missedCall      = 2,
    ancCategoryId_voiceMail       = 3,
    ancCategoryId_social          = 4,
    ancCategoryId_schedule        = 5,
    ancCategoryId_email           = 6,
    ancCategoryId_news            = 7,
    ancCategoryId_healthFitness   = 8,
    ancCategoryId_businessFinance = 9,
    ancCategoryId_location        = 10,
    ancCategoryId_entertainment   = 11

} ancCategoryId_t;

/*! Notification action*/
typedef enum
{
    ancEventId_NotifAdded    = 0,
    ancEventId_NotifModified = 1,
    ancEventId_NotifRemoved  = 2

} ancEventId_t;

#endif
