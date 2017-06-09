// Type: notifications_types.h

// Some commonly used types in the notifications module.

#ifndef _notifications_types_h_
#define _notifications_types_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "OSA.h"
#include "rtc_driver.h"
#include "host_mcu_interface.h"

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

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

// category for iOS notifications
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

// notifications actions
typedef enum
{
    ancEventId_NotifAdded    = 0,
    ancEventId_NotifModified = 1,
    ancEventId_NotifRemoved  = 2

} ancEventId_t;

#endif