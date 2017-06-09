/**
 * \file gui_pedometer_driver.c
 * \version 1.00
 * \brief this file contains pedometer app GUI main task and functionality
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

#include "gui_pedometer.h"
#include "gui_pedometer_private.h"

#include "screens_common.h"

#include "fsl_os_abstraction.h"
#include "error.h"

#include "pedometer_driver.h"

/** private variables */

MSG_QUEUE_DECLARE( gui_pedometer_queue, 1, sizeof(uint32_t) );

static void gui_pedometer_Task( task_param_t param );
static void gui_pedometer_UpdateStepsTask( void* param );
static void gui_pedometer_Update();
static gui_pedometer_status_t gui_pedometer_QueueMsgGet( uint32_t timeout );

static msg_queue_handler_t
    gui_pedometer_queueHnd;

/** new value given by the pedometer task */

static uint32_t
    newPedVal = 0;

/** steps */

static uint16_t
    oldStepVal = 0,
    newStepVal = 0;

/** calories */

static uint16_t
    oldCalVal = 0,
    newCalVal = 0;

static task_handler_t
    gui_pedometer_step_counter_taskHandler,
    gui_pedometer_taskHandler;

static hostInterface_packet_t
	gui_pedometer_packet;

static bool
	isPedometerActive = false;

/**
 * initialize pedometer app GUI
 * @param param optional parameter
 */
void gui_pedometer_Init( void* param )
{
    // create pedometer packet queue
    gui_pedometer_queueHnd = OSA_MsgQCreate (
                                                gui_pedometer_queue,
                                                1,
                                                sizeof(uint32_t) / sizeof(uint32_t)
                                            );
#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( gui_pedometer_queueHnd, (char*)"GUI Pedometer Queue" );
#endif

    GuiDriver_ImageAddToScr( &screen_buttonStart );

    GuiDriver_LabelCreate( &gui_pedometer_stepCounter_label );
    snprintf( (char*)gui_pedometer_stepCounter_label.caption, 4, "%03u", 000 );

    GuiDriver_LabelCreate( &gui_pedometer_stepText_label );
    GuiDriver_LabelSetCaption( &gui_pedometer_stepText_label, (uint8_t*)"steps" );

    GuiDriver_LabelCreate( &gui_pedometer_calCounter_label );
    snprintf( (char*)gui_pedometer_calCounter_label.caption, 4, "%03u", 000 );

    GuiDriver_LabelCreate( &gui_pedometer_calText_label );
    GuiDriver_LabelSetCaption( &gui_pedometer_calText_label, (uint8_t*)"Cal" );

    GuiDriver_ImageAddToScr( &gui_pedometer_icon );

    // listen if the user wants to use the pedometer
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );

    // initiate the pedometer process structures
    oldStepVal = newStepVal = 0;
    pedometer_Init();

    GuiDriver_NotifyKW40( GUI_CURRENT_APP_PEDOMETER );
}

/**
 * create the pedometer GUI app tasks
 * @param param optional parameter
 */
void gui_pedometer_CreateTasks( void* param )
{
    osa_status_t
        taskStatus;

    pedometer_CreateTask();

	taskStatus = OSA_TaskCreate (
									gui_pedometer_Task,
									(uint8_t*) "pedometer window",
									GUI_PEDOMETER_STACK_SIZE,
									NULL,
									GUI_PEDOMETER_PRIO,
									(task_param_t)0,
									false,
									&gui_pedometer_taskHandler
								);

	taskStatus |= OSA_TaskCreate(
									gui_pedometer_UpdateStepsTask,
									(uint8_t*) "pedometer step counter",
									GUI_PEDOMETER_STEP_COUNTER_STACK_SIZE,
									NULL,
									GUI_PEDOMETER_STEP_COUNTER_PRIO,
									(task_param_t)0,
									false,
									&gui_pedometer_step_counter_taskHandler
								);

    if ( kStatus_OSA_Success != taskStatus )
    {
    	catch( CATCH_INIT );
    }
    vTaskSuspend( gui_pedometer_step_counter_taskHandler );
}

/**
 * destroy the pedometer GUI app tasks
 * @param param optional parameter
 */
void gui_pedometer_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_pedometer_taskHandler );
    OSA_TaskDestroy( gui_pedometer_step_counter_taskHandler );
    OSA_MsgQDestroy( gui_pedometer_queueHnd );

    pedometer_Deinit();

    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_pedometer_stepCounter_label );
    GuiDriver_LabelDestroy( &gui_pedometer_stepText_label );

    GuiDriver_LabelDestroy( &gui_pedometer_calCounter_label );
    GuiDriver_LabelDestroy( &gui_pedometer_calText_label );

    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );

    isPedometerActive = false;

    power_EnablePowerSave();

    if ( false  == gui_sensorTag_IsActive() )
    {
      GuiDriver_NotifyKW40( GUI_CURRENT_APP_IDLE );
    }
}

