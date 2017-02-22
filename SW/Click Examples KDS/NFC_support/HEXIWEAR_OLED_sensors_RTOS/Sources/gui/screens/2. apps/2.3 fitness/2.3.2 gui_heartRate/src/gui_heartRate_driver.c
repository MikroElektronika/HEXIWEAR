/**
 * GUI pedometer app functions
 * Project HEXIWEAR, 2015
 */

#include "gui_heartRate.h"
#include "gui_heartRate_private.h"

#include "screens_common.h"

#include "fsl_os_abstraction.h"
#include "error.h"

#include "heartRate_driver.h"
//#include <stdbool.h>

/**
 * private variables
 */

MSG_QUEUE_DECLARE( gui_heartRate_queue, 1, sizeof(uint32_t) );

static void gui_heartRate_Task( task_param_t param );
static void gui_heartRate_UpdateHRTask( void* param );
static void gui_heartRate_Update();
static gui_heartRate_status_t gui_heartRate_QueueMsgGet( uint32_t timeout );

static msg_queue_handler_t
    gui_heartRate_queueHnd;

/** new value given by the pedometer task */
static uint32_t
	oldHrVal = 0,
    newHrVal = 0;

static task_handler_t
	gui_heartRate_updateHR_taskHandler,
    gui_heartRate_taskHandler;

static hostInterface_packet_t
	gui_heartRate_packet;

static bool
	isHeartRateAppActive = false;

 /**
  * [gui_heartRate_Init description]
  * @param param [description]
  */
void gui_heartRate_Init( void* param )
{
    // create pedometer packet queue
    gui_heartRate_queueHnd = OSA_MsgQCreate (
                                                gui_heartRate_queue,
                                                1,
                                                sizeof(uint32_t) / sizeof(uint32_t)
                                            );
#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( gui_heartRate_queueHnd, (char*)"GUI Pedometer Queue" );
#endif

    GuiDriver_ImageAddToScr(&screen_buttonStart);

    GuiDriver_LabelCreate( &gui_heartRate_bpmVal_label );
    snprintf( (char*)gui_heartRate_bpmVal_label.caption, 4, "%03u", 000 );

    GuiDriver_LabelCreate( &gui_heartRate_bpmText_label );
    GuiDriver_LabelSetCaption( &gui_heartRate_bpmText_label, (uint8_t*)"bpm" );

    GuiDriver_ImageAddToScr( &gui_heartRate_icon );

    // listen if the user wants to use the pedometer
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );

    // initiate the pedometer process structures
    newHrVal = 0;
    heartRate_Init();

    GuiDriver_NotifyKW40( GUI_CURRENT_APP_HEART_RATE );
}

/**
 * [gui_heartRate_CreateTasks description]
 * @param param [description]
 */
void gui_heartRate_CreateTasks( void* param )
{
    osa_status_t
        taskStatus;

    taskStatus = OSA_TaskCreate (
    								gui_heartRate_Task,
    								(uint8_t*) "heart-rate window",
    								GUI_HEARTRATE_STACK_SIZE,
    								NULL,
    								GUI_HEARTRATE_PRIO,
    								(task_param_t)0,
    								false,
    								&gui_heartRate_taskHandler
    							);

	taskStatus |= OSA_TaskCreate(
									gui_heartRate_UpdateHRTask,
									(uint8_t*) "heart-rate bpm value",
									GUI_HEARTRATE_STEP_COUNTER_STACK_SIZE,
									NULL,
									GUI_HEARTRATE_STEP_COUNTER_PRIO,
									(task_param_t)0,
									false,
									&gui_heartRate_updateHR_taskHandler
								);

    if ( kStatus_OSA_Success != taskStatus )
    {
    	catch( CATCH_INIT );
    }
    vTaskSuspend( gui_heartRate_updateHR_taskHandler );
}

/**
 * [gui_heartRate_DestroyTasks description]
 * @param param [description]
 */
void gui_heartRate_DestroyTasks( void* param )
{
	// destroy tasks
    OSA_TaskDestroy( gui_heartRate_taskHandler );
    OSA_TaskDestroy( gui_heartRate_updateHR_taskHandler );

    // destroy queues
    OSA_MsgQDestroy( gui_heartRate_queueHnd );

    heartRate_Deinit();

    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_heartRate_bpmVal_label );
    GuiDriver_LabelDestroy( &gui_heartRate_bpmText_label );

    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );

    isHeartRateAppActive = false;

    power_EnablePowerSave();

    if ( false  == gui_sensorTag_IsActive() )
    {
      GuiDriver_NotifyKW40( GUI_CURRENT_APP_IDLE );
    }
}

