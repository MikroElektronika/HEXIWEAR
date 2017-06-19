// File: gui_notifications.h

// Declarations of main functionalities in the notifications gui module.

#ifndef _gui_notifications_h_
#define _gui_notifications_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "rtc_driver.h"
#include "gui_driver.h"
#include "notifications.h"
#include "screens_common.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////
 
// notifications screens
extern guiScreen_t notifScreen;
extern guiScreen_t notifMainScreen;

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises gui notifications module.
void gui_notifications_Init( void* param );

// Creates the gui notifications tasks.
void gui_notifications_CreateTasks( void* param );

// Destroys the gui notifications tasks.
void gui_notifications_DestroyTasks( void* param );

#endif