/**
 * @file sensor_info.h
 * @brief info related to sensors and its communication
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

#ifndef HG_SENSOR_INFO
#define HG_SENSOR_INFO

#include "host_mcu_interface.h"

/**
 * define sensors which are present in the system
 */

#define SENSOR_FXOS_PRESENT
#define SENSOR_FXAS_PRESENT
#define SENSOR_MPL_PRESENT
#define SENSOR_HTU_PRESENT
#define SENSOR_TSL_PRESENT
#define SENSOR_MAXIM_PRESENT

/**
 * sensors' tasks stack sizes
 */
#define SENSOR_GET_DATA_STACK_SIZE ( 0x1000 )

#define SENSOR_TAG_BLINK_PERIOD ( 99 )

/**
 * sensors' tasks priorities
 */
#define SENSOR_GET_DATA_PRIO     ( HEXIWEAR_SENSOR_PRIO )

/** number of retries for sensor read */
#define SENSOR_RETRY_NUM ( 3 )

/**
 * motion data format parameters
 *
 * OR the parameters below to create a bit-vector with complete info
 * regarding formatting data
 */

/**
 * sensor data types eligible for format conversions
 * use existing enumerations from hostInterface_packetType_t type
 * occupy bits [3:0] in the bit-vector
 */

#define DATA_TYPE_SHIFT ( 0 )
#define DATA_TYPE_MASK  ( 0x0F << DATA_TYPE_SHIFT )

// battery service
#define DATA_TYPE_BATTERYLEVEL ( packetType_batteryLevel )

// motion service
#define DATA_TYPE_ACCEL ( packetType_accel )
#define DATA_TYPE_MAG   ( packetType_magnet )
#define DATA_TYPE_GYRO  ( packetType_gyro )

// weather service
#define DATA_TYPE_AMBI  ( packetType_ambiLight )
#define DATA_TYPE_TEMP  ( packetType_temperature )
#define DATA_TYPE_HUMID ( packetType_humidity )
#define DATA_TYPE_PRES  ( packetType_pressure )
//#define DATA_TYPE_ALT   ( packetType_altitude )

// health service
#define DATA_TYPE_HR       ( packetType_heartRate )
#define DATA_TYPE_STEPS    ( packetType_steps )
#define DATA_TYPE_CALORIES ( packetType_calories )

/**
 * data formats
 */

// occupy bits [5:4] in the bit-vector
#define DATA_FORMAT_FROM_SHIFT   ( 4 )
#define DATA_FORMAT_FROM_MASK    ( 0x3 << DATA_FORMAT_FROM_SHIFT )
#define DATA_FORMAT_FROM_DEFAULT ( 1 )
#define DATA_FORMAT_FROM_FLOAT   ( 2 )
#define DATA_FORMAT_FROM_mE      ( 3 )


// occupy bits [7:6] in the bit-vector
#define DATA_FORMAT_TO_SHIFT   ( 6 )
#define DATA_FORMAT_TO_MASK    ( 0x3 << DATA_FORMAT_TO_SHIFT )
#define DATA_FORMAT_TO_DEFAULT ( 0 )
#define DATA_FORMAT_TO_BYTE    ( 1 )
#define DATA_FORMAT_TO_mE      ( 2 )
#define DATA_FORMAT_TO_FLOAT   ( 3 )

/**
 * sensor power constants
 */
#define SENSOR_ACTIVE_FSL   ( 1 << 0 )
#define SENSOR_ACTIVE_NFSL  ( 1 << 1 )
#define SENSOR_ACTIVE_MAXIM ( 1 << 2 )
#define ADC_ACTIVE_BAT      ( 1 << 3 )

/**
 * default polling periods
 */

#define ACC_DEFAULT_POLL_PERIOD_MS  ( 400 )
#define MAG_DEFAULT_POLL_PERIOD_MS  ( 400 )
#define GYRO_DEFAULT_POLL_PERIOD_MS ( 400 )

#define TEMP_DEFAULT_POLL_PERIOD_MS ( 60000 )
#define BAT_DEFAULT_POLL_PERIOD_MS  ( 61000 )
#define PRES_DEFAULT_POLL_PERIOD_MS ( 62000 )
#define HUM_DEFAULT_POLL_PERIOD_MS  ( 63000 )
#define LUX_DEFAULT_POLL_PERIOD_MS  ( 64000 )
//#define HR_DEFAULT_POLL_PERIOD_MS   ( 400 )

/**
 * default minimum delay
 */
#define SENSOR_DEFAULT_MINIMUM_DELAY_MS ( 400 )

#endif
