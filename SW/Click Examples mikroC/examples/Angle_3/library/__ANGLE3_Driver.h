/*

    __ANGLE3_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __ANGLE3_Driver.h
@brief                         Angle3 Click
   
@mainpage Angle3 Click
@{

### Device Description ###

    The AK7451 is a magnetic rotational angle sensor IC of Si monolithic with a
built-in Hall element, and easily achieve a non-contact rotation angle sensor in
combination with diametrically magnetized two pole magnet. By detecting the
magnetic field parallel vector to the IC package surface, the AK7451 outputs the
absolute angular position of the magnet, and the relative angular position.
    By transverse magnetic field detection method using a magnetic flux
concentrator, the AK7451 has excellent axial misalignment immunity.
    AK7451 is the Zero Latency rotation angle sensor to follow up to 20,000rpm
with the architecture of the tracking servo system, it is suitable to various
motor drive applications and an encoder applications.

@}

@defgroup    ANGLE3
@brief       Angle3 Click Driver
@{

    Global Library Prefix : **ANGLE3**
    Version               : **1.0.0**
    Date                  : 12.05.2017.
    Developer             : *Aleksandar Zecevic*

    This library contains functionalities for initializing Angle3 click and
communicating with it. Communication is done via an SPI interface. Data is sent
to and received from the click by commands consisting of three bytes.
    The first four bits represent the desired command. The next eight stand for
the address of data to read or write. The final twelve bits will either be data
to send to the click or data received from the click, depending on the command.
    Angle3 works in two modes: normal mode, in which the measured data can be
read at any time, and user mode, in which it is possible to write to regiters
and EEPROM locations. There are special commans for changing modes.
    The click contains several registers and an EEPROM, which can be read from
and written to, with certain limitations. The angle data itself is read with a
special command. All the operation codes, register and EEPROM addresses, and
modes are listed in this file.
    The ERR LED on the click will glow red when there is an error in the
measured data. This will happen due to there not being a strong magnetic field
at the sensor's location, indicating that no magnetic material is held close
enough to the sensor for the magnetic field to be measurable. The data read
at this time should not be considered valid.

/*----------------------------------------------------------------------------*/
/**
    @example Click_Angle3_ARM_STM.c
    @example Click_Angle3_ARM_TIVA.c
    @example Click_Angle3_ARM_CEC.c
    @example Click_Angle3_ARM_KIN.c
    @example Click_Angle3_ARM_MSP.c
    @example Click_Angle3_PIC.c
    @example Click_Angle3_PIC32.c
    @example Click_Angle3_DSPIC.c
    @example Click_Angle3_AVR.c
    @example Click_Angle3_FTDI.c
    @example Click_Angle3_ARM_STM.mbas
    @example Click_Angle3_ARM_TIVA.mbas
    @example Click_Angle3_ARM_CEC.mbas
    @example Click_Angle3_ARM_KIN.mbas
    @example Click_Angle3_ARM_MSP.mbas
    @example Click_Angle3_PIC.mbas
    @example Click_Angle3_PIC32.mbas
    @example Click_Angle3_DSPIC.mbas
    @example Click_Angle3_AVR.mbas
    @example Click_Angle3_FTDI.mbas
    @example Click_Angle3_ARM_STM.mpas
    @example Click_Angle3_ARM_TIVA.mpas
    @example Click_Angle3_ARM_CEC.mpas
    @example Click_Angle3_ARM_KIN.mpas
    @example Click_Angle3_ARM_MSP.mpas
    @example Click_Angle3_PIC.pas
    @example Click_Angle3_PIC32.pas
    @example Click_Angle3_DSPIC.pas
    @example Click_Angle3_AVR.pas
    @example Click_Angle3_FTDI.pas

*//*--------------------------------------------------------------------------*/

#ifndef _ANGLE3_H_
#define _ANGLE3_H_

#include <stdint.h>

