/**
 * \file power_driver.c
 * \version 1.00
 * \brief this file contains power management routines
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

#include "power.h"

#include "OLED_driver.h"
#include "OLED_info.h"

#include "sensor_driver.h"

#include "timer_driver.h"

#include "PWR_Manager.h"

#include "screens_common.h"

#include "error.h"
#include "GPIO.h"

#include "fsl_i2c_master_driver.h"

static semaphore_t
  power_sema,
	power_wakeSrcSema,
	power_STSema;

static bool
	isBatteryLow = false;

static bool
  isActive_powerSave = true;

static power_current_mode_t
    currentPowerMode = POWER_CURRENT_MODE_NORMAL;

static power_sleep_mode_t
    selectedSleepMode = POWER_SLEEP_MODE_TOTAL;

static osa_status_t power_CreateBinSema(semaphore_t* semaphore );
static void power_TriggerTask();
static void power_Task( void* param );
static power_status_t power_PutMCUToSleep();

/** status flags */

static bool
	isPowerActive_OLED    = false,
	isPowerActive_HTU_TSL = false,
	isPowerActive_BATTERY = false,
	isPowerActive_MAXIM   = false;

/** flags to track who puts the MCU to sleep and wakes it up */

static power_sleep_src_t
    currentSleepSrc = POWER_SLEEP_SRC_NONE;

static power_wake_src_t
    currentWakeSrc = POWER_WAKE_SRC_NONE;

static bool
	isActive_Sleep = false;

#define PWR_HTU_TSL_TurnON()  GPIO_DRV_ClearPinOutput( PWR_SENSORS_NF ); OSA_TimeDelay( 50 ); isPowerActive_HTU_TSL = true
#define PWR_HTU_TSL_TurnOFF() isPowerActive_HTU_TSL = false; GPIO_DRV_SetPinOutput( PWR_SENSORS_NF )

#define PWR_HR_TurnON()  GPIO_DRV_SetPinOutput( PWR_HR ); OSA_TimeDelay( 50 ); isPowerActive_MAXIM = true
#define PWR_HR_TurnOFF() isPowerActive_MAXIM = false; GPIO_DRV_ClearPinOutput( PWR_HR )

#define PWR_BATT_TurnON()  GPIO_DRV_ClearPinOutput( PWR_BAT_SENS ); OSA_TimeDelay( 50 ); isPowerActive_BATTERY = true
#define PWR_BATT_TurnOFF() isPowerActive_BATTERY = false; GPIO_DRV_SetPinOutput( PWR_BAT_SENS )

#define PWR_OLED_TurnON()  GPIO_DRV_SetPinOutput( PWR_OLED ); OSA_TimeDelay( 50 ); isPowerActive_OLED = true
#define PWR_OLED_TurnOFF() isPowerActive_OLED = false; GPIO_DRV_ClearPinOutput( PWR_OLED )

task_handler_t
  power_handler;

/**
 * initialize the power task and relevant power objects
 * @return status flag
 */
power_status_t power_Init()
{
  if ( kStatus_OSA_Success != OSA_SemaCreate( &power_sema, 0 ) )
  {
	  return POWER_STATUS_ERROR;
  }

  if ( kStatus_OSA_Success != power_CreateBinSema( &power_wakeSrcSema ) )
  {
	  return POWER_STATUS_ERROR;
  }

  if ( kStatus_OSA_Success != power_CreateBinSema( &power_STSema ) )
  {
	  return POWER_STATUS_ERROR;
  }

  osa_status_t
    status = OSA_TaskCreate (
                              power_Task,
                              (uint8_t *) "Active power management",
                              POWER_STACK_SIZE,
                              NULL,
						                  HEXIWEAR_STARTUP_PRIO,
                              (task_param_t)0,
                              false,
                              &power_handler
                            );

  if ( kStatus_OSA_Success != status )
  {
    return POWER_STATUS_ERROR;
  }
  else
  {
    return POWER_STATUS_SUCCESS;
  }
}

/**
 * return power flags
 * @param peripheral peripheral which flags to return
 * @return flag
 */
bool power_IsActive( power_peripheral_t peripheral )
{
    switch ( peripheral )
    {
        case POWER_OLED:
        {
            return isPowerActive_OLED;
            break;
        }

        case POWER_HTU_TSL:
        {
            return isPowerActive_HTU_TSL;
            break;
        }

        case POWER_MAXIM:
        {
            return isPowerActive_MAXIM;
            break;
        }

        case POWER_BATTERY:
        {
            return isPowerActive_BATTERY;
            break;
        }

        default:
        {
            return false;
        }
    }
}

