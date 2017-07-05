/*

    __C4DOT_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __C4DOT_Driver.h
@brief                         4DotMatrix Click
   
@mainpage 4DotMatrix Click
@{

### Device Description ###

    The SLR/SLO/SLG/SLY2016 is a four digit 5 x 7 dot matrix display module with
a built-in CMOS integrated circuit. This display is X/Y stackable.
    The integrated circuit contains memory, a 128 ASCII ROM decoder,multiplexing
circuitry and drivers. Data entry is asynchronous. A display system can be built
using any number of SLR/SLO/SLG/SLY2016 since each digit can be addressed
independently and will continue to display the character last stored until
replaced by another.

@}

@defgroup    C4DOT
@brief       4DotMatrix Click Driver
@{

    Global Library Prefix : **C4DOT**
    Version               : **1.0.0**
    Date                  : 07.06.2017.
    Developer             : *Aleksandar Zecevic*

    This library contains functionalities for initializing 4DotMatrix click and
communicating with it. Communication is done with an MCP23017 16 bit I/O
expander via I2C communication. MCP23017 directly communicates with an SLx2016
display to show the characters.
    All the functions work in a similar fashion, in that they send a character,
or several of them, to be displayed. It is possible to send single characters
on any of the four display positions, a string of characters, or integers in any
numeral system.
    C4DOT_BL_PIN should be either set to high, or should be connected to a PWM
module, in which case it would be possible to blink the display or change its
intensity.

/*----------------------------------------------------------------------------*/
/**
    @example Click_4DotMatrix_ARM_STM.c
    @example Click_4DotMatrix_ARM_TIVA.c
    @example Click_4DotMatrix_ARM_CEC.c
    @example Click_4DotMatrix_ARM_KIN.c
    @example Click_4DotMatrix_ARM_MSP.c
    @example Click_4DotMatrix_PIC.c
    @example Click_4DotMatrix_PIC32.c
    @example Click_4DotMatrix_DSPIC.c
    @example Click_4DotMatrix_AVR.c
    @example Click_4DotMatrix_FTDI.c
    @example Click_4DotMatrix_ARM_STM.mbas
    @example Click_4DotMatrix_ARM_TIVA.mbas
    @example Click_4DotMatrix_ARM_CEC.mbas
    @example Click_4DotMatrix_ARM_KIN.mbas
    @example Click_4DotMatrix_ARM_MSP.mbas
    @example Click_4DotMatrix_PIC.mbas
    @example Click_4DotMatrix_PIC32.mbas
    @example Click_4DotMatrix_DSPIC.mbas
    @example Click_4DotMatrix_AVR.mbas
    @example Click_4DotMatrix_FTDI.mbas
    @example Click_4DotMatrix_ARM_STM.mpas
    @example Click_4DotMatrix_ARM_TIVA.mpas
    @example Click_4DotMatrix_ARM_CEC.mpas
    @example Click_4DotMatrix_ARM_KIN.mpas
    @example Click_4DotMatrix_ARM_MSP.mpas
    @example Click_4DotMatrix_PIC.pas
    @example Click_4DotMatrix_PIC32.pas
    @example Click_4DotMatrix_DSPIC.pas
    @example Click_4DotMatrix_AVR.pas
    @example Click_4DotMatrix_FTDI.pas

*//*--------------------------------------------------------------------------*/

#ifndef _C4DOT_H_
#define _C4DOT_H_

#include <stdint.h>

