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
#include "ft_controls.h"
#include "../source/controls/ft_controls_prv.h"
#include "ft_electrodes.h"
#include "../source/electrodes/ft_electrodes_prv.h"
#include "ft_control_arotary.h"
#include "ft_control_arotary_prv.h"
#include "ft_keydetector_safa.h"

/* Invoke callback based on the even has occured */
static void _ft_control_arotary_invoke_callback(const struct ft_control_data *control,
                                       enum ft_control_arotary_event event, 
                                       uint32_t position);
/* Find maximum delta electrode */
static int32_t _ft_control_arotary_get_base_data(struct ft_control_data *control,
                                                   struct ft_control_arotary_temp_data *temp_data);
/* Calculate position */
static uint32_t _ft_control_arotary_calculate_position(const struct ft_control_data *control,
                                              struct ft_control_arotary_temp_data *temp_data);
/* Provide event when all electrodes are released. */ 
static void __ft_control_arotary_process_all_released(struct ft_control_data *control);
/* The Analog Rotary initialization function. */
static int32_t _ft_control_arotary_init(struct ft_control_data *control);
/* The Analog Rotary process function. */
static int32_t _ft_control_arotary_process(struct ft_control_data *control);

/* The Analog Rotary control interface. */
const struct ft_control_interface ft_control_arotary_interface = {
  .init    = _ft_control_arotary_init,
  .process = _ft_control_arotary_process,
  .name    = "ft_control_arotary_interface",
};

void ft_control_arotary_register_callback(const struct ft_control *control,
                                           ft_control_arotary_callback callback)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_arotary_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  struct ft_control_arotary_data *ram = control_data->data.arotary;
  FT_ASSERT(ram != NULL);

  ram->callback = callback;
}

uint32_t ft_control_arotary_get_position(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_arotary_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  struct ft_control_arotary_data *ram = control_data->data.arotary;
  FT_ASSERT(ram != NULL);

  return (uint32_t)ram->position;
}

uint32_t ft_control_arotary_is_touched(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_arotary_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  uint32_t flag = _ft_control_get_flag(control_data, FT_AROTARY_TOUCH_FLAG);
  return flag ? 1U : 0U;
}

uint32_t ft_control_arotary_movement_detected(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_arotary_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  uint32_t flag = _ft_control_get_flag(control_data, FT_AROTARY_MOVEMENT_FLAG);
  return flag ? 1U : 0U;
}

uint32_t ft_control_arotary_get_direction(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_arotary_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  uint32_t flag = _ft_control_get_flag(control_data, FT_AROTARY_DIRECTION_FLAG);
  return flag ? 1U : 0U;
}

uint32_t ft_control_arotary_get_invalid_position(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_arotary_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  uint32_t flag = _ft_control_get_flag(control_data, FT_AROTARY_INVALID_POSITION_FLAG);
  return flag ? 1U : 0U;
}

static void _ft_control_arotary_invoke_callback(const struct ft_control_data *control,
                                       enum ft_control_arotary_event event, 
                                       uint32_t position)
{
  struct ft_control_arotary_data *ram = control->data.arotary;
  FT_ASSERT(ram != NULL);

  if (ram->callback != NULL) 
  {
    ram->callback(control->rom, event, position);
  }
}


static int32_t _ft_control_arotary_get_base_data(struct ft_control_data *control,
                                                   struct ft_control_arotary_temp_data *temp_data)
{
    uint32_t elec_counter = control->electrodes_size;
    int32_t delta;
    int32_t delta1 = 0, delta2 = 0;
    uint32_t max_first = 0, max_second = 0;

    /* finding the maximum 2 deltas in the control */
    while (elec_counter--) 
    {
        delta = _ft_electrode_get_delta(control->electrodes[elec_counter]);
        
        if(delta < 0)
        {
          return FT_INVALID_RESULT;
        }
        
        if (delta > delta1) 
        {
            max_second = max_first;
            max_first = elec_counter;
            delta2 = delta1;
            delta1 = delta;
        } else if (delta > delta2) 
        {
            max_second = elec_counter;
            delta2 = delta;
        }
    }
    
    if (_ft_control_check_neighbours_electrodes(control, max_first, max_second, 1) != FT_SUCCESS) 
    {
        _ft_control_set_flag(control, FT_AROTARY_INVALID_POSITION_FLAG);
        return FT_INVALID_RESULT;
    }
    
    if((_ft_control_check_edge_electrodes(control, max_first) == FT_SUCCESS) && 
       (_ft_control_check_edge_electrodes(control, max_second) == FT_SUCCESS))
    {
      temp_data->active_el_ix = control->electrodes_size - 1;
      if(max_first == 0)
        temp_data->first_delta = delta1;
      else
        temp_data->first_delta = delta2;      
    }else if(max_first < max_second)
    {
      temp_data->active_el_ix = max_first;
      temp_data->first_delta = delta2;
      
    }else
    {
      temp_data->active_el_ix = max_second;
      temp_data->first_delta = delta1;
    } 
    temp_data->range = delta1 + delta2;
    
    _ft_control_clear_flag(control, FT_AROTARY_INVALID_POSITION_FLAG);
    
    return FT_SUCCESS;
}





static uint32_t _ft_control_arotary_calculate_position(const struct ft_control_data *control,
                                              struct ft_control_arotary_temp_data *temp_data)
{
  FT_ASSERT(control->rom->interface == &ft_control_arotary_interface);

  uint32_t temp_range = 0xffffU / control->electrodes_size;
  
