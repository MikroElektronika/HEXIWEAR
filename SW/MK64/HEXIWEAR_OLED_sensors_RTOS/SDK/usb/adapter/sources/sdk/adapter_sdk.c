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
 * $FileName: osadapter_ucos.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief The file includes the implementation of OS adapter based on SDK OSA.
 * 
 *****************************************************************************/
#include "adapter_cfg.h"
#include "adapter_types.h"
#include "adapter_sdk.h"
#include "adapter.h"

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"

uint8_t soc_get_usb_vector_number(uint8_t controller_id)
{
    if (controller_id == 0)
    {
        return USB0_IRQn;
    }
#if defined (USBHS_BASE)
    else if (controller_id == 2)
    {
        return USBHS_IRQn;
    }
#endif
    return 0;
}

uint32_t soc_get_usb_base_address(uint8_t controller_id)
{
    if (controller_id == 0)
    {
        return (uint32_t) USB0_BASE;
    }
#if defined (USBHS_BASE)
    else if (controller_id == 2)
    {
        return (uint32_t)USBHS_BASE;
    }
#endif
    return (uint32_t) NULL;
}

os_gpio_handle OS_Gpio_init(uint32_t id, uint32_t dir, uint32_t value)
{
    return (os_gpio_handle)(0x0000FFFF);
}

uint32_t OS_Gpio_set_functionality(os_gpio_handle handle, uint32_t function)
{
    return OS_GPIO_OK;
}

uint32_t OS_Gpio_set_value(os_gpio_handle handle, uint32_t value)
{
    return OS_GPIO_OK;
}

uint32_t OS_Gpio_deinit(os_gpio_handle handle)
{
    return OS_GPIO_OK;
}

/* Structure for uC/OS to manage the task stack and task handler. */
#if ((defined (FSL_RTOS_UCOSII)) || (defined (FSL_RTOS_UCOSIII)))
typedef struct _usb_adapter_task_struct
{
    void *stack_mem;  // Pointer to task stack.
    task_handler_t handler;// Handler of task.
}usb_adapter_task_struct;
#endif

uint32_t OS_Task_create(task_start_t pstart, void* param, uint32_t pri, uint32_t stack_size, char* task_name, void* opt)
{
    osa_status_t status;
    /*
     * For uC/OS, we should allocate memory for task stack.
     */
#if ((defined (FSL_RTOS_UCOSII)) || (defined (FSL_RTOS_UCOSIII)))
    usb_adapter_task_struct* task_struct = OSA_MemAllocZero(sizeof(usb_adapter_task_struct));
    if (!task_struct)
    {
        return (uint32_t)OS_TASK_ERROR;
    }

    task_struct->stack_mem = OSA_MemAlloc(stack_size);
    if(!task_struct->stack_mem)
    {
        OSA_MemFree(task_struct);
        return (uint32_t)OS_TASK_ERROR;
    }

#if defined (FSL_RTOS_UCOSIII)
    task_struct->handler = OSA_MemAllocZero(sizeof(OS_TCB));
    if(!task_struct->handler)
    {
        OSA_MemFree(task_struct->stack_mem);
        OSA_MemFree(task_struct);
        return (uint32_t)OS_TASK_ERROR;
    }
#endif
    status = OSA_TaskCreate((task_t)pstart, (uint8_t*)task_name, stack_size,
    task_struct->stack_mem, pri, (task_param_t)param, false, &task_struct->handler);
    if (kStatus_OSA_Success == status)
    {
        return (uint32_t)task_struct;
    }
    else
    {
        return (uint32_t)OS_TASK_ERROR;
    }

#else //((defined (FSL_RTOS_UCOSII)) || (defined (FSL_RTOS_UCOSIII)))
    task_handler_t task_handler;
    status = OSA_TaskCreate((task_t) pstart, (uint8_t*) task_name, stack_size, NULL, pri, (task_param_t) param, false, &task_handler);

    if (kStatus_OSA_Success == status)
    {
        return (uint32_t) task_handler;
    }
    else
    {
        return (uint32_t) OS_TASK_ERROR;
    }
#endif //((defined (FSL_RTOS_UCOSII)) || (defined (FSL_RTOS_UCOSIII)))
}

