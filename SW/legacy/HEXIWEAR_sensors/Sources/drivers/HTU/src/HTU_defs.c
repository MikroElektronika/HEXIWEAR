/**
 * TSL2561-related data structures
 * Project HEXIWEAR, 2015
 */

#include "HTU_defs.h"
#include "HTU_info.h"

#include "i2cCom2.h"
#include "generic_i2c_info.h"

handleHTU_t
  htuModule = {
                // define module to use
                .protocol.instance = FSL_I2CCOM2, // defined in board.h

                // configure timeout
                .protocol.timeout = I2C_TIMEOUT
              };

settingsHTU_t
  htuSettings = {
                  .bitRes  = BITRES_HTU_RH_12_TEMP14,
                  .address = HTU_I2C_ADDRESS
                };
