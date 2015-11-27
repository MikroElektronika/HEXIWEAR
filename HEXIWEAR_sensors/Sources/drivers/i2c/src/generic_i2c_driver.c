/**
 * Write the specified registers via I2C
 * Project HEXIWEAR, 2015
 */

#include "generic_i2c_driver.h"
#include "generic_i2c_types.h"
#include "generic_i2c_info.h"

#include "i2cCom1.h"
#include "i2cCom2.h"

// number of initialized I2C modules
static uint32_t
  i2cNum_ON = 0;

/**
 * [I2C_Init description]
 * @param  self    [description]
 * @param  devAddr [description]
 * @return         [description]
 */
statusI2C_t I2C_Init(
                      genericI2cHandle_t* self,
                                  uint8_t devAddr
                    )
{
  switch ( self->instance )
  {
    case FSL_I2CCOM1: {
                        // assign the master structure
                        self->state = i2cCom1_MasterState;

                        // configure the device info
                        self->device.baudRate_kbps = i2cCom1_MasterConfig0.baudRate_kbps;
                        break;
                      }

    case FSL_I2CCOM2: {
                        // assign the master structure
                        self->state = i2cCom2_MasterState;

                        // configure the device info
                        self->device.baudRate_kbps = i2cCom2_MasterConfig0.baudRate_kbps;
                        break;
                      }
    default: {}
  }

  self->device.address = devAddr;
  self->timeout        = I2C_TIMEOUT;

  I2C_DRV_MasterSetBaudRate( self->instance, &(self->device) );

  i2cNum_ON++;
  return STATUS_I2C_SUCCESS;
}

/**
 * [I2C_deinit description]
 * @param  self [description]
 * @return      [description]
 */
statusI2C_t I2C_Deinit(
                        genericI2cHandle_t* self
                      )
{
  if ( 0 == i2cNum_ON )
  {
    return STATUS_I2C_DEINIT_ERROR;
  }

  else
  {
    i2c_status_t
      status = I2C_DRV_MasterDeinit(self->instance);

    if ( kStatus_I2C_Success != status )
    {
      return STATUS_I2C_ERROR;
    }

    else
    {
      i2cNum_ON--;
      return STATUS_I2C_SUCCESS;
    }
  }
}

/**
 * Write to the specified register
 * The writing process is done via I2C
 *
 * @param  self [description]
 * @param  reg  [description]
 * @param  val  [description]
 *
 * @return      [description]
 */
statusI2C_t I2C_WriteReg(
                          genericI2cHandle_t* self,
                                      uint8_t reg,
                                      uint8_t val
                        )
{
  uint8_t
    // the register address
    cmd[1]  = {
                reg
              },
    // data
    buff[1] = {
                val
              };

  i2c_status_t
    status = I2C_DRV_MasterSendDataBlocking (
                                              self->instance,
                                              &(self->device),

                                              cmd,
                                              1,

                                              buff,
                                              1,

                                              self->timeout
                                            );
  if ( kStatus_I2C_Success != status )
  {
    return STATUS_I2C_ERROR;
  }
  else
  {
    return STATUS_I2C_SUCCESS;
  }
}

/**
 * Read the specified register value
 * The reading process is done via I2C
 *
 * @param  self         [description]
 * @param  regAddr      [description]
 * @param  valToReceive [description]
 *
 * @return              [description]
 */
statusI2C_t I2C_ReadReg (
                          genericI2cHandle_t* self,
                                      uint8_t regAddr,
                                     uint8_t* valToReceive
                        )
{
  uint8_t
    cmd[1] =  {
                regAddr
              },
    buff[1];

  i2c_status_t
    status = I2C_DRV_MasterReceiveDataBlocking(
                                                self->instance,
                                                &(self->device),

                                                cmd,
                                                1,

                                                buff,
                                                1,

                                                self->timeout
                                              );
  if ( kStatus_I2C_Success != status )
  {
    return STATUS_I2C_ERROR;
  }
  else
  {
    // save the returned value
    *valToReceive = buff[0];
    return STATUS_I2C_SUCCESS;
  }
}

/**
 * modify the specified register value
 * the process is done via I2C
 *
 * @param  self    [description]
 * @param  reg     [description]
 * @param  clrMask [description]
 * @param  setMask [description]
 *
 * @return         [description]
 */
statusI2C_t I2C_ModifyReg (
                            genericI2cHandle_t* self,
                                        uint8_t reg,
                                        uint8_t clrMask,
                                        uint8_t setMask
                          )
{
  uint8_t
    regVal;

  i2c_status_t
    status = I2C_ReadReg(self, reg, &regVal);

  if ( kStatus_I2C_Success != status )
  {
    return STATUS_I2C_ERROR;
  }
  else
  {
    regVal &= clrMask;
    regVal |= setMask;
    return I2C_WriteReg(self, reg, regVal);
  }
}
