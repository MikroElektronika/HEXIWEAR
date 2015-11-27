/**
 * FXAS21002-related data structures
 * Project KWAP, 2015
 */

#include "FXAS_defs.h"
#include "FXAS_info.h"

#include "i2cCom1.h"
#include "generic_i2c_info.h"

// sensor's handle
handleFXAS_t
  fxasModule =  {
                  .protocol.instance = FSL_I2CCOM1,
                  .protocol.timeout  = I2C_TIMEOUT
                };

// sensor's user settings
settingsFXAS_t
  fxasSettings =  {
                        .odr = GODR_200HZ,
                        .fsr = GFSR_250DPS,
                    .address = FXAS_I2C_ADDR
                  };
