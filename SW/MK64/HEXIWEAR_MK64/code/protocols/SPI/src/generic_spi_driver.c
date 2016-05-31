/**
 * \file generic_spi_driver.c
 * \version 1.00
 * \brief this file contains generic SPI driver routines
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#include "generic_spi_driver.h"
#include "generic_spi_types.h"
#include "generic_spi_info.h"

#include "OLED_SPI.h"
#include "FLASH_SPI.h"

// number of initialized SPI modules
static uint32_t
  spiNum_ON = 0;

/**
 * initialize SPI interface and its required structures
 * @param  self SPI handle
 * @return      status flag
 */
statusSPI_t SPI_Init( genericSpiHandle_t* self )
{
  {
    switch ( self->instance )
    {
    	case FSL_OLED_SPI:
		{
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

    	case FSL_FLASH_SPI:
    	{
			// assign the master structure
			self->state = FLASH_SPI_MasterState;

			// configure the device info
			self->device.bitsPerSec                 = FLASH_SPI_BusConfig.bitsPerSec;
			self->device.dataBusConfig.bitsPerFrame = FLASH_SPI_BusConfig.dataBusConfig.bitsPerFrame;
			self->device.dataBusConfig.clkPolarity  = FLASH_SPI_BusConfig.dataBusConfig.clkPolarity;
			self->device.dataBusConfig.clkPhase     = FLASH_SPI_BusConfig.dataBusConfig.clkPhase;
			self->device.dataBusConfig.direction    = FLASH_SPI_BusConfig.dataBusConfig.direction;
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
 * deinitialize SPI interface (not used)
 */
statusSPI_t SPI_Deinit( genericSpiHandle_t* self )
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
