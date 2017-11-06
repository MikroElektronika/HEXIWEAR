/*

    __QIRCV_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __QIRCV_Driver.h
@brief                         Qi_Receiver Click

@mainpage Qi_Receiver Click
@{

### Click Description ###

The P9025AC is an integrated single-chip, WPC-1.1.2
compliant wireless power receiver with an advanced Foreign
Object Detection (FOD) feature. This device operates with an
AC power signal from a resonant tank and converts it into a
regulated 5.3V output voltage.

@}

@defgroup    QIRCV
@brief       Qi_Receiver Click Driver
@{

| Global Library Prefix | **QIRCV** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Aug 2017.**      |
| Developer             | *Djordje Rosic*       |


### Library Descritption ###

This library contains functions for reading from, and writing to, registers of
Qi receiver click.

@}
*//*--------------------------------------------------------------------------*/
/**
    @example Click_Qi_Receiver_STM.c
    @example Click_Qi_Receiver_TIVA.c
    @example Click_Qi_Receiver_CEC.c
    @example Click_Qi_Receiver_KIN.c
    @example Click_Qi_Receiver_MSP.c
    @example Click_Qi_Receiver_PIC.c
    @example Click_Qi_Receiver_PIC32.c
    @example Click_Qi_Receiver_DSPIC.c
    @example Click_Qi_Receiver_AVR.c
    @example Click_Qi_Receiver_FT90x.c
    @example Click_Qi_Receiver_STM.mbas
    @example Click_Qi_Receiver_TIVA.mbas
    @example Click_Qi_Receiver_CEC.mbas
    @example Click_Qi_Receiver_KIN.mbas
    @example Click_Qi_Receiver_MSP.mbas
    @example Click_Qi_Receiver_PIC.mbas
    @example Click_Qi_Receiver_PIC32.mbas
    @example Click_Qi_Receiver_DSPIC.mbas
    @example Click_Qi_Receiver_AVR.mbas
    @example Click_Qi_Receiver_FT90x.mbas
    @example Click_Qi_Receiver_STM.mpas
    @example Click_Qi_Receiver_TIVA.mpas
    @example Click_Qi_Receiver_CEC.mpas
    @example Click_Qi_Receiver_KIN.mpas
    @example Click_Qi_Receiver_MSP.mpas
    @example Click_Qi_Receiver_PIC.pas
    @example Click_Qi_Receiver_PIC32.pas
    @example Click_Qi_Receiver_DSPIC.pas
    @example Click_Qi_Receiver_AVR.pas
    @example Click_Qi_Receiver_FT90x.pas

*//*--------------------------------------------------------------------------*/

#ifndef _QIRCV_H_
#define _QIRCV_H_

#include <stdint.h>
#include "__QIRCV_Hal.h"

extern uint8_t _QIRCV_STATUS;

extern uint8_t _QIRCV_OK;
extern uint8_t _QIRCV_ERR;

/** @addtogroup QIRCV */
///@{
/**
 * @name                 Qi_Receiver Click Types
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name                 Qi_Receiver Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/* EXAMPLE OF GPIO INTI FUNCTION 
void TEST_GPIOmap( T_TEST_GPIO_Set ctlAN, T_TEST_GPIO_Get ctlRST );
*/

#if QIRCV_SPI_CLICK == 1
/**
 * @brief QIRCV SPI Driver Initialization
 *
 * @param[in] fnWrite   SPI Write Function
 * @param[in] fnRead    SPI Read  Function
 *
 * Initialization of QIRCV SPI driver.
 *
 * @note
 * This function must be called first.
 *
 */
void QIRCV_SPIdriverInit( T_QIRCV_SPI_Write     fnWrite,
                                  T_QIRCV_SPI_Read      fnRead );
#endif
#if QIRCV_I2C_CLICK == 1
/**
 * @brief QIRCV I2C Driver Initialization
 *
 * @param[in] fnStart    I2C Start   Function
 * @param[in] fnStop     I2C Stop    Function
 * @param[in] fnReastart I2C Restart Function
 * @param[in] fnWrite    I2C Write   Function
 * @param[in] fnRead     I2C Read    Function
 *
 * Initialization of QIRCV I2C driver.
 *
 * @note
 * This function must be called first.
 *
 * @note
 * Some compilers don't have all the function pointers, for example
 * mikroE ARM compilers don't have the I2C_Stop function, in that case
 * it is enough to provide NULL pointer.
 */
void QIRCV_I2CdriverInit( T_QIRCV_I2C_Start        fnStart,
                                  T_QIRCV_I2C_Stop         fnStop,
                                  T_QIRCV_I2C_Restart      fnRestart,
                                  T_QIRCV_I2C_Write        fnWrite,
                                  T_QIRCV_I2C_Read         fnRead );
#endif
#if QIRCV_UART_CLICK == 1
/**
 * @brief QIRCV UART Driver Initialization
 *
 * @param[in] fnWrite   UART Write Function
 * @param[in] fnRead    UART Ready Function
 * @param[in] fnReady   UART Data Ready Function
 *
 * Initialization of QIRCV UART driver.
 *
 * @note
 * This function must be called first.
 *
 */
void QIRCV_UARTdriverInit( T_QIRCV_UART_Write   fnWrite,
                                   T_QIRCV_UART_Read    fnRead,
                                   T_QIRCV_UART_Ready   fnReady );
#endif

/**
 * @brief QIRCV Read Voltage
 *
 * @retval VRECT value in Volts.
 *
 * This function returns the voltage at the output of the internal rectifier.
 * This value is higher if the receiver is placed correctly over the
 * transmitter, and can be used to measure power transfer efficiency.
 *
 * @note
 * I2C functions only work if the device is powered on by the transmitter.
 *
 */
float QIRCV_readV ();
/**
 * @brief QIRCV Read Current
 *
 * @retval IOUT value in miliamperes
 *
 * This function returns the output current of the system.
 *
 * @note
 * I2C functions only work if the device is powered on by the transmitter.
 *
 */
float QIRCV_readI ();

/**
 * @brief QIRCV Read Register
 *
 * @param[in] inputAddress    Register to read from
 * @retval Value of the register
 *
 * This function returns the value of the selected register.
 *
 * @note
 * I2C functions only work if the device is powered on by the transmitter.
 *
 */
uint8_t QIRCV_readReg (uint8_t inputAddress);
/**
 * @brief QIRCV Write Register
 *
 * @param[in] inputAddress    Register to write to
 * @param[in] inputData       Data to write
 *
 * This function writes the value to the selected register.
 *
 * @note
 * I2C functions only work if the device is powered on by the transmitter.
 *
 */
void QIRCV_writeReg (uint8_t inputAddress, uint8_t inputData);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __QIRCV_Driver.h

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