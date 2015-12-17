/**
 * sensors wrapper routines
 * Project HEXIWEAR, 2015
 */

#include "string.h"

#include "HEXIWEAR_info.h"

#include "GPIO.h"
#include "BATTERY_ADC.h"

#include "menu_driver.h"

#include "sensor_driver.h"
#include "sensor_info.h"
#include "sensor_defs.h"

#include "FXOS_info.h"
#include "FXOS_defs.h"
#include "FXOS_driver.h"

#include "FXAS_info.h"
#include "FXAS_defs.h"
#include "FXAS_driver.h"

#include "MPL_info.h"
#include "MPL_defs.h"
#include "MPL_driver.h"

#include "TSL_info.h"
#include "TSL_defs.h"
#include "TSL_driver.h"

#include "HTU_info.h"
#include "HTU_defs.h"
#include "HTU_driver.h"

#include "MAXIM_info.h"
#include "MAXIM_defs.h"
#include "MAXIM_driver.h"

#include "OLED_info.h"
#include "OLED_driver.h"

#include "error.h"

#if defined( HEXIWEAR_DEBUG )
#include "fsl_uart_driver.h"
#include "DEBUG_UART.h"
#endif

/**
 * intern variables
 */

static sensor_settings_t
  sensor_settings[ SENSOR_PACKET_ALL ] = {
                                          // SENSOR_PACKET_ACC
                                          {
                                            .targets  = SENSOR_PUSH_KW40,
                                            .isActive = NO
                                          },

                                          // SENSOR_PACKET_MAG
                                          {
                                            .targets  = SENSOR_PUSH_KW40,
                                            .isActive = NO
                                          },

                                          // SENSOR_PACKET_GYRO
                                          {
                                            .targets  = SENSOR_PUSH_KW40,
                                            .isActive = NO
                                          },

                                          // SENSOR_PACKET_PRES
                                          {
                                            .targets  = SENSOR_PUSH_KW40,
                                            .isActive = NO
                                          },

                                          // SENSOR_PACKET_TEMP
                                          {
                                            .targets  = SENSOR_PUSH_KW40,
                                            .isActive = NO
                                          },

                                          // SENSOR_PACKET_HUM
                                          {
                                            .targets  = SENSOR_PUSH_KW40,
                                            .isActive = NO
                                          },

                                          // SENSOR_PACKET_LUX
                                          {
                                            .targets  = SENSOR_PUSH_NONE,
                                            .isActive = NO
                                          },

                                          // SENSOR_PACKET_HR
                                          {
                                            .targets  = SENSOR_PUSH_NONE,
                                            .isActive = NO
                                          },

                                          // SENSOR_PACKET_BAT
                                          {
                                            .targets  = SENSOR_PUSH_KW40,
                                            .isActive = NO
                                          }
                                        };
/**
 * helpful macros
 */

#define START_PACKET ( packetType_batteryLevel )
#define END_PACKET   ( packetType_steps )
#define nextSensor(sensPkt) sensPkt = ( (++sensPkt) % END_PACKET ) + START_PACKET * ( sensPkt / END_PACKET )

// OSA_TASK_DEFINE( sensor_GetData,    HEXIWEAR_SENSOR_TASK_GET_DATA_STACK_SIZE );
// OSA_TASK_DEFINE( sensor_GetFitData, HEXIWEAR_SENSOR_TASK_GET_FITDATA_STACK_SIZE );

/**
 * declarations
 */
/**
 * push data to various mediums
 * @return status flag
 */
static void sensor_PushData (
                              hostInterface_packet_t* dataPacket,
                                  sensor_pushTarget_t pushTargets
                            );

/**
 * [sensor_Wait  description]
 * @param delay [description]
 */
static void sensor_Wait (
                          uint32_t delay
                        );

/**
 * initialize sensors' modules
 * @return bit-vector with sensor initialization success flags
 */