uint32_t OS_Task_delete(uint32_t task_id)
{
#if ((defined (FSL_RTOS_UCOSII)) || (defined (FSL_RTOS_UCOSIII)))
    usb_adapter_task_struct* task_struct = (usb_adapter_task_struct*)task_id;

    if (kStatus_OSA_Success != OSA_TaskDestroy(task_struct->handler))
    {
        return (uint32_t)OS_TASK_ERROR;
    }
#if defined (FSL_RTOS_UCOSIII)
    OSA_MemFree(task_struct->handler);  // Free TCB
#endif
    OSA_MemFree(task_struct->stack_mem);  // Free stack memory
    OSA_MemFree(task_struct);
    return (uint32_t)OS_TASK_OK;
#else
    return (kStatus_OSA_Success == OSA_TaskDestroy((task_handler_t) task_id)) ? (uint32_t) OS_TASK_OK : (uint32_t) OS_TASK_ERROR;
#endif
}

/* Event create and destroy */
os_event_handle OS_Event_create(uint32_t flag)
{
    event_t *p_event = (event_t *) OSA_MemAllocZero(sizeof(event_t));

    if (!p_event)
    {
        return (os_event_handle) 0;
    }

    if (kStatus_OSA_Success != OSA_EventCreate(p_event, flag ? kEventAutoClear : kEventManualClear))
    {
        OSA_MemFree(p_event);
        return (os_event_handle) 0;
    }
    return (os_event_handle) p_event;
}

uint32_t OS_Event_destroy(os_event_handle handle)
{
    event_t* obj = (event_t*) handle;

    if (kStatus_OSA_Success == OSA_EventDestroy(obj))
    {
        OSA_MemFree(handle);
        return (uint32_t) OS_EVENT_OK;
    }
    else
    {
        return (uint32_t) OS_EVENT_ERROR;
    }
}

/* Message queue create and destroy */
/*
 * NOTE: The msg_size here is counted by words, not bytes!
 */
os_msgq_handle OS_MsgQ_create(uint32_t max_msg_number, uint32_t msg_size)
{
    os_msgq_handle ret;
#if defined (FSL_RTOS_UCOSII)
    uint8_t *p_tmp;
    uint32_t size = sizeof(msg_queue_t)
    + (msg_size*sizeof(int32_t)+sizeof(void*))*max_msg_number;
#elif defined (FSL_RTOS_UCOSIII)
    uint8_t *p_tmp;
    uint32_t size = sizeof(msg_queue_t) + (msg_size*sizeof(int32_t))*max_msg_number;
#elif defined (FSL_RTOS_MQX)
    uint32_t size = (SIZE_IN_MMT_UNITS(sizeof(LWMSGQ_STRUCT))
    + SIZE_IN_MMT_UNITS((msg_size*sizeof(int32_t))*(max_msg_number)))
    * sizeof(_mqx_max_type);
#elif defined (FSL_RTOS_FREE_RTOS)
#else /* Bare metal by default. */
    uint8_t *p_tmp;
    uint32_t size = sizeof(msg_queue_t) + sizeof(uint32_t) * max_msg_number * msg_size;
#endif

#if defined (FSL_RTOS_FREE_RTOS)
    msg_queue_t* msgq = NULL;
#else
    msg_queue_t* msgq = (msg_queue_t*) OSA_MemAllocZero(size);

    if (!msgq)
    {
        return (msg_queue_handler_t) 0;
    }
#endif
    /* initialize the msg_queue_t */
#if defined (FSL_RTOS_UCOSII)
    p_tmp = (uint8_t*)msgq;
    p_tmp += sizeof(msg_queue_t);
    msgq->msgTbl = (void**)p_tmp;
    p_tmp += max_msg_number*sizeof(void*);
    msgq->msgs = (uint32_t*)p_tmp;
#elif defined (FSL_RTOS_UCOSIII)
    p_tmp = (uint8_t*)msgq;
    p_tmp += sizeof(msg_queue_t);
    msgq->msgs = (void*)p_tmp;
#elif defined (FSL_RTOS_MQX)
#elif defined (FSL_RTOS_FREE_RTOS)
#else /* Bare metal by default. */
    p_tmp = (uint8_t*) msgq;
    p_tmp += sizeof(msg_queue_t);
    msgq->queueMem = (uint32_t*) p_tmp;
#endif
    ret = OSA_MsgQCreate(msgq, max_msg_number, msg_size);
#if !defined (FSL_RTOS_FREE_RTOS)
    if (!ret)
    {
        OSA_MemFree(msgq);
    }
#endif
    return ret;
}

