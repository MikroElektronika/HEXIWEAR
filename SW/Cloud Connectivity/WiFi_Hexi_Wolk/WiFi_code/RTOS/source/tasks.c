// File: tasks.c

// The implementation of functionalities for manipulating tasks and scheduler.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "StackMacros.h"

//extern void vApplicationStackOverflowHook();

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

#define tskIDLE_STACK_SIZE configMINIMAL_STACK_SIZE

#define taskYIELD_IF_USING_PREEMPTION() portYIELD_WITHIN_API()

// The value used to fill the stack of a task when it is created.
#define tskSTACK_FILL_BYTE      0xA5

// Macros used by vListTask to indicate which state the task is in.
#define tskBLOCKED_CHAR   'B'
#define tskREADY_CHAR     'B'
#define tskDELETED_CHAR   'B'
#define tskSUSPENDED_CHAR 'B'

// Set uxPriority to the priority of the highest priority ready state task.
#define taskRECORD_READY_PRIORITY( uxPriority )                                \
{                                                                              \
    if( ( uxPriority ) > uxTopReadyPriority )                                  \
        uxTopReadyPriority = ( uxPriority );                                   \
}

// Sets the next task from the highest priority list to the current TCB.
#define taskSELECT_HIGHEST_PRIORITY_TASK()                                     \
{                                                                              \
    while( listLIST_IS_EMPTY( &( pxReadyTasksLists[ uxTopReadyPriority ] ) ) ) \
    {                                                                          \
        configASSERT( uxTopReadyPriority );                                    \
        uxTopReadyPriority--;                                                  \
    }                                                                          \
                                                                               \
    listGET_OWNER_OF_NEXT_ENTRY(                                               \
        pxCurrentTCB, &( pxReadyTasksLists[ uxTopReadyPriority ] ) );          \
}

// Define these away since they are only required
// when a port optimised method of task selection is being used.
#define taskRESET_READY_PRIORITY( uxPriority )
#define portRESET_READY_PRIORITY( uxPriority, uxTopReadyPriority )

// Current and overflowed task lists are switched when the tick count overflows.
#define taskSWITCH_DELAYED_LISTS()                                             \
{                                                                              \
    List_t *pxTemp;                                                            \
                                                                               \
    /* The delayed task list should be empty when the tasks are switched. */   \
    configASSERT( listLIST_IS_EMPTY( pxDelayedTaskList ) );                    \
                                                                               \
    pxTemp = pxDelayedTaskList;                                                \
    pxDelayedTaskList = pxOverflowDelayedTaskList;                             \
    pxOverflowDelayedTaskList = pxTemp;                                        \
                                                                               \
    xNumOfOverflows++;                                                         \
    prvResetNextTaskUnblockTime();                                             \
}

// Places pxTCB at the end of the appropriate ready list.
#define prvAddTaskToReadyList( pxTCB )                                         \
    taskRECORD_READY_PRIORITY( ( pxTCB )->uxPriority );                        \
    vListInsertEnd( &( pxReadyTasksLists[ ( pxTCB )->uxPriority ] ),           \
        &( ( pxTCB )->xGenericListItem ) );

// Returns TCB_t pointer from the handle.
// If the handle is NULL, pxCurrentTCB is returned.
#define prvGetTCBFromHandle( pxHandle )                                        \
    ( ( ( pxHandle ) == NULL )                                                 \
        ? ( TCB_t * ) pxCurrentTCB                                             \
        : ( TCB_t * ) ( pxHandle ) )

// The value of the event list item is normally used for holding the priority.
// However, sometimes it is used for other purposes,
// and should not be updated with the new priority.
// This bit mask informs the scheduler that the value shouldn't be changed.
#define taskEVENT_LIST_ITEM_VALUE_IN_USE 0x80000000

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/



/******************************************************************************
 * Static variable definitions.                                               *
 ******************************************************************************/

// Lists of ready tasks, arranged by priority.
static List_t pxReadyTasksLists [ configMAX_PRIORITIES ];
// Two lists that will be used for delayed tasks.
static List_t xDelayedTaskList1;
static List_t xDelayedTaskList2;
// Pointer to currently used list of delayed tasks.
static List_t * volatile pxDelayedTaskList;
// Pointer to list of delayed tasks that have overflowed the current tick count.
static List_t * volatile pxOverflowDelayedTaskList;
// List of tasks that have been readied while the scheduler was suspended.
static List_t xPendingReadyList;
// List of tasks waiting to be terminated.
static List_t xTasksWaitingTermination;
// Counter of tasks that have been deleted.
static volatile UBaseType_t uxTasksDeleted = 0;
// List of suspended tasks.
static List_t xSuspendedTaskList;

// Number of currently existing tasks.
static volatile UBaseType_t uxCurrentNumberOfTasks = 0;
// Tick counter.
static volatile TickType_t xTickCount = 0;
// Maximum priority of all currently ready tasks.
static volatile UBaseType_t uxTopReadyPriority = tskIDLE_PRIORITY;
// Scheduler running indicator.
static volatile BaseType_t xSchedulerRunning = pdFALSE;
// Pended ticks counter.
static volatile UBaseType_t uxPendedTicks = 0;
// Yield pending indicator.
static volatile BaseType_t xYieldPending = pdFALSE;
// Overflow counter.
static volatile BaseType_t xNumOfOverflows = 0;
// Task number.
static UBaseType_t uxTaskNumber = 0;
// Time at which the next delayed task should unblock.
static volatile TickType_t xNextTaskUnblockTime = portMAX_DELAY;

// Scheduler suspended indicator.
static volatile UBaseType_t uxSchedulerSuspended = pdFALSE;

/******************************************************************************
 * Global variable definitions.                                               *
 ******************************************************************************/

// TCB of the currently running task.
TCB_t * volatile pxCurrentTCB = NULL;

/******************************************************************************
 * Static function definitions.                                               *
 ******************************************************************************/

