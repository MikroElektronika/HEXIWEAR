/**
 * generic SPI data structures
 * Project HEXIWEAR, 2015
 */

#ifndef HG_GENERIC_SPI_TYPES
#define HG_GENERIC_SPI_TYPES

#include <stdint.h>
#include "generic_spi_info.h"

#include "fsl_dspi_edma_master_driver.h"

typedef struct
{
  /**
   * general SPI information
   */
                  uint32_t instance; // SPI instance
        dspi_edma_device_t device;   // SPI device setting
  dspi_edma_master_state_t state;    // SPI internal state space
                  uint32_t timeout;  // SPI timeout

  /**
   * specific I2C information can go below this
   */

} genericSpiHandle_t;

typedef enum
{
  STATUS_SPI_SUCCESS,     // success
  STATUS_SPI_ERROR,       // fail
  STATUS_SPI_INIT_ERROR,  // initialization error
  STATUS_SPI_DEINIT_ERROR // deinitialization error

} statusSPI_t;

typedef enum
{
  GUI_COLOR_BLACK    = 0x0000,
  GUI_COLOR_BLUE_1   = 0x06FF,
  GUI_COLOR_BLUE     = 0x001F,
  GUI_COLOR_RED      = 0xF800,
  GUI_COLOR_GREEN    = 0x07E0,
  GUI_COLOR_CYAN     = 0x07FF,
  GUI_COLOR_MAGENTA  = 0xF81F,
  GUI_COLOR_YELLOW   = 0xFFE0,
  GUI_COLOR_GRAY     = 0x528A,
  GUI_COLOR_WHITE    = 0xFFFF

} guiColor_t;

#endif