/**
 * turn the selected peripheral ON
 * @param  peripheral peripheral to turn on
 * @return            status flag
 */
power_status_t power_TurnON ( power_peripheral_t peripheral )
{
  switch ( peripheral )
  {
    case POWER_OLED:
    {
        PWR_OLED_TurnON();
        break;
    }

    default: {}
  }

  return POWER_STATUS_SUCCESS;
}

/**
 * turn the selected peripheral OFF
 * @param  peripheral peripheral to turn off
 * @return            status flag
 */
power_status_t power_TurnOFF( power_peripheral_t peripheral )
{
  switch ( peripheral )
  {
    case POWER_OLED:
    {
        PWR_OLED_TurnOFF();
        break;
    }
    default: {}
  }

  return POWER_STATUS_SUCCESS;
}

/**
 * put HEXIWEAR to sleep
 * @return status flag
 */
static power_status_t power_Sleep()
{
    // check the current power state
    power_manager_modes_t
        powerMode = POWER_SYS_GetCurrentMode();

    /** proceed with going to sleep only if we're in RUN mode */
    if ( kPowerManagerRun == powerMode )
    {
    	power_status_t
    		sleepStatus = POWER_STATUS_SUCCESS;

        switch ( selectedSleepMode )
        {
			/**
			 * in case of shallow sleep mode,
			 * just turn off the OLED
			 */
			case POWER_SLEEP_MODE_SHALLOW:
			{
			  // turn OLED off
			  power_TurnScreenOFF();

			  currentPowerMode = POWER_CURRENT_MODE_SLEEP_SHALLOW;
			  return POWER_STATUS_SUCCESS;
			}

			/**
			* if the sleep mode has been initiated by RTC, go to total sleep:
			* shutdown sensors, screen and put the core to deep sleep
			*/
			case POWER_SLEEP_MODE_TOTAL:
			{
				if ( true == isPowerActive_MAXIM )
				{
					PWR_HR_TurnOFF();
				}
				if ( true == isPowerActive_HTU_TSL )
				{
					PWR_HTU_TSL_TurnOFF();
				}
				if ( true == isPowerActive_BATTERY )
				{
					PWR_BATT_TurnOFF();
				}

				// turn OLED off
				power_TurnScreenOFF();

				currentPowerMode = POWER_CURRENT_MODE_SLEEP_TOTAL;
				break;
			}

			/**
 			 * if the sleep mode has been requested while in sensor tag mode,
			 * shutdown the screen initially and then go to sleep
			 */
			case POWER_SLEEP_MODE_SENSOR_TAG:
			{
				/** current power mode flag has been already set, so no need to do it here */
//				currentPowerMode = POWER_CURRENT_MODE_SLEEP_SENSOR_TAG;
				power_TurnScreenOFF();
				break;
            }
        }

        // go to sleep
	    if ( POWER_STATUS_SUCCESS != power_PutMCUToSleep() )
	    {
	    	/**
	    	 * if going to sleep didn't work,
	    	 * act like user woke up the MCU
	    	 */

            RTC_UpdateAlarm();
            power_TurnScreenON();

	    	currentWakeSrc   = POWER_WAKE_SRC_USER;
	    	currentPowerMode = POWER_CURRENT_MODE_NORMAL;
	    	sleepStatus      = POWER_STATUS_INIT_ERROR;
	    }

        while ( POWER_WAKE_SRC_NONE == currentWakeSrc ) {}

        /**
         * let's see what's next, since it depends
         * on the peripheral that has awaken the MCU
         */

        switch ( currentWakeSrc )
        {
            case POWER_WAKE_SRC_NONE:
            {
                 // shouldn't happen
                break;
            }

            case POWER_WAKE_SRC_USER:
            {
                switch ( power_GetSleepMode() )
                {
                    case POWER_SLEEP_MODE_SHALLOW:
                    {
                        break;
                    }

                    /**
                     * if we're about leave the total sleep mode,
                     * turn sensors' power supplies on, if they were turned off
                     * before entering
                     */

                    case POWER_SLEEP_MODE_TOTAL:
                    {
                        currentPowerMode = POWER_CURRENT_MODE_NORMAL;

						if ( true == isPowerActive_MAXIM )
						{
							PWR_HR_TurnON();
						}
						if ( true == isPowerActive_HTU_TSL )
						{
							PWR_HTU_TSL_TurnON();
						}
						if ( true == isPowerActive_BATTERY )
						{
							PWR_BATT_TurnON();
						}

                        break;
                    }

                    case POWER_SLEEP_MODE_SENSOR_TAG:
                    {
                        break;
                    }
                }

                break;
            }

            case POWER_WAKE_SRC_SENSOR_TIMER:
            {
                /**
                 * do nothing,
                 * as we'll re-enter the sleep soon enough
                 */
                break;
            }
        }

        return sleepStatus;
    }

    else
    {
        /**
         * shouldn't happen,
         * we should always use run configuration
         */

        catch( CATCH_POWER );
        return POWER_STATUS_ERROR;
    }
}

