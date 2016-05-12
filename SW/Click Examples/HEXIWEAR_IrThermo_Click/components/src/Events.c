/* ###################################################################
**     Filename    : Events.c
**     Project     : HEXIWEAR_OLED_sensors_RTOS
**     Processor   : MK64FN1M0VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-12-03, 12:23, # CodeGen: 0
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

void I2C0_IRQHandler(void)
{
  I2C_DRV_IRQHandler(FSL_FS_I2C);
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
