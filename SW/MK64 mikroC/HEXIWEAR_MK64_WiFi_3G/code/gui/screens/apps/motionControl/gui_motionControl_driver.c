// File: gui_motionControl_driver.c

// Definitions of main functionalities in the motion control gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "OSA.h"
#include "error.h"

#include "sensorTag/gui_sensorTag.h"
#include "apps/motionControl/gui_motionControl.h"
#include "apps/motionControl/gui_motionControl_private.h"

#include "HEXIWEAR_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////
 
typedef enum
{
    active_acc,
    active_gyro

} activeScreen_t;

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static activeScreen_t activeScreen = active_acc;

static task_handler_t gui_motionControl_taskHandler;

static hostInterface_packet_t gui_motionControl_packet;

static packet_pushTarget_t appBackupList[PACKET_ALL];

static packet_pushTarget_t appPushTarget = PACKET_PUSH_OLED;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Motion control main task,
// charged with getting data from sensors and displaying them.
static void gui_motionControl_AppTask( task_param_t param )
{
    while( 1 )
    {
        gui_status_t clickStatus = GuiDriver_QueueMsgGet(
            &gui_motionControl_packet , OSA_WAIT_FOREVER );

        if( clickStatus == GUI_STATUS_SUCCESS )
        {
            switch( gui_motionControl_packet.type )
            {
                case packetType_accel:
                {
                    mE_t sensorValue;
                    
                    sensorValue = ( mE_t )( gui_motionControl_packet._data[0] |
                        ( mE_t )gui_motionControl_packet._data[1] << 8 );

                    if( sensorValue >= 0 )
                    {
                        // 5 characters max
                        sprintf( ( uint8_t* )gui_motionControl_labelX.caption,
                            "%i.%02i", sensorValue / 100, sensorValue % 100 );
                    }
                    else
                    {
                        // 5 characters max
                        sprintf( ( uint8_t* )gui_motionControl_labelX.caption,
                            "-%i.%02i", abs( sensorValue / 100 ),
                            abs( sensorValue % 100 ) );
                    }

                    sensorValue = ( mE_t )( gui_motionControl_packet._data[2] |
                        ( mE_t )gui_motionControl_packet._data[3] << 8 );

                    if( sensorValue >= 0 )
                    {
                        // 5 characters max
                        sprintf( ( uint8_t* )gui_motionControl_labelY.caption,
                            "%i.%02i", sensorValue / 100, sensorValue % 100 );
                    }
                    else
                    {
                        // 5 characters max
                        sprintf( ( uint8_t* )gui_motionControl_labelY.caption,
                            "-%i.%02i", abs( sensorValue / 100 ),
                            abs( sensorValue % 100 ) );
                    }

                    sensorValue = ( mE_t )( gui_motionControl_packet._data[4] |
                        ( mE_t )gui_motionControl_packet._data[5] << 8 );

                    if( sensorValue >= 0 )
                    {
                        // 5 characters max
                        sprintf( ( uint8_t* )gui_motionControl_labelZ.caption,
                            "%i.%02i", sensorValue / 100, sensorValue % 100 );
                    }
                    else
                    {
                        // 5 characters max
                        sprintf( ( uint8_t* )gui_motionControl_labelZ.caption,
                            "-%i.%02i", abs( sensorValue / 100 ),
                            abs( sensorValue % 100 ) );
                    }
                    break;
                } // case packetType_accel:

                case packetType_gyro:
                {
                    mE_t sensorValue;
                    
                    sensorValue = ( mE_t )( gui_motionControl_packet._data[0] |
                        ( mE_t )gui_motionControl_packet._data[1] << 8 );
                    // 5 characters max
                    sprintf( ( uint8_t* )gui_motionControl_labelX.caption,
                        "%i", sensorValue );

                    sensorValue = ( mE_t )( gui_motionControl_packet._data[2] |
                        ( mE_t )gui_motionControl_packet._data[3] << 8 );
                    // 5 characters max
                    sprintf( ( uint8_t* )gui_motionControl_labelY.caption,
                        "%i", sensorValue );

                    sensorValue = ( mE_t )( gui_motionControl_packet._data[4] |
                        ( mE_t )gui_motionControl_packet._data[5] << 8 );
                    // 5 characters max
                    sprintf( ( uint8_t* )gui_motionControl_labelZ.caption,
                        "%i", sensorValue );
                }

                default: {}
            }

            GuiDriver_LabelDraw( &gui_motionControl_labelX );
            GuiDriver_LabelDraw( &gui_motionControl_labelY );
            GuiDriver_LabelDraw( &gui_motionControl_labelZ );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the motion control app.
void gui_motionControl_Init( void* param )
{
    GuiDriver_LabelCreate( &gui_motionControl_labelX );
    GuiDriver_LabelCreate( &gui_motionControl_labelY );
    GuiDriver_LabelCreate( &gui_motionControl_labelZ );

    if( guiDriver_display.guiItem == &gui_motionControl_accScreen )
    {
        activeScreen = active_acc;
    }
    else if( guiDriver_display.guiItem == &gui_motionControl_gyroScreen )
    {
        activeScreen = active_gyro;
    }

    if( gui_sensorTag_IsActive() == false )
    {
        GuiDriver_RegisterMinPollDelay( 100 );

        if( activeScreen == active_acc )
        {
            GuiDriver_RegisterForSensors( PACKET_ACC, 100, true );
        }
        else
        {
            GuiDriver_RegisterForSensors( PACKET_GYRO, 100, true );
        }
    }
    else
    {
        if( activeScreen == active_acc )
        {
            GuiDriver_RegisterForSensors( PACKET_ACC, 100, true ); // -1
        }
        else
        {
            GuiDriver_RegisterForSensors( PACKET_GYRO, 100, true ); // -1
        }
    }

    HEXIWEAR_SetBackupList( ( packet_pushTarget_t* )appBackupList );
    HEXIWEAR_SetTargetApp ( appPushTarget );
}

// Creates the app main task.
void gui_motionControl_CreateTasks( void* param )
{
    osa_status_t taskStatus = OSA_TaskCreate(
                                              gui_motionControl_AppTask,
                                              ( uint8_t* )"motion control app",
                                              GUI_MOTION_CONTROL_STACK_SIZE,
                                              NULL,
                                              GUI_MOTION_CONTROL_PRIO,
                                              ( task_param_t )0,
                                              false,
                                              &gui_motionControl_taskHandler
                                            );

    if( kStatus_OSA_Success != taskStatus )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys the app task.
void gui_motionControl_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_motionControl_taskHandler );

    if( activeScreen == active_acc )
    {
        GuiDriver_UnregisterFromSensors( PACKET_ACC, true );
    }
    else
    {
        GuiDriver_UnregisterFromSensors( PACKET_GYRO, true );
    }

    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_motionControl_labelX );
    GuiDriver_LabelDestroy( &gui_motionControl_labelY );
    GuiDriver_LabelDestroy( &gui_motionControl_labelZ );

    HEXIWEAR_SetBackupList( NULL );
    HEXIWEAR_SetTargetApp( PACKET_PUSH_NONE );
}