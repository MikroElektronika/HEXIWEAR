// File: rtc_driver.c

// Definitions of main functionalities in the rtc module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "rtc_driver.h"
#include "lptmr_driver.h"
#include "power_driver.h"

#include "OSA.h"

#include "error.h"

#include "HEXIWEAR_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define SECONDS_IN_A_DAY     (86400U)
#define SECONDS_IN_A_HOUR    (3600U)
#define SECONDS_IN_A_MIN     (60U)
#define MINS_IN_A_HOUR       (60U)
#define HOURS_IN_A_DAY       (24U)
#define DAYS_IN_A_YEAR       (365U)
#define DAYS_IN_A_LEAP_YEAR  (366U)
#define YEAR_RANGE_START     (1970U)
#define YEAR_RANGE_END       (2099U)

 
#define YES ( 1 )
#define NO  ( 0 )

#define RTC_DecrementSleepCounter()                                            \
    RTC_SleepCounter = ( RTC_SleepCounter == 0)                                \
        ? RTC_SleepCounterReloadValue                                          \
        : RTC_SleepCounter-1
        
#define RTC_HasSleepCounterExpired() ( RTC_SleepCounter == 0 )

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static uint8_t updateInterval              = 1;
static uint8_t RTC_SleepCounterReloadValue = ( 10 - 1 );
static uint8_t RTC_SleepCounter            = ( 10 - 1 );

static event_t alarm_event;

static event_flags_t timeUpdate_eventFlag  = 1 << 0;
static event_flags_t dateUpdate_eventFlag  = 1 << 1;
static event_flags_t alarm_eventFlag       = 1 << 2;

static rtc_datetime_t currentTime;

const rtc_datetime_t initDateTime =
{
    2000, // .year
    1,    // .month
    1,    // .day
    00,   // .hour
    00,   // .minute
    00    // .second
};

// Table of month length (in days) for the Un-leap-year.
static const uint8_t ULY[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U,
    31U,30U,31U};

// Table of month length (in days) for the Leap-year.
static const uint8_t LY[] = {0U, 31U, 29U, 31U, 30U, 31U, 30U, 31U, 31U, 30U,
    31U,30U,31U};

// Number of days from begin of the non Leap-year.
static const uint16_t MONTH_DAYS[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U,
    212U, 243U, 273U, 304U, 334U};

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Clears all interrupts
// and resets the RTC module if the time invalid flag is set.
static void RTC_HAL_Init()
{
    if( TIF_RTC_SR_bit == 1 )
    {
        // Reset the RTC registers except for the SWR bit.
        SWR_bit = 1;
        SWR_bit = 0;
        
        // Set TSR register to 0x1
        // to avoid the TIF bit being set in the SR register.
        RTC_TPR = 0x0000;
        RTC_TSR = 0x00000001;
    }
    
    // Clear the interrupt enable register.
    TSIE_bit = 0;
    TAIE_bit = 0;
    TOIE_RTC_IER_bit = 0;
    TIIE_bit = 0;
}

// Initiates a soft-reset of the RTC module to reset all the RTC registers.
// Also enables the RTC oscillator.
static void RTC_HAL_Enable()
{
    // Enable RTC oscillator since it is required to start the counter.
    OSCE_bit = 1;
}

// Initialises the Real Time Clock module.
static void RTC_DRV_Init()
{
    // Enable clock gate to RTC module.
    RTC_bit = 1;

    // Initialise the general configuration for RTC module.
    RTC_HAL_Init();
    RTC_HAL_Enable();

    NVIC_ICPR1.B14 = 1; // Clear IRQ pending bit for RTC interrupt.
    NVIC_ICPR1.B15 = 1; // Clear IRQ pending bit for seconds RTC interrupt.
    NVIC_IntEnable( IVT_INT_RTC );
    NVIC_IntEnable( IVT_INT_RTC_Seconds );
}

