/**
 * generic SPI driver
 * Project HEXIWEAR, 2015
 */

#include "generic_spi_driver.h"
#include "generic_spi_types.h"
#include "generic_spi_info.h"

#include "OLED_SPI.h"

// number of initialized SPI modules
static uint32_t
  spiNum_ON = 0;

/**
 * [SPI_init description]
 * @param  self [description]
 * @return      [description]
 */
statusSPI_t SPI_Init(
                      genericSpiHandle_t* self
                    )
{
  {
    switch ( self->instance )
    {
      case FSL_OLED_SPI:  {
                            // assign the master structure
                            self->state = OLED_SPI_MasterState;

                            // configure the device info
                            self->device.bitsPerSec                 = OLED_SPI_BusConfig.bitsPerSec;
                            self->device.dataBusConfig.bitsPerFrame = OLED_SPI_BusConfig.dataBusConfig.bitsPerFrame;
                            self->device.dataBusConfig.clkPolarity  = OLED_SPI_BusConfig.dataBusConfig.clkPolarity;
                            self->device.dataBusConfig.clkPhase     = OLED_SPI_BusConfig.dataBusConfig.clkPhase;
                            self->device.dataBusConfig.direction    = OLED_SPI_BusConfig.dataBusConfig.direction;
                            break;
                          }

      default: {}
    }

    // DSPI_DRV_MasterConfigureBus(self->instance, &self->device, &calculatedBaudRate);

    spiNum_ON++;
    return STATUS_SPI_SUCCESS;
  }
}

/**
 * [SPI_deinit description]
 * @param  self [description]
 * @return      [description]
 */
statusSPI_t SPI_Deinit(
                        genericSpiHandle_t* self
                      )
{
  if ( 0 == spiNum_ON )
  {
    return STATUS_SPI_DEINIT_ERROR;
  }

  else
  {
    dspi_status_t
      status = DSPI_DRV_EdmaMasterDeinit(self->instance);

    if ( kStatus_DSPI_Success != status )
    {
      return STATUS_SPI_ERROR;
    }

    else
    {
      spiNum_ON--;
      return STATUS_SPI_SUCCESS;
    }
  }
}
