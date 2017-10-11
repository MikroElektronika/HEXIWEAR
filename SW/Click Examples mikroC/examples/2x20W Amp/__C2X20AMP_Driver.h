/*

    __C2X20AMP_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file   __C2X20AMP_Driver.h
@brief    C2X20W_Amp Click
@mainpage C2X20W_Amp Click
@{

### Click Description ###

${CLICK_INFO}

@image html C2X20W_Amp_img.jpg
@}
@page       C2X20AMP_SCHEMATICS Schematics
@{
@image html C2X20W_Amp_sch.jpg "C2X20W_Amp Schematic" width=600px
@}
@defgroup   C2X20AMP
@brief      C2X20W_Amp Click Driver
@{

| Global Library Prefix | **C2X20AMP** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Aug 2017.**      |
| Developer             | **Djordje Rosic**     |


### Library Descritption ###

${LIBRARY_DESCRIPTION}

*/
/**
    @example Click_C2X20W_Amp_STM.c
    @example Click_C2X20W_Amp_TIVA.c
    @example Click_C2X20W_Amp_CEC.c
    @example Click_C2X20W_Amp_KIN.c
    @example Click_C2X20W_Amp_MSP.c
    @example Click_C2X20W_Amp_PIC.c
    @example Click_C2X20W_Amp_PIC32.c
    @example Click_C2X20W_Amp_DSPIC.c
    @example Click_C2X20W_Amp_AVR.c
    @example Click_C2X20W_Amp_FT90x.c
    @example Click_C2X20W_Amp_STM.mbas
    @example Click_C2X20W_Amp_TIVA.mbas
    @example Click_C2X20W_Amp_CEC.mbas
    @example Click_C2X20W_Amp_KIN.mbas
    @example Click_C2X20W_Amp_MSP.mbas
    @example Click_C2X20W_Amp_PIC.mbas
    @example Click_C2X20W_Amp_PIC32.mbas
    @example Click_C2X20W_Amp_DSPIC.mbas
    @example Click_C2X20W_Amp_AVR.mbas
    @example Click_C2X20W_Amp_FT90x.mbas
    @example Click_C2X20W_Amp_STM.mpas
    @example Click_C2X20W_Amp_TIVA.mpas
    @example Click_C2X20W_Amp_CEC.mpas
    @example Click_C2X20W_Amp_KIN.mpas
    @example Click_C2X20W_Amp_MSP.mpas
    @example Click_C2X20W_Amp_PIC.pas
    @example Click_C2X20W_Amp_PIC32.pas
    @example Click_C2X20W_Amp_DSPIC.pas
    @example Click_C2X20W_Amp_AVR.pas
    @example Click_C2X20W_Amp_FT90x.pas

*/
/* -------------------------------------------------------------------------- */

#ifndef _C2X20AMP_H_
#define _C2X20AMP_H_

#include <stdint.h>
#include "__C2X20AMP_Hal.h"

/** @name                                              C2X20W_Amp Click ...
 *  @{                                          *///---------------------------

extern const uint8_t _C2X20AMP_SOME_VAR;

/// @}
/** @name                                             C2X20W_Amp Click Types
 *  @{                                          *///----------------------------

// ...

/// @}

#ifdef __cplusplus
extern "C"{
#endif

/** @name                                  C2X20W_Amp Click Driver Functions
 *  @{                               *///---------------------------------------

/**
 * @brief Init
 */
void C2X20AMP_init ();
void C2X20AMP_setVolume (uint8_t newVolume);

void C2X20AMP_increaseVolume ();
void C2X20AMP_decreaseVolume ();

void C2X20AMP_classicPWM ();
void C2X20AMP_filterlessModulation ();



/// @}
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/// @}
/* -------------------------------------------------------------------------- */
/*
  __C2X20AMP_Driver.h

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