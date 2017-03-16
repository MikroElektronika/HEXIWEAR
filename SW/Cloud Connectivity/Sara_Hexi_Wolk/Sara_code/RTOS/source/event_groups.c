// File: event_groups.c

// Implementation for the event groups functionalities.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/
 
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "event_groups.h"

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

// Bitfields for control information in a task's event list item value.
#define eventCLEAR_EVENTS_ON_EXIT_BIT   0x01000000UL
#define eventUNBLOCKED_DUE_TO_BIT_SET   0x02000000UL
#define eventWAIT_FOR_ALL_BITS          0x04000000UL
#define eventEVENT_BITS_CONTROL_BYTES   0xff000000UL

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

// Structure for defining an event group.
typedef struct xEventGroupDefinition
{
    // Bits that tasks in this group are waiting for.
    EventBits_t uxEventBits;
    // List of tasks waiting in this group.
    List_t xTasksWaitingForBits;
} EventGroup_t;

/******************************************************************************
 * Static function definitions.                                               *
 ******************************************************************************/

// Tests the waiting condition by comparing
// the current event bits with the bits to wait for.
static BaseType_t prvTestWaitCondition( const EventBits_t uxCurrentEventBits,
    const EventBits_t uxBitsToWaitFor, const BaseType_t xWaitForAllBits )
{
    BaseType_t xWaitConditionMet = pdFALSE;
    
    // Should we wait for just one of the given bits, or all of them?
    if( xWaitForAllBits == pdFALSE )
    {
        // Waiting for any one of the given bits.
        if( ( uxCurrentEventBits & uxBitsToWaitFor ) != 0 )
            xWaitConditionMet = pdTRUE;
    }
    else
    {
        // Waiting for all of the givent bits.
        if( ( uxCurrentEventBits & uxBitsToWaitFor ) == uxBitsToWaitFor )
            xWaitConditionMet = pdTRUE;
    }
    
    return xWaitConditionMet;
}

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/
 
// Creates an event group.
EventGroupHandle_t xEventGroupCreate()
{
    EventGroup_t *pxEventBits;
    
    pxEventBits = pvPortMalloc( sizeof( EventGroup_t ) );
    if( pxEventBits != NULL )
    {
        pxEventBits->uxEventBits = 0;
        vListInitialise( &( pxEventBits->xTasksWaitingForBits ) );
    }
    
    return ( EventGroupHandle_t ) pxEventBits;
}

// Synchronise with the event group, which means setting some bits
// and waiting for some others.
EventBits_t xEventGroupSync( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToSet,
    const EventBits_t uxBitsToWaitFor,
    TickType_t xTicksToWait
    )
{
    EventBits_t uxOriginalBitValue, uxReturn;
    EventGroup_t *pxEventBits = ( EventGroup_t * ) xEventGroup;
    BaseType_t xAlreadyYielded;

    // Check if the user is not attempting to wait for bits used by the kernel.
    configASSERT( ( uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0 );
    // Check if at least one bit is being waited on.
    configASSERT( uxBitsToWaitFor != 0 );
    // Check if the scheduler is suspended while the wait time is non-zero.
    configASSERT( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED )
        && ( xTicksToWait != 0 ) ) );

    vTaskSuspendAll();
    {
        uxOriginalBitValue = pxEventBits->uxEventBits;

        xEventGroupSetBits( xEventGroup, uxBitsToSet );

        if( ( ( uxOriginalBitValue | uxBitsToSet ) & uxBitsToWaitFor )
            == uxBitsToWaitFor )
        {
            // All the bits are set, no need to block.
            uxReturn = uxOriginalBitValue | uxBitsToSet;

            // Always clear the bits.
            pxEventBits->uxEventBits &= ~uxBitsToWaitFor; // '~' ?

            xTicksToWait = 0;
        }
        else if( xTicksToWait != 0 )
        {
            // Store the bits that the task is waiting for
            // in its event list item, then block the task.
            vTaskPlaceOnUnorderedEventList(
                &( pxEventBits->xTasksWaitingForBits ),
                ( uxBitsToWaitFor | eventCLEAR_EVENTS_ON_EXIT_BIT
                | eventWAIT_FOR_ALL_BITS ), xTicksToWait );

            uxReturn = 0;
        }
        else
        {
            // The bits were not set, but no wait time is specified.
            // Return the current event bit value.
            uxReturn = pxEventBits->uxEventBits;
        }
    }
    xAlreadyYielded = xTaskResumeAll();

    if( xTicksToWait != 0 )
    {
        if( xAlreadyYielded == pdFALSE )
            taskYIELD();

        // Retrieve the required bits from the task's event list item,
        // then reset them.
        uxReturn = uxTaskResetEventItemValue();

        if( ( uxReturn & eventUNBLOCKED_DUE_TO_BIT_SET ) == 0 )
        {
            taskENTER_CRITICAL();
            {
                // The task timed out, just return the current event bit value.
                uxReturn = pxEventBits->uxEventBits;

                // It is possible that the event bits were updated
                // between the task leaving the blocked state and running again.
                if( ( uxReturn & uxBitsToWaitFor ) == uxBitsToWaitFor )
                    pxEventBits->uxEventBits &= ~uxBitsToWaitFor;
            }
            taskEXIT_CRITICAL();
        }
        else
        {
            // The task unblocked because the bits were set.
            // Clear the control bits and return the value.
            uxReturn &= ~eventEVENT_BITS_CONTROL_BYTES;
        }
    }

    return uxReturn;
}

