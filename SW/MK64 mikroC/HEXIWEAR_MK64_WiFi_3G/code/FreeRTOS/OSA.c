// File: OSA.h

// Declaration of the abstractions of FreeRTOS functionalities.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <assert.h>

#include "OSA.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions                                                          //
////////////////////////////////////////////////////////////////////////////////

#define MSEC_TO_TICK( msec )                                                   \
    ( ( ( uint32_t )( msec ) + 500uL / ( uint32_t )configTICK_RATE_HZ )        \
      * ( uint32_t )configTICK_RATE_HZ / 1000uL )
      
#define TICKS_TO_MSEC( tick )                                                  \
    ( ( tick ) * 1000 / ( uint32_t )configTICK_RATE_HZ )

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Signals a semaphore from a task.
static osa_status_t OSA_SemaphorePostFromTask( semaphore_t *pSem )
{
    if( pdTRUE == xSemaphoreGive( *pSem ) )
    {
        return kStatus_OSA_Success;
    }
    else
    {
        return kStatus_OSA_Error;
    }
}

// Signals a semaphore from an ISR.
static osa_status_t OSA_SemaphorePostFromISR( semaphore_t *pSem )
{
    portBASE_TYPE taskToWake = pdFALSE;

    if( pdTRUE == xSemaphoreGiveFromISR( *pSem, &taskToWake ) )
    {
        if ( pdTRUE == taskToWake )
        {
            portYIELD();
        }
        return kStatus_OSA_Success;
    }
    else
    {
        return kStatus_OSA_Error;
    }
}

// Puts a message into the queue from a task.
static osa_status_t OSA_MessageQueuePutFromTask(
    msg_queue_handler_t handler, void* pMessage )
{
    if ( xQueueSendToBack( handler, pMessage, 0 ) != pdPASS )
    {
      return kStatus_OSA_Error;
    }
    else
    {
      return kStatus_OSA_Success;
    }
}

