/**HEADER********************************************************************
 * 
 * Copyright (c) 2008, 2013 - 2014 Freescale Semiconductor;
 * All Rights Reserved
 *
 * Copyright (c) 1989 - 2008 ARC International;
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
 * $FileName: usb_phdc.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief The file contains USB stack PHDC layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"

#if USBCFG_DEV_PHDC 
#include "usb_class_internal.h"
#include "usb_class_phdc.h"
#include "usb_phdc.h"

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Functions - Prototypes
 ****************************************************************************/
void USB_PHDC_Endpoint_Service(usb_event_struct_t* event,void* arg);
/****************************************************************************
 * Global Variables
 ****************************************************************************/
phdc_device_struct_t g_phdc_class[MAX_PHDC_DEVICE];
phdc_app_data_struct_t event_data_received;
/* Add all the variables needed for usb_phdc.c to this structure */
#if USB_METADATA_SUPPORTED
/* string used to give preamble verifiability */
static char msg_preamble_signature[17] = "PhdcQoSSignature";
#endif
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
/*****************************************************************************
 * Local Functions
 *****************************************************************************/

/*************************************************************************//*!
 *
 * @name  USB_Phdc_Allocate_Handle
 *
 * @brief The function reserves entry in device array and returns the index.
 *
 * @param none.
 * @return returns the reserved handle or if no entry found device busy.      
 *
 *****************************************************************************/
static usb_status USB_Phdc_Allocate_Handle(phdc_device_struct_t** handle)
{
    uint32_t cnt = 0;
    for (;cnt< MAX_PHDC_DEVICE;cnt++)
    {
        if (g_phdc_class[cnt].handle == NULL)
        {
            *handle = (phdc_device_struct_t*)&g_phdc_class[cnt];
            return USB_OK;
        }
    }
    return USBERR_DEVICE_BUSY;
}
/*************************************************************************//*!
 *
 * @name  USB_Phdc_Free_Handle
 *
 * @brief The function releases entry in device array .
 *
 * @param handle  index in device array to be released..
 * @return returns and error code or USB_OK.      
 *
 *****************************************************************************/

static usb_status USB_Phdc_Free_Handle(phdc_device_struct_t* handle)
{
    int32_t cnt = 0;
    for (;cnt< MAX_PHDC_DEVICE;cnt++)
    {
        if ((&g_phdc_class[cnt]) == handle)
        {
            OS_Mem_zero((void*)handle, sizeof(phdc_device_struct_t));
            return USB_OK;
        }
    }
    return USBERR_INVALID_PARAM;
}

/*************************************************************************//*!
 *
 * @name  USB_Phdc_Get_Device_Ptr
 *
 * @brief The function gets the device pointer from device array .
 *
 * @param handle  index in device array.
 * @return returns returns pointer to HID device structure..      
 *
 *****************************************************************************/
