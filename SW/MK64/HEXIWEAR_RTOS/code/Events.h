/**
 * \file Events.h
 * \version 1.00
 * \brief various events' handlers should be placed here, such as interrupts' handlers, etc.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

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

void PORTB_IRQHandler(void);

void test_uart_RxCallback(uint32_t instance, void * uartState);

void test_uart_TxCallback(uint32_t instance, void * uartState);

#ifdef __cplusplus
}   /** extern "C" */
#endif
