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
#ifndef FT_KEYDETECTOR_H
#define FT_KEYDETECTOR_H

#include "ft_system.h"
#include "ft_electrodes.h"
#include "ft_modules.h"
#include "ft_controls.h"

 /**
 * \defgroup detectors Key Detectors
 * \ingroup ftapi
 *
 * Key Detectors represent different types of signal-processing algorithms;
 * the primary purpose of a key detector algorithm is to determine, whether an electrode has been
 * touched or not, calculate the normalized signal, and provide all these information
 * to the \ref controls layer. The Controls layer is then able to detect much more
 * complex finger gestures, such as a slider swing or a key press within a multiplexed keypad.
 *
 * As an input, the Key Detector gets the raw electrode signal value obtained from
 * the data-acquisition algorithm, wrapped by one of the \ref modules instance.
 * The output values and intermediate calculated parameters needed by the Key Detector
 * layer are contained within a structure type, derived from the ft_electrode type. See
 * more information in the \ref electrodes section.
 *
 * In addition to signal processing, the Key Detector also detects, reports, and acts
 * on fault conditions during the scanning process. Two main fault conditions are
 * reported as electrode short-circuit to supply voltage (capacitance too small),
 * or short-circuit to ground (capacitance too high).
 */

/* forward declaration */
struct ft_electrode_data;

union ft_keydetector_params
{
  const struct ft_keydetector_afid     * afid;
  const struct ft_keydetector_safa     * safa;
};




/**
 * The key detector interface structure represents the Freescale Touch library Key
 * Detector algorithm interface. The context data of the key detectors are stored in the
 * \ref electrodes application objects.
 *
 */
struct ft_keydetector_interface {
  int32_t (* ft_keydetector_init)(struct ft_electrode_data *electrode);        /**< Key Detector initialization function pointer */
  void (* ft_keydetector_enable)(struct ft_electrode_data *electrode, uint32_t touch); /**< Key Detector enable function pointer */
  void (* ft_keydetector_process)(struct ft_electrode_data *electrode);        /**< Key Detector process function pointer       */
  void (* ft_keydetector_measure)(struct ft_electrode_data *electrode, uint32_t signal); /**< Key Detector measure function pointer */
  const char* name;                                                             /**< A name of the varible of this type, used for FreeMASTER support purposes. */
};



#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

/** \} end of detectors group */

#endif /* FT_KEYDETECTOR_H */
