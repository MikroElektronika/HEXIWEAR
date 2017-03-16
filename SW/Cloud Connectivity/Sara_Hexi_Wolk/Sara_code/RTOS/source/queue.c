// File: queue.c

// Implementation of queues, which are used as semaphores,
// for storing items waiting on an event etc.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/

// Constants used with the xRxLock and xTxLock structure members.
#define queueUNLOCKED              ( -1 )
#define queueLOCKED_UNMODIFIED     ( 0 )

// Alternative names for pcTail and pcHead when the queue is used as a mutex.
#define pxMutexHolder              pcTail
#define uxQueueType                pcHead
#define queueQUEUE_IS_MUTEX        NULL

// Semaphores don't store data, so their size is zero.
#define queueSEMAPHORE_QUEUE_ITEM_LENGTH 0
#define queueMUTEX_GIVE_BLOCK_TIME       0

#define queueYIELD_IF_USING_PREEMPTION() portYIELD_WITHIN_API()

// Locks the given queue.
#define prvLockQueue( pxQueue )                                                \
    taskENTER_CRITICAL();                                                      \
    {                                                                          \
        if( ( pxQueue )->xRxLock == queueUNLOCKED )                            \
        {                                                                      \
            ( pxQueue )->xRxLock = queueLOCKED_UNMODIFIED;                     \
        }                                                                      \
        if( ( pxQueue )->xTxLock == queueUNLOCKED )                            \
        {                                                                      \
            ( pxQueue )->xTxLock = queueLOCKED_UNMODIFIED;                     \
        }                                                                      \
    }                                                                          \
    taskEXIT_CRITICAL()

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

// Queue structure. Items are queued by copy, not by reference.
typedef struct QueueDefinition
{
    // Pointer to the beginning of the queue storage area.
    int8_t *pcHead;
    // Pointer to the byte at the end of the queue storage area,
    // which is used as an end marker.
    int8_t *pcTail;
    // Pointer to the next free place in the storage area.
    int8_t *pcWriteTo;
    
    // Save RAM by using a union for two mutually exclusive fields.
    union
    {
        // Pointer to the last place that an item was read from,
        // when the structure is used as a queue.
        int8_t *pcReadFrom;
        // Number of times a recursive mutex was taken,
        // when the structure is used as a mutex.
        UBaseType_t uxRecursiveCallCount;
    } u;
    
    // Prioritised list of tasks that are waiting to write to this queue.
    List_t xTasksWaitingToSend;
    // Prioritised list of tasks that are waiting to read from this queue.
    List_t xTasksWaitingToReceive;
    
    // Number of items currently in the queue.
    volatile UBaseType_t uxMessagesWaiting;
    // Length of the queue, i.e. the number of items (not bytes) it can hold.
    UBaseType_t uxLength;
    // Size of the items that the queue holds.
    UBaseType_t uxItemSize;
    
    // Number of items received (removed) from the queue while it was locked.
    volatile BaseType_t xRxLock;
    // Number of items transmitted (added) to the queue while it was locked.
    volatile BaseType_t xTxLock;
} xQUEUE;

// Redefine the queue name to the new version,
// and keep the old one for backward compatibility.
typedef xQUEUE Queue_t;

// Structure stored withing the queue registry array.
// Allows a name to be assigned to each queue for debugging purposes.
typedef struct QUEUE_REGISTRY_ITEM
{
    // Queue name.
    const char *pcQueueName;
    // Handle for the queue.
    QueueHandle_t xHandle;
} xQueueRegistryItem;

// Redefine the queue registry item name to the new version,
// and keep the old one for backward compatibility.
typedef xQueueRegistryItem QueueRegistryItem_t;

/******************************************************************************
 * Global variable definitions.                                               *
 ******************************************************************************/

// Array of queue registries, useful for debugging.
QueueRegistryItem_t xQueueRegistry[ configQUEUE_REGISTRY_SIZE ];

/******************************************************************************
 * Static function definitions.                                               *
 ******************************************************************************/

