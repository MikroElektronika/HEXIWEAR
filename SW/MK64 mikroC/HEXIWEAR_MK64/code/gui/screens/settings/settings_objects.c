// File: settings_objects.c

// Definitions of objects used in the settings gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "settings_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t settingsScreen =
{
    &notifScreen,          // .navigation.up
    // &appsScreen,        // .navigation.up
    &gui_sensorTag_screen, // .navigation.down
    &watchScreen,          // .navigation.left
    &bluetoothScreen,      // .navigation.right

    settings_screen_bmp,   // .image

    NULL,                  // .initFunction
    NULL,                  // .createTaskFunction
    NULL                   // .destroyTaskFunction
};