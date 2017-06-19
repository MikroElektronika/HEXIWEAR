// File: gui_notifications_objects.c

// Definitions of objects used in the notifications gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "gui_notifications_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////
 
// watch screen

guiScreen_t notifScreen =
{
    &appsScreen,                  // .navigation.up
    &settingsScreen,              // .navigation.down
    &watchScreen,                 // .navigation.left
    &notifMainScreen,             // .navigation.right

    gui_notifications_screen_bmp, //.image

    NULL,                         // .initFunction
    NULL,                         // .createTaskFunction
    NULL                          // .destroyTaskFunction
};

guiScreen_t notifMainScreen =
{
    NULL,                             // .navigation.up
    NULL,                             // .navigation.down
    &notifScreen,                     // .navigation.left
    NULL,                             // .navigation.right

    gui_notifications_mainScreen_bmp, // .image

    gui_notifications_Init,           // .initFunction
    gui_notifications_CreateTasks,    // .createTaskFunction
    gui_notifications_DestroyTasks    // .destroyTaskFunction
};

// images

guiImage_t gui_notifications_mailIcon =
{
    13,   // .dynamicArea.xCrd
    9,    // .dynamicArea.yCrd
    0,    // .dynamicArea.width
    0,    // .dynamicArea.height
    NULL, // .dynamicArea.areaBuffer

    NULL  // .img
};

guiImage_t gui_notifications_smsIcon =
{
    16,   // .dynamicArea.xCrd
    32,   // .dynamicArea.yCrd
    0,    // .dynamicArea.width
    0,    // .dynamicArea.height
    NULL, // .dynamicArea.areaBuffer

    NULL  // .img
};

guiImage_t gui_notifications_callIcon =
{
    16,   // .dynamicArea.xCrd
    54,   // .dynamicArea.yCrd
    0,    // .dynamicArea.width
    0,    // .dynamicArea.height
    NULL, // .dynamicArea.areaBuffer

    NULL  // .img
};

// counter labels

guiLabel_t gui_notifications_labelMail =
{
    57,                       // .dynamicArea.xCrd
    11,                       // .dynamicArea.yCrd
    29,                       // .dynamicArea.width
    13,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_CYAN,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,   // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    4                         // .captionLength
};

guiLabel_t gui_notifications_labelSms =
{
    57,                       // .dynamicArea.xCrd
    34,                       // .dynamicArea.yCrd
    29,                       // .dynamicArea.width
    13,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_CYAN,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,   // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    4                         // .captionLength
};

guiLabel_t gui_notifications_labelCall =
{
    57,                       // .dynamicArea.xCrd
    57,                       // .dynamicArea.yCrd
    29,                       // .dynamicArea.width
    13,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_CYAN,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,   // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    4                         // .captionLength
};