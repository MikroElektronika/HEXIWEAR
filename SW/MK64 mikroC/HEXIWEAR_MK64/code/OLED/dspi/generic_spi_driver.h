// File: generic_spi_driver.h

// Declarations of main functionalities in the generic SPI module.

#ifndef _genric_spi_driver_h_
#define _genric_spi_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "generic_spi_types.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initializes SPI interface and its required structures.
statusSPI_t SPI_Init( genericSpiHandle_t* self );

// Deinitializes SPI interface (not used).
statusSPI_t SPI_Deinit( genericSpiHandle_t* self );

#endif