// Readies a TCB for the given task. Mainly just copies parameter values.
static void prvInitialiseTCBVariables( TCB_t * const pxTCB,
    const char * const pcName,
    UBaseType_t uxPriority,
    const MemoryRegion_t * const xRegions,
    const unsigned int usStackDepth
    )
{
    // Store the task name.
    strcpy( pxTCB->pcTaskName, pcName );

    // Store the priority level.
    if( uxPriority >= configMAX_PRIORITIES )
        uxPriority = configMAX_PRIORITIES - 1;
    pxTCB->uxPriority = uxPriority;
    pxTCB->uxBasePriority = uxPriority;

    // Initialise the list items.
    vListInitialiseItem( &( pxTCB->xGenericListItem ) );
    vListInitialiseItem( &( pxTCB->xEventListItem ) );

    // Set the pxTCB as the list item owner.
    listSET_LIST_ITEM_OWNER( &( pxTCB->xGenericListItem ), pxTCB );

    // Set priority and owner of the event list item.
    listSET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ),
        configMAX_PRIORITIES - uxPriority );
    listSET_LIST_ITEM_OWNER( &( pxTCB->xEventListItem ), pxTCB );
}

// Checks whether a task is suspended.
static BaseType_t prvTaskIsTaskSuspended( const TaskHandle_t xTask )
{
    BaseType_t xReturn = pdFALSE;
    const TCB_t * const pxTCB = ( TCB_t * ) xTask;

    // Doesn't make sense to check whether the current task is suspended.
    configASSERT( xTask );

    // Is the task in the suspended list?
    if( listIS_CONTAINED_WITHIN( &xSuspendedTaskList,
        &( pxTCB->xGenericListItem ) ) != pdFALSE )
    {
        // Has the task already been resumed from within an ISR?
        if( listIS_CONTAINED_WITHIN( &xPendingReadyList,
            &( pxTCB->xEventListItem ) ) == pdFALSE )
        {
            // Is the task in the suspended state or blocked with no timeout?
            if( listIS_CONTAINED_WITHIN( NULL,
                &( pxTCB->xEventListItem ) ) != pdFALSE )
            {
                xReturn = pdTRUE;
            }
        }
    }

    return xReturn;
}

// Prepares all the lists required for execution of tasks.
static void prvInitialiseTaskLists()
{
    UBaseType_t uxPriority;

    // Initialise ready tasks lists for all priorities.
    for( uxPriority = 0; uxPriority < configMAX_PRIORITIES; uxPriority++ )
    {
        vListInitialise( &( pxReadyTasksLists[ uxPriority ] ) );
    }

    // Initialise the rest of the lists.
    vListInitialise( &xDelayedTaskList1 );
    vListInitialise( &xDelayedTaskList2 );
    vListInitialise( &xPendingReadyList );

    vListInitialise( &xTasksWaitingTermination );

    vListInitialise( &xSuspendedTaskList );

    // Assign delayed tasks list pointers to delayed task lists.
    pxDelayedTaskList = &xDelayedTaskList1;
    pxOverflowDelayedTaskList = &xDelayedTaskList2;
}

// Frees the TCB space, including the stack.
static void prvDeleteTCB( TCB_t *pxTCB )
{
    // Free stack space.
    vPortFree( pxTCB->pxStack, pxTCB->usStackDepth  * sizeof( StackType_t ) );
    // Free TCB space.
    vPortFree( pxTCB, sizeof( TCB_t ) );
}

// Used by the idle task. Deletes all tasks that are waiting to be terminated.
static void prvCheckTasksWaitingTermination()
{
    BaseType_t xListIsEmpty;

    while( uxTasksDeleted > 0 )
    {
        vTaskSuspendAll();
        {
            // Check whether termination list is empty.
            xListIsEmpty = listLIST_IS_EMPTY( &xTasksWaitingTermination );
        }
        xTaskResumeAll();

        if( xListIsEmpty == pdFALSE )
        {
            TCB_t *pxTCB;

            taskENTER_CRITICAL();
            {
                // Get the task at the top of termination list.
                pxTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY(
                    &xTasksWaitingTermination );
                uxListRemove( &( pxTCB->xGenericListItem ) );

                // Update task counters.
                uxCurrentNumberOfTasks--;
                uxTasksDeleted--;
            }
            taskEXIT_CRITICAL();

            // Delete the TCB.
            prvDeleteTCB( pxTCB );
        }
    }
}

// An equivalent of prvIdleTask.
static portTASK_FUNCTION_PROTO( prvIdleTask, pvParameters )
{
    while( 1 )
    {
        // Delete all the tasks that are waiting on it.
        prvCheckTasksWaitingTermination();

        // Yield if there are more tasks of the same priority as the idle task.
        if( listCURRENT_LIST_LENGTH(
            &( pxReadyTasksLists[ tskIDLE_PRIORITY ] ) ) > 1 )
        {
            taskYIELD();
        }

        asm nop;
    }
}

// Adds a task to the appropriate delayed list.
static void prvAddCurrentTaskToDelayedList( const TickType_t xTimeToWake )
{
    // Set list item value to the required time.
    listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xGenericListItem ), xTimeToWake );

    if( xTimeToWake < xTickCount )
    {
        // Wake time has overflowed. Put item in overflow delayed list.
        vListInsert( pxOverflowDelayedTaskList,
            &( pxCurrentTCB->xGenericListItem ) );
    }
    else
    {
        // Wake time has not overflowed. Put item in current delayed list.
        vListInsert( pxDelayedTaskList, &( pxCurrentTCB->xGenericListItem ) );

        // If task's time to wake is less than the next unblock time,
        // the unblock time should be updated.
        if( xTimeToWake < xNextTaskUnblockTime )
        {
            xNextTaskUnblockTime = xTimeToWake;
        }
    }
}

// Allocates the memory for a TCB and its stack.
static TCB_t *prvAllocateTCBAndStack( const int usStackDepth,
    StackType_t * const puxStackBuffer )
{
    TCB_t *pxNewTCB;
    
    // Allocate space for the TCB.
    pxNewTCB = ( TCB_t * ) pvPortMalloc( sizeof( TCB_t ) );

    if( pxNewTCB != NULL )
    {
        // Allocate space for the stack.
        pxNewTCB->pxStack = ( StackType_t * ) pvPortMallocAligned(
            usStackDepth * sizeof( StackType_t ), puxStackBuffer );
        pxNewTCB->usStackDepth = usStackDepth;

        if( pxNewTCB->pxStack == NULL )
        {
            // Error allocating TCB stack. Delete the allocated TCB.
            vPortFree( pxNewTCB, sizeof( TCB_t ) );
            pxNewTCB = NULL;
        }
        else
        {
            // Fill the stack with a predifined value to help with debugging.
            memset( pxNewTCB->pxStack, tskSTACK_FILL_BYTE,
                usStackDepth * sizeof(StackType_t) );
        }
    }
    
    return pxNewTCB;
}