sensor_mask_t sensor_InitModules(
                                  sensor_mask_t sensorList
                                )
{
  sensor_mask_t
    sensorStatus = SENSOR_MASK_NONE;

  /**
   * toggle the power supply for:
   * - non-Freescale sensors
   * - heart-rate sensor
   */

  GPIO_DRV_SetPinOutput  ( sensor_powerPins.B_EN_pin );
  GPIO_DRV_ClearPinOutput( sensor_powerPins.LDO_EN_pin );
  OSA_TimeDelay(5);
  GPIO_DRV_ClearPinOutput( sensor_powerPins.B_EN_pin );
  GPIO_DRV_SetPinOutput  ( sensor_powerPins.LDO_EN_pin );

  /**
   * adjust protocol interrupts
   */
  NVIC_SetPriority( HEXIWEAR_FS_I2C_IRQn,  HEXIWEAR_FS_I2C_IRQ_PRIO );
  NVIC_SetPriority( HEXIWEAR_NFS_I2C_IRQn, HEXIWEAR_NFS_I2C_IRQ_PRIO );

  /**
   * initialize individual sensors
   */

#if defined( SENSOR_FXOS )
   if ( 0 != ( sensorList & SENSOR_MASK_FXOS ) )
   {
    if  (
              ( STATUS_FXOS_SUCCESS == FXOS_Init( &fxosModule, &fxosSettings ) )
          &&  ( NO == sensor_settings[ SENSOR_PACKET_ACC ].isActive )
          &&  ( NO == sensor_settings[ SENSOR_PACKET_MAG ].isActive )
        )
    {
      sensor_settings[ SENSOR_PACKET_ACC ].isActive = YES;
      sensor_settings[ SENSOR_PACKET_MAG ].isActive = YES;
      sensorStatus |= SENSOR_MASK_FXOS;
    }
  }
#endif

#if defined( SENSOR_FXAS )
  if ( 0 != ( sensorList & SENSOR_MASK_FXAS ) )
  {
    if  (
              ( STATUS_FXAS_SUCCESS == FXAS_Init( &fxasModule, &fxasSettings ) )
          &&  ( NO == sensor_settings[ SENSOR_PACKET_GYRO ].isActive )
        )
    {
      sensor_settings[ SENSOR_PACKET_GYRO ].isActive = YES;
      sensorStatus |= SENSOR_MASK_FXAS;
    }
  }
#endif

#if defined( SENSOR_MPL )
  if ( 0 != ( sensorList & SENSOR_MASK_MPL ) )
  {
    if  (
              ( STATUS_MPL_SUCCESS == MPL_Init ( &mplModule,  &mplSettings ) )
          &&  ( NO == sensor_settings[ SENSOR_PACKET_PRES ].isActive )
          &&  ( NO == sensor_settings[ SENSOR_PACKET_TEMP ].isActive )
        )
    {
      sensor_settings[ SENSOR_PACKET_PRES ].isActive = YES;
      sensor_settings[ SENSOR_PACKET_TEMP ].isActive = YES;
      sensorStatus |= SENSOR_MASK_MPL;
    }
  }
#endif

#if defined( SENSOR_HTU )
  if ( 0 != ( sensorList & SENSOR_MASK_HTU ) )
  {
    if  (
              ( STATUS_HTU_SUCCESS == HTU_Init ( &htuModule,  &htuSettings ) )
          &&  ( NO == sensor_settings[ SENSOR_PACKET_HUM ].isActive )
        )
    {
      sensor_settings[ SENSOR_PACKET_HUM ].isActive = YES;
      sensorStatus |= SENSOR_MASK_HTU;
    }
  }
#endif

#if defined( SENSOR_TSL )
  if ( 0 != ( sensorList & SENSOR_MASK_TSL ) )
  {
    if  (
              ( STATUS_TSL_SUCCESS == TSL_Init ( &tslModule,  &tslSettings ) )
          &&  ( NO == sensor_settings[ SENSOR_PACKET_LUX ].isActive )
        )
    {
      sensor_settings[ SENSOR_PACKET_LUX ].isActive = YES;
      sensorStatus |= SENSOR_MASK_TSL;
    }
  }
#endif

#if defined( SENSOR_MAXIM )
  if ( 0 != ( sensorList & SENSOR_MASK_MAXIM ) )
  {
    if  (
              ( STATUS_MAXIM_SUCCESS == MAXIM_Init ( &maximModule,  &maximSettings ) )
          &&  ( NO == sensor_settings[ SENSOR_PACKET_HR ].isActive )
        )
    {
      sensor_settings[ SENSOR_PACKET_HR ].isActive = YES;
      sensorStatus |= SENSOR_MASK_MAXIM;
    }
  }
#endif

  return sensorStatus;
}

