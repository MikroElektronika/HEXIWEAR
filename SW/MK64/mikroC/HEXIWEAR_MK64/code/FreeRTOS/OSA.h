// File: OSA.h

// Declaration of the abstractions of FreeRTOS functionalities.

#ifndef _OS_h_
#define _OS_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "event_groups.h"
//#include "croutine.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions                                                          //
////////////////////////////////////////////////////////////////////////////////

// Constant to pass as timeout value in order to wait indefinitely.
#define  OSA_WAIT_FOREVER  0xFFFFFFFFU

// OSA's time range in millisecond, OSA time wraps if exceeds this value.
#define FSL_OSA_TIME_RANGE 0xFFFFFFFFU

// The default interrupt handler installed in vector table.
#define OSA_DEFAULT_INT_HANDLER ( ( osa_int_handler_t )( &DefaultISR ) )

// Creates a task descriptor
// that is used to create the task with OSA_TaskCreate.
#define OSA_TASK_DEFINE(task, stackSize)                                       \
    task_stack_t* task##_stack = NULL;                                         \
    task_handler_t task##_task_handler

// To provide unified task piority for upper layer, OSA layer makes conversion.
#define PRIORITY_OSA_TO_RTOS(osa_prio)  (configMAX_PRIORITIES - (osa_prio) - 2)
#define PRIORITY_RTOS_TO_OSA(rtos_prio) (configMAX_PRIORITIES - (rtos_prio) - 2)

// This macro statically reserves the memory required for the queue.
#define MSG_QUEUE_DECLARE(name, number, size)                                  \
    msg_queue_t *name = NULL

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// Defines the return status of OSA's functions.
typedef enum _osa_status_t
{
    kStatus_OSA_Success = 0U, // Success
    kStatus_OSA_Error   = 1U, // Failed
    kStatus_OSA_Timeout = 2U, // Timeout occurs while waiting
    kStatus_OSA_Idle    = 3U  // Used for bare metal only, the wait object
                              // is not ready and timeout still not occur
} osa_status_t;

// The event flags are cleared automatically or manually.
typedef enum _osa_event_clear_mode_t
{
    kEventAutoClear    = 0U,  // The flags will be cleared automatically.
    kEventManualClear  = 1U   // The flags will be cleared manually.
} osa_event_clear_mode_t;

// Locks the task scheduler or disables interrupt in critical section.
typedef enum _osa_critical_section_mode_t
{
    kCriticalLockSched   = 0U,  // Lock scheduler in critical section.
    kCriticalDisableInt  = 1U   // Disable interrupt in critical selection.
} osa_critical_section_mode_t;

// OSA interrupt handler.
typedef void ( *osa_int_handler_t )();
 
// Type for a task handler, returned by the OSA_TaskCreate function.
typedef TaskHandle_t      task_handler_t;

// Type for a task stack.
typedef portSTACK_TYPE   task_stack_t;

// Type for task parameter.
typedef void* task_param_t;

// Type for a task function.
typedef pdTASK_CODE      task_t;

// Type for a mutex.
typedef xSemaphoreHandle mutex_t;

// Type for a semaphore.
typedef xSemaphoreHandle semaphore_t;

// Type for an event flags object.
typedef EventBits_t      event_flags_t;

// Type for an event group object in FreeRTOS.
typedef struct EventFreertos {
    EventGroupHandle_t eventHandler;    // FreeRTOS event handler.
    osa_event_clear_mode_t clearMode;   // Auto clear or manual clear.
} event_freertos;

// Type for an event group object.
typedef event_freertos event_t;

// Type for a message queue declaration and creation.
typedef xQueueHandle  msg_queue_t;

// Type for a message queue handler.
typedef xQueueHandle  msg_queue_handler_t;

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Counting semaphore:

// Creates a semaphore with a given value.
osa_status_t OSA_SemaCreate( semaphore_t *pSem, uint8_t initValue );

// Pends a semaphore with timeout.
osa_status_t OSA_SemaWait( semaphore_t *pSem, uint32_t timeout );

// Signals for someone waiting on the semaphore to wake up.
osa_status_t OSA_SemaPost( semaphore_t *pSem );

