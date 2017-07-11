/*

    __FAN2_Hal.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __FAN2_Hal.c
@addtogroup     FAN2_HAL
@{
*/
#include "stdint.h"
#include "__FAN2_Hal.h"

#ifdef PLD_SPI_CLICK
/*----------------------------------------------------------------- SPI TYPES */

static T_FAN2_SPI_Write        fpWriteSPI;
static T_FAN2_SPI_Read         fpReadSPI;

static void HAL_spiWrite(uint8_t *pBuf, uint16_t nBytes);
static void HAL_spiRead(uint8_t *pBuf, uint16_t nBytes);
static void HAL_spiTransfer(uint8_t *pIn, uint8_t *pOut, uint16_t nBytes);
#endif
#ifdef PLD_I2C_CLICK
/*----------------------------------------------------------------- I2C TYPES */

static T_FAN2_I2C_Start        fpStartI2C;
static T_FAN2_I2C_Stop         fpStopI2C;
static T_FAN2_I2C_Restart      fpRestartI2C;
static T_FAN2_I2C_Write        fpWriteI2C;
static T_FAN2_I2C_Read         fpReadI2C;

static int HAL_i2cStartWrite(uint8_t slaveAddress);
static int HAL_i2cWrite(uint8_t slaveAddress, uint8_t *pBuf, uint16_t nBytes, uint8_t endMode);
static int HAL_i2cStartRead(uint8_t slaveAddress);
static int HAL_i2cRead(uint8_t slaveAddress, uint8_t *pBuf, uint16_t nBytes, uint8_t endMode);
#endif
#ifdef PLD_UART_CLICK
/*---------------------------------------------------------------- UART TYPES */

static T_FAN2_UART_Write       fpWriteUART;
static T_FAN2_UART_Read        fpReadUART;
static T_FAN2_UART_Ready       fpReadyUART;

static void HAL_uartWrite(uint8_t input);
static uint8_t HAL_uartReady(void);
static uint8_t HAL_uartReady(void);

#endif

/** @cond PORTING_GUIDE */
#ifdef PLD_SPI_CLICK
/*------------------------------------------------------------------- SPI HAL */

/**
    @brief HAL_spiWrite

    @param[in] pBuf             pointer to data buffer
    @param[in] nBytes           number of bytes for writing

#### SPI Write Function #####

    @todo: PORTING

- USE fpWriteSPI - function provided on driverInit call

Function should execute write sequence of n bytes.

@note
This function should not use CS pin.
*/
static void HAL_spiWrite(uint8_t *pBuf, uint16_t nBytes)
{
    uint8_t *ptr = pBuf;

    while( nBytes-- )
        fpWriteSPI( *( ptr++ ) );
}

/**
    @brief HAL_spiRead

    @param[out] pBuf             pointer to data buffer
    @param[in] nBytes           number of bytes for writing

#### SPI Read Function #####

    @todo: PORTING

- USE fpReadSPI - function provided on driverInit call

Function should execute write sequence of n bytes.

@note
This function should not use CS pin.
*/
static void HAL_spiRead(uint8_t *pBuf, uint16_t nBytes)
{
    uint8_t *ptr = pBuf;

    while( nBytes-- )
        *( ptr++ ) = fpReadSPI( 0x00 );
}

/**
    @brief HAL_spiTransfer

    @param[in] pIn              pointer to write data buffer
    @param[out] pOut            pointer to read data buffer
    @param[in] nBytes           number of bytes for writing

#### SPI Transfer Function #####

    @todo: PORTING

- USE fpReadSPI - function provided on driverInit call

Function should execute write sequence of n bytes.

@note
This function should not use CS pin.
*/
static void HAL_spiTransfer(uint8_t *pIn, uint8_t *pOut, uint16_t nBytes)
{
    uint8_t *in = pIn;
    uint8_t *out = pOut;

    while( nBytes-- )
        *( out++ ) = fpReadSPI( *( in++ ) );
}
#endif
#ifdef PLD_I2C_CLICK
/*------------------------------------------------------------------- I2C HAL */

#ifndef __MIKROC_PRO_FOR_ARM__
#define END_MODE_STOP        0
#define END_MODE_RESTART     1
#define END_MODE_NO          2
#endif

#ifdef __MIKROC_PRO_FOR_ARM__
#ifndef __MSP__
#ifdef __TI__

#define END_MODE_STOP        0
#define END_MODE_RESTART     1
#define END_MODE_NO          2
static uint8_t startF        = 0;
#endif
#endif

#ifdef __MSP__
static uint8_t startF        = 0;
#endif

#endif

#ifdef __MIKROC_PRO_FOR_FT90x__
static uint8_t startF        = 0;
#endif

