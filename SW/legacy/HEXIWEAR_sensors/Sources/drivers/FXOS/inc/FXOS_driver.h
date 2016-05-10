/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission
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
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 */

#ifndef HG_FXOS_DRIVER
#define HG_FXOS_DRIVER

#include "FXOS_types.h"
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
statusFXOS_t FXOS_Init(
                                handleFXOS_t* self,
                        const settingsFXOS_t* settings
                      );

/* Deinit the fxos8700 codec. Mainly used to close the I2C controller

 * @param handler fxos8700 handler structure pointer
 */
statusFXOS_t FXOS_Deinit();

/* read sensor data from FXOS using I2C

 * @param handler FXOS8700 handler structure
 * @param val Sensor data read from FXOS
 */
statusFXOS_t FXOS_ReadRawData (
                                int16_t* sensorData // 6-element array
                              );

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

#endif

