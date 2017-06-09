// File: buttons_group_objects.c

// Definitions of objects used in the buttons group gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "buttons_group_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t buttonsGroupScreen =
{
    &bootloaderCoverScreen,    // .navigation.up
    &hapticScreen,             // .navigation.down
    &settingsScreen,           // .navigation.left
    NULL,                      // .navigation.right

    buttons_group_screen_bmp,  // .image

    buttonsGroup_Init,         // .initFunction
    buttonsGroup_CreateTasks,  // .createTaskFunction
    buttonsGroup_DestroyTasks  // .destroyTaskFunction
};

guiImage_t buttonsGroup_img =
{
    24,                            // .dynamicArea.xCrd
    23,                            // .dynamicArea.yCrd
    0,                             // .dynamicArea.width
    0,                             // .dynamicArea.height
    NULL,                          // .dynamicArea.areaBuffer
    
    buttonGroup_rightSelected_bmp  // .img
};