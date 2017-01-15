/****************************************************************************
* Title                 :   I2C Hardware Access Layer
* Filename              :   ir_gesture_hal.h
* Author                :   Nikola Golubovic
* Origin Date           :   15/12/2015
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials    Description
*  15/12/15         1.0            NG
*
*****************************************************************************/
/** @file ir_gesture_hal.h
 *  @brief This represent a generic I2C read/write interface
 *
 *  @date 15 Dec 2015
 *  @author Nikola Golubovic
 *  @copyright MikroelEktronika
 *
 *  @version .1 - Initial testing and verification
 *
 *  @note Test configuration:
 *   MCU:             STM32F107VC
 *   Dev.Board:       EasyMx Pro v7
 *   Oscillator:      72 Mhz internal
 *   Ext. Modules:    TouchPad_Click
 *   SW:              ARM 4.5.1
 *
 */

#ifndef IRGESTURE_HAL_H
#define IRGESTURE_HAL_H

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define I2C_MAX_BUFFER 5

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
 * @brief hw_i2c_init
 * Initializes i2c module
 * @param address_id - slave device address
 */
int ir_gesture_i2c_init( uint8_t address_id );

/**
 * @brief ir_gesture_hal_delay
 * @param ms
 */
void ir_gesture_hal_delay( uint8_t ms );

/**
 * @brief hw_i2c_hal_write
 * Writes data through the i2c line
 * @param address - memory adress of the slave device
 * @param num     - number of bytes to send
 * @param buff    - buffer containing the bytes
 */
void ir_gesture_i2c_hal_write( uint8_t address,
                               uint8_t const *buff, uint16_t count );

/**
 * @brief hw_i2c_hal_read
 * Reads bytes from i2c bus, stores to a desired buffer
 * @param address - desired memory address on the slave device
 * @param num     - number of bytes to be read
 * @param buff    - buffer to where the read bytes will be stored
 */
void ir_gesture_i2c_hal_read( uint8_t address,
                              uint8_t const *buff , uint16_t count );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/
