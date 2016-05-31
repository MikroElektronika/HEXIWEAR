/**
 * \file gui_weatherStation_objects.c
 * \version 1.00
 * \brief this file contains weather station app related GUI objects
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

/** labels */

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

/** temperature */
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

/** relative humidity */
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

/** pressure */
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
