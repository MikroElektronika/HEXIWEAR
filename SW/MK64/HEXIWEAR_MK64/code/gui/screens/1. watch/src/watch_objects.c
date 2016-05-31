/**
 * \file watch_objects.c
 * \version 1.00
 * \brief this file contains watch screen related GUI objects
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
#include "watch_private.h"

/**
 * Definition of watch screen
 */
guiScreen_t watchScreen =
{
  .navigation =
  {
          .up     = NULL,
          .down   = NULL,
          .left   = NULL,
          .right  = &appsScreen,
  },

  .image = NULL,

  .initFunction        = watch_Init,
  .createTaskFunction  = watch_CreateTasks,
  .destroyTaskFunction = watch_DestroyTasks
};

/** definitions of screen objects */

/** battery image GUI object */
guiImage_t watch_imgBattery =
{
	.dynamicArea =
	{
		.xCrd = 74,
		.yCrd = 0,
	},

	.img = battery_0_bmp
};


/** notification sms image GUI object */
guiImage_t watch_imgSms =
{
	.dynamicArea =
	{
		.xCrd = 21,
		.yCrd = 4,
	},

	.img = NULL
};

/** notification mail image GUI object */
guiImage_t watch_imgMail =
{
	.dynamicArea =
	{
		.xCrd = 3,
		.yCrd = 6,
	},

	.img = NULL
};

/** notification call image GUI object */
guiImage_t watch_imgCall =
{
	.dynamicArea =
	{
		.xCrd = 37,
		.yCrd = 3,
	},

	.img = NULL
};

/** bluetooth link GUI object */
guiImage_t watch_imgBluetoothLogo =
{
	.dynamicArea =
	{
		.xCrd = 36,
		.yCrd = 72,
	},

	.img = watch_bluetooth_logo_white_bmp
};

/** temperature unit GUI object */
guiImage_t watch_imgTempUnit =
{
	.dynamicArea =
	{
		.xCrd = 17,
		.yCrd = 81,
	},

	.img = celsius_bmp
};

/** time GUI object */
guiLabel_t watch_labelTime =
{
	.dynamicArea =
	{
		.xCrd   = 0,
		.yCrd   = 38,
		.width  = 96,
		.height = 32
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_18_Regular,
		.fontColor  = GUI_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 15
};

/** date GUI object */
guiLabel_t watch_labelDate =
{
	.dynamicArea =
	{
		.xCrd   = 0,
		.yCrd   = 23,
		.width  = 96,
		.height = 15
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_8_Regular,
		.fontColor  = GUI_COLOR_GRAY,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 12
};

/** temperature GUI object */
guiLabel_t watch_labelTemp =
{
	.dynamicArea =
	{
		.xCrd   = 0,
		.yCrd   = 80,
		.width  = 19,
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
	.captionLength = 6
};

/** Menu label GUI object */
guiLabel_t watch_labelEnter =
{
	.dynamicArea =
	{
		.xCrd   = 65,
		.yCrd   = 80,
		.width  = 30,
		.height = 15
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_8_Regular,
		.fontColor  = GUI_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_LEFT,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 6
};
