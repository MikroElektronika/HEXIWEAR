/**
 * weather station global objects
 * Project HEXIWEAR, 2015
 */

#include "screens_common.h"
#include "gui_weatherStation_private.h"
#include "gui_weatherStation.h"

static guiScreen_t
    gui_weatherStationScreen_mainScreen;

guiScreen_t
    gui_weatherStation_coverScreen =
    {
        .navigation =
        {
            .up     = &fitnessScreen,
            .down   = &gui_motionControl_coverScreen,
            .left   = &appsScreen,
            .right  = &gui_weatherStationScreen_mainScreen
        },

        .image = gui_weatherStation_cover_bmp,

        .initFunction        = NULL,
        .createTaskFunction  = NULL,
        .destroyTaskFunction = NULL
    };

static guiScreen_t
    gui_weatherStationScreen_mainScreen =
    {
        .navigation =
        {
            .up     = NULL,
            .down   = NULL,
            .left   = &gui_weatherStation_coverScreen,
            .right  = NULL
        },

        .image = gui_weatherStation_appScreen_bmp,

        .initFunction        = gui_weatherStation_Init,
        .createTaskFunction  = gui_weatherStation_CreateTasks,
        .destroyTaskFunction = gui_weatherStation_DestroyTasks
    };

/**
 * labels
 */

guiLabel_t gui_weatherStation_label =
{
    .dynamicArea =
    {
        .width  = 35,
        .height = 15
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = gui_weatherStation_appScreen_bmp
    },
    .caption = NULL,
    .captionLength = 8
};

/////////////////////////////////////////////////////////////////////////////////////
//

guiLabel_t gui_weatherStation_labelTemp =
{
    .dynamicArea =
    {
        .xCrd   = 42,
        .yCrd   = 10,
        .width  = 50,
        .height = 15
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_RIGHT,
        .background = gui_weatherStation_appScreen_bmp
    },
    .caption = NULL,
    .captionLength = 10
};

/////////////////////////////////////////////////////////////////////////////////////
// Y coord Label

guiLabel_t gui_weatherStation_labelHum =
{
    .dynamicArea =
    {
        .xCrd   = 42,
        .yCrd   = 33,
        .width  = 50,
        .height = 15
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_RIGHT,
        .background = gui_weatherStation_appScreen_bmp
    },
    .caption = NULL,
    .captionLength = 10
};

/////////////////////////////////////////////////////////////////////////////////////
// Z coord Label

guiLabel_t gui_weatherStation_labelPress =
{
    .dynamicArea =
    {
        .xCrd   = 37,
        .yCrd   = 56,
        .width  = 55,
        .height = 15
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_RIGHT,
        .background = gui_weatherStation_appScreen_bmp
    },
    .caption = NULL,
    .captionLength = 20
};
