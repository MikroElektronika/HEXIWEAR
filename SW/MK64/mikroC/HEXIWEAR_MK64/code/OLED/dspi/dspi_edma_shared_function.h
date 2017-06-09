// File: dspi_edma_shared_function.h

// Declarations of shared functionalities in the DSPI module.

#ifndef _dspi_edma_shared_function_h_
#define _dspi_edma_shared_function_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include "dspi_hal.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define SPI_INSTANCE_COUNT (3U) // Number of instances of the SPI module.
#define SPI0_IDX (0U) // Instance number for SPI0.
#define SPI1_IDX (1U) // Instance number for SPI1.
#define SPI2_IDX (2U) // Instance number for SPI2.

// Peripheral SPI0 base address
#define SPI0_BASE                                ( 0x4002C000u )
// Peripheral SPI1 base address
#define SPI1_BASE                                ( 0x4002D000u )
// Peripheral SPI2 base address
#define SPI2_BASE                                ( 0x400AC000u )
// Array initializer of SPI peripheral base addresses
#define SPI_BASE_ADDRS { SPI0_BASE, SPI1_BASE, SPI2_BASE }

// Interrupt vectors for the SPI peripheral type
#define SPI_IRQS { IVT_INT_SPI0, IVT_INT_SPI1, IVT_INT_SPI2 }

// Receive/transmit FIFO size in number of items. */
#define FSL_FEATURE_DSPI_FIFO_SIZE (4)
#define FSL_FEATURE_DSPI_FIFO_SIZEx { 4, 1, 1 }
// Maximum transfer data width in bits. */
#define FSL_FEATURE_DSPI_MAX_DATA_WIDTH (16)
// Maximum number of chip select pins.
// (Reflects the width of register bit field PUSHR[PCS].)
#define FSL_FEATURE_DSPI_MAX_CHIP_SELECT_COUNT (6)
// Number of chip select pins.
#define FSL_FEATURE_DSPI_CHIP_SELECT_COUNT (6)
// Has chip select strobe capability on the PCS5 pin.
#define FSL_FEATURE_DSPI_HAS_CHIP_SELECT_STROBE (1)
// Has separated TXDATA and CMD FIFOs (register SREX).
#define FSL_FEATURE_DSPI_HAS_SEPARATE_TXDATA_CMD_FIFO (0)
// Has 16-bit data transfer support.
#define FSL_FEATURE_DSPI_16BIT_TRANSFERS (1)
// Has separate DMA RX and TX requests.
#define FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(x) \
    ((x) == 0 ? (1) : \
    ((x) == 1 ? (0) : \
    ((x) == 2 ? (0) : (-1))))

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Table of base pointers for SPI instances.
extern uint32_t* const g_dspiBase[ SPI_INSTANCE_COUNT ];

// Table to save DSPI IRQ enumeration numbers.
extern const uint32_t g_dspiIrqId[ SPI_INSTANCE_COUNT ];

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Passes IRQ control to either the master or slave driver.
void DSPI_DRV_EdmaIRQHandler( uint32_t instance );


#endif