// Function for unlocking a queue.
// This function must be called with the scheduler suspended.
static void prvUnlockQueue( Queue_t * const pxQueue )
{
    // The lock counts containt the number of extra data items
    // placed to or removed from the queue while it was locked.
    
    // Empty the receive list.
    taskENTER_CRITICAL();
    {
        // See if data was added to the queue while it was locked.
        while( pxQueue->xTxLock > queueLOCKED_UNMODIFIED )
        {
            // If receive waiting list is not empty remove a task from it.
            if( listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) )
                == pdFALSE )
            {
                if( xTaskRemoveFromEventList(
                    &( pxQueue->xTasksWaitingToReceive )) != pdFALSE );
                {
                    // The task waiting has a higher priority
                    // so record that a context switch is required.
                    vTaskMissedYield();
                }
            }
            else
            {
                break;
            }

            ( pxQueue->xTxLock )--;
        }

        pxQueue->xTxLock = queueUNLOCKED;
    }
    taskEXIT_CRITICAL();

    // Empty the send list.
    taskENTER_CRITICAL();
    {
        while( pxQueue->xRxLock > queueLOCKED_UNMODIFIED )
        {
            if( listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) )
                == pdFALSE )
            {
                if( xTaskRemoveFromEventList(
                    &( pxQueue->xTasksWaitingToSend ) ) != pdFALSE )
                {
                    vTaskMissedYield();
                }

                ( pxQueue->xRxLock )--;
            }
            else
            {
                break;
            }
        }

        pxQueue->xRxLock = queueUNLOCKED;
    }
    taskEXIT_CRITICAL();
}

// Checks whether a queue is empty.
static BaseType_t prvIsQueueEmpty( Queue_t * const pxQueue )
{
    BaseType_t xReturn;
    
    taskENTER_CRITICAL();
    {
        if( pxQueue->uxMessagesWaiting == 0 )
        {
            xReturn = pdTRUE;
        }
        else
        {
            xReturn = pdFALSE;
        }
    }
    taskEXIT_CRITICAL();
    
    return xReturn;
}

// Checks whether a queue is full.
static BaseType_t prvIsQueueFull( Queue_t *const pxQueue )
{
    BaseType_t xReturn;

    taskENTER_CRITICAL();
    {
        if( pxQueue->uxMessagesWaiting == pxQueue->uxLength )
        {
            xReturn = pdTRUE;
        }
        else
        {
            xReturn = pdFALSE;
        }
    }
    taskEXIT_CRITICAL();

    return xReturn;
}

// Copies the given item to the queue.
static void prvCopyDataToQueue( Queue_t * const pxQueue,
    const void *pvItemToQueue, const BaseType_t xPosition )
{
    if( pxQueue->uxItemSize == 0 )
    {
        // Is the queue being used as a mutex?
        if( pxQueue->uxQueueType == queueQUEUE_IS_MUTEX )
        {
            // The mutex is no longer being held
            vTaskPriorityDisinherit( pxQueue->pxMutexHolder );
            pxQueue->pxMutexHolder = NULL;
        }
    }
    else if( xPosition == queueSEND_TO_BACK )
    {
        // Write item to the back of the queue, and move the write pointer.
        memcpy( pxQueue->pcWriteTo, pvItemToQueue, pxQueue->uxItemSize );
        pxQueue->pcWriteTo += pxQueue->uxItemSize;
        if( pxQueue->pcWriteTo >= pxQueue->pcTail )
            pxQueue->pcWriteTo = pxQueue->pcHead;
    }
    else
    {
        // Write item to the front of the queue, and move the write pointer.
        memcpy( pxQueue->u.pcReadFrom, pvItemToQueue, pxQueue->uxItemSize );
        pxQueue->u.pcReadFrom -= pxQueue->uxItemSize;
        if( pxQueue->u.pcReadFrom < pxQueue->pcHead )
            pxQueue->u.pcReadFrom = ( pxQueue->pcTail - pxQueue->uxItemSize );
        
        // Is the item being overwritten?
        if( xPosition == queueOVERWRITE )
        {
            if( pxQueue->uxMessagesWaiting > 0 )
            {
                // Subtract one form item counter,
                // so that the number of items remains correct.
                ( pxQueue->uxMessagesWaiting )--;
            }
        }
    }

    ( pxQueue->uxMessagesWaiting )++;
}

// Copies an item from the queue to the given buffer.
static void prvCopyDataFromQueue( Queue_t * const pxQueue,
    void * const pvBuffer )
{
    if( pxQueue->uxQueueType != queueQUEUE_IS_MUTEX )
    {
        // Move the read pointer, and read the item from the front of the queue.
        pxQueue->u.pcReadFrom += pxQueue->uxItemSize;
        if( pxQueue->u.pcReadFrom >= pxQueue->pcTail )
            pxQueue->u.pcReadFrom = pxQueue->pcHead;
        memcpy( pvBuffer, pxQueue->u.pcReadFrom, pxQueue->uxItemSize );
    }
}

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/

