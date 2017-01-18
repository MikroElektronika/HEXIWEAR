/**
 * @file                                                    gsm4_dev_timer.c
 * @cond INTERNAL_DOC
 *
 * @brief                               AT Timer
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * - 0.0.1 (Nov/2016) Module created                        Milos Vidojevic
 *
 ******************************************************************************/

#include "dev_timer.h"

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

static volatile bool            timer_f;
static volatile uint32_t        timer_c;
static volatile uint32_t        timer;

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

void dev_timer_init
(
                void
)
{
    uint8_t c;

    timer       = 0;
    timer_c     = 0;
    timeout_f   = false;
    timer_f     = false;
}

void dev_tick_isr
(
                void
)
{
    if( timer_f )
        if( timer_c++ > timer )
            timeout_f = true;
}

void dev_timer_start
(
                void
)
{
    timer_f = true;
    timer_c = 0;
}

void dev_timer_restart
(
                void
)
{
    timer_c = 0;
}

void dev_timer_stop
(
                void
)
{
    timer_f = false;
    timer_c = 0;
}

void dev_timer_load
(
                uint32_t timeout
)
{
    timer = timeout;
}

/**
 * @endcond
 */
/*************** END OF FUNCTIONS *********************************************/
