/*

    __BRUSHLESS_3_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __BRUSHLESS_3_Driver.h
@brief                         Brushless_3 Click

@mainpage Brushless_3 Click
@{

### Click Description ###

${CLICK_INFO}

@}

@defgroup    BRUSHLESS_3
@brief       Brushless_3 Click Driver
@{

| Global Library Prefix | **BRUSHLESS_3** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **jul 2017.**      |
| Developer             | *MikroE Team*       |


### Library Descritption ###

${LIBRARY_DESCRIPTION}

@}
*//*--------------------------------------------------------------------------*/
/**
    @example Click_Brushless_3_STM.c
    @example Click_Brushless_3_TIVA.c
    @example Click_Brushless_3_CEC.c
    @example Click_Brushless_3_KIN.c
    @example Click_Brushless_3_MSP.c
    @example Click_Brushless_3_PIC.c
    @example Click_Brushless_3_PIC32.c
    @example Click_Brushless_3_DSPIC.c
    @example Click_Brushless_3_AVR.c
    @example Click_Brushless_3_FT90x.c
    @example Click_Brushless_3_STM.mbas
    @example Click_Brushless_3_TIVA.mbas
    @example Click_Brushless_3_CEC.mbas
    @example Click_Brushless_3_KIN.mbas
    @example Click_Brushless_3_MSP.mbas
    @example Click_Brushless_3_PIC.mbas
    @example Click_Brushless_3_PIC32.mbas
    @example Click_Brushless_3_DSPIC.mbas
    @example Click_Brushless_3_AVR.mbas
    @example Click_Brushless_3_FT90x.mbas
    @example Click_Brushless_3_STM.mpas
    @example Click_Brushless_3_TIVA.mpas
    @example Click_Brushless_3_CEC.mpas
    @example Click_Brushless_3_KIN.mpas
    @example Click_Brushless_3_MSP.mpas
    @example Click_Brushless_3_PIC.pas
    @example Click_Brushless_3_PIC32.pas
    @example Click_Brushless_3_DSPIC.pas
    @example Click_Brushless_3_AVR.pas
    @example Click_Brushless_3_FT90x.pas

*//*--------------------------------------------------------------------------*/

#ifndef _BRUSHLESS_3_H_
#define _BRUSHLESS_3_H_

#include <stdint.h>
#include "__BRUSHLESS_3_Hal.h"

extern uint8_t _BRUSHLESS_3_STATUS;

extern uint8_t _BRUSHLESS_3_OK;
extern uint8_t _BRUSHLESS_3_ERR;


/** @addtogroup BRUSHLESS_3 */
///@{
/**
 * @name                 Brushless_3 Click Types
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name                 Brushless_3 Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{

int writeParameters(uint8_t *parameters);
int getSpeed(uint16_t *speedValue);
int writeReg(uint8_t regAddr, uint8_t value);
int readReg(uint8_t regAddr, uint8_t *value);



#ifdef __cplusplus
extern "C"{
#endif

/* EXAMPLE OF GPIO INTI FUNCTION 
void TEST_GPIOmap( T_TEST_GPIO_Set ctlAN, T_TEST_GPIO_Get ctlRST );
*/

#if BRUSHLESS_3_SPI_CLICK == 1
/**
 * @brief BRUSHLESS_3 SPI Driver Initialization
 *
 * @param[in] fnWrite   SPI Write Function
 * @param[in] fnRead    SPI Read  Function
 *
 * Initialization of BRUSHLESS_3 SPI driver.
 *
 * @note
 * This function must be called first.
 *
 */
void BRUSHLESS_3_SPIdriverInit( T_BRUSHLESS_3_SPI_Write     fnWrite,
                                  T_BRUSHLESS_3_SPI_Read      fnRead );
#endif
#if BRUSHLESS_3_I2C_CLICK == 1
/**
 * @brief BRUSHLESS_3 I2C Driver Initialization
 *
 * @param[in] fnStart    I2C Start   Function
 * @param[in] fnStop     I2C Stop    Function
 * @param[in] fnReastart I2C Restart Function
 * @param[in] fnWrite    I2C Write   Function
 * @param[in] fnRead     I2C Read    Function
 *
 * Initialization of BRUSHLESS_3 I2C driver.
 *
 * @note
 * This function must be called first.
 *
 * @note
 * Some compilers don't have all the function pointers, for example
 * mikroE ARM compilers don't have the I2C_Stop function, in that case
 * it is enough to provide NULL pointer.
 */
void BRUSHLESS_3_I2CdriverInit( T_BRUSHLESS_3_I2C_Start        fnStart,
                                  T_BRUSHLESS_3_I2C_Stop         fnStop,
                                  T_BRUSHLESS_3_I2C_Restart      fnRestart,
                                  T_BRUSHLESS_3_I2C_Write        fnWrite,
                                  T_BRUSHLESS_3_I2C_Read         fnRead );
#endif
#if BRUSHLESS_3_UART_CLICK == 1
/**
 * @brief BRUSHLESS_3 UART Driver Initialization
 *
 * @param[in] fnWrite   UART Write Function
 * @param[in] fnRead    UART Ready Function
 * @param[in] fnReady   UART Data Ready Function
 *
 * Initialization of BRUSHLESS_3 UART driver.
 *
 * @note
 * This function must be called first.
 *
 */
void BRUSHLESS_3_UARTdriverInit( T_BRUSHLESS_3_UART_Write   fnWrite,
                                   T_BRUSHLESS_3_UART_Read    fnRead,
                                   T_BRUSHLESS_3_UART_Ready   fnReady );
#endif

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __BRUSHLESS_3_Driver.h

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