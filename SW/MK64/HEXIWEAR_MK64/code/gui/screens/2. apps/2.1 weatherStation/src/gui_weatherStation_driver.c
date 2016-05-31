/**
 * \file gui_weatherStation_driver.c
 * \version 1.00
 * \brief this file contains weather station app functionality
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

#include "gui_sensorTag.h"
#include "gui_weatherStation.h"
#include "gui_weatherStation_private.h"

#include "HEXIWEAR_driver.h"

#include "fsl_os_abstraction.h"

/** private variables */

static task_handler_t
    gui_weatherStation_taskHandler;

static hostInterface_packet_t
        gui_weatherStation_packet;

static packet_pushTarget_t
    gui_weatherStation_currentBackupList[PACKET_ALL];

static packet_pushTarget_t
    gui_weatherStation_currentApp;

/** private declarations */

static void gui_weatherStation_AppTask();

/** public API */

/**
 * initialize the weather station task
 * @param param optional parameter
 */
void gui_weatherStation_Init( void* param )
{
    GuiDriver_LabelCreate( &gui_weatherStation_labelTemp );
    GuiDriver_LabelCreate( &gui_weatherStation_labelHum );
    GuiDriver_LabelCreate( &gui_weatherStation_labelPress );

    if ( false == gui_sensorTag_IsActive() )
    {
		GuiDriver_RegisterMinPollDelay( 100 );
		GuiDriver_RegisterForSensors( PACKET_TEMP, 1e3, false );
		GuiDriver_RegisterForSensors( PACKET_PRES, 1e3, false );
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
}

/**
 * create tasks for the weather station app
 * @param param optional parameter
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
 * destroy tasks in the weather station app
 * @param param optional parameter
 */
void gui_weatherStation_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_weatherStation_taskHandler );

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

/** private API */

/**
 * GUI weather station task
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
