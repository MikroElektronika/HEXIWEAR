/**
 * general routine for catching errors
 */

#include <stdint.h>

/**
 * error codes:
 * 1: queue issue
 * 2: I2C-related issue
 * 3: motion data issue
 * 4: semaphore issue
 * 5: task issue
 * 6: sensor issue
 * 7: UART issue
 * 8: SPI issue
 * 9: OLED issue
 * 10: Serial Flash issue
 * 11: initialization issue
 */
void catch(
            uint8_t errorCode
          )
{
  __asm("nop");
//  while(1) {}
}
