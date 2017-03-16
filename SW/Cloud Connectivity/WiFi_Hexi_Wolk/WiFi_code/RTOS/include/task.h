// File: task.h

// The complete interface for manipulating tasks and the scheduler
// - creating and deleting tasks, suspending and delaying them,
// prioroty manipulation etc.

#ifndef _task_h_
#define _task_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include <stdint.h>

#include "projdefs.h"
#include "portable.h"
#include "list.h"

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

// FreeRTOS kernel version number.
#define tskKERNEL_VERSION_NUMBER "V8.0.0"
#define tskKERNEL_VERSION_MAJOR 8
#define tskKERNEL_VERSION_MINOR 0
#define tskKERNEL_VERSION_BUILD 0

#define tskIDLE_PRIORITY                        ( 0 )


// Macro for yielding the processor to another task.
#define taskYIELD()                                                            \
    do {                                                                       \
        SCB_ICSRbits.PENDSVSET = 1;                                            \
                                                                               \
        asm dsb;                                                               \
        asm isb;                                                               \
    } while( 0 )

// Macro for disabling interrupts.
#define taskDISABLE_INTERRUPTS()                                               \
    CPU_REG_SET( CPU_BASEPRI, configMAX_SYSCALL_INTERRUPT_PRIORITY )

// Macro for enabling interrupts.
#define taskENABLE_INTERRUPTS()                                                \
    CPU_REG_SET( CPU_BASEPRI, 0 )

// Macro for entering a critical section.
#define taskENTER_CRITICAL() vPortEnterCritical()
    
// Macro for entering a critical section within an ISR.
#define taskENTER_CRITICAL_FROM_ISR() taskENTER_CRITICAL()

// Macro for exiting a critical section.
#define taskEXIT_CRITICAL() vPortExitCritical()
    
// Macro for exiting a critical section within an ISR.
#define taskEXIT_CRITICAL_FROM_ISR() taskEXIT_CRITICAL()

// Scheduler states.
#define taskSCHEDULER_SUSPENDED         0
#define taskSCHEDULER_NOT_STARTED       1
#define taskSCHEDULER_RUNNING           2

// Creates a regular task.
#define xTaskCreate( pvTaskCode, pcName, usStackDepth, pvParameters,           \
    uxPriority, pxCreatedTask )                                                \
    xTaskGenericCreate( pvTaskCode, pcName, usStackDepth, pvParameters,        \
        uxPriority, pxCreatedTask, NULL, NULL )

// Creates a task that uses an MPU.
#define xTaskCreateRestricted( x, pxCreatedTask )                              \
    xTaskGenericCreate( (x)->pvTaskCode, (x)->pcName, (x)->usStackDepth,       \
        (x)->pvParameters, (x)->uxPriority, pxCreatedTask,                     \
        (x)->puxStackBuffer, (x)->xRegions )

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

// Definition of a task handle to be used outside of task.c.
typedef void * TaskHandle_t;

// Prototype of the application task hook functions.
typedef BaseType_t ( *TaskHookFunction_t )( void * );

// Task states returned by eTaskGetState.
typedef enum
{
    // A task is querying the state of itself, so must be running.
    eRunning = 0,
    // The task being queried is in a ready or pending ready list.
    eReady,
    // The task being queried is in the Blocked state.
    eBlocked,
    // The task being queried is in the Suspended state,
    // or is in the Blocked state with an infinite time out.
    eSuspended,
    // The task being queried has been deleted,
    // but its TCB has not yet been freed.
    eDeleted
} eTaskState;

// Structure used for task timeout.
typedef struct xTIME_OUT
{
    // Number of overflows upon setting the timeout structure.
    BaseType_t xOverflowCount;
    // Tick counter upon setting the timeout structure.
    TickType_t xTimeOnEntering;
} TimeOut_t;

// Definition of memory ranges allocated to the task when an MPU is used.
typedef struct xMEMORY_REGION
{
    // Base address of the region.
    void *pvBaseAddress;
    // Region length in bytes.
    UBaseType_t ulLengthInBytes;
    //
    UBaseType_t ulParameters;
} MemoryRegion_t;

// Parameters required to create an MPU protected task.
typedef struct xTASK_PARAMETERS
{
    // Pointer to task function code.
    TaskFunction_t pvTaskCode;
    // Name of the task.
    const char * const pcName;
    // Stack depth.
    unsigned int usStackDepth;
    // Task function parameters.
    void *pvParameters;
    // Starting priority of the task.
    UBaseType_t uxPriority;
    // Pointer to the task stack.
    StackType_t *puxStackBuffer;
    // Memory regions structure.
    MemoryRegion_t xRegions[ portNUM_CONFIGURABLE_REGIONS ];
} TaskParameters_t;

// Used with the uxTaskGetSystemState() function
// to return the state of each task in the system.
typedef struct xTASK_STATUS
{
    // The handle of the task.
    TaskHandle_t xHandle;
    // A pointer to the task's name.
    const char *pcTaskName;
    // A number unique to the task.
    UBaseType_t xTaskNumber;
    // The state in which the task exited when the structure was populated.
    eTaskState eCurrentState;
    // The priority of the task when the structure was populated.
    UBaseType_t uxCurrentPriority;
    // The base priority of the task when the structure was populated.
    UBaseType_t uxBasePriority;
    // The total run time allocated to the task so far.
    uint32_t ulRunTimeCounter;
    // The minimum amount of stack space that has remained for the task.
    uint16_t usStackHighWaterMark;
} TaskStatus_t;

