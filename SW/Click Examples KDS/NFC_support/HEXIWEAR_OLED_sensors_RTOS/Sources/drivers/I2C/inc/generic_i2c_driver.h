/**
 * manipulate registers via I2C
 * Project HEXIWEAR, 2015
 */

#ifndef HG_I2C_REG_IO_DRIVER
#define HG_I2C_REG_IO_DRIVER

#include "generic_i2c_types.h"
#include <stdbool.h>

/**
 * initialize I2C
 */
statusI2C_t I2C_Init(
                      genericI2cHandle_t* self,
                                  uint8_t devAddr,
								 uint16_t baudrate_kbps
                    );

/**
 * [I2C_deinit description]
 * @param  self [description]
 * @return      [description]
 */
statusI2C_t I2C_Deinit(
                        genericI2cHandle_t* self
                      );

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
                        );

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
                        );

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
                          );

/**
 * if needed, recover I2C by resetting the state on the bus
 * @param  self i2c handle
 * @return      status flag
 */
statusI2C_t I2C_Recover( genericI2cHandle_t* self );

statusI2C_t I2C_Send(genericI2cHandle_t* self, uint8_t *pCmd,  uint16_t CmdLen, uint8_t *pSnd,  uint16_t SndLen);
statusI2C_t I2C_Receive (genericI2cHandle_t* self, uint8_t *pRcv, uint16_t RcvLen);

#endif
