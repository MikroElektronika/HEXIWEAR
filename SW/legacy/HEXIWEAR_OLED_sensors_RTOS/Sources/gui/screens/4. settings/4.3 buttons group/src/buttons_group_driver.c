
/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#include "gui_driver.h"
#include "screens_common.h"
#include "buttons_group_private.h"
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

static void buttonsGroup_ToggleTask(task_param_t param);
static void buttonsGroup_ActiveUpdateTask(task_param_t param);

MSG_QUEUE_DECLARE( buttonsGroup_ActiveQueue, 1, 1);
static msg_queue_handler_t buttonsGroup_ActiveQueueHnd;

static event_t activeUpdate_event;

static event_flags_t activeUpdate_eventFlag  = 1;

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */

task_handler_t buttonsGroup_handler;
task_handler_t buttonsGroup_ActiveUpdatehandler;

/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */

static hostInterface_packet_t buttonsGroup_dataPacket =
{
	.start1 = gHostInterface_startByte1,
	.start2 = gHostInterface_startByte2,
	.length = 0,
	.data[0] = gHostInterface_trailerByte
};


static buttonsGroup_t buttonsGroupCurrentActive = buttonsGroup_right;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void buttonsGroup_CreateActiveUpdateEvent()
{
	OSA_EventCreate( &activeUpdate_event, kEventAutoClear );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_Init description]
 * @param param [description]
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_CreateTasks description]
 * @param param [description]
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_DestroyTasks description]
 * @param param [description]
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

buttonsGroup_t buttonsGroup_CurrnetActiveGet(void)
{
	return buttonsGroupCurrentActive;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void buttonsGroup_SendGetActiveReq(void)
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void buttonsGroup_SendToggleActiveReq(void)
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_DestroyTasks description]
 * @param param [description]
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_DestroyTasks description]
 * @param param [description]
 */

osa_status_t buttonsGroup_ActiveUpdate(buttonsGroup_t buttonsGroupActive)
{
	OSA_EventSet( &activeUpdate_event, (event_flags_t)activeUpdate_eventFlag);
	buttonsGroupCurrentActive = buttonsGroupActive;

	return kStatus_OSA_Success;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_ToggleTask description]
 * @param param [description]
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

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 * [buttonsGroup_ToggleTask description]
 * @param param [description]
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
