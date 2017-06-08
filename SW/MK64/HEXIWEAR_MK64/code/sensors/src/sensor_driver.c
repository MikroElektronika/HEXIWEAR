/**
 * @file sensor_driver.c
 * @brief this file contains the code for general sensor manipulation and
 * general sensor data-flow in HEXIWEAR
 *
 * @version 1.00
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
 * Neither the name of NXP Semiconductor, Inc. nor the names of its
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
 * support: http://www.mikroe.com/forum and https://community.freescale.com
 *
 * Project HEXIWEAR, 2015
 */

#include "string.h"

#include "HEXIWEAR_info.h"

#include "GPIO.h"
#include "BATTERY_ADC.h"

#include "gui_driver.h"
#include "screens_common.h"

#include "sensor_driver.h"
#include "sensor_info.h"

#include "power_driver.h"

#include "pedometer_driver.h"

#include "OLED_info.h"
#include "OLED_driver.h"

#include "error.h"

#include "timer_driver.h"

#include "heartRate_driver.h"

#if defined( HEXIWEAR_DEBUG )
#include "fsl_uart_driver.h"
#include "DEBUG_UART.h"
#endif

/** intern types */

typedef enum
{
  SEND_YES,
  SEND_NO,
  SEND_TRY_AGAIN,
  SEND_SKIP

} send_t;

typedef enum
{

  TASK_RESUME,
  TASK_SUSPEND

} taskAction_t;

/** intern variables */

static bool
  isSensorTaskActive = true;

static uint32_t
	oldPeriodVal = 0,
	newPeriodVal = 0;

static uint32_t
  sensor_minDelay_ms = SENSOR_DEFAULT_MINIMUM_DELAY_MS;

static bool
  FXOS_firstTime = true,
  FXAS_firstTime = true,
  MPL_firstTime  = true;

static mutex_t
  taskAccessMutex;

static semaphore_t
	sensor_sema;

static uint8_t
    KW40_backupList[ PACKET_ALL ] = { 0 };

static uint8_t
  sensor_retryCnt = SENSOR_RETRY_NUM;

static uint16_t
	bat_mvolts = 0;

static uint32_t
	sensor_LEDCounter        = 1,
	sensor_LEDCounterInitVal = ( (1000*TIMER_BLINKING_PERIOD_MS) / (1000*SENSOR_DEFAULT_MINIMUM_DELAY_MS) ) - 1;

#define LED_DecrementCounter() sensor_LEDCounter = ( 0 == sensor_LEDCounter ) ? sensor_LEDCounterInitVal : sensor_LEDCounter-1
#define LED_HasCounterExpired() ( 0 == sensor_LEDCounter )

/** if the sensorTag mode is active, go to sleep instead of waiting or suspending the task */
#define sensor_GoToSleep()\
if ( true == power_IsTotalSleepModeActive() )\
{\
	power_SetSleepSource( POWER_SLEEP_SENSOR_TAG );\
	power_GotoStandby();\
}

// packet settings
static packet_settings_t
  packetSettings[ PACKET_ALL ] =
  {
    /** methods */

    #define packetSettings_HasTargets( packet )   ( PACKET_PUSH_NONE != packetSettings[ packet ].targets )
    #define packetSettings_HasNoTargets( packet ) ( PACKET_PUSH_NONE == packetSettings[ packet ].targets )

	#define packetSettings_IncrementCounter(packet) packetSettings[ packet ].counter += 1

    #define packetSettings_DecrementCounter(packet)\
      packetSettings[ packet ].counter = ( 0 == packetSettings[ packet ].counter ) ?\
                                           packetSettings[ packet ].initCounterVal :\
                                           packetSettings[ packet ].counter-1

    #define packetSettings_HasCounterExpired( packet ) ( 0 == ( packetSettings[ packet ].counter ) )

     /** members */

    /** PACKET_ACC */
    {
      .targets         = PACKET_PUSH_NONE,
      .defaultDelay_ms = ACC_DEFAULT_POLL_PERIOD_MS,
      .counter         = 1
    },

    /** PACKET_MAG */
    {
      .targets         = PACKET_PUSH_NONE,
      .defaultDelay_ms = MAG_DEFAULT_POLL_PERIOD_MS,
      .counter         = 1
    },

    /** PACKET_GYRO */
    {
      .targets         = PACKET_PUSH_NONE,
      .defaultDelay_ms = GYRO_DEFAULT_POLL_PERIOD_MS,
      .counter         = 1
    },

    /** PACKET_PRES */
    {
      .targets         = PACKET_PUSH_NONE,
      .defaultDelay_ms = PRES_DEFAULT_POLL_PERIOD_MS,
      .counter         = 1
    },

    /** PACKET_TEMP */
    {
      .targets         = PACKET_PUSH_NONE,
      .defaultDelay_ms = TEMP_DEFAULT_POLL_PERIOD_MS,
      .counter         = 1
    },

    /** PACKET_HUM */
    {
      .targets         = PACKET_PUSH_NONE,
      .defaultDelay_ms = HUM_DEFAULT_POLL_PERIOD_MS,
      .counter         = 1
    },

    /** PACKET_LUX */
    {
      .targets         = PACKET_PUSH_NONE,
      .defaultDelay_ms = LUX_DEFAULT_POLL_PERIOD_MS,
      .counter         = 1
    },

    /** PACKET_HR */
    {
      .targets         = PACKET_PUSH_NONE,
//      .defaultDelay_ms = HR_DEFAULT_POLL_PERIOD_MS,
      .counter         = 1
    },

    /** PACKET_BAT */
    {
      .targets         = PACKET_PUSH_NONE,
      .defaultDelay_ms = BAT_DEFAULT_POLL_PERIOD_MS,
      .counter         = 1
    }
  };

// sensors settings
static sensor_settings_t
  sensorSettings[ SENSOR_ALL ] =
  {

    /** methods */

    #define sensorSettings_IsActive( sensor )    ( true  == sensorSettings[ sensor ].isActive )
    #define sensorSettings_IsNotActive( sensor ) ( false == sensorSettings[ sensor ].isActive )

    #define sensorSettings_Activate( sensor )    ( sensorSettings[ sensor ].isActive = true )
    #define sensorSettings_Deactivate( sensor )  ( sensorSettings[ sensor ].isActive = false )

    /** members */

    // SENSOR_FXOS
    {
      .isActive = false
    },

    // SENSOR_FXAS
    {
      .isActive = false
    },

    // SENSOR_MPL
    {
      .isActive = false
    },

    // SENSOR_HTU
    {
      .isActive = false
    },

    // SENSOR_TSL
    {
      .isActive = false
    },

    // SENSOR_MAXIM
    {
      .isActive = false
    },

    // SENSOR_BATT
    {
      .isActive = false
    }
  };

/** helpful macros */

