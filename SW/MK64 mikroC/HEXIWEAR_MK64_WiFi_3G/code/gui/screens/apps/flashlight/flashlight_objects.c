// File: flashlight_objects.c

// Definitions of objects used in the flashlight gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "apps/flashlight/flashlight_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// flashlight app screen
guiScreen_t flashlightScreen =
{
    &gui_motionControl_coverScreen, // .navigation.up
    &heartRateScreen,               // .navigation.down
    &appsScreen,                    // .navigation.left
    NULL,                           // .navigation.right

    flashlight_screen_bmp,          // .image

    flashlight_Init,         // .initFunction
    flashlight_CreateTasks,  // .createTaskFunction
    flashlight_DestroyTasks  // .destroyTaskFunction
};

guiImage_t flashlight_icon =
{
    24,                 // .dynamicArea.xCrd
    23,                 // .dynamicArea.yCrd
    0,                  // .dynamicArea.width
    0,                  // .dynamicArea.height
    NULL,               // .dynamicArea.areaBuffer
    flashlight_off_bmp  // .img
};