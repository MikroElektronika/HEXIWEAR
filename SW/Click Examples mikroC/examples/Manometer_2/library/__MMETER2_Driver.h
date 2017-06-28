/*

    __MMETER2_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.
    
------------------------------------------------------------------------------*/

/**
 * @file                                            __MMETER2_Driver.h
 * @brief                     Manometer 2 Click
 *
 * @defgroup MMETER2
 * @brief                   Manometer 2 Click Driver
 *
 * Global Library Prefix : **MMETER2**
 *
 * @mainpage Manometer 2 Click
 *
 * @{
 *
 * ![MMETER2](../../Manometer_2_Click.png)
 *
 * ### Device Description ###
 *
 * The MS5525DSO is a new generation of Digital Small Outline
 * pressure sensors from MEAS with SPI and I2C bus interface
 * designed for high volume OEM users. The sensor module
 * includes a pressure sensor and an ultra low power 24-bit ?S
 * ADC with internal factory calibrated coefficients. It provides a
 * 24-bit digital pressure and temperature value and different
 * operation modes that allow the user to optimize for conversion
 * speed and current consumption.
 *
 *
 * ### Features ###
 *
 *      - Small Outline IC Package
 *      - Barbed Pressure Ports
 *      - Low Power, High Resolution ADC
 *      - Digital Pressure and Temperature Outputs
 *
 * @}
 *
 * @example Manometer_2_Click_ARM_STM.c
 * @example Manometer_2_Click_ARM_TIVA.c
 * @example Manometer_2_Click_ARM_CEC.c
 * @example Manometer_2_Click_ARM_KIN.c
 * @example Manometer_2_Click_ARM_MSP.c
 * @example Manometer_2_Click_PIC.c
 * @example Manometer_2_Click_PIC32.c
 * @example Manometer_2_Click_DSPIC.c
 * @example Manometer_2_Click_AVR.c
 * @example Manometer_2_Click_FTDI.c
 * @example Manometer_2_Click_ARM_STM.mbas
 * @example Manometer_2_Click_ARM_TIVA.mbas
 * @example Manometer_2_Click_ARM_CEC.mbas
 * @example Manometer_2_Click_ARM_KIN.mbas
 * @example Manometer_2_Click_ARM_MSP.mbas
 * @example Manometer_2_Click_PIC.mbas
 * @example Manometer_2_Click_PIC32.mbas
 * @example Manometer_2_Click_DSPIC.mbas
 * @example Manometer_2_Click_AVR.mbas
 * @example Manometer_2_Click_FTDI.mbas
 * @example Manometer_2_Click_ARM_STM.mpas
 * @example Manometer_2_Click_ARM_TIVA.mpas
 * @example Manometer_2_Click_ARM_CEC.mpas
 * @example Manometer_2_Click_ARM_KIN.mpas
 * @example Manometer_2_Click_ARM_MSP.mpas
 * @example Manometer_2_Click_PIC.pas
 * @example Manometer_2_Click_PIC32.pas
 * @example Manometer_2_Click_DSPIC.pas
 * @example Manometer_2_Click_AVR.pas
 * @example Manometer_2_Click_FTDI.pas
 *
 ******************************************************************************/

#ifndef _MMETER2_H_
#define _MMETER2_H_

#include <stdint.h>

/*-------------------------- HAL POINTERS ------------------------------------*/

#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
typedef unsigned int ( *T_MMETER2_I2C_Start )();
typedef unsigned int ( *T_MMETER2_I2C_Write )(unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode);
typedef void ( *T_MMETER2_I2C_Read )(unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode);
    #elif defined( __MSP__ )
typedef unsigned int ( *T_MMETER2_I2C_Write )(unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode);
typedef void ( *T_MMETER2_I2C_Read )(unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode);
    #elif defined( __TI__ )
typedef void ( *T_MMETER2_I2C_SetSlaveAddress )(char slave_address, char dir);
typedef unsigned char ( *T_MMETER2_I2C_Write )(unsigned char data_in, unsigned char mode);
typedef unsigned char( *T_MMETER2_I2C_Read )(unsigned char *data_out, unsigned char mode);
    #endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )
typedef unsigned char( *T_MMETER2_I2C_Start )();
typedef void  ( *T_MMETER2_I2C_Stop )();
typedef void ( *T_MMETER2_I2C_Close )();
typedef void ( *T_MMETER2_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_MMETER2_I2C_Read )(unsigned char ack);

