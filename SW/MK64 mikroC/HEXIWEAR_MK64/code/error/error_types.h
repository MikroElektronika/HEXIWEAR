// File: error_types.h

// Types of errors for the error module.

#ifndef _error_types_h_
#define _error_types_h_

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
  // initialisation issues
  CATCH_INIT = 0,

  // data categories

  CATCH_MOTION  = 1,
  CATCH_WEATHER = 2,
  CATCH_HEALTH  = 3,

  // RTOS

  CATCH_QUEUE     = 4,
  CATCH_SEMAPHORE = 5,
  CATCH_EVENT           = 16,
  CATCH_TASK      = 6,
  CATCH_SENSOR    = 7,

  // protocols

  CATCH_UART = 8,
  CATCH_I2C  = 9,
  CATCH_SPI  = 10,

  // other modules

  CATCH_OLED  = 11,
  CATCH_FLASH = 12,

  // other structures

  CATCH_MENU  = 13,
  CATCH_POWER = 14,
  CATCH_INTERN_FLASH = 15,

  CATCH_MEM_ALLOC = 16,
  CATCH_MUTEX     = 17,

  // deinitialisation issues

  CATCH_DEINIT = 0xFF

} catch_status_t;

#endif