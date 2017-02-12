/**
 * \file MultipleChoice_objects.c
 * \version 1.00
 */

#include "platform_config.h"

#include "gui_driver.h"
#include "screens_common.h"
#include "MultipleChoice_private.h"

/**
 * ***********************************************************************************
* Definition of watch screen
 * ***********************************************************************************
 * */

guiScreen_t MultipleChoiceScreen =
{
  .navigation =
  {
     .up    = &gui_sensorTag_screen,
#if PL_CONFIG_HAS_LED_GUI
     .down  = &LEDs_Screen,
#else
     .down  = &appsScreen,
#endif
     .left  = &watchScreen,
     .right = NULL
  },
  .image = MultipleChoice_screen_bmp,
  .initFunction        = MultipleChoice_Init,
  .createTaskFunction  = MultipleChoice_CreateTasks,
  .destroyTaskFunction = MultipleChoice_DestroyTasks
};

/**
 * ***********************************************************************************
* Definition of screen objects
 * ***********************************************************************************
 * */

guiLabel_t MultipleChoice_label =
{
	.dynamicArea =
	{
		.xCrd = 25,
		.yCrd = 56,
		.width  = 46,
		.height = 15
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_8_Regular,
		.fontColor  = GUI_COLOR_YELLOW,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 7
};

