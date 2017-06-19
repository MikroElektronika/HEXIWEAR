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
#ifndef FT_ELECTRODES_PRV_H
#define FT_ELECTRODES_PRV_H

/**
 * \defgroup ftapi_private Freescale Touch Private API
 *
 * The functions documented in this module are the private ones used by the library
 * itself. All the API here is just documented and not designed to be used by the user.
 * \{
 */
 /**
 * \defgroup electrodes_private Electrodes
 * \ingroup ftapi_private
 *  
 * Electrodes are data objects which are used by data acquisition algorithms to store
 * per-electrode data as well as resulting signal and touch / time stamp information.
 *
 * Each Electrode provides at minimum
 * the processed and normalized signal value, the baseline value, and touch / timestamp
 * buffer containing the time of last few touch and release events. All such common
 * information are contained in the ft_electrode structure type. Also, the electrode 
 * contains information about the key detector used to detect touches for this physical 
 * electrode (this is mandatory). This brings the advantage that each electrode has its own
 * setting of the key detector independent on the module used. It contains information about 
 * hardware pin, immediate touch status, and time stamps of the last few touch or
 * release events.
 *
 * The private electrodes API provides all the functionality needed to handle the private
 * needs of the Freescale Touch library.
 * \{
 */

#include "ft_types.h"
#include "ft_electrodes.h"
#include "../source/system/ft_system_prv.h"
#include "../source/keydetectors/ft_keydetector_prv.h"

/* forward declarations */
struct ft_system;
struct ft_module_tsi_noise_data;

/**
 * The pointer to the special data of the electrode. Each module has its own types
 * handled by this union to keep clearance of the types.
 */
union ft_electrode_special_data
{
  struct ft_module_tsi_noise_data            * tsi_noise;  /**< Pointer to the TSI noise mode data for the TSI module. */     
};

/**
 *  Electrode RAM structure used to store volatile parameters, flags, and other data, to enable
 *  a generic behavior of the Electrode. You must allocate this structure and put a pointer
 *  into the ft_electrode structure, when the electrode is being configured and registered in the
 *  module and control.
 */
struct ft_electrode_data {
    const struct ft_electrode           *rom;                                      /**< Pointer to the electrode user parameters. */
    struct ft_module_data               *module_data;                              /**< Pointer to the owner module data. */
    uint16_t                            signal;                                    /**< Processed signal. */
    uint16_t                            raw_signal;                                /**< Raw data to be handled in the task process. */
    uint16_t                            baseline;                                  /**< Baseline. */
    struct ft_electrode_status          status[FT_ELECTRODE_STATUS_HISTORY_COUNT]; /**< Statuses. */
    uint8_t                             status_index;                              /**< Status index. */
    uint32_t                            flags;                                     /**< Flags. */
    union ft_keydetector_data           keydetector_data;                          /**< Pointer to the key detector data structure. */
    union ft_electrode_special_data     special_data;                              /**< Pointer to the special data (for example noise mode data for the TSI). */     
    struct ft_electrode_data            *shielding_electrode;                      /**< Pointer to a shielding electrode (if it is used). */     
};

/** Electrodes flags which can be set/cleared.
 */
enum ft_electrode_flags {
    FT_ELECTRODE_LOCK_BASELINE_REQ_FLAG = 1 << 0,       /**< This flag signals that the electrode's baseline should be locked (can't be updated). */
    FT_ELECTRODE_LOCK_BASELINE_FLAG = 1 << 1,           /**< This flag signals that the electrode's baseline is locked (cannot be updated). */
    FT_ELECTRODE_DIGITAL_RESULT_ONLY_FLAG = 1 << 2,     /**< This flag signals that the electrode's event does not have analog infomation (cannot be used for analog controls). */
    FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG = 1 << 3,        /**< This flag signals that the electrode is touched after the enable/init process. */
};

