// File: about_objects.c

// Definitions of objects used in the about gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "about_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t aboutScreen =
{
    &getAppScreen,    // .navigation.up
    &resetScreen,     // .navigation.down
    &settingsScreen,  // .navigation.left
    &infoScreen,      // .navigation.right

    about_screen_bmp, // .image

    NULL,             // .initFunction
    NULL,             // .createTaskFunction
    NULL              // .destroyTaskFunction
};


guiImage_t about_qrHexiwearIcon =
{
    9,                    // .dynamicArea.xCrd
    3,                    // .dynamicArea.yCrd
    0,                    // .dynamicArea.width
    0,                    // .dynamicArea.height
    NULL,                 // .dynamicArea.areaBuffer
    about_qrHexiwear_bmp  // .img
};