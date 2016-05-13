/**
 * sensor tag global objects
 * Project HEXIWEAR, 2015
 */

#include "gui_sensorTag_private.h"
#include "gui_sensorTag.h"

#include "watch.h"

#include "screens_common.h"

MSG_QUEUE_DECLARE( gui_sensorTag_queue, 1, sizeof(uint32_t) );

/**
 * private functions declarations
 */

static void gui_sensorTag_Register();
static void gui_sensorTag_Unregister();

/**
 * private variables
 */

static bool
    isSensorTagActive = false;

static task_handler_t
    gui_sensorTag_taskHandler;

static msg_queue_handler_t
    gui_sensorTag_queueHnd;

static hostInterface_packet_t
        gui_sensorTag_packet;

/**
 * private functions
 */

static void gui_sensorTag_ToggleTask( task_param_t param );

/**
 * public API
 */

/**
 * [void*  description]
 * @param param [description]
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

//    if ( false == isSensorTagActive )
//    {
//    	gui_sensorTag_icon.img = gui_sensorTag_off_bmp;
//    }
//    else
//    {
//    	gui_sensorTag_icon.img = gui_sensorTag_on_bmp;
//    }
    GuiDriver_ImageAddToScr( &gui_sensorTag_icon );


	// Read active button group
//	watch_SendGetLinkStateReq();
//
//    linkState_t
//    	linkState = watch_CurrentLinkStateGet();

//    if( linkState_connected == linkState )
    {
        screen_labelEnter.textProperties.fontColor = GUI_COLOR_WHITE;
        GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
    }
//    else
//    {
//        screen_labelEnter.textProperties.fontColor = GUI_COLOR_GRAY;
//    }
    GuiDriver_LabelAddToScr(&screen_labelEnter);
}

/**
 * [( description]
 * @param param [description]
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
 * [sensorTag_DestroyTasks description]
 * @param param [description]
 */
void gui_sensorTag_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_sensorTag_taskHandler );
    OSA_MsgQDestroy( gui_sensorTag_queueHnd );
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
    OLED_DestroyDynamicArea();
}

/**
 * [gui_sensorTag_ToggleTask description]
 * @param param [description]
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
 * [gui_sensorTag_TurnON description]
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
 * [gui_sensorTag_TurnOFF description]
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
