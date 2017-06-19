/**
 * \file MAXIM_driver.h
 * \version 1.00
 * \brief this file contains sensor MAX30101's implemented functionality
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

#include "MAXIM_types.h"
#include "arm_math.h"

/**
 * initialize MAXIM module
 */
maxim_status_t MAXIM_Init(
                                  handleMAXIM_t* maximHandle,
                          const settingsMAXIM_t* maximSettings
                        );

/**
 * shutdown the sensor
 */
maxim_status_t MAXIM_Deinit();

/**
 * reset the module
 * when the reset-bit is set to one, all configuration, threshold,
 * and data registers are reset to their power-on-state through
 * a power-on reset
 *
 * the reset bit is cleared automatically back to zero after the reset sequence is completed
 */
maxim_status_t MAXIM_Reset();

/**
 * read raw sensor data
 */
maxim_status_t MAXIM_ReadRawData(
                                    uint8_t* dataBuff,
                                    uint8_t* sampleNum
                                );



/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hr_fmtDef2Float(
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
void hr_fmtDef2Me (
                    const void* src,
                          void* dst,
                       uint32_t idx
                  );

/**
 * [MAXIM_Enable description]
 * @return [description]
 */
maxim_status_t MAXIM_Enable();

/**
 * [MAXIM_Disable description]
 * @return [description]
 */
maxim_status_t MAXIM_Disable();

/**
 * [MAXIM_InstallCallback description]
 * @param callback [description]
 */
void MAXIM_InstallCallback( maxim_callback_t callback );

/**
 * testing HR sensor
 */
void MAXIM_Test();
