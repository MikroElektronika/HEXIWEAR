// File: gui_weatherStation_driver.c

// Definitions of main functionalities in the weather station gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "sensorTag/gui_sensorTag.h"
#include "apps/weatherStation/gui_weatherStation.h"
#include "apps/weatherStation/gui_weatherStation_private.h"

#include "HEXIWEAR_driver.h"

#include "OSA.h"

#include "error.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static task_handler_t gui_weatherStation_taskHandler;

static hostInterface_packet_t gui_weatherStation_packet;

static packet_pushTarget_t gui_weatherStation_currentBackupList[PACKET_ALL];

static packet_pushTarget_t gui_weatherStation_currentApp;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// GUI weather station task.
static void gui_weatherStation_AppTask( task_param_t param )
{
    gui_status_t clickStatus;
    mE_t sensorValue;

    while( 1 )
    {
        clickStatus = GuiDriver_QueueMsgGet(
            &gui_weatherStation_packet , OSA_WAIT_FOREVER );

        if( clickStatus == GUI_STATUS_SUCCESS )
        {
            if( ( packetType_temperature != gui_weatherStation_packet.type ) &&
                ( packetType_humidity    != gui_weatherStation_packet.type ) &&
                ( packetType_pressure    != gui_weatherStation_packet.type ) )
            {
                continue;
            }

            sensorValue = ( mE_t )( gui_weatherStation_packet._data[0] |
                ( mE_t )gui_weatherStation_packet._data[1] << 8 );

            switch( gui_weatherStation_packet.type )
            {
                case packetType_temperature:
                {
                    // 10 characters max
                    sprintf( ( uint8_t* )gui_weatherStation_labelTemp.caption,
                        "%2i.%02i C", sensorValue / 100, sensorValue % 100 );
                    GuiDriver_LabelDraw( &gui_weatherStation_labelTemp );
                    break;
                }

                case packetType_humidity:
                {
                    // 10 characters max
                    sprintf( ( uint8_t* )gui_weatherStation_labelHum.caption,
                        "%2i.%02i %%", sensorValue / 100, sensorValue % 100 );
                    GuiDriver_LabelDraw( &gui_weatherStation_labelHum );
                    break;
                }

                case packetType_pressure:
                {
                     // 20 characters max
                    sprintf( ( uint8_t* )gui_weatherStation_labelPress.caption,
                        "%3i.%02i kPa", sensorValue / 100, sensorValue % 100 );
                    GuiDriver_LabelDraw( &gui_weatherStation_labelPress );
                    break;
                }

                default: {}
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the weather station task.
void gui_weatherStation_Init( void* param )
{
    GuiDriver_LabelCreate( &gui_weatherStation_labelTemp );
    GuiDriver_LabelCreate( &gui_weatherStation_labelHum );
    GuiDriver_LabelCreate( &gui_weatherStation_labelPress );

    if( gui_sensorTag_IsActive() == false )
    {
        GuiDriver_RegisterMinPollDelay( 100 );
        GuiDriver_RegisterForSensors( PACKET_TEMP, 1e3, false );
        GuiDriver_RegisterForSensors( PACKET_PRES, 1e3, false );
        GuiDriver_RegisterForSensors( PACKET_HUM,  1e3, true );
    }
    else
    {
        GuiDriver_RegisterForSensors( PACKET_TEMP, 1e3, false ); // -1
        GuiDriver_RegisterForSensors( PACKET_PRES, 1e3, false ); // -1
        GuiDriver_RegisterForSensors( PACKET_HUM,  1e3, true ); // -1
    }

    HEXIWEAR_SetBackupList(
        ( packet_pushTarget_t* )gui_weatherStation_currentBackupList );
    HEXIWEAR_SetTargetApp( gui_weatherStation_currentApp );
}

// Creates tasks for the weather station app.
void gui_weatherStation_CreateTasks( void* param )
{
    osa_status_t taskStatus =
        OSA_TaskCreate(
                        gui_weatherStation_AppTask,
                        ( uint8_t* )"weather station app",
                        GUI_WEATHER_STATION_STACK_SIZE,
                        NULL,
                        GUI_WEATHER_STATION_PRIO,
                        ( task_param_t )0,
                        false,
                        &gui_weatherStation_taskHandler
                      );

    if( taskStatus != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys tasks in the weather station app.
void gui_weatherStation_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_weatherStation_taskHandler );

    GuiDriver_UnregisterFromSensors( PACKET_TEMP, true );
    GuiDriver_UnregisterFromSensors( PACKET_PRES, true );
    GuiDriver_UnregisterFromSensors( PACKET_HUM,  true );

    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_weatherStation_labelTemp );
    GuiDriver_LabelDestroy( &gui_weatherStation_labelHum );
    GuiDriver_LabelDestroy( &gui_weatherStation_labelPress );

    HEXIWEAR_SetBackupList( NULL );
    HEXIWEAR_SetTargetApp( PACKET_PUSH_NONE );
}