/*-------------------------------------------------------------- HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

typedef unsigned int ( *T_C4DOT_I2C_Start )();
typedef unsigned int ( *T_C4DOT_I2C_Write )(unsigned char slave_address,
                                                    unsigned char *buffer, 
                                                    unsigned long count, 
                                                    unsigned long end_mode);
typedef void ( *T_C4DOT_I2C_Read )(unsigned char slave_address, 
                                           unsigned char *buffer,
                                           unsigned long count, 
                                           unsigned long end_mode);
    #elif defined( __MSP__ )

typedef unsigned int ( *T_C4DOT_I2C_Write )(unsigned char slave_address,
                                                    unsigned char *buffer,
                                                    unsigned long count, 
                                                    unsigned long end_mode);

typedef void ( *T_C4DOT_I2C_Read )(unsigned char slave_address, 
                                           unsigned char *buffer, 
                                           unsigned long count, 
                                           unsigned long end_mode);

    #elif defined( __TI__ )

typedef void ( *T_C4DOT_I2C_SetSlaveAddress )(char slave_address,
                                                      char dir);

typedef unsigned char ( *T_C4DOT_I2C_Write )(unsigned char data_in, 
                                                     unsigned char mode);
typedef unsigned char( *T_C4DOT_I2C_Read )(unsigned char *data_out, 
                                                   unsigned char mode);
    #endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )

typedef unsigned char( *T_C4DOT_I2C_Start )();
typedef void  ( *T_C4DOT_I2C_Stop )();
typedef void ( *T_C4DOT_I2C_Close )();
typedef void ( *T_C4DOT_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_C4DOT_I2C_Read )(unsigned char ack);

#elif  defined( __MIKROC_PRO_FOR_PIC__ )

typedef unsigned char( *T_C4DOT_I2C_Start )();
typedef void ( *T_C4DOT_I2C_Stop )();
typedef void ( *T_C4DOT_I2C_Restart )();
typedef unsigned char( *T_C4DOT_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_C4DOT_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

typedef unsigned int ( *T_C4DOT_I2C_Idle )();
typedef unsigned int ( *T_C4DOT_I2C_Start )();
typedef void ( *T_C4DOT_I2C_Stop )();
typedef unsigned int ( *T_C4DOT_I2C_Restart )();
typedef unsigned int ( *T_C4DOT_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_C4DOT_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )

typedef unsigned int ( *T_C4DOT_I2C_Start )();
typedef void ( *T_C4DOT_I2C_Stop )();
typedef void ( *T_C4DOT_I2C_Restart )();
typedef unsigned int ( *T_C4DOT_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_C4DOT_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_8051__ )

typedef unsigned char( *T_C4DOT_I2C_Start )();
typedef void ( *T_C4DOT_I2C_Stop )();
typedef void ( *T_C4DOT_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_C4DOT_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void ( *T_C4DOT_I2C_SetSlaveAddress )
                                                  (unsigned char slave_address);
typedef unsigned char ( *T_C4DOT_I2C_Write )(unsigned char *buffer, 
                                                     unsigned int count);
typedef unsigned char ( *T_C4DOT_I2C_Read )(unsigned char *buffer, 
                                                    unsigned int count);
#elif
typedef void ( *T_C4DOT_I2C_Start )();
typedef void ( *T_C4DOT_I2C_Stop )();
typedef void ( *T_C4DOT_I2C_Write )(uint8_t input);
typedef uint8_t ( *T_C4DOT_I2C_Read )(uint8_t input);
#endif
/*----------------------------------------------------------------------------*/

/**
 * @name                 4DotMatrix Click Registers
 *//*-------------------------------------------------------------------------*/
///@{

#define _C4DOT_I2C_ADDRESS 0x20

///@}
/**
 * @name                 4DotMatrix Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name                 4DotMatrix Click Types
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name                 4DotMatrix Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief 4DotMatrix Click Driver Initialization
 *
 * @param[in] I2C_Address   Slave I2C Address
 * @param others            Function pointers
 *
 * Initialization of 4DotMatrix click driver.
 *
 * @note
 * This function must be called first.
 *
 */
void C4DOT_initDriver
(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

        uint8_t I2C_Address, T_C4DOT_I2C_Start funStarter,
        T_C4DOT_I2C_Write funWriter, T_C4DOT_I2C_Read funReader

    #elif defined( __MSP__ )

        uint8_t I2C_Address,
        T_C4DOT_I2C_Write funWriter, T_C4DOT_I2C_Read funReader

    #elif defined( __TI__ )

        uint8_t I2C_Address, T_C4DOT_I2C_SetSlaveAddress funSlaveAddr,
        T_C4DOT_I2C_Write funWriter, T_C4DOT_I2C_Read funReader
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

       uint8_t I2C_Address,
       T_C4DOT_I2C_Start funStarter, T_C4DOT_I2C_Stop funStoper,
       T_C4DOT_I2C_Write funWriter, T_C4DOT_I2C_Read funReader

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

        uint8_t I2C_Address, T_C4DOT_I2C_SetSlaveAddress funSlaveAddr,
        T_C4DOT_I2C_Write funWriter, T_C4DOT_I2C_Read funReader

#else
        uint8_t slaveAddress,
        T_C4DOT_I2C_Start fpStart, T_C4DOT_I2C_Stop fpStop,
        T_C4DOT_I2C_Write fpWrite, T_C4DOT_I2C_Read fpRead
#endif
);

