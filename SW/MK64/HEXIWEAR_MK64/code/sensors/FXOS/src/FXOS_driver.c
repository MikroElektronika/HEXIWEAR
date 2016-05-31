/**
 * \file FXOS_driver.c
 * \version 1.00
 * \brief this file contains sensor FXOS8700cq implemented functionality
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

#include "FXOS_driver.h"
#include "FXOS_info.h"
#include "FXOS_types.h"

#include "generic_i2c_driver.h"
#include "generic_i2c_types.h"
#include "FS_I2C.h"

#include <stdint.h>
#include <string.h>

#include "HEXIWEAR_types.h"

#include "string.h"

#include "error.h"

// static uint8_t FXOS_WriteReg(uint8_t reg, uint8_t val);
// static uint8_t FXOS_ReadReg(uint8_t reg, uint8_t *val);
// static uint8_t FXOS_ModifyReg(uint8_t reg, uint8_t clr_mask, uint8_t val);

//static fxos_status_t ConfigureTapEvent();

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
 * sensitivity coefficientsL: [g/LSB] and [uT/LSB]
 */

static float
  accMag_sensCoef[] =   {
                          // acceleration
                          0.000244, // range: +- 2g
                          0.000488, // range: +- 4g
                          0.000976, // range: +- 8g
                          1e-1      // 0.1
                        };

//static float
//  mag_sensCoef[] =  {
//                      // magnetometer's data
//                    };

/**
 * reverese sensitivity for calbiration purposes [LSB/g]
 */
static uint32_t
    acc_reverseSensitivity[] =
    {
        4096, // range: +- 2g
        2048, // range: +- 4g
        1024  // range: +- 8g
    };

static bool
	isTapEnabled = false;

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
fxos_status_t FXOS_Init(
                                handleFXOS_t* fxosHandle,
                        const settingsFXOS_t* fxosSettings
                      )
{
  /**
   * initialize intern structures,
   * which will be used from now on
   */

  memcpy( (void*)&self, (void*)fxosHandle, sizeof(self) );
  memcpy( (void*)&settings, (void*)fxosSettings, sizeof(settings) );

  statusI2C_t
    status = I2C_Init( &(self.protocol), settings.address, settings.baudRate_kbps );

  if ( STATUS_I2C_SUCCESS != status )
  {
    return status;
  }

  else
  {
	statusI2C_t
	  devStatus = STATUS_I2C_SUCCESS;

    // soft reset
//    FXOS_SoftReset();

	 /** wait a bit */
//	OSA_TimeDelay(50);

	 /** go to standby */
	FXOS_GotoStandby();

	// set up Mag OSR and Hybrid mode
	if  ( settings.mode > fxosAccOnly )
	{
		devStatus |= I2C_WriteReg( &(self.protocol), FXOS_M_CTRL_REG1, (M_RST_MASK));
		devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_M_CTRL_REG1, M_OSR_MASK, settings.osr );
	}

	devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_M_CTRL_REG1, M_HMS_MASK, settings.mode );

	// enable hybrid mode auto increment
	if ( fxosBoth == settings.mode )
	{
		devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_M_CTRL_REG2, 0, M_HYB_AUTOINC_MASK );
	}

	// set range
	selectedRange = settings.range;
	devStatus |= I2C_ModifyReg( &(self.protocol), XYZ_DATA_CFG_REG, FS_MASK, settings.range );

	// setup sample rate
	devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, DR_MASK, settings.odr );

	// apply low noise filter
	if ( settings.range <= fxosRange4g )
	{
		devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, 0, LNOISE_MASK );
	}

	FXOS_ConfigureTapEvent();

	// activate the sensor
	FXOS_SetActive();

//	FXOS_CalibrateAcc();
//	FXOS_CalibrateMag();

	if ( STATUS_I2C_SUCCESS != devStatus )
	{
		catch( CATCH_I2C );
	}

	return devStatus;
  }
}

/**
 * turn off the sensor
 * @return [description]
 */