// Checks if the given datetime is in the correct format.
static bool RTC_HAL_IsDatetimeCorrectFormat( const rtc_datetime_t * datetime )
{
    bool result = false;
    
    // Test correctness of given parameters.
    if( ( datetime->year < YEAR_RANGE_START ) ||
        ( datetime->year > YEAR_RANGE_END ) ||
        ( datetime->month < 1 ) ||
        ( datetime->month > 12 ) ||
        ( datetime->day < 1 ) ||
        ( datetime->day > 31 ) ||
        ( datetime->hour >= HOURS_IN_A_DAY ) ||
        ( datetime->minute >= MINS_IN_A_HOUR ) ||
        ( datetime->second >= SECONDS_IN_A_MIN ) )
    {
        // Result is not correct.
        return false;
    }
    
    if( datetime->month == 2 )
    {
        // february
        if( ( ( datetime->year % 4 ) == 0 ) &&
            ( ( datetime->year % 100 ) != 0 ) || 
            ( ( datetime->year % 400 ) == 0 ) )
        {
            // leap year
            if( datetime-> day > 29 )
                return false;
            else
                return true;
        }
        else
        {
            // normal year
            if( datetime->day > 28 )
                return false;
            else
                return true;
        }
    }
    else
    {
        // not february
        if( ( datetime->month == 4 ) || ( datetime->month == 6 ) ||
            ( datetime->month == 9 ) || ( datetime->month == 11 ) )
        {
            // 30-day months
            if( datetime->day > 30 )
                return false;
            else
                return true;
        }
        else
        {
            // 31-day months, already checked
            return true;
        }
    }
}

// Converts time data from datetime to seconds.
static void RTC_HAL_ConvertDatetimeToSecs(
    const rtc_datetime_t* datetime, uint32_t* seconds )
{
    uint32_t days;

    // Compute number of days from start year till given year.
    days = ( datetime->year - YEAR_RANGE_START ) * DAYS_IN_A_YEAR;
    // Add leap year days.
    days += ((datetime->year / 4) - (YEAR_RANGE_START / 4));
    // Add number of days till given month.
    days += MONTH_DAYS[datetime->month];
    // Add days in given month. We take away seconds for the current day
    // as it is represented in the hours and seconds field.
    days += ( datetime->day - 1 );
    //  For leap year if month is less than or equal to Febraury,
    // decrement day counter.
    if ( ( ( datetime->year & 3 ) == 0 ) && ( datetime->month <= 2 ) )
    {
        days--;
    }

    *seconds = ( days * SECONDS_IN_A_DAY) +
               ( datetime->hour * SECONDS_IN_A_HOUR ) +
               ( datetime->minute * SECONDS_IN_A_MIN ) + datetime->second;
}

// Converts time data from seconds to datetime.
static void RTC_HAL_ConvertSecsToDatetime(
    const uint32_t * _seconds, rtc_datetime_t * datetime )
{
    uint32_t x;
    uint32_t Seconds, Days, Days_in_year;
    const uint8_t *Days_in_month;

    // Start from 1970-01-01.
    Seconds = *_seconds;
    // Add 1 for the current day
    // which is represented in the hours and seconds field.
    Days = Seconds / SECONDS_IN_A_DAY + 1;
    // seconds left
    Seconds = Seconds % SECONDS_IN_A_DAY;
    // hours
    datetime->hour = Seconds / SECONDS_IN_A_HOUR;
    // seconds left
    Seconds = Seconds % SECONDS_IN_A_HOUR;
    // minutes
    datetime->minute = Seconds / SECONDS_IN_A_MIN;
    // seconds
    datetime->second = Seconds % SECONDS_IN_A_MIN;
    // year
    datetime->year = YEAR_RANGE_START;
    Days_in_year = DAYS_IN_A_YEAR;

    while( Days > Days_in_year )
    {
        Days -= Days_in_year;
        datetime->year++;
        if( datetime->year & 3U )
        {
            Days_in_year = DAYS_IN_A_YEAR;
        }
        else
        {
            Days_in_year = DAYS_IN_A_LEAP_YEAR;
        }
    }

    if( datetime->year & 3U )
    {
        Days_in_month = ULY;
    }
    else
    {
        Days_in_month = LY;
    }

    for( x = 1U; x <= 12U; x++ )
    {
        if( Days <= ( *( Days_in_month + x ) ) )
        {
            datetime->month = x;
            break;
        }
        else
        {
            Days -= ( *( Days_in_month + x ) );
        }
    }

    datetime->day = Days;
}

