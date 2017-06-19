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
#ifndef FT_ROTARY_PRV_H
#define FT_ROTARY_PRV_H

/**
 * \defgroup rotary_private Rotary Control
 * \ingroup controls_private
 *
 * Rotary enables the detection of jog-dial-like finger movement using discrete
 * electrodes; it is represented by the ft_control_rotary_control structure.
 *
 * The Rotary Control uses a set of discrete electrodes to enable the calculation of finger
 * position within a circular area. The position algorithm localizes the touched
 * electrode and its sibling electrodes to estimate the finger position. The Rotary consisting
 * of N electrodes enables the rotary position to be calculated in 2N steps.
 *
 * The Rotary Control provides Position, Direction, and Displacement values. It
 * is able to generate event callbacks when finger Movement, Initial-touch, or Release is detected.
 *
 * The image below shows a typical Rotary electrode placement.
 * \image html rotary.png "Rotary Electrodes"
 * \image latex rotary.png "Rotary Electrodes"
 *
 * \{
 */

/** 
 * Rotary flags. 
 */
enum ft_control_rotary_flags {
    FT_ROTARY_INVALID_POSITION_FLAG = 1 << FT_FLAGS_SPECIFIC_SHIFT(0),  /**< Rotary invalid position flag. */
    FT_ROTARY_DIRECTION_FLAG        = 1 << FT_FLAGS_SPECIFIC_SHIFT(1),  /**< Rotary direction flag. */
    FT_ROTARY_MOVEMENT_FLAG         = 1 << FT_FLAGS_SPECIFIC_SHIFT(2),  /**< Rotary movement flag.*/
    FT_ROTARY_TOUCH_FLAG            = 1 << FT_FLAGS_SPECIFIC_SHIFT(3),  /**< Rotary touch flag. */
};

/**
 *  Rotary RAM structure used to store volatile parameters of the control.
 *
 *  You must allocate this structure and put a pointer into the ft_control_rotary_control
 *  structure when it is being registered in the system.
 */
struct ft_control_rotary_data {
    ft_control_rotary_callback callback;    /**< Callback handler. */
    uint8_t            position;            /**< Position. */
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/** \} */ // end of rotary_private group

#endif
