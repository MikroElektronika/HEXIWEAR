/**
 * \file rtc_driver.c
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

#include "rtc_driver.h"
#include "string.h"
#include "power_driver.h"

#include "flashlight.h"

void watch_SetClock();

#define YES ( 1 )
#define NO  ( 0 )

#define RTC_DecrementSleepCounter() RTC_SleepCounter = ( 0 == RTC_SleepCounter ) ? RTC_SleepCounterReloadValue : RTC_SleepCounter-1
#define RTC_HasSleepCounterExpired() ( 0 == RTC_SleepCounter )

static uint8_t
    updateInterval 				= 1,
	RTC_SleepCounterReloadValue = ( 10 - 1 ),
	RTC_SleepCounter            = ( 10 - 1 );

static event_t
  alarm_event;

static event_flags_t
  timeUpdate_eventFlag  = 1 << 0,
  dateUpdate_eventFlag  = 1 << 1,
  alarm_eventFlag       = 1 << 2;

static rtc_datetime_t
  currentTime;

const rtc_datetime_t initDateTime =
{
	.year   = 2000,
	.month  = 1,
	.day    = 1,
	.hour   = 00,
	.minute = 00,
	.second = 00
};

/**
 * initialize RTC module, set the time
 * create the alarm event and set the
 * next alarm occurrence
 * @return status flag
 */
_rtc_status_t RTC_Init ()
{
  NVIC_SetPriority( HEXIWEAR_RTC_IRQn, HEXIWEAR_RTC_IRQ_PRIO );
  RTC_DRV_Init( FSL_CLOCK );

  // set default time
  RTC_GetCurrentTime( &currentTime );
  if ( 1970 == currentTime.year )
  {
	  memcpy((void *)&currentTime, (void *)&initDateTime, sizeof(rtc_datetime_t));
	  RTC_DRV_SetDatetime( FSL_CLOCK, &currentTime);
  }

  if ( kStatus_OSA_Success != OSA_EventCreate( &alarm_event, kEventAutoClear ) )
  {
	return RTC_STATUS_ERROR;
  }

  RTC_TriggerAlarm( &currentTime, updateInterval );

  return RTC_STATUS_SUCCESS;
}

/**
 * set the time interval alarm is triggered on
 * @param  seconds time interval in [s]
 * @return         status flag
 */
_rtc_status_t RTC_SetAlarmInterval ( uint32_t seconds )
{
  if ( seconds <= 0 )
  {
    return RTC_STATUS_INIT_ERROR;
  }

  else
  {
    updateInterval = seconds;
    return RTC_STATUS_SUCCESS;
  }
}

/**
 * get the current alarm interval
 * @return status flag
 */
uint32_t RTC_GetAlarmInterval()
{
  return updateInterval;
}

/**
 * wind the clock
 * @param  time     current time
 * @param  duration interval for the next alarm (default will be used is 0 is passed)
 * @return status flag
 */
_rtc_status_t RTC_TriggerAlarm( rtc_datetime_t *time, uint16_t duration )
{
  uint32_t
    foo;

  rtc_datetime_t
    alarmTime;

  RTC_HAL_ConvertDatetimeToSecs( time, &foo );

  foo = ( 0 != duration ) ?
          ( foo + duration ):
          ( foo + updateInterval );

  // it goes ahead by 1s, dunno why
  foo -= 1;

  RTC_HAL_ConvertSecsToDatetime( &foo, &alarmTime );

  RTC_DRV_SetAlarm( FSL_CLOCK, &alarmTime, true );

  return RTC_STATUS_SUCCESS;
}

/**
 * get the time alarm is scheduled for
 * @return status flag
 */
_rtc_status_t RTC_GetAlarmTime( rtc_datetime_t* timeToReturn )
{
	RTC_DRV_GetAlarm( FSL_CLOCK, timeToReturn );
    return RTC_STATUS_SUCCESS;
}

/**
 * get current RTC time
 * @return status flag
 */
_rtc_status_t RTC_GetCurrentTime ( rtc_datetime_t* timeToReturn )
{
  RTC_DRV_GetDatetime( FSL_CLOCK, timeToReturn );
  return RTC_STATUS_SUCCESS;
}

/**
 * update current RTC time
 * @return status flag
 */
_rtc_status_t RTC_UpdateCurrentTime( uint32_t timestamp )
{
  rtc_datetime_t tmpTime;

  RTC_HAL_ConvertSecsToDatetime( &timestamp, &tmpTime );
  RTC_DRV_SetDatetime( FSL_CLOCK, &tmpTime );

  memcpy( (void *) &currentTime, (void*) &tmpTime, sizeof(rtc_datetime_t) );
  OSA_EventSet( &alarm_event, (event_flags_t)dateUpdate_eventFlag | timeUpdate_eventFlag);

  RTC_DRV_GetDatetime( FSL_CLOCK, &tmpTime );
  RTC_TriggerAlarm( &tmpTime, updateInterval );

  return RTC_STATUS_SUCCESS;
}

_rtc_status_t RTC_SetCurrentTime( rtc_datetime_t timestamp )
{
  RTC_DRV_SetDatetime( FSL_CLOCK, &timestamp );

  memcpy( (void *) &currentTime, (void*) &timestamp, sizeof(rtc_datetime_t) );
  OSA_EventSet( &alarm_event, (event_flags_t)dateUpdate_eventFlag | timeUpdate_eventFlag);

  RTC_DRV_GetDatetime( FSL_CLOCK, &timestamp );
  RTC_TriggerAlarm( &timestamp, updateInterval );

  return RTC_STATUS_SUCCESS;
}

