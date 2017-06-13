/*

    __ADAC_Driver.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
 * @file                                            __ADAC_Driver.h
 * @brief                     ADAC Click
 *
 * @defgroup ADAC
 * @brief                   ADAC Click Driver
 *
 * Global Library Prefix : **ADAC**
 *
 * @mainpage ADAC Click
 *
 * @{
 *
 * ![ADAC](../../ADAC_Click.png)
 *
 * ### Device Description ###
 *
 *     The AD5593R has eight input/output (I/O) pins, which can be
 * independently configured as digital-to-analog converter (DAC)
 * outputs, analog-to-digital converter (ADC) inputs, digital outputs,
 * or digital inputs.
 *
 * ### Features ###
 *
 * - 8-channel, configurable ADC/DAC/GPIO
 * - Configurable as any combination of
 * - 8 12-bit DAC channels
 * - 8 12-bit ADC channels
 * - 8 general-purpose I/O pins
 * - Integrated temperature sensor
 * - 16-lead TSSOP and LFCSP and 16-ball WLCSP packages
 * - I2C interface
 *
 * @}
 *
 * @example ADAC_Click_ARM_STM.c
 * @example ADAC_Click_ARM_TIVA.c
 * @example ADAC_Click_ARM_CEC.c
 * @example ADAC_Click_ARM_KIN.c
 * @example ADAC_Click_ARM_MSP.c
 * @example ADAC_Click_PIC.c
 * @example ADAC_Click_PIC32.c
 * @example ADAC_Click_DSPIC.c
 * @example ADAC_Click_AVR.c
 * @example ADAC_Click_FTDI.c
 * @example ADAC_Click_ARM_STM.mbas
 * @example ADAC_Click_ARM_TIVA.mbas
 * @example ADAC_Click_ARM_CEC.mbas
 * @example ADAC_Click_ARM_KIN.mbas
 * @example ADAC_Click_ARM_MSP.mbas
 * @example ADAC_Click_PIC.mbas
 * @example ADAC_Click_PIC32.mbas
 * @example ADAC_Click_DSPIC.mbas
 * @example ADAC_Click_AVR.mbas
 * @example ADAC_Click_FTDI.mbas
 * @example ADAC_Click_ARM_STM.mpas
 * @example ADAC_Click_ARM_TIVA.mpas
 * @example ADAC_Click_ARM_CEC.mpas
 * @example ADAC_Click_ARM_KIN.mpas
 * @example ADAC_Click_ARM_MSP.mpas
 * @example ADAC_Click_PIC.pas
 * @example ADAC_Click_PIC32.pas
 * @example ADAC_Click_DSPIC.pas
 * @example ADAC_Click_AVR.pas
 * @example ADAC_Click_FTDI.pas
 *
 ******************************************************************************/

#ifndef _ADAC_H_
#define _ADAC_H_

#include <stdint.h>

/*-------------------------- HAL POINTERS ------------------------------------*/

#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
typedef unsigned int ( *T_ADAC_I2C_Start )();
typedef unsigned int ( *T_ADAC_I2C_Write )(unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode);
typedef void ( *T_ADAC_I2C_Read )(unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode);
    #elif defined( __MSP__ )
typedef unsigned int ( *T_ADAC_I2C_Write )(unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode);
typedef void ( *T_ADAC_I2C_Read )(unsigned char slave_address, unsigned char *buffer, unsigned long count, unsigned long end_mode);
    #elif defined( __TI__ )
typedef void ( *T_ADAC_I2C_SetSlaveAddress )(char slave_address, char dir);
typedef unsigned char ( *T_ADAC_I2C_Write )(unsigned char data_in, unsigned char mode);
typedef unsigned char( *T_ADAC_I2C_Read )(unsigned char *data_out, unsigned char mode);
    #endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )
typedef unsigned char( *T_ADAC_I2C_Start )();
typedef void  ( *T_ADAC_I2C_Stop )();
typedef void ( *T_ADAC_I2C_Close )();
typedef void ( *T_ADAC_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_ADAC_I2C_Read )(unsigned char ack);