/**
 * [sensor_SetPushTargets description]
 * @param sensorToUpdate [description]
 * @param newPushTarget  [description]
 */
void sensor_SetPushTargets(
                                sensor_packet_t sensorToUpdate,
                            sensor_pushTarget_t newPushTarget
                          )
{
  sensor_settings[ sensorToUpdate ].targets = newPushTarget;
}

/**
 * [sensor_SetPushTargets  description]
 * @param  sensorToUpdate [description]
 * @return                [description]
 */
sensor_pushTarget_t sensor_GetPushTargets (
                                            sensor_packet_t sensorToUpdate
                                          )
{
  return sensor_settings[ sensorToUpdate ].targets;
}

/**
 * format sensor data to various formats
 * @param sensorData data to format
 * @param fmtOptions options include:
 *                   - type of given data
 *                   - original format
 *                   - new desired format
 */
void sensor_FormatData(
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
                            registerFormatters(hr);
                            dataLen = TypeMember_SCALAR;
                            break;
                          }

    case DATA_TYPE_STEPS:  { break; }
    case DATA_TYPE_ACTIVE: { break; }

    default: {}
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

                                        case DATA_FORMAT_TO_FLOAT:    {
                                                                        for ( uint8_t idx = 0; idx < dataLen; idx++ )
                                                                        {
                                                                          sensor_fmtDef2Float(src, dst, idx);
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
 * tasks
 */

/**
 * retrieve data from various sensors
 * @param param task parameter, currently unused
 */
static void sensor_GetData(
                            task_param_t param
                          )
{
  // data packet to be sent
  hostInterface_packet_t
    sensorPacket;

  // use this to designate if the packet is ready to be sent
  hexiwear_send_t
    isReadyToSend = SEND_NO;

  // packet type
  hostInterface_packetType_t
    sensorToSend = START_PACKET;

  // formatting options
  uint8_t
    fmtOptions = 0;

  // battery level
  mE_t
    adcData  = 0;

  void
    *dataStart = NULL;

  sensor_pushTarget_t
    pushTargets;

  /**
   * format for all the data: RAW -> mE
   */

  Write( fmtOptions, DATA_FORMAT_FROM, DATA_FORMAT_FROM_DEFAULT );
  Write( fmtOptions, DATA_FORMAT_TO,   DATA_FORMAT_TO_mE );

  while(1)
  {
    /**
     * prepare the packet
     */

    sensorPacket.start1 = gHostInterface_startByte1;
    sensorPacket.start2 = gHostInterface_startByte2;
    sensorPacket.type   = sensorToSend;
    isReadyToSend       = SEND_NO;

    /**
     * read, format and insert data into the packet
     */

    switch ( sensorToSend )
    {

      /**
       * Battery level
       */

      case packetType_batteryLevel: {
                                      ADC16_DRV_ConfigConvChn( FSL_BATTERY_ADC, 0, &BATTERY_ADC_ChnConfig);
                                      ADC16_DRV_WaitConvDone ( FSL_BATTERY_ADC, 0 );
                                      adcData = ADC16_DRV_GetConvValueSigned( FSL_BATTERY_ADC, 0 );

                                      dataStart           = (void*)&( adcData );
                                      sensorPacket.length = TypeMember_SCALAR;
                                      pushTargets         = sensor_settings[ SENSOR_PACKET_BAT ].targets;
                                      isReadyToSend       = SEND_YES;
                                      break;
                                    }

      /**
       * MOTION
       */

      case packetType_accel:  {
#if defined( SENSOR_FXOS )
                                statusFXOS_t
                                  fxosStatus =  FXOS_ReadRawData( (int16_t*)&motionData );

                                if  ( STATUS_FXOS_SUCCESS == fxosStatus )
                                {
                                  dataStart           = (void*)&( motionData.accData[0] );
                                  sensorPacket.length = TypeMember_NumEl( motionData_t , accData );
                                  pushTargets         = sensor_settings[ SENSOR_PACKET_ACC ].targets;
                                  isReadyToSend       = SEND_YES;
                                }

                                else
                                {
                                  catch( CATCH_MOTION );
#endif
                                  isReadyToSend = SEND_SKIP;
#if defined( SENSOR_FXOS )
                                }
#endif
                                break;
                              }

      case packetType_magnet:  {
#if defined( SENSOR_FXOS )
                                statusFXOS_t
                                  fxosStatus = FXOS_ReadRawData( (int16_t*)&motionData );

                                if  ( STATUS_FXOS_SUCCESS == fxosStatus )
                                {
                                  dataStart           = (void*)&( motionData.magData[0] );
                                  sensorPacket.length = TypeMember_NumEl( motionData_t , magData );
                                  pushTargets         = sensor_settings[ SENSOR_PACKET_MAG ].targets;
                                  isReadyToSend       = SEND_YES;
                                }

                                else
                                {
                                  catch( CATCH_MOTION );
#endif
                                  isReadyToSend = SEND_SKIP;
#if defined( SENSOR_FXOS )
                                }
#endif
                                break;
                              }

      case packetType_gyro:   {
#if defined( SENSOR_FXAS )
                                statusFXAS_t
                                  fxasStatus = FXAS_ReadRawData( (int16_t*)&(motionData.gyroData[0]) );

                                if  ( STATUS_FXAS_SUCCESS == fxasStatus )
                                {
                                  dataStart           = (void*)&( motionData.gyroData[0] );
                                  sensorPacket.length = TypeMember_NumEl( motionData_t , gyroData );
                                  pushTargets         = sensor_settings[ SENSOR_PACKET_GYRO ].targets;
                                  isReadyToSend       = SEND_YES;
                                }

                                else
                                {
                                  catch( CATCH_MOTION );
#endif
                                  isReadyToSend = SEND_SKIP;
#if defined( SENSOR_FXAS )
                                }
#endif
                                break;
                              }

      /**
       * WEATHER
       */

      case packetType_temperature:  {
#if defined( SENSOR_MPL )
                                      statusMPL_t
                                        mplStatus = MPL_ReadRawData( MPL_MODE_TEMPERATURE, (int16_t*)&(weatherData.tempData) );

                                      if ( STATUS_MPL_SUCCESS == mplStatus )
                                      {
                                        dataStart           = (void*)&( weatherData.tempData );
                                        sensorPacket.length = TypeMember_SCALAR;
                                        pushTargets         = sensor_settings[ SENSOR_PACKET_TEMP ].targets;
                                        isReadyToSend       = SEND_YES;
                                      }

                                      else
                                      {
                                        catch( CATCH_WEATHER );
#endif
                                        isReadyToSend = SEND_SKIP;
#if defined( SENSOR_MPL )
                                      }
#endif
                                      break;
                                    }

      case packetType_humidity:     {
#if defined( SENSOR_HTU )
                                      statusHTU_t
                                        htuStatus = HTU_GetHum( (int16_t*)&(weatherData.humidData) );

                                      if  ( STATUS_HTU_SUCCESS == htuStatus )
                                      {
                                        dataStart           = (void*)&( weatherData.humidData );
                                        sensorPacket.length = TypeMember_SCALAR;
                                        pushTargets         = sensor_settings[ SENSOR_PACKET_HUM ].targets;
                                        isReadyToSend       = SEND_YES;
                                      }

                                      else
                                      {
                                        catch( CATCH_WEATHER );
#endif
                                        isReadyToSend = SEND_SKIP;
#if defined( SENSOR_HTU )
                                      }
#endif
                                      break;
                                    }

      case packetType_pressure:     {
#if defined( SENSOR_MPL )
                                      statusMPL_t
                                        mplStatus = MPL_ReadRawData( MPL_MODE_PRESSURE, (int16_t*)&(weatherData.presAltData) );

                                      if  ( STATUS_MPL_SUCCESS == mplStatus )
                                      {
                                        dataStart           = (void*)&( weatherData.presAltData );
                                        sensorPacket.length = TypeMember_SCALAR;
                                        pushTargets         = sensor_settings[ SENSOR_PACKET_PRES ].targets;
                                        isReadyToSend       = SEND_YES;
                                      }

                                      else
                                      {
                                        catch( CATCH_WEATHER );
#endif
                                        isReadyToSend = SEND_SKIP;
#if defined( SENSOR_MPL )
                                      }
#endif
                                      break;
                                    }

      // skip these
      case packetType_ambiLight:    {
                                      isReadyToSend = SEND_SKIP;
                                      break;
                                    }

      case packetType_heartRate:    {
                                      isReadyToSend = SEND_SKIP;
                                      break;
                                    }
      default: {}
    }

    /**
     * finish with packet formation
     * and push the packet into the queue
     */

    switch( isReadyToSend )
    {
      case SEND_YES:  {
                        switch ( Extract( fmtOptions, DATA_FORMAT_TO ) )
                        {
                          case DATA_FORMAT_TO_DEFAULT:  { break; }

                          case DATA_FORMAT_TO_FLOAT:    {
                                                          sensorPacket.length *= sizeof( float );
                                                          break;
                                                        }

                          case DATA_FORMAT_TO_mE:       {
                                                          sensorPacket.length *= sizeof( mE_t );
                                                          break;
                                                        }

                          default: {}
                        }

                        // format data
                        Write( fmtOptions, DATA_TYPE, sensorToSend );
                        sensor_FormatData (
                                            dataStart,
                                            (void*)&( sensorPacket.data[0] ),
                                            fmtOptions
                                          );

                        // add trailer byte, denoting the packet end
                        sensorPacket.data[ sensorPacket.length ] = gHostInterface_trailerByte;

                        // push data
                        sensor_PushData( &sensorPacket , pushTargets );

                        // wait  it out, if necessary
                        sensor_Wait( 50 );
                      }

      case SEND_SKIP: {
                        // goto the next sensor
                        nextSensor(sensorToSend);
                        break;
                      }
      default: {}
    }
  }
}

/**
 * create tasks
 */

/**
 * initialize the sensor task
 * @return task initialization status
 */
osa_status_t sensor_Init()
{

  /**
   * initialize all the sensor modules
   */

  sensor_mask_t
    sensorStatus = sensor_InitModules( SENSOR_MASK_ALL );

  if ( SENSOR_MASK_ALL != sensorStatus )
  {
    catch( CATCH_INIT );
  }

  // create the task responsible for fetching data
  osa_status_t
    status = OSA_TaskCreate (
                              sensor_GetData,
                              (uint8_t*)"Sensor Task Get Data",
                              SENSOR_GET_DATA_STACK_SIZE,
                              NULL,
                              SENSOR_GET_DATA_PRIO,
                              (task_param_t)0,
                              false,
                              &hexiwear_sensor_TAG_handler
                            );

  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_INIT );
  }

  return (osa_status_t)status;
}


