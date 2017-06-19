// File: reset_driver.c

// Definitions of main functionalities in the reset gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "settings/reset/reset.h"
#include "settings/reset/reset_private.h"
#include "settings/haptic/haptic.h"
#include "HEXIWEAR_driver.h"
#include "error.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static hostInterface_packet_t reset_dataPacket;

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

task_handler_t reset_taskHandler;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Task for resseting the MCU.
static void reset_ToggleTask( task_param_t param )
{
    while( 1 )
    {
        GuiDriver_QueueMsgGet( &reset_dataPacket, OSA_WAIT_FOREVER );

        if( reset_dataPacket.type == packetType_pressRight )
        {
            haptic_Vibrate();
            HEXIWEAR_ResetMCU();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the Reset screen.
void reset_Init( void* param )
{
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

// Initialises the reset task.
void reset_CreateTasks( void* param )
{
    osa_status_t status = OSA_TaskCreate(
                                          reset_ToggleTask,
                                          ( uint8_t* )"reset task",
                                          RESET_STACK_SIZE,
                                          NULL,
                                          RESET_PRIO,
                                          ( task_param_t )0,
                                          false,
                                          &reset_taskHandler
                                        );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys the reset task.
void reset_DestroyTasks( void* param )
{
    osa_status_t status = OSA_TaskDestroy( reset_taskHandler );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}