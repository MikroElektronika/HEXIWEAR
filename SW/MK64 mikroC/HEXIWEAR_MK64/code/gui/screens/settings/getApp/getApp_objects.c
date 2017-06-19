// File: getApp_objects.c

// Definitions of objects used in the getApp gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "getApp_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t getAppScreen =
{
    &hapticScreen,     // .navigation.up
    &aboutScreen,      // .navigation.down
    &settingsScreen,   // .navigation.left
    &googleAppScreen,  // .navigation.right

    getApp_screen_bmp, // .image

    NULL,              // .initFunction
    NULL,              // .createTaskFunction
    NULL               // .destroyTaskFunction
};