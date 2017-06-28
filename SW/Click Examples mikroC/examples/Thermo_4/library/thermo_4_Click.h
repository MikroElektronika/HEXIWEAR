/**
 * @file                        thermo_4_click.h
 * @brief                       Thermo click
 *
 * @defgroup Thermo_click
 * @brief                        Thermo click Driver
 *
 * This is the driver for Thermo click
 *
 * @{
 *
 * ### Device Description ###
 * 
 * Thermo click measures temperature. It's standard measuring range is
 * between -55 and +125 degrees Celsius.
 *
 *
 * ### Features ###
 *
 *     - The LM75 temperature sensor measures
 *       temperature and converts the data into digital form.
 *     - The device accepts standard I2C commands to read the data,
 *       set the overtemperature alarm (OS) trip thresholds, and
 *       configure other characteristics.
 *     - The temperature register is updated for the new temperature
 *       measurement upon completion of the read operation.
 *
 * ### Library Description
 *        This library contains functions for initialization, settings 
 *        and reading from Thermo 4 click
 *
 * @example thermo_4_ARM.c
 * @example thermo_4_PIC.c
 * @example thermo_4_PIC32.c
 * @example thermo_4_dsPIC.c
 * @example thermo_4_AVR.c
 * @example thermo_4_FT90x.c
 *
 ******************************************************************************/

#ifndef thermo_4_click_H
#define thermo_4_click_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @name                 Device Properties
 ******************************************************************************/
///@{

#define _i2c_hw_address               0x48

///@}
/**
 * @name                 Return Values
 ******************************************************************************/
///@{

#define THERMO_CLICK_ERR                                 (-1)
#define THERMO_CLICK_OK                                  (0)

///@}

/**
 * @name                 Thermo Registers
 ******************************************************************************/
///@{

#define     THERMO_TEMP                                 0x00
#define     THERMO_CONFIG                               0x01
#define     THERMO_THYST                                0x02
#define     THERMO_TOS                                  0x03

///@}

/**
 * @name                 Config commands
 ******************************************************************************/
///@{
/**
 * Sends device into shutdown mode*/
#define THERMO_SHUTDOWN                   0x01
/**
 * Returns device to normal operating mode*/
#define THERMO_POWERUP                    0xFE

/**
 * Sets device to work in Interupt mode*/
#define THERMO_INTERUPT MODE              0x02
/**
 * Sets device to work in Comparator mode*/
#define THERMO_COMPARATOR_MODE            0xFD


/**
 * Sets the state of active OS signal to high*/
#define THERMO_OS_ACTIVE_HIGH             0x04
/**
 * Sets the state of active OS signal to low*/
#define THERMO_OS_ACTIVE_LOW              0xFB

/**
 * Sets the length of fault queue to 1*/
#define THERMO_FAULT_QUEUE_1              0xE7
/**
 * Sets the length of fault queue to 2*/
#define THERMO_FAULT_QUEUE_2              0x08
/**
 * Sets the length of fault queue to 4*/
#define THERMO_FAULT_QUEUE_4              0x10
/**
 * Sets the length of fault queue to 6*/
#define THERMO_FAULT_QUEUE_6              0x18

///@}
/**
 * @name                 Types
 ******************************************************************************/
///@{


///@}
/**
 * @name                 Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Thermo click Initialization
 *
 * @param[in]   i2c_address                 device adress
 *
 * @retval        0                 no errors
 * @retval        non_zero         error occured
 *
 * Initializes Thermo click
 *
 * @note
 * This function must be called first.
 *
 */
uint16_t thermo_init(uint8_t i2c_address);


/**
 * @brief Thermo click configuration
 *
 * This function deals with writing into configuration register of the click.
 * By calling this function with correct parameters, it is ensured that 
 * the state of all bits, exept one being changed is preserved.
 *
 * @param[in]   value                config command to be written
 *
 * @note function works as intended if one of the config commands is used as
 * input value. Using any other value might result in unpredicted behaviour.
 */


void thermo_config(uint8_t value);



/**
 * @brief Reads temperature and converts it to text
 *
 * Temperature is stored in 2 bytes, MSB representing whole number,
 * and LSB representing fraction part. This function outputs stored
 * value, in the form of a string, formated as "xx.x";
 *
 * @param[out]   output                     output text "xx.x"
 * @param[in]    _location                  register from which to read
 *
 */
 
void thermo_read_temperature_text( char *output [15],  uint8_t _location );

/**
 * @brief Returns unconverted value from a register
 *
 * @par
 * Most significant bit is sign. Next 7 bytes represent whole nubmer part of 
 * the temperature. 9th bit represents fraction (0.5 or 0), and the next 7
 * bits are not used.
 *
 * @param[in]    _location                  register from which to read
 *
 */
uint16_t thermo_read_temperature_binary(  uint8_t _location );





/**
 * @brief Returns temperature value in fahrenheits
 *
 * @par
 *
 * This function reads a temperature from a register, and then 
 * converts it into fahrenheits, and returns it as a float value.
 *
 * @param[in]    _location                  register adress
 *
 * @retval           temperature in degrees fahrenheit
 *
 */
float thermo_read_temperature_fh ( uint8_t _location );

/**
 * @brief Writes temperature into selected register
 *
 * @par
 *
 * This function transforms float value into 2 separate bytes of data,
 * one for the whole part of the number, and one for fraction part.
 * Then it writes the data into selected register.
 *
 * @param[in]    _value                     value to write
 * @param[in]    _location                  register adress
 *
 * @note register 0x00 (THERMO_TEMP) is read-only. Function will do nothing
 * if it is selected as location.
 *
 */
void thermo_write_temperature ( float _value, uint8_t _location );

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
/**
 * @}                                                                 End of File
 ******************************************************************************/