/**
 * @brief 4DotMatrix Char Write
 *
 * @param[in] charNum Number of char to write
 * @param[in] charValue Value to write to char
 *
 * Writes charValue to the character on the position of charNum.
 * 0 is the rightmost character, and 3 is the leftmost one.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 *
 * @note 
 * Function will do nothing in case of bad charNum or charValue.
 */
void C4DOT_writeChar(uint8_t charNum, uint8_t charValue);

/**
 * @brief 4DotMatrix Char 0 Write
 *
 * @param[in] charValue Value to write to char 0
 *
 * Writes charValue to character 0, the rightmost character.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 *
 * @note 
 * Function will do nothing in case of bad charValue.
 */
void C4DOT_writeChar0(uint8_t charValue);

/**
 * @brief 4DotMatrix Char 1 Write
 *
 * @param[in] charValue Value to 2rite to char 1
 *
 * Writes charValue to character 1, the second character from the right.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 *
 * @note 
 * Function will do nothing in case of bad charValue.
 */
void C4DOT_writeChar1(uint8_t charValue);

/**
 * @brief 4DotMatrix Char 2 Write
 *
 * @param[in] charValue Value to write to char 2
 *
 * Writes charValue to character 2, the second character from the left.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 *
 * @note 
 * Function will do nothing in case of bad charValue.
 */
void C4DOT_writeChar2(uint8_t charValue);

/**
 * @brief 4DotMatrix Char 3 Write
 *
 * @param[in] charValue Value to write to char 3
 *
 * Writes charValue to character 3, the leftmost character.
 * Character value can go from 0 to 127. Values in the range from 32 to 126
 * represent the corresponding ASCII characters. Refer to the OSRAM SLx2016
 * datasheet for a complete list of character values that can be written.
 *
 * @note 
 * Function will do nothing in case of bad charValue.
 */
void C4DOT_writeChar3(uint8_t charValue);

/**
 * @brief 4DotMatrix Text Write
 *
 * @param[in] textToWrite Text to write to character display
 *
 * Writes up to four characters from textToWrite to the display characters.
 */
void C4DOT_writeText(uint8_t *textToWrite);

/**
 * @brief 4DotMatrix Int Write
 *
 * @param[in] intToWrite Integer to write to character display
 * @param[in] intBase Numeral system base
 *
 * Writes intToWrite to the character display,
 * where intBase is the base of the number's numeral system.
 * Obviously, only the lowest four digits will be shown.
 * If the given number is negative, '-' will be shown if there is space left.
 */
void C4DOT_writeInt(int32_t intToWrite, uint8_t intBase);

/**
 * @brieaf 4DotMatrix Binary Int Write
 *
 * @param[in] intToWrite Integer to write to character display
 *
 * Writes intToWrite as a binary integer to the character display.
 * Obviously, only the lowest four digits will be shown.
 * If the given number is negative, '-' will be shown if there is space left.
 */
void C4DOT_writeIntBin(int32_t intToWrite);

/**
 * @brieaf 4DotMatrix Octal Int Write
 *
 * @param[in] intToWrite Integer to write to character display
 *
 * Writes intToWrite as an octal integer to the character display.
 * Obviously, only the lowest four digits will be shown.
 * If the given number is negative, '-' will be shown if there is space left.
 */
void C4DOT_writeIntOct(int32_t intToWrite);

/**
 * @brieaf 4DotMatrix Decimal Int Write
 *
 * @param[in] intToWrite Integer to write to character display
 *
 * Writes intToWrite as a decimal integer to the character display.
 * Obviously, only the lowest four digits will be shown.
 * If the given number is negative, '-' will be shown if there is space left.
 */
void C4DOT_writeIntDec(int32_t intToWrite);

/**
 * @brieaf 4DotMatrix Hexadecimal Int Write
 *
 * @param[in] intToWrite Integer to write to character display
 *
 * Writes intToWrite as a hexadecimal integer to the character display.
 * Obviously, only the lowest four digits will be shown.
 * If the given number is negative, '-' will be shown if there is space left.
 */
void C4DOT_writeIntHex(int32_t intToWrite);

/**
 * @brief 4DotMatrix Display Clear
 *
 * Clears all four display characters.
 */
void C4DOT_clearDisplay();

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __C4DOT_Driver.h

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