/**
 * put the packet into pedometer app GUI queue
 * @param  packet data to be put into the queue
 * @return        status flag
 */
gui_pedometer_status_t gui_pedometer_QueueMsgPut( uint32_t* packet )
{
  BaseType_t
    status = xQueueSendToBack ( gui_pedometer_queueHnd, (uint32_t*)packet, OSA_WAIT_FOREVER );

  if ( pdPASS == status )
  {
    return GUI_PEDOMETER_STATUS_SUCCESS;
  }

  else
  {
    catch( CATCH_QUEUE );
    return GUI_PEDOMETER_STATUS_ERROR;
  }
}

/** private API */

/**
 * pedometer app GUI main task,
 * get data from pedometer app and display it
 * @param  task_param_t optional parameter
 */
static void gui_pedometer_Task( task_param_t param )
{
	while (1)
	{
		gui_status_t
			rightClickStatus = GuiDriver_QueueMsgGet( &gui_pedometer_packet , OSA_WAIT_FOREVER );

		if( GUI_STATUS_SUCCESS == rightClickStatus )
		{
			if ( packetType_pressRight == gui_pedometer_packet.type )
			{
				if ( false == isPedometerActive )
				{
					isPedometerActive = true;
					power_DisablePowerSave();

					GuiDriver_CleanMainArea();
				    GuiDriver_LabelDraw( &gui_pedometer_stepCounter_label );
				    GuiDriver_LabelDraw( &gui_pedometer_stepText_label );
				    GuiDriver_LabelDraw( &gui_pedometer_calCounter_label );
				    GuiDriver_LabelDraw( &gui_pedometer_calText_label );
				    GuiDriver_ImageDraw(&screen_buttonStop);

					vTaskResume( gui_pedometer_step_counter_taskHandler );
					pedometer_Resume();
				}
				else
				{
  					pedometer_Pause();
  					vTaskSuspend( gui_pedometer_step_counter_taskHandler );

  					GuiDriver_CleanMainArea();
  					GuiDriver_ImageDraw( &gui_pedometer_icon );
  					GuiDriver_ImageDraw(&screen_buttonStart);

  					power_EnablePowerSave();
  					isPedometerActive = false;
				}

				haptic_Vibrate();
			}
		}
	}
}

/**
 * monitor and update GUI when step counter changes
 * @param  task_param_t optional parameter
 */
static void gui_pedometer_UpdateStepsTask( task_param_t param )
{
	while (1)
	{
	    // save the old values
	    oldStepVal = newStepVal;
	    oldCalVal  = newCalVal;

	    // wait for the new one
	    gui_pedometer_status_t
	      guiStatus = gui_pedometer_QueueMsgGet( OSA_WAIT_FOREVER );

	    if ( GUI_PEDOMETER_STATUS_SUCCESS != guiStatus )
	    {
	      catch ( CATCH_HEALTH );
	    }
	    else
	    {
	    	gui_pedometer_Update();
	    }
	}
}


/**
 * update pedometer GUI
 */
static void gui_pedometer_Update()
{
    newStepVal = (uint16_t)( newPedVal );
    newCalVal  = (uint16_t)( newPedVal >> 16 );

    if ( ( oldStepVal != newStepVal ) && ( 0 != newStepVal ) )
    {
    snprintf( (char*)gui_pedometer_stepCounter_label.caption, 4, "%03u", newStepVal );
    GuiDriver_LabelDraw( &gui_pedometer_stepCounter_label );
    }

    if ( ( oldCalVal != newCalVal ) && ( 0 != newCalVal ) )
    {
    snprintf( (char*)gui_pedometer_calCounter_label.caption, 4, "%03u", newCalVal );
    GuiDriver_LabelDraw( &gui_pedometer_calCounter_label );
    }
}

/**
 * get data from the GUI queue
 * @param  timeout time value to wait for data in [ms]
 * @return         status flag
 */
static gui_pedometer_status_t gui_pedometer_QueueMsgGet( uint32_t timeout )
{
  osa_status_t
    status = OSA_MsgQGet( gui_pedometer_queueHnd, &newPedVal, timeout );

  if ( kStatus_OSA_Error == status )
  {
    catch( CATCH_QUEUE );
    return GUI_PEDOMETER_STATUS_ERROR;
  }

  else
  {
    return GUI_PEDOMETER_STATUS_SUCCESS;
  }
}
