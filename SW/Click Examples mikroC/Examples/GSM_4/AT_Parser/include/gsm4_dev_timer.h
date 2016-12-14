/**
 * @file                                                    gsm4_dev_timer.h
 *
 * @defgroup AT_TIM AT Timer
 * @{
 *
 * @brief                           AT Timer
 *
 * @par
 * Timer for GSM engine
 *
 ******************************************************************************/

#ifndef AT_TIMER_H
#define AT_TIMER_H

#include "gsm4_config.h"

/******************************************************************************
* Variables
*******************************************************************************/

extern volatile bool                            timeout_f;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief AT Timer Initialisation
 *
 * @par
 * Must be executed before any other timer operation
 */
void dev_timer_init
(
                void
);

/**
 * @brief Tick ISR
 *
 * @par
 * This must be placed inside the ISR function that is going to be executed
 * every one millisecond
 */
void dev_tick_isr
(
                void
);

/**
 * @brief AT Timer Start
 *
 * @par
 * Starts the timer
 */
void dev_timer_start
(
                void
);

/**
 * @brief AT Timer Restart
 *
 * @par
 * Restart the timer
 */
void dev_timer_restart
(
                void
);

/**
 * @brief AT Timer Stop
 *
 * @par
 * Stops the timer
 */
void dev_timer_stop
(
                void
);

/**
 * @brief AT Timer Load
 *
 * @par
 * Load new timer
 *
 * @param[in] timeout ( milliseconds)
 */
void dev_timer_load
(
                uint32_t timeout
);

#ifdef __cplusplus
}
#endif

#endif

/**
 * @}
 */
/*******************************End of File ***********************************/