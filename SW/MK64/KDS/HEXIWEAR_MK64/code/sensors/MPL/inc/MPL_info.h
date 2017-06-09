/**
 * \file MPL_info.h
 * \version 1.00
 * \brief this file contains sensor MPL3115A2 related constants and other info
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

// Starting altitude to calculate mean sea level pressure in [m]
// #define START_ALTITUDE 89

// unshifted 7-bit I2C address
#define MPL_I2C_ADDRESS  (0x60)
#define MPL_I2C_BAUDRATE ( I2C_BAUDRATE )

#define MPL_OS_SHIFT (3)
#define MPL_OS_MASK  (0x7 << MPL_OS_SHIFT)

#define REG_STATUS      (0x00)
#define OUT_P_MSB       (0x01)
#define OUT_P_CSB       (0x02)
#define OUT_P_LSB       (0x03)
#define OUT_T_MSB       (0x04)
#define OUT_T_LSB       (0x05)
#define DR_STATUS       (0x06)
#define OUT_P_DELTA_MSB (0x07)
#define OUT_P_DELTA_CSB (0x08)
#define OUT_P_DELTA_LSB (0x09)
#define OUT_T_DELTA_MSB (0x0A)
#define OUT_T_DELTA_LSB (0x0B)
#define WHO_AM_I        (0x0C)
#define F_STATUS        (0x0D)
#define F_DATA          (0x0E)
#define F_SETUP         (0x0F)
#define TIME_DLY        (0x10)
#define SYSMOD          (0x11)
#define INT_SOURCE      (0x12)
#define PT_DATA_CFG     (0x13)
#define BAR_IN_MSB      (0x14)
#define BAR_IN_LSB      (0x15)
#define P_TGT_MSB       (0x16)
#define P_TGT_LSB       (0x17)
#define T_TGT           (0x18)
#define P_WND_MSB       (0x19)
#define P_WND_LSB       (0x1A)
#define T_WND           (0x1B)
#define P_MIN_MSB       (0x1C)
#define P_MIN_CSB       (0x1D)
#define P_MIN_LSB       (0x1E)
#define T_MIN_MSB       (0x1F)
#define T_MIN_LSB       (0x20)
#define P_MAX_MSB       (0x21)
#define P_MAX_CSB       (0x22)
#define P_MAX_LSB       (0x23)
#define T_MAX_MSB       (0x24)
#define T_MAX_LSB       (0x25)
#define MPL_CTRL_REG1   (0x26)
#define MPL_CTRL_REG2   (0x27)
#define MPL_CTRL_REG3   (0x28)
#define MPL_CTRL_REG4   (0x29)
#define MPL_CTRL_REG5   (0x2A)
#define OFF_P           (0x2B)
#define OFF_T           (0x2C)
#define OFF_H           (0x2D)

// shifts
#define MPL_TDR_SHIFT  (1)
#define MPL_PDR_SHIFT  (2)
#define MPL_PTDR_SHIFT (3)

#define MPL_SBYB_SHIFT (0)
#define MPL_OST_SHIFT  (1)
#define MPL_RST_SHIFT  (2)
