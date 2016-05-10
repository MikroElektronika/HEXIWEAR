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
#ifndef FT_MODULE_GPIOINT_H
#define FT_MODULE_GPIOINT_H

/**
 * \defgroup gpioint GPIO interrupt basic module
 * \ingroup modules
 * The GPIO module uses the General Purpose pins and Timer of the MCU.
 * Works on GPIO pins with interrupt.
 * \{
 */

#include "ft_modules.h"
#include "ft_types.h"
#include "ft_gpio.h"

/* forward declaration */
struct ft_module;
struct ft_module_interface;


/** GPIO user's interface, which is used by the GPIO modules.
 *  All of these functions must be implemented in the application.
 */
struct ft_module_gpioint_user_interface {
    void     (* set_pin_output)(uint32_t port, uint32_t pin);        /**< Set the pin direction to output */
    void     (* set_pin_input)(uint32_t port, uint32_t pin);         /**< Set the pin direction to input */
    void     (* set_pin_low)(uint32_t port, uint32_t pin);           /**< Set the pin to logic low */
    void     (* set_pin_high)(uint32_t port, uint32_t pin);          /**< Set the pin to logic high */
    void     (* init_pin)(uint32_t port, uint32_t pin);              /**< Initialize the pin to a state ready for measurement */
    void     (* set_pin_interrupt)(uint32_t port, uint32_t pin);     /**< Enable the pin to generate an interrupt */
    void     (* clear_pin_interrupt)(uint32_t port, uint32_t pin);   /**< Disable the pin to generate an interrupt */
    void     (* init_timer)(void);                                   /**< Init timer */
    void     (* start_timer)(void);                                  /**< Start timer */
    void     (* stop_timer)(void);                                   /**< Stop timer */
    void     (* timer_reset_counter)(void);                          /**< Reset timer counter */
    uint32_t (* timer_get_counter)(void);                            /**< Get timer counter */
};

/** GPIO interrupt module, which uses the port interrupts to sample a signal from the running timer counter.
 */
struct ft_module_gpioint_params {
    const struct ft_module_gpioint_user_interface *user_interface;    
};

extern const struct ft_module_interface ft_module_gpioint_interface; /**< Can't be NULL. */

#ifdef __cplusplus
extern "C" {
#endif


/**
 *  \brief This interrupt handler must be invoked from the user's port interrupt ISR.
 *         There can be other pins on the same port which can invoke the interrupt; therefore,
 *         it is up to the application to decode which pin caused the interrupt. For example, if
 *         there's a button on the PTA3 and an electrode on the PTA4, the PORTA ISR handler must decode,
 *         whether the interrupt was caused by the PTA3 or PTA4. Invoke the ft_module_gpioint_isr() only if any of the GPIO modules'
 *         electrodes caused an interrupt.
 *  \param module Pointer to the module that invokes the interrupt; it depends on the user application to handle the right value.
 *  \return None.
 */
void ft_module_gpioint_isr(const struct ft_module *module);

/**
 *  \brief This interrupt handler should be invoked from the user's timer interrupt ISR.
 *         It is not mandatory to call this function, but it's designed to avoid,
 *         stuck to the Freescale Touch GPIO Interrupt module. It should be called 
 *         after the user-defined maximal timeout for one measurement.
 *  \param module Pointer to the module that invokes the interrupt; it depends on the user application to handle the right value.
 *  \return None.
 */
void ft_module_gpioint_overflow_isr(const struct ft_module *module);
#ifdef __cplusplus
}
#endif

#endif

/** \} */ // end of the gpioint group
