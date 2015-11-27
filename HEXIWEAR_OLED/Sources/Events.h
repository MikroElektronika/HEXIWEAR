/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "fsl_device_registers.h"
#include "clkManager.h"
#include "pin_mux.h"
#include "osa1.h"
#include "OLED_SPI.h"
#include "FLASH_SPI.h"
#include "dmaController1.h"
#include "GPIO.h"
#include "PWR_Manager.h"

#ifdef __cplusplus
extern "C" {
#endif 


/*! FLASH_SPI IRQ handler */
void SPI1_IRQHandler(void);

/*! OLED_SPI IRQ handler */
void SPI2_IRQHandler(void);

void LLWU_IRQHandler(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