// Generic queue reset.
BaseType_t xQueueGenericReset( QueueHandle_t xQueue, BaseType_t xNewQueue )
{
    Queue_t * const pxQueue = ( Queue_t * ) xQueue;

    configASSERT( pxQueue );

    taskENTER_CRITICAL();
    {
        // Set appropriate values to the fields.
        pxQueue->pcTail
            = pxQueue->pcHead + ( pxQueue->uxLength * pxQueue->uxItemSize );
        pxQueue->uxMessagesWaiting = 0;
        pxQueue->pcWriteTo = pxQueue->pcHead;
        pxQueue->u.pcReadFrom = pxQueue->pcHead
            + ( ( pxQueue->uxLength - 1 ) * pxQueue->uxItemSize );
        pxQueue->xRxLock = queueUNLOCKED;
        pxQueue->xTxLock = queueUNLOCKED;

        if( xNewQueue == pdFALSE )
        {
            // If there are tasks waiting to write to the queue,
            // unblock one of them.
            if( listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) )
                == pdFALSE )
            {
                if( xTaskRemoveFromEventList(
                    &( pxQueue->xTasksWaitingToSend ) ) == pdTRUE )
                {
                    queueYIELD_IF_USING_PREEMPTION();
                }
            }
        }
        else
        {
            // Ensure the event queues start in the correct state.
            vListInitialise( &( pxQueue->xTasksWaitingToSend ) );
            vListInitialise( &( pxQueue->xTasksWaitingToReceive ) );
        }
    }
    taskEXIT_CRITICAL();

    return pdPASS;
}

// Generic queue creation.
QueueHandle_t xQueueGenericCreate( const UBaseType_t uxQueueLength,
    const UBaseType_t uxItemSize, const int8_t ucQueueType )
{
    Queue_t *pxNewQueue;
    UBaseType_t xQueueSizeInBytes;
    QueueHandle_t xReturn = NULL;

    if( uxQueueLength > 0 )
    {
        // Allocate space for the queue.
        pxNewQueue = ( Queue_t * ) pvPortMalloc( sizeof( Queue_t ) );
        if( pxNewQueue != NULL )
        {
            // Calculate size in bytes for the item space.
            // The size is one byte longer for the end marker.
            xQueueSizeInBytes = uxQueueLength * uxItemSize + 1;

            // Allocate queue item space.
            pxNewQueue->pcHead = ( int8_t * ) pvPortMalloc( xQueueSizeInBytes );
            if( pxNewQueue->pcHead != NULL )
            {
                // Initialise the queue members.
                pxNewQueue->uxLength = uxQueueLength;
                pxNewQueue->uxItemSize = uxItemSize;
                
                xQueueGenericReset( pxNewQueue, pdTRUE );

                xReturn = pxNewQueue;
            }
            else
            {
                vPortFree( pxNewQueue, sizeof( Queue_t ) );
            }
        }
    }
    configASSERT( xReturn );

    return xReturn;
}

// Creates a queue that serves as a mutex.
QueueHandle_t xQueueCreateMutex( const int8_t ucQueueType )
{
    Queue_t *pxNewQueue;

    // Allocate space for the queue.
    pxNewQueue = ( Queue_t * ) pvPortMalloc( sizeof( Queue_t ) );
    if( pxNewQueue != NULL )
    {
        // Information required for priority inheritance.
        pxNewQueue->pxMutexHolder = NULL;
        pxNewQueue->uxQueueType = queueQUEUE_IS_MUTEX;

        // No data is contained in a queue if it is used as a mutex.
        pxNewQueue->pcWriteTo = NULL;
        pxNewQueue->u.pcReadFrom = NULL;

        // A mutex has a length of 1, and an item size of 0.
        pxNewQueue->uxMessagesWaiting = 0;
        pxNewQueue->uxLength = 1;
        pxNewQueue->uxItemSize = 0;
        pxNewQueue->xRxLock = queueUNLOCKED;
        pxNewQueue->xTxLock = queueUNLOCKED;

        // Initialise event queues.
        vListInitialise( &( pxNewQueue->xTasksWaitingToSend ) );
        vListInitialise( &( pxNewQueue->xTasksWaitingToReceive ) );

        // Start with the semaphore in the expected state.
        xQueueGenericSend( pxNewQueue, NULL, 0, queueSEND_TO_BACK );
    }

    configASSERT( pxNewQueue );
    return pxNewQueue;
}

