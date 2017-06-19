// File: gui_weatherStation_objects.c

// Definitions of objects used in the weather station gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "screens_common.h"
#include "apps/weatherStation/gui_weatherStation_private.h"
#include "apps/weatherStation/gui_weatherStation.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t gui_weatherStation_coverScreen =
{
    &heartRateScreen,               // .navigation.up
    &gui_motionControl_coverScreen, // .navigation.down
    &appsScreen,                    // .navigation.left
    &gui_weatherStation_mainScreen, // .navigation.right

    gui_weatherStation_cover_bmp,   // .image

    NULL,                           // .initFunction
    NULL,                           // .createTaskFunction
    NULL                            // .destroyTaskFunction
};

guiScreen_t gui_weatherStation_mainScreen =
{
    NULL,                             // .navigation.up
    NULL,                             // .navigation.down
    &gui_weatherStation_coverScreen,  // .navigation.left
    NULL,                             // .navigation.right

    gui_weatherStation_appScreen_bmp, // .image

    gui_weatherStation_Init,          // .initFunction
    gui_weatherStation_CreateTasks,   // .createTaskFunction
    gui_weatherStation_DestroyTasks   // .destroyTaskFunction
};

guiLabel_t gui_weatherStation_label =
{
    35,                               // .dynamicArea.xCrd
    15,                               // .dynamicArea.yCrd
    0,                                // .dynamicArea.width
    0,                                // .dynamicArea.height
    NULL,                             // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular,         // .textProperties.font
    GUI_COLOR_WHITE,                  // .textProperties.fontColor
    OLED_TEXT_ALIGN_LEFT,             // .textProperties.alignParam
    gui_weatherStation_appScreen_bmp, // .textProperties.background

    NULL,                             // .caption
    8                                 // .captionLength
};

// temperature
guiLabel_t gui_weatherStation_labelTemp =
{
    42,                               // .dynamicArea.xCrd
    10,                               // .dynamicArea.yCrd
    50,                               // .dynamicArea.width
    15,                               // .dynamicArea.height
    NULL,                             // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular,         // .textProperties.font
    GUI_COLOR_WHITE,                  // .textProperties.fontColor
    OLED_TEXT_ALIGN_RIGHT,            // .textProperties.alignParam
    NULL, //gui_weatherStation_appScreen_bmp, // .textProperties.background

    NULL,                             // .caption
    10                                // .captionLength
};

// relative humidity
guiLabel_t gui_weatherStation_labelHum =
{
    42,                               // .dynamicArea.xCrd
    33,                               // .dynamicArea.yCrd
    50,                               // .dynamicArea.width
    15,                               // .dynamicArea.height
    NULL,                             // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular,         // .textProperties.font
    GUI_COLOR_WHITE,                  // .textProperties.fontColor
    OLED_TEXT_ALIGN_RIGHT,            // .textProperties.alignParam
    NULL, //gui_weatherStation_appScreen_bmp, // .textProperties.background

    NULL,                             // .caption
    10                                // .captionLength
};

// pressure
guiLabel_t gui_weatherStation_labelPress =
{
    37,                               // .dynamicArea.xCrd
    56,                               // .dynamicArea.yCrd
    55,                               // .dynamicArea.width
    15,                               // .dynamicArea.height
    NULL,                             // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular,         // .textProperties.font
    GUI_COLOR_WHITE,                  // .textProperties.fontColor
    OLED_TEXT_ALIGN_RIGHT,            // .textProperties.alignParam
    NULL, //gui_weatherStation_appScreen_bmp, // .textProperties.background

    NULL,                             // .caption
    20                                // .captionLength
};