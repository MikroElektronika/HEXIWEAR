/**
 * \file PE_low_level_init.c
 * \brief This file implements hardware low level initialization
 *
 * @version 1.00
 *
 * Copyright : 1997 - 2015 NXP Semiconductor, Inc.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *  of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *
 * Neither the name of NXP Semiconductor, Inc. nor the names of its
 *  contributors may be used to endorse or promote products derived from this
 *  software without specific prior written permission.
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
 *
 * http: www.nxp.com
 * mail: support@nxp.com
 */

#include "PE_low_level_init.h"
#if CPU_HARDWARE_INIT
  #include "board.h"
#endif
#if CPU_PERIPHERALS_INIT
  #include "Peripherals_Init.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * initialize hardware components
 */
void PEX_components_init()
{
   /** Common initialization */
  #if CPU_COMMON_INIT
  Common_Init();
  #endif  /** CPU_COMMON_INIT */

   /** Peripheral initialization components initialization */
  #if CPU_PERIPHERALS_INIT
  Peripherals_Init();
  #endif  /** CPU_PERIPHERALS_INIT */

   /** Rest of components initialization */
//  #if CPU_COMPONENTS_INIT
  Components_Init();
//  #endif  /** CPU_COMPONENTS_INIT */
}

/**
 * set clocks, configure pins and initialize RTOS and hardware components
 */
void PE_low_level_init()
{
   /** Global routing function and crystal values initialization */
//  #if CPU_HARDWARE_INIT
  hardware_init();
//  #endif  /** CPU_HARDWARE_INIT */

   /** RTOS initialization */
//  #ifdef PEX_RTOS_INIT
  PEX_RTOS_INIT();                    /** Initialization of the selected RTOS. Macro is defined by the RTOS component. */
//  #endif

   /** Components initialization, when RTOS is active this method is called in rtos_main_task() (from MainTask component) */
//  #ifdef PEX_COMPONENTS_INIT
  PEX_components_init();
//  #endif
}

#ifdef __cplusplus
}
#endif
