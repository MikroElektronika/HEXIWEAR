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
#ifndef FT_SLIDER_H
#define FT_SLIDER_H

/**
 * \defgroup slider Slider control
 * \ingroup controls
 *
 * Slider control enables the detection of linear finger movement using discrete electrodes;
 * it is represented by the ft_control structure.
 *
 * The Slider control uses a set of discrete electrodes to enable calculation of the finger
 * position within a linear area. The position algorithm localizes the touched
 * electrode and its sibling electrodes to estimate finger position. A Slider consisting
 * of N electrodes enables the position to be calculated in 2N-1 steps.
 *
 * The Slider control provides Position, Direction, and Displacement values. It
 * is able to generate event callbacks when finger Movement, Initial-touch, or Release
 * is detected.
 *
 * The image below shows a typical Slider electrode placement.
 * \image html slider.png "Slider Electrodes"
 * \image latex slider.png "Slider Electrodes"
 *
 * \{
 */

#include "ft_controls.h"
#include "ft_types.h"

/** Slider event types. */
enum ft_control_slider_event {
    FT_SLIDER_MOVEMENT      = 0,  /**< Finger movement event. */
    FT_SLIDER_ALL_RELEASE   = 1,  /**< Release event. */
    FT_SLIDER_INITIAL_TOUCH = 2,  /**< Initial-touch event. */
};



/* forward declarations */

/**
 * Slider event callback function pointer type.
 */
typedef void (* ft_control_slider_callback)(const struct ft_control *control,
                                            enum ft_control_slider_event,
                                            uint32_t position);

/** An interface structure, which contains pointers to the entry points of
 *  Slider algorithms. A pointer to this structure must be assigned to any
 *  instace of ft_control_slider_control to define the control behavior. */
extern const struct ft_control_interface ft_control_slider_interface;

/**
 * \defgroup slider_api Slider Control API
 * \ingroup slider
 *
 * These functions can be used to set or get the Slider control properties.
 *
 * A common example definition of the Slider control for all source code examples is as follows:
 * \code
 *  // Definition of the electrode array used by the control (more info in electrodes)
 *  const struct ft_electrode  * const control_0_electrodes[] = {&electrode_0, &electrode_1,
 *    NULL};
 *
 *  // Definition of the Slider control
 *  const struct ft_control my_slider_control =
 *  {
 *    .interface = &ft_control_slider_interface,
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
 * Register the specified callback function as the Slider events handler.
 * Example:
 * \code
 *  
 *  //Create the callback function for aslider
 *  static void my_slider_cb(const struct ft_control *control,
 *                            enum ft_control_aslider_event event,
 *                            uint32_t position)
 *  {
 *    (void)control;
 *    char* event_names[] = 
 *     {
 *      "FT_SLIDER_MOVEMENT",     
 *      "FT_SLIDER_ALL_RELEASE",  
 *      "FT_SLIDER_INITIAL_TOUCH",
 *      };
 *    printf("New slider control event %s on position: %d.", event_names[event], position);
 *  }
 *
 *  // register the callback function for slider
 *  ft_control_slider_register_callback(&my_slider_control, my_slider_cb);
 * \endcode
 */
void ft_control_slider_register_callback(const struct ft_control *control,
                                         ft_control_slider_callback callback);
/**
 * \brief Get the Slider 'Position' value.
 * \param control Pointer to the control.
 * \return Position. The returned value is in the range of zero to the maximum
 *         value configured in the ft_control structure.
 *
 * This function retrieves the actual finger position value.
 * Example:
 * \code
 * uint32_t position; 
 * // Get position of Slider control
 * position = ft_control_slider_get_position(&my_slider_control);
 * printf("Position of Slider control is: %d.", position);
 * \endcode
 */
uint32_t ft_control_slider_get_position(const struct ft_control *control);

/**
 * \brief Get 'Touched' state.
 * \param control Pointer to the control.
 * \return Non-zero value, when the control is currently touched.
 * Example:
 * \code
 * uint32_t touched; 
 * // Get state of Slider control
 * touched = ft_control_slider_is_touched(&my_slider_control);
 * if(touched)
 *      printf("The Slider control is currently touched.");
 * else
 *      printf("The Slider control is currently not touched.");
 * \endcode
 */
uint32_t ft_control_slider_is_touched(const struct ft_control *control);

/**
 * \brief Get 'Movement' flag.
 * \param control Pointer to the control.
 * \return Non-zero value, when the control detects finger movement.
 * Example:
 * \code
 * uint32_t movement; 
 * // Get state of Slider control
 * movement = ft_control_slider_movement_detected(&my_slider_control);
 * if(movement)
 *      printf("The Slider control is currently moving.");
 * else
 *      printf("The Slider control is currently not moving.");
 * \endcode
 */
uint32_t ft_control_slider_movement_detected(const struct ft_control *control);

/**
 * \brief Get 'Direction' flag.
 * \param control Pointer to the control.
 * \return Non-zero value, when a movement is detected in a direction towards higher
 *         values. Returns zero, when a movement towards zero is detected.
 * Example:
 * \code
 * uint32_t direction; 
 * // Get direction of Slider control
 * direction = ft_control_slider_get_direction(&my_slider_control);
 * if(direction)
 *      printf("The Slider direction is left.");
 * else
 *      printf("The Slider direction is right.");
 * \endcode
 */
uint32_t ft_control_slider_get_direction(const struct ft_control *control);

/**
 * \brief Get 'Invalid' flag.
 * \param control Pointer to the control.
 * \return Non-zero value, when an invalid position was detected,
 *         otherwise zero.
 * Example:
 * \code
 * uint32_t invalid_position; 
 * // Get invalid position of Slider control
 * invalid_position = ft_control_slider_get_invalid_position(&my_slider_control);
 * if(invalid_position)
 *      printf("The Slider control has an invalid position (two fingers touch ?).");
 * else
 *      printf("The Slider control has a valid position.");
 * \endcode
 */
uint32_t ft_control_slider_get_invalid_position(const struct ft_control *control);


/** \} end of slider_api group */
/** \} end of slider group */

#ifdef __cplusplus
}
#endif

#endif