#elif  defined( __MIKROC_PRO_FOR_PIC__ )
typedef unsigned char( *T_ADAC_I2C_Start )();
typedef void ( *T_ADAC_I2C_Stop )();
typedef void ( *T_ADAC_I2C_Restart )();
typedef unsigned char( *T_ADAC_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_ADAC_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
typedef unsigned int ( *T_ADAC_I2C_Idle )();
typedef unsigned int ( *T_ADAC_I2C_Start )();
typedef void ( *T_ADAC_I2C_Stop )();
typedef unsigned int ( *T_ADAC_I2C_Restart )();
typedef unsigned int ( *T_ADAC_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_ADAC_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )
typedef unsigned int ( *T_ADAC_I2C_Start )();
typedef void ( *T_ADAC_I2C_Stop )();
typedef void ( *T_ADAC_I2C_Restart )();
typedef unsigned int ( *T_ADAC_I2C_Write )(unsigned char data_out);
typedef unsigned char ( *T_ADAC_I2C_Read )(unsigned int ack);

#elif defined( __MIKROC_PRO_FOR_8051__ )
typedef unsigned char( *T_ADAC_I2C_Start )();
typedef void ( *T_ADAC_I2C_Stop )();
typedef void ( *T_ADAC_I2C_Write )(unsigned char data_out);
typedef unsigned char( *T_ADAC_I2C_Read )(unsigned char ack);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
typedef void ( *T_ADAC_I2C_SetSlaveAddress )(unsigned char slave_address);
typedef unsigned char ( *T_ADAC_I2C_Write )(unsigned char *buffer, unsigned int count);
typedef unsigned char ( *T_ADAC_I2C_Read )(unsigned char *buffer, unsigned int count);
#elif
typedef void ( *T_ADAC_I2C_Start )();
typedef void ( *T_ADAC_I2C_Stop )();
typedef void ( *T_ADAC_I2C_Write )(uint8_t input);
typedef uint8_t ( *T_ADAC_I2C_Read )(uint8_t input);
#endif

/*----------------------------------------------------------------------------*/

/**
 * @name 		ADAC Configuration Pointer Bytes
 ******************************************************************************/
///@{


#define _ADAC_NULL           0b00000000
#define _ADAC_ADC_SEQUENCE   0b00000010 // ADC sequence register - Selects ADCs for conversion
#define _ADAC_GP_CONTROL     0b00000011 // General-purpose control register - DAC and ADC control register
#define _ADAC_ADC_CONFIG     0b00000100 // ADC pin configuration - Selects which pins are ADC inputs
#define _ADAC_DAC_CONFIG     0b00000101 // DAC pin configuration - Selects which pins are DAC outputs
#define _ADAC_PULL_DOWN      0b00000110 // Pull-down configuration - Selects which pins have an 85 kO pull-down resistor to GND
#define _ADAC_LDAC_MODE      0b00000111 // LDAC mode - Selects the operation of the load DAC
#define _ADAC_GPIO_WR_CONFIG 0b00001000 // GPIO write configuration - Selects which pins are general-purpose outputs
#define _ADAC_GPIO_WR_DATA   0b00001001 // GPIO write data - Writes data to general-purpose outputs
#define _ADAC_GPIO_RD_CONFIG 0b00001010 // GPIO read configuration - Selects which pins are general-purpose inputs
#define _ADAC_POWER_REF_CTRL 0b00001011 // Power-down/reference control - Powers down the DACs and enables/disables the reference
#define _ADAC_OPEN_DRAIN_CFG 0b00001100 // Open-drain configuration - Selects open-drain or push-pull for general-purpose outputs
#define _ADAC_THREE_STATE    0b00001101 // Three-state pins - Selects which pins are three-stated
#define _ADAC_RESERVED       0b00001110 // Reserved
#define _ADAC_SOFT_RESET     0b00001111 // Software reset - Resets the AD5593R

/**
 * @name 		ADAC Configuration Data Bytes
 ******************************************************************************/
///@{
//write into MSB after _ADAC_POWER_REF_CTRL command to enable VREF
#define _ADAC_VREF_ON     0b00000010
#define _ADAC_SEQUENCE_ON 0b00000010
//write into LSB to choose which pin is selected by the command
#define _ADAC_IO0         0b00000001
#define _ADAC_IO1         0b00000010
#define _ADAC_IO2         0b00000100
#define _ADAC_IO3         0b00001000
#define _ADAC_IO4         0b00010000
#define _ADAC_IO5         0b00100000
#define _ADAC_IO6         0b01000000
#define _ADAC_IO7         0b10000000


/**
 * @name   ADAC Write / Read Pointer Bytes
******************************************************************************/
///@{
#define _ADAC_DAC_WRITE       0b00010000
#define _ADAC_ADC_READ        0b01000000
#define _ADAC_DAC_READ        0b01010000
#define _ADAC_GPIO_READ       0b01110000
#define _ADAC_REG_READ        0b01100000

/**
 * @name   ADAC Pointer Byte Pin Selection
 ******************************************************************************/
///@{

#define _ADAC_PB_PIN0      0b00000000
#define _ADAC_PB_PIN1      0b00000001
#define _ADAC_PB_PIN2      0b00000010
#define _ADAC_PB_PIN3      0b00000011
#define _ADAC_PB_PIN4      0b00000100
#define _ADAC_PB_PIN5      0b00000101
#define _ADAC_PB_PIN6      0b00000110
#define _ADAC_PB_PIN7      0b00000111

/**
 * @name 		ADAC Click Return Values
 ******************************************************************************/
///@{

#define _ADAC_OK			(0)
#define _ADAC_ERR			(-1)

///@}
/**
 * @name 		ADAC Click Types
 ******************************************************************************/
///@{


///@}
/**
 * @name 		ADAC Click Driver Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief ADAC Click Driver Initialization
 *
 * @param[in] I2C_Address   Slave I2C Address
 * @param others            Function pointers
 *
 * Initialization of ADAC click driver.
 *
 * @note
 * This function must be called first.
 *
 */
void ADAC_driverInit
(
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( __STM32__ ) || defined( __KINETIS__ ) || defined( __MCHP__ )
        uint8_t I2C_Address, T_ADAC_I2C_Start funStarter,
        T_ADAC_I2C_Write funWriter, T_ADAC_I2C_Read funReader
    #elif defined( __MSP__ )
        uint8_t I2C_Address,
        T_ADAC_I2C_Write funWriter, T_ADAC_I2C_Read funReader
    #elif defined( __TI__ )
        uint8_t I2C_Address, T_ADAC_I2C_SetSlaveAddress funSlaveAddr,
        T_ADAC_I2C_Write funWriter, T_ADAC_I2C_Read funReader
    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )   || \
      defined( __MIKROC_PRO_FOR_8051__ )  || \
      defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
      defined( __MIKROC_PRO_FOR_PIC32__ ) || \
      defined( __MIKROC_PRO_FOR_PIC__ )
        uint8_t I2C_Address,
        T_ADAC_I2C_Start funStarter, T_ADAC_I2C_Stop funStoper,
        T_ADAC_I2C_Write funWriter, T_ADAC_I2C_Read funReader

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
        uint8_t I2C_Address, T_ADAC_I2C_SetSlaveAddress funSlaveAddr,
        T_ADAC_I2C_Write funWriter, T_ADAC_I2C_Read funReader

#else
        uint8_t slaveAddress,
        T_ADAC_I2C_Start fpStart, T_ADAC_I2C_Stop fpStop,
        T_ADAC_I2C_Write fpWrite, T_ADAC_I2C_Read fpRead
#endif
);


