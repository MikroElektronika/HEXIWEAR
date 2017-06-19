/*`
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
#include "../source/modules/ft_module_tsi_prv.h"
#include "../source/electrodes/ft_electrodes_prv.h"
#include "ft_modules.h"
#include "ft_module_tsi.h"
#include "../source/filters/ft_filters_prv.h"
#include "../source/modules/ft_modules_prv.h"

#include "board.h"

/* Call back function of SDK TSI driver */
static void _ft_module_tsi_driver_callback(uint32_t instance, void* usrData);

/* Local functions */
static void _ft_module_tsi_measure(struct ft_module_data *module);
static int32_t _ft_module_tsi_init(struct ft_module_data *module);
static int32_t _ft_module_tsi_trigger(struct ft_module_data *module);
static int32_t _ft_module_tsi_process(struct ft_module_data *module);
static int32_t _ft_module_tsi_module_recalibrate(struct ft_module_data *module,
                                        void *configuration);
static int32_t _ft_module_tsi_electrode_enable(struct ft_module_data *module,
                                   uint32_t elec_index);
static int32_t _ft_module_tsi_electrode_disable(struct ft_module_data *module,
                                    uint32_t elec_index);
static int32_t _ft_module_tsi_change_mode(struct ft_module_data *module, 
                                         const enum ft_module_mode mode, 
                                         const struct ft_electrode * electrode);
/* Local functions for noise mode implementation */
static int32_t _ft_module_tsi_noise_rom_check(const struct ft_module_tsi_noise *rom);
static int32_t _ft_module_tsi_noise_init(struct ft_electrode_data *electrode);
static void _ft_module_tsi_noise_measure(struct ft_electrode_data *electrode, 
                                        uint32_t signal);
static int32_t _ft_module_tsi_noise_process(struct ft_electrode_data *electrode, 
                                           uint32_t maximum_noise);
static int32_t _ft_module_tsi_noise_get_max(struct ft_module_data *module);
                                            
static int32_t _ft_module_tsi_load_configuration(struct ft_module_data *module, const enum ft_module_mode mode, const void* config); /**<  Load the configuration for select mode. */
static int32_t _ft_module_tsi_save_configuration(struct ft_module_data *module, const enum ft_module_mode mode, void* config); /**<  Save the configuration of select mode. */

static int32_t _ft_get_tsi_mode(const enum ft_module_mode mode);
static int32_t _ft_update_electrodes_for_noise(struct ft_module_data *module);

/** interface tsi module */
const struct ft_module_interface ft_module_tsi_interface = {
  .init              = _ft_module_tsi_init,
  .trigger           = _ft_module_tsi_trigger,
  .process           = _ft_module_tsi_process,
  .recalibrate       = _ft_module_tsi_module_recalibrate,
  .electrode_enable  = _ft_module_tsi_electrode_enable,
  .electrode_disable = _ft_module_tsi_electrode_disable,
  .change_mode       = _ft_module_tsi_change_mode,
  .load_configuration = _ft_module_tsi_load_configuration,
  .save_configuration = _ft_module_tsi_save_configuration,
  .name              = "ft_module_tsi_interface",
};

