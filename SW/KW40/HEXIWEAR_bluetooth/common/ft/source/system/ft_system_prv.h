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
#ifndef FT_SYSTEM_PRV_H
#define FT_SYSTEM_PRV_H

#include "ft_system.h"
#include "../source/system/ft_system_mem_prv.h"
/**
 * \defgroup ftapi_private Freescale Touch Private API
 *
 * The functions documented in this module are the private ones used by the library
 * itself. All the API here is just documented and not designed to be used by the user.
 * \{
 */

/**
 * \defgroup system_private System
 / \ingroup ftapi_private
 *
 * The system private API and definitions.
 * \{
 */

/** Internal Module function call identifier
 */
enum ft_system_module_call {
    FT_SYSTEM_MODULE_INIT       = 0,    ///< Do module initialization 
    FT_SYSTEM_MODULE_TRIGGER    = 1,    ///< Send trigger event to module 
    FT_SYSTEM_MODULE_PROCESS    = 2,    ///< Do process data in the module
    FT_SYSTEM_MODULE_CHECK_DATA = 3,    ///< Check the module data
};

/** Internal Controls function call identifier
 */
enum ft_system_control_call {
    FT_SYSTEM_CONTROL_INIT       = 0,   ///< Do control initialization
    FT_SYSTEM_CONTROL_PROCESS    = 1,   ///< Process the new data of control
    FT_SYSTEM_CONTROL_OVERRUN    = 2,   ///< Control data are overrun 
    FT_SYSTEM_CONTROL_DATA_READY = 3,   ///< Control data are ready
};

/**
 * System RAM structure used to store volatile parameters, counter, and system callback
 * functions. This is the only statically placed RAM variable in the whole Freescale Touch library.
 */
struct ft_kernel {
    const struct ft_system      *rom;           /**< Pointer to the system parameters. */
    struct ft_control_data      **controls;     /**< Pointer to the list of controls. Can't be NULL. */
    struct ft_module_data       **modules;      /**< Pointer to the list of modules. Can't be NULL. */
    uint8_t                     controls_cnt;   /**< Count of the controls. */
    uint8_t                     modules_cnt;    /**< Count of the modules. */
    uint32_t                    time_counter;   /**< Time counter. */
    ft_system_callback          callback;       /**< System event handler. */
    struct ft_mem               memory;         /**< System Memory handler */
#if (FT_DEBUG != 0)
    ft_error_callback           error_callback; /**< User Error handler */
#endif
};

/**
 * \defgroup system_api_private API Functions
 * \ingroup system_private
 * General Private Function definition of system.
 *
 * \{
 */

#ifdef __cplusplus
extern "C" {
#endif
 
  
/**
 * \brief Obtain a pointer to the system.
 * \return A pointer to the system kernel structure.
 */
struct ft_kernel *_ft_system_get(void);

/**
 * \brief Increments the system counter.
 * \return None.
 */
void _ft_system_increment_time_counter(void);

/**
 * \brief Get time period.
 * \return Time period.
 */
uint32_t _ft_system_get_time_period(void);

/**
 * \brief Time offset by a defined period.
 * \param event_period Defined event period.
 * \return 0 if event_period period modulo current counter is equal to 0
 *         positive number otherwise.
 *
 *  This function is used to find out if an event can be invoked in its defined period.
 */
uint32_t _ft_system_get_time_offset_from_period(uint32_t event_period);

/**
 * \brief Invoke the module function based on the option parameter.
 * \param option One of the options from the ft_system_module_call enum
 * \return
 *   - FT_SUCCESS if the module's action was carried out succesfully,
 *   - FT_FAILURE if the module's action failed.
 */
int32_t _ft_system_module_function(uint32_t option);

/**
 * \brief Invoke the control function based on the option parameter.
 * \param option One of the options from ft_system_control_call enum
 * \return
 *   - FT_SUCCESS if the control's action was carried out succesfully,
 *   - FT_FAILURE if the control's action failed.
 */
int32_t _ft_system_control_function(uint32_t option);

/**
 * \brief Initialize system.
 * \param system Pointer to the user system parameters structure.
 * \return
 *   - FT_SUCCESS if the system data are set correctly,
 *   - FT_FAILURE if the system data check failed.
 */
int32_t _ft_system_init(const struct ft_system *system);

/**
 * \brief System callback invocation.
 * \param event  Callback event.
 * \return None.
 */
void _ft_system_invoke_callback(uint32_t event);

/**
 * \brief Function used internally to detect, whether new \ref modules data are available and
 * to set the same flag for the controls. This function also invokes the control callbacks.
 * \return None.
 */
void _ft_system_modules_data_ready(void);

/**
 * \brief Find the n-th instance of a module of a specified type.
 * \param interface_address Address to the module's interface (uniquely identifies module type).
 * \param instance Zero-based module instance index.
 * \return
 *   - valid pointer to module.
 *   - NULL if the module was not found
 */
const struct ft_module *_ft_system_get_module(uint32_t interface_address,
                                             uint32_t instance);

/**
 * \brief The FT error function that is invoked from FT asserts
 * \param file_name Pointer to the file name.
 * \param line Number of the line which was asserted.
 * \return none
 */
void ft_error(char *file_name, uint32_t line);

#ifdef __cplusplus
}
#endif

/** \} end of system_api_private group */
/** \} end of system_private group */
/** \} end of ftapi_private group */

#endif
