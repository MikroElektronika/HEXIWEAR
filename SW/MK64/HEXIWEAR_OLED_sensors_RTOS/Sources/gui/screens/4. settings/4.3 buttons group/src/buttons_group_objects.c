

#include "gui_driver.h"
#include "screens_common.h"
#include "buttons_group_private.h"

/************************************************************************************
*************************************************************************************
* Definition of watch screen
*************************************************************************************
************************************************************************************/

guiScreen_t buttonsGroupScreen =
{
  .navigation =
  {
          .up     = &bootloaderCoverScreen,
          .down   = &hapticScreen,
          .left   = &settingsScreen,
          .right  = NULL
  },

  .image = buttons_group_screen_bmp,

  .initFunction        = buttonsGroup_Init,
  .createTaskFunction  = buttonsGroup_CreateTasks,
  .destroyTaskFunction = buttonsGroup_DestroyTasks
};

guiImage_t buttonsGroup_img =
{
	.dynamicArea =
	{
		.xCrd = 24,
		.yCrd = 23,
	},

	.img = buttonGroup_rightSelected_bmp
};
