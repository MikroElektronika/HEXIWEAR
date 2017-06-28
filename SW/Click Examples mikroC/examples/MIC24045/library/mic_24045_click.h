/**
 * @file                        mic_24045_click.h
 * @brief                       MIC24045 click
 *
 * @defgroup MIC24045_click
 * @brief                        MIC24045 click Driver
 *
 * This is the driver for MIC24045 click
 *
 * @{
 *
 * ### Device Description ###
 * 
 * The MIC24045 is an I2C-programmable, high-efficiency,
 * wide input range, 5A synchronous step-down
 * regulator. The MIC24045 is perfectly suited for multiple
 * voltage rail application environments, typically found in
 * computing and telecommunication systems.
 *
 *
 * ### Features ###
 *
 *     - 4.5V to 19V Input Voltage Range
 *     - 5A (maximum) Output Current
 *     -  I2C Programmable Output Voltage:
 *        0.64V to 5.25V in 5 mV, 10 mV, 30 mV and 50 mV steps
 *     - I2C Programmability of multiple other functions
 *
 * ### Library Description
 *        This library contains functions for writing into, and reading from
 * MIC24045 registers.
 *
 *
 * @example mic_24045_ARM.c
 * @example mic_24045_PIC.c
 * @example mic_24045_PIC32.c
 * @example mic_24045_dsPIC.c
 * @example mic_24045_AVR.c
 * @example mic_24045_FT90x.c
 *
 ******************************************************************************/

#ifndef mic_24045_click_H
#define mic_24045_click_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @name                 Device Properties
 ******************************************************************************/
///@{

#define _i2c_hw_address               0x50

///@}
/**
 * @name                 Return Values
 ******************************************************************************/
///@{

#define MIC24045_CLICK_ERR                                 (-1)
#define MIC24045_CLICK_OK                                  (0)

///@}

/**
 * @name                 MIC24045 Registers
 ******************************************************************************/
///@{

#define     MIC24045_STATUS                               0x00
#define     MIC24045_SETTINGS1                            0x01
#define     MIC24045_SETTINGS2                            0x02
#define     MIC24045_VOUT                                 0x03
#define     MIC24045_COMMAND                              0x04

///@}

/**
 * @name               Read status commands (reg 0x00)
 ******************************************************************************/
///@{
/**
 * Reads the status of the Power-good pin*/
#define MIC24045_PGS                          0x01
/**
 * Reads the status of the Enable pin*/
#define MIC24045_ENS                          0x08
/**
 * Reads the Thermal Warning Flag*/
#define MIC24045_THWRNF                       0x20
/**
 * Reads the Thermal Shutdown Flag*/
#define MIC24045_THSDF                        0x40
/**
 * Reads the Over-Current Flag*/
#define MIC24045_OCF                          0x80

///@}

/**
 * @name               Clear flags command (reg 0x04)
 ******************************************************************************/
///@{
/**
 * Clears fault flag bits*/
#define MIC24045_CIFF                   0x01


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
 * @brief MIC24045 click Initialization
 *
 * @param[in]   i2c_address                 device adress
 *
 * @retval        0                 no errors
 * @retval        non_zero         error occured
 *
 * Initializes MIC24045 click
 *
 * @note
 * This function must be called first.
 *
 */
uint16_t mic_24045_init(uint8_t i2c_address);
/**
 * @brief Reads MIC24045 status
 *
 * This function returns a value of the requested bit from the status register.
 * There are 5 possible bits to read.
 *
 * @param[in]   cmd                 Read status command
 */
bool mic_24045_status (uint8_t cmd);
/**
 * @brief Sets MIC24045 status flags to 0
 *
 * This function sets all the flags in status register to 0.
 */
void mic_24045_clear_flags ();



/**
 * @brief Reads MIC24045 vout setting
 *
 * This function returns output voltage value set by the vout register.
 *
 */
float mic_24045_read_vout ();
/**
 * @brief Writes into MIC24045 vout settings
 *
 * This function sets the voltage to specified float value, between 0.640V
 * and 5.250V. If specified value is outside the possible range, it will set
 * the voltage to the nearest possible value.
 * It is not recommended to change vout while EN pin is high, exept as
 * specified in the device datasheet.
 *
 * @param[in]   vout                 between 0.640V and 5.250V
 */
void mic_24045_write_vout (float vout);



/**
 * @brief Reads MIC24045 settings
 *
 * This function returns settings from one of the 2 settings registers.
 *
 * @param[in]   reg                 Register address (0x01 or 0x02)
 */
uint8_t mic_24045_read_settings (uint8_t reg);
/**
 * @brief Sets new MIC24045 settings
 *
 * This function writes data into one of the 2 settings registers.
 * Default settings data is restored upon power-off reset.
 *
 * @param[in]   reg                 Register address (0x01 or 0x02)
 * @param[in]   set                 New data to be written
 */
void mic_24045_write_settings (uint8_t reg, uint8_t set);



#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
/**
 * @}                                                                 End of File
 ******************************************************************************/