// Makes the calling task wait on the given event bits in the given event group.
EventBits_t xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToWaitFor,
    const BaseType_t xClearOnExit,
    const BaseType_t xWaitForAllBits,
    TickType_t xTicksToWait
    )
{
    EventGroup_t *pxEventBits = ( EventGroup_t * ) xEventGroup;
    EventBits_t uxReturn, uxControlBits = 0;
    BaseType_t xWaitConditionMet, xAlreadyYielded;
    
    // Check if the bits aren't used by the kernel itself.
    configASSERT( ( uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0 );
    // Check if at least one bit is being waited on.
    configASSERT( uxBitsToWaitFor != 0 );
    // Check if the scheduler is suspended while the wait time is non-zero.
    configASSERT( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED )
        && ( xTicksToWait != 0 ) ) );
        
    vTaskSuspendAll();
    {
        EventBits_t uxCurrentEventBits = pxEventBits->uxEventBits;
        
        // Check to see if the wait condition is already met.
        xWaitConditionMet = prvTestWaitCondition( uxCurrentEventBits,
            uxBitsToWaitFor, xWaitForAllBits );

        if( xWaitConditionMet != pdFALSE )
        {
            // The wait condition has already been met.
            uxReturn = uxCurrentEventBits;
            xTicksToWait = 0;
            
            // Clear the bits if needed.
            if( xClearOnExit != pdFALSE )
                pxEventBits->uxEventBits &= ~uxBitsToWaitFor;
        }
        else if( xTicksToWait == 0 )
        {
            // The wait condition has not been met, but the wait time is zero.
            uxReturn = uxCurrentEventBits;
        }
        else
        {
            // Task is going to block to wait for the required bits.
            // uxControlBits are used to remember the specifics of this call
            // for when the task is unblocked.
            if( xClearOnExit != pdFALSE )
                uxControlBits |= eventCLEAR_EVENTS_ON_EXIT_BIT;

            if( xWaitForAllBits != pdFALSE )
                uxControlBits |= eventWAIT_FOR_ALL_BITS;
                
            // Store the bits that the task is waiting for
            // in its event list item, then block the task.
            vTaskPlaceOnUnorderedEventList(
                &( pxEventBits->xTasksWaitingForBits ),
                ( uxBitsToWaitFor | uxControlBits ), xTicksToWait );

            uxReturn = 0;
        }
    }
    xAlreadyYielded = xTaskResumeAll();
    
    if( xTicksToWait != 0 )
    {
        if( xAlreadyYielded == pdFALSE )
            taskYIELD();

        // Retrieve the required bits from the task's event list item,
        // then reset them.
        uxReturn = uxTaskResetEventItemValue();
        
        if( ( uxReturn & eventUNBLOCKED_DUE_TO_BIT_SET ) == 0 )
        {
            taskENTER_CRITICAL();
            {
                // The task timed out, return the current event bit value.
                uxReturn = pxEventBits->uxEventBits;
                
                // It is possible that the event bits were updated
                // between the task leaving the blocked state and running again.
                if( prvTestWaitCondition(
                    uxReturn, uxBitsToWaitFor, xWaitForAllBits ) != pdFALSE )
                {
                    if( xClearOnExit != pdFALSE )
                        pxEventBits->uxEventBits &= ~uxBitsToWaitFor;
                }
            }
            taskEXIT_CRITICAL();
        }
        else
        {
            // The task unblocked because the bits were set.
            // Clear the control bits and return the value.
            uxReturn &= ~eventEVENT_BITS_CONTROL_BYTES;
        }
    }
    
    return uxReturn;
}

// Clears the given bits in the given event group.
EventBits_t xEventGroupClearBits( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToClear )
{
    EventGroup_t *pxEventBits = ( EventGroup_t * ) xEventGroup;
    EventBits_t uxReturn;
    
    // Check if the user is not attempting to clear bits used by the kernel.
    configASSERT( ( uxBitsToClear & eventEVENT_BITS_CONTROL_BYTES ) == 0 );
    
    taskENTER_CRITICAL();
    {
        // The return value is the current event group value.
        uxReturn = pxEventBits->uxEventBits;
        
        // Clear the bits.
        pxEventBits->uxEventBits &= ~uxBitsToClear;
    }
    taskEXIT_CRITICAL();
    
    return uxReturn;
}

