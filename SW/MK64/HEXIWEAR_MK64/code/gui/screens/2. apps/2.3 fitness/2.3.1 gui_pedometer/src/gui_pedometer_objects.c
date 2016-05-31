/**
 * \file gui_pedometer_objects.c
 * \version 1.00
 * \brief this file contains pedometer app related GUI objects
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

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
