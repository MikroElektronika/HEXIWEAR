/**HEADER********************************************************************
* 
* Copyright (c) 2013 - 2014 Freescale Semiconductor;
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
* $FileName: osadapter.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains OS adapter layer api header function.
*
*****************************************************************************/

#ifndef _USB_OSADAPTER_H
#define _USB_OSADAPTER_H 1
#include "adapter_cfg.h"
#include "adapter_types.h"

#if defined (__cplusplus)
extern "C" {
#endif

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)            /* USB stack running on MQX */
#include "adapter_mqx.h"
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM)        /* USB stack running on BM  */
#include "adapter_bm.h"
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)        /* USB stack running on SDK  */
#include "adapter_sdk.h"
#endif

extern uint32_t OS_Task_create(task_start_t pstart, void* param, uint32_t pri, uint32_t stack_size, char* task_name, void* opt);
extern uint32_t OS_Task_delete(uint32_t task_id);
extern uint32_t OS_Task_suspend(uint32_t task_id);
extern uint32_t OS_Task_resume(uint32_t task_id);

extern os_event_handle OS_Event_create(uint32_t flag);
extern uint32_t OS_Event_destroy(os_event_handle handle);
extern uint32_t OS_Event_set(os_event_handle handle, uint32_t bitmask);
extern uint32_t OS_Event_check_bit(os_event_handle handle, uint32_t bitmask);
//extern uint32_t OS_Event_set_auto_clear(os_event_handle event, uint32 bitmask);
extern uint32_t OS_Event_clear(os_event_handle handle, uint32_t bitmask);
extern uint32_t OS_Event_wait(os_event_handle handle, uint32_t bitmask, uint32_t flag, uint32_t timeout);
//extern OS_Event_get_value(a,b)      _lwevent_get_value(a,b)
//#define OS_EVENT_WAIT_TIMEOUT            0x01


extern os_msgq_handle OS_MsgQ_create(uint32_t max_msg_number, uint32_t msg_size);
extern uint32_t OS_MsgQ_send(os_msgq_handle msgq, void* msg, uint32_t flag);
extern uint32_t OS_MsgQ_recv(os_msgq_handle msgq, void* msg, uint32_t flag, uint32_t timeout);
extern uint32_t OS_MsgQ_destroy(os_msgq_handle msgq);

extern os_gpio_handle OS_Gpio_init(uint32_t id, uint32_t dir, uint32_t value);
extern uint32_t OS_Gpio_set_functionality(os_gpio_handle handle, uint32_t function);
extern uint32_t OS_Gpio_set_value(os_gpio_handle handle, uint32_t value);

extern os_mutex_handle OS_Mutex_create(void);
extern uint32_t OS_Mutex_lock(os_mutex_handle handle);
extern uint32_t OS_Mutex_unlock(os_mutex_handle handle);
extern uint32_t OS_Mutex_destroy(os_mutex_handle handle);


extern os_sem_handle OS_Sem_create(uint32_t initial_number);
extern uint32_t OS_Sem_post(os_sem_handle handle);
extern uint32_t OS_Sem_wait(os_sem_handle handle,uint32_t timeout);
extern uint32_t OS_Sem_destroy(os_sem_handle handle);

#if defined(__cplusplus)
}
#endif


#endif