/*******************************************************************************
*                       TSI MODULE functions
*******************************************************************************/
static int32_t _ft_module_tsi_init(struct ft_module_data *module)
{
  
  module->special_data.tsi = _ft_mem_alloc(sizeof(struct ft_module_tsi_data));
  
  if(module->special_data.tsi == NULL)
  {
    return FT_OUT_OF_MEMORY;
  }
  
  tsi_user_config_t tsi_config;

  //Create the TSI structure
  tsi_config.config = module->rom->config;
  tsi_config.pCallBackFunc = _ft_module_tsi_driver_callback;
  tsi_config.usrData = (void*)_ft_system_get();

  if(TSI_DRV_Init(module->rom->instance, &module->special_data.tsi->tsi_state, &tsi_config) != kStatus_TSI_Success)
  {
    return FT_FAILURE;
  }
  
  if(module->rom->module_params.tsi) /* noise mode parameters detected */
  {
    #if (FSL_FEATURE_TSI_VERSION == 4)
        tsi_operation_mode_t tsi_op_mode;
        //tsi_op_mode.config = (tsi_config_t *)(module->rom->module_params.tsi->config); 
    #endif
        
    if(_ft_module_tsi_noise_rom_check(&module->rom->module_params.tsi->noise) == FT_FAILURE)
    {
      return FT_FAILURE;
    }
    
    _ft_module_set_flag(module, FT_MODULE_HAS_NOISE_MODE_FLAG);
    
    for(uint32_t i=0; i<module->electrodes_cnt; i++)
    {
      struct ft_electrode_data *elec = module->electrodes[i];

      if(_ft_module_tsi_noise_init(elec) != FT_SUCCESS)
      {
         return FT_OUT_OF_MEMORY;
      } /* init noise keydetectors data */
    }
#if (FSL_FEATURE_TSI_VERSION == 4)
    
    // Load settings for the noise mode from noise setup    
    tsi_op_mode.config.ps = module->rom->module_params.tsi->config->ps; 
    tsi_op_mode.config.nscn = module->rom->module_params.tsi->config->nscn; 
    tsi_op_mode.config.refchrg = module->rom->module_params.tsi->config->refchrg;   
    tsi_op_mode.config.mode = module->rom->module_params.tsi->config->mode;   
    tsi_op_mode.config.dvolt = module->rom->module_params.tsi->config->dvolt;    
    tsi_op_mode.config.serres = module->rom->module_params.tsi->config->serres;   
    tsi_op_mode.config.filter = module->rom->module_params.tsi->config->filter; 
      
    
    if(TSI_DRV_LoadConfiguration(module->rom->instance, tsi_OpModeNoise, &tsi_op_mode) != kStatus_TSI_Success)
    {
      return FT_FAILURE;
    }
        
#endif
  }
  return FT_SUCCESS;
}

static int32_t _ft_module_tsi_trigger(struct ft_module_data *module)
{
  tsi_status_t result = kStatus_TSI_Success;
  
  // Handle noise mode if possible
  if(module->rom->module_params.tsi)
  {
    if(_ft_module_get_flag(module, FT_MODULE_HAS_NOISE_MODE_FLAG))
    {
      if((!_ft_module_get_flag(module, FT_MODULE_IN_NOISE_MODE_FLAG)) && ((!_ft_system_get_time_offset_from_period((module->rom->module_params.tsi->noise.update_rate) /_ft_system_get_time_period())) || (_ft_module_get_flag(module, FT_MODULE_NOISE_MODE_REQ_FLAG))))
      {
        /* when no touch on the module electrodes */
        if(!_ft_module_get_electrodes_state(module))
        { 
          // Switch to noise mode
          result = TSI_DRV_ChangeMode(module->rom->instance, tsi_OpModeNoise);
          
          if(result == kStatus_TSI_Success)
          {
            _ft_module_set_flag(module, FT_MODULE_IN_NOISE_MODE_FLAG);
            _ft_module_clear_flag(module, FT_MODULE_NOISE_MODE_REQ_FLAG);
          }
          else if(result == kStatus_TSI_InvalidMode)
          {
            _ft_module_clear_flag(module, FT_MODULE_HAS_NOISE_MODE_FLAG | FT_MODULE_NOISE_MODE_REQ_FLAG);
          }else
          {
            _ft_module_set_flag(module, FT_MODULE_NOISE_MODE_REQ_FLAG);
          }
        }
                
      }
      else
      {
        if ((_ft_module_get_flag(module, FT_MODULE_IN_NOISE_MODE_FLAG)) && (!_ft_module_get_flag(module, FT_MODULE_DIGITAL_RESULTS_FLAG)))
        {
          
          if( ft_system_get_time_offset(module->special_data.tsi->noise_timestamp) > module->rom->module_params.tsi->noise.noise_mode_timeout)
          {           
            // switch back to CAP (no noise result measured in the last process and timeout occured)
            result = TSI_DRV_ChangeMode(module->rom->instance, tsi_OpModeNormal);
			_ft_module_clear_flag(module, FT_MODULE_IN_NOISE_MODE_FLAG);
          }
        }
      }
    }
  }
  
  if(result == kStatus_TSI_Success)
  {
    result = TSI_DRV_Measure(module->rom->instance);
  }

  switch(result)
  {
    case kStatus_TSI_Success:
    return FT_SUCCESS;

    case kStatus_TSI_Busy:
    return FT_SCAN_IN_PROGRESS;

    default:
    return FT_FAILURE;
  }
}

