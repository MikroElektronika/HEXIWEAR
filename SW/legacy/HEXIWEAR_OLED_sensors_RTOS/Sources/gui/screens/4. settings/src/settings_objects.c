

#include "gui_driver.h"
#include "screens_common.h"
#include "settings_private.h"

/************************************************************************************
*************************************************************************************
* Definition of watch screen
*************************************************************************************
************************************************************************************/

guiScreen_t settingsScreen =
{
  .navigation =
  {
          .up     = &notifScreen,
//          .up     = &appsScreen,
          .down   = &gui_sensorTag_screen,
          .left   = &watchScreen,
          .right  = &bluetoothScreen
  },

  .image = settings_screen_bmp,

  .initFunction        = NULL,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = NULL
};
