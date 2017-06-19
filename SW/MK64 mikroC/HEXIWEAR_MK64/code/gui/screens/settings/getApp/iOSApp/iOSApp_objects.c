// File: iOSApp_objects.c

// Definitions of objects used in the iOSApp gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "iOSApp_private.h"
#include "settings/getApp/getApp.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t iOSAppScreen =
{
    &googleAppScreen,    // .navigation.up
    &googleAppScreen,    // .navigation.down
    &getAppScreen,       // .navigation.left
    &iOSAppQrCodeScreen, // .navigation.right

    iOSApp_screen_bmp,   // .image

    NULL,                // .initFunction
    NULL,                // .createTaskFunction
    NULL                 // .destroyTaskFunction
};


guiScreen_t iOSAppQrCodeScreen =
{
    NULL,                    // .navigation.up
    NULL,                    // .navigation.down
    &iOSAppScreen,           // .navigation.left
    NULL,                    // .navigation.right

    iOSAppQrCode_screen_bmp, // .image

    getApp_Init,             // .initFunction
    NULL,                    // .createTaskFunction
    getApp_Destroy           // .destroyTaskFunction
};