// Returns the mutex holder of a queue used as a mutex.
TaskHandle_t xQueueGetMutexHolder( QueueHandle_t xMutex )
{
    void *pxReturn;

    // This function is called by xSemaphoreGetMutexHolder().
    // This is only useful for determining whether the current task
    // the current holder.

    taskENTER_CRITICAL();
    {
        if( ( ( Queue_t * ) xMutex )->uxQueueType == queueQUEUE_IS_MUTEX )
        {
            pxReturn = ( TaskHandle_t ) ( ( Queue_t * ) xMutex )->pxMutexHolder;
        }
    }
    taskEXIT_CRITICAL();

    return pxReturn;
}

// Performs a recursive give of a mutex.
BaseType_t xQueueGiveMutexRecursive( QueueHandle_t xMutex )
{
    BaseType_t xReturn;
    Queue_t * const pxMutex = ( Queue_t * ) xMutex;

    configASSERT( pxMutex );

    if( pxMutex->pxMutexHolder == xTaskGetCurrentTaskHandle() )
    {
        ( pxMutex->u.uxRecursiveCallCount )--;

        if( pxMutex->u.uxRecursiveCallCount == 0 )
        {
            xQueueGenericSend(
                pxMutex, NULL, queueMUTEX_GIVE_BLOCK_TIME, queueSEND_TO_BACK );
        }

        xReturn = pdPASS;
    }
    else
    {
        // Current task is not the holder and cannot give the mutex.
        xReturn = pdFAIL;
    }

    return xReturn;
}

// Performs a recursive take of a mutex.
BaseType_t xQueueTakeMutexRecursive( QueueHandle_t xMutex,
    TickType_t xTicksToWait )
{
    BaseType_t xReturn;
    Queue_t * const pxMutex = ( Queue_t * ) xMutex;

    configASSERT( pxMutex );

    if( pxMutex->pxMutexHolder == xTaskGetCurrentTaskHandle() )
    {
        // Current task is the mutex holder, increment recursive call counter.
        ( pxMutex->u.uxRecursiveCallCount )++;
        xReturn = pdPASS;
    }
    else
    {
         // Current task isn't the mutex holder,
         // call the generic receive routine, which might block us.
         xReturn = xQueueGenericReceive( pxMutex, NULL, xTicksToWait, pdFALSE );

         // Only take mutex (and increment the counter)
         // if we successfully received from queue.
         if( xReturn == pdPASS )
         {
             ( pxMutex->u.uxRecursiveCallCount )++;
         }
    }

    return xReturn;
}

// Function for creating a queue that serves as a semaphore.
QueueHandle_t xQueueCreateCountingSemaphore( const UBaseType_t uxMaxCount,
    const UBaseType_t uxInitialCount )
{
    QueueHandle_t xHandle;

    configASSERT( uxMaxCount != 0 );
    configASSERT( uxInitialCount <= uxMaxCount );

    // Create queue to use as semaphore.
    xHandle = xQueueGenericCreate( uxMaxCount, queueSEMAPHORE_QUEUE_ITEM_LENGTH,
        queueQUEUE_TYPE_COUNTING_SEMAPHORE );

    if( xHandle != NULL )
    {
        // Set number of messages to be equal to the initial count,
        // this is okay since item length is equal to 0.
        ( ( Queue_t * ) xHandle )->uxMessagesWaiting = uxInitialCount;
    }

    configASSERT( xHandle );
    return xHandle;
}

