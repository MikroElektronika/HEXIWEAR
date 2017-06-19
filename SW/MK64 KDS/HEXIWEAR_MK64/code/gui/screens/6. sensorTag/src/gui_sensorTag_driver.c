/**
 * \file gui_sensorTag_driver.c
 * \version 1.00
 * \brief this file contains Sensor Tag mode implementation
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

#include "gui_sensorTag_private.h"
#include "gui_sensorTag.h"

#include "watch.h"

#include "screens_common.h"

MSG_QUEUE_DECLARE( gui_sensorTag_queue, 1, sizeof(uint32_t) );

/** private functions declarations */

static void gui_sensorTag_Register();
static void gui_sensorTag_Unregister();

/** private variables */

static bool
    isSensorTagActive = false;

static task_handler_t
    gui_sensorTag_taskHandler;

static msg_queue_handler_t
    gui_sensorTag_queueHnd;

static hostInterface_packet_t
        gui_sensorTag_packet;

/** private functions */

static void gui_sensorTag_ToggleTask( task_param_t param );

/** public API */

/**
 * initialize sensor tag mode structures and tasks
 * @param param optional parameter
 */
void gui_sensorTag_Init( void* param )
{
    // create pedometer packet queue
    gui_sensorTag_queueHnd = OSA_MsgQCreate (
                                                gui_sensorTag_queue,
                                                1,
                                                sizeof(uint32_t) / sizeof(uint32_t)
                                            );
#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( gui_sensorTag_queueHnd, (char*)"SensorTag Queue" );
#endif

    GuiDriver_ImageAddToScr( &gui_sensorTag_icon );

    screen_labelEnter.textProperties.fontColor = GUI_COLOR_WHITE;
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );

    GuiDriver_LabelAddToScr(&screen_labelEnter);
}

/**
 * create sensor tag mode task
 * @param param optional parameter
 */
void gui_sensorTag_CreateTasks( void* param )
{
    osa_status_t
        taskStatus = OSA_TaskCreate(
                                        gui_sensorTag_ToggleTask,
                                        (uint8_t*) "sensor tag process",
                                        GUI_SENSOR_TAG_STACK_SIZE,
                                        NULL,
                                        GUI_SENSOR_TAG_PRIO,
                                        (task_param_t)0,
                                        false,
                                        &gui_sensorTag_taskHandler
                                    );

    if ( kStatus_OSA_Success != taskStatus )
    {
        catch( CATCH_INIT );
    }
}

/**
 * destroy sensor tag mode task
 * @param param optional parameter
 */
void gui_sensorTag_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_sensorTag_taskHandler );
    OSA_MsgQDestroy( gui_sensorTag_queueHnd );
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
    OLED_DestroyDynamicArea();
}

/**
 * sensor tag mode task charged with toggling the sensor tag mode
 * @param param optional  parameter
 */
static void gui_sensorTag_ToggleTask( task_param_t param )
{
    while (1)
    {
        gui_status_t
            clickStatus = GuiDriver_QueueMsgGet( &gui_sensorTag_packet , OSA_WAIT_FOREVER );

        if( GUI_STATUS_SUCCESS == clickStatus )
        {
            if ( packetType_pressRight == gui_sensorTag_packet.type )
            {
    	    	/** load the current state in flash */
    	    	hexiwear_flags_t
    	    		hexiwear_stateFlags = {0};
    	    	memcpy( (void*)&hexiwear_stateFlags, (const void*)HEXIWEAR_FLAGS, sizeof( hexiwear_stateFlags ) );


                if ( false == isSensorTagActive )
                {
                    gui_sensorTag_icon.img = gui_sensorTag_on_bmp;
                    GuiDriver_ImageDraw( &gui_sensorTag_icon );

                    gui_sensorTag_TurnON();
                    hexiwear_stateFlags.isON_SensorTag = 1;
                }

                else
                {
                	hexiwear_stateFlags.isON_SensorTag = 0;
                    gui_sensorTag_TurnOFF();

                    gui_sensorTag_icon.img = gui_sensorTag_off_bmp;
                    GuiDriver_ImageDraw( &gui_sensorTag_icon );
                }

                HEXIWEAR_SetFlags( (uint32_t)HEXIWEAR_STATE_FLAGS_ADDRESS, (void*)&hexiwear_stateFlags, sizeof(hexiwear_stateFlags) );
                haptic_Vibrate();
            }
        }
    }
}

/**
 * return task state
 */
bool gui_sensorTag_IsActive()
{
	return isSensorTagActive;
}

/**
 * register for all the packets
 */
static void gui_sensorTag_Register()
{
	sensor_SetMinimumDelay( 0 );
    for ( packet_t pktIdx = PACKET_ACC; pktIdx < PACKET_HR; pktIdx++ )
    {
    	sensor_RegisterPacketDelay( pktIdx, 0 );
    	sensor_SetPacketTargets( pktIdx, sensor_GetPacketTargets( pktIdx ) | PACKET_PUSH_KW40, false );
    }
    sensor_RegisterPacketDelay( PACKET_BAT, 0 );
	sensor_SetPacketTargets( PACKET_BAT, sensor_GetPacketTargets( PACKET_BAT ) | PACKET_PUSH_KW40, true );
}

/**
 * unregister from all the packets
 */
static void gui_sensorTag_Unregister()
{
    for ( packet_t pktIdx = PACKET_ACC; pktIdx < PACKET_HR; pktIdx++ )
    {
	  sensor_SetPacketTargets( pktIdx, sensor_GetPacketTargets( pktIdx ) & ~PACKET_PUSH_KW40, false );
    }
    sensor_SetPacketTargets( PACKET_BAT, sensor_GetPacketTargets( PACKET_BAT ) & ~PACKET_PUSH_KW40, true );
    sensor_ResetTargetsForKW40();
}

/**
 * turn on sensor tag
 */
void gui_sensorTag_TurnON()
{
	// notify KW40
	GuiDriver_NotifyKW40( GUI_CURRENT_APP_SENSOR_TAG );

    // register all the sensors
    gui_sensorTag_Register();
    isSensorTagActive = true;

	/**
     * check for the bluetooth connection,
     * to determine sleep mode
     */

    watch_LinkStateUpdate( watch_CurrentLinkStateGet() );
}

/**
 * turn off sensor tag
 */
void gui_sensorTag_TurnOFF()
{
    // unregister from all the sensors
    gui_sensorTag_Unregister();
    isSensorTagActive = false;

    // notify KW40
    GuiDriver_NotifyKW40( GUI_CURRENT_APP_IDLE );

    // go back to total sleep mode
    power_SetSleepMode( POWER_SLEEP_MODE_TOTAL );

    // sensor_ClearLEDIndicator();
}


/**
 * check if sensor tag should be enabled at startup
 */
void gui_sensorTag_CheckAtStartup()
{
    if  (
				( 1 == HEXIWEAR_FLAGS->isON_SensorTag )
			||  ( 0xFF == HEXIWEAR_FLAGS->isON_SensorTag )
		)
    {
        gui_sensorTag_TurnON();
        gui_sensorTag_icon.img = gui_sensorTag_on_bmp;
    }
}
