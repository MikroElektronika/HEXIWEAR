#include "gui_driver.h"
#include "screens_common.h"
#include "about_private.h"

guiScreen_t aboutScreen =
{
  .navigation =
  {
          .up     = &getAppScreen,
          .down   = &resetScreen,
          .left   = &settingsScreen,
          .right  = &infoScreen
  },

  .image = about_screen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};


guiImage_t about_qrHexiwearIcon =
{
       .dynamicArea =
       {
               .xCrd = 9,
               .yCrd = 3,
       },

       .img = about_qrHexiwear_bmp
};