/**
 * put MCU to VLPS mode,
 * enable/disable possible interrupts
 * @return status flag
 */
static power_status_t power_PutMCUToSleep()
{
    bool
        sensorTimerState = false;

    /** check for active communication */

    /** I2C */

    i2c_status_t
      currentStatus;

    uint32_t
      rxBytesRemaining = 0,
      txBytesRemaining = 0;

    for ( uint8_t i2cIdx = 0; i2cIdx < 2; i2cIdx++ )
    {
        currentStatus = kStatus_I2C_Success;
        currentStatus |= I2C_DRV_MasterGetSendStatus   ( i2cIdx, &txBytesRemaining );
        currentStatus |= I2C_DRV_MasterGetReceiveStatus( i2cIdx, &rxBytesRemaining );
        if  (
                    ( kStatus_I2C_Success == currentStatus )
                &&  ( 0 != ( txBytesRemaining + rxBytesRemaining ) )
            )
        {
            return POWER_STATUS_INIT_ERROR;
        }
    }

    /** UART */

    // ...

    switch ( currentPowerMode )
    {
        case POWER_CURRENT_MODE_NORMAL:
        case POWER_CURRENT_MODE_SLEEP_SHALLOW:
        {
            // shouldn't happen
            catch( CATCH_POWER );
        }

        case POWER_CURRENT_MODE_SLEEP_TOTAL:
        {
            // check sensor timer's state to remember for later
            sensorTimerState = timer_IsActive( HEXIWEAR_TIMER_SENSOR );
            if ( true == sensorTimerState )
            {
            	timer_Stop( HEXIWEAR_TIMER_SENSOR );
            }
            break;
        }

        case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
        {
            // do nothing
            break;
        }
    }

	/**
	 * set the wake-up source to none,
	 * as it will be set by invoking the wake-up function in the appropriate interrupt handler
	 */

    if ( POWER_CURRENT_MODE_NORMAL != currentPowerMode )
    {
        // disable interrupts
        // asm(" CPSID i");

		/** put MCU to sleep (VLPS) */
		POWER_SYS_SetMode( 1, kPowerManagerPolicyAgreement );
		CLOCK_SYS_UpdateConfiguration( 0, kClockManagerPolicyForcible );

		OSA_TimeDelay(10);
		// GPIO_DRV_TogglePinOutput( KW40_WU );

		// enable interrupts
		// asm(" CPSIE i ");

//		rtc_datetime_t
//			tmpTime;
//		RTC_GetCurrentTime( &tmpTime );
//		RTC_TriggerAlarm( &tmpTime, 1 );
    }

    /**
     * MCU is now woken up,
     * undo all the power-save changes from the above
     */

    switch ( currentPowerMode )
    {
        case POWER_CURRENT_MODE_NORMAL:
        {
            RTC_EnableAlarm();
            RTC_UpdateAlarm();
            power_TurnScreenON();

            // if the timer was enabled before entering the sleep mode, enable it
            if ( true == sensorTimerState )
            {
                timer_Start( HEXIWEAR_TIMER_SENSOR );
            }

            break;
        }

        case POWER_CURRENT_MODE_SLEEP_SHALLOW:
        {
            // shouldn't happen
            catch( CATCH_POWER );
            break;
        }

        case POWER_CURRENT_MODE_SLEEP_TOTAL:
        {
            break;
        }

        case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
        {
            break;
        }
    }

    return POWER_STATUS_SUCCESS;
}

/** intern functions */

/**
 * create the semaphore for signallizing wake-up source
 * @param  semaphore pointer which should be pointed to the new semaphore
 * @return           status flag
 */
static osa_status_t power_CreateBinSema(semaphore_t* semaphore )
{
    assert( semaphore );

    *semaphore = xSemaphoreCreateCounting( 0x1, 0 );

    if ( NULL == *semaphore )
    {
        return kStatus_OSA_Error;
    }
    return kStatus_OSA_Success;
}

