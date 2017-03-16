// File: timers.c

// Implementation of the timer functionalities.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

#define tmrNO_DELAY 0

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/
 
// Structure which represents a timer.
typedef struct tmrTimerControl
{
    // Name of the timer, used for debug only.
    const char              *pcTimerName;
    // List item used for event management.
    ListItem_t              xTimerListItem;
    // Timer period duration counted in ticks.
    TickType_t              xTimerPeriodInTicks;
    // Indicator of whether the timer should
    // automatically restart once expired (pdTRUE) or not (pdFALSE).
    UBaseType_t             uxAutoReload;
    // An ID to identify the timer by.
    void                    *pvTimerID;
    // Function that is called when the timer expires.
    TimerCallbackFunction_t pxCallbackFunction;
} Timer_t;
 
// Structure of messages that manipulate a software timer.
typedef struct tmrTimerParameters
{
    // Optional value used for a subset of commands.
    TickType_t xMessageValue;
    // Timer to which the command is applied.
    Timer_t    *pxTimer;
} TimerParameter_t;

// Structure of messages that that request the execution of a callback function.
typedef struct tmrCallbackParameters
{
    // Callback function to execute.
    PendedFunction_t pxCallbackFunction;
    // First parameter of the callback function.
    void             *pvParameter1;
    // Second parameter of the callback function.
    UBaseType_t      ulParameter2;
} CallbackParameters_t;

// Structure that contains a message of a specific type,
// and an identifier which determines the type.
typedef struct tmrTimerQueueMessage
{
    // Type of command being sent.
    BaseType_t xMessageID;
    // Union of two parameter types.
    union
    {
        // Manipulation type parameters.
        TimerParameter_t     xTimerParameters;
        // Execution type parameters.
        CallbackParameters_t xCallbackParameters;
    } u;
} DaemonTaskMessage_t;

/******************************************************************************
 * Static variable definitions.                                               *
 ******************************************************************************/

// Lists for active timers, ordered by expire time.
static List_t xActiveTimerList1;
static List_t xActiveTimerList2;
static List_t *pxCurrentTimerList;
static List_t *pxOverflowTimerList;

// Queue that is used for timer commands.
static QueueHandle_t xTimerQueue = NULL;

/******************************************************************************
 * Static function definitions.                                               *
 ******************************************************************************/

// Checks if active timers lists and queue have been initialised.
static void prvCheckForValidListAndQueue()
{
    taskENTER_CRITICAL();
    {
        if( xTimerQueue == NULL )
        {
            // Initialise active timers lists.
            vListInitialise( &xActiveTimerList1 );
            vListInitialise( &xActiveTimerList2 );
            pxCurrentTimerList = &xActiveTimerList1;
            pxOverflowTimerList = &xActiveTimerList2;
            
            // Initialise timer queue.
            xTimerQueue = xQueueCreate(
                configTIMER_QUEUE_LENGTH, sizeof( DaemonTaskMessage_t ) );
            configASSERT( xTimerQueue );
            
            // Add timer queue to registry.
            vQueueAddToRegistry( xTimerQueue, "TmrQ" );
        }
    }
    taskEXIT_CRITICAL();
}

// Insert a timer into the appropriate timer list,
// based on whether it will overflow or not.
static BaseType_t prvInsertTimerInActiveList( Timer_t * const pxTimer,
    const TickType_t xNextExpiryTime,
    const TickType_t xTimeNow,
    const TickType_t xCommandTime
    )
{
    BaseType_t xProcessTimerNow = pdFALSE;

    // Set list item value and owner.
    listSET_LIST_ITEM_VALUE( &( pxTimer->xTimerListItem ), xNextExpiryTime );
    listSET_LIST_ITEM_OWNER( &( pxTimer->xTimerListItem ), pxTimer );

    if( xNextExpiryTime <= xTimeNow )
    {
        // Has enough time passed between when the command was issued and now?
        if( ( xTimeNow - xCommandTime ) >= pxTimer->xTimerPeriodInTicks )
        {
            // Enough time has passed, the command should be processed now.
            xProcessTimerNow = pdTRUE;
        }
        else
        {
            vListInsert( pxOverflowTimerList, &( pxTimer->xTimerListItem ) );
        }
    }
    else
    {
        if( ( xTimeNow < xCommandTime ) && ( xNextExpiryTime >= xCommandTime ) )
        {
            // Timer has overflowed, but the expiry time has not,
            // so the timer must have passed it
            // which means the command should be processed now.
            xProcessTimerNow = pdTRUE;
        }
        else
        {
            vListInsert( pxCurrentTimerList, &( pxTimer->xTimerListItem ) );
        }
    }

    return xProcessTimerNow;
}

