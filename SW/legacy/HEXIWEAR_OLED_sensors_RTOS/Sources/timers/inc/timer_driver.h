/**
 * timers used throughout HEXIWEAR,
 * their functionality is coded here
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "sensor_timer.h"
//#include "pit_sensor_timer.h"
#include "sensor_driver.h"
#include "HEXIWEAR_info.h"

#define TIMER_BLINKING_PERIOD_MS ( 8000 )

/**
 * initialize the timer
 */
void timer_Init( hexiwear_timer_t timerToUse );

/**
 * deinitialize the timer
 */
void timer_Deinit( hexiwear_timer_t timerToUse );

/**
 * start the timer
 */
void timer_Start( hexiwear_timer_t timerToUse );

/**
 * set the period for the chosen timer
 * @param timerToUse chosen timer
 * @param newPeriod  desired timer period
 */
void timer_SetPeriod( hexiwear_timer_t timerToUse, uint32_t newPeriod );

/**
 * stop the timer
 */
void timer_Stop( hexiwear_timer_t timerToUse );

/**
 * get timer state
 */
bool timer_IsActive( hexiwear_timer_t timerToUse );
