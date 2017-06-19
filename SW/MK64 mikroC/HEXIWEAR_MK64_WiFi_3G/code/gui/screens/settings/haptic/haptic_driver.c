// File: haptic_driver.c

// Definitions of main functionalities in the haptic gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"
#include "screens_common.h"
#include "haptic.h"
#include "haptic_private.h"
#include "host_mcu_interface.h"
#include "OSA.h"
#include "error.h"
#include "HEXIWEAR_types.h"

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

static hostInterface_packet_t haptic_dataPacket =
{
    gHostInterface_startByte1,  // .start1
    gHostInterface_startByte2,  // .start2
    0,                          // .type
    0,                          // .length
    gHostInterface_trailerByte  // ._data[0]
};

static hapticState_t hapticStateCurrent = hapticState_disable;

static mutex_t hapticMutex;

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

task_handler_t haptic_StateToggleHandler;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Haptic feedback toggle task.
static void haptic_StateToggleTask( task_param_t param )
{
    while( 1 )
    {
        GuiDriver_QueueMsgGet( &haptic_dataPacket, OSA_WAIT_FOREVER );

        if( haptic_dataPacket.type == packetType_pressRight )
        {
            hexiwear_flags_t hexiwear_stateFlags;
            
            hapticStateCurrent = ( hapticStateCurrent == hapticState_enable ) ?
                                 hapticState_disable :
                                 hapticState_enable;

            // save the current state in flash
            memcpy( ( void* )&hexiwear_stateFlags,
                ( const void* )HEXIWEAR_FLAGS, sizeof( hexiwear_stateFlags ) );

            hexiwear_stateFlags.isON_Haptic = hapticStateCurrent;
            HEXIWEAR_SetFlags( ( uint32_t )HEXIWEAR_STATE_FLAGS_ADDRESS,
                ( void* )&hexiwear_stateFlags, sizeof( hexiwear_stateFlags ) );

            if( hapticStateCurrent == hapticState_enable )
            {
                haptic_icon.img = haptic_icon_blue_bmp;
                haptic_MutexLock( OSA_WAIT_FOREVER );
                haptic_Run();
                haptic_MutexUnlock();
            }
            else
            {
                haptic_icon.img = haptic_icon_white_bmp;
            }

            GuiDriver_ImageDraw( &haptic_icon );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Performs a haptic vibration.
void haptic_Run()
{
    VIBRO_ON();
    OSA_TimeDelay( 40 );
    VIBRO_OFF();
}

// Vibrates if needed.
void haptic_Vibrate()
{
    if( haptic_CurrentStateGet() == hapticState_enable )
    {
        haptic_MutexLock( OSA_WAIT_FOREVER );
        haptic_Run();
        haptic_MutexUnlock();
    }
}

// Creates the mutex to ensure the exclusive right to haptic feedback.
osa_status_t haptic_MutexCreate()
{
    return OSA_MutexCreate( &hapticMutex );
}

// Takes the haptic feedback mutex.
osa_status_t haptic_MutexLock( uint32_t timeout )
{
    return OSA_MutexLock( &hapticMutex, timeout );
}

// Releases the haptic feedback mutex.
osa_status_t haptic_MutexUnlock()
{
    return OSA_MutexUnlock( &hapticMutex );
}

// Initialises the haptic feedback screen.
void haptic_Init( void *param )
{
    if( hapticStateCurrent == hapticState_enable )
    {
        haptic_icon.img = haptic_icon_blue_bmp;
    }
    else
    {
        haptic_icon.img = haptic_icon_white_bmp;
    }

    GuiDriver_ImageAddToScr( &haptic_icon );

    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

// Creates the GUI task for toggling haptic feedback.
void haptic_CreateTasks( void *param )
{
    osa_status_t status;

    status = OSA_TaskCreate(
                             haptic_StateToggleTask,
                             ( uint8_t* )"haptic_ToggleTask",
                             BLUETOOTH_STACK_SIZE,
                             NULL,
                             BLUETOOTH_PRIO,
                             ( task_param_t )0,
                             false,
                             &haptic_StateToggleHandler
                           );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys the GUI task for toggling haptic feedback.
void haptic_DestroyTasks( void *param )
{
    osa_status_t status;

    status = OSA_TaskDestroy( haptic_StateToggleHandler );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

// Gets current haptic feedback state.
hapticState_t haptic_CurrentStateGet()
{
    return hapticStateCurrent;
}

// Checks if haptic feedback should be enabled at startup.
void haptic_CheckAtStartup()
{
    if( ( HEXIWEAR_FLAGS->isON_Haptic == 1 ) ||
        ( HEXIWEAR_FLAGS->isON_Haptic == 0xFF ) )
    {
        hapticStateCurrent = hapticState_enable;
        haptic_icon.img    = haptic_icon_blue_bmp;
    }
}