// Checks the free stack space.
static int prvTaskCheckFreeStackSpace( const char * pucStackByte )
{
    unsigned long ulCount = 0;
    
    // Increment the counter while the stack value is equal to the fill byte.
    while( *pucStackByte == tskSTACK_FILL_BYTE )
    {
        pucStackByte -= portSTACK_GROWTH;
        ulCount++;
    }
    
    ulCount /= sizeof( StackType_t );
    
    return ulCount;
}

// Resets the unblock time according to the next blocked task.
static void prvResetNextTaskUnblockTime()
{
    TCB_t *pxTCB;

    if( listLIST_IS_EMPTY( pxDelayedTaskList ) != pdFALSE )
    {
        // The current delayed list is empty.
        // Set the unblock time to the max value.
        xNextTaskUnblockTime = portMAX_DELAY;
    }
    else
    {
        // The current delayed list is not empty.
        // Set unblock time to the wake time of the first task to be woken.
        pxTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxDelayedTaskList );
        xNextTaskUnblockTime
            = listGET_LIST_ITEM_VALUE( &( pxTCB->xGenericListItem ) );
    }
}

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/
 
// Creates a task. Will initialise all TCB fields and stack.
BaseType_t xTaskGenericCreate( TaskFunction_t pxTaskCode,
    const char * const pcName,
    int usStackDepth,
    void * const pvParameters,
    UBaseType_t uxPriority,
    TaskHandle_t * const pxCreatedTask,
    StackType_t * const puxStackBuffer,
    const MemoryRegion_t * const xRegions
    )
{
    BaseType_t xReturn;
    TCB_t *pxNewTCB;
    
    configASSERT( pxTaskCode );
    if( usStackDepth < configMINIMAL_STACK_SIZE )
        usStackDepth = configMINIMAL_STACK_SIZE;

    // Allocate the memory for the TCB and stack, and check if it succeded.
    pxNewTCB = prvAllocateTCBAndStack( usStackDepth, NULL );

    if( pxNewTCB != NULL )
    {
        StackType_t *pxTopOfStack;

        // Calculate the top of stack address.
        pxTopOfStack = pxNewTCB->pxStack + usStackDepth - 1;
        pxTopOfStack = ( StackType_t )
            (( BaseType_t ) pxTopOfStack  &
            ~( ( BaseType_t ) portBYTE_ALIGNMENT_MASK ));

        // Check if the alignment of the calculated top of stack is correct.
        configASSERT( ( ( ( BaseType_t ) pxTopOfStack
            & ( BaseType_t ) portBYTE_ALIGNMENT_MASK ) == 0 ) );

        // Initialise TCB fields.
        if( uxPriority >= configMAX_PRIORITIES )
            uxPriority = configMAX_PRIORITIES - 1;
        prvInitialiseTCBVariables(
            pxNewTCB, pcName, uxPriority, NULL, usStackDepth );

        // Initialise the stack.
        pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack,
            pxTaskCode, pvParameters );

        // If task handle is required, pass it out.
        if( pxCreatedTask != NULL )
            *pxCreatedTask = ( TaskHandle_t ) pxNewTCB;

        // Changing global structures, so a critical section must be entered.
        taskENTER_CRITICAL();
        {
            uxCurrentNumberOfTasks++;

            if( pxCurrentTCB == NULL )
            {
                // There are no other tasks,
                // set this task to be the currently running one.
                pxCurrentTCB = pxNewTCB;

                if( uxCurrentNumberOfTasks == 1 )
                {
                    // This is the first task to be created.
                    // Task lists should be initialised.
                    prvInitialiseTaskLists();
                }
            }
            else
            {
                // If scheduler isn't running, make this task the current one
                // if it has the highest priority so far.
                if( xSchedulerRunning == pdFALSE )
                {
                    if( pxCurrentTCB->uxPriority <= uxPriority )
                    {
                        pxCurrentTCB = pxNewTCB;
                    }
                }
            }
            
            uxTaskNumber++;

            prvAddTaskToReadyList( pxNewTCB );
            xReturn = pdPASS;
        }
        taskEXIT_CRITICAL();
    }
    else
    {
        xReturn = errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
    }

    if( xReturn == pdPASS )
    {
        if( xSchedulerRunning != pdFALSE ) // scheduler is currently running
        {
            // If the created task is of higher priority than the current task,
            // it should run now.
            if( pxCurrentTCB->uxPriority < uxPriority )
            {
                taskYIELD_IF_USING_PREEMPTION();
            }
        }
    }

    return xReturn;
}

// Pends a task to be terminated. It will be deleted in the idle task.
void vTaskDelete( TaskHandle_t xTaskToDelete )
{
    TCB_t *pxTCB;

    taskENTER_CRITICAL();
    {
        // If the task to delete is null,
        // then the current task should be deleted.
        pxTCB = prvGetTCBFromHandle( xTaskToDelete );

        // Remove the task from the ready list.
        if( uxListRemove( &( pxTCB->xGenericListItem ) ) == 0 )
            taskRESET_READY_PRIORITY( pxTCB->uxPriority );

        // Is the task also waiting on an event?
        if( listLIST_ITEM_CONTAINER( &( pxTCB->xEventListItem ) ) != NULL )
            uxListRemove( &( pxTCB->xEventListItem ) );

        // Set task to wait termination.
        vListInsertEnd( &xTasksWaitingTermination,
            &( pxTCB->xGenericListItem ) );

        // Increment deleted tasks counter,
        // so that the idle tasks knows there are tasks to be deleted.
        uxTasksDeleted++;
        
        // Increment the uxTaskNumber variable so kernel aware debuggers
        // can detect that the task lists need re-generating.
        uxTaskNumber++;
    }
    taskEXIT_CRITICAL();

    // Force a reschedule if the current task has been deleted.
    if( xSchedulerRunning != pdFALSE )
    {
        if( pxTCB == pxCurrentTCB )
        {
            configASSERT( uxSchedulerSuspended == 0 );

            portYIELD_WITHIN_API();
        }
        else
        {
            // If the deleted task was the next to be unblocked,
            // reset the unblock time.
            prvResetNextTaskUnblockTime();
        }
    }
}