/**
 * trigger the power task
 * by filling the semaphore the task is blocked on
 */
static void power_TriggerTask()
{
	OSA_SemaPost( &power_sema );
}


/**
 * task in charge for putting HEXIWEAR to sleep
 * @param param optional parameter
 */
static void power_Task( void* param )
{
  while (1)
  {
	  osa_status_t
	  	  status = OSA_SemaWait( &power_sema, OSA_WAIT_FOREVER );

	  if ( kStatus_OSA_Success == status )
	  {
		  while ( POWER_STATUS_SUCCESS != power_Sleep() )
		  {
			  OSA_TimeDelay( 100 );
		  }
	  }
	  else
	  {
		  catch( CATCH_SEMAPHORE );
	  }
  }
}

/** public API */

/**
 * put HEXIWEAR to sleep
 */
void power_GotoSleep()
{
	if ( true == isActive_powerSave )
	{
		power_TriggerTask();
	}
}

/**
 * activate/deactivate power supplies for sensors
 */
void power_SensorManagement()
{
  /** humidity & ambient light */

  if ( PACKET_PUSH_NONE != ( sensor_GetPacketTargets( PACKET_HUM ) | sensor_GetPacketTargets( PACKET_TEMP ) | sensor_GetPacketTargets( PACKET_LUX ) ) )
  {
    if ( false == isPowerActive_HTU_TSL )
    {
      PWR_HTU_TSL_TurnON();
    }
  }

  else
  {
    if ( true == isPowerActive_HTU_TSL )
    {
      PWR_HTU_TSL_TurnOFF();
    }
  }

   /** MAXIM */

  if ( PACKET_PUSH_NONE != sensor_GetPacketTargets( PACKET_HR ) )
  {
    if ( false == isPowerActive_MAXIM )
    {
      PWR_HR_TurnON();
    }
  }

  else
  {
    if ( true == isPowerActive_MAXIM )
    {
      PWR_HR_TurnOFF();
    }
  }

   /** battery reading */

  if ( PACKET_PUSH_NONE != sensor_GetPacketTargets( PACKET_BAT ) )
  {
    if ( false == isPowerActive_BATTERY )
    {
      PWR_BATT_TurnON();
    }
  }

  else
  {
    if ( true == isPowerActive_BATTERY )
    {
      PWR_BATT_TurnOFF();
    }
  }
}

/**
 * set BLE_RST pin to 0 and then release it
 */
void power_ResetKW40()
{
	GPIO_DRV_ClearPinOutput( KW40_RST );
	OSA_TimeDelay( 10 );
	GPIO_DRV_SetPinOutput( KW40_RST );
	OSA_TimeDelay( 200 );
}

/**
 * enable the power save feature:
 * enable OLED
 * enable current sensor subscriptions
 */
void power_EnablePowerSave()
{
    RTC_EnableAlarm();
    isActive_powerSave = true;
}

/**
 * disable the power save feature:
 * disable OLED
 * disable current sensor subscriptions
 */
void power_DisablePowerSave()
{
    isActive_powerSave = false;
    RTC_DisableAlarm();
}

/**
 * set sleep source
 * @param sleepSrc entity which will put the MCU to sleep
 */
void power_SetSleepSource( power_sleep_src_t sleepSrc )
{
    currentSleepSrc = sleepSrc;
}

/**
 * get sleep source
 * @return current entity which will put the MCU to sleep
 */
power_sleep_src_t power_GetSleepSource()
{
    return currentSleepSrc;
}

/**
 * set wakeup source
 * @param wakeupSrc entity which will wake up the MCU
 */
power_status_t power_SetWakeSource( power_wake_src_t wakeSrc )
{
    if ( kStatus_OSA_Success == OSA_SemaWait( &power_wakeSrcSema, 0 ) )
    {
        currentWakeSrc = wakeSrc;
        return POWER_STATUS_SUCCESS;
    }
    else
    {
        return POWER_STATUS_ERROR;
    }
}

/**
 * get wakeup source
 * @return current entity which will wake up the MCU
 */
power_wake_src_t power_GetWakeSource()
{
    return currentWakeSrc;
}

/**
 * check if this was the touch that woken the MCU
 * @return touch flag
 */
bool power_HasJustExitSleep()
{
    return isActive_Sleep;
}

/**
 * set current HEXIWEAR mode
 * @param newMode mode to set
 */
void power_SetCurrentMode( power_current_mode_t newMode )
{
	if ( true == isActive_powerSave )
	{
		currentPowerMode = newMode;
	}
}

/**
 * get current HEXIWEAR mode
 * @return current mode
 */
