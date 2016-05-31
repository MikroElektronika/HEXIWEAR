/**
 * weather station global objects
 * Project HEXIWEAR, 2015
 */

#include "screens_common.h"
#include "gui_motionControl_private.h"
#include "gui_motionControl.h"

guiScreen_t
    gui_motionControl_coverScreen =
    {
        .navigation =
        {
            .up     = &gui_weatherStation_coverScreen,
            .down   = &flashlightScreen,
            .left   = &appsScreen,
            .right  = &gui_motionControl_accScreen
        },

        .image = gui_motionControl_cover_bmp,

        .initFunction        = NULL,
        .createTaskFunction  = NULL,
        .destroyTaskFunction = NULL
    };

guiScreen_t
    gui_motionControl_accScreen =
    {
        .navigation =
        {
            .up     = &gui_motionControl_gyroScreen,
            .down   = &gui_motionControl_gyroScreen,
            .left   = &gui_motionControl_coverScreen,
            .right  = NULL
        },

        .image = gui_motionControl_acc_bmp,

        .initFunction        = gui_motionControl_Init,
        .createTaskFunction  = gui_motionControl_CreateTasks,
        .destroyTaskFunction = gui_motionControl_DestroyTasks
    };

guiScreen_t
    gui_motionControl_gyroScreen =
    {
        .navigation =
        {
            .up     = &gui_motionControl_accScreen,
            .down   = &gui_motionControl_accScreen,
            .left   = &gui_motionControl_coverScreen,
            .right  = NULL
        },

        .image = gui_motionControl_gyro_bmp,

        .initFunction        = gui_motionControl_Init,
        .createTaskFunction  = gui_motionControl_CreateTasks,
        .destroyTaskFunction = gui_motionControl_DestroyTasks
    };

/**
 * labels
 */

guiLabel_t gui_motionControl_label =
{
    .dynamicArea =
    {
        .width  = 32,
        .height = 15
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = gui_motionControl_acc_bmp
    },
    .caption = NULL,
    .captionLength = 8
};

/////////////////////////////////////////////////////////////////////////////////////
// X coord Label

guiLabel_t gui_motionControl_labelX =
{
    .dynamicArea =
    {
        .xCrd   = 60,
        .yCrd   = 10,
        .width  = 25,
        .height = 15
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_RIGHT,
        .background = NULL
    },
    .caption = NULL,
    .captionLength = 8
};

/////////////////////////////////////////////////////////////////////////////////////
// Y coord Label

guiLabel_t gui_motionControl_labelY =
{
    .dynamicArea =
    {
        .xCrd   = 60,
        .yCrd   = 33,
        .width  = 25,
        .height = 15
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_RIGHT,
        .background = NULL
    },
    .caption = NULL,
    .captionLength = 8
};

/////////////////////////////////////////////////////////////////////////////////////
// Z coord Label

guiLabel_t gui_motionControl_labelZ =
{
    .dynamicArea =
    {
        .xCrd   = 60,
        .yCrd   = 56,
        .width  = 25,
        .height = 15
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_RIGHT,
        .background = NULL
    },
    .caption = NULL,
    .captionLength = 8
};
