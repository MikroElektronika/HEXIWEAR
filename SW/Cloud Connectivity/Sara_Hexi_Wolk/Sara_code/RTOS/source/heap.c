// file: heap.c

// Functions for allocating and deallocating memory
// that can be safely used within multiple tasks.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

//extern void vApplicationMallocFailedHook();

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/

// Allocates the required amount of memory.
void *pvPortMalloc( UBaseType_t xWantedSize )
{
    void *pvReturn;

    vTaskSuspendAll();
    {
        pvReturn = Malloc( xWantedSize );
    }
    xTaskResumeAll();

    if( pvReturn == NULL )
    {
//        vApplicationMallocFailedHook();
    }

    return pvReturn;
}

// Deallocates the required amount of memory.
void vPortFree( void *pv, UBaseType_t xSize )
{
    if( pv )
    {
        vTaskSuspendAll();
        {
            Free( pv, xSize );
        }
        xTaskResumeAll();
    }
}