#include "gui_driver.h"
#include "screens_common.h"
#include "bluetooth_private.h"

/************************************************************************************
*************************************************************************************
* Definition of watch screen
*************************************************************************************
************************************************************************************/

guiScreen_t bluetoothScreen =
{
  .navigation =
  {
          .up     = &resetScreen,
          .down   = &bootloaderCoverScreen,
          .left   = &settingsScreen,
          .right  = NULL
  },

  .image = bluetooth_screen_bmp,

  .initFunction        = bluetooth_Init,
  .createTaskFunction  = bluetooth_CreateTasks,
  .destroyTaskFunction = bluetooth_DestroyTasks
};

guiImage_t
    bluetooth_icon =
    {
        .dynamicArea =
        {
			.xCrd   = 24,
			.yCrd   = 23
        },

		.img = bluetooth_icon_blue_bmp
    };
