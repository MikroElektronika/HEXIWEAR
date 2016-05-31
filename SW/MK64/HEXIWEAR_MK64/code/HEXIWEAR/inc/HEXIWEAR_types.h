/**
 * \file HEXIWEAR_types.h
 * \version 1.00
 * \brief this file contains HEXIWEAR project-specific data types
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

#include "MAXIM_info.h"
#include "MAXIM_types.h"

/**
 * raw data structures
 */

typedef union
{
  // vector data
  struct
  {
    // FXOS
    int16_t accData[3];
    int16_t magData[3];

    // FXAS
    int16_t gyroData[3];

  };

  uint8_t allData[ 3*sizeof(int16_t) + 3*sizeof(int16_t) + 3*sizeof(int16_t) ];

} motionData_t;

typedef union
{
  // scalar data
  struct
  {
    // MPL
    int32_t presAltData;

    // TSL
//    uint16_t ambiData[2];
    uint8_t ambiData;

    // HTU
    uint16_t humidData;
     int16_t tempData;
  };

//  uint8_t allData[ sizeof(int32_t) + 2*sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint16_t) ];
  uint8_t allData[ sizeof(int32_t) + sizeof(uint8_t) + sizeof(uint16_t) + sizeof(int16_t) ];

} weatherData_t;


typedef union
{
  // scalar data
  struct
  {
    // MAXIM
    dataMAXIM_t redLedData  [ MAXIM_FIFO_DEPTH ];
    dataMAXIM_t irLedData   [ MAXIM_FIFO_DEPTH ];
    dataMAXIM_t greenLedData[ MAXIM_FIFO_DEPTH ];
    dataMAXIM_t sampNum;
  };

  uint8_t allData[ 3*MAXIM_FIFO_DEPTH*sizeof(dataMAXIM_t) + sizeof(dataMAXIM_t) ];

} healthData_t;

typedef int16_t mE_t;

typedef enum
{
  HEXIWEAR_STATUS_SUCCESS,    // success
  HEXIWEAR_STATUS_ERROR,      // fail
  HEXIWEAR_STATUS_INIT_ERROR, // initialization error
  HEXIWEAR_STATUS_POWER_ERROR // power mode error

} hexiwear_status_t;

typedef struct __attribute__ ((aligned))
{
   uint8_t isON_SensorTag;
   uint8_t isON_Haptic;

   /** space for additional flags */
   uint8_t padding[6];

} hexiwear_flags_t;

typedef enum
{
  HEXIWEAR_TIMER_SENSOR

} hexiwear_timer_t;

typedef struct name
{
    uint8_t ver_patchNumber;
    uint8_t ver_minorNumber;
    uint8_t ver_majorNumber;

} hexiwear_version_t;

typedef struct
{
	uint8_t hexiwear_major_ver; // hexiwear version
	uint8_t hexiwear_minor_ver; // hexiwear version
	uint8_t hexiwear_patch_ver; // hexiwear version
	uint8_t hexiwear_build_ver; // hexiwear version

	uint8_t pcb_main_ver; // main pcb version
	uint8_t pcb_hr_ver;   // heart-rate pcb version
	uint8_t pcb_cs_ver;   // capSense pcb version

	uint8_t padding;

} hexiwear_hw_rev_t;
