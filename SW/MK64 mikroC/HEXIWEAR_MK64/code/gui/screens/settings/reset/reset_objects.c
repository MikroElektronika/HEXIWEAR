// File: reset_objects.c

// Definitions of objects used in the reset gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "reset_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t resetScreen =
{
    &aboutScreen,       // .navigation.up
    &bluetoothScreen,   // .navigation.down
    &settingsScreen,    // .navigation.left
    NULL,               // .navigation.right

    reset_screen_bmp,   // .image

    reset_Init,         // .initFunction
    reset_CreateTasks,  // .createTaskFunction
    reset_DestroyTasks  // .destroyTaskFunction
};