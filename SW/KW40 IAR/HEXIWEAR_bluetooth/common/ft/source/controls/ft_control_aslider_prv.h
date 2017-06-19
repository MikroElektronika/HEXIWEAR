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
#ifndef FT_ASLIDER_PRV_H
#define FT_ASLIDER_PRV_H

/**
 * \defgroup aslider_private Analog Slider Control
 * \ingroup controls_private
 *
 * Analog Slider enables the detection of linear finger movement using two or more electrodes;
 * it is represented by the ft_control_aslider structure.
 *
 * An Analog Slider Control uses two or more specially-shaped electrodes to enable
 * the calculation of finger position within a linear area. The position algorithm uses
 * a ratio of electrode signals to estimate the finger position with required precision.
 *
 * The Analog Slider works similarly to the "standard" Slider, but requires less
 * electrodes, while achieving a higher resolution of the calculated position. For
 * example, a two-electrode analog slider can provide finger position detection in the
 * range of 0-127. The shape of the electrodes needs to be designed specifically to achieve
 * stable signal with a linear dependance on finger movement.
 *
 * The Analog Slider Control provides Position, Direction, and Displacement values. It
 * is able to generate event callbacks when finger Movement, Initial-touch, or Release
 * is detected.
 *
 * The image below shows a typical two-electrode Analog Slider electrode placement.
 * \image html aslider.png "Analog Slider Electrodes"
 * \image latex aslider.png "Analog Slider Electrodes"
 *
 * \{
 */

/**
 * Value that is used to mark an invalid position of analog slider.
 */
#define FT_ASLIDER_INVALID_POSITION_VALUE 65535U


/** 
 * Analog Slider flags. 
 */
enum ft_control_aslider_flags {
    FT_ASLIDER_INVALID_POSITION_FLAG = 1 << FT_FLAGS_SPECIFIC_SHIFT(0), /**< Analog Slider invalid position flag. */
    FT_ASLIDER_DIRECTION_FLAG        = 1 << FT_FLAGS_SPECIFIC_SHIFT(1), /**< Analog Slider direction flag. */
    FT_ASLIDER_MOVEMENT_FLAG         = 1 << FT_FLAGS_SPECIFIC_SHIFT(2), /**< Analog Slider movement flag.*/
    FT_ASLIDER_TOUCH_FLAG            = 1 << FT_FLAGS_SPECIFIC_SHIFT(3), /**< Analog Slider touch flag. */
};

/**
 *  Analog Slider RAM structure used to store volatile parameters of the control.
 *
 *  You need to allocate this structure and put a pointer into the ft_control_aslider
 *  structure when it is being registered in the system.
 */
struct ft_control_aslider_data {
    ft_control_aslider_callback   callback;     /**< Analog Slider callback handler. */
    uint8_t                       position;     /**< Position. */
};


/**
 *  Analog Slider help structure to handle temporary values
 */
struct ft_control_aslider_temp_data {
    uint32_t    active_el_ix;    /**< Index of electrode of first active electrode. */
    uint32_t    first_delta;           /**< Value of first delta (signal - baseline). */
    uint32_t    range;           /**< Value of first delta (signal - baseline). */    
};


#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

/** \} end of aslider_private group */

#endif