uint32_t OS_MsgQ_destroy(os_msgq_handle msgq)
{
    if (kStatus_OSA_Success == OSA_MsgQDestroy((msg_queue_handler_t) msgq))
    {
#if !defined (FSL_RTOS_FREE_RTOS)
        OSA_MemFree(msgq);
#endif
        return (uint32_t) OS_MSGQ_OK;
    }
    else
    {
        return (uint32_t) OS_MSGQ_ERROR;
    }
}

/* Mutex create and destroy */
os_mutex_handle OS_Mutex_create(void)
{
    mutex_t *p_mutex = (mutex_t *) OSA_MemAllocZero(sizeof(mutex_t));

    if (!p_mutex)
    {
        return (os_mutex_handle) 0;
    }
    if (kStatus_OSA_Success != OSA_MutexCreate(p_mutex))
    {
        OSA_MemFree(p_mutex);
        return (os_mutex_handle) 0;
    }

    return (os_mutex_handle) p_mutex;
}

uint32_t OS_Mutex_destroy(os_mutex_handle handle)
{
    if (kStatus_OSA_Success == OSA_MutexDestroy((mutex_t*) handle))
    {
        OSA_MemFree(handle);
        return (uint32_t) OS_MUTEX_OK;
    }
    else
    {
        return (uint32_t) OS_MUTEX_ERROR;
    }
}

/* Semaphore create and destroy */
os_sem_handle OS_Sem_create(uint32_t initial_number)
{
    semaphore_t *p_sem = (semaphore_t *) OSA_MemAllocZero(sizeof(semaphore_t));

    if (!p_sem)
    {
        return (os_sem_handle) 0;
    }

    if (kStatus_OSA_Success != OSA_SemaCreate(p_sem, initial_number))
    {
        OSA_MemFree(p_sem);
        return (os_sem_handle) 0;
    }

    return (os_sem_handle) p_sem;
}

uint32_t OS_Sem_destroy(os_sem_handle handle)
{
    if (kStatus_OSA_Success == OSA_SemaDestroy((semaphore_t*) handle))
    {
        OSA_MemFree(handle);
        return (uint32_t) OS_SEM_OK;
    }
    else
    {
        return (uint32_t) OS_SEM_ERROR;
    }
}

/* Events */
uint32_t OS_Event_check_bit(os_event_handle handle, uint32_t bitmask)
{
    event_t* event = (event_t*) handle;
    return (((uint32_t) OSA_EventGetFlags(event)) & bitmask);
}

uint32_t OS_Event_set(os_event_handle handle, uint32_t bitmask)
{
    return ((kStatus_OSA_Success == OSA_EventSet((event_t*) (handle), (bitmask))) ? OS_EVENT_OK : OS_EVENT_ERROR);
}

uint32_t OS_Event_clear(os_event_handle handle, uint32_t bitmask)
{
    return ((kStatus_OSA_Success == OSA_EventClear((event_t*) (handle), (bitmask))) ? OS_EVENT_OK : OS_EVENT_ERROR);
}