#define START_PACKET ( packetType_batteryLevel )
#define END_PACKET   ( packetType_steps )

#define NextSensor( sensor ) sensor = ( (++sensor) % END_PACKET ) + START_PACKET * ( sensor / END_PACKET )

#define ShouldSensorBeActivated( sensor, packet )   ( packetSettings_HasTargets( packet ) && sensorSettings_IsNotActive( sensor ) )
#define ShouldSensorBeDeactivated( sensor, packet ) ( packetSettings_HasNoTargets( packet ) && sensorSettings_IsActive( sensor ) )

#define registerFormatters( sensType )\
sensor_fmtDef2Float = sensType##_fmtDef2Float;\
sensor_fmtDef2Me    = sensType##_fmtDef2Me;\
sensor_fmtDef2Byte  = sensType##_fmtDef2Byte

/** private declarations */

static void sensor_PushData ( hostInterface_packet_t* dataPacket, packet_pushTarget_t pushTargets );
static void sensor_InitModules();
static void sensor_DeinitModules();
static void sensor_GetData( task_param_t param );

static uint32_t sensor_GetTimerPeriod();
static void sensor_SetTimerPeriod( uint32_t newPeriod );
static void sensor_UpdateTimer();

static sensor_status_t sensor_Wait();

static uint8_t GetActivePacketsNum();
static void UpdatePacketCounters();

static void bat_fmtDef2Float( const void* src, void* dst, uint32_t idx );
static void bat_fmtDef2Me   ( const void* src, void* dst, uint32_t idx );

static void bat_fmtDef2Byte( const void* src, void* dst, uint32_t idx );

static void sensor_ChangeTaskState( taskAction_t taskAction );

static osa_status_t sensor_CreateBinSema( semaphore_t* semaphore );

static bool sensor_AreThereNoTargets();

/** Public API */

/**
 * reset the packet counter, to trigger reading during the
 * next sensor loop
 * @param packetToUpdate packet to reset
 */
void sensor_ResetPacketcounter( packet_t packetToUpdate )
{
  packetSettings[ packetToUpdate ].counter = 1;
}

/**
 * set targets for the particular sensor packet
 * @param packetToUpdate packet which targets are to be updated
 * @param newPushTarget  new targets
 * @param shouldToggleTask  flag to check if sensor task should be triggered, if paused before
 */
void sensor_SetPacketTargets	(
									           packet_t packetToUpdate,
								    packet_pushTarget_t newPushTarget,
										   	   	   bool shouldToggleTask
                           	    )
{
  packetSettings[ packetToUpdate ].targets = newPushTarget;
  sensor_ResetPacketcounter( packetToUpdate );

  // update all counter initial values, according to new active packets
  UpdatePacketCounters();

  if ( true == shouldToggleTask )
  {
	  sensor_ChangeTaskState( TASK_RESUME );
  }
}

/**
 * [sensor_SetPushTargets  description]
 * @param  oldPushTargets [description]
 * @return                [description]
 */
packet_pushTarget_t sensor_GetPacketTargets ( packet_t oldPushTargets )
{
  return packetSettings[ oldPushTargets ].targets;
}

/**
 * create the sensor task
 */
osa_status_t sensor_Init()
{
	osa_status_t
		osaStatus = kStatus_OSA_Success;

	// create a mutex for controlling the access to toggling the task
	osaStatus = OSA_MutexCreate( &taskAccessMutex );

	if ( kStatus_OSA_Success != osaStatus )
	{
		catch( CATCH_MUTEX );
		return SENSOR_STATUS_ERROR;
	}

	// create a semaphore for signalizing when to acquire new sensor readings
	osaStatus = sensor_CreateBinSema( &sensor_sema );

	if ( kStatus_OSA_Success != osaStatus )
	{
		catch( CATCH_SEMAPHORE );
		return SENSOR_STATUS_ERROR;
	}

	osaStatus = OSA_TaskCreate  (
									sensor_GetData,
									(uint8_t*)"Sensor Task Get Data",
									SENSOR_GET_DATA_STACK_SIZE,
									NULL,
									SENSOR_GET_DATA_PRIO,
									(task_param_t)0,
									false,
									&hexiwear_sensor_TAG_handler
								);

	if ( kStatus_OSA_Success != osaStatus )
	{
		catch( CATCH_INIT );
		return SENSOR_STATUS_ERROR;
	}

	return osaStatus;
}

/**
 * check is there are any flags active
 * @return true, if there are no active targets
 */
