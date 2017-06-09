/*

    __LSM303AGR_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
@file           __LSM303AGR_Driver.h
@brief                         LSM303AGR Click
   
@mainpage LSM303AGR Click
@{

### Device Description ###

    ${CLICK_INFO}

@}

@defgroup    LSM303AGR
@brief       LSM303AGR Click Driver
@{

    Global Library Prefix : **LSM303AGR**
    Version               : **${VER}**
    Date                  : ${DATE}
    Developer             : *${SW_ENG}*

    ${LIBRARY_DESCRIPTION}

/*----------------------------------------------------------------------------*/
/**
    @example Click_LSM303AGR_ARM_STM.c
    @example Click_LSM303AGR_ARM_TIVA.c
    @example Click_LSM303AGR_ARM_CEC.c
    @example Click_LSM303AGR_ARM_KIN.c
    @example Click_LSM303AGR_ARM_MSP.c
    @example Click_LSM303AGR_PIC.c
    @example Click_LSM303AGR_PIC32.c
    @example Click_LSM303AGR_DSPIC.c
    @example Click_LSM303AGR_AVR.c
    @example Click_LSM303AGR_FTDI.c
    @example Click_LSM303AGR_ARM_STM.mbas
    @example Click_LSM303AGR_ARM_TIVA.mbas
    @example Click_LSM303AGR_ARM_CEC.mbas
    @example Click_LSM303AGR_ARM_KIN.mbas
    @example Click_LSM303AGR_ARM_MSP.mbas
    @example Click_LSM303AGR_PIC.mbas
    @example Click_LSM303AGR_PIC32.mbas
    @example Click_LSM303AGR_DSPIC.mbas
    @example Click_LSM303AGR_AVR.mbas
    @example Click_LSM303AGR_FTDI.mbas
    @example Click_LSM303AGR_ARM_STM.mpas
    @example Click_LSM303AGR_ARM_TIVA.mpas
    @example Click_LSM303AGR_ARM_CEC.mpas
    @example Click_LSM303AGR_ARM_KIN.mpas
    @example Click_LSM303AGR_ARM_MSP.mpas
    @example Click_LSM303AGR_PIC.pas
    @example Click_LSM303AGR_PIC32.pas
    @example Click_LSM303AGR_DSPIC.pas
    @example Click_LSM303AGR_AVR.pas
    @example Click_LSM303AGR_FTDI.pas

*//*--------------------------------------------------------------------------*/

#ifndef _LSM303AGR_H_
#define _LSM303AGR_H_

#include <stdint.h>
#include <stdbool.h>

/*-------------------------------------------------------------- HAL POINTERS */
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

typedef unsigned int ( *T_LSM303AGR_I2C_Start )();
typedef unsigned int ( *T_LSM303AGR_I2C_Write )( unsigned char slave_address,
                                                    unsigned char *buffer, 
                                                    unsigned long count, 
                                                    unsigned long end_mode );
typedef void ( *T_LSM303AGR_I2C_Read )( unsigned char slave_address,
                                           unsigned char *buffer,
                                           unsigned long count, 
                                           unsigned long end_mode );
    #elif defined( __MSP__ )

typedef unsigned int ( *T_LSM303AGR_I2C_Write )( unsigned char slave_address,
                                                    unsigned char *buffer,
                                                    unsigned long count, 
                                                    unsigned long end_mode );

typedef void ( *T_LSM303AGR_I2C_Read )( unsigned char slave_address,
                                           unsigned char *buffer, 
                                           unsigned long count, 
                                           unsigned long end_mode );

    #elif defined( __TI__ )

typedef void ( *T_LSM303AGR_I2C_SetSlaveAddressA )( char slave_address,
                                                      char dir );
typedef void ( *T_LSM303AGR_I2C_SetSlaveAddressM )( char slave_address,
                                                      char dir );

typedef unsigned char ( *T_LSM303AGR_I2C_Write )( unsigned char data_in,
                                                     unsigned char mode );
typedef unsigned char( *T_LSM303AGR_I2C_Read )( unsigned char *data_out,
                                                   unsigned char mode );
    #endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )

typedef unsigned char( *T_LSM303AGR_I2C_Start )();
typedef void  ( *T_LSM303AGR_I2C_Stop )();
typedef void ( *T_LSM303AGR_I2C_Close )();
typedef void ( *T_LSM303AGR_I2C_Write )( unsigned char data_out );
typedef unsigned char ( *T_LSM303AGR_I2C_Read )( unsigned char ack );

#elif  defined( __MIKROC_PRO_FOR_PIC__ )

