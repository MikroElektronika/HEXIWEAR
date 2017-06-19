// File: wifi_objects.c

// Definitions of objects in the wifi gui module.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "gui_driver.h"
#include "screens_common.h"
#include "wireless_common.h"

/******************************************************************************
 * Global variable definitions.                                               *
 ******************************************************************************/

guiScreen_t wirelessScreen =
{
    &resetScreen,       // .navigation.up
    &bluetoothScreen,       // .navigation.down
    &settingsScreen,        // .navigation.left
    NULL,                   // .navigation.right

    wifi_screen_bmp,   // .image

    wireless_Init,           // .initFunction
    wireless_CreateTasks,    // .createTaskFunction
    wireless_DestroyTasks    // .destroyTaskFunction
};

guiImage_t wireless_icon =
{
    24,                      // .dynamicArea.xCrd
    23,                      // .dynamicArea.yCrd
    0,                       // .dynamicArea.width
    0,                       // .dynamicArea.height
    NULL,                    // .dynamicArea.areaBuffer

    none_icon_bmp  // .img
};