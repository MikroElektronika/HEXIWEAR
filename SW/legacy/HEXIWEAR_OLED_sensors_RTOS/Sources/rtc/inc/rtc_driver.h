/**
 * RTC-related functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_RTC_DRIVER
#define HG_RTC_DRIVER

#include "CLOCK.h"
#include "fsl_rtc_driver.h"
#include "rtc_types.h"

/**
 * [RTC_Init description]
 * @return [description]
 */
_rtc_status_t RTC_Init();

/**
 * [RTC_SetAlarmInterval  description]
 * @param  seconds [description]
 * @return         [description]
 */
_rtc_status_t RTC_SetAlarmInterval(
                                    uint32_t seconds
                                  );

/**
 * [RTC_GetAlarmInterval description]
 * @return [description]
 */
uint32_t RTC_GetAlarmInterval();

/**
 * [RTC_Trigger description]
 * @return [description]
 */
_rtc_status_t RTC_TriggerAlarm( rtc_datetime_t *currentTime, uint16_t duration );

/**
 * [RTC_UnsetAlarm description]
 * @return [description]
 */
void RTC_HaltAlarm();

/**
 * [RTC_UnsetAlarm description]
 * @return [description]
 */
_rtc_status_t RTC_GetAlarmTime( rtc_datetime_t* timeToReturn );

/**
 * [RTC_UnsetAlarm description]
 * @return [description]
 */
_rtc_status_t RTC_GetCurrentTime( rtc_datetime_t* timeToReturn );

/**
 * [RTC_UpdateCurrentTime description]
 * @return [description]
 */
_rtc_status_t RTC_UpdateCurrentTime (uint32_t timestamp);

/**
 * [RTC_AlarmCallback description]
 *
 */
void RTC_AlarmCallback (void);

/**
 * [RTC_WatchUpdateEventWait description]
 *
 */
_rtc_status_t RTC_WatchUpdateEventWait (rtc_datetime_t *dateTime, bool *dateUpdateFlag, bool *timeUpdateFlag, uint32_t timeout);

/**
 * [RTC_AlarmEventWait description]
 *
 */
_rtc_status_t RTC_AlarmEventWait (uint32_t timeout);

/**
 * update the current alarm time
 */
void RTC_UpdateAlarm();

/**
 * disable the RTC alarm
 */
void RTC_DisableAlarm();

/**
 * enable the RTC alarm
 */
void RTC_EnableAlarm();

void RTC_SetSleepReloadValue( uint32_t interval );

uint32_t RTC_GetSleepReloadValue();

#endif
