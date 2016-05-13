/**
 * common error types
 * Project HEXIWEAR, 2015
 */

#ifndef HG_ERROR_TYPES
#define HG_ERROR_TYPES

typedef enum
{
  /**
   * initialization issues
   */

  CATCH_INIT = 0,

  /**
   * data categories
   */

  CATCH_MOTION  = 1,
  CATCH_WEATHER = 2,
  CATCH_HEALTH  = 3,

  /**
   * RTOS
   */

  CATCH_QUEUE     = 4,
  CATCH_SEMAPHORE = 5,
  CATCH_EVENT 	  = 16,
  CATCH_TASK      = 6,
  CATCH_SENSOR    = 7,

  /**
   * protocols
   */

  CATCH_UART = 8,
  CATCH_I2C  = 9,
  CATCH_SPI  = 10,

  /**
   * other modules
   */

  CATCH_OLED  = 11,
  CATCH_FLASH = 12,

  /**
   * other structures
   */

  CATCH_MENU  = 13,
  CATCH_POWER = 14,
  CATCH_INTERN_FLASH = 15,

  CATCH_MEM_ALLOC = 16,
  CATCH_MUTEX     = 17,

  /**
   * deinitialization issues
   */

  CATCH_DEINIT = 0xFF

} catch_status_t;

#endif
