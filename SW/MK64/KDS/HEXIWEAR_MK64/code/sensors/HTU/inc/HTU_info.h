/**
 * \file HTU_info.h
 * \version 1.00
 * \brief this file contains sensor HTU21D related info, constants, etc.
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

#define HTU_I2C_ADDRESS  (0x40)
#define HTU_I2C_BAUDRATE ( I2C_BAUDRATE )

#define HTU21D_TRIGGER_TEMP_HOLD   0xE3
#define HTU21D_TRIGGER_HUMD_HOLD   0xE5
#define HTU21D_TRIGGER_TEMP_NOHOLD 0xF3
#define HTU21D_TRIGGER_HUMD_NOHOLD 0xF5
#define HTU21D_WRITE_USER_REG      0xE6
#define HTU21D_READ_USER_REG       0xE7
#define HTU21D_SOFT_RESET          0xFE

#define HTU21D_END_OF_BATTERY_SHIFT 6
#define HTU21D_ENABLE_HEATER_SHIFT  2
#define HTU21D_DISABLE_OTP_RELOAD   1
#define HTU21D_RESERVED_MASK        0x31

#define HTU21D_STARTUP_DELAY 15000
#define HTU21D_TEMP_MAX_DELAY 50000

#define HTU_TEMP_CALIB_OFFSET_0 ( 0 )
#define HTU_TEMP_CALIB_OFFSET_1 ( 4 )
#define HTU_TEMP_CALIB_OFFSET_2 ( 6 )
