/**
 * \file timer_driver.c
 * \version 1.00
 * \brief this file contains functionality for timers used throughout HEXIWEAR
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

#include "timer_driver.h"
#include "power_driver.h"
#include "gui_sensorTag.h"

// #include "flashlight.h"

static void lptmr_Callback();

static bool
	isTimerInit_sensor   = false,
	isTimerActive_sensor = false;

/**
 * initialize the timer
 * @param timerToUse selected timer peripheral
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
 * @param timerToUse selected timer peripheral
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
 * @param timerToUse selected timer peripheral
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
 * @param timerToUse selected timer peripheral
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
 * @param timerToUse selected timer peripheral
 * @param newPeriod  new desired timer period
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
 * @param timerToUse selected timer peripheral
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
