/**
 * FLASH-related data structures
 * Project HEXIWEAR, 2015
 */

#include "FLASH_defs.h"
#include "GPIO.h"
#include "board.h"

#include "generic_spi_info.h"
#include "FLASH_SPI.h"

handleFLASH_t
 flashModule =  {
                  // define module to use
                  .protocol.instance = FSL_FLASH_SPI,

                  // configure timeout
                  .protocol.timeout = SPI_TIMEOUT
                };

settingsFLASH_t
  flashSettings = {
                    .CSpin   = FLASH_CS // output
//                    .HOLDpin// output
//                    .Wpin // output
                  };
