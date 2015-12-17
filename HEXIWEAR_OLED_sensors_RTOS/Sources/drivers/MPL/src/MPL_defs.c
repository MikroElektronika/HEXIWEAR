/**
 * MPL3115A2-related structures
 * Project KWAP, 2015
 */

#include "MPL_defs.h"
#include "MPL_info.h"

#include "FS_I2C.h"
#include "generic_i2c_info.h"

handleMPL_t
  mplModule = {
                .protocol.instance = FSL_FS_I2C, // module to be used
                .protocol.timeout  = I2C_TIMEOUT  // configure timeout
              };

settingsMPL_t
  mplSettings = {
                  .mode       = MPL_MODE_PRESSURE, // barometer mode
//                  .oversample = MPL_OS_7,          // over-sampling ratio
                  .oversample = MPL_OS_0,          // over-sampling ratio
                  .address    = MPL_I2C_ADDRESS
                };
