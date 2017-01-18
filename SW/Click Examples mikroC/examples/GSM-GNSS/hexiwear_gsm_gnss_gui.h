/**
 * @file hexiwear_gsm_gnss_gui.h
 * @brief <h2> GSM/GNSS click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * GSM/GNSS click board. 
 *
 *
 *
 ******************************************************************************/

/**
 * @page        Example
 * @date        23 Nov 2016
 * @author      Branislav Marton
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 *
 * ### Test configuration STM : ###
 * @par
 * -<b> MCU           </b> :    STM32F207VG
 * -<b> Dev. Board    </b> :    EasyMx v7 for STM32
 * -<b> Ext. Modules  </b> :    GSM/GNSS click
 * -<b> SW            </b> :    mikroC PRO for ARM v4.9.0
 *
 */

#ifndef HEXIWEAR_GSM_GNSS_GUI_H
#define HEXIWEAR_GSM_GNSS_GUI_H

//#define _DEBUG_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <built_in.h>

#include "resources.h"
#include "OLED_driver.h"

/******************************************************************************
* Preprocessors
*******************************************************************************/
#define NULL 0

/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variable Definitions
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/


/******************************************************************************
* Private Functions
*******************************************************************************/

/******************************************************************************
* Public Functions
*******************************************************************************/
void hexiwear_gsm_gnss_gui_init( void );
void hexiwear_gsm_gnss_gui_draw_arrows( void );
void hexiwear_gsm_gnss_gui_draw_button( void );
void hexiwear_gsm_gnss_gui_clear_page( void );
void hexiwear_gsm_gnss_gui_write_msg( char** msg );
void hexiwear_gsm_gnss_gui_draw_sending_page( void );
void hexiwear_gsm_gnss_gui_draw_waiting_bar( uint8_t index );
void hexiwear_gsm_gnss_gui_draw_msg_select_page( char** msg );


/*************** END OF FUNCTIONS *********************************************/

#endif // HEXIWEAR_GSM_GNSS_GUI_H