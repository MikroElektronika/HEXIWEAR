/**
 * \file Cpu.c
 * \version 01.00
 * \brief this file contains high-level peripherals' initialization routine
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
 * Neither the name of NXP Semiconductor, Inc. nor the names of its
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
 * http: www.nxp.com
 * mail: support@nxp.com
 */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif

/** not implemented */
#if CPU_COMMON_INIT
void Common_Init()
{}
#endif  /** CPU_COMMON_INIT */

#if CPU_COMPONENTS_INIT

/**
 * Initialization of components (with exception for Peripheral
 * Initialization Components which are initialized in
 * Peripherals_Init() method).
 */
void Components_Init()
{
  /*! DMA_controller Auto initialization start */
  EDMA_DRV_Init(&DMA_controller_State,&DMA_controller_InitConfig0);
  /*! DMA_controller Auto initialization end */

  /*! OLED_SPI Auto initialization start */
  DSPI_DRV_EdmaMasterInit(FSL_OLED_SPI, &OLED_SPI_MasterState, &OLED_SPI_MasterConfig, &OLED_SPI_dmaTcd);
  DSPI_DRV_EdmaMasterConfigureBus(FSL_OLED_SPI, &OLED_SPI_BusConfig, &OLED_SPI_calculatedBaudRate);
  /*! OLED_SPI Auto initialization end */

  /*! FLASH_SPI Auto initialization start */
  DSPI_DRV_EdmaMasterInit(FSL_FLASH_SPI, &FLASH_SPI_MasterState, &FLASH_SPI_MasterConfig, &FLASH_SPI_dmaTcd);
  DSPI_DRV_EdmaMasterConfigureBus(FSL_FLASH_SPI, &FLASH_SPI_BusConfig, &FLASH_SPI_calculatedBaudRate);
  /*! FLASH_SPI Auto initialization end */

  /*! GPIO Auto initialization start */
  GPIO_DRV_Init(NULL,NULL);
  /*! GPIO Auto initialization end */

  /*! KW40_UART Auto initialization start */
  UART_DRV_Init(FSL_KW40_UART,&KW40_UART_State,&KW40_UART_InitConfig0);
  /*! KW40_UART Auto initialization end */
  /*! DEBUG_UART Auto initialization start */
  UART_DRV_Init(FSL_DEBUG_UART,&DEBUG_UART_State,&DEBUG_UART_InitConfig0);
  /*! DEBUG_UART Auto initialization end */
  /*! FS_I2C Auto initialization start */
  I2C_DRV_MasterInit(FSL_FS_I2C, &FS_I2C_MasterState);
  I2C_DRV_MasterSetBaudRate(FSL_FS_I2C, &FS_I2C_MasterConfig);
  /*! FS_I2C Auto initialization end */

  /*! NFS_I2C Auto initialization start */
  I2C_DRV_MasterInit(FSL_NFS_I2C, &NFS_I2C_MasterState);
  I2C_DRV_MasterSetBaudRate(FSL_NFS_I2C, &NFS_I2C_MasterConfig);
  /*! NFS_I2C Auto initialization end */

  /*! PWR_Manager Auto initialization start */
//  POWER_SYS_Init(powerConfigsArr, 2U, NULL , 0U);
  INT_SYS_EnableIRQ(LLWU_IRQn);
  /*! PWR_Manager Auto initialization end */
  /*! CLOCK Auto initialization start */
  RTC_DRV_Init(FSL_CLOCK);
  /*! CLOCK Auto initialization end */

  /*! BATTERY_ADC Auto initialization start */
  ADC16_DRV_Init(FSL_BATTERY_ADC, &BATTERY_ADC_InitConfig);
  ADC16_DRV_ConfigConvChn(FSL_BATTERY_ADC, 0U, &BATTERY_ADC_ChnConfig);
  /*! BATTERY_ADC Auto initialization end */

  /*! sensor_timer Auto initialization start */
  LPTMR_DRV_Init(FSL_SENSOR_TIMER,&sensor_timer_State,&sensor_timer_cfg);
  /*! sensor_timer Auto initialization end */
}
#endif  /** CPU_COMPONENTS_INIT */

#ifdef __cplusplus
}
#endif

 /** END Cpu. */

