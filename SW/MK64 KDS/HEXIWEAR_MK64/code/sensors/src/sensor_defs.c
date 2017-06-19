/**
 * @file sensor_defs.c
 * @brief this file containts sensor-related global variables
 *
 * @version 1.00
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

#include "sensor_defs.h"
#include "GPIO.h"
#include "HEXIWEAR_info.h"

sensor_pins_t
  sensor_powerPins =  {
                      // power options
                      .B_EN_pin        = PWR_SENSORS_NF,
                      .LDO_EN_pin      = PWR_HR,
                      .BAT_SENS_EN_pin = PWR_BAT_SENS,

                      // vibro-motor options
                      .VIBRO_pin       = VIBRO
                    };

// sensor tasks
task_handler_t
  hexiwear_sensor_TAG_handler,
  hexiwear_sensor_FITNESS_handler;

/**
 * sensor category buffers
 */

motionData_t
  motionData;

weatherData_t
  weatherData;

healthData_t
  healthData;

dataConversion_t
  sensor_fmtDef2Float = (void*)(0),
  sensor_fmtDef2Me    = (void*)(0),
  sensor_fmtDef2Byte  = (void*)(0),

  sensor_fmtFloat2Def = (void*)(0),
  sensor_fmtFloat2Me  = (void*)(0),

  sensor_fmtMe2Def    = (void*)(0),
  sensor_fmtMe2Float  = (void*)(0);

mutex_t
  sensor_i2cAccessMutex;
