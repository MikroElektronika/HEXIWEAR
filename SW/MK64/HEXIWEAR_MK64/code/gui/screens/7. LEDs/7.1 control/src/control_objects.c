/*
 * LEDs_objects.c
 *
 *  Created on: 08.11.2016
 *      Author: Patrick
 */

#include "gui_driver.h"
#include "control.h"
#include "control_private.h"
#include "screens_common.h"


guiScreen_t control_Screen =
{
	.navigation =
	{
			.up 	= NULL,
			.down	= NULL,
			.left	= &LEDs_Screen,
	        .right	= NULL
	},

	.image = control_bmp,

	.initFunction 		= control_Init,
	.createTaskFunction	= control_CreateTasks,
	.destroyTaskFunction= control_DestroyTasks
};
