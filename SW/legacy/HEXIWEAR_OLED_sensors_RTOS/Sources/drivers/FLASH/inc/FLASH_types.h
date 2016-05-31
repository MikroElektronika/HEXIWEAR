/**
 * FLASH-related data types
 * Project HEXIWEAR, 2015
 */

#ifndef HG_FLASH_TYPES
#define HG_FLASH_TYPES

#include <stdint.h>
#include "generic_spi_types.h"

typedef enum
{
  STATUS_FLASH_SUCCESS,        // success
  STATUS_FLASH_ERROR,          // fail
  STATUS_FLASH_PROTOCOL_ERROR, // SPI failure
  STATUS_FLASH_INIT_ERROR,     // initialization error
  STATUS_FLASH_DEINIT_ERROR    // deinitialization error

} statusFLASH_t;

typedef struct
{
  /**
   * SPI relevant information
   */
  genericSpiHandle_t protocol;

} handleFLASH_t;

typedef struct
{
  uint32_t CSpin;
//  uint32_t HOLDpin;
//  uint32_t Wpin;

} settingsFLASH_t;

#endif