// Sends an item to the designated place in the queue.
BaseType_t xQueueGenericSend( QueueHandle_t xQueue,
    const void * const pvItemToQueue,
    TickType_t xTicksToWait,
    const BaseType_t xCopyPosition
    )
{
    BaseType_t xEntryTimeSet = pdFALSE;
    TimeOut_t xTimeOut;
    Queue_t * const pxQueue = ( Queue_t * ) xQueue;

    // Error - Queue handle is null.
    configASSERT( pxQueue );
    // Error - Item to send to the queue is null and item size isn't zero,
    // or vice-versa.
    configASSERT( ( pvItemToQueue == NULL ) == ( pxQueue->uxItemSize == 0 ) );
    // Error - Trying to overwrite while queue size is not 1.
    configASSERT( ( xCopyPosition != queueOVERWRITE )
        || ( pxQueue->uxLength == 1 ) );
    // Error - Trying to wait (for more than zero ticks),
    // while scheduler is suspended.
    configASSERT( ( xTaskGetSchedulerState() != taskSCHEDULER_SUSPENDED )
        || ( xTicksToWait == 0 ) );
    
    // There are multiple exit points from this loop.
    while( 1 )
    {
        taskENTER_CRITICAL();
        {
            // Is there available space in the queue?
            // In case of overwrite, it doesn't matter.
            if( ( pxQueue->uxMessagesWaiting < pxQueue->uxLength )
                || ( xCopyPosition == queueOVERWRITE ) )
            {
                // Send data to queue.
                prvCopyDataToQueue( pxQueue, pvItemToQueue, xCopyPosition );

                // Is there a task waiting for data to arrive to the queue?
                if( listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToReceive ) )
                    == pdFALSE )
                {
                    if( xTaskRemoveFromEventList(
                        &( pxQueue->xTasksWaitingToReceive ) ) == pdTRUE)
                    {
                        // The unblocked task has higher priority.
                        queueYIELD_IF_USING_PREEMPTION();
                    }
                }

                taskEXIT_CRITICAL();
                
                return pdPASS;
            }
            else
            {
                if( xTicksToWait == 0 )
                {
                    // The queue is full and block time is zero, so leave now.
                    taskEXIT_CRITICAL();
                    return errQUEUE_FULL;
                }
                else if( xEntryTimeSet == pdFALSE )
                {
                    // The queue is full and block time is specified.
                    vTaskSetTimeOutState( &xTimeOut );
                    xEntryTimeSet = pdTRUE;
                }
            }
        }
        taskEXIT_CRITICAL();
        
        // Prevent interrupts and other tasks from accessing the queue.
        vTaskSuspendAll();
        prvLockQueue( pxQueue );
        
        // Update timeout state and check if it is expired yet.
        if( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) == pdFALSE )
        {
            // Timeout hasn't expired.
            if( prvIsQueueFull( pxQueue ) != pdFALSE )
            {
                // The queue is full.
                
                // Place task on waiting to send list.
                vTaskPlaceOnEventList(
                    &( pxQueue->xTasksWaitingToSend ), xTicksToWait );

                // Unlock the queue, if an interrupt removes the task
                // from the event list, it will go to the pending ready list.
                prvUnlockQueue( pxQueue );
                
                // Resuming the scheduler will move the tasks
                // from the pending ready list to the ready lists,
                // so this task may be in the ready list
                // and not yield in xTaskResumeAll.
                if( xTaskResumeAll() == pdFALSE )
                {
                    portYIELD_WITHIN_API();
                }
            }
            else
            {
                // Queue isn't full, try again.
                prvUnlockQueue( pxQueue );
                xTaskResumeAll();
            }
        }
        else
        {
            // The timeout has expired.
            
            prvUnlockQueue( pxQueue );
            xTaskResumeAll();
            
            return errQUEUE_FULL;
        }
    }
}

// Sends an item to the designated place in the queue. 
// Can be called from an ISR.
BaseType_t xQueueGenericSendFromISR( QueueHandle_t xQueue,
    const void * const pvItemToQueue,
    BaseType_t * const pxHigherPriorityTaskWoken,
    const BaseType_t xCopyPosition
    )
{
    BaseType_t xReturn;
    UBaseType_t uxSavedInterruptStatus;
    Queue_t * const pxQueue = ( Queue_t * ) xQueue;
    
    // Error - Queue handle is null.
    configASSERT( pxQueue );
    // Error - Item to send to the queue is null and item size isn't zero,
    // or vice-versa.
    configASSERT( ( pvItemToQueue == NULL ) == ( pxQueue->uxItemSize == 0 ) );
    // Error - Trying to overwrite while queue size is not 1.
    configASSERT( ( xCopyPosition != queueOVERWRITE )
        || ( pxQueue->uxLength == 1 ) );
        
    uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        // Is there available space in the queue?
        // In case of overwrite, it doesn't matter.
        if( ( pxQueue->uxMessagesWaiting < pxQueue->uxLength )
            || ( xCopyPosition == queueOVERWRITE ) )
        {
            // Send data to the queue.
            prvCopyDataToQueue( pxQueue, pvItemToQueue, xCopyPosition );
            
            // Event list is not altered if the queue is locked.
            if( pxQueue->xTxLock == queueUNLOCKED )
            {
                if( listLIST_IS_EMPTY( 
                    &( pxQueue->xTasksWaitingToReceive ) ) == pdFALSE )
                {
                    if( xTaskRemoveFromEventList(
                        &( pxQueue->xTasksWaitingToReceive ) ) != pdFALSE )
                    {
                        // The task waiting has a higher priority,
                        // signal for a context switch.
                        if( pxHigherPriorityTaskWoken != NULL )
                        {
                            *pxHigherPriorityTaskWoken = pdTRUE;
                        }
                    }
                }
            }
            else
            {
                // Increment the lock count so the task that unlocks it
                // knows that data was posted.
                ( pxQueue->xTxLock )++;
            }
            
            xReturn = pdPASS;
        }
        else
        {
            // No space in the queue.
            xReturn = errQUEUE_FULL;
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );
    
    return xReturn;
}

