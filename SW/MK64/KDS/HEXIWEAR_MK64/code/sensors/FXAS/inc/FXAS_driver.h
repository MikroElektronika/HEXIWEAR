/**
 * \file FXAS_driver.h
 * \version 1.00
 * \brief this file contains sensor FXAS21002's functionality
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

#include "FXAS_types.h"

/**
 * initialize the sensor
 * @param  fxasHandle    handle to be populated with sensor info
 * @param  fxasSettings  user settings
 * @return status flag
 */
fxas_status_t FXAS_Init(
                                handleFXAS_t* self,
                        const settingsFXAS_t* settings
                      );

/**
 * turn off the sensor
 * @return sensor's status
 */
fxas_status_t FXAS_Deinit();

/**
 * read raw data from the sensor
 * @param  sensorData pointer where to save sensor's data
 * @return            status flag
 */
fxas_status_t FXAS_ReadRawData ( int16_t* sensorData );


/**
 * put the FXAS21002C into standby mode
 * standby mode is necessary before attempting to modify most of the registers
 * @return status flag
 */
fxas_status_t FXAS_GotoStandby();

/**
 * set the FXAS21000 to Ready mode
 * it's necessary to be in this mode to output data
 * @return status flag
 */
fxas_status_t FXAS_GetReady();

/**
* put the FXAS21002C into active mode
 * it's necessary to be in this mode to output data
 * @return status flag
 */
fxas_status_t FXAS_SetActive();

/**
 * reset the module
 */
void FXAS_SoftReset();

/**
 * format data from raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void gyro_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      );

/**
 * format data from raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void gyro_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

/**
 * format raw to byte - currently unimplemented
 */
void gyro_fmtDef2Byte (
							const void* src,
								  void* dst,
							   uint32_t idx
						);
