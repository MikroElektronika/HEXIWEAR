/*

    __IRGRID2_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __IRGRID2_Driver.h
@brief                         IR Grid 2 Click
   
@mainpage IR Grid 2 Click
@{

### Device Description ###

    The AK9750 is an ultra-low power and compact infrared-ray (IR) sensor
    module. It is composed of four quantum IR sensors and an integrated circuit 
    (IC) for characteristic compensation. The four IR sensors’ offset and gain
    variations are calibrated at shipment. An integral analog-to-digital 
    converter provides 16-bits data outputs. Additional integrated features
    include a field of view limiter and an optical filter. The AK9750 is 
    suitable for applications including stationary human detection.


### Features ###

    - Quantum-type IR Sensor with Four IR Elements
    - 16-bits Digital Outputs to I2C bus
    - Integrated temperature sensor: -10 ~ 60ºC output on I2C bus
    - Interrupt Function

@}

@defgroup    IRGRID2
@brief       IR Grid 2 Click Driver
@{

    Global Library Prefix : **IRGRID2**
    Version               : **1.0.0**
    Date                  : May 2017
    Developer             : *Djordje Rosic*

    This library contains functions for IR grid 2 click.

/*----------------------------------------------------------------------------*/
/**
    @example Click_IR_Grid_2_ARM_STM.c
    @example Click_IR_Grid_2_ARM_TIVA.c
    @example Click_IR_Grid_2_ARM_CEC.c
    @example Click_IR_Grid_2_ARM_KIN.c
    @example Click_IR_Grid_2_ARM_MSP.c
    @example Click_IR_Grid_2_PIC.c
    @example Click_IR_Grid_2_PIC32.c
    @example Click_IR_Grid_2_DSPIC.c
    @example Click_IR_Grid_2_AVR.c
    @example Click_IR_Grid_2_FTDI.c
    @example Click_IR_Grid_2_ARM_STM.mbas
    @example Click_IR_Grid_2_ARM_TIVA.mbas
    @example Click_IR_Grid_2_ARM_CEC.mbas
    @example Click_IR_Grid_2_ARM_KIN.mbas
    @example Click_IR_Grid_2_ARM_MSP.mbas
    @example Click_IR_Grid_2_PIC.mbas
    @example Click_IR_Grid_2_PIC32.mbas
    @example Click_IR_Grid_2_DSPIC.mbas
    @example Click_IR_Grid_2_AVR.mbas
    @example Click_IR_Grid_2_FTDI.mbas
    @example Click_IR_Grid_2_ARM_STM.mpas
    @example Click_IR_Grid_2_ARM_TIVA.mpas
    @example Click_IR_Grid_2_ARM_CEC.mpas
    @example Click_IR_Grid_2_ARM_KIN.mpas
    @example Click_IR_Grid_2_ARM_MSP.mpas
    @example Click_IR_Grid_2_PIC.pas
    @example Click_IR_Grid_2_PIC32.pas
    @example Click_IR_Grid_2_DSPIC.pas
    @example Click_IR_Grid_2_AVR.pas
    @example Click_IR_Grid_2_FTDI.pas

*//*--------------------------------------------------------------------------*/

#ifndef _IRGRID2_H_
#define _IRGRID2_H_

#include <stdint.h>

