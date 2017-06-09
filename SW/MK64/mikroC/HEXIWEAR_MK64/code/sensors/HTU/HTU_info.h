// File: HTU_info.h

// Some commonly used macros in the HTU sensor module.

#ifndef _HTU_info_h_
#define _HTU_info_h_

////////////////////////////////////////////////////////////////////////////////
// Macro definitions                                                          //
////////////////////////////////////////////////////////////////////////////////
 
// unshifted 7-bit I2C address
#define HTU_I2C_ADDRESS  (0x40)

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

#endif