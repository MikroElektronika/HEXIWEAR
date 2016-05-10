
#include "screens_common.h"

/////////////////////////////////////////////////////////////////////////////////////
// Enter/Next label

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

/////////////////////////////////////////////////////////////////////////////////////
// Back label

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

/////////////////////////////////////////////////////////////////////////////////////
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
