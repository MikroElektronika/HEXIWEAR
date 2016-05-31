/**
 * \file HTU_driver.h
 * \version 1.00
 * \brief this file contains sensor HTU21D's implemented functionality
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

#include "HTU_types.h"

/**
 * initialize i2c interface to HTU21D sensor and reset the module
 * @return status flag
 */
htu_status_t HTU_Init(
                        handleHTU_t* self,
                      settingsHTU_t* settings
                    );
/**
 * initialize i2c interface to HTU21D sensor and reset the module
 * @return status flag
 */
htu_status_t HTU_Deinit();

/**
 * reset the sensor
 * @return status flag
 */
htu_status_t HTU_SoftReset();

/**
 * configure the measurement resolution
 * @return status flag
 */
htu_status_t HTU_SetUserRegister();

/**
 * retrieve temperature data
 * @param  sensorData data to be filled
 * @return            status flag
 */
htu_status_t HTU_GetTemp ( int16_t* tempData );

/**
 * retrieve humidity data
 * @param  humData  data to be filled
 * @return          status flag
 */
htu_status_t HTU_GetHum( int16_t* humData );

/**
 * retrieve temperature and humidity data
 * @param  temperature address to place the temperature data to
 * @param  humidity    address to place the humidity data to
 * @return             status flag
 */
htu_status_t HTU_ReadRawData(
                            	int16_t* temperature,
								int16_t* humidity
							);

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void hum_fmtDef2Float (
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
void hum_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

/**
 * format raw to byte - currently unimplemented
 */
void hum_fmtDef2Byte(
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
void temp_fmtDef2Float(
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
void temp_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

/**
 * format raw to byte - currently unimplemented
 */
void temp_fmtDef2Byte(
						const void* src,
							  void* dst,
						   uint32_t idx
					);

/**
 * check if I2C bus needs to be recovered
 * @return status flag
 */
htu_status_t HTU_RecoverI2C();
