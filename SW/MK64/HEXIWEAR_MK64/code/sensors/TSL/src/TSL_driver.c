/**
 * \file TSL_driver.c
 * \version 1.00
 * \brief this file contains sensor TSL2561's implemented functionality
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

#include "TSL_driver.h"
#include "TSL_info.h"

#include "generic_i2c_driver.h"
#include <FS_I2C.h>

#include "HEXIWEAR_types.h"

#include <string.h>
#include "error.h"

/** intern variables */

static handleTSL_t
  self;
static settingsTSL_t
  settings;

static gainTSL_t
  selectedGain = TSL_GAIN_16X;

static integrationTSL_t
  selectedTiming = TSL_INTEGRATION_TIME_13MS;

//static uint16_t
//  samplingDelays[] = { 14, 102, 403 };

/** intern functions */

/** public API */

/**
 * enable the sensor
 */
void TSL_Enable ()
{
  statusI2C_t
    status = I2C_WriteReg( &(self.protocol), TSL_COMMAND_BIT | TSL_REG_CONTROL, TSL_CONTROL_POWERON );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(10);
  }
}

/**
 * disable the sensor
 */
void TSL_Disable()
{
  statusI2C_t
    status = I2C_WriteReg( &(self.protocol), TSL_COMMAND_BIT | TSL_REG_CONTROL, TSL_CONTROL_POWEROFF );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(10);
  }
}

/**
 * initialize the sensor
 * @param  tslHandle    handle to be populated with sensor info
 * @param  tslSettings  user settings
 * @return  status flag
 */
tsl_status_t TSL_Init(
                              handleTSL_t* tslHandle,
                      const settingsTSL_t* tslSettings
                    )
{
  /**
   * initialize the intern structures,
   * which will be used from now on
   */

  memcpy( (void*)&self,     (void*)tslHandle,   sizeof(self) );
  memcpy( (void*)&settings, (void*)tslSettings, sizeof(settings) );

  statusI2C_t
    status = I2C_Init( &(self.protocol), settings.address, settings.baudRate_kbps );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(10);
    return STATUS_TSL_INIT_ERROR;
  }

  else
  {
    // power cycle the module
    TSL_Disable();
    TSL_Enable();

    tsl_status_t
      devStatus = STATUS_TSL_SUCCESS;

    // set default integration time and gain
    devStatus |= TSL_SetGain  ( settings.gain );
    devStatus |= TSL_SetTiming( settings.timing );

    if ( STATUS_TSL_SUCCESS != devStatus )
    {
      catch(10);
      return STATUS_TSL_ERROR;
    }

    else
    {
      return STATUS_TSL_SUCCESS;
    }
  }
}

/**
 * deinit I2C for the sensor
 * @return status flag
 */
tsl_status_t TSL_Deinit()
{
  statusI2C_t
    status = I2C_Deinit( &(self.protocol) );

  if ( STATUS_I2C_SUCCESS == status )
  {
    TSL_Disable();
    catch(10);
    return STATUS_TSL_PROTOCOL_ERROR;
  }

  else
  {
    return STATUS_TSL_SUCCESS;
  }
}

/**
 * set sensor's gain
 * @param  gain desired gain
 * @return      status flag
 */
tsl_status_t TSL_SetGain ( gainTSL_t gain )
{
  statusI2C_t
    status = I2C_WriteReg( &(self.protocol), TSL_COMMAND_BIT | TSL_REG_TIMING, selectedGain | selectedTiming );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(10);
    return STATUS_TSL_PROTOCOL_ERROR;
  }

  else
  {
    selectedGain = gain;
    return STATUS_TSL_SUCCESS;
  }
}

/**
 * set sensor integration time
 * @param  integration integration time
 * @return             status flag
 */
tsl_status_t TSL_SetTiming ( integrationTSL_t integration )
{
  statusI2C_t
    status = I2C_WriteReg( &(self.protocol), TSL_COMMAND_BIT | TSL_REG_TIMING, selectedGain | selectedTiming );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(10);
    return STATUS_TSL_PROTOCOL_ERROR;
  }

  else
  {
    selectedTiming = integration;
    return STATUS_TSL_SUCCESS;
  }
}

/**
 * read raw sensor data
 * @param  channel    TSL channel (red or infrared)
 * @param  sensorData sensor data to be filled
 * @return            status flag
 */
