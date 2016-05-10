/**
 * MAXIM-related data structures
 * Project HEXIWEAR, 2015
 */

#include "MAXIM_defs.h"
#include "MAXIM_info.h"

#include "i2cCom2.h"
#include "generic_i2c_info.h"

handleMAXIM_t
  maximModule = {
                  .protocol.instance = FSL_I2CCOM2,
                  .protocol.timeout  = I2C_TIMEOUT
                };

settingsMAXIM_t
  maximSettings = {
                    .mode  = modeHR,

                    .slot1 = slotRed,
                    .slot2 = slotRed,
                    .slot3 = slotRed,
                    .slot4 = slotRed,

                    .sampleRate = sampleRate_400,
                    .pulseWidth = ledPower_411,

                    .address = MAXIM_I2C_ADDRESS
                  };
