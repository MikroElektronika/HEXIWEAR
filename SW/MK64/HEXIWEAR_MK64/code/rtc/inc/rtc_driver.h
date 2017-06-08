/**
 * \file rtc_driver.h
 * \version 1.00
 * \brief this file contains RTC-related function wrappers and callbacks
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
 * Neither the name of NXP Semiconductor, Inc. nor the names of its
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
 * support: http://www.mikroe.com/forum and https://community.freescale.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "CLOCK.h"
#include "fsl_rtc_driver.h"
#include "rtc_types.h"

/**
 * setup IRQ, set RTC datetime and trigger the initial alarm
 * @return status flag
 */
_rtc_status_t RTC_Init();

/**
 * set RTC alarm interval
 * @param  seconds interval in [s]
 * @return         status flag
 */
_rtc_status_t RTC_SetAlarmInterval( uint32_t seconds );

/**
 * get current RTC alarm interval
 * @return seconds interval in [s]
 */
uint32_t RTC_GetAlarmInterval();

/**
 * set next RTC alarm occurence
 * @return status flag
 */
_rtc_status_t RTC_TriggerAlarm( rtc_datetime_t *currentTime, uint16_t duration );

/**
 * get the RTC alarm time
 * @return status flag
 */
_rtc_status_t RTC_GetAlarmTime( rtc_datetime_t* timeToReturn );

/**
 * get the actual RTC time
 * @return status flag
 */
_rtc_status_t RTC_GetCurrentTime( rtc_datetime_t* timeToReturn );

/**
 * set new RTC date-time
 * @return status flag
 */
_rtc_status_t RTC_UpdateCurrentTime (uint32_t timestamp);


/**
 * set new RTC date-time from structure
 * @return status flag
 */
_rtc_status_t RTC_SetCurrentTime( rtc_datetime_t timestamp );

/**
 * interrupt callback
 */
void RTC_AlarmCallback();

/**
 * set RTC event for updating date-time
 * @param dateTime new date-time
 * @param dateUpdateFlag flag to update date
 * @param timeUpdateFlag flag to update time
 * @param timeout timeout in [ms]
 * @return status flag
 */
_rtc_status_t RTC_WatchUpdateEventWait (rtc_datetime_t *dateTime, bool *dateUpdateFlag, bool *timeUpdateFlag, uint32_t timeout);

/**
 * wait for the RTC event for updating date-time
 * @param timeout timeout value in [ms]
 * @return status flag
 */
_rtc_status_t RTC_AlarmEventWait (uint32_t timeout);

/**
 * update RTC counter's value to the default one
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

/**
 * set the new RTC counter for MCU sleep
 * @param interval interval in [ms]
 */
void RTC_SetSleepReloadValue( uint32_t interval );

/**
 * get the current RTC sleep counter value
 * @return counter value
 */
uint32_t RTC_GetSleepReloadValue();
