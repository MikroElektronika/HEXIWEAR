#include "gui_driver.h"
#include "screens_common.h"
#include "haptic_private.h"

/************************************************************************************
*************************************************************************************
* Definition of watch screen
*************************************************************************************
************************************************************************************/

guiScreen_t hapticScreen =
{
  .navigation =
  {
          .up     = &buttonsGroupScreen,
          .down   = &getAppScreen,
          .left   = &settingsScreen,
          .right  = NULL
  },

  .image = haptic_screen_bmp,

  .initFunction        = haptic_Init,
  .createTaskFunction  = haptic_CreateTasks,
  .destroyTaskFunction = haptic_DestroyTasks
};

guiImage_t
	haptic_icon =
    {
        .dynamicArea =
        {
			.xCrd   = 24,
			.yCrd   = 23
        },

		.img = haptic_icon_blue_bmp
    };
