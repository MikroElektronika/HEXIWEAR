/*

    __THERMOJ_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file   __THERMOJ_Driver.h
@brief    Thermo_J Click
@mainpage Thermo_J Click
@{

### Click Description ###

${CLICK_INFO}

@image html Thermo_J_img.jpg
@}
@page       THERMOJ_SCHEMATICS Schematics
@{
@image html Thermo_J_sch.jpg "Thermo_J Schematic" width=600px
@}
@defgroup   THERMOJ
@brief      Thermo_J Click Driver
@{

| Global Library Prefix | **THERMOJ** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **okt 2017.**      |
| Developer             | **MikroE Team**     |


### Library Descritption ###

${LIBRARY_DESCRIPTION}

*/
/**
    @example Click_Thermo_J_STM.c
    @example Click_Thermo_J_TIVA.c
    @example Click_Thermo_J_CEC.c
    @example Click_Thermo_J_KIN.c
    @example Click_Thermo_J_MSP.c
    @example Click_Thermo_J_PIC.c
    @example Click_Thermo_J_PIC32.c
    @example Click_Thermo_J_DSPIC.c
    @example Click_Thermo_J_AVR.c
    @example Click_Thermo_J_FT90x.c
    @example Click_Thermo_J_STM.mbas
    @example Click_Thermo_J_TIVA.mbas
    @example Click_Thermo_J_CEC.mbas
    @example Click_Thermo_J_KIN.mbas
    @example Click_Thermo_J_MSP.mbas
    @example Click_Thermo_J_PIC.mbas
    @example Click_Thermo_J_PIC32.mbas
    @example Click_Thermo_J_DSPIC.mbas
    @example Click_Thermo_J_AVR.mbas
    @example Click_Thermo_J_FT90x.mbas
    @example Click_Thermo_J_STM.mpas
    @example Click_Thermo_J_TIVA.mpas
    @example Click_Thermo_J_CEC.mpas
    @example Click_Thermo_J_KIN.mpas
    @example Click_Thermo_J_MSP.mpas
    @example Click_Thermo_J_PIC.pas
    @example Click_Thermo_J_PIC32.pas
    @example Click_Thermo_J_DSPIC.pas
    @example Click_Thermo_J_AVR.pas
    @example Click_Thermo_J_FT90x.pas

*/
/* -------------------------------------------------------------------------- */

#ifndef _THERMOJ_H_
#define _THERMOJ_H_

#include "__THERMOJ_Hal.h"

/** @name                                              Thermo_J Click ...
 *  @{                                          *///---------------------------

extern const uint8_t _THERMOJ_ADDRESS_VDD;        
extern const uint8_t _THERMOJ_ADDRESS_GND;

extern const uint8_t _THERMOJ_HOT_JUNCTION;
extern const uint8_t _THERMOJ_DELTA_TEMP;
extern const uint8_t _THERMOJ_COLD_JUNCTION;

extern const uint8_t _THERMOJ_RAW_ADC;
extern const uint8_t _THERMOJ_STATUS;
extern const uint8_t _THERMOJ_SENSOR_CFG;
extern const uint8_t _THERMOJ_DEVICE_CFG;

extern const uint8_t _THERMOJ_ALERT1_CFG;
extern const uint8_t _THERMOJ_ALERT2_CFG;
extern const uint8_t _THERMOJ_ALERT3_CFG;
extern const uint8_t _THERMOJ_ALERT4_CFG;

extern const uint8_t _THERMOJ_ALERT1_HYST;
extern const uint8_t _THERMOJ_ALERT2_HYST;
extern const uint8_t _THERMOJ_ALERT3_HYST;
extern const uint8_t _THERMOJ_ALERT4_HYST;

extern const uint8_t _THERMOJ_ALERT1_LIMIT;
extern const uint8_t _THERMOJ_ALERT2_LIMIT;
extern const uint8_t _THERMOJ_ALERT3_LIMIT;
extern const uint8_t _THERMOJ_ALERT4_LIMIT;

extern const uint8_t _THERMOJ_DEVICE_ID;    

/// @}
/** @name                                             Thermo_J Click Types
 *  @{                                          *///----------------------------

// ...

/// @}

#ifdef __cplusplus
extern "C"{
#endif

/** @name                                  Thermo_J Click Driver Functions
 *  @{                               *///---------------------------------------

/**
 * @brief Writing one byte to MCP9600 via I2C
 *
 * @param[in] slaveAddress            Choose between two slave addresses
 * which will be used to address the chip.
 *
 * @param[in] registerAddress 
 *
 * @note refer to MCP9600 datasheet for more information about the registers
 * and their functions
 * 
 */

void THERMOJ_write_byte(uint8_t slaveAddress, uint8_t registerAddress, uint8_t value);
/**
 * @brief Reading one byte from MCP9600 via I2C
 *
 * @param[in] slaveAddress            Choose between two slave addresses
 * which will be used to address the chip.
 *
 * @param[in] registerAddress 
 *
 * 
 * @note refer to MCP9600 datasheet for more information about the registers
 * and their functions
 * 
 */

uint8_t THERMOJ_read_byte(uint8_t slaveAddress, uint8_t registerAddress);
/**
 * @brief Reading one byte from MCP9600 via I2C
 *
 * @param[in] slaveAddress            Choose between two slave addresses
 * which will be used to address the chip.
 *
 * @param[in] registerAddress 
 *
 * Returns the value of register
 * 
 * @note refer to MCP9600 datasheet for more information about the registers
 * and their functions
 * 
 */

void THERMOJ_write_2byte(uint8_t slaveAddress, uint8_t registerAddress, uint16_t value);
/**
 * @brief Reading two bytes from MCP9600 via I2C
 *
 * @param[in] slaveAddress            Choose between two slave addresses
 * which will be used to address the chip.
 *
 * @param[in] registerAddress 
 *
 * 
 * @note refer to MCP9600 datasheet for more information about the registers
 * and their functions
 * 
 */
uint16_t THERMOJ_read_2byte(uint8_t slaveAddress, uint8_t registerAddress);
/**
 * @brief Reading two bytes from MCP9600 via I2C
 *
 * @param[in] slaveAddress            Choose between two slave addresses
 * which will be used to address the chip.
 *
 * @param[in] registerAddress 
 *
 * Returns the value of register 
 * 
 * @note refer to MCP9600 datasheet for more information about the registers
 * and their functions
 * 
 */
float THERMOJ_getTemperature(uint8_t slaveAddress);
/**
 * @brief Reading the temparature value from Hot-Junction
 *  Temperature register
 *
 * @param[in] slaveAddress            Choose between two slave addresses
 * which will be used to address the chip.
 *
 *
 * Returns the temperature in Celsius
 * 
 * @note refer to MCP9600 datasheet for more information about the registers
 * and their functions
 * 
 */


/// @}
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/// @}
/* -------------------------------------------------------------------------- */
/*
  __THERMOJ_Driver.h

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