/**
 * push data to various mediums
 * @return status flag
 */
static void sensor_PushData (
                              hostInterface_packet_t* dataPacket,
                                  sensor_pushTarget_t pushTargets
                            )
{
  if ( 0 != ( pushTargets & SENSOR_PUSH_KW40 ) )
  {
    HostInterface_TxQueueMsgPut( dataPacket );
  }

  if ( 0 != ( pushTargets & SENSOR_PUSH_OLED ) )
  {
    MenuDriver_QueueMsgPut( dataPacket );
  }
}

/**
 * wait for some amount of time
 */
static void sensor_Wait (
                          uint32_t delay
                        )
{
  OSA_TimeDelay(delay);
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
void bat_fmtDef2Float(
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
void bat_fmtDef2Me (
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

  uint16_t
    mvolts;

  // convert data
  mvolts = ( (float)input[idx] * (3.3 / 65535.0) ) / 1.4 * 3300;

  if (mvolts >= 3000)
  {
	  output[idx] = 100;
  }
  else if (mvolts > 2900)
  {
	  output[idx] = 100 - ((3000 - mvolts) * 58) / 100;
  }
  else if (mvolts > 2740)
  {
	  output[idx] = 42 - ((2900 - mvolts) * 24) / 160;
  }
  else if (mvolts > 2440)
  {
	  output[idx] = 18 - ((2740 - mvolts) * 12) / 300;
  }
  else if (mvolts > 2100)
  {
	  output[idx] = 6 - ((2440 - mvolts) * 6) / 340;
  }
  else
  {
	  output[idx] = 0;
  }

}
