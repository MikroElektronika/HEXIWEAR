/**
 * MAXIM-related driver functions
 * Project HEXIWEAR, 2015
 */

/**
 * intern variables
 */
#include "HEXIWEAR_types.h"
#include "HEXIWEAR_info.h"

#include "MAXIM_driver.h"
#include "MAXIM_info.h"

#include "generic_i2c_driver.h"

#include "string.h"
#include "error.h"

#define IsPeak( array, idx ) ( 0 != ( ( array[ (idx) ] > array[ ( (idx) + 1 ) ] ) && ( array[ ( (idx) ) ] > array[ ( (idx) - 1 ) ] ) ) )

static handleMAXIM_t
  self;

static settingsMAXIM_t
  settings;

static dataMAXIM_t**
  ledBuffers = 0;

static uint8_t
  currentActiveSlots = 0;

static uint8_t
  selectedBitshift;

/**
 * initialize MAXIM module
 */
statusMAXIM_t MAXIM_Init(
                                  handleMAXIM_t* maximHandle,
                          const settingsMAXIM_t* maximSettings
                        )
{
  statusI2C_t
    status = I2C_Init( &(maximHandle->protocol), maximSettings->address );

  if ( STATUS_I2C_SUCCESS != status )
  {
    return STATUS_MAXIM_INIT_ERROR;
  }

  else
  {
    /**
     * initialize intern structures,
     * which will be used from now on
     */

    memcpy( (void*)&self,     (void*)maximHandle,   sizeof(self) );
    memcpy( (void*)&settings, (void*)maximSettings, sizeof(settings) );

    uint8_t
      foo = 0;

    // read revision ID
    statusI2C_t
      i2cStatus = STATUS_I2C_SUCCESS;

    genericI2cHandle_t
      i2cProtocol = self.protocol;

    uint8_t
      revID  = 0,
      partID = 0;

    // read revision ID
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_ID_REV, &revID );
    // read part ID
    i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_ID_PART, &partID );

    /**
     * set up the registers
     */

    // reset the module
    i2cStatus |= MAXIM_Reset();

    /**
     * set LED amplitude
     */
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_LED_RED_PA,   settings.LEDCurrentRed );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_LED_IR_PA,    settings.LEDCurrentIR );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_LED_GREEN_PA, settings.LEDCurrentGreen );

    // set FIFO settings
    WriteZ( foo, MAXIM_FIFO_CFG_FIFO_OVS, settings.oversample );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_CFG , foo );

    /**
     * set the mode
     */

    switch ( settings.mode )
    {
      case modeHR:        { break; }
      case modeSPO2:      { break; }

      case modeMultiLED:  {
                            currentActiveSlots = settings.activeSlots;

                            WriteZ( foo, MAXIM_SLOT_1_3, settings.LEDSlot[0] );
                            Write( foo, MAXIM_SLOT_2_4, settings.LEDSlot[1] );
                            i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_MULTILED_MODE_CR_12 , foo );

                            WriteZ( foo, MAXIM_SLOT_1_3, settings.LEDSlot[2] );
                            Write( foo, MAXIM_SLOT_2_4, settings.LEDSlot[3] );
                            i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_MULTILED_MODE_CR_34 , foo );

                            /**
                             * save the current number of assigned active slots
                             * and allocate memory for the buffer pointers
                             */

                            ledBuffers = ( dataMAXIM_t** ) pvPortMalloc( currentActiveSlots * sizeof( dataMAXIM_t* ) );

                            if ( NULL == ledBuffers )
                            {
                              return STATUS_MAXIM_ERROR;
                            }

                            break;
                          }

      default: {}
    }

    /**
     * set the timings
     * ADC bit resolution is determined by chosen sample rate
     */

    pwMAXIM_t
      selectedPulseWidth = settings.pulseWidth;

    sampleRateMAXIM_t
      selectedSamplerate;

    switch ( selectedPulseWidth )
    {
      case ledPower_69:   {
                            selectedSamplerate = settings.sampleRate;
                            selectedBitshift   = MAXIM_FIFO_BITSHIFT_15;
                            break;
                          }

      case ledPower_118:  {
                            selectedSamplerate =  ( settings.sampleRate > sampleRate_1600 ) ?
                                                    sampleRate_1600 :
                                                    settings.sampleRate;
                            selectedBitshift   = MAXIM_FIFO_BITSHIFT_16;
                            break;
                          }

      case ledPower_215:  {
                            selectedSamplerate =  ( settings.sampleRate > sampleRate_1600 ) ?
                                                    sampleRate_1600 :
                                                    settings.sampleRate;
                            selectedBitshift   = MAXIM_FIFO_BITSHIFT_17;
                            break;
                          }

      case ledPower_411:  {
                            selectedSamplerate =  ( settings.sampleRate > sampleRate_1000 ) ?
                                                    sampleRate_1000 :
                                                    settings.sampleRate;
                            selectedBitshift   = MAXIM_FIFO_BITSHIFT_18;
                            break;
                          }

      default:  {
                  return STATUS_MAXIM_ERROR;
                }
    }

    WriteZ( foo, MAXIM_CFG_LED_PW, selectedPulseWidth );
    Write ( foo, MAXIM_CFG_SR,     selectedSamplerate );
    Write ( foo, MAXIM_CFG_ADC,    settings.range );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_SPO2_CFG , foo );

    // clear FIFO pointers
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_WR_PTR , 0 );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_RD_PTR , 0 );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_FIFO_OV_PTR , 0 );

    // turn the module on
    WriteZ( foo, MAXIM_MODE, settings.mode );
    i2cStatus |= I2C_WriteReg( &i2cProtocol, MAXIM_REG_MODE_CFG , foo );

    if ( STATUS_I2C_SUCCESS != i2cStatus )
    {
      catch(11);
      return STATUS_MAXIM_PROTOCOL_ERROR;
    }

    else
    {
      return STATUS_MAXIM_SUCCESS;
    }
  }
}

