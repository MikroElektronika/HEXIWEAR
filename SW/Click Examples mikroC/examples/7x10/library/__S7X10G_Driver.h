/*

    __S7X10G_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __S7X10G_Driver.h
@brief 			7 x 10 R LED Matrix driver

@mainpage S7X10G Click
@{

### Click Description ###

7x10 G click carries a matrix of 70 green LEDs driven by a pair of 8-bit serial-in, parallel-out shift registers, a Darlington Transistor array and a Johnson counter. The click communicates with the target MCU through the mikroBUS™ SPI interface (SCK, SDO, SDI), with additional functionality provided by R CLK, MR#, LATCH and R RST pins. 7x10 G click is designed to use either a 3.3V or a 5V power supply.

### Features ###
    - A pair of red 7x5 LED matrices
    - SPI interface (plus MR#, LATCH and R RST pins)
    - 3.3V or 5V power supply
    - Scrolling text capability

@}

@addtogroup  S7X10G_DRIVER
@brief       S7X10G Click Driver
@{

    Global Library Prefix : **S7X10G**
    Version               : **1.0.0**
    Date                  : Jul 2017.
    Developer             : *MikroE Team*

    This library contains functions for 7 x 10 G LED Matrix click.
*/
/**
    @example Click_S7X10G_STM.c
    @example Click_S7X10G_KINETIS.c
    @example Click_S7X10G_TIVA.c
    @example Click_S7X10G_PIC.c
    @example Click_S7X10G_PIC32.c
    @example Click_S7X10G_DSPIC.c
    @example Click_S7X10G_AVR.c

*//*--------------------------------------------------------------------------*/

#ifndef _S7X10G_HW_H_
#define _S7X10G_HW_H_

#include <stdint.h>

/**
 * @name 		S7X10G Click Types
 *//*-------------------------------------------------------------------------*/
///@{

typedef enum
{
    S7X10G_SPEED_SLOW,  /**< Scroll columns at 1 per second */
    S7X10G_SPEED_MED,   /**< Scroll columns at 2 per second */
    S7X10G_SPEED_FAST   /**< Scroll columns at 3 per second */
} T_S7X10G_speed;

///@}
/**
 * @name 		S7X10G Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the display
 *
 * @note SPI bus must be initialized before calling.
 *
 * @code
 * ...
 * SPI_Init();
 * S7X10G_init();
 * @endcode
 */
void S7X10G_init( void );

/**
 * @brief Refreshes display
 * @note Needs to be called as frequently as possible.
 * @code
 * while( 1 )
 * {
 *     S7X10G_refreshDisplay();
 * }
 * @endcode
 */
bool S7X10G_refreshDisplay( void );

/**
 * @brief Clears display
 */
void S7X10G_clearDisplay( void );

/**
 * @brief Draws a pixel at specified x, y location
 * @param[in] row   matrix row
 * @param[in] col   matrix column
 * @code
 * S7X10G_drawPixels( 1, 3 ); // Lights pixel on row 1 column 3
 * @endcode
 * @note min x value is 1 max is 7, min y value is 1 max is 10
 */
void S7X10G_drawPixel( uint8_t row, uint8_t col );

/**
 * @brief Write Text on the display
 * @param[in] txt    text to be written
 */
void S7X10G_drawText( char *txt );

/**
 * @brief Draws numbers on the display
 * @param[in] num    max number is 99
 */
void S7X10G_drawNumber( uint8_t num );

/**
 * @brief Enable scrolling feature
 * @param[in] speed    scrolling speed
 */
void S7X10G_scrollEnable( T_S7X10G_speed speed );

/**
 * @brief Disables scrolling
 */
void S7X10G_scrollDisable( void );

/**
 * @brief Tick called to control scrolling speed
 *
 * This function is used on the scrolling feature.  It is to be called
 * after starting the scroll and around each display refresh. It does not
 * need to be called if scrolling is not needed.
 */
void S7X10G_tick( void );

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __S7X10G_Driver.h

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