// Function for receiving an item or taking a peek at the queue.
BaseType_t xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer,
    TickType_t xTicksToWait, const BaseType_t xJustPeeking )
{
    BaseType_t xEntryTimeSet = pdFALSE;
    TimeOut_t xTimeOut;
    int8_t *pcOriginalReadPosition;
    Queue_t * const pxQueue = ( Queue_t * ) xQueue;

    // Error - Queue handle is null.
    configASSERT( pxQueue );
    // Error - Buffer is null and item size isn't zero, or vice-versa.
    configASSERT( ( pvBuffer == NULL ) == ( pxQueue->uxItemSize == 0 ) );
    // Error - Trying to wait (for more than zero ticks),
    // while scheduler is suspended.
    configASSERT( ( xTaskGetSchedulerState() != taskSCHEDULER_SUSPENDED )
        || ( xTicksToWait == 0 ) );
    
    // There are multiple exit points from this loop.
    while( 1 )
    {
        taskENTER_CRITICAL();
        {
            // Is there data in the queue?
            if( pxQueue->uxMessagesWaiting > 0 )
            {
                // Remember the read position in case of peek.
                pcOriginalReadPosition = pxQueue->u.pcReadFrom;
                
                prvCopyDataFromQueue( pxQueue, pvBuffer );
                
                if( xJustPeeking == pdFALSE )
                {
                    // Decrement data counter.
                    ( pxQueue->uxMessagesWaiting )--;
                    
                    if( pxQueue->uxQueueType == queueQUEUE_IS_MUTEX )
                    {
                        // Remember the current task for priority inheritance.
                        pxQueue->pxMutexHolder
                            = ( int8_t * ) xTaskGetCurrentTaskHandle();
                    }
                    
                    // If there is a task waiting to send, unblock it.
                    if( listLIST_IS_EMPTY(
                        &( pxQueue->xTasksWaitingToSend ) ) == pdFALSE )
                    {
                        if( xTaskRemoveFromEventList(
                            &( pxQueue->xTasksWaitingToSend ) ) == pdTRUE )
                            {
                                queueYIELD_IF_USING_PREEMPTION();
                            }
                    }
                }
                else
                {
                    // Data isn't being removed,
                    // so restore the original read position.
                    pxQueue->u.pcReadFrom = pcOriginalReadPosition;
                    
                    // Data is being left in the queue,
                    // so unblock a task that might be waiting to receive it.
                    if( listLIST_IS_EMPTY(
                        &( pxQueue->xTasksWaitingToReceive ) ) == pdFALSE )
                    {
                        if( xTaskRemoveFromEventList(
                            &( pxQueue->xTasksWaitingToReceive ) ) != pdFALSE )
                        {
                            // The task waiting has a higher priority.
                            queueYIELD_IF_USING_PREEMPTION();
                        }
                    }
                }
                
                taskEXIT_CRITICAL();
                return pdPASS;
            }
            else
            {
                // The queue is empty.
                
                if( xTicksToWait == 0 )
                {
                    // Queue is empty and there is no wait time, so leave now.
                    taskEXIT_CRITICAL();
                    return errQUEUE_EMPTY;
                }
                else if( xEntryTimeSet == pdFALSE )
                {
                    // Queue is empty and block time is specified.
                    vTaskSetTimeOutState( &xTimeOut );
                    xEntryTimeSet = pdTRUE;
                }
            }
        }
        taskEXIT_CRITICAL();
        
        // Prevent interrupts and other tasks from accessing the queue.
        vTaskSuspendAll();
        prvLockQueue( pxQueue );
        
        // Update timeout state and check if it is expired yet.
        if( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) == pdFALSE )
        {
            // Timeout hasn't expired.
            if( prvIsQueueEmpty( pxQueue ) != pdFALSE )
            {
                // Queue is empty.

                // Inherit priority if task is used as a mutex.
                if( pxQueue->uxQueueType == queueQUEUE_IS_MUTEX )
                {
                    taskENTER_CRITICAL();
                    {
                        vTaskPriorityInherit( pxQueue->pxMutexHolder );
                    }
                    taskEXIT_CRITICAL();
                }

                // Place task on waiting to receive list.
                vTaskPlaceOnEventList(
                    &( pxQueue->xTasksWaitingToReceive ), xTicksToWait );

                // Unlock the queue, if an interrupt removes the task
                // from the event list, it will go to the pending ready list.
                prvUnlockQueue( pxQueue );

                // Resuming the scheduler will move the tasks
                // from the pending ready list to the ready lists,
                // so this task may be in the ready list
                // and not yield in xTaskResumeAll.
                if( xTaskResumeAll() == pdFALSE )
                {
                    portYIELD_WITHIN_API();
                }
            }
            else
            {
                // Queue isn't empty, try again.
                prvUnlockQueue( pxQueue );
                xTaskResumeAll();
            }
        }
        else
        {
            // Timeout has expired.

            prvUnlockQueue( pxQueue );
            xTaskResumeAll();

            return errQUEUE_FULL;
        }
    }
}

