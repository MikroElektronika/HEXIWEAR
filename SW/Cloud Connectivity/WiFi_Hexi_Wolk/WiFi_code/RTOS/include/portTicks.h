// File: portTicks.h

// Interface for the tick counter.

#ifndef _portTicks_h_
#define _portTicks_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "FreeRTOSConfig.h"
#include "portmacro.h"

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

// SysTick is counting down.
#define FREERTOS_HWTC_DOWN_COUNTER 1
// Counter is decrementing from this value to zero.
#define FREERTOS_HWTC_PERIOD ( ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1 )

#define HWTC_COUNT_DIRECTION  DIRECTION_DECREMENTING
#define HWTC_PERIOD           FREERTOS_HWTC_PERIOD
#define HWTC_DIVISOR          2
#define HWTC_COUNT            uxGetTickCounterValue()

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Returns the current tick counter value.
portLONG uxGetTickCounterValue(void);

#endif