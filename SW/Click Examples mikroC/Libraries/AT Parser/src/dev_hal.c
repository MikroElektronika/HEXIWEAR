/**
 * @file                                                    gsm4_dev_hal.c
 * @cond INTERNAL_DOC
 *
 * @brief                           HAL layer
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * - 0.0.1 (Nov/2016) Module created                        Milos Vidojevic
 *
 ******************************************************************************/

#include "dev_hal.h"

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )
static void         ( *write_uart_p )           ( unsigned int data_out );

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )    || \
      defined( __MIKROC_PRO_FOR_FT90x__ )
static void         ( *write_uart_p )           ( unsigned char data_out );
#endif

#if defined( __MIKROC_PRO_FOR_ARM__ )     || \
    defined( __MIKROC_PRO_FOR_AVR__ )     || \
    defined( __MIKROC_PRO_FOR_PIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )   || \
    defined( __MIKROC_PRO_FOR_8051__ )    || \
    defined( __MIKROC_PRO_FOR_FT90x__ )
extern sfr sbit GSM_PWR;
extern sfr sbit GSM_RTS;
extern sfr sbit GSM_CTS;
#endif

/******************************************************************************
* Function Definitions
*******************************************************************************/

void dev_hal_pwr_ctl( bool state )
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )  || \
    defined( __MIKROC_PRO_FOR_FT90x__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    if ( state )
        GSM_PWR = 1;
    else
        GSM_PWR = 0;
#endif
}

bool dev_hal_rts_ctl()
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )  || \
    defined( __MIKROC_PRO_FOR_FT90x__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    if( GSM_CTS )
        return false;
    else
        return true;
#endif
    return true;
}

void dev_hal_cts_ctl( bool state )
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )  || \
    defined( __MIKROC_PRO_FOR_FT90x__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    if( state )
        GSM_RTS = 0;
    else
        GSM_RTS = 1;
#endif
}

void dev_hal_init()
{
    write_uart_p = UART_Wr_Ptr;
}

void dev_hal_write( char ch )
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )  || \
    defined( __MIKROC_PRO_FOR_FT90x__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    write_uart_p( ch );
#endif
}

/**
 * @endcond
 */
/*************** END OF FUNCTIONS ***************************************************************************/
