/*

    __MACADDRESS_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file   __MACADDRESS_Driver.h
@brief    MAC_Address Click
@mainpage MAC_Address Click
@{

### Click Description ###

EEPROM organizes as two blocks of 128 x 8-bit memory with I2C interface.

@image html MAC_Address_img.jpg
@}
@page       MACADDRESS_SCHEMATICS Schematics
@{
@image html MAC_Address_sch.jpg "MAC_Address Schematic" width=600px
@}
@defgroup   MACADDRESS
@brief      MAC_Address Click Driver
@{

| Global Library Prefix | **MACADDRESS** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Aug 2017.**      |
| Developer             | **MikroE Team**     |


### Library Descritption ###

Library covers all functionalities of the click board.

*/
/**
    @example Click_MAC_Address_STM.c
    @example Click_MAC_Address_TIVA.c
    @example Click_MAC_Address_CEC.c
    @example Click_MAC_Address_KIN.c
    @example Click_MAC_Address_MSP.c
    @example Click_MAC_Address_PIC.c
    @example Click_MAC_Address_PIC32.c
    @example Click_MAC_Address_DSPIC.c
    @example Click_MAC_Address_AVR.c
    @example Click_MAC_Address_FT90x.c
    @example Click_MAC_Address_STM.mbas
    @example Click_MAC_Address_TIVA.mbas
    @example Click_MAC_Address_CEC.mbas
    @example Click_MAC_Address_KIN.mbas
    @example Click_MAC_Address_MSP.mbas
    @example Click_MAC_Address_PIC.mbas
    @example Click_MAC_Address_PIC32.mbas
    @example Click_MAC_Address_DSPIC.mbas
    @example Click_MAC_Address_AVR.mbas
    @example Click_MAC_Address_FT90x.mbas
    @example Click_MAC_Address_STM.mpas
    @example Click_MAC_Address_TIVA.mpas
    @example Click_MAC_Address_CEC.mpas
    @example Click_MAC_Address_KIN.mpas
    @example Click_MAC_Address_MSP.mpas
    @example Click_MAC_Address_PIC.pas
    @example Click_MAC_Address_PIC32.pas
    @example Click_MAC_Address_DSPIC.pas
    @example Click_MAC_Address_AVR.pas
    @example Click_MAC_Address_FT90x.pas

*/
/* -------------------------------------------------------------------------- */

#ifndef _MACADDRESS_H_
#define _MACADDRESS_H_

#include "__MACADDRESS_Hal.h"

extern const uint8_t _MACADDRESS_OK;
extern const uint8_t _MACADDRESS_PAR_ERR;
extern const uint8_t _MACADDRESS_COM_ERR;

/** @name                                             MAC_Address Click Types
 *  @{                                          *///----------------------------

typedef int8_t T_MACADDRESS_ret;

/// @}

#ifdef __cplusplus
extern "C"{
#endif

/** @name                                  MAC_Address Click Driver Functions
 *  @{                               *///---------------------------------------

/**
 * @brief MACADDRESS_init
 * @param slaveAddress
 */
void MACADDRESS_init(uint8_t slaveAddress);

/**
 * @brief Read MAC Address
 * @param[out] mac Node Unique Value
 * @return _MACADDRESS_OK / _MACADDRESS_ERR
 * @note
 * Parameter must be 6 bytes long array
 */
T_MACADDRESS_ret 
  MACADDRESS_readMAC(uint8_t *mac);

/**
 * @brief Write One Byte
 * @param[in] addrses EEPROM address
 * @param[in] data_ Data to write
 * @return _MACADDRESS_OK / _MACADDRESS_ERR
 * @note
 * Address must be in range 0x00 - 0x7F
 */
T_MACADDRESS_ret 
  MACADDRESS_writeByte(uint8_t addrses, uint8_t data_);

/**
 * @brief Read One Byte
 * @param[in] addrses EEPROM address
 * @param[out] data_ Read data
 * @return _MACADDRESS_OK / _MACADDRESS_ERR
 * @note
 * Address must be in range 0x00 - 0x7F
 */
T_MACADDRESS_ret 
  MACADDRESS_readByte(uint8_t addrses, uint8_t *data_);

/**
 * @brief Write Multiple Bytes
 * @param[in] address EEPROM address
 * @param[in] buffer Data to write
 * @param[in] nBytes Number of bytes to write
 * @return _MACADDRESS_OK / _MACADDRESS_ERR
 * @note
 * Address + nBytes may not exceed 0x7F
 */
T_MACADDRESS_ret 
  MACADDRESS_writeMulti(uint8_t address, uint8_t *buffer, int8_t nBytes);

/**
 * @brief Read Multiple Bytes
 * @param[in] address EEPROM address
 * @param[out] buffer Read Data
 * @param[in] nBytes Number of bytes to read
 * @return _MACADDRESS_OK / _MACADDRESS_ERR
 * @note
 * Address + nBytes may not exceed 0x7F
 */
T_MACADDRESS_ret 
  MACADDRESS_readMulti(uint8_t address, uint8_t *buffer, int8_t nBytes);

/// @}

#ifdef __cplusplus
} // extern "C"
#endif
#endif

/// @}
/* -------------------------------------------------------------------------- */
/*
  __MACADDRESS_Driver.h

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
