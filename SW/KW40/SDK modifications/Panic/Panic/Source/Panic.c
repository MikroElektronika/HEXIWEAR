/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file Panic.c
* This is the source file for the Panic module.
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

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#define gUsePanic_c 1

#include "panic.h"
#include "fsl_os_abstraction.h"

/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */
#if gUsePanic_c
panicData_t panic_data;
extern void ResetMCU(void);
#endif

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
* \brief  This function will halt the system
*
* \param[in]  id Description of the param2 in parameter
* \param[in]  location address where the Panic occured
* \param[in]  extra1 parameter to be stored in Panic structure
* \param[in]  extra2 parameter to be stored in Panic structure
*
********************************************************************************** */

void panic( panicId_t id, uint32_t location, uint32_t extra1, uint32_t extra2 )
{
#if gUsePanic_c
    /* Save the Link Register */
    volatile uint32_t savedLR;
    //  __asm("str  r14, [SP]");
    __asm("push {r2}  ");
    __asm("push {LR} ");
    __asm("pop  {r2} ");
    __asm("str  r2, [SP, #4]");
    __asm("pop {r2}");

    panic_data.id = id;
    panic_data.location = location;
    panic_data.extra1 = extra1;
    panic_data.extra2 = extra2;
    panic_data.linkRegister = savedLR;
    panic_data.cpsr_contents   = 0;
    
#if 0
    OSA_ExitCritical(kCriticalDisableInt); /* enable interrupts */
    OSA_TimeDelay(100);    /*  allowing datalogs to get out */
#endif
    OSA_EnterCritical(kCriticalDisableInt); /* disable interrupts */
    
    /* cause processor to halt */
#ifdef __IAR_SYSTEMS_ICC__
    __asm("BKPT #0xF");
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
#endif
#ifdef RVDS
    __breakpoint();
#endif
    
    /* infinite loop just to ensure this routine never returns */
    for(;;)
    {
        __asm("NOP");
        ResetMCU();
    }
#endif
}
