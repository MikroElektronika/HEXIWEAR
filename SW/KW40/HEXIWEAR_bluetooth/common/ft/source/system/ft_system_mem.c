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
#include "../source/system/ft_system_prv.h"
#include "../source/system/ft_system_mem_prv.h"

int32_t _ft_mem_init(uint8_t *pool, const uint32_t size)
{
  uint32_t  *data_pointer;
  uint32_t  counter;
  struct ft_kernel * system = _ft_system_get();

  if(pool == NULL)
  {
    return FT_FAILURE;
  }

  // Is the buffer start address aligned?
  if(((uint32_t)pool) & 0x03)
  {
    return FT_FAILURE;
  }

  if(system->memory.pool != NULL)
  {
    return FT_FAILURE;
  }

  system->memory.pool = pool;
  system->memory.pool_size = (size & 0xfffffffc); // Just only 4 byte aligned area is interesting
  system->memory.free_pointer = pool;

  data_pointer = (uint32_t*)system->memory.pool;
  counter = system->memory.pool_size / 4;

  while(counter--)
  {
     *data_pointer = 0;
     data_pointer++;
  }

  return FT_SUCCESS;
}

void* _ft_mem_alloc(const uint32_t size)
{
  uint32_t  free_size;
  uint8_t   *memory_block;
  uint32_t  pool_size = size;
  struct ft_kernel * system = _ft_system_get();

  if(system->memory.pool == NULL)
  {
    return NULL;
  }

  if(size == 0)
  {
    return NULL;
  }

  // compute free size
  free_size = system->memory.pool_size - ((uint32_t)system->memory.free_pointer - (uint32_t)system->memory.pool);

  if(pool_size > free_size)
  {
    return NULL;
  }

  memory_block = system->memory.free_pointer;

  pool_size--;
  pool_size |= 0x03; // Get full aligned block to 4 bytes
  pool_size++;

  system->memory.free_pointer += pool_size;

  return memory_block;
}

uint32_t ft_mem_get_free_size(void)
{
  struct ft_kernel * system = _ft_system_get();
  struct ft_mem * mem = &system->memory;
  
  int32_t size = mem->pool_size;
  
  size -= mem->free_pointer - mem->pool;
  
  FT_ASSERT(size >= 0);
  
  return size;
}

int32_t _ft_mem_deinit(void)
{
  struct ft_kernel * system = _ft_system_get();

  system->memory.pool = NULL;
  system->memory.pool_size = 0;
  system->memory.free_pointer = NULL;

  return FT_SUCCESS;
}
