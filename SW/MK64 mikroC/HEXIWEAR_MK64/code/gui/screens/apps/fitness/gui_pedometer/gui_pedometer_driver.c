// File: gui_pedometer_driver.c

// Definitions of main functionalities in the pedometer gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "apps/fitness/gui_pedometer/gui_pedometer.h"
#include "apps/fitness/gui_pedometer/gui_pedometer_private.h"

#include "screens_common.h"

#include "OSA.h"
#include "error.h"

//#include "pedometer_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

MSG_QUEUE_DECLARE( gui_pedometer_queue, 1, sizeof(uint32_t) );

static msg_queue_handler_t gui_pedometer_queueHnd;

// new value given by the pedometer task

static uint32_t newPedVal = 0;

// steps

static uint16_t oldStepVal = 0;
static uint16_t newStepVal = 0;

// calories

static uint16_t oldCalVal = 0;
static uint16_t newCalVal = 0;

static task_handler_t gui_pedometer_step_counter_taskHandler;
static task_handler_t gui_pedometer_taskHandler;

static hostInterface_packet_t gui_pedometer_packet;

static bool isPedometerActive = false;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Gets data from the GUI queue.
static gui_pedometer_status_t gui_pedometer_QueueMsgGet( uint32_t timeout )
{
    osa_status_t status =
        OSA_MsgQGet( gui_pedometer_queueHnd, &newPedVal, timeout );

    if( status == kStatus_OSA_Error )
    {
        error_catch( CATCH_QUEUE );
        return GUI_PEDOMETER_STATUS_ERROR;
    }
    else
    {
        return GUI_PEDOMETER_STATUS_SUCCESS;
    }
}

// Updates pedometer GUI.
static void gui_pedometer_Update()
{
    newStepVal = ( uint16_t )( newPedVal );
    newCalVal  = ( uint16_t )( newPedVal >> 16 );

    if( ( newStepVal != oldStepVal ) && ( newStepVal != 0 ) )
    {
        sprintf( ( uint8_t* )gui_pedometer_stepCounter_label.caption, // 4,
            "%03u", newStepVal );
        GuiDriver_LabelDraw( &gui_pedometer_stepCounter_label );
    }

    if( ( newCalVal != oldCalVal ) && ( newCalVal != 0 ) )
    {
        sprintf( ( uint8_t* )gui_pedometer_calCounter_label.caption, // 4,
            "%03u", newCalVal );
        GuiDriver_LabelDraw( &gui_pedometer_calCounter_label );
    }
}

// Pedometer app GUI main task.
// Gets data from pedometer app and displays it.
static void gui_pedometer_Task( task_param_t param )
{
    while( 1 )
    {
        gui_status_t status =
            GuiDriver_QueueMsgGet( &gui_pedometer_packet , OSA_WAIT_FOREVER );

        if( status == GUI_STATUS_SUCCESS )
        {
            if( packetType_pressRight == gui_pedometer_packet.type )
            {
                if( isPedometerActive == false )
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
                    // pedometer_Resume();
                }
                else
                {
                    // pedometer_Pause();
                    vTaskSuspend( gui_pedometer_step_counter_taskHandler );

                    GuiDriver_CleanMainArea();
                    GuiDriver_ImageDraw( &gui_pedometer_icon );
                    GuiDriver_ImageDraw( &screen_buttonStart );

                    power_EnablePowerSave();
                    isPedometerActive = false;
                }

                haptic_Vibrate();
            }
        }
    }
}

