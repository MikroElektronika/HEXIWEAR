// File: generic_spi_driver.c

// Definitions of main functionalities in the generic SPI module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "generic_spi_driver.h"
#include "generic_spi_types.h"
#include "generic_spi_info.h"

#include "OLED_SPI.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// number of initialized SPI modules
static uint32_t spiNum_ON = 0;

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initializes SPI interface and its required structures.
statusSPI_t SPI_Init( genericSpiHandle_t* self )
{
    switch( self->instance )
    {
        case FSL_OLED_SPI:
        {
            // assign the master structure
            self->state = OLED_SPI_MasterState;

            // configure the device info
            self->device.bitsPerSec                 
                = OLED_SPI_BusConfig.bitsPerSec;
            self->device.dataBusConfig.bitsPerFrame 
                = OLED_SPI_BusConfig.dataBusConfig.bitsPerFrame;
            self->device.dataBusConfig.clkPolarity  
                = OLED_SPI_BusConfig.dataBusConfig.clkPolarity;
            self->device.dataBusConfig.clkPhase     
                = OLED_SPI_BusConfig.dataBusConfig.clkPhase;
            self->device.dataBusConfig.direction    
                = OLED_SPI_BusConfig.dataBusConfig.direction;
            break;
        }

//        case FSL_FLASH_SPI:
//        {
            // assign the master structure
//            self->state = FLASH_SPI_MasterState;
//
            // configure the device info
//            self->device.bitsPerSec
//                = FLASH_SPI_BusConfig.bitsPerSec;
//            self->device.dataBusConfig.bitsPerFrame
//                = FLASH_SPI_BusConfig.dataBusConfig.bitsPerFrame;
//            self->device.dataBusConfig.clkPolarity
//                = FLASH_SPI_BusConfig.dataBusConfig.clkPolarity;
//            self->device.dataBusConfig.clkPhase
//                = FLASH_SPI_BusConfig.dataBusConfig.clkPhase;
//            self->device.dataBusConfig.direction
//                = FLASH_SPI_BusConfig.dataBusConfig.direction;
//            break;
//        }

            default: {}
    }

    // DSPI_DRV_MasterConfigureBus(
    //     self->instance, &self->device, &calculatedBaudRate );

    spiNum_ON++;
    return STATUS_SPI_SUCCESS;
}

// Deinitializes SPI interface (not used).
statusSPI_t SPI_Deinit( genericSpiHandle_t* self )
{
    dspi_status_t status;

    if( spiNum_ON == 0 )
    {
        return STATUS_SPI_DEINIT_ERROR;
    }

    status = DSPI_DRV_EdmaMasterDeinit( self->instance );

    if( status != kStatus_DSPI_Success )
    {
        return STATUS_SPI_ERROR;
    }

    spiNum_ON--;
    return STATUS_SPI_SUCCESS;
}