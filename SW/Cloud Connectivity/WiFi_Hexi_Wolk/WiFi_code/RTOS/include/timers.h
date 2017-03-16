// File: timers.h

// Interface of the timers functionalities.

#ifndef _timers_h_
#define _timers_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

//#include "task.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/

// IDs for commands that can be senr and received on the timer queue
#define tmrCOMMAND_EXECUTE_CALLBACK_FROM_ISR    ( -2 )
#define tmrCOMMAND_EXECUTE_CALLBACK             ( -1 )
#define tmrCOMMAND_START_DONT_TRACE             ( 0 )
#define tmrCOMMAND_START                        ( 1 )
#define tmrCOMMAND_RESET                        ( 2 )
#define tmrCOMMAND_STOP                         ( 3 )
#define tmrCOMMAND_CHANGE_PERIOD                ( 4 )
#define tmrCOMMAND_DELETE                       ( 5 )

#define tmrFIRST_FROM_ISR_COMMAND               ( 6 )
#define tmrCOMMAND_START_FROM_ISR               ( 6 )
#define tmrCOMMAND_RESET_FROM_ISR               ( 7 )
#define tmrCOMMAND_STOP_FROM_ISR                ( 8 )
#define tmrCOMMAND_CHANGE_PERIOD_FROM_ISR       ( 9 )

// Starts the specified timer.
#define xTimerStart( xTimer, xTicksToWait )                                    \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_START,                        \
        ( xTaskGetTickCount() ), NULL, ( xTicksToWait ) )

// Stops the specified timer.
#define xTimerStop( xTimer, xTicksToWait )                                     \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_STOP, 0U, NULL,               \
        ( xTicksToWait ) )

// Changes the period of the specified timer.
#define xTimerChangePeriod( xTimer, xNewPeriod, xTicksToWait )                 \
     xTimerGenericCommand( ( xTimer ), tmrCOMMAND_CHANGE_PERIOD,               \
         ( xNewPeriod ), NULL, ( xTicksToWait ) )

// Deletes the specified timer.
#define xTimerDelete( xTimer, xTicksToWait )                                   \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_DELETE, 0U, NULL,             \
        ( xTicksToWait ) )

// Resets the specified timer.
#define xTimerReset( xTimer, xTicksToWait )                                    \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_RESET,                        \
        ( xTaskGetTickCount() ), NULL, ( xTicksToWait ) )

// Starts the specified timer from ISR.
#define xTimerStartFromISR( xTimer, pxHigherPriorityTaskWoken )                \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_START_FROM_ISR,]              \
        ( xTaskGetTickCountFromISR() ), ( pxHigherPriorityTaskWoken ), 0U )

// Stops the specified timer from ISR.
#define xTimerStopFromISR( xTimer, pxHigherPriorityTaskWoken )                 \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_STOP_FROM_ISR, 0,             \
        ( pxHigherPriorityTaskWoken ), 0U )

// Changes the period of the specified timer from ISR.
#define xTimerChangePeriodFromISR(                                             \
    xTimer, xNewPeriod, pxHigherPriorityTaskWoken )                            \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_CHANGE_PERIOD_FROM_ISR,       \
        ( xNewPeriod ), ( pxHigherPriorityTaskWoken ), 0U )

// Resets the specified timer form ISR.
#define xTimerResetFromISR( xTimer, pxHigherPriorityTaskWoken )                \
    xTimerGenericCommand( ( xTimer ), tmrCOMMAND_RESET_FROM_ISR,               \
        ( xTaskGetTickCountFromISR() ), ( pxHigherPriorityTaskWoken ), 0U )

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

// Handle by which the timers are referenced.
typedef void * TimerHandle_t;

// Prototype for timer callback functions.
typedef void ( *TimerCallbackFunction_t )( TimerHandle_t xTimer );

// Prototype for functions used with the xTimerPendFunctionCallFromISR.
typedef void ( *PendedFunction_t )(
    void *pvParameter1, unsigned long ulParameter2 );

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Creates a timer with the given parameters, including the callback function.
TimerHandle_t xTimerCreate( const char * const pcTimerName,
    const TickType_t xTimerPeriodInTicks,
    const UBaseType_t uxAutoReload,
    void * const pvTimerID,
    TimerCallbackFunction_t pxCallbackFunction
    );

// Returns the ID of the given timer.
void *pvGetTimerID( TimerHandle_t xTimer );

// Checks if the timer is in an active list.
BaseType_t xTimerIsTimerActive( TimerHandle_t xTimer );

// Pends a function call from ISR.
BaseType_t xTimerPendFunctionCallFromISR( PendedFunction_t xFunctionToPend,
    void *pvParameter1,
    UBaseType_t ulParameter2,
    BaseType_t *pxHigherPriorityTaskWoken
    );

// Pends a function call.
BaseType_t xTimerPendFunctionCall( PendedFunction_t xFunctionToPend,
    void *pvParameter1,
    UBaseType_t ulParameter2,
    TickType_t xTicksToWait
    );

// Creates the timer task. To be used in the scheduler initialisation function.
BaseType_t xTimerCreateTimerTask();

// Function for a generic timer command.
BaseType_t xTimerGenericCommand( TimerHandle_t xTimer,
    const BaseType_t xCommandID,
    const TickType_t xOptionalValue,
    BaseType_t * const pxHigherPriorityTaskWoken,
    const TickType_t xTicksToWait
    );

#endif