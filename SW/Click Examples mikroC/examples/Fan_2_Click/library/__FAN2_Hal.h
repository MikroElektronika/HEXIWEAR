/*

    __FAN2_Hal.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __FAN2_Hal.h
@addtogroup  FAN2
@{

| Global HAL Prefix     | **HAL**       |
|:---------------------:|:-------------:|
| Version               | **2.1.0**     |
| Date                  | **Jun 2017**  |
| Developer             | *MilosV*      |

#### MikroC HAL covers : ####
 - ARM (CEC, MSP, KINETIS, STM32, TIVA)
 - PIC
 - PIC32
 - FT90x
 - dsPIC
 - AVR
*/

#ifndef _FAN2_HAL_
#define _FAN2_HAL_

/** @cond PORTING_GUIDE */
// #define PLD_EXT_TOOLCHAIN    /**< Uncomment in case of non mikroC compiler */

#ifndef PLD_EXT_TOOLCHAIN
#define GPIO_TYPE               sfr sbit
#else

/**
    @todo: Toolchain specific typedefs for GPIO
*/

#endif

#ifdef PLD_SPI_CLICK
/*---------------------------------------------------------- SPI HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ ) || defined( __MIKROC_PRO_FOR_DSPIC__ )

typedef void                          ( *T_FAN2_SPI_Write )(        unsigned int data_out);
typedef unsigned int         ( *T_FAN2_SPI_Read ) (        unsigned int buffer);

#elif defined( __MIKROC_PRO_FOR_AVR__ ) || defined( __MIKROC_PRO_FOR_PIC__ )

typedef void                           ( *T_FAN2_SPI_Write )(        unsigned char data_out);
typedef unsigned char         ( *T_FAN2_SPI_Read )(        unsigned char dummy);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

typedef void                         ( *T_FAN2_SPI_Write )(        unsigned long data_out);
typedef unsigned long        ( *T_FAN2_SPI_Read )(        unsigned long dummy);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void                         ( *T_FAN2_SPI_Write )(        unsigned char data_out);
typedef unsigned char         ( *T_FAN2_SPI_Read )(        unsigned char dummy);

#elif defined( PLD_EXT_TOOLCHAIN )
/**
    @todo: Toolchain specific typedefs for functions used for SPI BUS

 - T_FAN2_SPI_Write - Writes one byte
 - T_FAN2_SPI_Read - Reads one byte

@note
Functions should not have influence on CS pin.
*/

