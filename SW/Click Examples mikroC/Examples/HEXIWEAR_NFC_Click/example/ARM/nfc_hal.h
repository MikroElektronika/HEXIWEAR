/****************************************************************************
* Title                 :   CLICKNAME click
* Filename              :   CLICKNAME_hal.h
* Author                :   MSV
* Origin Date           :   28/01/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  28/01/16    XXXXXXXXXXX         MSV      Interface Created.
*
*****************************************************************************/
/**
 * @file nfc_hal.h
 *  @brief What is does
 *
 *  @date 28 Jan 2016
 *  @author Milos Vidojevic
 *  @copyright GNU Public License
 *
 *  @version .1 - Initial testing and verification
 *
 *  @note Test configuration:
 *   MCU:             STM32F107VC
 *   Dev.Board:       EasyMx Pro v7
 *   Oscillator:      72 Mhz internal
 *   Ext. Modules:    GPS Click
 *   SW:              ARM 4.5.2
 *
 */
#ifndef NFC_HAL_H_
#define NFC_HAL_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define TIMEOUT_INFINITE    0
#define TIMEOUT_100MS       100
#define TIMEOUT_1S          1000
#define TIMEOUT_2S          2000

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

void nfc_hal_init( uint8_t address_id );

void nfc_hal_delay( uint16_t ms );

void nfc_hal_reset( void );

int nfc_hal_write( uint8_t *data_out, uint16_t count );

int nfc_hal_read( uint8_t *data_in, uint16_t *nbytes_read,
                  uint16_t count );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CLICKNAME_HAL_H_ */

/*** End of File **************************************************************/