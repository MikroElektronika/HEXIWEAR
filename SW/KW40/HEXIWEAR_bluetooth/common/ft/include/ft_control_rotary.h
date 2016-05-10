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
#ifndef FT_ROTARY_H
#define FT_ROTARY_H

/**
 * \defgroup rotary Rotary Control
 * \ingroup controls
 *
 * The Rotary control enables the detection of jog-dial-like finger movement using discrete
 * electrodes; it is represented by the ft_control_rotary_control structure.
 *
 * The Rotary control uses a set of discrete electrodes to enable the calculation of finger
 * position within a circular area. The position algorithm localizes the touched
 * electrode and its sibling electrodes, to estimate the finger position. A Rotary control consisting
 * of N electrodes enables the rotary position to be calculated in 2N steps.
 *
 * The Rotary control provides Position, Direction, and Displacement values. It
 * is able to generate event callbacks when the finger Movement, Initial-touch, or Release is detected.
 *
 * The figure below shows a typical Rotary electrode placement.
 * \image html rotary.png "Rotary Electrodes"
 * \image latex rotary.png "Rotary Electrodes"
 *
 * \{
 */

#include "ft_controls.h"
#include "ft_types.h"

/** Rotary event types. */
enum ft_control_rotary_event {
    FT_ROTARY_MOVEMENT      = 0,  /**< Finger movement event */
    FT_ROTARY_ALL_RELEASE   = 1,  /**< Release event */
    FT_ROTARY_INITIAL_TOUCH = 2,  /**< Initial-touch event */
};


/**
 * Rotary event callback function pointer type.
 */
typedef void (* ft_control_rotary_callback)(const struct ft_control *control,
                                            enum ft_control_rotary_event,
                                            uint32_t position);

/** The interface structure, which contains pointers to the entry points of the
 *  Rotary algorithms. A pointer to this structure must be assigned to any
 *  instance of ft_control_rotary_control to define the control behavior. */
extern const struct ft_control_interface ft_control_rotary_interface;

/**
 * \defgroup rotary_api Rotary Control API
 * \ingroup rotary
 *
 * These functions can be used to set or get the Rotary control properties.
 *
 * The common example defition of Rotary control for all source code examples is as follows:
 * \code
 *  // definition of electrode array used by control (more info in electrodes )
 *  const struct ft_electrode  * const control_0_electrodes[] = {&electrode_0, &electrode_1,
 *    &electrode_2, &electrode_3, NULL};
 *
 *  // Definition of the Rotary control
 *  const struct ft_control my_rotary_control =
 *  {
 *    .interface = &ft_control_rotary_interface,
 *    .electrodes = control_0_electrodes,
 *  };
 *
 * \endcode
 * \{
 */


#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Registers the events handler function.
 * \param control  Pointer to the control.
 * \param callback Adress of function to be invoked.
 * \return none
 *
 * Register the specified callback function as the Rotary events handler.
 * Example:
 * \code
 *  
 *  //Create the callback function for arotary
 *  static void my_rotary_cb(const struct ft_control *control,
 *                            enum ft_control_arotary_event event,
 *                            uint32_t position)
 *  {
 *    (void)control;
 *    char* event_names[] = 
 *     {
 *      "FT_ROTARY_MOVEMENT",     
 *      "FT_ROTARY_ALL_RELEASE",  
 *      "FT_ROTARY_INITIAL_TOUCH",
 *      };
 *    printf("New rotary control event %s on position: %d.", event_names[event], position);
 *  }
 *
 *  // register the callback function for rotary
 *  ft_control_rotary_register_callback(&my_rotary_control, my_rotary_cb);
 * \endcode
 */
void ft_control_rotary_register_callback(const struct ft_control *control,
                                         ft_control_rotary_callback callback);

/**
 * \brief Get the Rotary 'Position' value.
 * \param control Pointer to the control.
 * \return Position. The returned value is in the range of zero to 2N-1, where N is
 *     the number of electrodes assigned to Rotary control.
 *
 * This function retrieves the actual finger position value.
 * Example:
 * \code
 * uint32_t position; 
 * // Get position of Rotary control
 * position = ft_control_rotary_get_position(&my_rotary_control);
 * printf("Position of Rotary control is: %d.", position);
 * \endcode
 */
uint32_t ft_control_rotary_get_position(const struct ft_control *control);

/**
 * \brief Get 'Touched' state.
 * \param control Pointer to the control.
 * \return Non-zero value, when the control is currently touched.
 * Example:
 * \code
 * uint32_t touched; 
 * // Get state of the Rotary control
 * touched = ft_control_rotary_is_touched(&my_rotary_control);
 * if(touched)
 *      printf("The Rotary control is currently touched.");
 * else
 *      printf("The Rotary control is currently not touched.);
 * \endcode
 */
uint32_t ft_control_rotary_is_touched(const struct ft_control *control);

/**
 * \brief Get 'Movement' flag.
 * \param control Pointer to the control.
 * \return Non-zero value, when the control detects finger movement.
 * Example:
 * \code
 * uint32_t movement; 
 * // Get state of rotary control
 * movement = ft_control_rotary_movement_detected(&my_rotary_control);
 * if(movement)
 *      printf("The Rotary control is currently moving.");
 * else
 *      printf("The Rotary control is currently not moving.);
 * \endcode
 */
uint32_t ft_control_rotary_movement_detected(const struct ft_control *control);

/**
 * \brief Get 'Direction' flag.
 * \param control Pointer to the control.
 * \return Non-zero value, when a movement is detected in a direction towards higher
 *         values. Returns zero, when a movement is detected towards zero.
 * Example:
 * \code
 * uint32_t direction; 
 * // Get direction of rotary control
 * direction = ft_control_rotary_get_direction(&my_rotary_control);
 * if(direction)
 *      printf("The Rotary direction is left.");
 * else
 *      printf("The Rotary direction is right.");
 * \endcode
 */
uint32_t ft_control_rotary_get_direction(const struct ft_control *control);

/**
 * \brief Get 'Invalid' flag.
 * \param control Pointer to the control.
 * \return Non-zero value when an invalid position was detected,
 *         otherwise a zero value.
 * Example:
 * \code
 * uint32_t invalid_position; 
 * // Get invalid position of Rotary control
 * invalid_position = ft_control_rotary_get_invalid_position(&my_rotary_control);
 * if(invalid_position)
 *      printf("The Rotary control has an invalid position (two fingers touch ?).");
 * else
 *      printf("The Rotary control has a valid position.");
 * \endcode
 */
uint32_t ft_control_rotary_get_invalid_position(const struct ft_control *control);



#ifdef __cplusplus
}
#endif

/** \} */ // end of rotary_api group
/** \} */ // end of rotary group
  
#endif
