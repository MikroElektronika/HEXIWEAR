/**
 * \file flashlight_driver.c
 * \version 1.00
 * \brief this file contains flashlight app related functionality
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

#include "gui_driver.h"
#include "flashlight.h"
#include "flashlight_private.h"
#include "haptic.h"
#include "GPIO.h"

#define SetFlashOFF() isFlashlightOn = false; flashlight_icon.img = flashlight_off_bmp; FLASH_SetOFF()
#define SetFlashON()  isFlashlightOn = true;  flashlight_icon.img = flashlight_on_bmp;  FLASH_SetON()

/** intern functions declarations */

static void flashlight_ToggleTask( task_param_t param );


task_handler_t
	flashlight_taskHandler;

static bool
	isFlashlightOn;

static hostInterface_packet_t
	flashlight_dataPacket;

/**
 * initialize the flashlight app
 * @param param optional parameter
 */
void flashlight_Init( void* param )
{
    GuiDriver_ImageAddToScr( &flashlight_icon );
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * create the app task
 * @param param optional parameter
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
 * destroy the app task
 * @param param optional parameter
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
 * toggle the task, making it active/inactive
 * @param param optional parameter
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
                    SetFlashOFF();
                    GuiDriver_ImageDraw( &flashlight_icon );
                    break;
                }
                case false:
                {
                    SetFlashON();
                    GuiDriver_ImageDraw( &flashlight_icon );
                    break;
                }
            }

            haptic_Vibrate();
        }
    }
}

/**
 * check if the app is active
 * @return status flag
 */
bool flashlight_isFlashlightOn()
{
	return isFlashlightOn;
}
