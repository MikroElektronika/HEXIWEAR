#include "gui_driver.h"
#include "screens_common.h"
#include "gui_notifications_private.h"

/************************************************************************************
*************************************************************************************
* Definition of watch screen
*************************************************************************************
************************************************************************************/

guiScreen_t notifScreen =
{
  .navigation =
  {
          .up    = &appsScreen,
          .down  = &settingsScreen,
          .left  = &watchScreen,
          .right = &notifMainScreen
  },

  .image = gui_notifications_screen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};

guiScreen_t notifMainScreen =
{
  .navigation =
  {
          .up    = NULL,
          .down  = NULL,
          .left  = &notifScreen,
          .right = NULL
  },

  .image = gui_notifications_mainScreen_bmp,

  .initFunction        = gui_notifications_Init,
  .createTaskFunction  = gui_notifications_CreateTasks,
  .destroyTaskFunction = gui_notifications_DestroyTasks
};

/** images */

guiImage_t
    gui_notifications_mailIcon =
    {
        .dynamicArea =
        {
            .xCrd   = 13,
            .yCrd   = 9
        },

        .img = NULL
    };

guiImage_t
    gui_notifications_smsIcon =
    {
        .dynamicArea =
        {
            .xCrd   = 16,
            .yCrd   = 32
        },

        .img = NULL
    };

guiImage_t
    gui_notifications_callIcon =
    {
        .dynamicArea =
        {
            .xCrd   = 16,
            .yCrd   = 54
        },

        .img = NULL
    };

/** counter labels */

guiLabel_t
	gui_notifications_labelMail =
	{
		.dynamicArea =
		{
			.xCrd   = 57,
			.yCrd   = 11,
			.width  = 29,
			.height = 13
		},
		.textProperties =
		{
			.font       = guiFont_Tahoma_8_Regular,
			.fontColor  = GUI_COLOR_CYAN,
			.alignParam = OLED_TEXT_ALIGN_CENTER,
			.background = NULL
		},
		.caption = NULL,
		.captionLength = 4
	};

guiLabel_t
	gui_notifications_labelSms =
	{
		.dynamicArea =
		{
			.xCrd   = 57,
			.yCrd   = 34,
			.width  = 29,
			.height = 13
		},
		.textProperties =
		{
			.font       = guiFont_Tahoma_8_Regular,
			.fontColor  = GUI_COLOR_CYAN,
			.alignParam = OLED_TEXT_ALIGN_CENTER,
			.background = NULL
		},
		.caption = NULL,
		.captionLength = 4
	};

guiLabel_t
	gui_notifications_labelCall =
	{
		.dynamicArea =
		{
			.xCrd   = 57,
			.yCrd   = 57,
			.width  = 29,
			.height = 13
		},
		.textProperties =
		{
			.font       = guiFont_Tahoma_8_Regular,
			.fontColor  = GUI_COLOR_CYAN,
			.alignParam = OLED_TEXT_ALIGN_CENTER,
			.background = NULL
		},
		.caption = NULL,
		.captionLength = 4
	};
