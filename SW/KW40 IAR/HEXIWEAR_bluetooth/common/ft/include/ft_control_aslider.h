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
#ifndef FT_ASLIDER_H
#define FT_ASLIDER_H

/**
 * \defgroup aslider Analog Slider Control
 * \ingroup controls
 *
 * Analog Slider enables detection of linear finger movement using two or more electrodes;
 * it is represented by the ft_control_aslider structure.
 *
 * The Analog Slider Control uses two or more specially-shaped electrodes to enable
 * the calculation of finger position within a linear area. The position algorithm uses
 * ratio of electrode signals to estimate finger position with required precision.
 *
 * The Analog Slider works similarly to the "standard" Slider, but requires less
 * electrodes, while achieving a higher resolution of the calculated position. For
 * example, a two-electrode analog slider can provide finger position detection in the
 * range of 0-127. The shape of the electrodes needs to be designed specifically to achieve
 * a stable signal with a linear dependence on finger movement.
 *
 * The Analog Slider Control provides Position, Direction, and Displacement values. It
 * is able to generate event callbacks when finger Movement, Initial-touch, or Release
 * is detected.
 *
 * The figure below shows a typical two-electrode Analog Slider electrode placement.
 * \image html aslider.png "Analog Slider Electrodes"
 * \image latex aslider.png "Analog Slider Electrodes"
 *
 * \{
 */

#include "ft_controls.h"
#include "ft_types.h"

/** Analog Slider event types. */
enum ft_control_aslider_event {
    FT_ASLIDER_MOVEMENT      = 0,  /**< Finger movement event */
    FT_ASLIDER_ALL_RELEASE   = 1,  /**< Release event */
    FT_ASLIDER_INITIAL_TOUCH = 2,  /**< Initial-touch event */
};


/**
 * Analog Slider event callback function pointer type.
 */
typedef void (* ft_control_aslider_callback)(const struct ft_control *control,
                                             enum ft_control_aslider_event event,
                                             uint32_t position);

/**
 *  The main structure representing the Analog Slider Control.
 *
 *  An instance of this data type represents the Analog Slider Control. You are
 *  responsible to initialize all the members before registerring the control in
 *  the system. This structure can be allocated in ROM.
 */
struct ft_control_aslider {
    uint8_t                range;  /**< Maximum range for the ram->position value. */
    uint8_t                insensitivity;  /**< Insensitivity for the callbacks invokes when the position is changed. */
};

/** An interface structure, which contains pointers to the entry points of the Analog
 *  Slider algorithms. A pointer to this structure must be assigned to any
 *  instace of the ft_control_aslider to define the control behavior. */
extern const struct ft_control_interface ft_control_aslider_interface;

/**
 * \defgroup aslider_api Analog Slider Control API
 * \ingroup aslider
 *
 * These functions can be used to set or get the Analog Slider control properties.
 *
 * Common example definition of the Analog Slider control for all source code examples is as follows:
 * \code
 *  // definition of the electrode array used by the control (more info in electrodes )
 *  const struct ft_electrode  * const control_0_electrodes[] = {&electrode_0, &electrode_1,
 *    NULL};
 *
 *  // Define additional parameters of Analog Slider
 *  const struct ft_control_aslider my_aslider_params =
 *  {
 *   .range = 100,
 *  };
 *
 *  // Definition of the Analog Slider control
 *  const struct ft_control my_aslider_control =
 *  {
 *    .interface = &ft_control_aslider_control_interface,
 *    .electrodes = control_0_electrodes,
 *    .control_params.aslider = &my_aslider_params,
 *  };
 *
 * \endcode
 * \{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Registers the Analog Slider events handler function.
 * \param control  Pointer to the control.
 * \param callback Adress of the function to be invoked.
 * \return none
 *
 * Register the specified callback function as the Analog Slider events handler.
 * If the callback parameter is NULL, the callback is disabled.
 * Example:
 * \code
 *  
 *  //Create the callback function for aslider
 *  static void my_aslider_cb(const struct ft_control *control,
 *                            enum ft_control_aslider_event event,
 *                            uint32_t position)
 *  {
 *    (void)control;
 *    char* event_names[] = 
 *     {
 *      "FT_ASLIDER_MOVEMENT",     
 *      "FT_ASLIDER_ALL_RELEASE",  
 *      "FT_ASLIDER_INITIAL_TOUCH",
 *      };
      printf("New analog slider control event %s on position: %d.", event_names[event], position);
    }
  
    // register the callback function for aslider movement
    ft_control_aslider_register_callback(&my_aslider_control, my_aslider_cb);
   \endcode
 */