fxos_status_t FXOS_Deinit()
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
fxos_status_t FXOS_ReadRawData (
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
    sensorData[0] = (int16_t)( (int16_t)fxosData.accDataXMSB << 8 | fxosData.accDataXLSB ) >> 2;
    sensorData[1] = (int16_t)( (int16_t)fxosData.accDataYMSB << 8 | fxosData.accDataYLSB ) >> 2;
    sensorData[2] = (int16_t)( (int16_t)fxosData.accDataZMSB << 8 | fxosData.accDataZLSB ) >> 2;

    // get magnetometer's data
    sensorData[3] = (int16_t)( (int16_t)fxosData.magDataXMSB << 8 | fxosData.magDataXLSB );
    sensorData[4] = (int16_t)( (int16_t)fxosData.magDataYMSB << 8 | fxosData.magDataYLSB );
    sensorData[5] = (int16_t)( (int16_t)fxosData.magDataZMSB << 8 | fxosData.magDataZLSB );

    return STATUS_FXOS_SUCCESS;
  }
}

/**
 * accelerometer offset calibration
 */
fxos_status_t FXOS_CalibrateAcc()
{
	int16_t
        accValX,
        accValY,
        accValZ;

    uint8_t
        acc_xOffset,
        acc_yOffset,
        acc_zOffset;


    uint8_t
      cmd[1] =  {
                  OUT_X_MSB_REG
                };

    statusI2C_t
      devStatus = STATUS_I2C_SUCCESS;

    // goto standby
    devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, ACTIVE_MASK, ~ACTIVE_MASK );

    // read only acc data
    i2c_status_t
        status = I2C_DRV_MasterReceiveDataBlocking  (
                                                        self.protocol.instance,
                                                        &( self.protocol.device ),

                                                        cmd,
                                                        1,

                                                        (uint8_t*)&fxosData,
                                                        6,

                                                        self.protocol.timeout
                                                    );

    if ( kStatus_I2C_Success != status )
    {
    	return STATUS_FXOS_PROTOCOL_ERROR;
    }

    // get 14-bit acceleration output values for all 3 axes
    accValX = ( (int16_t)( (int16_t)fxosData.accDataXMSB << 8 | fxosData.accDataXLSB) ) >> 2;
    accValY = ( (int16_t)( (int16_t)fxosData.accDataYMSB << 8 | fxosData.accDataYLSB) ) >> 2;
    accValZ = ( (int16_t)( (int16_t)fxosData.accDataZMSB << 8 | fxosData.accDataZLSB) ) >> 2;

    // compute offset correction values
    acc_xOffset = ( accValX / 8 ) * (-1);
    acc_yOffset = ( accValY / 8 ) * (-1);
    acc_zOffset = ( ( accValZ - acc_reverseSensitivity[ selectedRange ] ) / 8 ) * (-1);

    // save offset values
    devStatus |= I2C_WriteReg( &(self.protocol), FXOS_OFF_X_REG, acc_xOffset );
    devStatus |= I2C_WriteReg( &(self.protocol), FXOS_OFF_Y_REG, acc_yOffset );
    devStatus |= I2C_WriteReg( &(self.protocol), FXOS_OFF_Z_REG, acc_zOffset );

    // activate the module
    devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, ACTIVE_MASK, ACTIVE_MASK );

    if ( STATUS_I2C_SUCCESS == devStatus )
    {
    	return STATUS_FXOS_SUCCESS;
    }

    else
    {
    	catch( CATCH_I2C );
    	return STATUS_FXOS_ERROR;
    }
}

/**
 *  magnetometer offset calibration
 */
