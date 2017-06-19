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

#include "../source/system/ft_system_prv.h"
#include "../source/system/ft_system_mem_prv.h"
#include "../source/system/ft_system_frmstr_prv.h"
#include "ft_modules.h"
#include "../source/modules/ft_modules_prv.h"
#include "ft_keydetectors.h"
#include "../source/electrodes/ft_electrodes_prv.h"
#include "ft_electrodes.h"

static uint32_t _ft_module_count_electrodes(const struct ft_module *module);
static int32_t _ft_module_data_check(const struct ft_module_data *module);
static int32_t _ft_module_init_electrode(struct ft_module_data *module, uint32_t index);

static int32_t _ft_module_data_check(const struct ft_module_data *module)
{
  if (module->rom == NULL)
  {
      return FT_FAILURE;
  }
  if (module->rom->electrodes == NULL)
  {
      return FT_FAILURE;
  }

  return FT_SUCCESS;
}

static uint32_t _ft_module_count_electrodes(const struct ft_module *module)
{
  uint32_t elec_counter = 0U;

  while (module->electrodes[elec_counter] != NULL)
  {
    elec_counter++;
  }
  return elec_counter;
}

uint32_t _ft_module_get_electrodes_state(struct ft_module_data *module)
{
    FT_ASSERT(module != NULL);
    uint32_t elec_counter = module->electrodes_cnt;
    uint32_t current_state = 0U;

    while (elec_counter--) {
        uint32_t electrode_state = _ft_electrode_is_touched(module->electrodes[elec_counter]);
        /* all elec status in a bit field */
        current_state |= (electrode_state << elec_counter);
    }
    return current_state;
}

/* internal function */
struct ft_module_data *_ft_module_get_data(const struct ft_module *module)
{
  FT_ASSERT(module != NULL);
  uint32_t i = 0;

  struct ft_module **modules = (struct ft_module **)_ft_system_get()->rom->modules;

  while(*modules != NULL)
  {
    if(*modules == module)
    {
      return _ft_system_get()->modules[i];
    }
    i++;
    modules++;
  }

  return NULL;
}

static int32_t _ft_module_init_electrode(struct ft_module_data *module, uint32_t index)
{
  struct ft_electrode_data *elec;

  elec = _ft_electrode_init(module, module->rom->electrodes[index]);

  if(elec == NULL)
  {
    return FT_OUT_OF_MEMORY;
  }
  
  module->electrodes[index] = elec;
  elec->module_data = module;

  FT_ASSERT(elec->rom->keydetector_interface->ft_keydetector_init != NULL);

  if(elec->rom->keydetector_interface->ft_keydetector_init(elec) != FT_SUCCESS)
  {
     return FT_OUT_OF_MEMORY;
  } /* init keydetectors data */
  
  if(_ft_freemaster_add_variable(elec->rom->keydetector_interface->name, "ft_keydetector_interface", (void*) elec->rom->keydetector_interface, sizeof(struct ft_keydetector_interface)) != FT_SUCCESS)
  {
    return FT_OUT_OF_MEMORY;
  }
  
  return FT_SUCCESS;
}

struct ft_module_data *_ft_module_init(const struct ft_module *module)
{
  FT_ASSERT(module != NULL);
  FT_ASSERT(module->interface != NULL);
  FT_ASSERT(module->electrodes != NULL);

  struct ft_module_data *_this = _ft_mem_alloc(sizeof(struct ft_module_data));


  if(_this == NULL)
  {
      return NULL;
  }

  _this->electrodes_cnt = (uint8_t)_ft_module_count_electrodes(module);
  _ft_module_set_mode(_this, FT_MODULE_MODE_NORMAL);

  _this->electrodes = _ft_mem_alloc(sizeof(struct ft_electrode_data*) * _this->electrodes_cnt);

  if(_this->electrodes == NULL)
  {
      return NULL;
  }

  _this->rom = module;

  if (_ft_module_data_check(_this) < FT_SUCCESS)
  {
    return NULL;
  }

  uint32_t i;

  for(i=0; i<_this->electrodes_cnt; i++)
  {
    _this->electrodes[i] = NULL;
  }
  
  for(i=0; i<_this->electrodes_cnt; i++)
  {
    struct ft_electrode const * shield_electrode;
    
    if(_this->electrodes[i] != NULL)
    {
      continue;
    }
    
    shield_electrode = _ft_electrode_get_shield(_this->rom->electrodes[i]);
    
    if(shield_electrode != NULL)
    {
      // There is non initialize the shield electrode, so it must be initialize before 
      // the electrodes that is it using
      int32_t  j = _ft_electrode_get_index_from_module(_this->rom, shield_electrode);
      if(j >= 0)
      {
        if(_ft_module_init_electrode(_this, j) != FT_SUCCESS)
        {
          return NULL;
        }
      }
    }
      
    if(_ft_module_init_electrode(_this, i) != FT_SUCCESS)
    {
      return NULL;
    }
  }

  if(module->interface->init)
  {
    if(module->interface->init(_this) != FT_SUCCESS)
    {
      return NULL;
    }
  }
  