static bool sensor_AreThereNoTargets()
{
	bool
		confirmDestroy = true;

	for ( packet_t pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
	{
		if packetSettings_HasTargets( pktIdx )
		{
		  confirmDestroy = false;
		  break;
		}
	}

	return confirmDestroy;
}

/**
 * intern functions
 */

static osa_status_t sensor_CreateBinSema(semaphore_t* semaphore )
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
 * pause/resume the sensor task,
 * depending on the active sensors
 */
static void sensor_ChangeTaskState( taskAction_t taskAction )
{
    osa_status_t
        mutexStatus = OSA_MutexLock( &taskAccessMutex, OSA_WAIT_FOREVER );

    if ( kStatus_OSA_Success == mutexStatus )
    {
		 /** check for the current flag state */
		bool
			confirmDestroy = sensor_AreThereNoTargets();

		switch( taskAction )
		{
		  /**
		   * if the task is to be suspended, the correct sequence is:
		   * init/deinit -> power supply on/off -> suspend
		   */

		  case TASK_SUSPEND:
		  {
			sensor_InitModules();
			sensor_DeinitModules();

			power_SensorManagement();

			  if ( true == confirmDestroy )
			  {
				  OSA_MutexUnlock( &taskAccessMutex );
				  sensor_Suspend();
			  }

			  break;
		  }

		  /**
		   * if the task is to be resumed, the sequence is:
		   * power supply on/off -> resume -> init/deinit
		   * (the last step will occur during the task execution)
		   */
		  case TASK_RESUME:
		  {
			power_SensorManagement();

			  if ( false == confirmDestroy )
			  {
				  sensor_Resume();
			  }

			  break;
		  }

		  default: {}
		}
    }

    else
    {
    	catch( CATCH_MUTEX );
    }

    OSA_MutexUnlock( &taskAccessMutex );
}

/**
 * format sensor data to various formats
 * @param sensorData data to format
 * @param fmtOptions options include:
 *                   - type of given data
 *                   - original format
 *                   - new desired format
 */
static void sensor_FormatData(
                                  const void* src,
                                        void* dst,
                                const uint8_t fmtOptions
                              )
{
  uint8_t
    // data length
    dataLen,
    // fmtOptions bit-field [3:0] - sensor type
    dataType      = Extract( fmtOptions, DATA_TYPE ),
    // fmtOptions bit-field [5:4] - old format
    oldDataFormat = Extract( fmtOptions, DATA_FORMAT_FROM ),
    // fmtOptions bit-field [7:6] - new format
    newDataFormat = Extract( fmtOptions, DATA_FORMAT_TO );

  /**
   * register formatting functions
   * determine data length
   */
  dataLen = TypeMember_SCALAR;
  switch ( dataType )
  {
    /**
     * battery level
     */

    case DATA_TYPE_BATTERYLEVEL:  {
                                    registerFormatters(bat);
                                    dataLen = TypeMember_SCALAR;
                                    break;
                                  }

    /**
     * motion data
     */

    case DATA_TYPE_ACCEL: {
                            registerFormatters(acc);
                            dataLen = TypeMember_NumEl( motionData_t, accData );
                            break;
                          }

    case DATA_TYPE_MAG:   {
                            registerFormatters(mag);
                            dataLen = TypeMember_NumEl( motionData_t, magData );
                            break;
                          }

    case DATA_TYPE_GYRO:  {
                            registerFormatters(gyro);
                            dataLen = TypeMember_NumEl( motionData_t, gyroData );
                            break;
                          }

    /**
     * weather data
     */

    case DATA_TYPE_AMBI:  {
                            registerFormatters(ambi);
//                            dataLen = TypeMember_NumEl( weatherData_t, ambiData );
                            dataLen = TypeMember_SCALAR;
                            break;
                          }

    case DATA_TYPE_TEMP:  {
                            registerFormatters(temp);
                            dataLen = TypeMember_SCALAR;
                            break;
                          }

    case DATA_TYPE_HUMID: {
                            registerFormatters(hum);
                            dataLen = TypeMember_SCALAR;
                            break;
    }

    case DATA_TYPE_PRES:  {
                            registerFormatters(pres);
                            dataLen = TypeMember_SCALAR;
                            break;
                          }

    /**
     * health data
     */

    case DATA_TYPE_HR:    {
//                            registerFormatters(hr);
                            dataLen = TypeMember_SCALAR;
							break;
//                            break;
                          }

    case DATA_TYPE_STEPS:    { break; }
    case DATA_TYPE_CALORIES: { break; }

    default:
    {
    	// to bypass the warning
    	dataLen = TypeMember_SCALAR;
    }
  }

  /**
   * format data to its new format
   */

  switch ( oldDataFormat )
  {
    case DATA_FORMAT_FROM_DEFAULT:  {
                                      switch (newDataFormat)
                                      {
                                        case DATA_FORMAT_TO_DEFAULT: { break; }

                                        case DATA_FORMAT_TO_BYTE:       {
                                                                        for ( uint8_t idx = 0; idx < dataLen; idx++ )
                                                                        {
                                                                          sensor_fmtDef2Byte(src, dst, idx);
                                                                        }

                                                                        break;
                                                                      }

                                        case DATA_FORMAT_TO_mE:       {
                                                                        for ( uint8_t idx = 0; idx < dataLen; idx++ )
                                                                        {
                                                                          sensor_fmtDef2Me(src, dst, idx);
                                                                        }

                                                                        break;
                                                                      }

                                        case DATA_FORMAT_TO_FLOAT:    {
                                                                        for ( uint8_t idx = 0; idx < dataLen; idx++ )
                                                                        {
                                                                          sensor_fmtDef2Float(src, dst, idx);
                                                                        }

                                                                        break;
                                                                      }

                                        default: {}
                                      }

                                      break;
                                    }

    case DATA_FORMAT_FROM_FLOAT:  {
                                    switch ( newDataFormat )
                                    {
                                      case DATA_FORMAT_TO_DEFAULT:  { break; }
                                      case DATA_FORMAT_TO_FLOAT:    { break; }
                                      case DATA_FORMAT_TO_mE:       { break; }
                                      default: {}
                                    }

                                    break;
                                  }

    case DATA_FORMAT_FROM_mE:     {
                                    switch (newDataFormat)
                                    {
                                      case DATA_FORMAT_TO_DEFAULT:  { break; }
                                      case DATA_FORMAT_TO_FLOAT:    { break; }
                                      case DATA_FORMAT_TO_mE:       { break; }
                                      default: {}
                                    }

                                    break;
                                  }
    default: {}
  }
}

/**
 * retrieve data from various sensors
 * @param param task parameter, currently unused
 */
static void sensor_GetData( task_param_t param )
{
    // data packet to be sent
    hostInterface_packet_t
        sensorPacket;

    // use this to announce if the packet is ready to be sent
    send_t
        isReadyToSend = SEND_NO;

    // packet type
    hostInterface_packetType_t
        sensorToSend = START_PACKET;

    // formatting options
    uint8_t
        fmtOptions = 0;

    // battery level
    uint16_t
        adcData  = 0;

    void
        *dataStart = NULL;

    packet_pushTarget_t
        pushTargets;

    /**
     * format for all the data: RAW -> mE or byte
     */
    Write( fmtOptions, DATA_FORMAT_FROM, DATA_FORMAT_FROM_DEFAULT );

    while (1)
    {
        sensor_UpdateTimer();
        Write( fmtOptions, DATA_FORMAT_TO, DATA_FORMAT_TO_mE );

    	/**
    	 * (de)initialize appropriate sensors, power supplies,
    	 * suspend the task, if appropriate
    	 */

        sensor_ChangeTaskState( TASK_SUSPEND );
	    isReadyToSend = SEND_NO;

        /**
         * prepare the data packet
         */

        sensorPacket.type = sensorToSend;

        /**
         * read, format and insert data into the packet
         */

        switch ( sensorToSend )
        {
            /**
            * Battery level
            */

            case packetType_batteryLevel:
            {
                if ( packetSettings_HasTargets( PACKET_BAT ) )
                {
                    packetSettings_DecrementCounter( PACKET_BAT );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_BAT ) )
                    {
                        ADC16_DRV_ConfigConvChn( FSL_BATTERY_ADC, 0, &BATTERY_ADC_ChnConfig);
                        ADC16_DRV_WaitConvDone ( FSL_BATTERY_ADC, 0 );
                        adcData = ADC16_DRV_GetConvValueSigned( FSL_BATTERY_ADC, 0 );
                        ADC16_DRV_PauseConv(FSL_BATTERY_ADC, 0 );

                        dataStart           = (void*)&( adcData );
                        sensorPacket.length = TypeMember_SCALAR;
                        pushTargets         = packetSettings[ PACKET_BAT ].targets;
                        isReadyToSend       = SEND_YES;
                        sensor_retryCnt     = SENSOR_RETRY_NUM;
                    }
                    else
                    {
                        asm("nop");
                    }
                }
                break;
            }

            /**
             * MOTION
             */

            case packetType_accel:
            {
#if defined( SENSOR_FXOS_PRESENT )
                if ( packetSettings_HasTargets( PACKET_ACC ) )
                {
                    packetSettings_DecrementCounter( PACKET_ACC );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_ACC ) )
                    {
                        fxos_status_t
                            fxosStatus;

                        if sensorSettings_IsActive( SENSOR_FXOS )
                        {
                            uint8_t
                              sensorStatus;

                            fxosStatus = FXOS_ReadStatus( &sensorStatus );

                            if ( 0x00 == sensorStatus )
                            {
                            	fxosStatus = STATUS_FXOS_ERROR;
                            }
                            else
                            {
                              // check also if tap is enabled
                              if ( false == FXOS_CheckForTap() )
                              {
                                fxosStatus = STATUS_FXOS_ERROR;
                              }
                              else
                              {
                            	  fxosStatus = FXOS_ReadRawData( (int16_t*)&motionData );
                              }
                            }
                        }
                        else
                        {
                            fxosStatus = STATUS_FXOS_INIT_ERROR;
                        }

                        if ( STATUS_FXOS_SUCCESS == fxosStatus )
                        {
                            dataStart           = (void*)&( motionData.accData[0] );
                            sensorPacket.length = TypeMember_NumEl( motionData_t , accData );
                            pushTargets         = packetSettings[ PACKET_ACC ].targets;
                            isReadyToSend       = SEND_YES;
                            sensor_retryCnt     = SENSOR_RETRY_NUM;
                        }

                        // try again, when the initialization is successful
                        else if ( STATUS_FXOS_INIT_ERROR == fxosStatus )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_ACC );
                        }

                        // else, report the error and eventually move on
                        else
                        {
                        	// check if I2C bus needs to be reset
                        	FXOS_RecoverI2C();

                            if ( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_ACC );
                                sensor_retryCnt--;
                            }
                            else
                            {
                            	FXOS_firstTime = true;
                                FXOS_SoftReset();
                                sensorSettings_Deactivate( SENSOR_FXOS );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                catch( CATCH_MOTION );
                            }
                        }
                    }
                }