fxos_status_t FXOS_CalibrateMag()
{
    int16_t
        magValX,
        magValY,
        magValZ,

        magValX_avg,
        magValY_avg,
        magValZ_avg,

        magValX_min,
        magValY_min,
        magValZ_min,

        magValX_max,
        magValY_max,
        magValZ_max;

    uint8_t
        i = 0;

    statusI2C_t
      devStatus = STATUS_I2C_SUCCESS;

    // This will take ~30s
//    while ( i < 3000 )
    while ( i < 1000 )
    {
        // wait for the sample ( current setting for ODR is 0x2 => ODR(hybrid mode) == 100 Hz )
        OSA_TimeDelay( 10 );

        uint8_t
          cmd[1] =  {
                      M_OUT_X_MSB_REG
                    };

        // read only mag data
        i2c_status_t
            status = I2C_DRV_MasterReceiveDataBlocking  (
                                                            self.protocol.instance,
                                                            &( self.protocol.device ),

                                                            cmd,
                                                            1,

                                                            (uint8_t*)&(fxosData.magDataXMSB),
                                                            6,

                                                            self.protocol.timeout
                                                        );

        if ( kStatus_I2C_Success != status )
        {
            return STATUS_FXOS_PROTOCOL_ERROR;
        }

        // Compute 16-bit X-axis magnetic output value
        magValX = (int16_t)( (int16_t)fxosData.magDataXMSB << 8 | fxosData.magDataXLSB );
        magValY = (int16_t)( (int16_t)fxosData.magDataYMSB << 8 | fxosData.magDataYLSB );
        magValZ = (int16_t)( (int16_t)fxosData.magDataZMSB << 8 | fxosData.magDataZLSB );

        // first sample?
        if ( 0 == i )
        {
            magValX_max = magValX;
            magValX_min = magValX;

            magValY_max = magValY;
            magValY_min = magValY;

            magValZ_max = magValZ;
            magValZ_min = magValZ;
        }

        // Check to see if current sample is the maximum or minimum X-axis value
        if (magValX > magValX_max)  {magValX_max = magValX;}
        if (magValX < magValX_min)  {magValX_min = magValX;}

        // Check to see if current sample is the maximum or minimum Y-axis value
        if (magValY > magValY_max)  {magValY_max = magValY;}
        if (magValY < magValY_min)  {magValY_min = magValY;}

        // Check to see if current sample is the maximum or minimum Z-axis value
        if (magValZ > magValZ_max)  {magValZ_max = magValZ;}
        if (magValZ < magValZ_min)  {magValZ_min = magValZ;}

        i++;
    }

    /**
     * compute the average
     */

    magValX_avg = (magValX_max + magValX_min) / 2; // X-axis hard-iron offset
    magValY_avg = (magValY_max + magValY_min) / 2; // Y-axis hard-iron offset
    magValZ_avg = (magValZ_max + magValZ_min) / 2; // Z-axis hard-iron offset

    /**
     * Left-shift by one as magnetometer offset registers are left justified 15-bit
     */

    magValX_avg <<= 1;
    magValY_avg <<= 1;
    magValZ_avg <<= 1;

    // goto standby
    devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, ACTIVE_MASK, ~ACTIVE_MASK );

    devStatus |= I2C_WriteReg( &(self.protocol), M_OFF_X_LSB_REG, (uint8_t)   ( magValX_avg & 0xFF)         );
    devStatus |= I2C_WriteReg( &(self.protocol), M_OFF_X_MSB_REG, (uint8_t) ( ( magValX_avg >> 8 ) & 0xFF ) );
    devStatus |= I2C_WriteReg( &(self.protocol), M_OFF_Y_LSB_REG, (uint8_t)   ( magValY_avg & 0xFF)         );
    devStatus |= I2C_WriteReg( &(self.protocol), M_OFF_Y_MSB_REG, (uint8_t) ( ( magValY_avg >> 8 ) & 0xFF ) );
    devStatus |= I2C_WriteReg( &(self.protocol), M_OFF_Z_LSB_REG, (uint8_t)   ( magValZ_avg & 0xFF)         );
    devStatus |= I2C_WriteReg( &(self.protocol), M_OFF_Z_MSB_REG, (uint8_t) ( ( magValZ_avg >> 8 ) & 0xFF ) );

    // activate the module
    devStatus |= I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, ACTIVE_MASK, ACTIVE_MASK );

    if ( STATUS_I2C_SUCCESS == devStatus )
    {
        return STATUS_FXOS_SUCCESS;
    }

    else
    {
        catch( CATCH_I2C );
        return STATUS_FXOS_ERROR;
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
  output[idx] = (float)input[idx] * accMag_sensCoef[selectedRange];
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
  output[idx] = (mE_t)( ( (float)input[idx] * accMag_sensCoef[selectedRange] ) * 100 );
}

