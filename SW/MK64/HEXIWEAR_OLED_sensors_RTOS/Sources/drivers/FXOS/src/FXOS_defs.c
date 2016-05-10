/**
 * FXOS8700-related structures
 * Project KWAP, 2015
 */

#include "FXOS_defs.h"
#include "FXOS_info.h"

#include "FS_I2C.h"
#include "generic_i2c_info.h"

dataFXOS_t
  fxosData;

handleFXOS_t
  fxosModule =  {
                  .protocol.instance = 1,
                  .protocol.timeout  = I2C_TIMEOUT
                };

settingsFXOS_t
  fxosSettings = {
                    .odr     = fxosODR0,
                    .osr     = fxosOSR0,
                    .mode    = fxosBoth,
                    .range   = fxosRange4g,

                    .address       = FXOS_I2C_ADDRESS,
                    .baudRate_kbps = FXOS_I2C_BAUDRATE
                  };
