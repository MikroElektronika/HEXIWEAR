#include "screens_common.h"
#include "gui_heartRate_private.h"
#include "gui_heartRate.h"

guiScreen_t
    heartRateScreen =
    {
        .navigation =
        {
            .up     = &pedometerScreen,
            .down   = &pedometerScreen,
            .left   = &fitnessScreen,
            .right  = NULL
        },

        .image = heartRate_screen_bmp,

        .initFunction        = gui_heartRate_Init,
        .createTaskFunction  = gui_heartRate_CreateTasks,
        .destroyTaskFunction = gui_heartRate_DestroyTasks
    };

guiLabel_t
    gui_heartRate_bpmVal_label =
    {
        .dynamicArea =
        {
        .xCrd   = 33,
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
    gui_heartRate_bpmText_label =
    {
        .dynamicArea =
        {
        .xCrd   = 38,
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

guiImage_t
    gui_heartRate_icon =
    {
        .dynamicArea =
        {
			.xCrd   = 24,
            .yCrd   = 23
        },

		.img = heartRate_icon_bmp
    };
