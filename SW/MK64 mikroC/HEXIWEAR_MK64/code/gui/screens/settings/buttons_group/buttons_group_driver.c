// File: buttons_group_driver.c

// Definitions of main functionalities in the buttons group gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "buttons_group.h"
#include "buttons_group_private.h"
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

MSG_QUEUE_DECLARE( buttonsGroup_ActiveQueue, 1, 1);

static msg_queue_handler_t buttonsGroup_ActiveQueueHnd;

static event_t activeUpdate_event;

static event_flags_t activeUpdate_eventFlag  = 1;

static hostInterface_packet_t buttonsGroup_dataPacket =
{
    gHostInterface_startByte1,  // .start1
    gHostInterface_startByte2,  // .start2
    0,                          // .type
    0,                          // .length
    gHostInterface_trailerByte  // ._data[0]
};

static buttonsGroup_t buttonsGroupCurrentActive = buttonsGroup_right;

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////
 
task_handler_t buttonsGroup_handler;
task_handler_t buttonsGroup_ActiveUpdatehandler;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Destroys the button group GUI toggle task.
static void buttonsGroup_ToggleTask( task_param_t param )
{
    while( 1 )
    {
        GuiDriver_QueueMsgGet( &buttonsGroup_dataPacket, OSA_WAIT_FOREVER );

        if( buttonsGroup_dataPacket.type == packetType_pressRight )
        {
            buttonsGroup_SendToggleActiveReq();
            haptic_Vibrate();
        }
    }
}

// Waits for the update and then updates the active button group.
static void buttonsGroup_ActiveUpdateTask( task_param_t param )
{
    while( 1 )
    {
        buttonsGroup_WaitForActiveUpdate( OSA_WAIT_FOREVER );

        if( buttonsGroupCurrentActive == buttonsGroup_right )
        {
            buttonsGroup_img.img = buttonGroup_rightSelected_bmp;

            OLED_DrawBox( 2, 30, 4, 35, 0 );
        }
        else
        {
            buttonsGroup_img.img = buttonGroup_leftSelected_bmp;

            OLED_DrawBox( 92, 30, 4, 35, 0 );
        }

        GuiDriver_ImageDraw( &buttonsGroup_img );

        GuiDriver_DrawButtonPointers( true, true );
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Creates the event for updating the active button group.
void buttonsGroup_CreateActiveUpdateEvent()
{
    OSA_EventCreate( &activeUpdate_event, kEventAutoClear );
}

// Initialises the button group screen.
void buttonsGroup_Init( void *param )
{
    if( buttonsGroupCurrentActive == buttonsGroup_right )
    {
        buttonsGroup_img.img = buttonGroup_rightSelected_bmp;
    }
    else
    {
        buttonsGroup_img.img = buttonGroup_leftSelected_bmp;
    }

    GuiDriver_ImageAddToScr( &buttonsGroup_img );

    // Create Rx Message Queue
    buttonsGroup_ActiveQueueHnd =
        OSA_MsgQCreate( buttonsGroup_ActiveQueue, 1, 1 );

    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

// Creates the button group GUI task.
void buttonsGroup_CreateTasks( void *param )
{
    osa_status_t status;

    status = OSA_TaskCreate(
                             buttonsGroup_ToggleTask,
                             ( uint8_t* )"buttonsGroup_ToggleTask",
                             BUTTONS_GROUP_STACK_SIZE,
                             NULL,
                             BUTTONS_GROUP_PRIO,
                             ( task_param_t )0,
                             false,
                             &buttonsGroup_handler
                           );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    status = OSA_TaskCreate(
                             buttonsGroup_ActiveUpdateTask,
                             ( uint8_t* )"buttonsGroup_ActiveUpdateTask",
                             BUTTONS_GROUP_STACK_SIZE,
                             NULL,
                             BUTTONS_GROUP_PRIO,
                             ( task_param_t )0,
                             false,
                             &buttonsGroup_ActiveUpdatehandler
                           );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys the button group GUI task.
void buttonsGroup_DestroyTasks( void *param )
{
    osa_status_t status;

    status = OSA_TaskDestroy( buttonsGroup_handler );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    status = OSA_TaskDestroy( buttonsGroup_ActiveUpdatehandler );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    OSA_MsgQDestroy( buttonsGroup_ActiveQueueHnd );

    OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

// Gets active button group.
buttonsGroup_t buttonsGroup_CurrentActiveGet()
{
    return buttonsGroupCurrentActive;
}

// Sends the request to KW40.
void buttonsGroup_SendGetActiveReq()
{
    static hostInterface_packet_t dataPacket =
    {
        gHostInterface_startByte1,  // .start1
        gHostInterface_startByte2,  // .start2
        0,                          // .type
        0,                          // .length
        gHostInterface_trailerByte, // ._data[0]
    };

    dataPacket.type = packetType_buttonsGroupGetActive;
    while( HostInterface_TxQueueMsgPut(
        ( hostInterface_packet_t* )&dataPacket, true ) != kStatus_OSA_Success );
}

// Sends the request for toggling the active group.
void buttonsGroup_SendToggleActiveReq()
{
    static hostInterface_packet_t dataPacket =
    {
        gHostInterface_startByte1,  // .start1
        gHostInterface_startByte2,  // .start2
        0,                          // .type
        0,                          // .length
        gHostInterface_trailerByte  // ._data[0]
    };

    dataPacket.type = packetType_buttonsGroupToggleActive;
    while( HostInterface_TxQueueMsgPut(
        ( hostInterface_packet_t* )&dataPacket, true ) != kStatus_OSA_Success );
}

// Waits for the update.
osa_status_t buttonsGroup_WaitForActiveUpdate( uint32_t timeout )
{
    osa_status_t status;
    event_flags_t setFlags;

    status = OSA_EventWait( &activeUpdate_event, activeUpdate_eventFlag,
        false, timeout, &setFlags );

    if( status != kStatus_OSA_Success )
    {
        return kStatus_OSA_Error;
    }

    return ( osa_status_t )status;
}

// Destroys the button group GUI update task.
osa_status_t buttonsGroup_ActiveUpdate( buttonsGroup_t buttonsGroupActive )
{
    OSA_EventSet( &activeUpdate_event, ( event_flags_t )activeUpdate_eventFlag);
    buttonsGroupCurrentActive = buttonsGroupActive;

    return kStatus_OSA_Success;
}