// Processes an expired timer.
static void prvProcessExpiredTimer( const TickType_t xNextExpireTime,
    const TickType_t xTimeNow )
{
    BaseType_t xResult;
    Timer_t * const pxTimer
        = ( Timer_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxCurrentTimerList );

    // Remove the timer from the list of active timers.
    uxListRemove( &( pxTimer->xTimerListItem ) );

    // If the timer is auto reload, calculate its next expiry time
    // and place it in the appropriate list.
    if( pxTimer->uxAutoReload == pdTRUE )
    {
        // Insert the timer to the list. If it has expired,
        // it should be put into the timer queue again.
        if( prvInsertTimerInActiveList( pxTimer,
            ( xNextExpireTime + pxTimer->xTimerPeriodInTicks ),
            xTimeNow,
            xNextExpireTime ) == pdTRUE )
        {
            xResult = xTimerGenericCommand( pxTimer,
                tmrCOMMAND_START_DONT_TRACE,
                xNextExpireTime,
                NULL,
                tmrNO_DELAY );
            configASSERT( xResult );
        }
    }

    // Call the timer's callback function.
    pxTimer->pxCallbackFunction( ( TimerHandle_t ) pxTimer );
}

// Function for switching the active and overflowed timer lists.
static void prvSwitchTimerLists()
{
    TickType_t xNextExpireTime, xReloadTime;
    List_t *pxTemp;
    Timer_t *pxTimer;
    BaseType_t xResult;
    
    // Tick count has overflowed and the timer lists must be switched.
    // If there are any timers in the current timer lists,
    // they must have expired and should be processed.
    while( listLIST_IS_EMPTY( pxCurrentTimerList ) == pdFALSE )
    {
        xNextExpireTime
            = listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxCurrentTimerList );

        // Remove the timer from the list.
        pxTimer
            = ( Timer_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxCurrentTimerList );
        uxListRemove( &( pxTimer->xTimerListItem ) );
        
        // Execute the callback, then send the command to restart the timer
        // if it is an auto-reload timer. It cannot be restarted here
        // since the lists haven't been switched yet.
        pxTimer->pxCallbackFunction( pxTimer );
        
        if( pxTimer->uxAutoReload == pdTRUE )
        {
            // Calculate the reload value.
            xReloadTime = ( xNextExpireTime + pxTimer->xTimerPeriodInTicks );
            if( xReloadTime > xNextExpireTime )
            {
                // The value hasn't overflowed so the timer
                // is still in the current list and should be reinserted
                // so that it is processed later in this loop.
                listSET_LIST_ITEM_VALUE(
                    &( pxTimer->xTimerListItem ), xReloadTime );
                listSET_LIST_ITEM_OWNER(
                    &( pxTimer->xTimerListItem ), pxTimer );
                vListInsert( pxCurrentTimerList, &( pxTimer->xTimerListItem ) );
            }
            else
            {
                // The value has overflowed so a command should be sent
                // to restart the timer after the lists have been swapped.
                xResult = xTimerGenericCommand( pxTimer,
                    tmrCOMMAND_START_DONT_TRACE,
                    xNextExpireTime,
                    NULL,
                    tmrNO_DELAY );
                configASSERT( xResult );
            }
        }
    }
    
    // Swap the timer lists.
    pxTemp = pxCurrentTimerList;
    pxCurrentTimerList = pxOverflowTimerList;
    pxOverflowTimerList = pxTemp;
}

// Function for sampling the current time.
static TickType_t prvSampleTimeNow(
    BaseType_t * const pxTimerListsWereSwitched )
{
    TickType_t xTimeNow;
    static TickType_t xLastTime = 0;

    xTimeNow = xTaskGetTickCount();

    if( xTimeNow < xLastTime )
    {
        // Timer lists should be switched.
        prvSwitchTimerLists();
        *pxTimerListsWereSwitched = pdTRUE;
    }
    else
    {
        // Timer lists shouldn't be switched.
        *pxTimerListsWereSwitched = pdFALSE;
    }

    xLastTime = xTimeNow;

    return xTimeNow;
}

