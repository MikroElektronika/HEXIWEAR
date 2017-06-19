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
 
#include "ft_setup.h"
#include "board.h"
#include "fsl_tsi_driver.h"

/* USER DEFINED */

/*
 * Key Detectors 
 * The same Keydetectors AFID / SAFA can be used for all electrodes 
 * Or different keydetectors may be used for different electrodes for testing
 */

#define TSI_CHANNEL_0              (0)
#define TSI_CHANNEL_1              (1)
#define TSI_CHANNEL_4              (4)
#define TSI_CHANNEL_5              (5)
#define TSI_CHANNEL_6              (6)
#define TSI_CHANNEL_7              (7)
#define TSI_CHANNEL_12             (12)
#define TSI_CHANNEL_10             (10)
     
/* SAFA keydetector settings */
const struct ft_keydetector_safa keydec_safa = 
{
    .signal_filter = 4,
    .base_avrg = {.n2_order = 12},
    .non_activity_avrg =  {.n2_order = 14},
    .entry_event_cnt = 2,
    .signal_to_noise_ratio = 7,
    .deadband_cnt = 2,
    .min_noise_limit = 11,
};

/* Electrodes */
/* Different SAFA / AFID Keydecs used to evaluate the performance */
const struct ft_electrode electrode_rightUp =
{
    .pin_input = TSI_CHANNEL_0,
    .keydetector_interface = &ft_keydetector_safa_interface,
    .keydetector_params.safa = &keydec_safa,
};

const struct ft_electrode electrode_rightDown =
{
    .pin_input = TSI_CHANNEL_1,
    .keydetector_interface = &ft_keydetector_safa_interface,
    .keydetector_params.safa = &keydec_safa,
};

const struct ft_electrode electrode_leftUp =
{
    .pin_input = TSI_CHANNEL_7,
    .keydetector_interface = &ft_keydetector_safa_interface,
    .keydetector_params.safa = &keydec_safa,
};

const struct ft_electrode electrode_leftDown =
{
    .pin_input = TSI_CHANNEL_6,
    .keydetector_interface = &ft_keydetector_safa_interface,
    .keydetector_params.safa = &keydec_safa,
};

const struct ft_electrode electrode_left =
{
    .pin_input = TSI_CHANNEL_5,
    .keydetector_interface = &ft_keydetector_safa_interface, /* AFID used for test*/
    .keydetector_params.safa = &keydec_safa,
};

const struct ft_electrode electrode_right =
{
    .pin_input = TSI_CHANNEL_4,
    .keydetector_interface = &ft_keydetector_safa_interface,
    .keydetector_params.safa = &keydec_safa,
};

/* Modules */
const struct ft_electrode * const module_0_electrodes[] = 
{
    &electrode_leftUp, 
    &electrode_leftDown,
    
    &electrode_rightUp, 
    &electrode_rightDown,
    
    &electrode_left, 
    &electrode_right, 
    NULL
};

const tsi_config_t hw_config =
{
  .ps = kTsiElecOscPrescaler_64div,          /*!< Prescaler */
  .extchrg = kTsiExtOscChargeCurrent_32uA,    /*!< Electrode charge current */
  .refchrg = kTsiRefOscChargeCurrent_32uA,   /*!< Reference charge current */
  .nscn = kTsiConsecutiveScansNumber_24time, /*!< Number of scans. */
  .mode = kTsiAnalogModeSel_Capacitive,
  .dvolt = kTsiOscVolRails_Dv_103,
  .thresh = 100,                               /*!< High threshold. */
  .thresl = 200,                               /*!< Low threshold. */
};

const struct ft_module tsi_module =
{
    .interface = &ft_module_tsi_interface,
    .electrodes = &module_0_electrodes[0],
    .config = (void*)&hw_config,
    .instance = 0,

};

/* Controls */
const struct ft_electrode  * const control_0_electrodes[] = 
{
    &electrode_leftUp, 
    &electrode_leftDown,
    
    &electrode_rightUp, 
    &electrode_rightDown,
    
    &electrode_left, 
    &electrode_right, 
    NULL
};

const struct ft_control_keypad keypad_params =
{
   .groups = NULL,
   .groups_size = 0,
};

const struct ft_control keypad_0 =
{
  .interface = &ft_control_keypad_interface,
  .electrodes = control_0_electrodes,
  .control_params.keypad = &keypad_params,
};

/* System */
const struct ft_control * const controls[] = {&keypad_0, NULL};
const struct ft_module * const modules[] = {&tsi_module, NULL};


const struct ft_system system_0 = {
    .controls = &controls[0],
    .modules = &modules[0],
    .time_period = 5,
    .init_time = 400,
};