// Destroys a previously created semaphore.
osa_status_t OSA_SemaDestroy( semaphore_t *pSem );

// Mutex:

// Create an unlocked mutex.
osa_status_t OSA_MutexCreate( mutex_t *pMutex );

// Waits for a mutex and locks it.
osa_status_t OSA_MutexLock( mutex_t *pMutex, uint32_t timeout );

// Unlocks a previously locked mutex.
osa_status_t OSA_MutexUnlock( mutex_t *pMutex );

// Destroys a previously created mutex.
osa_status_t OSA_MutexDestroy( mutex_t *pMutex );

// Event signalling:

// Initialises an event object with all flags cleared.
osa_status_t OSA_EventCreate( event_t *pEvent,
    osa_event_clear_mode_t clearMode );

// Waits for specified event flags to be set.
osa_status_t OSA_EventWait(
    event_t       *pEvent,
    event_flags_t  flagsToWait,
    bool           waitAll,
    uint32_t       timeout,
    event_flags_t *setFlags
    );
    
// Sets one or more event flags.
osa_status_t OSA_EventSet( event_t *pEvent, event_flags_t flagsToSet );

// Clears one or more flags.
osa_status_t OSA_EventClear( event_t *pEvent, event_flags_t flagsToClear );

// Gets event flags status.
event_flags_t OSA_EventGetFlags( event_t *pEvent );

// Destroys a previously created event object.
osa_status_t OSA_EventDestroy( event_t *pEvent );

// Task management:

// Creates a task.
osa_status_t OSA_TaskCreate(
    task_t          task,
    uint8_t        *name,
    uint16_t        stackSize,
    task_stack_t   *stackMem,
    uint16_t        priority,
    task_param_t    param,
    bool            usesFloat,
    task_handler_t *handler
    );
    
// Destroys a previously created task.
osa_status_t OSA_TaskDestroy( task_handler_t handler );

// Puts the active task to the end of scheduler's queue.
osa_status_t OSA_TaskYield();

// Gets the handler of active task.
task_handler_t OSA_TaskGetHandler();

// Gets the priority of a task.
uint16_t OSA_TaskGetPriority(task_handler_t handler);

// Sets the priority of a task.
osa_status_t OSA_TaskSetPriority( task_handler_t handler, uint16_t priority );

// Message queues:

// Initialises a message queue.
msg_queue_handler_t OSA_MsgQCreate(
    msg_queue_t *queue,
    uint16_t  message_number,
    uint16_t  message_size
    );

// Puts a message at the end of the queue.
osa_status_t OSA_MsgQPut( msg_queue_handler_t handler, void* pMessage );

// Reads and removes a message at the head of the queue.
osa_status_t OSA_MsgQGet(
    msg_queue_handler_t handler,
    void               *pMessage,
    uint32_t            timeout
    );

// Destroys a previously created queue.
osa_status_t OSA_MsgQDestroy( msg_queue_handler_t handler );

// Memory management:

// Reserves the requested amount of memory in bytes.
void *OSA_MemAlloc( size_t size );

// Reserves the requested amount of memory in bytes and initialises it to 0.
void *OSA_MemAllocZero( size_t size );

// Releases the memory previously reserved.
osa_status_t OSA_MemFree( void *ptr );

// Time management:

// Delays execution for a number of milliseconds.
void OSA_TimeDelay( uint32_t delay );

// Gets the current time since system boot in milliseconds.
uint32_t OSA_TimeGetMsec();

// Interrupt management:

// Installs the interrupt handler.
osa_int_handler_t OSA_InstallIntHandler(
    int32_t IRQNumber,
    osa_int_handler_t handler
    );

// Critical section:

// Enters the critical section to ensure some code is not preempted.
void OSA_EnterCritical( osa_critical_section_mode_t mode );

// Exits the critical section.
void OSA_ExitCritical( osa_critical_section_mode_t mode );

// OSA initialise:

// Initialises the RTOS services.
osa_status_t OSA_Init();

// Starts the RTOS.
osa_status_t OSA_Start();

#endif