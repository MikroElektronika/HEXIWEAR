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
/**
 * @file T4T_NDEF_EMU.h
 * @brief What is does
 *
 * @date 20 Feb 2016
 * @author Richard Lowe
 * @copyright GNU Public License
 *
 * @version .1 - Initial testing and verification
 *
 * @note Test configuration:
 *   MCU:             STM32F107VC
 *   Dev.Board:       EasyMx Pro v7
 *   Oscillator:      72 Mhz internal
 *   Ext. Modules:    GPS Click
 *   SW:              ARM 4.5.2
 *
 */
#ifndef T4T_NDEF_EMU_H_
#define T4T_NDEF_EMU_H_

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

/**
 * @brief t4t_ndef_emu_reset
 */
void t4t_ndef_emu_reset( void );

/**
 * @brief t4t_ndef_emu_next
 * @param p_cmd
 * @param cmd_size
 * @param rsp
 * @param p_rsp_size
 */
void t4t_ndef_emu_next( uint8_t *p_cmd, uint16_t cmd_size,
                        uint8_t *rsp, uint16_t *p_rsp_size );
/**
 * @brief t4t_ndef_emu_set_record
 * @param p_record
 * @param record_size
 * @param cb
 * @return
 */
bool t4t_ndef_emu_set_record( uint8_t *p_record,
                             uint16_t record_size, void *cb );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/


