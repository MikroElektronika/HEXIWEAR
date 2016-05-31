/**HEADER********************************************************************
 *
 * Copyright (c) 2008, 2013 - 2015 Freescale Semiconductor;
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
 * $FileName: usb_cdc.c$
 * $Version :
 * $Date    :
 *
 *
 * @brief The file contains CDC layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"

#if USBCFG_DEV_CDC
#include "usb_class_internal.h"
#include "usb_class_cdc.h"
#include "usb_cdc.h"
#include "usb_cdc_pstn.h"
/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
cdc_device_struct_t cdc_device_array[MAX_CDC_DEVICE];

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
uint8_t USB_Map_Ep_To_Struct_Index(cdc_device_struct_t * cdc_obj_ptr, uint8_t ep_num);
static usb_status USB_Cdc_Allocate_Handle(cdc_handle_t* handle);
static usb_status USB_Cdc_Free_Handle(cdc_handle_t handle);
/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/
#if CDC_IMPLEMENT_QUEUING
/*************************************************************************//*!
 *
 * @name  USB_Cdc_Ep_Mutex_Lock
 *
 * @brief The function locks the mutex for RTOS. For BM, disable interrupt.
 *
 * @param none.
 * @return none.
 *
 *****************************************************************************/
void USB_Cdc_Ep_Mutex_Lock(cdc_device_struct_t * cdc_obj_ptr, uint32_t ep_num)
{
    uint8_t index, type, direction;

    index = USB_Map_Ep_To_Struct_Index(cdc_obj_ptr, ep_num);
    type = cdc_obj_ptr->ep[index].type;
    direction = cdc_obj_ptr->ep[index].direction;
#if (((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK) && (USE_RTOS)) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX))
    switch(type)
    {
    case USB_BULK_PIPE:
        if(direction == USB_SEND)
        {
            OS_Mutex_lock(cdc_obj_ptr->send_mutex);
        }
        else if(direction == USB_RECV)
        {
            OS_Mutex_lock(cdc_obj_ptr->recv_mutex);
        }
        break;
    case USB_INTERRUPT_PIPE:
        break;
    default:
        break;
    }
#else
    OS_Lock();
#endif

}

/*************************************************************************//*!
 *
 * @name  USB_Cdc_Ep_Mutex_Unlock
 *
 * @brief The function unlocks the mutex for RTOS. For BM, enable interrupt.
 *
 * @param none.
 * @return none.
 *
 *****************************************************************************/
void USB_Cdc_Ep_Mutex_Unlock(cdc_device_struct_t * cdc_obj_ptr, uint8_t ep_num)
{
    uint8_t index, type, direction;

    index = USB_Map_Ep_To_Struct_Index(cdc_obj_ptr, ep_num);
    type = cdc_obj_ptr->ep[index].type;
    direction = cdc_obj_ptr->ep[index].direction;
#if (((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK) && (USE_RTOS)) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX))
    switch(type)
    {
    case USB_BULK_PIPE:
        if(direction == USB_SEND)
        {
            OS_Mutex_unlock(cdc_obj_ptr->send_mutex);
        }
        else if(direction == USB_RECV)
        {
            OS_Mutex_unlock(cdc_obj_ptr->recv_mutex);
        }
        break;
    case USB_INTERRUPT_PIPE:
        break;
    default:
        break;
    }
#else
    OS_Unlock();
#endif

}

/*************************************************************************//*!
 *
 * @name  USB_Cdc_Mutex_Lock
 *
 * @brief The function locks the mutex for RTOS. For BM, disable interrupt.
 *
 * @param none.
 * @return none.
 *
 *****************************************************************************/
void USB_Cdc_Mutex_Lock(os_mutex_handle handle)
{
#if (((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK) && (USE_RTOS)) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX))
    OS_Mutex_lock(handle);
#else
    OS_Lock();
#endif

}

/*************************************************************************//*!
 *
 * @name  USB_Cdc_Mutex_Unlock
 *
 * @brief The function unlocks the mutex for RTOS. For BM, enable interrupt.
 *
 * @param none.
 * @return none.
 *
 *****************************************************************************/
void USB_Cdc_Mutex_Unlock(os_mutex_handle handle)
{
#if (((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK) && (USE_RTOS)) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX))
    OS_Mutex_unlock(handle);
#else
    OS_Unlock();
#endif

}
#endif
/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/
/*************************************************************************//*!
 *
 * @name  USB_Cdc_Allocate_Handle
 *
 * @brief The function reserves entry in device array and returns the index.
 *
 * @param none.
 * @return returns the reserved handle or if no entry found device busy.
 *
 *****************************************************************************/
static usb_status USB_Cdc_Allocate_Handle(cdc_handle_t* handle)
{
    uint32_t cnt = 0;
    for (; cnt < MAX_CDC_DEVICE; cnt++)
    {
        if (cdc_device_array[cnt].controller_handle == NULL)
        {
            *handle = (cdc_handle_t)&cdc_device_array[cnt];
            return USB_OK;
        }
    }
    return USBERR_DEVICE_BUSY;
}
/*************************************************************************//*!
 *
 * @name  USB_Cdc_Free_Handle
 *
 * @brief The function releases entry in device array .
 *
 * @param handle  index in device array to be released..
 * @return returns and error code or USB_OK.
 *
 *****************************************************************************/

static usb_status USB_Cdc_Free_Handle(cdc_handle_t handle)
{
    int32_t cnt = 0;
    for (; cnt < MAX_CDC_DEVICE; cnt++)
    {
        if (((cdc_handle_t)&cdc_device_array[cnt]) == handle)
        {
            OS_Mem_zero((void * )handle, sizeof(cdc_device_struct_t));
            return USB_OK;
        }
    }

    return USBERR_INVALID_PARAM;
}

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

