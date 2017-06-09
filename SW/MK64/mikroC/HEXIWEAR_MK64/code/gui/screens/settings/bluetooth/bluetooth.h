// File: bluetooth.h

// Declarations of main functionalities in the bluetooth gui module.

#ifndef _bluetooth_h_
#define _bluetooth_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define BLUETOOTH_STACK_SIZE ( 0x500 )
#define BLUETOOTH_PRIO       ( HEXIWEAR_GUI_PRIO )

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    bluetooth_advMode_disable  = 0,
    bluetooth_advMode_enable   = 1,
} bluetooth_advMode_t;

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// screens
extern guiScreen_t bluetoothScreen;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Creates the event for bluetooth update.
void bluetooth_CreateAdvModeUpdateEvent();

// Gets current advertisement mode.
bluetooth_advMode_t bluetooth_CurrentAdvModeGet();

// Sends request to get advertisement mode.
void bluetooth_SendGetAdvModeReq();

// Sends request to toggle advertisement mode.
void bluetooth_SendToggleAdvModeReq();

// Waits for the mode update.
osa_status_t bluetooth_WaitForAdvModeUpdate( uint32_t timeout );

osa_status_t bluetooth_AdvModeUpdate( bluetooth_advMode_t bluetooth_advMode );

#endif