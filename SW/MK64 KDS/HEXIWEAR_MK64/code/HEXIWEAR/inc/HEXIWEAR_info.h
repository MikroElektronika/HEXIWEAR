/**
 * \file HEXIWEAR_info.h
 * \version 1.00
 * \brief project-specific info and constants
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
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * support: http://www.mikroe.com/forum and https://community.freescale.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "host_mcu_interface.h"
#include "sensor_info.h"
#include "gui_info.h"
#include "GPIO.h"
#include "generic_i2c_info.h"

#define HEXIWEAR_STATE_FLAGS_ADDRESS ( 0xF1000 )
#define HEXIWEAR_FLAGS ( (hexiwear_flags_t*)HEXIWEAR_STATE_FLAGS_ADDRESS )

/** HEXIWEAR firmware version */
#define HEXIWEAR_VERSION_PATCH ( 3 )
#define HEXIWEAR_VERSION_MINOR ( 0 )
#define HEXIWEAR_VERSION_MAJOR ( 1 )

/** uncomment below to enable additional debugging capabilities */
// #define HEXIWEAR_DEBUG

/** global  constants  */
#define UART_TIMEOUT (10)
#define VIBRO_DURATION (50)
#define SEND_PACKETS_VIA_UART_INT

#define VIBRO_ON()  GPIO_DRV_SetPinOutput( VIBRO )
#define VIBRO_OFF() GPIO_DRV_ClearPinOutput( VIBRO )

#if defined( HEXIWEAR_DEBUG )
	#define HEXIWEAR_DEBUG_UART_INSTANCE ( FSL_DEBUG_UART )

	#define SET_PROBE()    GPIO_DRV_SetPinOutput( PROBE )
	#define CLEAR_PROBE()  GPIO_DRV_ClearPinOutput( PROBE )
	#define TOGGLE_PROBE() GPIO_DRV_TogglePinOutput( PROBE )

	#define SET_PROBE2()    GPIO_DRV_SetPinOutput( PROBE2 )
	#define CLEAR_PROBE2()  GPIO_DRV_ClearPinOutput( PROBE2 )
	#define TOGGLE_PROBE2() GPIO_DRV_TogglePinOutput( PROBE2 )
#else
	#define SET_PROBE()
	#define CLEAR_PROBE()
	#define TOGGLE_PROBE()

	#define SET_PROBE2()
	#define CLEAR_PROBE2()
	#define TOGGLE_PROBE2()
#endif

#define HEXIWEAR_EnableExceptions() SCB->SHCSR |= 0x00070000; SCnSCB->ACTLR |= SCnSCB_ACTLR_DISDEFWBUF_Msk
#define HEXIWEAR_Start() OSA_Start()

/** tasks' stack sizes */
#define HEXIWEAR_KW40_INTF_TASK_OK_STACK_SIZE    ( gHostInterfaceOkTaskStackSize_c )
#define HEXIWEAR_KW40_INTF_TASK_Tx_STACK_SIZE    ( gHostInterfaceTxTaskStackSize_c )
#define HEXIWEAR_KW40_INTF_TASK_Rx_STACK_SIZE    ( gHostInterfaceRxTaskStackSize_c )

#define HEXIWEAR_TASK_SENSOR_GET_DATA_STACK_SIZE ( SENSOR_GET_DATA_STACK_SIZE )

#define HEXIWEAR_APP_WATCH_STACK_SIZE            ( WATCH_STACK_SIZE )
#define HEXIWEAR_APP_SENSOR_TAG_STACK_SIZE       ( SENSOR_TAG_STACK_SIZE )
#define HEXIWEAR_STARTUP_STACK_SIZE              ( 0x1000 )

/** tasks' priorities */
#define HEXIWEAR_STARTUP_PRIO ( 1 )
#define HEXIWEAR_KW40_INTF_TASK_OK_PRIO ( gHostInterfaceOkPriority_c )
#define HEXIWEAR_KW40_INTF_TASK_Tx_PRIO ( gHostInterfaceTxPriority_c )
#define HEXIWEAR_KW40_INTF_TASK_Rx_PRIO ( gHostInterfaceRxPriority_c )
#define HEXIWEAR_GUI_PRIO     ( 5 )
#define HEXIWEAR_APP_PRIO     ( 6 )
#define HEXIWEAR_SENSOR_PRIO  ( 7 )
#define HEXIWEAR_USB_TASK     ( USB_PRIO )

