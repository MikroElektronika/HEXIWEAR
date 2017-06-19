// File: bootloader_driver.c

// Definitions of main functionalities in the bootloader gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "settings/bluetooth/bluetooth.h"
#include "screens_common.h"
#include "settings/bootloader/bootloader.h"
#include "settings/bootloader/bootloader_private.h"
#include "power_driver.h"
#include "error.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define OTAP_DELAY_PERIOD ( ( 5000 ) / 100 )

#define OTAP_Delay() OSA_TimeDelay(100); OTAP_TimeoutCounter--

#define OTAP_HasCounterExpired() ( OTAP_TimeoutCounter == 0 )
#define OTAP_ResetCounter()                                                    \
    /** pxPreviousWakeTime = xTaskGetTickCount(); */                           \
    OTAP_TimeoutCounter = OTAP_DELAY_PERIOD

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

MSG_QUEUE_DECLARE(
    bootloader_queue, BOOTLOADER_QUEUE_SIZE, sizeof( hostInterface_packet_t ) );

static msg_queue_handler_t bootloader_queueHnd;

static hostInterface_packet_t bootloader_dataPacket;

static task_handler_t bootloader_handler;

static bootInfo_t bootflags =
{
    0x0 // .newBootImageAvailable[ 0 ]
};

static bool isBootloaderQueueCreated = false;

// OTAP counter
static uint32_t OTAP_TimeoutCounter = 0;

static guiImage_t* loadImages[ LOAD_IMG_NUM ] =
    { &bootloader_loadImg_white, &bootloader_loadImg_blue };

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Gets a message from the head of the designated queue.
static bootloader_status_t bootloader_QueueMsgGet( uint32_t timeout )
{
    osa_status_t status = OSA_MsgQGet( bootloader_queueHnd,
        ( hostInterface_packet_t* )&bootloader_dataPacket, timeout);

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_QUEUE );
        return BOOTLOADER_STATUS_ERROR;
    }
    else
    {
        return BOOTLOADER_STATUS_SUCCESS;
    }
}

