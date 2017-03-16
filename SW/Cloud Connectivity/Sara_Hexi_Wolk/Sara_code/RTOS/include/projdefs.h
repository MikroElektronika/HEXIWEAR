// File: projdefs.h

// Some general definitions for the FreeRTOS implementation.

#ifndef _projdefs_h_
#define _projdefs_h_

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

#define NULL                                  0

#define pdFALSE                               0
#define pdTRUE                                1

#define pdPASS                                ( pdTRUE )
#define pdFAIL                                ( pdFALSE )
#define errQUEUE_EMPTY                        ( 0 )
#define errQUEUE_FULL                         ( 0 )

// Error definitions.
#define errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ( -1 )
#define errQUEUE_BLOCKED                      ( -4 )
#define errQUEUE_YIELD                        ( -5 )

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

// The prototype to which task functions must conform.
// Defined here to ensure it is known before portable.h is included.
typedef void ( *TaskFunction_t )( void * );

#endif