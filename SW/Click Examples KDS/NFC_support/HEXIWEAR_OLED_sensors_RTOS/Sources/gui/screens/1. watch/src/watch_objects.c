
#include "gui_driver.h"
#include "screens_common.h"
#include "watch_private.h"

/************************************************************************************
*************************************************************************************
* Definition of watch screen
*************************************************************************************
************************************************************************************/

guiScreen_t watchScreen =
{
  .navigation =
  {
          .up     = NULL,
          .down   = NULL,
          .left   = NULL,
          .right  = &appsScreen,
  },

  .image = NULL,

  .initFunction        = watch_Init,
  .createTaskFunction  = watch_CreateTasks,
  .destroyTaskFunction = watch_DestroyTasks
};

/************************************************************************************
*************************************************************************************
* Definition of screen objects
*************************************************************************************
************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////
// Battery Image

guiImage_t watch_imgBattery =
{
	.dynamicArea =
	{
		.xCrd = 74,
		.yCrd = 0,
	},

	.img = battery_0_bmp
};


/////////////////////////////////////////////////////////////////////////////////////
// Notification Image

guiImage_t watch_imgSms =
{
	.dynamicArea =
	{
		.xCrd = 21,
		.yCrd = 4,
//		.xCrd = 42,
//		.yCrd = 6,
	},

	.img = NULL
};

guiImage_t watch_imgMail =
{
	.dynamicArea =
	{
		.xCrd = 3,
		.yCrd = 6,
//		.xCrd = 22,
//		.yCrd = 8,
	},

	.img = NULL
};

guiImage_t watch_imgCall =
{
	.dynamicArea =
	{
		.xCrd = 37,
		.yCrd = 3,
//		.xCrd = 58,
//		.yCrd = 6,
	},

	.img = NULL
};

/////////////////////////////////////////////////////////////////////////////////////
// Battery Image

guiImage_t watch_imgBluetoothLogo =
{
	.dynamicArea =
	{
		.xCrd = 36,
		.yCrd = 72,
	},

	.img = watch_bluetooth_logo_white_bmp
};

/////////////////////////////////////////////////////////////////////////////////////
// Temp unit Image

guiImage_t watch_imgTempUnit =
{
	.dynamicArea =
	{
		.xCrd = 17,
		.yCrd = 81,
	},

	.img = celsius_bmp
};

/////////////////////////////////////////////////////////////////////////////////////
// Time Label

guiLabel_t watch_labelTime =
{
	.dynamicArea =
	{
		.xCrd   = 10,
		.yCrd   = 38,
		.width  = 76,
		.height = 32
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_18_Regular,
		.fontColor  = GUI_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 15
};

/////////////////////////////////////////////////////////////////////////////////////
// Date Label

guiLabel_t watch_labelDate =
{
	.dynamicArea =
	{
		.xCrd   = 19,
		.yCrd   = 23,
		.width  = 63,
		.height = 15
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_8_Regular,
		.fontColor  = GUI_COLOR_GRAY,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 12
};

/////////////////////////////////////////////////////////////////////////////////////
// Temperature Label

guiLabel_t watch_labelTemp =
{
	.dynamicArea =
	{
		.xCrd   = 0,
		.yCrd   = 80,
		.width  = 19,
		.height = 15
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_8_Regular,
		.fontColor  = GUI_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_RIGHT,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 6
};

/////////////////////////////////////////////////////////////////////////////////////
// Enter Label

guiLabel_t watch_labelEnter =
{
	.dynamicArea =
	{
		.xCrd   = 65,
		.yCrd   = 80,
		.width  = 30,
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
	.captionLength = 6
};
