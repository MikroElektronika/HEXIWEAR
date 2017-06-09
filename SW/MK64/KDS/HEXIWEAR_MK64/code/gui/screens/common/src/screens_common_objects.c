/**
 * \file screens_common_objects.c
 * \version 1.00
 * \brief this file contains common screen objects and structures
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

/** Enter/Next label */

guiLabel_t screen_labelEnter =
{
	.dynamicArea =
	{
		.xCrd   = 53,
		.yCrd   = 81,
		.width  = 43,
		.height = 15
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_8_Regular,
		.fontColor  = GUI_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 8
};

/** Back label */

guiLabel_t screen_labelBack =
{
	.dynamicArea =
	{
		.xCrd   = 0,
		.yCrd   = 81,
		.width  = 43,
		.height = 15
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_8_Regular,
		.fontColor  = GUI_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 8
};

guiScreen_t
  splashScreen = {
                        .navigation = {
                                        .up     = NULL,
                                        .down   = NULL,
                                        .left   = NULL,
                                        .right  = NULL
                                      },

                        .image = hexiwear_logo_bmp,

                        .initFunction        = NULL,
                        .createTaskFunction  = NULL,
                        .destroyTaskFunction = NULL
                      };

//

guiImage_t screen_buttonStartDisabled =
{
	.dynamicArea =
	{
		.xCrd = 50,
		.yCrd = 81,
	},

	.img = button_start_disabled_bmp
};

guiImage_t screen_buttonStart =
{
	.dynamicArea =
	{
		.xCrd = 50,
		.yCrd = 81,
	},

	.img = button_start_bmp
};

guiImage_t screen_buttonStop =
{
	.dynamicArea =
	{
		.xCrd = 50,
		.yCrd = 81,
	},

	.img = button_stop_bmp
};

guiImage_t screen_buttonReset =
{
	.dynamicArea =
	{
		.xCrd = 50,
		.yCrd = 81,
	},

	.img = button_reset_bmp
};

guiImage_t screen_buttonBack =
{
	.dynamicArea =
	{
		.xCrd = 0,
		.yCrd = 81,
	},

	.img = button_back_bmp
};

guiImage_t screen_buttonBackDisabled =
{
	.dynamicArea =
	{
		.xCrd = 0,
		.yCrd = 81,
	},

	.img = button_back_disabled_bmp
};

guiImage_t screen_buttonRightUp =
{
	.dynamicArea =
	{
		.xCrd = 92,
		.yCrd = 30,
	},

	.img = buttonGroup_right_bmp
};

guiImage_t screen_buttonRightDown =
{
	.dynamicArea =
	{
		.xCrd = 92,
		.yCrd = 57,
	},

	.img = buttonGroup_right_bmp
};

guiImage_t screen_buttonLeftUp =
{
	.dynamicArea =
	{
		.xCrd = 2,
		.yCrd = 30,
	},

	.img = buttonGroup_left_bmp
};

guiImage_t screen_buttonLeftDown =
{
	.dynamicArea =
	{
		.xCrd = 2,
		.yCrd = 57,
	},

	.img = buttonGroup_left_bmp
};
