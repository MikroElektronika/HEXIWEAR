/**HEADER********************************************************************
 * 
 * Copyright (c) 2008, 2013 - 2014 Freescale Semiconductor;
 * All Rights Reserved
 *
 * Copyright (c) 1989-2008 ARC International;
 * All Rights Reserved
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
 * $FileName: usb_dev.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 *  This file contains the main USB device API functions that will be 
 *  used by most applications.
 *                                                               
 *END*********************************************************************/
#include "usb_device_config.h"
#if USBCFG_DEV_KHCI || USBCFG_DEV_EHCI
#include "usb.h"
#include "usb_device_stack_interface.h"

//#define USBCFG_DEV_USE_TASK                   (0)
#define USBCFG_DEV_SERVICE_MSG_CNT            (8)
#define MSG_SIZE_IN_MAX_TYPE                  (1 + (sizeof(usb_event_struct_t) - 1) / sizeof(uint32_t))

#include "usb_dev.h"
#include "khci_dev_misc.h"
#ifdef USBCFG_OTG
#include "usb_otg_dev_api.h"
#endif

#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)))
    #if defined( __ICCARM__ )
        #pragma data_alignment=32
        __no_init usb_dev_data_t g_usb_dev_data[USBCFG_DEV_NUM];
    #elif defined (__CC_ARM) || defined(__GNUC__)
        __attribute__((aligned(32))) usb_dev_data_t g_usb_dev_data[USBCFG_DEV_NUM];
    #else
        #error Unsupported compiler, please use IAR, Keil or arm gcc compiler and rebuild the project.
    #endif
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
        usb_dev_data_t* g_usb_dev_data_ptr[USBCFG_DEV_NUM] = {NULL};
#endif

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM)
#define OS_Mutex_lock(_M_) OS_Lock()
#define OS_Mutex_unlock(_M_) OS_Unlock()
#endif
#define USB_DEV_HANDLE_OCCUPIED ((uint8_t)1)
#define USB_DEV_HANDLE_FREE     ((uint8_t)0)

#if USBCFG_DEV_USE_TASK
#define USB_DEVICE_TASK_TEMPLATE_INDEX           0

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)            /* USB stack running on MQX */
#define USB_DEVICE_TASK_ADDRESS                   _usb_dev_task_stun

#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM)        /* USB stack running on BM  */
#define USB_DEVICE_TASK_ADDRESS                   _usb_dev_task

#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
#if USE_RTOS
#define USB_DEVICE_TASK_ADDRESS                   _usb_dev_task_stun
#else
#define USB_DEVICE_TASK_ADDRESS                   _usb_dev_task
#endif

#endif

#define USB_DEVICE_TASK_PRIORITY                 (6)
#define USB_DEVICE_TASK_STACKSIZE                (3500)
#define USB_DEVICE_TASK_NAME                     "Device Task"
#define USB_DEVICE_TASK_ATTRIBUTES               (0)
#define USB_DEVICE_TASK_CREATION_PARAMETER       (0)
#define USB_DEVICE_TASK_DEFAULT_TIME_SLICE       (0)

#endif
extern usb_status bsp_usb_dev_init(uint8_t controller_id);
#ifdef USBCFG_OTG
extern usb_status bsp_usb_otg_dev_init(uint8_t controller_id);
#endif
#if USBCFG_DEV_KHCI && USBCFG_DEV_DETACH_ENABLE && USBCFG_DEV_IO_DETACH_ENABLE
extern int32_t bsp_usb_detach_init(uint8_t controller_id);
#endif
extern void USB_Control_Service (void* handle, usb_event_struct_t* event,void* arg);
extern void USB_Reset_Service(void* handle, usb_event_struct_t* event, void* arg);
extern void USB_Error_Service(void* handle, usb_event_struct_t* event, void* arg);
extern void USB_Suspend_Service(void* handle, usb_event_struct_t* event,void* arg);
extern void USB_Resume_Service(void* handle,usb_event_struct_t* event,void* arg );

static usb_dev_state_struct_t g_usb_dev[USBCFG_DEV_NUM] = {{0}};
#if USBCFG_DEV_KHCI
extern const usb_dev_interface_functions_struct_t _usb_khci_dev_function_table;
#endif
#if USBCFG_DEV_EHCI
extern const usb_dev_interface_functions_struct_t _usb_ehci_dev_function_table;
#endif

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_device_get_handle
 *  Returned Value : NULL
 *  Comments       :
 *        This function is used to get one unused device object
 *
 *END*-----------------------------------------------------------------*/
