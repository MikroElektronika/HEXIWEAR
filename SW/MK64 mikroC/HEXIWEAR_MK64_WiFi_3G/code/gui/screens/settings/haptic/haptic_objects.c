// File: haptic_objects.c

// Definitions of objects used in the haptic gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "haptic_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// haptic screen structure
guiScreen_t hapticScreen =
{
    &buttonsGroupScreen, // .navigation.up
    &getAppScreen,       // .navigation.down
    &settingsScreen,     // .navigation.left
    NULL,                // .navigation.right

    haptic_screen_bmp,   // .image

    haptic_Init,         // .initFunction
    haptic_CreateTasks,  // .createTaskFunction
    haptic_DestroyTasks  // .destroyTaskFunction
};

guiImage_t haptic_icon =
{
    24,                   // .dynamicArea.xCrd
    23,                   // .dynamicArea.yCrd
    0,                    // .dynamicArea.width
    0,                    // .dynamicArea.height
    NULL,                 // .dynamicArea.areaBuffer

    haptic_icon_blue_bmp  // .img
};