// Delays a task until the desired time.
void vTaskDelayUntil( TickType_t * const pxPreviousWakeTime,
    const TickType_t xTimeIncrement )
{
    TickType_t xTimeToWake;
    BaseType_t xAlreadyYielded;
    BaseType_t xShouldDelay = pdFALSE;

    configASSERT( pxPreviousWakeTime );
    configASSERT( ( xTimeIncrement > 0 ) );
    configASSERT( uxSchedulerSuspended == 0 );

    vTaskSuspendAll();
    {
        // Minor optimisation.
        /* const */ TickType_t xConstTickCount = xTickCount;
        
        // Calculate the tick time at which the task should wake.
        xTimeToWake = *pxPreviousWakeTime + xTimeIncrement;

        if( xConstTickCount < *pxPreviousWakeTime )
        {
            // Tick count has overflowed since this function was last called.
            // In this case we should delay only if the time to wake
            // has also overflowed AND is greater than tick count.
            if( ( xTimeToWake < *pxPreviousWakeTime )
                && ( xTimeToWake > xConstTickCount ) )
            {
                xShouldDelay = pdTRUE;
            }
        }
        else // tick count has not overflowed
        {
            // Tick count has not overflowed since the last call.
            // In this case we should delay if the time to wake has overflowed
            // OR it is greater than tick count.
            if( ( xTimeToWake < *pxPreviousWakeTime )
                || ( xTimeToWake > xConstTickCount ) )
            {
                xShouldDelay = pdTRUE;
            }
        }

        // Update the wake time for the next call.
        *pxPreviousWakeTime = xTimeToWake;

        if( xShouldDelay != pdFALSE )
        {
            // Remove this TCB from the ready list.
            if( uxListRemove( &( pxCurrentTCB->xGenericListItem ) ) == 0 )
            {
                portRESET_READY_PRIORITY(
                    pxCurrentTCB->uxPriority, uxTopReadyPriority );
            }

            // Add this TCB to the delayed list.
            prvAddCurrentTaskToDelayedList( xTimeToWake );
        }
    }
    xAlreadyYielded = xTaskResumeAll();

    // Preform a reschedule if xTaskResumeAll has not done it already.
    if( xAlreadyYielded == pdFALSE )
    {
        portYIELD_WITHIN_API();
    }
}

// Delays a task for a number of ticks.
void vTaskDelay( const TickType_t xTicksToDelay )
{
    TickType_t xTimeToWake;
    BaseType_t xAlreadyYielded = pdFALSE;

    // If delay is zero, a simple context switch is required.
    if( xTicksToDelay > 0 )
    {
        configASSERT( uxSchedulerSuspended == 0 );

        vTaskSuspendAll();
        {
            // Calculate time to wake up.
            xTimeToWake = xTickCount + xTicksToDelay;

            // Remove this TCB from the ready list.
            if( uxListRemove( &( pxCurrentTCB->xGenericListItem ) ) == 0 )
            {
                portRESET_READY_PRIORITY(
                    pxCurrentTCB->uxPriority, uxTopReadyPriority );
            }

            // Add this TCB to the delayed list.
            prvAddCurrentTaskToDelayedList( xTimeToWake );
        }
        xAlreadyYielded = xTaskResumeAll();
    }

    // Preform a reschedule if xTaskResumeAll has not done it already.
    if( xAlreadyYielded == pdFALSE )
    {
        portYIELD_WITHIN_API();
    }
}

// Returns the priority of a task.
UBaseType_t uxTaskPriorityGet( TaskHandle_t pxTask )
{
    TCB_t *pxTCB;
    UBaseType_t uxReturn;

    taskENTER_CRITICAL();
    {
        // If null is passed the priority of calling task will be returned.
        pxTCB = prvGetTCBFromHandle( pxTask );
        uxReturn = pxTCB->uxPriority;
    }
    taskEXIT_CRITICAL();

    return uxReturn;
}

// Sets the priority of a task.
void vTaskPrioritySet( TaskHandle_t pxTask, UBaseType_t uxNewPriority )
{
    TCB_t *pxTCB;
    UBaseType_t uxCurrentBasePriority;
    UBaseType_t uxPriorityUsedOnEntry;
    BaseType_t xYieldRequired = pdFALSE;

    // If new priority is greater than maximum priority clip it.
    if( uxNewPriority >= configMAX_PRIORITIES )
        uxNewPriority = configMAX_PRIORITIES - 1;

    taskENTER_CRITICAL();
    {
        // If null is passed the priority of calling task will be changed.
        pxTCB = prvGetTCBFromHandle( pxTask );
        
        uxCurrentBasePriority = pxTCB->uxBasePriority;

        // Check if we need to change the priority at all.
        if( uxCurrentBasePriority != uxNewPriority )
        {
            // A task of higher priority than the calling task may be ready now.
            if( uxNewPriority > uxCurrentBasePriority )
            {
                if( pxTCB != pxCurrentTCB )
                {
                    // If the new priority of the task is higher
                    // than the current task's priority it is ready to run.
                    if( uxNewPriority >= pxCurrentTCB->uxPriority )
                    {
                        xYieldRequired = pdTRUE;
                    }
                }
            }
            else if( pxTCB == pxCurrentTCB )
            {
                // Lowering the calling task priority
                // means that there mey be a new one ready to execute.
                xYieldRequired = pdTRUE;
            }

            // Remember the previous priority value.
            uxPriorityUsedOnEntry = pxTCB->uxPriority;

            // Only change the priority if the task is not using
            // an inherited priority.
            if( pxTCB->uxBasePriority == pxTCB->uxPriority )
            {
                pxTCB->uxPriority = uxNewPriority;
            }

            // Always change the base priority.
            pxTCB->uxBasePriority = uxNewPriority;

            // Change the event list item value
            // only if it is not being used for something else.
            if( ( listGET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ) )
                & taskEVENT_LIST_ITEM_VALUE_IN_USE ) == 0 )
            {
                listSET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ),
                    configMAX_PRIORITIES - uxNewPriority );
            }

            // If task is within a ready list,
            // we must change the list to match its new priority.
            if( listIS_CONTAINED_WITHIN(
                &( pxReadyTasksLists[ uxPriorityUsedOnEntry ] ),
                &( pxTCB->xGenericListItem ) ) != pdFALSE )
            {
                if( uxListRemove( &( pxTCB->xGenericListItem ) ) == 0 )
                {
                    portRESET_READY_PRIORITY(
                        uxPriorityUsedOnEntry, uxTopReadyPriority );
                }

                prvAddTaskToReadyList( pxTCB );
            }

            // Yield if it is needed.
            if( xYieldRequired == pdTRUE )
            {
                taskYIELD();
            }
        }
    }
    taskEXIT_CRITICAL();
}