#endif
                break;
            }

            case packetType_magnet:
            {
#if defined( SENSOR_FXOS_PRESENT )
                if ( packetSettings_HasTargets( PACKET_MAG ) )
                {
                    packetSettings_DecrementCounter( PACKET_MAG );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_MAG ) )
                    {
                        fxos_status_t
                            fxosStatus;

                        if sensorSettings_IsActive( SENSOR_FXOS )
                        {
                        	fxosStatus = FXOS_ReadRawData( (int16_t*)&motionData );
                        }
                        else
                        {
                        	fxosStatus = STATUS_FXOS_INIT_ERROR;
                        }

                        if ( STATUS_FXOS_SUCCESS == fxosStatus )
                        {
                            dataStart           = (void*)&( motionData.magData[0] );
                            sensorPacket.length = TypeMember_NumEl( motionData_t , magData );
                            pushTargets         = packetSettings[ PACKET_MAG ].targets;
                            isReadyToSend       = SEND_YES;
                            sensor_retryCnt     = SENSOR_RETRY_NUM;
                        }

                        // try again, when the initialization is successful
                        else if ( STATUS_FXOS_INIT_ERROR == fxosStatus )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_MAG );
                        }

                        // else, report the error and eventually move on
                        else
                        {
                            if ( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_MAG );
                                sensor_retryCnt--;
                            }
                            else
                            {
                            	FXOS_firstTime = true;
                                FXOS_SoftReset();
                                sensorSettings_Deactivate( SENSOR_FXOS );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                catch( CATCH_MOTION );
                            }
                        }
                    }
                }
#endif
                break;
            }

            case packetType_gyro:
            {
#if defined( SENSOR_FXAS_PRESENT )
                if ( packetSettings_HasTargets( PACKET_GYRO ) )
                {
                    packetSettings_DecrementCounter( PACKET_GYRO );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_GYRO ) )
                    {
                        fxas_status_t
                            fxasStatus;

                        if sensorSettings_IsActive( SENSOR_FXAS )
                        {
                        	fxasStatus = FXAS_ReadRawData( (int16_t*)&(motionData.gyroData[0]) );
                        }
                        else
                        {
                        	fxasStatus = STATUS_FXAS_INIT_ERROR;
                        }

                        if ( STATUS_FXAS_SUCCESS == fxasStatus )
                        {
                            dataStart           = (void*)&( motionData.gyroData[0] );
                            sensorPacket.length = TypeMember_NumEl( motionData_t , gyroData );
                            pushTargets         = packetSettings[ PACKET_GYRO ].targets;
                            isReadyToSend       = SEND_YES;
                            sensor_retryCnt     = SENSOR_RETRY_NUM;
                        }

                        // try again, when the initialization is successful
                        else if ( STATUS_FXAS_INIT_ERROR == fxasStatus )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_GYRO );
                        }

                        // else, report the error and eventually move on
                        else
                        {
                            if ( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_GYRO );
                                sensor_retryCnt--;
                            }
                            else
                            {
                            	FXAS_firstTime = true;
                                FXAS_SoftReset();
                                sensorSettings_Deactivate( SENSOR_FXAS );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                catch( CATCH_MOTION );
                            }
                        }
                    }
                }
#endif
                break;
            }

            /**
             * WEATHER
             */

            case packetType_temperature:
            {
#if defined( SENSOR_HTU_PRESENT )
                if ( packetSettings_HasTargets( PACKET_TEMP ) )
                {
                    packetSettings_DecrementCounter( PACKET_TEMP );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_TEMP ) )
                    {
                        htu_status_t
                            htuStatus;

                        if sensorSettings_IsActive( SENSOR_HTU )
                        {
                            htuStatus = HTU_GetTemp( (int16_t*)&(weatherData.tempData) );
                        }
                        else
                        {
                            htuStatus = STATUS_HTU_INIT_ERROR;
                        }

                        if ( STATUS_HTU_SUCCESS == htuStatus )
                        {
                            dataStart           = (void*)&( weatherData.tempData );
                            sensorPacket.length = TypeMember_SCALAR;
                            pushTargets         = packetSettings[ PACKET_TEMP ].targets;
                            isReadyToSend       = SEND_YES;
                            sensor_retryCnt     = SENSOR_RETRY_NUM;
                        }

                        // try again, when the initialization is successful
                        else if ( STATUS_HTU_INIT_ERROR == htuStatus )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_TEMP );
                        }

                        // else, report the error and eventually move on
                        else
                        {
                            if ( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_TEMP );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                HTU_SoftReset();
                                sensorSettings_Deactivate( SENSOR_HTU );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                catch( CATCH_WEATHER );
                            }
                        }
                    }
                }
