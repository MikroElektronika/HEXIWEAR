
/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#include "gui_driver.h"
#include "screens_common.h"
#include "bluetooth_private.h"
#include "host_mcu_interface.h"
#include "fsl_os_abstraction.h"


/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec)  (((uint32_t)(msec)+500uL/(uint32_t)configTICK_RATE_HZ) \
                             *(uint32_t)configTICK_RATE_HZ/1000uL)


/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

static void bluetooth_AdvModeToggleTask(task_param_t param);
static void bluetooth_AdvModeUpdateTask(task_param_t param);

static event_t advModeUpdate_event;

static event_flags_t advModeUpdate_eventFlag  = 1;

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

task_handler_t bluetooth_AdvModeToggleHandler;
task_handler_t bluetooth_AdvModeUpdateHandler;

/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */

static hostInterface_packet_t bluetooth_dataPacket =
{
	.start1 = gHostInterface_startByte1,
	.start2 = gHostInterface_startByte2,
	.length = 0,
	.data[0] = gHostInterface_trailerByte
};


static bluetooth_advMode_t bluetoothCurrentAdvMode = bluetooth_advMode_enable;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void bluetooth_CreateAdvModeUpdateEvent()
{
	OSA_EventCreate( &advModeUpdate_event, kEventAutoClear );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_Init description]
 * @param param [description]
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_CreateTasks description]
 * @param param [description]
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_DestroyTasks description]
 * @param param [description]
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bluetooth_advMode_t bluetooth_CurrentAdvModeGet(void)
{
	return bluetoothCurrentAdvMode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void bluetooth_SendGetAdvModeReq(void)
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void bluetooth_SendToggleAdvModeReq(void)
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_DestroyTasks description]
 * @param param [description]
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_DestroyTasks description]
 * @param param [description]
 */

osa_status_t bluetooth_AdvModeUpdate(bluetooth_advMode_t bluetooth_advMode)
{
	OSA_EventSet( &advModeUpdate_event, (event_flags_t)advModeUpdate_eventFlag);
	bluetoothCurrentAdvMode = bluetooth_advMode;

	return kStatus_OSA_Success;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_ToggleTask description]
 * @param param [description]
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

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_ToggleTask description]
 * @param param [description]
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
