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
#ifndef FT_MODULE_GPIOINT_PRV_H
#define FT_MODULE_GPIOINT_PRV_H

/**
 * \defgroup gpioint_private GPIO interrupt module
 * \ingroup modules_private
 *
 * The GPIO interrupt module describes the hardware configuration and control of the elementary functionality
 * of the method that is using standard GPIO pins of the MCU with the GPIO and timer interrupts.
 *
 * The GPIO interrupt method is designed for all general processors that have a GPIO module with intterupt capability.
 *
 * \{
 */

#include "../source/electrodes/ft_electrodes_prv.h"
#include "ft_modules.h"

#include "ft_types.h"
#include "ft_electrodes.h"
#include "../source/filters/ft_filters_prv.h"


/** GPIO interrupt module's RAM. This structure contains 
 */
struct ft_module_gpioint_data {
    uint32_t pen;          /**< PEN - enablement of all modules' electrodes */
    uint8_t  measured_pin; /**< The currently measured pin */
    uint8_t  scan_status;  /**< Module's scanning status - see enum ft_gpio_scan_states */  
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/** \} */ // end of gpioint_private group

#endif