/*-------------------------------------------------------------- HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )

typedef void ( *T_ANGLE3_SPI_Write )(unsigned int data_out);
typedef unsigned int ( *T_ANGLE3_SPI_Read )(unsigned int buffer);

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )

typedef void ( *T_ANGLE3_SPI_Write )(unsigned char data_out);
typedef unsigned char ( *T_ANGLE3_SPI_Read )(unsigned char dummy);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

typedef void ( *T_ANGLE3_SPI_Write )(unsigned long data_out);
typedef unsigned long( *T_ANGLE3_SPI_Read )(unsigned long dummy);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void ( *T_ANGLE3_SPI_Write )(unsigned char data_out);
typedef unsigned char ( *T_ANGLE3_SPI_Read )(unsigned char dummy);
#else
typedef void ( *T_ANGLE3_SPI_Write )(uint8_t input);
typedef uint8_t ( *T_ANGLE3_SPI_Read )(uint8_t input);
#endif
/*----------------------------------------------------------------------------*/

/**
 * @name                 Angle3 Click Command
 *//*-------------------------------------------------------------------------*/
///@{

#define _ANGLE3_WRITE_EEPROM    (0x01) /**< Write EEPROM Command */
#define _ANGLE3_READ_EEPROM     (0x02) /**< Read EEPROM Command */
#define _ANGLE3_WRITE_REGISTER  (0x03) /**< Write Register Command */
#define _ANGLE3_READ_REGISTER   (0x04) /**< Read Register Command */
#define _ANGLE3_CHANGE_MODE     (0x05) /**< Change Mode Command */
#define _ANGLE3_DATA_RENEW      (0x08) /**< Data Renew Command */
#define _ANGLE3_READ_ANGLE      (0x09) /**< Read Angle Data Command */

///@}
/**
 * @name                 Angle3 Click Registers
 *//*-------------------------------------------------------------------------*/
///@{

#define _ANGLE3_R_ANG           (0x00) /**< ANG Register Address */
#define _ANGLE3_R_MAG           (0x01) /**< MAG Register Address */
#define _ANGLE3_R_CHMD          (0x02) /**< CHMD Register Address */
#define _ANGLE3_R_ERRMON        (0x03) /**< ERRMON Register Address */
#define _ANGLE3_R_ZP            (0x06) /**< ZP Register Address */
#define _ANGLE3_R_RDABZ         (0x07) /**< RDABZ Register Address */
#define _ANGLE3_R_MLK           (0x08) /**< MLK Register Address */
#define _ANGLE3_R_EBDIS         (0x09) /**< EBDIS Register Address */
#define _ANGLE3_R_UVW           (0x0A) /**< UVW Register Address */

///@}
/**
 * @name                 Angle3 Click EEPROM locations
 *//*-------------------------------------------------------------------------*/
///@{

#define _ANGLE3_E_ID1           (0x04) /**< ID1 EEPROM Address */
#define _ANGLE3_E_ID2           (0x05) /**< ID2 EEPROM Address */
#define _ANGLE3_E_ZP            (0x06) /**< ZP EEPROM Address */
#define _ANGLE3_E_RDABZ         (0x07) /**< RDABZ EEPROM Address */
#define _ANGLE3_E_MLK           (0x08) /**< MLK EEPROM Address */
#define _ANGLE3_E_EBDIS         (0x09) /**< EBDIS EEPROM Address */
#define _ANGLE3_E_UVW           (0x0A) /**< UVW EEPROM Address */

///@}
/**
 * @name                 Angle3 Click Modes
 *//*-------------------------------------------------------------------------*/
///@{

#define _ANGLE3_NORMAL_MODE     (0x0000) /**< Normal Mode CHMD Value */
#define _ANGLE3_USER_MODE       (0x050F) /**< User Mode CHMD Value */

///@}
/**
 * @name                 Angle3 Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

#define _ANGLE3_OK  (1) /**< No Error */
#define _ANGLE3_ERR (0) /**< Error */

#define _ANGLE3_ERR_BITMASK (0x1000) /**< Bitmask for Error Bit in Angle Data */

///@}
/**
 * @name                 Angle3 Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Angle3 Driver Initialization
 *
 * @param[in] fnWrite   SPI Write Function
 * @param[in] fnRead    SPI Read Function
 *
 * Initialization of Angle 3 Click driver.
 *
 * @note
 * This function must be called first.
 */
