/**
 * \file FXOS_driver.h
 * \version 1.00
 * \brief this file contains sensor FXOS8700cq implemented functionality
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

#include "FXOS_types.h"
#include "FXOS_defs.h"
#include "sensor_types.h"

/**
 *
 * If the fxos_Config is NULL, it would initialize fxos8700 using default settings
 * The default setting:
 * fxos_Config->odr = kFxosODR1,
 * fxos_Config->osr = kFxosOSR7,
 * fxos_Config->hms = kFxosBoth,
 * fxos_Config->range = kFxos4gMode,
 *
 * @param handler fxos8700 handler structure
 * @param fxos_Config fxos8700 configuration structure
 */
fxos_status_t FXOS_Init(
                                handleFXOS_t* self,
                        const settingsFXOS_t* settings
                      );

 /** Deinit the fxos8700 codec. Mainly used to close the I2C controller

 * @param handler fxos8700 handler structure pointer
 */
fxos_status_t FXOS_Deinit();

 /** read sensor data from FXOS using I2C

 * @param handler FXOS8700 handler structure
 * @param val Sensor data read from FXOS
 */
fxos_status_t FXOS_ReadRawData (
                                int16_t* sensorData // 6-element array
                              );

/**
 *  accelerometer offset calibration
 */
fxos_status_t FXOS_CalibrateAcc();

/**
 *  magnetometer offset calibration
 */
fxos_status_t FXOS_CalibrateMag();

/**
 * formatting pointers
 */

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void acc_fmtDef2Float (
                        const void* src,
                              void* dst,
                           uint32_t idx
                      );

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void acc_fmtDef2Me(
                    const void* src,
                          void* dst,
                       uint32_t idx
                  );

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void mag_fmtDef2Float (
                        const void* src,
                              void* dst,
                           uint32_t idx
                      );

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void mag_fmtDef2Me(
                    const void* src,
                          void* dst,
                       uint32_t idx
                  );

/**
 * format raw to byte - currently unimplemented
 */
void mag_fmtDef2Byte(
						const void* src,
							  void* dst,
						   uint32_t idx
					);

/**
 * format raw to byte - currently unimplemented
 */
void acc_fmtDef2Byte(
						const void* src,
							  void* dst,
						   uint32_t idx
					);

/**
 * format mE to raw format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void acc_fmtMe2Def(
                    const void* src,
                          void* dst
//                       uint32_t idx
                  );

/**
 * [FXOS_Sleep description]
 * @return [description]
 */
fxos_status_t FXOS_GotoStandby();

/**
 * [FXOS_Wake description]
 * @return [description]
 */
fxos_status_t FXOS_SetActive();

/**
 * reset the module
 */
fxos_status_t FXOS_SoftReset();

/**
 * [FXOS_ReadTemp description]
 * @return [description]
 */
fxos_status_t FXOS_ReadRawTemp( uint8_t* tempVal );

/**
 * [FXOS_ConfigureTapEvent description]
 * @return [description]
 */
fxos_status_t FXOS_ConfigureTapEvent();

/**
 * enable tap detection
 */
fxos_status_t FXOS_EnableTap();

/**
 * disable tap detection
 */
fxos_status_t FXOS_DisableTap();

/**
 * check if tap is enabled
 */
bool FXOS_IsTapEnabled();

/**
 * callback for the interrupt
 * @return status flag
 */
fxos_status_t FXOS_Callback();

/**
 * read the status of the tap source register
 */
void FXOS_TapHandler();

/**
 * check if I2C bus needs to be recovered
 * @return status flag
 */
fxos_status_t FXOS_RecoverI2C();

/**
 * read FXOS status register
 * @param sensorStatus variable tu put the status register value in
 * @return reading status flag
 */
fxos_status_t FXOS_ReadStatus( uint8_t* sensorStatus );

/**
 * check if tap is enabled
 * @return status flag
 */
bool FXOS_CheckForTap();
