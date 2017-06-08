                                                               /****************************************************************************
* Title                 :   I2C Hardware Access Layer for FAN Click
* Filename              :   fan_hal.h
* Author                :   Richard Lowe
* Origin Date           :   16/11/2015
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials    Description
*  16/11/15         1.0            RL
*
*****************************************************************************/
/**
 * @file heartrate1_hal.h
 * @brief This represent I2C read/write interface for Heartrate 1 Click
 *
 * @date 16 Nov 2015
 * @author Richard Lowe
 * @copyright GPL
 *
 * @version .1 - Initial testing and verification
 *
 * @note Test configuration:
 *   MCU:             STM32F107VC
 *   Dev.Board:       EasyMx Pro v7
 *   Oscillator:      72 Mhz internal
 *   Ext. Modules:    Fan Click
 *   SW:              ARM 4.5.1
 *
 */

#ifndef FAN_CLICK_HAL_H
#define FAN_CLICK_HAL_H

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define MAX_READ_SIZE 2

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes i2c module
 * @param address_id - slave device address
 */
int fan_i2c_init( uint8_t address_id );

/**
 * @brief Writes data through the i2c line
 * @param address - memory adress of the slave device
 * @param num     - number of bytes to send
 * @param buff    - buffer containing the bytes
 */
void fan_i2c_hal_write( uint8_t address, uint16_t num, uint8_t *buff );

/**
 * @brief Reads bytes from i2c bus, stores to a desired buffer
 * @param address - desired memory address on the slave device
 * @param num     - number of bytes to be read
 * @param buff    - buffer to where the read bytes will be stored
 */
void fan_i2c_hal_read(  uint8_t address, uint16_t num, uint8_t *buff );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*FAN_HAL_H_*/

/*** End of File **************************************************************/