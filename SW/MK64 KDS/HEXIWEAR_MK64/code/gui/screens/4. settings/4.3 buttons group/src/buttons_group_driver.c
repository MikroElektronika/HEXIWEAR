/**
 * \file buttons_group_driver.c
 * \version 1.00
 * \brief this file contains button group private objects' declarations
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

/** include */

#include "gui_driver.h"
#include "screens_common.h"
#include "buttons_group_private.h"
#include "host_mcu_interface.h"
#include "fsl_os_abstraction.h"


/** private type definitions */

/** private macros */

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec)  (((uint32_t)(msec)+500uL/(uint32_t)configTICK_RATE_HZ) \
                             *(uint32_t)configTICK_RATE_HZ/1000uL)


/** private prototypes */

static void buttonsGroup_ToggleTask(task_param_t param);
static void buttonsGroup_ActiveUpdateTask(task_param_t param);

MSG_QUEUE_DECLARE( buttonsGroup_ActiveQueue, 1, 1);
static msg_queue_handler_t buttonsGroup_ActiveQueueHnd;

static event_t activeUpdate_event;

static event_flags_t activeUpdate_eventFlag  = 1;

/** public memory declarations */

task_handler_t buttonsGroup_handler;
task_handler_t buttonsGroup_ActiveUpdatehandler;

/** private memory declarations */

static hostInterface_packet_t buttonsGroup_dataPacket =
{
	.start1 = gHostInterface_startByte1,
	.start2 = gHostInterface_startByte2,
	.length = 0,
	.data[0] = gHostInterface_trailerByte
};

static buttonsGroup_t buttonsGroupCurrentActive = buttonsGroup_right;

/**
 * create the event for updating the active button group
 */
void buttonsGroup_CreateActiveUpdateEvent()
{
	OSA_EventCreate( &activeUpdate_event, kEventAutoClear );
}

/**
 * initialize the button group screen
 * @param param optional parameter
 */
void buttonsGroup_Init( void *param )
{
	if(buttonsGroupCurrentActive == buttonsGroup_right)
	{

		buttonsGroup_img.img = buttonGroup_rightSelected_bmp;
	}
	else
	{
		buttonsGroup_img.img = buttonGroup_leftSelected_bmp;
	}

	GuiDriver_ImageAddToScr(&buttonsGroup_img);

	// Create Rx Message Queue
	buttonsGroup_ActiveQueueHnd = OSA_MsgQCreate (buttonsGroup_ActiveQueue, 1, 1);

	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * create the button group GUI task
 * @param param optional parameter
 */
void buttonsGroup_CreateTasks( void *param )
{
	osa_status_t status;


	status = OSA_TaskCreate (
							      buttonsGroup_ToggleTask,
                                  (uint8_t *) "buttonsGroup_ToggleTask",
								  BUTTONS_GROUP_STACK_SIZE,
                                  NULL,
								  BUTTONS_GROUP_PRIO,
                                  (task_param_t)0,
                                  false,
                                  &buttonsGroup_handler
                                );

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	status = OSA_TaskCreate (
								      buttonsGroup_ActiveUpdateTask,
	                                  (uint8_t *) "buttonsGroup_ActiveUpdateTask",
									  BUTTONS_GROUP_STACK_SIZE,
	                                  NULL,
									  BUTTONS_GROUP_PRIO,
	                                  (task_param_t)0,
	                                  false,
	                                  &buttonsGroup_ActiveUpdatehandler
	                                );

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}
}

/**
 * destroy the button group GUI task
 * @param param optional parameter
 */
void buttonsGroup_DestroyTasks( void *param )
{
	osa_status_t status;


	status = OSA_TaskDestroy(buttonsGroup_handler);

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	status = OSA_TaskDestroy(buttonsGroup_ActiveUpdatehandler);

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	OSA_MsgQDestroy(buttonsGroup_ActiveQueueHnd);

	OLED_DestroyDynamicArea();
	GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * get active button group
 * @return  active button group
 */
buttonsGroup_t buttonsGroup_CurrnetActiveGet()
{
	return buttonsGroupCurrentActive;
}

/**
 * send the request to KW40
 */
void buttonsGroup_SendGetActiveReq()
{
	static hostInterface_packet_t dataPacket =
	{
		.start1 = gHostInterface_startByte1,
		.start2 = gHostInterface_startByte2,
		.length = 0,
		.data[0] = gHostInterface_trailerByte
	};

	dataPacket.type = packetType_buttonsGroupGetActive;
	while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&dataPacket, true) != kStatus_OSA_Success);
}

/**
 * send the request for toggling the active group
 */
void buttonsGroup_SendToggleActiveReq()
{
	static hostInterface_packet_t dataPacket =
	{
		.start1 = gHostInterface_startByte1,
		.start2 = gHostInterface_startByte2,
		.length = 0,
		.data[0] = gHostInterface_trailerByte
	};

	dataPacket.type = packetType_buttonsGroupToggleActive;
	while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&dataPacket, true) != kStatus_OSA_Success);
}

/**
 * wait for the update
 * @param  timeout time to wait in [ms]
 * @return         status flag
 */
osa_status_t buttonsGroup_WaitForActiveUpdate(uint32_t timeout)
{
	osa_status_t status;
	event_flags_t setFlags;

	status = OSA_EventWait(&activeUpdate_event, activeUpdate_eventFlag, false, timeout, &setFlags);

	if ( kStatus_OSA_Success != status )
	{
		return kStatus_OSA_Error;
	}

	return (osa_status_t)status;
}

/**
 * destroy the button group GUI update task
 * @param param optional parameter
 */
osa_status_t buttonsGroup_ActiveUpdate(buttonsGroup_t buttonsGroupActive)
{
	OSA_EventSet( &activeUpdate_event, (event_flags_t)activeUpdate_eventFlag);
	buttonsGroupCurrentActive = buttonsGroupActive;

	return kStatus_OSA_Success;
}

/**
 * destroy the button group GUI toggle task
 * @param param optional parameter
 */
static void buttonsGroup_ToggleTask(task_param_t param)
{
	while(1)
	{
		GuiDriver_QueueMsgGet( &buttonsGroup_dataPacket, OSA_WAIT_FOREVER );

		if(buttonsGroup_dataPacket.type == packetType_pressRight)
		{
			buttonsGroup_SendToggleActiveReq();
			haptic_Vibrate();
		}
	}
}

/**
 * wait for the update and then
 * update the active button group
 * @param param optional parameter
 */
static void buttonsGroup_ActiveUpdateTask(task_param_t param)
{
	while(1)
	{
		buttonsGroup_WaitForActiveUpdate(OSA_WAIT_FOREVER);

		if(buttonsGroupCurrentActive == buttonsGroup_right)
		{
			buttonsGroup_img.img = buttonGroup_rightSelected_bmp;

			OLED_DrawBox(2, 30, 4, 35, 0);
		}
		else
		{
			buttonsGroup_img.img = buttonGroup_leftSelected_bmp;

			OLED_DrawBox(92, 30, 4, 35, 0);
		}

		GuiDriver_ImageDraw(&buttonsGroup_img);

		GuiDriver_DrawButtonPointers(true, true);
	}
}


