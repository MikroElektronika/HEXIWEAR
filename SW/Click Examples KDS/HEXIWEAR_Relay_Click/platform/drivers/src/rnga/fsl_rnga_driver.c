/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#include "fsl_rnga_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_RNG_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION*********************************************************************
 *
 * Function Name: RNGA_DRV_Init
 * Description: This function is used to initialize the RNGA
 *
 *END*************************************************************************/
rnga_status_t RNGA_DRV_Init(uint32_t instance, const rnga_user_config_t *config)
{
    assert(instance < RNG_INSTANCE_COUNT);
    RNG_Type * base = g_rngaBase[instance];
    bool mEnable;
 
    if (!config)
    {
        return kStatus_RNGA_InvalidArgument;
    }
    /* Enable the clock gate from clock manager. */
    mEnable = CLOCK_SYS_GetRngaGateCmd(instance);
    if (!mEnable)
    {
        CLOCK_SYS_EnableRngaClock(instance);
    }
    /* Reset the registers for RNGA module to reset state. */
    RNGA_HAL_Init(base);
    RNGA_HAL_SetIntMaskCmd(base, config->isIntMasked);
    RNGA_HAL_SetHighAssuranceCmd(base, config->highAssuranceEnable);
    RNGA_HAL_Enable(base);
    
    return kStatus_RNGA_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name: RNGA_DRV_Deinit
 * Description: This function is used to shut down the RNGA.
 *
 *END*************************************************************************/
void RNGA_DRV_Deinit(uint32_t instance)
{
    assert(instance < RNG_INSTANCE_COUNT);
    RNG_Type * base = g_rngaBase[instance];
    
    RNGA_HAL_Disable(base);
    CLOCK_SYS_DisableRngaClock(instance);
}

/*FUNCTION*********************************************************************
 *
 * Function Name: RNGA_DRV_IRQHandler
 * Description: This function is used to handle error interrupt caused by RNGA underflow.
 *
 *END*************************************************************************/
void RNGA_DRV_IRQHandler(uint32_t instance)
{
    assert(instance < RNG_INSTANCE_COUNT);
    RNG_Type * base = g_rngaBase[instance];
    RNGA_HAL_ClearIntFlag(base, true);
    RNGA_HAL_GetOutputRegUnderflowCmd(base);
    RNGA_HAL_GetLastReadStatusCmd(base);
}
#endif

/*******************************************************************************
 * EOF
 *******************************************************************************/

