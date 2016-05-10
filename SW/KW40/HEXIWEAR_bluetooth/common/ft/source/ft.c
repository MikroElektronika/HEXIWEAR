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
#include "../source/system/ft_system_frmstr_prv.h"
#include "../source/controls/ft_controls_prv.h"
#include "ft.h"

int32_t ft_init(const struct ft_system *system, uint8_t *pool, const uint32_t size)
{
  FT_ASSERT(system != NULL);
  
  int32_t result = FT_SUCCESS;

  if (_ft_mem_init(pool, size) < FT_SUCCESS)
  {
    return FT_FAILURE;
  }  
  if (_ft_freemaster_init() < FT_SUCCESS)
  {
    return FT_FAILURE;
  }  
  if ((result = _ft_system_init(system)) < FT_SUCCESS)
  {
    return result;
  }
  if ((result = _ft_system_module_function(FT_SYSTEM_MODULE_INIT)) < FT_SUCCESS)
  {
    return result;
  }
  if ((result = _ft_system_control_function(FT_SYSTEM_CONTROL_INIT)) < FT_SUCCESS)
  {
    return result;
  }
  return result;
}

int32_t ft_trigger(void)
{
    int32_t result = FT_SUCCESS;

    _ft_system_increment_time_counter();
    if (_ft_system_module_function(FT_SYSTEM_MODULE_TRIGGER) < FT_SUCCESS) {
        result = FT_FAILURE;
    }
    if (_ft_system_control_function(FT_SYSTEM_CONTROL_OVERRUN) < FT_SUCCESS) {
        result = FT_FAILURE;
    }
    if (result == FT_FAILURE) {
        /* triggering is faster than measurement/processing */
        _ft_system_invoke_callback(FT_SYSTEM_EVENT_OVERRUN);
    }

    return result;
}

int32_t ft_task(void)
{
    int32_t ret;
  
		ret = _ft_system_module_function(FT_SYSTEM_MODULE_PROCESS);
    if (ret < FT_SUCCESS) {
        return ret;
    }
		ret = _ft_system_control_function(FT_SYSTEM_CONTROL_PROCESS);
    if (ret < FT_SUCCESS) {
        return ret;
    }
    return FT_SUCCESS;
}

void ft_error(char *file, uint32_t line)
{
  /* User's error handling */
  #if (FT_DEBUG != 0) 
  if(_ft_system_get()->error_callback)
  {
    _ft_system_get()->error_callback(file, line);
  }
  #endif
  while (1);
}
