// File: gui_sensorTag_driver.c

// Definitions of main functionalities in the sensor tag gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "HEXIWEAR_info.h"
#include "HEXIWEAR_types.h"

#include "gui_sensorTag_private.h"
#include "gui_sensorTag.h"

#include "watch/watch.h"

#include "screens_common.h"

#include "sensor_driver.h"
#include "power_driver.h"

#include "error.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

MSG_QUEUE_DECLARE( gui_sensorTag_queue, 1, sizeof( uint32_t ) );

static bool isSensorTagActive = false;

static task_handler_t gui_sensorTag_taskHandler;

static msg_queue_handler_t gui_sensorTag_queueHnd;

static hostInterface_packet_t gui_sensorTag_packet;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Registers for all the packets.
static void gui_sensorTag_Register()
{
    packet_t pktIdx;

    sensor_SetMinimumDelay( 0 );
    for( pktIdx = PACKET_ACC; pktIdx < PACKET_HR; pktIdx++ )
    {
        sensor_RegisterPacketDelay( pktIdx, 0 );
        sensor_SetPacketTargets( pktIdx,
            sensor_GetPacketTargets( pktIdx ) | PACKET_PUSH_KW40, false );
    }
    sensor_RegisterPacketDelay( PACKET_BAT, 0 );
    sensor_SetPacketTargets( PACKET_BAT,
        sensor_GetPacketTargets( PACKET_BAT ) | PACKET_PUSH_KW40, true );
}

// Unregisters from all the packets.
static void gui_sensorTag_Unregister()
{
    packet_t pktIdx;

    for( pktIdx = PACKET_ACC; pktIdx < PACKET_HR; pktIdx++ )
    {
        sensor_SetPacketTargets( pktIdx,
            sensor_GetPacketTargets( pktIdx ) & ~PACKET_PUSH_KW40, false );
    }
    sensor_SetPacketTargets( PACKET_BAT,
        sensor_GetPacketTargets( PACKET_BAT ) & ~PACKET_PUSH_KW40, true );
    sensor_ResetTargetsForKW40();
}

// Sensor tag mode task charged with toggling the sensor tag mode.
static void gui_sensorTag_ToggleTask( task_param_t param )
{
    while( 1 )
    {
        gui_status_t clickStatus =
            GuiDriver_QueueMsgGet( &gui_sensorTag_packet , OSA_WAIT_FOREVER );

        if( clickStatus == GUI_STATUS_SUCCESS )
        {
            if( gui_sensorTag_packet.type == packetType_pressRight )
            {
                // load the current state in flash
                hexiwear_flags_t hexiwear_stateFlags;
                memcpy( ( void* )&hexiwear_stateFlags,
                        ( const void* )HEXIWEAR_FLAGS,
                        sizeof( hexiwear_stateFlags ) );
                
                if( isSensorTagActive == false )
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

                OSA_TimeDelay(10);
                HEXIWEAR_SetFlags( ( uint32_t )HEXIWEAR_STATE_FLAGS_ADDRESS,
                                   ( void* )&hexiwear_stateFlags,
                                   sizeof( hexiwear_stateFlags ) );
                haptic_Vibrate();
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises sensor tag mode structures and tasks.
void gui_sensorTag_Init( void* param )
{
    // create pedometer packet queue
    gui_sensorTag_queueHnd = OSA_MsgQCreate(
        gui_sensorTag_queue, 1, sizeof( uint32_t ) / sizeof( uint32_t ) );

    // vQueueAddToRegistry( gui_sensorTag_queueHnd, (char*)"SensorTag Queue" );

    GuiDriver_ImageAddToScr( &gui_sensorTag_icon );

    screen_labelEnter.textProperties.fontColor = GUI_COLOR_WHITE;
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );

//    GuiDriver_LabelAddToScr( &screen_labelEnter );
}

// Creates sensor tag mode task.
void gui_sensorTag_CreateTasks( void* param )
{
    osa_status_t taskStatus;
    
    taskStatus = OSA_TaskCreate(
                                 gui_sensorTag_ToggleTask,
                                 ( uint8_t* ) "sensor tag process",
                                 GUI_SENSOR_TAG_STACK_SIZE,
                                 NULL,
                                 GUI_SENSOR_TAG_PRIO,
                                 ( task_param_t )0,
                                 false,
                                 &gui_sensorTag_taskHandler
                               );

    if( taskStatus != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys sensor tag mode task.
void gui_sensorTag_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_sensorTag_taskHandler );
    OSA_MsgQDestroy( gui_sensorTag_queueHnd );
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
    OLED_DestroyDynamicArea();
}

// Returns task state.
bool gui_sensorTag_IsActive()
{
    return isSensorTagActive;
}

// Turns on sensor tag.
void gui_sensorTag_TurnON()
{
    linkState_t linkState;

    // notify KW40
    GuiDriver_NotifyKW40( GUI_CURRENT_APP_SENSOR_TAG );

    // register all the sensors
    gui_sensorTag_Register();
    isSensorTagActive = true;

    // check for the bluetooth connection to determine sleep mode
    linkState = watch_CurrentLinkStateGet();
    watch_LinkStateUpdate( linkState );
}

// Turns off sensor tag.
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

// Checks if sensor tag should be enabled at startup.
void gui_sensorTag_CheckAtStartup()
{
    if( ( HEXIWEAR_FLAGS->isON_SensorTag == 1 ) ||
        ( HEXIWEAR_FLAGS->isON_SensorTag == 0xFF ) )
    {
        gui_sensorTag_TurnON();
        gui_sensorTag_icon.img = gui_sensorTag_on_bmp;
    }
}