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
#ifndef FT_CONTROLS_PRV_H
#define FT_CONTROLS_PRV_H

/**
 * \defgroup controls_private Controls
 * \ingroup ftapi_private
 *
 * Controls represent the highest level of abstraction in the finger touch evaluation;
 * the generic control object used as a base for other "derived" control types is
 * represented by the ft_control structure.
 *
 * Based on the signal and status information coming from the Electrode layer, the controls
 * calculate finger actions like movement, keyboard touch, hold and so on.
 * \{
 */

#include "ft_types.h"
#include "ft_electrodes.h"

/* forward declarations */
struct ft_electrode;
struct ft_control;
struct ft_control_data;
struct ft_control_interface;

/**
 * \defgroup gcontrols_private General API
 * \ingroup controls_private
 * General Function definition of controls.
 *
 * \{
 */

/** Controls flags which can be set / cleared.
 */
enum ft_control_flags {
    FT_CONTROL_NEW_DATA_FLAG  = 1 << FT_FLAGS_SYSTEM_SHIFT(0),  /**< Indication flag that the control has new data. */
    FT_CONTROL_EN_FLAG        = 1 << FT_FLAGS_SYSTEM_SHIFT(1),  /**< Control Enable flag. */
};

/**
 * The pointer to the special data of the control. Each control type has its own type
 * of the data structure, and the pointers to these special data structures are handled
 * by this union, to keep the clearance of the types.
 */
union ft_control_special_data
{
  struct ft_control_arotary_data           * arotary;  /**< Pointer to the Analog Rotary control special data. */
  struct ft_control_aslider_data           * aslider;  /**< Pointer to the Analog Slider control special data. */
  struct ft_control_keypad_data            * keypad;  /**< Pointer to the Keypad control special data. */
  struct ft_control_rotary_data            * rotary;  /**< Pointer to the Rotary control special data. */
  struct ft_control_slider_data            * slider;  /**< Pointer to the Slider control special data. */
  void                                     * general; /**< Just one point of view on this union for a general sanity check. */ 
};

/**
 *  The Control RAM structure used to store volatile parameters, flags, and other data to enable
 *  a generic behavior of the Control. You must allocate this structure and put a pointer
 *  into the ft_control structure when the control is being registered in the system.
 */
struct ft_control_data {
  const struct ft_control           *rom;               /**< The pointer to user control parameter structure. */
  union ft_control_special_data     data;               /**< The pointer to the control data structure. */
  struct ft_electrode_data          **electrodes;       /**< List of electrodes. Can't be NULL. */
  uint32_t                          flags;              /**< Flags. */
  uint8_t                           electrodes_size;    /**< Number of electrodes. */
};

/**
 *  Control interface structure; each control uses this structure to register the entry points
 *  to its algorithms. This approach enables a kind-of polymorphism in the touch System.
 *  All controls are processed in the same way from the System layer, regardless of the specific
 *  implementation. Each control type defines one static constant structure of this type to
 *  register its own initialization and processing functions.
 */
struct ft_control_interface {
  int32_t (* init)(struct ft_control_data *control);    /**< The adress of init function. */
  int32_t (* process)(struct ft_control_data *control); /**< The adress of process function. */
  const char* name;                                     /**< The name of the varible of this type, used for FreeMASTER support purposes. */
};

/**
 * \defgroup gcontrols_api_private API Functions
 * \ingroup gcontrols_private
 *
 * The functions in this category can be used to manipulate the Control objects.
 * \{
 */

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief Get control data structure pointer.
 * \param control Pointer to the control user parameter structure.
 * \return Pointer to the data control structure that is represented by the handled user parameter structure pointer.        
 */
struct ft_control_data *_ft_control_get_data(const struct ft_control *control);

/**
 * \brief Initialize the control object.
 * \param control Pointer to the control.
 * \return Pointer to create the control data structure. In case of a fail it returns NULL.
 *
 * The function creates and initializes the control data structure, including the 
 * special data of the selected control (keypad, rotary, and so on).
 */
struct ft_control_data *_ft_control_init(const struct ft_control *control);

/**
 * \brief Validate control data.
 * \param control Pointer to the control data.
 * \return Status code.
 *
 * Checking, whether the control data structure is sane; the interface, ram, and electrodes
 * array should not be NULL.
 */
int32_t _ft_control_check_data(const struct ft_control_data *control);


/**
 * \brief Get the state of all control electrodes.
 * \param control Pointer to the control data.
 * \return This function returns a bit-mask value where each bit represents one
 *         control electrode. Logic 1 in the returned value represents a touched
 *         electrode.
 */
uint32_t _ft_control_get_electrodes_state(struct ft_control_data *control);

/**
 * \brief Get the digital state of all control electrodes.
 * \param control Pointer to the control data.
 * \return This function returns a bit-mask value where each bit represents one
 *         control electrode. Logic 1 in the returned value represents a electrode
 *         digital result(not analog value).
 */
uint32_t _ft_control_get_electrodes_digital_state(struct ft_control_data *control);

