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
#ifndef FT_H
#define FT_H

/* The main Freescale Touch header. */
#include "ft_types.h"
#include "ft_system.h"
#include "ft_electrodes.h"

/* Controls */
#include "ft_controls.h"
#include "ft_control_keypad.h"
#include "ft_control_aslider.h"
#include "ft_control_arotary.h"
#include "ft_control_rotary.h"
#include "ft_control_slider.h"

/* Modules */
#include "ft_modules.h"
#include "ft_module_tsi.h"
#include "ft_module_gpioint.h"
#include "ft_module_gpio.h"

/* Key Detectors */
#include "ft_keydetector_safa.h"
#include "ft_keydetector_afid.h"

/**
 * \defgroup ftapi Freescale Touch User API
 *
 * The functions documented in this module are the primary functions used in the user
 * application that uses the Freescale Touch library. The user calls the API
 * functions to give run-time for the Freescale Touch measurement and data-processing
 * algorithms. All library callbacks are executed in a context of one of
 * these API calls.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup system_api
 * \{
 */
  
/**
 * \brief Freescale Touch Library initialization.
 * \param system Pointer to the FT system parameters structure.
 * \param pool  Pointer to the memory pool what will be used for internal FT data.
 * \param size  Size of the memory pool handled by the parameter pool (needed size depends
 *              on the number of components used in the FT - electrodes, modules, controls, and so on).
 * \return
 *   - FT_SUCCESS if library was properly initialized,
 *   - FT_FAILURE if initialization failed (one of the reasons is not enough memory in the memory pool).
 *
 * This function validates the Freescale Touch configuration passed within the
 * ft_system structure. After this call, the system structure becomes the main
 * data provider for the application. There are also created and filled-up internal 
 * volatile data structures used by the driver. It is the user's responsibility to prepare
 * the configuration of all electrodes, modules, and controls in the system structure
 * before calling this function. The application should not execute any other
 * FT library calls if this function returns FT_FAILURE.
 * This is an example of the FT library initialization:
   \code
    uint8_t ft_memory_pool[512];
    
    if(ft_init(&my_ft_system_params, ft_memory_pool, sizeof(ft_memory_pool)) == FT_FAILURE)
    {
      printf("Initialization of FT failed. There can be a problem with the memory size
      or invalid parameters in component parameter structures.");
    }
    // The FT is successfuly initialized
  
   \endcode
 */
int32_t ft_init(const struct ft_system *system, uint8_t *pool, const uint32_t size);

/**
 * \brief Freescale Touch Main processing entry point.
 * \return
 *   - FT_SUCCESS when data acquired during the last trigger are now processed
 *   - FT_FAILURE when no new data are ready
 *
 * This function should be called by the application as often as possible, in
 * order to process the data acquired during the data trigger. This function
 * should be called at least once per trigger time.
 *
 * Internally, this function passes the FT_SYSTEM_MODULE_PROCESS and
 * FT_SYSTEM_CONTROL_PROCESS command calls to each object configured in \ref modules and
 * \ref controls.
 * This is an example of running a task of the FT library:
   \code
    uint8_t ft_memory_pool[512];
    
    if(ft_init(&my_ft_system_params, ft_memory_pool, sizeof(ft_memory_pool)) == FT_FAILURE)
    {
      printf("Initialization of FT failed. There can be problem with memory size
      or invalid parameters in component parameter structures.");
    }
    // The FT is successfuly initialized
  
    // Main never-ending loop of the application
    while(1)
    {
      if(ft_task() == FT_SUCCESS)
      {
        // New data has been processed
      }
    }

   \endcode
 */
int32_t ft_task(void);

/**
 * \brief Main Trigger function to acquire the touch-sensing data.
 * \return
 *   - FT_SUCCESS when the trigger was performed without any errors or warnings.
 *   - FT_FAILURE when a problem is detected, such as module not ready, overrun
 *               (data loss) error, and so on. Regardless of the error, the trigger
 *               is always initiated.
 *
 * This function should be called by the application periodically in a timer
 * interrupt, or in a task to trigger new data measurement. Depending on the
 * \ref modules implementation, this function may take the data immediately, or
 * may only start the hardware sampling with interrupt enabled.
 * This is an example of the FT library triggering:
   \code
    //For example, there is a callback routine from any priodical source (for example 5 ms)   
    static void Timer_5msCallBack(void)
    {
     if(ft_trigger() != FT_SUCCESS)
      {
        // Trigger error
      }
    }
   \endcode
 */
int32_t ft_trigger(void);

#ifdef __cplusplus
}
#endif

/** \} end of system group */

#endif
