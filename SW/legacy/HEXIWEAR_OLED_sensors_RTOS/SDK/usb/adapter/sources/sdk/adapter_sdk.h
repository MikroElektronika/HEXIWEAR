/**HEADER********************************************************************
*
* Copyright (c) 2013 Freescale Semiconductor;
* All Rights Reserved
*
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: osadapter_ucos.h$
* $Version :
* $Date    :
*
* Comments:
*
* @brief The file contains the definition of OS adapter base-on SDK OSA.
*
*****************************************************************************/

#ifndef _USB_OSADAPTER_SDK_H
#define _USB_OSADAPTER_SDK_H 1

#include "fsl_os_abstraction.h"
#if !defined (FSL_RTOS_MQX)
#include "compiler.h"
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// lajka
//#include "fsl_debug_console.h"

#define BIG_ENDIAN           0
#define LITTLE_ENDIAN        1

#define ENDIANNESS           LITTLE_ENDIAN

#define _CODE_PTR_ *

#ifndef FALSE
#define FALSE ((bool)0)
#endif

#ifndef TRUE
#define TRUE ((bool)1)
#endif

#define UNUSED(x)   (void)x;

#define OS_MSGQ_TIMEOUT    (-2)
//extern void * memset (void *, int32_t, unsigned);
//extern int32_t printf_kinetis (const char *fmt, ...);

//#define USB_PRINTF                                           PRINTF
// lajka
#define USB_PRINTF( arg ) ((void) 0)
//#define OS_install_isr
#define OS_install_isr(num, isr, data)   OSA_InstallIntHandler(num, isr)
#define OS_intr_init(num, prior, subprior, enable)         \
do { \
    NVIC_SetPriority(num, prior); \
    NVIC_EnableIRQ(num); \
}while(0)

#define TICKS_PER_SEC 1000

//#define TICKS_TO_MSEC(ticks) ((ticks)*1000uL/OS_TICKS_PER_SEC)

#define OS_Lock()   OSA_EnterCritical(kCriticalDisableInt)
#define OS_Unlock() OSA_ExitCritical(kCriticalDisableInt)

/* Based on the targets it should be modified, for ColdFire it is MBYTES */
#define OS_dcache_invalidate_mlines(p,n)
#define OS_dcache_flush_mlines(p,n)


#ifndef OS_Mem_alloc_uncached
#define OS_Mem_alloc_uncached             OS_Mem_alloc
#endif

#ifndef OS_Mem_alloc_uncached_zero
#define OS_Mem_alloc_uncached_zero        OS_Mem_alloc_zero
#endif

#define OS_Mem_alloc_zero(n)              OSA_MemAllocZero(n)
#define OS_Mem_alloc(n)                   OSA_MemAlloc(n)
#define OS_Mem_free(ptr)                  OSA_MemFree(ptr)

#define OS_Mem_zero(ptr,n)                memset((ptr),(0),(n))
#define OS_Mem_copy(src,dst,n)            memcpy((dst),(src),(n))
#if defined(__cplusplus)
extern "C"{
#endif
extern uint32_t OS_MsgQ_Is_Empty(os_msgq_handle msgq, void* msg);

#if defined(__cplusplus)
}
#endif
/* TimeDelay */
#define OS_Time_delay                     OSA_TimeDelay

#endif


