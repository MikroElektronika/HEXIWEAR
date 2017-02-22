/**
 * general routine for catching errors
 */

#ifndef HG_ERROR
#define HG_ERROR

#include <stdint.h>
#include "error_types.h"

/**
 * catch common errors
 * @param errorCode code which signifies the origin of the error:
 * 0:  initialization issue
 *
 * 1:  MOTION data issue
 * 2:  WEATHER data issue
 * 3:  HEALTH data issue
 *
 * 4:  queue issue
 * 5:  semaphore issue
 * 6:  task issue
 *
 * 7:  sensor issue
 *
 * 8:  UART issue
 * 9:  I2C issue
 * 10: SPI issue
 *
 * 11: OLED issue
 * 12: FLASH issue
 */
void catch(
            uint8_t errorCode
          );

#endif
