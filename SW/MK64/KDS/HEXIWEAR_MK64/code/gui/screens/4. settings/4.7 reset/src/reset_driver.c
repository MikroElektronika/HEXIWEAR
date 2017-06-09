/**
 * \file reset_driver.c
 * \version 1.00
 * \brief this file contains HEXIWEAR Reset Screen functionality
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
#include "reset.h"
#include "reset_private.h"
#include "haptic.h"
#include "GPIO.h"
#include "HEXIWEAR_driver.h"

/**
 * intern functions declarations
 */

static void reset_ToggleTask( task_param_t param );

task_handler_t
	reset_taskHandler;

static hostInterface_packet_t
	reset_dataPacket;

/**
 * [reset_Init description]
 * @param param [description]
 */
void reset_Init( void* param )
{
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * [reset_CreateTasks description]
 * @param param [description]
 */
void reset_CreateTasks( void* param )
{
    osa_status_t
        status = OSA_TaskCreate (
                                  reset_ToggleTask,
                                  (uint8_t *) "reset task",
                                  RESET_STACK_SIZE,
                                  NULL,
                                  RESET_PRIO,
                                  (task_param_t)0,
                                  false,
                                  &reset_taskHandler
                                );

    if ( kStatus_OSA_Success != status )
    {
        catch( CATCH_INIT );
    }
}

/**
 * [reset_DestroyTasks description]
 * @param param [description]
 */
void reset_DestroyTasks( void* param )
{
    osa_status_t
        status = OSA_TaskDestroy( reset_taskHandler );

    if ( kStatus_OSA_Success != status )
    {
        catch( CATCH_INIT );
    }

    OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * [reset_ToggleTask description]
 * @param param [description]
 */
static void reset_ToggleTask( task_param_t param )
{
    while(1)
    {
        GuiDriver_QueueMsgGet( &reset_dataPacket, OSA_WAIT_FOREVER );

        if( packetType_pressRight == reset_dataPacket.type )
        {
            haptic_Vibrate();
            HEXIWEAR_ResetMCU();
        }
    }
}
