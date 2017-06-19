// File: rtc_types.h

// Some commonly used types in the rtc module.

#ifndef _rtc_types_h_
#define _rtc_types_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    RTC_STATUS_SUCCESS,
    RTC_STATUS_ERROR,
    RTC_STATUS_INIT_ERROR

} _rtc_status_t;

// Structure for holding the time in a simple "date" format.
typedef struct RtcDatetime
{
   uint16_t year;    // Range from 1970 to 2099.
   uint16_t month;   // Range from 1 to 12.
   uint16_t day;     // Range from 1 to 31 (depending on month).
   uint16_t hour;    // Range from 0 to 23.
   uint16_t minute;  // Range from 0 to 59.
   uint8_t second;   // Range from 0 to 59.
} rtc_datetime_t;

#endif