// Suspends a task.
void vTaskSuspend( TaskHandle_t xTaskToSuspend )
{
    TCB_t *pxTCB;

    taskENTER_CRITICAL();
    {
        // If null is passed the calling task will be suspended.
        pxTCB = prvGetTCBFromHandle( xTaskToSuspend );
        
        // Remove the task from the ready list.
        if( uxListRemove( &( pxTCB->xGenericListItem ) ) == 0 )
        {
            taskRESET_READY_PRIORITY( pxTCB->uxPriority );
        }

        // If the task is waiting on an event, remove it from the event list.
        if( listLIST_ITEM_CONTAINER( &( pxTCB->xEventListItem ) ) != NULL )
        {
            uxListRemove( &( pxTCB->xEventListItem ) );
        }

        // Add the task to the suspended list.
        vListInsertEnd( &xSuspendedTaskList, &( pxTCB->xGenericListItem ) );
    }
    taskEXIT_CRITICAL();

    if( pxTCB == pxCurrentTCB )
    {
        if( xSchedulerRunning != pdFALSE )
        {
            // Yield because the current task has been suspended.
            configASSERT( uxSchedulerSuspended == 0 );
            portYIELD_WITHIN_API();
        }
        else
        {
            // The scheduler is not running,
            // but the task that pxCurrentTCB points to has been suspended.
            // The current task pointer should be changed.
            if( listCURRENT_LIST_LENGTH( &xSuspendedTaskList )
                == uxCurrentNumberOfTasks )
            {
                // No other tasks are ready, pxCurrentTCB should be null.
                pxCurrentTCB = NULL;
            }
            else
            {
                vTaskSwitchContext();
            }
        }
    }
    else
    {
        if( xSchedulerRunning != pdFALSE )
        {
            // Suspended task is not the current one.
            // In case it was the next to unblock, unblock time should change.
            prvResetNextTaskUnblockTime();
        }
    }
}

// Resumes a suspended task.
void vTaskResume( TaskHandle_t xTaskToResume )
{
    TCB_t * const pxTCB = ( TCB_t * ) xTaskToResume;

    // It doesn't make sense to resume the current task.
    configASSERT( xTaskToResume );

    if( ( pxTCB != NULL ) && ( pxTCB != pxCurrentTCB ) )
    {
        taskENTER_CRITICAL();
        {
            // Is the task suspended at all?
            if( prvTaskIsTaskSuspended(pxTCB) == pdTRUE )
            {
                // Remove task from the suspended list
                uxListRemove( &( pxTCB->xGenericListItem ) );
                // Add task to the ready list
                prvAddTaskToReadyList( pxTCB );

                // Is the resumed task of higher priority than the current task?
                if( pxTCB->uxPriority >= pxCurrentTCB->uxPriority )
                {
                    // Yield because the new task should run.
                    taskYIELD_IF_USING_PREEMPTION();
                }
            }
        }
        taskEXIT_CRITICAL();
    }
}

// Resumes a suspended task, can be called from an ISR.
BaseType_t xTaskResumeFromISR( TaskHandle_t xTaskToResume )
{
    BaseType_t xYieldRequired = pdFALSE;
    TCB_t * const pxTCB = ( TCB_t * ) xTaskToResume;
    UBaseType_t uxSavedInterruptStatus;

    // Trying to resume the current task.
    configASSERT( xTaskToResume );

    uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        if( prvTaskIsTaskSuspended(pxTCB) == pdTRUE )
        {
            // Check if the ready lists can be accessed.
            if( uxSchedulerSuspended == pdFALSE )
            {
                // Ready lists can be accessed
                // so move the task from the suspended list to the ready list.
                if( pxTCB->uxPriority >= pxCurrentTCB->uxPriority )
                {
                    xYieldRequired = pdTRUE;
                }

                uxListRemove( &( pxTCB->xGenericListItem ) );
                prvAddTaskToReadyList( pxTCB );
            }
            else
            {
                // Delayed or ready lists cannot be accessed,
                // add the task to the pending ready list instead.
                vListInsertEnd( &xPendingReadyList,
                    &( pxTCB->xEventListItem ) );
            }
        }
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );

    return xYieldRequired;
}

// Starts the scheduler, allowing tasks to execute.
void vTaskStartScheduler()
{
    BaseType_t xReturn;

    // Create the idle task.
    xReturn = xTaskCreate( ( TaskFunction_t ) prvIdleTask,
        "Idle",
        tskIDLE_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY,
        NULL
        );

    if( xReturn == pdPASS )
    {
        // Create the timer task.
        xReturn = xTimerCreateTimerTask();
    }

    if( xReturn == pdPASS )
    {
        // Disable interrupts so that a tick doesn't occur
        // before the initialisation is complete. The first task
        // will automatically enable interrupts when it starts executing.
        portDISABLE_INTERRUPTS();

        xSchedulerRunning = pdTRUE;
        xTickCount = 0;

        xPortStartScheduler();
    }
    else
    {
        configASSERT( xReturn );
    }
}

// Stops the scheduler. All tasks will stop executing.
void vTaskEndScheduler()
{
    // Stop the scheduler interrupts and call the portable scheduler end routine
    // so the original ISRs can be restored if necessary.
    taskDISABLE_INTERRUPTS();
    xSchedulerRunning = pdFALSE;
    vPortEndScheduler();
}

