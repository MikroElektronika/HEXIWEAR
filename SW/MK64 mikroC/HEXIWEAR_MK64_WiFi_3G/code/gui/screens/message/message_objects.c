// File: bond_objects.c

// Definitions of objects used in the bond gui module.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "gui_driver.h"
#include "screens_common.h"
#include "message_private.h"

/******************************************************************************
 * Global variable definitions.                                               *
 ******************************************************************************/


guiScreen_t messageMissingWirelessScreen =
{
    NULL,              // .navigation.up
    NULL,              // .navigation.down
    NULL,              // .navigation.left
    NULL,              // .navigation.right

    missing_wireless_bmp,   // .image

    messageMissingWireless_Init,         // .initFunction
    NULL,              // .createTaskFunction
    message_DestroyTasks  // .destroyTaskFunction
};