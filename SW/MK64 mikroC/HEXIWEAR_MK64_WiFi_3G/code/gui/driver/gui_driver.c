// File: gui_driver.c

// Definitions of main functionalities of the gui driver module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "gui_driver.h"
#include "gui_types.h"
#include "gui_info.h"

#include "gui_defs.h"
#include "gui_resources.h"

#include "OLED_info.h"
#include "OLED_defs.h"
#include "OLED_driver.h"
#include "OLED_SPI.h"

#include "projdefs.h"
#include "queue.h"
#include "OSA.h"
#include "error.h"

#include "screens_common.h"
#include "watch\watch.h"

#include "sensor_driver.h"

#include "host_mcu_interface.h"

#include "settings/buttons_group/buttons_group.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static guiNavigationDir_t guiScreenRegNav = 0;

static mutex_t buttonHandlerAccess;

MSG_QUEUE_DECLARE(
    GuiDriver_queue, QUEUE_GUI_LENGTH, sizeof( hostInterface_packet_t ) );
    
MSG_QUEUE_DECLARE(
    GuiDriverFlash_queue, QUEUE_GUI_LENGTH, sizeof( hostInterface_packet_t ) );

//static mutex_t printMutex;
static uint8_t printBuffer[256];

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Adds button pointers.
static void GuiDriver_AddButtonPointers( guiNavigation_t *navigation )
{
    buttonsGroup_t buttonsGroup;
    guiImage_t *buttonUp;
    guiImage_t *buttonDown;
    
    buttonsGroup = buttonsGroup_CurrentActiveGet();
    
    if( buttonsGroup == buttonsGroup_right )
    {
        buttonUp   = &screen_buttonRightUp;
        buttonDown = &screen_buttonRightDown;
        screen_buttonRightUp.img = buttonGroup_right_bmp;
        screen_buttonRightDown.img = buttonGroup_right_bmp;
    }
    else
    {
        buttonUp   = &screen_buttonLeftUp;
        buttonDown = &screen_buttonLeftDown;
        screen_buttonLeftUp.img = buttonGroup_left_bmp;
        screen_buttonLeftDown.img = buttonGroup_left_bmp;
    }

    if( navigation->up != NULL )
    {
        GuiDriver_ImageAddToScr( buttonUp );
    }

    if( navigation->down != NULL )
    {
        GuiDriver_ImageAddToScr( buttonDown );
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialise the gui driver module.
gui_status_t GuiDriver_Init()
{
    oled_status_t oledStatus;

    // Create mutex for the access to handling the buttons.
    OSA_MutexCreate( &buttonHandlerAccess );
    
    // Create mutex for snprintf.
    // OSA_MutexCreate( &printMutex );
    
    // Create the queue.
    GuiDriver_queueHnd = OSA_MsgQCreate(
        GuiDriver_queue,
        gHostInterface_msgNum,
        sizeof(hostInterface_packet_t) / sizeof(uint32_t)
    );

    if( GuiDriver_queueHnd == NULL )
    {
        error_catch( CATCH_QUEUE );
        return GUI_STATUS_ERROR;
    }
    
    GuiDriverFlash_queueHnd = OSA_MsgQCreate(
        GuiDriverFlash_queue,
        gHostInterface_msgNum,
        sizeof(hostInterface_packet_t) / sizeof(uint32_t)
    );

    if( GuiDriverFlash_queueHnd == NULL )
    {
        error_catch( CATCH_QUEUE );
        return GUI_STATUS_ERROR;
    }

    oledModule.protocol.instance = FSL_OLED_SPI;
    oledModule.protocol.timeout = SPI_TIMEOUT;
    if( OLED_Init( &oledModule ) != OLED_STATUS_SUCCESS )
    {
        error_catch( CATCH_QUEUE );
        return GUI_STATUS_ERROR;
    }
    
    guiDriver_display.guiItem = &splashScreen;
    GuiDriver_Navigation( GUI_NAVIGATION_SPLASH, NULL );
    OSA_TimeDelay( 750 );

    // Read link state
    watch_CreateLinkStateUpdateEvent();
    do
    {
        watch_SendGetLinkStateReq();
    }
    while( watch_WaitForLinkStateUpdate( 100 ) != kStatus_OSA_Success );

    // Read active button group
    buttonsGroup_CreateActiveUpdateEvent();
    do
    {
        buttonsGroup_SendGetActiveReq();
    }
    while( buttonsGroup_WaitForActiveUpdate( 100 ) != kStatus_OSA_Success );

    // Read advertise mode
    bluetooth_CreateAdvModeUpdateEvent();
    do
    {
        bluetooth_SendGetAdvModeReq();
    }
    while( bluetooth_WaitForAdvModeUpdate( 100 ) != kStatus_OSA_Success );

    // exchange version numbers with KW40
    HEXIWEAR_CreateVersionEvent();
    do
    {
        HEXIWEAR_SendVersionReq();
    }
    while( HEXIWEAR_WaitForVersionUpdate( 100 ) != kStatus_OSA_Success );

    GuiDriver_Navigation( GUI_NAVIGATION_WATCH, NULL );

    return GUI_STATUS_SUCCESS;
}

// Handler for gui buttons.
gui_status_t GuiDriver_ButtonsHandler( hostInterface_packet_t* packet )
{
    gui_status_t status = GUI_STATUS_SUCCESS;
    
    guiNavigationDir_t navigationDir;
    
    switch( packet->type )
    {
        case packetType_pressUp:
            navigationDir = GUI_NAVIGATION_UP;
            break;

        case packetType_pressDown:
            navigationDir = GUI_NAVIGATION_DOWN;
            break;

        case packetType_pressLeft:
            navigationDir = GUI_NAVIGATION_LEFT;
            break;

        case packetType_pressRight:
            navigationDir = GUI_NAVIGATION_RIGHT;
            break;

        default:
            return GUI_STATUS_ERROR;
    }
    
    if( guiScreenRegNav & navigationDir )
    {
        status = GuiDriver_QueueMsgPut( packet );
    }
    else
    {
        status = GuiDriver_Navigation( navigationDir, NULL );
    }
    
    return status;
}

// Navigates from the current to the next screen.
gui_status_t GuiDriver_Navigation(
    guiNavigationDir_t navigationDir, void *param )
{
    const guiScreen_t *ptrNewScreen;
    oled_transition_t transition;
    void *destroyParam = NULL;
    void *initParam = NULL;
    void *createParam = NULL;
    
    oled_status_t statusOLED = OLED_STATUS_SUCCESS;
    uint8_t xCrd = 0;
    uint8_t yCrd = 0;
    uint8_t width;
    uint8_t height;
    
    const guiNavigation_t *navigation = &guiDriver_display.guiItem->navigation;
    
    switch( navigationDir )
    {
        // splash screen
        case GUI_NAVIGATION_SPLASH:
            ptrNewScreen = &splashScreen;
            transition = OLED_TRANSITION_NONE;
            break;

        // go to watch directly
        case GUI_NAVIGATION_WATCH:
            ptrNewScreen = &watchScreen;
            transition = OLED_TRANSITION_NONE;
            break;

        case GUI_NAVIGATION_BOND:
        {
            uint32_t passkey;
            memcpy( ( uint8_t* )&passkey, ( uint8_t* )param, 4 );
            bond_SetPasskey( passkey );
            ptrNewScreen = &bondScreen;
            initParam = guiDriver_display.guiItem;
            transition = OLED_TRANSITION_RIGHT_LEFT;
            break;
        }
        case GUI_NAVIGATION_MESSAGE:
        {
            uint8_t messageType;
            memcpy( ( uint8_t*) &messageType, ( uint8_t* )param, 1 );
            if(messageType == 0)
            {
                ptrNewScreen = &messageMissingWirelessScreen;
            }
            initParam = guiDriver_display.guiItem;
            transition = OLED_TRANSITION_RIGHT_LEFT;
            break;
        }

        // regular navigation cases
        
        case GUI_NAVIGATION_LEFT:
            ptrNewScreen = navigation->left;
            transition = OLED_TRANSITION_LEFT_RIGHT;
            break;

        case GUI_NAVIGATION_RIGHT:
            ptrNewScreen = navigation->right;
            transition = OLED_TRANSITION_RIGHT_LEFT;
            break;

        case GUI_NAVIGATION_UP:
            ptrNewScreen = navigation->up;
            transition = OLED_TRANSITION_DOWN_TOP;
            break;

        case GUI_NAVIGATION_DOWN:
            ptrNewScreen = navigation->down;
            transition = OLED_TRANSITION_TOP_DOWN;
            break;

        default:
            return GUI_STATUS_ERROR;
    }
    
    if( ptrNewScreen == NULL )
        return GUI_STATUS_ERROR;

   if( haptic_CurrentStateGet() == hapticState_enable )
   {
       haptic_MutexLock( OSA_WAIT_FOREVER );
       haptic_Run();
   }
    
    // End action for the current screen.
    if( guiDriver_display.guiItem->destroyTaskFunction != NULL )
    {
        osa_status_t mutexStatus;
        
        mutexStatus = OSA_MutexLock( &spiAccessMutex, OSA_WAIT_FOREVER );
        if( mutexStatus != kStatus_OSA_Success )
        {
            error_catch( CATCH_MUTEX );
        }

        // Release the mutex, in case the destroy function uses OLED.
        OSA_MutexUnlock( &spiAccessMutex );

        guiDriver_display.guiItem->destroyTaskFunction( destroyParam );
        OSA_TimeDelay( 20 ); //TODO: fine-tune the delay
    }
    
    // Update the current gui item.
    guiDriver_display.guiItem = ptrNewScreen;
    
    if( guiDriver_display.guiItem->image != NULL )
        OLED_Swap( guiDriver_display.image,
            GuiDriver_SkipHeader( ptrNewScreen->image ), OLED_SCREEN_SIZE );
    else
        memset( guiDriver_display.image, 0,
            OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL );

    // Starting action for the new screen.
    if( ptrNewScreen->initFunction != NULL )
        ptrNewScreen->initFunction( initParam );

    if( guiDriver_display.guiItem->image != NULL )
    {
        OLED_GetImageDimensions(
            &width, &height, guiDriver_display.guiItem->image );
    }
    else
    {
        width = 96;
        height = 96;
    }
    
    GuiDriver_AddButtonPointers( &guiDriver_display.guiItem->navigation );
    
    while( 1 )
    {
        statusOLED = OLED_DrawScreen(
            guiDriver_display.image,
            xCrd,
            yCrd,
            width,
            height,
            transition );

        if( statusOLED == OLED_STATUS_SUCCESS )
            break;
    }

   if( haptic_CurrentStateGet() == hapticState_enable )
   {
       OSA_TimeDelay( 50 );
       haptic_MutexUnlock();
   }
    
    if( statusOLED == OLED_STATUS_SUCCESS )
    {
        // Post-load action for the new screen.
        if( ptrNewScreen->createTaskFunction != NULL )
            ptrNewScreen->createTaskFunction( createParam );

        return GUI_STATUS_SUCCESS;
    }
    else
    {
        return GUI_STATUS_ERROR;
    }
}

// Puts a message into the gui driver message queue.
gui_status_t GuiDriver_QueueMsgPut( hostInterface_packet_t* packet )
{
    BaseType_t status = xQueueSendToBack(
        GuiDriver_queueHnd, packet, OSA_WAIT_FOREVER );

    if( status != pdPASS )
    {
        error_catch( CATCH_QUEUE );
        return GUI_STATUS_ERROR;
    }
    
    return GUI_STATUS_SUCCESS;
}

// Puts a message into the gui driver message queue.
gui_status_t GuiDriverFlash_QueueMsgPut( hostInterface_packet_t* packet )
{
    BaseType_t status = xQueueSendToBack(
        GuiDriverFlash_queueHnd, packet, OSA_WAIT_FOREVER );

    if( status != pdPASS )
    {
        error_catch( CATCH_QUEUE );
        return GUI_STATUS_ERROR;
    }

    return GUI_STATUS_SUCCESS;
}



// Gets a message from the gui driver message queue.
gui_status_t GuiDriver_QueueMsgGet(
    hostInterface_packet_t* packet, uint32_t timeout )
{
    osa_status_t status = OSA_MsgQGet( GuiDriver_queueHnd, packet, timeout );
    
    if( status == kStatus_OSA_Error )
    {
        error_catch( CATCH_QUEUE );
        return GUI_STATUS_ERROR;
    }
    
    return GUI_STATUS_SUCCESS;
}

// Gets a message from the gui driver flash message queue.
gui_status_t GuiDriverFlash_QueueMsgGet(
    hostInterface_packet_t* packet, uint32_t timeout )
{
    osa_status_t status = OSA_MsgQGet( GuiDriverFlash_queueHnd, packet, timeout );

    if( status == kStatus_OSA_Error )
    {
        error_catch( CATCH_QUEUE );
        return GUI_STATUS_ERROR;
    }

    return GUI_STATUS_SUCCESS;
}

// Updates the main screen buffer.
void GuiDriver_UpdateScreen (
    uint8_t xCrd,
    uint8_t yCrd,
    uint8_t width,
    uint8_t height,
    const uint8_t* image )
{
    uint8_t i;
    oled_pixel_t copyAddr;
    // Copy data.
    copyAddr = ( oled_pixel_t )guiDriver_display.image
        + ( yCrd * OLED_SCREEN_WIDTH + xCrd );

    for( i = 0; i < height; i++ )
    {
        memcpy( copyAddr, image, width * OLED_BYTES_PER_PIXEL );
        copyAddr += OLED_SCREEN_WIDTH;
        image    += width * OLED_BYTES_PER_PIXEL;
    }
}

// Creates a label.
gui_status_t GuiDriver_LabelCreate( guiLabel_t *label )
{
    if( label->caption != NULL )
        return GUI_STATUS_ERROR;

    label->caption = ( uint8_t * )OSA_MemAlloc( label->captionLength );
    
    if( label->caption == NULL )
        return GUI_STATUS_ERROR;
    
    return GUI_STATUS_SUCCESS;
}

// Destroys a label.
gui_status_t GuiDriver_LabelDestroy(guiLabel_t *label)
{
    if( label->caption == NULL )
        return GUI_STATUS_ERROR;

    if( OSA_MemFree( label->caption )
        != kStatus_OSA_Success )
    {
        return GUI_STATUS_ERROR;
    }
    
    label->caption = NULL;
    return GUI_STATUS_SUCCESS;
}

// Sets label caption.
void GuiDriver_LabelSetCaption(guiLabel_t *label, uint8_t *caption)
{
    strcpy( label->caption, caption );
}

// Formats the caption of a label.
gui_status_t GuiDriver_LabelFormatCaption(guiLabel_t *label, uint8_t *caption,
    uint8_t *length, guiLabelCutFormat_t format)
{
    uint8_t tmpLength;
    uint8_t inLength;
    
    if( length == NULL )
        inLength = strlen( caption );
    else
        inLength = *length;

    if( inLength > ( label->captionLength - 1 ) )
        tmpLength = label->captionLength - 1;
    else
        tmpLength = inLength;

    tmpLength = OLED_CharCount( label->dynamicArea.width,
        label->textProperties.font, caption, tmpLength );
    if( tmpLength == 0 )
        return GUI_STATUS_ERROR;

    memcpy( label->caption, caption, tmpLength );
    label->caption[tmpLength] = 0;
    
    if( tmpLength < inLength )
    {
        if( format == GUI_LABEL_CUT_FORMAT_DOTS )
        {
            if( tmpLength <= 2 )
                return GUI_STATUS_ERROR;

            label->caption[ tmpLength - 1 ] = '.';
            label->caption[ tmpLength - 2 ] = '.';
            tmpLength -= 2;
        }
        else if( format == GUI_LABEL_CUT_FORMAT_SPACE )
        {
            char *tmpPtr;
            tmpPtr = strrchr( label->caption, ' ' );
            if( ( tmpPtr != NULL ) && ( tmpPtr != label->caption ) )
            {
                *tmpPtr = 0;
                tmpLength = tmpPtr - ( char* )label->caption;
            }
        }
    }
    
    if( length != NULL )
        *length = tmpLength;

    return GUI_STATUS_SUCCESS;
}

// Draws the given label.
void GuiDriver_LabelDraw( guiLabel_t *label )
{
    OLED_SetTextProperties( &label->textProperties );
    OLED_SetDynamicArea( &label->dynamicArea );
    while( 1 )
    {
        if( OLED_DrawText( label->caption ) == OLED_STATUS_SUCCESS )
            break;
    }
}

// Adds a label to the screen.
void GuiDriver_LabelAddToScr( guiLabel_t *label )
{
    OLED_SetTextProperties( &label->textProperties );
    OLED_SetDynamicArea( &label->dynamicArea );
    OLED_AddText( label->caption );
}

// Draws the given image.
void GuiDriver_ImageDraw( guiImage_t *image )
{
    OLED_GetImageDimensions( &image->dynamicArea.width,
        &image->dynamicArea.height, image->img );
    OLED_SetDynamicArea( &image->dynamicArea );
    while( 1 )
    {
        if ( OLED_DrawImage( image->img ) == OLED_STATUS_SUCCESS )
            break;
    }
}

// Adds an image to the screen.
void GuiDriver_ImageAddToScr( guiImage_t *image )
{
    if( image->img != NULL )
    {
        OLED_GetImageDimensions( &image->dynamicArea.width,
            &image->dynamicArea.height, image->img );
        OLED_SetDynamicArea( &image->dynamicArea );
        OLED_AddImage( image->img );
    }
}

// Draws button pointers on the screen.
void GuiDriver_DrawButtonPointers( bool upButtonFlag, bool downButtonFlag )
{
    buttonsGroup_t buttonsGroup;
    guiImage_t    *buttonUp;
    guiImage_t    *buttonDown;
    
    buttonsGroup = buttonsGroup_CurrentActiveGet();

    if( buttonsGroup == buttonsGroup_right )
    {
        buttonUp   = &screen_buttonRightUp;
        buttonDown = &screen_buttonRightDown;
        screen_buttonRightUp.img = buttonGroup_right_bmp;
        screen_buttonRightDown.img = buttonGroup_right_bmp;
    }
    else
    {
        buttonUp   = &screen_buttonLeftUp;
        buttonDown = &screen_buttonLeftDown;
        screen_buttonLeftUp.img = buttonGroup_left_bmp;
        screen_buttonLeftDown.img = buttonGroup_left_bmp;
    }

    if( upButtonFlag )
    {
        GuiDriver_ImageDraw( buttonUp );
    }

    if( downButtonFlag )
    {
        GuiDriver_ImageDraw( buttonDown );
    }
}

// Clears the screen.
void GuiDriver_ClearScr()
{
    memset( guiDriver_display.image, 0,
        OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL );
    OLED_FillScreen(0);
}

// Registers for sensor data.
void GuiDriver_RegisterForSensors(
    packet_t packetToReceive, uint32_t delay_ms, bool shouldToggleTask )
{
    if( delay_ms != portMAX_DELAY )
        sensor_RegisterPacketDelay( packetToReceive, delay_ms );
    sensor_SetPacketTargets( packetToReceive,
        sensor_GetPacketTargets( packetToReceive ) | PACKET_PUSH_OLED,
        shouldToggleTask );
}

// Registers for sensor data through flash queue.
void GuiDriver_RegisterForSensorsFlash(
    packet_t packetToReceive, uint32_t delay_ms, bool shouldToggleTask )
{
    if( delay_ms != portMAX_DELAY )
        sensor_RegisterPacketDelay( packetToReceive, delay_ms );
    sensor_SetPacketTargets( packetToReceive,
        sensor_GetPacketTargets( packetToReceive ) | PACKET_PUSH_FLASH,
        shouldToggleTask );
}

// Sets minimum delay for sensors.
void GuiDriver_RegisterMinPollDelay( uint32_t delay )
{
    sensor_SetMinimumDelay( delay );
}

// Adds a navigation to the navigation register.
void GuiDriver_RegisterForNavigation( guiNavigationDir_t navigations )
{
    guiScreenRegNav |= navigations;
}

// Un-registers for sensor data.
void GuiDriver_UnregisterFromSensors(
    packet_t packetToReceive, bool shouldDeactivateTask )
{
    sensor_SetPacketTargets( packetToReceive,
        sensor_GetPacketTargets( packetToReceive ) & ~PACKET_PUSH_OLED,
        shouldDeactivateTask );
}

// Un-registers for sensor data.
void GuiDriver_UnregisterFromSensorsFlash(
    packet_t packetToReceive, bool shouldDeactivateTask )
{
    sensor_SetPacketTargets( packetToReceive,
        sensor_GetPacketTargets( packetToReceive ) & ~PACKET_PUSH_FLASH,
        shouldDeactivateTask );
}

// Removes a navigation from the navigation register.
void GuiDriver_UnregisterFromNavigation( guiNavigationDir_t navigations )
{
    guiScreenRegNav &= ~navigations;
}

// Cleans the main area of the screen.
void GuiDriver_CleanMainArea()
{
    while ( OLED_DrawBox( 0, 20, 90, 55, 0x0 ) != OLED_STATUS_SUCCESS ) {}
}

// Cleans most of the screen.
void GuiDriver_CleanAbout()
{
    while ( OLED_DrawBox( 0, 0, 90, 80, 0x0 ) != OLED_STATUS_SUCCESS ) {}
}

// Notifies KW40 about the current app.
gui_status_t GuiDriver_NotifyKW40( gui_current_app_t currentApp )
{
    osa_status_t txStatus;
    hostInterface_packet_t currentAppPacket;

    currentAppPacket.type = packetType_appMode;
    currentAppPacket.length = sizeof( currentApp );

    memcpy( ( void* )&( currentAppPacket._data[0] ), ( void* )&currentApp,
        sizeof( currentApp ) );
    currentAppPacket._data[ currentAppPacket.length ] =
        gHostInterface_trailerByte;

    txStatus = HostInterface_TxQueueMsgPut( &currentAppPacket, true );

    if ( kStatus_OSA_Success == txStatus )
    {
        return GUI_STATUS_SUCCESS;
    }
    else
    {
        error_catch( CATCH_QUEUE );
        return GUI_STATUS_ERROR;
    }
}

// Writes formatted output to sized buffer.
/* uint8_t snprintf( uint8_t * s, uint8_t n, const code uint8_t * format, ... )
{
    va_list argptr;

    OSA_MutexLock( &printMutex, OSA_WAIT_FOREVER );
    
    va_start( argptr, format );
    sprintf( printBuffer, format, argptr );
    // va_end( argptr );
    
    printBuffer[ n - 1 ] = '\0';
    memcpy( s, printBuffer, n );
    
    OSA_MutexUnlock( &printMutex );
    
    return strlen( s );
} */