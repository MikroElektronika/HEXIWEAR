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
#include "../source/filters/ft_filters_prv.h"

/* Extract 16 MSBs from 32bit fractional value. */
static int16_t _ft_get_msb_from_int32(int32_t lsrc);
/* Multiply 16 bit fractional value with 32bit fractional value. */
static int32_t _ft_multiply_int32_int16(int32_t lsrc1, int16_t ssrc1);
/* Multiply two 32bit fractional values. */
static int32_t _ft_multiply_int32(int32_t lsrc1, int32_t lsrc2);
/* Execute IIR filter on the signals */
static int32_t _ft_iir_iterate(int16_t x, int16_t *px,
                           int32_t *py, int32_t p1coef);
/* Calculates ceofficient in the runtime. */
static int32_t _ft_filter_fbutt_get_coef(int32_t fsample, int32_t fcutt);

/* filters using frac arithmetics */
#define _FT_FRAC32(x) ((int64_t) ((x)*(((x) > 0) ? 0x7fffffff : 0x80000000)))

static inline int16_t _ft_get_msb_from_int32(int32_t lsrc)
{
    return (int16_t)((int32_t)lsrc >> 16);
}

static int32_t _ft_multiply_int32_int16(int32_t lsrc1, int16_t ssrc1)
{
    return (int32_t)(((int64_t)lsrc1*(int64_t)ssrc1) >> 15);
}

static int32_t _ft_multiply_int32(int32_t lsrc1, int32_t lsrc2)
{
    return (int32_t)(((int64_t)lsrc1 * (int64_t)lsrc2) >> 31);
}

uint32_t _ft_abs_int32(int32_t lsrc)
{
  if(lsrc < 0)
    return lsrc * -1;
  else
    return lsrc;
}

static int32_t _ft_iir_iterate(int16_t x, int16_t *px,
                           int32_t *py, int32_t p1coef)
{
    int32_t sum_coef = p1coef + p1coef;
    uint32_t substr = sum_coef - _FT_FRAC32(1.00000000000000);
    uint32_t satur_x = _ft_multiply_int32_int16(p1coef, x);
    uint32_t multiply = _ft_multiply_int32_int16(p1coef, *px) + satur_x;
    uint32_t tmp = multiply - _ft_multiply_int32(*py, substr);
    *px = x;
    return *py = tmp;
}

static int32_t _ft_filter_fbutt_get_coef(int32_t fsample, int32_t fcutt)
{
    int32_t ratio = fsample / fcutt;
    if (ratio < 4) {
        ratio = 4;
    }
    /* calculate fbutt coef by approximation equation
       minimum error = 0.03%, average error = 8%) */
    return (int32_t)( (((uint32_t)1<<31)-1) / ratio) * 3;
}

void _ft_filter_fbutt_init(const struct ft_filter_fbutt *rom, 
                           struct ft_filter_fbutt_data *ram, uint32_t signal)
{
  ram->x = (int16_t)signal;
  ram->y = (int32_t)((int32_t)signal << 16); /* expands signal to the higher part */
  ram->coeficient = _ft_filter_fbutt_get_coef(1000 / _ft_system_get()->rom->time_period, rom->cutoff);    
}

uint16_t _ft_filter_fbutt_process(struct ft_filter_fbutt_data *ram,
                                 uint16_t signal)
{
    /* calculate fbutt coef by approximation function (not accurate!) */
    int32_t process_iir = _ft_iir_iterate((int16_t)signal, &ram->x, &ram->y, ram->coeficient);
    int32_t new_signal = (int32_t)_ft_get_msb_from_int32(process_iir);
    return (uint16_t)new_signal;
}

uint32_t _ft_filter_iir_process(const struct ft_filter_iir *rom,
                               uint32_t signal, uint32_t previous_signal)
{
    uint32_t coef = (uint32_t)rom->coef1;
    return ((signal + (coef * previous_signal)) / (coef + 1U));
}

int32_t _ft_filter_moving_average_init(const struct ft_filter_moving_average *rom,
                                        struct ft_filter_moving_average_data *ram,
                                        uint16_t value)
{
    if(rom->n2_order > FT_FILTER_MOVING_AVERAGE_MAX_ORDER)
        return -1;
    
    ram->sum = value << rom->n2_order;
    
    return 0;
}

uint32_t _ft_filter_moving_average_process(const struct ft_filter_moving_average *rom,
                                            struct ft_filter_moving_average_data *ram,
                                            uint16_t value)
{
    ram->sum -= (ram->sum >> rom->n2_order);
    ram->sum += value;
    return (ram->sum >> rom->n2_order);    
}

uint16_t _ft_filter_abs(int16_t value)
{
  if(value < 0)
    return value * -1;
  
  return value;
}

uint16_t _ft_filter_limit_u(int32_t value, uint16_t limit_l, uint16_t limit_h)
{
  if(value > limit_h)
    return limit_h;
  
  if(value < limit_l)
    return limit_l;
  
  return value;
}

uint16_t _ft_filter_deadrange_u(uint16_t value, uint16_t base, uint16_t range)
{
    if(_ft_filter_is_deadrange_u(value, base, range))
    {
      if(value > base)
        return _ft_filter_limit_u(base + range, 0, 0xffff);
      else
        return _ft_filter_limit_u(base - range, 0, 0xffff);
    }
  
    return value;
}

int32_t _ft_filter_is_deadrange_u(uint16_t value, uint16_t base, uint16_t range)
{
  if(value < (base + range))
  {
    if(value > (base - range))
    {
      return 1;
    }
  }
  return 0;
}
