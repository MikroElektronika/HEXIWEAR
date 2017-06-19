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
#include "../source/electrodes/ft_electrodes_prv.h"
#include "../source/system/ft_system_prv.h"
#include "../source/keydetectors/ft_keydetector_afid_prv.h"
#include "ft_keydetectors.h"
#include "../source/system/ft_system_mem_prv.h"


static void _ft_keydetector_afid_asc_init(struct ft_keydetector_afid_data *ram);
static void _ft_keydetector_afid_asc_track(const struct ft_keydetector_afid *rom,
                                           struct ft_keydetector_afid_data *ram);
static void _ft_keydetector_afid_asc_process(const struct ft_keydetector_afid *rom,
                                             struct ft_keydetector_afid_data *ram);
static void _ft_keydetector_afid_measure(struct ft_electrode_data *electrode,
                                         uint32_t signal);

static int32_t _ft_keydetector_afid_init(struct ft_electrode_data *electrode);
static int32_t _ft_keydetector_afid_rom_check(const struct ft_keydetector_afid *rom);
static void _ft_keydetector_afid_process(struct ft_electrode_data *electrode);
static void _ft_keydetector_afid_enable(struct ft_electrode_data *electrode, uint32_t touch);

const struct ft_keydetector_interface ft_keydetector_afid_interface = {
  .ft_keydetector_init =        _ft_keydetector_afid_init,
  .ft_keydetector_enable =      _ft_keydetector_afid_enable,
  .ft_keydetector_process =     _ft_keydetector_afid_process,
  .ft_keydetector_measure =     _ft_keydetector_afid_measure,
  .name                   = "ft_keydetector_afid_interface",
};

static int32_t _ft_keydetector_afid_rom_check(const struct ft_keydetector_afid *rom)
{
    if (rom->fast_signal_filter.cutoff == 0) {
        return FT_FAILURE;
    }
    if (rom->slow_signal_filter.cutoff == 0) {
        return FT_FAILURE;
    }
    if (rom->base_avrg.n2_order == 0) {
        return FT_FAILURE;
    }
    return FT_SUCCESS;
}

static void _ft_keydetector_afid_asc_init(struct ft_keydetector_afid_data *ram)
{
    ram->asc.max_resets = 0;
}

static void _ft_keydetector_afid_asc_track(const struct ft_keydetector_afid *rom, struct ft_keydetector_afid_data *ram)
{
    if (ram->asc.max_resets < (int16_t)ram->touch_reset_counter) {
        ram->asc.max_resets = (int16_t)ram->touch_reset_counter;
    }
}

static void _ft_keydetector_afid_asc_process(const struct ft_keydetector_afid *rom, struct ft_keydetector_afid_data *ram)
{
  /* if transition from electrode touch state to release happen */
  if (ram->asc.max_resets != 0) 
  {
    uint32_t touch_threshold = ram->touch_threshold;
    if (ram->asc.max_resets > rom->asc.resets_for_touch) 
    {
      touch_threshold = (touch_threshold * ram->asc.max_resets) / (rom->asc.resets_for_touch * 4);

      if (touch_threshold <= rom->asc.noise_resets_minimum) { /* check if sensitivity is not too low */
        touch_threshold = rom->asc.noise_resets_minimum;
      }
    }else
    {
      touch_threshold = rom->asc.noise_resets_minimum;
    }
    
    
    
    ram->touch_threshold = touch_threshold;
    
    ram->asc.max_resets = 0;
  }
}

static int32_t _ft_keydetector_afid_init(struct ft_electrode_data *electrode)
{
  FT_ASSERT(electrode->rom->keydetector_interface == &ft_keydetector_afid_interface);

  const struct ft_keydetector_afid *rom = electrode->rom->keydetector_params.afid;

  if(_ft_keydetector_afid_rom_check(rom) != FT_SUCCESS)
  {
    return FT_FAILURE;
  }
  
  electrode->keydetector_data.afid = (struct ft_keydetector_afid_data*) 
    _ft_mem_alloc(sizeof(struct ft_keydetector_afid_data));

  if(electrode->keydetector_data.afid == NULL)
  {
      return FT_OUT_OF_MEMORY;
  }
  return FT_SUCCESS;
}

static void _ft_keydetector_afid_enable(struct ft_electrode_data *electrode, uint32_t touch)
{
  const struct ft_keydetector_afid *rom = electrode->rom->keydetector_params.afid;
  struct ft_keydetector_afid_data *ram = electrode->keydetector_data.afid; 
    
  ram->integration_value = FT_KEYDETECTOR_AFID_INITIAL_INTEGRATOR_VALUE;
  ram->touch_threshold = rom->asc.noise_resets_minimum;
  ram->touch_reset_counter = FT_KEYDETECTOR_AFID_INITIAL_RESET_TOUCH_COUNTER_VALUE;
  ram->release_reset_counter = FT_KEYDETECTOR_AFID_INITIAL_RESET_RELEASE_COUNTER_VALUE;
  _ft_keydetector_afid_asc_init(ram);	
	
  if(touch)
  {
      _ft_electrode_set_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG);
  }
  else
  {
      _ft_electrode_clear_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG);
  }
  ram->filter_state = FT_FILTER_STATE_INIT;
  _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_INIT);
  
}

