/**
 * \file gui_heartRate_driver.c
 * \version 1.00
 * \brief this file contains heart-rate app GUI main task and functionality
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

#include "gui_heartRate.h"
#include "gui_heartRate_private.h"

#include "screens_common.h"

#include "fsl_os_abstraction.h"
#include "error.h"

#include "heartRate_driver.h"

/** private variables */

MSG_QUEUE_DECLARE( gui_heartRate_queue, 1, sizeof(uint32_t) );

static void gui_heartRate_Task( task_param_t param );
static void gui_heartRate_UpdateHRTask( void* param );
static void gui_heartRate_Update();
static gui_heartRate_status_t gui_heartRate_QueueMsgGet( uint32_t timeout );

static msg_queue_handler_t
    gui_heartRate_queueHnd;

/** new value given by the HR task */

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
 * initialize heart-rate GUI
 * @param param optional parameter
 */
void gui_heartRate_Init( void* param )
{
    // create the HR packet queue
    gui_heartRate_queueHnd = OSA_MsgQCreate (
                                                gui_heartRate_queue,
                                                1,
                                                sizeof(uint32_t) / sizeof(uint32_t)
                                            );
#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( gui_heartRate_queueHnd, (char*)"GUI HR Queue" );
#endif

    GuiDriver_ImageAddToScr(&screen_buttonStart);

    GuiDriver_LabelCreate( &gui_heartRate_bpmVal_label );
    snprintf( (char*)gui_heartRate_bpmVal_label.caption, 4, "%03u", 000 );

    GuiDriver_LabelCreate( &gui_heartRate_bpmText_label );
    GuiDriver_LabelSetCaption( &gui_heartRate_bpmText_label, (uint8_t*)"bpm" );

    GuiDriver_ImageAddToScr( &gui_heartRate_icon );

    // listen if the user wants to use the HR
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );

    // initiate the HR process structures
    newHrVal = 0;
    heartRate_Init();

    GuiDriver_NotifyKW40( GUI_CURRENT_APP_HEART_RATE );
}

/**
 * create HR GUI tasks
 * @param param optional parameter
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
 * destroy HR GUI tasks
 * @param param optional parameter
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
 * put data into designated HR GUI queue
 * @param  packet data to display
 * @return        status flag
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

/** private API */

/**
 * main heart-rate GUI task
 * wait for data, check if user turned the app on
 * display received heart-rate
 * @param  task_param_t optional parameter
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
 * receive new data and update heart-rate GUI
 * @param  task_param_t optional parameter
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
 * update heart-rate GUI
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
 * get data from the designated HR queue
 * @param  timeout time to wait for new data in [ms]
 * @return         status flag
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
