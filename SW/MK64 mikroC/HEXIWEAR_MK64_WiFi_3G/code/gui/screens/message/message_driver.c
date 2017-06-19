// File: message_driver.c

// Definitions of main functionalities in the bond gui module.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "message.h"
#include "gui_driver.h"
#include "screens_common.h"
#include "message/message_private.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/
    
/******************************************************************************
 * Static variable definitions.                                               *
 ******************************************************************************/

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/

// Initialises the Message Wifi Screen.
void messageMissingWireless_Init( void *param )
{
    if( ( guiScreen_t* )param != &messageMissingWirelessScreen)
    {
        messageMissingWirelessScreen.navigation.left = ( guiScreen_t* )param;
    }
}

// Destroys the Bond Screen.
void message_DestroyTasks( void *param )
{
    OLED_DestroyDynamicArea();
}