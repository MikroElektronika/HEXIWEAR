/**
 * \file generic_i2c_types.h
 * \version 1.00
 * \brief  this file contains I2C-related data-types used throughout the project
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

#include <stdint.h>
#include <stdbool.h>

#include "fsl_i2c_master_driver.h"

#pragma once

typedef struct
{
  /** generic I2C information */
            uint32_t instance; /**< I2C instance */
        i2c_device_t device;   /**< I2C device setting */
  i2c_master_state_t state;    /**< I2C internal state space */
            uint32_t timeout;  /**< I2C timeout */

  /** specific I2C information should go below this */

} genericI2cHandle_t;

/** I2C generic status enum */
typedef enum
{
  STATUS_I2C_SUCCESS,      /**< success */
  STATUS_I2C_ERROR,        /**< fail */
  STATUS_I2C_INIT_ERROR,   /**< initialization error */
  STATUS_I2C_DEINIT_ERROR, /**< deinitialization error */
  STATUS_I2C_TIMEOUT_ERROR /**< timeout occured */

} statusI2C_t;
