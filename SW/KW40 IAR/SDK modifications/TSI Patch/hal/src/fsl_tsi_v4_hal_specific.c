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
#include "fsl_tsi_hal.h"
#include <assert.h>
#if FSL_FEATURE_SOC_TSI_COUNT

static int32_t TSI_HAL_MeasurementBlocking(TSI_Type * base, uint32_t electrode, uint32_t noise_mode);

uint32_t tsi_hal_gencs/*[TSI_INSTANCE_COUNT]*/;

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_EnableLowPower
* Description   : Function enables low power
*END**************************************************************************/
void TSI_HAL_EnableLowPower(TSI_Type * base)
{
    TSI_HAL_EnableStop(base);
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_EnableHwTrigger
* Description   : Function enables low power
*END**************************************************************************/
void TSI_HAL_EnableHwTrigger(TSI_Type * base)
{
    TSI_HAL_EnableHardwareTriggerScan(base);
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_Init
* Description   : Function inits the whole TSI peripheral
*
*END**************************************************************************/
void TSI_HAL_Init(TSI_Type * base)
{
    TSI_WR_GENCS(base, 0);
    tsi_hal_gencs = 0;
    TSI_WR_DATA(base, 0);
    TSI_WR_TSHD(base, 0);
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_SetConfiguration
* Description   : Function set the whole TSI peripheral by handled configuration
*
*END**************************************************************************/
void TSI_HAL_SetConfiguration(TSI_Type * base, tsi_config_t *config)
{
    assert(config != NULL);

    uint32_t is_enabled = TSI_HAL_IsModuleEnabled(base);
    uint32_t is_int_enabled = TSI_HAL_IsInterruptEnabled(base);
    
    if (is_enabled) {
        TSI_HAL_DisableModule(base);
    }
    if (is_int_enabled) {
        TSI_HAL_DisableInterrupt(base);
    }
    
    if(config->mode == kTsiAnalogModeSel_AutoNoise)
    {
     TSI_HAL_SetMode(base, config->mode); 
     TSI_HAL_SetPrescaler(base, config->ps);
     TSI_HAL_SetNumberOfScans(base, config->nscn);
     TSI_HAL_SetReferenceChargeCurrent(base, config->refchrg);
     TSI_HAL_SetOscilatorVoltageRails(base, config->dvolt);
     TSI_HAL_SetElectrodeSeriesResistor(base, config->serres);
     TSI_HAL_SetFilterBits(base, config->filter);
    }
    
    else
    {  
     TSI_HAL_SetPrescaler(base, config->ps);
     TSI_HAL_SetNumberOfScans(base, config->nscn);
     TSI_HAL_SetReferenceChargeCurrent(base, config->refchrg);
     TSI_HAL_SetElectrodeChargeCurrent(base, config->extchrg);
     TSI_HAL_SetMode(base, config->mode);
     TSI_HAL_SetOscilatorVoltageRails(base, config->dvolt);
     TSI_HAL_SetLowThreshold(base, config->thresl);
     TSI_HAL_SetHighThreshold(base, config->thresh);
    }
    
    if (is_enabled) {
        TSI_HAL_EnableModule(base);
    }
    if (is_int_enabled) {
        TSI_HAL_EnableInterrupt(base);
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_Recalibrate
* Description   : Function do recalibration process of TSI main parameters to
*                 find the gold cut on all enabled electrodes
*
*END**************************************************************************/
#define TSI_RECALIBRATE_MAX_SIGNAL_VAL (65535U)
uint32_t TSI_HAL_Recalibrate(TSI_Type * base, tsi_config_t *config, const uint32_t electrodes, const tsi_parameter_limits_t *parLimits)
{
    assert(config != NULL);

    uint32_t is_enabled = TSI_HAL_IsModuleEnabled(base);
    uint32_t is_int_enabled = TSI_HAL_IsInterruptEnabled(base);
    uint32_t lowest_signal = TSI_RECALIBRATE_MAX_SIGNAL_VAL;

    if(electrodes == 0)
    {
      return 0;
    }
    
    if (is_enabled) {
        TSI_HAL_DisableModule(base);
    }
    if (is_int_enabled) {
        TSI_HAL_DisableInterrupt(base);
    }
    
    if(parLimits == NULL) /* If NOISE mode calibration*/
    {
      /* parLimits are not used in NOISE mode so this is calibration of noise mode. */      
      TSI_HAL_SetConfiguration(base, config);
      
      lowest_signal = 1;      
      
    }else
    {
      // Normal capacitive mode calibration 
      TSI_HAL_SetNumberOfScans(base, config->nscn);
      TSI_HAL_SetPrescaler(base, config->ps);
      TSI_HAL_SetElectrodeChargeCurrent(base, config->extchrg);
      TSI_HAL_SetReferenceChargeCurrent(base, config->refchrg);

       TSI_HAL_EnableModule(base);

      for (uint32_t i = 0U; i < 16U; i++) 
          {
          if ((uint32_t)(1 << i) & electrodes) 
                  {
              int32_t counter = TSI_HAL_MeasurementBlocking(base, i, 0);
              if (counter < lowest_signal) {
                  lowest_signal = counter;
              }
          }
      }
    }
    
    if (!is_enabled) {
        TSI_HAL_EnableModule(base);
    }
    if (is_int_enabled) {
        TSI_HAL_EnableInterrupt(base);
    }
    if (lowest_signal == TSI_RECALIBRATE_MAX_SIGNAL_VAL) {
        lowest_signal = 0U;  /* not valid */
    }

    return lowest_signal;
}

/*FUNCTION**********************************************************************
*
* Function Name : TSI_HAL_MeasurementBlocking
* Description   : Function do blocking measurement of enabled electrodes
*                 It used just for recalibration process
*END**************************************************************************/
static int32_t TSI_HAL_MeasurementBlocking(TSI_Type * base, uint32_t electrode, uint32_t noise_mode)
{
    int32_t result;
    uint32_t timeout = 1000000;
    /* measure only if at least one electrode is enabled */
    TSI_HAL_EnableSoftwareTriggerScan(base);
    TSI_HAL_SetMeasuredChannelNumber(base, electrode);
    TSI_HAL_SetMode(base, TSI_HAL_GetMode(base)); /* force to HW right analog mode. */    
    TSI_HAL_EnableModule(base);
    TSI_HAL_StartSoftwareTrigger(base);
    
    while((TSI_HAL_GetEndOfScanFlag(base) == 0U) && (--timeout))
    {
      /* Do nothing, just to meet MISRA C 2004 rule 14.3 . */
    }
    
    if(timeout == 0)
    {
      result = 0;
    }else
    {
      if(noise_mode)
      {
        result = TSI_HAL_GetNoiseResult(base);
      }else
      {
        result = TSI_HAL_GetCounter(base);
      }
    }
    
    TSI_HAL_ClearEndOfScanFlag(base);
    TSI_HAL_DisableModule(base);
    
    return result;
}
#endif