// Sets the RTC date and time according to the given time struct.
static bool RTC_DRV_SetDatetime( rtc_datetime_t *datetime )
{
    uint32_t srcClock = 0;
    uint32_t seconds = 0;
    uint16_t prescaler = 0;
    uint64_t tmp = 0;
    
    if( !RTC_HAL_IsDatetimeCorrectFormat(datetime) )
        return false;

    RTC_HAL_ConvertDatetimeToSecs( datetime, &seconds );
    
    if( ( srcClock = g_xtalRtcClkFreq ) != 32768U )
    {
        // As the second register will not increment every second,
        // we need to adjust the value programmed to the seconds register.
        tmp = ( uint64_t )seconds * ( uint64_t )srcClock;
        prescaler = ( uint32_t )( tmp & 0x7FFFU );
        seconds = ( uint32_t )( tmp >> 15U );
    }

    // Set time in seconds.
    TCE_bit = 0;
    // Set seconds counter.
    RTC_TSR = seconds;
    // Set time counter.
    RTC_TPR = prescaler;
    // Enable the counter.
    TCE_bit = 0;
    
    return true;
}

// Sets the RTC alarm.
static bool RTC_DRV_SetAlarm(
    rtc_datetime_t *alarmTime, bool enableAlarmInterrupt )
{
    uint32_t srcClock = 0;
    uint32_t alrmSeconds = 0;
    uint32_t currSeconds = 0;
    uint64_t tmp = 0;
    
    // Return error if the alarm time provided is not valid.
    if( !( RTC_HAL_IsDatetimeCorrectFormat( alarmTime ) ) )
    {
        return false;
    }
    
    RTC_HAL_ConvertDatetimeToSecs(alarmTime, &alrmSeconds);
    
    // Get the current time.
    currSeconds = RTC_TSR;
    
    if( ( srcClock = g_xtalRtcClkFreq ) != 32768U )
    {
        // As the seconds register will not increment every second,
        // we need to adjust the value programmed to the alarm register.
        tmp = ( uint64_t )alrmSeconds * ( uint64_t )srcClock;
        alrmSeconds = (uint32_t)(tmp >> 15U);
    }
    
    // Make sure the alarm is for a future time.
    if( alrmSeconds < currSeconds )
    {
        return false;
    }
    
    // Set alarm in seconds.
    RTC_TAR = alrmSeconds;
    
    // Activate or deactivate the Alarm interrupt based on user choice.
    TAIE_bit = enableAlarmInterrupt;
    
    return true;
}

// Returns the RTC alarm time.
static void RTC_DRV_GetAlarm( rtc_datetime_t *date )
{
    uint32_t alrmSeconds = 0;
    uint32_t srcClock = 0;

    // Get alarm in seconds
    alrmSeconds = RTC_TAR;

    if ( ( srcClock = g_xtalRtcClkFreq ) != 32768U )
    {
        // Re-adjust the alarm value to match the method used to program it.
        alrmSeconds = ( alrmSeconds * ( 32768U / srcClock ) );
    }

    RTC_HAL_ConvertSecsToDatetime( &alrmSeconds, date );
}

