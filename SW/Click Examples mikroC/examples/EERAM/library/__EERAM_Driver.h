/*

    __EERAM_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __EERAM_Driver.h
@brief                         EERAM 5V Click
   
@mainpage  EERAM 5V Click
@{

### Device Description ###

    The Microchip Technology Inc.
    47L04/47C04/47L16/47C16 (47XXX) is a 4/16 Kbit
    SRAM with EEPROM backup. The device is organized
    as 512 x 8 bits or 2,048 x 8 bits of memory, and
    utilizes the I2C serial interface. The 47XXX provides
    infinite read and write cycles to the SRAM while
    EEPROM cells provide high-endurance nonvolatile
    storage of data.


### Features ###

    • 4 Kbit/16 Kbit SRAM with EEPROM Backup:
        - Internally organized as 512 x 8 bits (47X04)
        or 2,048 x 8 bits (47X16)
        - Automatic Store to EEPROM array upon
        power-down (using optional external
        capacitor)
        - Automatic Recall to SRAM array upon
        power-up
        - Hardware Store pin for manual Store
        operations
        - Software commands for initiating Store and
        Recall operations
        - Store time 8 ms maximum (47X04) or
        25 ms maximum (47X16)
    • Nonvolatile External Event Detect Flag
    • High Reliability:
        - Infinite read and write cycles to SRAM
        - More than one million store cycles to
        EEPROM
        - Data retention: >200 years
        - ESD protection: >4,000V

@}

@defgroup    EERAM
@brief       EERAM Click Driver
@{

    Global Library Prefix : **EERAM**
    Version               : **1.0.0**
    Date                  : Jun 2017
    Developer             : *Djordje Rosic*

    This library contains functions for EERAM click operation. It contains
    functions for reading and writing to SRAM, sending commands, and reading
    the status from the device.

/*----------------------------------------------------------------------------*/
/**
    @example Click_EERAM_ARM_STM.c
    @example Click_EERAM_ARM_TIVA.c
    @example Click_EERAM_ARM_CEC.c
    @example Click_EERAM_ARM_KIN.c
    @example Click_EERAM_ARM_MSP.c
    @example Click_EERAM_PIC.c
    @example Click_EERAM_PIC32.c
    @example Click_EERAM_DSPIC.c
    @example Click_EERAM_AVR.c
    @example Click_EERAM_FTDI.c
    @example Click_EERAM_ARM_STM.mbas
    @example Click_EERAM_ARM_TIVA.mbas
    @example Click_EERAM_ARM_CEC.mbas
    @example Click_EERAM_ARM_KIN.mbas
    @example Click_EERAM_ARM_MSP.mbas
    @example Click_EERAM_PIC.mbas
    @example Click_EERAM_PIC32.mbas
    @example Click_EERAM_DSPIC.mbas
    @example Click_EERAM_AVR.mbas
    @example Click_EERAM_FTDI.mbas
    @example Click_EERAM_ARM_STM.mpas
    @example Click_EERAM_ARM_TIVA.mpas
    @example Click_EERAM_ARM_CEC.mpas
    @example Click_EERAM_ARM_KIN.mpas
    @example Click_EERAM_ARM_MSP.mpas
    @example Click_EERAM_PIC.pas
    @example Click_EERAM_PIC32.pas
    @example Click_EERAM_DSPIC.pas
    @example Click_EERAM_AVR.pas
    @example Click_EERAM_FTDI.pas

*//*--------------------------------------------------------------------------*/

#ifndef _EERAM_H_
#define _EERAM_H_

#include <stdint.h>

/*-------------------------------------------------------------- HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

typedef unsigned int ( *T_EERAM_I2C_Start )();
typedef unsigned int ( *T_EERAM_I2C_Write )(unsigned char slave_address,
                                                    unsigned char *buffer, 
                                                    unsigned long count, 
                                                    unsigned long end_mode);
typedef void ( *T_EERAM_I2C_Read )(unsigned char slave_address,
                                           unsigned char *buffer,
                                           unsigned long count, 
                                           unsigned long end_mode);
    #elif defined( __MSP__ )

typedef unsigned int ( *T_EERAM_I2C_Write )(unsigned char slave_address,
                                                    unsigned char *buffer,
                                                    unsigned long count, 
                                                    unsigned long end_mode);

typedef void ( *T_EERAM_I2C_Read )(unsigned char slave_address,
                                           unsigned char *buffer, 
                                           unsigned long count, 
                                           unsigned long end_mode);

    #elif defined( __TI__ )

typedef void ( *T_EERAM_I2C_SetSlaveAddress )(char slave_address,
                                                      char dir);

typedef unsigned char ( *T_EERAM_I2C_Write )(unsigned char data_in,
                                                     unsigned char mode);
typedef unsigned char( *T_EERAM_I2C_Read )(unsigned char *data_out,
                                                   unsigned char mode);
    #endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )

typedef unsigned char( *T_EERAM_I2C_Start )();
typedef void  ( *T_EERAM_I2C_Stop )();
typedef void ( *T_EERAM_I2C_Close )();
typedef void ( *T_EERAM_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_EERAM_I2C_Read )(unsigned char ack);

#elif  defined( __MIKROC_PRO_FOR_PIC__ )

typedef unsigned char( *T_EERAM_I2C_Start )();
typedef void ( *T_EERAM_I2C_Stop )();
typedef void ( *T_EERAM_I2C_Restart )();
typedef unsigned char( *T_EERAM_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_EERAM_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

typedef unsigned int ( *T_EERAM_I2C_Idle )();
typedef unsigned int ( *T_EERAM_I2C_Start )();
typedef void ( *T_EERAM_I2C_Stop )();
typedef unsigned int ( *T_EERAM_I2C_Restart )();
typedef unsigned int ( *T_EERAM_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_EERAM_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )

typedef unsigned int ( *T_EERAM_I2C_Start )();
typedef void ( *T_EERAM_I2C_Stop )();
typedef void ( *T_EERAM_I2C_Restart )();
typedef unsigned int ( *T_EERAM_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_EERAM_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_8051__ )

typedef unsigned char( *T_EERAM_I2C_Start )();
typedef void ( *T_EERAM_I2C_Stop )();
typedef void ( *T_EERAM_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_EERAM_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void ( *T_EERAM_I2C_SetSlaveAddress )
                                                  (unsigned char slave_address);
typedef unsigned char ( *T_EERAM_I2C_Write )(unsigned char *buffer,
                                                     unsigned int count);
typedef unsigned char ( *T_EERAM_I2C_Read )(unsigned char *buffer,
                                                    unsigned int count);
#elif
typedef void ( *T_EERAM_I2C_Start )();
typedef void ( *T_EERAM_I2C_Stop )();
typedef void ( *T_EERAM_I2C_Write )(uint8_t input);
typedef uint8_t ( *T_EERAM_I2C_Read )(uint8_t input);
#endif
/*----------------------------------------------------------------------------*/

