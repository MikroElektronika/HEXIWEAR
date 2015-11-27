/* ###################################################################
**     Filename    : Events.h
**     Project     : sensor_freertos
**     Processor   : MK64FN1M0VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-10-15, 12:52, # CodeGen: 0
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
#include "clockMan1.h"
#include "pin_init.h"
#include "i2cCom2.h"
#include "uartCom2.h"
#include "osa1.h"
#include "free_rtos.h"
#include "i2cCom1.h"
#include "gpio1.h"
#include "uartCom1.h"
#include "dmaController1.h"

#ifdef __cplusplus
extern "C" {
#endif 


/*! i2cCom1 IRQ handler */
void I2C1_IRQHandler(void);

/*! i2cCom2 IRQ handler */
void I2C0_IRQHandler(void);

/*! adConv1 IRQ handler */
void RTC_IRQHandler(void);

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
