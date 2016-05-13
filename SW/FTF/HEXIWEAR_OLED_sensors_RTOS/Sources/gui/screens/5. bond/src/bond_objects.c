

#include "gui_driver.h"
#include "screens_common.h"
#include "bond_private.h"

/************************************************************************************
*************************************************************************************
* Definition of watch screen
*************************************************************************************
************************************************************************************/

guiScreen_t bondScreen =
{
  .navigation =
  {
          .up     = NULL,
          .down   = NULL,
          .left   = NULL,
          .right  = NULL
  },

  .image = bond_screen_bmp,

  .initFunction        = bond_Init,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = bond_DestroyTasks
};

/************************************************************************************
*************************************************************************************
* Definition of screen objects
*************************************************************************************
************************************************************************************/

guiLabel_t bond_label =
{
	.dynamicArea =
	{
		.xCrd = 25,
		.yCrd = 56,
		.width  = 46,
		.height = 15
	},
	.textProperties =
	{
		.font       = guiFont_Tahoma_8_Regular,
		.fontColor  = GUI_COLOR_YELLOW,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
		.background = NULL
	},
	.caption = NULL,
	.captionLength = 7
};

