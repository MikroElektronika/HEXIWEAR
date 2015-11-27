/**
 * FXOS8700-related structures
 * Project KWAP, 2015
 */

#include "FXOS_defs.h"
#include "FXOS_info.h"

#include "i2cCom1.h"
#include "generic_i2c_info.h"

dataFXOS_t
  fxosData;

handleFXOS_t
  fxosModule =  {
                  .protocol.instance = FSL_I2CCOM1,
                  .protocol.timeout  = I2C_TIMEOUT
                };

settingsFXOS_t
  fxosSettings = {
                    .odr     = fxosODR7,
                    .osr     = fxosOSR7,
                    .mode    = fxosBoth,
                    .range   = fxosRange4g,
                    .address = FXOS_I2C_ADDRESS
                  };
