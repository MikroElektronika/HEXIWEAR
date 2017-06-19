/**
 * \file MAXIM_defs.c
 * \version 1.00
 * \brief this file contains sensor MAX30101's global objects
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

#include "MAXIM_defs.h"
#include "MAXIM_info.h"

#include "NFS_I2C.h"
#include "generic_i2c_info.h"

handleMAXIM_t
  maximModule = {
                  .protocol.instance = FSL_NFS_I2C,
                  .protocol.timeout  = I2C_TIMEOUT
                };

settingsMAXIM_t
  maximSettings = {
                    .mode  = modeMultiLED,

                    // slots
                    .LEDSlot[0] = LEDSlotGreen,
                    .LEDSlot[1] = LEDSlotNone,
                    .LEDSlot[2] = LEDSlotNone,
                    .LEDSlot[3] = LEDSlotNone,

                    .activeSlots = 1,

                    // timings
                    .sampleRate = sampleRate_50,
                    .pulseWidth = ledPower_411,

                    .range      = adcRange8192,

                    // currents
                    .LEDCurrentRed   = 0x0,
                    .LEDCurrentIR    = 0x0,
                    .LEDCurrentGreen = 0x0,

                    // average samples
                    .oversample = ovsNone,

                    // I2C
                    .address = MAXIM_I2C_ADDRESS,
                    .baudRate_kbps = 400ul
                  };
