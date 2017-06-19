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
#include "ft_modules.h"
#include "ft_module_gpioint.h"
#include "../source/system/ft_system_prv.h"
#include "../source/modules/ft_module_gpioint_prv.h"
#include "../source/electrodes/ft_electrodes_prv.h"
#include "../source/filters/ft_filters_prv.h"
#include "../source/modules/ft_modules_prv.h"

#include "fsl_interrupt_manager.h"

/* Local functions */
static int32_t ft_module_gpioint_check_interface(const struct ft_module_data *module);
static int32_t ft_module_gpioint_data_check(const struct ft_module_data *module);

static int32_t _ft_module_gpioint_init(struct ft_module_data *module);
static int32_t _ft_module_gpioint_process(struct ft_module_data *module);
static int32_t _ft_module_gpioint_trigger(struct ft_module_data *module);
static int32_t _ft_module_gpioint_electrode_enable(struct ft_module_data *module,
                                   uint32_t elec_index);
static int32_t _ft_module_gpioint_electrode_disable(struct ft_module_data *module,
                                    uint32_t elec_index);
static int32_t _ft_module_gpioint_change_mode(struct ft_module_data *module, 
                                         const enum ft_module_mode mode, 
                                         const struct ft_electrode * electrode);

static void ft_module_gpioint_start_channel(struct ft_module_data *module,
                                     struct ft_electrode_data *electrode,
                                     uint32_t elec_index);
static void ft_module_gpioint_stop_channel(struct ft_module_data *module,
                                    struct ft_electrode_data *electrode);


/** interface gpio module */
const struct ft_module_interface ft_module_gpioint_interface = {
  .init              = _ft_module_gpioint_init,
  .trigger           = _ft_module_gpioint_trigger,
  .process           = _ft_module_gpioint_process,
  .recalibrate       = NULL,
  .electrode_enable  = _ft_module_gpioint_electrode_enable,
  .electrode_disable = _ft_module_gpioint_electrode_disable,
  .change_mode       = _ft_module_gpioint_change_mode,
  .name              = "ft_module_gpioint_interface",
};

/*******************************************************************************
*                       GPIO MODULE functions
*******************************************************************************/
static int32_t _ft_module_gpioint_init(struct ft_module_data *module)
{
  module->special_data.gpioint = _ft_mem_alloc(sizeof(struct ft_module_gpioint_data));
  
  if(module->special_data.gpioint == NULL)
  {
    return FT_OUT_OF_MEMORY;
  }

  if (ft_module_gpioint_data_check(module) < FT_SUCCESS) 
  {
      return FT_FAILURE;
  }
  
  const struct ft_module_gpioint_user_interface *interface = 
    module->rom->module_params.gpioint->user_interface;

  interface->init_timer();
  
  uint32_t electrode_counter = module->electrodes_cnt;
  
  while (electrode_counter--) 
  {
    /* Get the pointer to electrode. */
    const struct ft_electrode *elec = module->electrodes[electrode_counter]->rom;
    
    /* default state for all pins. */
    interface->init_pin(elec->pin_input >> FT_GPIO_PORT_SHIFT,
                                                 elec->pin_input & 0xFFU);
  }
  return FT_SUCCESS;
}

static int32_t _ft_module_gpioint_trigger(struct ft_module_data *module)
{
  if (module->special_data.gpioint->scan_status == FT_GPIO_IN_PROGRESS)  // todo this macro
  {
    return FT_SCAN_IN_PROGRESS;
  } else 
  {
    struct ft_electrode_data *elec = module->electrodes[0];
    ft_module_gpioint_start_channel(module, elec, 0U);
    //ft_module_gpioint_basic_clear_flag(_this, FT_GPIO_INTERRUPTED_FLAG);
    module->special_data.gpioint->scan_status = (uint8_t)FT_GPIO_IN_PROGRESS;
  }
  return FT_SUCCESS;
}

static int32_t _ft_module_gpioint_process(struct ft_module_data *module)
{
  uint32_t electrode_counter = module->electrodes_cnt;

  while (electrode_counter--) 
  {
      struct ft_electrode_data *elec = module->electrodes[electrode_counter];
      elec->rom->keydetector_interface->ft_keydetector_measure(elec, _ft_electrode_get_raw_signal(elec));
      elec->rom->keydetector_interface->ft_keydetector_process(elec);
  }
  
  _ft_module_clear_flag(module, FT_MODULE_NEW_DATA_FLAG);
  return FT_SUCCESS;
}

static int32_t _ft_module_gpioint_electrode_enable(struct ft_module_data *module,
                            const uint32_t elec_index)
{
  if (elec_index < module->electrodes_cnt) 
  {
    module->special_data.gpioint->pen |= (uint32_t)(1U << elec_index);
  }
  return FT_SUCCESS;
}

static int32_t _ft_module_gpioint_electrode_disable(struct ft_module_data *module,
                             const uint32_t elec_index)
{
  if (elec_index < module->electrodes_cnt) 
  {
    module->special_data.gpioint->pen &= ~(uint32_t)(1U << elec_index);
  }
  return FT_SUCCESS;
}

