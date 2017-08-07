/*

    __MACADDRESS_Hal.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */
/**
@file  __MACADDRESS_Hal.c
@brief   MACADDRESS HAL Source
*/
/**
@page    MACADDRESS_PORTING_GUIDE MAC_Address Porting Guide

---
### HAL Function Pointers ###

@ref HAL_Pointers "HAL" pointers are involved to improve portability, they can 
be also dynamiclly reassigned which means that same HAL can be used for more 
than one device. This pointers are assinged using HAL_init public functions.
Implementation of static functions should by done by using only this 
static function pointers.

---
### HAL Static Functions ###

@ref HAL_Private_Functions "HAL static" functions should use only function 
pointers assigned during HAL initialization. This function are used by driver. 
Check function description for more details about what each function should do.

---
### HAL Types ###

#### SPI Types ####

- Add preprocessor specific for your compiler
- Under the preprocessor write typedefs for SPI functions
  + ```T_MACADDRESS_SPI_Write``` - Writes one byte - 8 clock cycles
  + ```T_MACADDRESS_SPI_Read``` - Reads one byte - 8 clock cycles

#### I2C Types ####

- Add preprocessor specific for your compiler
- Under the preprocessor write typedefs for I2C Functions
  + ```T_MACADDRESS_I2C_Start```       - I2C Start
  + ```T_MACADDRESS_I2C_Stop```        - I2C Stop
  + ```T_MACADDRESS_I2C_Restart```     - I2C Reastart
  + ```T_MACADDRESS_I2C_Write```       - Write byte
  + ```T_MACADDRESS_I2C_Read```        - Read byte

#### UART Types ####

 - Add preprocessor specific for your compiler
 - Under the preprocessor write typedefs for UART functions
  + ```T_MACADDRESS_UART_Write```     - writes one byte
  + ```T_MACADDRESS_UART_Read```      - reads one byte
  + ```T_MACADDRESS_UART_Ready```     - checks rx buffer
*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"
    
#include "__MACADDRESS_Hal.h"
#include "__MACADDRESS_Cfg.c"

#ifdef __MACADDRESS_I2C
#if defined (__MIKROC_PRO_FOR_ARM__) && defined (__TI__) && !defined(__MSP__)
static uint8_t startF           = 0;
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
static uint8_t startF           = 0;
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
static uint8_t startF           = 0;
#endif
#endif

#ifdef __MACADDRESS_I2C
#if defined (__MIKROC_PRO_FOR_ARM__) && defined (__TI__) && !defined(__MSP__)
#define END_MODE_STOP            0
#define END_MODE_RESTART         1
#define END_MODE_NO              2
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
#define READ_BIT                 1
#define WRITE_BIT                0
#define NACK_BIT                 1
#define ACK_BIT                  0
#define END_MODE_STOP            0
#define END_MODE_RESTART         1
#define END_MODE_NO              2
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
#define READ_BIT                 1
#define WRITE_BIT                0
#define NACK_BIT                 1
#define ACK_BIT                  0
#define END_MODE_STOP            0
#define END_MODE_RESTART         1
#define END_MODE_NO              2
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
#define READ_BIT                 1
#define WRITE_BIT                0
#define NACK_BIT                 0
#define ACK_BIT                  1
#define END_MODE_STOP            0
#define END_MODE_RESTART         1
#define END_MODE_NO              2
#endif
#ifdef __MIKROC_PRO_FOR_AVR__ 
#define READ_BIT                 1
#define WRITE_BIT                0
#define NACK_BIT                 0
#define ACK_BIT                  1
#define END_MODE_STOP            0
#define END_MODE_RESTART         1
#define END_MODE_NO              2
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
#define END_MODE_STOP            0
#define END_MODE_RESTART         1
#define END_MODE_NO              2
#endif
#endif

/** 
 *  @name                                                          HAL_Pointers
 *  @{                                                       *///---------------

// GPIO_POINTERS _____________________________________

#ifdef __MACADDRESS_GPIO
static T_MACADDRESS_GPIO_Set          fpAN;                                  /**< Set Pin State Function Pointer */
static T_MACADDRESS_GPIO_Get          fpRST;                                 /**< Get Pin State Function Pointer */
#endif

// SPI POINTERS ______________________________________

