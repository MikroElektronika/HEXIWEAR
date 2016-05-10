/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef FT_MODULE_GPIO_H
#define FT_MODULE_GPIO_H

/**
 * \defgroup gpio GPIO module
 * \ingroup modules
 * GPIO module uses the MCU's General Purpose pins and Timer.
 * \{
 */

#include "ft_modules.h"
#include "ft_types.h"
#include "ft_gpio.h"


/* forward declaration */
struct ft_module;
struct ft_module_interface;
                                     

/** Gpio user's interface, which is used by the GPIO modules.
 *  All of these functions must be implemented in the application.
 */
struct ft_module_gpio_user_interface {
    void (* set_pin_output)(uint32_t port, uint32_t pin);        /**< Set pin direction to output */
    void (* set_pin_input)(uint32_t port, uint32_t pin);         /**< Set pin direction to input */
    void (* set_pin_low)(uint32_t port, uint32_t pin);           /**< Set pin to logic low */
    void (* set_pin_high)(uint32_t port, uint32_t pin);          /**< Set pin to logic high */
    uint32_t (* get_pin_value)(uint32_t port, uint32_t pin);     /**< Get pin value */
    void (* set_pin_default_state)(uint32_t port, uint32_t pin); /**< Set pin to default state when it's not being measured */
    void (* init_timer)(void);                                   /**< Init timer */
    void (* start_timer)(void);                                  /**< Start timer */
    void (* stop_timer)(void);                                   /**< Stop timer */
    void (* timer_reset_counter)(void);                          /**< Reset timer counter */
    uint32_t (* timer_get_counter)(void);                        /**< Get timer counter */
    uint32_t (* timer_get_overrun)(void);                        /**< Get timer overrun */
};

/** GPIO module, which uses the \b ??interrupts? port to sample a signal from the running timer counter.
 */
struct ft_module_gpio_params {
    const struct ft_module_gpio_user_interface *user_interface;    
};

extern const struct ft_module_interface ft_module_gpio_interface; /**< Can't be NULL. */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif

/** \} */ // end of gpio group