// Receives an item from a queue. Can be called from an ISR.
BaseType_t xQueueReceiveFromISR( QueueHandle_t xQueue, void * const pvBuffer,
    BaseType_t * const pxHigherPriorityTaskWoken )
{
    BaseType_t xReturn;
    UBaseType_t uxSavedInterruptStatus;
    Queue_t * const pxQueue = ( Queue_t * ) xQueue;

    // Error - Queue handle is null.
    configASSERT( pxQueue );
    // Error - Buffer is null and item size isn't zero,
    // or vice-versa.
    configASSERT( ( pvBuffer == NULL ) == ( pxQueue->uxItemSize == 0 ) );

    uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        // Is there data in the queue?
        if( pxQueue->uxMessagesWaiting > 0 )
        {
            // Copy data from the queue
            prvCopyDataFromQueue( pxQueue, pvBuffer );
            ( pxQueue->uxMessagesWaiting )--;

            // Event list is not altered if the queue is locked.
            if( pxQueue->xRxLock == queueUNLOCKED )
            {
                if( listLIST_IS_EMPTY(
                    &( pxQueue->xTasksWaitingToSend ) ) == pdFALSE )
                {
                    if( xTaskRemoveFromEventList(
                        &( pxQueue->xTasksWaitingToSend ) ) != pdFALSE )
                    {
                        // The task waiting has a higher priority,
                        // signal for a context switch.
                        if( pxHigherPriorityTaskWoken != NULL )
                        {
                            *pxHigherPriorityTaskWoken = pdTRUE;
                        }
                    }
                }
            }
            else
            {
                // Increment the lock count so the task that unlocks it
                // knows that data was posted.
                ( pxQueue->xRxLock )++;
            }

            xReturn = pdPASS;
        }
        else
        {
            // Queue is empty.
            xReturn = pdFAIL;
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );

    return xReturn;
}

// Takes a peek at the top of a queue. Can be called form an ISR.
BaseType_t xQueuePeekFromISR( QueueHandle_t xQueue, void * const pvBuffer )
{
    BaseType_t xReturn;
    UBaseType_t uxSavedInterruptStatus;
    int8_t *pcOriginalReadPosition;
    Queue_t * const pxQueue = ( Queue_t * ) xQueue;

    // Error - Queue handle is null.
    configASSERT( pxQueue );
    // Error - Buffer is null and item size isn't zero,
    // or vice-versa.
    configASSERT( ( pvBuffer == NULL ) == ( pxQueue->uxItemSize == 0 ) );

    uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        // Check if there is data available.
        if( pxQueue->uxMessagesWaiting > 0 )
        {
            // Remember the read position so it can be reset.
            pcOriginalReadPosition = pxQueue->u.pcReadFrom;
            prvCopyDataFromQueue( pxQueue, pvBuffer );
            pxQueue->u.pcReadFrom = pcOriginalReadPosition;

            xReturn = pdPASS;
        }
        else
        {
            xReturn = pdFAIL;
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );

    return xReturn;
}

// Returns the number of messages waiting on a queue.
UBaseType_t uxQueueMessagesWaiting( const QueueHandle_t pxQueue )
{
    UBaseType_t uxReturn;

    // Error - Queue handle is null.
    configASSERT( pxQueue );

    taskENTER_CRITICAL();
    {
        uxReturn = ( ( Queue_t * ) pxQueue )->uxMessagesWaiting;
    }
    taskEXIT_CRITICAL();

    return uxReturn;
}

