/**
 * generic SPI driver
 * Project HEXIWEAR, 2015
 */

#ifndef HG_GENERIC_SPI_DRIVER
#define HG_GENERIC_SPI_DRIVER

#include "generic_spi_types.h"

/**
 * [SPI_init description]
 * @param  self [description]
 * @return      [description]
 */
statusSPI_t SPI_Init(
                      genericSpiHandle_t* self
                    );

/**
 * [SPI_deinit description]
 * @param  self [description]
 * @return      [description]
 */
statusSPI_t SPI_Deinit(
                        genericSpiHandle_t* self
                      );

#endif