// Returns the actual RTC time.
void RTC_DRV_GetDatetime( rtc_datetime_t *datetime )
{
    uint32_t seconds = 0;
    uint32_t srcClock = 0;
    uint64_t tmp = 0;

    seconds = RTC_TSR;

    if ( ( srcClock = g_xtalRtcClkFreq ) != 32768U )
    {
        // In case the input clock to the RTC counter is not 32KHz,
        // the seconds register will not increment every second,
        // therefore the seconds register value needs to be adjusted
        // to get actual seconds.
        // We then add the prescaler register value to the seconds.
        tmp = ( uint64_t )seconds << 15U;
        tmp |= ( uint64_t )( RTC_TPR & 0x7FFFU );
        seconds = tmp / srcClock;
    }
    RTC_HAL_ConvertSecsToDatetime(&seconds, datetime);
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Setups IRQ, sets RTC datetime and triggers the initial alarm.
_rtc_status_t RTC_Init()
{
    // Set RTC interrupt priority.
    HEXIWEAR_SetIntPriority(IVT_INT_RTC, _NVIC_INT_PRIORITY_LVL7);

    RTC_DRV_Init();
    
    // Get current time.
    RTC_GetCurrentTime( &currentTime );
    if( currentTime.year == 1970 )
    {
        memcpy( &currentTime, &initDateTime, sizeof( rtc_datetime_t ) );
        RTC_DRV_SetDatetime( &currentTime);
    }
    
    if( OSA_EventCreate( &alarm_event, kEventAutoClear )
        != kStatus_OSA_Success )
    {
        return RTC_STATUS_ERROR;
    }
    
    RTC_TriggerAlarm( &currentTime, updateInterval );
    
    TCE_bit = 1;
    
    return RTC_STATUS_SUCCESS;
}

// Set the time interval alarm is triggered on.
_rtc_status_t RTC_SetAlarmInterval( uint32_t seconds )
{
    if( seconds <= 0 )
    {
        return RTC_STATUS_INIT_ERROR;
    }
    else
    {
        updateInterval = seconds;
        return RTC_STATUS_SUCCESS;
    }
}

// Gets current RTC alarm interval.
uint32_t RTC_GetAlarmInterval()
{
    return updateInterval;
}

// Sets next RTC alarm occurence.
_rtc_status_t RTC_TriggerAlarm(
    rtc_datetime_t *currentTime, uint16_t duration )
{
    uint32_t temp;

    rtc_datetime_t alarmTime;

    RTC_HAL_ConvertDatetimeToSecs( currentTime, &temp );

    temp = ( 0 != duration ) ?
           ( temp + duration ):
           ( temp + updateInterval );

    // It goes ahead by 1s, decrement it.
    temp -= 1;

    RTC_HAL_ConvertSecsToDatetime( &temp, &alarmTime );

    RTC_DRV_SetAlarm( &alarmTime, true );

    return RTC_STATUS_SUCCESS;
}

// Gets the RTC alarm time.
_rtc_status_t RTC_GetAlarmTime( rtc_datetime_t* timeToReturn )
{
    RTC_DRV_GetAlarm( timeToReturn );
    return RTC_STATUS_SUCCESS;
}

// Gets the actual RTC time.
_rtc_status_t RTC_GetCurrentTime( rtc_datetime_t* timeToReturn )
{
    RTC_DRV_GetDatetime( timeToReturn );
    return RTC_STATUS_SUCCESS;
}

// Sets new RTC datetime.
_rtc_status_t RTC_UpdateCurrentTime( uint32_t timestamp )
{
    rtc_datetime_t tmpTime;

    RTC_HAL_ConvertSecsToDatetime( &timestamp, &tmpTime );
    RTC_DRV_SetDatetime( &tmpTime );

    memcpy( (void *) &currentTime, (void*) &tmpTime, sizeof(rtc_datetime_t) );
    OSA_EventSet( &alarm_event, dateUpdate_eventFlag | timeUpdate_eventFlag);

    RTC_DRV_GetDatetime( &tmpTime );
    RTC_TriggerAlarm( &tmpTime, updateInterval );

    return RTC_STATUS_SUCCESS;
}

//#include "apps/flashlight/flashlight.h" // TODO: remove

// Interrupt callback.
void RTC_AlarmCallback() iv IVT_INT_RTC ics ICS_AUTO
{
    rtc_datetime_t tmpTime;
    
//    RED_LED_TOGGLE(); // TODO: remove

    RTC_GetCurrentTime( &tmpTime );
    RTC_TriggerAlarm( &tmpTime, updateInterval );

    if ( tmpTime.day != currentTime.day )
    {
        OSA_EventSet(
            &alarm_event, dateUpdate_eventFlag | timeUpdate_eventFlag);
        memcpy( &currentTime, &tmpTime, sizeof(rtc_datetime_t) );
    }
    else if ( tmpTime.minute != currentTime.minute )
    {
        OSA_EventSet( &alarm_event, timeUpdate_eventFlag);
        memcpy( &currentTime, &tmpTime, sizeof(rtc_datetime_t) );
    }

    OSA_EventSet( &alarm_event, alarm_eventFlag );

    // RTC also puts MCU to sleep.
    RTC_DecrementSleepCounter();
    if( RTC_HasSleepCounterExpired() )
    {
        switch ( power_GetCurrentMode() )
        {
            // If we're in normal mode, proceed to go to sleep.
            case POWER_CURRENT_MODE_NORMAL:
            {
                // disable RTC
                RTC_DisableAlarm();

                switch( power_GetSleepMode() )
                {
                    // In case of the shallow and total sleep mode,
                    // trigger the sleep task to finish the procedure.
                    case POWER_SLEEP_MODE_SHALLOW:
                    case POWER_SLEEP_MODE_TOTAL:
                    {
                        // goto sleep
                        power_SetSleepSource( POWER_SLEEP_SRC_RTC );
                        power_GoToSleep();
                        break;
                    }

                    // For the sensor tag sleep mode,
                    // announce that we're ready for sensor tag sleep mode.
                    case POWER_SLEEP_MODE_SENSOR_TAG:
                    {
                        power_SetCurrentMode(
                            POWER_CURRENT_MODE_SLEEP_SENSOR_TAG );
                        break;
                    }
                }

                break;
            }

            // This shouldn't happen,
            // if RTC is enabled, we shouldn't be sleeping.
            case POWER_CURRENT_MODE_SLEEP_SHALLOW:
            case POWER_CURRENT_MODE_SLEEP_TOTAL:
            case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
            {
                error_catch( CATCH_POWER );
                break;
            }
        }
    }
}

// Sets RTC event for updating date-time.
_rtc_status_t RTC_WatchUpdateEventWait( rtc_datetime_t *dateTime,
    bool *dateUpdateFlag, bool *timeUpdateFlag, uint32_t timeout )
{
    event_flags_t setFlags;
    osa_status_t status;

    *dateUpdateFlag = false;
    *timeUpdateFlag = false;

    status = OSA_EventWait( &alarm_event,
        timeUpdate_eventFlag | dateUpdate_eventFlag, false, timeout, &setFlags);

    if( status == kStatus_OSA_Success )
    {
        if( setFlags & timeUpdate_eventFlag )
        {
            *timeUpdateFlag = true;
        }
        if( setFlags & dateUpdate_eventFlag )
        {
            *dateUpdateFlag = true;
        }

        memcpy( dateTime, &currentTime, sizeof( rtc_datetime_t ) );
        return RTC_STATUS_SUCCESS;
    }
    return RTC_STATUS_ERROR;
}

// Waits for the RTC event for updating date-time.
_rtc_status_t RTC_AlarmEventWait( uint32_t timeout )
{
    event_flags_t setFlags;
    osa_status_t status;
    
    status = OSA_EventWait(
        &alarm_event, alarm_eventFlag, false, timeout, &setFlags);

    if( status == kStatus_OSA_Success )
    {
        return RTC_STATUS_SUCCESS;
    }
    return RTC_STATUS_ERROR;
}

// Updates RTC counter's value to the default one.
void RTC_UpdateAlarm()
{
    RTC_SleepCounter = RTC_SleepCounterReloadValue;
}

// Disables the RTC alarm.
void RTC_DisableAlarm()
{
    TAIE_bit = 0;
}

// Enables the RTC alarm.
void RTC_EnableAlarm()
{
    TAIE_bit = 1;
}

// Sets the new RTC counter for MCU sleep.
void RTC_SetSleepReloadValue( uint32_t interval )
{
    RTC_SleepCounterReloadValue = interval - 1;
    RTC_UpdateAlarm();
}

// Get the current RTC sleep counter value.
uint32_t RTC_GetSleepReloadValue()
{
    return ( RTC_SleepCounterReloadValue + 1 );
}