/**
 * \defgroup electrodes_api_private API Functions
 * \ingroup electrodes_private
 *
 * The functions in this category can be used to manipulate the Electrode objects.
 * \{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Get electrode data structure pointer.
 * \param electrode Pointer to the electrode user parameter structure.
 * \return The pointer to the data electrode structure that is reprasented by the handled user parameter structure pointer.        
 */
struct ft_electrode_data *_ft_electrode_get_data(const struct ft_electrode *electrode);

/**
 * \brief Get the electrode index in the module electrode array structure pointer.
 * \param electrode Pointer to the electrode user parameter structure.
 * \return The index to the electrode structure array, in case that the electrode is not available it returns -1.        
 */
int32_t _ft_electrode_get_index_from_module(const struct ft_module * module, const struct ft_electrode *electrode);

/**
 * \brief Initialize an electrode object.
 * \param module Pointer to the module data.
 * \param electrode Pointer to the electrode.
 * \return Pointer to the newly-created electrode data structure. (In case of a fail, it returns NULL).
 *
 * This function creates the electrode data, and resets the electrode's status and status index.
 */
struct ft_electrode_data *_ft_electrode_init(struct ft_module_data * module, const struct ft_electrode *electrode);

/**
 * \brief Process shielding if it is enabled, otherwise it returns the same value.
 * \param electrode A pointer to the electrode data.
 * \param signal Current signal value.
 * \return signal value.
 *
 * The signal is substracted by the baseline, and incremented by the signal.
 * If the signal is greater than 0, it returns the signal value other than 0.
 */
uint32_t _ft_electrode_shielding_process(struct ft_electrode_data *electrode,
                                       uint32_t signal);

/**
 * \brief Scale signal.
 * \param electrode A pointer to the electrode data.
 * \param signal
 * \return signal
 *
 * Normalize the signal to working values. Values from
 * ft_electrode divider or multiplier normalize the measured signal.
 */
uint32_t _ft_electrode_normalization_process(const struct ft_electrode_data *electrode,
                                           uint32_t signal);

/**
 * \brief Set the signal for the electrode.
 * \param electrode A pointer to the electrode.
 * \param signal
 * \return none
 */
void _ft_electrode_set_signal(struct ft_electrode_data *electrode,
                             uint32_t signal);

/**
 * \brief Set the raw signal for the electrode.
 * \param electrode Pointer to the electrode data.
 * \param signal
 * \return none
 */
void _ft_electrode_set_raw_signal(struct ft_electrode_data *electrode,
                                 uint32_t signal);

/**
 * \brief Set the status of the electrode.
 * \param electrode A pointer to the electrode data.
 * \param state ft_electrode_state
 * \return none
 *
 * This function sets the state of the electrode, and assigns a time stamp
 * from the system to the electrode.
 */
void _ft_electrode_set_status(struct ft_electrode_data *electrode,
                             int32_t state);

/* INLINE electrode functions */

/**
 * \internal
 * \brief Set electrode flag - used internally by the touch-detection logic.
 * \param electrode Pointer to the electrode data.
 * \param The flags to be set.
 * \return none
 */
static inline void _ft_electrode_set_flag(struct ft_electrode_data *electrode,
                                         uint32_t flags)
{
    electrode->flags |= flags;
}


/**
 * \internal
 * \brief Clears the electrode flags - used internally by the touch detection logic.
 * \param electrode Pointer to the electrode data.
 * \param flags The flags to be cleared.
 * \return none
 */
static inline void _ft_electrode_clear_flag(struct ft_electrode_data *electrode,
                                           uint32_t flags)
{
    electrode->flags &= ~flags;
}

/**
 * \internal
 * \brief Test electrode flags - used internally by the touch detection logic.
 * \param electrode Pointer to the electrode data.
 * \param flags Flags to be tested
 * \return non-zero if any of the tested flags are set. This is bit-wise AND of
 *     the electrode flags and the flags parameter.
 */
static inline uint32_t _ft_electrode_get_flag(struct ft_electrode_data *electrode,
                                             uint32_t flags)
{
    return (electrode->flags & flags);
}

