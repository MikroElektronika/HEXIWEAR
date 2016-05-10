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
#include "ft_module_gpio.h"
#include "../source/system/ft_system_prv.h"
#include "../source/modules/ft_module_gpio_prv.h"
#include "../source/electrodes/ft_electrodes_prv.h"
#include "../source/filters/ft_filters_prv.h"
#include "../source/modules/ft_modules_prv.h"

#include "fsl_interrupt_manager.h"


/* Local functions */
static int32_t ft_gpio_check_interface(const struct ft_module_data *module);
static int32_t ft_gpio_data_check(const struct ft_module_data *module);

static int32_t _ft_module_gpio_init(struct ft_module_data *module);
static int32_t _ft_module_gpio_process(struct ft_module_data *module);
static int32_t _ft_module_gpio_trigger(struct ft_module_data *module);
static int32_t _ft_module_gpio_electrode_enable(struct ft_module_data *module,
                                   uint32_t elec_index);
static int32_t _ft_module_gpio_electrode_disable(struct ft_module_data *module,
                                    uint32_t elec_index);
static int32_t _ft_module_gpio_change_mode(struct ft_module_data *module, 
                                         const enum ft_module_mode mode, 
                                         const struct ft_electrode * electrode);

/** interface gpio module */
const struct ft_module_interface ft_module_gpio_interface = {
  .init              = _ft_module_gpio_init,
  .trigger           = _ft_module_gpio_trigger,
  .process           = _ft_module_gpio_process,
  .recalibrate       = NULL,
  .electrode_enable  = _ft_module_gpio_electrode_enable,
  .electrode_disable = _ft_module_gpio_electrode_disable,
  .change_mode       = _ft_module_gpio_change_mode,
  .name              = "ft_module_gpio_interface",
};

/*******************************************************************************
*                       GPIO MODULE functions
*******************************************************************************/
static int32_t _ft_module_gpio_init(struct ft_module_data *module)
{
  module->special_data.gpio = _ft_mem_alloc(sizeof(struct ft_module_gpio_data));
  
  if(module->special_data.gpio == NULL)
  {
    return FT_OUT_OF_MEMORY;
  }

  if (ft_gpio_data_check(module) < FT_SUCCESS) 
  {
      return FT_FAILURE;
  }
  
  const struct ft_module_gpio_user_interface *interface = 
    module->rom->module_params.gpio->user_interface;

  interface->init_timer();
  
  uint32_t electrode_counter = module->electrodes_cnt;
  
  while (electrode_counter--) 
  {
    /* Get the pointer to electrode. */
    const struct ft_electrode *elec = module->electrodes[electrode_counter]->rom;
    
    /* default state for all pins. */
    interface->set_pin_default_state(elec->pin_input >> FT_GPIO_PORT_SHIFT,
                                                 elec->pin_input & 0xFFU);
  }
 
  return FT_SUCCESS;
}

static int32_t _ft_module_gpio_trigger(struct ft_module_data *module)
{
  _ft_module_set_flag(module, FT_MODULE_NEW_DATA_FLAG);
  return FT_SUCCESS;
}

static int32_t _ft_module_gpio_process(struct ft_module_data *module)
{
  uint32_t electrode_counter = module->electrodes_cnt;
  const struct ft_module_gpio_user_interface *interface = 
    module->rom->module_params.gpio->user_interface;
  
  while (electrode_counter--) 
  {
    struct ft_electrode_data *elec = module->electrodes[electrode_counter];
    uint32_t port = elec->rom->pin_input >> FT_GPIO_PORT_SHIFT;
    uint32_t pin = elec->rom->pin_input & 0xFFU;
    uint32_t overrun = 0;
    uint32_t disabledInterrupts;
    interface->set_pin_output(port, pin);
    
    disabledInterrupts = __get_PRIMASK();
    // all interrupts MUST be disabled to achieve valuable measurement
    if(!disabledInterrupts)
    {
      INT_SYS_DisableIRQGlobal();
    }
    
    interface->set_pin_low(port, pin);
    interface->timer_reset_counter();
    interface->start_timer();
    interface->set_pin_input(port, pin);
    while (!interface->get_pin_value(port, pin))
    {
      if(interface->timer_get_overrun())
      {
        overrun = 1;
        break;
      }
    };
    uint32_t signal = interface->timer_get_counter();

    if(!disabledInterrupts)
    {
      INT_SYS_EnableIRQGlobal();
    }
    
    interface->set_pin_default_state(port, pin);
    
    if(!overrun)
    {
      _ft_electrode_set_raw_signal(elec, signal);
      
      // call general keydetector
      elec->rom->keydetector_interface->ft_keydetector_measure(elec, signal);
      elec->rom->keydetector_interface->ft_keydetector_process(elec); 
    }
  }
  
  _ft_module_set_flag(module, FT_MODULE_NEW_DATA_FLAG);
  _ft_system_modules_data_ready();
  
  return FT_SUCCESS;
}

static int32_t _ft_module_gpio_electrode_enable(struct ft_module_data *module,
                            const uint32_t elec_index)
{
  if (elec_index < module->electrodes_cnt) 
  {
    module->special_data.gpio->pen |= (uint32_t)(1U << elec_index);
  }
  return FT_SUCCESS;
}

static int32_t _ft_module_gpio_electrode_disable(struct ft_module_data *module,
                             const uint32_t elec_index)
{
  if (elec_index < module->electrodes_cnt) 
  {
    module->special_data.gpio->pen &= ~(uint32_t)(1U << elec_index);
  }
  return FT_SUCCESS;
}

static int32_t _ft_module_gpio_change_mode(struct ft_module_data *module, const enum ft_module_mode mode, const struct ft_electrode * electrode)
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

static int32_t ft_gpio_check_interface(const struct ft_module_data *module)
{
  const struct ft_module_gpio_user_interface *interface = 
    module->rom->module_params.gpio->user_interface;
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
  } else if (interface->timer_get_counter == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->timer_get_overrun == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->set_pin_default_state == NULL) 
  {
    return FT_FAILURE;
  } else if (interface->get_pin_value == NULL) 
  {
    return FT_FAILURE;
  }
  return FT_SUCCESS;
}

static int32_t ft_gpio_data_check(const struct ft_module_data *module)
{
  if (module->rom->module_params.gpio->user_interface == NULL) 
  {
      return FT_FAILURE;
  }
  if (ft_gpio_check_interface(module) < FT_SUCCESS) 
  {
      return FT_FAILURE;
  }
  return FT_SUCCESS;
}
