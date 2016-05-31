/**
 * Weather station app
 * Project HEXIWEAR, 2015
 */

#include "fsl_os_abstraction.h"

#include "gui_sensorTag.h"
#include "gui_motionControl.h"
#include "gui_motionControl_private.h"

#include "HEXIWEAR_driver.h"


/**
 * private typedefs
 */

typedef enum
{
    active_acc,
    active_gyro

} activeScreen_t;

/**
 * private variables
 */

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

/**
 * private declarations
 */

static void gui_motionControl_AppTask();

/**
 * public API
 */

/**
 * [gui_motionControl_Init description]
 * @param param [description]
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
//          sensor_SetPushTargets( PACKET_ACC, sensor_GetPushTargets( PACKET_ACC ) | PACKET_PUSH_KW40, false );
          GuiDriver_RegisterForSensors( PACKET_ACC, 100, true );
        }
        else
        {
//		  sensor_SetPushTargets( PACKET_GYRO, sensor_GetPushTargets( PACKET_GYRO ) | PACKET_PUSH_KW40, false );
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
//    GuiDriver_NotifyKW40( GUI_CURRENT_APP_MOTION_CONTROL_ACC );
}

/**
 * [gui_motionControl_CreateTasks description]
 * @param param [description]
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
 * [gui_motionControl_DestroyTasks description]
 * @param param [description]
 */
void gui_motionControl_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_motionControl_taskHandler );

    if ( active_acc == activeScreen )
    {
//	  if ( false == gui_sensorTag_IsActive() )
//	  {
//		  sensor_SetPushTargets( PACKET_ACC, sensor_GetPushTargets( PACKET_ACC ) & ~PACKET_PUSH_KW40, false );
//	  }
      GuiDriver_UnregisterFromSensors( PACKET_ACC, true );
    }

    else
    {
//	  if ( false == gui_sensorTag_IsActive() )
//	  {
//		  sensor_SetPushTargets( PACKET_GYRO, sensor_GetPushTargets( PACKET_GYRO ) & ~PACKET_PUSH_KW40, false );
//	  }
      GuiDriver_UnregisterFromSensors( PACKET_GYRO, true );
    }

    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_motionControl_labelX );
    GuiDriver_LabelDestroy( &gui_motionControl_labelY );
    GuiDriver_LabelDestroy( &gui_motionControl_labelZ );

    HEXIWEAR_SetBackupList( NULL );
    HEXIWEAR_SetTargetApp ( PACKET_PUSH_NONE );
}

/**
 * private functions
 */

//static uint8_t
//	appRefreshRate = 1;

/**
 * [gui_motionControl_AppTask description]
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
