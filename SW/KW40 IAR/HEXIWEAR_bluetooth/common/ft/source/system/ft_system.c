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
#include "../source/modules/ft_modules_prv.h"
#include "../source/controls/ft_controls_prv.h"
#include "../include/ft_system.h"
#include "ft_types.h"

struct ft_kernel ft_kernel_data;

/* System data check */
static int32_t _ft_system_check_data(const struct ft_system *system);
/* Get the count of pointer array ended by NULL pointer. */
static uint32_t _ft_system_count_pointer_array(const void** pointer_array);

/* System data check */
static int32_t _ft_system_check_data(const struct ft_system *system)
{
  if (system->modules == NULL)
  {
    return FT_FAILURE;
  }
  if (system->controls == NULL)
  {
    return FT_FAILURE;
  }
  if (system->time_period == 0U)
  {
    return FT_FAILURE;
  }
  return FT_SUCCESS;
}

/* Get the count of pointer array terminated by NULL pointer. */
static uint32_t _ft_system_count_pointer_array(const void** pointer_array)
{
  void** array = (void**)pointer_array;
  uint32_t count = 0;

  if(array == NULL)
  {
    return 0;
  }

  while(*array++)
  {
    count++;
  }

  return count;
}


/* internal function */
int32_t _ft_system_init(const struct ft_system *system)
{
    FT_ASSERT(system != NULL);
    if (_ft_system_check_data(system) < FT_SUCCESS) {
        return FT_FAILURE;
    }

    ft_kernel_data.controls_cnt = (uint8_t)_ft_system_count_pointer_array((const void**)system->controls);
    ft_kernel_data.modules_cnt = (uint8_t)_ft_system_count_pointer_array((const void**)system->modules);

    ft_kernel_data.controls = _ft_mem_alloc(sizeof(void*) * ft_kernel_data.controls_cnt);

    if(ft_kernel_data.controls == NULL)
    {
      return FT_OUT_OF_MEMORY;
    }

    ft_kernel_data.modules = _ft_mem_alloc(sizeof(void*) * ft_kernel_data.modules_cnt);

    if(ft_kernel_data.modules == NULL)
    {
      return FT_OUT_OF_MEMORY;
    }

    ft_kernel_data.rom = system;
    ft_kernel_data.time_counter = 0U;
    return FT_SUCCESS;
}

/* private function */
struct ft_kernel *_ft_system_get(void)
{
    return &ft_kernel_data;
}

/* private function */
void _ft_system_increment_time_counter(void)
{
  ft_kernel_data.time_counter += ft_kernel_data.rom->time_period;
}

/* private function */
uint32_t _ft_system_get_time_period(void)
{
  return (uint32_t)ft_kernel_data.rom->time_period;
}

/* public function */
uint32_t ft_system_get_time_offset(uint32_t event_stamp)
{
    uint32_t time_counter = ft_system_get_time_counter();
    if (time_counter > event_stamp) {
        return (time_counter - event_stamp);
    } else {
        return (event_stamp - time_counter);
    }
}

/* private function */
uint32_t _ft_system_get_time_offset_from_period(uint32_t event_period)
{
    if (event_period) {
        uint32_t time_period = _ft_system_get_time_period();
        return (uint32_t)((ft_system_get_time_counter() / time_period) % event_period);
    } else {
        return 1U; /* returns positive number, event should not be triggered */
    }
}

/* public function */
uint32_t ft_system_get_time_counter(void)
{
    return ft_kernel_data.time_counter;
}

