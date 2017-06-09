// File: fitness_objects.c

// Definitions of objects used in the fitness gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "apps/fitness/fitness_private.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

guiScreen_t fitnessScreen =
{
    &flashlightScreen,               // .navigation.up
    &gui_weatherStation_coverScreen, // .navigation.down
    &appsScreen,                     // .navigation.left
    &pedometerScreen,                // .navigation.right

    fitness_screen_bmp,              // .image

    NULL,                            // .initFunction
    NULL,                            // .createTaskFunction
    NULL                             // .destroyTaskFunction
};