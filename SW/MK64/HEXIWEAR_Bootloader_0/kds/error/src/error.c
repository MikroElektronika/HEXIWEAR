/**
 * catch errors
 */

/**
 * catch unwanted behavior
 */
void catch()
{
  __asm("nop");
}

/**
 * [defaultISR description]
 */
void defaultISR()
{
  catch();
}

void UsageFault_Handler()
{
  __asm("nop");
}

void HardFault_Handler()
{
  __asm("nop");
}

void MemManage_Handler()
{
  __asm("nop");
}

void BusFault_Handler()
{
  __asm("nop");
}

void NMI_Handler()
{
  __asm("nop");
}