/*************************************************************************//*!
 *
 * @name  USB_Cdc_Get_Desc_Info
 *
 * @brief The function gets the info of the descriptors. .
 *
 * @param handle  index in device array.
 * @param type     descriptor type.
 * @param object   store the returned value.
 * @return returns USB_OK if successful.
 *
 *****************************************************************************/
usb_status USB_Cdc_Get_Desc_Info(cdc_device_struct_t * cdc_obj_ptr, USB_DESC_INFO_T type, uint32_t * object)
{
    usb_class_struct_t* usbclassPtr;
    usb_interfaces_struct_t * ifs_ptr;
    /* Get class info */
#if USBCFG_DEV_COMPOSITE
    usb_composite_info_struct_t* usbcompinfoPtr;
    uint32_t interface_index;
    cdc_obj_ptr->desc_callback.get_desc_entity((uint32_t)cdc_obj_ptr->controller_handle,
    USB_COMPOSITE_INFO,
    (uint32_t *)&usbcompinfoPtr);
    cdc_obj_ptr->desc_callback.get_desc_entity((uint32_t)cdc_obj_ptr,
    USB_CLASS_INTERFACE_INDEX_INFO,
    (uint32_t *)&interface_index);
#else
    cdc_obj_ptr->desc_callback.get_desc_entity((uint32_t)cdc_obj_ptr->controller_handle,
        USB_CLASS_INFO,
        (uint32_t *)&usbclassPtr);
#endif
    switch(type)
    {
    case USB_EP_COUNT:
        case USB_CDC_EP_COUNT:
        {
        uint32_t ep_cnt = 0;
#if USBCFG_DEV_COMPOSITE
        if ((interface_index < usbcompinfoPtr->count) && (usbcompinfoPtr->class_handle[interface_index].type == USB_CLASS_CDC))
        {
            usbclassPtr = &(usbcompinfoPtr->class_handle[interface_index]);
        }
        else
        {
            *object = 0;
            break;
        }
#endif
        ifs_ptr = &usbclassPtr->interfaces;
        for (uint8_t if_index = 0; if_index < ifs_ptr->count; if_index++)
        {
            ep_cnt += ifs_ptr->interface[if_index].endpoints.count;
        }
        *object = ep_cnt;
        break;
    }
    case USB_INTERFACE_COUNT:
        case USB_CDC_INTERFACE_COUNT:
        {
#if USBCFG_DEV_COMPOSITE
        if ((interface_index < usbcompinfoPtr->count) && (usbcompinfoPtr->class_handle[interface_index].type == USB_CLASS_CDC))
        {
            usbclassPtr = &(usbcompinfoPtr->class_handle[interface_index]);
        }
        else
        {
            *object = 0;
            break;
        }
#endif
        ifs_ptr = &usbclassPtr->interfaces;
        *object = ifs_ptr->count;
        break;
    }
    default:
        break;
    }
    return USB_OK;
}
/**************************************************************************//*!
 *
 * @name  USB_Map_Ep_To_Struct_Index
 *
 * @brief The function maps the endpoint num to the index of the ep data
 *           structure
 *
 * @param handle          handle to identify the controller
 * @param ep_num          endpoint num
 *
 * @return index          mapped index
 *
 *****************************************************************************/
uint8_t USB_Map_Ep_To_Struct_Index(cdc_device_struct_t * cdc_obj_ptr, uint8_t ep_num)
{
    uint8_t index = 0;
    uint32_t ep_count;

    USB_Cdc_Get_Desc_Info(cdc_obj_ptr, USB_EP_COUNT, &ep_count);
    /* map the endpoint num to the index of the endpoint structure */
    for (index = 0; index < ep_count; index++)
    {
        if (cdc_obj_ptr->ep[index].endpoint == ep_num)
        {
            break;
        }
    }
    return index;
}

/**************************************************************************//*!
 *
 * @name  USB_Service_Cdc_Notif
 *
 * @brief The function ic callback function of CIC Notification endpoint
 *
 * @param event
 *
 * @return None
 *
 *****************************************************************************/