// Suspends all ready tasks.
void vTaskSuspendAll()
{
    // No critical section is needed since the variable is of type BaseType_t.
    uxSchedulerSuspended++;
}

// Resumes all tasks that were suspended by vTaskSuspendAll().
BaseType_t xTaskResumeAll()
{
    TCB_t *pxTCB;
    BaseType_t xAlreadyYielded = pdFALSE;

    // If uxSchedulerSuspended is not zero,
    // this call does not match a call to vTaskSuspendAll.
    configASSERT( uxSchedulerSuspended );

    // If any tasks were removed from an event list while
    // the scheduler was suspended, they would be in the pending ready list.
    //
    taskENTER_CRITICAL();
    {
        uxSchedulerSuspended--;

        if( uxSchedulerSuspended == pdFALSE )
        {
            if( uxCurrentNumberOfTasks > 0 )
            {
                // Move any pending ready tasks into the ready lists.
                while( listLIST_IS_EMPTY( &xPendingReadyList ) == pdFALSE )
                {
                    pxTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY(
                        &xPendingReadyList );
                    uxListRemove( &( pxTCB->xEventListItem ) );
                    uxListRemove( &( pxTCB->xGenericListItem ) );
                    prvAddTaskToReadyList( pxTCB );
                    
                    // If a task with higher priority than the current task
                    // has been moved, the processor should yield.
                    if( pxTCB->uxPriority >= pxCurrentTCB->uxPriority )
                    {
                        xYieldPending = pdTRUE;
                    }
                }

                // Execute all ticks that occured while scheduler was suspended.
                // This ensures that the tick count does not slip,
                // and that any delayed tasks are resumed at the correct time.
                while( uxPendedTicks > 0 )
                {
                    if( xTaskIncrementTick() != pdFALSE )
                    {
                        xYieldPending = pdTRUE;
                    }
                    uxPendedTicks--;
                }

                if( xYieldPending == pdTRUE )
                {
                    xAlreadyYielded = pdTRUE;

                    taskYIELD_IF_USING_PREEMPTION();
                }
            }
        }
    }
    taskEXIT_CRITICAL();

    return xAlreadyYielded;
}

// Returns the current tick count.
TickType_t xTaskGetTickCount()
{
    TickType_t xTicks;

    taskENTER_CRITICAL();
    {
        xTicks = xTickCount;
    }
    taskEXIT_CRITICAL();

    return xTicks;
}

// Returns the current tick count, can be called from within an ISR.
TickType_t xTaskGetTickCountFromISR()
{
    TickType_t xReturn;
    UBaseType_t uxSavedInterruptStatus;

    uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        xReturn = xTickCount;
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );

    return xReturn;
}

// Returns the current number of tasks
UBaseType_t uxTaskGetNumberOfTasks()
{
    // Critical sections are not needed
    // because the variable is of type BaseType_t.
    return uxCurrentNumberOfTasks;
}

// Increments the SysTick.
// Checks the delayed list for potential tasks that need to be unblocked.
BaseType_t xTaskIncrementTick()
{
    TCB_t *pxTCB;
    TickType_t xItemValue;
    BaseType_t xSwitchRequired = pdFALSE;

    if( uxSchedulerSuspended == pdFALSE )
    {
        // Increment the tick count and switch delayed lists
        // if the tick overflowed.
        xTickCount++;
        if( xTickCount == 0 )
        {
            taskSWITCH_DELAYED_LISTS();
        }

        // See if this tick has made a timeout expire.
        if( xTickCount >= xNextTaskUnblockTime )
        {
            while( 1 )
            {
                if( listLIST_IS_EMPTY( pxDelayedTaskList ) != pdFALSE )
                {
                    // Delayed list is empty, set unblock time to max value.
                    xNextTaskUnblockTime = portMAX_DELAY;
                    break;
                }
                else
                {
                    // Delayed list is not empty.
                    // Get the first task that needs waking.
                    pxTCB = listGET_OWNER_OF_HEAD_ENTRY( pxDelayedTaskList );
                    xItemValue = listGET_LIST_ITEM_VALUE(
                        pxTCB->xGenericListItem );

                    if( xTickCount < xItemValue )
                    {
                        // The task should not be woken up yet.
                        // Its item value is the next unblock time.
                        xNextTaskUnblockTime = xItemValue;
                        break;
                    }

                    // Remove the item from the blocked state.
                    uxListRemove( &( pxTCB->xGenericListItem ) );

                    // Remove the item from the event list, if it is waiting.
                    if( listLIST_ITEM_CONTAINER(
                        &( pxTCB->xEventListItem ) ) != NULL )
                    {
                        uxListRemove( &( pxTCB->xEventListItem ) );
                    }

                    // Add task to the ready list according to its priority.
                    prvAddTaskToReadyList( pxTCB );

                    // Request context switch if this task has higher priority
                    // than the current one.
                    if( pxTCB->uxPriority >= pxCurrentTCB->uxPriority )
                    {
                        xSwitchRequired = pdTRUE;
                    }
                }
            }
        }

        // Request switch if there are more tasks of the same priority.
        if( listCURRENT_LIST_LENGTH(
            &( pxReadyTasksLists[ pxCurrentTCB->uxPriority ] ) )
            > ( UBaseType_t ) 1 )
        {
            xSwitchRequired = pdTRUE;
        }
    }
    else
    {
        uxPendedTicks++;
    }

    if( xYieldPending != pdFALSE )
    {
        xSwitchRequired = pdTRUE;
    }

    return xSwitchRequired;
}

// Switches the context of the currently running task with the new one.
void vTaskSwitchContext()
{
    if( uxSchedulerSuspended != pdFALSE )
    {
        // The scheduler is suspended, postpone yield for later.
        xYieldPending = pdTRUE;
    }
    else
    {
        xYieldPending = pdFALSE;

        // Check for stack overflow of current task.
        taskFIRST_CHECK_FOR_STACK_OVERFLOW();

        // Set the highest priority task to be te one currently executing.
        taskSELECT_HIGHEST_PRIORITY_TASK();
    }
}

