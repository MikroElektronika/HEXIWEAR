/*
 * watch_set_objects.c
 *
 *  Created on: Aug 30, 2016
 *      Author: denes
 */


#include "gui_driver.h"
#include "screens_common.h"
#include "watch_set_private.h"
#include "watch_set.h"

guiScreen_t watchSetScreen =
{
  .navigation =
  {
          .up     = &resetScreen,
          .down   = &bluetoothScreen,
          .left   = &settingsScreen,
          .right  = &watchSetScreen_mainScreen
  },

  .image = main_screen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};

guiScreen_t watchSetScreen_mainScreen =
{
	.navigation =
	{
		.up     = NULL,
		.down   = NULL,
		.left   = &watchSetScreen,
		.right  = NULL
	},

	.image = setting_screen_bmp,

	.initFunction        = watchSet_Init,
	.createTaskFunction  = watchSet_CreateTasks,
	.destroyTaskFunction = watchSet_DestroyTasks
};

guiLabel_t gui_hour_label =
{
    .dynamicArea =
    {
		.xCrd   = 20,
		.yCrd   = 38,
		.width  = 32,
		.height = 32
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_16_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = NULL
    },
    .caption = NULL,
    .captionLength = 3
};

guiLabel_t gui_time_colon_label =
{
    .dynamicArea =
    {
		.xCrd   = 47,
		.yCrd   = 36,
		.width  = 5,
		.height = 32
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_16_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = NULL
    },
    .caption = NULL,
    .captionLength = 2
};

guiLabel_t gui_minute_label =
{
    .dynamicArea =
    {
		.xCrd   = 55,
		.yCrd   = 38,
		.width  = 35,
		.height = 32
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_16_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = NULL
    },
    .caption = NULL,
    .captionLength = 3
};

guiLabel_t gui_year_label =
{
	.dynamicArea =
	{
		.xCrd   = 12,
		.yCrd   = 23,
		.width  = 35,
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
	.captionLength = 6 // year dot terminator
};

guiLabel_t gui_month_label =
{
	.dynamicArea =
	{
		.xCrd   = 47,
		.yCrd   = 23,
		.width  = 22,
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
	.captionLength = 4
};

guiLabel_t gui_day_label =
{
	.dynamicArea =
	{
		.xCrd   = 72,
		.yCrd   = 23,
		.width  = 21,
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
	.captionLength = 4
};