/*-------------------------------------------------------------- HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

typedef unsigned int ( *T_IRGRID2_I2C_Start )();
typedef unsigned int ( *T_IRGRID2_I2C_Write )(unsigned char slave_address,
                                                    unsigned char *buffer, 
                                                    unsigned long count, 
                                                    unsigned long end_mode);
typedef void ( *T_IRGRID2_I2C_Read )(unsigned char slave_address,
                                           unsigned char *buffer,
                                           unsigned long count, 
                                           unsigned long end_mode);
    #elif defined( __MSP__ )

typedef unsigned int ( *T_IRGRID2_I2C_Write )(unsigned char slave_address,
                                                    unsigned char *buffer,
                                                    unsigned long count, 
                                                    unsigned long end_mode);

typedef void ( *T_IRGRID2_I2C_Read )(unsigned char slave_address,
                                           unsigned char *buffer, 
                                           unsigned long count, 
                                           unsigned long end_mode);

    #elif defined( __TI__ )

typedef void ( *T_IRGRID2_I2C_SetSlaveAddress )(char slave_address,
                                                      char dir);

typedef unsigned char ( *T_IRGRID2_I2C_Write )(unsigned char data_in,
                                                     unsigned char mode);
typedef unsigned char( *T_IRGRID2_I2C_Read )(unsigned char *data_out,
                                                   unsigned char mode);
    #endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )

typedef unsigned char( *T_IRGRID2_I2C_Start )();
typedef void  ( *T_IRGRID2_I2C_Stop )();
typedef void ( *T_IRGRID2_I2C_Close )();
typedef void ( *T_IRGRID2_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_IRGRID2_I2C_Read )(unsigned char ack);

#elif  defined( __MIKROC_PRO_FOR_PIC__ )

typedef unsigned char( *T_IRGRID2_I2C_Start )();
typedef void ( *T_IRGRID2_I2C_Stop )();
typedef void ( *T_IRGRID2_I2C_Restart )();
typedef unsigned char( *T_IRGRID2_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_IRGRID2_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

typedef unsigned int ( *T_IRGRID2_I2C_Idle )();
typedef unsigned int ( *T_IRGRID2_I2C_Start )();
typedef void ( *T_IRGRID2_I2C_Stop )();
typedef unsigned int ( *T_IRGRID2_I2C_Restart )();
typedef unsigned int ( *T_IRGRID2_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_IRGRID2_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )

typedef unsigned int ( *T_IRGRID2_I2C_Start )();
typedef void ( *T_IRGRID2_I2C_Stop )();
typedef void ( *T_IRGRID2_I2C_Restart )();
typedef unsigned int ( *T_IRGRID2_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_IRGRID2_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_8051__ )

typedef unsigned char( *T_IRGRID2_I2C_Start )();
typedef void ( *T_IRGRID2_I2C_Stop )();
typedef void ( *T_IRGRID2_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_IRGRID2_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void ( *T_IRGRID2_I2C_SetSlaveAddress )
                                                  (unsigned char slave_address);
typedef unsigned char ( *T_IRGRID2_I2C_Write )(unsigned char *buffer,
                                                     unsigned int count);
typedef unsigned char ( *T_IRGRID2_I2C_Read )(unsigned char *buffer,
                                                    unsigned int count);
#elif
typedef void ( *T_IRGRID2_I2C_Start )();
typedef void ( *T_IRGRID2_I2C_Stop )();
typedef void ( *T_IRGRID2_I2C_Write )(uint8_t input);
typedef uint8_t ( *T_IRGRID2_I2C_Read )(uint8_t input);
#endif
/*----------------------------------------------------------------------------*/

/**
 * @name                 IR Grid 2 Click Registers
 *//*-------------------------------------------------------------------------*/
///@{

//Read Registers
#define _IRGRID2_INT_STATUS            0x04
#define _IRGRID2_STATUS1               0x05
#define _IRGRID2_IR1DATAL              0x06
#define _IRGRID2_IR1DATAH              0x07
#define _IRGRID2_IR2DATAL              0x08
#define _IRGRID2_IR2DATAH              0x09
#define _IRGRID2_IR3DATAL              0x0A
#define _IRGRID2_IR3DATAH              0x0B
#define _IRGRID2_IR4DATAL              0x0C
#define _IRGRID2_IR4DATAH              0x0D
#define _IRGRID2_TEMPERATUREL          0x0E
#define _IRGRID2_TEMPERATUREH          0x0F
#define _IRGRID2_STATUS2               0x10

//Threshold levels
#define _IRGRID2_THRLVL_IR13_UL        0x11
#define _IRGRID2_THRLVL_IR13_UH        0x12
#define _IRGRID2_THRLVL_IR13_LL        0x13
#define _IRGRID2_THRLVL_IR13_LH        0x14
#define _IRGRID2_THRLVL_IR24_UL        0x15
#define _IRGRID2_THRLVL_IR24_UH        0x16
#define _IRGRID2_THRLVL_IR24_LL        0x17
#define _IRGRID2_THRLVL_IR24_LH        0x18
//Hysteresis
#define _IRGRID2_HYST_IR13             0x19
#define _IRGRID2_HYST_IR24             0x1A
//Setting registers
#define _IRGRID2_INT_SETTING           0x1B
#define _IRGRID2_MODE_SETTING          0x1C
#define _IRGRID2_RESET                 0x1D

/**
 * @name                 IR Grid 2 Config Register Values
 *//*-------------------------------------------------------------------------*/
///@{

