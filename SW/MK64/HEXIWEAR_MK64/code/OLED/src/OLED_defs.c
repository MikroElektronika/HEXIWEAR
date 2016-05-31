/**
 * \file OLED_defs.c
 * \version 1.00
 * \brief this file contains data-structures with specific settings for OLED
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

#include "OLED_defs.h"
#include "OLED_info.h"
#include "OLED_SPI.h"
#include "GPIO.h"
#include "generic_spi_info.h"

/** global OLED handle */
handleOLED_t
  oledModule =  {
                  .protocol.instance = FSL_OLED_SPI, /**< define which module to use */

                  .protocol.timeout = SPI_TIMEOUT    /**< configure timeout in [ms] */
                };

/** specific OLED settings */
settingsOLED_t
  oledSettings =  {
                    .DCpin  = OLED_DC,  /**< OLED DC pin  */
                    .CSpin  = OLED_CS,  /**< OLED Chip Select pin  */
                    .RSTpin = OLED_RST, /**< OLED Reset pin  */
                    .ENpin  = PWR_OLED  /**< OLED Power Supply pin  */
                  };

mutex_t
  spiAccessMutex;