static void _ft_keydetector_afid_measure(struct ft_electrode_data *electrode, uint32_t signal)
{
  FT_ASSERT(electrode->rom->keydetector_interface == &ft_keydetector_afid_interface);

  struct ft_keydetector_afid_data *ram = electrode->keydetector_data.afid;
  const struct ft_keydetector_afid *rom = electrode->rom->keydetector_params.afid;
  
  signal = _ft_electrode_normalization_process(electrode, signal);

  if (ram->filter_state == FT_FILTER_STATE_INIT)
  {
    _ft_filter_fbutt_init(&rom->fast_signal_filter, &ram->fast_signal_filter, signal);
    _ft_filter_fbutt_init(&rom->slow_signal_filter, &ram->slow_signal_filter, signal);
    _ft_filter_moving_average_init(&rom->base_avrg, 
                                   &ram->base_avrg,
                                   signal);
    electrode->baseline = signal;
    ram->slow_signal = (uint16_t)signal;
    _ft_electrode_set_signal(electrode, signal);
    ram->filter_state = FT_FILTER_STATE_RUN;
  } else
  {
    signal = _ft_electrode_shielding_process(electrode, signal);
    uint32_t prev_signal = (uint32_t)_ft_electrode_get_signal(electrode);
    signal = _ft_filter_iir_process(&rom->signal_filter, signal, prev_signal);
        
    ram->slow_signal = (uint16_t)_ft_filter_fbutt_process(&ram->slow_signal_filter, signal);
    signal = (uint16_t)_ft_filter_fbutt_process(&ram->fast_signal_filter, signal);
    _ft_electrode_set_signal(electrode, signal);
  }
  /* calculate delta (subtraction of fast and slow filter) */
  int32_t integration_value = (int32_t)((int32_t)signal - (int32_t)ram->slow_signal);
  /* signal drift suppression - caused by not ideal filters */
  if(_ft_abs_int32(integration_value) <= 8)
  {
    integration_value = 0;
  }
  /* process integration */
  integration_value += (int32_t)ram->integration_value;
  /* process resetting */
  uint32_t touch_reset_counter = ram->touch_reset_counter;
  uint32_t release_reset_counter = ram->release_reset_counter;
  /* perform reset function and touch detection */
  if(_ft_abs_int32(integration_value) > ram->touch_threshold)
  {
    if(integration_value < 0)
    {
      /* negative saturation reset - release */
      /* report release state after so many resets happen as many touch resets happen */
      if (touch_reset_counter > 4U)
      {
        touch_reset_counter -= 4U;
      } else
      {
        release_reset_counter++;
        touch_reset_counter = 0U;
      }
    }else
    {
      /* positive saturation reset - touch */
      /* report touch status */
      touch_reset_counter++;
      release_reset_counter = 0U;
    }    
    integration_value = 0;
  }
  
  ram->touch_reset_counter = touch_reset_counter;
  ram->release_reset_counter = release_reset_counter;
  ram->integration_value = (int16_t)integration_value;
  
  /* perform time dependent operations if release state */
  if (release_reset_counter > 0U) {
      /* slow touch threshold fall if touch threshold > dest threshold */
      if (ram->touch_threshold > rom->asc.noise_resets_minimum) {
          if (!(_ft_electrode_get_time_offset_period(electrode,
                                                    rom->asc.touch_treshold_fall_rate))) {
              ram->touch_threshold -= (ram->touch_threshold / rom->asc.noise_resets_minimum);
              if(ram->touch_threshold < rom->asc.noise_resets_minimum)
                ram->touch_threshold = rom->asc.noise_resets_minimum;
          }
      }
      /* integration reset - for suppression of longterm temperature drift */
      if (!(_ft_electrode_get_time_offset_period(electrode, rom->reset_rate))) {
          ram->integration_value = FT_KEYDETECTOR_AFID_INITIAL_INTEGRATOR_VALUE;
      }
      
      /* Update the baseline */
      electrode->baseline = _ft_filter_moving_average_process(&rom->base_avrg,
                                           &ram->base_avrg,
                                           signal);
  }
}

static void _ft_keydetector_afid_process(struct ft_electrode_data *electrode)
{
  FT_ASSERT(electrode->rom->keydetector_interface == &ft_keydetector_afid_interface);

  struct ft_keydetector_afid_data *ram = electrode->keydetector_data.afid;
  const struct ft_keydetector_afid *rom = electrode->rom->keydetector_params.afid;
  struct ft_kernel *system = _ft_system_get();

  switch (_ft_electrode_get_last_status(electrode)) {
    case FT_ELECTRODE_STATE_INIT:
      /* manage switch from init to run phase */
      if (_ft_electrode_get_time_offset(electrode) >= system->rom->init_time)
      {
        _ft_keydetector_afid_asc_track(rom, ram);
        _ft_keydetector_afid_asc_process(rom, ram);
        
        if(_ft_electrode_get_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG))
            _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_TOUCH);
        else
            _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_RELEASE);
        
        _ft_electrode_clear_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG);
      }
    break;
    case FT_ELECTRODE_STATE_TOUCH:
      if (ram->release_reset_counter > 0U)
      {
        _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_RELEASE);
      } else {
        _ft_keydetector_afid_asc_track(rom, ram);
        
        if (ram->touch_reset_counter < rom->asc.resets_for_touch / 2)
        {
          ram->touch_reset_counter = 0;
        }
      }
    break;

    case FT_ELECTRODE_STATE_RELEASE:
      if (ram->touch_reset_counter > rom->asc.resets_for_touch)
      {
        _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_TOUCH);        
      } else {
        _ft_keydetector_afid_asc_process(rom, ram);
      }
    break;

    default:
    break;
  }
}
