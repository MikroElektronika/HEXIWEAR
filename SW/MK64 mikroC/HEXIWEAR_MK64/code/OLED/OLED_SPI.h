// File: OLED_SPI.h

// Declarations of SPI functionalities in the OLED module.

#ifndef _OLED_SPI_h_
#define _OLED_SPI_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "edma_driver.h"
#include "dspi_edma_master_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// Device instance number
#define FSL_OLED_SPI 2
// OLED_SPI component mode
#define OLED_SPI_DMA_MODE 1U

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Driver state structure.
extern dspi_edma_master_state_t OLED_SPI_MasterState;

// eDMA TCD structure for DMA transfers.
extern edma_software_tcd_t OLED_SPI_dmaTcd aligned( 32 );

// Driver calculated baudrate is returned from DSPI_DRV_MasterInit() call.
extern uint32_t OLED_SPI_calculatedBaudRate;

// Master bus configuration declaration
extern const dspi_edma_device_t OLED_SPI_BusConfig;

// Master configuration declaration
extern const dspi_edma_master_user_config_t OLED_SPI_MasterConfig;

#endif