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
#ifndef FT_KEYDETECTOR_AFID_PRV_H
#define FT_KEYDETECTOR_AFID_PRV_H

 /**
 * \defgroup afid_private Advanced Filtering and Integrating Detection
 * \ingroup detectors_private
 * The AFID (Advanced Filtering and Integrating Detection) key detector is based on using two IIR filters
 * with different depths (one short / fast, the other long / slow) and on integrating the difference between the
 * two filtered signals. The algorithm uses two thresholds; the touch threshold and the release threshold. The touch
 * threshold is defined in the sensitivity register. The release threshold has twice the lower level than the touch threshold.
 * If the integrated signal is higher than the touch threshold, or lower than the release threshold, then the integrated signal is
 * reset. The Touch state is reported for the electrode when the first touch reset is detected. The Release state is reported,
 * when as many release resets as the touch resets were detected during the previous touch state.
 * \{
 */

#include "../source/filters/ft_filters_prv.h"
#include "../source/keydetectors/ft_keydetector_prv.h"
#include "ft_types.h"
#include "ft_keydetector_afid.h"

/**
 * The initial integration value of the AFID.
 */
#define FT_KEYDETECTOR_AFID_INITIAL_INTEGRATOR_VALUE     0

/**
 * The initial reset counter value of the AFID.
 */
#define FT_KEYDETECTOR_AFID_INITIAL_RESET_TOUCH_COUNTER_VALUE  0

/**
 * The reset threshold value of the AFID.
 */
#define FT_KEYDETECTOR_AFID_INITIAL_RESET_RELEASE_COUNTER_VALUE  10

/**
 * AFID Automatic Sensitive Calibration RAM structure; This structure is used for internal
 * algorithms to store the data while evaluating the AFID.
 * Contains data of the calculating result and auxiliary variables.
 *
 * This structure only manages and uses the internal methods.
 */
struct ft_keydetector_afid_asc_data 
{
  int32_t max_resets;  
};

/**
 * AFID Ram structure; This structure is used for internal
 * algorithms to store the data while evaluating the AFID.
 * Contains the data of the calculating result and auxiliary variables.
 *
 * This structure only manages and uses the internal methods.
 */
struct ft_keydetector_afid_data 
{
  struct ft_filter_fbutt_data fast_signal_filter;   /**< Signal fast butterworth filter data storage. */
  struct ft_filter_fbutt_data slow_signal_filter;   /**< Signal slow butterworth filter data storage. */
  struct ft_filter_moving_average_data    base_avrg;/**< Base line moving average filter data. */
  uint16_t                    slow_signal;          /**< Slow signal value .*/    
  struct ft_keydetector_afid_asc_data     asc;      /**< Storage of ASC (Atomatic snsitive calibration) data for AFID*/
  uint8_t                    filter_state;          /**< State of filter. */
  int32_t                    integration_value;     /**< Current value of internal integrator. */
  uint32_t                   touch_threshold;       /**< Current threshold value for integrator resets. */
  uint32_t                   touch_reset_counter;   /**< Count of touch resets. */
  uint32_t                   release_reset_counter; /**< Count of relaase events resets. */
};

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

/** \} */ // end of afid_private group

#endif
