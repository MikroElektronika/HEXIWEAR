/**
 * Fitness app functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_FITNESS
#define HG_FITNESS

#include <stdbool.h>
#include "gui_driver.h"
#include "gui_pedometer.h"

#define FITNESS_STACK_SIZE  ( 0x400 ) // todo: change to meaningful value

#define FITNESS_PRIO  ( HEXIWEAR_GUI_PRIO ) // todo: change to meaningful value

extern guiScreen_t
  fitnessScreen;

#endif