static int32_t _ft_module_gpioint_change_mode(struct ft_module_data *module, const enum ft_module_mode mode, const struct ft_electrode * electrode)
{
  FT_ASSERT(module != NULL);
  FT_ASSERT(electrode != NULL);

  if(mode == FT_MODULE_MODE_NORMAL)
  {
    return FT_SUCCESS;
  }else
  {
    return FT_NOT_SUPPORTED;
  }
}

static int32_t ft_module_gpioint_check_interface(const struct ft_module_data *module)
{
  const struct ft_module_gpioint_user_interface *interface = 
    module->rom->module_params.gpioint->user_interface;
  if (interface->set_pin_output == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->set_pin_input == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->set_pin_low == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->set_pin_high == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->init_timer == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->start_timer == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->stop_timer == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->timer_reset_counter == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->init_pin == NULL) 
  {
    return FT_FAILURE;
  }
  return FT_SUCCESS;
}

static int32_t ft_module_gpioint_data_check(const struct ft_module_data *module)
{
  if (module->rom->module_params.gpioint->user_interface == NULL) 
  {
    return FT_FAILURE;
  }
  if (ft_module_gpioint_check_interface(module) < FT_SUCCESS) 
  {
    return FT_FAILURE;
  }
  return FT_SUCCESS;
}


static void ft_module_gpioint_start_channel(struct ft_module_data *module,
                                     struct ft_electrode_data *electrode,
                                     uint32_t elec_index)
{
  uint32_t port = electrode->rom->pin_input >> FT_GPIO_PORT_SHIFT;
  uint32_t pin = electrode->rom->pin_input & 0xFFU;

  const struct ft_module_gpioint_user_interface *interface = 
  module->rom->module_params.gpioint->user_interface;
  
  module->special_data.gpioint->measured_pin = elec_index;
  interface->set_pin_output(port, pin);
  interface->set_pin_low(port, pin);
  interface->clear_pin_interrupt(port, pin);
  interface->set_pin_interrupt(port, pin);
  interface->timer_reset_counter();
  //      ft_module_gpioint_basic_clear_flag(_this, FT_GPIO_INTERRUPTED_FLAG);
  interface->start_timer();
  interface->set_pin_input(port, pin);  
}

static void ft_module_gpioint_stop_channel(struct ft_module_data *module,
                                    struct ft_electrode_data *electrode)
{
  uint32_t port = electrode->rom->pin_input >> FT_GPIO_PORT_SHIFT;
  uint32_t pin = electrode->rom->pin_input & 0xFFU;

  const struct ft_module_gpioint_user_interface *interface = 
  module->rom->module_params.gpioint->user_interface;
  interface->clear_pin_interrupt(port, pin);
  interface->stop_timer();
  interface->set_pin_high(port, pin);
  interface->set_pin_output(port, pin);
}

void ft_module_gpioint_isr(const struct ft_module *module)
{
  FT_ASSERT(module != NULL);
  
  struct ft_module_data *module_data = _ft_module_get_data(module);

  uint32_t measured_pin = module_data->special_data.gpioint->measured_pin;
  struct ft_electrode_data *elec = module_data->electrodes[measured_pin];
  const struct ft_module_gpioint_user_interface *interface = 
    module->module_params.gpioint->user_interface;
  
  uint32_t signal = interface->timer_get_counter();
  _ft_electrode_set_raw_signal(elec, signal);
  
//  if (!ft_module_gpioint_basic_get_flag(_this, FT_GPIO_INTERRUPTED_FLAG)) {
//      /* timer was not interrupted by any other interrupt, process the signal */
//      uint32_t signal = _this->user_interface->timer_get_counter();
//      ft_electrode_set_raw_signal(&elec->electrode, signal);
//  } else {
//      /* sample ignored, clear the flag only */
//      ft_module_gpioint_basic_clear_flag(_this, FT_GPIO_INTERRUPTED_FLAG);
//  }

  ft_module_gpioint_stop_channel(module_data, elec);

  if (measured_pin < (module_data->electrodes_cnt - 1U)) 
  {
    measured_pin++;
    elec = module_data->electrodes[measured_pin];
    ft_module_gpioint_start_channel(module_data, elec, measured_pin);
  } else 
  {
    /* all pins measured */
    _ft_module_set_flag(module_data, FT_MODULE_NEW_DATA_FLAG);
    _ft_system_modules_data_ready();
    module_data->special_data.gpioint->scan_status = (uint8_t)FT_GPIO_MEASURED;
  }
}

void ft_module_gpioint_overflow_isr(const struct ft_module *module)
{
  FT_ASSERT(module != NULL);
  
  struct ft_module_data *module_data = _ft_module_get_data(module);

  uint32_t measured_pin = module_data->special_data.gpioint->measured_pin;
  struct ft_electrode_data *elec = module_data->electrodes[measured_pin];

  ft_module_gpioint_stop_channel(module_data, elec);

  if (measured_pin < (module_data->electrodes_cnt - 1U)) 
  {
    measured_pin++;
    elec = module_data->electrodes[measured_pin];
    ft_module_gpioint_start_channel(module_data, elec, measured_pin);
  } else 
  {
    /* all pins measured */
    module_data->special_data.gpioint->scan_status = (uint8_t)FT_GPIO_MEASURED;
  }
}
