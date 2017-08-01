/*

    __LSM6DSL_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __LSM6DSL_Driver.h
@brief                         LSM6DSL Click
   
@mainpage LSM6DSL Click
@{

### Device Description ###

    The LSM6DSL is a system-in-package featuring a 3D
    digital accelerometer and a 3D digital gyroscope
    performing at 0.65 mA in high-performance mode and
    enabling always-on low-power features for an optimal
    motion experience for the consumer.

@}

@defgroup    LSM6DSL
@brief       LSM6DSL Click Driver
@{

    Global Library Prefix : **LSM6DSL**
    Version               : **1.0.0**
    Date                  : Jun 2017
    Developer             : *Djordje Rosic*

    This library contains basic functions for using the LSM6DSL click board.
    It contains initialization, configuration and data reading functions, as
    well as generic access functions for advanced operation with the device.

/*----------------------------------------------------------------------------*/
/**
    @example Click_LSM6DSL_ARM_STM.c
    @example Click_LSM6DSL_ARM_TIVA.c
    @example Click_LSM6DSL_ARM_CEC.c
    @example Click_LSM6DSL_ARM_KIN.c
    @example Click_LSM6DSL_ARM_MSP.c
    @example Click_LSM6DSL_PIC.c
    @example Click_LSM6DSL_PIC32.c
    @example Click_LSM6DSL_DSPIC.c
    @example Click_LSM6DSL_AVR.c
    @example Click_LSM6DSL_FTDI.c
    @example Click_LSM6DSL_ARM_STM.mbas
    @example Click_LSM6DSL_ARM_TIVA.mbas
    @example Click_LSM6DSL_ARM_CEC.mbas
    @example Click_LSM6DSL_ARM_KIN.mbas
    @example Click_LSM6DSL_ARM_MSP.mbas
    @example Click_LSM6DSL_PIC.mbas
    @example Click_LSM6DSL_PIC32.mbas
    @example Click_LSM6DSL_DSPIC.mbas
    @example Click_LSM6DSL_AVR.mbas
    @example Click_LSM6DSL_FTDI.mbas
    @example Click_LSM6DSL_ARM_STM.mpas
    @example Click_LSM6DSL_ARM_TIVA.mpas
    @example Click_LSM6DSL_ARM_CEC.mpas
    @example Click_LSM6DSL_ARM_KIN.mpas
    @example Click_LSM6DSL_ARM_MSP.mpas
    @example Click_LSM6DSL_PIC.pas
    @example Click_LSM6DSL_PIC32.pas
    @example Click_LSM6DSL_DSPIC.pas
    @example Click_LSM6DSL_AVR.pas
    @example Click_LSM6DSL_FTDI.pas

*//*--------------------------------------------------------------------------*/

#ifndef _LSM6DSL_H_
#define _LSM6DSL_H_

#include <stdint.h>

/*-------------------------------------------------------------- HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )

typedef void ( *T_LSM6DSL_SPI_Write )(unsigned int data_out);
typedef unsigned int ( *T_LSM6DSL_SPI_Read )(unsigned int buffer);

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )

typedef void ( *T_LSM6DSL_SPI_Write )(unsigned char data_out);
typedef unsigned char ( *T_LSM6DSL_SPI_Read )(unsigned char dummy);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

typedef void ( *T_LSM6DSL_SPI_Write )(unsigned long data_out);
typedef unsigned long( *T_LSM6DSL_SPI_Read )(unsigned long dummy);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void ( *T_LSM6DSL_SPI_Write )(unsigned char data_out);
typedef unsigned char ( *T_LSM6DSL_SPI_Read )(unsigned char dummy);
#else
typedef void ( *T_LSM6DSL_SPI_Write )(uint8_t input);
typedef uint8_t ( *T_LSM6DSL_SPI_Read )(uint8_t input);
#endif
/*----------------------------------------------------------------------------*/

/**
 * @name                 LSM6DSL Click Registers
 *//*-------------------------------------------------------------------------*/
///@{
#define CONFIG_ACCELERATION 0x10
#define CONFIG_ROTATION     0x11

/**
 * @name                 LSM6DSL Click Output Data Rates
 *//*-------------------------------------------------------------------------*/
///@{
#define DISABLE_MEASUREMENT    0x00
#define ODR_6660_HZ    0xA0
#define ODR_3330_HZ    0x90
#define ODR_1660_HZ    0x80
#define ODR_833_HZ     0x70
#define ODR_416_HZ     0x60
#define ODR_208_HZ     0x50
#define ODR_104_HZ     0x40
#define ODR_52_HZ      0x30
#define ODR_26_HZ      0x20
#define ODR_12_5_HZ    0x10
//Only for Acceleration
#define ODR_1_6_HZ     0xB0


