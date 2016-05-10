/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
#include "ft_keydetector_safa_prv.h"
#include "ft_keydetectors.h"
#include "../source/system/ft_system_mem_prv.h"

static int32_t _ft_keydetector_safa_rom_check(const struct ft_keydetector_safa *rom);
static void _ft_keydetector_safa_signal_track(struct ft_electrode_data *electrode,
                                                const struct ft_keydetector_safa *rom,
                                                struct ft_keydetector_safa_data *ram,
                                                uint16_t signal);
static void _ft_reset_keydetector_safa_reset(struct ft_electrode_data *electrode, uint32_t signal, uint32_t touch);
static void _ft_keydetector_safa_lock_baseline(struct ft_electrode_data *electrode,
                                                const struct ft_keydetector_safa *rom, 
                                                struct ft_keydetector_safa_data *ram, 
                                                uint16_t signal);

static void _ft_keydetector_safa_unlock_baseline(struct ft_electrode_data *electrode,
                                                const struct ft_keydetector_safa *rom, 
                                                struct ft_keydetector_safa_data *ram, 
                                                uint16_t signal);

static int32_t _ft_keydetector_safa_init(struct ft_electrode_data *electrode);
static void _ft_keydetector_safa_measure(struct ft_electrode_data *electrode,
                      uint32_t signal);
static void _ft_keydetector_safa_process(struct ft_electrode_data *electrode);
static void _ft_keydetector_safa_enable(struct ft_electrode_data *electrode, uint32_t touch);

const struct ft_keydetector_safa ft_keydetector_safa_default = 
{
    .signal_filter = 2,
    .base_avrg = {.n2_order = 9},
    .non_activity_avrg =  {.n2_order = FT_FILTER_MOVING_AVERAGE_MAX_ORDER},
    .entry_event_cnt = 4,
    .signal_to_noise_ratio = 8,
    .deadband_cnt = 5,
    .min_noise_limit = 20,
};

const struct ft_keydetector_interface ft_keydetector_safa_interface = {
  .ft_keydetector_init =        _ft_keydetector_safa_init,
  .ft_keydetector_process =     _ft_keydetector_safa_process,
  .ft_keydetector_measure =     _ft_keydetector_safa_measure,
  .ft_keydetector_enable =      _ft_keydetector_safa_enable,
  .name                   =     "ft_keydetector_safa_interface",
};

static int32_t _ft_keydetector_safa_rom_check(const struct ft_keydetector_safa *rom)
{
    
    return FT_SUCCESS;
}

static int32_t _ft_keydetector_safa_init(struct ft_electrode_data *electrode)
{
  FT_ASSERT(electrode->rom->keydetector_interface == &ft_keydetector_safa_interface);

  const struct ft_keydetector_safa *rom = electrode->rom->keydetector_params.safa;

  if(_ft_keydetector_safa_rom_check(rom) != FT_SUCCESS)
  {
    return FT_FAILURE;
  }

  electrode->keydetector_data.safa = (struct ft_keydetector_safa_data *) _ft_mem_alloc(sizeof(struct ft_keydetector_safa_data));

  if(electrode->keydetector_data.safa == NULL)
  {
      return FT_OUT_OF_MEMORY;
  }
  electrode->keydetector_data.safa->recovery_cnt = 0;
  
  electrode->keydetector_data.safa->base_avrg_init = rom->base_avrg;
  electrode->keydetector_data.safa->noise_avrg_init = rom->base_avrg;
  electrode->keydetector_data.safa->noise_avrg_init.n2_order += 2;
  electrode->keydetector_data.safa->predicted_signal_avrg_init = rom->base_avrg;
  if(electrode->keydetector_data.safa->predicted_signal_avrg_init.n2_order > 2)
    electrode->keydetector_data.safa->predicted_signal_avrg_init.n2_order -= 2;
  
  _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_INIT);
  
  return FT_SUCCESS;
}