/**
 * shutdown the sensor
 */
statusMAXIM_t MAXIM_Deinit()
{
  statusI2C_t
    status = I2C_Deinit( &(self.protocol) );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(11);
    return STATUS_MAXIM_PROTOCOL_ERROR;
  }

  else
  {
    // dealocate memory
    if ( NULL != ledBuffers )
    {
      free( ledBuffers );
    }

    return STATUS_MAXIM_SUCCESS;
  }
}

/**
 * reset the module
 * when the reset-bit is set to one, all configuration, threshold,
 * and data registers are reset to their power-on-state through
 * a power-on reset
 *
 * the reset bit is cleared automatically back to zero after the reset sequence is completed
 */
statusMAXIM_t MAXIM_Reset()
{
  uint8_t
    timeoutCnt = 0;

  statusI2C_t
    i2cStatus = 0;

  uint8_t
    foo = 0;

  // reset the module
  I2C_WriteReg( &(self.protocol), MAXIM_REG_MODE_CFG , MAXIM_MODE_CFGBIT_RST );

  // poll the RESET bit until it's cleared by hardware
  while (1)
  {
    i2cStatus = I2C_ReadReg( &(self.protocol), MAXIM_REG_MODE_CFG , &foo );

    if ( STATUS_I2C_SUCCESS != i2cStatus )
    {
      catch(11);
      return STATUS_MAXIM_PROTOCOL_ERROR;
    }

    else
    {
      if ( 0 == ( foo & MAXIM_MODE_CFGBIT_RST ) )
      {
        return STATUS_MAXIM_SUCCESS;
      }

      else
      {
        // wait a bit
        OSA_TimeDelay(10);
        timeoutCnt++;

        // exit if the module is stuck
        if ( timeoutCnt > 5 )
        {
          catch(11);
          return STATUS_MAXIM_TIMEOUT;
        }
      }
    }
  }
}

/**
 * read one sample from the FIFO buffer
 * @param  ledVal sample value
 * @return        status flag
 */
statusMAXIM_t MAXIM_ReadFIFO(
                              uint32_t* ledVal
                            )
{
  genericI2cHandle_t
    i2cProtocol = self.protocol;

  uint8_t
    cmd[1] =  {
                MAXIM_REG_FIFO_DATA
              };

  *ledVal = 0;

  uint8_t
    dataBuff[ MAXIM_BYTES_PER_SAMPLE ] = {0};

  // read number of requested samples
  i2c_status_t
    status = I2C_DRV_MasterReceiveDataBlocking(
                                                i2cProtocol.instance,
                                                &(i2cProtocol.device),

                                                (const uint8_t*)cmd,
                                                ArraySize(cmd),

                                                (uint8_t*)dataBuff,
                                                ArraySize(dataBuff),

                                                i2cProtocol.timeout
                                              );

  if ( kStatus_I2C_Success != status )
  {
    catch(11);
    return STATUS_MAXIM_PROTOCOL_ERROR;
  }
  else
  {
    *ledVal = (
                (   ( ( (uint32_t)dataBuff[0] ) << 16 )
                  | ( ( (uint32_t)dataBuff[1] ) << 8 )
                  | ( ( (uint32_t)dataBuff[2] ) << 0 )
                ) & MAXIM_FIFO_BITMASK
              ) >> selectedBitshift;

    return STATUS_MAXIM_SUCCESS;
  }
}

/**
 * read raw sensor data
 * @param  sensorData buffer with sensor data
 * @param  sampleNum  number of acquired samples
 * @return            status flag
 */