// Processes commands received via the timer queue.
static void prvProcessReceivedCommands()
{
    DaemonTaskMessage_t xMessage;
    Timer_t             *pxTimer;
    BaseType_t          xTimerListsWereSwitched, xResult;
    TickType_t          xTimeNow;

    while( xQueueReceive( xTimerQueue, &xMessage, tmrNO_DELAY ) != pdFAIL )
    {
        if( xMessage.xMessageID < 0 )
        {
            // Negative commands are pended function calls.

            // Get the callback parameters.
            const CallbackParameters_t * const pxCallback
                = &( xMessage.u.xCallbackParameters );
            configASSERT( pxCallback );

            // Call the function.
            pxCallback->pxCallbackFunction(
                pxCallback->pvParameter1, pxCallback->ulParameter2 );
        }
        else
        {
            // Positive commands are timer manipulation commands.

            // Get the command parameters.
            pxTimer = xMessage.u.xTimerParameters.pxTimer;

            // Is the timer in a list?
            if( listIS_CONTAINED_WITHIN( NULL, &( pxTimer->xTimerListItem ) )
                == pdFALSE )
            {
                // Remove timer from the list.
                uxListRemove( &( pxTimer->xTimerListItem ) );
            }

            // This call must be made after a message is received;
            // otherwise it is possible that a task of higher priority
            // could add a message that is ahead of the measured time.
            xTimeNow = prvSampleTimeNow( &xTimerListsWereSwitched );

            switch( xMessage.xMessageID )
            {
                case tmrCOMMAND_START:
                case tmrCOMMAND_START_FROM_ISR:
                case tmrCOMMAND_RESET:
                case tmrCOMMAND_RESET_FROM_ISR:
                case tmrCOMMAND_START_DONT_TRACE:
                    // Start or restart a timer.
                    if( prvInsertTimerInActiveList( pxTimer,
                        xMessage.u.xTimerParameters.xMessageValue
                            + pxTimer->xTimerPeriodInTicks,
                        xTimeNow,
                        xMessage.u.xTimerParameters.xMessageValue ) == pdTRUE )
                    {
                        // The timer expired before it was added
                        // to the appropriate list. Process it now.
                        pxTimer->pxCallbackFunction(
                            ( TimerHandle_t ) pxTimer );

                        if( pxTimer->uxAutoReload == pdTRUE )
                        {
                            xResult = xTimerGenericCommand( pxTimer,
                                tmrCOMMAND_START_DONT_TRACE,
                                xMessage.u.xTimerParameters.xMessageValue
                                    + pxTimer->xTimerPeriodInTicks,
                                NULL,
                                tmrNO_DELAY );
                            configASSERT( xResult );
                        }
                    }
                    break;

                case tmrCOMMAND_STOP :
                case tmrCOMMAND_STOP_FROM_ISR :
                    // The timer has already been removed from the active list.
                    break;

                case tmrCOMMAND_CHANGE_PERIOD :
                case tmrCOMMAND_CHANGE_PERIOD_FROM_ISR :
                    pxTimer->xTimerPeriodInTicks
                        = xMessage.u.xTimerParameters.xMessageValue;
                    configASSERT( ( pxTimer->xTimerPeriodInTicks > 0 ) );

                    // Command time is set to the current one,
                    // and the expiry time is determined by the new period.
                    prvInsertTimerInActiveList( pxTimer,
                        ( xTimeNow + pxTimer->xTimerPeriodInTicks ),
                        xTimeNow,
                        xTimeNow );
                    break;

                case tmrCOMMAND_DELETE :
                    // The timer has already been removed from the active list.
                    // Just free the memory.
                    vPortFree( pxTimer, sizeof( Timer_t ) );
                    break;

                default :
                    // Should never reach here.
                    break;
            }
        }
    }
}

