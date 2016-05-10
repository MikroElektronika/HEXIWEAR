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
#ifndef FT_KEYDETECTOR_AFID_H
#define FT_KEYDETECTOR_AFID_H

 /**
 * \defgroup afid Advanced Filtering and Integrating Detection
 * \ingroup detectors
 * The AFID (Advanced Filtering and Integrating Detection) key detector is based on using two IIR filters
 * with different depths (one short / fast, the other long / slow) and on integrating the difference between the
 * two filtered signals. The algorithm uses two thresholds: the touch threshold and the release threshold. The touch
 * threshold is defined in the sensitivity register. The release threshold has a twice lower level than the touch threshold.
 * If the integrated signal is higher than the touch threshold, or lower than the release threshold, then the integrated signal is
 * reset. The touch state is reported for the electrode when the first touch reset is detected. The release state is reported
 * when as many release resets are detected as the touch resets were detected during the previous touch state.
 * \{
 */
#include "ft_types.h"

/**
 * AFID Automatic Sensitive Calibration default ASC settings:
 * - touch_treshold_fall_rate (default 255) 
 * - noise_resets_minimum (default 128) 
 * - resets_for_touch (default 6)
 * This default values for AFID ASC definition for example:
  \code
  const struct ft_keydetector_afid keydec =
  {
      .signal_filter = {
          .cutoff = 8
      },
      .baseline_filter = {
          .cutoff = 4
      },
      .reset_rate = 1000,
      .asc = FT_KEYDETECTOR_AFID_ASC_DEFAULT,
  };
  \endcode
 */
#define FT_KEYDETECTOR_AFID_ASC_DEFAULT { \
        .touch_treshold_fall_rate = 1000, \
        .noise_resets_minimum = 128, \
        .resets_for_touch = 10 \
}


/**
 * AFID Automatic Sensitive Calibration structure; This structure is used to define the parameters of
 * evaluating the AFID process flow.
 * You can manage your own setup of parameters, or use the default setting in the \ref FT_KEYDETECTOR_AFID_ASC_DEFAULT.
 * This structure must be filled in.
 */
struct ft_keydetector_afid_asc {
    int16_t touch_treshold_fall_rate;      /**< Rate of how often the touch threshould can fall */
    uint32_t noise_resets_minimum;         /**< Noise Resets Minimum */
    int16_t resets_for_touch;              /**< Number of resets required for touch */
};

/**
 * The main structure representing the AFID key detector.
 * An instance of this data type represents the AFID key detector. Consisting of parameters
 * of filters, the AFID automatic sensitive calibration, and update rate.
 *
 * You're responsible to initialize all the members before registering the AFID in
 * the module. This structure can be allocated in ROM.
 */
struct ft_keydetector_afid {
  struct ft_filter_iir                signal_filter;          /**< Coeficient of the input IIR signal filter, used to supress high frequency noise. */
  struct ft_filter_fbutt              fast_signal_filter;     /**< Signal butterworth signal (fast).*/
  struct ft_filter_fbutt              slow_signal_filter;     /**< Baseline butterworth signal (slow).*/
  struct ft_filter_moving_average     base_avrg;              /**< Settings of the moving avarage filter for the baseline in release state of electrode. */
  struct ft_keydetector_afid_asc      asc;     	              /**< ASC structure for the AFID detector. */
  uint16_t                            reset_rate;             /** Reset rate of the AFID. Cannot be 0. */
};

/**
 * AFID key detector interface structure.
 */
extern const struct ft_keydetector_interface ft_keydetector_afid_interface;

#ifdef __cplusplus
extern "C" {
#endif

/** \} */ // end of the afid group

#ifdef __cplusplus
}
#endif

#endif
