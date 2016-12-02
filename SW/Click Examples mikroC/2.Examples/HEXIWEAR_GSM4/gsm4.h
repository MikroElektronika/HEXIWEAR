/**
 * @file                                                            gsm4.h
 * @page Example
 * @brief                   GSM 4 Example
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * GSM4 click board.
 *
 * @date        28 Jan 2016
 * @author      Milos Vidojevic
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 *
 * ### Example Configuration : ###
 * @par
 * -<b> MCU           </b> :
 * -<b> Dev. Board    </b> :
 * -<b> Oscillator    </b> :
 * -<b> Ext. Modules  </b> :
 * -<b> SW            </b> :
 *
 * @mainpage
 *
 *
 ******************************************************************************/

#ifndef _GSM_GPS_H_
#define _GSM_GPS_H_

#include "at_engine.h"

/* Initialization - Constructor
 ******************************************************************************/
void gsm4_init( void );

/* Event handlers
 ******************************************************************************/

void gsm4_evn_default( char *response );

void gsm4_ev_ring( char *response );

void gsm4_evn_call_id( char *response );


/* Actions
 ******************************************************************************/

void gsm_act_read_info( void );

void gsm_act_send_info( void );

void gps_act_pwr_control( bool state );

#endif
