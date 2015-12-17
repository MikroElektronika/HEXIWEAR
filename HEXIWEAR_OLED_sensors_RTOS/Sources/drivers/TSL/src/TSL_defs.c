/**
 * TSL2561-related data structures
 * Project HEXIWEAR, 2015
 */

#include "TSL_defs.h"
#include "TSL_info.h"

#include "generic_i2c_info.h"
#include "NFS_I2C.h"


handleTSL_t
  tslModule = {
                .protocol.instance = FSL_NFS_I2C,
                .protocol.timeout  = I2C_TIMEOUT
              };

settingsTSL_t
  tslSettings = {
                  .timing  = TSL_INTEGRATION_TIME_13MS,
                  .gain    = TSL_GAIN_16X,
                  .address = TSL_I2C_ADDRESS
                };