typedef unsigned char( *T_LSM303AGR_I2C_Start )();
typedef void ( *T_LSM303AGR_I2C_Stop )();
typedef void ( *T_LSM303AGR_I2C_Restart )();
typedef unsigned char( *T_LSM303AGR_I2C_Write )( unsigned char data_out );
typedef unsigned char( *T_LSM303AGR_I2C_Read )( unsigned char ack );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

typedef unsigned int ( *T_LSM303AGR_I2C_Idle )();
typedef unsigned int ( *T_LSM303AGR_I2C_Start )();
typedef void ( *T_LSM303AGR_I2C_Stop )();
typedef unsigned int ( *T_LSM303AGR_I2C_Restart )();
typedef unsigned int ( *T_LSM303AGR_I2C_Write )( unsigned char data_out );
typedef unsigned char ( *T_LSM303AGR_I2C_Read )( unsigned int ack );

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )

typedef unsigned int ( *T_LSM303AGR_I2C_Start )();
typedef void ( *T_LSM303AGR_I2C_Stop )();
typedef void ( *T_LSM303AGR_I2C_Restart )();
typedef unsigned int ( *T_LSM303AGR_I2C_Write )( unsigned char data_out );
typedef unsigned char ( *T_LSM303AGR_I2C_Read )( unsigned int ack );

#elif defined( __MIKROC_PRO_FOR_8051__ )

typedef unsigned char( *T_LSM303AGR_I2C_Start )();
typedef void ( *T_LSM303AGR_I2C_Stop )();
typedef void ( *T_LSM303AGR_I2C_Write )( unsigned char data_out );
typedef unsigned char( *T_LSM303AGR_I2C_Read )( unsigned char ack );

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

typedef void ( *T_LSM303AGR_I2C_SetSlaveAddressA )
                                                  (uint8_t slave_address);
typedef void ( *T_LSM303AGR_I2C_SetSlaveAddressM )
                                                  (uint8_t slave_address);
typedef unsigned char ( *T_LSM303AGR_I2C_Write )( unsigned char *buffer,
                                                     unsigned int count);
typedef unsigned char ( *T_LSM303AGR_I2C_Read )( unsigned char *buffer,
                                                    unsigned int count);
#else
typedef void ( *T_LSM303AGR_I2C_Start )();
typedef void ( *T_LSM303AGR_I2C_Stop )();
typedef void ( *T_LSM303AGR_I2C_Write )( uint8_t input);
typedef uint8_t ( *T_LSM303AGR_I2C_Read )( uint8_t input);
#endif
/*----------------------------------------------------------------------------*/

/**
 * @name                 LSM303AGR Click Registers
 *//*-------------------------------------------------------------------------*/
///@{