static void _ft_module_tsi_measure(struct ft_module_data *module)
{
  uint32_t elec_counter = module->electrodes_cnt;
  while (elec_counter--) 
  {
    struct ft_electrode_data *elec = module->electrodes[elec_counter];
    uint32_t raw_signal = _ft_electrode_get_raw_signal(elec);
    
    if(_ft_module_get_flag(module, FT_MODULE_IN_NOISE_MODE_FLAG | FT_MODULE_HAS_NOISE_MODE_FLAG) == (FT_MODULE_IN_NOISE_MODE_FLAG | FT_MODULE_HAS_NOISE_MODE_FLAG)) 
    {
        _ft_module_tsi_noise_measure(elec, raw_signal);
    } else 
    {
        elec->rom->keydetector_interface->ft_keydetector_measure(elec, raw_signal);
    }
  }
}

static int32_t _ft_module_tsi_noise_get_max(struct ft_module_data *module)
{
  uint32_t maximum_noise = 0U;
  struct ft_electrode_data *elec;
  struct ft_module_tsi_noise_data *ram;

  uint32_t elec_counter = module->electrodes_cnt;

  while (elec_counter--) {
      elec = module->electrodes[elec_counter];
      ram = elec->special_data.tsi_noise;
      /* check electrode noise level */
      if (_ft_module_tsi_noise_process(elec, 0U) == FT_SUCCESS) 
      {
          if (maximum_noise < ram->noise) 
          {
              maximum_noise = ram->noise;
          }
      }
  }
  return maximum_noise;
}

static int32_t _ft_module_tsi_process(struct ft_module_data *module)
{
  uint32_t elec_counter;
  
  _ft_module_tsi_measure(module);
  uint32_t cap_process = 1U;

  if(_ft_module_get_flag(module, FT_MODULE_IN_NOISE_MODE_FLAG | FT_MODULE_HAS_NOISE_MODE_FLAG) == (FT_MODULE_IN_NOISE_MODE_FLAG | FT_MODULE_HAS_NOISE_MODE_FLAG)) 
  {
    /* process noise keydetector */
    uint32_t noise_result = _ft_module_tsi_noise_get_max(module);
    elec_counter = module->electrodes_cnt;
    
    if (noise_result > 0U) 
    {
      /* store noise timestamp */
      module->special_data.tsi->noise_timestamp = ft_system_get_time_counter(); 
      while (elec_counter--) 
      {
        struct ft_electrode_data *elec = module->electrodes[elec_counter];
        /* evaluate touch/release */
        (void)_ft_module_tsi_noise_process(elec, noise_result);
        
        _ft_electrode_set_flag(elec, FT_ELECTRODE_DIGITAL_RESULT_ONLY_FLAG);
      }
      _ft_module_set_flag(module, FT_MODULE_DIGITAL_RESULTS_FLAG);
      
      cap_process = 0U;
    }
  }

  if (cap_process) 
  {
      _ft_module_clear_flag(module, FT_MODULE_DIGITAL_RESULTS_FLAG);
      elec_counter = module->electrodes_cnt;
      
      while (elec_counter--) 
      {
          struct ft_electrode_data *elec = module->electrodes[elec_counter];
          elec->rom->keydetector_interface->ft_keydetector_process(elec);
          _ft_electrode_clear_flag(elec, FT_ELECTRODE_DIGITAL_RESULT_ONLY_FLAG);
      }
  }
  return FT_SUCCESS;
}

static int32_t _ft_module_tsi_module_recalibrate(struct ft_module_data *module,
                                        void *configuration)
{
  uint32_t lowest_signal = 0;
  tsi_modes_t curr_mode;
  tsi_status_t result = kStatus_TSI_Success;
  const tsi_modes_t tsi_opModes[] = {tsi_OpModeNormal, tsi_OpModeProximity, tsi_OpModeLowPower, tsi_OpModeNoise};
  uint32_t mode;
  
  /* Save the current operational mode */
  curr_mode = TSI_DRV_GetMode(module->rom->instance);
  
  for(mode = 0; mode < sizeof(tsi_opModes); mode++)
  {
    /* Change modes*/
    if((result = TSI_DRV_ChangeMode(module->rom->instance, tsi_opModes[mode])) == kStatus_TSI_Success)
    {
      /* recalibrate */
      result = TSI_DRV_Recalibrate(module->rom->instance, &lowest_signal);
    } 
    if(result != kStatus_TSI_Success)
    {
      /* skip to end if failed*/
      break;  
    }
  }
  
  /* Return back to the original mode */
  result = TSI_DRV_ChangeMode(module->rom->instance, curr_mode);
  return result;
}