#endif
                break;
            }

            case packetType_humidity:
            {
#if defined( SENSOR_HTU_PRESENT )
                if ( packetSettings_HasTargets( PACKET_HUM ) )
                {
                    packetSettings_DecrementCounter( PACKET_HUM );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_HUM ) )
                    {
                        htu_status_t
                            htuStatus;

                        if sensorSettings_IsActive( SENSOR_HTU )
                        {
                	        htuStatus = HTU_GetHum( (int16_t*)&(weatherData.humidData) );

                            // if read 0, try again
                            if ( 0 == weatherData.humidData )
                            {
                            	htuStatus = STATUS_HTU_ERROR;
                            }
                        }
                        else
                        {
                	        htuStatus = STATUS_HTU_INIT_ERROR;
                        }

                        if ( STATUS_HTU_SUCCESS == htuStatus )
                        {
                            dataStart           = (void*)&( weatherData.humidData );
                            sensorPacket.length = TypeMember_SCALAR;
                            pushTargets         = packetSettings[ PACKET_HUM ].targets;
                            isReadyToSend       = SEND_YES;
                            sensor_retryCnt     = SENSOR_RETRY_NUM;
                        }

                        // try again, when the initialization is successful
                        else if ( STATUS_HTU_INIT_ERROR == htuStatus )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_HUM );
                        }

                        // else, report the error and eventually move on
                        else
                        {
                        	// check if I2C bus needs to be reset
                        	HTU_RecoverI2C();

                            if ( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_HUM );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                HTU_SoftReset();
                                sensorSettings_Deactivate( SENSOR_HTU );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                catch( CATCH_WEATHER );
                            }
                        }
                    }
                }
#endif
                break;
            }

            case packetType_pressure:
            {
#if defined( SENSOR_MPL_PRESENT )
                if ( packetSettings_HasTargets( PACKET_PRES ) )
                {
                    packetSettings_DecrementCounter( PACKET_PRES );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_PRES ) )
                    {
                        mpl_status_t
                            mplStatus;

                        if sensorSettings_IsActive( SENSOR_MPL )
                        {
                    	    mplStatus = MPL_ReadRawData( MPL_MODE_PRESSURE, (int16_t*)&(weatherData.presAltData) );
                        }
                        else
                        {
                    	    mplStatus = STATUS_MPL_INIT_ERROR;
                        }

                        if ( STATUS_MPL_SUCCESS == mplStatus )
                        {
                            dataStart           = (void*)&( weatherData.presAltData );
                            sensorPacket.length = TypeMember_SCALAR;
                            pushTargets         = packetSettings[ PACKET_PRES ].targets;
                            isReadyToSend       = SEND_YES;
                            sensor_retryCnt     = SENSOR_RETRY_NUM;
                        }

                        // try again, when the initialization is successful
                        else if ( STATUS_MPL_INIT_ERROR == mplStatus )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_PRES );
                        }

                        // else, report the error and eventually move on
                        else
                        {
                            if ( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_PRES );
                                sensor_retryCnt--;
                            }
                            else
                            {
                            	MPL_firstTime = true;
                                MPL_SoftReset();
                                sensorSettings_Deactivate( SENSOR_MPL );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                catch( CATCH_WEATHER );
                            }
                        }
                    }
                }
#endif
                break;
            }

            case packetType_ambiLight:
            {
#if defined( SENSOR_TSL_PRESENT)
                if ( packetSettings_HasTargets( PACKET_LUX ) )
                {
                    packetSettings_DecrementCounter( PACKET_LUX );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_LUX ) )
                    {
                        tsl_status_t
                            tslStatus = STATUS_TSL_SUCCESS;
                        uint32_t
                            luxVal;
                        uint16_t
                            TSL_adcData[2];

                        if sensorSettings_IsActive( SENSOR_TSL )
                        {
                            tslStatus |= TSL_ReadRawData( TSL_CHANNEL_FULL,     &(TSL_adcData[0]) );
                            tslStatus |= TSL_ReadRawData( TSL_CHANNEL_INFRARED, &(TSL_adcData[1]) );
                        }
                        else
                        {
                            tslStatus = STATUS_TSL_INIT_ERROR;
                        }


                        if ( STATUS_TSL_SUCCESS == tslStatus )
                        {
                            tslStatus = TSL_CalculateLux( &( TSL_adcData[0] ), &luxVal );
                            TSL_FormatLux( luxVal, &( weatherData.ambiData ) );

                            Write( fmtOptions, DATA_FORMAT_TO, DATA_FORMAT_TO_BYTE );
                            dataStart = (void*)&( weatherData.ambiData );
                            sensorPacket.length = TypeMember_SCALAR;
                            pushTargets         = packetSettings[ PACKET_LUX ].targets;
                            isReadyToSend       = SEND_YES;
                            sensor_retryCnt     = SENSOR_RETRY_NUM;
                        }

                        // try again, when the initialization is successful
                        else if ( STATUS_TSL_INIT_ERROR == tslStatus )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_LUX );
                        }

                        // else, report the error and eventually move on
                        else
                        {
                            if ( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_LUX );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                catch( CATCH_WEATHER );
                            }
                        }
                    }
                }
#endif
                break;
            }

            case packetType_heartRate:
            {
#if defined(SENSOR_MAXIM_PRESENT)
                if ( packetSettings_HasTargets( PACKET_HR ) )
                {
                    packetSettings_DecrementCounter( PACKET_HR );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_HR ) )
                    {
                        maxim_status_t
                            maximStatus;

                        if sensorSettings_IsActive( SENSOR_MAXIM )
                        {
                            maximStatus = MAXIM_ReadRawData( NULL, NULL );
                        }
                        else
                        {
                            maximStatus = STATUS_MAXIM_INIT_ERROR;
                        }

                        if  ( STATUS_MAXIM_SUCCESS == maximStatus )
                        {
                        	// ...
                        }

                        else if ( STATUS_MAXIM_INIT_ERROR == maximStatus )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_HR );
                        }

                        else
                        {
                            isReadyToSend = SEND_NO;
                            catch( CATCH_HEALTH );
                        }
                    }
                }
