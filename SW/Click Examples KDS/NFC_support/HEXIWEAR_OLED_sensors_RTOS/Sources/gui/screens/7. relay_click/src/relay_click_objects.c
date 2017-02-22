#include "gui_driver.h"
#include "screens_common.h"
#include "relay_click_private.h"

/**
 *
 * Definition of a_new_screen_screen
 */

 guiScreen_t relay_click_Screen =
 {
   .navigation =
   {
           .up     = &gui_sensorTag_screen,
           .down   = &appsScreen,
           .left   = NULL,
           .right  = NULL
   },

   .image = relay_click_bmp,

   .initFunction        = relay_click_Init,
   .createTaskFunction  = relay_click_CreateTasks,
   .destroyTaskFunction = relay_click_DestroyTasks
 };
