/**
 * TSL2561-related data structures
 * Project HEXIWEAR, 2015
 */

#include "HTU_defs.h"
#include "HTU_info.h"

#include "NFS_I2C.h"
#include "generic_i2c_info.h"

handleHTU_t
  htuModule = {
                // define module to use
                .protocol.instance = FSL_NFS_I2C, // defined in board.h

                // configure timeout
                .protocol.timeout = I2C_TIMEOUT
              };

settingsHTU_t
  htuSettings = {
                  .bitRes  = BITRES_HTU_RH_8_TEMP12,
                  // .bitRes  = BITRES_HTU_RH_10_TEMP13,
                  .address = HTU_I2C_ADDRESS,
                  .baudRate_kbps = HTU_I2C_BAUDRATE
                };