void ANGLE3_initDriver(T_ANGLE3_SPI_Write fnWrite, T_ANGLE3_SPI_Read fnRead);

/**
 * @brief Angle3 Data Write
 *
 * @param[in] opcode Operation Code
 * @param[in] address Address of Data to Write
 * @param[in] _data Data to Write
 *
 * Writes given data to given address.
 *
 * @note This is a basic write function used by other specific functions.
 * When using this function be sure to provide a valid opcode.
 */
void ANGLE3_writeData(uint8_t opcode, uint8_t address, uint16_t _data);

/**
 * @brief Angle3 Data Read
 *
 * @param[in] opcode Operation Code
 * @param[in] address Address of Data to Read
 * @return Read Data
 *
 * Reads data from given address.
 *
 * @note This is a basic read function used by other specific functions.
 * When using this function be sure to provide a valid opcode.
 */
uint16_t ANGLE3_readData(uint8_t opcode, uint8_t address);

/**
 * @brief Angle3 EEPROM Write
 * @param[in] address Address in EEPROM to Write to
 * @param[in] _data Data to Write
 *
 * Writes given data to given address in EEPROM.
 *
 * @note You should only write to EEPROM before calling the lock function,
 * and provide only the valid EEPROM addresses.
 */
void ANGLE3_writeEEPROM(uint8_t address, uint16_t _data);

/**
 * @brief Angle3 EEPROM Read
 * @param[in] address Address in EEPROM to Read from
 * @return Read Data
 *
 * Reads data from given address in EEPROM.
 *
 * @note You should provide only the valid EEPROM addresses.
 */
uint16_t ANGLE3_readEEPROM(uint8_t address);

/**
 * @brief Angle3 EEPROM Lock
 *
 * Locks the EEPROM so that it cannot be written to until the next reset.
 *
 * @note After calling this routine it will be impossible to modify the EEPROM,
 * so all writes to it should be done before calling this.
 */
void ANGLE3_lockEEPROM();

/**
 * @brief Angle3 Register Write
 * @param[in] address Address of Register to Write to
 * @param[in] _data Data to Write
 *
 * Writes given data to Register at given address.
 *
 * @note You should only write to registers in user mode,
 * and provide only the valid registers addresses.
 */
void ANGLE3_writeRegister(uint8_t address, uint16_t _data);

/**
 * @brief Angle3 Register Read
 * @param[in] address Address of Register to Read from
 * @return Read Data
 *
 * Reads data from Register at given address.
 *
 * @note You should only read from registers in user mode,
 * and provide only the valid registers addresses.
 */
uint16_t ANGLE3_readRegister(uint8_t address);

/**
 * @brief Angle3 Mode Set
 *
 * @param mode Mode to Set Angle3 to
 *
 * Sets mode of Angle3 to the one provided.
 *
 * @note
 * The two valid modes are: normal with value 0x0000,
 * and user with value 0x050F.
 */
void ANGLE3_setMode(uint16_t mode);

/**
 * @brief Angle3 Normal Mode Set
 *
 * Sets mode of Angle3 to normal.
 */
void ANGLE3_setNormalMode();

/**
 * @brief Angle3 User Mode Set
 *
 * Sets mode of Angle3 to user.
 */
void ANGLE3_setUserMode();

/**
 * @brief Angle3 Angle Data Read
 * @return Read Angle Data
 *
 * Reads the latest angle output data.
 */
uint16_t ANGLE3_readAngleData();

/**
 * @brief Angle3 Degrees Calculation
 * @param[in] angle Angle to Convert to Degrees
 * @return Angle in Degrees
 *
 * Converts an angle value read from Angle3 to degrees.
 */
uint32_t ANGLE3_calculateDegrees(uint16_t angle);

/**
 * @brief Angle3 Error Pin Read
 * @retval _ANGLE3_OK No Error
 * @retval _ANGLE3_ERR Error
 *
 * Reads Angle3 error pin, connected to the INT pin on MikroBUS.
 * This pin is connected to the ERROR pin of the sensor,
 * so it can be used to check for errors in the current measurement.
 */
uint8_t ANGLE3_readErrorPin();

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __Angle3_Driver.h

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