// Bootloader app task.
// Listens for user's input and starts the appropriate boot procedure.
static void boootloader_Task( task_param_t param )
{
    bool isOtapStarted = false;

    hostInterface_packetType_t bootloadTarget = packetType_otapKW40Started;

    hostInterface_packet_t bootloaderPacket =
    {
        gHostInterface_startByte1,  // .start1
        gHostInterface_startByte2,  // .start2
        packetType_otapKW40Started, // .type
        0                           // .length
    };
    bootloaderPacket._data[ bootloaderPacket.length ] =
        gHostInterface_trailerByte;

    GuiDriver_DrawButtonPointers( true, true );
    
    while( 1 )
    {
        // wait for the user input
        bootloader_status_t status =
            GuiDriver_QueueMsgGet( &bootloader_dataPacket, OSA_WAIT_FOREVER );

        if( status != BOOTLOADER_STATUS_SUCCESS )
        {
            error_catch( CATCH_QUEUE );
            continue;
        }
        
        switch( bootloader_dataPacket.type )
        {
            // select MK64
            case packetType_pressUp:
            {
                // display the chosen option
                GuiDriver_ImageDraw( &bootloader_selectMK64 );

                // save chosen option and designate the packet type

                bootloaderPacket.type = packetType_otapMK64Started;
                bootloadTarget = packetType_otapMK64Started;
                haptic_Vibrate();
                break;
            }

            // select MKW40
            case packetType_pressDown:
            {
                // display the chosen option
                GuiDriver_ImageDraw( &bootloader_selectKW40 );

                // save chosen option and designate the packet type

                bootloaderPacket.type = packetType_otapKW40Started;
                bootloadTarget = packetType_otapKW40Started;
                haptic_Vibrate();
                break;
            }

            // start the process
            case packetType_pressRight:
            {
                // send the OTAP packet

                isOtapStarted = true;
                haptic_Vibrate();
                break;
            }

            default: {}
        } // switch( bootloader_dataPacket.type )
        
        if( isOtapStarted == true )
        {
            uint8_t loadImgIdx = 0;
            
            // Make both of the buttons unavailable during the process,
            // and gray them out to give the visual feedback.
            // Disable the power save feature.

            power_DisablePowerSave();

            GuiDriver_RegisterForNavigation( GUI_NAVIGATION_LEFT );

            GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_UP );
            GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_DOWN );
            GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );

            GuiDriver_ImageDraw( &screen_buttonStartDisabled );
            GuiDriver_ImageDraw( &screen_buttonBackDisabled );

            // send the packet and start to measure for timeout
            HostInterface_TxQueueMsgPut( &bootloaderPacket, true );

            GuiDriver_CleanMainArea();
            
            while( 1 )
            {
                // start waiting for the new firmware download confirmation
                bootloader_status_t bootStatus = bootloader_QueueMsgGet( 0 );
                
                if( bootStatus == BOOTLOADER_STATUS_SUCCESS )
                {
                    switch( bootloader_dataPacket.type )
                    {
                        case packetType_otapCompleted:
                        {
                            GuiDriver_ImageDraw( &bootloader_success );
                            OLED_DrawBox( 0, 76, 48, 20, 0x0 );
                            
                            switch( bootloadTarget )
                            {
                                case packetType_otapMK64Started:
                                {
                                    uint32_t result;

                                    // set the flags in FLASH,
                                    // announcing that a new image is available
                                    bootflags.newBootImageAvailable[0] = 0x1;
                                    
                                    // erase the sector before programming
                                    result = Flash_EraseSector(
                                        ( uint32_t )BOOT_IMAGE_FLAGS_ADDRESS );
                                    if( result != 0 )
                                        error_catch( CATCH_INTERN_FLASH );
                                
                                    result = Flash_ProgramPhrase(
                                        ( uint32_t )BOOT_IMAGE_FLAGS_ADDRESS,
                                        ( uint8_t )&bootflags );
                                    if( result != 0 )
                                        error_catch( CATCH_INTERN_FLASH );
                                
                                    // reset the MCU
                                    OSA_TimeDelay( 3000 );
                                    HEXIWEAR_ResetMCU();
                                    break;
                                }
                                
                                case packetType_otapKW40Started:
                                {
                                    OSA_TimeDelay( 3000 );
                                    HEXIWEAR_ResetMCU();
                                    break;
                                }
                                
                                default: {}
                            }
                            break;
                        } // case packetType_otapCompleted:
                        
                        case packetType_otapFailed:
                        {
                            GuiDriver_ImageDraw( &bootloader_failure );
                            break;
                        }
                        
                        default: {}
                    } // switch( bootloader_dataPacket.type )
                
                    // exit the boot-loop and let user go back
                    power_EnablePowerSave();
                    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_LEFT );
                    break;
                } // if( bootStatus == BOOTLOADER_STATUS_SUCCESS )
                else
                {
                    GuiDriver_ImageDraw( loadImages[ loadImgIdx ] );
                    loadImgIdx = ( LOAD_IMG_NUM - 1 == loadImgIdx ) ?
                                 0                                  :
                                 loadImgIdx + 1;
                    OTAP_Delay();
                } // else
            } // while( 1 )
            
            // if we got here, either timeout occurred
            // or KW40 finished with the image download for itself
        } // if( isOtapStarted == true )
    } // while( 1 )
}

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the bootloader app.
void bootloader_Init( void* param )
{
    // create the queue
    bootloader_queueHnd = OSA_MsgQCreate(
        bootloader_queue, BOOTLOADER_QUEUE_SIZE,
        sizeof( hostInterface_packet_t ) / sizeof( uint32_t ) );
    isBootloaderQueueCreated = true;

#if defined( HEXIWEAR_DEBUG )
    vQueueAddToRegistry( bootloader_queueHnd, ( char* )"App Bootloader Queue" );
#endif

    if( bootloader_queueHnd == NULL )
    {
        error_catch( CATCH_QUEUE );
    }

    // insert default screen, which will be updated upon user's input

    OTAP_ResetCounter();

    GuiDriver_LabelCreate( &bootloader_labelLoad );

    GuiDriver_ImageAddToScr( &screen_buttonBack );

    // select KW40 by default
    GuiDriver_ImageAddToScr( &bootloader_selectKW40 );

    // register buttons for toggling fitness processes
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_UP );
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_DOWN );

    // If bluetooth advertise disabled, prohibit the OTAP mode.
    if( bluetooth_CurrentAdvModeGet() == bluetooth_advMode_enable )
    {
        GuiDriver_ImageAddToScr( &screen_buttonStart );
        GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
    }
    else
    {
        GuiDriver_ImageAddToScr(&screen_buttonStartDisabled);
    }
}

// Creates the bootloader app task.
void bootloader_CreateTasks( void* param )
{
    osa_status_t status = OSA_TaskCreate(
                                          boootloader_Task,
                                          ( uint8_t * )"Bootloader task",
                                          BOOTLOADER_STACK_SIZE,
                                          NULL,
                                          BOOTLOADER_PRIO,
                                          ( task_param_t )0,
                                          false,
                                          &bootloader_handler
                                        );

    if( kStatus_OSA_Success != status )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys the bootloader app task, queue,
// and unregisters from listening to touch buttons.
void bootloader_DestroyTasks( void* param )
{
    osa_status_t status = OSA_TaskDestroy( bootloader_handler );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    OSA_MsgQDestroy( bootloader_queueHnd );
    isBootloaderQueueCreated = false;

    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_UP );
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_DOWN );
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );

    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &bootloader_labelLoad );

    power_EnablePowerSave();
}

// Puts the packet into the designated bootloader's queue.
bootloader_status_t boootloader_QueueMsgPut ( hostInterface_packet_t* packet )
{
    if( isBootloaderQueueCreated == true )
    {
        BaseType_t status = xQueueSendToBack( bootloader_queueHnd,
            ( hostInterface_packet_t* )packet, OSA_WAIT_FOREVER );

        if( status == pdPASS )
        {
            return BOOTLOADER_STATUS_SUCCESS;
        }
        else
        {
            error_catch( CATCH_QUEUE );
            return BOOTLOADER_STATUS_ERROR;
        }
    }
    else
    {
        error_catch( CATCH_QUEUE );
        return BOOTLOADER_STATUS_ERROR;
    }
}