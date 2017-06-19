// File: googleApp_objects.c

// Definitions of objects used in the googleApp gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "googleApp_private.h"
#include "settings/getApp/getApp.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t googleAppScreen =
{
    &iOSAppScreen,          // .navigation.up
    &iOSAppScreen,          // .navigation.down
    &getAppScreen,          // .navigation.left
    &googleAppQrCodeScreen, // .navigation.right

    googleApp_screen_bmp,   // .image

    NULL,                   // .initFunction
    NULL,                   // .createTaskFunction
    NULL                    // .destroyTaskFunction
};


guiScreen_t googleAppQrCodeScreen =
{
    NULL,                       // .navigation.up
    NULL,                       // .navigation.down
    &googleAppScreen,           // .navigation.left
    NULL,                       // .navigation.right

    googleAppQrCode_screen_bmp, // .image

    getApp_Init,                // .initFunction
    NULL,                       // .createTaskFunction
    getApp_Destroy              // .destroyTaskFunction
};