#ifdef __MACADDRESS_SPI
static T_MACADDRESS_SPI_Write        fpWriteSPI;                             /**< Write SPI Function Pointer */
static T_MACADDRESS_SPI_Read         fpReadSPI;                              /**< Read SPI Function Pointer */
#endif

// I2C POINTERS ______________________________________

#ifdef __MACADDRESS_I2C
static T_MACADDRESS_I2C_Start        fpStartI2C;                             /**< Start I2C Function Pointer */
static T_MACADDRESS_I2C_Stop         fpStopI2C;                              /**< Stop I2C Function Pointer */
static T_MACADDRESS_I2C_Restart      fpRestartI2C;                           /**< Restart I2C Function Pointer */
static T_MACADDRESS_I2C_Write        fpWriteI2C;                             /**< Write I2C Function Pointer */
static T_MACADDRESS_I2C_Read         fpReadI2C;                              /**< Read I2C Function Pointer */
#endif

// UART POINTERS _____________________________________

#ifdef __MACADDRESS_UART
static T_MACADDRESS_UART_Write       fpWriteUART;                            /**< Write UART Function Pointer */
static T_MACADDRESS_UART_Read        fpReadUART;                             /**< Read UART Function Pointer */
static T_MACADDRESS_UART_Ready       fpReadyUART;                            /**< Ready UART Function Pointer */
#endif

/// @} 
/** @name                                                 HAL_Private_Functions
 *  @{                                              *///------------------------

// SPI HAL ___________________________________________

#ifdef __MACADDRESS_SPI

/**
 * @brief hal_spiWrite
 *
 * @param[in] pBuf             pointer to data buffer
 * @param[in] nBytes           number of bytes for writing
 *
 * Function executes write sequence of n bytes.
 *
 * @note
 * This function have not using CS pin.
 */
static void hal_spiWrite(uint8_t *pBuf, uint16_t nBytes);

/**
 * @brief hal_spiRead
 *
 * @param[out] pBuf            pointer to data buffer
 * @param[in]  nBytes          number of bytes for writing
 *
 * Function executes read sequence of n bytes.
 *
 * @note
 * This function should not use CS pin.
 */
static void hal_spiRead(uint8_t *pBuf, uint16_t nBytes);

/**
 * @brief hal_spiTransfer
 *
 * @param[in]  pIn             pointer to write data buffer
 * @param[out] pOut            pointer to read data buffer
 * @param[in]  nBytes          number of bytes for writing
 *
 * Function should executes read/write sequence of n bytes.
 *
 * @note
 * This function should not use CS pin.
 */
static void hal_spiTransfer(uint8_t *pIn, uint8_t *pOut, uint16_t nBytes);

static void hal_spiWrite(uint8_t *pBuf, uint16_t nBytes)
{
#ifdef __MIKROC__
    uint8_t *ptr = pBuf;
    while( nBytes-- )
        fpWriteSPI( *( ptr++ ) );
#endif
}

static void hal_spiRead(uint8_t *pBuf, uint16_t nBytes)
{
#ifdef __MIKROC__
    uint8_t *ptr = pBuf;
    while( nBytes-- )
        *( ptr++ ) = fpReadSPI( 0x00 );
#endif
}

static void hal_spiTransfer(uint8_t *pIn, uint8_t *pOut, uint16_t nBytes)
{
#ifdef __MIKROC__
    uint8_t *in = pIn;
    uint8_t *out = pOut;
    while( nBytes-- )
        *( out++ ) = fpReadSPI( *( in++ ) );
#endif
}
#endif

// I2C HAL ___________________________________________

#ifdef __MACADDRESS_I2C

/**
 * @brief hal_i2cStart
 *
 * @return    0                No Error
 *
 * Function executes start condition on I2C BUS.
 */
static int hal_i2cStart(void);

/**
 * @brief hal_i2cWrite
 *
 * @param[in] slaveAddress     7 bit slave addres without 0 bit (read/write bit)
 * @param[in] pBuf             pointer to data buffer
 * @param[in] nBytes           number of bytes for writing
 * @param[in] endMode          END_MODE_STOP / END_MODE_RESTART / END_MODE_NO
 *
 * @return    0                No Error
 *
 * Function should executes write sequence on I2C bus.
 *
 * |       8 Bits      | Write Sequence (n Bytes) | End Mode       |
 * |:-----------------:|:------------------------:|:--------------:|
 * | Slave Address + W | Data Bytes               | Stop / Restart |
 *
 * @note
 * This function alongside with hal_i2cStart represents comlete write sequence.
 *
 * @warning
 * No End mode is not possible on all architectures.
 */
