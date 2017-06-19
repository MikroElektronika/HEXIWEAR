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
#ifndef FT_MODULE_TSI_H
#define FT_MODULE_TSI_H

/**
 * \defgroup tsi TSI module
 * \ingroup modules
 *
 * The TSI module describes the hardware configuration and control of the elementary functionality
 * of the TSI peripheral; it covers all versions of the TSI peripheral by a generic
 * low-level driver API.
 *
 * The TSI Basic module is designed for processors that have the hardware TSI module
 * version 1, 2, or 4 (for example Kinetis L).
 *
 * The module also handles the NOISE mode supported by the TSI v4 (Kinetis L).
 * \{
 */

#include "ft_modules.h"

#include "ft_types.h"
#include "ft_electrodes.h"

#include "fsl_tsi_driver.h"

/**
 * The structure represents the Noise detection of the TSI v4 module.
 * An instance of this data type represents the Noise detection of the TSI v4 module. It contains the parameters
 * of Noise filters automatic sensitive calibration.
 *
 * You must initialize all the members before registering the noise in
 * the module. This structure can be allocated in ROM.
 */
struct ft_module_tsi_noise
{
  struct ft_filter_iir noise_filter;    ///< Noise filter parameters
  uint8_t              update_rate;     ///< Period of the noise checking on the measured electrodes
  uint8_t              noise_mode_timeout; ///< Time of switching back to capacitive mode since last noise event
};

/**
 * The main structure representing the Noise detection of the TSI v4 module.
 * An instance of this data type represents the Noise detection of the TSI v4 module. It contains the parameters
 * of the Noise filters automatic sensitive calibration.
 *
 * You must initialize all the members before registering the Noise in
 * the module. This structure can be allocated in ROM.
 */
struct ft_module_tsi_params
{
  struct ft_module_tsi_noise    noise;
  const  tsi_config_t         *config;  /**< A pointer to the HW cfg for noise mode Can't be NULL. */
};

/**
 * The TSI module interface structure.
 */
extern const struct ft_module_interface ft_module_tsi_interface;   /**< Can't be NULL. */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/** \} */ // end of the TSI group

#endif
