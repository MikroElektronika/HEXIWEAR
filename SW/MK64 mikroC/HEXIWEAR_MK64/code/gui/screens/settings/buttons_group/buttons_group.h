// File: buttons_group.h

// Declarations of main functionalities in the buttons group gui module.

#ifndef _buttons_group_h_
#define _buttons_group_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define BUTTONS_GROUP_STACK_SIZE ( 0x500 )
#define BUTTONS_GROUP_PRIO       ( HEXIWEAR_GUI_PRIO )

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    buttonsGroup_left   = 0,
    buttonsGroup_right  = 1,
}
buttonsGroup_t;

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// screens
extern guiScreen_t buttonsGroupScreen;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////
 
// Creates the event for updating the active button group.
void buttonsGroup_CreateActiveUpdateEvent();

// Gets active button group.
buttonsGroup_t buttonsGroup_CurrentActiveGet();

// Sends the request to KW40.
void buttonsGroup_SendGetActiveReq();

// Sends the request for toggling the active group.
void buttonsGroup_SendToggleActiveReq();

// Waits for the update.
osa_status_t buttonsGroup_WaitForActiveUpdate( uint32_t timeout );

// Destroys the button group GUI update task.
osa_status_t buttonsGroup_ActiveUpdate( buttonsGroup_t buttonsGroupActive );

#endif