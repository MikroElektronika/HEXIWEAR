/* ###################################################################
**     Filename    : Events.c
**     Project     : OLED_bm
**     Processor   : MK64FN1M0VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-11-24, 19:40, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*! FLASH_SPI IRQ handler */
void SPI1_IRQHandler(void)
{
#if FLASH_SPI_DMA_MODE
  DSPI_DRV_EdmaIRQHandler(FSL_FLASH_SPI);
#else
  DSPI_DRV_IRQHandler(FSL_FLASH_SPI);
#endif
  /* Write your code here ... */
}

/*! OLED_SPI IRQ handler */
void SPI2_IRQHandler(void)
{
#if OLED_SPI_DMA_MODE
  DSPI_DRV_EdmaIRQHandler(FSL_OLED_SPI);
#else
  DSPI_DRV_IRQHandler(FSL_OLED_SPI);
#endif
  /* Write your code here ... */
}

void LLWU_IRQHandler(void)
{
  /* Write your code here. For example clear LLWU wake up flags ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
