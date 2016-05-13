#include "gui_driver.h"
#include "screens_common.h"
#include "iOSApp_private.h"
#include "getApp.h"

guiScreen_t iOSAppScreen =
{
  .navigation =
  {
          .up     = &googleAppScreen,
          .down   = &googleAppScreen,
          .left   = &getAppScreen,
          .right  = &iOSAppQrCodeScreen
  },

  .image = iOSApp_screen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};


guiScreen_t iOSAppQrCodeScreen =
{
  .navigation =
  {
          .up     = NULL,
          .down   = NULL,
          .left   = &iOSAppScreen,
          .right  = NULL
  },

  .image = iOSAppQrCode_screen_bmp,

  .initFunction        = getApp_Init,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = getApp_Destroy
};
