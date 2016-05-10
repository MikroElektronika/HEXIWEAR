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
 *   list of conditions, and the following disclaimer in the documentation, and/or
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
#ifndef FT_AROTARY_H
#define FT_AROTARY_H

/**
 * \defgroup arotary Analog Rotary Control
 * \ingroup controls
 *
 * Analog Rotary enables the detection of jog-dial-like finger movement using three or more electrodes;
 * it is represented by the ft_control structure.
 *
 * The Analog Rotary Control uses three or more specially-shaped electrodes to enable
 * the calculation of finger position within a circular area. The position algorithm uses the
 * ratio of sibling electrode signals to estimate the finger position with the required precision.
 *
 * The Analog Rotary works similarly to the "standard" Rotary, but requires less
 * electrodes, while achieving a higher resolution of the calculated position. For
 * example, a four-electrode Analog Rotary can provide the finger position detection in the
 * range of 0-64. The shape of the electrodes needs to be designed specifically to achieve
 * a stable signal with a linear dependence on finger movement.
 *
 * The Analog Rotary Control provides Position, Direction, and Displacement values. It
 * is able to generate event callbacks when finger Movement, Initial-touch, or Release is detected.
 *
 * The image below shows a typical four-electrode Analog Rotary electrode placement.
 * \image html arotary.png "Analog Rotary Electrodes"
 * \image latex arotary.png "Analog Rotary Electrodes"
 *
 * \{
 */

#include "ft_controls.h"
#include "ft_types.h"

/** Analog Rotary event types. */
enum ft_control_arotary_event {
    FT_AROTARY_MOVEMENT      = 0,  /**< Finger movement event. */
    FT_AROTARY_ALL_RELEASE   = 1,  /**< Release event. */
    FT_AROTARY_INITIAL_TOUCH = 2,  /**< Initial-touch event. */
};

/**
 * Analog Rotary event callback function pointer type.
 */
typedef void (* ft_control_arotary_callback)(const struct ft_control *control,
                                             enum ft_control_arotary_event event,
                                             uint32_t position);

/**
 *  The main structure representing the Analog Rotary Control.
 *
 *  An instance of this data type represents the Analog Rotary Control. You are
 *  responsible to initialize all the members before registering the control in
 *  the system. This structure can be allocated in ROM.
 *
 */
struct ft_control_arotary {
    uint8_t               range;   /**< Range. */
};




/** An interface structure, which contains pointers to the entry points of the Analog
 *  Rotary algorithms. A pointer to this structure must be assigned to any
 *  instance of the ft_control to define the control behavior. */
extern const struct ft_control_interface ft_control_arotary_interface;    /**< Can't be NULL. */

/**
 * \defgroup arotary_api Analog Rotary Control API
 * \ingroup arotary
 *
 * These functions can be used to set or get the Analog Rotary control properties.
 *
 * A common example defition of the Analog Rotary control for all source code examples is as follows:
 * \code
 *  // definition of the electrode array used by the control (more info in electrodes )
 *  const struct ft_electrode  * const control_0_electrodes[] = {&electrode_0, &electrode_1,
 *    &electrode_2, &electrode_3, NULL};
 *
 *  // Define additional parameters of the Analog Rotary
 *  const struct ft_control_arotary my_arotary_params =
 *  {
 *   .range = 255,
 *  };
 *
 *  // Definition of the Analog Rotary control
 *  const struct ft_control my_arotary_control =
 *  {
 *    .interface = &ft_control_arotary_control_interface,
 *    .electrodes = control_0_electrodes,
 *    .control_params.arotary = &my_arotary_params,
 *  };
 *
 * \endcode
 * \{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Registers the Analog Rotary events handler function.
 * \param control  Pointer to the control.
 * \param callback Address of function to be invoked.
 * \return none
 *
 * Register the specified callback function as the Analog Rotary events handler.
 * If the callback parameter is NULL, the callback is disabled.
 * Example:
 * \code
 *  
 *  //Create the callback function for arotary
 *  static void my_arotary_cb(const struct ft_control *control,
 *                            enum ft_control_arotary_event event,
 *                            uint32_t position)
 *  {
 *    (void)control;
 *    char* event_names[] = 
 *     {
 *      "FT_AROTARY_MOVEMENT",     
 *      "FT_AROTARY_ALL_RELEASE",  
 *      "FT_AROTARY_INITIAL_TOUCH",
 *      };
 *    printf("New analog rotary control event %s on position: %d.", event_names[event], position);
 *  }
 *
 *  // register the callback function for arotary
 *  ft_control_arotary_register_callback(&my_arotary_control, my_arotary_cb);
 * \endcode
 */
