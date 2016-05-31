#include "gui_driver.h"
#include "screens_common.h"

#include "power_driver.h"

guiScreen_t power_standbyScreen =
{
  .navigation =
  {
    .up     = NULL,
    .down   = NULL,
    .left   = NULL,
    .right  = NULL
  },

  .image = NULL,

  .initFunction        = power_StandbyInit,
  .createTaskFunction  = NULL,
  .destroyTaskFunction = power_StandbyDestroyTasks
};
