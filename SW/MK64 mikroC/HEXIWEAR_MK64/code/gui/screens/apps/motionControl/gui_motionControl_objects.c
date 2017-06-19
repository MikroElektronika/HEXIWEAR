// File: gui_motionControl_objects.c

// Definitions of objects used in the motion control gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "screens_common.h"
#include "apps/motionControl/gui_motionControl_private.h"
#include "apps/motionControl/gui_motionControl.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t gui_motionControl_coverScreen =
{
    &gui_weatherStation_coverScreen, // .navigation.up
    &flashlightScreen,               // .navigation.down
    &appsScreen,                     // .navigation.left
    &gui_motionControl_accScreen,    // .navigation.right

    gui_motionControl_cover_bmp,     // .image

    NULL,                            // .initFunction
    NULL,                            // .createTaskFunction
    NULL                             // .destroyTaskFunction
};

guiScreen_t gui_motionControl_accScreen =
{
    &gui_motionControl_gyroScreen,  // .navigation.up
    &gui_motionControl_gyroScreen,  // .navigation.down
    &gui_motionControl_coverScreen, // .navigation.left
    NULL,                           // .navigation.right

    gui_motionControl_acc_bmp,      // .image

    gui_motionControl_Init,         // .initFunction
    gui_motionControl_CreateTasks,  // .createTaskFunction
    gui_motionControl_DestroyTasks  // .destroyTaskFunction
};

guiScreen_t gui_motionControl_gyroScreen =
{
    &gui_motionControl_accScreen,   // .navigation.up
    &gui_motionControl_accScreen,   // .navigation.down
    &gui_motionControl_coverScreen, // .navigation.left
    NULL,                           // .navigation.right

    gui_motionControl_gyro_bmp,     // .image

    gui_motionControl_Init,         // .initFunction
    gui_motionControl_CreateTasks,  // .createTaskFunction
    gui_motionControl_DestroyTasks  // .destroyTaskFunction
};

// labels

guiLabel_t gui_motionControl_label =
{
    0,                         // .dynamicArea.xCrd
    0,                         // .dynamicArea.yCrd
    32,                        // .dynamicArea.width
    15,                        // .dynamicArea.height
    NULL,                      // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular,  // .textProperties.font
    GUI_COLOR_WHITE,           // .textProperties.fontColor
    OLED_TEXT_ALIGN_LEFT,      // .textProperties.alignParam
    gui_motionControl_acc_bmp, // .textProperties.background

    NULL,                      // .caption
    8                          // .captionLength
};

// x-coordinate

guiLabel_t gui_motionControl_labelX =
{
    60,                       // .dynamicArea.xCrd
    10,                       // .dynamicArea.yCrd
    25,                       // .dynamicArea.width
    15,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_WHITE,          // .textProperties.fontColor
    OLED_TEXT_ALIGN_RIGHT,    // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    8                         // .captionLength
};

// y-coordinate

guiLabel_t gui_motionControl_labelY =
{
    60,                       // .dynamicArea.xCrd
    33,                       // .dynamicArea.yCrd
    25,                       // .dynamicArea.width
    15,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_WHITE,          // .textProperties.fontColor
    OLED_TEXT_ALIGN_RIGHT,    // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    8                         // .captionLength
};

// z-coordinate

guiLabel_t gui_motionControl_labelZ =
{
    60,                       // .dynamicArea.xCrd
    56,                       // .dynamicArea.yCrd
    25,                       // .dynamicArea.width
    15,                       // .dynamicArea.height
    NULL,                     // .dynamicArea.areaBuffer

    guiFont_Tahoma_8_Regular, // .textProperties.font
    GUI_COLOR_WHITE,          // .textProperties.fontColor
    OLED_TEXT_ALIGN_RIGHT,    // .textProperties.alignParam
    NULL,                     // .textProperties.background

    NULL,                     // .caption
    8                         // .captionLength
};