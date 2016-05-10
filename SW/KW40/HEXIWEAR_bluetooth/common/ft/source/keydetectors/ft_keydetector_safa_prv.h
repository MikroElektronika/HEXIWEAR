/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#ifndef FT_KEYDETECTOR_SAFA_PRV_H
#define FT_KEYDETECTOR_SAFA_PRV_H

 /**
 * \defgroup safa_prv Safa Detector
 * \ingroup detectors_private
 *
 * Safa key detector is a method for recognition of touch or release states. It can be used for each type of control.
 *
 * If the measured sample is reported as a valid sample, the module calculates the delta value from the actual signal value and
 * the baseline value. The delta value is compared to the threshold value computed from the expected signal and baseline values.
 * Based on the result, it determines the electrode state, which can be released, touched, changing from
 * released to touched, and changing from touched to released. The method is using moving average filters to determine the baseline and expected signal values 
 * with a different depth of the filter, depending on the state of the electrode. The deadband filters in the horizontal and vertical directions are also implemented.
 * \{
 */

#include "../source/filters/ft_filters_prv.h"
#include "../source/keydetectors/ft_keydetector_prv.h"
#include "ft_types.h"
#include "ft_keydetector_safa.h"

/**
 * Safa RAM structure. This structure is used for internal
 * algorithms to store data, while evaluating Safa.
 * Contains the data of result calculation and auxiliary variables.
 *
 * This structure only manages and uses internal methods.
 */
struct ft_keydetector_safa_data {
    enum ft_filter_state                    filter_state;               /**< Input filter state. */
    struct ft_filter_moving_average_data    base_avrg;                  /**< Baseline moving average filter data. */
    struct ft_filter_moving_average_data    noise_avrg;                 /**< Noise signal moving average filter data. */
    struct ft_filter_moving_average_data    predicted_signal_avrg;      /**< Predicted signal line moving average filter data. */
    struct ft_filter_moving_average         base_avrg_init;             /**< Baseline moving average filter settings. */
    struct ft_filter_moving_average         noise_avrg_init;            /**< Noise moving average filter settings. */
    struct ft_filter_moving_average         predicted_signal_avrg_init; /**< Predicted signal moving average filter settings. */
    uint32_t                                noise;                      /**< Noise value. */
    uint32_t                                predicted_signal;           /**< Predicted signal value. */
    int32_t                                 entry_event_cnt;            /**< Event counter value. */
    int32_t                                 deadband_cnt;               /**< Deadband event counter. */
    int32_t                                 recovery_cnt;               /**< Recovery counter. */
};


#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

/** \} */ // end of safa private  group

#endif
