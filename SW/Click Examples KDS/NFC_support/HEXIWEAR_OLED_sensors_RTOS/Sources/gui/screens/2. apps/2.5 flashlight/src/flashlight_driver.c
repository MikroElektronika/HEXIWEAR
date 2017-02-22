/**
 * flashlight app functionalty
 * Project HEXIWEAR, 2015
 */

#include "gui_driver.h"
#include "flashlight.h"
#include "flashlight_private.h"
#include "haptic.h"
#include "GPIO.h"

#define SetFlashOFF() isFlashlightOn = false; flashlight_icon.img = flashlight_off_bmp; FLASH_SetOFF()
#define SetFlashON()  isFlashlightOn = true;  flashlight_icon.img = flashlight_on_bmp;  FLASH_SetON()

/**
 * intern functions declarations
 */

static void flashlight_ToggleTask( task_param_t param );


task_handler_t
	flashlight_taskHandler;

static bool
	isFlashlightOn;

static hostInterface_packet_t
	flashlight_dataPacket;

/**
 * [flashlight_Init description]
 * @param param [description]
 */
void flashlight_Init( void* param )
{
    GuiDriver_ImageAddToScr( &flashlight_icon );
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * [flashlight_CreateTasks description]
 * @param param [description]
 */
void flashlight_CreateTasks( void* param )
{
    osa_status_t
        status = OSA_TaskCreate (
                                  flashlight_ToggleTask,
                                  (uint8_t *) "flashlight task",
                                  FLASHLIGHT_STACK_SIZE,
                                  NULL,
                                  FLASHLIGHT_PRIO,
                                  (task_param_t)0,
                                  false,
                                  &flashlight_taskHandler
                                );

    if ( kStatus_OSA_Success != status )
    {
        catch( CATCH_INIT );
    }
}

/**
 * [flashlight_DestroyTasks description]
 * @param param [description]
 */
void flashlight_DestroyTasks( void* param )
{
    osa_status_t
        status = OSA_TaskDestroy( flashlight_taskHandler );

    if ( kStatus_OSA_Success != status )
    {
        catch( CATCH_INIT );
    }

    OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
    SetFlashOFF();
}

/**
 * [flashlight_ToggleTask description]
 * @param param [description]
 */
static void flashlight_ToggleTask( task_param_t param )
{
    while(1)
    {
        GuiDriver_QueueMsgGet( &flashlight_dataPacket, OSA_WAIT_FOREVER );

        if( packetType_pressRight == flashlight_dataPacket.type )
        {
            switch ( isFlashlightOn )
            {
                case true:
                {
                	FLASH_SetOFF();
                	isFlashlightOn = false;
                	flashlight_icon.img = (uint8_t*)flashlight_off_bmp;
                    GuiDriver_ImageDraw( &flashlight_icon );
                    break;
                }
                case false:
                {
                	FLASH_SetON();
                	flashlight_icon.img = (uint8_t*)flashlight_on_bmp;
                    GuiDriver_ImageDraw( &flashlight_icon );
                    isFlashlightOn = true;
                    break;
                }
            }

            haptic_Vibrate();
        }
    }
}

/**
 * check if the app is active
 */
bool flashlight_isFlashlightOn()
{
	return isFlashlightOn;
}