#if defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )
#define READ_BIT                1
#define WRITE_BIT               0

static uint8_t NACK_BIT         = 0x01;
static uint8_t ACK_BIT          = 0x00;
#elif defined( __MIKROC_PRO_FOR_PIC__ ) || \
      defined( __MIKROC_PRO_FOR_AVR__ )

#define READ_BIT                1
#define WRITE_BIT               0

static uint8_t NACK_BIT         = 0x00;
static uint8_t ACK_BIT          = 0x01;
#endif

/**
    @brief HAL_i2cStart

    @return    0                No Error

#### I2C Start Write Function #####

    @todo: PORTING

- USE fpStartI2C - function provided on driverInit call

Function should execute start condition on I2C BUS.

@note
This function alongisde with HAL_i2cWrite or HAL_i2cRead represents the whole 
I2C master write/read sequence. Keep on mind that during the implementation.
*/
static int HAL_i2cStart()
{
    int res = 0;

#if defined(__MIKROC_PRO_FOR_ARM__)

    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

    res |= fpStartI2C();

    #elif defined( __TI__ )

    startF = 1;

    #endif
#elif defined( __MIKROC_PRO_FOR_FT90x__ )

    startF = 1;

#elif defined( __MIKROC_PRO_FOR_AVR__ )

    res |= fpStartI2C();

#elif defined( __MIKROC_PRO_FOR_DSPIC__ ) || defined( __MIKROC_PRO_FOR_PIC32__ ) || defined( __MIKROC_PRO_FOR_PIC__ )

    res |= fpStartI2C();

#elif defined( PLD_EXT_TOOLCHAIN )

// ...

#endif
    return res;
}

/**
    @brief HAL_i2cWrite

    @param[in] slaveAddress     7 bit slave addres without 0 bit (read/write bit)
    @param[in] pBuf             pointer to data buffer
    @param[in] nBytes           number of bytes for writing
    @param[in] endMode          END_MODE_STOP / END_MODE_RESTART
    @return    0                No Error

#### I2C Write Function ####

    @todo PORTING

- USE fpWriteI2C - function provided on driverInit call
- USE fpStopI2C - function provided on driverInit call
- USE fpRestartI2C - function provided on driverInit call

Function should execute write referenced ```pBuf``` and execute "end" or
"restart" depend on ```endMode argument.

@note
This function alongisde with HAL_i2cStartWrite represents the whole I2C master
write sequence. Keep on mind that during the implementation.
 */
static int HAL_i2cWrite(uint8_t slaveAddress, uint8_t *pBuf, uint16_t nBytes, uint8_t endMode)
{
    int res = 0;
    uint8_t *ptr = pBuf;

#if defined(__MIKROC_PRO_FOR_ARM__)

    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

    res |= fpWriteI2C(slaveAddress, ptr, nBytes, endMode);

    #elif defined( __MSP__ )

    res |= fpWriteI2C(slaveAddress, ptr, nBytes, endMode);

    #elif defined( __TI__ )

    if( startF )
    {
        fpStartI2C(slaveAddress, _I2C_DIR_MASTER_TRANSMIT);
        Delay_1ms();
        startF = 0;
    }

    if(nBytes == 1)
    {
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_SINGLE_SEND );
        Delay_1ms();
    }
    else if(nBytes == 2)
    {
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        Delay_1ms();
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    }
    else
    {
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        Delay_1ms();
        while(--nBytes > 1)
            res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_CONT );
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    }
    
    if( endMode = END_MODE_RESTART )
    {
        startF = 1;
    }
    #endif

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

    if( startF )
    {
        fpStartI2C(slaveAddress);
        startF = 0;
    }
    res |= fpWriteI2C(ptr, nBytes);
    if( endMode = END_MODE_RESTART )
    {
        startF = 1;
    }

#elif defined( __MIKROC_PRO_FOR_AVR__ )

    fpWriteI2C( (slaveAddress << 1) | WRITE_BIT );
    while(nBytes--)
        fpWriteI2C(*( ptr++ ));
    if( endMode == END_MODE_STOP )
        fpStopI2C();
    if( endMode == END_MODE_RESTART )
        fpRestartI2C();

#elif defined( __MIKROC_PRO_FOR_DSPIC__ ) || defined( __MIKROC_PRO_FOR_PIC32__ ) || defined( __MIKROC_PRO_FOR_PIC__ )

    res |= fpWriteI2C( (slaveAddress << 1) | WRITE_BIT );
    while(nBytes--)
        res |= fpWriteI2C(*( ptr++ ));
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpStartI2C();

#elif defined( PLD_EXT_TOOLCHAIN )

