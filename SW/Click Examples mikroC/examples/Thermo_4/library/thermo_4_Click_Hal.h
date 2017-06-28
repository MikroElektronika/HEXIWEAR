/**
 * @file thermo_4_Click_hal.h
 * @brief                                 HAL layer for I2C communication
 *
 ******************************************************************************/

#ifndef I2C_HAL_H_
#define I2C_HAL_H_

#include <stdint.h>

/*                         Functions
 ******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief HAL Delay
 * 
 * @param[in]         ms              Amount of delay in miliseconds
 */
void hal_delay( uint16_t ms );

/**
 * @brief HAL Initialization
 *
 * Initialization of HAL layer.  
 * Initializes function pointers and must be called first.
 */
uint16_t hal_thermo_init( uint8_t address_id );

/**
 * @brief HAL Write
 *
 * @param[in]   i2c_address        Device I2C slave address
 * @param[in]   buffer                 Data for writting
 * @param[in]   count                 Number of bytes to write
 *
 * @retval        0                 no errors
 * @retval        non_zero         error occured
 */
uint16_t hal_thermo_write
(
        uint8_t i2c_address,
        uint8_t *buffer,
        uint16_t count 
);

/**
 * @brief HAL Read
 * 
 * @param[in]        i2c_address        Device I2C slave address
 * @param[in,out]    buffer             Data buffer
 * @param[in]        count              Number of bytes to read
 *
 * @retval        0                 no errors
 * @retval        non_zero          error occured
 *
 * @note
 * Data buffer caries command ( register address ) at first byte which will be
 * rewritten after reading.
 */
uint16_t hal_thermo_read
(
        uint8_t i2c_address,
        uint8_t *buffer,
        uint16_t count 
);

/**
 * @brief HAL Transfer
 *
 * @param[in]          i2c_address         Device I2C slave address
 * @param[in]          *input                Data for writting
 * @param[in]          in_count        Number of bytes to write
 * @param[out]         *output                Buffer to store data from device
 * @param[in]          out_count        Number of bytes to read
 *
 * @retval        0                 no errors
 * @retval        non_zero         error occured
 */
uint16_t hal_thermo_transfer
(
        uint8_t i2c_address,
        uint8_t* input,
        uint16_t in_count,
        uint8_t* output,
        uint16_t out_count
);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
/*                                                                End of File
 ******************************************************************************/