static phdc_device_struct_t* USB_Phdc_Get_Device_Ptr
(
phdc_handle_t handle
)
{
    return (phdc_device_struct_t *)handle;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Event
 *
 * @brief Initializes non control endpoints
 *
 * @param handle         
 * @param event          : event notified by the layer below
 * @param value          : additional parameter used by the event
 *
 * @return               : None
 ******************************************************************************
 * Initializes non control endpoints when Enumeration complete event is 
 * received.
 *****************************************************************************/
void USB_Class_PHDC_Event
(
uint8_t event,
void* val,
void* arg
)
{
    uint8_t count_rx = 0;
    uint8_t count_tx = 0;
    uint8_t index;
    usb_ep_struct_t* ep_struct_ptr;
    phdc_device_struct_t* devicePtr;
    uint8_t * phdc_qos;
#if USBCFG_DEV_COMPOSITE
    usb_composite_info_struct_t* usb_composite_info;
    uint32_t interface_index = 0xFF;
#else
    usb_class_struct_t* usbclass = NULL;
#endif

    devicePtr = (phdc_device_struct_t *)arg;

    /* if enum is complete initialize non-control endpoints */
    if (event == USB_DEV_EVENT_CONFIG_CHANGED)
    {
        uint8_t count = 0;
#if USBCFG_DEV_COMPOSITE
        uint8_t type_sel;
        devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr->handle,
        USB_COMPOSITE_INFO,
        (uint32_t *)&usb_composite_info);

        devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr->handle,
        USB_PHDC_QOS_INFO,
        (uint32_t *)&phdc_qos);

        devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr,
        USB_CLASS_INTERFACE_INDEX_INFO, (uint32_t *)&interface_index);
        if(interface_index == 0xFF)
        {
#if _DEBUG
            USB_PRINTF("not find interface index\n");
#endif  
            return;
        }

        for (type_sel = 0;type_sel < usb_composite_info->count;type_sel++)
        {
            if ((usb_composite_info->class_handle[type_sel].type == USB_CLASS_PHDC) && (type_sel == interface_index))
            {
                break;
            }
        }
        if(type_sel >= usb_composite_info->count)
        {
#if _DEBUG
            USB_PRINTF("not find phdc interface\n");
#endif 
            return;
        }

        devicePtr->ep_desc_data = (usb_endpoints_t *) &usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints;
        devicePtr->phdc_endpoint_data.count_rx = 0; /* init the count_rx */
        devicePtr->phdc_endpoint_data.count_tx = 0; /* init the count_tx */

        /* calculate the rx and tx endpoint counts */
        for (index = 0; index < usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.count; index++)
        {
            if ((usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].direction == USB_RECV) &
            (devicePtr->phdc_endpoint_data.count_rx < PHDC_RX_ENDPOINTS))
            {
                devicePtr->phdc_endpoint_data.count_rx++;
            }
            else if ((usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].direction == USB_SEND) &
            (devicePtr->phdc_endpoint_data.count_tx < PHDC_TX_ENDPOINTS))
            {
                devicePtr->phdc_endpoint_data.count_tx++;
            }
        }

        /* initialize endpoint data structure for all endpoints */
        for (index = 0; index <usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.count; index++)
        {
            if ((usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].direction == USB_RECV) &
            (count_rx < PHDC_RX_ENDPOINTS))
            {
                /* initialize endpoint data structure for recv endpoint */
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].endpoint =
                usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].ep_num;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].type =
                usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].type;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].size =
                usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].size;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].qos = phdc_qos[index];
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].current_qos =
                INVALID_VAL;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].buff_ptr = NULL;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].buffer_size = 0;
                /* increment count_rx by 1 */
                count_rx++;
            }
            else if ((usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].direction == USB_SEND) &
            (count_tx < PHDC_TX_ENDPOINTS))
            {
                /* initialize endpoint data structure for send endpoint */
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].endpoint =
                usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].ep_num;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].type =
                usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].type;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].size =
                usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.ep[index].size;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].qos = phdc_qos[index];
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].current_qos = INVALID_VAL;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].bin_consumer = 0x00;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].bin_producer = 0x00;
                /* increment count_tx by 1 */
                count_tx++;
            }
        }
#else
        devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr->handle,
        USB_CLASS_INFO, (uint32_t *)&usbclass);
        devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr->handle,
        USB_PHDC_QOS_INFO, (uint32_t *)&phdc_qos);
        devicePtr->ep_desc_data = (usb_endpoints_t *) &usbclass->interfaces.interface->endpoints;
        devicePtr->phdc_endpoint_data.count_rx = 0; /* init the count_rx */
        devicePtr->phdc_endpoint_data.count_tx = 0; /* init the count_tx */

        /* calculate the rx and tx endpoint counts */
        for (index = 0; index < usbclass->interfaces.interface->endpoints.count; index++)
        {
            if ((usbclass->interfaces.interface->endpoints.ep[index].direction == USB_RECV) &
            (devicePtr->phdc_endpoint_data.count_rx < PHDC_RX_ENDPOINTS))
            {
                devicePtr->phdc_endpoint_data.count_rx++;
            }
            else if ((usbclass->interfaces.interface->endpoints.ep[index].direction == USB_SEND) &
            (devicePtr->phdc_endpoint_data.count_tx < PHDC_TX_ENDPOINTS))
            {
                devicePtr->phdc_endpoint_data.count_tx++;
            }
        }

        /* initialize endpoint data structure for all endpoints */
        for (index = 0; index < usbclass->interfaces.interface->endpoints.count; index++)
        {
            if ((usbclass->interfaces.interface->endpoints.ep[index].direction == USB_RECV) &
            (count_rx < PHDC_RX_ENDPOINTS))
            {
                /* initialize endpoint data structure for recv endpoint */
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].endpoint =
                usbclass->interfaces.interface->endpoints.ep[index].ep_num;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].type =
                usbclass->interfaces.interface->endpoints.ep[index].type;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].size =
                usbclass->interfaces.interface->endpoints.ep[index].size;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].qos = phdc_qos[index];
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].current_qos = INVALID_VAL;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].buff_ptr = NULL;
                devicePtr->phdc_endpoint_data.ep_rx[count_rx].buffer_size = 0;
                /* increment count_rx by 1 */
                count_rx++;
            }
            else if ((usbclass->interfaces.interface->endpoints.ep[index].direction == USB_SEND) &
            (count_tx < PHDC_TX_ENDPOINTS))
            {
                /* initialize endpoint data structure for send endpoint */
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].endpoint =
                usbclass->interfaces.interface->endpoints.ep[index].ep_num;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].type =
                usbclass->interfaces.interface->endpoints.ep[index].type;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].size =
                usbclass->interfaces.interface->endpoints.ep[index].size;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].qos = phdc_qos[index];
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].current_qos = INVALID_VAL;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].bin_consumer = 0x00;
                devicePtr->phdc_endpoint_data.ep_tx[count_tx].bin_producer = 0x00;
                /* increment count_tx by 1 */
                count_tx++;
            }
        }

