/**
 * Weather station app
 * Project HEXIWEAR, 2015
 */

#include "gui_sensorTag.h"
#include "gui_weatherStation.h"
#include "gui_weatherStation_private.h"

#include "HEXIWEAR_driver.h"

#include "fsl_os_abstraction.h"

/**
 * private variables
 */

static task_handler_t
    gui_weatherStation_taskHandler;

static hostInterface_packet_t
        gui_weatherStation_packet;

static packet_pushTarget_t
    gui_weatherStation_currentBackupList[PACKET_ALL];

static packet_pushTarget_t
    gui_weatherStation_currentApp;

/**
 * private declarations
 */

static void gui_weatherStation_AppTask();

/**
 * public API
 */

/**
 * [gui_weatherStation_Init description]
 * @param param [description]
 */
void gui_weatherStation_Init( void* param )
{
    GuiDriver_LabelCreate( &gui_weatherStation_labelTemp );
    GuiDriver_LabelCreate( &gui_weatherStation_labelHum );
    GuiDriver_LabelCreate( &gui_weatherStation_labelPress );

    if ( false == gui_sensorTag_IsActive() )
    {
		GuiDriver_RegisterMinPollDelay( 100 );
//		sensor_SetPushTargets( PACKET_TEMP, sensor_GetPushTargets( PACKET_TEMP ) | PACKET_PUSH_KW40, false );
		GuiDriver_RegisterForSensors( PACKET_TEMP, 1e3, false );
//		sensor_SetPushTargets( PACKET_PRES, sensor_GetPushTargets( PACKET_PRES ) | PACKET_PUSH_KW40, false );
		GuiDriver_RegisterForSensors( PACKET_PRES, 1e3, false );
//		sensor_SetPushTargets( PACKET_HUM, sensor_GetPushTargets( PACKET_HUM ) | PACKET_PUSH_KW40, false );
		GuiDriver_RegisterForSensors( PACKET_HUM,  1e3, true );
    }
	else
	{
		GuiDriver_RegisterForSensors( PACKET_TEMP, -1, false );
		GuiDriver_RegisterForSensors( PACKET_PRES, -1, false );
		GuiDriver_RegisterForSensors( PACKET_HUM,  -1, true );
	}


    HEXIWEAR_SetBackupList( (packet_pushTarget_t*)gui_weatherStation_currentBackupList );
    HEXIWEAR_SetTargetApp ( gui_weatherStation_currentApp );
//    GuiDriver_NotifyKW40( GUI_CURRENT_APP_WEATHER_STATION );
}

/**
 * [gui_weatherStation_CreateTasks description]
 * @param param [description]
 */
void gui_weatherStation_CreateTasks( void* param )
{
    osa_status_t
        taskStatus = OSA_TaskCreate(
                                        gui_weatherStation_AppTask,
                                        (uint8_t*) "weather station app",
                                        GUI_WEATHER_STATION_STACK_SIZE,
                                        NULL,
                                        GUI_WEATHER_STATION_PRIO,
                                        (task_param_t)0,
                                        false,
                                        &gui_weatherStation_taskHandler
                                    );

    if ( kStatus_OSA_Success != taskStatus )
    {
        catch( CATCH_INIT );
    }
}

/**
 * [gui_weatherStation_DestroyTasks description]
 * @param param [description]
 */
void gui_weatherStation_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_weatherStation_taskHandler );

//    if ( false == gui_sensorTag_IsActive() )
//    {
//        sensor_SetPushTargets( PACKET_PRES, sensor_GetPushTargets( PACKET_PRES ) & ~PACKET_PUSH_KW40, false );
//        sensor_SetPushTargets( PACKET_TEMP, sensor_GetPushTargets( PACKET_TEMP ) & ~PACKET_PUSH_KW40, false );
//        sensor_SetPushTargets( PACKET_HUM,  sensor_GetPushTargets( PACKET_HUM )  & ~PACKET_PUSH_KW40, false );
//    }

    GuiDriver_UnregisterFromSensors( PACKET_PRES, false );
    GuiDriver_UnregisterFromSensors( PACKET_TEMP, false );
    GuiDriver_UnregisterFromSensors( PACKET_HUM,  true );

    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_weatherStation_labelTemp );
    GuiDriver_LabelDestroy( &gui_weatherStation_labelHum );
    GuiDriver_LabelDestroy( &gui_weatherStation_labelPress );

    HEXIWEAR_SetBackupList( NULL );
    HEXIWEAR_SetTargetApp ( PACKET_PUSH_NONE );
}

/**
 * private functions
 */

/**
 * [gui_weatherStation_AppTask description]
 */
static void gui_weatherStation_AppTask()
{
    while (1)
    {
        gui_status_t
            clickStatus = GuiDriver_QueueMsgGet( &gui_weatherStation_packet , OSA_WAIT_FOREVER );

        if( GUI_STATUS_SUCCESS == clickStatus )
        {
            if(
                    ( packetType_temperature != gui_weatherStation_packet.type )
               &&   ( packetType_humidity    != gui_weatherStation_packet.type )
               &&   ( packetType_pressure    != gui_weatherStation_packet.type )
              )
            {
                continue;
            }

            mE_t
            	sensorValue = (mE_t)( gui_weatherStation_packet.data[0] | (mE_t)gui_weatherStation_packet.data[1] << 8 );

            switch( gui_weatherStation_packet.type )
            {
                case packetType_temperature:
                {
                    snprintf( (char*)gui_weatherStation_labelTemp.caption, 10, "%2i.%02i C", sensorValue / 100, sensorValue % 100 );
                    GuiDriver_LabelDraw(&gui_weatherStation_labelTemp);
                    break;
                }

                case packetType_humidity:
                {
                    snprintf( (char*)gui_weatherStation_labelHum.caption, 10, "%2i.%02i %%", sensorValue / 100, sensorValue % 100 );
                    GuiDriver_LabelDraw(&gui_weatherStation_labelHum);
                    break;
                }

                case packetType_pressure:
                {
                    snprintf( (char*)gui_weatherStation_labelPress.caption, 20, "%3i.%02i kPa", sensorValue / 100, sensorValue % 100 );
                    GuiDriver_LabelDraw(&gui_weatherStation_labelPress);
                    break;
                }

                default: {}
            }
        }
    }
}
