/*

    __S7X10G_Hal.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __S7X10G_Hal.h
@addtogroup     S7X10G_HAL
@brief 7 x 10 LED Matrix hardware layer. Represents a generic SPI read/write
       interface for multiple platforms
@note This implimentation assumes that all SPI bus hardware has been
      initialized outside of this module.
@{

Global HAL Prefix     : **HAL**
Date                  : **July 2017**
Developer             : *MikroE Team*
*/

#ifndef S7X10G_HAL_H
#define S7X10G_HAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Hardware initialization
 *
 */
int HAL_spiInit( void );

/**
 * @brief Reset SPI
 */
void HAL_spiReset( void );

/**
 * @brief Abstraction of writing to SPI
 *
 * @param[in] buff        bytes to transfer to display
 */
void HAL_spiWrite( uint8_t *buff );

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
/*------------------------------------------------------------------------------

  __S7X10G_Hal.h

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
