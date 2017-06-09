// File: info_objects.c

// Definitions of objects used in the info gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "info_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t infoScreen =
{
    NULL,              // .navigation.up
    NULL,              // .navigation.down
    &aboutScreen,      // .navigation.left
    NULL,              // .navigation.right

    NULL,              // .image

    info_Init,         // .initFunction
    info_CreateTasks,  // .createTaskFunction
    info_DestroyTasks  // .destroyTaskFunction
};

guiLabel_t info_labelTitle =
{
    8,                        // .dynamicArea.xCrd
    21,                       // .dynamicArea.yCrd
    80,                       // .dynamicArea.width
    15,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_GRAY,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,   // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    14                        // .captionLength
};

guiLabel_t info_labelData =
{
    4,                        // .dynamicArea.xCrd
    37,                       // .dynamicArea.yCrd
    89,                       // .dynamicArea.width
    13,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_BLUE_1,         // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,   // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    18                        // .captionLength
};

guiLabel_t info_labelData2 =
{
    0,                        // .dynamicArea.xCrd
    60,                       // .dynamicArea.yCrd
    96,                       // .dynamicArea.width
    13,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_GRAY,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,   // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    18                        // .captionLength
};