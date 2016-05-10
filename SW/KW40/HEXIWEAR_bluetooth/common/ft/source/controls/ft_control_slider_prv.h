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
#ifndef FT_SLIDER_PRV_H
#define FT_SLIDER_PRV_H

/**
 * \defgroup slider_private Slider Control
 * \ingroup controls_private
 *
 * Slider control enables the detection of a linear finger movement using discrete electrodes;
 * it is represented by the ft_control structure.
 *
 * The Slider Control uses a set of discrete electrodes to enable the calculation of finger
 * position within a linear area. The position algorithm localizes the touched
 * electrode and its sibling electrodes to estimate the finger position. The Slider consisting
 * of N electrodes enables the position to be calculated in 2N-1 steps.
 *
 * The Slider Control provides Position, Direction, and Displacement values. It
 * is able to generate event callbacks when finger Movement, Initial-touch, or Release
 * is detected.
 *
 * The image below shows a typical Slider electrode placement.
 * \image html slider.png "Slider Electrodes"
 * \image latex slider.png "Slider Electrodes"
 *
 * \{
 */

   
   
/** 
 *Slider flags. 
 */
enum ft_control_slider_flags {
    FT_SLIDER_INVALID_POSITION_FLAG = 1 << FT_FLAGS_SPECIFIC_SHIFT(0),  /**< Slider invalid position flag. */
    FT_SLIDER_DIRECTION_FLAG        = 1 << FT_FLAGS_SPECIFIC_SHIFT(1),  /**< Slider direction flag. */
    FT_SLIDER_MOVEMENT_FLAG         = 1 << FT_FLAGS_SPECIFIC_SHIFT(2),  /**< Slider movement flag.*/
    FT_SLIDER_TOUCH_FLAG            = 1 << FT_FLAGS_SPECIFIC_SHIFT(3),  /**< Slider touch flag. */
};

/**
 *  Slider RAM structure used to store volatile parameters of the control.
 *
 *  You must allocate this structure and put a pointer into the ft_control_slider_control
 *  structure when it is being registered in the system.
 */
struct ft_control_slider_data {
    ft_control_slider_callback  callback;       /**< Slider Callback handler. */
    uint8_t                     position;       /**< Position. */
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/** \} end of slider_private group */

#endif
