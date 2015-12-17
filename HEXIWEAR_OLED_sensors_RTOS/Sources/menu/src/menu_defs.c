/**
 * menu structures
 * Project HEXIWEAR, 2015
 */

#include "menu_defs.h"
#include "apps.h"

// the screen structure
menuScreen_t
  menuDriver_screen;

msg_queue_handler_t
  MenuDriver_queueHnd;

// apps
task_handler_t
//  hexiwear_app_WATCH_handler = watch_handler,
  hexiwear_app_WATCH_handler,
  hexiwear_app_SENSORS_handler,
  hexiwear_app_FITNESS_handler;
