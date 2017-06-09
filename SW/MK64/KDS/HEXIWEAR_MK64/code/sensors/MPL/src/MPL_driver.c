/**
 * \file MPL_driver.c
 * \version 1.00
 * \brief this file contains sensor MPL3115A2's implemented functionality
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

#include "MPL_driver.h"

#include "fsl_i2c_master_driver.h"
#include "generic_i2c_driver.h"
#include "FS_I2C.h"

#include "sensor_types.h"

#include "HEXIWEAR_types.h"
#include "string.h"

#include "error.h"

/**
 * intern variables
 */

// variable which denotes the sensor working as altimeter/barometer
static modeMPL_t
  selectedMode = MPL_MODE_PRESSURE;

static uint16_t
  selectedSampleRate  = 0xA5A5,
  selectedDelay       = 0xA5A5;

static uint16_t
  // oversample factor
  overSampleFactors[] = { 1,  2,  4,  8, 16,  32,  64, 128 },
  // min. time between data samples in [ms]
  overSampleDelays[]  = { 6, 10, 18, 34, 66, 130, 258, 512 };


static handleMPL_t
  self;

static settingsMPL_t
  settings;

/**
 * intern functions
 */

/**
 * visible functions
 */

/**
 * initialize underlying protocol and other stuff
 */
mpl_status_t MPL_Init(
                              handleMPL_t* mplHandle,
                      const settingsMPL_t* mplSettings
                    )
{
  /**
   * initialize intern structures,
   * which will be used from now on
   */

  memcpy( (void*)&self,     (void*)mplHandle,   sizeof(self) );
  memcpy( (void*)&settings, (void*)mplSettings, sizeof(settings) );

  statusI2C_t
    status = I2C_Init( &(self.protocol), settings.address, settings.baudRate_kbps );

  if ( STATUS_I2C_SUCCESS != status )
  {
    return STATUS_MPL_INIT_ERROR;
  }

  else
  {
    mpl_status_t
      devStatus = STATUS_MPL_SUCCESS;

    // goto standby
    devStatus |= MPL_GotoStandby();

    // set the mode
    devStatus |= MPL_SetMode( settings.mode );

    // set over-sampling
    devStatus |= MPL_SetOversampleRate( settings.oversample );

    // enable the flags
    devStatus |= MPL_EnableEventFlags();

    // goto active state
    devStatus |= MPL_SetActive();

    if ( STATUS_MPL_SUCCESS != devStatus )
    {
      catch(8);
      return STATUS_MPL_ERROR;
    }

    else
    {
      return STATUS_MPL_SUCCESS;
    }
  }
}

/**
 * shutdown the sensor
 */
mpl_status_t MPL_Deinit()
{
  statusI2C_t
    status = I2C_Deinit( &(self.protocol) );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(8);
    return STATUS_MPL_PROTOCOL_ERROR;
  }

  else
  {
    return STATUS_MPL_SUCCESS;
  }
}

/**
 * software reset
 * the reset mechanism can be enabled in standby and active mode
 * when this bit is enabled, the reset mechanism resets all functional block registers and loads the respective internal registers
 * with default values
 * if the system was already in standby mode, the reboot process will immediately begin; else if the system was in active
 * mode, the boot mechanism will automatically transition the system from active mode to standby mode, and only then can the
 * reboot process begin
 */
