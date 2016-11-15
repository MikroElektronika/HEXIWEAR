/*
 * Control_driver.c
 *
 *  Created on: 12.11.2016
 *      Author: Patrick
 */


#include "gui_driver.h"
#include "control.h"
#include "control_private.h"
#include "haptic.h"
#include "GPIO.h"

/** intern functions declarations */

static void control_LED1ToggleTask( task_param_t param );

task_handler_t
	control_taskHandler;

static hostInterface_packet_t
	control_dataPacket;


void control_Init( void *param )
{
	//GuiDriver_ImageAddToScr(&bluetooth_icon);
	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_UP );
	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_DOWN );
}


void control_CreateTasks( void* param )
{
    osa_status_t
        status = OSA_TaskCreate (
        						  control_LED1ToggleTask,
                                  (uint8_t *) "LED1Toggle task",
                                  CONTROL_STACK_SIZE,
                                  NULL,
                                  CONTROL_PRIO,
                                  (task_param_t)0,
                                  false,
                                  &control_taskHandler
                                );

    if ( kStatus_OSA_Success != status )
    {
        catch( CATCH_INIT );
    }
}

void control_DestroyTasks( void* param )
{
    osa_status_t
        status = OSA_TaskDestroy( control_taskHandler );

    if ( kStatus_OSA_Success != status )
    {
        catch( CATCH_INIT );
    }

    //OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_UP );
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_DOWN );
    //SetFlashOFF();
}


static void control_LED1ToggleTask(task_param_t param)
{
	while(1)
	{
		GuiDriver_QueueMsgGet(&control_dataPacket, OSA_WAIT_FOREVER);

		if(control_dataPacket.type == packetType_pressUp)
		{
			GPIO_DRV_TogglePinOutput(LED1);
		}
		else if(control_dataPacket.type == packetType_pressDown)
		{
			GPIO_DRV_TogglePinOutput(LED2);
		}
		haptic_Vibrate();
	}
}




/**
 * initialize control GUI
 * @param param optional parameter

void bluetooth_Init( void *param )
{
	if(bluetoothCurrentAdvMode == bluetooth_advMode_enable)
	{
		bluetooth_icon.img = bluetooth_icon_blue_bmp;
	}
	else
	{
		bluetooth_icon.img = bluetooth_icon_white_bmp;
	}

	GuiDriver_ImageAddToScr(&bluetooth_icon);

	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}
*/
