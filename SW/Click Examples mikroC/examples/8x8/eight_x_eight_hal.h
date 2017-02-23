/****************************************************************************
* Title                 :   8x8 click HAL
* Filename              :   eight_x_eight_hal.h
* Author                :   CAL
* Origin Date           :   03/29/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  03/29/2016     1.0.0            CAL        Module Created.
*
*****************************************************************************/
/**
 * @file CLICKNAME_hal.h
 * @brief <h2> HAL layer </h2>
 *
 * @par
 * HAL layer for
 * <a href="http://www.mikroe.com">MikroElektronika's</a> CLICKNAME click
 * board.
 */
#ifndef EIGHT_X_EIGHT_HAL_H_
#define EIGHT_X_EIGHT_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define DUMMY_BYTE                                                  0x00
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
extern "C"{
#endif

/**
 * @brief <h3> CS High </h3>
 *
 * @par
 * Used by HW layer functions to set CS PIN high ( deselect )
 */
void led_eight_hal_cs_high( void );

/**
 * @brief <h3> CS Low </h3>
 *
 * @par
 * Used by HW layer functions to set CS PIN low ( selecet )
 */
void led_eight_hal_cs_low( void );

/**
 * @brief <h3> HAL Initialization </h3>
 *
 * Hal layer initialization. Must be called before any other function.
 */
void led_eight_hal_init( void );

/**
 * @brief <h3> HAL Write </h3>
 *
 * @par
 * Writes data through SPI bus
 *
 * @note Function have no affect to the CS PIN state - chip select is
 * controled directly from HW layer.
 *
 * @param[in] buffer
 *
 */
void led_eight_hal_write( uint8_t *buffer );


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CLICKNAME_HAL_H_ */

/*** End of File **************************************************************/