/**
 * @name                 LSM6DSL Full Scale Selections
 *//*-------------------------------------------------------------------------*/
///@{
#define FULLSCALE_A_2    0x00
#define FULLSCALE_A_4    0x04
#define FULLSCALE_A_8    0x08
#define FULLSCALE_A_16   0x0C


#define FULLSCALE_R_125   0x02
#define FULLSCALE_R_245   0x00
#define FULLSCALE_R_500   0x04
#define FULLSCALE_R_1000  0x08
#define FULLSCALE_R_2000  0x0C


///@}
/**
 * @name                 LSM6DSL Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

#define _LSM6DSL_OK (0)
#define _LSM6DSL_ERR (-1)

///@}
/**
 * @name                 LSM6DSL Click Types
 *//*-------------------------------------------------------------------------*/
///@{


///@}
/**
 * @name                 LSM6DSL Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief LSM6DSL Driver Initialization
 *
 * @param[in] fnWrite   SPI Write Function
 * @param[in] fnRead    SPI Read Function
 *
 * Initialization of LSM6DSL click driver.
 *
 * @note
 * This function must be called first.
 *
 */
void LSM6DSL_initDriver(T_LSM6DSL_SPI_Write fnWrite,
                              T_LSM6DSL_SPI_Read fnRead);


/**
 * @brief LSM6DSL Generic Read Function
 *
 * @param[in] registerAddress   Address to read from
 *
 * This function will return the value of chosen register
 *
 * @note
 * This function is intended for advanced operation, and should only be used
 * with full understanding of device functions and registers.
 *
 */
uint8_t LSM6DSL_readRegister (uint8_t registerAddress);
/**
 * @brief LSM6DSL Generic Write Function
 *
 * @param[in] registerAddress   Address to write to
 * @param[in] writeData         Data to write
 *
 * This function will write the data into chosen register
 *
 * @note
 * This function is intended for advanced operation, and should only be used
 * with full understanding of device functions and registers.
 *
 */
void LSM6DSL_writeRegister (uint8_t registerAddress, uint8_t writeData);



/**
 * @brief LSM6DSL Measurement Configuration
 *
 * @param[in] registerAddress   CONFIG_ACCELERATION or CONFIG_ROTATION
 * @param[in] configurationData Parameters for measurement configuration
 *
 * This function will setup output data rate and full-scale value for
 * measuring acceleration or rotation. Call this function with either
 * CONFIG_ACCELERATION or CONFIG_ROTATION as first parameter, and setup
 * ODR and FULLSCALE parameters. FULLSCALE parameter is needed for read
 * functions.
 *
 * @example LSM6DSL_configureRead (CONFIG_ACCELERATION, ODR_104_HZ | FULLSCALE_A_2);
 *
 * @note
 * This function should be called before any readings, because the device
 * won't perform any measurements by default. It can also be used to disable
 * measurements if called with DISABLE_MEASUREMENT parameter.
 *
 */
void LSM6DSL_configureRead (uint8_t registerAddress, uint8_t configurationData);
/**
 * @brief LSM6DSL Read Acceleration Function
 *
 * @param[out] x,y,z                Read values
 * @param[in] fullScale             FULLSCALE selection value
 *
 * This function will read the registers and get the acceleration values for
 * x, y and z axes. It will output them as float values expressed in
 * mili-Gs (1/1000 part of standard g-force).
 *
 * @note
 * LSM6DSL_configureRead should be configured first, and fullscale value should
 * be the same as the one set there.
 */
void LSM6DSL_readAccelerationXYZ (float * x, float * y, float * z, uint8_t fullScale);
/**
 * @brief LSM6DSL Read Rotation Function
 *
 * @param[out] x,y,z                Read values
 * @param[in] fullScale             FULLSCALE selection value
 *
 * This function will read the registers and get the rotation values for
 * pitch, roll and yaw. It will output them as float values expressed in
 * mili-Degrees per second (1/1000 part of a Degree per second).
 *
 * @note
 * LSM6DSL_configureRead should be configured first, and fullscale value should
 * be the same as the one set there.
 */
void LSM6DSL_readRotationXYZ (float * x, float * y, float * z, uint8_t fullScale);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __LSM6DSL_Driver.h

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