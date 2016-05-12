/**
 * OLED-related structures
 * Project KWAP, 2015
 */

#include "OLED_defs.h"
#include "OLED_info.h"
#include "OLED_SPI.h"
#include "GPIO.h"
#include "main.h"
#include "generic_spi_info.h"

handleOLED_t
  oledModule =  {
                  // define module to use
                  .protocol.instance = FSL_OLED_SPI,

                  // configure timeout
                  .protocol.timeout = 500
                };

settingsOLED_t
  oledSettings =  {
                    .DCpin  = OLED_DC,
                    .CSpin  = OLED_CS,
                    .RSTpin = OLED_RST,
                    .ENpin  = PWR_OLED
                  };
