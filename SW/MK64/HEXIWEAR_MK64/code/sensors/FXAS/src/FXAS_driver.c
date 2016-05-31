/**
 * \file FXAS_driver.c
 * \version 1.00
 * \brief this file contains sensor FXAS21002's functionality
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

#include "fsl_i2c_hal.h"
#include "fsl_i2c_master_driver.h"
#include "fsl_os_abstraction.h"

#include "FXAS_driver.h"
#include "FXAS_defs.h"
#include "FXAS_info.h"
#include "FXAS_types.h"

#include "generic_i2c_driver.h"
#include "generic_i2c_types.h"
#include "generic_i2c_info.h"

#include <stdint.h>
#include <string.h>

#include "HEXIWEAR_types.h"

#include "error.h"

/** intern variables */

static uint16_t
  selectedDPS = GFSR_2000DPS;

static handleFXAS_t
  self;

static settingsFXAS_t
  settings;

/** sensitivity coefficients */

static float
  gyro_sensCoefs[] =  {
                        0.0625,    // 1000 dps
                        0.03125,   // 500  dps
                        0.015625,  // 250  dps
                        0.0078125  // 125  dps
                      };

/**
 * initialize the sensor
 * @param  fxasHandle    handle to be populated with sensor info
 * @param  fxasSettings  user settings
 * @return  status flag
 */
fxas_status_t FXAS_Init(
                                handleFXAS_t* fxasHandle,
                        const settingsFXAS_t* fxasSettings
                      )
{
  /**
   * initialize intern structures,
   * which will be used from now on
   */

  memcpy( (void*)&self,     (void*)fxasHandle,   sizeof(self) );
  memcpy( (void*)&settings, (void*)fxasSettings, sizeof(settings) );

  statusI2C_t
    status = I2C_Init( &(self.protocol), settings.address, settings.baudRate_kbps );

  if ( STATUS_I2C_SUCCESS != status )
  {
    return STATUS_FXAS_INIT_ERROR;
  }

  else
  {
    /** put the sensor in the standby mode to change registers */
    FXAS_GotoStandby();

    genericI2cHandle_t
      i2cProtocol = self.protocol;

    statusI2C_t
      devStatus = STATUS_I2C_SUCCESS;

    /** set up the scale range in [dps] (degrees per second) */
    selectedDPS = settings.fsr;
    devStatus |= I2C_WriteReg( &i2cProtocol, FXAS_H_CTRL_REG0, selectedDPS );

    /** setup the data rate bits [4:2] */
    devStatus |= I2C_WriteReg( &i2cProtocol, FXAS_H_CTRL_REG1, settings.odr << 2);

    /** disable FIFO, route FIFO and rate threshold interrupts to INT2, enable data ready interrupt, route to INT1 */
    /** active HIGH, push-pull output driver on interrupts */
    devStatus |= I2C_WriteReg( &i2cProtocol, FXAS_H_CTRL_REG2, 0x0E );

    /** set up rate threshold detection; at max rate threshold = FSR; rate threshold = THS*FSR/128 */
    devStatus |= I2C_WriteReg( &i2cProtocol, FXAS_H_RT_CFG,   0x07);        /** enable rate threshold detection on all axes */
    devStatus |= I2C_WriteReg( &i2cProtocol, FXAS_H_RT_THS,   0x00 | 0x0D); /** unsigned 7-bit THS, set to one-tenth FSR; set clearing debounce counter */
    devStatus |= I2C_WriteReg( &i2cProtocol, FXAS_H_RT_COUNT, 0x04);        /** set to 4 (can set up to 255) */

    if ( STATUS_I2C_SUCCESS != devStatus )
    {
      catch( CATCH_MOTION );
      return STATUS_FXAS_PROTOCOL_ERROR;
    }

    else
    {
      /** set the sensor to active mode */
      FXAS_SetActive();
      return STATUS_FXAS_SUCCESS;
    }
  }
}

/**
 * turn off the sensor
 * @return sensor's status
 */
fxas_status_t FXAS_Deinit()
{
  statusI2C_t
    status = I2C_Deinit( &(self.protocol) );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch( CATCH_MOTION );
    return STATUS_FXAS_PROTOCOL_ERROR;
  }

  else
  {
    return status;
  }
}

/**
 * read raw data from the sensor
 * @param  sensorData pointer where to save sensor's data
 * @return            status flag
 */
fxas_status_t FXAS_ReadRawData ( int16_t* sensorData )
{
  uint8_t
    cmd[1] =  { FXAS_H_OUT_X_MSB };

  dataFXAS_t
    fxasData;

  genericI2cHandle_t
    i2cProtocol = self.protocol;

  i2c_status_t
    status = I2C_DRV_MasterReceiveDataBlocking(
                                                i2cProtocol.instance,
                                                &(i2cProtocol.device),

                                                cmd,
                                                1,

                                                (uint8_t*)&fxasData,
                                                sizeof(dataFXAS_t),

                                                i2cProtocol.timeout
                                              );

  if( kStatus_I2C_Success != status )
  {
    sensorData[0] = 0;
    sensorData[1] = 0;
    sensorData[2] = 0;

    return STATUS_FXAS_PROTOCOL_ERROR;
  }

  else
  {
    /** gyro data: 16-bit 2's complement data */

    /** get gyro data */
    sensorData[0] = (int16_t)( (fxasData.gyroXMSB << 8) | fxasData.gyroXLSB );
    sensorData[1] = (int16_t)( (fxasData.gyroYMSB << 8) | fxasData.gyroYLSB );
    sensorData[2] = (int16_t)( (fxasData.gyroZMSB << 8) | fxasData.gyroZLSB );

    return STATUS_FXAS_SUCCESS;
  }
}

