#include "gui_driver.h"
#include "screens_common.h"
#include "info_private.h"

guiScreen_t infoScreen =
{
  .navigation =
  {
          .up     = NULL,
          .down   = NULL,
          .left   = &aboutScreen,
          .right  = NULL
  },

  .image = 	NULL,

  .initFunction        = info_Init,
  .createTaskFunction  = info_CreateTasks,
  .destroyTaskFunction = info_DestroyTasks
};

guiLabel_t info_labelTitle =
{
  .dynamicArea =
  {
          .xCrd   = 8,
          .yCrd   = 21,
          .width  = 80,
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
  .captionLength = 14
};

guiLabel_t info_labelData =
{
  .dynamicArea =
  {
          .xCrd   = 4,
          .yCrd   = 37,
          .width  = 89,
          .height = 13
  },

  .textProperties =
  {
          .font       = guiFont_Tahoma_8_Regular,
          .fontColor  = GUI_COLOR_BLUE_1,
          .alignParam = OLED_TEXT_ALIGN_CENTER,
          .background = NULL
  },

  .caption = NULL,
  .captionLength = 18
};

guiLabel_t info_labelData2 =
{
  .dynamicArea =
  {
          .xCrd   = 0,
          .yCrd   = 60,
          .width  = 96,
          .height = 13
  },

  .textProperties =
  {
          .font       = guiFont_Tahoma_8_Regular,
          .fontColor  = GUI_COLOR_GRAY,
          .alignParam = OLED_TEXT_ALIGN_CENTER,
          .background = NULL
  },

  .caption = NULL,
  .captionLength = 18
};
