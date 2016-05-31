/**
 * \file FXOS_types.h
 * \version 1.00
 * \brief this file contains sensor HTU21D related data-types
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
  STATUS_HTU_SUCCESS,
  STATUS_HTU_ERROR,
  STATUS_HTU_PROTOCOL_ERROR,
  STATUS_HTU_INIT_ERROR,
  STATUS_HTU_TIMEOUT

} htu_status_t;

typedef enum
{
  BITRES_HTU_RH_12_TEMP14 = 0,
  BITRES_HTU_RH_8_TEMP12,
  BITRES_HTU_RH_10_TEMP13,
  BITRES_HTU_RH_11_TEMP11,

} bitResHTU_t;

typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleHTU_t;

typedef struct
{
  bitResHTU_t bitRes;
      uint8_t address;
     uint16_t baudRate_kbps; // I2C baud-rate

} settingsHTU_t;
