
#include "menu_defs.h"
#include "menu_resources.h"
#include "menu_screens.h"

//////////////////////////////////////////////////////////////////////////////////////
// Main Item

const menuItem_t menuItem_main =
{
	.navigation = {
		.enter 	= &menuItem_apps,
		.back  	= NULL,
		.up     = NULL,
		.down  	= NULL,
		.left  	= NULL,
		.right 	= NULL,
	},

	.image 				= menuItem_main_bmp,

	.initFunction 		= NULL,
	.callbackFunction 	= NULL,
};

//////////////////////////////////////////////////////////////////////////////////////
// Apps Item

const menuItem_t menuItem_apps =
{
	.navigation = {
		.enter 	= NULL,
		.back  	= &menuItem_main,
		.up     = NULL,
		.down  	= NULL,
		.left  	= NULL,
		.right 	= &menuItem_settings,
	},

	.image 				= menuItem_apps_bmp,

	.initFunction 		= NULL,
	.callbackFunction 	= NULL,
};

//////////////////////////////////////////////////////////////////////////////////////
// Settings Item

const menuItem_t menuItem_settings =
{
	.navigation = {
		.enter 	= NULL,
		.back  	= &menuItem_main,
		.up     = NULL,
		.down  	= NULL,
		.left  	= &menuItem_apps,
		.right 	= NULL,
	},

	.image 				= menuItem_settings_bmp,

	.initFunction 		= NULL,
	.callbackFunction 	= NULL,
};
