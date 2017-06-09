// File: FXAS_info.h

// Some commonly used macros in the FXAS sensor module.

#ifndef _FXAS_info_h_
#define _FXAS_info_h_

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// unshifted 7-bit I2C address
#define FXAS_I2C_ADDR       ( 0x20 )

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

#endif