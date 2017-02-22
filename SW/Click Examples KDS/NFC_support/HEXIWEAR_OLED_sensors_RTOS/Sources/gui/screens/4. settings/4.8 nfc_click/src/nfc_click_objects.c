#include "gui_driver.h"
#include "screens_common.h"
#include "nfc_click_private.h"

/**
 *
 * Definition of a_new_screen_screen
 */

 guiScreen_t nfc_click_Screen =
 {
   .navigation =
   {
           .up     = &resetScreen,
           .down   = &bluetoothScreen,
           .left   = &settingsScreen,
           .right  = NULL
   },

   .image = nfc_click_bmp,

   .initFunction        = nfc_click_Init,
   .createTaskFunction  = nfc_click_CreateTasks,
   .destroyTaskFunction = nfc_click_DestroyTasks
 };

guiImage_t nfc_click_OFF_icon =
{
		.dynamicArea =
		{
				.xCrd   = 24,
				.yCrd   = 23
		},

		.img = nfc_click_OFF_bmp
};

guiImage_t nfc_click_ON_icon =
{
		.dynamicArea =
		{
				.xCrd   = 24,
				.yCrd   = 23
		},

		.img = nfc_click_ON_bmp
};
