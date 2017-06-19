// File: apps_objects.c

// Definitions of objects used in the apps gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "apps_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t appsScreen =
{
    &gui_sensorTag_screen,           // .navigation.up
    &notifScreen,                    // .navigation.down
    &watchScreen,                    // .navigation.left
    &gui_weatherStation_coverScreen, // .navigation.right

    apps_screen_bmp,                 // .image

    NULL,                            // .initFunction
    NULL,                            // .createTaskFunction
    NULL                             // .destroyTaskFunction
};