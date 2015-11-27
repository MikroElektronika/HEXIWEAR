/**
 * sensors wrapper routines
 * Project HEXIWEAR, 2015
 */

#include "string.h"

#include "HEXIWEAR_info.h"
#include "gpio1.h"

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

#include "error.h"

#if defined( HEXIWEAR_DEBUG )
#include "fsl_uart_driver.h"
#include "uartCom2.h"
#endif

/**
 * intern variables
 */

// sensor settings, to be used in the sensor functions
static settingsSENSOR_t
  settings;

/**
 * helpful macros
 */

#define START_PACKET ( packetType_accel )
#define END_PACKET   ( packetType_steps )
#define nextSensor(sensPkt) sensPkt = ( (++sensPkt) % END_PACKET ) + START_PACKET * ( sensPkt / END_PACKET )

OSA_TASK_DEFINE( sensor_GetData, TASK_SENSOR_GET_DATA_STACK_SIZE );

/**
 * declarations
 */
static void sensor_Wait(uint32_t delay);
static void sensor_GetData(task_param_t param);

/**
 * initialize the sensor task
 * @return task initialization status
 */
osa_status_t sensor_Init()
{
  // create the task responsible for fetching data
  osa_status_t
    status = OSA_TaskCreate (
                              sensor_GetData,
                              (uint8_t*)"sensor_GetData",
                              TASK_SENSOR_GET_DATA_STACK_SIZE,
                              sensor_GetData_stack,
                              TASK_SENSOR_GET_DATA_DATA_PRIO,
                              (task_param_t)0,
                              false,
                              &sensor_GetData_task_handler
                            );

  if ( kStatus_OSA_Success != status )
  {
    catch(3);
  }

  return (osa_status_t)status;
}

/**
 * initialize sensors' modules
 * @return bit-vector with sensor initialization success flags
 */
