// File: gui_heartRate_objects.c

// Definitions of objects used in the heart rate gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "screens_common.h"
#include "apps/fitness/gui_heartRate/gui_heartRate_private.h"
#include "apps/fitness/gui_heartRate/gui_heartRate.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t heartRateScreen =
{
    &flashlightScreen,               // .navigation.up
    &gui_weatherStation_coverScreen, // .navigation.down
    &appsScreen,                     // .navigation.left
    NULL,                            // .navigation.right

    heartRate_screen_bmp,       // .image

    gui_heartRate_Init,         // .initFunction
    gui_heartRate_CreateTasks,  // .createTaskFunction
    gui_heartRate_DestroyTasks  // .destroyTaskFunction
};

guiLabel_t gui_heartRate_bpmVal_label =
{
    33,                        // .dynamicArea.xCrd
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


guiLabel_t gui_heartRate_bpmText_label =
{
    38,                       // .dynamicArea.xCrd
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

guiImage_t gui_heartRate_icon =
{
    24,                 // .dynamicArea.xCrd
    23,                 // .dynamicArea.yCrd
    0,                  // .dynamicArea.width
    0,                  // .dynamicArea.height
    NULL,               // .dynamicArea.areaBuffer
    heartRate_icon_bmp  // .img
};