/**
 * [gui_heartRate_QueueMsgPut description]
 * @param  packet [description]
 * @return        [description]
 */
gui_heartRate_status_t gui_heartRate_QueueMsgPut( uint32_t* packet )
{
    BaseType_t
        status = xQueueSendToBack ( gui_heartRate_queueHnd, (uint32_t*)packet, OSA_WAIT_FOREVER );

    if ( pdPASS == status )
    {
        return GUI_HEART_RATE_STATUS_SUCCESS;
    }

    else
    {
        catch( CATCH_QUEUE );
        return GUI_HEART_RATE_STATUS_ERROR;
    }
}

/**
 * private functions
 */

/**
 * [gui_heartRate_Task description]
 * @param  task_param_t [description]
 * @return              [description]
 */
static void gui_heartRate_Task( task_param_t param )
{
	while (1)
	{
		gui_status_t
			rightClickStatus = GuiDriver_QueueMsgGet( &gui_heartRate_packet , OSA_WAIT_FOREVER );

		if( GUI_STATUS_SUCCESS == rightClickStatus )
		{
			if ( packetType_pressRight == gui_heartRate_packet.type )
			{
				if ( false == isHeartRateAppActive )
				{
				    isHeartRateAppActive = true;

                    power_DisablePowerSave();

					GuiDriver_CleanMainArea();
				    GuiDriver_LabelDraw( &gui_heartRate_bpmVal_label );
				    GuiDriver_LabelDraw( &gui_heartRate_bpmText_label );
				    GuiDriver_ImageDraw(&screen_buttonStop);

  					vTaskResume( gui_heartRate_updateHR_taskHandler );
  					heartRate_Resume();
				}

				else
				{
					heartRate_Pause();
					vTaskSuspend( gui_heartRate_updateHR_taskHandler );

					GuiDriver_CleanMainArea();
					GuiDriver_ImageDraw( &gui_heartRate_icon );
					GuiDriver_ImageDraw(&screen_buttonStart);

					power_EnablePowerSave();
					isHeartRateAppActive = false;
				}

				haptic_Vibrate();
			}
		}
	}
}

/**
 * [gui_heartRate_UpdateSteps description]
 * @param  task_param_t [description]
 * @return              [description]
 */
static void gui_heartRate_UpdateHRTask( task_param_t param )
{
	while (1)
	{
	    // wait for the new one
	    gui_heartRate_status_t
	        guiStatus = gui_heartRate_QueueMsgGet( OSA_WAIT_FOREVER );

	    if ( GUI_HEART_RATE_STATUS_SUCCESS != guiStatus )
	    {
	        catch ( CATCH_HEALTH );
	    }
	    else
	    {
        	gui_heartRate_Update();
	    }
	}
}

/**
 * [gui_heartRate_UpdateScreen description]
 * @return [description]
 */
static void gui_heartRate_Update()
{
	if ( oldHrVal != newHrVal )
	{
		uint16_t
			valToWrite;

		// if invalid HR is received
		if ( 0xFF == newHrVal )
		{
			valToWrite = 0;
		}

		else
		{
			valToWrite = newHrVal;
		}

		snprintf( (char*)gui_heartRate_bpmVal_label.caption, 4, "%03u", valToWrite );
		GuiDriver_LabelDraw( &gui_heartRate_bpmVal_label );

		oldHrVal = newHrVal;
	}
}

/**
 * [heartRate_QueueMsgGet  description]
 * @param  timeout [description]
 * @return         [description]
 */
static gui_heartRate_status_t gui_heartRate_QueueMsgGet( uint32_t timeout )
{
    osa_status_t
        status = OSA_MsgQGet( gui_heartRate_queueHnd, &newHrVal, timeout );

    if ( kStatus_OSA_Error == status )
    {
        catch( CATCH_QUEUE );
        return GUI_HEART_RATE_STATUS_ERROR;
    }

    else
    {
        return GUI_HEART_RATE_STATUS_SUCCESS;
    }
}
