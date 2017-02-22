/**
 * fitness application objects,
 * Project HEXIWEAR, 2015
 */

#include "gui_driver.h"
#include "screens_common.h"
#include "fitness_private.h"

/************************************************************************************
*************************************************************************************
* Definition of fitness screen
*************************************************************************************
************************************************************************************/

guiScreen_t
	fitnessScreen =
	{
		.navigation =
		{
			.up     = &flashlightScreen,
			.down   = &gui_weatherStation_coverScreen,
			.left   = &appsScreen,
			.right  = &pedometerScreen
		},

		.image = fitness_screen_bmp,

		.initFunction        = NULL,
		.createTaskFunction  = NULL,
		.destroyTaskFunction = NULL
	};