static usb_dev_state_struct_t* _usb_device_get_handle
(
    void
)
{
    uint8_t i = 0;

    for (; i < USBCFG_DEV_NUM; i++)
    {
        if (g_usb_dev[i].occupied != USB_DEV_HANDLE_OCCUPIED)
        {
            OS_Mem_zero(&g_usb_dev[i], sizeof(usb_dev_state_struct_t));
            g_usb_dev[i].occupied = USB_DEV_HANDLE_OCCUPIED;
            g_usb_dev[i].dev_index = i;
            return &g_usb_dev[i];
        }
    }
    return NULL;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_device_release_handle
 *  Returned Value : NULL
 *  Comments       :
 *        This function is used to set one used device object to free
 *
 *END*-----------------------------------------------------------------*/
static void _usb_device_release_handle
(
usb_dev_state_struct_t *usb_dev
)
{
    usb_dev->occupied = USB_DEV_HANDLE_FREE;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_device_get_DCI
 *  Returned Value : NULL
 *  Comments       :
 *        This function is used to get the device controller's interface table pointer
 *
 *END*-----------------------------------------------------------------*/
static void _usb_device_get_DCI
(
    uint8_t controller_id,
    const usb_dev_interface_functions_struct_t ** controller_if_ptr
)
{
#if USBCFG_DEV_KHCI
    if ((controller_id == USB_CONTROLLER_KHCI_0) || ((controller_id == USB_CONTROLLER_KHCI_1)))
    {
        *controller_if_ptr = (usb_dev_interface_functions_struct_t const*)&_usb_khci_dev_function_table;
    }
#endif

#if USBCFG_DEV_EHCI
    if ((controller_id == USB_CONTROLLER_EHCI_0) || (controller_id == USB_CONTROLLER_EHCI_1))
    {
        *controller_if_ptr = &_usb_ehci_dev_function_table;
    }
#endif
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_device_shutdown
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Shutdown an initialized USB device
 *
 *END*-----------------------------------------------------------------*/
static usb_status _usb_device_shutdown
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle         handle
)
{
    usb_status error;
    usb_dev_state_struct_t* usb_dev_ptr;

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;
#if USBCFG_DEV_USE_TASK

    if (usb_dev_ptr->task_id != (uint32_t)OS_TASK_ERROR)
    {
        OS_Task_delete(usb_dev_ptr->task_id);
    }
    if (NULL != usb_dev_ptr->usb_dev_service_que)
    {
        OS_MsgQ_destroy(usb_dev_ptr->usb_dev_service_que);
    }
#endif
    if (usb_dev_ptr->usb_dev_interface->dev_shutdown != NULL)
    {
        error = (usb_dev_ptr->usb_dev_interface)->dev_shutdown(usb_dev_ptr->controller_handle);
        return error;
    }
    else
    {
#if _DEBUG
        USB_PRINTF("_usb_device_shutdown: DEV_SHUTDOWN is NULL\n");
#endif  
        return USBERR_ERROR;
    }
} /* EndBody */

/*FUNCTION*----------------------------------------------------------------
 * 
 * Function Name  : usb_device_call_service
 * Returned Value : USB_OK or error code
 * Comments       :
 *     Calls the appropriate service for the specified type, if one is
 *     registered. Used internally only.
 * 
 *END*--------------------------------------------------------------------*/
usb_status _usb_device_call_service_internal
(
      /* [IN] pointer to usb device status structure  */ 
      usb_dev_state_struct_t*       usb_dev_ptr,
      /* [IN] pointer to event structure  */ 
      usb_event_struct_t*    event 
)
{
    service_struct_t* service_ptr = NULL;
    uint32_t i;

    /* Needs mutual exclusion */
    //OS_Mutex_lock(usb_dev_ptr->mutex);
    switch (event->type)
    {
    case USB_SERVICE_EP0:
        USB_Control_Service(&usb_dev_ptr->usb_framework, event, NULL);
        break;
    case USB_SERVICE_BUS_RESET:
        USB_Reset_Service(&usb_dev_ptr->usb_framework, event, NULL);
        break;
#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME
    case USB_SERVICE_SUSPEND:
        USB_Suspend_Service(&usb_dev_ptr->usb_framework, event, NULL);
        break;
    case USB_SERVICE_RESUME:
        USB_Resume_Service(&usb_dev_ptr->usb_framework, event, NULL);
        break;
#endif
#if USBCFG_DEV_KHCI_ADVANCED_ERROR_HANDLING
    case USB_SERVICE_ERROR:
        USB_Error_Service(&usb_dev_ptr->usb_framework, event, NULL);
        break;
#endif
#if USBCFG_DEV_DETACH_ENABLE
    case USB_SERVICE_DETACH:
        USB_Detach_Service(&usb_dev_ptr->usb_framework, event, NULL);
        break;
#endif
        default:
        break;
    } /* Endswitch */

    /* Search for an existing entry for type */
    for (i = 0; i < MAX_DEVICE_SERVICE_NUMBER; i++)
    {
        service_ptr = &usb_dev_ptr->services[i];
        if (service_ptr->type == event->type)
        {
            service_ptr->service(event,service_ptr->arg);
            //OS_Mutex_unlock(usb_dev_ptr->mutex);
            return USB_OK;
        }
    }

    //OS_Mutex_unlock(usb_dev_ptr->mutex);
    return USBERR_CLOSED_SERVICE;
} /* EndBody */

#if USBCFG_DEV_USE_TASK
static void _usb_dev_task
(
    void* dev_inst_ptr
)
{
    usb_dev_state_struct_t* usb_dev_ptr = (usb_dev_state_struct_t*)dev_inst_ptr;
    static usb_event_struct_t msg = {0};

    //if (!OS_MsgQ_Is_Empty(usb_device_ptr->isr_que,&msg))
    while (!OS_MsgQ_recv(usb_dev_ptr->usb_dev_service_que, (uint32_t *) &msg, OS_MSGQ_RECEIVE_BLOCK_ON_EMPTY, 10))
    {
        _usb_device_call_service_internal(usb_dev_ptr, &msg);
    }
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_khci_task_stun
 *  Returned Value : none
 *  Comments       :
 *        KHCI task
 *END*-----------------------------------------------------------------*/
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX) || ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK) && USE_RTOS)
static void _usb_dev_task_stun
(
    void* dev_inst_ptr
)
{
    while (1)
    {
        _usb_dev_task(dev_inst_ptr);
    }
}
#endif

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : _usb_task_create
 *  Returned Value : error or USB_OK
 *  Comments       :
 *        Create device task
 *END*-----------------------------------------------------------------*/