#endif
                break;
            }
            default: {}
        }

        /** blink a LED if needed */

        if ( SEND_NO != isReadyToSend )
        {
			LED_DecrementCounter();
			if ( LED_HasCounterExpired() )
			{
				if ( false == flashlight_isFlashlightOn() )
				{
					switch ( power_GetCurrentMode() )
					{
						/** in normal or shallow sleep case, blink normally */
						case POWER_CURRENT_MODE_NORMAL:
						case POWER_CURRENT_MODE_SLEEP_SHALLOW:
						{
							if ( true == power_IsBatteryLow() )
							{
								RED_LED_ON();
								OSA_TimeDelay(10);
								RED_LED_OFF();
							}
							else if (
											( true == gui_sensorTag_IsActive() )
										&& 	( linkState_connected == watch_CurrentLinkStateGet() )
									)
							{
							    BLUE_LED_ON();
							    OSA_TimeDelay(10);
							    BLUE_LED_OFF();
							}
							break;
						}

						/** blink BLUE or RED, depending on the battery state */
						case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
						{
							if ( true == power_IsBatteryLow() )
							{
								RED_LED_ON();
								OSA_TimeDelay(10);
								RED_LED_OFF();
							}
							else
							{
								BLUE_LED_ON();
								OSA_TimeDelay(10);
								BLUE_LED_OFF();
							}

							break;
						}

						/** do nothing */
						case POWER_CURRENT_MODE_SLEEP_TOTAL:
						{
							break;
						}
					}
				}
			}
        }

        /**
         * finish with packet formation and push the packet
         */

        switch( isReadyToSend )
        {
            case SEND_YES:
    		{
                switch ( Extract( fmtOptions, DATA_FORMAT_TO ) )
                {
                    case DATA_FORMAT_TO_DEFAULT:
                    {
                        break;
                    }

                    case DATA_FORMAT_TO_BYTE:
                    {
        			    sensorPacket.length *= sizeof( uint8_t );
            		    break;
        	       	}

                    case DATA_FORMAT_TO_mE:
                    {
                        sensorPacket.length *= sizeof( mE_t );
                        break;
                    }

                    case DATA_FORMAT_TO_FLOAT:
                    {
                        sensorPacket.length *= sizeof( float );
                        break;
                    }

                    default: {}
                }

                // format data
                Write( fmtOptions, DATA_TYPE, sensorToSend );
                sensor_FormatData   (
                                        dataStart,
                                        (void*)&( sensorPacket.data[0] ),
                                        fmtOptions
                                    );

                // add trailer byte, denoting the packet end
                sensorPacket.data[ sensorPacket.length ] = gHostInterface_trailerByte;

                // push data
                sensor_PushData( &sensorPacket , pushTargets );

                // wait
                sensor_Wait();

                // goto next sensor
                NextSensor(sensorToSend);
                break;
            }

            case SEND_SKIP:
            {
    		    switch( power_GetCurrentMode() )
    		    {
    		    	case POWER_CURRENT_MODE_NORMAL:
    		    	case POWER_CURRENT_MODE_SLEEP_SHALLOW:
    		    	{
                        // wait
    					sensor_Wait();
    		    		break;
    		    	}

    		    	case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
    		    	{
                		power_SetSleepSource( POWER_SLEEP_SRC_SENSOR_TAG );
                		power_GotoSleep();
                		sensor_Wait();
    		    		break;
    		    	}

    		    	case POWER_CURRENT_MODE_SLEEP_TOTAL:
    		    	{
    		    		// shouldn't be here
    		    		break;
    		    	}
    		    }

                // goto next sensor
                NextSensor(sensorToSend);
    		    break;
            }

            case SEND_NO:
            {
          		// goto next sensor
          		NextSensor(sensorToSend);
          		break;
      	    }

            case SEND_TRY_AGAIN:
            {
                // try again to read the same sensor
                break;
            }
        }
    }
}

void sensor_InitAcc()
{
	fxos_status_t
		fxosStatus = FXOS_Init( &fxosModule, &fxosSettings );

	if ( STATUS_FXOS_SUCCESS != fxosStatus )
	{
	  catch( CATCH_INIT );
	}
	else
	{
	  sensorSettings_Activate( SENSOR_FXOS );
	  if ( true == FXOS_firstTime )
	  {
		  FXOS_firstTime = false;
	  }
	}
}
/**
 * initialize sensors' modules
 */
static void sensor_InitModules()
{
  /**
   * toggle the power supply for:
   * - non-NXP sensors
   * - heart-rate sensor
   */

#if defined( SENSOR_FXOS_PRESENT )
  if  (
           ShouldSensorBeActivated( SENSOR_FXOS, PACKET_ACC )
        || ShouldSensorBeActivated( SENSOR_FXOS, PACKET_MAG )
      )
  {
    fxos_status_t
      fxosStatus = STATUS_FXOS_SUCCESS;

    if ( true == FXOS_firstTime )
    {
      fxosStatus = FXOS_Init( &fxosModule, &fxosSettings );
    }
//    else
//    {
//      fxosStatus = FXOS_SetActive();
//    }

    if ( STATUS_FXOS_SUCCESS != fxosStatus )
    {
      catch( CATCH_INIT );
    }
    else
    {
      sensorSettings_Activate( SENSOR_FXOS );
      if ( true == FXOS_firstTime )
      {
        FXOS_firstTime = false;
      }
    }
  }
#endif

#if defined( SENSOR_FXAS_PRESENT )
  if ( ShouldSensorBeActivated( SENSOR_FXAS, PACKET_GYRO ) )
  {
    fxas_status_t
	fxasStatus = STATUS_FXAS_SUCCESS;

    if ( true == FXAS_firstTime )
    {
      fxasStatus = FXAS_Init( &fxasModule, &fxasSettings );
    }
    else
    {
      fxasStatus = FXAS_SetActive();
    }

    if ( STATUS_FXAS_SUCCESS != fxasStatus )
    {
      catch( CATCH_INIT );
    }
    else
    {
      sensorSettings_Activate( SENSOR_FXAS );
      if ( true == FXAS_firstTime )
      {
        FXAS_firstTime = false;
      }
    }
  }
#endif

#if defined( SENSOR_MPL_PRESENT )
  if  ( ShouldSensorBeActivated( SENSOR_MPL, PACKET_PRES ) )
  {
    mpl_status_t
      mplStatus = STATUS_MPL_SUCCESS;

    if ( true == MPL_firstTime )
    {
      mplStatus = MPL_Init( &mplModule, &mplSettings );
    }
    else
    {
      mplStatus = MPL_SetActive();
    }

    if ( STATUS_MPL_SUCCESS != mplStatus )
    {
      catch( CATCH_INIT );
    }
    else
    {
      sensorSettings_Activate( SENSOR_MPL );
      if ( true == MPL_firstTime )
      {
        MPL_firstTime = false;
      }
    }
  }
#endif

#if defined( SENSOR_HTU_PRESENT )
	if  (
			   ShouldSensorBeActivated( SENSOR_HTU, PACKET_HUM )
		  || ShouldSensorBeActivated( SENSOR_HTU, PACKET_TEMP )
		)
	{
		if ( true == power_IsActive( POWER_HTU_TSL ) )
		{
			if ( STATUS_HTU_SUCCESS != HTU_Init( &htuModule,  &htuSettings ) )
			{
				catch( CATCH_INIT );
			}
			else
			{
				sensorSettings_Activate( SENSOR_HTU );
			}
		}

		else
		{
			catch( CATCH_SENSOR );
		}
	}
#endif

#if defined( SENSOR_TSL_PRESENT )
	if ( ShouldSensorBeActivated( SENSOR_TSL, PACKET_LUX ) )
	{
		if ( true == power_IsActive( POWER_HTU_TSL ) )
		{
			if ( STATUS_TSL_SUCCESS != TSL_Init( &tslModule,  &tslSettings ) )
			{
				catch( CATCH_INIT );
			}
			else
			{
				sensorSettings_Activate( SENSOR_TSL );
			}
		}

		else
		{
			catch( CATCH_SENSOR );
		}
	}
#endif

#if defined( SENSOR_MAXIM_PRESENT )
	if ( ShouldSensorBeActivated( SENSOR_MAXIM, PACKET_HR ) )
	{
		if ( true == power_IsActive( POWER_MAXIM ) )
		{
			if ( STATUS_MAXIM_SUCCESS != MAXIM_Init( &maximModule,  &maximSettings ) )
			{
				catch( CATCH_INIT );
			}
			else
			{
				MAXIM_Enable();
				sensorSettings_Activate( SENSOR_MAXIM );
				MAXIM_InstallCallback( heartRate_Process );
			}
		}

		else
		{
			catch( CATCH_SENSOR );
		}
	}
#endif
}