// Places the running task on an event list.
// This function must be called with either interrupts disabled
// or the scheduler suspended and the queue being access locked.
void vTaskPlaceOnEventList( List_t * const pxEventList,
    const TickType_t xTicksToWait )
{
    TickType_t xTimeToWake;

    configASSERT( pxEventList );

    // Add the task to the event list, sorted by priority.
    // The queue that contains the list is locked.
    vListInsert( pxEventList, &( pxCurrentTCB->xEventListItem ) );

    // Remove list item from the running list.
    if( uxListRemove( &( pxCurrentTCB->xGenericListItem ) ) == 0 )
    {
        portRESET_READY_PRIORITY(
            pxCurrentTCB->uxPriority, uxTopReadyPriority );
    }

    if( xTicksToWait == portMAX_DELAY )
    {
        // The task should not wake up on a timer.
        // Add the task to the suspended list instead of the delayed one.
        vListInsertEnd( &xSuspendedTaskList,
            &( pxCurrentTCB->xGenericListItem ) );
    }
    else
    {
        // Calculate time to wake and place the task in the delayed list.
        xTimeToWake = xTickCount + xTicksToWait;
        prvAddCurrentTaskToDelayedList( xTimeToWake );
    }
}

// Places the current task on an unordered event list.
// This function must be called with the scheduler suspended.
// It is used by the event groups implementation.
void vTaskPlaceOnUnorderedEventList( List_t * const pxEventList,
    const TickType_t xItemValue, const TickType_t xTicksToWait )
{
    TickType_t xTimeToWake;

    configASSERT( pxEventList );

    configASSERT( uxSchedulerSuspended != 0 );

    // Store the item value in the event list item.
    listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xEventListItem ),
        xItemValue | taskEVENT_LIST_ITEM_VALUE_IN_USE );

    // Add the task to the event list.
    vListInsertEnd( pxEventList, &( pxCurrentTCB->xEventListItem ) );

    // Remove the list item from the running list.
    if( uxListRemove( &( pxCurrentTCB->xGenericListItem ) ) == 0 )
    {
        portRESET_READY_PRIORITY(
            pxCurrentTCB->uxPriority, uxTopReadyPriority );
    }

    if( xTicksToWait == portMAX_DELAY )
    {
        // The task should not wake up on a timer.
        // Add the task to the suspended list instead of the delayed one.
        vListInsertEnd( &xSuspendedTaskList,
            &( pxCurrentTCB->xGenericListItem ) );
    }
    else
    {
        // Calculate time to wake and place the task in the delayed list.
        xTimeToWake = xTickCount + xTicksToWait;
        prvAddCurrentTaskToDelayedList( xTimeToWake );
    }
}

// Places the running task on an event list - restricted version.
// This function should not be called by application code.
// It is intended to be called by the kernel, and in a critical section
void vTaskPlaceOnEventListRestricted( List_t * const pxEventList,
    const TickType_t xTicksToWait )
{
    TickType_t xTimeToWake;

    configASSERT( pxEventList );

    // Add the task to the event list.
    vListInsertEnd( pxEventList, &( pxCurrentTCB->xEventListItem ) );

    // Remove list item from the running list.
    if( uxListRemove( &( pxCurrentTCB->xGenericListItem ) ) == 0 )
    {
        portRESET_READY_PRIORITY(
            pxCurrentTCB->uxPriority, uxTopReadyPriority );
    }

    // Calculate time to wake and place the task to the delayed list.
    xTimeToWake = xTickCount + xTicksToWait;
    prvAddCurrentTaskToDelayedList( xTimeToWake );
}

// Removes one task from an event list and places it in the ready list.
// This function must be called from a critical section, even from an ISR.
BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList )
{
    TCB_t *pxUnblockedTCB;
    BaseType_t xReturn;

    // Remove the head item from the event list.
    pxUnblockedTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxEventList );
    configASSERT( pxUnblockedTCB );
    uxListRemove( &( pxUnblockedTCB->xEventListItem ) );

    if( uxSchedulerSuspended == pdFALSE )
    {
        // Remove the task from the suspended list and add it to the ready list.
        uxListRemove( &( pxUnblockedTCB->xGenericListItem ) );
        prvAddTaskToReadyList( pxUnblockedTCB );
    }
    else
    {
        // Cannot access the ready and suspended lists,
        // so put the task into the pending ready list.
        vListInsertEnd( &( xPendingReadyList ),
            &( pxUnblockedTCB->xEventListItem ) );
    }

    if( pxUnblockedTCB->uxPriority > pxCurrentTCB->uxPriority )
    {
        // Removed task has higher priority than the current one,
        // return pdTRUE and schedule a yield.
        xReturn = pdTRUE;
        xYieldPending = pdTRUE;
    }
    else
    {
        xReturn = pdFALSE;
    }

    return xReturn;
}

// Function for removing one task from an unordered event list.
// This function must be called with the scheduler suspended.
// It is used by the event flags implementation.
BaseType_t xTaskRemoveFromUnorderedEventList( ListItem_t *pxEventListItem,
    TickType_t xItemValue )
{
    TCB_t *pxUnblockedTCB;
    BaseType_t xReturn;

    configASSERT( uxSchedulerSuspended != pdFALSE );

    // Store the new item value in the event list.
    listSET_LIST_ITEM_VALUE( pxEventListItem,
        xItemValue | taskEVENT_LIST_ITEM_VALUE_IN_USE );

    // Remove the event list item form the event list.
    pxUnblockedTCB = ( TCB_t * ) listGET_LIST_ITEM_OWNER( pxEventListItem );
    configASSERT( pxUnblockedTCB );
    uxListRemove( pxEventListItem );

    // Remove the task from the delayed list and add it to the ready list.
    uxListRemove( &( pxUnblockedTCB->xGenericListItem ) );
    prvAddTaskToReadyList( pxUnblockedTCB );

    if( pxUnblockedTCB->uxPriority > pxCurrentTCB->uxPriority )
    {
        // Removed task has higher priority than the current one,
        // return pdTRUE and schedule a yield.
        xReturn = pdTRUE;
        xYieldPending = pdTRUE;
    }
    else
    {
        xReturn = pdFALSE;
    }

    return xReturn;
}

// Sets the given timeout state, so it can be used later when checking timeout.
void vTaskSetTimeOutState( TimeOut_t *pxTimeOut )
{
    configASSERT( pxTimeOut );

    pxTimeOut->xOverflowCount = xNumOfOverflows;
    pxTimeOut->xTimeOnEntering = xTickCount;
}

