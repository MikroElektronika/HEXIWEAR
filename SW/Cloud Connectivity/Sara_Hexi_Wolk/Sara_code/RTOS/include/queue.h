// file: queue.h

#ifndef _queue_h_
#define _queue_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "task.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/

#define queueSEND_TO_BACK               0
#define queueSEND_TO_FRONT              1
#define queueOVERWRITE                  2

#define queueQUEUE_TYPE_BASE                    0
#define queueQUEUE_TYPE_SET                     0
#define queueQUEUE_TYPE_MUTEX                   1
#define queueQUEUE_TYPE_COUNTING_SEMAPHORE      2
#define queueQUEUE_TYPE_BINARY_SEMAPHORE        3
#define queueQUEUE_TYPE_RECURSIVE_MUTEX         4

// Creates a queue with the given length and item size.
#define xQueueCreate( uxQueueLength, uxItemSize )                              \
    xQueueGenericCreate( uxQueueLength, uxItemSize, queueQUEUE_TYPE_BASE )

// Sends the given item to the front of the given queue.
#define xQueueSendToFront( xQueue, pvItemToQueue, xTicksToWait )               \
    xQueueGenericSend(                                                         \
        ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_FRONT )

// Sends the given item to the back of the given queue.
#define xQueueSendToBack( xQueue, pvItemToQueue, xTicksToWait )                \
    xQueueGenericSend(                                                         \
        ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_BACK )

// Sends the given item to the back of the given queue (default).
#define xQueueSend( xQueue, pvItemToQueue, xTicksToWait )                      \
    xQueueGenericSend(                                                         \
        ( xQueue ), ( pvItemToQueue ), ( xTicksToWait ), queueSEND_TO_BACK )

// Overwrites an item in the given queue with the new given item.
#define xQueueOverwrite( xQueue, pvItemToQueue )                               \
    xQueueGenericSend( ( xQueue ), ( pvItemToQueue ), 0, queueOVERWRITE )

// Copies the item at the top of the given queue, without removing it,
// and place it in the given buffer.
#define xQueuePeek( xQueue, pvBuffer, xTicksToWait )                           \
    xQueueGenericReceive( ( xQueue ), ( pvBuffer ), ( xTicksToWait ), pdTRUE )

// Removes an item from the queue and place it in the given buffer.
#define xQueueReceive( xQueue, pvBuffer, xTicksToWait )                        \
    xQueueGenericReceive( ( xQueue ), ( pvBuffer ), ( xTicksToWait ), pdFALSE )

// Sends the given item to the front of the given queue.
// Can be called from an ISR.
#define xQueueSendToFrontFromISR(                                              \
    xQueue, pvItemToQueue, pxHigherPriorityTaskWoken )                         \
    xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ),                   \
        ( pxHigherPriorityTaskWoken ), queueSEND_TO_FRONT )

// Sends the given item to the back of the given queue.
// Can be called from an ISR.
#define xQueueSendToBackFromISR(                                               \
    xQueue, pvItemToQueue, pxHigherPriorityTaskWoken )                         \
    xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ),                   \
        ( pxHigherPriorityTaskWoken ), queueSEND_TO_BACK )

// Overwrites an item in the given queue with the new given item.
// Can be called from an ISR.
#define xQueueOverwriteFromISR(                                                \
    xQueue, pvItemToQueue, pxHigherPriorityTaskWoken )                         \
    xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ),                   \
        ( pxHigherPriorityTaskWoken ), queueOVERWRITE )

// Sends the given item to the back of the given queue (default).
// Can be called from an ISR.
#define xQueueSendFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken )  \
    xQueueGenericSendFromISR( ( xQueue ), ( pvItemToQueue ),                   \
        ( pxHigherPriorityTaskWoken ), queueSEND_TO_BACK )

// Resets the given queue.
#define xQueueReset( xQueue ) xQueueGenericReset( xQueue, pdFALSE )

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/
 
// Type by which queues are referenced.
typedef void * QueueHandle_t;

// Type by which queue sets are referenced.
typedef void * QueueSetHandle_t;

// Type by which queue set members (queues and semaphores) are referenced.
typedef void * QueueSetMemberHandle_t;

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Sends an item to the designated place in the queue.
BaseType_t xQueueGenericSend( QueueHandle_t xQueue,
    const void * const pvItemToQueue,
    TickType_t xTicksToWait,
    const BaseType_t xCopyPosition
    );

// Takes a peek at the top of a queue. Can be called form an ISR.
BaseType_t xQueuePeekFromISR( QueueHandle_t xQueue, void * const pvBuffer );

// Function for receiving an item or taking a peek at the queue.
BaseType_t xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer,
    TickType_t xTicksToWait, const BaseType_t xJustPeeking );
    
// Returns the number of messages waiting on a queue.
UBaseType_t uxQueueMessagesWaiting( const QueueHandle_t pxQueue );

// Returns the number of available spaces in a queue.
UBaseType_t uxQueueSpacesAvailable( const QueueHandle_t xQueue );

// Deletes a queue.
void vQueueDelete( QueueHandle_t xQueue );

// Sends an item to the designated place in the queue.
// Can be called from an ISR.
BaseType_t xQueueGenericSendFromISR( QueueHandle_t xQueue,
    const void * const pvItemToQueue,
    BaseType_t * const pxHigherPriorityTaskWoken,
    const BaseType_t xCopyPosition
    );
    
// Receives an item from a queue. Can be called from an ISR.
BaseType_t xQueueReceiveFromISR( QueueHandle_t xQueue, void * const pvBuffer,
    BaseType_t * const pxHigherPriorityTaskWoken );
    
// Checks whether a queue is empty. Can be called form an ISR.
BaseType_t xQueueIsQueueEmptyFromISR( const QueueHandle_t pxQueue );

// Checks whether a queue is full. Can be called from an ISR.
BaseType_t xQueueIsQueueFullFromISR( const QueueHandle_t pxQueue );

// Returns the number of messages waiting on a queue. Can be called from an ISR.
UBaseType_t uxQueueMessagesWaitingFromISR( const QueueHandle_t pxQueue );

// Creates a queue that serves as a mutex.
QueueHandle_t xQueueCreateMutex( const int8_t ucQueueType );

// Function for creating a queue that serves as a semaphore.
QueueHandle_t xQueueCreateCountingSemaphore( const UBaseType_t uxMaxCount,
    const UBaseType_t uxInitialCount );
    
// Returns the mutex holder of a queue used as a mutex.
TaskHandle_t xQueueGetMutexHolder( QueueHandle_t xMutex );

// Performs a recursive take of a mutex.
BaseType_t xQueueTakeMutexRecursive( QueueHandle_t xMutex,
    TickType_t xTicksToWait );
    
// Performs a recursive give of a mutex.
BaseType_t xQueueGiveMutexRecursive( QueueHandle_t xMutex );

// Adds a queue to the new registry.
void vQueueAddToRegistry( QueueHandle_t xQueue, const char *pcQueueName );

// Removes a queue from the queue registry.
void vQueueUnregisterQueue( QueueHandle_t xQueue );

// Generic queue creation.
QueueHandle_t xQueueGenericCreate( const UBaseType_t uxQueueLength,
    const UBaseType_t uxItemSize, const int8_t ucQueueType );
    
// Waits for a message in a queue - restricted version.
void vQueueWaitForMessageRestricted( QueueHandle_t xQueue,
    TickType_t xTicksToWait );
    
// Generic queue reset.
BaseType_t xQueueGenericReset( QueueHandle_t xQueue, BaseType_t xNewQueue );

#endif