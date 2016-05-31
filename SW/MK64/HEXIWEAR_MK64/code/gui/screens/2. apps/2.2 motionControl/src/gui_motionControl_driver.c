/**
 * \file gui_motionControl_driver.c
 * \version 1.00
 * \brief this file contains motion control app functionality
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

#include "fsl_os_abstraction.h"

#include "gui_sensorTag.h"
#include "gui_motionControl.h"
#include "gui_motionControl_private.h"

#include "HEXIWEAR_driver.h"


/** private typedefs */

typedef enum
{
    active_acc,
    active_gyro

} activeScreen_t;

/** private variables */

static activeScreen_t
    activeScreen = active_acc;

static task_handler_t
    gui_motionControl_taskHandler;

static hostInterface_packet_t
        gui_motionControl_packet;

static packet_pushTarget_t
    appBackupList[PACKET_ALL];

static packet_pushTarget_t
    appPushTarget = PACKET_PUSH_OLED;

/** private declarations */

static void gui_motionControl_AppTask();

/** public API */

/**
 * initialize the motion control app
 * @param param optional parameter
 */
void gui_motionControl_Init( void* param )
{
    GuiDriver_LabelCreate( &gui_motionControl_labelX );
    GuiDriver_LabelCreate( &gui_motionControl_labelY );
    GuiDriver_LabelCreate( &gui_motionControl_labelZ );

    if ( &gui_motionControl_accScreen == guiDriver_display.guiItem )
    {
        activeScreen = active_acc;
    }
    else if ( &gui_motionControl_gyroScreen == guiDriver_display.guiItem )
    {
        activeScreen = active_gyro;
    }

	if ( false == gui_sensorTag_IsActive() )
	{
		GuiDriver_RegisterMinPollDelay( 100 );

        if ( active_acc == activeScreen )
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
        if ( active_acc == activeScreen )
        {
		  GuiDriver_RegisterForSensors( PACKET_ACC, -1, true );
        }
        else
        {
          GuiDriver_RegisterForSensors( PACKET_GYRO, -1, true );
        }
	}


    HEXIWEAR_SetBackupList( (packet_pushTarget_t*)appBackupList );
    HEXIWEAR_SetTargetApp ( appPushTarget );
}

/**
 * create the app main task
 * @param param optional parameter
 */
void gui_motionControl_CreateTasks( void* param )
{
    osa_status_t
        taskStatus = OSA_TaskCreate(
                                        gui_motionControl_AppTask,
                                        (uint8_t*) "motion control app",
                                        GUI_MOTION_CONTROL_STACK_SIZE,
                                        NULL,
                                        GUI_MOTION_CONTROL_PRIO,
                                        (task_param_t)0,
                                        false,
                                        &gui_motionControl_taskHandler
                                    );

    if ( kStatus_OSA_Success != taskStatus )
    {
        catch( CATCH_INIT );
    }
}

/**
 * destroy the app task
 * @param param optional parameter
 */
void gui_motionControl_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_motionControl_taskHandler );

    if ( active_acc == activeScreen )
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
    HEXIWEAR_SetTargetApp ( PACKET_PUSH_NONE );
}

/** private API */

/**
 * motion control main task, charged with
 * getting data from sensors and displaying them
 */
static void gui_motionControl_AppTask()
{
    while (1)
    {
        gui_status_t
            clickStatus = GuiDriver_QueueMsgGet( &gui_motionControl_packet , OSA_WAIT_FOREVER );

        if( GUI_STATUS_SUCCESS == clickStatus )
        {
        	switch ( gui_motionControl_packet.type )
        	{
        	    case packetType_accel:
        	    {
        	        mE_t
        	            sensorValue = (mE_t)( gui_motionControl_packet.data[0] | (mE_t)gui_motionControl_packet.data[1] << 8 );

        	        if ( sensorValue >= 0 )
        	        {
        	            snprintf( (char*)gui_motionControl_labelX.caption, 5, "%i.%02i", sensorValue / 100, sensorValue % 100 );
        	        }
        	        else
        	        {
        	            snprintf( (char*)gui_motionControl_labelX.caption, 5, "-%i.%02i", abs(sensorValue / 100), abs(sensorValue % 100) );
        	        }

        	        sensorValue = (mE_t)( gui_motionControl_packet.data[2] | (mE_t)gui_motionControl_packet.data[3] << 8 );

        	        if ( sensorValue >= 0 )
        	        {
        	            snprintf( (char*)gui_motionControl_labelY.caption, 5, "%i.%02i", sensorValue / 100, sensorValue % 100 );
        	        }
        	        else
        	        {
        	            snprintf( (char*)gui_motionControl_labelY.caption, 5, "-%i.%02i", abs(sensorValue / 100), abs(sensorValue % 100) );
        	        }

        	        sensorValue = (mE_t)( gui_motionControl_packet.data[4] | (mE_t)gui_motionControl_packet.data[5] << 8 );

        	        if ( sensorValue >= 0 )
        	        {
        	            snprintf( (char*)gui_motionControl_labelZ.caption, 5, "%i.%02i", sensorValue / 100, sensorValue % 100 );
        	        }
        	        else
        	        {
        	            snprintf( (char*)gui_motionControl_labelZ.caption, 5, "-%i.%02i", abs(sensorValue / 100), abs(sensorValue % 100) );
        	        }
        	        break;
        	    }

        	    case packetType_gyro:
        	    {
        	        mE_t
        	            sensorValue = (mE_t)( gui_motionControl_packet.data[0] | (mE_t)gui_motionControl_packet.data[1] << 8 );
					snprintf( (char*)gui_motionControl_labelX.caption, 5, "%i", sensorValue );

        	        sensorValue = (mE_t)( gui_motionControl_packet.data[2] | (mE_t)gui_motionControl_packet.data[3] << 8 );
        	        snprintf( (char*)gui_motionControl_labelY.caption, 5, "%i", sensorValue );

        	        sensorValue = (mE_t)( gui_motionControl_packet.data[4] | (mE_t)gui_motionControl_packet.data[5] << 8 );
        	        snprintf( (char*)gui_motionControl_labelZ.caption, 5, "%i", sensorValue );
        	    }

        	    default: {}
        	}

            GuiDriver_LabelDraw( &gui_motionControl_labelX );
            GuiDriver_LabelDraw( &gui_motionControl_labelY );
            GuiDriver_LabelDraw( &gui_motionControl_labelZ );
        }
    }
}