statusMAXIM_t MAXIM_ReadRawData (
                                  dataMAXIM_t* redData,
                                  dataMAXIM_t* irData,
                                  dataMAXIM_t* greenData,

                                     uint32_t* sampleNum
                                )
{
  statusI2C_t
    i2cStatus = STATUS_I2C_SUCCESS;

  uint8_t
    fifoWrPtr = 0,
    fifoRdPtr = 0,
    fifoOvPtr = 0;

  uint32_t
    samIdx = 0;

  statusMAXIM_t
    devStatus = STATUS_MAXIM_SUCCESS;

  genericI2cHandle_t
    i2cProtocol = self.protocol;

  /**
   * assign and check the buffers,
   * if necessary
   */

  if ( modeMultiLED == settings.mode )
  {
    uint8_t
      bufIdx = 0;

    for ( uint8_t slotIdx = 0; slotIdx < MAXIM_SLOT_NUM; slotIdx++ )
    {
      switch ( settings.LEDSlot[ slotIdx ] )
      {
        case LEDSlotRed:    {
                              if ( NULL == redData )
                              {
                                return STATUS_MAXIM_PARAM_ERROR;
                              }
                              else
                              {
                                ledBuffers[ bufIdx++ ] = redData;
                              }
                              break;
                            }

        case LEDSlotGreen:  {
                              if ( NULL == greenData )
                              {
                                return STATUS_MAXIM_PARAM_ERROR;
                              }
                              else
                              {
                                ledBuffers[ bufIdx++ ] = greenData;
                              }
                              break;
                            }

        case LEDSlotIR:     {
                              if ( NULL == irData )
                              {
                                return STATUS_MAXIM_PARAM_ERROR;
                              }
                              else
                              {
                                ledBuffers[ bufIdx++ ] = irData;
                              }
                              break;
                            }

        case LEDSlotNone:   {
                              break;
                            }

        default:  {
                    return STATUS_MAXIM_PARAM_ERROR;
                  }
      }
    }

    if ( currentActiveSlots != bufIdx )
    {
      catch(11);
    }
  }

  // read FIFO pointers
  i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_RD_PTR , &fifoRdPtr );
  i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_WR_PTR , &fifoWrPtr );
  i2cStatus |= I2C_ReadReg( &i2cProtocol, MAXIM_REG_FIFO_OV_PTR , &fifoOvPtr );

  /**
   * determine the number of samples to be read
   */

  if ( fifoOvPtr > 0 )
  {
    *sampleNum = MAXIM_FIFO_OVERFLOW;
  }

  else
  {
    if ( fifoWrPtr > fifoRdPtr )
    {
      *sampleNum = fifoWrPtr - fifoRdPtr;
    }

    // if FIFO write pointer rolled over
    else if ( fifoWrPtr < fifoRdPtr )
    {
      *sampleNum = ( fifoWrPtr + MAXIM_FIFO_DEPTH ) - fifoRdPtr;
    }

    else
    {
      // there is no new data
      *sampleNum = 0;
    }
  }

  /**
   * read the samples
   */

  // has overflow happened?
  if ( MAXIM_FIFO_OVERFLOW == *sampleNum )
  {
    // dummy read the FIFO to clear the overflow
    uint8_t
      cmd[1] =  { MAXIM_REG_FIFO_DATA },
      dummyBuf[ MAXIM_FIFO_DEPTH * MAXIM_BYTES_PER_SAMPLE ];

    I2C_DRV_MasterReceiveDataBlocking (
                                        i2cProtocol.instance,
                                        &(i2cProtocol.device),

                                        (const uint8_t*)cmd,
                                        ArraySize(cmd),

                                        (uint8_t*)dummyBuf,
                                        ArraySize(dummyBuf),

                                        i2cProtocol.timeout
                                      );
  }

  else
  {
    while ( samIdx < *sampleNum )
    {
      switch ( settings.mode )
      {
        case modeHR:        {
                              if ( NULL == redData )
                              {
                                return STATUS_MAXIM_PARAM_ERROR;
                              }
                              else
                              {
                                devStatus |= MAXIM_ReadFIFO( &( redData[ samIdx++ ] ) ); // RED diode
                              }

                              break;
                            }

        case modeSPO2:      {
                              if  (
                                        ( NULL == redData )
                                    ||  ( NULL == irData )
                                  )
                              {
                                return STATUS_MAXIM_PARAM_ERROR;
                              }
                              else
                              {
                                devStatus |= MAXIM_ReadFIFO( &( redData[ samIdx++ ] ) ); // RED diode
                                devStatus |= MAXIM_ReadFIFO( &( irData[ samIdx++ ] ) );  // IR diode
                              }

                              break;
                            }

        case modeMultiLED:  {
                              /**
                               * read data
                               */

                              for ( uint8_t bufIdx = 0; bufIdx < currentActiveSlots; bufIdx++ )
                              {
                                devStatus |= MAXIM_ReadFIFO( &( ledBuffers[ bufIdx ][ samIdx++ ] ) );
                              }

                              break;
                            }

        default: {}
      }
    }
  }

  if ( STATUS_MAXIM_SUCCESS != devStatus )
  {
    catch(11);
    return STATUS_MAXIM_ERROR;
  }
  else
  {
    return STATUS_MAXIM_SUCCESS;
  }
}