static usb_status _usb_dev_task_create
(
    usb_device_handle handle
)
{
    //USB_STATUS status;
    //task_id = _task_create_blocked(0, 0, (uint32_t)&task_template);
    usb_dev_state_struct_t* usb_dev_ptr;

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;
    usb_dev_ptr->task_id = OS_Task_create(USB_DEVICE_TASK_ADDRESS, (void*)handle, (uint32_t)USB_DEVICE_TASK_PRIORITY, USB_DEVICE_TASK_STACKSIZE, USB_DEVICE_TASK_NAME, NULL);

    if (usb_dev_ptr->task_id == (uint32_t)OS_TASK_ERROR)
    {
        return USBERR_ERROR;
    }

    //_task_ready(_task_get_td(task_id));
    //OS_Task_resume(task_id);

    return USB_OK;
}

#endif

/*FUNCTION*----------------------------------------------------------------
 * 
 * Function Name  : usb_device_call_service
 * Returned Value : USB_OK or error code
 * Comments       :
 *     Calls the appropriate service for the specified type, if one is
 *     registered. Used internally only.
 * 
 *END*--------------------------------------------------------------------*/
usb_status _usb_device_call_service
(
    /* [IN] Type of service or endpoint */
    uint8_t                  type,
    /* [IN] pointer to event structure  */ 
    usb_event_struct_t*      event
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    usb_dev_ptr = (usb_dev_state_struct_t*)event->handle;

    event->type = type;
    if((type & 0x7F) && ((type & 0x7F) < 0x10))
    {
        event->type = (uint8_t)(((uint8_t)(event->direction << 7)) | (uint8_t)(type & 0x7F));
    }
#if USBCFG_DEV_USE_TASK
    if (0 != OS_MsgQ_send(usb_dev_ptr->usb_dev_service_que, (void *)event, 0))
    {
        return USBERR_ALLOC_STATE;
    }
    return USB_OK;
#else
    return _usb_device_call_service_internal(usb_dev_ptr, event);
#endif

}
/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_set_address
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Sets the device address as assigned by the host during enumeration
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_set_address
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle         handle,
    /* [IN] the USB address to be set in the hardware */
    uint8_t                     address
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    usb_status error;

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    if ((usb_dev_ptr->usb_dev_interface)->dev_set_address != NULL)
    {
        error = (usb_dev_ptr->usb_dev_interface)->dev_set_address(usb_dev_ptr->controller_handle, address);
        return error;
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_set_address: DEV_SET_ADDRESS is NULL\n");
#endif  
        return USBERR_ERROR;
    }

}

/*FUNCTION*----------------------------------------------------------------
 * 
 * Function Name  : usb_device_get_status
 * Returned Value : USB_OK or error code
 * Comments       :
 *     Provides API to access the USB internal state.
 * 
 *END*--------------------------------------------------------------------*/
usb_status usb_device_get_status
(
    /* [IN] Handle to the USB device */
    usb_device_handle   handle,
    /* [IN] What to get the error of */
    uint8_t              component,
    /* [OUT] The requested error */
    uint16_t*            error
)
{ /* Body */
    usb_dev_state_struct_t* usb_dev_ptr;

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    OS_Mutex_lock(usb_dev_ptr->mutex);
    if (component & USB_STATUS_ENDPOINT)
    {
        if ((usb_dev_ptr->usb_dev_interface)->dev_get_endpoint_status != NULL)
        {
            (usb_dev_ptr->usb_dev_interface)->dev_get_endpoint_status(usb_dev_ptr->controller_handle,
            (uint8_t)(component),error);
        }
        else
        {
#if _DEBUG
            USB_PRINTF("usb_device_get_status: DEV_GET_ENDPOINT_STATUS is NULL\n");
#endif  
            OS_Mutex_unlock(usb_dev_ptr->mutex);
            return USBERR_ERROR;
        }
    }
    else
    {
        if ((usb_dev_ptr->usb_dev_interface)->dev_get_device_status != NULL)
        {
            (usb_dev_ptr->usb_dev_interface)->dev_get_device_status(usb_dev_ptr->controller_handle,
            (uint8_t)(component),error);
        }
        else
        {
#if _DEBUG
            USB_PRINTF("usb_device_get_status: DEV_GET_DEVICE_STATUS is NULL\n");
#endif  
            OS_Mutex_unlock(usb_dev_ptr->mutex);
            return USBERR_ERROR;
        }
    }

    OS_Mutex_unlock(usb_dev_ptr->mutex);
    return USB_OK;
}