#define HEXIWEAR_TASK_SENSOR_TAG_PRIO     ( SENSOR_GET_DATA_PRIO )
#define HEXIWEAR_APP_WATCH_DATA_PRIO      ( WATCH_PRIO )

/** interrupts' IRQ channels */
#define HEXIWEAR_KW40_UART_IRQn   ( UART4_RX_TX_IRQn )

#if defined( HEXIWEAR_DEBUG )
#define HEXIWEAR_DEBUG_UART_IRQn  ( UART3_RX_TX_IRQn )
#endif

#define HEXIWEAR_FS_I2C_IRQn       ( I2C1_IRQn )
#define HEXIWEAR_NFS_I2C_IRQn      ( I2C0_IRQn )

#define HEXIWEAR_OLED_SPI_IRQn     ( SPI2_IRQn )
#define HEXIWEAR_OLED_DMA_RX_IRQn  ( DMA0_IRQn )
#define HEXIWEAR_OLED_DMA_TX_IRQn  ( DMA1_IRQn )

#define HEXIWEAR_FLASH_SPI_IRQn    ( SPI1_IRQn )
#define HEXIWEAR_FLASH_DMA_RX_IRQn ( DMA3_IRQn )
#define HEXIWEAR_FLASH_DMA_TX_IRQn ( DMA4_IRQn )

#define HEXIWEAR_RTC_IRQn ( RTC_IRQn )

#define HEXIWEAR_TIMER_IRQn ( LPTMR0_IRQn )

/**
 * interrupts' priorities for protocols
 */

/** KW40 and debug UART */
#define HEXIWEAR_KW40_UART_IRQ_PRIO  ( 1 )
#if defined( HEXIWEAR_DEBUG )
#define HEXIWEAR_DEBUG_UART_IRQ_PRIO ( 3 )
#endif

/** OLED SPI */
#define HEXIWEAR_OLED_SPI_IRQ_PRIO    ( 4 )
#define HEXIWEAR_OLED_DMA_TX_IRQ_PRIO ( 5 )
#define HEXIWEAR_OLED_DMA_RX_IRQ_PRIO ( 5 )

/** I2C */
#define HEXIWEAR_FS_I2C_IRQ_PRIO      ( 6 )
#define HEXIWEAR_NFS_I2C_IRQ_PRIO     ( 6 )

/** RTC */
#define HEXIWEAR_RTC_IRQ_PRIO     ( 7 )

/** sensor timer */
#define HEXIWEAR_TIMER_IRQ_PRIO   ( 8 )

/** external FLASH SPI */
#define HEXIWEAR_FLASH_SPI_IRQ_PRIO   ( 11 )
#define HEXIWEAR_FLASH_DMA_TX_IRQ_PRIO ( 12 )
#define HEXIWEAR_FLASH_DMA_RX_IRQ_PRIO ( 12 )

/** GPIO */
#define HEXIWEAR_CHG_IRQ_PRIO ( 1 )
#define HEXIWEAR_TAP_IRQ_PRIO ( 2 )

/** helpful macros */
#define TypeMember_Size( type, member )  ( sizeof( ( (type*)0 )->member ) )
#define TypeMember_NumEl( type, member ) ( sizeof( ( (type*)0 )->member ) / sizeof( ( (type*)0 )->member[0] ) )
#define TypeMember_SCALAR                ( 1 )
#define ArraySize( array )               ( sizeof(array) / sizeof(array[0]) )

#define Extract( vector, field )              ( ( vector & field##_MASK ) >> field##_SHIFT )
#define Add( vector, field, valueToOR )       vector =   vector                       | ( valueToOR    << field##_SHIFT )
#define Write( vector, field, valueToWrite )  vector = ( vector & ~( field##_MASK ) ) | ( valueToWrite << field##_SHIFT )
#define WriteZ( vector, field, valueToWrite ) vector = 0; Write( vector, field, valueToWrite )
