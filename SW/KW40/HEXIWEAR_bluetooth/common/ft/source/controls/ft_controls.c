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
#include "ft_system.h"
#include "../source/system/ft_system_mem_prv.h"
#include "../source/system/ft_system_frmstr_prv.h"
#include "ft_controls.h"
#include "../source/controls/ft_controls_prv.h"
#include "ft_electrodes.h"
#include "../source/electrodes/ft_electrodes_prv.h"

/* internal function */
struct ft_control_data *_ft_control_get_data(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  uint32_t i = 0;

  struct ft_control **controls = (struct ft_control **)_ft_system_get()->rom->controls;

  while(*controls != NULL)
  {
    if(*controls == control)
    {
      return _ft_system_get()->controls[i];
    }
    i++;
    controls++;
  }
  return NULL;
}

int32_t _ft_control_check_data(const struct ft_control_data *control)
{
  int32_t result = FT_SUCCESS;

  if (control->rom == NULL)
  {
    result = FT_FAILURE;
  }

  if (control->rom->interface == NULL)
  {
    result = FT_FAILURE;
  }

  if (control->data.general == NULL)
  {
    result = FT_FAILURE;
  }

  if (control->rom->electrodes == NULL)
  {
    result = FT_FAILURE;
  }
  return result;
}

struct ft_control_data *_ft_control_init(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);

  struct ft_control_data *_this = _ft_mem_alloc(sizeof(struct ft_control_data));

  if(_this == NULL)
  {
      return NULL;
  }

  _this->rom = control;
  _this->electrodes_size = ft_control_count_electrodes(_this->rom);

  _this->electrodes = _ft_mem_alloc(sizeof(struct ft_electrode_data*) * _this->electrodes_size);

  if(_this->electrodes == NULL)
  {
      return NULL;
  }

  uint32_t i;
  for(i=0; i < _this->electrodes_size; i++)
  {
    _this->electrodes[i] = _ft_electrode_get_data(control->electrodes[i]);
  }

  if(control->interface->init != NULL)
  {
      if(control->interface->init(_this) < FT_SUCCESS)
      {
          return NULL; /* failure stops the entire init phase */
      }
  }

  if (_ft_control_check_data(_this) != FT_SUCCESS) {
      return NULL;
  }
  
  if(_ft_freemaster_add_variable(control->interface->name, "ft_control_interface", (void*) control->interface, sizeof(struct ft_control_interface)) != FT_SUCCESS)
  {
    return NULL;
  }

  return _this;
}

void ft_control_enable(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  
  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);
  
  _ft_control_set_flag(control_data, FT_CONTROL_EN_FLAG);
}

void ft_control_disable(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  
  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);
  
  _ft_control_clear_flag(control_data, FT_CONTROL_EN_FLAG);
}

int32_t ft_control_get_touch_button(const struct ft_control *control,
                                    uint32_t index)
{
  FT_ASSERT(control != NULL);
  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT((control_data != NULL));
  
  uint32_t elec_counter = control_data->electrodes_size;

  for (uint32_t i = index; i < elec_counter; i++) {
      if (_ft_electrode_get_last_status(control_data->electrodes[i]) == FT_ELECTRODE_STATE_TOUCH) {
          return i;
      }
  }
  return FT_FAILURE;
}

uint32_t _ft_control_get_electrodes_state(struct ft_control_data *control)
{
    FT_ASSERT(control != NULL);
    uint32_t elec_counter = control->electrodes_size;
    uint32_t current_state = 0U;

    while (elec_counter--) {
        uint32_t electrode_state = _ft_electrode_is_touched(control->electrodes[elec_counter]);
        /* all elec status in a bit field */
        current_state |= (electrode_state << elec_counter);
    }
    return current_state;
}

uint32_t _ft_control_get_electrodes_digital_state(struct ft_control_data *control)
{
    FT_ASSERT(control != NULL);
    uint32_t elec_counter = control->electrodes_size;
    uint32_t current_state = 0U;

    while (elec_counter--) {
        /* all elec status in a bit field */
		if(_ft_electrode_get_flag(control->electrodes[elec_counter], FT_ELECTRODE_DIGITAL_RESULT_ONLY_FLAG | FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG))
        	current_state |= (1 << elec_counter);
    }
    return current_state;
}

uint32_t ft_control_get_electrodes_state(struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);
    
  return _ft_control_get_electrodes_state(control_data);
}

/* Internal function */
void _ft_control_set_flag_all_elec(struct ft_control_data *control,
                                  uint32_t flag)
{
    FT_ASSERT(control != NULL);
    uint32_t elec_counter = control->electrodes_size;

    while (elec_counter--) {
        _ft_electrode_set_flag(control->electrodes[elec_counter], flag);
    }
}

/* Internal function */
void _ft_control_clear_flag_all_elec(struct ft_control_data *control, uint32_t flag)
{
    FT_ASSERT(control != NULL);
    uint32_t elec_counter = control->electrodes_size;

    while (elec_counter--) {
        _ft_electrode_clear_flag(control->electrodes[elec_counter], flag);
    }
}

int32_t _ft_control_check_neighbours_electrodes(struct ft_control_data *control,
                                                uint32_t first, 
                                                uint32_t second, 
                                                uint32_t overrun)
{
    uint32_t result;
    uint32_t elec_size = control->electrodes_size;
    
    if (first > second) {
        result = first - second;
    } else {
        result = second - first;
    }
    
    if(overrun)
    {
      if ((result > 1U) && (result == (elec_size - 1U))) 
      {
          result = 1; /* valid for arotary */
      }
    }
    
    return (result > 1U) ? FT_INVALID_RESULT : FT_SUCCESS;
}

int32_t _ft_control_check_edge_electrodes(struct ft_control_data *control,
                                                uint32_t electrode_ix)
{
    
    uint32_t elec_size = control->electrodes_size;
    
    if((electrode_ix == 0) || (electrode_ix == (elec_size-1)))
      return FT_SUCCESS;
    
    return FT_INVALID_RESULT;
}

uint32_t ft_control_count_electrodes(const struct ft_control *control)
{
    FT_ASSERT(control != NULL);
    uint32_t elec_counter = 0U;

    while (control->electrodes[elec_counter] != NULL) {
        elec_counter++;
    }

    return elec_counter;
}

const struct ft_electrode *ft_control_get_electrode(const struct ft_control *control,
                                                                  uint32_t index)
{
  FT_ASSERT((control != NULL));
  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT((control_data != NULL));
  
  if (control_data->electrodes_size < index) {
      return control->electrodes[index];
  } else {
      return NULL;
  }
}

uint32_t _ft_control_get_first_elec_touched(uint32_t current_state)
{
    FT_ASSERT(current_state != 0U);
    uint32_t first_elec_index = 0U;

    while (((current_state >> first_elec_index) & 0x1U) == 0U) {
        first_elec_index++;
    }
    return first_elec_index;
}

uint32_t _ft_control_get_last_elec_touched(uint32_t current_state)
{
    FT_ASSERT(current_state != 0U);
    uint32_t last_elec_index = 0U;

    while (current_state >> last_elec_index) {
        last_elec_index++;
    }
    return last_elec_index;
}

uint32_t _ft_control_get_touch_count(uint32_t current_state)
{
    uint32_t touch_count = 0U;
    uint32_t i_mask = 1U;
    
    while (current_state) 
    {
      if(current_state & i_mask)
      {
        current_state &= ~i_mask;
        touch_count++;
      }
      i_mask <<= 1U; 
    }
    return touch_count;
}

