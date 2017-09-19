/*

    __SECURE2_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __SECURE2_Driver.c
@addtogroup     SECURE2
@{
------------------------------------------------------------------------------*/
char bufferrrr [40];
#include "__SECURE2_Hal.h"
#include "__SECURE2_Hal.c"
#include "__SECURE2_Driver.h"

/**
 * @name    Secure_2 Click GPIO
 *//*-------------------------------------------------------------------------*/
///@{

extern GPIO_TYPE SECURE2_SOME_PIN;                                        /**< Secure_2 Some Pin */

///@}
/**
 * @name    Secure_2 Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

uint8_t _SECURE2_OK     = 0;                                              /**< NO ERROR */
uint8_t _SECURE2_ERR    = 1;                                              /**< ERROR OCCURED */

///@}
/**
 * @name    Secure_2 Click Registers
 *//*-------------------------------------------------------------------------*/
///@{

uint8_t _SECURE2_STATUS = 0x00;                                           /**< Status Register Address */

///@}
/** @cond PORTING_GUIDE */
/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/*---------------------------------------------------------- PUBLIC FUNCTIONS */

#if SECURE2_SPI_CLICK == 1
void SECURE2_SPIdriverInit( T_SECURE2_SPI_Write     fnWrite,
                                  T_SECURE2_SPI_Read      fnRead )
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
}
#endif
#if SECURE2_I2C_CLICK == 1
void SECURE2_I2CdriverInit( T_SECURE2_I2C_Start     fnStart,
                                  T_SECURE2_I2C_Stop      fnStop,
                                  T_SECURE2_I2C_Restart   fnRestart,
                                  T_SECURE2_I2C_Write     fnWrite,
                                  T_SECURE2_I2C_Read      fnRead )
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}
#endif
#if SECURE2_UART_CLICK == 1
void SECURE2_UARTdriverInit( T_SECURE2_UART_Write   fnWrite,
                                   T_SECURE2_UART_Read    fnRead,
                                   T_SECURE2_UART_Ready   fnReady )
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}
#endif


uint8_t i2c_disable_phys()
{
    return 0x00;
}
uint8_t i2c_enable_phys()
{
    return 0x00;
}
uint8_t i2c_select_device_phys(uint8_t device_id)
{
    return 0x00;
}
uint8_t i2c_send_slave_address(uint8_t readBit)
{
     return 0x00;
}
uint8_t i2c_send_stop()
{
     return 0x00;
}
uint8_t i2c_send_start()
{
      return 0x00;
}

uint8_t i2c_send_bytes(uint8_t count, uint8_t * writeData)
{
     int i;
     for (i = 0; i <20; i++)
      bufferrrr [i] = writeData [i];
     HAL_i2cStart();
     HAL_i2cWrite(0x50, writeData, count, END_MODE_STOP);
     delay_ms (100);
     return 0x00;
}
uint8_t i2c_receive_bytes(uint8_t count, uint8_t * readData)
{
     HAL_i2cStart();
     HAL_i2cRead(0x50, readData, count, END_MODE_STOP);

     return 0x00;
}



/** @endcond */
/** @} */
/*------------------------------------------------------------------------------

  __SECURE2_Driver.c

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