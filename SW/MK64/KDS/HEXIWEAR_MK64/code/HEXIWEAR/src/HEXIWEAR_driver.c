/**
 * \file HEXIWEAR_driver.c
 * \version 1.00
 * \brief this file contains global HEXIWEAR functionality
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
 * get support at: http://www.mikroe.com/forum and https://community.freescale.com
 *
 * Project HEXIWEAR, 2015
 */

#include "HEXIWEAR_driver.h"
#include "HEXIWEAR_defs.h"
#include "HEXIWEAR_info.h"

#include "flash_boot_kinetis.h"

#include "sensor_driver.h"
#include "sensor_defs.h"

#include "timer_driver.h"

#include "power_driver.h"

#include "notifications.h"
#include "flashlight.h"

#include "host_mcu_interface.h"
#include "gui_driver.h"

#include "FLASH_driver.h"

#include "CLOCK.h"

#include "PWR_Manager.h"

#include "error.h"
#include "error_types.h"

#include "screens_common.h"

static packet_pushTarget_t*
  HEXIWEAR_currentBackupList = NULL;

static packet_pushTarget_t
  HEXIWEAR_currentApp = PACKET_PUSH_NONE;

static event_t
  HEXIWEAR_versionEvent;

static event_flags_t
	HEXIWEAR_eventFlag  = 1;

void HEXIWEAR_startup( task_param_t param )
{
  uint8_t
    status = 0;

  /** output GPIO configuration */

  GPIO_DRV_Init( NULL, OLED_cfg );
  GPIO_DRV_Init( NULL, FLASH_cfg );
  GPIO_DRV_Init( NULL, PWR_cfg );
  GPIO_DRV_Init( NULL, VIBRO_cfg );
  GPIO_DRV_Init( NULL, RGB_cfg );
  GPIO_DRV_Init( NULL, KW40_GPIO_cfg );


  /** input GPIO configuration */

  GPIO_DRV_Init( BAT_CHG_cfg, NULL );
  GPIO_DRV_Init( TAP_cfg, NULL );

#if defined( HEXIWEAR_DEBUG )
  GPIO_DRV_Init( NULL, DEBUG_cfg );
#endif

  power_ResetKW40();
  timer_Init( HEXIWEAR_TIMER_SENSOR );

  status |= RTC_Init();
  status |= FLASH_Init( &flashModule, &flashSettings );

  // intern flash initialization
  INTFLASH_Init();

  // RGB off
  FLASH_SetOFF();

  /** create basic tasks */
  status |= Notification_Init();
  status |= HostInterface_Init();
  status |= sensor_Init();
  status |= GuiDriver_Init();

  haptic_MutexCreate();

  sensor_InitAcc();

  /** set GPIO interrupt for the tap function */
  PORT_HAL_SetPinIntMode( PORTC, 1, kPortIntFallingEdge );

  /** set charging battery interrupt */
  PORT_HAL_SetPinIntMode( PORTC, 12, kPortIntEitherEdge );
  NVIC_SetPriority( PORTC_IRQn, HEXIWEAR_CHG_IRQ_PRIO );
  INT_SYS_EnableIRQ( PORTC_IRQn );

  if ( HEXIWEAR_STATUS_SUCCESS != status )
  {
    catch( CATCH_INIT );
  }

  /** check for settings in flash at startup */
  gui_sensorTag_CheckAtStartup();
  haptic_CheckAtStartup();

  CLOCK_SYS_Init( g_clockManConfigsArr, FSL_CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, FSL_CLOCK_MANAGER_CALLBACK_CNT );
  POWER_SYS_Init( powerConfigsArr, 2U, powerStaticCallbacksConfigsArr , 2U );

  // turn on regular battery readings
  sensor_SetPacketTargets( PACKET_BAT, sensor_GetPacketTargets( PACKET_BAT) | PACKET_PUSH_POWER_MGMT, true );

  while (1)
  {
    power_Init();
    OSA_TaskDestroy( NULL );
  }
}

/**
 * initialize the rest of the tasks
 * @return status flag
 */