static void _ft_keydetector_safa_enable(struct ft_electrode_data *electrode, uint32_t touch)
{
  struct ft_keydetector_safa_data *ram = electrode->keydetector_data.safa;
  uint32_t signal = _ft_electrode_get_signal(electrode);
  
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

static void _ft_keydetector_safa_measure(struct ft_electrode_data *electrode, uint32_t signal)
{
    FT_ASSERT(electrode->rom->keydetector_interface == &ft_keydetector_safa_interface);

    const struct ft_keydetector_safa *rom = electrode->rom->keydetector_params.safa;
    struct ft_keydetector_safa_data *ram = electrode->keydetector_data.safa;

    
    signal = _ft_electrode_normalization_process(electrode, signal);

    if (ram->filter_state == FT_FILTER_STATE_INIT) {
        _ft_reset_keydetector_safa_reset(electrode, signal, _ft_electrode_get_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG));       
        ram->filter_state = FT_FILTER_STATE_RUN;
    } else {
        signal = _ft_electrode_shielding_process(electrode, signal);
        uint32_t prev_signal = (uint32_t)_ft_electrode_get_signal(electrode);
        uint32_t iir_signal = _ft_filter_iir_process(&rom->signal_filter, signal, prev_signal);
        _ft_electrode_set_signal(electrode, iir_signal);
        
        _ft_keydetector_safa_signal_track(electrode, rom, ram, iir_signal);
    }
    
}


static void _ft_reset_keydetector_safa_reset(struct ft_electrode_data *electrode, uint32_t signal, uint32_t touch)
{
    FT_ASSERT(electrode->rom->keydetector_interface == &ft_keydetector_safa_interface);

    const struct ft_keydetector_safa *rom = electrode->rom->keydetector_params.safa;
    struct ft_keydetector_safa_data *ram = electrode->keydetector_data.safa;

    _ft_electrode_clear_flag(electrode, 
                             FT_ELECTRODE_LOCK_BASELINE_REQ_FLAG | 
                             FT_ELECTRODE_LOCK_BASELINE_FLAG | 
                             FT_ELECTRODE_DIGITAL_RESULT_ONLY_FLAG | 
                             FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG
                             );
    
    if(!touch)
    {    
      _ft_electrode_set_signal(electrode, signal);
      
      ram->base_avrg_init.n2_order = rom->base_avrg.n2_order;
      _ft_filter_moving_average_init(&ram->base_avrg_init, 
                                     &ram->base_avrg,
                                     signal);
      electrode->baseline = electrode->signal;
      _ft_filter_moving_average_init(&ram->noise_avrg_init, 
                                     &ram->noise_avrg,
                                     rom->min_noise_limit); 

      ram->predicted_signal = signal + rom->min_noise_limit * rom->signal_to_noise_ratio;
      _ft_filter_moving_average_init(&rom->non_activity_avrg, 
                                     &ram->predicted_signal_avrg,
                                     ram->predicted_signal);

      ram->noise = rom->min_noise_limit;
      
      _ft_electrode_clear_flag(electrode, FT_ELECTRODE_LOCK_BASELINE_FLAG);
    }
    else
    {
      _ft_electrode_set_signal(electrode, signal);
      
      electrode->baseline = _ft_filter_limit_u(((signal / 4) * 3), 0, 50000);

      ram->base_avrg_init = rom->non_activity_avrg;
      _ft_filter_moving_average_init(&ram->base_avrg_init,
                                     &ram->base_avrg,
                                     electrode->baseline);
      
      _ft_filter_moving_average_init(&ram->noise_avrg_init,
                                     &ram->noise_avrg,
                                     rom->min_noise_limit); 

      ram->predicted_signal = signal;
      _ft_filter_moving_average_init(&ram->predicted_signal_avrg_init,
                                     &ram->predicted_signal_avrg,
                                     ram->predicted_signal);

      ram->noise = rom->min_noise_limit;
      
      _ft_keydetector_safa_lock_baseline(electrode, rom, ram, signal);
      _ft_electrode_set_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG);
    }
}