/**
 * put the FXAS21002C into standby mode
 * standby mode is necessary before attempting to modify most of the registers
 *
 * @return status flag
 */
fxas_status_t FXAS_GotoStandby()
{
  uint8_t
    regVal;

  genericI2cHandle_t
    i2cProtocol = self.protocol;

  statusI2C_t
    status = STATUS_I2C_SUCCESS;

  status |= I2C_ReadReg( &i2cProtocol, FXAS_H_CTRL_REG1, &regVal );

  // clear bits 0 and 1 to enter standby mode
  status |= I2C_WriteReg( &i2cProtocol, FXAS_H_CTRL_REG1, regVal & ~0x03 );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch( CATCH_MOTION );
    return STATUS_FXAS_PROTOCOL_ERROR;
  }
  else
  {
    return STATUS_FXAS_SUCCESS;
  }
}

/**
* put the FXAS21002C into active mode
 * it's necessary to be in this mode to output data
 * @return status flag
 */
fxas_status_t FXAS_SetActive()
{
  uint8_t
    regVal;

  genericI2cHandle_t
    i2cProtocol = self.protocol;

  statusI2C_t
    status = STATUS_I2C_SUCCESS;

  status |= I2C_ReadReg( &i2cProtocol, FXAS_H_CTRL_REG1, &regVal );

  /** clear bits 0 and 1; standby mode */
  status |= I2C_WriteReg( &i2cProtocol, FXAS_H_CTRL_REG1, regVal & ~0x03 );

  /** set bit 1 to 1; active mode, data acquisition enabled */
  status |= I2C_WriteReg( &i2cProtocol, FXAS_H_CTRL_REG1, regVal | 0x02 );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch( CATCH_MOTION );
    return STATUS_FXAS_PROTOCOL_ERROR;
  }
  else
  {
    return STATUS_FXAS_SUCCESS;
  }
}

/**
 * set the FXAS21000 to Ready mode
 * it's necessary to be in this mode to output data
 * @return status flag
 */
fxas_status_t FXAS_GetReady()
{
  uint8_t
    regVal;

  statusI2C_t
    status = STATUS_I2C_SUCCESS;

  status |= I2C_ReadReg ( &(self.protocol), FXAS_H_CTRL_REG1, &regVal );

  /** clear bits 0 and 1; standby mode */
  status |= I2C_WriteReg( &(self.protocol), FXAS_H_CTRL_REG1, regVal & ~0x03 );

  /** and then set bit 0 to 1; ready mode, no data acquisition yet */
  status |= I2C_WriteReg( &(self.protocol), FXAS_H_CTRL_REG1, regVal | 0x01 );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch( CATCH_MOTION );
    return STATUS_FXAS_PROTOCOL_ERROR;
  }
  else
  {
    return STATUS_FXAS_SUCCESS;
  }
}

/**
 * reset the module
 */
void FXAS_SoftReset()
{
  uint8_t
    foo;

  genericI2cHandle_t
    i2cProtocol = self.protocol;

  statusI2C_t
    status = STATUS_I2C_SUCCESS;

  /** set reset bit to 1 to assert software reset to zero at end of boot process */
  status |= I2C_WriteReg( &i2cProtocol, FXAS_H_CTRL_REG1, 0x20 );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch( CATCH_MOTION );
  }

  else
  {
    OSA_TimeDelay(100);

    /** wait for boot end flag to be set */
    do
    {
      status = I2C_ReadReg( &i2cProtocol, FXAS_H_INT_SRC_FLAG, &foo);
      if ( STATUS_I2C_SUCCESS != status )
      {
        catch( CATCH_MOTION );
      }
    } while ( 0 == ( foo & 0x08 ) );
  }
}

/**
 * get current sensitivity
 * @return current sensitivity
 */
float FXAS_GetSens()
{
  return gyro_sensCoefs[selectedDPS];
}

/** formatting functions */

/**
 * format data from raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void gyro_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
  /** helper pointers */
  int16_t*
    input  = (int16_t*)src;
  float*
    output = (float*)dst;

  /** convert data */
  output[idx] = (float)input[idx] * gyro_sensCoefs[selectedDPS];
}

/**
 * format data from raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void gyro_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{
  /** helper pointers */
  int16_t*
    input  = (int16_t*)src;
  mE_t*
    output = (mE_t*)dst;

  /** convert data */
  output[idx] = (mE_t)( ( (float)input[idx] * gyro_sensCoefs[selectedDPS] ) /* * 100 */ );
}

/**
 * format raw to byte - currently unimplemented
 */
void gyro_fmtDef2Byte   (
							const void* src,
								  void* dst,
							   uint32_t idx
						)
{}