/**
 * \internal
 * \brief Set flag in all electrodes.
 * \param control Pointer to the control data.
 * \param flags The flag to be set.
 * \return none
 *
 * This function sets the specified flag in all electrode objects.
 */
void _ft_control_set_flag_all_elec(struct ft_control_data *control,
                                  uint32_t flags);

/**
 * \internal
 * \brief Clear the flag in all electrodes.
 * \param control Pointer to the control data.
 * \param flag The flag to be cleared.
 * \return none
 *
 * This function clears the specified flag in all electrode objects.
 */
void _ft_control_clear_flag_all_elec(struct ft_control_data *control, uint32_t flag);

/**
 * \internal
 * \brief Get the index of the first touched electrode.
 * \param current_state Status of all electrodes.
 * \return This function scans the current_state parameter returned from the
 *         _ft_control_get_electrodes_state function, and returns the first
 *         touched electrode.
 */
uint32_t _ft_control_get_first_elec_touched(uint32_t current_state);

/**
 * \internal
 * \brief Get the index of the last touched electrode.
 * \param current_state Status of all electrodes.
 * \return This function scans the current_state parameter returned from the
 *         _ft_control_get_electrodes_state function, and returns the last
 *         touched electrode.
 */
uint32_t _ft_control_get_last_elec_touched(uint32_t current_state);

/**
 * \internal
 * \brief Returns the number of touches.
 * \param current_state Status of all electrodes.
 * \return This function scans the current_state parameter returned from the
 *         _ft_control_get_electrodes_state function, and returns the number of
 *         touched electrodes.
 */
uint32_t _ft_control_get_touch_count(uint32_t current_state);

/**
 * \internal
 * \brief The function checks, whether the two electrodes are neighbours, it also supports
 *        the overrun list of electrodes for never-ending controls - rotary types.
 * \param control Pointer to the control data.
 * \param first Index of the first electrode.
 * \param second Index of the second electrode.
 * \param overrun Marks the never-ending control types - rotary
 * \return Returns FT_SUCCESS if the input electrodes are neighours, otherwise it returns FT_INVALID_RESULT.
 */
int32_t _ft_control_check_neighbours_electrodes(struct ft_control_data *control,
                                                uint32_t first, 
                                                uint32_t second, 
                                                uint32_t overrun);
 
 
 
/**
 * \internal
 * \brief The function checks, whether the electrode is on the edge of the electrode list.
 * \param control Pointer to the control data.
 * \param electrode_ix Index of the electrode.
 * \return Returns FT_SUCCESS if the electrode is on the edge of the list, otherwise it returns FT_INVALID_RESULT.
 */
int32_t _ft_control_check_edge_electrodes(struct ft_control_data *control,
                                                uint32_t electrode_ix);
/**
 * \internal
 * \brief Set control flag.
 * \param control Pointer to the control data.
 * \param flags The flags to be set.
 */
static inline void _ft_control_set_flag(struct ft_control_data *control,
                                       uint32_t flags)
{
    control->flags |= flags;
}

/**
 * \internal
 * \brief Reset control flag.
 * \param control Pointer to the control data.
 * \param flags The flags to be cleared.
 */
static inline void _ft_control_clear_flag(struct ft_control_data *control,
                                         uint32_t flags)
{
    control->flags &= ~flags;
}

/**
 * \internal
 * \brief Test control flags.
 * \param control Pointer to the control data.
 * \param flags The flags to be tested
 * \return non-zero if any of the tested flags are set. This is bit-wise AND of
 *     the control flags and the flags parameter.
 */
static inline uint32_t _ft_control_get_flag(const struct ft_control_data *control,
                                           uint32_t flags)
{
    return (control->flags & flags);
}

/**
 * \internal
 * \brief Check for data everrun in the control.
 * \param control Pointer to the control data.
 * \return FT_FAILURE
           FT_SUCCESS
 *
 * If the control flag is not FT_CONTROL_NEW_DATA_FLAG, it resets the flag in control.
 */
static inline int32_t _ft_control_overrun(struct ft_control_data *control)
{
    if (_ft_control_get_flag(control, FT_CONTROL_NEW_DATA_FLAG)) {
        return FT_FAILURE; /* overrun, data has not been processed */
    }
    _ft_control_clear_flag(control, FT_CONTROL_NEW_DATA_FLAG);
    return FT_SUCCESS;
}

/**
 * \internal
 * \brief Returns the electrode by index.
 * \param control Pointer to the control data.
 * \param index
 * \return Pointer to electrode instance retrieved from the control's electrode list.
 */
static inline const struct ft_electrode *_ft_control_get_electrode(const struct ft_control_data *control,
                                                                  uint32_t index)
{
    if (control->electrodes_size < index) {
        return control->rom->electrodes[index];
    } else {
        return NULL;
    }
}

#ifdef __cplusplus
}
#endif

/** \} end of gcontrols_api_private group */
/** \} end of gcontrols_private group */
/** \} end of controls_private group */

#endif
