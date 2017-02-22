/**
 * sensor tag global objects
 * Project HEXIWEAR, 2015
 */

#include "screens_common.h"
#include "gui_sensorTag_private.h"
#include "gui_sensorTag.h"

guiScreen_t
    gui_sensorTag_screen =
    {
        .navigation =
        {
            .up     = &settingsScreen,
            .down   = &relay_click_Screen,
            .left   = &watchScreen,
            .right  = NULL
        },

        .image = gui_sensorTag_blank_bmp,

        .initFunction        = gui_sensorTag_Init,
        .createTaskFunction  = gui_sensorTag_CreateTasks,
        .destroyTaskFunction = gui_sensorTag_DestroyTasks
    };

guiImage_t
    gui_sensorTag_icon =
    {
        .dynamicArea =
        {
            .xCrd   = 24,
            .yCrd   = 23
        },

        .img = gui_sensorTag_off_bmp
    };
