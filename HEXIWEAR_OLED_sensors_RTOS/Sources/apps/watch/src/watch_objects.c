
#include "apps.h"
#include "watch_objects.h"

/////////////////////////////////////////////////////////////////////////////////////
// Battery Image

apps_image_t watch_imgBattery =
{
	.dynamicArea =
	{
		.xCrd = 71,
		.yCrd = 0,
	},

	.img = battery_0_bmp
};

/////////////////////////////////////////////////////////////////////////////////////
// Digital Watch Label

static uint8_t watch_labelTime_caption[15];
apps_label_t watch_labelTime =
{
	.dynamicArea =
	{
		.xCrd   = 19,
		.yCrd   = 41,
		.width  = 60,
		.height = 30
	},
	.textProperties =
	{
		.font       = appsFont_Tahoma21x25_Regular,
		.fontColor  = MENU_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
	},
	.caption = watch_labelTime_caption
};

/////////////////////////////////////////////////////////////////////////////////////
// Date Label

static uint8_t watch_labelDate_caption[9];
apps_label_t watch_labelDate =
{
	.dynamicArea =
	{
		.xCrd   = 24,
		.yCrd   = 26,
		.width  = 51,
		.height = 15
	},
	.textProperties =
	{
		.font       = appsFont_Tahoma11x13_Regular,
		.fontColor  = MENU_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
	},
	.caption = watch_labelDate_caption
};

/////////////////////////////////////////////////////////////////////////////////////
// Temperature Label

static uint8_t watch_labelTemp_caption[6] = "18 C";
apps_label_t watch_labelTemp =
{
	.dynamicArea =
	{
		.xCrd   = 19,
		.yCrd   = 80,
		.width  = 23,
		.height = 15
	},
	.textProperties =
	{
		.font       = appsFont_Tahoma11x13_Regular,
		.fontColor  = MENU_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
	},
	.caption = watch_labelTemp_caption
};