void ft_control_aslider_register_callback(const struct ft_control *control,
                                           ft_control_aslider_callback callback);

/**
 * \brief Get the Analog Slider 'Position' value.
 * \param control Pointer to the control.
 * \return Position. The returned value is in the range of zero to maximum
 *         value configured in the ft_control_aslider structure.
 *
 * This function retrieves the actual finger position value.
 * Example:
 * \code
 * uint32_t position; 
 * // Get position of aslider control
 * position = ft_control_aslider_get_position(&my_aslider_control);
 * printf("Position of analog slider control is: %d.", position);
 * \endcode
 */
uint32_t ft_control_aslider_get_position(const struct ft_control *control);

/**
 * \brief Get 'Touched' state.
 * \param control Pointer to the control.
 * \return Non-zero value, when the control is currently touched.
 * Example:
 * \code
 * uint32_t touched; 
 * // Get state of aslider control
 * touched = ft_control_aslider_is_touched(&my_aslider_control);
 * if(touched)
 *      printf("The Analog Slider control is currently touched.");
 * else
 *      printf("The Analog Slider control is currently not touched.);
 * \endcode
 */
uint32_t ft_control_aslider_is_touched(const struct ft_control *control);

/**
 * \brief Get 'Movement' flag.
 * \param control Pointer to the control.
 * \return Non-zero value, if the control currently detects finger movement.
 * Example:
 * \code
 * uint32_t movement; 
 * // Get state of aslider control
 * movement = ft_control_aslider_movement_detected(&my_aslider_control);
 * if(movement)
 *      printf("The Analog Slider control is currently moving.");
 * else
 *      printf("The Analog Slider control is currently not moving.);
 * \endcode
 */
uint32_t ft_control_aslider_movement_detected(const struct ft_control *control);

/**
 * \brief Get 'Direction' flag.
 * \param control Pointer to the control.
 * \return Non-zero value, when a movement towards higher
 *         values is detected. Returns zero when a movement towards zero is detected.
 * Example:
 * \code
 * uint32_t direction; 
 * // Get direction of aslider control
 * direction = ft_control_aslider_get_direction(&my_aslider_control);
 * if(direction)
 *      printf("The Analog Slider direction is left.");
 * else
 *      printf("The Analog Slider direction is right.");
 * \endcode
 */
uint32_t ft_control_aslider_get_direction(const struct ft_control *control);

/**
 * \brief Returns invalid position flag.
 * \param control Pointer to the control.
 * \return Non-zero value, when an invalid touch is detected.
 *
 * This function works only in the Analog Slider controls, constisting of at least
 * three elecrodes. This flag is set when the algorithm detects two or more fingers
 * touching the electrodes that are not adjacent to each other.
 * Example:
 * \code
 * uint32_t invalid_position; 
 * // Get invalid position of aslider control
 * invalid_position = ft_control_aslider_get_invalid_position(&my_aslider_control);
 * if(invalid_position)
 *      printf("The Analog Slider control has an invalid position (two fingers touch ?).");
 * else
 *      printf("The Analog Slider control has a valid position.");
 * \endcode
 */
uint32_t ft_control_aslider_get_invalid_position(const struct ft_control *control);

#ifdef __cplusplus
}
#endif

/** \} end of aslider_api group */
/** \} end of aslider group */

#endif
