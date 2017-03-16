// File: portable.h

// Portable layer API. Each function must be defined for each port.

#ifndef _portable_h_
#define _portable_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "portmacro.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/
 
#define portBYTE_ALIGNMENT_MASK 0x0007

#define portNUM_CONFIGURABLE_REGIONS 1

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Initialises the stack of a new task so it is ready to be executed.
// The registers have to be placed on the stack in the correct order.
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack,
    TaskFunction_t pxCode, void *pvParamaters );
    
// Memory management routines required for the port.
void *pvPortMalloc( UBaseType_t xSize );
void vPortFree( void *pv, UBaseType_t xSize );
//void vPortInitialiseBlocks();
//size_t xPortGetFreeHeapSize();
//size_t xPortGetMinimumEverFreeHeapSize();

// Setup the hardware so that scheduler can take control.
// This generally sets up a tick interrupt and sets timers.
BaseType_t xPortStartScheduler();

// Undo anything that was performed by xPortStartScheduler()
// so that hardware is left in its original state.
void vPortEndScheduler();

// Tick timer management routines.
void vPortInitTickTimer();
void vPortStartTickTimer();
void vPortStopTickTimer();

#endif