/**
 * a_new_screen functionalty
 * Project HEXIWEAR, 2015
 */

#include "gui_driver.h"
#include "relay_click.h"
#include "relay_click.h"
#include "haptic.h"
#include "GPIO.h"
#include "flashlight.h"

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

static task_handler_t relay_toggleHandler;
static hostInterface_packet_t relay_dataPacket;

static void relayToggle_Task(task_param_t param);

/**
 * [relay_click_Init description]
 * @param param [description]
 */
void relay_click_Init( void* param )
{
	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_LEFT );
	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}


/**
 * [relay_click_CreateTasks description]
 * @param param [description]
 */
void relay_click_CreateTasks( void* param )
{
	osa_status_t status;
	status = OSA_TaskCreate ( relayToggle_Task, (uint8_t *) "relayToggle_Task", 100, NULL,
							  10,
							  (task_param_t)0,
							  false,
							  &relay_toggleHandler
						    );
	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}
}

/**
 * [relay_click_DestroyTasks description]
 * @param param [description]
 */
void relay_click_DestroyTasks( void* param )
{
	osa_status_t status;

	status = OSA_TaskDestroy(relay_toggleHandler);

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_LEFT );
	GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}


/**
 * [buttonsGroup_ToggleTask description]
 * @param param [description]
 */

static void relayToggle_Task(task_param_t param)
{

	while (1)
	{
		GuiDriver_QueueMsgGet( &relay_dataPacket, OSA_WAIT_FOREVER );

		if(relay_dataPacket.type == packetType_pressLeft)
		{
			BLUE_LED_TOGGLE();
			GPIO_DRV_TogglePinOutput(REL2);
		}
		else if(relay_dataPacket.type == packetType_pressRight)
		{
			GREEN_LED_TOGGLE();
			GPIO_DRV_TogglePinOutput(REL1);
		}

		haptic_Vibrate();
	}
}