// Returns the next time at which the timer task should unblock.
static TickType_t prvGetNextExpireTime( BaseType_t * const pxListWasEmpty )
{
    TickType_t xNextExpireTime;
    
    // The timer list is in non-descending order,
    // so the head of the list should contain the next expire time.
    *pxListWasEmpty = listLIST_IS_EMPTY( pxCurrentTimerList );
    if( *pxListWasEmpty == pdFALSE )
    {
        xNextExpireTime
            = listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxCurrentTimerList );
    }
    else
    {
        // If the list is empty, set the expire time to 0,
        // so that the timer task wakes up on the next tick overflow.
        xNextExpireTime = 0;
    }
    
    return xNextExpireTime;
}

// Decides whether a timer should be processed, or this task should be blocked.
static void prvProcessTimerOrBlockTask( const TickType_t xNextExpireTime,
    const BaseType_t xListWasEmpty )
{
    TickType_t xTimeNow;
    BaseType_t xTimerListsWereSwitched;
    
    vTaskSuspendAll();
    {
        // Obtain the current time. If the lists were switched
        // all the timers that remained in the list will have been processed.
        xTimeNow = prvSampleTimeNow( &xTimerListsWereSwitched );
        if( xTimerListsWereSwitched == pdFALSE )
        {
            // The tick count has not overflowed. Has the timer expired?
            if( ( xListWasEmpty == pdFALSE )
                && ( xNextExpireTime <= xTimeNow ) )
            {
                xTaskResumeAll();
                prvProcessExpiredTimer( xNextExpireTime, xTimeNow );
            }
            else
            {
                // Tick count has not overflowed, and the next expire time
                // has not been reached. This task should block and wait
                // for the next expire time or a new command.
                vQueueWaitForMessageRestricted( xTimerQueue,
                    ( xNextExpireTime - xTimeNow ) );

                if( xTaskResumeAll() == pdFALSE )
                {
                    portYIELD_WITHIN_API();
                }
            }
        }
        else
        {
            xTaskResumeAll();
        }
    }
}

// Function for the task that controls timer functionality.
static void prvTimerTask( void *pvParameters )
{
    TickType_t xNextExpireTime;
    BaseType_t xListWasEmpty;

    while( 1 )
    {
        // Obtain the time at which the task should wake.
        xNextExpireTime = prvGetNextExpireTime( &xListWasEmpty );

        // If a timer has expired, process it. Otherwise block this task
        // until a timer expires or a command is received.
        prvProcessTimerOrBlockTask( xNextExpireTime, xListWasEmpty );

        // Empty the command queue.
        prvProcessReceivedCommands();
    }
}

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/

// Creates the timer task. To be used in the scheduler initialisation function.
BaseType_t xTimerCreateTimerTask()
{
    BaseType_t xReturn = pdFAIL;

    // Check if timer lists and queue have been initialised.
    prvCheckForValidListAndQueue();

    if( xTimerQueue != NULL )
    {
        // Create the timer task without storing its handle.
        xReturn = xTaskCreate( ( TaskFunction_t ) prvTimerTask,
            "Tmr Svc",
            configTIMER_TASK_STACK_DEPTH,
            NULL,
            configTIMER_TASK_PRIORITY,
            NULL );
    }

    configASSERT( xReturn );
    return xReturn;
}

// Creates a timer with the given parameters, including the callback function.
TimerHandle_t xTimerCreate( const char * const pcTimerName,
    const TickType_t xTimerPeriodInTicks,
    const UBaseType_t uxAutoReload,
    void * const pvTimerID,
    TimerCallbackFunction_t pxCallbackFunction
    )
{
    Timer_t *pxNewTimer;

    // Error - Timer period is less than or equal to zero.
    if( xTimerPeriodInTicks <= 0 )
    {
        pxNewTimer = NULL;
    }
    else
    {
        // Allocate timer structure.
        pxNewTimer = ( Timer_t * ) pvPortMalloc( sizeof( Timer_t ) );
        if( pxNewTimer != NULL )
        {
            // Ensure that timer lists and queue have been initialised.
            prvCheckForValidListAndQueue();

            // Initialise the timer structure members.
            pxNewTimer->pcTimerName = pcTimerName;
            pxNewTimer->xTimerPeriodInTicks = xTimerPeriodInTicks;
            pxNewTimer->uxAutoReload = uxAutoReload;
            pxNewTimer->pvTimerID = pvTimerID;
            pxNewTimer->pxCallbackFunction = pxCallbackFunction;
            vListInitialiseItem( &( pxNewTimer->xTimerListItem ) );
        }
    }

    /* 0 is not a valid value for xTimerPeriodInTicks. */
    configASSERT( ( xTimerPeriodInTicks > 0 ) );

    return ( TimerHandle_t ) pxNewTimer;
}

