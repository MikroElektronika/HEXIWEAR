/* ###################################################################
**     Filename    : Events.h
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
#include "CLK_manager.h"
#include "DMA_controller.h"
#include "pin_mux.h"
#include "OLED_SPI.h"
#include "FLASH_SPI.h"
#include "GPIO.h"
#include "KW40_UART.h"
#include "DEBUG_UART.h"
#include "FS_I2C.h"
#include "NFS_I2C.h"
#include "PWR_Manager.h"
#include "HEXI_OS.h"
#include "free_rtos.h"
#include "CLOCK.h"
#include "BATTERY_ADC.h"
#include "sensor_timer.h"
#include "test_uart.h"

#ifdef __cplusplus
extern "C" {
#endif 


void LLWU_IRQHandler(void);

/*! NFS_I2C IRQ handler */
void I2C0_IRQHandler(void);

/*! FS_I2C IRQ handler */
void I2C1_IRQHandler(void);

/*! FLASH_SPI IRQ handler */
void SPI1_IRQHandler(void);

/*! OLED_SPI IRQ handler */
void SPI2_IRQHandler(void);

void RTC_IRQHandler(void);

void RTC_Seconds_IRQHandler(void);

/*! BATTERY_ADC IRQ handler */
void ADC0_IRQHandler(void);

void sensor_timer_OnTimerCompare(void);

void PORTC_IRQHandler(void);

void PORTD_IRQHandler(void);

void GPIO_PORTD_IRQHandler(void);

void PIT0_IRQHandler(void);

void PORTB_IRQHandler(void);

void test_uart_RxCallback(uint32_t instance, void * uartState);

void test_uart_TxCallback(uint32_t instance, void * uartState);

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