/**
 * find the HR peak in the desired part of the spectrum
 * @param  spectrum  heart-rate frequenct spectrum
 * @param  minFreq   lower frequency border
 * @param  maxFreq   upper frequency border
 * @param  heartRate heart rate to be calculated
 * @return           status flag
 */
statusMAXIM_t MAXIM_GetHR (
                            float32_t* spectrum,
                             float32_t minFreq,
                             float32_t maxFreq,
                            float32_t* heartRate
                          )
{
  uint16_t
    selectedSamplerate = 0;

  *heartRate = -1;

  switch ( settings.sampleRate )
  {
    case sampleRate_50:   {
                            selectedSamplerate = 50 / ( 1 << settings.oversample );
                            break;
                          }

    case sampleRate_100:  {
                            selectedSamplerate = 100 / ( 1 << settings.oversample );
                            break;
                          }

    case sampleRate_200:  {
                            selectedSamplerate = 200 / ( 1 << settings.oversample );
                            break;
                          }

    case sampleRate_400:  {
                            selectedSamplerate = 400 / ( 1 << settings.oversample );
                            break;
                          }

    case sampleRate_800:  {
                            selectedSamplerate = 800 / ( 1 << settings.oversample );
                            break;
                          }

    case sampleRate_1000: {
                            selectedSamplerate = 1000 / ( 1 << settings.oversample );
                            break;
                          }

    case sampleRate_1600: {
                            selectedSamplerate = 1600 / ( 1 << settings.oversample );
                            break;
                          }

    case sampleRate_3200: {
                            selectedSamplerate = 3200 / ( 1 << settings.oversample );
                            break;
                          }
    default:  {
                return STATUS_MAXIM_PARAM_ERROR;
              }
  }

  uint16_t
    minIdx = ( uint16_t ) floor( minFreq * MAXIM_FFT_SIZE / selectedSamplerate ),
    maxIdx = ( uint16_t ) ceil ( maxFreq * MAXIM_FFT_SIZE / selectedSamplerate );

  uint16_t
    currPeak;

  uint32_t
    *peaks  = NULL,
    peakIdx = 0;

  peaks = (uint32_t*) malloc( floor( (maxIdx-minIdx)/2 ) * sizeof( uint32_t ) );
  if ( NULL == peaks )
  {
    return STATUS_MAXIM_INIT_ERROR;
  }

  /**
   * find all the peaks in the [ 45 - 180 ] bpm range,
   * then find the biggest one among them
   */

  for ( uint16_t i = minIdx+1; i < maxIdx; i++ )
  {
    if IsPeak( spectrum, i )
    {
      // add the value to the peaks' array
      peaks[ peakIdx++ ] = i;
    }
  }

  // if no peaks found, exit now
  if ( 0 == peakIdx )
  {
    free( peaks );
    return STATUS_MAXIM_ERROR;
  }

  else
  {
//    *heartRate = -1;
    currPeak   = peaks[0];

    if ( peakIdx > 1 )
    {
      for ( uint16_t i = 1; i < peakIdx; i++ )
      {
        if ( spectrum [ currPeak ] < spectrum[ peaks[i] ] )
        {
          currPeak = peaks[i];
        }
      }
    }

    free( peaks );

    // calculate heart rate, if the peak is large enough
    if ( spectrum[ currPeak ] > MAXIM_PEAK_THRESHOLD )
    {
      // convert to BPM
      *heartRate = 60 * ( ( (float32_t)currPeak * selectedSamplerate ) / MAXIM_FFT_SIZE );
      return STATUS_MAXIM_SUCCESS;
    }
    else
    {
      return STATUS_MAXIM_ERROR;
    }
  }
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
void hr_fmtDef2Float(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{
  /**
   * helper pointers
   */

  float32_t*
    input = (float32_t*)src;
  float*
    output = (float*)dst;

  // convert data
  output[idx] = (float)( input[idx] );
}

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hr_fmtDef2Me (
                    const void* src,
                          void* dst,
                       uint32_t idx
                  )
{
  /**
   * helper pointers
   */

  float32_t*
    input = (float32_t*)src;
  mE_t*
    output = (mE_t*)dst;

  // convert data
  output[idx] = (mE_t)( round( input[idx] ) *100 );
}