tsl_status_t TSL_ReadRawData (
                              channelTSL_t channel,
                                 uint16_t* sensorData
                            )
{
  statusI2C_t
    status = STATUS_I2C_SUCCESS;

  uint8_t
    regData[1],
    dataLow  = 0,
    dataHigh = 0;

  // wait for the data acquisition time
//  OSA_TimeDelay( samplingDelays[ selectedTiming ]);

  switch ( channel )
  {
    // read ADC channel 0 (Visible and IR)
    case TSL_CHANNEL_FULL:      {
                                  status = I2C_ReadReg( &(self.protocol), TSL_COMMAND_BIT | TSL_REG_CHAN0_LOW, regData);
                                  if ( STATUS_I2C_SUCCESS == status )
                                  {
                                    dataLow = regData[0];
                                  }
                                  else
                                  {
                                    catch(10);
                                    return STATUS_TSL_PROTOCOL_ERROR;
                                  }

                                  status = I2C_ReadReg( &(self.protocol), TSL_COMMAND_BIT | TSL_REG_CHAN0_HIGH, regData);
                                  if ( STATUS_I2C_SUCCESS == status )
                                  {
                                    dataHigh = regData[0];
                                  }
                                  else
                                  {
                                    catch(10);
                                    return STATUS_TSL_PROTOCOL_ERROR;
                                  }

                                  *sensorData++ = ( dataLow | ( (uint16_t)dataHigh << 8 ) );
                                }

    // read ADC channel 1 (IR only)
    case TSL_CHANNEL_INFRARED:  {
                                  status = I2C_ReadReg( &(self.protocol), TSL_COMMAND_BIT | TSL_REG_CHAN1_LOW, regData);
                                  if ( STATUS_I2C_SUCCESS == status )
                                  {
                                    dataLow = regData[0];
                                  }
                                  else
                                  {
                                    catch(10);
                                    return STATUS_TSL_PROTOCOL_ERROR;
                                  }

                                  status = I2C_ReadReg( &(self.protocol), TSL_COMMAND_BIT | TSL_REG_CHAN1_HIGH, regData);
                                  if ( STATUS_I2C_SUCCESS == status )
                                  {
                                    dataHigh = regData[0];
                                  }
                                  else
                                  {
                                    catch(10);
                                    return STATUS_TSL_PROTOCOL_ERROR;
                                  }

                                  *sensorData = ( dataLow | ( (uint16_t)dataHigh << 8 ) );

                                  break;
                                }

    default: {}
  }

  return STATUS_TSL_SUCCESS;
}

/**
 * simplified lux calculation
 * @param  channelValues ADC values from both channels
 * @param  luxVal        value in [lx]
 * @return               status flag
 */
tsl_status_t TSL_CalculateLux(
                              uint16_t* channelValues,
                              uint32_t* luxVal
                            )
{
  uint32_t
    chScale,
    channel0,
    channel1,
    foo,
    ratio;

  uint32_t
    ratio1 = 0;

  uint16_t
    b,
    m;

  uint16_t
    ch0 = channelValues[0],
    ch1 = channelValues[1];

  switch ( selectedTiming )
  {
    // 13.7 msec
    case 0:   {
                chScale = TSL_CHSCALE_TINT0;
                break;
              }

    // 101 msec
    case 1:   {
                chScale = TSL_CHSCALE_TINT1;
                break;
              }

    // no scaling ... integration time = 402ms
    default:  {
                chScale = 1 << TSL_CHSCALE;
                break;
              }
  }

  // scale for gain (1x or 16x)
  if ( 0 == selectedGain )
  {
    chScale <<= 4;
  }

  // scale the channel values
  channel0 = (ch0 * chScale) >> TSL_CHSCALE;
  channel1 = (ch1 * chScale) >> TSL_CHSCALE;

  /**
   * find the ratio of the channel values (Channel1/Channel0)
   * protect against divide by zero
   */

  if ( 0 != channel0 )
  {
    ratio1 = ( channel1 << ( 1 + TSL_RATIO_SCALE ) ) / channel0;
  }

  // round the ratio value
  ratio = ( 1 + ratio1 ) >> 1;

  if  (
           ( ratio >= 0 )
        && ( ratio <= TSL_K1T )
      )
  {
    b = TSL_B1T;
    m = TSL_M1T;
  }

  else if ( ratio <= TSL_K2T )
  {
    b = TSL_B2T;
    m = TSL_M2T;
  }

  else if ( ratio <= TSL_K3T )
  {
    b = TSL_B3T;
    m = TSL_M3T;
  }

  else if ( ratio <= TSL_K4T )
  {
    b = TSL_B4T;
    m = TSL_M4T;
  }

  else if ( ratio <= TSL_K5T )
  {
    b = TSL_B5T;
    m = TSL_M5T;
  }

  else if ( ratio <= TSL_K6T )
  {
    b = TSL_B6T;
    m = TSL_M6T;
  }

  else if ( ratio <= TSL_K7T )
  {
    b = TSL_B7T;
    m = TSL_M7T;
  }

  else if ( ratio > TSL_K8T )
  {
    b = TSL_B8T;
    m = TSL_M8T;
  }

  foo = ( (channel0 * b) - (channel1 * m) );

  // do not allow negative lux value
  if ( foo < 0 )
  {
    foo = 0;
  }

  // round lsb ( 2^(LUX_SCALE-1) )
  foo = foo + ( 1 << (TSL_LUX_SCALE -1) );

  // strip off fractional portion
  *luxVal = foo >> TSL_LUX_SCALE;

  return STATUS_TSL_SUCCESS;
}

/** formatting functions */

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void ambi_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
  /** helper pointers */
  uint16_t*
    input = (uint16_t*)src;
  float*
    output = (float*)dst;

  // convert data
  output[idx] = (float)input[idx];
}

/**
 * format raw to mE format - currently unimplemented
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void ambi_fmtDef2Me(
						const void* src,
							  void* dst,
						   uint32_t idx
					)
{}

/**
 * format raw to byte format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void ambi_fmtDef2Byte	(
                     		const void* src,
                                  void* dst,
							   uint32_t idx
						)
{
  /** helper pointers */
  uint8_t*
    input = (uint8_t*)src;
  uint8_t*
    output = (uint8_t*)dst;

  // convert data
  output[idx] = (uint8_t)( ( input[idx] ) );
}

/**
 * convert lux value to light percentage
 * @param luxVal   value in [lx]
 * @param ambLight value in [%]
 */
void TSL_FormatLux(
					uint32_t luxVal,
					uint8_t* ambLight
				  )
{
//  *ambLight = ( luxVal * 100 ) >> 12;

	if ( luxVal < 128 )
	{
		*ambLight = ( luxVal * 100 ) >> 7;
	}
	else
	{
		*ambLight = 100;
	}
}
