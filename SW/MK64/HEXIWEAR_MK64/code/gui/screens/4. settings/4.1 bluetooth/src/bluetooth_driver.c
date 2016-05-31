/**
 * \file bluetooth_driver.c
 * \version 1.00
 * \brief this file contains bluetooth GUI functionality
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

/** includes */

#include "gui_driver.h"
#include "screens_common.h"
#include "bluetooth_private.h"
#include "host_mcu_interface.h"
#include "fsl_os_abstraction.h"


/** private type definitions */

/** private macros */

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec)  (((uint32_t)(msec)+500uL/(uint32_t)configTICK_RATE_HZ) \
                             *(uint32_t)configTICK_RATE_HZ/1000uL)


/** private prototypes */

static void bluetooth_AdvModeToggleTask(task_param_t param);
static void bluetooth_AdvModeUpdateTask(task_param_t param);

static event_t advModeUpdate_event;

static event_flags_t advModeUpdate_eventFlag  = 1;

/** Public memory declarations */

task_handler_t bluetooth_AdvModeToggleHandler;
task_handler_t bluetooth_AdvModeUpdateHandler;

/** Private memory declarations */

static hostInterface_packet_t bluetooth_dataPacket =
{
	.start1 = gHostInterface_startByte1,
	.start2 = gHostInterface_startByte2,
	.length = 0,
	.data[0] = gHostInterface_trailerByte
};

static bluetooth_advMode_t bluetoothCurrentAdvMode = bluetooth_advMode_enable;

/**
 * create the event for bluetooth update
 */
void bluetooth_CreateAdvModeUpdateEvent()
{
	OSA_EventCreate( &advModeUpdate_event, kEventAutoClear );
}

/**
 * initialize bluetooth GUI
 * @param param optional parameter
 */
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

/**
 * create bluetooth GUI tasks
 * @param param optional parameter
 */

void bluetooth_CreateTasks( void *param )
{
	osa_status_t status;


	status = OSA_TaskCreate (
			                      bluetooth_AdvModeToggleTask,
                                  (uint8_t *) "bluetooth_ToggleTask",
								  BLUETOOTH_STACK_SIZE,
                                  NULL,
								  BLUETOOTH_PRIO,
                                  (task_param_t)0,
                                  false,
                                  &bluetooth_AdvModeToggleHandler
                                );

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	status = OSA_TaskCreate (
			                          bluetooth_AdvModeUpdateTask,
	                                  (uint8_t *) "bluetooth_AdvModeUpdateTask",
									  BLUETOOTH_STACK_SIZE,
	                                  NULL,
									  BLUETOOTH_PRIO,
	                                  (task_param_t)0,
	                                  false,
	                                  &bluetooth_AdvModeUpdateHandler
	                                );

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}
}

/**
 * destroy bluetooth GUI tasks
 * @param param optional parameter
 */

void bluetooth_DestroyTasks( void *param )
{
	osa_status_t status;


	status = OSA_TaskDestroy(bluetooth_AdvModeToggleHandler);

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	status = OSA_TaskDestroy(bluetooth_AdvModeUpdateHandler);

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	OLED_DestroyDynamicArea();
	GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * get current advertisement mode
 * @return  current mode
 */
bluetooth_advMode_t bluetooth_CurrentAdvModeGet()
{
	return bluetoothCurrentAdvMode;
}

/**
 * send request to get advertisement mode
 */
void bluetooth_SendGetAdvModeReq()
{
	static hostInterface_packet_t dataPacket =
	{
		.start1 = gHostInterface_startByte1,
		.start2 = gHostInterface_startByte2,
		.length = 0,
		.data[0] = gHostInterface_trailerByte
	};

	dataPacket.type = packetType_advModeGet;
	while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&dataPacket, true) != kStatus_OSA_Success);
}


/**
 * send request to toggle advertisement mode
 */
void bluetooth_SendToggleAdvModeReq()
{
	static hostInterface_packet_t dataPacket =
	{
		.start1 = gHostInterface_startByte1,
		.start2 = gHostInterface_startByte2,
		.length = 0,
		.data[0] = gHostInterface_trailerByte
	};

	dataPacket.type = packetType_advModeToggle;
	while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&dataPacket, true) != kStatus_OSA_Success);
	haptic_Vibrate();
}

/**
 * wait for the mode update
 * @param  timeout time to wait in [ms]
 * @return         status flag
 */
osa_status_t bluetooth_WaitForAdvModeUpdate(uint32_t timeout)
{
	osa_status_t status;
	event_flags_t setFlags;

	status = OSA_EventWait(&advModeUpdate_event, advModeUpdate_eventFlag, false, timeout, &setFlags);

	if ( kStatus_OSA_Success != status )
	{
		return kStatus_OSA_Error;
	}

	return (osa_status_t)status;
}

/**
 * update the advertisement mode
 * @param  bluetooth_advMode new mode
 * @return                   status flag
 */
osa_status_t bluetooth_AdvModeUpdate(bluetooth_advMode_t bluetooth_advMode)
{
	OSA_EventSet( &advModeUpdate_event, (event_flags_t)advModeUpdate_eventFlag);
	bluetoothCurrentAdvMode = bluetooth_advMode;

	return kStatus_OSA_Success;
}

/**
 * toggle the advertisement mode
 * @param param optional parameter
 */
static void bluetooth_AdvModeToggleTask(task_param_t param)
{
	while(1)
	{
		GuiDriver_QueueMsgGet( &bluetooth_dataPacket, OSA_WAIT_FOREVER );

		if(bluetooth_dataPacket.type == packetType_pressRight)
		{
			bluetooth_SendToggleAdvModeReq();
		}
	}
}

/**
 * wait for the mode update and then update the advertisement mode
 * @param param optional parameter
 */
static void bluetooth_AdvModeUpdateTask(task_param_t param)
{
	bluetooth_SendGetAdvModeReq();

	while(1)
	{
		bluetooth_WaitForAdvModeUpdate(OSA_WAIT_FOREVER);

		if(bluetoothCurrentAdvMode == bluetooth_advMode_enable)
		{
			OSA_TimeDelay( 500 );
			if ( true == gui_sensorTag_IsActive() )
			{
				GuiDriver_NotifyKW40( GUI_CURRENT_APP_SENSOR_TAG );
			}

			bluetooth_icon.img = bluetooth_icon_blue_bmp;
		}
		else
		{
			watch_LinkStateUpdate(linkState_disconnected);
			bluetooth_icon.img = bluetooth_icon_white_bmp;
		}

		GuiDriver_ImageDraw(&bluetooth_icon);
	}
}