static int hal_i2cWrite(uint8_t slaveAddress, uint8_t *pBuf, uint16_t nBytes, uint8_t endMode);

/**
 * @brief hal_i2cRead
 *
 * @param[in] slaveAddress     7 bit slave addres without 0 bit (read/write bit)
 * @param[in] pBuf             pointer to data buffer
 * @param[in] nBytes           number of bytes to read
 * @param[in] endMode          END_MODE_STOP / END_MODE_RESTART / END_MODE_NO
 *
 * @return    0                No Error
 *
 * Function should executes read sequence on I2C bus.
 * 
 * |       8 Bits      | Read Sequence (n Bytes)  | End Mode       |
 * |:-----------------:|:------------------------:|:--------------:|
 * | Slave Address + R | Data Bytes + ACK/NACK    | Stop / Restart |
 *
 * @note
 * This function alongside with hal_i2cStart represents comlete read sequence.
 *
 * @warning
 * No End mode is not possible on all architectures.
 */
static int hal_i2cRead(uint8_t slaveAddress, uint8_t *pBuf, uint16_t nBytes, uint8_t endMode);

static int hal_i2cStart()
{
    int res = 0;

#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __STM32__
    res |= fpStartI2C();
#endif 
#ifdef __KINETIS__
    res |= fpStartI2C();
#endif
#ifdef __MCHP__
    res |= fpStartI2C();
#endif
#ifdef __TI__
    startF = 1;
#endif
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
    startF = 1;
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
    res |= fpStartI2C();
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
    res |= fpStartI2C();
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
    res |= fpStartI2C();
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
    res |= fpStartI2C();
#endif
    return res;
}

static int hal_i2cWrite(uint8_t slaveAddress, uint8_t *pBuf, uint16_t nBytes, uint8_t endMode)
{
    int res = 0;
    uint8_t *ptr = pBuf;

#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __STM32__ 
    res |= fpWriteI2C(slaveAddress, ptr, nBytes, endMode);
#endif
#ifdef __KINETIS__ 
    res |= fpWriteI2C(slaveAddress, ptr, nBytes, endMode);
#endif
#ifdef __MCHP__
    res |= fpWriteI2C(slaveAddress, ptr, nBytes, endMode);
#endif
#ifdef __TI__ 
#ifdef __MSP__
    res |= fpWriteI2C(slaveAddress, ptr, nBytes, endMode);
#else
    if( startF ) {
        fpStartI2C(slaveAddress, _I2C_DIR_MASTER_TRANSMIT);
        Delay_1ms();
        startF = 0;
    }
    if(nBytes == 1) {
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_SINGLE_SEND );
        Delay_1ms();
    } else if(nBytes == 2) {
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        Delay_1ms();
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    } else {
        res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_START );
        Delay_1ms();
        while(--nBytes > 1) {
            res |= fpWriteI2C( *ptr++, _I2C_MASTER_MODE_BURST_SEND_CONT );
            Delay_1ms();
        }
        res |= fpWriteI2C( *ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    }
    if( endMode = END_MODE_RESTART ){
        startF = 1;
    }
#endif
#endif
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
    if( startF ) {
        fpStartI2C(slaveAddress);
        startF = 0;
    }
    res |= fpWriteI2C(ptr, nBytes);
    if( endMode = END_MODE_RESTART ) {
        startF = 1;
    }
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
    fpWriteI2C( (slaveAddress << 1) | WRITE_BIT );
    while(nBytes--)
        fpWriteI2C(*( ptr++ ));
    if( endMode == END_MODE_STOP )
        fpStopI2C();
    if( endMode == END_MODE_RESTART )
        fpStartI2C();
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__ 
    res |= fpWriteI2C( (slaveAddress << 1) | WRITE_BIT );
    while(nBytes--)
        res |= fpWriteI2C(*( ptr++ ));
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpStartI2C();
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
    res |= fpWriteI2C( (slaveAddress << 1) | WRITE_BIT );
    while(nBytes--)
        res |= fpWriteI2C(*( ptr++ ));
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpStartI2C();
#endif
#ifdef __MIKROC_PRO_FOR_PIC__ 
    res |= fpWriteI2C( (slaveAddress << 1) | WRITE_BIT );
    while(nBytes--)
        res |= fpWriteI2C(*( ptr++ ));
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpStartI2C();
#endif
    return res;
}

