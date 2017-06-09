/**
 * \file FXAS_types.h
 * \version 1.00
 * \brief this file contains sensor FXAS21002 related data-types
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
  GODR_800HZ = 0,
  GODR_400HZ,
  GODR_200HZ,
  GODR_100HZ,
  GODR_50HZ,
  GODR_12_5HZ,
  GODR_6_25HZ,
  GODR_1_56HZ

} gyroODR_t;

// Set initial input parameters
typedef enum
{
  GFSR_2000DPS,
  GFSR_1000DPS,
  GFSR_500DPS,
  GFSR_250DPS

} gyroFSR_t;

// device handle
typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleFXAS_t;


typedef struct
{
  gyroODR_t odr;     // output data rate selection
  gyroFSR_t fsr;     // degrees per second
    uint8_t address; // I2C address
   uint16_t baudRate_kbps; // I2C baud-rate

} settingsFXAS_t;

typedef struct
{
  uint8_t gyroXMSB;
  uint8_t gyroXLSB;
  uint8_t gyroYMSB;
  uint8_t gyroYLSB;
  uint8_t gyroZMSB;
  uint8_t gyroZLSB;

} dataFXAS_t;

typedef enum
{
  STATUS_FXAS_SUCCESS,        // success
  STATUS_FXAS_ERROR,          // fail
  STATUS_FXAS_PROTOCOL_ERROR, // I2C failure
  STATUS_FXAS_INIT_ERROR,     // initialization error
  STATUS_FXAS_PARAM_ERROR     // invalid parameter is given

} fxas_status_t;
