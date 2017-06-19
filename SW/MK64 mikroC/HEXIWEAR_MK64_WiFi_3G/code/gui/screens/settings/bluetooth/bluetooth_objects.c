// File: bluetooth_objects.c

// Definitions of objects in the bluetooth gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "bluetooth_private.h"
#include "settings/wireless_conn/wireless_common.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t bluetoothScreen =
{
    &wirelessScreen,            // .navigation.up
    &bootloaderCoverScreen, // .navigation.down
    &settingsScreen,        // .navigation.left
    NULL,                   // .navigation.right

    bluetooth_screen_bmp,   // .image

    bluetooth_Init,           // .initFunction
    bluetooth_CreateTasks,    // .createTaskFunction
    bluetooth_DestroyTasks    // .destroyTaskFunction
};

guiImage_t bluetooth_icon =
{
    24,                      // .dynamicArea.xCrd
    23,                      // .dynamicArea.yCrd
    0,                       // .dynamicArea.width
    0,                       // .dynamicArea.height
    NULL,                    // .dynamicArea.areaBuffer

    bluetooth_icon_blue_bmp  // .img
};