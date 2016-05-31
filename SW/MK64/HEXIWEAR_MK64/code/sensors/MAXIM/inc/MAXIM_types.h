/**
 * \file MAXIM_types.h
 * \version 1.00
 * \brief this file contains sensor MAX30101's data-types
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
#include "MAXIM_info.h"

typedef struct
{
  /**
   * I2C relevant information
   */
  genericI2cHandle_t protocol;

} handleMAXIM_t;

typedef enum
{
  modeHR        = 0x2,
  modeSPO2      = 0x3,
  modeMultiLED  = 0x7

} modeMAXIM_t;

typedef enum
{
  ledPower_69  = 0x0, // ADC -> 15 bit
  ledPower_118 = 0x1, // ADC -> 16 bit
  ledPower_215 = 0x2, // ADC -> 17 bit
  ledPower_411 = 0x3  // ADC -> 18 bit

} pwMAXIM_t;

typedef enum
{
  sampleRate_50   = 0x0,
  sampleRate_100  = 0x1,
  sampleRate_200  = 0x2,
  sampleRate_400  = 0x3,
  sampleRate_800  = 0x4,
  sampleRate_1000 = 0x5,
  sampleRate_1600 = 0x6,
  sampleRate_3200 = 0x7

} sampleRateMAXIM_t;

typedef enum
{
  LEDSlotNone  =  0x0,
  LEDSlotRed   =  0x1,
  LEDSlotIR    =  0x2,
  LEDSlotGreen =  0x3

} LEDSlotMAXIM_t;

typedef enum
{
  STATUS_MAXIM_SUCCESS,        // success
  STATUS_MAXIM_ERROR,          // fail
  STATUS_MAXIM_PROTOCOL_ERROR, // protocol failure
  STATUS_MAXIM_INIT_ERROR,     // initialization error
  STATUS_MAXIM_PARAM_ERROR,    // invalid parameter is given
  STATUS_MAXIM_OVF_ERROR,      // sensor data overflow
  STATUS_MAXIM_TIMEOUT         // timeout occured

} maxim_status_t;

/**
 * use evaluation board software and datasheet to determine the desired current value
 */
typedef uint8_t LEDCurrentMAXIM_t;
typedef uint32_t dataMAXIM_t;


typedef enum
{
  adcRange2048  = 0x0,
  adcRange4096  = 0x1,
  adcRange8192  = 0x2,
  adcRange16384 = 0x3

} adcRangeMAXIM_t;

typedef enum
{
  ovsNone = 0x0, // no averaging
  ovs2    = 0x1, // average 2 samples
  ovs4    = 0x2, // average 4 samples
  ovs8    = 0x3, // average 8 samples
  ovs16   = 0x4, // average 16 samples
  ovs32   = 0x5  // average 32 samples

} ovsMAXIM_t;
/**
 * general module settings
 */

typedef struct
{
  // mode (HR, SpO2, or multi-led)
  modeMAXIM_t mode;

  // multiLED slots
  LEDSlotMAXIM_t LEDSlot[ MAXIM_SLOT_NUM ];
         uint8_t activeSlots;

  // LED currents
  LEDCurrentMAXIM_t LEDCurrentRed;
  LEDCurrentMAXIM_t LEDCurrentIR;
  LEDCurrentMAXIM_t LEDCurrentGreen;

  // timings
  sampleRateMAXIM_t sampleRate;
          pwMAXIM_t pulseWidth;

  // ADC range
    adcRangeMAXIM_t range;

  // averaging
        ovsMAXIM_t oversample;

  // device I2C address
  uint8_t address;
 uint16_t baudRate_kbps; // I2C baud-rate

} settingsMAXIM_t;

typedef void (*maxim_callback_t)( void* sampleBuf, uint8_t numAvailSam, void* param );
