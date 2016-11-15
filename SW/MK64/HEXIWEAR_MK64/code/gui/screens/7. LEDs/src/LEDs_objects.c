/*
 * LEDs_objects.c
 *
 *  Created on: 08.11.2016
 *      Author: Patrick
 */

#include "gui_driver.h"
#include "LEDs_private.h"
#include "screens_common.h"


guiScreen_t LEDs_Screen =
{
	.navigation =
	{
			.up 	= &gui_sensorTag_screen,
			.down	= &appsScreen,
			.left	= &watchScreen,
	        .right	= &control_Screen
	},

	.image = LEDs_bmp,

	.initFunction 		= NULL,
	.createTaskFunction	= NULL,
	.destroyTaskFunction= NULL
};