mpl_status_t MPL_SoftReset()
{
  uint8_t
    counter         = 0,
    controlSettings = 0,
    cmd[1]          =   {
                          MPL_CTRL_REG1
                        };

  // read current settings
  statusI2C_t
    status = I2C_ReadReg( &(self.protocol), MPL_CTRL_REG1, &controlSettings);
  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(8);
    return STATUS_MPL_PROTOCOL_ERROR;
  }

  else
  {
    // set RST bit and write it back
    controlSettings |= ( 1 << MPL_RST_SHIFT );
    i2c_status_t
      i2cStatus = I2C_DRV_MasterSendDataBlocking(
                                                  self.protocol.instance, // number of i2c module being used
                                                  &(self.protocol.device),   // device-specific settings

                                                  cmd,   	           // command to send
                                                  1,                 // command size in [B]

                                                  &controlSettings,  // data-buffer to use for reception
                                                  1,                 // data size in [B]

                                                  OSA_WAIT_FOREVER
                                                );
    if ( kStatus_I2C_Success != i2cStatus )
    {
      catch(8);
      return STATUS_MPL_PROTOCOL_ERROR;
    }

    else
    {
      // by the end of the boot process the RST bit should be de-asserted to 0; check for it
      while (1)
      {
        status = I2C_ReadReg( &(self.protocol), MPL_CTRL_REG1, &controlSettings);
        if ( STATUS_I2C_SUCCESS != status )
        {
          catch(8);
          return STATUS_MPL_PROTOCOL_ERROR;
        }

        else
        {
          if ( 0 == ( controlSettings & ( 1 << MPL_RST_SHIFT ) ) )
          {
            return STATUS_MPL_SUCCESS;
          }
          else
          {
            // error out after ~0.5 s for a read
            if ( ++counter > 5 )
            {
              catch(8);
              return STATUS_MPL_TIMEOUT;
            }
          }
        }
      }
    }
  }
}

 /**
  * clears then sets the OST bit which causes the sensor to immediately take another reading,
  * necessary to sample faster than 1Hz
  */
mpl_status_t MPL_ToggleOneShot()
{
  uint8_t
    controlSettings = 0;

  // read current settings
  statusI2C_t
    status = I2C_ReadReg( &(self.protocol), MPL_CTRL_REG1, &controlSettings);

  // clear OST bit and write it back
  controlSettings &= ~( 1 << MPL_OST_SHIFT );
  status |= I2C_WriteReg( &(self.protocol), MPL_CTRL_REG1, controlSettings);

  // read again settings, just to be safe
  status |= I2C_ReadReg( &(self.protocol), MPL_CTRL_REG1, &controlSettings);

  // set OST bit and write it back
  controlSettings |= ( 1 << MPL_OST_SHIFT );
  status |= I2C_WriteReg( &(self.protocol), MPL_CTRL_REG1, controlSettings);

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(8);
    return STATUS_MPL_PROTOCOL_ERROR;
  }

  else
  {
    return STATUS_MPL_SUCCESS;
  }
}

/**
 * set the device to be barometer or altimeter
 *
 * @param mode 1 - barometer
 *             0 - altimeter
 */
mpl_status_t MPL_SetMode (
                          modeMPL_t mode
                        )
{
  uint8_t
    controlSettings;

  // read current settings
  statusI2C_t
    status = I2C_ReadReg( &(self.protocol), MPL_CTRL_REG1, &controlSettings);

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(8);
    return STATUS_MPL_PROTOCOL_ERROR;
  }

  else
  {
    // set/clear ALT bit
    controlSettings = ( mode ) ?
                        controlSettings |  ( 1 << 7 ) : // altimeter
                        controlSettings & ~( 1 << 7 );  // barometer

    status = I2C_WriteReg( &(self.protocol), MPL_CTRL_REG1, controlSettings);
    if ( STATUS_I2C_SUCCESS != status )
    {
      catch(8);
      return STATUS_MPL_PROTOCOL_ERROR;
    }

    else
    {
      // update the static variable
      selectedMode = mode;
      return STATUS_MPL_SUCCESS;
    }
  }
}

/**
 * put the sensor in stand-by mode
 * this is needed so that we can modify major control registers
 */
mpl_status_t MPL_GotoStandby()
{
  uint8_t
    controlSettings;

  // read current settings
  statusI2C_t
    status = I2C_ReadReg( &(self.protocol), MPL_CTRL_REG1, &controlSettings);

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(8);
    return STATUS_MPL_PROTOCOL_ERROR;
  }

  else
  {
    // clear SBYB bit for entering stand-by mode
    controlSettings &= ~( 1 << MPL_SBYB_SHIFT );
    status = I2C_WriteReg( &(self.protocol), MPL_CTRL_REG1, controlSettings);
    if ( STATUS_I2C_SUCCESS != status )
    {
      catch(8);
      return STATUS_MPL_PROTOCOL_ERROR;
    }

    else
    {
      return STATUS_MPL_SUCCESS;
    }
  }
}

/**
 * put the sensor in active mode
 */