power_current_mode_t power_GetCurrentMode()
{
    return currentPowerMode;
}

/**
 * set new power mode
 * @param new desired power mode
 */
void power_SetSleepMode( power_sleep_mode_t newMode )
{
	if ( true == isActive_powerSave )
	{
		selectedSleepMode = newMode;
	}
}

/**
 * get currently selected sleep mode
 * @return current sleep mode
 */
power_sleep_mode_t power_GetSleepMode()
{
    return selectedSleepMode;
}

/**
 * turn the screen off by sending the command
 * and turning off the power supply
 */
void power_TurnScreenOFF()
{
    if ( true == isPowerActive_OLED )
    {
        while ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE ) ) {}
        PWR_OLED_TurnOFF();

        GPIO_DRV_ClearPinOutput( KW40_GPIO );
    }
}

/**
 * turn the screen on by switching on the power supply
 * and sending the command
 */
void power_TurnScreenON()
{
    if ( false == isPowerActive_OLED )
    {
    	GPIO_DRV_TogglePinOutput( KW40_WU );
    	OSA_TimeDelay(10);
    	GPIO_DRV_SetPinOutput( KW40_GPIO );

        PWR_OLED_TurnON();
        while ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYON, FIRST_BYTE ) ) {}
    }
}

/**
 * fill the semaphore for wake-up sources to take
 * @return status flag
 */
power_status_t power_PostToSTSema()
{
	osa_status_t
		status = OSA_SemaPost( &power_STSema );

	if ( kStatus_OSA_Success == status )
	{
		return POWER_STATUS_SUCCESS;
	}
	else
	{
		return POWER_STATUS_ERROR;
	}
}

/**
 * take semaphore to signalize the wake-up happened
 * @return status flag
 */
power_status_t power_TakeFromSTSema()
{
	osa_status_t
			status = OSA_SemaWait( &power_STSema, 0 );

	if ( kStatus_OSA_Success == status )
	{
		return POWER_STATUS_SUCCESS;
	}
	else
	{
		return POWER_STATUS_ERROR;
	}
}

/**
 * send sleep ON/OFF packet to KW40
 * @param  sleepState desired sleep state
 * @return            status flag
 */
power_status_t power_AlertKW40( power_sleepState_t sleepState )
{
    hostInterface_packet_t
        sleepPacket =
        {
            .length = 0,
            .data[0] = gHostInterface_trailerByte
        };

    switch ( sleepState )
    {
        case POWER_SLEEP_STATE_ON:
        {
            sleepPacket.type = packetType_sleepON;
            break;
        }
        case POWER_SLEEP_STATE_OFF:
        {
            sleepPacket.type = packetType_sleepOFF;
            break;
        }
    }

    osa_status_t
        txStatus = HostInterface_TxQueueMsgPut( &sleepPacket, false );

    if ( kStatus_OSA_Success == txStatus )
    {
        return POWER_STATUS_SUCCESS;
    }

    else
    {
        catch( CATCH_QUEUE );
        return POWER_STATUS_ERROR;
    }
}

/**
 * call before entering sleep mode
 * @param notify optional parameters
 * @param callbackData optional parameters
 * @return status flag
 */
power_manager_error_code_t power_CallBeforeSleep(
													power_manager_notify_struct_t *notify,
													power_manager_callback_data_t* callbackData
												)
{
    currentWakeSrc = POWER_WAKE_SRC_NONE;

    /** enable UART edge interrupt circuit, */
    UART_WR_BDH_RXEDGIE( g_uartBase[ 4 ] , 1 );

    /** post to semaphore to make it available to interrupts */
    OSA_SemaPost( &power_wakeSrcSema );

	return kPowerManagerSuccess;
}

/**
 * call after exiting sleep mode
 * @param notify optional parameters
 * @param callbackData optional parameters
 * @return flag
 */
power_manager_error_code_t power_CallAfterSleep (
													power_manager_notify_struct_t *notify,
													power_manager_callback_data_t* callbackData
												)
{
    /** disable UART edge interrupt circuit */
    UART_WR_BDH_RXEDGIE( g_uartBase[4] , 0 );
    return kPowerManagerSuccess;
}

/**
 * check for battery status
 * @return status flag
 */
bool power_IsBatteryLow()
{
	return isBatteryLow;
}

/**
 * set battery status as low
 */
void power_SetBatteryLow()
{
	isBatteryLow = true;
}

/**
 * unset battery status as low
 */
void power_UnsetBatteryLow()
{
	isBatteryLow = false;
}