#endif
#endif
#ifdef PLD_I2C_CLICK
/*---------------------------------------------------------- I2C HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

typedef unsigned int        ( *T_FAN2_I2C_Start )();
typedef void                           ( *T_FAN2_I2C_Stop )();                                                // DUMMY
typedef void                         ( *T_FAN2_I2C_Restart )();                                                // DUMMY
typedef unsigned int         ( *T_FAN2_I2C_Write )(        unsigned char slave,
                                                            unsigned char *buffer,
                                                            unsigned long count,
                                                            unsigned long end_mode);
typedef void                         ( *T_FAN2_I2C_Read )(        unsigned char slave,
                                                                           unsigned char *buffer,
                                                                           unsigned long count,
                                                                           unsigned long end_mode);
    #elif defined( __MSP__ )
typedef void                          ( *T_FAN2_I2C_Start )();                                                // DUMMY
typedef void                           ( *T_FAN2_I2C_Stop )();                                                // DUMMY
typedef void                         ( *T_FAN2_I2C_Restart )();                                                // DUMMY
typedef unsigned int         ( *T_FAN2_I2C_Write )(        unsigned char slave,
                                                            unsigned char *buffer,
                                                            unsigned long count,
                                                            unsigned long end_mode);

typedef void                         ( *T_FAN2_I2C_Read )(        unsigned char slave,
                                                                           unsigned char *buffer,
                                                                           unsigned long count,
                                                                           unsigned long end_mode);

    #elif defined( __TI__ )

typedef void                         ( *T_FAN2_I2C_Start )(        char slave_address,
                                                              char dir);
typedef void                           ( *T_FAN2_I2C_Stop )();                                                // DUMMY
typedef void                         ( *T_FAN2_I2C_Restart )();                                                // DUMMY
typedef unsigned char         ( *T_FAN2_I2C_Write )(        unsigned char data_in,
                                                             unsigned char mode);
typedef unsigned char        ( *T_FAN2_I2C_Read )(        unsigned char *data_out,
                                                                   unsigned char mode);
    #endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )

typedef unsigned char        ( *T_FAN2_I2C_Start )();
typedef void                           ( *T_FAN2_I2C_Stop )();
typedef void                         ( *T_FAN2_I2C_Restart )();                                                // DUMMY
typedef void                         ( *T_FAN2_I2C_Write )( rx       unsigned char data_out);
typedef unsigned char         ( *T_FAN2_I2C_Read )(  rx      unsigned char ack);

#elif  defined( __MIKROC_PRO_FOR_PIC__ )

typedef unsigned char        ( *T_FAN2_I2C_Start )();
typedef void                         ( *T_FAN2_I2C_Stop )();
typedef void                         ( *T_FAN2_I2C_Restart )();
typedef unsigned char        ( *T_FAN2_I2C_Write )(        unsigned char data_out);
typedef unsigned char        ( *T_FAN2_I2C_Read )(        unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

typedef unsigned int         ( *T_FAN2_I2C_Start )();
typedef void                         ( *T_FAN2_I2C_Stop )();
typedef unsigned int         ( *T_FAN2_I2C_Restart )();
typedef unsigned int         ( *T_FAN2_I2C_Write )(        unsigned char data_out);
typedef unsigned char         ( *T_FAN2_I2C_Read )(        unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )

typedef unsigned int         ( *T_FAN2_I2C_Start )();
typedef void                         ( *T_FAN2_I2C_Stop )();
typedef void                         ( *T_FAN2_I2C_Restart )();
typedef unsigned int         ( *T_FAN2_I2C_Write )(        unsigned char data_out);
typedef unsigned char         ( *T_FAN2_I2C_Read )(        unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_8051__ )

typedef unsigned char        ( *T_FAN2_I2C_Start )();
typedef void                         ( *T_FAN2_I2C_Stop )();
typedef void                         ( *T_FAN2_I2C_Restart )();                                                // DUMMY
typedef void                         ( *T_FAN2_I2C_Write )(        unsigned char data_out);
typedef unsigned char        ( *T_FAN2_I2C_Read )(        unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void                               ( *T_FAN2_I2C_Start )(        unsigned char slave);
typedef void                               ( *T_FAN2_I2C_Stop )();                                                  // DUMMY
typedef void                               ( *T_FAN2_I2C_Restart )();                                                // DUMMY
typedef unsigned char         ( *T_FAN2_I2C_Write )(        unsigned char *buffer,
                                                             unsigned int count);
typedef unsigned char         ( *T_FAN2_I2C_Read )(        unsigned char *buffer,
                                                            unsigned int count);

#elif defined( PLD_EXT_TOOLCHAIN )

/**
    @todo: Toolchain specific typedefs for functions used for I2C BUS

 - T_FAN2_I2C_Start       - not required - I2C Start
 - T_FAN2_I2C_Stop        - not required - I2C Stop
 - T_FAN2_I2C_Restart     - not required - I2C Reastart
 - T_FAN2_I2C_Write       - required     - Write N bytes
 - T_FAN2_I2C_Read        - required     - Read N bytes

@note
Not all are required to implement complete write or read sequence
*/
#endif
#endif
#ifdef PLD_UART_CLICK
/*--------------------------------------------------------- UART HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ ) || defined( __MIKROC_PRO_FOR_DSPIC__ ) || defined( __MIKROC_PRO_FOR_PIC32__ )

typedef void                         ( *T_FAN2_UART_Write )( unsigned int data_out);
typedef unsigned int         ( *T_FAN2_UART_Read )();
typedef unsigned int         ( *T_FAN2_UART_Ready )();

#elif defined( __MIKROC_PRO_FOR_AVR__ ) || defined( __MIKROC_PRO_FOR_PIC__ ) || defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void                               ( *T_FAN2_UART_Write )( unsigned char data_out);
typedef unsigned char         ( *T_FAN2_UART_Read )();
typedef unsigned char         ( *T_FAN2_UART_Ready )();
#elif defined( PLD_EXT_TOOLCHAIN )

/**
    @todo: Toolchain specific functions prototypes for UART BUS

 - T_FAN2_UART_Write     - writes one byte
 - T_FAN2_UART_Read      - reads one byte
 - T_FAN2_UART_Ready     - checks rx buffer
*/
#endif
#endif
/** @endcond */
/** @} */
#endif
/*------------------------------------------------------------------------------

  __FAN2_Hal.h

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