#define _LSM303AGR_STATUS
#define _LSM303AGR_STATUS_REG_AUX_A 0x07    /**< Temperature sensor status */
#define _LSM303AGR_OUT_TEMP_L_A 0x0C        /**< Temperature sensor data lower 8 bits */
#define _LSM303AGR_OUT_TEMP_H_A 0x0D        /**< Temperature sensor data higher 8 bits */
#define _LSM303AGR_INT_COUNTER_REG_A 0x0E   /**< Interrupt counter */
#define _LSM303AGR_WHO_AM_I_A 0x0F          /**< Device identification */
#define _LSM303AGR_TEMP_CFG_REG_A 0x1F      /**< Temperature sensor enable */
#define _LSM303AGR_CTRL_REG1_A 0x20         /**< Accelerometer control */
#define _LSM303AGR_CTRL_REG2_A 0x21         /**< Accelerometer control */
#define _LSM303AGR_CTRL_REG3_A 0x22         /**< Accelerometer control */
#define _LSM303AGR_CTRL_REG4_A 0x23         /**< Accelerometer control */
#define _LSM303AGR_CTRL_REG5_A 0x24         /**< Accelerometer control */
#define _LSM303AGR_CTRL_REG6_A 0x25         /**< Accelerometer control */
#define _LSM303AGR_REF_DATACAP_A 0x26       /**< Reference value for interrupt generation */
#define _LSM303AGR_STATUS_REG_A 0x27        /**< Accelerometer status */
#define _LSM303AGR_OUT_X_L_A 0x28           /**< X-axis acceleration data */
#define _LSM303AGR_OUT_X_H_A 0x29           /**< X-axis acceleration data */
#define _LSM303AGR_OUT_Y_L_A 0x2A           /**< Y-axis acceleration data */
#define _LSM303AGR_OUT_Y_H_A 0x2B           /**< Y-axis acceleration data */
#define _LSM303AGR_OUT_Z_L_A 0x2C           /**< Z-axis acceleration data */
#define _LSM303AGR_OUT_Z_H_A 0x2D           /**< Z-axis acceleration data */
#define _LSM303AGR_FIFO_CTRL_REG_A 0x2E     /**< FIFO control (mode, trigger selection) */
#define _LSM303AGR_FIFO_SRC_REG_A 0x2F      /**< FIFO (empty/full flags, num of unread samples) */
#define _LSM303AGR_INT1_CFG_A 0x30          /**< Interrupt 1 configuration */
#define _LSM303AGR_INT1_SRC_A 0x31          /**< Interrupt 1 source */
#define _LSM303AGR_INT1_THS_A 0x32          /**< Interrupt 1 threshold */
#define _LSM303AGR_INT1_DURATION_A 0x33     /**< Interrupt 1 minimum duration */
#define _LSM303AGR_INT2_CFG_A 0x34          /**< Interrupt 2 configuration */
#define _LSM303AGR_INT2_SRC_A 0x35          /**< Interrupt 2 source */
#define _LSM303AGR_INT2_THS_A 0x36          /**< Interrupt 2 threshold */
#define _LSM303AGR_INT2_DURATION_A 0x37     /**< Interrupt 2 minimum duration */
#define _LSM303AGR_CLICK_CFG_A 0x38         /**< Interrupt click configuration */
#define _LSM303AGR_CLICK_SRC_A 0x39         /**< Click source */
#define _LSM303AGR_CLICK_THS_A 0x3A         /**< Click threshold*/
#define _LSM303AGR_TIME_LIMIT_A 0x3B        /**< Click time limit */
#define _LSM303AGR_TIME_LATENCY_A 0x3C      /**< Click time latency */
#define _LSM303AGR_TIME_WINDOW_A 0x3D       /**< Click time window */
#define _LSM303AGR_Act_THS_A 0x3E           /**< Sleep-to-wake, return-to-sleep activation threshold in low-power mode */
#define _LSM303AGR_Act_DUR_A 0x3F           /**< Sleep-to-wake, return-to-sleep duration */
#define _LSM303AGR_OFFSET_X_REG_L_M 0x45    /**< Least significant bits of X hard-iron offset */
#define _LSM303AGR_OFFSET_X_REG_H_M 0x46    /**< Most significant bits of X hard-iron offset */
#define _LSM303AGR_OFFSET_Y_REG_L_M 0x47    /**< Least significant bits of Y hard-iron offset*/
#define _LSM303AGR_OFFSET_Y_REG_H_M 0x48    /**< Most significant bits of Y hard-iron offset */
#define _LSM303AGR_OFFSET_Z_REG_L_M 0x49    /**< Least significant bits of  Z hard-iron offset*/
#define _LSM303AGR_OFFSET_Z_REG_H_M 0x4A    /**< Most significant bits of Z hard-iron offset */
#define _LSM303AGR_WHO_AM_I_M 0x4F          /**< Identification (magnetometer) */
#define _LSM303AGR_CFG_REG_A_M 0x60         /**< Magnetometer configuration */
#define _LSM303AGR_CFG_REG_B_M 0x61         /**< Magnetometer configuration */
#define _LSM303AGR_CFG_REG_C_M 0x62         /**< Magnetometer configuration */
#define _LSM303AGR_INT_CRTL_REG_M 0x63      /**< Magnetometer iterrupt control */
#define _LSM303AGR_INT_SOURCE_REG_M 0x64    /**< Magnetometer iterrupt source */
#define _LSM303AGR_INT_THS_L_REG_M 0x65     /**< Least significant bits of the interrupt threshold value */
#define _LSM303AGR_INT_THS_H_REG_M 0x66     /**< Most significant bits of the interrupt threshold value */
#define _LSM303AGR_STATUS_REG_M 0x67        /**< Magnetometer status */
#define _LSM303AGR_OUTX_L_REG_M 0x68        /**< Least significant bits of X component of magnetic data */
#define _LSM303AGR_OUTX_H_REG_M 0x69        /**< Most significant bits of X component of magnetic data */
#define _LSM303AGR_OUTY_L_REG_M 0x6A        /**< Least significant bits of Y component of magnetic data */
#define _LSM303AGR_OUTY_H_REG_M 0x6B        /**< Most significant bits of Y component of magnetic data */
#define _LSM303AGR_OUTZ_L_REG_M 0x6C        /**< Least significant bits of Z component of magnetic data */
#define _LSM303AGR_OUTZ_H_REG_M 0x6D        /**< Most significant bits of Z component of magnetic data */

///@}
/**
 * @name                 LSM303AGR Click Return Values
 *//*-------------------------------------------------------------------------*/
///@{

#define _LSM303AGR_OK (0)
#define _LSM303AGR_ERR (-1)