// Function for a generic timer command.
BaseType_t xTimerGenericCommand( TimerHandle_t xTimer,
    const BaseType_t xCommandID,
    const TickType_t xOptionalValue,
    BaseType_t * const pxHigherPriorityTaskWoken,
    const TickType_t xTicksToWait
    )
{
    BaseType_t xReturn = pdFAIL;
    DaemonTaskMessage_t xMessage;

    // Send a message to the timer service task to perform a specified action
    // on a specified timer.
    if( xTimerQueue != NULL )
    {
        // Prepare the values of the timer command.
        xMessage.xMessageID = xCommandID;
        xMessage.u.xTimerParameters.xMessageValue = xOptionalValue;
        xMessage.u.xTimerParameters.pxTimer = ( Timer_t * ) xTimer;

        if( xCommandID < tmrFIRST_FROM_ISR_COMMAND )
        {
            // Not one of the ISR commands.
            if( xTaskGetSchedulerState() == taskSCHEDULER_RUNNING )
            {
                xReturn
                    = xQueueSendToBack( xTimerQueue, &xMessage, xTicksToWait );
            }
            else
            {
                xReturn
                    = xQueueSendToBack( xTimerQueue, &xMessage, tmrNO_DELAY );
            }
        }
        else
        {
            // One of the ISR commands.
            xReturn = xQueueSendToBackFromISR(
                xTimerQueue, &xMessage, pxHigherPriorityTaskWoken );
        }
    }

    return xReturn;
}

// Checks if the timer is in an active list.
BaseType_t xTimerIsTimerActive( TimerHandle_t xTimer )
{
    BaseType_t xTimerIsInActiveList;
    Timer_t *pxTimer = ( Timer_t * ) xTimer;

    taskENTER_CRITICAL();
    {
        // Check if the timer is in the current or overflowed list.
        xTimerIsInActiveList = !( listIS_CONTAINED_WITHIN(
            NULL, &( pxTimer->xTimerListItem ) ) );
    }
    taskEXIT_CRITICAL();

    return xTimerIsInActiveList;
}

// Returns the ID of the given timer.
void *pvGetTimerID( TimerHandle_t xTimer )
{
    Timer_t * const pxTimer = ( Timer_t * ) xTimer;
    
    return pxTimer->pvTimerID;
}

// Pends a function call from ISR.
BaseType_t xTimerPendFunctionCallFromISR( PendedFunction_t xFunctionToPend,
    void *pvParameter1,
    UBaseType_t ulParameter2,
    BaseType_t *pxHigherPriorityTaskWoken
    )
{
    DaemonTaskMessage_t xMessage;
    BaseType_t xReturn;

    // Set the function parameters to the message structure.
    xMessage.xMessageID = tmrCOMMAND_EXECUTE_CALLBACK_FROM_ISR;
    xMessage.u.xCallbackParameters.pxCallbackFunction = xFunctionToPend;
    xMessage.u.xCallbackParameters.pvParameter1 = pvParameter1;
    xMessage.u.xCallbackParameters.ulParameter2 = ulParameter2;

    // Post the message to the timer task queue.
    xReturn = xQueueSendFromISR(
        xTimerQueue, &xMessage, pxHigherPriorityTaskWoken );

    return xReturn;
}

// Pends a function call from ISR.
BaseType_t xTimerPendFunctionCall( PendedFunction_t xFunctionToPend,
    void *pvParameter1,
    UBaseType_t ulParameter2,
    TickType_t xTicksToWait
    )
{
    DaemonTaskMessage_t xMessage;
    BaseType_t xReturn;

    // Set the function parameters to the message structure.
    xMessage.xMessageID = tmrCOMMAND_EXECUTE_CALLBACK;
    xMessage.u.xCallbackParameters.pxCallbackFunction = xFunctionToPend;
    xMessage.u.xCallbackParameters.pvParameter1 = pvParameter1;
    xMessage.u.xCallbackParameters.ulParameter2 = ulParameter2;

    // Post the message to the timer task queue.
    xReturn = xQueueSendToBack( xTimerQueue, &xMessage, xTicksToWait );

    return xReturn;
}