static int hal_i2cRead(uint8_t slaveAddress, uint8_t *pBuf, uint16_t nBytes, uint8_t endMode)
{
    int res = 0;
    uint8_t *ptr = pBuf;

#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __STM32__ 
    fpReadI2C(slaveAddress, ptr, nBytes, endMode);
#endif
#ifdef __KINETIS__
    fpReadI2C(slaveAddress, ptr, nBytes, endMode);
#endif
#ifdef __MCHP__
    fpReadI2C(slaveAddress, ptr, nBytes, endMode);
#endif
#ifdef __TI__
#ifdef __MSP__
    fpReadI2C(slaveAddress, ptr, nBytes, endMode);
#else
    if( startF ) {
        fpStartI2C(slaveAddress, _I2C_DIR_MASTER_RECEIVE);
        Delay_1ms();
        startF = 0;
    }
    if(nBytes == 1) {
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_SINGLE_RECEIVE);
        Delay_1ms();
    } else if(nBytes == 2) {
        res |= fpReadI2C(ptr++, _I2C_MASTER_MODE_BURST_RECEIVE_START);
        Delay_1ms();
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
    } else {
        res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_RECEIVE_START);
        Delay_1ms();
        while(--nBytes > 1) {
            res |= fpReadI2C(ptr++ , _I2C_MASTER_MODE_BURST_RECEIVE_CONT);
            Delay_1ms();
        }
        res |= fpReadI2C(ptr, _I2C_MASTER_MODE_BURST_RECEIVE_FINISH);
    }
    if( endMode = END_MODE_RESTART ) {
        startF = 1;
    }
#endif
#endif
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
    if( startF ) {
        fpStartI2C(slaveAddress);
        startF = 0;
    }
    res |= fpReadI2C(ptr, nBytes);
    if( endMode = END_MODE_RESTART ) {
        startF = 1;
    }
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
    fpWriteI2C((slaveAddress << 1) | READ_BIT);
    while(--nBytes) *ptr++ =
        fpReadI2C(ACK_BIT);
    *ptr = fpReadI2C(NACK_BIT);
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpStartI2C();
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__ 
    res |= fpWriteI2C((slaveAddress << 1) | READ_BIT);
    while(--nBytes)
        *ptr++ = fpReadI2C(ACK_BIT);
    *ptr = fpReadI2C(NACK_BIT);
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpRestartI2C();
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
    res |= fpWriteI2C((slaveAddress << 1) | READ_BIT);
    while(--nBytes)
        *ptr++ = fpReadI2C(ACK_BIT);
    *ptr = fpReadI2C(NACK_BIT);
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpRestartI2C();
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
    res |= fpWriteI2C((slaveAddress << 1) | READ_BIT);
    while(--nBytes)
        *ptr++ = fpReadI2C(ACK_BIT);
    *ptr = fpReadI2C(NACK_BIT);
    if(endMode == END_MODE_STOP)
        fpStopI2C();
    if(endMode == END_MODE_RESTART)
        fpRestartI2C();
#endif
    return res;
}
#endif

// UART HAL __________________________________________

#ifdef __MACADDRESS_UART

/**
 * @brief hal_uartWrite
 *
 * @param[in] input tx data byte
 *
 * Function writes one byte on UART.
 */
static void hal_uartWrite(uint8_t input);

/**
 * @brief hal_uartRead
 *
 * @return rx data byte
 *
 * Function reads one byte.
 */
static uint8_t hal_uartRead();

/**
 * @brief hal_uartReady
 *
 * @return rx buffer state
 *
 * Function should return 1 if rx buffer have received new data.
 */
static uint8_t hal_uartReady();

static void hal_uartWrite(uint8_t input)
{
#ifdef __MIKROC__
    fpWriteUART(input);
#endif
}

static uint8_t hal_uartRead()
{
#ifdef __MIKROC__
    return ( uint8_t )fpReadUART();
#endif
}

static uint8_t hal_uartReady()
{
#ifdef __MIKROC__
    return ( uint8_t )fpReadyUART();
#endif
}
#endif

/// @}
/// @}
/* -------------------------------------------------------------------------- */
/*
  __MACADDRESS_Hal.c

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