/**
 * \file haptic_driver.c
 * \version 1.00
 * \brief this file contains haptic feedback functionality
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

/** includes */

#include "gui_driver.h"
#include "screens_common.h"
#include "haptic_private.h"
#include "host_mcu_interface.h"
#include "fsl_os_abstraction.h"

/** private type definitions */

/** private macros */

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec)  (((uint32_t)(msec)+500uL/(uint32_t)configTICK_RATE_HZ) \
                             *(uint32_t)configTICK_RATE_HZ/1000uL)

/** private prototypes */

static void haptic_StateToggleTask(task_param_t param);

/** public memory declarations */

task_handler_t haptic_StateToggleHandler;

/** private memory declarations */

static hostInterface_packet_t haptic_dataPacket =
{
	.start1 = gHostInterface_startByte1,
	.start2 = gHostInterface_startByte2,
	.length = 0,
	.data[0] = gHostInterface_trailerByte
};

static hapticState_t hapticStateCurrent = hapticState_disable;

static mutex_t hapticMutex;

void haptic_Run()
{
	VIBRO_ON();
	OSA_TimeDelay(40);
	VIBRO_OFF();
}

void haptic_Vibrate()
{
	if ( haptic_CurrentStateGet() == hapticState_enable )
	{
		haptic_MutexLock(OSA_WAIT_FOREVER);
		haptic_Run();
		haptic_MutexUnlock();
	}
}

/**
 * create the mutex to ensure the exclusive right to haptic feedback
 * @return status flag
 */
osa_status_t haptic_MutexCreate()
{
	return OSA_MutexCreate( &hapticMutex );
}

/**
 * take the haptic feedback mutex
 * @return status flag
 */
osa_status_t haptic_MutexLock(uint32_t timeout)
{
	return OSA_MutexLock( &hapticMutex, timeout );
}

/**
 * release the haptic feedback mutex
 * @return status flag
 */
osa_status_t haptic_MutexUnlock()
{
	return OSA_MutexUnlock( &hapticMutex );
}

/**
 * initialize the haptic feedback screen
 * @param param optional parameter
 */
void haptic_Init( void *param )
{
	if(hapticStateCurrent == hapticState_enable)
	{
		haptic_icon.img = haptic_icon_blue_bmp;
	}
	else
	{
		haptic_icon.img = haptic_icon_white_bmp;
	}

	GuiDriver_ImageAddToScr(&haptic_icon);

	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * create the GUI task for toggling haptic feedback
 * @param param optional parameter
 */
void haptic_CreateTasks( void *param )
{
	osa_status_t status;

	status = OSA_TaskCreate (
			                      haptic_StateToggleTask,
                                  (uint8_t *) "haptic_ToggleTask",
								  BLUETOOTH_STACK_SIZE,
                                  NULL,
								  BLUETOOTH_PRIO,
                                  (task_param_t)0,
                                  false,
                                  &haptic_StateToggleHandler
                                );

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}
}

/**
 * destroy the GUI task for toggling haptic feedback
 * @param param optional parameter
 */
void haptic_DestroyTasks( void *param )
{
	osa_status_t status;

	status = OSA_TaskDestroy(haptic_StateToggleHandler);

	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	OLED_DestroyDynamicArea();
	GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

/**
 * get current haptic feedback state
 * @return  current state
 */
hapticState_t haptic_CurrentStateGet()
{
	return hapticStateCurrent;
}

/**
 * check if haptic feedback should be enabled at startup
 */
void haptic_CheckAtStartup()
{
	if 	(
				( 1 == HEXIWEAR_FLAGS->isON_Haptic )
			||  ( 0xFF == HEXIWEAR_FLAGS->isON_Haptic )
		)
	{
		hapticStateCurrent = hapticState_enable;
		haptic_icon.img    = haptic_icon_blue_bmp;
	}
}

/**
 * haptic feedback toggle task
 * @param param optional parameter
 */
static void haptic_StateToggleTask(task_param_t param)
{
	while(1)
	{
		GuiDriver_QueueMsgGet( &haptic_dataPacket, OSA_WAIT_FOREVER );

	    if(haptic_dataPacket.type == packetType_pressRight)
		{
	    	hapticStateCurrent = (hapticStateCurrent == hapticState_enable) ? hapticState_disable : hapticState_enable;

	    	/** save the current state in flash */
	    	hexiwear_flags_t
	    		hexiwear_stateFlags = {0};
	    	memcpy( (void*)&hexiwear_stateFlags, (const void*)HEXIWEAR_FLAGS, sizeof( hexiwear_stateFlags ) );

            hexiwear_stateFlags.isON_Haptic = hapticStateCurrent;
            HEXIWEAR_SetFlags( (uint32_t)HEXIWEAR_STATE_FLAGS_ADDRESS, (void*)&hexiwear_stateFlags, sizeof(hexiwear_stateFlags) );

		    if(hapticStateCurrent == hapticState_enable)
			{
				haptic_icon.img = haptic_icon_blue_bmp;
				haptic_MutexLock(OSA_WAIT_FOREVER);
				haptic_Run();
				haptic_MutexUnlock();
			}
			else
			{
				haptic_icon.img = haptic_icon_white_bmp;
			}

			GuiDriver_ImageDraw(&haptic_icon);
		}
	}
}
