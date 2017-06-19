// File: OLED_SPI.c

// Definitions of SPI functionalities in the OLED module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "OLED_SPI.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

dspi_edma_master_state_t OLED_SPI_MasterState;
edma_software_tcd_t OLED_SPI_dmaTcd aligned( 32 );
uint32_t OLED_SPI_calculatedBaudRate = 0;

const dspi_edma_device_t OLED_SPI_BusConfig = {
    8000000U,                     // .bitsPerSec
    8U,                           // .dataBusConfig.bitsPerFrame
    kDspiClockPolarity_ActiveLow, // .dataBusConfig.clkPolarity
    kDspiClockPhase_SecondEdge,   // .dataBusConfig.clkPhase
    kDspiMsbFirst                 // .dataBusConfig.direction
};

const dspi_edma_master_user_config_t OLED_SPI_MasterConfig = {
    kDspiCtar0,         // .whichCtar
    false,              // .isSckContinuous
    false,              // .isChipSelectContinuous
    kDspiPcs0,          // .whichPcs
    kDspiPcs_ActiveLow  // .pcsPolarity
};