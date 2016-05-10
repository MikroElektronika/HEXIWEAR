/**
 * Power management, related data types
 * Project HEXIWEAR, 2015
 */

#ifndef HG_POWER_TYPES
#define HG_POWER_TYPES

#include <stdint.h>

typedef enum
{
  POWER_OLED,
  POWER_MCU,
  POWER_SENSORS

} periphPOWER_t;

typedef enum
{
  STATUS_POWER_SUCCESS, // success
  STATUS_POWER_ERROR    // fail

} statusPOWER_t;

#endif
