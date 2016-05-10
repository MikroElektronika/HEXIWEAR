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
#ifndef FT_TYPES_H
#define FT_TYPES_H

#include <stdint.h>
#include <stdlib.h>

/**
 * \defgroup types General Types
 * \ingroup ftapi
 * The standard types used in the whole Freescale Touch software library. The code is 
 * built on the standard library types, such as uint32_t, int8_t, and so on, loaded from 
 * "stdint.h", and it defines just few additional types needed to run the FT.
 *
 * \{
 */

#ifndef NULL
  /**
  * \brief Standard NULL pointer.
  *              There is a definition in the FT, in case that NULL is not defined in the project 
                previously.
  */
  #define NULL (void *)0
#endif

/** Generic flags for FT processing. */
#define FT_FLAGS_SYSTEM_SHIFT(x) ((x) + 0)
#define FT_FLAGS_SPECIFIC_SHIFT(x) ((x) + 16)

/**
  * \brief The Freescale Touch result of most operations / API. The standard API function 
  *             returns the result of the finished operation if needed, and it can have
  *             the following values.
  */
enum ft_result
{
  FT_SUCCESS          =  0,     ///< Successful result - Everything is alright.
  FT_FAILURE          = -1,     ///< Something is wrong, unspecified error.
  FT_OUT_OF_MEMORY    = -2,     ///< The FT does not have enough memory.
  FT_SCAN_IN_PROGRESS = -3,     ///< The scan is currently in progress.
  FT_NOT_SUPPORTED    = -4,     ///< The feature is not supported.
  FT_INVALID_RESULT   = -5,     ///< The function ends with an invalid result.
};

/**
  * \brief FT_FREEMASTER_SUPPORT enables the support of FreeMASTER for the Freescale Touch
  *             project. When it is enabled, the FT starts using / including the freemaster.h file.
  *             FT_DEBUG is enabled by default. 
  */
#ifndef FT_FREEMASTER_SUPPORT
  #define FT_FREEMASTER_SUPPORT 0
#endif

/**
  * \brief FT_DEBUG enables the debugging code that caused the assert states in the FT. 
  *             For the release compilation, this option should be disabled.
  *             FT_DEBUG is enabled by default, which enables the FT ASSERTS. 
  */
#ifndef FT_DEBUG
  #define FT_DEBUG 1
#endif

#if (FT_DEBUG == 0)
  #define FT_ASSERT(expr) ((void)0)
#else
  #define FT_ASSERT(expr)                  \
    {                                      \
        if (!(expr)) {                     \
            ft_error(__FILE__, __LINE__);  \
        }                                  \
    }
#endif

#ifdef __cplusplus
  extern "C"
  {
#endif

#ifdef __cplusplus
  }
#endif

/** \} */ // end of types group

#endif
