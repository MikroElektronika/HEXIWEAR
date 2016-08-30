/*
 * watch_set_objects.c
 *
 *  Created on: Aug 30, 2016
 *      Author: denes
 */


#include "gui_driver.h"
#include "screens_common.h"
#include "watch_set_private.h"
#include "watch_set.h"

guiScreen_t watchSetScreen =
{
  .navigation =
  {
          .up     = &resetScreen,
          .down   = &bluetoothScreen,
          .left   = &settingsScreen,
          .right  = NULL
  },

  .image = NULL,

  .initFunction        = watchSet_Init,
  .createTaskFunction  = watchSet_CreateTasks,
  .destroyTaskFunction = watchSet_DestroyTasks
};
