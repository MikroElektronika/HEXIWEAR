/**
 * a_new_screen functionalty
 * Project HEXIWEAR, 2015
 */

#include "gui_driver.h"
#include "nfc_click.h"
#include "haptic.h"
#include "GPIO.h"
#include "flashlight.h"
#include "nfc_task.h"

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

static task_handler_t nfc_toggleHandler;
static hostInterface_packet_t nfc_dataPacket;

static void nfcToggle_Task(task_param_t param);

/**
 * [nfc_click_Init description]
 * @param param [description]
 */
void nfc_click_Init( void* param )
{
	if(nfc_task_isActive())
	{
		GuiDriver_ImageAddToScr( &nfc_click_ON_icon );
	}
	else
	{
		GuiDriver_ImageAddToScr( &nfc_click_OFF_icon );
	}
	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}


/**
 * [nfc_click_CreateTasks description]
 * @param param [description]
 */
void nfc_click_CreateTasks( void* param )
{
	osa_status_t status;
	status = OSA_TaskCreate ( nfcToggle_Task, (uint8_t *) "nfcToggle_Task", 1200, NULL,
							  10,
							  (task_param_t)0,
							  false,
							  &nfc_toggleHandler
						    );
	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}
}

/**
 * [nfc_click_DestroyTasks description]
 * @param param [description]
 */
void nfc_click_DestroyTasks( void* param )
{
	osa_status_t status;

	status = OSA_TaskDestroy(nfc_toggleHandler);

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}


/**
 * [buttonsGroup_ToggleTask description]
 * @param param [description]
 */

static void nfcToggle_Task(task_param_t param)
{
	while (1)
	{
		GuiDriver_QueueMsgGet( &nfc_dataPacket, OSA_WAIT_FOREVER );

		if (nfc_task_isActive())
		{
			if(nfc_task_deinit())
			{
				GuiDriver_ImageDraw( &nfc_click_OFF_icon );
			}
		}
		else
		{
			if(nfc_task_init())
			{
				GuiDriver_ImageDraw( &nfc_click_ON_icon );
			}
		}
		haptic_Vibrate();
	}
}
