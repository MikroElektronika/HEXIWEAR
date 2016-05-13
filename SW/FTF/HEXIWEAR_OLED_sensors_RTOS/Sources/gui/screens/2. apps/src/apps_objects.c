

#include "gui_driver.h"
#include "screens_common.h"
#include "apps_private.h"

/************************************************************************************
*************************************************************************************
* Definition of watch screen
*************************************************************************************
************************************************************************************/

guiScreen_t appsScreen =
{
  .navigation =
  {
          .up     = &relay_click_Screen,
          .down   = &notifScreen,
          .left   = &watchScreen,
          .right  = &gui_weatherStation_coverScreen
  },

  .image = apps_screen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};