  uint32_t real_position = temp_range * temp_data->active_el_ix;
  
  const struct ft_control_arotary *arotary_desc = control->rom->control_params.arotary;

  real_position += ( temp_range * temp_data->first_delta) / temp_data->range;
  
  return (real_position * arotary_desc->range) / 0xffffU;
}

static void __ft_control_arotary_process_all_released(struct ft_control_data *control)
{
    /* all released */
    if (_ft_control_get_flag(control, FT_AROTARY_TOUCH_FLAG)) {
      struct ft_control_arotary_data *ram = control->data.arotary;
      FT_ASSERT(ram != NULL);
      /* if none is touched & touch was reported, allreleased event */
      _ft_control_clear_flag(control, FT_AROTARY_TOUCH_FLAG | FT_AROTARY_INVALID_POSITION_FLAG | FT_AROTARY_MOVEMENT_FLAG);
      _ft_control_arotary_invoke_callback(control, FT_AROTARY_ALL_RELEASE,
                                  (uint32_t)ram->position);
      _ft_control_clear_flag_all_elec(control, FT_ELECTRODE_LOCK_BASELINE_REQ_FLAG);
    }
    _ft_control_clear_flag(control, FT_CONTROL_NEW_DATA_FLAG); /* data processed */
}

static int32_t _ft_control_arotary_init(struct ft_control_data *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->rom->interface == &ft_control_arotary_interface);
  FT_ASSERT(control->rom->control_params.arotary != NULL);
  
  #if (FT_DEBUG == 0)
  uint32_t elec_cnt = control->electrodes_size;
  while(elec_cnt--)
  {
    FT_ASSERT(control->electrodes[elec_cnt]->rom->keydetector_interface == &ft_keydetector_safa_interface);
  }
  #endif

  const struct ft_control_arotary *arotary = control->rom->control_params.arotary;

  if(arotary->range == 0)
  {
      return FT_FAILURE;
  }

  control->data.arotary = _ft_mem_alloc(sizeof(struct ft_control_arotary_data));

  if(control->data.arotary == NULL)
  {
      return FT_OUT_OF_MEMORY;
  }

  if (_ft_control_check_data(control) != FT_SUCCESS) {
      return FT_FAILURE;
  }

  return FT_SUCCESS;
}

static int32_t _ft_control_arotary_process(struct ft_control_data *control)
{
    FT_ASSERT(control != NULL);
    FT_ASSERT(control->rom->interface == &ft_control_arotary_interface);

    if (!_ft_control_get_flag(control, FT_CONTROL_EN_FLAG) ||
        !_ft_control_get_flag(control, FT_CONTROL_NEW_DATA_FLAG)) {
        return FT_FAILURE; /* control disabled or data not ready */
    }

    if (!_ft_control_get_electrodes_state(control)) {
        __ft_control_arotary_process_all_released(control);
        return FT_SUCCESS; /* no touch on the control's electrodes */
    }

    if (_ft_control_get_electrodes_digital_state(control)) {
        return FT_SUCCESS; /* no touch on the control's electrodes */
    }
        
    struct ft_control_arotary_data *ram = control->data.arotary;
    const struct ft_control_arotary *arotary = control->rom->control_params.arotary;

    struct ft_control_arotary_temp_data computing_data;
    
    /* at least one is touched, validate position */
    if (_ft_control_arotary_get_base_data(control, &computing_data) == FT_SUCCESS) 
    {
        uint32_t current_position = _ft_control_arotary_calculate_position(control,
                                                                  &computing_data);


        uint32_t previous_pos = ram->position;

        uint32_t subrange = (arotary->range - 1U) / control->electrodes_size;
        if (previous_pos != current_position) {
            /* handle edge cases on rotary */
            if ((previous_pos > ((arotary->range - 1U) - subrange)) && ( previous_pos < subrange)) {
                _ft_control_set_flag(control, FT_AROTARY_DIRECTION_FLAG);
            } else if ((current_position > ((arotary->range - 1U) - subrange)) &&
                       (current_position < subrange)) {
                _ft_control_clear_flag(control, FT_AROTARY_DIRECTION_FLAG);
            } else {
                /* no edge case here */
                if (previous_pos < current_position) {
                    _ft_control_set_flag(control, FT_AROTARY_DIRECTION_FLAG);
                } else {
                    _ft_control_clear_flag(control, FT_AROTARY_DIRECTION_FLAG);
                }
            }
            ram->position = current_position;
            _ft_control_set_flag(control, FT_AROTARY_MOVEMENT_FLAG);
            _ft_control_arotary_invoke_callback(control, FT_AROTARY_MOVEMENT,
                                       (uint32_t)ram->position);
        }else
        {
          _ft_control_clear_flag(control, FT_AROTARY_MOVEMENT_FLAG);
        }

    }

    /* if arotary is touched for the first time */
    if (!_ft_control_get_flag(control, FT_AROTARY_TOUCH_FLAG)) {
        _ft_control_arotary_invoke_callback(control, FT_AROTARY_INITIAL_TOUCH,
                                   (uint32_t)ram->position);
    }
    /* lock baseline for all elec in the control */
    _ft_control_set_flag_all_elec(control, FT_ELECTRODE_LOCK_BASELINE_REQ_FLAG);
    _ft_control_set_flag(control, FT_AROTARY_TOUCH_FLAG);
    _ft_control_clear_flag(control, FT_CONTROL_NEW_DATA_FLAG); /* data processed */
    return FT_SUCCESS;
}

