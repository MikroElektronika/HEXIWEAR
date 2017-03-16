// File: StackMacros.h

// Macro definitions for task stack manipulation.

#ifndef _StackMacros_h_
#define _StackMacros_h_

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

// Checks stack overflow of current task.
#define  taskFIRST_CHECK_FOR_STACK_OVERFLOW()                                  \
{                                                                              \
    /* Is the current task's stack pointer within the stack limit? */          \
    if( pxCurrentTCB->pxTopOfStack <= pxCurrentTCB->pxStack )                  \
    {                                                                          \
        /* vApplicationStackOverflowHook(); */                                 \
    }                                                                          \
}

#endif