#include "screens_common.h"
#include "gui_pedometer_private.h"
#include "gui_pedometer.h"

guiScreen_t
    pedometerScreen =
    {
        .navigation =
        {
            .up     = &heartRateScreen,
            .down   = &heartRateScreen,
            .left   = &fitnessScreen,
            .right  = NULL
        },

        .image = pedometer_screen_bmp,

        .initFunction        = gui_pedometer_Init,
        .createTaskFunction  = gui_pedometer_CreateTasks,
        .destroyTaskFunction = gui_pedometer_DestroyTasks
    };

guiLabel_t
    gui_pedometer_stepCounter_label =
    {
        .dynamicArea =
        {
        .xCrd   = 55,
        .yCrd   = 31,
        .width  = 35,
        .height = 25
        },

        .textProperties =
        {
        .font       = guiFont_Tahoma_14_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = NULL
        },

        .caption       = NULL,
        .captionLength = 6
    };


guiLabel_t
    gui_pedometer_stepText_label =
    {
        .dynamicArea =
        {
        .xCrd   = 58,
        .yCrd   = 55,
        .width  = 28,
        .height = 14
        },

        .textProperties =
        {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = NULL
        },

        .caption       = NULL,
        .captionLength = 6
    };

guiLabel_t
    gui_pedometer_calCounter_label =
    {
        .dynamicArea =
        {
        .xCrd   = 9,
        .yCrd   = 31,
        .width  = 35,
        .height = 25
        },

        .textProperties =
        {
        .font       = guiFont_Tahoma_14_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = NULL
        },

        .caption       = NULL,
        .captionLength = 6
    };


guiLabel_t
    gui_pedometer_calText_label =
    {
        .dynamicArea =
        {
        .xCrd   = 18,
        .yCrd   = 55,
        .width  = 15,
        .height = 14
        },

        .textProperties =
        {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = NULL
        },

        .caption       = NULL,
        .captionLength = 4
    };

guiImage_t
    gui_pedometer_icon =
    {
        .dynamicArea =
        {
			.xCrd   = 24,
            .yCrd   = 23
        },

		.img = pedometer_icon_bmp
    };