/*FUNCTION*----------------------------------------------------------------
 * 
 * Function Name  : usb_device_set_status
 * Returned Value : USB_OK or error code
 * Comments       :
 *     Provides API to set internal state
 * 
 *END*--------------------------------------------------------------------*/
usb_status usb_device_set_status
(
/* [IN] Handle to the usb device */
usb_device_handle handle,
/* [IN] What to set the error of */
uint8_t component,
/* [IN] What to set the error to */
uint16_t setting
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    uint8_t error = USB_OK;

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;
    OS_Mutex_lock(usb_dev_ptr->mutex);
    if ((usb_dev_ptr->usb_dev_interface)->dev_set_device_status != NULL)
    {
        (usb_dev_ptr->usb_dev_interface)->dev_set_device_status(usb_dev_ptr->controller_handle,
        (uint8_t)(component),setting);
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_set_status: dev_set_device_status is NULL\n");
#endif  
        OS_Mutex_unlock(usb_dev_ptr->mutex);
        return USBERR_ERROR;
    }

    OS_Mutex_unlock(usb_dev_ptr->mutex);
    return error;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_init
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Initializes the USB device specific data structures and calls 
 *  the low-level device controller chip initialization routine.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_init
(
      /* [IN] the USB device controller to initialize */
      uint8_t controller_id,
      /* [OUT] the USB_USB_dev_initialize state structure */
      usb_device_handle *  handle
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    uint8_t i;
    usb_status error = USB_OK;
    const usb_dev_interface_functions_struct_t* dev_if = NULL;
    usb_class_fw_object_struct_t* usb_fw_ptr = NULL;

    //OS_Lock();

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    for(i = 0; i < USBCFG_DEV_NUM; i++)
    {
        if(NULL == g_usb_dev_data_ptr[i])
        {
            g_usb_dev_data_ptr[i] = OS_Mem_alloc_uncached_align(sizeof(usb_dev_data_t), 32);
        }
    }
#endif

    usb_dev_ptr = _usb_device_get_handle();

    if(usb_dev_ptr == NULL)
    {
        /* The interface does not support device functionality */
        //OS_Unlock();
        return USBERR_DEVICE_BUSY;
    }
    usb_dev_ptr->controller_id = controller_id;
    usb_fw_ptr = &usb_dev_ptr->usb_framework;
    usb_dev_ptr->mutex = OS_Mutex_create();
#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)))
    usb_fw_ptr->ext_req_to_host = (uint8_t*)(&g_usb_dev_data[usb_dev_ptr->dev_index].control_out);
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    usb_fw_ptr->ext_req_to_host = (uint8_t*)g_usb_dev_data_ptr[usb_dev_ptr->dev_index]->control_out;
#endif

    for (i= 0; i < MAX_DEVICE_SERVICE_NUMBER; i++)
    {
        usb_dev_ptr->services[i].type = (uint8_t)-1;
    }

    _usb_device_get_DCI(controller_id, &dev_if);

    if(dev_if == NULL)
    {
        _usb_device_release_handle(usb_dev_ptr);
        //OS_Unlock();
        return USBERR_DEVICE_NOT_FOUND;
    }

    usb_dev_ptr->usb_dev_interface = dev_if;

#if USBCFG_DEV_USE_TASK
    /* The _lwmsgq_init accepts the size of ISR_MSG_STRUCT as a multiplier of sizeof(_mqx_max_type) */
    usb_dev_ptr->usb_dev_service_que = (os_msgq_handle)OS_MsgQ_create(USBCFG_DEV_SERVICE_MSG_CNT, MSG_SIZE_IN_MAX_TYPE);
    _usb_dev_task_create(usb_dev_ptr);
#endif

    //OS_Unlock();
    /* Initialize the USB interface. */
    if (dev_if->dev_preint != NULL)
    {
        error = dev_if->dev_preint(usb_dev_ptr, (usb_device_handle *) (&usb_dev_ptr->controller_handle));
    }

    if (usb_dev_ptr->controller_handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("1 memalloc failed in usb_device_init\n");
#endif  
        return USBERR_ALLOC_STATE;
    } /* Endif */
    usb_fw_ptr->controller_handle = usb_dev_ptr->controller_handle;
    usb_fw_ptr->dev_handle = usb_dev_ptr;
#ifndef USBCFG_OTG
    error = bsp_usb_dev_init(controller_id);
#if USBCFG_DEV_KHCI && USBCFG_DEV_DETACH_ENABLE && USBCFG_DEV_IO_DETACH_ENABLE
    error = bsp_usb_detach_init(controller_id);
#endif
#else
    error = bsp_usb_otg_dev_init(controller_id);
#endif
    if (error != USB_OK)
    {
        if (dev_if->dev_shutdown != NULL)
        {
            dev_if->dev_shutdown(usb_dev_ptr->controller_handle);
        }
        return USBERR_UNKNOWN_ERROR;
    }

    /* Initialize the USB controller chip */
    if (dev_if->dev_init != NULL)
    {
        error = dev_if->dev_init(controller_id,usb_dev_ptr->controller_handle);
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_init: DEV_INIT is NULL\n");
#endif  
        return USBERR_ERROR;
    }

    if (error)
    {
        if (dev_if->dev_shutdown != NULL)
        {
            dev_if->dev_shutdown(usb_dev_ptr->controller_handle);
        }
        return USBERR_INIT_FAILED;
    } /* Endif */

    *handle = usb_dev_ptr;
    return error;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_postinit
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Initializes the USB device specific data structures and calls 
 *  the low-level device controller chip initialization routine.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_postinit
(
      /* [IN] the USB device controller to initialize */
      uint8_t controller_id,
      /* [OUT] the USB_USB_dev_initialize state structure */
      usb_device_handle  handle
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    usb_status error = 0;

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;
    if ((usb_dev_ptr->usb_dev_interface)->dev_postinit != NULL)
    {
        error = (usb_dev_ptr->usb_dev_interface)->dev_postinit(controller_id, handle);
    }
    return error;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_deinit
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *  uninitializes the USB device specific data structures and calls 
 *  the low-level device controller chip initialization routine.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_deinit
(
    /* [OUT] the USB_USB_dev_initialize state structure */
    usb_device_handle  handle
)
{
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    uint32_t i;
#endif
    usb_dev_state_struct_t* usb_dev_ptr;
    //usb_class_fw_object_struct_t* usb_fw_ptr = NULL;
    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("_usb_device_shutdowna: handle is NULL\n");
#endif  
        return USBERR_ERROR;
    }

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    OS_Mutex_destroy(usb_dev_ptr->mutex);
    _usb_device_shutdown(handle);

    _usb_device_release_handle(usb_dev_ptr);

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    for(i = 0; i < USBCFG_DEV_NUM; i++)
    {
        if(NULL != g_usb_dev_data_ptr[i])
        {
            OS_Mem_free(g_usb_dev_data_ptr[i]);
            g_usb_dev_data_ptr[i] = NULL;
        }
    }
#endif

    return USB_OK;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_init_endpoint
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *     Initializes the endpoint and the data structures associated with the 
 *  endpoint
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_init_endpoint
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle         handle,
    /* [IN] the endpoint structure, include members such as endpoint number, 
     * endpoint type, endpoint direction and the max packet size 
     */                  
    usb_ep_struct_t*          ep_ptr, 
    /* [IN] After all data is transfered, should we terminate the transfer
     * with a zero length packet if the last packet size == MAX_PACKET_SIZE?
     */
    uint8_t                    flag
)
{
    usb_status error = 0;
    usb_dev_state_struct_t* usb_dev_ptr;
    struct xd_struct xd;
    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("_usb_device_shutdowna: handle is NULL\n");
#endif  
        return USBERR_ERROR;
    }

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    /* Initialize the transfer descriptor */
    xd.ep_num = ep_ptr->ep_num;
    xd.bdirection = ep_ptr->direction;
    xd.wmaxpacketsize = (uint16_t)(ep_ptr->size & 0x0000FFFF);
    xd.ep_type = ep_ptr->type;
    xd.dont_zero_terminate = flag;
    xd.wtotallength = 0;
    xd.wsofar = 0;

    if ((usb_dev_ptr->usb_dev_interface)->dev_init_endoint != NULL)
    {
        error=(usb_dev_ptr->usb_dev_interface)->dev_init_endoint(usb_dev_ptr->controller_handle, &xd);
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_init_endpoint: DEV_INIT_ENDPOINT is NULL\n");
#endif  
        return USBERR_ERROR;
    }

    return error;
} /* EndBody */

/*FUNCTION*----------------------------------------------------------------
 * 
 * Function Name  : usb_device_register_service
 * Returned Value : USB_OK or error code
 * Comments       :
 *     Registers a callback routine for a specified event or endpoint.
 * 
 *END*--------------------------------------------------------------------*/
usb_status usb_device_register_service
(
    /* [IN] Handle to the USB device */
    usb_device_handle          handle,
    /* [IN] type of event or endpoint number to service */
    uint8_t                    type,
    /* [IN] Pointer to the service's callback function */
    usb_event_service_t        service,
    /*[IN] User Argument to be passed to Services when invoked.*/
    void*                      arg
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    service_struct_t* service_ptr;
    uint32_t i;

    if (handle == NULL)
    {
        return USBERR_ERROR;
    }
    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    OS_Mutex_lock(usb_dev_ptr->mutex);

    for (i = 0; i < MAX_DEVICE_SERVICE_NUMBER; i++)
    {
        service_ptr = &usb_dev_ptr->services[i];
        if (service_ptr->type == type)
        {
            OS_Mutex_unlock(usb_dev_ptr->mutex);
            return USBERR_OPEN_SERVICE;
        }
    }

    for (i = 0; i < MAX_DEVICE_SERVICE_NUMBER; i++)
    {
        service_ptr = &usb_dev_ptr->services[i];
        if (service_ptr->type == (uint8_t)-1)
        {
            service_ptr->type = type;
            service_ptr->service = service;
            service_ptr->arg = arg;
            OS_Mutex_unlock(usb_dev_ptr->mutex);
            return USB_OK;
        }
    }

    OS_Mutex_unlock(usb_dev_ptr->mutex);
    return USBERR_ALLOC;
} /* EndBody */

/*FUNCTION*----------------------------------------------------------------
 * 
 * Function Name  : usb_device_unregister_service
 * Returned Value : USB_OK or error code
 * Comments       :
 *     Unregisters a callback routine for a specified event or endpoint.
 * 
 *END*--------------------------------------------------------------------*/
usb_status usb_device_unregister_service
(
    /* [IN] Handle to the USB device */
    usb_device_handle           handle,
    /* [IN] type of event or endpoint number to service */
    uint8_t                     type
)
{ /* Body */
    usb_dev_state_struct_t* usb_dev_ptr;
    service_struct_t* service_ptr;
    uint32_t i;

    if (handle == NULL)
    {
        return USBERR_ERROR;
    }

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;
    /* Needs mutual exclusion */
    OS_Mutex_lock(usb_dev_ptr->mutex);

    for (i = 0; i < MAX_DEVICE_SERVICE_NUMBER; i++)
    {
        service_ptr = &usb_dev_ptr->services[i];
        if (service_ptr->type == type)
        {
            service_ptr->type = (uint8_t)-1;
            service_ptr->service = NULL;
            service_ptr->arg = NULL;
            OS_Mutex_unlock(usb_dev_ptr->mutex);
            return USB_OK;
        }
    }

    OS_Mutex_unlock(usb_dev_ptr->mutex);
    return USBERR_CLOSED_SERVICE;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_deinit_endpoint
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *  Disables the endpoint and the data structures associated with the 
 *  endpoint
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_deinit_endpoint
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle         handle,
    /* [IN] the Endpoint number */
    uint8_t                    ep_num,
    /* [IN] Direction */
    uint8_t                    direction
)
{
    uint8_t error = 0;
    usb_dev_state_struct_t* usb_dev_ptr;

    if (handle == NULL)
    {
        return USBERR_ERROR;
    }

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;
    OS_Mutex_lock(usb_dev_ptr->mutex);

    if ((usb_dev_ptr->usb_dev_interface)->dev_deinit_endoint != NULL)
    {
        error = (usb_dev_ptr->usb_dev_interface)->dev_deinit_endoint(usb_dev_ptr->controller_handle,
        ep_num, direction);
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_deinit_endpoint: DEV_DEINIT_ENDPOINT is NULL\n");
#endif  
        return USBERR_ERROR;
    }

    OS_Mutex_unlock(usb_dev_ptr->mutex);
    return error;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_recv_data
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Receives data on a specified endpoint.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_recv_data
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle           handle,
    /* [IN] the Endpoint number */
    uint8_t                     ep_num,
    /* [IN] buffer to receive data */
    uint8_t *                   buff_ptr,
    /* [IN] length of the transfer */
    uint32_t                    size
)
{
    usb_status error = USB_OK;
    xd_struct_t* xd_ptr;
    usb_dev_state_struct_t* usb_dev_ptr;

    if (handle == NULL)
    {
        return USBERR_ERROR;
    }

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;
    if ((usb_dev_ptr->usb_dev_interface)->dev_get_xd != NULL)
    {
        error = (usb_dev_ptr->usb_dev_interface)->dev_get_xd(usb_dev_ptr->controller_handle, &xd_ptr);

        if (USB_OK != error)
        {
#if _DEBUG
            USB_PRINTF("usb_device_recv_data: DEV_GET_XD failed\n");
#endif
            return USBERR_ERROR;
        }
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_recv_data: DEV_GET_XD is NULL\n");
#endif  
        return USBERR_ERROR;
    }

    OS_Mutex_lock(usb_dev_ptr->mutex);

    /* Initialize the new transfer descriptor */
    xd_ptr->ep_num = ep_num;
    xd_ptr->bdirection = USB_RECV;
    xd_ptr->wtotallength = size;
    xd_ptr->wstartaddress = buff_ptr;
    xd_ptr->wsofar = 0;
    xd_ptr->bstatus = USB_STATUS_TRANSFER_ACCEPTED;

    if ((usb_dev_ptr->usb_dev_interface)->dev_recv != NULL)
    {

#if (USBCFG_DEV_BUFF_PROPERTY_CACHEABLE)  
        if (size > 0)
        {
            OS_dcache_invalidate_mlines((void*)buff_ptr, size);
        }
#endif 
        error = (usb_dev_ptr->usb_dev_interface)->dev_recv(usb_dev_ptr->controller_handle, xd_ptr);
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_recv_data: DEV_RECV is NULL\n");
#endif
        OS_Mutex_unlock(usb_dev_ptr->mutex);
        return USBERR_ERROR;
    }

    OS_Mutex_unlock(usb_dev_ptr->mutex);
    if (error)
    {
        return USBERR_RX_FAILED;
    } /* Endif */

    return error;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_send_data
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Sends data on a specified endpoint.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_send_data
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle           handle,
    /* [IN] the Endpoint number */
    uint8_t                    ep_num,
    /* [IN] buffer to send */
    uint8_t *                  buff_ptr,
    /* [IN] length of the transfer */
    uint32_t                   size
)
{ /* Body */
    usb_status error;
    xd_struct_t* xd_ptr;
    usb_dev_state_struct_t* usb_dev_ptr;

    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("usb_device_send_data: handle is NULL\n");
#endif  
        return USBERR_ERROR;
    }

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    if ((usb_dev_ptr->usb_dev_interface)->dev_get_xd != NULL)
    {
        error = (usb_dev_ptr->usb_dev_interface)->dev_get_xd(usb_dev_ptr->controller_handle, &xd_ptr);

        if (USB_OK != error)
        {
#if _DEBUG
            USB_PRINTF("usb_device_send_data: DEV_GET_XD failed\n");
#endif
            return USBERR_ERROR;
        }
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_send_data: DEV_GET_XD is NULL\n");
#endif  
        return USBERR_ERROR;
    }

    OS_Mutex_lock(usb_dev_ptr->mutex);

    /* Initialize the new transfer descriptor */
    xd_ptr->ep_num = ep_num;
    xd_ptr->bdirection = USB_SEND;
    xd_ptr->wtotallength = size;
    xd_ptr->wstartaddress = buff_ptr;
    xd_ptr->wsofar = 0;
    xd_ptr->bstatus = USB_STATUS_TRANSFER_ACCEPTED;

    if ((usb_dev_ptr->usb_dev_interface)->dev_send != NULL)
    {
#if (USBCFG_DEV_BUFF_PROPERTY_CACHEABLE)  
        if (size > 0)
        {
            /********************************************************
             If system has a data cache, it is assumed that buffer
             passed to this routine will be aligned on a cache line
             boundary. The following code will flush the
             buffer before passing it to hardware driver.   
             ********************************************************/
            OS_dcache_flush_mlines((void*)buff_ptr, size);
        }
#endif 
        error = (usb_dev_ptr->usb_dev_interface)->dev_send(usb_dev_ptr->controller_handle, xd_ptr);
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_send_data: DEV_SEND is NULL\n");
#endif
        OS_Mutex_unlock(usb_dev_ptr->mutex);
        return USBERR_ERROR;
    }

    OS_Mutex_unlock(usb_dev_ptr->mutex);
    if (error)
    {
#if _DEBUG
        USB_PRINTF("usb_device_send_data, transfer failed\n");
#endif  
        return USBERR_TX_FAILED;
    }
    return error;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_unstall_endpoint
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *     Unstalls the endpoint in specified direction
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_unstall_endpoint
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle          handle,
    /* [IN] the Endpoint number */
    uint8_t                    ep_num,
    /* [IN] direction */
    uint8_t                    direction
)
{
    usb_status error = USB_OK;
    usb_dev_state_struct_t* usb_dev_ptr;

    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("usb_device_unstall_endpoint: handle is NULL\n");
#endif    
        return USBERR_ERROR;
    }

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    OS_Mutex_lock(usb_dev_ptr->mutex);

    if ((usb_dev_ptr->usb_dev_interface)->dev_unstall_endpoint != NULL)
    {
        error= (usb_dev_ptr->usb_dev_interface)->dev_unstall_endpoint(usb_dev_ptr->controller_handle, ep_num, direction);
    }
    else
    {
        OS_Mutex_unlock(usb_dev_ptr->mutex);
        return USBERR_ERROR;
    }
    OS_Mutex_unlock(usb_dev_ptr->mutex);
    return error;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_stall_endpoint
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *     Stalls the endpoint.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_stall_endpoint
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle          handle,
    /* [IN] the Endpoint number */
    uint8_t                    ep_num,
    /* [IN] direction */
    uint8_t                    direction
)
{
    usb_status error = 0;
    usb_dev_state_struct_t* usb_dev_ptr;

    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("usb_device_stall_endpoint: handle is NULL\n");
#endif    
        return USBERR_ERROR;
    }
    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    if ((usb_dev_ptr->usb_dev_interface)->dev_stall_endpoint
    != NULL)
    {
        error = (usb_dev_ptr->usb_dev_interface)->dev_stall_endpoint(usb_dev_ptr->controller_handle,
        ep_num, direction);
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_stall_endpoint: DEV_STALL_ENDPOINT is NULL\n");
#endif  
        error = USBERR_ERROR;
    }

    return error;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_register_application_notify
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Process Resume event
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_register_application_notify
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle         handle,
    usb_device_notify_t       device_notify_callback,
    void*                     device_notify_param
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    usb_status error = USB_OK;

    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("usb_device_register_application_notify: handle is NULL\n");