static void _ft_keydetector_safa_process(struct ft_electrode_data *electrode)
{
    FT_ASSERT(electrode->rom->keydetector_interface == &ft_keydetector_safa_interface);

    const struct ft_keydetector_safa *rom = electrode->rom->keydetector_params.safa;
    struct ft_keydetector_safa_data *ram = electrode->keydetector_data.safa;
    struct ft_kernel *system = _ft_system_get();

    int32_t signal = (int32_t)_ft_electrode_get_signal(electrode);
    int32_t delta = _ft_filter_abs(electrode->baseline - signal);
    uint16_t sig_filter = signal;
    
      switch (_ft_electrode_get_last_status(electrode))
      {
        case FT_ELECTRODE_STATE_INIT:
            /* manage switch from electrode init to run phase */
            if (_ft_electrode_get_time_offset(electrode) >= system->rom->init_time)
            {
              ram->entry_event_cnt = 0;
              ram->deadband_cnt = rom->deadband_cnt;
                            
              if(_ft_electrode_get_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG))
              {  
                if(sig_filter < (ram->noise * rom->signal_to_noise_ratio))
                {
                  sig_filter = ram->noise * rom->signal_to_noise_ratio;
                }
                _ft_filter_moving_average_init(&ram->predicted_signal_avrg_init, 
                   &ram->predicted_signal_avrg, sig_filter);
                _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_TOUCH);
                _ft_keydetector_safa_lock_baseline(electrode, rom, ram, signal);
              }
              else
              { 
                _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_RELEASE);
                _ft_filter_moving_average_init(&rom->non_activity_avrg, 
                               &ram->predicted_signal_avrg,
                               ram->predicted_signal);
                _ft_keydetector_safa_unlock_baseline(electrode, rom, ram, signal);
              }              
            }
          break;
        case FT_ELECTRODE_STATE_TOUCH:
            if((delta < (_ft_filter_abs(ram->predicted_signal - electrode->baseline) / 2)) && (ram->deadband_cnt == 0))              
            {
              ram->entry_event_cnt = 0;
              ram->deadband_cnt = rom->deadband_cnt;
              _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_RELEASE);
              _ft_filter_moving_average_init(&rom->non_activity_avrg, 
                               &ram->predicted_signal_avrg,
                               ram->predicted_signal);
              
              /* is init touch */
              if(_ft_electrode_get_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG))
              {
                if(!_ft_electrode_get_flag(electrode, FT_ELECTRODE_LOCK_BASELINE_REQ_FLAG))
                  _ft_keydetector_safa_unlock_baseline(electrode, rom, ram, signal);
              }
            }else
            {
                ram->entry_event_cnt = 0;
                if(ram->deadband_cnt)
                {
                    ram->deadband_cnt--;
                }
            }
            

          break;
        case FT_ELECTRODE_STATE_RELEASE:
              if(((delta > (_ft_filter_abs(ram->predicted_signal - electrode->baseline) / 4))) &&
                 (ram->deadband_cnt == 0) &&
                 (!_ft_filter_is_deadrange_u(signal, electrode->baseline, (ram->noise * rom->signal_to_noise_ratio))))
              {
                ram->entry_event_cnt++;
                if(ram->entry_event_cnt > rom->entry_event_cnt)
                {
                  ram->entry_event_cnt = 0;
                  ram->deadband_cnt = rom->deadband_cnt;
                  
                  if(!_ft_electrode_get_flag(electrode, FT_ELECTRODE_LOCK_BASELINE_FLAG))
                    _ft_keydetector_safa_lock_baseline(electrode, rom, ram, signal);
                  
                  _ft_filter_moving_average_init(&ram->predicted_signal_avrg_init, 
                     &ram->predicted_signal_avrg,
                     _ft_filter_deadrange_u(signal, electrode->baseline, 
                                            (ram->noise * rom->signal_to_noise_ratio)));
                  _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_TOUCH);
                }
              }else
              {
                ram->entry_event_cnt = 0;
                
                if(_ft_electrode_get_flag(electrode, FT_ELECTRODE_LOCK_BASELINE_FLAG))
                {
                  if(ram->deadband_cnt)
                  {
                    ram->deadband_cnt--;
                    break;
                  }
                }
                else
                {
                  if(ram->recovery_cnt)
                  {
                      ram->recovery_cnt--;
                      if(ram->recovery_cnt == 0)
                      {
                        ram->base_avrg_init = rom->base_avrg;
                        _ft_filter_moving_average_init(&ram->base_avrg_init, 
                                 &ram->base_avrg,
                                 electrode->baseline);
                      }
                      break;
                  }
                }  

                ram->deadband_cnt = 0;
                ram->recovery_cnt = 0;
                  
                if(_ft_electrode_get_flag(electrode, FT_ELECTRODE_LOCK_BASELINE_REQ_FLAG))
                    _ft_keydetector_safa_lock_baseline(electrode, rom, ram, signal);
                
                if(_ft_electrode_get_flag(electrode, FT_ELECTRODE_LOCK_BASELINE_REQ_FLAG | FT_ELECTRODE_LOCK_BASELINE_FLAG) == FT_ELECTRODE_LOCK_BASELINE_FLAG)
                    _ft_keydetector_safa_unlock_baseline(electrode, rom, ram, signal);
                
              }
            break;
        default:
            break;
      }
}

