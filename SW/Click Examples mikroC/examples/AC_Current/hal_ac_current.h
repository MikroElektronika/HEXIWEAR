
/**
 * @file                        hal_ac_current.h
 * @brief               	HAL for AC Current click board 
 *
/******************************************************************************/

#ifndef _HAL_AC_CURRENT_H_
#define _HAL_AC_CURRENT_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*                         Functions
 ******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief HAL Delay
 *
 * @param[in]   ms          Amount of delay in miliseconds
 */
void hal_ac_current_delay( uint16_t ms );

/**
 * @brief HAL Initialization
 *
 * Initialization of HAL layer
 * Initializes function pointers and must be called first.
 */
void hal_ac_current_init( void );


/**
 * @brief SPI Read
 *
 * @param[out]         *buffer     Buffer to store data from device
 * @param[in]          count       Number of bytes to read
 *
 * @note Function have no affect to the CS PIN state - chip select is
 * controled directly from HW layer
 */
void hal_ac_current_read
(
        uint8_t* buffer,
        uint16_t count
);

#ifdef __cplusplus
} // extern "C"
#endif
#endif 
/*                                                                End of File
 ******************************************************************************/