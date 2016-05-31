/**
 * \file gui_notifications_objects.c
 * \version 1.00
 * \brief this file contains notifications GUI related objects
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

#include "gui_driver.h"
#include "screens_common.h"
#include "gui_notifications_private.h"

/** watch screen */

guiScreen_t notifScreen =
{
  .navigation =
  {
          .up    = &appsScreen,
          .down  = &settingsScreen,
          .left  = &watchScreen,
          .right = &notifMainScreen
  },

  .image = gui_notifications_screen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};

guiScreen_t notifMainScreen =
{
  .navigation =
  {
          .up    = NULL,
          .down  = NULL,
          .left  = &notifScreen,
          .right = NULL
  },

  .image = gui_notifications_mainScreen_bmp,

  .initFunction        = gui_notifications_Init,
  .createTaskFunction  = gui_notifications_CreateTasks,
  .destroyTaskFunction = gui_notifications_DestroyTasks
};

/** images */

guiImage_t
    gui_notifications_mailIcon =
    {
        .dynamicArea =
        {
            .xCrd   = 13,
            .yCrd   = 9
        },

        .img = NULL
    };

guiImage_t
    gui_notifications_smsIcon =
    {
        .dynamicArea =
        {
            .xCrd   = 16,
            .yCrd   = 32
        },

        .img = NULL
    };

guiImage_t
    gui_notifications_callIcon =
    {
        .dynamicArea =
        {
            .xCrd   = 16,
            .yCrd   = 54
        },

        .img = NULL
    };

/** counter labels */

guiLabel_t
	gui_notifications_labelMail =
	{
		.dynamicArea =
		{
			.xCrd   = 57,
			.yCrd   = 11,
			.width  = 29,
			.height = 13
		},
		.textProperties =
		{
			.font       = guiFont_Tahoma_8_Regular,
			.fontColor  = GUI_COLOR_CYAN,
			.alignParam = OLED_TEXT_ALIGN_CENTER,
			.background = NULL
		},
		.caption = NULL,
		.captionLength = 4
	};

guiLabel_t
	gui_notifications_labelSms =
	{
		.dynamicArea =
		{
			.xCrd   = 57,
			.yCrd   = 34,
			.width  = 29,
			.height = 13
		},
		.textProperties =
		{
			.font       = guiFont_Tahoma_8_Regular,
			.fontColor  = GUI_COLOR_CYAN,
			.alignParam = OLED_TEXT_ALIGN_CENTER,
			.background = NULL
		},
		.caption = NULL,
		.captionLength = 4
	};

guiLabel_t
	gui_notifications_labelCall =
	{
		.dynamicArea =
		{
			.xCrd   = 57,
			.yCrd   = 57,
			.width  = 29,
			.height = 13
		},
		.textProperties =
		{
			.font       = guiFont_Tahoma_8_Regular,
			.fontColor  = GUI_COLOR_CYAN,
			.alignParam = OLED_TEXT_ALIGN_CENTER,
			.background = NULL
		},
		.caption = NULL,
		.captionLength = 4
	};