#elif  defined( __MIKROC_PRO_FOR_PIC__ )
typedef unsigned char( *T_MMETER2_I2C_Start )();
typedef void ( *T_MMETER2_I2C_Stop )();
typedef void ( *T_MMETER2_I2C_Restart )();
typedef unsigned char( *T_MMETER2_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_MMETER2_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
typedef unsigned int ( *T_MMETER2_I2C_Idle )();
typedef unsigned int ( *T_MMETER2_I2C_Start )();
typedef void ( *T_MMETER2_I2C_Stop )();
typedef unsigned int ( *T_MMETER2_I2C_Restart )();
typedef unsigned int ( *T_MMETER2_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_MMETER2_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )
typedef unsigned int ( *T_MMETER2_I2C_Start )();
typedef void ( *T_MMETER2_I2C_Stop )();
typedef void ( *T_MMETER2_I2C_Restart )();
typedef unsigned int ( *T_MMETER2_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_MMETER2_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_8051__ )
typedef unsigned char( *T_MMETER2_I2C_Start )();
typedef void ( *T_MMETER2_I2C_Stop )();
typedef void ( *T_MMETER2_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_MMETER2_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
typedef void ( *T_MMETER2_I2C_SetSlaveAddress )(unsigned char slave_address);
typedef unsigned char ( *T_MMETER2_I2C_Write )(unsigned char *buffer, unsigned int count);
typedef unsigned char ( *T_MMETER2_I2C_Read )(unsigned char *buffer, unsigned int count);
#elif
typedef void ( *T_MMETER2_I2C_Start )();
typedef void ( *T_MMETER2_I2C_Stop )();
typedef void ( *T_MMETER2_I2C_Write )(uint8_t input);
typedef uint8_t ( *T_MMETER2_I2C_Read )(uint8_t input);
#endif

/*----------------------------------------------------------------------------*/

/**
 * @name 		Manometer 2 Click Commands
 ******************************************************************************/
///@{

#define RESET            0x1E
#define ADC_READ         0x00
#define D1_CONVERT_256   0x40
#define D1_CONVERT_512   0x42
#define D1_CONVERT_1024  0x44
#define D1_CONVERT_2048  0x46
#define D1_CONVERT_4096  0x48
#define D2_CONVERT_256   0x50
#define D2_CONVERT_512   0x52
#define D2_CONVERT_1024  0x54
#define D2_CONVERT_2048  0x56
#define D2_CONVERT_4096  0x58
#define C1_READ          0xA2
#define C2_READ          0xA4
#define C3_READ          0xA6
#define C4_READ          0xA8
#define C5_READ          0xAA
#define C6_READ          0xAC

/**
 * @name 		Manometer 2 Click Oversampling Ratio Commands
 ******************************************************************************/
///@{

#define CONVERT_256    0
#define CONVERT_512    1
#define CONVERT_1024   2
#define CONVERT_2048   3
#define CONVERT_4096   4

/**
 * @name 		Manometer 2 Click Return Values
 ******************************************************************************/
///@{

#define _MMETER2_OK			(0)
#define _MMETER2_ERR			(-1)

///@}
/**
 * @name 		Manometer 2 Click Types
 ******************************************************************************/
///@{


///@}
/**
 * @name 		Manometer 2 Click Driver Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif


/**
 * @brief Manometer 2 Click Driver Initialization
 *
 * @param[in] sensorType    Type of sensor used
 * @param[in] I2C_Address   Slave I2C Address
 * @param others            Function pointers
 *
 * Initialization of Manometer 2 click driver.
 * Will read factory callibration for use in later calculations.
 *
 * @note
 * This function must be called first.
 *
 */
void MMETER2_initDriver
(
        uint8_t sensorType,
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
        uint8_t I2C_Address, T_MMETER2_I2C_Start funStarter,
        T_MMETER2_I2C_Write funWriter, T_MMETER2_I2C_Read funReader
    #elif defined( __MSP__ )
        uint8_t I2C_Address,
        T_MMETER2_I2C_Write funWriter, T_MMETER2_I2C_Read funReader
    #elif defined( __TI__ )
        uint8_t I2C_Address, T_MMETER2_I2C_SetSlaveAddress funSlaveAddr,
        T_MMETER2_I2C_Write funWriter, T_MMETER2_I2C_Read funReader
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )
        uint8_t I2C_Address,
        T_MMETER2_I2C_Start funStarter, T_MMETER2_I2C_Stop funStoper,
        T_MMETER2_I2C_Write funWriter, T_MMETER2_I2C_Read funReader

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
        uint8_t I2C_Address, T_MMETER2_I2C_SetSlaveAddress funSlaveAddr,
        T_MMETER2_I2C_Write funWriter, T_MMETER2_I2C_Read funReader

#else
        uint8_t slaveAddress,
        T_MMETER2_I2C_Start fpStart, T_MMETER2_I2C_Stop fpStop,
        T_MMETER2_I2C_Write fpWrite, T_MMETER2_I2C_Read fpRead
#endif
);

/**
 * @brief Manometer 2 Temperature read
 *
 * @param[in] oversamplingRatio    oversampling ratio used
 *
 * Will read the temperature, and convert it into float value, expressed in
 * degrees celsius.
 *
 * @retval Relative pressure in degrees celsius
 *
 */
float MMETER2_getTemperature (uint8_t oversamplingRatio);
/**
 * @brief Manometer 2 Pressure read
 *
 * @param[in] oversamplingRatio    oversampling ratio used
 *
 * Will read the pressure, and convert it into float value, expressed in PSI.
 *
 * @retval Relative pressure in PSI
 *
 */
float MMETER2_getPressure (uint8_t oversamplingRatio);


#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __MMETER2_Driver.h

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