// probably external API todo
/**
 * \brief Determine, whether the specified time (or its multiples) has elapsed since the last electrode event.
 * \param electrode Pointer to the electrode data.
 * \param event_period Number of time periods that should elapse since the last electrode event.
 * \return zero if the specified number of time periods has elapsed, or any whole multiple of this number
 *   has elapsed since the last electrode event.
 *
 * This function can be used to determine the multiples of specified time inteval since the
 * electrode event has been detected.
 */
uint32_t _ft_electrode_get_time_offset_period(const struct ft_electrode_data *electrode,
                                             uint32_t event_period);

/**
 * \brief Get the last known electrode status.
 * \param electrode Pointer to the electrode data.
 * \return Current electrode status.
 */
int32_t _ft_electrode_get_last_status(const struct ft_electrode_data *electrode);

/**
 * \brief Get the time since the last electrode event.
 * \param electrode Pointer to the electrode data.
 * \return Time elapsed since the last electrode event.
 */
uint32_t _ft_electrode_get_time_offset(const struct ft_electrode_data *electrode);

/**
 * \brief Get the normalized and processed electrode signal.
 * \param electrode Pointer to the electrode data.
 * \return Signal calculated from the last raw value measured.
 *
 * The signal value is calculated from the raw electrode capacitance or other
 * physical signal by applying the filtering and normalization algorithms.
 * This signal is used by "analog" \ref controls, which estimate the finger
 * position based on the signal value, rather than on a simple touch / release status.
 */
uint32_t _ft_electrode_get_signal(const struct ft_electrode_data *electrode);

/**
 * \brief Get the electrode status by specifying the history buffer index.
 * \param electrode Pointer to the electrode data.
 * \param index Index of the required status.
 * \return
 *   - status within the ft_electrode_state, if the index is within the range
 *   - FT_FAILURE if the index is out of range.
 */
int32_t _ft_electrode_get_status(const struct ft_electrode_data *electrode,
                                uint32_t index);

/**
 * \brief Get the last known electrode time-stamp.
 * \param electrode Pointer to the electrode data.
 * \return Current electrode status.
 */
uint32_t _ft_electrode_get_last_time_stamp(const struct ft_electrode_data *electrode);

/**
 * \brief Get the electrode status time-stamp by specifying the history buffer index.
 * \param electrode Pointer to the electrode data.
 * \param index Index of the required status.
 * \return
 *   - non-zero value (valid time stamp)
 *   - 0 - index out of range
 */
uint32_t _ft_electrode_get_time_stamp(const struct ft_electrode_data *electrode,
                                     uint32_t index);

/**
 * \brief Get the raw electrode signal.
 * \param electrode Pointer to the electrode data.
 * \return Electrode signal, as it is measured by the physical module.
 *
 * The raw signal is used internally by the filtering and normalization algorithms
 * to calculate the real electrode signal value, which is good to be compared
 * with the signals coming from other electrodes.
 */
uint32_t _ft_electrode_get_raw_signal(const struct ft_electrode_data *electrode);

/**
 * \brief Return difference between the signal and its baseline.
 * \param electrode Pointer to the electrode data.
 * \return Immediate delta value between the processed signal and its baseline
 *     (idle) value.
 */
int32_t _ft_electrode_get_delta(const struct ft_electrode_data *electrode);

/**
 * \brief Get the state of the electrode.
 * \param electrode Pointer to the electrode data.
 * \return Non-zero if the current electrode status is "touched"; zero otherwise.
 */
uint32_t _ft_electrode_is_touched(const struct ft_electrode_data *electrode);

/**
 * \brief Get the shielding electrode.
 * \param electrode Pointer to the electrode.
 * \return Pointer to the shielding electrode, if available.
 */
const struct ft_electrode * _ft_electrode_get_shield(const struct ft_electrode *electrode);


#ifdef __cplusplus
}
#endif

/** \} end of electrodes_api_private group */
/** \} end of electrodes_private group */
                                        
#endif
