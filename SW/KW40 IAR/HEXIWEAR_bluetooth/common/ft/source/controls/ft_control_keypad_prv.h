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
#ifndef FT_KEYPAD_PRV_H
#define FT_KEYPAD_PRV_H

/**
 * \defgroup keypad_private Keypad Control
 * \ingroup controls_private
 *
 * Keypad implements the keyboard-like functionality on top of an array of
 * electrodes; it is represented by the ft_control_keypad structure.
 *
 * An application may use the Electrode API to determine the touch or release states
 * of individual electrodes. The Keypad simplifies this task and it extends this
 * simple scenario by introducing a concept of a "key". The "key" is represented
 * by one or more physical electrodes, so the Keypad control enables one
 * electrode to be shared by several keys. Each key is defined by a set of electrodes that
 * all need to be touched in order to report the "key press" event.
 *
 * The Keypad Control provides Key status values and is able to generate the Key Touch,
 * Auto-repeat, and Release events.
 *
 * The images below show simple and grouped keypad electrode layouts.
 * \image html keypad.png "Keypad Electrodes"
 * \image latex keypad.png "Keypad Electrodes"
 *
 * \{
 */

#include "ft_controls.h"
#include "ft_types.h"
/* forward declaration */
struct ft_control_keypad;


/** 
 * Keypad flags. 
 */
enum ft_control_keypad_flags {
    FT_KEYPAD_ONLY_ONE_KEY_FLAG       = 1 << FT_FLAGS_SPECIFIC_SHIFT(0), /**< Keypad only one key is valid flag. */
};

/**
 *  The Keypad RAM structure used to store volatile parameters of the control.
 *
 *  You must allocate this structure and put a pointer into the ft_control_keypad
 *  structure when it is being registered in the system.
 */
struct ft_control_keypad_data {
    uint32_t                    last_state;                   /**< Last state of keypad electrodes. */
    uint32_t                    last_key_state;               /**< Last state of keypad keys. */
    ft_control_keypad_callback  callback;                     /**< Keypad callback handler. */
    uint16_t                    autorepeat_rate;              /**< Autorepeat rate. */
    uint32_t                    start_autorepeat_rate;        /**< Start Autorepeat rate. */
    uint32_t                    repeat_time;                  /**< Time of next autorepeat event. */
    int32_t                     last_electrode;               /**< Last touched electrode index. */
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/** \} end of keypad_private group */

#endif