// Possible return values for eTaskConfirmSleepModeStatus().
typedef enum
{
    // A task has been made ready or a context switch pended
    // since portSUPPORESS_TICKS_AND_SLEEP() was called
    // - abort entering a sleep mode.
    eAbortSleep = 0,
    // Enter a sleep mode that will not last longer than the expected idle time.
    eStandardSleep,
    // No tasks are waiting for a timeout
    // so it is safe to enter a sleep mode
    // that can only be exited by an external interrupt.
    eNoTasksWaitingTimeout
} eSleepModeStatus;

// Task control block structure.
// All relevant information about a task is located here.
typedef struct tskTaskControlBlock
{
    // Pointer to the last item placen on the stack.
    // This must be the first member of the TCB structure.
    volatile StackType_t          *pxTopOfStack;

    // List item for ready/blocked/suspended task lists.
    ListItem_t                    xGenericListItem;
    // List item for event task lists.
    ListItem_t                    xEventListItem;

    // Priority of the task.
    BaseType_t                    uxPriority;
    // Priority last assigned to the task, used for priority inheritance.
    BaseType_t                    uxBasePriority;

    // Pointer to the start of the stack.
    StackType_t                   *pxStack;
    // Depth of the allocated stack.
    unsigned int                  usStackDepth;

    // Descriptive name of the task, for debug purposes only.
    char                          pcTaskName[ configMAX_TASK_NAME_LEN ];
} tskTCB;

// Redefine the task name to the new version,
// and keep the old one for backward compatibility.
typedef tskTCB TCB_t;

/******************************************************************************
 * Global variable declarations.                                              *
 ******************************************************************************/

// TCB of the currently running task.
extern TCB_t * volatile pxCurrentTCB;

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Creates a generic task. Will initialise all TCB fields and stack.
BaseType_t xTaskGenericCreate(
    TaskFunction_t pxTaskCode,
    const char * const pcName,
    int usStackDepth,
    void * const pvParameters,
    UBaseType_t uxPriority,
    TaskHandle_t * const pxCreatedTask,
    StackType_t * const puxStackBuffer,
    const MemoryRegion_t * const xRegions
    );

// Pends a task to be terminated. It will be deleted in the idle task.
void vTaskDelete( TaskHandle_t xTaskToDelete );

// Delays a task for a number of ticks.
void vTaskDelay( const TickType_t xTicksToDelay );

// Delays a task until the desired time.
void vTaskDelayUntil( TickType_t * const pxPreviousWakeTime,
    const TickType_t xTimeIncrement );

// Returns the priority of a task.
UBaseType_t uxTaskPriorityGet( TaskHandle_t pxTask );

// Sets the priority of a task.
void vTaskPrioritySet( TaskHandle_t pxTask, UBaseType_t uxNewPriority );

// Suspends a task.
void vTaskSuspend( TaskHandle_t xTaskToSuspend );

// Resumes a suspended task.
void vTaskResume( TaskHandle_t pxTaskToResume );

// Resumes a suspended task, can be called from an ISR.
BaseType_t xTaskResumeFromISR( TaskHandle_t pxTaskToResume );

// Starts the scheduler, allowing tasks to execute.
void vTaskStartScheduler();

// Stops the scheduler. All tasks will stop executing.
void vTaskEndScheduler();

// Suspends all ready tasks.
void vTaskSuspendAll();

// Resumes all tasks that were suspended by vTaskSuspendAll().
BaseType_t xTaskResumeAll();

// Returns the current tick count.
TickType_t xTaskGetTickCount();

// Returns the current tick count, can be called from within an ISR.
TickType_t xTaskGetTickCountFromISR();

// Returns the current number of tasks
UBaseType_t uxTaskGetNumberOfTasks();

// Increments the SysTick.
// Checks the delayed list for potential tasks that need to be unblocked.
BaseType_t xTaskIncrementTick();

// Switches the context of the currently running task with the new one.
void vTaskSwitchContext();

// Places the running task on an event list.
// This function must be called with either interrupts disabled
// or the scheduler suspended and the queue being access locked.
void vTaskPlaceOnEventList( List_t * const pxEventList,
    const TickType_t xTicksToWait );
    
// Places the current task on an unordered event list.
// This function must be called with the scheduler suspended.
// It is used by the event groups implementation.
void vTaskPlaceOnUnorderedEventList( List_t * const pxEventList,
    const TickType_t xItemValue, const TickType_t xTicksToWait );
    
// Places the running task on an event list - restricted version.
// This function should not be called by application code.
// It is intended to be called by the kernel, and in a critical section
void vTaskPlaceOnEventListRestricted( List_t * const pxEventList,
    const TickType_t xTicksToWait );

// Removes one task from an event list and places it in the ready list.
// This function must be called from a critical section, even from an ISR.
BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList );

// Function for removing one task from an unordered event list.
// This function must be called with the scheduler suspended.
// It is used by the event flags implementation.
BaseType_t xTaskRemoveFromUnorderedEventList( ListItem_t *pxEventListItem,
    TickType_t xItemValue );

// Sets the given timeout state, so it can be used later when checking timeout.
void vTaskSetTimeOutState( TimeOut_t *pxTimeOut );

// Checks for timeout with the given timeout state.
BaseType_t xTaskCheckForTimeOut( TimeOut_t *pxTimeOut,
    TickType_t *pxTicksToWait );

// Schedules a yield.
void vTaskMissedYield();

//Returns a handle for the current task.
TaskHandle_t xTaskGetCurrentTaskHandle();

// Returns the current scheduler state.
BaseType_t xTaskGetSchedulerState();

// Inherits the current task's priority to the given task.
void vTaskPriorityInherit( TaskHandle_t pxMutexHolder );

// Disinherits the inherited priority.
void vTaskPriorityDisinherit( TaskHandle_t pxMutexHolder );

// Resets the value of the event list item of the current task.
TickType_t uxTaskResetEventItemValue();

#endif