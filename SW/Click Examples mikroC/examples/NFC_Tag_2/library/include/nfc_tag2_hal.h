/**
 * @file nfc_tag2_hal.h
 * @brief <h2> HAL layer </h2>
 *
 ******************************************************************************/

#ifndef NFC_TAG2_HAL_H_
#define NFC_TAG2_HAL_H_

#include <stdint.h>

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

void hal_delay( uint16_t ms );

/**
 * @brief HAL Initialization
 *
 * @par
 * Initialization of HAL layer used to initialize function pointers. This
 * Function is usually caled from HW layer initialization so user should not
 * care about it in that case.
 */
int hal_nfctag2_init( void );

/**
 * @brief HAL Write
 *
 * @param[in]   uint8_t     i2c_address
 * @param[in]   uint8_t*    buffer - data buffer
 * @param[in]   uint16_t    count - data size in bytes
 *
 * @par
 * Generic write function slightly adapted for NFC Tag 2 click.
 *
 */
int hal_nfctag2_write
(
        uint8_t i2c_address,
        uint8_t *buffer,
        uint16_t count 
);

/**
 * @brief HAL Read
 *
 * @par
 * Generic read function slightly adapted for NFC Tag 2 click.
 *
 * @note
 * Buffer caries command ( register address ) at first byte which will be
 * rewritten after reading.
 *
 * @param[in/out] buffer - data buffer
 * @param[in] count - data size in bytes
 */
int hal_nfctag2_read
(
        uint8_t i2c_address,
        uint8_t *buffer,
        uint16_t count 
);

/**
 * @brief HAL Transfer
 *
 * @param input
 * @param in_count
 * @param output
 * @param out_count
 * @return
 */
int hal_nfctag2_transfer
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

/*** End of File **************************************************************/
