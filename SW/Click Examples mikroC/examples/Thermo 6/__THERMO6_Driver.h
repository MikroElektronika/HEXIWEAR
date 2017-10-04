/*

    __THERMO6_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file   __THERMO6_Driver.h
@brief    Thermo_6 Click
@mainpage Thermo_6 Click
@{

### Click Description ###

The MAX31875 is a ±2°C-accurate local temperature
sensor with I2C/SMBus interface. The combination of tiny
package and excellent temperature measurement
accuracy makes this product ideal for a variety of
equipment.

@image html Thermo_6_img.jpg
@}
@page       THERMO6_SCHEMATICS Schematics
@{
@image html Thermo_6_sch.jpg "Thermo_6 Schematic" width=600px
@}
@defgroup   THERMO6
@brief      Thermo_6 Click Driver
@{

| Global Library Prefix | **THERMO6** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **sep 2017.**      |
| Developer             | **MikroE Team**     |


### Library Descritption ###

This is library for Thermo 6 click

*/
/**
    @example Click_Thermo_6_STM.c
    @example Click_Thermo_6_TIVA.c
    @example Click_Thermo_6_CEC.c
    @example Click_Thermo_6_KIN.c
    @example Click_Thermo_6_MSP.c
    @example Click_Thermo_6_PIC.c
    @example Click_Thermo_6_PIC32.c
    @example Click_Thermo_6_DSPIC.c
    @example Click_Thermo_6_AVR.c
    @example Click_Thermo_6_FT90x.c
    @example Click_Thermo_6_STM.mbas
    @example Click_Thermo_6_TIVA.mbas
    @example Click_Thermo_6_CEC.mbas
    @example Click_Thermo_6_KIN.mbas
    @example Click_Thermo_6_MSP.mbas
    @example Click_Thermo_6_PIC.mbas
    @example Click_Thermo_6_PIC32.mbas
    @example Click_Thermo_6_DSPIC.mbas
    @example Click_Thermo_6_AVR.mbas
    @example Click_Thermo_6_FT90x.mbas
    @example Click_Thermo_6_STM.mpas
    @example Click_Thermo_6_TIVA.mpas
    @example Click_Thermo_6_CEC.mpas
    @example Click_Thermo_6_KIN.mpas
    @example Click_Thermo_6_MSP.mpas
    @example Click_Thermo_6_PIC.pas
    @example Click_Thermo_6_PIC32.pas
    @example Click_Thermo_6_DSPIC.pas
    @example Click_Thermo_6_AVR.pas
    @example Click_Thermo_6_FT90x.pas

*/
/* -------------------------------------------------------------------------- */

#ifndef _THERMO6_H_
#define _THERMO6_H_

#include "__THERMO6_Hal.h"

/** @name                                              Thermo_6 Click ...
 *  @{                                          *///---------------------------

extern const uint8_t CFG_HIGH_12_BIT          ;
extern const uint8_t CFG_LOW_12_BIT           ;

extern const uint8_t CFG_HIGH_10_BIT          ;
extern const uint8_t CFG_LOW_10_BIT           ;

extern const uint8_t CFG_HIGH_9_BIT           ;
extern const uint8_t CFG_LOW_9_BIT            ;

extern const uint8_t CFG_HIGH_8_BIT           ;
extern const uint8_t CFG_LOW_8_BIT            ;

/// @}
/** @name                                             Thermo_6 Click Types
 *  @{                                          *///----------------------------

// ...

/// @}

#ifdef __cplusplus
extern "C"{
#endif

/** @name                                  Thermo_6 Click Driver Functions
 *  @{                               *///---------------------------------------
/**
 * @brief Thermo 6 reading  temperature data
 *
 * @param[in] buffer for temperature data
 *
 * 
 */
uint8_t THERMO6_readRegTemp(uint16_t *value);
/**
 * @brief Writing to CFG register 
 *
 * @param[in] High and low register address
 *
 * 
 */
uint8_t THERMO6_writeRegCfg(uint8_t valueHi,uint8_t valueLow);

/**
 * @brief Reading of CFG register
 *
 * @param[in] buffer for the register value
 *
 * 
 */
uint8_t THERMO6_readRegCfg(uint16_t *value);

/**
 * @brief Writing to Hyst register 
 *
 * @param[in] High and low register address
 *
 * 
 */
uint8_t THERMO6_writeRegHyst(uint8_t valueHi,uint8_t valueLow);
/**
 * @brief Reading of Hyst register
 *
 * @param[in] buffer for the register value
 *
 * 
 */
uint8_t THERMO6_readRegHyst(uint16_t *value);
/**
 * @brief Writing to Threshold register 
 *
 * @param[in] High and low register address
 *
 * 
 */
uint8_t THERMO6_writeRegOs(uint8_t valueHi,uint8_t valueLow);
/**
 * @brief Reading of Threshold register
 *
 * @param[in] buffer for the register value
 *
 * 
 */
uint8_t THERMO6_readRegOs(uint16_t *value);

/**
 * @brief Reading of the 12 bit temperature data and calculating the value
 * in Celsius
 * 
 * @param[in] none
 * 
 */
float THERMO6_getTemperature();



/// @}
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/// @}
/* -------------------------------------------------------------------------- */
/*
  __THERMO6_Driver.h

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
