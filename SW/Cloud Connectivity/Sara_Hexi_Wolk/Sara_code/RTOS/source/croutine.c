// File: croutine.c

// Implementation for the co-routines functionality.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/

 // The initial state of the co-routine when it is created.
#define corINITIAL_STATE        ( 0 )

// Adds a coroutine to the ready queue.
#define prvAddCoRoutineToReadyQueue( pxCRCB )                                  \
{                                                                              \
        if( pxCRCB->uxPriority > uxTopCoRoutineReadyPriority )                 \
        {                                                                      \
                uxTopCoRoutineReadyPriority = pxCRCB->uxPriority;              \
        }                                                                      \
        vListInsertEnd(                                                        \
            ( List_t * ) &( pxReadyCoRoutineLists[ pxCRCB->uxPriority ] ),     \
            &( pxCRCB->xGenericListItem ) );                                   \
}

/******************************************************************************
 * Static variable definitions.                                               *
 ******************************************************************************/

// Lists of ready co-routines, organised by priority.
static List_t pxReadyCoRoutineLists[ configMAX_CO_ROUTINE_PRIORITIES ];
// Two lists that will be used for delayed co-routines.
static List_t xDelayedCoRoutineList1;
static List_t xDelayedCoRoutineList2;
// Pointer to the current list of delayed co-routines.
static List_t * pxDelayedCoRoutineList;
// Pointer to the overflowed list of delayed co-routines.
static List_t * pxOverflowDelayedCoRoutineList;
// List of co-routines that are pending to be put in the ready lists.
static List_t xPendingReadyCoRoutineList;

// Currently running co-routine.
CRCB_t * pxCurrentCoRoutine = NULL;
// Highest priority of a ready co-routine.
static UBaseType_t uxTopCoRoutineReadyPriority = 0;
// Co-routine tick counter.
static TickType_t xCoRoutineTickCount = 0;
// Last value of the co-routine tick counter.
static TickType_t xLastTickCount = 0;
// Number of ticks passed between current task tick and the last tick counter.
static TickType_t xPassedTicks = 0;

/******************************************************************************
 * Static function definitions.                                               *
 ******************************************************************************/

// Initialises all the lists used by co-routines.
static void prvInitialiseCoRoutineLists()
{
    UBaseType_t uxPriority;
    
    // Initialise all the ready lists.
    for( uxPriority = 0; uxPriority < configMAX_CO_ROUTINE_PRIORITIES;
        uxPriority++ )
    {
        vListInitialise(
            ( List_t * ) &( pxReadyCoRoutineLists[ uxPriority ] ) );
    }
    
    // Initialise the rest of the lists.
    vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
    vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
    vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );
    
    // Assign delayed lists to pointers.
    pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
    pxOverflowDelayedCoRoutineList = &xDelayedCoRoutineList2;
}

// Checks if there are co-routines waiting to be put in the ready lists.
static void prvCheckPendingReadyList()
{
    // Are there any co-routines that are pending to be put to the ready lists?
    // Since ISRs cannot access the ready lists,
    // they   will put the readied co-routines to the pending ready list.
    while( listLIST_IS_EMPTY( &xPendingReadyCoRoutineList ) == pdFALSE )
    {
        CRCB_t *pxUnblockedCRCB;
        
        // Disable interrupts, since ISRs can access the pending ready list.
        portDISABLE_INTERRUPTS();
        {
            // Remove the CRCB from the pending ready list.
            pxUnblockedCRCB = ( CRCB_t * ) listGET_OWNER_OF_HEAD_ENTRY(
                ( &xPendingReadyCoRoutineList ) );
            uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
        }
        portENABLE_INTERRUPTS();
        
        // Add the CRCB to the ready lists.
        uxListRemove( &( pxUnblockedCRCB->xGenericListItem ) );
        prvAddCoRoutineToReadyQueue( pxUnblockedCRCB );
    }
}

// Checks the delayed list for any co-routines that need to be readied.
// Also updates xCoRoutineTickCount, xLastTickCount and xPassedTicks.
static void prvCheckDelayedList()
{
    CRCB_t *pxCRCB;
    
    xPassedTicks = xTaskGetTickCount() - xLastTickCount;
    while( xPassedTicks > 0 )
    {
        xCoRoutineTickCount++;
        xPassedTicks--;
        
        // If the tick count has overflowed, the delay lists need to be swapped.
        if( xCoRoutineTickCount == 0 )
        {
            List_t *pxTemp;
            
            // Swap the delay lists. If there are any items
            // in the pxDelayedCoRoutineList then there is an error!
            pxTemp = pxDelayedCoRoutineList;
            pxDelayedCoRoutineList = pxOverflowDelayedCoRoutineList;
            pxOverflowDelayedCoRoutineList = pxTemp;
        }
        
        // Has a timeout expired?
        while( listLIST_IS_EMPTY( pxDelayedCoRoutineList ) == pdFALSE )
        {
            pxCRCB = ( CRCB_t * ) listGET_OWNER_OF_HEAD_ENTRY(
                pxDelayedCoRoutineList );

            if( xCoRoutineTickCount
                < listGET_LIST_ITEM_VALUE( &( pxCRCB->xGenericListItem ) ) )
            {
                // Timeout hasn't expired yet.
                break;
            }
            
            portDISABLE_INTERRUPTS();
            {
                // The event could have occurred before this critical section.
                // In that case the generic list item will have been moved
                // to the pending ready list, so the following line is valid.
                // Also the pvContainer will have been set to NULL.
                uxListRemove( &( pxCRCB->xGenericListItem ) );
                
                // Is the co-routine also waiting on an event?
                if( pxCRCB->xEventListItem.pvContainer != NULL )
                    uxListRemove( &( pxCRCB->xEventListItem ) );
            }
            portENABLE_INTERRUPTS();
            
            prvAddCoRoutineToReadyQueue( pxCRCB );
        }
    }
    
    xLastTickCount = xCoRoutineTickCount;
}

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/

