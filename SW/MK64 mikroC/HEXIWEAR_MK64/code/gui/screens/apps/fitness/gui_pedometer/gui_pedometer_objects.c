// File: gui_pedometer_objects.c

// Definitions of objects used in the pedometer gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "screens_common.h"
#include "apps/fitness/gui_pedometer/gui_pedometer_private.h"
#include "apps/fitness/gui_pedometer/gui_pedometer.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t pedometerScreen =
{
    &heartRateScreen,           // .navigation.up
    &heartRateScreen,           // .navigation.down
    &fitnessScreen,             // .navigation.left
    NULL,                       // .navigation.right

    pedometer_screen_bmp,       // .image

    gui_pedometer_Init,         // .initFunction
    gui_pedometer_CreateTasks,  // .createTaskFunction
    gui_pedometer_DestroyTasks  // .destroyTaskFunction
};

guiLabel_t gui_pedometer_stepCounter_label =
{
    55,                        // .dynamicArea.xCrd
    31,                        // .dynamicArea.yCrd
    35,                        // .dynamicArea.width
    25,                        // .dynamicArea.height
    NULL,                      // .dynamicArea.areaBuffer

    guiFont_Tahoma_14_Regular, // .textProperties.font
    GUI_COLOR_WHITE,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_LEFT,      // .textProperties.alignParam
    NULL,                      // .textProperties.background

    NULL,                      // .caption
    6                          // .captionLength
};


guiLabel_t gui_pedometer_stepText_label =
{
    58,                       // .dynamicArea.xCrd
    55,                       // .dynamicArea.yCrd
    28,                       // .dynamicArea.width
    14,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer
    
    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_WHITE,          // .textProperties.fontColor
    OLED_TEXT_ALIGN_LEFT,     // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    6                         // .captionLength
};

guiLabel_t gui_pedometer_calCounter_label =
{
    9,                         // .dynamicArea.xCrd
    31,                        // .dynamicArea.yCrd
    35,                        // .dynamicArea.width
    25,                        // .dynamicArea.height
    NULL,                      // .dynamicArea.areaBuffer

    guiFont_Tahoma_14_Regular, // .textProperties.font
    GUI_COLOR_WHITE,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_LEFT,      // .textProperties.alignParam
    NULL,                      // .textProperties.background

    NULL,                      // .caption
    6                          // .captionLength
};


guiLabel_t gui_pedometer_calText_label =
{
    18,                       // .dynamicArea.xCrd
    55,                       // .dynamicArea.yCrd
    15,                       // .dynamicArea.width
    14,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_WHITE,          // .textProperties.fontColor
    OLED_TEXT_ALIGN_LEFT,     // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    4                         // .captionLength
};

guiImage_t gui_pedometer_icon =
{
    24,                // .dynamicArea.xCrd
    23,                // .dynamicArea.yCrd
    0,                 // .dynamicArea.width
    0,                 // .dynamicArea.height
    NULL,              // .dynamicArea.areaBuffer
    pedometer_icon_bmp // .img
};