hexiwear_status_t HEXIWEAR_Init()
{
  osa_status_t
    status = OSA_TaskCreate (
                              HEXIWEAR_startup,
                              (uint8_t*)"HEXIWEAR startup",
                              HEXIWEAR_STARTUP_STACK_SIZE,
                              NULL,
                              HEXIWEAR_STARTUP_PRIO,
                              (task_param_t)0,
                              false,
                              &hexiwear_startup_handler
                            );

  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_INIT );
    return HEXIWEAR_STATUS_INIT_ERROR;
  }

  else
  {
    return HEXIWEAR_STATUS_SUCCESS;
  }
}

/**
 * reset the MCU
 */
void HEXIWEAR_ResetMCU()
{
  NVIC_SystemReset();
}

/**
 * [HEXIWEAR_GetBackupList description]
 */
void* HEXIWEAR_GetAppBackupList()
{
    return HEXIWEAR_currentBackupList;
}

/**
 * [HEXIWEAR_GetTargetApp description]
 */
packet_pushTarget_t HEXIWEAR_GetAppTarget()
{
    return HEXIWEAR_currentApp;
}

/**
 * [HEXIWEAR_SetBackupList description]
 */
void HEXIWEAR_SetBackupList( packet_pushTarget_t* currentBackupList )
{
    HEXIWEAR_currentBackupList = (packet_pushTarget_t*)currentBackupList;
}

/**
 * [HEXIWEAR_SetTargetApp description]
 */
void HEXIWEAR_SetTargetApp( packet_pushTarget_t currentApp )
{
    HEXIWEAR_currentApp = currentApp;
}

/**
 * set application-specific flags
 * @param  flashAddress flash address for programming
 * @param  flags        data to be programmed into flash
 * @param  flagSize     data size, must be multiple of 8 bytes
 * @return              status flag
 */
hexiwear_status_t HEXIWEAR_SetFlags (
                                         uint32_t flashAddress,
                                            void* flags,
                                         uint32_t flagSize
                                    )
{
	if ( 0 != ( flagSize % 8 ) )
	{
		return HEXIWEAR_STATUS_INIT_ERROR;
	}

    /** erase the sector before programming */
    if  ( INTFLASH_OK != INTFLASH_EraseSector( (uint32_t)flashAddress ) )
    {
        catch( CATCH_INTERN_FLASH );
        return HEXIWEAR_STATUS_ERROR;
    }

    /** program flags */
    if  (
            INTFLASH_OK != INTFLASH_Program(
                                                (uint32_t)flashAddress,
                                                (uint32_t)flags,
                                                flagSize
                                            )
        )
    {
        catch( CATCH_INTERN_FLASH );
        return HEXIWEAR_STATUS_ERROR;
    }

    return HEXIWEAR_STATUS_SUCCESS;
}

void vApplicationIdleHook( void )
{
	asm("nop");
}


/**
 * [HEXIWEAR_CreateVersionEvent description]
 */
void HEXIWEAR_CreateVersionEvent()
{
    OSA_EventCreate( &HEXIWEAR_versionEvent, kEventAutoClear );
}

/**
 * [HEXIWEAR_CreateVersionEvent description]
 */
void HEXIWEAR_SendVersionReq()
{
    static hostInterface_packet_t
        dataPacket;

    dataPacket.length  = 3;
    dataPacket.type    = packetType_buildVersion;

    dataPacket.data[0] = HEXIWEAR_VERSION_MAJOR;
    dataPacket.data[1] = HEXIWEAR_VERSION_MINOR;
    dataPacket.data[2] = HEXIWEAR_VERSION_PATCH;

    dataPacket.data[3] = gHostInterface_trailerByte;

    while( HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&dataPacket, true) != kStatus_OSA_Success ) {}
}

/**
 * [HEXIWEAR_WaitForVersionUpdate description]
 * @param  timeout [description]
 * @return         [description]
 */
osa_status_t HEXIWEAR_WaitForVersionUpdate(uint32_t timeout)
{
    osa_status_t
        status;
    event_flags_t
        setFlags;

    status = OSA_EventWait( &HEXIWEAR_versionEvent, HEXIWEAR_eventFlag, false, timeout, &setFlags );

    if ( kStatus_OSA_Success != status )
    {
        return kStatus_OSA_Error;
    }

    return (osa_status_t)status;
}

/**
 * update KW40 version
 * @return status flag
 */
osa_status_t HEXIWEAR_UpdateVersion()
{
	OSA_EventSet( &HEXIWEAR_versionEvent, (event_flags_t)HEXIWEAR_eventFlag);
	return kStatus_OSA_Success;
}