#endif    
        return USBERR_ERROR;
    }
    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    usb_dev_ptr->usb_framework.device_notify_callback = device_notify_callback;
    usb_dev_ptr->usb_framework.device_notify_param = device_notify_param;
    return error;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_register_vendor_class_request_notify
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Process Resume event
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_register_vendor_class_request_notify
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle         handle,
    usb_request_notify_t      request_notify_callback,
    void*                     request_notify_param
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    usb_status error = USB_OK;

    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("usb_device_register_vendor_class_request_notify: handle is NULL\n");
#endif    
        return USBERR_ERROR;
    }
    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    usb_dev_ptr->usb_framework.request_notify_callback = request_notify_callback;
    usb_dev_ptr->usb_framework.request_notify_param = request_notify_param;

    return error;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_register_desc_request_notify
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_register_desc_request_notify
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle              handle,
    usb_desc_request_notify_struct_t*  desc_request_notify_callback,
    void*                           desc_request_notify_param
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    usb_status error = USB_OK;

    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("usb_device_register_desc_request_notify\n");
#endif    
        return USBERR_ERROR;
    }
    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    usb_dev_ptr->usb_framework.desc_notify_callback = desc_request_notify_callback;
    usb_dev_ptr->usb_framework.desc_notify_param = desc_request_notify_param;

    return error;
}
#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE
/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_cancel_transfer
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        returns the status of the transaction on the specified endpoint.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_cancel_transfer
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle         handle,
    /* [IN] the Endpoint number */
    uint8_t                     ep_num,
    /* [IN] direction */
    uint8_t                     direction
)
{
    uint8_t error = USB_OK;
    usb_dev_state_struct_t* usb_dev_ptr;
    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("_usb_device_shutdowna: handle is NULL\n");
#endif  
        return USBERR_ERROR;
    }

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;
    OS_Mutex_lock(usb_dev_ptr->mutex);

    /* Cancel transfer on the specified endpoint for the specified 
     ** direction 
     */
    if ((usb_dev_ptr->usb_dev_interface)->dev_cancel_transfer != NULL)
    {
        error = (usb_dev_ptr->usb_dev_interface)->dev_cancel_transfer(usb_dev_ptr->controller_handle,
        ep_num, direction);
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_cancel_transfer: dev_cancel_transfer is NULL\n");
#endif
        OS_Mutex_unlock(usb_dev_ptr->mutex);
        return USBERR_ERROR;
    }

    OS_Mutex_unlock(usb_dev_ptr->mutex);

    return error;
}
#endif