#endif
        usb_endpoints_t *ep_desc_data = devicePtr->ep_desc_data;
        /* initialize all non control endpoints */
        count = 0;
        while (count < ep_desc_data->count)
        {
            ep_struct_ptr= (usb_ep_struct_t*) &ep_desc_data->ep[count];
            (void)usb_device_init_endpoint(devicePtr->handle, ep_struct_ptr, TRUE);

            /* register callback service for endpoint 1 */
            (void)usb_device_register_service(devicePtr->handle,
            (uint8_t)((uint8_t)(USB_SERVICE_EP0+ep_struct_ptr->ep_num) | ((uint8_t)(ep_struct_ptr->direction << 7))),
            USB_PHDC_Endpoint_Service, arg);
            count++;
        }
    }
    else if (event == USB_DEV_EVENT_ENUM_COMPLETE)
    {

    }
    else if (event == USB_DEV_EVENT_BUS_RESET)
    {

    }

    if (devicePtr->phdc_application_callback.callback != NULL)
    {
        devicePtr->phdc_application_callback.callback(event,val,devicePtr->phdc_application_callback.arg);
    }
}

/**************************************************************************//*!
 *
 * @name  USB_PHDC_Requests
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param handle           
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned                   
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 ******************************************************************************
 * The function provides flexibility to add class and vendor specific requests
 *****************************************************************************/
