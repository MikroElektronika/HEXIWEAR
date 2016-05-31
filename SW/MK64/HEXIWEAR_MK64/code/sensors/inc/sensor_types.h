/**
 * @file sensor_types.h
 * @brief data-types related to sensors and their communication
 *
 * @version 1.0.1
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
 * Neither the name of NXP Semiconductor, Inc. nor the names of its
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
 * support: http://www.mikroe.com/forum and https://community.freescale.com
 *
 * Project HEXIWEAR, 2015
 */

#ifndef HG_SENSOR_TYPES
#define HG_SENSOR_TYPES

#include <stdint.h>
#include <stdbool.h>

#include "host_mcu_interface.h"
#include "HEXIWEAR_info.h"

#include "FXOS_types.h"
#include "FXAS_types.h"
#include "HTU_types.h"
#include "MPL_types.h"

/**
 * list of particular sensors
 */
typedef enum
{
  SENSOR_MASK_NONE  =   0,
  SENSOR_MASK_FXOS  =   1 << 0, // compass
  SENSOR_MASK_FXAS  =   1 << 1, // gyroscope
  SENSOR_MASK_MPL   =   1 << 2, // pressure & temperature
  SENSOR_MASK_HTU   =   1 << 3, // humidity
  SENSOR_MASK_TSL   =   1 << 4, // ambient light
  SENSOR_MASK_MAXIM =   1 << 5, // heart-rate

  SENSOR_MASK_ALL   = ( 1 << 6 ) - 1

} sensor_mask_t;

/** list of sensors and other peripherals which feature in data packets */
typedef enum
{
  PACKET_ACC,  // accelerometer
  PACKET_MAG,  // magnetometer
  PACKET_GYRO, // gyroscope
  PACKET_PRES, // pressure
  PACKET_TEMP, // temperature
  PACKET_HUM,  // humidity
  PACKET_LUX,  // ambient light
  PACKET_HR,   // heart-rate
  PACKET_BAT,  // battery

  PACKET_ALL

} packet_t;

/** list of sensors in HEXIWEAR */
typedef enum
{
  SENSOR_FXOS,  // compass
  SENSOR_FXAS,  // gyroscope
  SENSOR_MPL,   // pressure & temperature
  SENSOR_HTU,   // humidity
  SENSOR_TSL,   // ambient light
  SENSOR_MAXIM, // heart-rate
  SENSOR_BATT,  // battery readings

  SENSOR_ALL

} sensor_t;

typedef struct
{
  uint32_t B_EN_pin;
  uint32_t LDO_EN_pin;
  uint32_t BAT_SENS_EN_pin;
  uint32_t VIBRO_pin;

} sensor_pins_t;

typedef enum
{
  PACKET_PUSH_NONE  = 0,

  PACKET_PUSH_KW40  = 0x1 << 0,
  PACKET_PUSH_OLED  = 0x1 << 1,
  PACKET_PUSH_FLASH = 0x1 << 2,

  PACKET_PUSH_APP_PEDOMETER  = 0x1 << 3,
  PACKET_PUSH_APP_HEART_RATE = 0x1 << 4,
  PACKET_PUSH_POWER_MGMT     = 0x1 << 5,

  PACKET_PUSH_ALL   = 0xFF,

} packet_pushTarget_t;


typedef enum
{
  SENSOR_STATUS_SUCCESS,
  SENSOR_STATUS_ERROR

} sensor_status_t;

typedef struct
{
  packet_pushTarget_t targets;
             uint32_t defaultDelay_ms;
             uint32_t delay_ms;
             uint32_t initCounterVal;
             uint32_t counter;

} packet_settings_t;

typedef struct
{
  bool isActive;

} sensor_settings_t;


// formatting pointer
typedef void (*dataConversion_t)(
                                  const void* src,
                                        void* dst,
                                     uint32_t idx
                                );
#endif

