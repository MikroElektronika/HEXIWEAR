// File: croutine.h

// Interface for the co-routines functionality.

#ifndef _croutine_h_
#define _croutine_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "list.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/

// Macro that must be called at the start of a co-routine function.
#define crSTART( pxCRCB ) switch( ( ( CRCB_t * )pxCRCB )->uxState ) \
        {                                                           \
            case 0:

// Macro that must be called at the start of a co-routine function.
#define crEND() }

// Exits the co-routine function
// and sets the co-routine to return to code below the next time it enters.
// This macro is only to be used within the kernel code.
#define crSET_STATE0( xHandle )                                                \
        ( ( CRCB_t * )xHandle )->uxState = __LINE__ * 2;                       \
        return;                                                                \
    case ( __LINE__ * 2 ):

// Another variant of the macro above.
#define crSET_STATE1( xHandle )                                                \
        ( ( CRCB_t * )xHandle )->uxState = __LINE__ * 2 + 1;                   \
        return;                                                                \
    case ( __LINE__ * 2 + 1 ):

// Makes a delay in a co-routine function.
#define crDELAY( xHandle, xTicksToDelay )                                      \
    if( ( xTicksToDelay ) > 0 )                                                \
        vCoRoutineAddToDelayedList( xTicksToDelay, NULL );                     \
    crSET_STATE0( xHandle );

// Sends an item to a queue.
#define crQUEUE_SEND( xHandle, pxQueue, pvItemToQueue, xTicksToWait, pxResult )\
{                                                                              \
     *( pxResult ) = xQueueCRSend( pxQueue, pvItemToQueue, xTicksToWait );     \
     if( *( pxResult ) == errQUEUE_BLOCKED )                                   \
     {                                                                         \
         crSET_STATE0( xHandle );                                              \
         *( pxResult ) = xQueueCRSend( pxQueue, pvItemToQueue, 0 );            \
     }                                                                         \
     if( *( pxResult ) == errQUEUE_YIELD )                                     \
     {                                                                         \
         crSET_STATE1( xHandle );                                              \
         *( pxResult ) = pdPASS;                                               \
     }                                                                         \
}

// Receives an item from a queue.
#define crQUEUE_RECEIVE( xHandle, pxQueue, pvBuffer, xTicksToWait, pxResult )  \
{                                                                              \
    *( pxResult ) = xQueueCRReceive( pxQueue, pvBuffer, xTicksToWait );        \
     if( *( pxResult ) == errQUEUE_BLOCKED )                                   \
     {                                                                         \
         crSET_STATE0( xHandle );                                              \
         *( pxResult ) = xQueueCRReceive( pxQueue, pvBuffer, 0 );              \
     }                                                                         \
     if( *( pxResult ) == errQUEUE_YIELD )                                     \
     {                                                                         \
         crSET_STATE1( xHandle );                                              \
         *( pxResult ) = pdPASS;                                               \
     }                                                                         \
}

// Sends an item to a queue. Can be called from an ISR
#define crQUEUE_SEND_FROM_ISR( pxQueue, pvItemToQueue,                         \
     xCoRoutinePreviouslyWoken )                                               \
     xQueueCRSendFromISR(                                                      \
         ( pxQueue ), ( pvItemToQueue ), ( xCoRoutinePreviouslyWoken ) )       \

// Receives an item from a queue. Can be called from an ISR.
#define crQUEUE_RECEIVE_FROM_ISR( pxQueue, pvBuffer, pxCoRoutineWoken )        \
    xQueueCRReceiveFromISR(                                                    \
        ( pxQueue ), ( pvBuffer ), ( pxCoRoutineWoken ) )                      \

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

// Definition of a handle
// that hides the implementation of the co-routine control block.
typedef void * CoRoutineHandle_t;

// A prototype for the co-routine functions.
typedef void ( *crCOROUTINE_CODE )( CoRoutineHandle_t, UBaseType_t );

// Structure that represents a control block for a co-routine (CRCB).
// This definition must be in the header file
// due to the macro nature of the co-routine implementation.
typedef struct corCoRoutineControlBlock
{
    // The co-routine function code.
    crCOROUTINE_CODE pxCoRoutineFunction;
    // List item used to place the CRBC in ready and blocked queues.
    ListItem_t       xGenericListItem;
    // List item used to place the CRBC in event lists.
    ListItem_t       xEventListItem;
    // The priority of the co-routine in relation to other co-routines.
    UBaseType_t      uxPriority;
    // Used to distinguish between co-routines
    // when multiple co-routines use the same function.
    UBaseType_t      uxIndex;
    // Used internally by the co-routine implementation.
    unsigned int     uxState;
} CRCB_t;

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Creates a co-routine for the given function.
BaseType_t xCoRoutineCreate( crCOROUTINE_CODE pxCoRoutineCode,
    UBaseType_t uxPriority, UBaseType_t uxIndex );

// Schedules the execution of a co-routine.
void vCoRoutineSchedule();

// Delays a co-routine for the given number of ticks.
// This function is only to be used within the kernel code.
void vCoRoutineAddToDelayedList( TickType_t xTicksToDelay,
    List_t *pxEventList );

// Removes the highest priority co-routine from the event list
// and places it in the pending ready list.
// This function is only to be used within the kernel code.
BaseType_t xCoRoutineRemoveFromEventList( const List_t *pxEventList );

#endif