static void _ft_keydetector_safa_lock_baseline(struct ft_electrode_data *electrode, const struct ft_keydetector_safa *rom, struct ft_keydetector_safa_data *ram, uint16_t signal)
{
  _ft_electrode_set_flag(electrode, FT_ELECTRODE_LOCK_BASELINE_FLAG);
                  
  ram->base_avrg_init = rom->non_activity_avrg;
  _ft_filter_moving_average_init(&ram->base_avrg_init, 
                               &ram->base_avrg,
                               electrode->baseline);
}

static void _ft_keydetector_safa_unlock_baseline(struct ft_electrode_data *electrode, const struct ft_keydetector_safa *rom, struct ft_keydetector_safa_data *ram, uint16_t signal)
{
  if(_ft_electrode_get_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG))
  {
      ram->recovery_cnt = rom->deadband_cnt * 8;
      ram->base_avrg_init.n2_order = rom->base_avrg.n2_order / 4;
      _ft_electrode_clear_flag(electrode, FT_ELECTRODE_AFTER_INIT_TOUCH_FLAG);
      
  }else
  {
      ram->recovery_cnt = rom->deadband_cnt * 2;
      ram->base_avrg_init.n2_order = rom->base_avrg.n2_order / 2;
  }
  
  
  _ft_filter_moving_average_init(&ram->base_avrg_init, 
                               &ram->base_avrg,
                               electrode->baseline);
    
                
  
  
  _ft_electrode_clear_flag(electrode, FT_ELECTRODE_LOCK_BASELINE_FLAG);
}

static void _ft_keydetector_safa_signal_track(struct ft_electrode_data *electrode, const struct ft_keydetector_safa *rom, struct ft_keydetector_safa_data *ram, uint16_t signal)
{
  if(ram->entry_event_cnt == 0)
  {
    electrode->baseline = _ft_filter_moving_average_process(&ram->base_avrg_init, 
                                           &ram->base_avrg,
                                           signal);
  }
  
  if(!_ft_electrode_get_flag(electrode, FT_ELECTRODE_LOCK_BASELINE_FLAG))
  {
    if(_ft_filter_abs(electrode->baseline - signal) < (ram->noise * rom->signal_to_noise_ratio))
    {
        ram->noise = _ft_filter_moving_average_process(&ram->noise_avrg_init, 
                                               &ram->noise_avrg,
                                               _ft_filter_limit_u(_ft_filter_abs(electrode->baseline - signal), rom->min_noise_limit, (rom->min_noise_limit * 4)));       
    }
  }
  
  if(_ft_electrode_get_last_status(electrode) != FT_ELECTRODE_STATE_TOUCH)
  {
	    uint16_t sig_filter = signal;
    
            sig_filter = _ft_filter_abs(signal - electrode->baseline);
	    if(sig_filter < (ram->noise * rom->signal_to_noise_ratio))
              sig_filter = ram->noise * rom->signal_to_noise_ratio;
            
            sig_filter += electrode->baseline;
            
            sig_filter = _ft_filter_limit_u(sig_filter, 0, 65535);    
            ram->predicted_signal = _ft_filter_moving_average_process(&rom->non_activity_avrg, 
	                                           &ram->predicted_signal_avrg,
	                                           sig_filter);
  }else
  {
    ram->predicted_signal = _ft_filter_deadrange_u(_ft_filter_moving_average_process(&ram->predicted_signal_avrg_init, 
                                               &ram->predicted_signal_avrg,
                                               signal), electrode->baseline, (ram->noise * rom->signal_to_noise_ratio));

  }
  
}