/**
 * @brief ADAC Click configuration setting
 *
 * @param[in] pointerByte  One of the ADAC Configuration Pointer Bytes
 * @param[in] MSDataByte   Setting byte 1
 * @param[in] LSDatabyte   Setting byte 2
 *
 * Writes the settings into the ADAC click registers.
 * This function just calls a basic I2C write to write the three bytes that 
 * were passed to it.
 */
void ADAC_setConfiguration (uint8_t pointerByte, uint8_t MSDataByte,
                                                 uint8_t LSDatabyte);
/**
 * @brief DAC write
 *
 * @param[in] pointerByte    _ADAC_DAC_WRITE | ADAC Pointer Byte Pin Selection
 * @param[in] MSDataByte   4 MS bits to write
 * @param[in] LSDatabyte   8 LS bits to write
 *
 * Writes the digital value to be converted to an analog one into the selected
 * channel. Will automatically format data for writing (0x80 + Selected channel
 * code into the 4 MS bits of the MS byte, followed by 12 bits of data)
 *
 * @note
 * Configure the device properly first using the ADAC_setConfiguration function.
 */
void ADAC_writeDAC (uint8_t pointerByte, uint8_t MSDataByte,
                                         uint8_t LSDatabyte);
/**
 * @brief ADC read
 *
 * @param[in] pointerByte   _ADAC_ADC_READ
 * @param[out] IOChannel    Channel that the value was read from
 *
 * Reads the most recent ADC conversion.
 *
 * @note
 * Configure the device properly first using the ADAC_setConfiguration function.
 */
uint16_t ADAC_readADC (uint8_t pointerByte, uint8_t * IOChannel);

/**
 * @brief DAC read
 *
 * @param[in] pointerByte   _ADAC_DAC_READ | ADAC Pointer Byte Pin Selection
 * @param[out] IOChannel    Channel that the value was read from
 *
 * Reads the value on the selected DAC channel.
 *
 * @note
 * Configure the device properly first using the ADAC_setConfiguration function.
 *
 */
uint16_t ADAC_readDAC (uint8_t pointerByte, uint8_t * IOChannel);

/**
 * @brief GPIO input read
 *
 * @param[in]  pointerByte   _ADAC_GPIO_READ
 *
 * Reads the status of all GPIO pins. Value of the channel is contained in the
 * corresponding bit. IO0 = bit0 etc...
 *
 * @note
 * Configure the device properly first using the ADAC_setConfiguration function.
 *
 */
uint16_t ADAC_readGPIO (uint8_t pointerByte);

/**
 * @brief Read configuration
 *
 * @param[in] pointerByte   _ADAC_REG_READ | ADAC Configuration Pointer Bytes
 *
 * This function returns the value of one of the configuration registers.
 *
 */
uint16_t ADAC_readConfig (uint8_t pointerByte);
#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
///@}
/*------------------------------------------------------------------------------

  __ADAC_Driver.h

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