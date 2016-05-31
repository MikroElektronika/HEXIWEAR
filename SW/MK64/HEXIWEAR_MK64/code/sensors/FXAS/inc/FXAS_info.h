/**
 * \file FXAS_info.h
 * \version 1.00
 * \brief this file contains sensor FXAS21002's general info, constants etc.
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

// register addresses
#define FXAS_H_STATUS       (0x00)
#define FXAS_H_DR_STATUS    (0x07)
#define FXAS_H_F_STATUS     (0x08)
#define FXAS_H_OUT_X_MSB    (0x01)
#define FXAS_H_OUT_X_LSB    (0x02)
#define FXAS_H_OUT_Y_MSB    (0x03)
#define FXAS_H_OUT_Y_LSB    (0x04)
#define FXAS_H_OUT_Z_MSB    (0x05)
#define FXAS_H_OUT_Z_LSB    (0x06)
#define FXAS_H_F_SETUP      (0x09)
#define FXAS_H_F_EVENT      (0x0A)
#define FXAS_H_INT_SRC_FLAG (0x0B)
#define FXAS_H_WHO_AM_I     (0x0C)
#define FXAS_H_CTRL_REG0    (0x0D)
#define FXAS_H_RT_CFG       (0x0E)
#define FXAS_H_RT_SRC       (0x0F)
#define FXAS_H_RT_THS       (0x10)
#define FXAS_H_RT_COUNT     (0x11)
#define FXAS_H_TEMP         (0x12)
#define FXAS_H_CTRL_REG1    (0x13)
#define FXAS_H_CTRL_REG2    (0x14)
#define FXAS_H_CTRL_REG3    (0x15)


// i2c parameters
#define FXAS_I2C_ADDR       ( 0x20 )
#define FXAS_I2C_BAUDRATE   ( I2C_BAUDRATE )