// Monitors and updates GUI when step counter changes.
static void gui_pedometer_UpdateStepsTask( task_param_t param )
{
    while( 1 )
    {
        gui_pedometer_status_t guiStatus;
    
        // save the old values
        oldStepVal = newStepVal;
        oldCalVal  = newCalVal;

        // wait for the new one
        guiStatus = gui_pedometer_QueueMsgGet( OSA_WAIT_FOREVER );

        if( guiStatus != GUI_PEDOMETER_STATUS_SUCCESS )
        {
            error_catch( CATCH_HEALTH );
        }
        else
        {
            gui_pedometer_Update();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises pedometer app GUI.
void gui_pedometer_Init( void* param )
{
    // create pedometer packet queue
    gui_pedometer_queueHnd = OSA_MsgQCreate( gui_pedometer_queue,
        1, sizeof( uint32_t ) / sizeof( uint32_t ) );
#if defined( HEXIWEAR_DEBUG )
    vQueueAddToRegistry(
        gui_pedometer_queueHnd, ( uint8_t* )"GUI Pedometer Queue" );
#endif

    GuiDriver_ImageAddToScr( &screen_buttonStart );

    GuiDriver_LabelCreate( &gui_pedometer_stepCounter_label );
    // 4 characters max
    sprintf( ( uint8_t* )gui_pedometer_stepCounter_label.caption,
        "%03u", 000 );

    GuiDriver_LabelCreate( &gui_pedometer_stepText_label );
    GuiDriver_LabelSetCaption(
        &gui_pedometer_stepText_label, ( uint8_t* )"steps" );

    GuiDriver_LabelCreate( &gui_pedometer_calCounter_label );
    // 4 characters max
    sprintf( ( uint8_t* )gui_pedometer_calCounter_label.caption,
        "%03u", 000 );

    GuiDriver_LabelCreate( &gui_pedometer_calText_label );
    GuiDriver_LabelSetCaption(
        &gui_pedometer_calText_label, ( uint8_t* )"Cal" );

    GuiDriver_ImageAddToScr( &gui_pedometer_icon );

    // listen if the user wants to use the pedometer
    // GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );

    // initiate the pedometer process structures
    oldStepVal = newStepVal = 0;
    // pedometer_Init();

    GuiDriver_NotifyKW40( GUI_CURRENT_APP_PEDOMETER );
}

// Creates the pedometer GUI app tasks.
void gui_pedometer_CreateTasks( void* param )
{
    osa_status_t taskStatus = kStatus_OSA_Success;

    // pedometer_CreateTask();

//    taskStatus = OSA_TaskCreate(
//                                 gui_pedometer_Task,
//                                 ( uint8_t* )"pedometer window",
//                                 GUI_PEDOMETER_STACK_SIZE,
//                                 NULL,
//                                 GUI_PEDOMETER_PRIO,
//                                 ( task_param_t )0,
//                                 false,
//                                 &gui_pedometer_taskHandler
//                               );

//    taskStatus |= OSA_TaskCreate(
//                                  gui_pedometer_UpdateStepsTask,
//                                  ( uint8_t* )"pedometer step counter",
//                                  GUI_PEDOMETER_STEP_COUNTER_STACK_SIZE,
//                                  NULL,
//                                  GUI_PEDOMETER_STEP_COUNTER_PRIO,
//                                  ( task_param_t )0,
//                                  false,
//                                  &gui_pedometer_step_counter_taskHandler
//                                );

    if( taskStatus != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
//    vTaskSuspend( gui_pedometer_step_counter_taskHandler );
}

// Destroys the pedometer GUI app tasks.
void gui_pedometer_DestroyTasks( void* param )
{
//    OSA_TaskDestroy( gui_pedometer_taskHandler );
//    OSA_TaskDestroy( gui_pedometer_step_counter_taskHandler );
    OSA_MsgQDestroy( gui_pedometer_queueHnd );

    // pedometer_Deinit();

    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_pedometer_stepCounter_label );
    GuiDriver_LabelDestroy( &gui_pedometer_stepText_label );

    GuiDriver_LabelDestroy( &gui_pedometer_calCounter_label );
    GuiDriver_LabelDestroy( &gui_pedometer_calText_label );

    // GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );

    isPedometerActive = false;

    power_EnablePowerSave();

    if( gui_sensorTag_IsActive() == false  )
    {
        GuiDriver_NotifyKW40( GUI_CURRENT_APP_IDLE );
    }
}

// Puts the packet into pedometer app GUI queue.
gui_pedometer_status_t gui_pedometer_QueueMsgPut( uint32_t* packet )
{
    BaseType_t status = xQueueSendToBack(
        gui_pedometer_queueHnd, ( uint32_t* )packet, OSA_WAIT_FOREVER );

    if( status == pdPASS )
    {
        return GUI_PEDOMETER_STATUS_SUCCESS;
    }
    else
    {
        error_catch( CATCH_QUEUE );
        return GUI_PEDOMETER_STATUS_ERROR;
    }
}