void ft_control_arotary_register_callback(const struct ft_control *control,
                                           ft_control_arotary_callback callback);

/**
 * \brief Get the Analog Rotary 'Position' value.
 * \param control Pointer to the control.
 * \return Position. The returned value is in the range of zero to the maximum
 *         value configured in the ft_control structure.
 *
 * This function retrieves the actual finger position value.
 * Example:
 * \code
 * uint32_t position; 
 * // Get position of arotary control
 * position = ft_control_arotary_get_position(&my_arotary_control);
 * printf("Position of Analog Rotary control is: %d.", position);
 * \endcode
 */
uint32_t ft_control_arotary_get_position(const struct ft_control *control);

/**
 * \brief Get 'Touched' state.
 * \param control Pointer to the control.
 * \return Non-zero value, if the control is currently touched.
 * Example:
 * \code
 * uint32_t touched; 
 * // Get state of arotary control
 * touched = ft_control_arotary_is_touched(&my_arotary_control);
 * if(touched)
 *      printf("The Analog Rotary control is currently touched.");
 * else
 *      printf("The Analog Rotary control is currently not touched.);
 * \endcode
 */
uint32_t ft_control_arotary_is_touched(const struct ft_control *control);

/**
 * \brief Get 'Movement' flag.
 * \param control Pointer to the control.
 * \return Non-zero value, if the control currently detects finger movement.
 * Example:
 * \code
 * uint32_t movement; 
 * // Get state of arotary control
 * movement = ft_control_arotary_movement_detected(&my_arotary_control);
 * if(movement)
 *      printf("The Analog Rotary control is currently moving.");
 * else
 *      printf("The Analog Rotary control is currently not moving.);
 * \endcode
 */
uint32_t ft_control_arotary_movement_detected(const struct ft_control *control);

/**
 * \brief Get 'Direction' flag.
 * \param control Pointer to the control.
 * \return
 *   - Non-zero value, if a movement towards higher values is detected.
 *   - Returns zero, if a movement towards zero is detected.
 * Example:
 * \code
 * uint32_t direction; 
 * // Get direction of arotary control
 * direction = ft_control_arotary_get_direction(&my_arotary_control);
 * if(direction)
 *      printf("The Analog Rotary direction is left.");
 * else
 *      printf("The Analog Rotary direction is right.");
 * \endcode
 */
uint32_t ft_control_arotary_get_direction(const struct ft_control *control);

/**
 * \brief Returns invalid position flag.
 * \param control Pointer to the control.
 * \return Non-zero value, if an invalid touch is detected.
 *
 * This flag is set, if the algorithm detects two or more fingers touching the
 * electrodes, which are not adjacent to each other.
 * Example:
 * \code
 * uint32_t invalid_position; 
 * // Get invalid position of arotary control
 * invalid_position = ft_control_arotary_get_invalid_position(&my_arotary_control);
 * if(invalid_position)
 *      printf("The Analog Rotary control has an invalid position (two fingers touch ?).");
 * else
 *      printf("The Analog Rotary control has a valid position.");
 * \endcode
 */
uint32_t ft_control_arotary_get_invalid_position(const struct ft_control *control);

/** \} end of arotary_api group */
/** \} end of arotary group */

#ifdef __cplusplus
}
#endif

#endif
