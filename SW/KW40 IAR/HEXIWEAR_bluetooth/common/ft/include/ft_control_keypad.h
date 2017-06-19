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
#ifndef FT_KEYPAD_H
#define FT_KEYPAD_H

/**
 * \defgroup keypad Keypad Control
 * \ingroup controls
 *
 * Keypad implements the keyboard-like functionality on top of an array of
 * electrodes; it is represented by the ft_control_keypad structure.
 *
 * The application may use the Electrode API to determine the touch or release states
 * of individual electrodes. The Keypad simplifies this task, and extends this
 * simple scenario by introducing a concept of a "key". The "key" is represented
 * by one or more physical electrodes, therefore the Keypad control enables sharing of one
 * electrode by several keys. Each key is defined by a set of electrodes that
 * all must be touched, in order to report the "key press" event.
 *
 * The Keypad Control provides the Key status values and is able to generate Key Touch,
 * Auto-repeat, and Release events.
 *
 * The figures below show simple and grouped Keypad electrode layouts.
 * \image html keypad.png "Keypad Electrodes"
 * \image latex keypad.png "Keypad Electrodes"
 *
 * \{
 */

#include "ft_controls.h"
#include "ft_types.h"

/** Keypad event types. */
enum ft_control_keypad_event {
    FT_KEYPAD_RELEASE    = 0, /**< Release event */
    FT_KEYPAD_TOUCH      = 1, /**< Key-touch event */
    FT_KEYPAD_AUTOREPEAT = 2  /**< Auto-repeat event */
};

/**
 * Keypad event callback function pointer type.
 */
typedef void (* ft_control_keypad_callback)(const struct ft_control *control,
                                    enum ft_control_keypad_event event,        
                                    uint32_t index);

/**
 *  The main structure representing the Keypad Control.
 *
 *  An instance of this data type represents the Keypad Control. You must initialize all the members before registerring the control in
 *  the system. This structure can be allocated in ROM.
 *
 */
struct ft_control_keypad {
    uint32_t const       *groups;     /**< Pointer to the group definitions. An array
                                           of integers, where bits in the integer represents
                                           electrodes in a group.*/
    uint8_t              groups_size; /**< Number of groups. */
};

/** An interface structure, which contains pointers to the entry points of the Keypad
 *  algorithms. A pointer to this structure must be assigned to any
 *  instance of the ft_control_keypad, to define the control behavior. */
extern const struct ft_control_interface ft_control_keypad_interface;

/**
 * \defgroup keypad_api Keypad Control API
 * \ingroup keypad
 *
 * These functions can be used to set or get the Keypad control properties.
 *
 * A common example defition of the Keypad control for all source code examples is as follows:
 * \code
 *  // definition of electrode array used by control (more info in electrodes )
 *  const struct ft_electrode  * const control_0_electrodes[] = {&electrode_0, &electrode_1,
 *    &electrode_2, &electrode_3, NULL};
 *
 *  const struct ft_control_keypad keypad_params =
 *  {
 *     .groups = NULL,
 *     .groups_size = 0,
 *  };
 *
 *  // Definition of rotary control
 *  const struct ft_control my_keypad_control =
 *  {
 *    .interface = &ft_control_keypad_control_interface,
 *    .electrodes = control_0_electrodes,
 *    .control_params.keypad = keypad_params,
 *  };
 *
 * \endcode
 * \{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Enable or disable the functionality that only one key press is valid.
 * \param control   Pointer to the control.
 * \param enable    enable the only one key pressed is valid.
 * \return none
 *
 * Enable or Disable the only one key press is valid at once. The behavior is following:
 * Once the feature is enabled the first touched key is valid and all other are ignored 
 * since the active electrode is pressed.
 * Example:
 * \code
 *  
 *  // switch off the only one key is valid functionality
 *  ft_control_keypad_only_one_key_valid(&my_keypad_control, 0);
 * \endcode
 */  
void ft_control_keypad_only_one_key_valid(const struct ft_control *control,
                                       uint32_t enable);

/**
 * \brief Registers the Keypad event handler function.
 * \param control  Pointer to the control.
 * \param callback Adress of function to be invoked.
 * \return none
 *
 * Register the specified callback function as the KeyPad event handler.
 * If the callback parameter is NULL, the callback is disabled.
 * Example:
 * \code
 *  
 *  //Create the callback function for keypad
 *  static void my_keypad_cb(const struct ft_control *control,
 *                           enum ft_control_keypad_event event,
 *                           uint32_t index)
 *  {
 *    (void)control;
 *     char* event_names[] = 
 *     {
 *      "FT_KEYPAD_RELEASE",
 *      "FT_KEYPAD_TOUCH",
 *      "FT_KEYPAD_AUTOREPEAT",
*      };
 *
 *    printf("New keypad control event %s on key: %d.", event_names[event], index);
 *  }
 *
 *  // register the callback function for keypad 
 *  ft_control_keypad_register_touch_callback(&my_keypad_control, my_keypad_touch_cb);
 * \endcode
 */
void ft_control_keypad_register_callback(const struct ft_control *control,
                                       ft_control_keypad_callback callback);

/**
 * \brief Set the auto-repeat rate.
 * \param control Pointer to the Keypad control.
 * \param value Auto-repeat value. Value 0 disables the auto-repeat feature.
 * \param value Auto-repeat start value. Value 0 disables the auto-repeat start feature.
 * \return none
 * Example:
 * \code
 *  
 *  //Set autorepeat rate to 100 ticks and start after 1000 ticks
 *  ft_control_keypad_set_autorepeat_rate(&my_keypad_control, 100, 1000);
 * \endcode
 */
void ft_control_keypad_set_autorepeat_rate(const struct ft_control *control,
                                   uint32_t value, uint32_t start_value);

/**
 * \brief Get the auto-repeat rate.
 * \param control Pointer to the Keypad control.
 * \return The auto-repeat value or 0 when this feature is disabled.
 * Example:
 * \code
 *  uint32_t autorepeat_rate;
 *  //Get autorepeat rate
 *  autorepeat_rate = ft_control_keypad_get_autorepeat_rate(&my_keypad_control);
 *  printf("Auto-repeat rate of my keypad control is set to : %d.", autorepeat_rate);
 * \endcode
 */
uint32_t ft_control_keypad_get_autorepeat_rate(const struct ft_control *control);

/**
 * \brief Get the button touch status.
 * \param control Pointer to the Keypad control.
 * \param index   The button's number (index) in the control.
 * \return 1 if the button is touched,
 *         0 otherwise.
 *
 * Returns the state of the keypad button. In case there are groups defined, the touch
 * state reflects that all electrodes forming one button are touched. Otherwise, a button is
 * in the release state.
 * Example:
 * \code
 * uint32_t touched; 
 * // Get the state of first key Keypad control
 * touched = ft_control_keypad_is_button_touched(&my_keypad_control, 0);
 * if(touched)
 *      printf("The first key of the Keypad control is currently touched.");
 * else
 *      printf("The first key of the Keypad control is currently not touched.);
 * \endcode
 */
uint32_t ft_control_keypad_is_button_touched(const struct ft_control *control,
                                     uint32_t index);

/** \} end of keypad_api group */
/** \} end of keypad group */

#ifdef __cplusplus
}
#endif

#endif
