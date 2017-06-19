// File: timer_driver.c

// Definitions of main functionalities in the timer driver module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "timer_driver.h"
#include "lptmr_driver.h"
#include "power_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               *
////////////////////////////////////////////////////////////////////////////////

static bool isTimerInit_sensor   = false;
static bool isTimerActive_sensor = false;



const lptmr_user_config_t sensor_timer_cfg = {
    kLptmrTimerModeTimeCounter,          // .timerMode
    kLptmrPinSelectInput0,               // .pinSelect
    kLptmrPinPolarityActiveHigh,         // .pinPolarity
    false,                               // .freeRunningEnable
    false,                               // .prescalerEnable
    kClockLptmrSrcLpoClk,                // .prescalerClockSource
    kLptmrPrescalerDivide4GlitchFilter2, // .prescalerValue
    true,                                // .isInterruptEnabled
};

// Driver state structure
lptmr_state_t sensor_timer_State;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Timer interrupt callback.
static void lptmr_Callback()
{
    switch( power_GetCurrentMode() )
    {
        // In normal or shallow sleep case, continue working normally.
        case POWER_CURRENT_MODE_NORMAL:
        case POWER_CURRENT_MODE_SLEEP_SHALLOW:
        {
            break;
        }

        // If sensor tag sleep mode is active,
        // mark this callback as the wake-up source.
        case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
        {
            if( power_SetWakeSource( POWER_WAKE_SRC_SENSOR_TIMER )
                == POWER_STATUS_SUCCESS )
            {
                // power_TakeFromSTSema();
            }
            else
            {
                asm NOP;
                // RED_LED_ON();
            }
            break;
        }

        case POWER_CURRENT_MODE_SLEEP_TOTAL:
        {
            // Do nothing, since we will probably end up here
            // between declaring total sleep mode
            // and actually disabling the sensor timer.
            break;
        }
    }

    sensor_StopWait();
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the timer.
void timer_Init( hexiwear_timer_t timerToUse )
{
    switch( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
            if( isTimerInit_sensor == false)
            {
                isTimerInit_sensor = true;
                HEXIWEAR_SetIntPriority(IVT_INT_LPTimer, _NVIC_INT_PRIORITY_LVL8);
                LPTMR_DRV_InstallCallback( lptmr_Callback );
            }
            break;
        }
        
        default:
            break;
    }
}

// Deinitialises the timer.
void timer_Deinit( hexiwear_timer_t timerToUse )
{
    switch( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
            if( isTimerInit_sensor == true )
            {
                isTimerInit_sensor = false;
                LPTMR_DRV_Deinit();
            }
            break;
        }

        default:
            break;
    }
}

// Starts the timer.
void timer_Start( hexiwear_timer_t timerToUse )
{
    switch( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
            if( isTimerActive_sensor == false )
            {
                isTimerActive_sensor = true;
                LPTMR_DRV_Start();
            }
            break;
        }

        default:
            break;
    }
}

// Sets the period for the chosen timer in microseconds.
void timer_SetPeriod( hexiwear_timer_t timerToUse, uint32_t newPeriod )
{
    switch( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
            LPTMR_DRV_SetTimerPeriodUs( newPeriod );
            break;
        }
        
        default:
            break;
    }
}

// Stops the timer.
void timer_Stop( hexiwear_timer_t timerToUse )
{
    switch( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
        {
            if( isTimerActive_sensor == true )
            {
                isTimerActive_sensor = false;
                LPTMR_DRV_Stop();
            }
            break;
        }

        default:
            break;
    }
}

// Gets timer state.
bool timer_IsActive( hexiwear_timer_t timerToUse )
{
    switch ( timerToUse )
    {
        case HEXIWEAR_TIMER_SENSOR:
            return isTimerActive_sensor;

        default:
            return false;
    }
}