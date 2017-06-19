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
#ifndef FT_KEYDETECTOR_PRV_H
#define FT_KEYDETECTOR_PRV_H

 /**
 * \defgroup detectors_private Key Detectors
 * \ingroup ftapi_private
 * The key detector module determines, whether an electrode has been touched or released, based on the values
 * obtained by the capacitive sensing layer. Along with this detection, the key detector module uses a
 * debounce algorithm that prevents the library from false touches.
 * The key detector also detects, reports, and acts on fault conditions during the scanning process. Two main
 * fault conditions are identified according to the electrode short-circuited either to the supply voltage or to the ground. The same conditions
 * can be caused by a small capacitance (equal to a short circuit to supply voltage) or by a big capacitance
 * (equals to a short circuit to the ground).
 * \{
 */

/**
 * The key detector optional run-time data.
 *
 */
union ft_keydetector_data
{
  struct ft_keydetector_afid_data       *afid;          /**< AFID electrode run-time data */
  struct ft_keydetector_safa_data       *safa;          /**< SAFA electrode run-time data */
};


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/** \} */ // end of detectors_private group

#endif
