/**
 * general routine for catching errors
 * Project HEXIWEAR, 2015
 */

#include "error.h"
#include "HEXIWEAR_driver.h"
#include "flashlight.h"

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
          )
{
  __asm("nop");

  if ( CATCH_MEM_ALLOC == errorCode )
  {
	  __asm("nop");
  }
}

void vApplicationMallocFailedHook()
{
  __asm("nop");
}

void vApplicationStackOverflowHook()
{
  __asm("nop");
}

void UsageFault_Handler()
{
  __asm("nop");
}

void HardFault_Handler()
{
  __asm("nop");
  RED_LED_ON();
  HEXIWEAR_ResetMCU();
}

void MemManage_Handler()
{
  __asm("nop");
}

void DefaultISR()
{
  __asm("nop");
  RED_LED_ON();
  HEXIWEAR_ResetMCU();
}

void BusFault_Handler()
{
  __asm("nop");
  RED_LED_ON();
 HEXIWEAR_ResetMCU();
}

void NMI_Handler()
{
  __asm("nop");
  RED_LED_ON();
  HEXIWEAR_ResetMCU();
}
