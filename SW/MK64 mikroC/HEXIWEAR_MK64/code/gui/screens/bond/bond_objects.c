// File: bond_objects.c

// Definitions of objects used in the bond gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "bond_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t bondScreen =
{
    NULL,              // .navigation.up
    NULL,              // .navigation.down
    NULL,              // .navigation.left
    NULL,              // .navigation.right

    bond_screen_bmp,   // .image

    bond_Init,         // .initFunction
    NULL,              // .createTaskFunction
    bond_DestroyTasks  // .destroyTaskFunction
};

guiLabel_t bond_label =
{
    25,                       // .dynamicArea.xCrd
    56,                       // .dynamicArea.yCrd
    46,                       // .dynamicArea.width
    15,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_YELLOW,         // .textProperties.fontColor
    OLED_TEXT_ALIGN_CENTER,   // .textProperties.alignParam
    NULL,                     // .textProperties.background
    
    NULL,                     // .caption
    7                         // .captionLength
};