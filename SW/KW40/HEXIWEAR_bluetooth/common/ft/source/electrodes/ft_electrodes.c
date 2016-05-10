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
#include "../source/electrodes/ft_electrodes_prv.h"
#include "ft_electrodes.h"
#include "../source/modules/ft_modules_prv.h"
#include "../include/ft_system.h"

/* internal function */
struct ft_module_data *ft_electrode_get_module_data(const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);

  struct ft_module_data **modules = _ft_system_get()->modules;
  // try to find in each module
  while(*modules != NULL)
  {
    struct ft_module *module = (struct ft_module *)(*modules)->rom;
    struct ft_electrode **electrodes = (struct ft_electrode **)(module)->electrodes;

    while(*electrodes != NULL)
    {
      if(electrode == *electrodes)
      {
        return *modules;
      }
      electrodes++;
    }
    modules++;
  }
  return NULL;
}

/* internal function */
int32_t _ft_electrode_get_index_from_module(const struct ft_module * module, const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);
  uint32_t e = 0;

  struct ft_electrode **electrodes = (struct ft_electrode **)module->electrodes;
  e = 0;
  while(*electrodes != NULL)
  {
    if(electrode == *electrodes)
    {
      return e;
    }
    e++;
    electrodes++;
  }

  return -1;
}

/* internal function */
struct ft_electrode_data *_ft_electrode_get_data(const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);
  uint32_t m = 0;
  int32_t e = 0;

  struct ft_module **modules = (struct ft_module **)_ft_system_get()->rom->modules;
  // try to find in each module
  while(*modules != NULL)
  {
    e = _ft_electrode_get_index_from_module(*modules, electrode);
    
    if(e >= 0)
    {
      return _ft_system_get()->modules[m]->electrodes[e];
    }
    
    m++;
    modules++;
  }

  return NULL;
}
/* internal function */
uint32_t _ft_electrode_shielding_process(struct ft_electrode_data *electrode,
                                        uint32_t signal)
{
    FT_ASSERT(electrode != NULL);
    struct ft_electrode_data *shielding_electrode = electrode->shielding_electrode;

    if (shielding_electrode != NULL) {
        uint32_t shielding_signal = _ft_electrode_get_signal(shielding_electrode);
        shielding_signal -= shielding_electrode->baseline;
        shielding_signal += signal;
        if (shielding_signal > 0) {
            signal = shielding_signal;
        } else {
            signal = 0;
        }
    }
    return signal;
}

/* internal function */
uint32_t _ft_electrode_normalization_process(const struct ft_electrode_data *electrode,
                                            uint32_t signal)
{
    FT_ASSERT(electrode != NULL);
    /* signal here is unsigned - division */
    if (electrode->rom->multiplier > 0U) {
        if (electrode->rom->multiplier < (0xFFFFU / signal)) {
            signal *=  electrode->rom->multiplier;
        } else {
            signal = 0xFFFFU;
        }
    }
    if (electrode->rom->divider > 0U) {
        signal /= electrode->rom->divider;
    }
    return signal;
}

struct ft_electrode_data *_ft_electrode_init(struct ft_module_data * module, const struct ft_electrode *electrode)
{
    FT_ASSERT(electrode != NULL);


    struct ft_electrode_data *elec = _ft_mem_alloc(sizeof(struct ft_electrode_data));
    if (elec == NULL)
    {
      return NULL;
    }

    elec->rom = electrode;

    _ft_electrode_set_status(elec, FT_ELECTRODE_STATE_INIT);
    elec->status_index = 0U;
    if(electrode->shielding_electrode != NULL)
    {
      int32_t index = _ft_electrode_get_index_from_module(module->rom, electrode->shielding_electrode);
      if(index < 0)
      {
        return NULL;
      }
      elec->shielding_electrode = module->electrodes[index];
    }else
    {
      elec->shielding_electrode = NULL;
    }
    return elec;
}


int32_t ft_electrode_enable(const struct ft_electrode *electrode, uint32_t touch)
{
  FT_ASSERT(electrode != NULL);
  int32_t res;
  struct ft_module_data *module_data = ft_electrode_get_module_data(electrode);
  struct ft_electrode_data * electrode_data = _ft_electrode_get_data(electrode);
  FT_ASSERT(electrode_data != NULL);
  
  FT_ASSERT(module_data != NULL);
  FT_ASSERT(module_data->rom->interface->electrode_enable != NULL);

  res = module_data->rom->interface->electrode_enable(module_data, electrode->pin_input);
  
  if(res != FT_SUCCESS)
      return res;
	  
  electrode_data->signal = 0;
  
  electrode->keydetector_interface->ft_keydetector_enable(electrode_data, touch);
  
  return FT_SUCCESS; 
}

int32_t ft_electrode_disable(const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);

  struct ft_module_data *module_data = ft_electrode_get_module_data(electrode);

  FT_ASSERT(module_data != NULL);
  FT_ASSERT(module_data->rom->interface->electrode_disable != NULL);

  return module_data->rom->interface->electrode_disable(module_data, electrode->pin_input);
}

uint32_t ft_electrode_get_signal(const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);
  
  struct ft_electrode_data * electrode_data = _ft_electrode_get_data(electrode);
  FT_ASSERT(electrode_data != NULL);
  
  return _ft_electrode_get_signal(electrode_data);
}