void USB_Service_Cdc_Notif(usb_event_struct_t* event, void* arg)
{
    cdc_device_struct_t * cdc_obj_ptr = (cdc_device_struct_t *)arg;
#if CDC_IMPLEMENT_QUEUING
    uint8_t index;
    uint8_t producer, consumer;
//        usb_endpoints_t *usb_ep_data = cdc_obj_ptr->usb_ep_data;

    cdc_queue_struct_t queue;
    usb_status status = USB_OK;
#endif

    //UNUSED_ARGUMENT (event)

#if CDC_IMPLEMENT_QUEUING
    /* map the endpoint num to the index of the endpoint structure */
    index = USB_Map_Ep_To_Struct_Index(cdc_obj_ptr, event->ep_num);

    USB_Cdc_Ep_Mutex_Lock(cdc_obj_ptr, event->ep_num);
    producer = cdc_obj_ptr->ep[index].bin_producer;
    consumer = cdc_obj_ptr->ep[index].bin_consumer;

    /* No pending transfer */
    if(producer == consumer)
    {
        return;
    }
    /* if there are no errors de-queue the queue and decrement the no. of
     transfers left, else send the same data again */
    cdc_obj_ptr->ep[index].bin_consumer++;
    consumer = cdc_obj_ptr->ep[index].bin_consumer;
    while(consumer != producer)
    {
        queue = cdc_obj_ptr->ep[index].queue[consumer%CDC_MAX_QUEUE_ELEMS];
        status = USB_Class_Send_Data(cdc_obj_ptr->class_handle, queue.channel,
        queue.app_data.data_ptr, queue.app_data.data_size);
        if(USB_OK == status)
        {
            break;
        }
        else
        {

            USB_Cdc_Ep_Mutex_Unlock(cdc_obj_ptr, event->ep_num);
            if(cdc_obj_ptr->class_specific_callback.callback != NULL)
            {
                uint8_t event_type = USB_APP_CDC_SERIAL_STATE_NOTIF;
                event->len = 0xFFFFFFFF;
                cdc_obj_ptr->class_specific_callback.callback(event_type,
                USB_REQ_VAL_INVALID,
                NULL,
                &(event->len),
                cdc_obj_ptr->class_specific_callback.arg);
            }
            USB_Cdc_Ep_Mutex_Lock(cdc_obj_ptr, event->ep_num);
            producer = cdc_obj_ptr->ep[index].bin_producer;
            cdc_obj_ptr->ep[index].bin_consumer++;
            consumer = cdc_obj_ptr->ep[index].bin_consumer;
        }
    }
    USB_Cdc_Ep_Mutex_Unlock(cdc_obj_ptr, event->ep_num);
#endif

    cdc_obj_ptr->has_sent_state = FALSE;
    if (cdc_obj_ptr->class_specific_callback.callback != NULL)
    {
        uint8_t event_type = USB_APP_CDC_SERIAL_STATE_NOTIF;
        cdc_obj_ptr->class_specific_callback.callback(event_type,
        USB_REQ_VAL_INVALID,
        NULL,
        NULL,
            cdc_obj_ptr->class_specific_callback.arg);
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Service_Dic_Bulk_In
 *
 * @brief The function ic callback function of DIC Bulk In Endpoint
 *
 * @param event
 *
 * @return None
 *
 *****************************************************************************/
void USB_Service_Dic_Bulk_In(usb_event_struct_t* event, void* arg)
{
    uint8_t event_type;
    cdc_device_struct_t * cdc_obj_ptr = (cdc_device_struct_t *)arg;

    //if(USB_UNINITIALIZED_VAL_32 == event->len) return;
#if CDC_IMPLEMENT_QUEUING
    uint8_t index;
    uint8_t producer, consumer;
//        usb_endpoints_t *usb_ep_data = cdc_obj_ptr->usb_ep_data;

    cdc_queue_struct_t queue;
    usb_status status = USB_OK;

    /* map the endpoint num to the index of the endpoint structure */
    index = USB_Map_Ep_To_Struct_Index(cdc_obj_ptr, event->ep_num);
    USB_Cdc_Ep_Mutex_Lock(cdc_obj_ptr, event->ep_num);
    producer = cdc_obj_ptr->ep[index].bin_producer;
    consumer = cdc_obj_ptr->ep[index].bin_consumer;

    /* No pending transfer */
    if(producer == consumer)
    {
        return;
    }
    /* if there are no errors de-queue the queue and decrement the no. of
     transfers left, else send the same data again */
    cdc_obj_ptr->ep[index].bin_consumer++;
    consumer = cdc_obj_ptr->ep[index].bin_consumer;

    while(consumer != producer)
    {
        queue = cdc_obj_ptr->ep[index].queue[consumer%CDC_MAX_QUEUE_ELEMS];

        status = USB_Class_Send_Data(cdc_obj_ptr->class_handle, queue.channel,
        queue.app_data.data_ptr, queue.app_data.data_size);
        if(USB_OK == status)
        {
            break;
        }
        else
        {
            USB_Cdc_Ep_Mutex_Unlock(cdc_obj_ptr, event->ep_num);
            if(cdc_obj_ptr->class_specific_callback.callback != NULL)
            {
                event_type = USB_DEV_EVENT_SEND_COMPLETE;
                event->len = 0xFFFFFFFF;
                cdc_obj_ptr->class_specific_callback.callback(event_type,
                USB_REQ_VAL_INVALID,
                &(event->buffer_ptr),
                &(event->len),
                cdc_obj_ptr->class_specific_callback.arg);
            }
            USB_Cdc_Ep_Mutex_Lock(cdc_obj_ptr, event->ep_num);
            producer = cdc_obj_ptr->ep[index].bin_producer;
            cdc_obj_ptr->ep[index].bin_consumer++;
            consumer = cdc_obj_ptr->ep[index].bin_consumer;
        }
    }
    USB_Cdc_Ep_Mutex_Unlock(cdc_obj_ptr, event->ep_num);
#endif

    if (cdc_obj_ptr->class_specific_callback.callback != NULL)
    {
        event_type = USB_DEV_EVENT_SEND_COMPLETE;
        cdc_obj_ptr->class_specific_callback.callback(event_type,
        USB_REQ_VAL_INVALID,
            &(event->buffer_ptr),
            &(event->len),
            cdc_obj_ptr->class_specific_callback.arg);
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Service_Dic_Bulk_Out
 *
 * @brief The function ic callback function of DIC Bulk Out Endpoint
 *
 * @param event
 *
 * @return None
 *
 *****************************************************************************/
void USB_Service_Dic_Bulk_Out(usb_event_struct_t* event, void* arg)
{
    uint8_t event_type;
    cdc_device_struct_t * cdc_obj_ptr = (cdc_device_struct_t *)arg;

    //if(USB_UNINITIALIZED_VAL_32 == event->len) return;
#if CDC_IMPLEMENT_QUEUING
    uint8_t index;
    uint8_t producer, consumer;

    cdc_queue_struct_t queue;
    usb_status status = USB_OK;

    /* map the endpoint num to the index of the endpoint structure */
    index = USB_Map_Ep_To_Struct_Index(cdc_obj_ptr, event->ep_num);
    USB_Cdc_Ep_Mutex_Lock(cdc_obj_ptr, event->ep_num);
    producer = cdc_obj_ptr->ep[index].bin_producer;
    consumer = cdc_obj_ptr->ep[index].bin_consumer;

    /* No pending transfer */
    if(producer == consumer)
    {
        return;
    }
    /* if there are no errors de-queue the queue and decrement the no. of
     transfers left, else send the same data again */
    cdc_obj_ptr->ep[index].bin_consumer++;
    consumer = cdc_obj_ptr->ep[index].bin_consumer;

    while(consumer != producer)
    {
        queue = cdc_obj_ptr->ep[index].queue[consumer%CDC_MAX_QUEUE_ELEMS];

        status = usb_device_recv_data(cdc_obj_ptr->controller_handle,
        queue.channel, queue.app_data.data_ptr, queue.app_data.data_size);
        if(USB_OK == status)
        {
            break;
        }
        else
        {
            USB_Cdc_Ep_Mutex_Unlock(cdc_obj_ptr, event->ep_num);
            if(cdc_obj_ptr->class_specific_callback.callback != NULL)
            {
                event_type = USB_DEV_EVENT_DATA_RECEIVED;
                event->len = 0xFFFFFFFF;
                cdc_obj_ptr->class_specific_callback.callback(event_type,
                USB_REQ_VAL_INVALID,
                &(event->buffer_ptr),
                &(event->len),
                cdc_obj_ptr->class_specific_callback.arg);
            }
            USB_Cdc_Ep_Mutex_Lock(cdc_obj_ptr, event->ep_num);
            producer = cdc_obj_ptr->ep[index].bin_producer;
            cdc_obj_ptr->ep[index].bin_consumer++;
            consumer = cdc_obj_ptr->ep[index].bin_consumer;
        }
    }
    USB_Cdc_Ep_Mutex_Unlock(cdc_obj_ptr, event->ep_num);
#endif
    if (cdc_obj_ptr->class_specific_callback.callback != NULL)
    {
        event_type = USB_DEV_EVENT_DATA_RECEIVED;
        cdc_obj_ptr->class_specific_callback.callback(event_type,
        USB_REQ_VAL_INVALID,
            &(event->buffer_ptr),
            &(event->len),
            cdc_obj_ptr->class_specific_callback.arg);
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Event
 *
 * @brief The function initializes CDC endpoints
 *
 * @param handle   handle to Identify the controller
 * @param event           pointer to event structure
 * @param val             gives the configuration value
 *
 * @return None
 *
 *****************************************************************************/
void USB_Class_CDC_Event(uint8_t event, void* val, void* arg)
{
#if USBCFG_DEV_COMPOSITE
    usb_composite_info_struct_t* usbcompinfoPtr;
    uint32_t interface_index = 0xFF;
#else
    usb_class_struct_t* usbclassPtr;
#endif
    cdc_device_struct_t * cdc_obj_ptr = NULL;
    cdc_obj_ptr = (cdc_device_struct_t *)arg;
    uint8_t index;
    if (event == USB_DEV_EVENT_CONFIG_CHANGED)
    {
#if CDC_RNDIS_SUPPORT
        uint32_t max_if_count;
#endif
        usb_ep_struct_t* ep_struct_ptr = NULL;
        /* Get class info */
#if USBCFG_DEV_COMPOSITE
        cdc_obj_ptr->desc_callback.get_desc_entity((uint32_t)cdc_obj_ptr->controller_handle,
        USB_COMPOSITE_INFO,
        (uint32_t*)&usbcompinfoPtr);
        cdc_obj_ptr->desc_callback.get_desc_entity((uint32_t)cdc_obj_ptr,
        USB_CLASS_INTERFACE_INDEX_INFO, (uint32_t *)&interface_index);
#else
        cdc_obj_ptr->desc_callback.get_desc_entity((uint32_t)cdc_obj_ptr->controller_handle,
            USB_CLASS_INFO,
            (uint32_t*)&usbclassPtr);
#endif
#if CDC_RNDIS_SUPPORT
        /* Get count of interfaces for a specific configuration */
        USB_Cdc_Get_Desc_Info(cdc_obj_ptr, USB_CDC_INTERFACE_COUNT, &max_if_count);
        cdc_obj_ptr->max_supported_interfaces = max_if_count;
#endif
        if (NULL != cdc_obj_ptr->ep)
        {
            index = 0;
#if USBCFG_DEV_COMPOSITE
            if ((interface_index < usbcompinfoPtr->count) && (usbcompinfoPtr->class_handle[interface_index].type == USB_CLASS_CDC))
            {
                for (int inter_index =0; inter_index < usbcompinfoPtr->class_handle[interface_index].interfaces.count; inter_index++)
                {
                    for (int ep_index = 0; ep_index < usbcompinfoPtr->class_handle[interface_index].interfaces.interface[inter_index].endpoints.count; ep_index++)
                    {
                        ep_struct_ptr = &usbcompinfoPtr->class_handle[interface_index].interfaces.interface[inter_index].endpoints.ep[ep_index];

#else
            for_each_ep_in_class_begin(ep_struct_ptr, usbclassPtr, USB_CLASS_CDC)
                                        {
#endif
                                cdc_obj_ptr->ep[index].endpoint = ep_struct_ptr->ep_num;
                                cdc_obj_ptr->ep[index].type = ep_struct_ptr->type;
                                cdc_obj_ptr->ep[index].direction = ep_struct_ptr->direction;
#if CDC_IMPLEMENT_QUEUING
                                cdc_obj_ptr->ep[index].bin_consumer = 0x00;
                                cdc_obj_ptr->ep[index].bin_producer = 0x00;
#endif
                                index++;
                            }
                            #if (!USBCFG_DEV_COMPOSITE)
                        for_each_ep_in_class_end()
                        #endif
#if USBCFG_DEV_COMPOSITE
                    }
                }
#endif
        }
        /* Initialize all non control endpoints */
#if USBCFG_DEV_COMPOSITE
        if ((interface_index < usbcompinfoPtr->count) && (usbcompinfoPtr->class_handle[interface_index].type == USB_CLASS_CDC))
        {
            for (int inter_index =0; inter_index < usbcompinfoPtr->class_handle[interface_index].interfaces.count; inter_index++)
            {
                for (int ep_index = 0; ep_index < usbcompinfoPtr->class_handle[interface_index].interfaces.interface[inter_index].endpoints.count; ep_index++)
                {
                    ep_struct_ptr = &usbcompinfoPtr->class_handle[interface_index].interfaces.interface[inter_index].endpoints.ep[ep_index];
#else
        for_each_ep_in_class_begin(ep_struct_ptr, usbclassPtr, USB_CLASS_CDC)
                                {
#endif
                            (void)usb_device_init_endpoint(cdc_obj_ptr->controller_handle,
                                ep_struct_ptr, TRUE);

                            /* register callback service for Non Control EndPoints */
                            switch(ep_struct_ptr->type)
                            {
                            case USB_INTERRUPT_PIPE:
                                (void)usb_device_register_service(cdc_obj_ptr->controller_handle,
                                    (uint8_t)((uint8_t)(USB_SERVICE_EP0 + ep_struct_ptr->ep_num) | ((uint8_t)(ep_struct_ptr->direction << 7))),
                                    USB_Service_Cdc_Notif, (void *)cdc_obj_ptr);
                                cdc_obj_ptr->cic_recv_endpoint = USB_CONTROL_ENDPOINT;
                                cdc_obj_ptr->cic_send_endpoint = ep_struct_ptr->ep_num;
                                cdc_obj_ptr->cic_send_pkt_size = ep_struct_ptr->size;
                                break;
                            case USB_BULK_PIPE:
                                if (ep_struct_ptr->direction == USB_RECV)
                                {
                                    (void)usb_device_register_service(cdc_obj_ptr->controller_handle,
                                        (uint8_t)((uint8_t)(USB_SERVICE_EP0 + ep_struct_ptr->ep_num) | ((uint8_t)(ep_struct_ptr->direction << 7))),
                                        USB_Service_Dic_Bulk_Out, (void *)cdc_obj_ptr);
                                    cdc_obj_ptr->dic_recv_endpoint = ep_struct_ptr->ep_num;
                                    cdc_obj_ptr->dic_recv_pkt_size = ep_struct_ptr->size;
                                }
                                else
                                {
                                    (void)usb_device_register_service(cdc_obj_ptr->controller_handle,
                                        (uint8_t)((uint8_t)(USB_SERVICE_EP0 + ep_struct_ptr->ep_num) | ((uint8_t)(ep_struct_ptr->direction << 7))),
                                        USB_Service_Dic_Bulk_In, (void *)cdc_obj_ptr);
                                    cdc_obj_ptr->dic_send_endpoint = ep_struct_ptr->ep_num;
                                    cdc_obj_ptr->dic_send_pkt_size = ep_struct_ptr->size;
                                }
                                break;
                            default:
                                break;
                            }
                        }
                        #if (!USBCFG_DEV_COMPOSITE)
                    for_each_ep_in_class_end()
                    #endif
#if USBCFG_DEV_COMPOSITE
                }
            }
#endif
    }
    else if (event == USB_DEV_EVENT_ENUM_COMPLETE)
    {
        /* To Do */
    }
#if CDC_RNDIS_SUPPORT
    else if(event == USB_DEV_EVENT_BUS_RESET)
    {
        uint8_t * data;
        uint32_t size;
        /* Cancel if there are any pending transfers */
        RNDIS_Halt_Command(cdc_obj_ptr);
        RNDIS_Reset_Command(cdc_obj_ptr, &data, &size);
    }
#endif
    if (cdc_obj_ptr->cdc_application_callback.callback != NULL)
    {
        cdc_obj_ptr->cdc_application_callback.callback(event,
            val, cdc_obj_ptr->cdc_application_callback.arg);
    }
}

/**************************************************************************//*!
 *
 * @name  USB_CDC_Other_Requests
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests
 *
 * @param handle
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : When Successful
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_CDC_Other_Requests
(
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size,
    void* arg
    )
{
    usb_status status;
    cdc_device_struct_t * cdc_obj_ptr = NULL;
    cdc_obj_ptr = (cdc_device_struct_t *)arg;
    status = USBERR_INVALID_REQ_TYPE;
    if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_POS) ==
    USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_CLASS)
    {
        /* class request so handle it here */
        status = USB_OK;
        /* call for class/subclass specific requests */
        switch(setup_packet->request)
        {
        case SEND_ENCAPSULATED_COMMAND:
            #if CDC_RNDIS_SUPPORT
            /* Pass the Remote NDIS Control Message supported by
             802.3 connectionless device to PSTN Layer */
            status = PSTN_Rndis_Message_Set(cdc_obj_ptr,setup_packet,data,size);
#endif
            *size = 0;
            break;
        case GET_ENCAPSULATED_RESPONSE:
            #if CDC_RNDIS_SUPPORT
            /* Get the Remote NDIS Control Message supported by
             802.3 connectionless device from  PSTN Layer */
            status = PSTN_Rndis_Message_Get(cdc_obj_ptr,setup_packet,data,size);
#else
            *size = 0;
            /* protocol says to return zero byte data instead of stalling
             the command if you don't have data to return */
            status = USB_OK;
#endif
            break;
        case SET_COMM_FEATURE:
            status = PSTN_Set_Comm_Feature(cdc_obj_ptr, setup_packet, data, size);
            break;
        case GET_COMM_FEATURE:
            status = PSTN_Get_Comm_Feature(cdc_obj_ptr, setup_packet, data, size);
            break;
        case CLEAR_COMM_FEATURE: /* Verify this implementation */
            *size = cdc_obj_ptr->comm_feature_data_size;
            **data = 0x00;
            *( ++(*data)) = 0x00;/*clear both feature bytes*/
            status = PSTN_Set_Comm_Feature(cdc_obj_ptr,
                setup_packet, data, size);
            break;
        case GET_LINE_CODING:
            status = PSTN_Get_Line_Coding(cdc_obj_ptr,
                setup_packet, data, size);
            break;
        case SET_LINE_CODING:
            status = PSTN_Set_Line_Coding(cdc_obj_ptr, setup_packet, data, size);
            break;
        case SET_CONTROL_LINE_STATE:
            status = PSTN_Set_Ctrl_Line_State(cdc_obj_ptr,
                setup_packet, data, size);
            break;
        case SEND_BREAK:
            status = PSTN_Send_Break(cdc_obj_ptr, setup_packet, data, size);
            break;
        default:
            *size = 0;
            break;
        }
    }
    else if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_POS) ==
    USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_VENDOR)
    {
        /* vendor specific request  */
        if (cdc_obj_ptr->vendor_req_callback.callback != NULL)
        {
            status = cdc_obj_ptr->vendor_req_callback.callback(setup_packet,
                data, size, cdc_obj_ptr->vendor_req_callback.arg);
        }
    }

    return status;
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Init
 *
 * @brief The function initializes the Device and Controller layer
 *
 * @param *cdc_config_ptr[IN]:  This structure contains configuration parameter
 *                              send by APP to configure CDC class.
 *
 * @return status
 *         USB_OK           : When Successful
 *         Others           : Errors
 ******************************************************************************
 *
 *This function initializes the CDC Class layer and layers it is dependent on
 *
 *****************************************************************************/
usb_status USB_Class_CDC_Init
(
    uint8_t controller_id,
    cdc_config_struct_t * cdc_config_ptr,
    cdc_handle_t * cdc_handle_ptr
)
{
    usb_status error = USB_OK;
    cdc_handle_t cdc_handle;
    cdc_device_struct_t * devicePtr = NULL;

    if (NULL == (void *)cdc_config_ptr)
    {
        return USBERR_ERROR;
    }

    if (USBERR_DEVICE_BUSY == USB_Cdc_Allocate_Handle(&cdc_handle))
    {
        return USBERR_INIT_FAILED;
    }

    devicePtr = (cdc_device_struct_t *)cdc_handle;
    /* initialize the Global Variable Structure */
    OS_Mem_zero(devicePtr, sizeof(cdc_device_struct_t));
#if CDC_IMPLEMENT_QUEUING
    devicePtr->send_mutex = OS_Mutex_create();
    devicePtr->recv_mutex = OS_Mutex_create();
    if((NULL != devicePtr->recv_mutex) && (NULL != devicePtr->send_mutex))
    {
#endif
    //devicePtr->ep = NULL;
#if USBCFG_DEV_COMPOSITE
    devicePtr->class_handle = USB_Class_Get_Class_Handle();
    devicePtr->controller_handle =(usb_device_handle)USB_Class_Get_Ctrler_Handle(devicePtr->class_handle);
    if(NULL != devicePtr->controller_handle)
    {
#else
    /* Initialize the device layer*/
    error = usb_device_init(controller_id, &devicePtr->controller_handle);
    /* +1 is for Control Endpoint */
    if (error == USB_OK)
    {
        /* Initialize the generic class functions */
        devicePtr->class_handle = USB_Class_Init(devicePtr->controller_handle,
            USB_Class_CDC_Event, USB_CDC_Other_Requests, (void *)cdc_handle,
            cdc_config_ptr->desc_callback_ptr);

#endif
        /* Initialize the generic class functions */
        /* Save the desc callback to ask application for class specific params*/
        OS_Mem_copy(cdc_config_ptr->desc_callback_ptr,
            &devicePtr->desc_callback, sizeof(usb_desc_request_notify_struct_t));
        /* save the callback pointer */
        devicePtr->cdc_application_callback.callback = cdc_config_ptr->cdc_application_callback.callback;
        devicePtr->cdc_application_callback.arg = cdc_config_ptr->cdc_application_callback.arg;
        /* save the callback pointer */
        devicePtr->vendor_req_callback.callback =
        cdc_config_ptr->vendor_req_callback.callback;
        devicePtr->vendor_req_callback.arg = cdc_config_ptr->vendor_req_callback.arg;
        /* save the callback pointer */
        devicePtr->class_specific_callback.callback = cdc_config_ptr->class_specific_callback.callback;
        devicePtr->class_specific_callback.arg = cdc_config_ptr->class_specific_callback.arg;
        devicePtr->comm_feature_data_size = COMM_FEATURE_DATA_SIZE;

        *cdc_handle_ptr = cdc_handle;
#if CDC_RNDIS_SUPPORT
        devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr->controller_handle,
        USB_RNDIS_INFO,
        (uint32_t*)&devicePtr->rndis_info);
#endif

#if PSTN_SUBCLASS_NOTIF_SUPPORT
        /* Initialize the pstn subclass functions */
        error = USB_Pstn_Init(devicePtr, &cdc_config_ptr->cdc_application_callback);
        if (error == USB_OK)
        {
#endif
#if !USBCFG_DEV_COMPOSITE
            usb_device_postinit(controller_id, devicePtr->controller_handle);
#endif
            return USB_OK;
#if PSTN_SUBCLASS_NOTIF_SUPPORT
        }/* error == USB_OK */
#endif
    }/* error == USB_OK */
#if CDC_IMPLEMENT_QUEUING
}/* devicePtr->recv_mutex != NULL */
#endif

    /* Error handler */
#if CDC_IMPLEMENT_QUEUING
    if(devicePtr->recv_mutex)
    {
        if(OS_MUTEX_OK == OS_Mutex_destroy(devicePtr->recv_mutex))
        {
            devicePtr->recv_mutex = NULL;
        }
    }
    if(devicePtr->send_mutex)
    {
        if(OS_MUTEX_OK == OS_Mutex_destroy(devicePtr->send_mutex))
        {
            devicePtr->send_mutex = NULL;
        }
    }
#endif
    USB_Cdc_Free_Handle(cdc_handle);
    devicePtr = NULL;
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Deinit
 *
 * @brief The function initializes the Device and Controller layer
 *
 * @param cdc_handle
 *
 * @return status
 *         USB_OK           : When Successful
 *         Others           : Errors
 ******************************************************************************
 *
 *This function initializes the CDC Class layer and layers it is dependent on
 *
 *****************************************************************************/
usb_status USB_Class_CDC_Deinit
(
    cdc_handle_t cdc_handle
    )
{
    usb_status error = USB_OK;
    cdc_device_struct_t * devicePtr = NULL;
    devicePtr = (cdc_device_struct_t *)cdc_handle;

#if PSTN_SUBCLASS_NOTIF_SUPPORT
    /* deinitialize the pstn subclass functions */
    error = USB_Pstn_Deinit(devicePtr);
#endif
#if !USBCFG_DEV_COMPOSITE
    if (error == USB_OK)
    {
        /* deinitialize the generic class functions */
        error = USB_Class_Deinit(devicePtr->controller_handle, devicePtr->class_handle);
    }
    if (error == USB_OK)
    {
        /* deinitialize the device layer*/
        error = usb_device_deinit(devicePtr->controller_handle);
    }
#endif
#if CDC_IMPLEMENT_QUEUING
    if(devicePtr->recv_mutex)
    {
        if(OS_MUTEX_OK == OS_Mutex_destroy(devicePtr->recv_mutex))
        {
            devicePtr->recv_mutex = NULL;
        }
    }
    if(devicePtr->send_mutex)
    {
        if(OS_MUTEX_OK == OS_Mutex_destroy(devicePtr->send_mutex))
        {
            devicePtr->send_mutex = NULL;
        }
    }
#endif
    if (error == USB_OK)
    {
        error = USB_Cdc_Free_Handle(cdc_handle);
    }

    devicePtr = NULL;
    return error;
}

#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Cancel
 *
 * @brief
 *
 * @param handle          :   handle returned by USB_Class_CDC_Init
 * @param ep_num          :   endpoint num
 * @param direction        :   direction of the endpoint
 *
 * @return status
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/

usb_status USB_Class_CDC_Cancel
(
    cdc_handle_t cdc_handle,/*[IN]*/
    uint8_t ep_num,/*[IN]*/
    uint8_t type,
    uint8_t direction
    )
{
    cdc_device_struct_t* devicePtr;
#if CDC_IMPLEMENT_QUEUING
    uint8_t index;
    uint8_t producer, consumer;
    cdc_queue_struct_t queue;
    static usb_event_struct_t event;
    uint8_t event_type;
#endif
    usb_status error = USB_OK;
    if (cdc_handle == 0)
    {
        return USBERR_ERROR;
    }

    devicePtr = (cdc_device_struct_t *)cdc_handle;
    if (NULL == devicePtr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }
#if CDC_IMPLEMENT_QUEUING
    index = USB_Map_Ep_To_Struct_Index(devicePtr, ep_num);
    switch(type)
    {
    case USB_BULK_PIPE:
        if(direction == USB_SEND)
        {
            event_type = USB_DEV_EVENT_SEND_COMPLETE;
        }
        else if(direction == USB_RECV)
        {
            event_type = USB_DEV_EVENT_DATA_RECEIVED;
        }
        break;
    case USB_INTERRUPT_PIPE:
        event_type = USB_APP_CDC_SERIAL_STATE_NOTIF;
        break;
    default:
        break;
    }
    USB_Cdc_Ep_Mutex_Lock(devicePtr, ep_num);

    producer = devicePtr->ep[index].bin_producer;
    consumer = devicePtr->ep[index].bin_consumer;

    /* Cancel the pending transfer */
    if(consumer != producer)
    {
        USB_Cdc_Ep_Mutex_Unlock(devicePtr, ep_num);
#endif

    error = usb_device_cancel_transfer(devicePtr->controller_handle, ep_num, direction);

#if CDC_IMPLEMENT_QUEUING
    USB_Cdc_Ep_Mutex_Lock(devicePtr, ep_num);
    producer = devicePtr->ep[index].bin_producer;
    if(USB_OK == error)
    {
        //devicePtr->ep[index].bin_consumer++;
        consumer = devicePtr->ep[index].bin_consumer;
    }
    else
    {
#if _DEBUG
        USB_PRINTF("usb_device_cancel_transfer fail\r\n");
#endif
    }
}
/* Cancel the transfer in queue */
while(consumer != producer)
{
    queue = devicePtr->ep[index].queue[consumer%CDC_MAX_QUEUE_ELEMS];

    USB_Cdc_Ep_Mutex_Unlock(devicePtr, ep_num);
    if(devicePtr->class_specific_callback.callback != NULL)
    {
        event.buffer_ptr = queue.app_data.data_ptr;
        event.len = 0xFFFFFFFF;  //queue.app_data.data_size;
        devicePtr->class_specific_callback.callback(event_type,
        USB_REQ_VAL_INVALID,
        &(event.buffer_ptr),
        &(event.len),
        devicePtr->class_specific_callback.arg);
    }
    USB_Cdc_Ep_Mutex_Lock(devicePtr, ep_num);
    producer = devicePtr->ep[index].bin_producer;
    devicePtr->ep[index].bin_consumer++;
    consumer = devicePtr->ep[index].bin_consumer;
}
USB_Cdc_Ep_Mutex_Unlock(devicePtr, ep_num);

#endif

    return error;

}
#endif
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Send_Data
 *
 * @brief
 *
 * @param handle          :   handle returned by USB_Class_CDC_Init
 * @param ep_num          :   endpoint num
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer
 *
 * @return status
 *         USB_OK         : When Successful
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Class_CDC_Send_Data
(
    cdc_handle_t handle,
    uint8_t ep_num,
    uint8_t * app_buff,
    uint32_t size
    )
{
#if CDC_IMPLEMENT_QUEUING
    uint8_t index;
    uint8_t producer, consumer;
//        usb_endpoints_t *usb_ep_data;
#endif

    cdc_device_struct_t * cdc_obj_ptr;
    usb_status status = USB_OK;
    cdc_obj_ptr = (cdc_device_struct_t *)handle;
    if (NULL == cdc_obj_ptr)
    {
        return USBERR_ERROR;
    }

#if CDC_IMPLEMENT_QUEUING
//        usb_ep_data = cdc_obj_ptr->usb_ep_data;

    /* map the endpoint num to the index of the endpoint structure */
    index = USB_Map_Ep_To_Struct_Index(cdc_obj_ptr, ep_num);

    producer = cdc_obj_ptr->ep[index].bin_producer;
    USB_Cdc_Ep_Mutex_Lock(cdc_obj_ptr, ep_num);
    consumer = cdc_obj_ptr->ep[index].bin_consumer;

    if((producer >= consumer? (producer - consumer): (0x100 + producer - consumer)) != (uint8_t)(CDC_MAX_QUEUE_ELEMS))
    {
        /* the bin is not full*/
        uint8_t queue_num = (uint8_t)(producer % CDC_MAX_QUEUE_ELEMS);

        /* put all send request parameters in the endpoint data structure*/
        cdc_obj_ptr->ep[index].queue[queue_num].channel = ep_num;
        cdc_obj_ptr->ep[index].queue[queue_num].app_data.data_ptr = app_buff;
        cdc_obj_ptr->ep[index].queue[queue_num].app_data.data_size = size;
        cdc_obj_ptr->ep[index].queue[queue_num].handle =
        cdc_obj_ptr->controller_handle;

        if(producer == consumer)
        {

#endif
            status = USB_Class_Send_Data(cdc_obj_ptr->class_handle,
                                         ep_num, app_buff,size);
#if CDC_IMPLEMENT_QUEUING
            if(USB_OK == status)
            {
                /* increment producer bin by 1*/
                cdc_obj_ptr->ep[index].bin_producer = ++producer;
            }
        }
        else
        {
            /* increment producer bin by 1*/
            cdc_obj_ptr->ep[index].bin_producer = ++producer;
        }
    }
    else /* bin is full */
    {
        status = USBERR_DEVICE_BUSY;
    }
    USB_Cdc_Ep_Mutex_Unlock(cdc_obj_ptr, ep_num);
#endif
    return status;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Recv_Data
 *
 * @brief This functions receives Data from Host.
 *
 * @param handle          :   handle returned by USB_Class_CDC_Init
 * @param ep_num          :   endpoint num
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer
 *
 * @return status
 *         USB_OK         : When Successful
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Class_CDC_Recv_Data
(
    cdc_handle_t cdc_handle,
    uint8_t ep_num,
    uint8_t * buff_ptr, /* [IN] buffer to recv */
    uint32_t size /* [IN] length of the transfer */
)
{

#if CDC_IMPLEMENT_QUEUING
    uint8_t index;
    uint8_t producer, consumer;
#endif
    cdc_device_struct_t * cdc_obj_ptr;
    usb_status status = USB_OK;

    cdc_obj_ptr = (cdc_device_struct_t *)cdc_handle;
    if (NULL == cdc_obj_ptr)
    {
        return USBERR_ERROR;
    }
#if CDC_IMPLEMENT_QUEUING

    /* map the endpoint num to the index of the endpoint structure */
    index = USB_Map_Ep_To_Struct_Index(cdc_obj_ptr, ep_num);

    producer = cdc_obj_ptr->ep[index].bin_producer;
    USB_Cdc_Ep_Mutex_Lock(cdc_obj_ptr, ep_num);
    consumer = cdc_obj_ptr->ep[index].bin_consumer;

    if((producer >= consumer? (producer - consumer): (0x100 + producer - consumer)) != (uint8_t)(CDC_MAX_QUEUE_ELEMS))
    {
        /* the bin is not full*/
        uint8_t queue_num = (uint8_t)(producer % CDC_MAX_QUEUE_ELEMS);

        /* put all send request parameters in the endpoint data structure*/
        cdc_obj_ptr->ep[index].queue[queue_num].channel = ep_num;
        cdc_obj_ptr->ep[index].queue[queue_num].app_data.data_ptr = buff_ptr;
        cdc_obj_ptr->ep[index].queue[queue_num].app_data.data_size = size;
        cdc_obj_ptr->ep[index].queue[queue_num].handle =
        cdc_obj_ptr->controller_handle;

        if(producer == consumer)
        {
            USB_Cdc_Ep_Mutex_Unlock(cdc_obj_ptr, ep_num);
#endif
            status = usb_device_recv_data(cdc_obj_ptr->controller_handle,
                                          ep_num,buff_ptr,size);
#if CDC_IMPLEMENT_QUEUING
            USB_Cdc_Ep_Mutex_Lock(cdc_obj_ptr, ep_num);
            if(USB_OK == status)
            {
                /* increment producer bin by 1*/
                cdc_obj_ptr->ep[index].bin_producer = ++producer;
            }
        }
        else
        {
            /* increment producer bin by 1*/
            cdc_obj_ptr->ep[index].bin_producer = ++producer;
        }
    }
    else /* bin is full */
    {
        status = USBERR_DEVICE_BUSY;
    }
    USB_Cdc_Ep_Mutex_Unlock(cdc_obj_ptr, ep_num);
#endif
    return status;

}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Get_Speed
 *
 * @brief This functions get speed from Host.
 *
 * @param handle          :   handle returned by USB_Class_CDC_Init
 * @param speed           :   speed
 *
 * @return status
 *         USB_OK         : When Successfull
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Class_CDC_Get_Speed
(
    cdc_handle_t cdc_handle,
    uint16_t * speed/* [OUT] the requested error */
    )
{
    cdc_device_struct_t * cdc_obj_ptr;
    usb_status error = USB_OK;

    cdc_obj_ptr = (cdc_device_struct_t *)cdc_handle;
    if (NULL == cdc_obj_ptr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }
    error = USB_Class_Get_Status(cdc_obj_ptr->class_handle, USB_STATUS_SPEED, speed);

    return error;
}

#endif /*CDC_CONFIG*/
/* EOF */
