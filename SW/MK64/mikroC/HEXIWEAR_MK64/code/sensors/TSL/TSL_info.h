// File: TSL_info.h

// Some commonly used macros in the TSL sensor module.

#ifndef _TSL_info_h_
#define _TSL_info_h_

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// unshifted 7-bit I2C address
#define TSL_I2C_ADDRESS  (0x29)

#define TSL_COMMAND_BIT (0x80)    // must be 1
#define TSL_CLEAR_BIT   (0x40)    // clears any pending interrupt (write 1)
#define TSL_WORD_BIT    (0x20)    // read/write word (rather than byte)
#define TSL_BLOCK_BIT   (0x10)    // using block read/write

#define TSL_CONTROL_POWERON  (0x03)
#define TSL_CONTROL_POWEROFF (0x00)

#define TSL_LUX_SCALE     (14)      // scale by 2^14
#define TSL_RATIO_SCALE   (9)       // scale ratio by 2^9
#define TSL_CHSCALE       (10)      // scale channel values by 2^10
#define TSL_CHSCALE_TINT0 (0x7517)  // 322/11 * 2^TSL_LUX_CHSCALE
#define TSL_CHSCALE_TINT1 (0x0FE7)  // 322/81 * 2^TSL_LUX_CHSCALE

// T, FN and CL package coefficients
#define TSL_K1T (0x0040)  // 0.125 * 2^RATIO_SCALE
#define TSL_B1T (0x01f2)  // 0.0304 * 2^LUX_SCALE
#define TSL_M1T (0x01be)  // 0.0272 * 2^LUX_SCALE
#define TSL_K2T (0x0080)  // 0.250 * 2^RATIO_SCALE
#define TSL_B2T (0x0214)  // 0.0325 * 2^LUX_SCALE
#define TSL_M2T (0x02d1)  // 0.0440 * 2^LUX_SCALE
#define TSL_K3T (0x00c0)  // 0.375 * 2^RATIO_SCALE
#define TSL_B3T (0x023f)  // 0.0351 * 2^LUX_SCALE
#define TSL_M3T (0x037b)  // 0.0544 * 2^LUX_SCALE
#define TSL_K4T (0x0100)  // 0.50 * 2^RATIO_SCALE
#define TSL_B4T (0x0270)  // 0.0381 * 2^LUX_SCALE
#define TSL_M4T (0x03fe)  // 0.0624 * 2^LUX_SCALE
#define TSL_K5T (0x0138)  // 0.61 * 2^RATIO_SCALE
#define TSL_B5T (0x016f)  // 0.0224 * 2^LUX_SCALE
#define TSL_M5T (0x01fc)  // 0.0310 * 2^LUX_SCALE
#define TSL_K6T (0x019a)  // 0.80 * 2^RATIO_SCALE
#define TSL_B6T (0x00d2)  // 0.0128 * 2^LUX_SCALE
#define TSL_M6T (0x00fb)  // 0.0153 * 2^LUX_SCALE
#define TSL_K7T (0x029a)  // 1.3 * 2^RATIO_SCALE
#define TSL_B7T (0x0018)  // 0.00146 * 2^LUX_SCALE
#define TSL_M7T (0x0012)  // 0.00112 * 2^LUX_SCALE
#define TSL_K8T (0x029a)  // 1.3 * 2^RATIO_SCALE
#define TSL_B8T (0x0000)  // 0.000 * 2^LUX_SCALE
#define TSL_M8T (0x0000)  // 0.000 * 2^LUX_SCALE

// CS package values
#define TSL_K1C           (0x0043)  // 0.130 * 2^RATIO_SCALE
#define TSL_B1C           (0x0204)  // 0.0315 * 2^LUX_SCALE
#define TSL_M1C           (0x01ad)  // 0.0262 * 2^LUX_SCALE
#define TSL_K2C           (0x0085)  // 0.260 * 2^RATIO_SCALE
#define TSL_B2C           (0x0228)  // 0.0337 * 2^LUX_SCALE
#define TSL_M2C           (0x02c1)  // 0.0430 * 2^LUX_SCALE
#define TSL_K3C           (0x00c8)  // 0.390 * 2^RATIO_SCALE
#define TSL_B3C           (0x0253)  // 0.0363 * 2^LUX_SCALE
#define TSL_M3C           (0x0363)  // 0.0529 * 2^LUX_SCALE
#define TSL_K4C           (0x010a)  // 0.520 * 2^RATIO_SCALE
#define TSL_B4C           (0x0282)  // 0.0392 * 2^LUX_SCALE
#define TSL_M4C           (0x03df)  // 0.0605 * 2^LUX_SCALE
#define TSL_K5C           (0x014d)  // 0.65 * 2^RATIO_SCALE
#define TSL_B5C           (0x0177)  // 0.0229 * 2^LUX_SCALE
#define TSL_M5C           (0x01dd)  // 0.0291 * 2^LUX_SCALE
#define TSL_K6C           (0x019a)  // 0.80 * 2^RATIO_SCALE
#define TSL_B6C           (0x0101)  // 0.0157 * 2^LUX_SCALE
#define TSL_M6C           (0x0127)  // 0.0180 * 2^LUX_SCALE
#define TSL_K7C           (0x029a)  // 1.3 * 2^RATIO_SCALE
#define TSL_B7C           (0x0037)  // 0.00338 * 2^LUX_SCALE
#define TSL_M7C           (0x002b)  // 0.00260 * 2^LUX_SCALE
#define TSL_K8C           (0x029a)  // 1.3 * 2^RATIO_SCALE
#define TSL_B8C           (0x0000)  // 0.000 * 2^LUX_SCALE
#define TSL_M8C           (0x0000)  // 0.000 * 2^LUX_SCALE

#define TSL_REG_CONTROL          (0x00)
#define TSL_REG_TIMING           (0x01)
#define TSL_REG_THRESHHOLDL_LOW  (0x02)
#define TSL_REG_THRESHHOLDL_HIGH (0x03)
#define TSL_REG_THRESHHOLDH_LOW  (0x04)
#define TSL_REG_THRESHHOLDH_HIGH (0x05)
#define TSL_REG_INTERRUPT        (0x06)
#define TSL_REG_CRC              (0x08)
#define TSL_REG_ID               (0x0A)
#define TSL_REG_CHAN0_LOW        (0x0C)
#define TSL_REG_CHAN0_HIGH       (0x0D)
#define TSL_REG_CHAN1_LOW        (0x0E)
#define TSL_REG_CHAN1_HIGH       (0x0F)

#endif