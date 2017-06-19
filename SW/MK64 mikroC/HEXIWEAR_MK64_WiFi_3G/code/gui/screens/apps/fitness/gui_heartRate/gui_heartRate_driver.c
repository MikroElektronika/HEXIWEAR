// File: gui_heartRate_driver.c

// Definitions of main functionalities in the heart rate gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "apps/fitness/gui_heartRate/gui_heartRate.h"
#include "apps/fitness/gui_heartRate/gui_heartRate_private.h"

#include "screens_common.h"

#include "OSA.h"
#include "error.h"

#include "heartRate_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

MSG_QUEUE_DECLARE( gui_heartRate_queue, 1, sizeof( uint32_t ) );

static msg_queue_handler_t gui_heartRate_queueHnd;

// new value given by the HR task

static uint32_t oldHrVal = 0;
static uint32_t newHrVal = 0;

static task_handler_t gui_heartRate_updateHR_taskHandler;
static task_handler_t gui_heartRate_taskHandler;

static hostInterface_packet_t gui_heartRate_packet;

static bool isHeartRateAppActive = false;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Updates heart-rate GUI.
static void gui_heartRate_Update()
{
    if( newHrVal != oldHrVal )
    {
        uint16_t valToWrite;

        // if invalid HR is received
        if( newHrVal == 0xFF )
        {
            valToWrite = 0;
        }
        else
        {
            valToWrite = newHrVal;
        }

        sprintf( ( uint8_t* )gui_heartRate_bpmVal_label.caption, // 4,
            "%03u", valToWrite );
        GuiDriver_LabelDraw( &gui_heartRate_bpmVal_label );

        oldHrVal = newHrVal;
    }
}

// Gets data from the designated HR queue.
static gui_heartRate_status_t gui_heartRate_QueueMsgGet( uint32_t timeout )
{
    osa_status_t status =
        OSA_MsgQGet( gui_heartRate_queueHnd, &newHrVal, timeout );

    if ( status == kStatus_OSA_Error )
    {
        error_catch( CATCH_QUEUE );
        return GUI_HEART_RATE_STATUS_ERROR;
    }
    else
    {
        return GUI_HEART_RATE_STATUS_SUCCESS;
    }
}

// Main heart-rate GUI task.
// Waits for data, checks if user turned the app on.
// Displays received heart-rate.
static void gui_heartRate_Task( task_param_t param )
{
    while( 1 )
    {
        gui_status_t status =
            GuiDriver_QueueMsgGet( &gui_heartRate_packet, OSA_WAIT_FOREVER );

        if( status == GUI_STATUS_SUCCESS )
        {
            if( gui_heartRate_packet.type == packetType_pressRight )
            {
                if( isHeartRateAppActive == false )
                {
                    isHeartRateAppActive = true;

                    power_DisablePowerSave();

                    GuiDriver_CleanMainArea();
                    GuiDriver_LabelDraw( &gui_heartRate_bpmVal_label );
                    GuiDriver_LabelDraw( &gui_heartRate_bpmText_label );
                    GuiDriver_ImageDraw( &screen_buttonStop );

                    vTaskResume( gui_heartRate_updateHR_taskHandler );
                    heartRate_Resume();
                }
                else
                {
                    heartRate_Pause();
                    vTaskSuspend( gui_heartRate_updateHR_taskHandler );

                    GuiDriver_CleanMainArea();
                    GuiDriver_ImageDraw( &gui_heartRate_icon );
                    GuiDriver_ImageDraw( &screen_buttonStart );

                    power_EnablePowerSave();
                    isHeartRateAppActive = false;
                }

                haptic_Vibrate();
            }
        }
    }
}

// Receives new data and updates heart-rate GUI.
static void gui_heartRate_UpdateHRTask( task_param_t param )
{
    while( 1 )
    {
        // wait for the new one
        gui_heartRate_status_t guiStatus =
            gui_heartRate_QueueMsgGet( OSA_WAIT_FOREVER );

        if( guiStatus != GUI_HEART_RATE_STATUS_SUCCESS )
        {
            error_catch( CATCH_HEALTH );
        }
        else
        {
            gui_heartRate_Update();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises heart-rate GUI.
void gui_heartRate_Init( void* param )
{
    // create the HR packet queue
    gui_heartRate_queueHnd = OSA_MsgQCreate( gui_heartRate_queue,
        1, sizeof( uint32_t ) / sizeof( uint32_t ) );
#if defined( HEXIWEAR_DEBUG )
    vQueueAddToRegistry( gui_heartRate_queueHnd, ( uint8_t* )"GUI HR Queue" );
#endif

    GuiDriver_ImageAddToScr( &screen_buttonStart );

    GuiDriver_LabelCreate( &gui_heartRate_bpmVal_label );
    sprintf( ( uint8_t* )gui_heartRate_bpmVal_label.caption, // 4,
        "%03u", 000 );

    GuiDriver_LabelCreate( &gui_heartRate_bpmText_label );
    GuiDriver_LabelSetCaption(
        &gui_heartRate_bpmText_label, ( uint8_t* )"bpm" );

    GuiDriver_ImageAddToScr( &gui_heartRate_icon );

    // listen if the user wants to use the HR
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );

    // initiate the HR process structures
    newHrVal = 0;
    heartRate_Init();

    GuiDriver_NotifyKW40( GUI_CURRENT_APP_HEART_RATE );
}

// Creates HR GUI tasks.
void gui_heartRate_CreateTasks( void* param )
{
    osa_status_t taskStatus;

    taskStatus = OSA_TaskCreate(
                                 gui_heartRate_Task,
                                 ( uint8_t* )"heart-rate window",
                                 GUI_HEARTRATE_STACK_SIZE,
                                 NULL,
                                 GUI_HEARTRATE_PRIO,
                                 ( task_param_t )0,
                                 false,
                                 &gui_heartRate_taskHandler
                               );

    taskStatus |= OSA_TaskCreate(
                                  gui_heartRate_UpdateHRTask,
                                  ( uint8_t* )"heart-rate bpm value",
                                  GUI_HEARTRATE_STEP_COUNTER_STACK_SIZE,
                                  NULL,
                                  GUI_HEARTRATE_STEP_COUNTER_PRIO,
                                  ( task_param_t )0,
                                  false,
                                  &gui_heartRate_updateHR_taskHandler
                                );

    if( taskStatus != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
    vTaskSuspend( gui_heartRate_updateHR_taskHandler );
}

// Destroys HR GUI tasks.
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

    if( gui_sensorTag_IsActive() == false  )
    {
        GuiDriver_NotifyKW40( GUI_CURRENT_APP_IDLE );
    }
}

// Puts data into designated HR GUI queue.
gui_heartRate_status_t gui_heartRate_QueueMsgPut( uint32_t* packet )
{
    BaseType_t status = xQueueSendToBack(
        gui_heartRate_queueHnd, ( uint32_t* )packet, OSA_WAIT_FOREVER );

    if( status == pdPASS )
    {
        return GUI_HEART_RATE_STATUS_SUCCESS;
    }
    else
    {
        error_catch( CATCH_QUEUE );
        return GUI_HEART_RATE_STATUS_ERROR;
    }
}