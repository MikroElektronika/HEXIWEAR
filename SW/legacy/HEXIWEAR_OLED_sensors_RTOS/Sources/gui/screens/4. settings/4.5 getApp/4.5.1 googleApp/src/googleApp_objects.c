#include "gui_driver.h"
#include "screens_common.h"
#include "googleApp_private.h"
#include "getApp.h"

guiScreen_t googleAppScreen =
{
  .navigation =
  {
          .up     = &iOSAppScreen,
          .down   = &iOSAppScreen,
          .left   = &getAppScreen,
          .right  = &googleAppQrCodeScreen
  },

  .image = googleApp_screen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};


guiScreen_t googleAppQrCodeScreen =
{
  .navigation =
  {
          .up     = NULL,
          .down   = NULL,
          .left   = &googleAppScreen,
          .right  = NULL
  },

  .image = googleAppQrCode_screen_bmp,

  .initFunction        = getApp_Init,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = getApp_Destroy
};
