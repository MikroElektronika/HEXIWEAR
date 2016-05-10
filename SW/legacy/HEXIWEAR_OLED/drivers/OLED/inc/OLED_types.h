/**
 * OLED-related data structures
 * Project HEXIWEAR, 2015
 */

#ifndef HG_OLED_TYPES
#define HG_OLED_TYPES

#include <stdint.h>
#include "generic_spi_types.h"

typedef enum
{
  OLED_TRANSITION_NONE,
  OLED_TRANSITION_TOP_DOWN,
  OLED_TRANSITION_DOWN_TOP,
  OLED_TRANSITION_LEFT_RIGHT,
  OLED_TRANSITION_RIGHT_LEFT

} transition_t;

typedef enum
{
  STATUS_OLED_SUCCESS,        // success
  STATUS_OLED_ERROR,          // fail
  STATUS_OLED_PROTOCOL_ERROR, // SPI failure
  STATUS_OLED_INIT_ERROR,     // initialization error
  STATUS_OLED_DEINIT_ERROR    // deinitialization error

} statusOLED_t;

typedef struct
{
  /**
   * SPI relevant information
   */
  genericSpiHandle_t protocol;

} handleOLED_t;

typedef struct
{
  uint32_t DCpin;
  uint32_t CSpin;
  uint32_t RSTpin;
//  uint32_t RWpin;
  uint32_t ENpin;

} settingsOLED_t;

#endif
