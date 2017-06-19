// File: flashlight_driver.c

// Definitions of main functionalities in the flashlight gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////
 
#include "gui_driver.h"
#include "apps/flashlight/flashlight.h"
#include "apps/flashlight/flashlight_private.h"
#include "settings/haptic/haptic.h"
#include "error.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define SetFlashOFF()                                                          \
    isFlashlightOn = false;                                                    \
    flashlight_icon.img = flashlight_off_bmp;                                  \
    FLASH_SetOFF()
    
#define SetFlashON()                                                           \
    isFlashlightOn = true;                                                     \
    flashlight_icon.img = flashlight_on_bmp;                                   \
    FLASH_SetON()

////////////////////////////////////////////////////////////////////////////////
// Static variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

task_handler_t flashlight_taskHandler;

static bool isFlashlightOn;

static hostInterface_packet_t flashlight_dataPacket;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Toggles the LEDS, making them active/inactive.
static void flashlight_ToggleTask( task_param_t param )
{
    while( 1 )
    {
        GuiDriver_QueueMsgGet( &flashlight_dataPacket, OSA_WAIT_FOREVER );

        if( flashlight_dataPacket.type == packetType_pressRight )
        {
            switch( isFlashlightOn )
            {
                case true:
                {
                    SetFlashOFF();
                    GuiDriver_ImageDraw( &flashlight_icon );
                    break;
                }
                case false:
                {
                    SetFlashON();
                    GuiDriver_ImageDraw( &flashlight_icon );
                    break;
                }
            }

            haptic_Vibrate();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the flashlight app.
void flashlight_Init( void* param )
{
    GuiDriver_ImageAddToScr( &flashlight_icon );
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

// Creates the app task.
void flashlight_CreateTasks( void* param )
{
    osa_status_t status = OSA_TaskCreate(
                                          flashlight_ToggleTask,
                                          ( uint8_t* )"flashlight task",
                                          FLASHLIGHT_STACK_SIZE,
                                          NULL,
                                          FLASHLIGHT_PRIO,
                                          ( task_param_t )0,
                                          false,
                                          &flashlight_taskHandler
                                        );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys the app task.
void flashlight_DestroyTasks( void* param )
{
    osa_status_t status = OSA_TaskDestroy( flashlight_taskHandler );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
    SetFlashOFF();
}

// Checks if the app is active.
bool flashlight_isFlashlightOn()
{
    return isFlashlightOn;
}