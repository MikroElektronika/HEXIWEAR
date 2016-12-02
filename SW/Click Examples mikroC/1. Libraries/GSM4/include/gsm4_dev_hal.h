/**
 * @file                                                        gsm4_dev_hal.h
 *
 * @defgroup AT_HAL HAL Layer
 * @{
 *
 * @brief                       HAL layer
 *
 * @par
 * HAL layer for AT parser.
 *
 ******************************************************************************/

#ifndef DEV_HAL_H
#define DEV_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief PWR
 *
 * @par
 * Power pin control
 *
 * @param[in] state
 */
void dev_hal_pwr_ctl
(
                bool state
);

/**
 * @brief RTS
 *
 * @par
 * Hardware flow control of sending data
 *
 * @retval RTS pin state
 */
bool dev_hal_rts_ctl
(
                void
);

/**
 * @brief CTS
 *
 * @par
 * Hardware flow control of incoming data
 *
 * @param[in] state of CTS
 */
void dev_hal_cts_ctl
(
                bool state
);

/**
 * @brief HAL Initialization
 *
 * HAL layer initialization. Must be called before any other function.
 * Used for assigning the function pointers.
 */
void dev_hal_init
(
                void
);

/**
 * @brief HAL Write
 *
 * @par
 * Writes data through UART bus
 *
 * @param[in] buffer
 */
void dev_hal_write( char ch );

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/**
 * @}
 */
/*** End of File **************************************************************/