// Puts a message into the queue from an ISR.
static osa_status_t OSA_MessageQueuePutFromISR(
    msg_queue_handler_t handler, void* pMessage )
{
    portBASE_TYPE taskToWake = pdFALSE;

    if ( pdTRUE == xQueueSendToBackFromISR( handler, pMessage, &taskToWake ) )
    {
        if ( pdTRUE == taskToWake )
        {
            portYIELD();
        }
        return kStatus_OSA_Success;
    }
    else
    {
        return kStatus_OSA_Error;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Counting semaphore:

// Creates a semaphore with a given value.
osa_status_t OSA_SemaCreate( semaphore_t *pSem, uint8_t initValue )
{
    assert( pSem );
    
    *pSem = xSemaphoreCreateCounting( 0xFF, initValue );
    if( *pSem == NULL )
        return kStatus_OSA_Error;
    
    return kStatus_OSA_Success;
}

// Pends a semaphore with timeout.
osa_status_t OSA_SemaWait( semaphore_t *pSem, uint32_t timeout )
{
    uint32_t timeoutTicks;
    
    assert( pSem );
    
    // Convert timeout from millisecond to tick.
    if( timeout == OSA_WAIT_FOREVER )
        timeoutTicks = portMAX_DELAY;
    else
        timeoutTicks = MSEC_TO_TICK( timeout );
    
    // Check if this function is called within an interrupt routine or not.
    if (xPortIsInsideInterrupt() == pdFALSE)
    {
        if( xSemaphoreTake( *pSem, timeoutTicks ) == pdFALSE )
            return kStatus_OSA_Timeout;
    }
    else
    {
        if (xSemaphoreTakeFromISR(*pSem, NULL) == pdFALSE)
            return kStatus_OSA_Timeout;
    }

    return kStatus_OSA_Success;
}

// Signals for someone waiting on the semaphore to wake up.
osa_status_t OSA_SemaPost( semaphore_t *pSem )
{
    assert( pSem );
    
    if( CPU_REG_GET( CPU_IPSR ) != 0 )
        return OSA_SemaphorePostFromISR( pSem );
    else
        return OSA_SemaphorePostFromTask( pSem );
}

// Destroys a previously created semaphore.
osa_status_t OSA_SemaDestroy( semaphore_t *pSem )
{
    assert( pSem );
    assert( *pSem );
    
    vSemaphoreDelete( *pSem );
    return kStatus_OSA_Success;
}

// Mutex:

// Create an unlocked mutex.
osa_status_t OSA_MutexCreate( mutex_t *pMutex )
{
    assert( pMutex );

    *pMutex = xSemaphoreCreateMutex();
    if( *pMutex == NULL )
        return kStatus_OSA_Error;

    return kStatus_OSA_Success;
}

// Waits for a mutex and locks it.
osa_status_t OSA_MutexLock( mutex_t *pMutex, uint32_t timeout )
{
    uint32_t timeoutTicks;
    
    assert( pMutex );
    
    // If pMutex has been locked by current task, return error.
    if( xSemaphoreGetMutexHolder( *pMutex ) == xTaskGetCurrentTaskHandle() )
        return kStatus_OSA_Error;

    // Convert timeout from millisecond to tick.
    if( timeout == OSA_WAIT_FOREVER )
        timeoutTicks = portMAX_DELAY;
    else
        timeoutTicks = MSEC_TO_TICK( timeout );

    if( xSemaphoreTake( *pMutex, timeoutTicks ) != pdPASS )
        return kStatus_OSA_Timeout;

    return kStatus_OSA_Success;
}

// Unlocks a previously locked mutex.
osa_status_t OSA_MutexUnlock( mutex_t *pMutex )
{
    assert( pMutex );
    
    // If pMutex is not locked by current task, return error.
    if( xSemaphoreGetMutexHolder( *pMutex ) != xTaskGetCurrentTaskHandle() )
        return kStatus_OSA_Error;

    if( xSemaphoreGive( *pMutex ) != pdPASS )
        return kStatus_OSA_Error;

    return kStatus_OSA_Success;
}

// Destroys a previously created mutex.
osa_status_t OSA_MutexDestroy( mutex_t *pMutex )
{
    assert( pMutex );
    assert( *pMutex );
    
    vSemaphoreDelete( *pMutex );
    return kStatus_OSA_Success;
}

// Event signalling:

// Initialises an event object with all flags cleared.
osa_status_t OSA_EventCreate( event_t *pEvent,
    osa_event_clear_mode_t clearMode )
{
    assert( pEvent );
    
    pEvent->eventHandler = xEventGroupCreate();
    
    if( pEvent->eventHandler == NULL )
        return kStatus_OSA_Error;

    pEvent->clearMode = clearMode;
    return kStatus_OSA_Success;
}

// Waits for specified event flags to be set.
osa_status_t OSA_EventWait(
    event_t       *pEvent,
    event_flags_t  flagsToWait,
    bool           waitAll,
    uint32_t       timeout,
    event_flags_t *setFlags
    )
{
    BaseType_t clearMode;
    uint32_t timeoutTicks;
    event_flags_t flagsSave;

    assert( pEvent );
    
    // Convert timeout from millisecond to tick.
    if( timeout == OSA_WAIT_FOREVER )
        timeoutTicks = portMAX_DELAY;
    else
        timeoutTicks = MSEC_TO_TICK( timeout );

    clearMode = ( pEvent->clearMode == kEventAutoClear ) ? pdTRUE : pdFALSE;
    
    flagsSave = xEventGroupWaitBits(
        pEvent->eventHandler,
        flagsToWait,
        clearMode,
        ( BaseType_t )waitAll,
        timeoutTicks
        );

    *setFlags = flagsSave & flagsToWait;
    
    if( *setFlags )
        return kStatus_OSA_Success;
    else
        return kStatus_OSA_Timeout;
}

// Sets one or more event flags.
osa_status_t OSA_EventSet( event_t *pEvent, event_flags_t flagsToSet )
{
    portBASE_TYPE taskToWake = pdFALSE;

    assert( pEvent );
    
    if( CPU_REG_GET( CPU_IPSR ) != 0 )
    {
        xEventGroupSetBitsFromISR(
            pEvent->eventHandler, flagsToSet, &taskToWake );
        if( pdTRUE == taskToWake )
            portYIELD();
    }
    else
    {
        xEventGroupSetBits( pEvent->eventHandler, flagsToSet );
    }
    
    return kStatus_OSA_Success;
}

// Clears one or more flags.
osa_status_t OSA_EventClear( event_t *pEvent, event_flags_t flagsToClear )
{
    assert( pEvent );
    
    if( CPU_REG_GET( CPU_IPSR ) != 0 )
        xEventGroupClearBitsFromISR( pEvent->eventHandler, flagsToClear );
    else
        xEventGroupClearBits( pEvent->eventHandler, flagsToClear );
        
    return kStatus_OSA_Success;
}

// Gets event flags status.
event_flags_t OSA_EventGetFlags( event_t *pEvent )
{
    assert( pEvent );
    
    if( CPU_REG_GET( CPU_IPSR ) != 0 )
        return xEventGroupGetBitsFromISR(pEvent->eventHandler);
    else
        return xEventGroupGetBits(pEvent->eventHandler);
}

// Destroys a previously created event object.
osa_status_t OSA_EventDestroy( event_t *pEvent )
{
    assert( pEvent );
    
    vEventGroupDelete( pEvent );
    
    return kStatus_OSA_Success;
}

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
    )
{
    if( xTaskCreate(
            task,
            ( char const * )name,
            stackSize / sizeof( portSTACK_TYPE ),
            param,
            PRIORITY_OSA_TO_RTOS( priority ),
            handler
            ) != pdPASS )
        return kStatus_OSA_Error;

    return kStatus_OSA_Success;
}

// Destroys a previously created task.
osa_status_t OSA_TaskDestroy( task_handler_t handler )
{
    vTaskDelete( handler );
    
    return kStatus_OSA_Success;
}

// Puts the active task to the end of scheduler's queue.
osa_status_t OSA_TaskYield()
{
    taskYIELD();
    
    return kStatus_OSA_Success;
}

// Gets the handler of active task.
task_handler_t OSA_TaskGetHandler()
{
    return xTaskGetCurrentTaskHandle();
}

// Gets the priority of a task.
uint16_t OSA_TaskGetPriority(task_handler_t handler)
{
    return ( uint16_t )( PRIORITY_RTOS_TO_OSA( uxTaskPriorityGet( handler ) ) );
}

// Sets the priority of a task.
osa_status_t OSA_TaskSetPriority( task_handler_t handler, uint16_t priority )
{
    vTaskPrioritySet( handler, PRIORITY_OSA_TO_RTOS( priority ) );
    
    return kStatus_OSA_Success;
}

// Message queues:

// Initialises a message queue.
msg_queue_handler_t OSA_MsgQCreate(
    msg_queue_t *queue,
    uint16_t  message_number,
    uint16_t  message_size
    )
{
    return xQueueCreate( message_number, message_size * sizeof( uint32_t ) );
}

// Puts a message at the end of the queue.
osa_status_t OSA_MsgQPut( msg_queue_handler_t handler, void* pMessage )
{
    if( CPU_REG_GET( CPU_IPSR ) != 0 )
        return OSA_MessageQueuePutFromISR(handler, pMessage);
    else
        return OSA_MessageQueuePutFromTask(handler, pMessage);
}

// Reads and removes a message at the head of the queue.
osa_status_t OSA_MsgQGet(
    msg_queue_handler_t handler,
    void               *pMessage,
    uint32_t            timeout
    )
{
    uint32_t timeoutTicks;
    
    if( timeout == OSA_WAIT_FOREVER )
        timeoutTicks = portMAX_DELAY;
    else
        timeoutTicks = MSEC_TO_TICK( timeout );
        
    if( xQueueReceive( handler, pMessage, timeoutTicks ) != pdPASS )
        return kStatus_OSA_Timeout;

    return kStatus_OSA_Success;
}

// Destroys a previously created queue.
osa_status_t OSA_MsgQDestroy( msg_queue_handler_t handler )
{
    vQueueDelete( handler );
    
    return kStatus_OSA_Success;
}

// Memory management:

// Reserves the requested amount of memory in bytes.
void *OSA_MemAlloc( size_t size )
{
    return pvPortMalloc( size );
}

// Reserves the requested amount of memory in bytes and initialises it to 0.
void *OSA_MemAllocZero( size_t size )
{
    void *ptr = pvPortMalloc( size );
    
    if( ptr == NULL )
        return NULL;

    return memset( ptr, 0, size );
}

// Releases the memory previously reserved.
osa_status_t OSA_MemFree( void *ptr )
{
    vPortFree( ptr );
    
    return kStatus_OSA_Success;
}

// Time management:

// Delays execution for a number of milliseconds.
void OSA_TimeDelay( uint32_t delay )
{
    vTaskDelay( MSEC_TO_TICK( delay ) );
}

// Gets the current time since system boot in milliseconds.
uint32_t OSA_TimeGetMsec()
{
    portTickType ticks;
    
    if( CPU_REG_GET( CPU_IPSR ) != 0 )
        ticks = xTaskGetTickCountFromISR();
    else
        ticks = xTaskGetTickCount();

    return TICKS_TO_MSEC( ticks );
}

// Interrupt management:

// Installs the interrupt handler.
osa_int_handler_t OSA_InstallIntHandler(
    int32_t IRQNumber,
    osa_int_handler_t handler
    )
{
    return kStatus_OSA_Success;
}

// Critical section:

// Enters the critical section to ensure some code is not preempted.
void OSA_EnterCritical( osa_critical_section_mode_t mode )
{
    if( mode == kCriticalDisableInt )
        portENTER_CRITICAL();
    else
        vTaskSuspendAll();
}

// Exits the critical section.
void OSA_ExitCritical( osa_critical_section_mode_t mode )
{
    if( mode == kCriticalDisableInt )
        portEXIT_CRITICAL();
    else
        xTaskResumeAll();
}

// OSA initialise:

// Initialises the RTOS services.
osa_status_t OSA_Init()
{
    return kStatus_OSA_Success;
}

// Starts the RTOS.
osa_status_t OSA_Start()
{
    vTaskStartScheduler();
    
    return kStatus_OSA_Success;
}