static sensorScoreboard_t sensor_InitModules(
                                              settingsSENSOR_t* sensorSettings
                                            )
{
  sensorScoreboard_t
    sensorStatus = SENSOR_SUCCESS_NONE;

  /**
   * copy sensor settings to the intern structure
   */

  memcpy( (void*)&settings, (void*)sensorSettings, sizeof(settings) );

  /**
   * toggle the power supply for:
   * - non-Freescale sensors
   * - heart-rate sensor
   */

  GPIO_DRV_SetPinOutput  ( settings.B_EN_pin );
  GPIO_DRV_ClearPinOutput( settings.LDO_EN_pin );
  OSA_TimeDelay(5);
  GPIO_DRV_ClearPinOutput( settings.B_EN_pin );
  GPIO_DRV_SetPinOutput  ( settings.LDO_EN_pin );

  /**
   * adjust I2C interrupts
   */
  NVIC_SetPriority( I2C0_IRQn , 7 );
  NVIC_SetPriority( I2C1_IRQn , 7 );

  /**
   * initialize individual sensors
   */

#if defined(SENSOR_FXOS)
  if  (
        STATUS_FXOS_SUCCESS == FXOS_Init( &fxosModule, &fxosSettings )
      )
#endif
  {
    sensorStatus |= SENSOR_SUCCESS_FXOS;
  }

#if defined(SENSOR_FXAS)
  if  (
        STATUS_FXAS_SUCCESS == FXAS_Init( &fxasModule, &fxasSettings )
      )
#endif
  {
    sensorStatus |= SENSOR_SUCCESS_FXAS;
  }

#if defined(SENSOR_MPL)
  if  (
        STATUS_MPL_SUCCESS == MPL_Init ( &mplModule,  &mplSettings )
      )
#endif
  {
    sensorStatus |= SENSOR_SUCCESS_MPL;
  }

#if defined(SENSOR_HTU)
  if  (
        STATUS_HTU_SUCCESS == HTU_Init ( &htuModule,  &htuSettings )
      )
#endif
  {
    sensorStatus |= SENSOR_SUCCESS_HTU;
  }

#if defined(SENSOR_TSL)
  if  (
        STATUS_TSL_SUCCESS == TSL_Init ( &tslModule,  &tslSettings )
      )
#endif
  {
    sensorStatus |= SENSOR_SUCCESS_TSL;
  }

#if defined(SENSOR_MAXIM)
  if  (
        STATUS_MAXIM_SUCCESS == MAXIM_Init ( &maximModule,  &maximSettings )
      )
#endif
  {
    sensorStatus |= SENSOR_SUCCESS_MAXIM;
  }

  return sensorStatus;
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
    case DATA_TYPE_BATTERYLEVEL: {break;}

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
 * retrieve data from various sensors
 * @param param task parameter, currently unused
 */
static void sensor_GetData(
                            task_param_t param
                          )
{
  sensorScoreboard_t
    sensorStatus = SENSOR_SUCCESS_NONE;

  // data packet to be sent
  hostInterface_packet_t
    sensorPacket;

  // use this to designate if the packet is ready to be sent
  send_t
    readyToSend = SEND_NO;

  // packet type
  hostInterface_packetType_t
    sensorToSend = START_PACKET;

  // formatting options
  uint8_t
    fmtOptions = 0;

  /**
   * format all data from its raw values to mE format
   */

  Write( fmtOptions, DATA_FORMAT_FROM, DATA_FORMAT_FROM_DEFAULT );
  Write( fmtOptions, DATA_FORMAT_TO,   DATA_FORMAT_TO_mE );

  /**
   * sensor category buffers
   */

  static motionData_t
    motionData;

  static weatherData_t
    weatherData;

//  static healthData_t
//    healthData;

  /**
   * initialize the modules
   */
  sensorStatus = sensor_InitModules( &sensorSettings );

  if ( SENSOR_SUCCESS_ALL != sensorStatus )
  {
    catch(0);
  }

  while(1)
  {
    /**
     * prepare the packet
     */

    sensorPacket.start1 = gHostInterface_startByte1;
    sensorPacket.start2 = gHostInterface_startByte2;
    sensorPacket.type   = sensorToSend;
    readyToSend         = SEND_NO;

    /**
     * read, format and insert data into the packet
     */

    switch ( sensorToSend )
    {

      /**
       * MOTION
       */

      case packetType_accel:  {
#if defined(SENSOR_FXOS)
                                statusFXOS_t
                                  status =  FXOS_ReadRawData( (int16_t*)&motionData );

                                if  ( STATUS_FXOS_SUCCESS == status )
                                {
                                  Write( fmtOptions, DATA_TYPE, DATA_TYPE_ACCEL );
                                  sensor_FormatData (
                                                      (void*)&(motionData.accData[0]),
                                                      (void*)&(sensorPacket.data[0]),
                                                      fmtOptions
                                                    );

                                  sensorPacket.length = TypeMember_NumEl( motionData_t , accData );
                                  readyToSend         = SEND_YES;
                                }

                                else
                                {
                                  catch(6);
#endif
                                  readyToSend = SEND_SKIP;
#if defined(SENSOR_FXOS)
                                }
#endif
                                break;
                              }

      case packetType_magnet:  {
#if defined(SENSOR_FXOS)
                                statusFXOS_t
                                  status = FXOS_ReadRawData( (int16_t*)&motionData );

                                if  ( STATUS_FXOS_SUCCESS == status )
                                {
                                  Write( fmtOptions, DATA_TYPE, DATA_TYPE_MAG );
                                  sensor_FormatData (
                                                      (void*)&(motionData.magData[0]),
                                                      (void*)&(sensorPacket.data[0]),
                                                      fmtOptions
                                                    );

                                  sensorPacket.length = TypeMember_NumEl( motionData_t , magData );
                                  readyToSend         = SEND_YES;
                                }

                                else
                                {
                                  catch(6);
#endif
                                  readyToSend = SEND_SKIP;
#if defined(SENSOR_FXOS)
                                }
#endif
                                break;
                              }

      case packetType_gyro:   {
#if defined(SENSOR_FXAS)
                                statusFXAS_t
                                  status = FXAS_ReadRawData( (int16_t*)&(motionData.gyroData[0]) );

                                if  ( STATUS_FXAS_SUCCESS == status )
                                {
                                  Write( fmtOptions, DATA_TYPE, DATA_TYPE_GYRO );
                                  sensor_FormatData (
                                                      (void*)&(motionData.gyroData[0]),
                                                      (void*)&(sensorPacket.data[0]),
                                                      fmtOptions
                                                    );

                                  sensorPacket.length = TypeMember_NumEl( motionData_t , gyroData );
                                  readyToSend         = SEND_YES;
                                }

                                else
                                {
                                  catch(7);
#endif
                                  readyToSend = SEND_SKIP;
#if defined(SENSOR_FXAS)
                                }
#endif
                                break;
                              }

      /**
       * WEATHER
       */

      case packetType_ambiLight:    {
                                      // don't send ambient light data
                                      readyToSend = SEND_SKIP;
                                      break;
                                    }

      case packetType_temperature:  {
#if defined(SENSOR_MPL)
                                      statusMPL_t
                                        mplStatus = MPL_ReadRawData( MPL_MODE_TEMPERATURE, (int16_t*)&(weatherData.tempData) );

                                      if ( STATUS_MPL_SUCCESS == mplStatus )
                                      {
                                        Write( fmtOptions, DATA_TYPE, DATA_TYPE_TEMP );
                                        sensor_FormatData (
                                                            (void*)&(weatherData.tempData),
                                                            (void*)&(sensorPacket.data[0]),
                                                            fmtOptions
                                                          );

                                        sensorPacket.length = TypeMember_SCALAR;
                                        readyToSend         = SEND_YES;
                                      }

                                      else
                                      {
                                        catch(8);
#endif
                                        readyToSend = SEND_SKIP;
#if defined(SENSOR_MPL)
                                      }
#endif
                                      break;
                                    }

      case packetType_humidity:     {
#if defined(SENSOR_HTU)
                                      statusHTU_t
                                        status = HTU_GetHum( (int16_t*)&(weatherData.humidData) );

                                      if  ( STATUS_HTU_SUCCESS == status )
                                      {
                                        Write( fmtOptions, DATA_TYPE, DATA_TYPE_HUMID );
                                        sensor_FormatData (
                                                            (void*)&(weatherData.humidData),
                                                            (void*)&(sensorPacket.data[0]),
                                                            fmtOptions
                                                          );

                                        sensorPacket.length = TypeMember_SCALAR;
                                        readyToSend         = SEND_YES;
                                      }

                                      else
                                      {
                                        catch(9);
#endif
                                        readyToSend = SEND_SKIP;
#if defined(SENSOR_HTU)
                                      }
#endif
                                      break;
                                    }

      case packetType_pressure:     {
#if defined(SENSOR_MPL)
                                      statusMPL_t
                                        mplStatus = MPL_ReadRawData( MPL_MODE_PRESSURE, (int16_t*)&(weatherData.presAltData) );

                                      if  ( STATUS_MPL_SUCCESS == mplStatus )
                                      {
                                        Write( fmtOptions, DATA_TYPE, DATA_TYPE_PRES );
                                        sensor_FormatData (
                                                            (void*)&(weatherData.presAltData),
                                                            (void*)&(sensorPacket.data[0]),
                                                            fmtOptions
                                                          );

                                        sensorPacket.length = TypeMember_SCALAR;
                                        readyToSend         = SEND_YES;
                                      }

                                      else
                                      {
                                        catch(8);
#endif
                                        readyToSend = SEND_SKIP;
#if defined(SENSOR_MPL)
                                      }
#endif
                                      break;
                                    }

      case packetType_heartRate:  {
#if defined(SENSOR_MAXIM)
                                    statusMAXIM_t
                                      status =  MAXIM_ReadRawData( (uint32_t*)(healthData.hrData), &(healthData.sampNum) );

                                    if  ( STATUS_MAXIM_SUCCESS == status )
                                    {
                                      Write( fmtOptions, DATA_TYPE, DATA_TYPE_HR );
                                      sensor_FormatData (
                                                          (void*)&(healthData.hrData),
                                                          (void*)&(sensorPacket.data[0]),
                                                          fmtOptions
                                                        );

                                      sensorPacket.length = TypeMember_SCALAR;
                                      readyToSend         = SEND_YES;
                                    }

                                    else
                                    {
                                      catch(6);
#endif
                                      readyToSend = SEND_SKIP;
#if defined(SENSOR_MAXIM)
                                    }
#endif
                                    break;
                                  }

      default: {}
    }

    /**
     * finish with packet formation
     * and push the packet into the queue
     */

    switch( readyToSend )
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

                        // add trailer byte, denoting the packet end
                        sensorPacket.data[ sensorPacket.length ] = gHostInterface_trailerByte;

                        // push data
                        HostInterface_TxQueueMsgPut( &sensorPacket );

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
 * wait for some amount of time
 */
static void sensor_Wait (
                          uint32_t delay
                        )
{
  OSA_TimeDelay(delay);
}