// ...

#endif
    return res;
}



/**
    @brief HAL_i2cRead

    @param[in] slaveAddress     7 bit slave addres without 0 bit (read/write bit)
    @param[out] pBuf            pointer to data buffer
    @param[in] nBytes           number of bytes to read
    @param[in] endMode          END_MODE_STOP / END_MODE_RESTART
    @return    0                No Error

#### I2C Read Function ####

    @todo PORTING

- USE fpReadI2C - function provided on driverInit call
- USE fpStopI2C - function provided on driverInit call
- USE fpRestartI2C - function provided on driverInit call

Function should execute write referenced ```pBuf``` and execute "end" or
"restart" depend on ```endMode argument.

@note
This function alongisde with HAL_i2cStartRead represents the whole I2C master
read sequence. Keep on mind that during the implementation.
 */
static int HAL_i2cRead(uint8_t slaveAddress, uint8_t *pBuf, uint16_t nBytes, uint8_t endMode)
{
    int res = 0;
    uint8_t *ptr = pBuf;

#if defined( __MIKROC_PRO_FOR_ARM__ )

    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

    fpReadI2C(slaveAddress, ptr, nBytes, endMode);

    #elif defined( __MSP__ )

    fpReadI2C(slaveAddress, ptr, nBytes, endMode);

    #elif defined( __TI__ )

    if( startF )
    {
        fpStartI2C(slaveAddress, _I2C_DIR_MASTER_RECEIVE);
        Delay_1ms();
        startF = 0;
    }

    if(nBytes == 1)
    {
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_SINGLE_RECEIVE);
        Delay_1ms();
    }
    else if(nBytes == 2)
    {
        res |= fpReadI2C(ptr++, _I2C_MASTER_MODE_BURST_RECEIVE_START);
        Delay_1ms();
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
    }
    else
    {
        res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_RECEIVE_START);
        Delay_1ms();
        while(--nBytes > 1)
        {
            res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_RECEIVE_CONT);
            Delay_1ms();
        }
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
    }
    if( endMode = END_MODE_RESTART )
    {
        startF = 1;
    }
    #endif

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

    if( startF )
    {
        fpStartI2C(slaveAddress);
        startF = 0;
    }
    res |= fpReadI2C(ptr, nBytes);
    if( endMode = END_MODE_RESTART )
    {
        startF = 1;
    }


#elif defined( __MIKROC_PRO_FOR_AVR__ )

    fpWriteI2C((slaveAddress << 1) | READ_BIT);
    while(--nBytes) *ptr++ =
        fpReadI2C(ACK_BIT);
    *ptr = fpReadI2C(NACK_BIT);
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpStartI2C();

#elif defined( __MIKROC_PRO_FOR_8051__ ) || defined( __MIKROC_PRO_FOR_PIC__ ) || defined( __MIKROC_PRO_FOR_DSPIC__ )

    res |= fpWriteI2C((slaveAddress << 1) | READ_BIT);
    while(--nBytes)
        *ptr++ = fpReadI2C(ACK_BIT);
    *ptr = fpReadI2C(NACK_BIT);
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpRestartI2C();

#elif defined( PLD_EXT_TOOLCHAIN )

// ...

#endif
    return res;
}
#endif
#ifdef PLD_UART_CLICK
/*------------------------------------------------------------------ UART HAL */

/**
    @brief HAL_uartWrite

    @param[in] input    tx data byte

#### UART Write Function #####

    @todo: PORTING

- USE fpWriteUART - function provided on driverInit call

Function should write one byte.

@note
This function should not use CS pin.
*/
static void HAL_uartWrite(uint8_t input)
{
#ifndef PLD_EXT_TOOLCHAIN
    fpWriteUART(input);
#else

    // ...

#endif
}

/**
    @brief HAL_uartRead

    @return         rx data byte

#### UART Read Function #####

    @todo: PORTING

- USE fpReadUART - function provided on driverInit call

Function should read one byte.
*/
static uint8_t HAL_uartRead()
{
#ifndef PLD_EXT_TOOLCHAIN
    return ( uint8_t )fpReadUART();
#else

    // ...

#endif
}

/**
    @brief HAL_uartReady

    @return     rx buffer state

#### UART Ready Function #####

    @todo: PORTING

- USE fpReadyUART - function provided on driverInit call

Function should return 1 if rx buffer have received new data.
*/

static uint8_t HAL_uartReady()
{
#ifndef PLD_EXT_TOOLCHAIN
    return ( uint8_t )fpReadyUART();
#else

    // ...

#endif
}
/** @endcond */
/** @} */
#endif
/*------------------------------------------------------------------------------

  __FAN2_Hal.c

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