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
#include "ft_control_slider.h"
#include "ft_control_slider_prv.h"
#include "ft_controls.h"
#include "../source/controls/ft_controls_prv.h"

/* Invokes a callback depending on the event */
static void _ft_control_slider_invoke_callback(const struct ft_control_data *control,
                                               enum ft_control_slider_event event,
                                               uint32_t position);
/* Invokes a callback depending on the event */
static void _ft_control_slider_calc_dynamic(struct ft_control_data *control,
                                   uint32_t position);
/* Calculates position */
static void _ft_control_slider_calc_position(struct ft_control_data *control,
                                    uint32_t first_elec, uint32_t last_elec,
                                    uint32_t touch_count);
/* The Slider control initialization function. */
static int32_t _ft_control_slider_init(struct ft_control_data *control);
/* The Slider control process function. */
static int32_t _ft_control_slider_process(struct ft_control_data *control);

/* The Slider control interface. */
const struct ft_control_interface ft_control_slider_interface = {
  .init    = _ft_control_slider_init,
  .process = _ft_control_slider_process,
  .name    = "ft_control_slider_interface",
};


void ft_control_slider_register_callback(const struct ft_control *control,
                                          ft_control_slider_callback callback)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_slider_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  struct ft_control_slider_data *ram = control_data->data.slider;
  FT_ASSERT(ram != NULL);

  ram->callback = callback;
}

uint32_t ft_control_slider_get_position(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_slider_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  struct ft_control_slider_data *ram = control_data->data.slider;
  FT_ASSERT(ram != NULL);

  return (uint32_t)ram->position;
}

uint32_t ft_control_slider_is_touched(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_slider_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  uint32_t flag = _ft_control_get_flag(control_data, FT_SLIDER_TOUCH_FLAG);
  return flag ? 1U : 0U;
}

uint32_t ft_control_slider_movement_detected(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_slider_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  uint32_t flag = _ft_control_get_flag(control_data, FT_SLIDER_MOVEMENT_FLAG);
  return flag ? 1U : 0U;
}

uint32_t ft_control_slider_get_direction(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_slider_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  uint32_t flag = _ft_control_get_flag(control_data, FT_SLIDER_DIRECTION_FLAG);
  return flag ? 1U : 0U;
}

uint32_t ft_control_slider_get_invalid_position(const struct ft_control *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->interface == &ft_control_slider_interface);

  struct ft_control_data *control_data = _ft_control_get_data(control);
  FT_ASSERT(control_data != NULL);

  uint32_t flag = _ft_control_get_flag(control_data, FT_SLIDER_INVALID_POSITION_FLAG);
  return flag ? 1U : 0U;
}

static void _ft_control_slider_invoke_callback(const struct ft_control_data *control,
                                      enum ft_control_slider_event event, 
                                      uint32_t position)
{
  struct ft_control_slider_data *ram = control->data.slider;
  FT_ASSERT(ram != NULL);

  if (ram->callback != NULL) 
  {
    ram->callback(control->rom, event, position);
  }
}

static void _ft_control_slider_calc_dynamic(struct ft_control_data *control,
                                   uint32_t position)
{
  struct ft_control_slider_data *ram = control->data.slider;
  FT_ASSERT(ram != NULL);

  if (position != ram->position)
  {
    if (position > ram->position)
    {
      _ft_control_set_flag(control, FT_SLIDER_DIRECTION_FLAG);
    } else
    {
      _ft_control_clear_flag(control, FT_SLIDER_DIRECTION_FLAG);
    }
    ram->position =  position;
    _ft_control_set_flag(control, FT_SLIDER_MOVEMENT_FLAG);
    _ft_control_slider_invoke_callback(control, FT_SLIDER_MOVEMENT, position);
  } else {
    _ft_control_clear_flag(control, FT_SLIDER_MOVEMENT_FLAG);
  }
}

static void _ft_control_slider_calc_position(struct ft_control_data *control,
                                    uint32_t first_elec, uint32_t last_elec,
                                    uint32_t touch_count)
{

  if (((last_elec - first_elec) == touch_count) && (touch_count <= 2))
  {
    /* valid position */
    _ft_control_clear_flag(control, FT_SLIDER_INVALID_POSITION_FLAG);
    uint32_t position = ((first_elec << 1U) + touch_count) - 1U;
    _ft_control_slider_calc_dynamic(control, position);
  } else
  {
    _ft_control_set_flag(control, FT_SLIDER_INVALID_POSITION_FLAG);
  }
}


static int32_t _ft_control_slider_init(struct ft_control_data *control)
{
  FT_ASSERT(control != NULL);
  FT_ASSERT(control->rom->interface == &ft_control_slider_interface);

  control->data.slider = _ft_mem_alloc(sizeof(struct ft_control_slider_data));

  if(control->data.slider == NULL)
  {
    return FT_OUT_OF_MEMORY;
  }

  if (_ft_control_check_data(control) != FT_SUCCESS)
  {
    return FT_FAILURE;
  }

  return FT_SUCCESS;
}

static int32_t _ft_control_slider_process(struct ft_control_data *control)
{
    FT_ASSERT(control != NULL);
    FT_ASSERT(control->rom->interface == &ft_control_slider_interface);

    if (!_ft_control_get_flag(control, FT_CONTROL_EN_FLAG) ||
        !_ft_control_get_flag(control, FT_CONTROL_NEW_DATA_FLAG)) {
        return FT_FAILURE; /* control disabled or data not ready */
    }

    struct ft_control_slider_data *ram = control->data.slider;
    uint32_t elec_state = _ft_control_get_electrodes_state(control);
    if (!elec_state) {
        /* all released */
        if (_ft_control_get_flag(control, FT_SLIDER_TOUCH_FLAG)) {
            /* if none is touched & touch was reported, allreleased event */
            _ft_control_clear_flag(control, FT_SLIDER_TOUCH_FLAG);
            _ft_control_clear_flag(control, FT_SLIDER_MOVEMENT_FLAG);
            _ft_control_slider_invoke_callback(control, FT_SLIDER_ALL_RELEASE,
                                      (uint32_t)ram->position);
        }
        _ft_control_clear_flag(control, FT_CONTROL_NEW_DATA_FLAG); /* data processed */
        return FT_SUCCESS; /* no touch on the control's electrodes */
    }

    uint32_t last_elec = _ft_control_get_last_elec_touched(elec_state);
    uint32_t first_elec = _ft_control_get_first_elec_touched(elec_state);
    uint32_t touch_count = _ft_control_get_touch_count(elec_state);
    _ft_control_slider_calc_position(control, first_elec, last_elec, touch_count);

    if (!_ft_control_get_flag(control, FT_SLIDER_TOUCH_FLAG)) {
        _ft_control_slider_invoke_callback(control, FT_SLIDER_INITIAL_TOUCH,
                                   (uint32_t)ram->position);
    }
    _ft_control_set_flag(control, FT_SLIDER_TOUCH_FLAG);

    _ft_control_clear_flag(control, FT_CONTROL_NEW_DATA_FLAG); /* data processed */
    return FT_SUCCESS;
}