mpl_status_t MPL_SetActive()
{
  uint8_t
    controlSettings;

  // read current settings
  statusI2C_t
    status = I2C_ReadReg( &(self.protocol), MPL_CTRL_REG1, &controlSettings);

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(8);
    return STATUS_MPL_PROTOCOL_ERROR;
  }

  else
  {
    // set SBYB bit for entering active mode
    controlSettings |= ( 1 << MPL_SBYB_SHIFT );
    status = I2C_WriteReg( &(self.protocol), MPL_CTRL_REG1, controlSettings);
    if ( STATUS_I2C_SUCCESS != status )
    {
      catch(8);
      return STATUS_MPL_PROTOCOL_ERROR;
    }
    else
    {
      return STATUS_MPL_SUCCESS;
    }
  }
}

/**
 * set the over-sample rate
 * datasheet calls for 128, but you can set it from 1 to 128 samples
 * The higher the oversample rate, the greater the time between data samples
 */
mpl_status_t MPL_SetOversampleRate (
                                    uint8_t sampleRate
                                  )
{
  if (sampleRate > 7)
  {
    // rate cannot be larger than 7
    sampleRate = 7;
  }

  selectedSampleRate = overSampleFactors[sampleRate];
  selectedDelay      = overSampleDelays[sampleRate];

  uint8_t
    controlSettings;

  // read current settings
  statusI2C_t
    status = I2C_ReadReg( &(self.protocol), MPL_CTRL_REG1, &controlSettings);
  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(8);
    return STATUS_MPL_PROTOCOL_ERROR;
  }

  else
  {
    // clear out old OS bits
    controlSettings &= ~MPL_OS_MASK;
    // mask in new OS bits
    controlSettings |= ( sampleRate << MPL_OS_SHIFT );

    status = I2C_WriteReg( &(self.protocol), MPL_CTRL_REG1, controlSettings);
    if ( STATUS_I2C_SUCCESS != status )
    {
      catch(8);
      return STATUS_MPL_PROTOCOL_ERROR;
    }
    else
    {
      return STATUS_MPL_SUCCESS;
    }
  }
}

/**
 * enables the pressure and temp measurement event flags so that we can test against them
 * this is recommended in datasheet during setup
 */
mpl_status_t MPL_EnableEventFlags()
{
  uint8_t
    controlSettings = 0x07;

  // read current settings
  statusI2C_t
    status = I2C_WriteReg( &(self.protocol), PT_DATA_CFG, controlSettings);
  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(8);
    return STATUS_MPL_PROTOCOL_ERROR;
  }

  else
  {
    return STATUS_MPL_SUCCESS;
  }
}

/**
 * read sensor raw data
 */
