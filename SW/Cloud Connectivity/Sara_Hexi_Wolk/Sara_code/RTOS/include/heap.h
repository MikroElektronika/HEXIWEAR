// file: heap.h

#ifndef _heap_h_
#define _heap_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "define.h"

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Function for allocating a required amount of memory.
void *pvPortMalloc( UBaseType_t xWantedSize );

// Function for deallocating a required amount of memory.
void vPortFree( void *pv, UBaseType_t xSize );

#endif