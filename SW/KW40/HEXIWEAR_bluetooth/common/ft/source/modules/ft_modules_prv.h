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
#ifndef FT_MODULES_PRV_H
#define FT_MODULES_PRV_H

#include "ft_types.h"
#include "ft_filters.h"

/**
 * \defgroup modules_private Modules
 * \ingroup ftapi_private
 * Modules represent the data-acquisition layer in the Freescale Touch system,
 * it is the layer that is tighly coupled to hardware module available on
 * the Freescale MCU device.
 *
 * Each Module implements a set of private functions contained in the ft_modules_prv.h
 * file.
 *
 * \{
 */

/**
 * \defgroup gmodules_private General API
 * \ingroup modules_private
 * General API and definition over all modules.
 *
 * \{
 */
   
// Forward declaration
struct ft_module;
struct ft_module_gpio_data;
struct ft_module_gpioint_data;
struct ft_module_tsi_data;

/**
 * The module optional run-time data.
 *
 */
union ft_module_special_data
{
  struct ft_module_gpio_data    *gpio;          /**< GPIO module run-time data */
  struct ft_module_gpioint_data *gpioint;       /**< GPIO interrupt module run-time data */
  struct ft_module_tsi_data     *tsi;           /**< TSI module run-time data */
};

/**
 *  Module RAM structure used to store volatile parameters, flags, and other data to enable
 *  a generic behavior of the Module. This is the main internal structure for a module in
 *  the FT library. A list of pointers to the electrode RAM data structure is created.
 */
struct ft_module_data {
  const struct ft_module        *rom;               /**< Pointer to the module parameters defined by the user. */
  struct ft_electrode_data      **electrodes;       /**< Pointer to the list of electrodes. Can't be NULL. */
  enum ft_module_mode           active_mode;        /**< Active mode of the module. */
  uint32_t                      flags;              /**< Module's symptoms. */
  uint8_t                       electrodes_cnt;     /**< Electrode's count. */  
  union ft_module_special_data  special_data;       /**< Pointer to the special data (for example run-time data for the GPIO). */
};

/**
 *  Module interface structure; each module uses this structure to register the entry points
 *  to its algorithms. This approach enables a kind-of polymorphism in the touch System.
 *  All modules are processed the same way from the System layer, regardless of the specific
 *  implementation. Each module type defines one static constant structure of this type to
 *  register its own initialization, triggering, processing functions, and functions for enabling
 *  or disabling of electrodes, low power, and proximity.
 */
struct ft_module_interface
{
  int32_t (* init)(struct ft_module_data *module);              /**< The initialization of the module. */
  int32_t (* trigger)(struct ft_module_data *module);           /**< Send a trigger event into the module to perform hardware reading of the touches. */
  int32_t (* process)(struct ft_module_data *module);           /**< Process the read data from the trigger event. */
  int32_t (* recalibrate)(struct ft_module_data *module, void *configuration);                  /**< Force recalibration of the module in the current mode. */
  int32_t (* electrode_enable)(struct ft_module_data *module, const uint32_t elec_index);       /**< Enable the module electrode in hardware. */
  int32_t (* electrode_disable)(struct ft_module_data *module, const uint32_t elec_index);      /**< Disable the module electrode in hardware. */
  int32_t (* change_mode)(struct ft_module_data *module, const enum ft_module_mode mode, const struct ft_electrode * electrode); /**< Change the the mode of the module. */
  int32_t (* load_configuration)(struct ft_module_data *module, const enum ft_module_mode mode, const void* config); /**<  Load the configuration for the selected mode. */
  int32_t (* save_configuration)(struct ft_module_data *module, const enum ft_module_mode mode, void* config); /**<  Save the configuration of the selected mode. */
  const char* name;                                                             /**< A name of the variable of this type, used for FreeMASTER support purposes. */
};

/**
 * \defgroup modules_api_private API functions
 * \ingroup gmodules_private
 * General Private Function definition of the modules.
 *
 * \{
 */ 

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Get the module data structure pointer.
 * \param module Pointer to the module user parameter structure.
 * \return Pointer to the data module structure that is represented by the handled user parameter structure pointer.        
 */
struct ft_module_data *_ft_module_get_data(const struct ft_module *module);

/**
 * \brief Init module.
 * \param module Pointer to the module to be initialized.
 * \return The result of the operation.
 */
struct ft_module_data *_ft_module_init(const struct ft_module *module);

/**
 * \brief Trigger the start of measure event of the module.
 * \param module Pointer to the module to be triggered.
 * \return The result of the operation.
 */
int32_t _ft_module_trigger(struct ft_module_data *module);

/**
 * \brief Process the module.
 * \param module Pointer to the module to be processed.
 * \return The result of the operation.
 */
int32_t _ft_module_process(struct ft_module_data *module);

/**
 * \brief Get the module electrodes state
 * \param module Pointer to the FT module_data.
 * \return mode.
 */
uint32_t _ft_module_get_electrodes_state(struct ft_module_data *module);

/**
 * \brief Set the flag of the module.
 * \param module Pointer to the FT module.
 * \param flags The flags to be set.
 * \return void
 */
static inline void _ft_module_set_flag(struct ft_module_data *module,
                                      uint32_t flags)
{
    module->flags |= flags;
}

/**
 * \brief Reset the flag of the module.
 * \param module Pointer to the FT module.
 * \param flags The flags to be cleared.
 * \return void
 */
static inline void _ft_module_clear_flag(struct ft_module_data *module,
                                        uint32_t flags)
{
    module->flags &= (~flags);
}

/**
 * \brief Return the flag of the module.
 * \param module Pointer to the FT module.
 * \param flags The flags to be tested
 * \return Non-zero if any of the tested flags are set. This is bit-wise AND of
 *     the control flags and the flags parameter.
 */
static inline uint32_t _ft_module_get_flag(struct ft_module_data *module,
                                          uint32_t flags)
{
    return (module->flags & flags);
}

/**
 * \brief Return the instance of the module.
 * \param module Pointer to the FT module.
 * \return instance
 */
static inline uint32_t _ft_module_get_instance(const struct ft_module_data *module)
{
    return module->rom->instance;
}

/**
 * \brief Set the module's mode.
 * \param module Pointer to the FT module.
 * \param mode
 * \return None.
 */
static inline void _ft_module_set_mode(struct ft_module_data *module,
                                      uint32_t mode)
{
    module->active_mode = (enum ft_module_mode)mode;
}

/**
 * \brief Get the module's mode.
 * \param module Pointer to the FT module_data.
 * \return mode.
 */
static inline uint32_t _ft_module_get_mode(struct ft_module_data *module)
{
    return (uint32_t)module->active_mode;
}

#ifdef __cplusplus
}
#endif

/** \} end of modules_api_private group */
/** \} end of gmodules_private group */
/** \} end of modules_private group */
                                        
#endif /* FT_MODULES_PRV_H */
