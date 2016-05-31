/**
 * \file MPL_types.h
 * \version 1.00
 * \brief this file contains sensor MPL3115A2's related data-types
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

/*
 * MPL3115A2 definitions
 */

#pragma once

#include <stdint.h>
#include "generic_i2c_types.h"

typedef enum
{
  STATUS_MPL_SUCCESS,
  STATUS_MPL_ERROR,
  STATUS_MPL_PROTOCOL_ERROR,
  STATUS_MPL_INIT_ERROR,
  STATUS_MPL_TIMEOUT

} mpl_status_t;

typedef enum
{
// oversample factor
  MPL_OS_0,
  MPL_OS_1,
  MPL_OS_2,
  MPL_OS_3,
  MPL_OS_4,
  MPL_OS_5,
  MPL_OS_6,
  MPL_OS_7

} overSampleMPL_t;

typedef enum
{
  MPL_MODE_PRESSURE    = 0,
  MPL_MODE_ALTITUDE    = 1,
  MPL_MODE_TEMPERATURE = 2,
  MPL_MODE_CURRENT     = 0xFF

} modeMPL_t;

typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleMPL_t;

typedef struct
{
        modeMPL_t mode;       // device mode, altimeter or barometer
  overSampleMPL_t oversample; // oversampling ratio
          uint8_t address;    // device I2C address
	     uint16_t baudRate_kbps; // I2C baud-rate

} settingsMPL_t;

typedef struct
{
  /**
   * pressure / altitude data
   */
  uint8_t presAltDataMSB;
  uint8_t presAltDataCSB;
  uint8_t presAltDataLSB;

  /**
   * temperature data
   */
  uint8_t tempDataMSB;
  uint8_t tempDataLSB;

} dataMPL_t;