///@}
/**
 * @name                 LSM303AGR Click Types
 *//*-------------------------------------------------------------------------*/
///@{

typedef enum
{
        LSM303AGR_LOW_POWER,
        LSM303AGR_HIGH_RES,
        LSM303AGR_NORMAL,
        LSM303AGR_NOT_ALLOWED,
} T_LSM303AGR_powerMode;

typedef enum
{
        LSM303AGR_CONT,
        LSM303AGR_SINGLE,
        LSM303AGR_IDLE        
} T_LSM303AGR_sysMode;

typedef enum
{
    LSM303AGR_ACC,
    LSM303AGR_MAG
} T_LSM303AGR_device;

///@}
/**
 * @name                 LSM303AGR Click Driver Functions
 *//*-------------------------------------------------------------------------*/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief LSM303AGR Click Driver Initialization
 *
 * @param[in] I2C_Address   Slave I2C Address
 * @param others            Function pointers
 *
 * Initialization of LSM303AGR click driver.
 *
 * @note
 * This function must be called first.
 *
 */
void LSM303AGR_initDriver
(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )

        uint8_t I2C_AddressA, uint8_t I2C_AddressM,
        T_LSM303AGR_I2C_Start funStarter,
        T_LSM303AGR_I2C_Write funWriter, T_LSM303AGR_I2C_Read funReader

    #elif defined( __MSP__ )

        uint8_t I2C_AddressA, uint8_t I2C_AddressM,
        T_LSM303AGR_I2C_Write funWriter, T_LSM303AGR_I2C_Read funReader

    #elif defined( __TI__ )

        uint8_t I2C_AddressA, uint8_t I2C_AddressM,
        T_LSM303AGR_I2C_SetSlaveAddressA funSlaveAddrA,
        T_LSM303AGR_I2C_SetSlaveAddressM funSlaveAddrM,
        T_LSM303AGR_I2C_Write funWriter, T_LSM303AGR_I2C_Read funReader
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )

       uint8_t I2C_AddressA, uint8_t I2C_AddressM,
       T_LSM303AGR_I2C_Start funStarter, T_LSM303AGR_I2C_Stop funStoper,
       T_LSM303AGR_I2C_Write funWriter, T_LSM303AGR_I2C_Read funReader

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

        uint8_t I2C_AddressA, uint8_t I2C_AddressM,
        T_LSM303AGR_I2C_SetSlaveAddressA funSlaveAddrA,
        T_LSM303AGR_I2C_SetSlaveAddressM funSlaveAddrM,
        T_LSM303AGR_I2C_Write funWriter, T_LSM303AGR_I2C_Read funReader

#else
        uint8_t slaveAddressA, uint8_t slaveAddressM,
        T_LSM303AGR_I2C_Start fpStart, T_LSM303AGR_I2C_Stop fpStop,
        T_LSM303AGR_I2C_Write fpWrite, T_LSM303AGR_I2C_Read fpRead
#endif
);

/**
* @brief Enables temperature sensor
*
*/
void LSM303AGR_enableTempSensor();

/**
* @brief Reboots accelerometer and magnetometer memory content
*
*/
void LSM303AGR_rebootMem();

/**
* @brief Disables accelerometer
*
*/
void LSM303AGR_disableAcc();

/**
* @brief Self-tests specified device
*
* @param[in] device         Device I2C slave address
*
* @retval          true                Self-test passed
* @retval    false                Self-test failed
*/
bool LSM303AGR_selfTest( T_LSM303AGR_device device );

/**
* @brief Sets operating mode for specified device
*
* @param[in] device         Device I2C slave address
* @param[in] mode                Operating mode
*/
void LSM303AGR_setPowerMode(
     T_LSM303AGR_device device,
     T_LSM303AGR_powerMode mode
);

/**
* @brief Sets measuring mode for magnetometer
*
* @param[in] mode           Measuring mode
*/
void LSM303AGR_setMeasureMode( T_LSM303AGR_sysMode mode );

/**
* @brief Sets output data rate
*
* @param[in] device                Device I2C slave address
* @param[in] dataRate   Output data rate
*/
void LSM303AGR_SetDataRate( T_LSM303AGR_device device, uint8_t dataRate );

/**
 * @brief Soft-reset magnetometer
 *
 * Resets the configuration registers and user registers.
 * Flash registers keep their values.
 */
void LSM303AGR_softResetMag();

/**
 * @brief Reads output data from specified device
 *
 * @param[in]  device         Device I2C slave address
 * @param[out] pOutput  Output data
 *
 */
void LSM303AGR_readOutput( T_LSM303AGR_device device, uint16_t *pOutput );

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __LSM303AGR_Driver.h

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