  if(_ft_freemaster_add_variable(module->interface->name, "ft_module_interface", (void*) module->interface, sizeof(struct ft_module_interface)) != FT_SUCCESS)
  {
    return NULL;
  }

  
  return _this;
}

int32_t _ft_module_trigger(struct ft_module_data *module)
{
  FT_ASSERT(module != NULL);

  int32_t result;

  if (_ft_module_get_flag(module, FT_MODULE_TRIGGER_DISABLED_FLAG))
  {
    return FT_FAILURE;
  }

  _ft_module_clear_flag(module, FT_MODULE_NEW_DATA_FLAG);
  
  if(module->rom->interface->trigger)
  {
    if((result = module->rom->interface->trigger(module)) != FT_SUCCESS)
    {
      return result;
    }
  }

  return FT_SUCCESS;
}

int32_t _ft_module_process(struct ft_module_data *module)
{
  FT_ASSERT(module != NULL);

  if (!_ft_module_get_flag(module, FT_MODULE_NEW_DATA_FLAG))
  {
    return FT_FAILURE; /* no data to be processed */
  }

  /* Give chance to any specific process inside of used module. */
  if(module->rom->interface->process)
  {
    if(module->rom->interface->process(module) != FT_SUCCESS)
    {
      return FT_FAILURE;
    }
  }else
  {
    uint32_t el_counter = module->electrodes_cnt;

    while (el_counter--)
    {
      struct ft_electrode_data *elec = module->electrodes[el_counter];
      {
        // call general keydetector
        elec->rom->keydetector_interface->ft_keydetector_measure(elec,
                                               _ft_electrode_get_raw_signal(elec));

        elec->rom->keydetector_interface->ft_keydetector_process(elec);
      }
    }
  }
  
  _ft_module_clear_flag(module, FT_MODULE_NEW_DATA_FLAG);
  return FT_SUCCESS;
}

uint32_t ft_module_recalibrate(const struct ft_module *module, void *configuration)
{
  FT_ASSERT(module != NULL);
  if(module->interface->recalibrate)
  {
    return (uint32_t)module->interface->recalibrate(_ft_module_get_data(module), configuration);
  }

  return FT_SUCCESS;
}

int32_t ft_module_change_mode(struct ft_module *module, const enum ft_module_mode mode, const struct ft_electrode *electrode)
{
  FT_ASSERT(module != NULL);
  FT_ASSERT(electrode != NULL);

  struct ft_module_mode_flags
  {
    enum ft_module_mode mode;
    uint32_t         flags_set;
    uint32_t         flags_clear;
  };

  const struct ft_module_mode_flags mode_flags[3] =
  {
    {
      FT_MODULE_MODE_NORMAL,
      0,
      FT_MODULE_TRIGGER_DISABLED_FLAG
    },
    {
      FT_MODULE_MODE_PROXIMITY,
      0,
      FT_MODULE_TRIGGER_DISABLED_FLAG
    },
    {
      FT_MODULE_MODE_LOW_POWER,
      FT_MODULE_TRIGGER_DISABLED_FLAG,
      0
    },
  };

  uint32_t mode_ix;

  struct ft_module_data *module_data = _ft_module_get_data(module);

  if (module->interface->change_mode == NULL)
  {
    return FT_FAILURE;
  }

  for(mode_ix = 0; mode_ix < 3; mode_ix++)
  {
    if(mode_flags[mode_ix].mode == mode)
      break;
  }

  if(mode_ix >= 3)
  {
    return FT_FAILURE;
  }

  _ft_module_set_flag(module_data, mode_flags[mode_ix].flags_set);


  int32_t result;
  if((result = (module->interface->change_mode(module_data, mode, electrode))) != FT_SUCCESS)
  {
    _ft_module_clear_flag(module_data, mode_flags[mode_ix].flags_set);
    return result;
  }


  _ft_module_clear_flag(module_data, mode_flags[mode_ix].flags_clear);

  if(mode == FT_MODULE_MODE_LOW_POWER)
  {
    _ft_system_increment_time_counter(); /* inc counter for the wake up interrupt */
  }

  _ft_module_set_mode(module_data, mode);

  return FT_SUCCESS;
}

int32_t ft_module_load_configuration(struct ft_module *module, const enum ft_module_mode mode, const void *config)
{
  FT_ASSERT(module != NULL);
  FT_ASSERT(config != NULL);
  
  struct ft_module_data *module_data = _ft_module_get_data(module);
  
  FT_ASSERT(module_data != NULL);
  int32_t result;
  
  if(module->interface->load_configuration)
  {
    result = module->interface->load_configuration(module_data, mode, config);
    
    if(result != FT_SUCCESS)
    {
      return result;
    }
  }
   
  return FT_SUCCESS;
}

int32_t ft_module_save_configuration(struct ft_module *module, const enum ft_module_mode mode, void *config)
{
  FT_ASSERT(module != NULL);
  FT_ASSERT(config != NULL);
  
  struct ft_module_data *module_data = _ft_module_get_data(module);
  
  FT_ASSERT(module_data != NULL);
  int32_t result;
  
  if(module->interface->save_configuration)
  {
    result = module->interface->save_configuration(module_data, mode, config);
    
    if(result != FT_SUCCESS)
    {
      return result;
    }
  }
   
  return FT_SUCCESS;
}
