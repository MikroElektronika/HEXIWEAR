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

  .image = NULL,

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

	.image = NULL,

	.initFunction        = watchSet_Init,
	.createTaskFunction  = watchSet_CreateTasks,
	.destroyTaskFunction = watchSet_DestroyTasks
};

guiLabel_t gui_hour_label =
{
    .dynamicArea =
    {
        .width  = 15,
        .height = 15,
		.xCrd   = 4,
		.yCrd   = 10
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = NULL
    },
    .caption = NULL,
    .captionLength = 3
};

guiLabel_t gui_minute_label =
{
    .dynamicArea =
    {
        .width  = 15,
        .height = 15,
		.xCrd   = 20,
		.yCrd   = 10
    },
    .textProperties =
    {
        .font       = guiFont_Tahoma_8_Regular,
        .fontColor  = GUI_COLOR_WHITE,
        .alignParam = OLED_TEXT_ALIGN_LEFT,
        .background = NULL
    },
    .caption = NULL,
    .captionLength = 3
};
