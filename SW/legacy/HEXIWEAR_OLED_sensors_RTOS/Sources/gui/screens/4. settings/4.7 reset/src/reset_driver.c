/**
 * reset screen
 * Project HEXIWEAR, 2015
 */

#include "gui_driver.h"
#include "reset.h"
#include "reset_private.h"
#include "haptic.h"
#include "GPIO.h"
#include "HEXIWEAR_driver.h"

/**
 * intern functions declarations
 */

static void reset_ToggleTask( task_param_t param );

task_handler_t
	reset_taskHandler;

static hostInterface_packet_t
	reset_dataPacket;

/**
 * [reset_Init description]
 * @param param [description]
 */
void reset_Init( void* param )
{
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * [reset_CreateTasks description]
 * @param param [description]
 */
void reset_CreateTasks( void* param )
{
    osa_status_t
        status = OSA_TaskCreate (
                                  reset_ToggleTask,
                                  (uint8_t *) "reset task",
                                  RESET_STACK_SIZE,
                                  NULL,
                                  RESET_PRIO,
                                  (task_param_t)0,
                                  false,
                                  &reset_taskHandler
                                );

    if ( kStatus_OSA_Success != status )
    {
        catch( CATCH_INIT );
    }
}

/**
 * [reset_DestroyTasks description]
 * @param param [description]
 */
void reset_DestroyTasks( void* param )
{
    osa_status_t
        status = OSA_TaskDestroy( reset_taskHandler );

    if ( kStatus_OSA_Success != status )
    {
        catch( CATCH_INIT );
    }

    OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * [reset_ToggleTask description]
 * @param param [description]
 */
static void reset_ToggleTask( task_param_t param )
{
    while(1)
    {
        GuiDriver_QueueMsgGet( &reset_dataPacket, OSA_WAIT_FOREVER );

        if( packetType_pressRight == reset_dataPacket.type )
        {
            haptic_Vibrate();
            HEXIWEAR_ResetMCU();
        }
    }
}