// Checks for timeout with the given timeout state.
BaseType_t xTaskCheckForTimeOut( TimeOut_t *pxTimeOut,
    TickType_t *pxTicksToWait )
{
    BaseType_t xReturn;

    configASSERT( pxTimeOut );
    configASSERT( pxTicksToWait );

    taskENTER_CRITICAL();
    {
        // Minor optimisation.
        /* const */ TickType_t xConstTickCount = xTickCount;

        if( *pxTicksToWait == portMAX_DELAY )
        {
            // The task should block indefinitely, and not time out.
            xReturn = pdFALSE;
        }
        else if( ( xNumOfOverflows != pxTimeOut->xOverflowCount )
            && ( xTickCount >= pxTimeOut->xTimeOnEntering ) )
        {
            // The tick counter is greater than the time of entering,
            // but it has also overflowed.
            xReturn = pdTRUE;
        }
        else if( ( xTickCount - pxTimeOut->xTimeOnEntering ) < *pxTicksToWait )
        {
            // Not a real timeout, adjust for the remaining time.
            *pxTicksToWait -= ( xTickCount - pxTimeOut->xTimeOnEntering );
            vTaskSetTimeOutState( pxTimeOut );
            xReturn = pdFALSE;
        }
        else
        {
            xReturn = pdTRUE;
        }
    }
    taskEXIT_CRITICAL();

    return xReturn;
}

// Schedules a yield.
void vTaskMissedYield()
{
    xYieldPending = pdTRUE;
}

// Calculates the remaining stack size of a task.
UBaseType_t uxTaskGetStackHighWaterMark( TaskHandle_t pxTask )
{
    TCB_t *pxTCB;
    int8_t *pucEndOfStack;
    UBaseType_t uxReturn;

    // If null is passed then the remaining stack of current task is returned.
    pxTCB = prvGetTCBFromHandle( pxTask );

    pucEndOfStack = ( int8_t * ) pxTCB->pxStack;

    uxReturn =  prvTaskCheckFreeStackSpace( pucEndOfStack );

    return uxReturn;
}

//Returns a handle for the current task.
TaskHandle_t xTaskGetCurrentTaskHandle()
{
    TaskHandle_t xReturn;

    // Critical section is not needed since current TCB will always be the same.
    xReturn = ( TaskHandle_t ) pxCurrentTCB;

    return xReturn;
}

// Returns the current scheduler state.
BaseType_t xTaskGetSchedulerState()
{
    BaseType_t xReturn;

    if( xSchedulerRunning == pdFALSE )
    {
        xReturn = taskSCHEDULER_NOT_STARTED;
    }
    else if( uxSchedulerSuspended == pdFALSE )
    {
        xReturn = taskSCHEDULER_RUNNING;
    }
    else
    {
        xReturn = taskSCHEDULER_SUSPENDED;
    }

    return xReturn;
}

// Inherits the current task's priority to the given task.
void vTaskPriorityInherit( TaskHandle_t pxMutexHolder )
{
    TCB_t * const pxTCB = ( TCB_t * ) pxMutexHolder;

    // Mutex holder might be null if the mutex was given back by an interrupt.
    if( pxMutexHolder != NULL )
    {
        // Is the current priority lower than the new one?
        if( pxTCB->uxPriority < pxCurrentTCB->uxPriority )
        {
            // Adjust the event list item for the new priority,
            // if it is not being used for something else.
            if( ( listGET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ) )
                & taskEVENT_LIST_ITEM_VALUE_IN_USE ) == 0 )
            {
                listSET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ),
                    configMAX_PRIORITIES - pxCurrentTCB->uxPriority );
            }

            // If the task is in a ready list, the list will have to be changed.
            if( listIS_CONTAINED_WITHIN(
                &( pxReadyTasksLists[ pxTCB->uxPriority ] ),
                &( pxTCB->xGenericListItem ) ) != pdFALSE )
            {
                // Remove task from previous list.
                if( uxListRemove( &( pxTCB->xGenericListItem ) ) == 0 )
                    taskRESET_READY_PRIORITY( pxTCB->uxPriority );
                // Inherit the priority before adding the task to the new list.
                pxTCB->uxPriority = pxCurrentTCB->uxPriority;
                prvAddTaskToReadyList( pxTCB );
            }
            else
            {
                // Just change the priority.
                pxTCB->uxPriority = pxCurrentTCB->uxPriority;
            }
        }
    }
}

// Disinherits the inherited priority.
void vTaskPriorityDisinherit( TaskHandle_t pxMutexHolder )
{
    TCB_t * const pxTCB = ( TCB_t * ) pxMutexHolder;

    // Mutex holder might be null if the mutex was given back by an interrupt.
    if( pxMutexHolder != NULL )
    {
        // Is the inherited priority different than the base one?
        if( pxTCB->uxPriority != pxTCB->uxBasePriority )
        {
            // This has to be the current task,
            // remove it from the current ready list.
            if( uxListRemove( &( pxTCB->xGenericListItem ) ) == 0 )
            {
                taskRESET_READY_PRIORITY( pxTCB->uxPriority );
            }

            // Adjust the priority before adding the task to the new ready list.
            pxTCB->uxPriority = pxTCB->uxBasePriority;
            
            // Adjust the event list item for the new priority,
            // if it is not being used for something else.
            if( ( listGET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ) )
                & taskEVENT_LIST_ITEM_VALUE_IN_USE ) == 0 )
            {
                listSET_LIST_ITEM_VALUE( &( pxTCB->xEventListItem ),
                    configMAX_PRIORITIES - pxTCB->uxPriority );
            }

            prvAddTaskToReadyList( pxTCB );
        }
    }
}

// Resets the value of the event list item of the current task.
TickType_t uxTaskResetEventItemValue()
{
    TickType_t uxReturn;

    uxReturn = listGET_LIST_ITEM_VALUE( &( pxCurrentTCB->xEventListItem ) );

    // Reset the event list item value to its normal value.
    listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xEventListItem ),
        configMAX_PRIORITIES - pxCurrentTCB->uxPriority );

    return uxReturn;
}