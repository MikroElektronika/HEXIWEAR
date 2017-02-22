/**
 * timers used throughout HEXIWEAR,
 * their functionality is coded here
 * Project HEXIWEAR, 2015
 */

#include "timer_driver.h"
#include "power_driver.h"
#include "gui_sensorTag.h"

// lajkatest
#include "flashlight.h"

static void lptmr_Callback();

static bool
	isTimerInit_sensor   = false,
	isTimerActive_sensor = false;

/**
 * initialize the timer
 */
void timer_Init( hexiwear_timer_t timerToUse )
{
    switch ( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
        	if ( false == isTimerInit_sensor )
        	{
        		isTimerInit_sensor = true;
        		NVIC_SetPriority( HEXIWEAR_TIMER_IRQn, HEXIWEAR_TIMER_IRQ_PRIO );
        		LPTMR_DRV_InstallCallback( FSL_SENSOR_TIMER, lptmr_Callback );
        	}
            break;
        }

        default: {}
    }
}

/**
 * deinitialize the timer
 */
void timer_Deinit( hexiwear_timer_t timerToUse )
{
    switch ( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
        	if ( true == isTimerInit_sensor )
        	{
        		isTimerInit_sensor = false;
        		LPTMR_DRV_Deinit( FSL_SENSOR_TIMER );
        	}
            break;
        }

        default: {}
    }
}

/**
 * get timer state
 */
bool timer_IsActive( hexiwear_timer_t timerToUse )
{
    switch ( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
            return isTimerActive_sensor;
        }

        default:
        {
            return false;
        }
    }
}

/**
 * start the timer
 */
void timer_Start( hexiwear_timer_t timerToUse )
{
    switch ( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
        	if ( false == isTimerActive_sensor )
        	{
				isTimerActive_sensor = true;
				LPTMR_DRV_Start( FSL_SENSOR_TIMER );
        	}
            break;
        }

        default: {}
    }
}

/**
 * set the period for the chosen timer
 * @param timerToUse chosen timer
 * @param newPeriod  desired timer period
 */
void timer_SetPeriod( hexiwear_timer_t timerToUse, uint32_t newPeriod )
{
    switch ( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
            LPTMR_DRV_SetTimerPeriodUs( FSL_SENSOR_TIMER, newPeriod );
            break;
        }
        default: {}
    }
}

/**
 * stop the timer
 */
void timer_Stop( hexiwear_timer_t timerToUse )
{
    switch ( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
        	if ( true == isTimerActive_sensor )
        	{
        		isTimerActive_sensor = false;
        		LPTMR_DRV_Stop( FSL_SENSOR_TIMER );
        	}
            break;
        }

        default: {}
    }
}

/**
 * timer interrupt callback
 */
static void lptmr_Callback()
{
    switch ( power_GetCurrentMode() )
    {
        /** in normal or shallow sleep case, continue working normally */
        case POWER_CURRENT_MODE_NORMAL:
        case POWER_CURRENT_MODE_SLEEP_SHALLOW:
        {
            break;
        }

        /**
         * if sensor tag sleep mode is active,
         * mark this callback as the wake-up source
         */
        case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
        {
        	if ( POWER_STATUS_SUCCESS == power_SetWakeSource( POWER_WAKE_SRC_SENSOR_TIMER ) )
        	{
//        		power_TakeFromSTSema();
        	}
        	else
        	{
                asm("nop");
        		// RED_LED_ON();
        	}
        	break;
        }

        case POWER_CURRENT_MODE_SLEEP_TOTAL:
        {
            /**
             * do nothing,
             * since we will probably end up here between declaring total sleep mode
             * and actually disabling the sensor timer
             */
            break;
        }
    }

    sensor_StopWait();
}