// Creates a co-routine for the given function.
BaseType_t xCoRoutineCreate( crCOROUTINE_CODE pxCoRoutineCode,
    UBaseType_t uxPriority, UBaseType_t uxIndex )
{
    BaseType_t xReturn;
    CRCB_t *pxCoRoutine;

    // Allocate the memory for the CRCB.
    pxCoRoutine = ( CRCB_t * ) pvPortMalloc( sizeof( CRCB_t ) );
    if( pxCoRoutine != NULL )
    {
        // If this is the first co-routine created
        // the co-routine lists need to be initialised.
        if( pxCurrentCoRoutine == NULL )
        {
            pxCurrentCoRoutine = pxCoRoutine;
            prvInitialiseCoRoutineLists();
        }

        // Is the priority within limits?
        if( uxPriority >= configMAX_CO_ROUTINE_PRIORITIES )
            uxPriority = configMAX_CO_ROUTINE_PRIORITIES - 1;

        // Initialise the fields of the CRCB.
        pxCoRoutine->uxState = corINITIAL_STATE;
        pxCoRoutine->uxPriority = uxPriority;
        pxCoRoutine->uxIndex = uxIndex;
        pxCoRoutine->pxCoRoutineFunction = pxCoRoutineCode;

        // Initialise the list items.
        vListInitialiseItem( &( pxCoRoutine->xGenericListItem ) );
        vListInitialiseItem( &( pxCoRoutine->xEventListItem ) );

        listSET_LIST_ITEM_OWNER(
            &( pxCoRoutine->xGenericListItem ), pxCoRoutine );
        listSET_LIST_ITEM_OWNER(
            &( pxCoRoutine->xEventListItem ), pxCoRoutine );

        listSET_LIST_ITEM_VALUE( &( pxCoRoutine->xEventListItem ),
            configMAX_CO_ROUTINE_PRIORITIES - uxPriority );

        // Add the CRCB to the ready list.
        prvAddCoRoutineToReadyQueue( pxCoRoutine );

        xReturn = pdPASS;
    }
    else
    {
        xReturn = errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY;
    }

    return xReturn;
}

// Delays a co-routine for the given number of ticks.
// This function is only to be used within the kernel code.
void vCoRoutineAddToDelayedList( TickType_t xTicksToDelay, List_t *pxEventList )
{
    TickType_t xTimeToWake;

    // Calculate time to wake. This may overflow, but that's not a problem.
    xTimeToWake = xCoRoutineTickCount + xTicksToDelay;

    // Remove the co-routine from the ready list.
    uxListRemove( ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );

    // Set the list item value to the wake time.
    listSET_LIST_ITEM_VALUE(
        &( pxCurrentCoRoutine->xGenericListItem ), xTimeToWake );

    if( xTimeToWake < xCoRoutineTickCount )
    {
        // Wake time has overflowed. Place the item in the overflow list.
        vListInsert( ( List_t * ) pxOverflowDelayedCoRoutineList,
            ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
    }
    else
    {
        // Wake time has not overflowed. Place the item in the current list.
        vListInsert( ( List_t * ) pxDelayedCoRoutineList,
            ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
    }

    if( pxEventList )
    {
        // Also add the co-routine to an event list.
        // If this is done the function must be called with interrupts disabled.
        vListInsert( pxEventList, &( pxCurrentCoRoutine->xEventListItem ) );
    }
}

// Schedules the execution of a co-routine.
void vCoRoutineSchedule()
{
    // See if any co-routines readied by events need moving to the ready lists.
    prvCheckPendingReadyList();

    // See if any delayed co-routines have timed out.
    prvCheckDelayedList();

    // Find the highest priority list that contains ready co-routines.
    while( listLIST_IS_EMPTY(
        &( pxReadyCoRoutineLists[ uxTopCoRoutineReadyPriority ] ) ) )
    {
        if( uxTopCoRoutineReadyPriority == 0 )
        {
            // No more co-routines to check.
            return;
        }
        uxTopCoRoutineReadyPriority--;
    }

    // Walk through the ready list and get the next entry.
    // All the co-routines will get an equal share of the processor time.
    listGET_OWNER_OF_NEXT_ENTRY( pxCurrentCoRoutine,
        &( pxReadyCoRoutineLists[ uxTopCoRoutineReadyPriority ] ) );

    // Call the co-routine.
    ( pxCurrentCoRoutine->pxCoRoutineFunction )(
        pxCurrentCoRoutine, pxCurrentCoRoutine->uxIndex );

    return;
}

// Removes the highest priority co-routine from the event list
// and places it in the pending ready list.
// This function is only to be used within the kernel code.
BaseType_t xCoRoutineRemoveFromEventList( const List_t *pxEventList )
{
    CRCB_t *pxUnblockedCRCB;
    BaseType_t xReturn;

    // This function can only be called from within an interrupt.
    // It can only access event lists and the pending ready list.
    // pxEventList is assumed to not be empty.
    pxUnblockedCRCB = ( CRCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxEventList );
    uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
    vListInsertEnd( ( List_t * ) &( xPendingReadyCoRoutineList ),
        &( pxUnblockedCRCB->xEventListItem ) );

    if( pxUnblockedCRCB->uxPriority >= pxCurrentCoRoutine->uxPriority )
    {
        return pdTRUE;
    }
    else
    {
        return pdFALSE;
    }

    return xReturn;
}
