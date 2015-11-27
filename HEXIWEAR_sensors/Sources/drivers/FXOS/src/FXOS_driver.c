/**
 * FXOS8700 drivers
 * Project KWAP, 2015
 */

#include "fsl_i2c_hal.h"
#include "fsl_i2c_master_driver.h"
#include "fsl_os_abstraction.h"

#include "FXOS_driver.h"
#include "FXOS_info.h"
#include "FXOS_types.h"

#include "generic_i2c_driver.h"
#include "generic_i2c_types.h"
#include "i2cCom1.h"

#include <stdint.h>
#include <string.h>

#include "HEXIWEAR_types.h"

#include "string.h"

#include "error.h"

/**
 * intern variables
 */

static accRangeFXOS_t
  selectedRange;

static handleFXOS_t
  self;

static settingsFXOS_t
  settings;

/**
 * sensitivity coefficients
 */

static float
  acc_sensCoef[] =  {
                      // acceleration
                      0.000244, // range: +- 2g
                      0.000488, // range: +- 4g
                      0.000976  // range: +- 8g
                    };

static float
  mag_sensCoef[] =  {
                      // magnetometer's data
                      1e-1 // 0.1uT/LSB
                    };

/**
 * intern functions
 */

/**
 * visible functions
 */

/**
 * initialize the FXOS8700
 * @param  self     [description]
 * @param  settings [description]
 * @return          [description]
 */
statusFXOS_t FXOS_Init(
                                handleFXOS_t* fxosHandle,
                        const settingsFXOS_t* fxosSettings
                      )
{
  statusFXOS_t
    status = I2C_Init( &(fxosHandle->protocol), fxosSettings->address );

  if ( STATUS_FXOS_SUCCESS != status )
  {
    return status;
  }

  else
  {

    /**
     * initialize intern structures,
     * which will be used from now on
     */

    memcpy( (void*)&self, (void*)fxosHandle, sizeof(self) );
    memcpy( (void*)&settings, (void*)fxosSettings, sizeof(settings) );

    statusI2C_t
      devStatus = STATUS_I2C_SUCCESS;

    // set ODR
      if  (
             ( settings.odr <= fxosODR7 )
          && ( settings.odr >= fxosODR0 )
        )
      {
        devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, DR_MASK, settings.odr );
      }

      else
      {
          return STATUS_FXOS_PARAM_ERROR;
      }

    // set OSR
    if  (
             ( settings.osr <= fxosOSR7 )
          && ( settings.osr >= fxosOSR0 )
        )
    {
      devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_M_CTRL_REG1, M_OSR_MASK, settings.osr );
    }

    else
    {
      return STATUS_FXOS_PARAM_ERROR;
    }

    // set mode
    if  (
           ( settings.mode <= fxosBoth )
        && ( settings.mode >= fxosAccOnly )
      )
    {
      devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_M_CTRL_REG1, M_HMS_MASK, settings.mode );
    }

    else
    {
        return STATUS_FXOS_PARAM_ERROR;
    }

    // set scale-mode
    if  (
             ( settings.range <= fxosRange8g )
          && ( settings.range >= fxosRange2g )
        )
    {
      selectedRange = settings.range;
      devStatus |= I2C_ModifyReg( &(self.protocol), XYZ_DATA_CFG_REG, FS_MASK, settings.range );
    }

    else
    {
      return STATUS_FXOS_PARAM_ERROR;
    }

    // activate FXOS8700
    devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, ACTIVE_MASK, ACTIVE_MASK );

    if ( STATUS_I2C_SUCCESS != devStatus )
    {
      catch(6);
      return STATUS_FXOS_PROTOCOL_ERROR;
    }

    else
    {
      return STATUS_FXOS_SUCCESS;
    }
  }
}

/**
 * turn off the sensor
 * @return [description]
 */
statusFXOS_t FXOS_Deinit()
{
  statusI2C_t
    status = I2C_Deinit( &(self.protocol) );

  if ( STATUS_I2C_SUCCESS != status )
  {
    catch(6);
    return STATUS_FXOS_PROTOCOL_ERROR;
  }

  else
  {
    return status;
  }
}

/**
 * read raw sensor data
 * Description   : Read sensor data value from FXOS8700
 * The reading process is through I2C
 */
statusFXOS_t FXOS_ReadRawData (
                                int16_t* sensorData // 6-element array
                              )
{
  uint8_t
    cmd[1] =  {
                OUT_X_MSB_REG
              };

  dataFXOS_t
    fxosData;

  i2c_status_t
    status = I2C_DRV_MasterReceiveDataBlocking(
                                                self.protocol.instance,
                                                &( self.protocol.device ),

                                                cmd,
                                                1,

                                                (uint8_t*)&fxosData,
                                                sizeof(fxosData),

                                                self.protocol.timeout
                                              );

  if ( kStatus_I2C_Success != status )
  {
    catch(6);
    return STATUS_FXOS_PROTOCOL_ERROR;
  }

  else
  {
    /**
     * acc-data is 14-bit left-justified 2's complement data
     * mag-data is 16-bit 2's complement data
     */

    // get acceleration data
    sensorData[0] = (int16_t)( (fxosData.accDataXMSB << 8) | fxosData.accDataXLSB ) >> 2;
    sensorData[1] = (int16_t)( (fxosData.accDataYMSB << 8) | fxosData.accDataYLSB ) >> 2;
    sensorData[2] = (int16_t)( (fxosData.accDataZMSB << 8) | fxosData.accDataZLSB ) >> 2;

    // get magnetometer's data
    sensorData[3] = (int16_t)( (fxosData.magDataXMSB << 8) | fxosData.magDataXLSB );
    sensorData[4] = (int16_t)( (fxosData.magDataYMSB << 8) | fxosData.magDataYLSB );
    sensorData[5] = (int16_t)( (fxosData.magDataZMSB << 8) | fxosData.magDataZLSB );

    return STATUS_FXOS_SUCCESS;
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
void acc_fmtDef2Float (
                        const void* src,
                              void* dst,
                           uint32_t idx
                      )
{
  /**
   * helper pointers
   */

  int16_t*
    input = (int16_t*)src;
  float*
    output = (float*)dst;

  // convert data
  output[idx] = (float)input[idx] * acc_sensCoef[selectedRange];
}

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void acc_fmtDef2Me(
                    const void* src,
                          void* dst,
                       uint32_t idx
                  )
{
  /**
   * helper pointers
   */

  int16_t*
    input = (int16_t*)src;
  mE_t*
    output = (mE_t*)dst;

  // convert data
  output[idx] = (mE_t)( ( (float)input[idx] * acc_sensCoef[selectedRange] ) * 100 );
}

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void mag_fmtDef2Float (
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
  output[idx] = (float)input[idx] * mag_sensCoef[0];
}

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void mag_fmtDef2Me(
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

  // convert data to [uT]
  output[idx] = (mE_t)( ( (float)input[idx] * mag_sensCoef[0] ) * 100 );
}