/**
 * RTC interrupt handler callback
 */
void RTC_AlarmCallback()
{
    rtc_datetime_t
    	tmpTime;

    RTC_GetCurrentTime( &tmpTime );
    RTC_TriggerAlarm( &tmpTime, updateInterval );

    if ( tmpTime.day != currentTime.day )
    {
        OSA_EventSet( &alarm_event, (event_flags_t)dateUpdate_eventFlag | timeUpdate_eventFlag);
        memcpy( (void*)&currentTime, (void*)&tmpTime, sizeof(rtc_datetime_t) );
    }

    else if ( tmpTime.minute != currentTime.minute )
    {
        OSA_EventSet( &alarm_event, (event_flags_t)timeUpdate_eventFlag);
        memcpy( (void*)&currentTime, (void*)&tmpTime, sizeof(rtc_datetime_t) );
    }

    OSA_EventSet( &alarm_event, (event_flags_t)alarm_eventFlag);

    /** RTC also puts MCU to sleep */

    RTC_DecrementSleepCounter();
    if ( RTC_HasSleepCounterExpired() )
	{
		switch ( power_GetCurrentMode() )
		{
			/** if we're in normal mode, proceed to go to sleep */
			case POWER_CURRENT_MODE_NORMAL:
			{
				// disable RTC
				RTC_DisableAlarm();

				switch( power_GetSleepMode() )
				{
					/**
					 * in case of the shallow and total sleep mode,
					 * trigger the sleep task to finish the procedure
					 */
					case POWER_SLEEP_MODE_SHALLOW:
					case POWER_SLEEP_MODE_TOTAL:
					{
						// goto sleep
						power_SetSleepSource( POWER_SLEEP_SRC_RTC );
						power_GotoSleep();
						break;
					}

					/**
					 * for the sensor tag sleep mode,
					 * announce that we're ready for sensor tag sleep mode
					 */
					case POWER_SLEEP_MODE_SENSOR_TAG:
					{
						power_SetCurrentMode( POWER_CURRENT_MODE_SLEEP_SENSOR_TAG );
						break;
					}
				}

				break;
			}

			/**
			 * this shouldn't happen,
			 * if RTC is enabled, we shouldn't be sleeping
			 */
			case POWER_CURRENT_MODE_SLEEP_SHALLOW:
			case POWER_CURRENT_MODE_SLEEP_TOTAL:
			case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
			{
				catch( CATCH_POWER );
				break;
			}
		}
	}
}

/**
 * set RTC event for updating date-time
 * @param dateTime new date-time
 * @param dateUpdateFlag flag to update date
 * @param timeUpdateFlag flag to update time
 * @param timeout timeout in [ms]
 * @return status flag
 */
_rtc_status_t RTC_WatchUpdateEventWait (rtc_datetime_t *dateTime, bool *dateUpdateFlag, bool *timeUpdateFlag, uint32_t timeout)
{
  event_flags_t setFlags;
  osa_status_t status;

  *dateUpdateFlag = false;
  *timeUpdateFlag = false;

  status = OSA_EventWait(&alarm_event, timeUpdate_eventFlag | dateUpdate_eventFlag, false, timeout, &setFlags);

  if(status == kStatus_OSA_Success)
  {
	  if(setFlags & timeUpdate_eventFlag)
	  {
		*timeUpdateFlag = true;
	  }
	  if(setFlags & dateUpdate_eventFlag)
	  {
		*dateUpdateFlag = true;
	  }

	  memcpy((void *)dateTime, (void *)&currentTime, sizeof(rtc_datetime_t));
	  return RTC_STATUS_SUCCESS;
  }
  return RTC_STATUS_ERROR;
}

/**
 * wait for the RTC event for updating date-time
 * @param timeout timeout value in [ms]
 * @return status flag
 */
_rtc_status_t RTC_AlarmEventWait (uint32_t timeout)
{
  event_flags_t setFlags;

  osa_status_t
    status = OSA_EventWait(&alarm_event, alarm_eventFlag, false, timeout, &setFlags);

  if(status == kStatus_OSA_Success)
  {
	  return RTC_STATUS_SUCCESS;
  }
  return RTC_STATUS_ERROR;
}

/**
 * disable the RTC alarm
 */
void RTC_DisableAlarm()
{
	RTC_DRV_SetAlarmIntCmd( FSL_CLOCK, false );
}

/**
 * enable the RTC alarm
 */
void RTC_EnableAlarm()
{
	RTC_DRV_SetAlarmIntCmd( FSL_CLOCK, true );
}

/**
 * set the new RTC counter for MCU sleep
 * @param interval interval in [ms]
 */
void RTC_SetSleepReloadValue( uint32_t interval )
{
	RTC_SleepCounterReloadValue = interval-1;
	RTC_UpdateAlarm();
}

/**
 * get the current RTC sleep counter value
 * @return counter value
 */
uint32_t RTC_GetSleepReloadValue()
{
	return (RTC_SleepCounterReloadValue+1);
}

/**
 * update RTC counter's value to the default one
 */
void RTC_UpdateAlarm()
{
  RTC_SleepCounter = RTC_SleepCounterReloadValue;
}
