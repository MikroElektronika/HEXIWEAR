/* ###################################################################
**     Filename    : Events.c
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

#include "host_mcu_interface.h"
#include "host_mcu_interface_types.h"

#include "HEXIWEAR_defs.h"

#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

/* User includes (#include below this line is not maintained by Processor Expert) */

/*! i2cCom1 IRQ handler */
void I2C1_IRQHandler(void)
{
  I2C_DRV_IRQHandler(FSL_I2CCOM1);
}

/*! i2cCom2 IRQ handler */
void I2C0_IRQHandler(void)
{
  I2C_DRV_IRQHandler(FSL_I2CCOM2);
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