usb_status USB_PHDC_Requests
(
usb_setup_struct_t *setup_packet,/* [IN] setup packet received */
uint8_t **data, /* [OUT] data to be send back */
uint32_t *size, /* [OUT] size to be returned */
void* arg
)
{
    usb_status error = USBERR_INVALID_REQ_TYPE;
    phdc_device_struct_t *devicePtr = (phdc_device_struct_t*)arg;

    if (devicePtr == NULL)
    {
#if _DEBUG
        USB_PRINTF("USB_PHDC_Requests:phdc_object_ptr is NULL\n");
#endif  
        return error;
    }
    if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_POS) ==
    USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_CLASS)
    { /*class request so handle it here */
        *size = 0;
        error = USB_OK;

        switch (setup_packet->request)
        {
            case SET_FEATURE_REQUEST:
            case CLEAR_FEATURE_REQUEST:
            {
#if USB_METADATA_SUPPORTED
                /* set/clear meta data feature */
                devicePtr->phdc_metadata = (bool)((setup_packet->request & USB_SET_REQUEST_MASK) >> 1);
                /* inform the application that feature has changed */
                if (devicePtr->phdc_application_callback.callback != NULL)
                {
                    devicePtr->phdc_application_callback.callback(USB_DEV_EVENT_FEATURE_CHANGED,
                    (void*)(&devicePtr->phdc_metadata),
                    devicePtr->phdc_application_callback.arg);
                }
#endif
                break;
            }
            case GET_STATUS_REQUEST:
            {
                /*implement get status request to get which endpoint has data*/
                *data = (uint8_t *)(&devicePtr->phdc_ep_has_data);
                *size = setup_packet->length;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    else if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_POS) ==
    USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_VENDOR)
    { /* vendor specific request  */
        if(devicePtr->vendor_req_callback.callback != NULL)
        {
            error = devicePtr->vendor_req_callback.callback(setup_packet,data,
            size,devicePtr->vendor_req_callback.arg);
        }
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_PHDC_Endpoint_Service
 *
 * @brief Called upon a completed endpoint (non-control) transfer 
 *
 * @param event :  Pointer to the event structure
 * 
 * @return  None
 *****************************************************************************
 * This function is called when a transfer completes on a non control endpoint
 *****************************************************************************/
void USB_PHDC_Endpoint_Service
(
usb_event_struct_t* event,
void* arg
)
{/* Body*/
    uint8_t index;
    uint8_t producer;
    uint8_t consumer;
    phdc_app_data_struct_t event_send_complete;
#if USB_METADATA_SUPPORTED   
    usb_app_event_metadata_params_t metadata_params;
#endif    
    usb_class_phdc_qos_bin_t qos_bin;
    phdc_device_struct_t* devicePtr = (phdc_device_struct_t*)arg;

    if (event->direction == USB_SEND)
    {
        /* get the index for the corresponding endpoint(channel) */
        for (index = 0; index < PHDC_TX_ENDPOINTS; index++)
        {
            if (devicePtr->phdc_endpoint_data.ep_tx[index].endpoint == event->ep_num)
            {
                break;
            }
        }

        /* initialize producer with the num of queued transfers */
        producer = devicePtr->phdc_endpoint_data.ep_tx[index].bin_producer;
        /* initialize consumer with the num of de-queued transfers */
        consumer = devicePtr->phdc_endpoint_data.ep_tx[index].bin_consumer;

        if (devicePtr->phdc_endpoint_data.ep_tx[index].
        qos_bin[consumer % MAX_QOS_BIN_ELEMS].meta_data == FALSE)
        {/* if the previous packet sent was a meta data do not 
         decrement the transfers_left else decrement */
            devicePtr->phdc_endpoint_data.ep_tx[index].transfers_left--;
        }

        /* de-queue the queue */
        devicePtr->phdc_endpoint_data.ep_tx[index].bin_consumer++;
        consumer = devicePtr->phdc_endpoint_data.ep_tx[index].bin_consumer;

        /* get the qos information of the next transfer */
        qos_bin = devicePtr->phdc_endpoint_data.ep_tx[index].qos_bin[consumer % MAX_QOS_BIN_ELEMS];

#if USB_METADATA_SUPPORTED   
        /* if transfers left is non zero and the next packet to send 
         is a meta data, discard the meta data packet */
        if (devicePtr->phdc_endpoint_data.ep_tx[index].transfers_left != 0)
        {
            /* discard all the meta data packets if any */
            while (qos_bin.meta_data == TRUE)
            {
                /* de-queue the queue-- discarding meta data packet */
                consumer = ++devicePtr->phdc_endpoint_data.ep_tx[index].bin_consumer;
                if (consumer == producer)
                {
                    break; /* queue is empty */
                }
                /* set qos_bin for next packet in the queue */
                qos_bin = devicePtr->phdc_endpoint_data.ep_tx[index].qos_bin[consumer % MAX_QOS_BIN_ELEMS];
            }
        }
#endif  

        if (consumer != producer)
        {/*if bin is not empty */
#if USB_METADATA_SUPPORTED
            if (qos_bin.meta_data == TRUE)
            {
                /* initialize transfers left if the packet is a meta data */
                devicePtr->phdc_endpoint_data.ep_tx[index].transfers_left = qos_bin.num_tfr;
                /* initialize current_qos of the transfers that follow the 
                 meta data packet */
                devicePtr->phdc_endpoint_data.ep_tx[index].current_qos = qos_bin.qos;
            }
#endif
            /* send data */
            (void)USB_Class_Send_Data(devicePtr->class_handle, qos_bin.channel, qos_bin.app_buff, qos_bin.size);
        }
        else /* bin is empty */
        {
            /*set endpoint bin as non active */
            devicePtr->phdc_ep_has_data &= (uint16_t)(~(uint16_t)(1<<event->ep_num));
        }

        /* Set the USB_APP_EVENT_SEND_DATA structure */
        event_send_complete.qos = devicePtr->phdc_endpoint_data.ep_tx[index].qos;
        event_send_complete.buffer_ptr = event->buffer_ptr;
        event_send_complete.size = event->len;

        /* notify the application of the send complete */
        if (NULL != devicePtr->class_specific_callback.callback)
        {
            phdc_app_data_struct_t* event_send_complete_tmp = &event_send_complete;
            devicePtr->class_specific_callback.callback(
            USB_DEV_EVENT_SEND_COMPLETE,
            USB_REQ_VAL_INVALID,
            (uint8_t **)&event_send_complete_tmp,
            &event->len,
            devicePtr->class_specific_callback.arg);
        }
    }
    else /* direction is USB_RECV */
    {
        if (!event->len)
        {/* indicates there was call of zero byte recv */
            return;
        }
        /* get the index for the corresponding endpoint */
        for (index = 0; index < PHDC_RX_ENDPOINTS; index++)
        {
            if (devicePtr->phdc_endpoint_data.ep_rx[index].endpoint == event->ep_num)
            {
                break;
            }
        }

        if (devicePtr->phdc_endpoint_data.ep_rx[index].buff_ptr == NULL)
        {
            /* First Call will have buff_ptr == NULL */
            devicePtr->phdc_endpoint_data.ep_rx[index].buffer_size = event->len;
            if (NULL != devicePtr->class_specific_callback.callback)
            {
                phdc_app_data_struct_t* event_data_received_tmp = &event_data_received;
                devicePtr->class_specific_callback.callback(
                USB_DEV_EVENT_GET_DATA_BUFF,
                USB_REQ_VAL_INVALID,
                (uint8_t **)(&event_data_received_tmp),
                &event->len,
                (void *)event->buffer_ptr);
            }
            devicePtr->phdc_endpoint_data.ep_rx[index].buff_ptr = event_data_received.buffer_ptr;
            /* Copy the first data packet to the app buffer */
            OS_Mem_copy(event->buffer_ptr,devicePtr->phdc_endpoint_data.ep_rx[index].buff_ptr,event_data_received.size);
        }
        else
        {
            /* update the size of received data */
            devicePtr->phdc_endpoint_data.ep_rx[index].buffer_size += event->len;
        }

        /* Receive all the data */
        if (event_data_received.size == devicePtr->phdc_endpoint_data.ep_rx[index].buffer_size)
        {
#if USB_METADATA_SUPPORTED   
            transfers_left = devicePtr->phdc_endpoint_data.ep_rx[index].
            transfers_left;
            /*compare the received signature with the string for preamble
             verifiability. if meta_data_packet = 0(both signatures match) 
             the incoming packet is a meta data */
            meta_data_packet = (uint8_t)strncmp(
            devicePtr->meta_data_msg_preamble.signature,
            msg_preamble_signature, METADATA_PREAMBLE_SIGNATURE);

            /*check whether transfers are left. we check for meta data only
             when number of transfers left is zero */
            if ((devicePtr->phdc_metadata == FALSE) || (transfers_left != 0 &&
            meta_data_packet !=0))
            {
                devicePtr->phdc_endpoint_data.ep_rx[index].transfers_left =
                (uint8_t)(transfers_left - 1);
                /* set the data received structure */
                event_data_received.qos =
                devicePtr->phdc_endpoint_data.ep_rx[index].qos;
                event_data_received.buffer_ptr = devicePtr->phdc_endpoint_data.ep_rx[index].buff_ptr;
                event_data_received.size = devicePtr->phdc_endpoint_data.ep_rx[index].buffer_size;

                /* notify the application that received data is complete */
                if (NULL != devicePtr->class_specific_callback.callback)
                {
                    phdc_app_data_struct_t* event_data_received_tmp = &event_data_received;
                    devicePtr->class_specific_callback.callback(
                    USB_DEV_EVENT_DATA_RECEIVED,
                    USB_REQ_VAL_INVALID,
                    (uintt_8 *)&event_data_received_tmp,
                    &event->len,
                    devicePtr->class_specific_callback.arg);
                }
            }
            else if ((transfers_left == 0 ) && (meta_data_packet == 0))
            {/*if number of transfers left is zero and the packet is meta 
             data msg preamble initialize the endpoint data structure 
             from the meta data msg preamble data structure */
                devicePtr->phdc_endpoint_data.ep_rx[index].transfers_left =
                devicePtr->meta_data_msg_preamble.num_tfr;
                devicePtr->phdc_endpoint_data.ep_rx[index].current_qos =
                devicePtr->meta_data_msg_preamble.qos;
                /* set the event phdc meta data params structure*/
                metadata_params.channel = event->ep_num;
                metadata_params.num_tfr =
                devicePtr->meta_data_msg_preamble.num_tfr;
                metadata_params.qos = devicePtr->meta_data_msg_preamble.qos;
                metadata_params.metadata_ptr =
                &devicePtr->meta_data_msg_preamble.opaque_data[0];

                /*notify the app that meta data params has changed*/
                devicePtr->phdc_class_callback.callback(USB_DEV_EVENT_META_DATA_PARAMS_CHANGED,
                (void*)(&metadata_params),devicePtr->phdc_class_callback.arg);
            }
#else
            /* set the data received structure */
            event_data_received.qos =devicePtr->phdc_endpoint_data.ep_rx[index].qos;
            event_data_received.buffer_ptr = devicePtr->phdc_endpoint_data.ep_rx[index].buff_ptr;
            event_data_received.size = devicePtr->phdc_endpoint_data.ep_rx[index].buffer_size;

            /* notify the application that received data is complete */
            if (NULL != devicePtr->class_specific_callback.callback)
            {
                phdc_app_data_struct_t * event_data_received_tmp = &event_data_received;
                devicePtr->class_specific_callback.callback(
                USB_DEV_EVENT_DATA_RECEIVED,
                USB_REQ_VAL_INVALID,
                (uint8_t **)&event_data_received_tmp,
                &event->len,
                devicePtr->class_specific_callback.arg);
            }
#endif
            /* when complete packet is received
             reset the buffer_size and buff_ptr */
            devicePtr->phdc_endpoint_data.ep_rx[index].buffer_size = 0;
            devicePtr->phdc_endpoint_data.ep_rx[index].buff_ptr = NULL;
        }/* Endif */
        else
        {
            /* Some data is still pending to be received
             copy data to app buffer and schedule next transfer */
            (void)USB_Class_PHDC_Recv_Data(devicePtr->user_handle,
            devicePtr->phdc_endpoint_data.ep_rx[index].qos,
            (uint8_t *)(devicePtr->phdc_endpoint_data.ep_rx[index].buff_ptr + devicePtr->phdc_endpoint_data.ep_rx[index].buffer_size),
            devicePtr->phdc_endpoint_data.ep_rx[index].size);
        }
    }/* Endif */
}/* EndBody*/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Send_Data
 *
 * @brief This function is used by Application to send data through PHDC class
 *
 * @param handle          :   handle returned by USB_Class_PHDC_Init
 * @param meta_data       :   packet is meta data or not
 * @param num_tfr         :   no. of transfers
 * @param qos             :   current qos of the transfer
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer   
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 ******************************************************************************
 * This function is used by Application to send data through PHDC class
 *****************************************************************************/
usb_status USB_Class_PHDC_Send_Data
(
phdc_handle_t handle,
bool meta_data, /* [IN] packet is meta data or not */
uint8_t num_tfr, /* [IN] no. of transfers */
uint8_t qos, /* [IN] current qos of the transfer */
uint8_t * app_buff, /* [IN] buffer to send */
uint32_t size /* [IN] length of the transfer */
)
{
    uint8_t channel;
    uint8_t producer;
    uint8_t consumer;
    uint8_t tx_index;
    phdc_device_struct_t* devicePtr;
    usb_status error = USB_OK;

    devicePtr = USB_Phdc_Get_Device_Ptr(handle);
    if (NULL == devicePtr)
    {
        return USBERR_ERROR;
    }

    /* get the index for the corresponding endpoint(channel) to send data
     of desired qos */
    for (tx_index = 0; tx_index < PHDC_TX_ENDPOINTS; tx_index++)
    {
        if(devicePtr->phdc_endpoint_data.ep_tx[tx_index].qos == qos)
        {
            break;
        }
    }

    if (tx_index == PHDC_TX_ENDPOINTS)
    {
        return USBERR_TX_FAILED;
    }

#if USB_METADATA_SUPPORTED   
    /* if the packet to send is not as desired return with an error */
    if ((((devicePtr->phdc_endpoint_data.ep_tx[tx_index].transfers_left == 0) ||
    (devicePtr->phdc_endpoint_data.ep_tx[tx_index].type != USB_BULK_PIPE)) &&
    (meta_data == FALSE) && (devicePtr->phdc_metadata == TRUE)) ||
    ((devicePtr->phdc_metadata == FALSE) && (meta_data == TRUE)))
    {
        return USBERR_TX_FAILED;
    }
#endif

    channel = devicePtr->phdc_endpoint_data.ep_tx[tx_index].endpoint;
    /*set channel active. Set bit map for the corresponding channel(endp)*/
    devicePtr->phdc_ep_has_data |= (uint16_t)(1 << channel);

    /* initialize producer with the num of queued transfers */
    producer = devicePtr->phdc_endpoint_data.ep_tx[tx_index].bin_producer;
    /* initialize consumer with the num of de-queued transfers */
    consumer = devicePtr->phdc_endpoint_data.ep_tx[tx_index].bin_consumer;
    OS_Mutex_lock(devicePtr->mutex);
    if ((uint8_t)(producer - consumer) != (uint8_t)(MAX_QOS_BIN_ELEMS))
    {/* the bin is not full*/
        uint8_t queue_num = (uint8_t)(producer % MAX_QOS_BIN_ELEMS);

        /* put all send request parameters in the endpoint data structure */
        devicePtr->phdc_endpoint_data.ep_tx[tx_index].qos_bin[queue_num].channel = channel;
        devicePtr->phdc_endpoint_data.ep_tx[tx_index].qos_bin[queue_num].meta_data = meta_data;
        devicePtr->phdc_endpoint_data.ep_tx[tx_index].qos_bin[queue_num].num_tfr = num_tfr;
        devicePtr->phdc_endpoint_data.ep_tx[tx_index].qos_bin[queue_num].qos = qos;
        devicePtr->phdc_endpoint_data.ep_tx[tx_index].qos_bin[queue_num].app_buff = app_buff;
        devicePtr->phdc_endpoint_data.ep_tx[tx_index].qos_bin[queue_num].size = size;

        /* increment producer bin by 1 -- queue the transfer */
        devicePtr->phdc_endpoint_data.ep_tx[tx_index].bin_producer = ++producer;

        if ((uint8_t)(producer - consumer) == (uint8_t)1)
        {/* bin has only this packet to send */
#if USB_METADATA_SUPPORTED
            /* discard the packet if the packet is a meta data and num of 
             transfers is not equal to zero */
            if ((meta_data == TRUE) &&
            (devicePtr->phdc_endpoint_data.ep_tx[tx_index].transfers_left != 0))
            {/* notify the application of the error*/
                devicePtr->phdc_application_callback.callback(USB_DEV_EVENT_ERROR,NULL,
                devicePtr->phdc_application_callback.arg);
                return USBERR_TX_FAILED;
            }
            else if (meta_data == TRUE)
            {
                /* initialize transfers left if the packet is a meta data */
                devicePtr->phdc_endpoint_data.ep_tx[tx_index].transfers_left = num_tfr;
                /* initialize current_qos of the transfers that follow the 
                 meta data packet */
                devicePtr->phdc_endpoint_data.ep_tx[tx_index].current_qos = qos;
            }
#endif
            /* send the packet if there is no packet (other than this packet) 
             in the queue */
            error = USB_Class_Send_Data(devicePtr->class_handle,channel, app_buff,size);
        }
    }
    else /* bin is full */
    {
        /* return device is busy when the queue is full */
        error = USBERR_DEVICE_BUSY;
    }
    OS_Mutex_unlock(devicePtr->mutex);
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Init
 *
 * @brief The function initializes the Device and Controller layer
 *
 * @param  phdc_config_ptr[IN]  : Phdc configuration structure pointer
 * @return phdc_handle_t        : When Successfully
 *         Others               : Errors
 ******************************************************************************
 * This function initializes the PHDC Class layer and layers it is dependent on
 *****************************************************************************/
usb_status USB_Class_PHDC_Init
(
uint8_t controller_id, /*[IN]*/
phdc_config_struct_t* phdc_config_ptr, /*[IN]*/
phdc_handle_t * phdcHandle /*[OUT]*/
)
{
    usb_status error = USBERR_ERROR;
    phdc_device_struct_t *devicePtr;

    if (NULL == phdc_config_ptr)
    {
        return USBERR_ERROR;
    }

    error = USB_Phdc_Allocate_Handle(&devicePtr);
    if (USB_OK != error)
    {
        return error;
    }

    devicePtr->mutex = OS_Mutex_create();

#if USBCFG_DEV_COMPOSITE
    devicePtr->class_handle = USB_Class_Get_Class_Handle();
    devicePtr->handle =(usb_device_handle)USB_Class_Get_Ctrler_Handle(devicePtr->class_handle);
    if (NULL == devicePtr->handle)
    {
        devicePtr = NULL;
        return error;
    }
#else
    /* Initialize the device layer*/
    error = usb_device_init(controller_id,(&devicePtr->handle));
    if(error != USB_OK)
    {
        devicePtr = NULL;
        return error;
    }

    /* Initialize the generic class functions */
    devicePtr->class_handle = USB_Class_Init(devicePtr->handle,
    USB_Class_PHDC_Event,USB_PHDC_Requests,
    (void *)devicePtr,
    phdc_config_ptr->desc_callback_ptr);

    if (error != USB_OK)
    {
        devicePtr = NULL;
        return error;
    }

#endif
    /* save the callback pointer */
    OS_Mem_copy(&phdc_config_ptr->phdc_application_callback,
    &devicePtr->phdc_application_callback,
    sizeof(usb_application_callback_struct_t));

    /* save the callback pointer */
    OS_Mem_copy(&phdc_config_ptr->vendor_req_callback,
    &devicePtr->vendor_req_callback,
    sizeof(usb_vendor_req_callback_struct_t));

    /* Save the callback to ask application for class specific params*/
    OS_Mem_copy(&phdc_config_ptr->class_specific_callback,
    &devicePtr->class_specific_callback ,
    sizeof(usb_class_specific_callback_struct_t));

    /* Save the desc  callback to ask application for class specific params*/
    OS_Mem_copy(phdc_config_ptr->desc_callback_ptr,
    &devicePtr->desc_callback ,
    sizeof(usb_desc_request_notify_struct_t));

    devicePtr->phdc_ep_has_data = 0; /* no endpoint has data */
    devicePtr->phdc_endpoint_data.count_rx = 0;
    devicePtr->phdc_endpoint_data.count_tx = 0;
    devicePtr->phdc_endpoint_data.handle = devicePtr->handle;
    devicePtr->service_buff_ptr = NULL;
    devicePtr->user_handle = *phdcHandle;

#if USB_METADATA_SUPPORTED   
    devicePtr->phdc_metadata = FALSE; /* metadata feature disabled */
#endif
    *phdcHandle =(unsigned long)devicePtr;
#if !USBCFG_DEV_COMPOSITE 
    usb_device_postinit(controller_id,devicePtr->handle);
#endif
    return USB_OK;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Deinit
 *
 * @brief 
 *
 * @param handle          :   handle returned by USB_Class_PHDC_Deinit   
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/
usb_status USB_Class_PHDC_Deinit
(
phdc_handle_t handle
)
{
#if !USBCFG_DEV_COMPOSITE
    usb_status error = USB_OK;
#endif
    phdc_device_struct_t* devicePtr;

    if (handle == 0)
    {
        return USBERR_ERROR;
    }

    devicePtr = USB_Phdc_Get_Device_Ptr(handle);

    if (NULL == devicePtr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }

#if !USBCFG_DEV_COMPOSITE   
    /* De-initialize the generic class functions */
    error = USB_Class_Deinit(devicePtr->handle,devicePtr->class_handle);
    if (error == USB_OK)
    {
        /* De-initialize the device layer*/
        error = usb_device_deinit(devicePtr->handle);
    }
#endif
    if (devicePtr->mutex != NULL)
    {
        OS_Mutex_destroy(devicePtr->mutex);
    }
    USB_Phdc_Free_Handle(devicePtr);
    devicePtr = NULL;

    return USB_OK;
}

#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE
/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Cancel
 *
 * @brief 
 *
 * @param handle          :   handle returned by USB_Class_PHDC_Init
 * @param ep_num          :   endpoint num 
 * @param direction        :   direction of the endpoint 
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/
usb_status USB_Class_PHDC_Cancel
(
phdc_handle_t handle,/*[IN]*/
uint8_t ep_num,/*[IN]*/
uint8_t direction
)
{
    phdc_device_struct_t *devicePtr;
    usb_status error = USB_OK;
    if (handle == 0)
    {
        return USBERR_ERROR;
    }

    devicePtr = USB_Phdc_Get_Device_Ptr(handle);
    if (NULL == devicePtr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }
    error = usb_device_cancel_transfer(devicePtr->handle, ep_num, direction);

    return error;
}
#endif

/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Recv_Data
 *
 * @brief This function is used by Application to receive data through PHDC class
 *
 * @param handle     :   Handle returned by USB_Class_PHDC_Init
 * @param ep_num          :   endpoint num 
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer   
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 ******************************************************************************
 * This function is used by Application to send data through PHDC class
 *****************************************************************************/
usb_status USB_Class_PHDC_Recv_Data
(
phdc_handle_t handle,
uint8_t qos, /* [IN] Qos of the transfer */
uint8_t * buff_ptr, /* [IN] buffer to recv */
uint32_t size /* [IN] length of the transfer */
)
{
    phdc_device_struct_t *devicePtr;
    uint8_t rx_index;
    usb_status status = USB_OK;

    devicePtr = USB_Phdc_Get_Device_Ptr(handle);
    if (NULL == devicePtr)
    {
        return USBERR_ERROR;
    }

    /* get the index for the corresponding endpoint(channel) to receive data
     of desired qos */
    for (rx_index = 0; rx_index < PHDC_RX_ENDPOINTS; rx_index++)
    {
        if ((devicePtr->phdc_endpoint_data.ep_rx[rx_index].qos & qos) !=0)
        {
            break;
        }
    }

    /* no channel supports the desired qos */
    if(rx_index == PHDC_RX_ENDPOINTS)
    {
        return USBERR_RX_FAILED;
    }
    status = usb_device_recv_data(devicePtr->handle, devicePtr->phdc_endpoint_data.ep_rx[rx_index].endpoint,buff_ptr,size);

    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_PHDC_Get_Speed
 *
 * @brief This functions get speed from Host.
 *
 * @param handle          :   handle returned by USB_Class_PHDC_Init
 * @param speed           :   speed
 *
 * @return status       
 *         USB_OK         : When Successfull 
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Class_PHDC_Get_Speed
(
phdc_handle_t handle,
uint16_t * speed/* [OUT] the requested error */
)
{
    phdc_device_struct_t * phdc_obj_ptr;
    usb_status error = USB_OK;

    phdc_obj_ptr = (phdc_device_struct_t *)handle;
    if (NULL == phdc_obj_ptr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }
    error = USB_Class_Get_Status(phdc_obj_ptr->class_handle, USB_STATUS_SPEED, speed);

    return error;
}

#endif /*PHDC_CONFIG*/
/* EOF */
