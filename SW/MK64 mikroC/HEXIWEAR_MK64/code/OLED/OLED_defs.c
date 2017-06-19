// File: OLED_defs.h

// Definitions of some commonly used types in the OLED module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "OLED_defs.h"
#include "OLED_info.h"
#include "OLED_SPI.h"
#include "generic_spi_info.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// global OLED handle
handleOLED_t oledModule; // =  {
//    FSL_OLED_SPI, // .protocol.instance, define which module to use
//    0,            // .protocol.device
//    0,            // .protocol.state
//    SPI_TIMEOUT   // .protocol.timeout, configure timeout in [ms]
//};

mutex_t spiAccessMutex;