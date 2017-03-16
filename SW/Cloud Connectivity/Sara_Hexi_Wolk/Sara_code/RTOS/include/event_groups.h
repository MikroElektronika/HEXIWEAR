// File: event_groups.h

// Interface for the event groups functionalities.

#ifndef _event_groups_h_
#define _event_groups_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "timers.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/

// Sets the given bits in the given event group from ISR.
#define xEventGroupSetBitsFromISR(                                             \
    xEventGroup, uxBitsToSet, pxHigherPriorityTaskWoken )                      \
    xTimerPendFunctionCallFromISR( vEventGroupSetBitsCallback,                 \
        ( void * ) xEventGroup,                                                \
        ( uint32_t ) uxBitsToSet,                                              \
        pxHigherPriorityTaskWoken                                              \
        )

// Returns the bits of the given event group.
#define xEventGroupGetBits( xEventGroup )                                      \
    xEventGroupClearBits( xEventGroup, 0 )

// Returns the bits of the given event group from ISR.
#define xEventGroupGetBitsFromISR( xEventGroup )                               \
    xEventGroupClearBitsFromISR( xEventGroup, 0 )
    
/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

// Definition of an event group handle to be used outside of event_groups.c.
typedef void * EventGroupHandle_t;

// Type for representing the event bits that a task waits for.
typedef TickType_t EventBits_t;

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Creates an event group.
EventGroupHandle_t xEventGroupCreate();

// Makes the calling task wait on the given event bits in the given event group.
EventBits_t xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToWaitFor,
    const BaseType_t xClearOnExit,
    const BaseType_t xWaitForAllBits,
    TickType_t xTicksToWait
    );

// Clears the given bits in the given event group.
EventBits_t xEventGroupClearBits( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToClear );

// Clears the given bits in the given event group from ISR.
EventBits_t xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToClear );

// Sets the given bits in the given event group.
EventBits_t xEventGroupSetBits( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToSet );

// Synchronise with the event group, which means setting some bits
// and waiting for some others.
EventBits_t xEventGroupSync( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToSet,
    const EventBits_t uxBitsToWaitFor,
    TickType_t xTicksToWait
    );

// Delete an event group.
void vEventGroupDelete( EventGroupHandle_t xEventGroup );

// Execute a "set bits" command that was pended from an interrupt.
// For internal use only.
void vEventGroupSetBitsCallback( void *pvEventGroup,
    const unsigned long ulBitsToSet );

#endif