/**
 * format raw to byte - currently unimplemented
 */
void acc_fmtDef2Byte(
						const void* src,
							  void* dst,
						   uint32_t idx
					)
{}

void acc_fmtMe2Def(
                    const void* src,
                          void* dst
//                       uint32_t idx
                  )
{
  /**
   * helper pointers
   */

  mE_t*
    input = (mE_t*)src;
  int16_t*
    output = (int16_t*)dst;

  // convert data
  *output = (int16_t)( (float)*input / ( 100 * accMag_sensCoef[selectedRange] ) );
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

  int16_t*
    input = (int16_t*)src;
  float*
    output = (float*)dst;

  // convert data
  output[idx] = (float)input[idx] * accMag_sensCoef[3];
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

	int16_t*
	input = (int16_t*)src;
	mE_t*
	output = (mE_t*)dst;

	// convert data to [uT]
	output[idx] = (mE_t)( ( (float)input[idx] * accMag_sensCoef[3] ) * 100 );
}

/**
 * format raw to byte - currently unimplemented
 */
void mag_fmtDef2Byte(
						const void* src,
							  void* dst,
						   uint32_t idx
					)
{}


/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_WriteReg
 * Description   : Write the specified register of fxos8700.
 * The writing process is through I2C.
 *END*/
static uint8_t FXOS_WriteReg(uint8_t reg, uint8_t val)
{
    uint8_t cmd[1],buff[1];
    uint8_t retval = 0;
     /** The register address */
    cmd[0] = reg;
     /** Data */
    buff[0] = val;
    retval = I2C_DRV_MasterSendDataBlocking(  self.protocol.instance, &(self.protocol.device), cmd,1,buff,1,100);
    if(retval != kStatus_I2C_Success)
    {
        return 1;
    }
    return 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_ReadReg
 * Description   : Read the specified register value of fxos8700.
 * The reading process is through I2C.
 *END*/
static uint8_t FXOS_ReadReg(uint8_t reg, uint8_t *val)
{
    uint8_t buff[1];
    uint8_t data[1];
    uint8_t retval = 0;
    buff[0] = reg;
    retval = I2C_DRV_MasterReceiveDataBlocking( self.protocol.instance, &(self.protocol.device) ,buff,1,data,1,100);
    if(retval != kStatus_I2C_Success)
    {
        return 1;
    }
    *val = data[0];
    return 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FXOS_ModifyReg
 * Description   : Modify the specified register value of fxos8700.
 * The modify process is through I2C.
 *END*/
static uint8_t FXOS_ModifyReg(uint8_t reg, uint8_t clr_mask, uint8_t val)
{
    uint8_t retval = 0;
    uint8_t reg_val;

    retval = FXOS_ReadReg(reg, &reg_val);
    if( 0 != retval )
    {
        return 1;
    }

    reg_val &= ~clr_mask;
    reg_val |= val;
    retval = FXOS_WriteReg(reg, reg_val);
    if( 0 != retval )
    {
        return 1;
    }

    return 0;
}

/**
 * [FXOS_Sleep description]
 * @return [description]
 */
fxos_status_t FXOS_GotoStandby()
{
    // goto standby
//    FXOS_ModifyReg(FXOS_CTRL_REG1, ACTIVE_MASK, ~ACTIVE_MASK);

	statusI2C_t
		i2cStatus = I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, ACTIVE_MASK, 0 );

	if ( STATUS_I2C_SUCCESS != i2cStatus )
	{
		return STATUS_FXOS_PROTOCOL_ERROR;
	}
	else
	{
		return STATUS_FXOS_SUCCESS;
	}

//    // sleep after ~36 seconds of inactivity at 6.25 Hz ODR
//    FXOS_WriteReg( ASLP_COUNT_REG, 0x40 );
//
//    // select 1.56 Hz sleep mode sample frequency for low power
//    FXOS_ModifyReg( FXOS_CTRL_REG1, 0xC0, 0xC0 );
//    // select low power mode
//    FXOS_ModifyReg( FXOS_CTRL_REG2, 0x18, 0x18 );
//    // enable auto sleep mode
//    FXOS_ModifyReg( FXOS_CTRL_REG2, 0x04, 0x04 );
//
//    // select wake on transient, orientation change, pulse, freefall/motion detect, or acceleration vector magnitude
//    // FXOS_ModifyReg( FXOS_CTRL_REG3, 0x7C, 0x7C );
//
//    // select  Auto-SLEEP/WAKE interrupt enable
//    // FXOS_ModifyReg( FXOS_CTRL_REG4, 0x80, 0x80 );
//
//    // goto active
//    FXOS_ModifyReg(FXOS_CTRL_REG1, ACTIVE_MASK, ACTIVE_MASK);

}

/**
 * [FXOS_Wake description]
 * @return [description]
 */
fxos_status_t FXOS_SetActive()
{
	// goto active
//	FXOS_ModifyReg(FXOS_CTRL_REG1, ACTIVE_MASK, ACTIVE_MASK);
	statusI2C_t
		i2cStatus = I2C_ModifyReg( &(self.protocol), FXOS_CTRL_REG1, 0, ACTIVE_MASK );

	if ( STATUS_I2C_SUCCESS != i2cStatus )
	{
		return STATUS_FXOS_PROTOCOL_ERROR;
	}
	else
	{
		return STATUS_FXOS_SUCCESS;
	}
}

/**
 * reset the module
 */
fxos_status_t FXOS_SoftReset()
{
	statusI2C_t
		i2cStatus = I2C_WriteReg( &(self.protocol), FXOS_CTRL_REG2, RST_MASK );

	if ( STATUS_I2C_SUCCESS != i2cStatus )
	{
		return STATUS_FXOS_PROTOCOL_ERROR;
	}
	else
	{
		return STATUS_FXOS_SUCCESS;
	}
}

/**
 * [FXOS_ReadTemp description]
 * @return [description]
 */
fxos_status_t FXOS_ReadRawTemp( uint8_t* tempVal )
{
  statusI2C_t
    status = I2C_ReadReg( &(self.protocol), TEMP_REG, tempVal );

    if ( STATUS_I2C_SUCCESS != status )
    {
      catch( CATCH_I2C );
      return STATUS_FXOS_PROTOCOL_ERROR;
    }
    else
    {
      return STATUS_FXOS_SUCCESS;
    }
}

/**
 * [FXOS_ConfigureTapEvent description]
 * @return [description]
 */
fxos_status_t FXOS_ConfigureTapEvent()
{
    statusI2C_t
        i2cStatus = STATUS_I2C_SUCCESS;

    i2cStatus |= I2C_WriteReg( &(self.protocol), HP_FILTER_CUTOFF_REG, 0x00 );
//    i2cStatus |= I2C_WriteReg( &(self.protocol), HP_FILTER_CUTOFF_REG, 0x02 );

//    i2cStatus |= I2C_WriteReg( &(self.protocol), PULSE_CFG_REG, 0x7F );
    i2cStatus |= I2C_WriteReg( &(self.protocol), PULSE_CFG_REG, (1 << 5) );
//    i2cStatus |= I2C_WriteReg( &(self.protocol), PULSE_CFG_REG, (1 << 4) | (1 << 2) | (1 << 0) );

    /**
     * set the threshold - minimum required acceleration to cause a tap.
     * write the value as a current sensitivity multiplier to get the desired value in [g]
     * current z-threshold is set at 0.25g
     */

//    i2cStatus |= I2C_WriteReg( &(self.protocol), PULSE_THSX_REG, 5 );
//    i2cStatus |= I2C_WriteReg( &(self.protocol), PULSE_THSY_REG, 5 );
    i2cStatus |= I2C_WriteReg( &(self.protocol), PULSE_THSZ_REG, 10 );

    /**
     * set the time limit - the maximum time that a tap can be above the threshold
     * 2.55s time limit at 100Hz odr, this is very dependent on data rate, see the app note
     */

    i2cStatus |= I2C_WriteReg( &(self.protocol), PULSE_TMLT_REG, 80 );

    /**
     * set the pulse latency - the minimum required time between one pulse and the next
     * 5.1s 100Hz odr between taps min, this also depends on the data rate
     */

    i2cStatus |= I2C_WriteReg( &(self.protocol), PULSE_LTCY_REG, 40 );

    // route the tap detect event to INT1 pin
    i2cStatus |= I2C_WriteReg( &(self.protocol), FXOS_CTRL_REG5, 1 << 3 );

    if ( STATUS_I2C_SUCCESS != i2cStatus )
    {
    	catch( CATCH_I2C );
    	return STATUS_FXOS_PROTOCOL_ERROR;
    }
    else
    {
        // enable the tap detect interrupt
        FXOS_EnableTap();

    	return STATUS_FXOS_SUCCESS;
    }
}

/**
 * check if tap is enabled
 * @return status flag
 */
bool FXOS_CheckForTap()
{
    uint8_t
        retVal,
        regVal;

    retVal = FXOS_ReadReg( PULSE_CFG_REG, &regVal );

    if ( 0 == retVal )
    {
        if ( 0 != ( regVal & (1 << 5) ) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/**
 * enable tap detection
 */
fxos_status_t FXOS_EnableTap()
{
	if ( false == isTapEnabled )
	{
		// must be in standby to change registers
		FXOS_GotoStandby();
		I2C_WriteReg( &(self.protocol), FXOS_CTRL_REG4, 1 << 3 );
		FXOS_SetActive();

		isTapEnabled = true;
	}

    return STATUS_FXOS_SUCCESS;
}

/**
 * disable tap detection
 */
fxos_status_t FXOS_DisableTap()
{
	if ( true == isTapEnabled )
	{
		isTapEnabled = false;

		// must be in standby to change registers
		FXOS_GotoStandby();

		uint8_t
			interrupts;
		// clear the flag
		I2C_ReadReg( &(self.protocol), PULSE_SRC_REG, &interrupts );

		// disable the tap event
		I2C_WriteReg( &(self.protocol), FXOS_CTRL_REG4, 0 );

		// activate
		FXOS_SetActive();
	}

    return STATUS_FXOS_SUCCESS;
}

/**
 * check if tap is enabled
 */
bool FXOS_IsTapEnabled()
{
	return isTapEnabled;
}

/**
 * callback for the interrupt
 * @return status flag
 */
fxos_status_t FXOS_Callback()
{
    uint8_t
        interrupts;
    statusI2C_t
        status = I2C_ReadReg( &(self.protocol), INT_SOURCE_REG, &interrupts );

    if ( STATUS_I2C_SUCCESS != status )
    {
      catch( CATCH_I2C );
      return STATUS_FXOS_PROTOCOL_ERROR;
    }
    else
    {
        // handle the tap event, if it occurred
        if ( 0 != ( interrupts & 0x08 ) )
        {
            TapHandler();
        }
        return STATUS_FXOS_SUCCESS;
    }
}

/**
 * read the status of the tap source register
 */
void FXOS_TapHandler()
{
    uint8_t
        interrupts;
    statusI2C_t
        status = I2C_ReadReg( &(self.protocol), PULSE_SRC_REG, &interrupts );

    if ( STATUS_I2C_SUCCESS != status )
    {
        catch( CATCH_I2C );
    }
//    else
//    {
//    	// ...
//    }
}

/**
 * check if I2C bus needs to be recovered
 * @return status flag
 */
fxos_status_t FXOS_RecoverI2C()
{
	statusI2C_t
		recoverStatus = I2C_Recover( &(self.protocol) );

	if ( STATUS_I2C_SUCCESS != recoverStatus )
	{
		catch( CATCH_MOTION );
		return STATUS_FXOS_ERROR;
	}
	else
	{
		return STATUS_FXOS_SUCCESS;
	}
}

/**
 * read FXOS status register
 * @param sensorStatus variable tu put the status register value in
 * @return reading status flag
 */
fxos_status_t FXOS_ReadStatus( uint8_t* sensorStatus )
{
	uint8_t
		statusVal,
		fxosStatus;
	fxosStatus = FXOS_ReadReg( STATUS_00_REG, &statusVal );

	if ( 1 != fxosStatus )
	{
		*sensorStatus = statusVal;
		return STATUS_FXOS_SUCCESS;
	}
	else
	{
		return STATUS_FXOS_ERROR;
	}
}