/**
 * put NXP sensors to standby
 * or just mark non-NXP sensors as inactive
 * (their power supply is shut off in that case )
 */
static void sensor_DeinitModules()
{
#if defined( SENSOR_FXOS_PRESENT )
//  if  (
//           ShouldSensorBeDeactivated( SENSOR_FXOS, PACKET_ACC )
//        && ShouldSensorBeDeactivated( SENSOR_FXOS, PACKET_MAG )
//      )
//  {
//    sensorSettings_Deactivate( SENSOR_FXOS );

//  	if ( STATUS_FXOS_SUCCESS != FXOS_GotoStandby() )
//  	{
//  	  catch( CATCH_INIT );
//  	}
//  	else
//  	{
//  	  sensorSettings_Deactivate( SENSOR_FXOS );
//  	}
//  }
#endif

#if defined( SENSOR_FXAS_PRESENT )
  if ( ShouldSensorBeDeactivated( SENSOR_FXAS, PACKET_GYRO ) )
  {
    sensorSettings_Deactivate( SENSOR_FXAS );

    if ( STATUS_FXAS_SUCCESS != FXAS_GotoStandby() )
    {
      catch( CATCH_INIT );
    }
//    else
//    {
//      sensorSettings_Deactivate( SENSOR_FXAS );
//    }
  }
#endif

#if defined( SENSOR_MPL_PRESENT )
  if  ( ShouldSensorBeDeactivated( SENSOR_MPL, PACKET_PRES ) )
  {
    sensorSettings_Deactivate( SENSOR_MPL );

    if ( STATUS_MPL_SUCCESS != MPL_GotoStandby() )
    {
      catch( CATCH_INIT );
    }
//   else
//   {
//     sensorSettings_Deactivate( SENSOR_MPL );
//   }
  }
#endif

#if defined( SENSOR_HTU_PRESENT )
  if  (
		       ShouldSensorBeDeactivated( SENSOR_HTU, PACKET_HUM )
	      && ShouldSensorBeDeactivated( SENSOR_HTU, PACKET_TEMP )
	  )
  {
	  sensorSettings_Deactivate( SENSOR_HTU );
  }
#endif

#if defined( SENSOR_TSL_PRESENT )
  if ( ShouldSensorBeDeactivated( SENSOR_TSL, PACKET_LUX ) )
  {
    sensorSettings_Deactivate( SENSOR_TSL );
  }
#endif

#if defined( SENSOR_MAXIM_PRESENT )
  if ( ShouldSensorBeDeactivated( SENSOR_MAXIM, PACKET_HR ) )
  {
    MAXIM_Disable();
    sensorSettings_Deactivate( SENSOR_MAXIM );
  }
#endif
}

/**
 * push data to various mediums
 * @return status flag
 */
static void sensor_PushData (
                              hostInterface_packet_t* dataPacket,
                                  packet_pushTarget_t pushTargets
                            )
{
	if ( 0 != ( pushTargets & PACKET_PUSH_KW40 ) )
	{
		{
			if (  POWER_CURRENT_MODE_SLEEP_SENSOR_TAG == power_GetCurrentMode() )
			{
				GPIO_DRV_TogglePinOutput( KW40_WU );
				OSA_TimeDelay(10);
			}
			HostInterface_TxQueueMsgPut( dataPacket, false );
		}
	}

	if ( 0 != ( pushTargets & PACKET_PUSH_OLED ) )
	{
		if ( true == power_IsActive( POWER_OLED ) )
		{
			GuiDriver_QueueMsgPut( dataPacket );
		}
	}

	if ( 0 != ( pushTargets & PACKET_PUSH_APP_PEDOMETER ) )
	{
		pedometer_QueueMsgPut( dataPacket );
	}

	if ( 0 != ( pushTargets & PACKET_PUSH_APP_HEART_RATE ) )
	{
		// do nothing
	}

	if ( 0 != ( pushTargets & PACKET_PUSH_POWER_MGMT ) )
	{
		switch( dataPacket->type )
		{
			case packetType_batteryLevel:
			{
				if ( 0 != bat_mvolts )
				{
					if ( bat_mvolts < 2267 )
					{
						power_SetBatteryLow();
					}
					else if ( bat_mvolts >= 2400 )
					{
						power_UnsetBatteryLow();
					}
				}
				break;
			}

			default: {}
		}
	}
}

/**
 * get the timer period
 * convert to [us] and divide by the number of active packets
 */
static uint32_t sensor_GetTimerPeriod()
{
	uint8_t
		activePacketNum = GetActivePacketsNum();

	if ( 0 != activePacketNum )
	{
		return sensor_minDelay_ms * 1000 / activePacketNum;
	}

	else
	{
	  return sensor_minDelay_ms * 1000;
	}
}

/**
 * set the timer period
 * convert to [us] and divide by the number of active packets
 */
static void sensor_SetTimerPeriod( uint32_t newPeriod )
{
    if ( 0 != newPeriod )
    {
        timer_SetPeriod( HEXIWEAR_TIMER_SENSOR, newPeriod );
    }
}

/**
 * update the sensor timer period
 */
static void sensor_UpdateTimer()
{
    oldPeriodVal = newPeriodVal;
    newPeriodVal = sensor_GetTimerPeriod();

    if ( oldPeriodVal != newPeriodVal )
    {
        sensor_SetTimerPeriod( newPeriodVal );
    }
}

/**
 * set minimum delay for the sensor loop
 */
void sensor_SetMinimumDelay(
                             uint32_t delay
                           )
{
  sensor_minDelay_ms = ( 0 == delay ) ?
                          SENSOR_DEFAULT_MINIMUM_DELAY_MS:
                          delay;
}

/**
 * assign delay in [ms] to the particular packet
 */