// Clears the given bits in the given event group from ISR.
EventBits_t xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToClear )
{
    UBaseType_t uxSavedInterruptStatus;
    EventGroup_t *pxEventBits = ( EventGroup_t * ) xEventGroup;
    EventBits_t uxReturn;

    // Check if the user is not attempting to clear bits used by the kernel.
    configASSERT( ( uxBitsToClear & eventEVENT_BITS_CONTROL_BYTES ) == 0 );
    
    uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
    {
        // The return value is the current event group value.
        uxReturn = pxEventBits->uxEventBits;

        // Clear the bits.
        pxEventBits->uxEventBits &= ~uxBitsToClear;
    }
    portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );
    
    return uxReturn;
}

// Sets the given bits in the given event group.
EventBits_t xEventGroupSetBits( EventGroupHandle_t xEventGroup,
    const EventBits_t uxBitsToSet )
{
    ListItem_t *pxListItem, *pxNext;
    ListItem_t const *pxListEnd;
    List_t *pxList;
    EventBits_t uxBitsToClear = 0, uxBitsWaitedFor, uxControlBits;
    EventGroup_t *pxEventBits = ( EventGroup_t * ) xEventGroup;
    BaseType_t xMatchFound = pdFALSE;
    
    // Check if the user is not attempting to set bits used by the kernel.
    configASSERT( ( uxBitsToSet & eventEVENT_BITS_CONTROL_BYTES ) == 0 );
    
    pxList = &( pxEventBits->xTasksWaitingForBits );
    pxListEnd = listGET_END_MARKER( pxList );
    vTaskSuspendAll();
    {
        pxListItem = listGET_HEAD_ENTRY( pxList );
        
        // Set the bits.
        pxEventBits->uxEventBits |= uxBitsToSet;
        
        // See if the new bit value should unblock a task.
        while( pxListItem != pxListEnd )
        {
            pxNext = listGET_NEXT( pxListItem );
            uxBitsWaitedFor = listGET_LIST_ITEM_VALUE( pxListItem );
            xMatchFound = pdFALSE;
            
            // Split the bits waited for from the control bits.
            uxControlBits = uxBitsWaitedFor & eventEVENT_BITS_CONTROL_BYTES;
            uxBitsWaitedFor &= ~eventEVENT_BITS_CONTROL_BYTES;
            
            if( ( uxControlBits & eventWAIT_FOR_ALL_BITS ) == 0 )
            {
                // Just looking for a single bit being set.
                if( ( uxBitsWaitedFor & pxEventBits->uxEventBits ) != 0 )
                    xMatchFound = pdTRUE;
            }
            else if( ( uxBitsWaitedFor & pxEventBits->uxEventBits )
                == uxBitsWaitedFor )
            {
                // All bits are set.
                xMatchFound = pdTRUE;
            }
            
            if( xMatchFound != pdFALSE )
            {
                // The bits match. Should the bits be cleared on exit?
                if( ( uxControlBits & eventCLEAR_EVENTS_ON_EXIT_BIT ) != 0 )
                    uxBitsToClear |= uxBitsWaitedFor;

                // Store the event bits in the event list item value
                // before removing it to the list.
                // The bit eventUNBLOCKED_DUE_TO_BIT_SET is added
                // so the task knows it was unblocked rather than timed out.
                xTaskRemoveFromUnorderedEventList( pxListItem,
                    pxEventBits->uxEventBits | eventUNBLOCKED_DUE_TO_BIT_SET );
            }
            
            // Move onto the next list item.
            // Note that pxListItem->pxNext is not used here
            // as the item may have been removed from the event list
            // and inserted into the ready/pending ready list.
            pxListItem = pxNext;
        }
        
        // Clear any bits that matched
        // when eventCLEAR_EVENTS_ON_EXIT_BIT was set.
        pxEventBits->uxEventBits &= ~uxBitsToClear;
    }
    xTaskResumeAll();
    
    return pxEventBits->uxEventBits;
}

// Delete an event group.
void vEventGroupDelete( EventGroupHandle_t xEventGroup )
{
    EventGroup_t *pxEventBits = ( EventGroup_t * ) xEventGroup;
    const List_t *pxTasksWaitingForBits
        = &( pxEventBits->xTasksWaitingForBits );

    vTaskSuspendAll();
    {
        while( listCURRENT_LIST_LENGTH( pxTasksWaitingForBits ) > 0 )
        {
            // The event list is being deleted, unblock the task and return 0.

            configASSERT( pxTasksWaitingForBits->xListEnd.pxNext
                != ( ListItem_t * ) &( pxTasksWaitingForBits->xListEnd ) );

            xTaskRemoveFromUnorderedEventList(
                pxTasksWaitingForBits->xListEnd.pxNext,
                eventUNBLOCKED_DUE_TO_BIT_SET );
        }

        vPortFree( pxEventBits, sizeof( pxEventBits ) );
    }
    xTaskResumeAll();
}

// Execute a "set bits" command that was pended from an interrupt.
// For internal use only.
void vEventGroupSetBitsCallback( void *pvEventGroup,
    const unsigned long ulBitsToSet )
{
    xEventGroupSetBits( pvEventGroup, ( EventBits_t ) ulBitsToSet );
}