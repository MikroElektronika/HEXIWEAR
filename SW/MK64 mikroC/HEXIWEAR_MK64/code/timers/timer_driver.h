// File: timer_driver.h

// Declarations of main functionalities in the timer driver module.

#ifndef _timer_driver_h_
#define _timer_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////
 
#include "sensor_driver.h"
#include "lptmr_driver.h"
#include "HEXIWEAR_info.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define TIMER_BLINKING_PERIOD_MS ( 8000 )

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// LPTMR configuration declaration.
extern const lptmr_user_config_t sensor_timer_cfg;

// Driver state structure which holds driver runtime data.
extern lptmr_state_t sensor_timer_State;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the timer.
void timer_Init( hexiwear_timer_t timerToUse );

// Deinitialises the timer.
void timer_Deinit( hexiwear_timer_t timerToUse );

// Starts the timer.
void timer_Start( hexiwear_timer_t timerToUse );

// Sets the period for the chosen timer in microseconds.
void timer_SetPeriod( hexiwear_timer_t timerToUse, uint32_t newPeriod );

// Stops the timer.
void timer_Stop( hexiwear_timer_t timerToUse );

// Gets timer state.
bool timer_IsActive( hexiwear_timer_t timerToUse );

#endif