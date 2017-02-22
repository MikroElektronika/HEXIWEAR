#include "gui_driver.h"
#include "screens_common.h"
#include "reset_private.h"

guiScreen_t resetScreen =
{
  .navigation =
  {
          .up     = &aboutScreen,
          .down   = &nfc_click_Screen,
          .left   = &settingsScreen,
          .right  = NULL
  },

  .image = reset_screen_bmp,

  .initFunction        = reset_Init,
  .createTaskFunction  = reset_CreateTasks,
  .destroyTaskFunction = reset_DestroyTasks
};
