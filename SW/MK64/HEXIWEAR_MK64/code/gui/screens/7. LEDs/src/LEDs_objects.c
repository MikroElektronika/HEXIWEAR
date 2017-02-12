/*
 * LEDs_objects.c
 *
 *  Created on: 08.11.2016
 *      Author: Patrick
 */

#include "platform_config.h"

#if PL_CONFIG_HAS_LED_GUI
#include "gui_driver.h"
#include "LEDs_private.h"
#include "screens_common.h"

guiScreen_t LEDs_Screen =
{
	.navigation =
	{
    .up 	= &MultipleChoiceScreen,
    .down	= &appsScreen,
    .left	= &watchScreen,
    .right	= &control_Screen
	},
	.image = LEDs_bmp,
	.initFunction 		= NULL,
	.createTaskFunction	= NULL,
	.destroyTaskFunction= NULL
};
#endif /* PL_CONFIG_HAS_LED_GUI */
