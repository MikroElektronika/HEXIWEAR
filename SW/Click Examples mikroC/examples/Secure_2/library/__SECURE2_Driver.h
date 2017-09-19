/*

    __SECURE2_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __SECURE2_Driver.h
@brief                         Secure_2 Click

@mainpage Secure_2 Click
@{

### Click Description ###

${CLICK_INFO}

@}

@defgroup    SECURE2
@brief       Secure_2 Click Driver
@{

| Global Library Prefix | **SECURE2** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Jul 2017.**      |
| Developer             | *Djordje Rosic*       |


### Library Descritption ###

${LIBRARY_DESCRIPTION}

@}
*//*--------------------------------------------------------------------------*/
/**
    @example Click_Secure_2_STM.c
    @example Click_Secure_2_TIVA.c
    @example Click_Secure_2_CEC.c
    @example Click_Secure_2_KIN.c
    @example Click_Secure_2_MSP.c
    @example Click_Secure_2_PIC.c
    @example Click_Secure_2_PIC32.c
    @example Click_Secure_2_DSPIC.c
    @example Click_Secure_2_AVR.c
    @example Click_Secure_2_FT90x.c
    @example Click_Secure_2_STM.mbas
    @example Click_Secure_2_TIVA.mbas
    @example Click_Secure_2_CEC.mbas
    @example Click_Secure_2_KIN.mbas
    @example Click_Secure_2_MSP.mbas
    @example Click_Secure_2_PIC.mbas
    @example Click_Secure_2_PIC32.mbas
    @example Click_Secure_2_DSPIC.mbas
    @example Click_Secure_2_AVR.mbas
    @example Click_Secure_2_FT90x.mbas
    @example Click_Secure_2_STM.mpas
    @example Click_Secure_2_TIVA.mpas
    @example Click_Secure_2_CEC.mpas
    @example Click_Secure_2_KIN.mpas
    @example Click_Secure_2_MSP.mpas
    @example Click_Secure_2_PIC.pas
    @example Click_Secure_2_PIC32.pas
    @example Click_Secure_2_DSPIC.pas
    @example Click_Secure_2_AVR.pas
    @example Click_Secure_2_FT90x.pas

*//*--------------------------------------------------------------------------*/

#ifndef _SECURE2_H_
#define _SECURE2_H_

#include <stdint.h>
#include "__SECURE2_Hal.h"
#include "aes132_comm_marshaling.h"

extern uint8_t _SECURE2_STATUS;

extern uint8_t _SECURE2_OK;
extern uint8_t _SECURE2_ERR;


/** @addtogroup SECURE2 */
///@{
/**
 * @name                 Secure_2 Click Types
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name                 Secure_2 Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif
#if SECURE2_SPI_CLICK == 1
/**
 * @brief SECURE2 SPI Driver Initialization
 *
 * @param[in] fnWrite   SPI Write Function
 * @param[in] fnRead    SPI Read  Function
 *
 * Initialization of SECURE2 SPI driver.
 *
 * @note
 * This function must be called first.
 *
 */
void SECURE2_SPIdriverInit( T_SECURE2_SPI_Write     fnWrite,
                                  T_SECURE2_SPI_Read      fnRead );
#endif
#if SECURE2_I2C_CLICK == 1
/**
 * @brief SECURE2 I2C Driver Initialization
 *
 * @param[in] fnStart    I2C Start   Function
 * @param[in] fnStop     I2C Stop    Function
 * @param[in] fnReastart I2C Restart Function
 * @param[in] fnWrite    I2C Write   Function
 * @param[in] fnRead     I2C Read    Function
 *
 * Initialization of SECURE2 I2C driver.
 *
 * @note
 * This function must be called first.
 *
 * @note
 * Some compilers don't have all the function pointers, for example
 * mikroE ARM compilers don't have the I2C_Stop function, in that case
 * it is enough to provide NULL pointer.
 */
void SECURE2_I2CdriverInit( T_SECURE2_I2C_Start        fnStart,
                                  T_SECURE2_I2C_Stop         fnStop,
                                  T_SECURE2_I2C_Restart      fnRestart,
                                  T_SECURE2_I2C_Write        fnWrite,
                                  T_SECURE2_I2C_Read         fnRead );
                                  
                                  
                                  
                                  
#endif
#if SECURE2_UART_CLICK == 1
/**
 * @brief SECURE2 UART Driver Initialization
 *
 * @param[in] fnWrite   UART Write Function
 * @param[in] fnRead    UART Ready Function
 * @param[in] fnReady   UART Data Ready Function
 *
 * Initialization of SECURE2 UART driver.
 *
 * @note
 * This function must be called first.
 *
 */
void SECURE2_UARTdriverInit( T_SECURE2_UART_Write   fnWrite,
                                   T_SECURE2_UART_Read    fnRead,
                                   T_SECURE2_UART_Ready   fnReady );
#endif



uint8_t i2c_disable_phys();
uint8_t i2c_enable_phys();
uint8_t i2c_select_device_phys(uint8_t device_id);
uint8_t i2c_send_slave_address(uint8_t readBit);
uint8_t i2c_send_stop();
uint8_t i2c_send_start();
uint8_t i2c_send_bytes(uint8_t count, uint8_t * writeData);
uint8_t i2c_receive_bytes(uint8_t count, uint8_t * readData);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __SECURE2_Driver.h

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