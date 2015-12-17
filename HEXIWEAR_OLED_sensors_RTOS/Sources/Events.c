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


/* User includes (#include below this line is not maintained by Processor Expert) */

void LLWU_IRQHandler(void)
{
  /* Write your code here. For example clear LLWU wake up flags ... */
}

/*! NFS_I2C IRQ handler */
void I2C0_IRQHandler(void)
{
  I2C_DRV_IRQHandler(FSL_NFS_I2C);
}

/*! FS_I2C IRQ handler */
void I2C1_IRQHandler(void)
{
  I2C_DRV_IRQHandler(FSL_FS_I2C);
}

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

void RTC_IRQHandler(void)
{
  /* Write your code here ... */
  RTC_DRV_AlarmIntAction(FSL_CLOCK);
}

void RTC_Seconds_IRQHandler(void)
{
  /* Write your code here ... */
}

/*! BATTERY_ADC IRQ handler */
void ADC0_IRQHandler(void)
{
  /* Write your code here ... */
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
