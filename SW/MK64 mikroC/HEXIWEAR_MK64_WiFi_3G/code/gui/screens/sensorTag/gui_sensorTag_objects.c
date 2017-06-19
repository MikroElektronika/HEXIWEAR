// File: gui_sensorTag_objects.c

// Definitions of objects in the sensor tag gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "screens_common.h"
#include "gui_sensorTag_private.h"
#include "gui_sensorTag.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t gui_sensorTag_screen =
{
    &settingsScreen,            // .navigation.up
    &appsScreen,                // .navigation.down
    &watchScreen,               // .navigation.left
    NULL,                       // .navigation.right

    gui_sensorTag_blank_bmp,    // .image

    gui_sensorTag_Init,         // .initFunction
    gui_sensorTag_CreateTasks,  // .createTaskFunction
    gui_sensorTag_DestroyTasks  // .destroyTaskFunction
};

guiImage_t gui_sensorTag_icon =
{
    24,                    // .dynamicArea.xCrd
    23,                    // .dynamicArea.yCrd
    0,                     // .dynamicArea.xCrd
    0,                     // .dynamicArea.yCrd
    NULL,                  // .dynamicArea.areaBuffer

    gui_sensorTag_off_bmp  // .img
};