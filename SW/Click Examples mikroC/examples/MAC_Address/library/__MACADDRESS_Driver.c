/*

    __MACADDRESS_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file         __MACADDRESS_Driver.c
@brief          MACADDRESS Driver Source
@addtogroup     MACADDRESS
@{

*/
/* -------------------------------------------------------------------------- */

#include "__MACADDRESS_Hal.h"
#include "__MACADDRESS_Hal.c"
#include "__MACADDRESS_Driver.h"

#define _MACADDRESS_END_ADDR    0x7F                                            /**< End R/W Zone Address */
#define _MACADDRESS_MAC_ADDR    0xFA                                            /**< Node Address Location */ 

static uint8_t _slaveAddress;

/** @name                                     MAC_Address Click Return Values
 *  @{                                  *///------------------------------------

const uint8_t _MACADDRESS_OK         = 0;                                       /**< No Error */
const uint8_t _MACADDRESS_PAR_ERR    = 1;                                       /**< Parameter Error */
const uint8_t _MACADDRESS_COM_ERR    = 2;                                       /**< Communication Error */   

/// @}
/* --------------------------------------------------------- PUBLIC FUNCTIONS */

void MACADDRESS_init(uint8_t slaveAddress)
{
    _slaveAddress = slaveAddress;
}

T_MACADDRESS_ret 
MACADDRESS_readMAC(uint8_t *mac)
{
    uint8_t macAddress = _MACADDRESS_MAC_ADDR;
    uint8_t res        = 0;

    res |= hal_i2cStart();
    res |= hal_i2cWrite( _slaveAddress, &macAddress, 1, END_MODE_RESTART );
    res |= hal_i2cRead( _slaveAddress, mac, 6, END_MODE_STOP );

    return ( res > 0 ) ? _MACADDRESS_COM_ERR : _MACADDRESS_OK;
}

T_MACADDRESS_ret 
MACADDRESS_writeByte(uint8_t address, uint8_t data_)
{       
    uint8_t tmp[ 2 ];
    uint8_t res = 0;

    if( address > _MACADDRESS_END_ADDR )
    {
        return _MACADDRESS_PAR_ERR;
    }
    else
    {
        tmp[0] = address;
        tmp[1] = data_;
        
        res |= hal_i2cStart();
        res |= hal_i2cWrite( _slaveAddress, tmp, 2, END_MODE_STOP );
        Delay_ms( 5 );
    }
    return ( res > 0 ) ? _MACADDRESS_COM_ERR : _MACADDRESS_OK;
}

T_MACADDRESS_ret 
MACADDRESS_readByte(uint8_t address, uint8_t *data_)
{
    uint8_t res = 0;

    if( address > _MACADDRESS_END_ADDR )
    {
        return _MACADDRESS_PAR_ERR;
    }
    else
    {
        res |= hal_i2cStart();
        res |= hal_i2cWrite( _slaveAddress, &address, 1, END_MODE_RESTART );
        res |= hal_i2cRead( _slaveAddress, data_, 1, END_MODE_STOP );
    }
    return ( res > 0 ) ? _MACADDRESS_COM_ERR : _MACADDRESS_OK;
}

T_MACADDRESS_ret 
MACADDRESS_writeMulti(uint8_t address, uint8_t *buffer, int8_t nBytes)
{
    uint8_t tmp[ 9 ];
    uint8_t repeat;
    uint8_t counter = 0;
    uint8_t res     = 0;

    if( address + nBytes > _MACADDRESS_END_ADDR )
    {
        return _MACADDRESS_PAR_ERR;
    }
    else
    {
        repeat = nBytes / 8;

        while( repeat-- )
        {
            tmp[ 0 ] = address + ( 8 * counter );
            memcpy( tmp + 1, buffer + (8 * counter), 8 );
            res |= hal_i2cStart();
            res |= hal_i2cWrite( _slaveAddress, tmp, 9, END_MODE_STOP );
            Delay_ms( 5 );  
            counter++;
        }

        if( repeat = nBytes % 8 )
        {
            tmp[ 0 ] = address + ( 8 * counter );
            memcpy( tmp + 1, buffer + (8 * counter), 8 );
            res |= hal_i2cStart();
            res |= hal_i2cWrite( _slaveAddress, tmp, repeat + 1, END_MODE_STOP );
            Delay_ms( 5 );
        }
    }
    return ( res > 0 ) ? _MACADDRESS_COM_ERR : _MACADDRESS_OK;
}

T_MACADDRESS_ret 
MACADDRESS_readMulti(uint8_t address, uint8_t *buffer, int8_t nBytes)
{
    uint8_t res = 0;
    
    if( address > _MACADDRESS_END_ADDR )
    {
        return _MACADDRESS_PAR_ERR;
    }
    else
    {
        res |= hal_i2cStart();
        res |= hal_i2cWrite( _slaveAddress, &address, 1, END_MODE_RESTART );
        res |= hal_i2cRead( _slaveAddress, buffer, nBytes, END_MODE_STOP );
    }
    return ( res > 0 ) ? _MACADDRESS_COM_ERR : _MACADDRESS_OK;
}

/* ----------------------------------------------------- HAL PUBLIC FUNCTIONS */

#ifdef __MACADDRESS_GPIO
void 
HAL_MACADDRESS_gpioInit
( 
        T_MACADDRESS_GPIO_Set      ctlAN, 
        T_MACADDRESS_GPIO_Get      ctlRST 
)
{
    fpAN   = ctlAN;      // Just an example
    fpRST  = ctlRST;     // Just an example
}
#endif
#ifdef __MACADDRESS_SPI
void 
HAL_MACADDRESS_spiInit
( 
        T_MACADDRESS_SPI_Write     fnWrite,
        T_MACADDRESS_SPI_Read      fnRead 
)
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
}
#endif
#ifdef __MACADDRESS_I2C
void 
HAL_MACADDRESS_i2cInit
( 
        T_MACADDRESS_I2C_Start     fnStart,
        T_MACADDRESS_I2C_Stop      fnStop,
        T_MACADDRESS_I2C_Restart   fnRestart,
        T_MACADDRESS_I2C_Write     fnWrite,
        T_MACADDRESS_I2C_Read      fnRead 
)
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}
#endif
#ifdef __MACADDRESS_UART
void 
HAL_MACADDRESS_uartInit
( 
        T_MACADDRESS_UART_Write   fnWrite,
        T_MACADDRESS_UART_Read    fnRead,
        T_MACADDRESS_UART_Ready   fnReady 
)
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}
#endif

/// @}
/* -------------------------------------------------------------------------- */
/*
  __MACADDRESS_Driver.c

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

----------------------------------------------------------------------------- */