/****************************************************************************
* Title                 :   ADC Application
* Filename              :   adc_app.h
* Author                :   RBL
* Origin Date           :   06/07/2012
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  20/02/16    XXXXXXXXXXX         RBL      Interface Created.
*
*****************************************************************************/
/** @file RW_NDEF.h
 *  @brief What is does
 *
 *  @date 20 Feb 2016
 *  @author Richard Lowe
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
#ifndef RW_NDEF_H_
#define RW_NDEF_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define RW_NDEF_TYPE_T1T    0x1
#define RW_NDEF_TYPE_T2T    0x2
#define RW_NDEF_TYPE_T3T    0x3
#define RW_NDEF_TYPE_T4T    0x4

/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define RW_MAX_NDEF_FILE_SIZE 240

/******************************************************************************
* Macros
*******************************************************************************/


/******************************************************************************
* Typedefs
*******************************************************************************/
typedef void rw_ndef_callback_t( uint8_t *, uint16_t );

/******************************************************************************
* Variables
*******************************************************************************/
extern uint8_t ndef_buffer[RW_MAX_NDEF_FILE_SIZE];
extern rw_ndef_callback_t *p_rw_ndef_pull_cb;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief rw_ndef_register_pull_callback
 * @param pCb
 */
void rw_ndef_register_pull_callback( void *p_cb );

/**
 * @brief rw_ndef_reset
 * @param type
 */
void rw_ndef_reset( uint8_t type );

/**
 * @brief rw_ndef_read_next
 * @param p_cmd
 * @param cmd_size
 * @param rsp
 * @param p_rsp_size
 */
void rw_ndef_read_next( uint8_t *p_cmd, uint16_t cmd_size,
                        uint8_t *rsp, uint16_t *p_rsp_size );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/