//Interrupts Enable
#define _IRGRID2_INT_DATARDY          0x01
#define _IRGRID2_INT_IR24LI           0x02
#define _IRGRID2_INT_IR24HI           0x04
#define _IRGRID2_INT_IR13LI           0x08
#define _IRGRID2_INT_IR13HI           0x10

//Mode Setting
#define _IRGRID2_MODE_STANDBY         0x00
#define _IRGRID2_MODE_EEPROM          0x41
#define _IRGRID2_MODE_SINGLESHOT      0x02
#define _IRGRID2_MODE_CONT0           0x04
#define _IRGRID2_MODE_CONT1           0x05
#define _IRGRID2_MODE_CONT2           0x06
#define _IRGRID2_MODE_CONT3           0x07

//Digital Filter Cutoff Frequency Setting
#define _IRGRID2_EFC_0300mHZ         0x00
#define _IRGRID2_EFC_0600mHZ         0x08
#define _IRGRID2_EFC_1100mHZ         0x10
#define _IRGRID2_EFC_2200mHZ         0x18
#define _IRGRID2_EFC_4400mHZ         0x20
#define _IRGRID2_EFC_8800mHZ         0x28

#define _IRGRID2_CMD_RESET          0x01

///@}
/**
 * @name                 IR Grid 2 Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

#define _IRGRID2_OK (0)
#define _IRGRID2_ERR (-1)

///@}
/**
 * @name                 IR Grid 2 Click Types
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name                 IR Grid 2 Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief IR Grid 2 Click Driver Initialization
 *
 * @param[in] I2C_Address   Slave I2C Address
 * @param others            Function pointers
 *
 * Initialization of IR Grid 2 click driver.
 *
 * @note
 * This function must be called first.
 * This function will also perform a soft reset of the device.
 */
void IRGRID2_initDriver
(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

        uint8_t I2C_Address, T_IRGRID2_I2C_Start funStarter,
        T_IRGRID2_I2C_Write funWriter, T_IRGRID2_I2C_Read funReader

    #elif defined( __MSP__ )

        uint8_t I2C_Address,
        T_IRGRID2_I2C_Write funWriter, T_IRGRID2_I2C_Read funReader

    #elif defined( __TI__ )

        uint8_t I2C_Address, T_IRGRID2_I2C_SetSlaveAddress funSlaveAddr,
        T_IRGRID2_I2C_Write funWriter, T_IRGRID2_I2C_Read funReader
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

       uint8_t I2C_Address,
       T_IRGRID2_I2C_Start funStarter, T_IRGRID2_I2C_Stop funStoper,
       T_IRGRID2_I2C_Write funWriter, T_IRGRID2_I2C_Read funReader

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

        uint8_t I2C_Address, T_IRGRID2_I2C_SetSlaveAddress funSlaveAddr,
        T_IRGRID2_I2C_Write funWriter, T_IRGRID2_I2C_Read funReader

#else
        uint8_t slaveAddress,
        T_IRGRID2_I2C_Start fpStart, T_IRGRID2_I2C_Stop fpStop,
        T_IRGRID2_I2C_Write fpWrite, T_IRGRID2_I2C_Read fpRead
#endif
);

/**
 * @brief IR Grid 2 Click Configuration Setting
 *
 * @param[in] registerAddress   address of the register to write to
 * @param[in] registerValue   data to be written
 *
 * Used for writing data into configuration registers of the device. Will
 * send the 2 bytes of data passed to it via I2C.
 *
 */
void IRGRID2_setConfig (uint8_t registerAddress, uint8_t registerValue );


/**
 * @brief IR Grid 2 Click Read Single Register
 *
 * @param[in] registerAddress   address of the register to read from
 *
 * Reads the data from a single register with a passed address. If address in
 * question is one of the registers containing sensor readings, will also read
 * STATUS 1 and STATUS 2 registers, as required.
 *
 */
uint8_t IRGRID2_readSingle (uint8_t registerAddress);

/**
 * @brief IR Grid 2 Click Read All Data Registers
 *
 * @param[out] pDataOut   array of sensor readings values
 *
 * Will read all the registers containing sensor readings, and pass the array
 * filled with data. Note that first and last ( [0] and [11] ) elements are
 * STATUS 1 and STATUS 2 bytes that must also be read, so elements 1 - 10
 * contain data.
 *
 * @note
 * This function must be called first.
 *
 */
void IRGRID2_readAll (uint8_t *pDataOut);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __IRGRID2_Driver.h

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