void sensor_RegisterPacketDelay (
                                  packet_t packetToUpdate,
                                  uint32_t delay_ms
                                )
{
  packetSettings[ packetToUpdate ].delay_ms = ( 0 == delay_ms ) ?
                         packetSettings[ packetToUpdate ].defaultDelay_ms:
                         delay_ms;
}

/**
 * register the counter value for the packet
 */
static void UpdatePacketCounters()
{
	uint8_t
		activePacketNum = GetActivePacketsNum();

	if ( 0 != activePacketNum )
	{
		for ( packet_t pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
		{
			if ( packetSettings_HasTargets( pktIdx ) )
			{
				uint32_t
					oldInitVal = packetSettings[ pktIdx ].initCounterVal;
				packetSettings[ pktIdx ].initCounterVal = round( ( 1000 * packetSettings[ pktIdx ].delay_ms ) / ( ( 1000 * sensor_minDelay_ms ) /* / activePacketNum */ ) ) - 1;

				// if there was a change in counter values, trigger new sensor reading
				if ( oldInitVal != packetSettings[ pktIdx ].initCounterVal )
				{
					sensor_ResetPacketcounter( pktIdx );
				}
			}
		}

	  	/**
	  	 * by the same logic,
	  	 * update the LED counter reload value and reset the counter, if appropriate
	  	 */

//		uint32_t
//			oldLedCntVal = sensor_LEDCounterInitVal;
	  	sensor_LEDCounterInitVal = ( round( ( 1000 * TIMER_BLINKING_PERIOD_MS ) / ( ( 1000 * sensor_minDelay_ms ) ) ) * activePacketNum ) - 1;
//	  	if ( oldLedCntVal != sensor_LEDCounterInitVal )
//	  	{
//	  		sensor_ResetLEDIndicator();
//	  	}
	}
}

/**
 * [sensor_Wait description]
 * @return [description]
 */
static sensor_status_t sensor_Wait()
{
	osa_status_t
		status = OSA_SemaWait( &sensor_sema, OSA_WAIT_FOREVER );

	if ( kStatus_OSA_Success != status )
	{
		return SENSOR_STATUS_ERROR;
	}

	return SENSOR_STATUS_SUCCESS;
}

/**
 * stop with waiting
 */
void sensor_StopWait()
{
	OSA_SemaPost( &sensor_sema );
}

/**
 * [GetActivePacketsNum description]
 * @return [description]
 */
static uint8_t GetActivePacketsNum()
{
  uint8_t
    activePacketsNum = 0;

  for ( packet_t pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
  {
    if packetSettings_HasTargets( pktIdx )
    {
      activePacketsNum++;
    }
  }

  return activePacketsNum;
}

/**
 * [sensor_ResetLedIndicator description]
 */
void sensor_ResetLEDIndicator()
{
  sensor_LEDCounter = 1;
}

/**
 * [sensor_ClearLEDIndicator description]
 */
void sensor_ClearLEDIndicator()
{
  BLUE_LED_OFF();
}

/**
 * formatting functions
 */

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
static void bat_fmtDef2Float(
                              const void* src,
                                    void* dst,
                                 uint32_t idx
                            )
{
  /**
   * helper pointers
   */
  uint16_t*
    input = (uint16_t*)src;
  float*
    output = (float*)dst;

  // convert data
  output[idx] = (float)input[idx] * (3.3 / 65536.0);
}

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
static void bat_fmtDef2Me(
                            const void* src,
                                  void* dst,
                               uint32_t idx
                          )
{
  /**
   * helper pointers
   */
  uint16_t*
    input = (uint16_t*)src;
  mE_t*
    output = (mE_t*)dst;

  // convert data to milivolts
  bat_mvolts = (uint16_t)( ( (float)input[idx] * ( 3.3 / 65535.0 ) ) * 1000 );

  if ( bat_mvolts > 2670 )
  {
    output[idx] = 100;
  }

  else if ( bat_mvolts > 2500 )
  {
    output[idx] = (mE_t)( 50 + 50.0 * ( ( bat_mvolts - 2500 ) / 170.0 ) );
  }
  else if ( bat_mvolts > 2430 )
  {
    output[idx] = (mE_t)( 30 + 20.0 * ( ( bat_mvolts - 2430 ) / 70.0 ) );
  }
  else if ( bat_mvolts > 2370 )
  {
    output[idx] = (mE_t)( 10 + 20.0 * ( ( bat_mvolts - 2370 ) / 60.0 ) );
  }
  else
  {
    output[idx] = 0;
  }
}

/**
 * format raw to byte - currently unimplemented
 */
static void bat_fmtDef2Byte (
								const void* src,
								      void* dst,
								   uint32_t idx
							)
{}

/**
 * [sensor_SaveCurrentTargetsForKW40 description]
 */
void sensor_SaveTargetsForKW40()
{
    for ( packet_t pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
       if ( 0 != ( packetSettings[ pktIdx ].targets & PACKET_PUSH_KW40 ) )
       {
          packetSettings[ pktIdx ].targets &= ~PACKET_PUSH_KW40;
          KW40_backupList[ pktIdx ] = 1;
       }
    }

    /**
     * no need to pause the sensor task,
     * since it will check for it itself
     * at the beginning of the loop
     * just check for potentially new counter values
     */

    UpdatePacketCounters();
}

/**
 * [sensor_RestoreCurrentTargetsForKW40 description]
 */
void sensor_RestoreTargetsForKW40()
{
    for ( packet_t pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
       if ( 1 == KW40_backupList[ pktIdx ] )
       {
          packetSettings[ pktIdx ].targets |= PACKET_PUSH_KW40;
          KW40_backupList[ pktIdx ] = 0;
       }
    }

	// potentially resume the sensor task
	UpdatePacketCounters();
    sensor_ChangeTaskState( TASK_RESUME );
}

/**
 * [sensor_CheckTargetsForKW40() description]
 */
bool sensor_CheckForKW40Targets()
{
    for ( packet_t pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
    	if ( 0 != ( packetSettings[ pktIdx ].targets & PACKET_PUSH_KW40 ) )
    	{
    		return true;
    	}
    }

    return false;
}

/**
 * [sensor_SaveCurrentTargetsForKW40 description]
 */
void sensor_ResetTargetsForKW40()
{
    for ( packet_t pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
		KW40_backupList[ pktIdx ] = 0;
    }
}

/**
 * suspend the sensor task
 */
void sensor_Suspend()
{
	if ( true == isSensorTaskActive )
	{
		isSensorTaskActive = false;
		timer_Stop( HEXIWEAR_TIMER_SENSOR );
		vTaskSuspend( hexiwear_sensor_TAG_handler );
	}
}

/**
 * resume the sensor task
 */
void sensor_Resume()
{
	if ( false == isSensorTaskActive )
	{
		isSensorTaskActive = true;
		timer_Start( HEXIWEAR_TIMER_SENSOR );
		vTaskResume( hexiwear_sensor_TAG_handler );
	}
}
