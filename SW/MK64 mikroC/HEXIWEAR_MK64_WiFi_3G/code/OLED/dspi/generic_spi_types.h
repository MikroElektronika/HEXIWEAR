// File: generic_spi_types.h

// Definitions of some commonly used types in the generic SPI module.

#ifndef _genric_spi_types_h_
#define _genric_spi_types_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "generic_spi_info.h"
#include "dspi_edma_master_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    // general SPI information
                    uint32_t instance; // SPI instance
          dspi_edma_device_t device;   // SPI device setting
    dspi_edma_master_state_t state;    // SPI internal state space
                    uint32_t timeout;  // SPI timeout

    // specific SPI information should go below this

} genericSpiHandle_t;

// SPI status enum
typedef enum
{
    STATUS_SPI_SUCCESS,     // success
    STATUS_SPI_ERROR,       // fail
    STATUS_SPI_INIT_ERROR,  // initialization error
    STATUS_SPI_DEINIT_ERROR // deinitialization error

} statusSPI_t;


#endif