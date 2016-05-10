/**
 * MAXIM-related data structures
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
