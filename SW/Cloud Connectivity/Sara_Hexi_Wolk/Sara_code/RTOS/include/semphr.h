// File: semphr.h

// Interface of semaphores functionalities.

#ifndef _semphr_h_
#define _semphr_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "queue.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/
 
#define semBINARY_SEMAPHORE_QUEUE_LENGTH        1
#define semSEMAPHORE_QUEUE_ITEM_LENGTH          0
#define semGIVE_BLOCK_TIME                      0

// Creates a binary semaphore.
#define vSemaphoreCreateBinary( xSemaphore )                                   \
{                                                                              \
    ( xSemaphore ) = xQueueGenericCreate(                                      \
        1, semSEMAPHORE_QUEUE_ITEM_LENGTH, queueQUEUE_TYPE_BINARY_SEMAPHORE ); \
    if( ( xSemaphore ) != NULL )                                               \
    {                                                                          \
        xSemaphoreGive( ( xSemaphore ) );                                      \
    }                                                                          \
}

// Creates a binary semaphore and returns a handle to it.
#define xSemaphoreCreateBinary()                                               \
    xQueueGenericCreate(                                                       \
        1, semSEMAPHORE_QUEUE_ITEM_LENGTH, queueQUEUE_TYPE_BINARY_SEMAPHORE )

// Performs a take operation on a semaphore.
#define xSemaphoreTake( xSemaphore, xBlockTime )                               \
    xQueueGenericReceive(                                                      \
        ( QueueHandle_t ) ( xSemaphore ), NULL, ( xBlockTime ), pdFALSE )
        
// Performs a recursive take operation on a semaphore.
#define xSemaphoreTakeRecursive( xMutex, xBlockTime )                          \
    xQueueTakeMutexRecursive( ( xMutex ), ( xBlockTime ) )

// Performs a give operation on a semaphore.
#define xSemaphoreGive( xSemaphore )                                           \
    xQueueGenericSend( ( QueueHandle_t ) ( xSemaphore ), NULL,                 \
        semGIVE_BLOCK_TIME, queueSEND_TO_BACK )

// Performs a recursive give operation on a semaphore.
#define xSemaphoreGiveRecursive( xMutex )                                      \
    xQueueGiveMutexRecursive( ( xMutex ) )

// Performs a give operation on a semaphore from ISR.
#define xSemaphoreGiveFromISR( xSemaphore, pxHigherPriorityTaskWoken )         \
    xQueueGenericSendFromISR( ( QueueHandle_t ) ( xSemaphore ), NULL,          \
        ( pxHigherPriorityTaskWoken ), queueSEND_TO_BACK )

// Performs a take operation on a semaphore from ISR.
#define xSemaphoreTakeFromISR( xSemaphore, pxHigherPriorityTaskWoken )         \
    xQueueReceiveFromISR( ( QueueHandle_t ) ( xSemaphore ), NULL,              \
        ( pxHigherPriorityTaskWoken ) )

// Creates a mutex semaphore.
#define xSemaphoreCreateMutex()                                                \
    xQueueCreateMutex( queueQUEUE_TYPE_MUTEX )

// Creates a recursive mutex semaphore.
#define xSemaphoreCreateRecursiveMutex()                                       \
    xQueueCreateMutex( queueQUEUE_TYPE_RECURSIVE_MUTEX )

// Creates a counting semaphore.
#define xSemaphoreCreateCounting( uxMaxCount, uxInitialCount )                 \
    xQueueCreateCountingSemaphore( ( uxMaxCount ), ( uxInitialCount ) )

// Deletes a semaphore.
#define vSemaphoreDelete( xSemaphore )                                         \
    vQueueDelete( ( QueueHandle_t ) ( xSemaphore ) )

// Returns the holder of a mutex semaphore.
#define xSemaphoreGetMutexHolder( xSemaphore )                                 \
    xQueueGetMutexHolder( ( xSemaphore ) )

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

// Semaphore handle is the same as a queue handle.
typedef QueueHandle_t SemaphoreHandle_t;

#endif