static int32_t _ft_module_tsi_electrode_enable(struct ft_module_data *module,
                            const uint32_t elec_index)
{
  if(TSI_DRV_EnableElectrode(module->rom->instance, elec_index, true) != kStatus_TSI_Success)
  {
    return FT_FAILURE;
  }
  
  if(module->rom->module_params.tsi)
  {
    if(_ft_update_electrodes_for_noise(module) != FT_SUCCESS)
    {
      return FT_FAILURE;
    }
  }

  return FT_SUCCESS;
}

static int32_t _ft_module_tsi_electrode_disable(struct ft_module_data *module,
                             const uint32_t elec_index)
{
  if(TSI_DRV_EnableElectrode(module->rom->instance, elec_index, false) != kStatus_TSI_Success)
  {
    return FT_FAILURE;
  }
  
  if(module->rom->module_params.tsi)
  {
    if(_ft_update_electrodes_for_noise(module) != FT_SUCCESS)
    {
      return FT_FAILURE;
    }
  }

  return FT_SUCCESS;
}

static int32_t _ft_update_electrodes_for_noise(struct ft_module_data *module)
{
  tsi_operation_mode_t tsi_op_mode;
  tsi_operation_mode_t tsi_op_mode_2;

  tsi_modes_t mode = TSI_DRV_GetMode(module->rom->instance);
  tsi_modes_t mode_2 = (mode == tsi_OpModeNoise)? tsi_OpModeNormal : tsi_OpModeNoise;

  // Duplicate settings for the noise mode from normal setup
  if(TSI_DRV_SaveConfiguration(module->rom->instance, mode, &tsi_op_mode) != kStatus_TSI_Success)
  {
    return FT_FAILURE;
  }

  if(TSI_DRV_SaveConfiguration(module->rom->instance, mode_2, &tsi_op_mode_2) != kStatus_TSI_Success)
  {
    return FT_FAILURE;
  }

  tsi_op_mode_2.enabledElectrodes = tsi_op_mode.enabledElectrodes;

  if(TSI_DRV_LoadConfiguration(module->rom->instance, mode_2, &tsi_op_mode_2) != kStatus_TSI_Success)
  {
    return FT_FAILURE;
  }
  
  return FT_SUCCESS;  
}

static int32_t _ft_get_tsi_mode(const enum ft_module_mode mode)
{
  struct modes_cross_table
  {
    enum ft_module_mode ft_modes;
    tsi_modes_t         sdk_tsi_modes;
  };

  const struct modes_cross_table modes_table[3] =
  {
    { FT_MODULE_MODE_NORMAL, tsi_OpModeNormal},
    { FT_MODULE_MODE_PROXIMITY, tsi_OpModeProximity},
    { FT_MODULE_MODE_LOW_POWER, tsi_OpModeLowPower},
  };
  
  for(int32_t mode_ix = 0; mode_ix < 3; mode_ix++)
  {
    if(modes_table[mode_ix].ft_modes == mode)
    {
      return modes_table[mode_ix].sdk_tsi_modes;
    }
  }
  
  return FT_FAILURE;
}