#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME
/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_process_resume
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Process Resume event
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_assert_resume
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle         handle
)
{
    usb_dev_state_struct_t* usb_dev_ptr;
    usb_status error = USB_OK;

    if (handle == NULL)
    {
#if _DEBUG
        USB_PRINTF("usb_device_assert_resume: handle is NULL\n");
#endif    
        return USBERR_ERROR;
    }
    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    if ((usb_dev_ptr->usb_dev_interface)->dev_assert_resume != NULL)
    {
        error= (usb_dev_ptr->usb_dev_interface)->dev_assert_resume(usb_dev_ptr->controller_handle);
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_assert_resume: dev_assert_resume is NULL\n");
#endif  
        error = USBERR_ERROR;
    }

    return error;
}
#endif

#ifdef USBCFG_OTG
/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_otg_init
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Process Resume event
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_otg_init
(
    usb_device_handle handle, 
    uint8_t     otg_attributes
)
{
    usb_status error;
    usb_khci_dev_state_struct_t* khci_dev_state_ptr;
    if (handle == NULL)
    {
        return USBERR_ERROR;
    }
    khci_dev_state_ptr = (usb_khci_dev_state_struct_t*)((usb_dev_state_struct_t*)handle)->controller_handle;
    khci_dev_state_ptr->otg_attr_srp = (otg_attributes & OTG_SRP_SUPPORT)?(TRUE):(FALSE);
    khci_dev_state_ptr->otg_attr_hnp = (otg_attributes & OTG_HNP_SUPPORT)?(TRUE):(FALSE);
    error = usb_otg_device_on_class_init(khci_dev_state_ptr->otg_handle, handle , otg_attributes );

    return error;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_otg_get_hnp_support
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Process Resume event
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_otg_get_hnp_support
(
    usb_device_handle handle, 
    uint8_t*    hnp_support_ptr 
)
{
    usb_khci_dev_state_struct_t* khci_dev_state_ptr;

    if (handle == NULL)
    {
        *hnp_support_ptr = 0;
        return USBERR_ERROR;
    }
    khci_dev_state_ptr = (usb_khci_dev_state_struct_t*)((usb_dev_state_struct_t*)handle)->controller_handle;
    *hnp_support_ptr = khci_dev_state_ptr->otg_attr_hnp;
    return USB_OK;
}

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_otg_set_hnp_enable
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        Process Resume event
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_otg_set_hnp_enable
(
    usb_device_handle handle
)
{
    usb_khci_dev_state_struct_t* khci_dev_state_ptr;
    if (handle == NULL)
    {
        return USBERR_ERROR;
    }
    khci_dev_state_ptr = (usb_khci_dev_state_struct_t*)((usb_dev_state_struct_t*)handle)->controller_handle;
    return usb_otg_device_hnp_enable(khci_dev_state_ptr->otg_handle, TRUE);
}
#endif /* USBCFG_OTG */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_device_reset
 *  Returned Value : USB_OK or error code
 *  Comments       :
 *        reset device.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_device_reset
(
    /* [IN] the USB_USB_dev_initialize state structure */
    usb_device_handle           handle
)
{
    usb_status error = USB_OK;
    usb_dev_state_struct_t* usb_dev_ptr;

    if (handle == NULL)
    {
        return USBERR_ERROR;
    }

    usb_dev_ptr = (usb_dev_state_struct_t*)handle;

    if ((usb_dev_ptr->usb_dev_interface)->dev_reset != NULL)
    {
        error = (usb_dev_ptr->usb_dev_interface)->dev_reset(usb_dev_ptr->controller_handle);
    }
    else
    {
#if _DEBUG
        //USB_PRINTF("usb_device_reset: dev_reset is NULL\n");
#endif    
        return USBERR_ERROR;
    }

    return error;
} /* EndBody */
#endif
