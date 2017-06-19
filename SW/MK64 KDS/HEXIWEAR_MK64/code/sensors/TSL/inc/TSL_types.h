/**
 * \file TSL_types.h
 * \version 1.00
 * \brief this file contains sensor TSL2561-related data structures
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

#include <stdint.h>
#include "generic_i2c_types.h"

typedef enum
{
  TSL_INTEGRATION_TIME_13MS  = 0, // 13.7ms
  TSL_INTEGRATION_TIME_101MS = 1, // 101ms
  TSL_INTEGRATION_TIME_402MS = 2  // 402ms

} integrationTSL_t;

typedef enum
{
  TSL_GAIN_0X  = 0x00, // no gain
  TSL_GAIN_16X = 0x10  // 16x gain

} gainTSL_t;

typedef enum
{
  TSL_CHANNEL_FULL     = 0,
  TSL_CHANNEL_INFRARED = 1

} channelTSL_t;

typedef enum
{
  STATUS_TSL_SUCCESS,        // success
  STATUS_TSL_ERROR,          // fail
  STATUS_TSL_PROTOCOL_ERROR, // I2C failure
  STATUS_TSL_INIT_ERROR      // initialization error

} tsl_status_t;

typedef struct
{
  integrationTSL_t timing;
         gainTSL_t gain;
           uint8_t address;
	      uint16_t baudRate_kbps; // I2C baud-rate

} settingsTSL_t;

typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleTSL_t;
