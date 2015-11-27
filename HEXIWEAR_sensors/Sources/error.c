/**
 * general routine for catching errors
 */

#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"

/**
 * general sensor issue: 0
 *
 * rtos issues:
 * -------------
 * 1: stack issue
 * 2: queue issue
 * 3: init issue
 * 4: n/a
 * 5: n/a
 *
 * specific sensor issues:
 * ---------------
 * 6 :  FXOS issue
 * 7 :  FXAS issue
 * 8 :   MPL issue
 * 9 :   HTU issue
 * 10:   TSL issue
 * 11: MAXIM issue
 */
void catch(
            uint8_t errorCode
          )
{
  __asm("nop");
//  while(1) {}
}