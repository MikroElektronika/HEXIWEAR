// File: bluetooth_driver.c

// Definitions of main functionalities in the bluetooth gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "bluetooth.h"
#include "screens_common.h"
#include "bluetooth_private.h"
#include "host_mcu_interface.h"
#include "OSA.h"
#include "error.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// Converts milliseconds to ticks.
#define MSEC_TO_TICK( msec )                                                   \
    ( ( ( uint32_t )( msec ) + 500uL / ( uint32_t )configTICK_RATE_HZ )        \
    * ( uint32_t )configTICK_RATE_HZ / 1000uL )

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static event_t advModeUpdate_event;

static event_flags_t advModeUpdate_eventFlag  = 1;

static hostInterface_packet_t bluetooth_dataPacket =
{
    gHostInterface_startByte1, // .start1
    gHostInterface_startByte2, // .start2
    0,                         // .type
    0,                         // .length
    gHostInterface_trailerByte // ._data[0]
};

static bluetooth_advMode_t bluetoothCurrentAdvMode = bluetooth_advMode_enable;

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

task_handler_t bluetooth_AdvModeToggleHandler;
task_handler_t bluetooth_AdvModeUpdateHandler;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Toggles the advertisement mode.
static void bluetooth_AdvModeToggleTask( task_param_t param )
{
    while( 1 )
    {
        GuiDriver_QueueMsgGet( &bluetooth_dataPacket, OSA_WAIT_FOREVER );

        if( bluetooth_dataPacket.type == packetType_pressRight )
        {
            bluetooth_SendToggleAdvModeReq();
        }
    }
}

// Waits for the mode update and then updates the advertisement mode.
static void bluetooth_AdvModeUpdateTask( task_param_t param )
{
    bluetooth_SendGetAdvModeReq();
    
    while( 1 )
    {
        bluetooth_WaitForAdvModeUpdate( OSA_WAIT_FOREVER );

        if( bluetoothCurrentAdvMode == bluetooth_advMode_enable )
        {
            OSA_TimeDelay( 500 );
            if( gui_sensorTag_IsActive() == true )
            {
                GuiDriver_NotifyKW40( GUI_CURRENT_APP_SENSOR_TAG );
            }

            bluetooth_icon.img = bluetooth_icon_blue_bmp;
        }
        else
        {
            watch_LinkStateUpdate( linkState_disconnected );
            bluetooth_icon.img = bluetooth_icon_white_bmp;

            RTC_UpdateAlarm();
            RTC_EnableAlarm();
        }

        GuiDriver_ImageDraw( &bluetooth_icon );
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Creates the event for bluetooth update.
void bluetooth_CreateAdvModeUpdateEvent()
{
    OSA_EventCreate( &advModeUpdate_event, kEventAutoClear );
}

// Initialises bluetooth GUI.
void bluetooth_Init( void *param )
{
    if( bluetoothCurrentAdvMode == bluetooth_advMode_enable )
    {
        bluetooth_icon.img = bluetooth_icon_blue_bmp;
    }
    else
    {
        bluetooth_icon.img = bluetooth_icon_white_bmp;
    }

    GuiDriver_ImageAddToScr( &bluetooth_icon );

    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

// Creates bluetooth GUI tasks.
void bluetooth_CreateTasks( void *param )
{
    osa_status_t status;

    status = OSA_TaskCreate(
                             bluetooth_AdvModeToggleTask,
                             ( uint8_t* )"bluetooth_ToggleTask",
                             BLUETOOTH_STACK_SIZE,
                             NULL,
                             BLUETOOTH_PRIO,
                             ( task_param_t )0,
                             false,
                             &bluetooth_AdvModeToggleHandler
                           );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    status = OSA_TaskCreate(
                             bluetooth_AdvModeUpdateTask,
                             ( uint8_t* )"bluetooth_AdvModeUpdateTask",
                             BLUETOOTH_STACK_SIZE,
                             NULL,
                             BLUETOOTH_PRIO,
                             ( task_param_t )0,
                             false,
                             &bluetooth_AdvModeUpdateHandler
                           );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys bluetooth GUI tasks.
void bluetooth_DestroyTasks( void *param )
{
    osa_status_t status;

    status = OSA_TaskDestroy( bluetooth_AdvModeToggleHandler );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    status = OSA_TaskDestroy( bluetooth_AdvModeUpdateHandler );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

// Gets current advertisement mode.
bluetooth_advMode_t bluetooth_CurrentAdvModeGet()
{
    return bluetoothCurrentAdvMode;
}

// Sends request to get advertisement mode.
void bluetooth_SendGetAdvModeReq()
{
    static hostInterface_packet_t dataPacket =
    {
        gHostInterface_startByte1, // .start1
        gHostInterface_startByte2, // .start2
        0,                         // .type
        0,                         // .length
        gHostInterface_trailerByte // ._data[0]
    };

    dataPacket.type = packetType_advModeGet;
    while( HostInterface_TxQueueMsgPut(
        ( hostInterface_packet_t* )&dataPacket, true ) != kStatus_OSA_Success );
}

// Sends request to toggle advertisement mode.
void bluetooth_SendToggleAdvModeReq()
{
    static hostInterface_packet_t dataPacket =
    {
        gHostInterface_startByte1, // .start1
        gHostInterface_startByte2, // .start2
        0,                         // .type
        0,                         // .length
        gHostInterface_trailerByte // ._data[0]
    };
    
    dataPacket.type = packetType_advModeToggle;
    while( HostInterface_TxQueueMsgPut(
        ( hostInterface_packet_t* )&dataPacket, true ) != kStatus_OSA_Success );
     haptic_Vibrate();
}

// Waits for the mode update.
osa_status_t bluetooth_WaitForAdvModeUpdate( uint32_t timeout )
{
    osa_status_t status;
    event_flags_t setFlags;

    status = OSA_EventWait( &advModeUpdate_event, advModeUpdate_eventFlag,
        false, timeout, &setFlags );

    if( status != kStatus_OSA_Success )
    {
        return kStatus_OSA_Error;
    }

    return ( osa_status_t )status;
}

// Updates the advertisement mode.
osa_status_t bluetooth_AdvModeUpdate( bluetooth_advMode_t bluetooth_advMode )
{
    bluetoothCurrentAdvMode = bluetooth_advMode;
    OSA_EventSet(
        &advModeUpdate_event, ( event_flags_t )advModeUpdate_eventFlag );
        
    return kStatus_OSA_Success;
}