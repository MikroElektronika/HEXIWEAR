#include "gui_driver.h"
#include "screens_common.h"
#include "getApp_private.h"

guiScreen_t getAppScreen =
{
  .navigation =
  {
          .up     = &hapticScreen,
          .down   = &aboutScreen,
          .left   = &settingsScreen,
          .right  = &googleAppScreen
  },

  .image = getApp_screen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};
