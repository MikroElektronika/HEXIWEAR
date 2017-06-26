/*

    __RS485_2_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
 * @file    __RS485_2_Driver.h
 * @brief   RS485 2 click
 *
 * @defgroup  RS485_2 RS485 2 click driver
 * @brief     RS485 2 click Driver
 *
 * Global Library Prefix : **RS485_2**
 *
 * @mainpage RS485 2 Click
 *
 * @{
 *
 * ![RS485_2](../../RS485_2_Click.png)
 *
 * ### Device Description ###
 *
 * The MAX3471 half-duplex transceiver is intended for lithium battery-powered 
 * RS-485/RS-422 applications. It draws only 1.6µA (typical) supply current from
 * a 3.6V supply with the receiver enabled and the driver disabled. Its wide 
 * 2.5V to 5.5V supply voltage guarantees operation over the lifetime of a 
 * lithium battery.
 *
 *
 * ### Features ###
 *
 * - 1.6µA Supply Current with Receiver Enabled
 * - +2.5V to +5.5V Single-Supply Operation
 * - True Fail-Safe Receiver Input
 * - Available in µMAX Package
 * - 1/8-Unit-Load Receiver Input
 * - -7V to +10V Common-Mode Input Voltage Range
 * 
 * @}
 *
 * @example RS485_2_Click_ARM_STM.c
 * @example RS485_2_Click_ARM_TIVA.c
 * @example RS485_2_Click_ARM_CEC.c
 * @example RS485_2_Click_ARM_KIN.c
 * @example RS485_2_Click_ARM_MSP.c
 * @example RS485_2_Click_PIC.c
 * @example RS485_2_Click_PIC32.c
 * @example RS485_2_Click_DSPIC.c
 * @example RS485_2_Click_AVR.c
 * @example RS485_2_Click_FTDI.c
 * @example RS485_2_Click_ARM_STM.mbas
 * @example RS485_2_Click_ARM_TIVA.mbas
 * @example RS485_2_Click_ARM_CEC.mbas
 * @example RS485_2_Click_ARM_KIN.mbas
 * @example RS485_2_Click_ARM_MSP.mbas
 * @example RS485_2_Click_PIC.mbas
 * @example RS485_2_Click_PIC32.mbas
 * @example RS485_2_Click_DSPIC.mbas
 * @example RS485_2_Click_AVR.mbas
 * @example RS485_2_Click_FTDI.mbas
 * @example RS485_2_Click_ARM_STM.mpas
 * @example RS485_2_Click_ARM_TIVA.mpas
 * @example RS485_2_Click_ARM_CEC.mpas
 * @example RS485_2_Click_ARM_KIN.mpas
 * @example RS485_2_Click_ARM_MSP.mpas
 * @example RS485_2_Click_PIC.pas
 * @example RS485_2_Click_PIC32.pas
 * @example RS485_2_Click_DSPIC.pas
 * @example RS485_2_Click_AVR.pas
 * @example RS485_2_Click_FTDI.pas
 *
 ******************************************************************************/

#ifndef _RS485_2_H_
#define _RS485_2_H_

#include <stdint.h>

/*-------------------------- HAL POINTERS ------------------------------------*/

#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )
typedef void ( *T_RS485_2_UART_Write )(unsigned int data_out);
typedef unsigned int ( *T_RS485_2_UART_Tx_Idle )( void );

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )    || \
      defined( __MIKROC_PRO_FOR_FT90x__ )
typedef void ( *T_RS485_2_UART_Write )(unsigned char data_out);
typedef char ( *T_RS485_2_UART_Tx_Idle )( void );

#else
typedef void ( *T_RS485_2_UART_Write )(unsigned char data_out);
typedef char ( *T_RS485_2_UART_Tx_Idle )( void );
#endif

/*----------------------------------------------------------------------------*/

/**
 * @name                 RS485 2 Click Registers
 ******************************************************************************/
///@{

///@}

/**
 * @name                 RS485 2 Click Return Values
 ******************************************************************************/
///@{

#define _RS485_2_OK (0)
#define _RS485_2_ERR (-1)

///@}

/**
 * @name                 RS485 2 Click Types
 ******************************************************************************/
///@{


///@}
/**
 * @name                 RS485 2 Click Driver Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief RS485 2 Click Driver Initialization.
 *
 * @param fpWrite UART write function pointer.
 * @param fpIdle The function to test if the transmit register is empty.
 *
 * Initialization of RS485 2 Click driver.
 *
 * @note
 * This function must be called first.
 *
 */
void RS485_2_driverInit(
    T_RS485_2_UART_Write fpWrite, 
    T_RS485_2_UART_Tx_Idle fpIdle
);

/**
 * @brief RS485 2 Click transmit.
 *
 * @param pData Data to transmit.
 * @param size Size of data in bytes to transmit.
 *
 * The function enables driver output and disables receiver output, in order to
 * transmit data over RS-485 bus. After transmition is done, driver output is
 * disabled and receiver output is enabled in order to be able to receive data.
 *
 */
void RS485_2_transmit(uint8_t *pData, uint32_t size);


#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __RS485_2_Click_Driver.h

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

    This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

------------------------------------------------------------------------------*/