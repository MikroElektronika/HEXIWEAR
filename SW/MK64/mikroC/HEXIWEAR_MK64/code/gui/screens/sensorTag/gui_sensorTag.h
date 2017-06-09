// File: gui_sensorTag.h

// Declarations of main functionalities in the sensor tag gui module.

#ifndef _gui_sensorTag_h_
#define _gui_sensorTag_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

extern guiScreen_t gui_sensorTag_screen;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //s
////////////////////////////////////////////////////////////////////////////////

// Initialises sensor tag mode structures and tasks.
void gui_sensorTag_Init( void* param );

// Creates sensor tag mode task.
void gui_sensorTag_CreateTasks( void* param );

// Destroys sensor tag mode task.
void gui_sensorTag_DestroyTasks( void* param );

// Returns task state.
bool gui_sensorTag_IsActive();

// Turns on sensor tag.
void gui_sensorTag_TurnON();

// Turns off sensor tag.
void gui_sensorTag_TurnOFF();

// Checks if sensor tag should be enabled at startup.
void gui_sensorTag_CheckAtStartup();

#endif