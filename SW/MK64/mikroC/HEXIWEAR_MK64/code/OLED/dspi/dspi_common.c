// File: dspi_common.c

// Definitions of common resources in the DSPI module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "FreeRTOS.h"
#include "dspi_edma_shared_function.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Pointer to runtime state structure.
void* g_dspiStatePtr[ SPI_INSTANCE_COUNT ] = { NULL };

// Table of base pointers for SPI instances.
uint32_t* const g_dspiBase[ SPI_INSTANCE_COUNT ] = SPI_BASE_ADDRS;

// Table of SPI FIFO sizes per instance.
const uint32_t g_dspiFifoSize[ SPI_INSTANCE_COUNT ] = 
    FSL_FEATURE_DSPI_FIFO_SIZEx;

// Table to save DSPI IRQ enum numbers.
const uint32_t g_dspiIrqId[] = SPI_IRQS;