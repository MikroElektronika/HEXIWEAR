/**
 * \file FXOS_types.h
 * \version 1.00
 * \brief this file contains sensor FXOS8700cq-related data-types
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
#include "FXOS_info.h"

// FXOS8700 output logic data rate selection
typedef enum
{
  fxosODR0 = ( 0 << FXOS_ODR_SHIFT ),
  fxosODR1 = ( 1 << FXOS_ODR_SHIFT ),
  fxosODR2 = ( 2 << FXOS_ODR_SHIFT ),
  fxosODR3 = ( 3 << FXOS_ODR_SHIFT ),
  fxosODR4 = ( 4 << FXOS_ODR_SHIFT ),
  fxosODR5 = ( 5 << FXOS_ODR_SHIFT ),
  fxosODR6 = ( 6 << FXOS_ODR_SHIFT ),
  fxosODR7 = ( 7 << FXOS_ODR_SHIFT )

} odrFXOS_t;

// FXOS8700 oversample ratio selection
typedef enum
{
  fxosOSR0 = ( 0 << FXOS_OSR_SHIFT ),
  fxosOSR1 = ( 1 << FXOS_OSR_SHIFT ),
  fxosOSR2 = ( 2 << FXOS_OSR_SHIFT ),
  fxosOSR3 = ( 3 << FXOS_OSR_SHIFT ),
  fxosOSR4 = ( 4 << FXOS_OSR_SHIFT ),
  fxosOSR5 = ( 5 << FXOS_OSR_SHIFT ),
  fxosOSR6 = ( 6 << FXOS_OSR_SHIFT ),
  fxosOSR7 = ( 7 << FXOS_OSR_SHIFT )

} osrFXOS_t;

// FXOS8700 accelerometer/magnetometer selection
typedef enum
{
  fxosAccOnly = ( 0 << FXOS_MODE_SHIFT ), // accelerometer only
  fxosMagOnly = ( 1 << FXOS_MODE_SHIFT ), // magnetometer only
  fxosBoth    = ( 3 << FXOS_MODE_SHIFT )  // select both accelerometer and magnetometer

} modeFXOS_t;

// FXOS8700 accelerometer full-scale range
typedef enum
{
  fxosRange2g = ( 0 << FXOS_ACCRANGE_SHIFT ), // 2g mode
  fxosRange4g = ( 1 << FXOS_ACCRANGE_SHIFT ), // 4g mode
  fxosRange8g = ( 2 << FXOS_ACCRANGE_SHIFT )  // 8g mode

} accRangeFXOS_t;

// FXOS8700 return status
typedef enum
{
  STATUS_FXOS_SUCCESS,        // success
  STATUS_FXOS_ERROR,          // general failure
  STATUS_FXOS_PROTOCOL_ERROR, // I2C failure
  STATUS_FXOS_INIT_ERROR,     // initialization failure
  STATUS_FXOS_PARAM_ERROR     // invalid parameter is given

} fxos_status_t;

// device handle
typedef struct
{
  /**
   * I2C relevant information
   */

  genericI2cHandle_t protocol;

} handleFXOS_t;

// FXOS8700 settings
typedef struct
{
        odrFXOS_t odr;     // output data-rate selection
        osrFXOS_t osr;     // over-sample ratio selection
       modeFXOS_t mode;    // accelerometer/magnetometer selection
   accRangeFXOS_t range;   // accelerometer full scale range selection
          uint8_t address; // I2C address
         uint16_t baudRate_kbps; // I2C baud-rate

} settingsFXOS_t;

// FXOS8700 accelerometer and magnetometer data struct
typedef struct
{
  /**
   * accelerometer data
   */
  uint8_t accDataXMSB;
  uint8_t accDataXLSB;
  uint8_t accDataYMSB;
  uint8_t accDataYLSB;
  uint8_t accDataZMSB;
  uint8_t accDataZLSB;

  /**
   * magnetometer data
   */
  uint8_t magDataXMSB;
  uint8_t magDataXLSB;
  uint8_t magDataYMSB;
  uint8_t magDataYLSB;
  uint8_t magDataZMSB;
  uint8_t magDataZLSB;

} dataFXOS_t;