static int32_t _ft_module_tsi_change_mode(struct ft_module_data *module, const enum ft_module_mode mode, const struct ft_electrode * electrode)
{
  FT_ASSERT(module != NULL);
  FT_ASSERT(electrode != NULL);

  int32_t tsi_mode = _ft_get_tsi_mode(mode);

  if(tsi_mode == FT_FAILURE)
  {
    return FT_FAILURE;
  }

  if(TSI_DRV_GetMode(module->rom->instance) == tsi_OpModeLowPower)
  {
    // Disable the low power mode and switch back driver to normal mode
    if(TSI_DRV_DisableLowPower(module->rom->instance, tsi_OpModeNoChange) != kStatus_TSI_Success)
    {
      return FT_FAILURE;
    }
  }

    //Change mode of TSI driver
  if(TSI_DRV_ChangeMode(module->rom->instance, (tsi_modes_t)tsi_mode) != kStatus_TSI_Success)
  {
    return FT_FAILURE;
  }

  if((tsi_mode == tsi_OpModeLowPower) || (tsi_mode == tsi_OpModeProximity))
  {
    // Enable the right electrode for Low Power and Proximity
    if(TSI_DRV_EnableElectrode(module->rom->instance, electrode->pin_input, true) != kStatus_TSI_Success)
    {
      return FT_FAILURE;
    }
  }

  // It should be in separate API to allow setup/recalibrate/manage low power
  if(tsi_mode == tsi_OpModeLowPower)
  {
    // Enable the low power functionality
    if(TSI_DRV_EnableLowPower(module->rom->instance) != kStatus_TSI_Success)
    {
      return FT_FAILURE;
    }
  }

  return FT_SUCCESS;
}

static int32_t _ft_module_tsi_load_configuration(struct ft_module_data *module, const enum ft_module_mode mode, const void* config)
{
  FT_ASSERT(module != NULL);
  FT_ASSERT(config != NULL);
  
  int32_t tsi_mode = _ft_get_tsi_mode(mode);

  if(tsi_mode == FT_FAILURE)
  {
    return FT_FAILURE;
  }
  
  tsi_operation_mode_t tsi_op_mode;
  
  tsi_op_mode.enabledElectrodes = TSI_DRV_GetEnabledElectrodes(module->rom->instance);
  tsi_op_mode.config = *((tsi_config_t*)config);

  if(TSI_DRV_LoadConfiguration(module->rom->instance, (tsi_modes_t)tsi_mode, &tsi_op_mode) != kStatus_TSI_Success)
  {
    return FT_FAILURE;
  }
  
  return FT_SUCCESS;
}

static int32_t _ft_module_tsi_save_configuration(struct ft_module_data *module, const enum ft_module_mode mode, void* config)
{
  FT_ASSERT(module != NULL);
  FT_ASSERT(config != NULL);
  
  int32_t tsi_mode = _ft_get_tsi_mode(mode);

  if(tsi_mode == FT_FAILURE)
  {
    return FT_FAILURE;
  }
  
  tsi_operation_mode_t tsi_op_mode;
  
  if(TSI_DRV_SaveConfiguration(module->rom->instance, (tsi_modes_t)tsi_mode, &tsi_op_mode) != kStatus_TSI_Success)
  {
    return FT_FAILURE;
  }
  
  *((tsi_config_t*)config) = tsi_op_mode.config;
  
  return FT_SUCCESS;
}

/*******************************************************************************
*                       TSI MODULE NOISE mode functions
*******************************************************************************/
static int32_t _ft_module_tsi_noise_rom_check(const struct ft_module_tsi_noise *rom)
{
    if (rom->noise_filter.coef1 == 0) {
        return FT_FAILURE;
    }
    if (rom->update_rate == 0) {
        return FT_FAILURE;
    }

    return FT_SUCCESS;
}

static int32_t _ft_module_tsi_noise_init(struct ft_electrode_data *electrode)
{
  FT_ASSERT(electrode != NULL);

  struct ft_module_tsi_noise_data *ram = (struct ft_module_tsi_noise_data *)
                        _ft_mem_alloc(sizeof(struct ft_module_tsi_noise_data));

  if(ram == NULL)
  {
      return FT_OUT_OF_MEMORY;
  }

  electrode->special_data.tsi_noise = ram;

  ram->touch_threshold = FT_TSI_NOISE_INITIAL_TOUCH_THRESHOLD;
  ram->filter_state = FT_FILTER_STATE_INIT;

  return FT_SUCCESS;
}

static void _ft_module_tsi_noise_measure(struct ft_electrode_data *electrode,
                             uint32_t signal)
{
  FT_ASSERT(electrode != NULL);
  struct ft_module_tsi_noise_data *ram = electrode->special_data.tsi_noise;
  FT_ASSERT(ram != NULL);
  const struct ft_module_tsi_noise *rom = &electrode->module_data->rom->module_params.tsi->noise;
  FT_ASSERT(rom != NULL);

  if (ram->filter_state == FT_FILTER_STATE_INIT)
  {
    ram->noise = (uint8_t)signal;
    ram->filter_state = FT_FILTER_STATE_RUN;
  } else 
  {
    
    ram->noise = (uint8_t)_ft_filter_iir_process(&rom->noise_filter, signal,
                                                ram->noise);  
  }
}


