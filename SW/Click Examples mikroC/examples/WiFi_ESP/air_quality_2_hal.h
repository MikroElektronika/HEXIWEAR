/**
 * @file        air_quality_2_hal.h
 * @brief       HAL layer for I2C communication
 *
 ******************************************************************************/

#ifndef I2C_HAL_H_
#define I2C_HAL_H_

#include <stdint.h>

/* 			Functions
 ******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief HAL Delay
 * 
 * @param[in] 	ms              Amount of delay in miliseconds
 */
void hal_delay( uint16_t ms );

/**
 * @brief HAL Initialization
 *
 * Initialization of HAL layer.  
 * Initializes function pointers and must be called first.
 */
int hal_air_quality_2_init( void );

/**
 * @brief HAL Read
 *
 * @param[in]	i2c_address	Device I2C slave address
 * @param[in] buffer 	Data buffer
 * @param[in] 	count 		Number of bytes to read
 *
 * @retval	0 		no errors
 * @retval	non_zero 	error occured
 *
 * @note
 * Data buffer caries command ( register address ) at first byte which will be
 * rewritten after reading.
 */
int hal_air_quality_2_read
(
        uint8_t i2c_address,
        uint8_t *buffer,
        uint16_t count 
);


#ifdef __cplusplus
} // extern "C"
#endif
#endif
/*								End of File
 ******************************************************************************/