mpl_status_t MPL_ReadRawData (
                              modeMPL_t mode,
                               int16_t* sensorData
                            )
{
  mpl_status_t
    status = STATUS_MPL_SUCCESS;

  uint8_t
    dataReadyFlag,
    dataReadyRegAddr;

  uint8_t
    statVal     = 0,
    bytesToRead = 0,
    *readData;

  // buffer for pressure/altitude and temperature sensor
  dataMPL_t
    mplData;

  /**
   * set the new working mode, if given one
   */

  if  (
            ( mode > MPL_MODE_TEMPERATURE )
        &&  ( mode < MPL_MODE_CURRENT )
      )
  {
    return STATUS_MPL_INIT_ERROR;
  }

  else if (
                ( MPL_MODE_CURRENT != mode )
            &&      ( selectedMode != mode )
          )
  {
    // goto standby
    status |= MPL_GotoStandby();
    // set the mode
    status |= MPL_SetMode(mode);
    // goto active state
    status |= MPL_SetActive();
  }

  if ( STATUS_MPL_SUCCESS != status )
  {
    catch(8);
    return STATUS_MPL_ERROR;
  }

  else
  {
    /**
     * prepare for reading data
     */

    switch ( selectedMode )
    {
      case MPL_MODE_PRESSURE:
      case MPL_MODE_ALTITUDE:     {
                                    dataReadyFlag     = 1 << MPL_PDR_SHIFT;
                                    dataReadyRegAddr  = OUT_P_MSB;
                                    bytesToRead       = 3;
                                    readData          = (uint8_t*)&(mplData.presAltDataMSB);
                                    break;
                                  }

      case MPL_MODE_TEMPERATURE:  {
                                    dataReadyFlag     = 1 << MPL_TDR_SHIFT;
                                    dataReadyRegAddr  = OUT_T_MSB;
                                    bytesToRead       = 2;
                                    readData          = (uint8_t*)&(mplData.tempDataMSB);
                                    break;
                                  }

      default:  {}
    }

    statusI2C_t
      status = I2C_ReadReg( &(self.protocol), REG_STATUS, &statVal);
    if ( STATUS_I2C_SUCCESS != status )
    {
      catch(8);
      return STATUS_MPL_PROTOCOL_ERROR;
    }

    // check PDR/PTR bit; if it's not set, toggle OST
    else if ( 0 == ( statVal & dataReadyFlag ) )
    {
      // toggle the OST bit, causing the sensor to immediately take another reading
      MPL_ToggleOneShot(self);
    }

    // wait for the data acquisition time
//     OSA_TimeDelay(selectedDelay);
//     OSA_TimeDelay( 10 );

    int16_t
      counter = 0;

    // wait for PDR/PTR bit, which indicates that we have new data
    while (1)
    {
      status = I2C_ReadReg( &(self.protocol), REG_STATUS, &statVal);
      if ( STATUS_I2C_SUCCESS != status )
      {
	     return STATUS_MPL_PROTOCOL_ERROR;
      }

      else
      {
      	if ( 0 == ( statVal & dataReadyFlag ) )
      	{
      	  // error out after more than 0.5s for a read op
      	  if ( ++counter > 5 )
      	  {
      	    return STATUS_MPL_TIMEOUT;
      	  }
      	}

      	else
      	{
      	  // continue with the program
      	  break;
      	}
      }
    }

    /**
     * read sensor data
     */

    genericI2cHandle_t
      i2cProtocol = self.protocol;

    i2c_status_t
      i2cStatus = I2C_DRV_MasterReceiveDataBlocking (
                                                      i2cProtocol.instance,  // I2C module being used
                                                      &(i2cProtocol.device), // device-specific settings

                                                      (uint8_t*)&dataReadyRegAddr, // command to send
                                                      sizeof(dataReadyRegAddr),    // command size in [B]

                                                      readData,    // data-buffer to use for reception
                                                      bytesToRead, // data size in [B]

                                                      i2cProtocol.timeout // default timeout value
                                                    );

    if ( kStatus_I2C_Success != i2cStatus )
    {
      catch(8);
      return STATUS_MPL_PROTOCOL_ERROR;
    }

    else
    {

      /**
       * save data
       */

      switch ( selectedMode )
      {
        // pressure value is a Q18.2 right-aligned number in [Pa]
        case MPL_MODE_PRESSURE:
        // altitude value is a Q16.4 right-aligned number in [m]
        case MPL_MODE_ALTITUDE:     {
                                      // save pressure/altitude
                                      uint32_t
                                        foo = (
                                        //                  MSB
                                                  ( mplData.presAltDataMSB << 16 )
                                        //                  CSB
                                                | ( mplData.presAltDataCSB << 8 )
                                        //                  LSB
                                                | ( mplData.presAltDataLSB )
                                        // discard first 4 bits
                                              ) >> 4;

                                      // pack it into the first two integers in the output array
                                      memcpy( (void*)sensorData, (const void*)&foo, sizeof(foo) );

                                      break;
                                    }

        // temperature value is a Q8.4 right-aligned number in [C]
        case MPL_MODE_TEMPERATURE:  {
                                      // save temperature                  MSB                            LSB
                                      *sensorData = (int16_t)( ( mplData.tempDataMSB << 4 ) | ( mplData.tempDataLSB >> 4 ) );

                                      break;
                                    }

        default:  {}
      }
    }

    return STATUS_MPL_SUCCESS;
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
void pres_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
  /**
   * helper pointers
   */
  int32_t*
    input = (int32_t*)src;
  float*
    output = (float*)dst;

  // convert data
  output[idx] = (float)input[idx] / 4.0;
}

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void pres_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{
  /**
   * helper pointers
   */
  int32_t*
    input = (int32_t*)src;
  mE_t*
    output = (mE_t*)dst;

  // convert data to [kPa]
  output[idx] = (mE_t)( ( (float)input[idx] / (4.0*1000) ) * 100 );
}

/**
 * format raw to byte - currently unimplemented
 */
void pres_fmtDef2Byte(
						const void* src,
							  void* dst,
						   uint32_t idx
					)
{}
