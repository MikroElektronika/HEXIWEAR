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
/** @file P2P_NDEF.h
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
#ifndef P2P_NDEF_H_
#define P2P_NDEF_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/
#define P2P_NDEF_MAX_NDEF_RECORD_SIZE 240

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

void p2p_ndef_reset( void );
void p2p_ndef_next( uint8_t *p_cmd, uint16_t cmd_size,
                    uint8_t *rsp, uint16_t *p_rsp_size );
bool p2p_ndef_set_record( uint8_t *p_record, uint16_t record_size,
                         void *cb );
void p2p_ndef_register_pull_callback( void *p_cb );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/





