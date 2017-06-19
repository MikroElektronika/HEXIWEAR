// File: haptic.h

// Declarations of main functionalities in the haptic gui module.

#ifndef _haptic_h_
#define _haptic_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define HAPTIC_STACK_SIZE ( 0x500 )
#define HAPTIC_PRIO       ( HEXIWEAR_GUI_PRIO )

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    hapticState_disable  = 0,
    hapticState_enable   = 1

} hapticState_t;

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// screens
extern guiScreen_t hapticScreen;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Performs a haptic vibration.
void haptic_Run();

// Vibrates if needed.
void haptic_Vibrate();

// Creates the mutex to ensure the exclusive right to haptic feedback.
osa_status_t haptic_MutexCreate();

// Takes the haptic feedback mutex.
osa_status_t haptic_MutexLock( uint32_t timeout );

// Releases the haptic feedback mutex.
osa_status_t haptic_MutexUnlock();

// Gets current haptic feedback state.
hapticState_t haptic_CurrentStateGet();

// Checks if haptic feedback should be enabled at startup.
void haptic_CheckAtStartup();

#endif