// Returns the number of available spaces in a queue.
UBaseType_t uxQueueSpacesAvailable( const QueueHandle_t xQueue )
{
    UBaseType_t uxReturn;
    Queue_t *pxQueue;

    pxQueue = ( Queue_t * ) xQueue;

    // Error - Queue handle is null.
    configASSERT( pxQueue );

    taskENTER_CRITICAL();
    {
        uxReturn = pxQueue->uxLength - pxQueue->uxMessagesWaiting;
    }
    taskEXIT_CRITICAL();

    return uxReturn;
}

// Returns the number of messages waiting on a queue. Can be called from an ISR.
UBaseType_t uxQueueMessagesWaitingFromISR( const QueueHandle_t pxQueue )
{
    UBaseType_t uxReturn;

    // Error - Queue handle is null.
    configASSERT( pxQueue );

    uxReturn = ( ( Queue_t * ) pxQueue )->uxMessagesWaiting;

    return uxReturn;
}

// Deletes a queue.
void vQueueDelete( QueueHandle_t xQueue )
{
    Queue_t * const pxQueue = ( Queue_t * ) xQueue;
    
    // Error - Queue handle is null.
    configASSERT( pxQueue );
        
    vQueueUnregisterQueue( pxQueue );
    
    // Free the queue item space.
    if( pxQueue->pcHead != NULL )
    {
        vPortFree( pxQueue->pcHead,
            pxQueue->uxLength * pxQueue->uxItemSize + 1 );
    }
    // Free the queue itself.
    vPortFree( pxQueue, sizeof( Queue_t ) );
}

// Checks whether a queue is empty. Can be called form an ISR.
BaseType_t xQueueIsQueueEmptyFromISR( const QueueHandle_t pxQueue )
{
    BaseType_t xReturn;

    // Error - Queue handle is null.
    configASSERT( pxQueue );

    if( ( ( Queue_t * ) pxQueue )->uxMessagesWaiting == 0 )
    {
        xReturn = pdTRUE;
    }
    else
    {
        xReturn = pdFALSE;
    }

    return xReturn;
}

// Checks whether a queue is full. Can be called from an ISR.
BaseType_t xQueueIsQueueFullFromISR( const QueueHandle_t pxQueue )
{
    BaseType_t xReturn;

    // Error - Queue handle is null.
    configASSERT( pxQueue );

    if( ( ( Queue_t * ) pxQueue )->uxMessagesWaiting
        == ( ( Queue_t * ) pxQueue )->uxLength )
    {
        xReturn = pdTRUE;
    }
    else
    {
        xReturn = pdFALSE;
    }

    return xReturn;
}

// Adds a queue to the new registry.
void vQueueAddToRegistry( QueueHandle_t xQueue, const char *pcQueueName )
{
    UBaseType_t ux;
    
    // See if there is an empty space in the registry. Its name will be null.
    for( ux = 0; ux < configQUEUE_REGISTRY_SIZE; ux++ )
    {
        if( xQueueRegistry[ ux ].pcQueueName == NULL )
        {
            // Store the information on this queue.
            xQueueRegistry[ ux ].pcQueueName = pcQueueName;
            xQueueRegistry[ ux ].xHandle = xQueue;
            
            break;
        }
    }
}

// Removes a queue from the queue registry.
void vQueueUnregisterQueue( QueueHandle_t xQueue )
{
    UBaseType_t ux;

    // See if one of the handles in the registry matches the queue handle.
    for( ux = 0; ux < configQUEUE_REGISTRY_SIZE; ux++  )
    {
        if( xQueueRegistry[ ux ].xHandle == xQueue )
        {
            // Set queue name to null.
            xQueueRegistry[ ux ].pcQueueName = NULL;
            break;
        }
    }
}

// Waits for a message in a queue - restricted version.
void vQueueWaitForMessageRestricted( QueueHandle_t xQueue,
    TickType_t xTicksToWait )
{
    Queue_t * const pxQueue = ( Queue_t * ) xQueue;

    // This function should not be called by application code.
    // It is designed for use by kernel code, and should be called
    // with the scheduler locked and not from a critical section.

    // Only do anything if there are no messages in the queue. 
    // This function will not actually cause the task to block,
    // just place it on a blocked list.

    prvLockQueue( pxQueue );
    if( pxQueue->uxMessagesWaiting == 0 )
    {
        // Queue is empty, block for the specified time.
        vTaskPlaceOnEventListRestricted(
            &( pxQueue->xTasksWaitingToReceive ), xTicksToWait );
    }
    prvUnlockQueue( pxQueue );
}