uint32_t OS_Event_wait(os_event_handle handle, uint32_t bitmask, uint32_t flag, uint32_t timeout)
{
    osa_status_t status = kStatus_OSA_Idle;
    event_flags_t event_bit;
    uint32_t re;
    event_t* event = (event_t*) handle;
    // flag will always be false, so wait any bits
#if (USE_RTOS)
    if (0 == timeout)
    {
        timeout = OSA_WAIT_FOREVER;
    }
#endif
    // Block or timeout mode
    do
    {
        status = OSA_EventWait(event, bitmask, flag, timeout, &event_bit);
    } while (kStatus_OSA_Idle == status);

    switch(status)
    {
    case kStatus_OSA_Success:
        re = (uint32_t) OS_EVENT_OK;
        break;
    case kStatus_OSA_Timeout:
        re = (uint32_t) OS_EVENT_TIMEOUT;
        break;
    default:
        re = (uint32_t) OS_EVENT_ERROR;
        break;
    }
    return re;
}

/* Semaphore */
uint32_t OS_Sem_post(os_sem_handle handle)
{
    return ((kStatus_OSA_Success == OSA_SemaPost((semaphore_t*) (handle))) ? OS_SEM_OK : OS_SEM_ERROR);
}

uint32_t OS_Sem_wait(os_sem_handle handle, uint32_t timeout)
{
    osa_status_t status = kStatus_OSA_Idle;
    uint32_t re;
#if (USE_RTOS)
    if (0==timeout)
    {
        timeout = OSA_WAIT_FOREVER;
    }
#endif
    do
    {
        status = OSA_SemaWait((semaphore_t*) handle, timeout);
    } while (kStatus_OSA_Idle == status);

    switch(status)
    {
    case kStatus_OSA_Success:
        re = (uint32_t) OS_SEM_OK;
        break;
    case kStatus_OSA_Timeout:
        re = (uint32_t) OS_SEM_TIMEOUT;
        break;
    default:
        re = (uint32_t) OS_SEM_ERROR;
        break;
    }
    return re;
}

/* Mutex */
uint32_t OS_Mutex_lock(os_mutex_handle handle)
{
    osa_status_t status = kStatus_OSA_Idle;
    uint32_t re;

#if !(USE_RTOS)
    status = OSA_MutexLock((mutex_t*) handle, 0);
#else
    status = OSA_MutexLock((mutex_t*)handle, OSA_WAIT_FOREVER);
#endif

    switch(status)
    {
    case kStatus_OSA_Success:
        re = (uint32_t) OS_MUTEX_OK;
        break;
    default:
        re = (uint32_t) OS_MUTEX_ERROR;
        break;
    }
    return re;
}

uint32_t OS_Mutex_unlock(os_mutex_handle handle)
{
    return ((kStatus_OSA_Success == OSA_MutexUnlock((mutex_t*) (handle))) ? OS_MUTEX_OK : OS_MUTEX_ERROR);
}

/* Message queue */
uint32_t OS_MsgQ_recv(os_msgq_handle msgq, void* msg, uint32_t flag, uint32_t timeout)
{
    osa_status_t status;
    uint32_t re;

    status = OSA_MsgQGet((msg_queue_handler_t)msgq, msg,
                          (!(OS_MSGQ_RECEIVE_BLOCK_ON_EMPTY & flag)) ?
                           0u                                        :
                          ((0==timeout) ? OSA_WAIT_FOREVER : timeout));

    switch(status)
    {
    case kStatus_OSA_Success:
        re = (uint32_t) OS_MSGQ_OK;
        break;
    case kStatus_OSA_Timeout:
        re = (uint32_t) OS_MSGQ_TIMEOUT;
        break;
    default:
        re = (uint32_t) OS_MSGQ_ERROR;
        break;
    }
    return re;
}

uint32_t OS_MsgQ_send(os_msgq_handle msgq, void* msg, uint32_t flag)
{
    return ((kStatus_OSA_Success == OSA_MsgQPut((msg_queue_handler_t)(msgq),
        msg
        )) ? OS_MSGQ_OK : OS_MSGQ_ERROR);
}

uint32_t OS_MsgQ_Is_Empty(os_msgq_handle msgq, void* msg)
{
    return (kStatus_OSA_Success == OSA_MsgQGet((msg_queue_handler_t) msgq, msg, 0)) ? 0 : 1;
}

