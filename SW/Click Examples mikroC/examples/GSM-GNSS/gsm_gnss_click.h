/**
 * @file gsm_gnss_click.h
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

#ifndef GSM_GNSS_CLICK_H
#define GSM_GNSS_CLICK_H

//#define _DEBUG_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdbool.h>

#include "gsm4_at_engine.h"

#include "log.h"
#include "hexiwear_gsm_gnss_gui.h"

/******************************************************************************
* Preprocessors
*******************************************************************************/
#define GSM_MODEM_BAUD_RATE  9600

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef void ( *send_sms_callback_t )( void );

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
void gsm_gnss_click_init( void );

void gsm_gnss_click_configure_callbacks(
    send_sms_callback_t sms_sent, 
    send_sms_callback_t sms_delivered,
    send_sms_callback_t sms_failed,
    send_sms_callback_t sms_confirmed
);

void gsm_gnss_click_send_sms(const char* phone_number, const char* msg);

void gsm_gnss_click_process( void );

void gsm_gnss_click_read_nav( char* );

/*************** END OF FUNCTIONS *********************************************/

#endif // GSM_GNSS_CLICK_H