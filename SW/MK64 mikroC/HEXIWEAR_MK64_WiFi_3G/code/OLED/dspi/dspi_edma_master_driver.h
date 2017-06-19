// File: dspi_edma_master_driver.h

// Declarations of master functionalities in the DSPI module.

#ifndef _dspi_edma_master_driver_h_
#define _dspi_edma_master_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "dspi_hal.h"
#include "edma_driver.h"
#include "dspi_edma_shared_function.h"
#include "OSA.h"

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// Data structure containing information
// about a device on the SPI bus with EDMA.
typedef struct DspiEdmaDevice {
    // Baud rate in bits per second.
    uint32_t bitsPerSec;
    // Data format configuration structure.
    dspi_data_format_config_t dataBusConfig;
} dspi_edma_device_t;

// Runtime state structure for the DSPI master driver with EDMA.
typedef struct DspiEdmaMasterState {
    // Desired Clock and Transfer Attributes Register (CTAR)
    dspi_ctar_selection_t whichCtar;
    // Desired number of bits per frame
    uint32_t bitsPerFrame;
    // Desired Peripheral Chip Select (pcs)
    dspi_which_pcs_config_t whichPcs;
    // Option to enable the continuous assertion of chip select
    // between transfers
    bool isChipSelectContinuous;
    // Module source clock
    uint32_t dspiSourceClock;
    // True if there is an active transfer.
    volatile bool isTransferInProgress;
    // True if transfer is a blocking transaction.
    volatile bool isTransferBlocking;
    // Used to wait for ISR to complete its business.
    semaphore_t irqSync;
    // Structure definition for the eDMA channel
    edma_chn_state_t dmaCmdData2Fifo;
    // Structure definition for the eDMA channel
    edma_chn_state_t dmaSrc2CmdData;
    // Structure definition for the eDMA channel
    edma_chn_state_t dmaFifo2Receive;
    // Pointer to SW TCD in memory
    edma_software_tcd_t *stcdSrc2CmdDataLast;
    // Flag used for 16-bit transfers with odd byte count
    bool extraByte;
    // The buffer into which received bytes are placed.
    uint8_t *rxBuffer;
    // Number of bytes to receive.
    uint32_t rxTransferByteCnt;
} dspi_edma_master_state_t;

// The user configuration structure for the DSPI master driver with EDMA.
typedef struct DspiEdmaMasterUserConfig {
    // Desired Clock and Transfer Attributes Register(CTAR)
    dspi_ctar_selection_t whichCtar;
    // Disable or Enable continuous SCK operation
    bool isSckContinuous;
    // Option to enable the continuous assertion of chip select
    // between transfers
    bool isChipSelectContinuous;
    // Desired Peripheral Chip Select (pcs)
    dspi_which_pcs_config_t whichPcs;
    // Peripheral Chip Select (pcs) polarity setting.
    dspi_pcs_polarity_config_t pcsPolarity;
} dspi_edma_master_user_config_t;

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

// Initialization and shutdown

// Initializes a DSPI instance for master mode operation to work with EDMA.
dspi_status_t DSPI_DRV_EdmaMasterInit( uint32_t instance,
    dspi_edma_master_state_t *dspiEdmaState,
    const dspi_edma_master_user_config_t *userConfig,
    edma_software_tcd_t *stcdSrc2CmdDataLast );

// Shuts down a DSPI instance with the EDMA support.
dspi_status_t DSPI_DRV_EdmaMasterDeinit( uint32_t instance );

// Configures the DSPI master mode bus timing delay options
// with the EDMA support.
dspi_status_t DSPI_DRV_EdmaMasterSetDelay( uint32_t instance,
    dspi_delay_type_t whichDelay, uint32_t delayInNanoSec,
    uint32_t *calculatedDelay );
    
// Bus configuration

// Configures the DSPI port physical parameters to access a device on the bus
// with the EDMA support.
dspi_status_t DSPI_DRV_EdmaMasterConfigureBus( uint32_t instance,
    const dspi_edma_device_t *device, uint32_t *calculatedBaudRate );
    
// Blocking transfers

// Performs a blocking SPI master mode transfer with the EDMA support.
dspi_status_t DSPI_DRV_EdmaMasterTransferBlocking( uint32_t instance,
    const dspi_edma_device_t *device, const uint8_t *sendBuffer,
    uint8_t *receiveBuffer, size_t transferByteCount, uint32_t timeout );
    
// Non-blocking transfers

// Performs a non-blocking SPI master mode transfer with the EDMA support.
dspi_status_t DSPI_DRV_EdmaMasterTransfer( uint32_t instance,
    const dspi_edma_device_t *device, const uint8_t *sendBuffer,
    uint8_t *receiveBuffer, size_t transferByteCount );

// Returns whether the previous transfer is completed with the EDMA support.
dspi_status_t DSPI_DRV_EdmaMasterGetTransferStatus( uint32_t instance,
    uint32_t *framesTransferred );

// Terminates an asynchronous transfer early with the EDMA support.
dspi_status_t DSPI_DRV_EdmaMasterAbortTransfer( uint32_t instance );

// Interrupt handler for DSPI master mode.
void DSPI_DRV_EdmaMasterIRQHandler( uint32_t instance );

#endif