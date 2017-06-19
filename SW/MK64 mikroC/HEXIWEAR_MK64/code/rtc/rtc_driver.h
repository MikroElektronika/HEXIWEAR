// File: rtc_driver.h

// Declarations of main functionalities in the rtc module.

#ifndef _rtc_driver_h_
#define _rtc_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

//#include "CLOCK.h"
//#include "fsl_rtc_driver.h"
#include "rtc_types.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Setups IRQ, sets RTC datetime and triggers the initial alarm.
_rtc_status_t RTC_Init();

// Sets the time interval alarm is triggered on.
_rtc_status_t RTC_SetAlarmInterval ( uint32_t seconds );

// Gets current RTC alarm interval.
uint32_t RTC_GetAlarmInterval();

// Sets next RTC alarm occurence.
_rtc_status_t RTC_TriggerAlarm(
    rtc_datetime_t *currentTime, uint16_t duration );
    
// Gets the RTC alarm time.
_rtc_status_t RTC_GetAlarmTime( rtc_datetime_t* timeToReturn );

// Gets the actual RTC time.
_rtc_status_t RTC_GetCurrentTime( rtc_datetime_t* timeToReturn );

// Sets new RTC date-time.
_rtc_status_t RTC_UpdateCurrentTime( uint32_t timestamp );


// Sets RTC event for updating date-time.
_rtc_status_t RTC_WatchUpdateEventWait( rtc_datetime_t *dateTime,
    uint8_t *dateUpdateFlag, uint8_t *timeUpdateFlag, uint32_t timeout );

// Waits for the RTC event for updating date-time.
_rtc_status_t RTC_AlarmEventWait( uint32_t timeout );

// Updates RTC counter's value to the default one.
void RTC_UpdateAlarm();

// Disables the RTC alarm.
void RTC_DisableAlarm();

// Enables the RTC alarm.
void RTC_EnableAlarm();

// Sets the new RTC counter for MCU sleep.
void RTC_SetSleepReloadValue( uint32_t interval );

// Get the current RTC sleep counter value.
uint32_t RTC_GetSleepReloadValue();

#endif