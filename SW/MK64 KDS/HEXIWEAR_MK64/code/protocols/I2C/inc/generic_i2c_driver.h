/**
 * \file generic_i2c_driver.h
 * \version 1.00
 * \brief  this file contains wrappers to manipulate with specific registers via I2C
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

#pragma once

#include "generic_i2c_types.h"
#include <stdbool.h>

/**
 * initialize I2C
 * @param  self          I2C handle
 * @param  devAddr       device address
 * @param  baudrate_kbps desired baud-rate
 * @return               status flag
 */
statusI2C_t I2C_Init(
                      genericI2cHandle_t* self,
                                  uint8_t devAddr,
								 uint16_t baudrate_kbps
                    );

/**
 * deinitialize I2C (not used)
 */
statusI2C_t I2C_Deinit( genericI2cHandle_t* self );

/**
 * Write to the specified register
 * The writing process is done via I2C
 *
 * @param  self I2C handle
 * @param  reg  register address
 * @param  val  register value to send
 *
 * @return      status flag
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
 * @param  self         I2C handle
 * @param  regAddr      register address
 * @param  valToReceive register value to receive
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
 * @param  self    I2C handle
 * @param  reg     register address
 * @param  clrMask mask to clear register value bits
 * @param  setMask mask to set register value bits
 *
 * @return         status flag
 */
statusI2C_t I2C_ModifyReg (
                            genericI2cHandle_t* self,
                                        uint8_t reg,
                                        uint8_t clrMask,
                                        uint8_t setMask
                          );

/**
 * if needed, recover I2C by resetting the state on the bus
 * @param  self I2C handle
 * @return      status flag
 */
statusI2C_t I2C_Recover( genericI2cHandle_t* self );