int32_t ft_electrode_get_last_status(const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);
  
  struct ft_electrode_data * electrode_data = _ft_electrode_get_data(electrode);
  FT_ASSERT(electrode_data != NULL);
  
  return _ft_electrode_get_last_status(electrode_data);
}

uint32_t ft_electrode_get_time_offset(const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);
  
  struct ft_electrode_data * electrode_data = _ft_electrode_get_data(electrode);
  FT_ASSERT(electrode_data != NULL);
  
  return _ft_electrode_get_time_offset(electrode_data);
}
  
uint32_t ft_electrode_get_last_time_stamp(const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);
  
  struct ft_electrode_data * electrode_data = _ft_electrode_get_data(electrode);
    
  FT_ASSERT(electrode_data != NULL);
  
  return _ft_electrode_get_last_time_stamp(electrode_data);
}

uint32_t ft_electrode_get_raw_signal(const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);
  
  struct ft_electrode_data * electrode_data = _ft_electrode_get_data(electrode);
  FT_ASSERT(electrode_data != NULL);
  
  return _ft_electrode_get_raw_signal(electrode_data);
}
  
uint32_t _ft_electrode_get_signal(const struct ft_electrode_data *electrode)
{
    FT_ASSERT(electrode != NULL);
    return electrode->signal;
}

const struct ft_electrode * _ft_electrode_get_shield(const struct ft_electrode *electrode)
{
  FT_ASSERT(electrode != NULL);
  
  return electrode->shielding_electrode;
}

/* internal function */
void _ft_electrode_set_signal(struct ft_electrode_data *electrode,
                             uint32_t signal)
{
    FT_ASSERT(electrode != NULL);
    electrode->signal = (uint16_t)signal;
}

/* internal function */
void _ft_electrode_set_raw_signal(struct ft_electrode_data *electrode,
                                 uint32_t signal)
{
    FT_ASSERT(electrode != NULL);
    electrode->raw_signal = (uint16_t)signal;
}

uint32_t _ft_electrode_get_raw_signal(const struct ft_electrode_data *electrode)
{
    FT_ASSERT(electrode != NULL);
    return (int32_t)electrode->raw_signal;
}

/* internal function */
void _ft_electrode_set_status(struct ft_electrode_data *electrode,
                             int32_t state)
{
    FT_ASSERT(electrode != NULL);
    uint32_t index = (uint32_t)electrode->status_index;

    if (++index >= FT_ELECTRODE_STATUS_HISTORY_COUNT) {
        index = 0U;
    }
    electrode->status_index = (uint8_t)index;
    electrode->status[index].state = (uint8_t)state;
    uint32_t time_stamp = ft_system_get_time_counter();
    electrode->status[index].time_stamp = time_stamp;
}

int32_t _ft_electrode_get_status(const struct ft_electrode_data *electrode,
                                uint32_t index)
{
    FT_ASSERT(electrode != NULL);
    if (index < FT_ELECTRODE_STATUS_HISTORY_COUNT) {
        return (int32_t)electrode->status[index].state;
    } else {
        return FT_FAILURE;
    }
}

int32_t _ft_electrode_get_last_status(const struct ft_electrode_data *electrode)
{
    FT_ASSERT(electrode != NULL);
    return _ft_electrode_get_status(electrode, electrode->status_index);
}

int32_t _ft_electrode_get_delta(const struct ft_electrode_data *electrode)
{
    FT_ASSERT(electrode != NULL);
    return (_ft_electrode_get_signal(electrode) - (uint32_t)electrode->baseline);
}

uint32_t _ft_electrode_get_time_stamp(const struct ft_electrode_data *electrode,
                                     uint32_t index)
{
    FT_ASSERT(electrode != NULL);
    if (index < FT_ELECTRODE_STATUS_HISTORY_COUNT) {
        return electrode->status[index].time_stamp;
    } else {
        return 0U;
    }
}

uint32_t _ft_electrode_get_last_time_stamp(const struct ft_electrode_data *electrode)
{
    FT_ASSERT(electrode != NULL);
    return _ft_electrode_get_time_stamp(electrode, electrode->status_index);
}

uint32_t _ft_electrode_get_time_offset(const struct ft_electrode_data *electrode)
{
    FT_ASSERT(electrode != NULL);
    return ft_system_get_time_offset(_ft_electrode_get_last_time_stamp(electrode));
}

uint32_t _ft_electrode_get_time_offset_period(const struct ft_electrode_data *electrode,
                                             uint32_t event_period)
{
    FT_ASSERT(electrode != NULL);
    if (event_period) {
        uint32_t time_offset = _ft_electrode_get_time_offset(electrode);
        uint32_t time_period = (uint32_t)_ft_system_get_time_period();
        return ((time_offset / time_period) % event_period);
    } else {
        return 1U; /* does not perform function if period is 0 */
    }
}

uint32_t _ft_electrode_is_touched(const struct ft_electrode_data *electrode)
{
    FT_ASSERT(electrode != NULL);
    uint32_t touched = 0;

    if (_ft_electrode_get_status(electrode, electrode->status_index) ==
        FT_ELECTRODE_STATE_TOUCH) {
        touched = 1;
    }
    return touched;
}