/* internal function */
int32_t _ft_system_module_function(uint32_t option)
{
    int32_t result = FT_SUCCESS;
    struct ft_module_data *module;
    uint32_t i;

    /* steps through all control pointers */
    for(i=0;i<ft_kernel_data.modules_cnt;i++)
    {
      module = ft_kernel_data.modules[i];
        switch (option)
        {
            case FT_SYSTEM_MODULE_INIT:
             ft_kernel_data.modules[i] = _ft_module_init(ft_kernel_data.rom->modules[i]);
             if (ft_kernel_data.modules[i] == NULL)
              {
                  return FT_OUT_OF_MEMORY; /* failure stops the entire init phase */
              }
              break;
            case FT_SYSTEM_MODULE_TRIGGER:
                if (_ft_module_trigger(module) == FT_SCAN_IN_PROGRESS)
                {
                    result = FT_FAILURE; /* module not ready, triggering continues */
                }
                break;
            case FT_SYSTEM_MODULE_PROCESS:
                _ft_module_process(module);
                break;
            case FT_SYSTEM_MODULE_CHECK_DATA:
                if (!_ft_module_get_flag(module, FT_MODULE_NEW_DATA_FLAG)) {
                    return FT_FAILURE; /* module has not processed all data yet */
                }
                break;
            default:
                break;
        }
        module++;
    }
    return result;
}

/* internal function */
int32_t _ft_system_control_function(uint32_t option)
{
    struct ft_control_data *control;
    int32_t result = FT_SUCCESS;
    uint32_t i;

    /* steps through all control pointers */
    for(i=0;i<ft_kernel_data.controls_cnt;i++)
    {
      control = ft_kernel_data.controls[i];

      switch (option) {
        case FT_SYSTEM_CONTROL_INIT:
          ft_kernel_data.controls[i] = _ft_control_init(ft_kernel_data.rom->controls[i]);
          if (ft_kernel_data.controls[i]== NULL) {
              return FT_OUT_OF_MEMORY; /* failure stops the entire init phase */
          }
          break;
        case FT_SYSTEM_CONTROL_OVERRUN:
          if (_ft_control_overrun(control) < FT_SUCCESS) {
              result = FT_FAILURE; /* overrun error, triger others anyway */
          }
          break;
        case FT_SYSTEM_CONTROL_PROCESS:
         {
            const struct ft_control_interface *interface = (const struct ft_control_interface *)
                                                       control->rom->interface;
            if(interface->process != NULL)
            {
              if (interface->process(control) < FT_SUCCESS)
              {
                result = FT_FAILURE; /* data not ready */
              }
            }
         }
          break;
        case FT_SYSTEM_CONTROL_DATA_READY:
          _ft_control_set_flag(control, FT_CONTROL_NEW_DATA_FLAG);
          break;
        default:
          break;
      }
    }
    return result;
}

void _ft_system_invoke_callback(uint32_t event)
{
  struct ft_kernel *system = _ft_system_get();

  if (system->callback == NULL)
  {
    return;
  }

  switch (event)
  {
    case FT_SYSTEM_EVENT_OVERRUN:
        system->callback(FT_SYSTEM_EVENT_OVERRUN);
        break;
    case FT_SYSTEM_EVENT_DATA_READY:
        system->callback(FT_SYSTEM_EVENT_DATA_READY);
        break;
    default:
        break;
  }
}

void ft_system_register_callback(ft_system_callback callback)
{
    ft_kernel_data.callback = callback;
}

void ft_error_register_callback(ft_error_callback callback)
{
  #if (FT_DEBUG != 0)  
    ft_kernel_data.error_callback = callback;
  #else
    (void)callback;
  #endif
}

void _ft_system_modules_data_ready(void)
{
    if (_ft_system_module_function(FT_SYSTEM_MODULE_CHECK_DATA) == FT_SUCCESS) {
        /* all modules have been processed, set data ready for all controls */
        _ft_system_control_function(FT_SYSTEM_CONTROL_DATA_READY);
        _ft_system_invoke_callback(FT_SYSTEM_EVENT_DATA_READY);
    }
}

const struct ft_module *_ft_system_get_module(uint32_t interface_address,
                                             uint32_t instance)
{
    const struct ft_module * const * module = ft_kernel_data.rom->modules;

    while (*module) {
        if ((uint32_t)((*module)->interface) == interface_address) {
            if (((*module)->instance) == instance) {
                return *module;
            }
        }
        module++;
    }

    return NULL;
}