static int32_t _ft_module_tsi_noise_process(struct ft_electrode_data *electrode, uint32_t maximum_noise)
{
  FT_ASSERT(electrode != NULL);
  struct ft_module_tsi_noise_data *ram = electrode->special_data.tsi_noise;
  FT_ASSERT(ram != NULL);

  int32_t result = FT_FAILURE;
  
  
  if (maximum_noise == 0u)
  {
    if (_ft_electrode_get_last_status(electrode) == FT_ELECTRODE_STATE_INIT) {
      // noise touch threshold calibration (find maximum) 
      if (ram->touch_threshold < ram->noise)
      {
        ram->touch_threshold = ram->noise;
      }
    } else
    {
      // check if noise is presented 
      if (ram->noise > ram->touch_threshold)
      {
        result = FT_SUCCESS;
      }
    }
  } 
  else // max_noise 
  {
    
    // evaluate touch/release 
    if (maximum_noise <= FT_TSI_NOISE_INITIAL_TOUCH_THRESHOLD)
    {
      maximum_noise = FT_TSI_NOISE_INITIAL_TOUCH_THRESHOLD + 1u;
    }
    
    if (maximum_noise > FT_TSI_NOISE_TOUCH_RANGE)
    {
      maximum_noise = FT_TSI_NOISE_TOUCH_RANGE;           
    }
      
    switch (_ft_electrode_get_last_status(electrode)) {
      case FT_ELECTRODE_STATE_TOUCH:
        if (ram->noise < FT_TSI_NOISE_INITIAL_TOUCH_THRESHOLD)
        {
          _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_RELEASE);
        }
        break;
      case FT_ELECTRODE_STATE_RELEASE:
        if (ram->noise >= FT_TSI_NOISE_INITIAL_TOUCH_THRESHOLD)
        {
          _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_TOUCH);
        }
        break;
      default:
        break;
    }
    result = FT_SUCCESS;
  }
  return result;
}


/*
static int32_t _ft_module_tsi_noise_process(struct ft_electrode_data *electrode, uint32_t maximum_noise)
{
   
  FT_ASSERT(electrode != NULL);
  struct ft_module_tsi_noise_data *ram = electrode->special_data.tsi_noise;
  FT_ASSERT(ram != NULL);

  int32_t result = FT_FAILURE;
  
  switch (_ft_electrode_get_last_status(electrode)) {
      case FT_ELECTRODE_STATE_TOUCH:
        if (ram->noise < FT_TSI_NOISE_INITIAL_TOUCH_THRESHOLD)
        {
          _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_RELEASE);
        }
        break;
      case FT_ELECTRODE_STATE_RELEASE:
        if (ram->noise >= FT_TSI_NOISE_INITIAL_TOUCH_THRESHOLD)
        {
          _ft_electrode_set_status(electrode, FT_ELECTRODE_STATE_TOUCH);
        }
        break;
      default:
        break;
    }
    result = FT_SUCCESS;  
}
*/

static void _ft_module_tsi_driver_callback(uint32_t instance, void* usrData)
{
  struct ft_module_data *module = _ft_module_get_data(_ft_system_get_module((uint32_t)&ft_module_tsi_interface, instance));
  struct ft_electrode_data *elec;
  const uint32_t enabled_electrodes = TSI_DRV_GetEnabledElectrodes(instance);
  uint32_t elec_size  = module->electrodes_cnt;

  while (elec_size--)
  {
    elec = module->electrodes[elec_size];

    if(enabled_electrodes & (1<<(elec->rom->pin_input)))
    {
      uint16_t data;
      TSI_DRV_GetCounter(instance, elec->rom->pin_input, &data);
      _ft_electrode_set_raw_signal(elec, data);
    }
  }
  _ft_module_set_flag(module, FT_MODULE_NEW_DATA_FLAG);
  _ft_system_modules_data_ready();
}