#if defined( __MCHP__ )
#define LOG UART1_Write_Text
#elif 1
#define LOG UART_Write_Text
#endif
/**
 * @name                 EERAM Click I2C Adresses
 *//*-------------------------------------------------------------------------*/
///@{


#define  _EERAM_ADDRESS_SRAM           0x50
#define  _EERAM_ADDRESS_CONTROL        0x18

/**
 * @name                 EERAM Click Commands
 *//*-------------------------------------------------------------------------*/
///@{

#define  _EERAM_CMD_STORE              0x33
#define  _EERAM_CMD_RECALL             0xDD


///@}
/**
 * @name                 EERAM Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

#define _EERAM_OK (0)
#define _EERAM_ERR (-1)

///@}
/**
 * @name                 EERAM Click Types
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name                 EERAM Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief EERAM Click Driver Initialization
 *
 * @param others            Function pointers
 *
 * Initialization of EERAM click driver.
 *
 * @note
 * This function must be called first.
 *
 */
void EERAM_initDriver
(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

        T_EERAM_I2C_Start funStarter,
        T_EERAM_I2C_Write funWriter, T_EERAM_I2C_Read funReader

    #elif defined( __MSP__ )

        T_EERAM_I2C_Write funWriter, T_EERAM_I2C_Read funReader

    #elif defined( __TI__ )

        T_EERAM_I2C_SetSlaveAddress funSlaveAddr,
        T_EERAM_I2C_Write funWriter, T_EERAM_I2C_Read funReader
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

       T_EERAM_I2C_Start funStarter, T_EERAM_I2C_Stop funStoper,
       T_EERAM_I2C_Write funWriter, T_EERAM_I2C_Read funReader

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

        T_EERAM_I2C_SetSlaveAddress funSlaveAddr,
        T_EERAM_I2C_Write funWriter, T_EERAM_I2C_Read funReader

#else
        T_EERAM_I2C_Start fpStart, T_EERAM_I2C_Stop fpStop,
        T_EERAM_I2C_Write fpWrite, T_EERAM_I2C_Read fpRead
#endif
);


/**
 * @brief EERAM Click Command Write
 *
 * @param command     Either _EERAM_CMD_STORE or _EERAM_CMD_RECALL
 *
 * Depending on the parameter, will either store the data from SRAM to EERAM,
 * or recall that data back to SRAM.
 */
void EERAM_command (uint8_t command);
/**
 * @brief EERAM Click Status Read
 *
 * @retval            Value of the Status register
 *
 * Returns the state of the status register.
 */
uint8_t EERAM_statusRead ();
/**
 * @brief EERAM Click Status Write
 *
 * @param command           Settings to be written to Status register
 *
 * Status register contains settings for write protection and auto-store
 * function. Use this function to configure them.
 */
void EERAM_statusWrite (uint8_t command);
/**
 * @brief EERAM Click SRAM Read
 *
 * @param addressH            SRAM address high
 * @param addressL            SRAM address low
 * @param pDataOut            Data buffer to be filled with read data
 * @param countOut            Number of bytes to read
 *
 * Reads the data from the selected SRAM address onwards.
 *
 */
void EERAM_read (uint8_t addressH, uint8_t addressL,
                 uint8_t * pDataOut, uint8_t countOut);
/**
 * @brief EERAM Click SRAM Write
 *
 * @param addressH            SRAM address high
 * @param addressL            SRAM address low
 * @param pDataIn             Write data
 * @param countIn             Number of bytes to write
 *
 * Writes the data to SRAM memory array.
 *
 */
void EERAM_write (uint8_t addressH, uint8_t addressL,
                 uint8_t * pDataIn, uint8_t countIn);


#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __EERAM_Driver.h

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