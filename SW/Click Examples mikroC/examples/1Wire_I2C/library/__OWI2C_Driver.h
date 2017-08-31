/*

    __OWI2C_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file   __OWI2C_Driver.h
@brief    One_Wire_I2C Click
@mainpage One_Wire_I2C Click
@{

### Click Description ###

The DS28E17 is a 1-Wire slave to I2C master bridge
device that interfaces directly to I2C slaves at standard
(100kHz max) or fast (400kHz max). Data transfers serially
by means of the 1-Wire® protocol, which requires only
a single data lead and a ground return.

@image html One_Wire_I2C_img.jpg
@}
@page       OWI2C_SCHEMATICS Schematics
@{
@image html One_Wire_I2C_sch.jpg "One_Wire_I2C Schematic" width=600px
@}
@defgroup   OWI2C
@brief      One_Wire_I2C Click Driver
@{

| Global Library Prefix | **OWI2C** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Aug 2017.**      |
| Developer             | **Djordje Rosic**     |


### Library Descritption ###


*/
/**
    @example Click_One_Wire_I2C_STM.c
    @example Click_One_Wire_I2C_TIVA.c
    @example Click_One_Wire_I2C_CEC.c
    @example Click_One_Wire_I2C_KIN.c
    @example Click_One_Wire_I2C_MSP.c
    @example Click_One_Wire_I2C_PIC.c
    @example Click_One_Wire_I2C_PIC32.c
    @example Click_One_Wire_I2C_DSPIC.c
    @example Click_One_Wire_I2C_AVR.c
    @example Click_One_Wire_I2C_FT90x.c
    @example Click_One_Wire_I2C_STM.mbas
    @example Click_One_Wire_I2C_TIVA.mbas
    @example Click_One_Wire_I2C_CEC.mbas
    @example Click_One_Wire_I2C_KIN.mbas
    @example Click_One_Wire_I2C_MSP.mbas
    @example Click_One_Wire_I2C_PIC.mbas
    @example Click_One_Wire_I2C_PIC32.mbas
    @example Click_One_Wire_I2C_DSPIC.mbas
    @example Click_One_Wire_I2C_AVR.mbas
    @example Click_One_Wire_I2C_FT90x.mbas
    @example Click_One_Wire_I2C_STM.mpas
    @example Click_One_Wire_I2C_TIVA.mpas
    @example Click_One_Wire_I2C_CEC.mpas
    @example Click_One_Wire_I2C_KIN.mpas
    @example Click_One_Wire_I2C_MSP.mpas
    @example Click_One_Wire_I2C_PIC.pas
    @example Click_One_Wire_I2C_PIC32.pas
    @example Click_One_Wire_I2C_DSPIC.pas
    @example Click_One_Wire_I2C_AVR.pas
    @example Click_One_Wire_I2C_FT90x.pas

*/
/* -------------------------------------------------------------------------- */


#ifndef _OWI2C_H_
#define _OWI2C_H_

#include <stdint.h>

/** @name                                       One_Wire_I2C Click Write Types
 *  @{                                          *///---------------------------

extern const uint8_t OWI2C_WRITE_NORMAL;
extern const uint8_t OWI2C_WRITE_NORMAL_NOSTOP;
extern const uint8_t OWI2C_WRITE_DATA_ONLY_WITHSTOP;
extern const uint8_t OWI2C_WRITE_DATA_ONLY_NOSTOP;

/// @}


#ifdef __cplusplus
extern "C"{
#endif

/** @name                                  One_Wire_I2C Click Driver Functions
 *  @{                               *///---------------------------------------

/*
 * Sets the port and pin to be used in One Wire communication.
 * This should be called before any other function.
 */
void OWI2C_pinSet (uint32_t * pOwPort, uint32_t owPin);


////////////////////////////////////////////////////////////////////////////////
/// ROM functions
////////////////////////////////////////////////////////////////////////////////

/*
 * Sends request for ROM on the One-wire line. There should be only one device
 * present at this moment to determine its unique ROM ID. If there are more
 * devices present, an error will occur. ROM is needed for further operation
 * with the device in any application that has more than one device on the
 * One-wire line.
 */
void OWI2C_readRom (uint8_t *pData);

/*
 * Sends a match ROM command on the One-Wire line. Only the device with the
 * sent ROM ID will respond to subsequent commands, until OW reset is sent.
 */
void OWI2C_matchRom (uint8_t *pData);

/*
 * Sends a skip ROM command on the One-Wire line. Subsequent commands will be
 * issued to all the devices on the line, so this should be used with care
 * (or when there is only one device present).
 */
void OWI2C_skipRom ();

/*
 * Sends a resume command on the One-Wire line. This will continue operation
 * with the device previously selected by a match ROM command. Will only work
 * if a device was previously selected.
 */
void OWI2C_resume ();

/*
 * Sends an overdrive skip ROM command on the One-Wire line. Subsequent 
 * commands will be issued to all the devices on the line, so this should be
 * used with care (or when there is only one device present).
 * This also sets all the devices that are capable into overdrive mode.
 */
void OWI2C_skipRomOverdrive ();

/*
 * Sends an overdrive match ROM command on the One-Wire line. Only the device 
 * with the sent ROM ID will respond to subsequent commands, until OW reset is 
 * sent. This will also set the selected device into overdrive mode.
 */
void OWI2C_matchRomOverdrive ( uint8_t *pData);


/*
 * Reads bytes from selected I2C address. Address parameter should be unshifted
 * as this function will autoshift i2c address, and add read bit.
 */
uint8_t OWI2C_readI2C ( uint8_t i2cAddress, uint8_t readLength, uint8_t *pData);

/*
 * Writes bytes using the mode selected by the command byte. In case of
 * data only writes, leave i2cAddress empty. In other cases, i2c address is
 * passed unshifted, and this function will shift it automatically.
 */
uint16_t OWI2C_writeI2C ( uint8_t commandByte, uint8_t i2cAddress,
                    uint8_t writeLength, uint8_t *pData);

/*
 * Sends a write+read command with required data.
 * pdata [0] - Device command (2D = write+read)
 * pdata [1] - I2C address - shifted, lsb=0
 * pdata [2] - Wr length - Number of bytes to write - Minimum 1
 * pdata [3] - pdata [wr Length+2 ] - Wr data
 * pdata [wr Length +3] - Read length
 * CRC is placed into last two bytes after calculation.
 *
 *
 * Read data is placed back into the pdata array, where first 2 bytes are
 * status bytes, and everything after that is read data.
 * pdata [0] - Status byte - Should be 0x00 if everything ok
 * pdata [1] - Write status byte - Should be 0x00 if everything ok
 * pdata [2] - pdata [Read Length+1 ] - Read bytes
 */
void OWI2C_transferI2C (char *pdata);


/// @}
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/// @}
/* -------------------------------------------------------------------------- */
/*
  __OWI2C_Driver.h

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