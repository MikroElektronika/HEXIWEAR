/**HEADER********************************************************************
 * 
 * Copyright (c) 2010, 2013 - 2014 Freescale Semiconductor;
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
 * $FileName: usb_audio.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief The file contains USB stack AUDIO layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"

#if USBCFG_DEV_AUDIO
#include "usb_class_internal.h"
#include "usb_audio_config.h"
#include "usb_class_audio.h"
#include "usb_audio.h"

audio_device_struct_t g_audio_class[MAX_AUDIO_DEVICE];

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/
/* Structure holding AUDIO class state information*/

/****************************************************************************
 * Global Variables
 ****************************************************************************/

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
usb_status USB_Audio_Other_Requests(usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size, void* arg);

void USB_Service_Audio_Status_Interrupt(usb_event_struct_t* event, void* arg);
void USB_Service_Audio_Isochronous_OUT(usb_event_struct_t* event, void* arg);
void USB_Service_Audio_Isochronous_IN(usb_event_struct_t* event, void* arg);

/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/*************************************************************************//*!
 *
 * @name  USB_Audio_Allocate_Handle
 *
 * @brief The function reserves entry in device array and returns the index.
 *
 * @param none.
 * @return returns the reserved handle or if no entry found device busy.      
 *
 *****************************************************************************/
static usb_status USB_Audio_Allocate_Handle(audio_device_struct_t** handle)
{
    uint32_t cnt = 0;
    for (; cnt < MAX_AUDIO_DEVICE; cnt++)
    {
        if (g_audio_class[cnt].handle == NULL)
        {
            *handle = (audio_device_struct_t*)&g_audio_class[cnt];
            return USB_OK;
        }
    }
    return USBERR_DEVICE_BUSY;
}
/*************************************************************************//*!
 *
 * @name  USB_Audio_Free_Handle
 *
 * @brief The function releases entry in device array .
 *
 * @param handle  index in device array to be released..
 * @return returns and error code or USB_OK.      
 *
 *****************************************************************************/

static usb_status USB_Audio_Free_Handle(audio_device_struct_t* handle)
{
    int32_t cnt = 0;
    for (; cnt < MAX_AUDIO_DEVICE; cnt++)
    {
        if ((&g_audio_class[cnt]) == handle)
        {
            OS_Mem_zero((void* )handle, sizeof(audio_device_struct_t));
            return USB_OK;
        }
    }
    return USBERR_INVALID_PARAM;
}

/**************************************************************************//*!
 *
 * @name  USB_Service_Audio_Status_Interrupt
 *
 * @brief The function is callback function of Audio Status Interrupt endpoint
 *
 * @param event
 *
 * @return None       
 *
 *****************************************************************************/
void USB_Service_Audio_Status_Interrupt(usb_event_struct_t* event, void* arg)
{
    audio_device_struct_t* audio_obj_ptr;

#if AUDIO_IMPLEMENT_QUEUING
    uint8_t index;
    uint8_t producer, consumer;
    usb_endpoints_t *usb_ep_data;
#endif

    audio_obj_ptr = (audio_device_struct_t*)arg;

#if AUDIO_IMPLEMENT_QUEUING
    usb_ep_data = audio_obj_ptr->usb_ep_data;

    /* map the endpoint num to the index of the endpoint structure */
    for(index = 0; index < usb_ep_data->count; index++)
    {
        if(usb_ep_data->ep[index].ep_num == event->ep_num)
        break;
    }

    producer = audio_obj_ptr->audio_endpoint_data.ep[index].bin_producer;

    /* if there are no errors de-queue the queue and decrement the no. of 
     transfers left, else send the same data again */
    /* de-queue if the send is complete with no error */
    consumer = audio_obj_ptr->audio_endpoint_data.ep[index].bin_consumer;
    if(consumer == (AUDIO_MAX_QUEUE_ELEMS -1))
    {
        audio_obj_ptr->audio_endpoint_data.ep[index].bin_consumer = 0;
    }
    else
    {
        audio_obj_ptr->audio_endpoint_data.ep[index].bin_consumer++;
    }

    audio_obj_ptr->audio_endpoint_data.ep[index].queue_num--;

    if(0 != audio_obj_ptr->audio_endpoint_data.ep[index].queue_num)
    {/*if bin is not empty */

        audio_queue_struct_t queue;
        /* send the next packet in queue */
        consumer = audio_obj_ptr->audio_endpoint_data.ep[index].bin_consumer;
        queue = audio_obj_ptr->audio_endpoint_data.ep[index].queue[consumer];
        (void)USB_Class_Send_Data(audio_obj_ptr->class_handle, queue.channel,
        queue.app_data.data_ptr, queue.app_data.data_size);
    }
#endif

    /* Callback to application */
    if (audio_obj_ptr->class_specific_callback.callback != NULL)
    {
        /* notify the app of the send complete */
        audio_obj_ptr->class_specific_callback.callback(USB_DEV_EVENT_SEND_COMPLETE, USB_REQ_VAL_INVALID,
            &event->buffer_ptr, &event->len, audio_obj_ptr->class_specific_callback.arg);
    }

}

/**************************************************************************//*!
 *
 * @name  USB_Service_Audio_Isochronous_IN
 *
 * @brief The function is callback function of Audio Isochronous IN endpoint
 *
 * @param event
 *
 * @return None       
 *
 *****************************************************************************/
void USB_Service_Audio_Isochronous_IN(usb_event_struct_t* event, void* arg)
{

    audio_app_data_t iso_in_recv;
    uint8_t event_type;
    audio_device_struct_t* audio_obj_ptr = (audio_device_struct_t*)arg;

#if AUDIO_IMPLEMENT_QUEUING
    uint8_t index;
    uint8_t producer, consumer;
    usb_endpoints_t *usb_ep_data = audio_obj_ptr->usb_ep_data;

    audio_queue_struct_t queue;

    /* map the endpoint num to the index of the endpoint structure */
    for(index = 0; index < usb_ep_data->count; index++)
    {
        if(usb_ep_data->ep[index].ep_num ==event->ep_num)
        break;
    }

    producer = audio_obj_ptr->audio_endpoint_data.ep[index].bin_producer;
    /* if there are no errors de-queue the queue and decrement the no. of 
     transfers left, else send the same data again */
    consumer = audio_obj_ptr->audio_endpoint_data.ep[index].bin_consumer;
    if((AUDIO_MAX_QUEUE_ELEMS-1) == consumer)
    {
        audio_obj_ptr->audio_endpoint_data.ep[index].bin_consumer = 0;
    }
    else
    {
        audio_obj_ptr->audio_endpoint_data.ep[index].bin_consumer++;
    }
    consumer = audio_obj_ptr->audio_endpoint_data.ep[index].bin_consumer;
    audio_obj_ptr->audio_endpoint_data.ep[index].queue_num--;

    if(0 != audio_obj_ptr->audio_endpoint_data.ep[index].queue_num)
    {/*if bin is not empty */

        queue = audio_obj_ptr->audio_endpoint_data.ep[index].queue[consumer];

        (void)USB_Class_Send_Data(audio_obj_ptr->class_handle, queue.channel,
        queue.app_data.data_ptr, queue.app_data.data_size);
    }
#endif

    /* Callback to application */
    if (audio_obj_ptr->class_specific_callback.callback != NULL)
    {
        event_type = USB_DEV_EVENT_SEND_COMPLETE;
        iso_in_recv.data_ptr = event->buffer_ptr;
        iso_in_recv.data_size = event->len;
        audio_obj_ptr->class_specific_callback.callback(event_type, USB_REQ_VAL_INVALID, (uint8_t **)&iso_in_recv, NULL,
            audio_obj_ptr->class_specific_callback.arg);
    }

}

/**************************************************************************//*!
 *
 * @name  USB_Service_Audio_Isochronous_OUT
 *
 * @brief The function is callback function of Isochronous Out Endpoint
 *
 * @param event
 *
 * @return None       
 *
 *****************************************************************************/
void USB_Service_Audio_Isochronous_OUT(usb_event_struct_t* event, void* arg)
{
    audio_app_data_t iso_out_recv;
    uint8_t event_type;
    audio_device_struct_t* audio_obj_ptr = (audio_device_struct_t*)arg;
    event_type = USB_DEV_EVENT_DATA_RECEIVED;
    iso_out_recv.data_ptr = event->buffer_ptr;
    iso_out_recv.data_size = event->len;

    /* Callback to application */
    if (audio_obj_ptr->class_specific_callback.callback != NULL)
    {
        audio_obj_ptr->class_specific_callback.callback(event_type, USB_REQ_VAL_INVALID, (uint8_t **)&iso_out_recv, NULL,
            audio_obj_ptr->class_specific_callback.arg);
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Event
 *
 * @brief The function initializes Audio endpoint
 *
 * @param handle          handle to Identify the controller
 * @param event           pointer to event structure
 * @param val             gives the configuration value 
 *
 * @return None       
 *
 *****************************************************************************/
void USB_Class_Audio_Event(uint8_t event, void* val, void* arg)
{
    audio_device_struct_t* devicePtr = (audio_device_struct_t*)arg;
    uint8_t index = 0;
    usb_ep_struct_t* ep_struct_ptr;
#if USBCFG_DEV_COMPOSITE
    usb_composite_info_struct_t* usb_composite_info;
    uint32_t interface_index = 0xFF;
#else
    usb_class_struct_t* usbclass;
#endif

    if (devicePtr == NULL)
    {
#if _DEBUG
        USB_PRINTF("USB_Class_Audio_Event:devicePtr is NULL\n");
#endif  
        return;
    }

    if (event == USB_DEV_EVENT_CONFIG_CHANGED)
    {
#if USBCFG_DEV_COMPOSITE
        uint8_t count = 0;
        //uint8_t component;
        uint8_t type_sel;
        devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr->handle,
        USB_COMPOSITE_INFO, (uint32_t *)&usb_composite_info);
        devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr,
        USB_CLASS_INTERFACE_INDEX_INFO, (uint32_t *)&interface_index);

        if(interface_index == 0xFF)
        {
            USB_PRINTF("not find interface index\n");
            return;
        }

        for(type_sel = 0;type_sel < usb_composite_info->count;type_sel++)
        {
            if ((usb_composite_info->class_handle[type_sel].type == USB_CLASS_AUDIO) && (type_sel == interface_index))
            {
                break;
            }
        }
        if(type_sel >= usb_composite_info->count)
        {
            USB_PRINTF("not find audio interface\n");
            return;
        }

        devicePtr->usb_ep_data = (usb_endpoints_t *) &usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints;
        if (usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.count > MAX_AUDIO_CLASS_EP_NUM)
        {
            USB_PRINTF("too many audio endpoint for the composite class driver\n");
            return;
        }

        for(index = 0; index < usb_composite_info->class_handle[type_sel].interfaces.interface->endpoints.count; index++)
#else
        uint8_t count = 0;
        //uint8_t component;

        devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr->handle,
            USB_CLASS_INFO, (uint32_t *)&usbclass);
        devicePtr->usb_ep_data = (usb_endpoints_t *)&usbclass->interfaces.interface->endpoints;
        if (usbclass->interfaces.interface->endpoints.count > MAX_AUDIO_CLASS_EP_NUM)
        {
            USB_PRINTF("too many audio endpoint for the class driver\n");
            return;
        }

        for (index = 0; index < usbclass->interfaces.interface->endpoints.count; index++)
        #endif
        {
            devicePtr->audio_endpoint_data.ep[index].endpoint = devicePtr->usb_ep_data->ep[index].ep_num;
            devicePtr->audio_endpoint_data.ep[index].type = devicePtr->usb_ep_data->ep[index].type;
#if AUDIO_IMPLEMENT_QUEUING
            devicePtr->audio_endpoint_data.ep[index].bin_consumer = 0x00;
            devicePtr->audio_endpoint_data.ep[index].bin_producer = 0x00;
            devicePtr->audio_endpoint_data.ep[index].queue_num = 0x00;
#endif
        }

        /* get the endpoints from the descriptor module */
        usb_endpoints_t *usb_ep_data = devicePtr->usb_ep_data;

        /* initialize all non control endpoints */
        while (count < usb_ep_data->count)
        {
            ep_struct_ptr = (usb_ep_struct_t*)&usb_ep_data->ep[count];

            (void)usb_device_init_endpoint(devicePtr->handle,
                ep_struct_ptr, TRUE);

            /* register callback service for Non Control EndPoints */
            switch(ep_struct_ptr->type)
            {
            case USB_INTERRUPT_PIPE:
                (void)usb_device_register_service(devicePtr->handle,
                    (uint8_t)((uint8_t)(USB_SERVICE_EP0 + ep_struct_ptr->ep_num) | (uint8_t)((ep_struct_ptr->direction << 7))),
                    USB_Service_Audio_Status_Interrupt, (void *)devicePtr);
                break;
            case USB_ISOCHRONOUS_PIPE:
                if (ep_struct_ptr->direction == USB_RECV)
                {
                    (void)usb_device_register_service(devicePtr->handle,
                        (uint8_t)((uint8_t)(USB_SERVICE_EP0 + ep_struct_ptr->ep_num) | ((uint8_t)(ep_struct_ptr->direction << 7))),
                        USB_Service_Audio_Isochronous_OUT, (void *)devicePtr);
                }
                else
                {
                    (void)usb_device_register_service(devicePtr->handle,
                        (uint8_t)((uint8_t)(USB_SERVICE_EP0 + ep_struct_ptr->ep_num) | ((uint8_t)(ep_struct_ptr->direction << 7))),
                        USB_Service_Audio_Isochronous_IN, (void *)devicePtr);
                }
                break;
            default:
                break;
            }

            count++;
        }/* EndWhile */
    }
    if (event == USB_DEV_EVENT_ENUM_COMPLETE)
    {

    }
    else if (event == USB_DEV_EVENT_BUS_RESET)
    {
    }
    if (devicePtr->audio_application_callback.callback != NULL)
    {
        devicePtr->audio_application_callback.callback(event,
            val, devicePtr->audio_application_callback.arg);
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Get_Cur_Audio_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Get_Cur_Audio_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    usb_status error;
    int32_t cmd = -1;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    error = USBERR_INVALID_REQ_TYPE;
    switch(setup_packet->value >> 8)
    {
    case MUTE_CONTROL:
        *size = 1;
        cmd = GET_CUR_MUTE_CONTROL;
        break;
    case VOLUME_CONTROL:
        *size = 2;
        cmd = GET_CUR_VOLUME_CONTROL;
        break;
    case BASS_CONTROL:
        *size = 1;
        cmd = GET_CUR_BASS_CONTROL;
        break;
    case MID_CONTROL:
        *size = 1;
        cmd = GET_CUR_MID_CONTROL;
        break;
    case TREBLE_CONTROL:
        *size = 1;
        cmd = GET_CUR_TREBLE_CONTROL;
        break;
    case GRAPHIC_EQUALIZER_CONTROL:
        *size = 5;
        cmd = GET_CUR_GRAPHIC_EQUALIZER_CONTROL;
        break;
    case AUTOMATIC_GAIN_CONTROL:
        *size = 1;
        cmd = GET_CUR_AUTOMATIC_GAIN_CONTROL;
        break;
    case DELAY_CONTROL:
        *size = 2;
        cmd = GET_CUR_DELAY_CONTROL;
        break;
    case BASS_BOOST_CONTROL:
        *size = 1;
        cmd = GET_CUR_BASS_BOOST_CONTROL;
        break;
    case LOUDNESS_CONTROL:
        *size = 1;
        cmd = GET_CUR_LOUDNESS_CONTROL;
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        if (audio_obj_ptr->class_specific_callback.callback != NULL)
        {

            /* notify the application of the class request.*/
            /* give control to the application */
            error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
                data, size, audio_obj_ptr->class_specific_callback.arg);
        }
    }

    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Get_Min_Audio_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Get_Min_Audio_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    usb_status error;
    int32_t cmd = -1;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    error = USBERR_INVALID_REQ_TYPE;
    switch(setup_packet->value >> 8)
    {
    case VOLUME_CONTROL:
        *size = 2;
        cmd = GET_MIN_VOLUME_CONTROL;
        break;
    case BASS_CONTROL:
        *size = 1;
        cmd = GET_MIN_BASS_CONTROL;
        break;
    case MID_CONTROL:
        *size = 1;
        cmd = GET_MIN_MID_CONTROL;
        break;
    case TREBLE_CONTROL:
        *size = 1;
        cmd = GET_MIN_TREBLE_CONTROL;
        break;
    case GRAPHIC_EQUALIZER_CONTROL:
        *size = 5;
        cmd = GET_MIN_GRAPHIC_EQUALIZER_CONTROL;
        break;
    case DELAY_CONTROL:
        *size = 2;
        cmd = GET_MIN_DELAY_CONTROL;
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
            data, size, audio_obj_ptr->class_specific_callback.arg);
    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Get_Max_Audio_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Get_Max_Audio_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    usb_status error;
    int32_t cmd = -1;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    error = USBERR_INVALID_REQ_TYPE;
    switch(setup_packet->value >> 8)
    {
    case VOLUME_CONTROL:
        *size = 2;
        cmd = GET_MAX_VOLUME_CONTROL;
        break;
    case BASS_CONTROL:
        *size = 1;
        cmd = GET_MAX_BASS_CONTROL;
        break;
    case MID_CONTROL:
        *size = 1;
        cmd = GET_MAX_MID_CONTROL;
        break;
    case TREBLE_CONTROL:
        *size = 1;
        cmd = GET_MAX_TREBLE_CONTROL;
        break;
    case GRAPHIC_EQUALIZER_CONTROL:
        *size = 5;
        cmd = GET_MAX_GRAPHIC_EQUALIZER_CONTROL;
        break;
    case DELAY_CONTROL:
        *size = 2;
        cmd = GET_MAX_DELAY_CONTROL;
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
            data, size, audio_obj_ptr->class_specific_callback.arg);
    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Get_Res_Audio_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Get_Res_Audio_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    usb_status error;
    int32_t cmd = -1;
    error = USBERR_INVALID_REQ_TYPE;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    switch(setup_packet->value >> 8)
    {
    case VOLUME_CONTROL:
        *size = 2;
        cmd = GET_RES_VOLUME_CONTROL;
        break;
    case BASS_CONTROL:
        *size = 1;
        cmd = GET_RES_BASS_CONTROL;
        break;
    case MID_CONTROL:
        *size = 1;
        cmd = GET_RES_MID_CONTROL;
        break;
    case TREBLE_CONTROL:
        *size = 1;
        cmd = GET_RES_TREBLE_CONTROL;
        break;
    case GRAPHIC_EQUALIZER_CONTROL:
        *size = 5;
        cmd = GET_RES_GRAPHIC_EQUALIZER_CONTROL;
        break;
    case DELAY_CONTROL:
        *size = 2;
        cmd = GET_RES_DELAY_CONTROL;
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
            data, size, audio_obj_ptr->class_specific_callback.arg);
    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Audio_Get_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Audio_Get_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    usb_status error = USBERR_INVALID_REQ_TYPE;
    /* Select SET request Control Feature Unit Module */
    switch(setup_packet->request)
    {
    case GET_CUR:
        error = USB_Get_Cur_Audio_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
        break;
    case GET_MIN:
        error = USB_Get_Min_Audio_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
        break;
    case GET_MAX:
        error = USB_Get_Max_Audio_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
        break;
    case GET_RES:
        error = USB_Get_Res_Audio_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
        break;
    default:
        break;
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Audio_Get_Control_Terminal
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Audio_Get_Control_Terminal
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    usb_status error = USBERR_INVALID_REQ_TYPE;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    switch(setup_packet->request)
    {
    /* Copy Protect Control only supports the CUR attribute!*/
    case GET_CUR:
        *size = 1;
        if ((setup_packet->value >> 8) == COPY_PROTECT_CONTROL)
        {

            error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, (uint8_t)GET_CUR_COPY_PROTECT_CONTROL,
                data, size, audio_obj_ptr->class_specific_callback.arg);
        }
        break;
    default:
        break;
    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Get_Request_Interface
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Get_Request_Interface
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    int32_t i;
    usb_status error = USBERR_INVALID_REQ_TYPE;
    audio_units_struct_t* entity_desc_data;
    audio_ut_struct_t* ut_struct;
    /* get the I/O Interface and Feature from the descriptor module */
    entity_desc_data = audio_obj_ptr->usb_ut_data;
    for (i = 0; i < entity_desc_data->count; i++)
    {
        ut_struct = (&entity_desc_data->put[i]);
        if ((setup_packet->index >> 8) == ut_struct->unit_id)
        {
            switch(ut_struct->type)
            {
            case AUDIO_CONTROL_INPUT_TERMINAL:
                error = USB_Audio_Get_Control_Terminal(audio_obj_ptr, setup_packet, data, size);
                break;
            case AUDIO_CONTROL_FEATURE_UNIT:
                error = USB_Audio_Get_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
                break;
            default:
                break;
            }
        }
    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Set_Cur_Audio_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Set_Cur_Audio_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t ** data,
    uint32_t* size
    )
{
    int32_t cmd = -1;
    usb_status error = USBERR_INVALID_REQ_TYPE;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    *size = 0;
    switch(setup_packet->value >> 8)
    {
    case MUTE_CONTROL:
        cmd = SET_CUR_MUTE_CONTROL;
        break;
    case VOLUME_CONTROL:
        cmd = SET_CUR_VOLUME_CONTROL;
        break;
    case BASS_CONTROL:
        cmd = SET_CUR_BASS_CONTROL;
        break;
    case MID_CONTROL:
        cmd = SET_CUR_MID_CONTROL;
        break;
    case TREBLE_CONTROL:
        cmd = SET_CUR_TREBLE_CONTROL;
        break;
    case GRAPHIC_EQUALIZER_CONTROL:
        cmd = SET_CUR_GRAPHIC_EQUALIZER_CONTROL;
        break;
    case AUTOMATIC_GAIN_CONTROL:
        cmd = SET_CUR_AUTOMATIC_GAIN_CONTROL;
        break;
    case DELAY_CONTROL:
        cmd = SET_CUR_DELAY_CONTROL;
        break;
    case BASS_BOOST_CONTROL:
        cmd = SET_CUR_BASS_BOOST_CONTROL;
        break;
    case LOUDNESS_CONTROL:
        cmd = SET_CUR_LOUDNESS_CONTROL;
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
            data, size, audio_obj_ptr->class_specific_callback.arg);
    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Set_Min_Audio_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Set_Min_Audio_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    usb_status error = USBERR_INVALID_REQ_TYPE;
    int32_t cmd = -1;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    *size = 0;
    switch(setup_packet->value >> 8)
    {
    case VOLUME_CONTROL:
        cmd = SET_MIN_VOLUME_CONTROL;
        break;
    case BASS_CONTROL:
        cmd = SET_MIN_BASS_CONTROL;
        break;
    case MID_CONTROL:
        cmd = SET_MIN_MID_CONTROL;
        break;
    case TREBLE_CONTROL:
        cmd = SET_MIN_TREBLE_CONTROL;
        break;
    case GRAPHIC_EQUALIZER_CONTROL:
        cmd = SET_MIN_GRAPHIC_EQUALIZER_CONTROL;
        break;
    case DELAY_CONTROL:
        cmd = SET_MIN_DELAY_CONTROL;
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
            data, size, audio_obj_ptr->class_specific_callback.arg);
    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Set_Max_Audio_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Set_Max_Audio_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    int32_t cmd = -1;
    usb_status error = USBERR_INVALID_REQ_TYPE;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    *size = 0;
    switch(setup_packet->value >> 8)
    {
    case VOLUME_CONTROL:
        cmd = SET_MAX_VOLUME_CONTROL;
        break;
    case BASS_CONTROL:
        cmd = SET_MAX_BASS_CONTROL;
        break;
    case MID_CONTROL:
        cmd = SET_MAX_MID_CONTROL;
        break;
    case TREBLE_CONTROL:
        cmd = SET_MAX_TREBLE_CONTROL;
        break;
    case GRAPHIC_EQUALIZER_CONTROL:
        cmd = SET_MAX_GRAPHIC_EQUALIZER_CONTROL;
        break;
    case DELAY_CONTROL:
        cmd = SET_MAX_DELAY_CONTROL;
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
            data, size, audio_obj_ptr->class_specific_callback.arg);
    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Set_Res_Audio_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Set_Res_Audio_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    int32_t cmd = -1;
    usb_status error = USBERR_INVALID_REQ_TYPE;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    *size = 0;
    switch(setup_packet->value >> 8)
    {
    case VOLUME_CONTROL:
        cmd = SET_RES_VOLUME_CONTROL;
        break;
    case BASS_CONTROL:
        cmd = SET_RES_BASS_CONTROL;
        break;
    case MID_CONTROL:
        cmd = SET_RES_MID_CONTROL;
        break;
    case TREBLE_CONTROL:
        cmd = SET_RES_TREBLE_CONTROL;
        break;
    case GRAPHIC_EQUALIZER_CONTROL:
        cmd = SET_RES_GRAPHIC_EQUALIZER_CONTROL;
        break;
    case DELAY_CONTROL:
        cmd = SET_RES_DELAY_CONTROL;
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
            data, size, audio_obj_ptr->class_specific_callback.arg);

    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Audio_Set_Feature_Unit
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Audio_Set_Feature_Unit
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    usb_status error = USBERR_INVALID_REQ_TYPE;
    /* Select SET request Control Feature Unit Module */
    switch(setup_packet->request)
    {
    case SET_CUR:
        error = USB_Set_Cur_Audio_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
        break;
    case SET_MIN:
        error = USB_Set_Min_Audio_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
        break;
    case SET_MAX:
        error = USB_Set_Max_Audio_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
        break;
    case SET_RES:
        error = USB_Set_Res_Audio_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
        break;
    default:
        break;
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Audio_Set_Control_Terminal
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Audio_Set_Control_Terminal
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    usb_status error = USBERR_INVALID_REQ_TYPE;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    *size = 0;
    switch(setup_packet->request)
    {
    /* Copy Protect Control only supports the CUR attribute!*/
    case SET_CUR:
        if ((setup_packet->value >> 8) == COPY_PROTECT_CONTROL)
        {

            error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, SET_CUR_COPY_PROTECT_CONTROL,
                data, size, audio_obj_ptr->class_specific_callback.arg);
        }
        break;
    default:
        break;
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Set_Request_Interface
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Set_Request_Interface
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    int32_t i;
    usb_status error = USBERR_INVALID_REQ_TYPE;
    audio_units_struct_t* entity_desc_data;
    audio_ut_struct_t* ut_struct;
    /* get the I/O Interface and Feature  from the descriptor module */
    entity_desc_data = audio_obj_ptr->usb_ut_data;
    for (i = 0; i < entity_desc_data->count; i++)
    {
        ut_struct = (&entity_desc_data->put[i]);
        if ((setup_packet->index >> 8) == ut_struct->unit_id)
        {
            switch(ut_struct->type)
            {
            case AUDIO_CONTROL_OUTPUT_TERMINAL:
                /*Select SET Request Control Input Terminal Module */
                error = USB_Audio_Set_Control_Terminal(audio_obj_ptr, setup_packet, data, size);
                break;
            case AUDIO_CONTROL_FEATURE_UNIT:
                /* Select SET request Control Feature Unit Module */
                error = USB_Audio_Set_Feature_Unit(audio_obj_ptr, setup_packet, data, size);
                break;
            default:
                break;
            }
        }
    }
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Set_Request_Endpoint
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Set_Request_Endpoint
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    int32_t cmd = -1;
    usb_status error = USBERR_INVALID_REQ_TYPE;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    *size = 0;
    switch(setup_packet->request)
    {
    case SET_CUR:
        switch(setup_packet->value >> 8)
        {
        case SAMPLING_FREQ_CONTROL:
            cmd = SET_CUR_SAMPLING_FREQ_CONTROL;
            break;
        case PITCH_CONTROL:
            cmd = SET_CUR_PITCH_CONTROL;
            break;
        default:
            break;
        }
        break;
    case SET_MIN:
        switch(setup_packet->value >> 8)
        {
        case SAMPLING_FREQ_CONTROL:
            cmd = SET_MIN_SAMPLING_FREQ_CONTROL;
            break;
        default:
            break;
        }
        break;
    case SET_MAX:
        switch(setup_packet->value >> 8)
        {
        case SAMPLING_FREQ_CONTROL:
            cmd = SET_MAX_SAMPLING_FREQ_CONTROL;
            break;
        default:
            break;
        }
        break;
    case SET_RES:
        switch(setup_packet->value >> 8)
        {
        case SAMPLING_FREQ_CONTROL:
            cmd = SET_RES_SAMPLING_FREQ_CONTROL;
            break;
        default:
            break;
        }
        break;
    case SET_MEM:
        *size = setup_packet->length;

        if (audio_obj_ptr->class_specific_callback.callback != NULL)
        {
            error = audio_obj_ptr->class_specific_callback.callback(
                /* request type */
                setup_packet->request,
                setup_packet->value,
                /* pointer to the data */
                data,
                /* size of the transfer */
                size, audio_obj_ptr->class_specific_callback.arg);
        }
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
            data, size, audio_obj_ptr->class_specific_callback.arg);
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Get_Request_Endpoint
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param audio_obj_ptr:    Pointer to Audio class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Get_Request_Endpoint
(
    audio_device_struct_t* audio_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size
    )
{
    int32_t cmd = -1;
    usb_status error = USBERR_INVALID_REQ_TYPE;
    if (size == NULL)
    {
        return USBERR_ERROR;
    }
    switch(setup_packet->request)
    {
    case GET_CUR:
        switch(setup_packet->value >> 8)
        {
        case SAMPLING_FREQ_CONTROL:
            *size = 3;
            cmd = GET_CUR_SAMPLING_FREQ_CONTROL;
            break;
        case PITCH_CONTROL:
            *size = 1;
            cmd = GET_CUR_PITCH_CONTROL;
            break;
        default:
            break;
        }
        break;
    case GET_MIN:
        switch(setup_packet->value >> 8)
        {
        case SAMPLING_FREQ_CONTROL:
            *size = 3;
            cmd = GET_MIN_SAMPLING_FREQ_CONTROL;
            break;
        default:
            break;
        }
        break;
    case GET_MAX:
        switch(setup_packet->value >> 8)
        {
        case SAMPLING_FREQ_CONTROL:
            *size = 3;
            cmd = GET_MAX_SAMPLING_FREQ_CONTROL;
            break;
        default:
            break;
        }
        break;
    case GET_RES:
        switch(setup_packet->value >> 8)
        {
        case SAMPLING_FREQ_CONTROL:
            cmd = GET_RES_SAMPLING_FREQ_CONTROL;
            *size = 3;
            break;
        default:
            break;
        }
        break;
    case GET_MEM:
        *size = setup_packet->length;
        if (audio_obj_ptr->class_specific_callback.callback != NULL)
        {
            error = audio_obj_ptr->class_specific_callback.callback(
                /* request type */
                setup_packet->request,
                setup_packet->value,
                /* pointer to the data */
                data,
                /* size of the transfer */
                size, audio_obj_ptr->class_specific_callback.arg);
        }
        break;
    default:
        break;
    }
    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface, cmd,
            data, size, audio_obj_ptr->class_specific_callback.arg);

    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Audio_Other_Requests
 *
 * @brief The function provides flexibility to add class and vendor specific
 *        requests 
 *
 * @param handle
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned    
 *
 * @return error:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status USB_Audio_Requests
(
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t* size,
    void* arg
    )
{
    usb_status error;
#if USBCFG_AUDIO_CLASS_2_0 
    uint8_t i;
    uint32_t cmd = 0;
    audio_ut_struct_t* ut_struct;
    audio_units_struct_t* entity_desc_data;
#endif  
    audio_device_struct_t* audio_obj_ptr = (audio_device_struct_t*)arg;
    error = USBERR_INVALID_REQ_TYPE;
    *data = ((uint8_t*)setup_packet) + USB_SETUP_PKT_SIZE;

    if (audio_obj_ptr == NULL)
    {
#if _DEBUG
        USB_PRINTF("USB_Audio_Other_Requests:audio_obj_ptr is NULL\n");
#endif  
        return error;
    }
    audio_obj_ptr->current_interface = (uint8_t)setup_packet->index;
#if USBCFG_AUDIO_CLASS_2_0
    entity_desc_data = audio_obj_ptr->usb_ut_data;
    for(i=0;i<entity_desc_data->count; i++)
    {
        ut_struct=(&entity_desc_data->put[i]);
        if((setup_packet->index >>8) == ut_struct->unit_id)
        {
            switch(ut_struct->type)
            {
                case AUDIO_CONTROL_OUTPUT_TERMINAL:
                break;
                case AUDIO_CONTROL_FEATURE_UNIT:
                break;

                case AUDIO_CONTROL_CLOCK_SOURCE_UNIT:
                if(((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_DIR_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_DIR_IN))
                {
                    switch(setup_packet->value>>8)
                    {
                        case CS_SAM_FREQ_CONTROL:
                        if (setup_packet->request == REQUEST_CUR)
                        {
                            cmd = GET_CUR_CLOCK_VALID_CONTROL;
                        }
                        else if (setup_packet->request == REQUEST_RANGE)
                        {
                            cmd = GET_RANGE_SAM_FREQ_CONTROL;
                        }
                        break;
                        case CS_CLOCK_VALID_CONTROL:
                        cmd = GET_CUR_CLOCK_VALID_CONTROL;
                        break;
                        default:
                        break;
                    }
                }
                else if(((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_DIR_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_DIR_OUT))
                {
                    switch(setup_packet->value>>8)
                    {
                        case CS_SAM_FREQ_CONTROL:
                        cmd = SET_CUR_SAM_FREQ_CONTROL;
                        *size = 0;
                        break;
                        case CS_CLOCK_VALID_CONTROL:
                        cmd = SET_CUR_CLOCK_VALID_CONTROL;
                        *size = 0;
                        break;
                        default:
                        break;
                    }
                    *size = 0;
                }
                break;
                default:
                break;
            }
        }
    }

    if (cmd > 0)
    {
        error = audio_obj_ptr->class_specific_callback.callback(audio_obj_ptr->current_interface,cmd,
        data,size,audio_obj_ptr->class_specific_callback.arg);
    }
    return error;
#else
    if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_POS) ==
    USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_CLASS)
    { /* class request so handle it here */

        switch(setup_packet->request_type)
        {
        /* Set I/O Interface and Feature Unit */
        case SET_REQUEST_ITF:
            error = USB_Set_Request_Interface(audio_obj_ptr, setup_packet, data, size);
            break;
            /*Get I/O Interface and Feature Unit */
        case GET_REQUEST_ITF:
            error = USB_Get_Request_Interface(audio_obj_ptr, setup_packet, data, size);
            break;
            /* Set Requests of Endpoint */
        case SET_REQUEST_EP:
            error = USB_Set_Request_Endpoint(audio_obj_ptr, setup_packet, data, size);
            break;
            /* Get Requests of Endpoint */
        case GET_REQUEST_EP:
            error = USB_Get_Request_Endpoint(audio_obj_ptr, setup_packet, data, size);
            break;
        default:
            *size = 0;
            break;
        } /* End of switch */
    }
    else if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_POS) ==
    USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_VENDOR)

    { /* vendor specific request  */
        if (audio_obj_ptr->vendor_req_callback.callback != NULL)
        {
            error = audio_obj_ptr->vendor_req_callback.callback(setup_packet,
                data, size, audio_obj_ptr->vendor_req_callback.arg);
        }
    }
    return error;
#endif
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Init
 *
 * @brief The function initializes the Device and Controller layer
 *
 * @param *audio_config_ptr[IN]:  This structure contains configuration parameter
 *                              send by APP to configure audio class.
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 ******************************************************************************
 *
 *This function initializes the Audio Class layer and layers it is dependent on
 *
 *****************************************************************************/

usb_status USB_Class_Audio_Init
(
    uint8_t controller_id,
    audio_config_struct_t* audio_config_ptr,
    audio_handle_t* audioHandle

    )
{
    usb_status error;

    uint8_t index;
    audio_device_struct_t* devicePtr = NULL;
    audio_units_struct_t *p_usb_data_ut = NULL;

    if (NULL == audio_config_ptr)
    {
        return USBERR_ERROR;
    }

    error = USB_Audio_Allocate_Handle(&devicePtr);

    if (USB_OK != error)
    {
        return error;
    }

#if USBCFG_DEV_COMPOSITE
    devicePtr->class_handle = (class_handle_t)USB_Class_Get_Class_Handle();
    devicePtr->handle = (usb_device_handle)USB_Class_Get_Ctrler_Handle(devicePtr->class_handle);
    if(NULL == devicePtr->handle)
    {
        return USBERR_INIT_FAILED;
    }
#else
    /* Initialize the device layer*/
    error = usb_device_init(controller_id, &devicePtr->handle);
    if (error != USB_OK)
    {
        devicePtr = NULL;
        return USBERR_INIT_FAILED;
    }
    devicePtr->class_handle = USB_Class_Init(devicePtr->handle,
        USB_Class_Audio_Event, USB_Audio_Requests, (void *)devicePtr,
        audio_config_ptr->desc_callback_ptr);
#endif
    /* save the callback pointer */
    OS_Mem_copy(&audio_config_ptr->audio_application_callback,
        &devicePtr->audio_application_callback, sizeof(usb_application_callback_struct_t));

    /* save the callback pointer */
    OS_Mem_copy(&audio_config_ptr->vendor_req_callback,
        &devicePtr->vendor_req_callback, sizeof(usb_vendor_req_callback_struct_t));

    /* Save the callback to ask application for class specific params*/
    OS_Mem_copy(&audio_config_ptr->class_specific_callback,
        &devicePtr->class_specific_callback, sizeof(usb_class_specific_callback_struct_t));

    /* Save the desc  callback to ask application for class specific params*/
    OS_Mem_copy(audio_config_ptr->desc_callback_ptr,
        &devicePtr->desc_callback, sizeof(usb_desc_request_notify_struct_t));

    devicePtr->desc_callback.get_desc_entity((uint32_t)devicePtr->handle,
        USB_AUDIO_UNITS, (uint32_t *)&p_usb_data_ut);

    for (index = 0; index < p_usb_data_ut->count; index++)
    {
        devicePtr->audio_ut_data.ut[index].unit_id = p_usb_data_ut->put[index].unit_id;
        devicePtr->audio_ut_data.ut[index].type = p_usb_data_ut->put[index].type;
    }
    devicePtr->usb_ut_data = p_usb_data_ut;

    *audioHandle = (uint32_t)devicePtr;
    devicePtr->user_handle = *audioHandle;
#if !USBCFG_DEV_COMPOSITE 
    usb_device_postinit(controller_id, devicePtr->handle);
#endif
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Deinit
 *
 * @brief 
 *
 * @param handle          :   handle returned by USB_Class_Audio_Init
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/
usb_status USB_Class_Audio_Deinit
(
    audio_handle_t handle
    )
{
#if !USBCFG_DEV_COMPOSITE
    usb_status error = USB_OK;
#endif
    audio_device_struct_t* devicePtr;

    devicePtr = (audio_device_struct_t*)handle;

    if (NULL == devicePtr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }
#if !USBCFG_DEV_COMPOSITE
    if (error == USB_OK)
    {
        /* De-initialize the generic class functions */
        error = USB_Class_Deinit(devicePtr->handle, devicePtr->class_handle);
    }
    if (error == USB_OK)
    {
        /* De-initialize the device layer*/
        error = usb_device_deinit(devicePtr->handle);
    }
#endif

    USB_Audio_Free_Handle(devicePtr);
    return USB_OK;
}

#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE
/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Cancel
 *
 * @brief 
 *
 * @param handle          :   handle returned by USB_Class_Audio_Init
 * @param ep_num          :   endpoint num 
 * @param direction        :   direction of the endpoint 
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/

usb_status USB_Class_Audio_Cancel
(
    audio_handle_t handle,/*[IN]*/
    uint8_t ep_num,/*[IN]*/
    uint8_t direction
    )
{
    usb_status error = USB_OK;
    audio_device_struct_t* devicePtr;

    devicePtr = (audio_device_struct_t*)handle;

    if (NULL == devicePtr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }
    error = usb_device_cancel_transfer(devicePtr->handle,
        ep_num, direction);

    return error;

}
#endif

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Send_Data
 *
 * @brief 
 *
 * @param handle          :   handle returned by USB_Class_Audio_Init
 * @param ep_num          :   endpoint num 
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer   
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/
usb_status USB_Class_Audio_Send_Data(
    audio_handle_t handle,/*[IN]*/
    uint8_t ep_num,/*[IN]*/
    uint8_t * app_buff,/*[IN]*/
    uint32_t size /*[IN]*/
    )
{
#if AUDIO_IMPLEMENT_QUEUING
    uint8_t index;
    uint8_t producer, consumer,queue_num;
    usb_endpoints_t *ep_desc_data;
    audio_queue_struct_t* queue_tmp;
#endif

    usb_status error = USB_OK;
    audio_device_struct_t* devicePtr;
    //PTR_usb_class_audio_queue_t queue_tmp;  

    devicePtr = (audio_device_struct_t*)handle;

#if AUDIO_IMPLEMENT_QUEUING
    ep_desc_data = devicePtr->usb_ep_data;

    /* map the endpoint num to the index of the endpoint structure */
    for(index = 0; index < ep_desc_data->count; index++)
    {
        if(ep_desc_data->ep[index].ep_num == ep_num)
        break;
    }

    producer = devicePtr->audio_endpoint_data.ep[index].bin_producer;
    consumer = devicePtr->audio_endpoint_data.ep[index].bin_consumer;
    queue_num = devicePtr->audio_endpoint_data.ep[index].queue_num;

    if(queue_num != AUDIO_MAX_QUEUE_ELEMS)
    {/* the bin is not full*/
        /* put all send request parameters in the endpoint data structure */
        queue_tmp = &(devicePtr->audio_endpoint_data.ep[index].queue[producer]);
        queue_tmp->channel = ep_num;
        queue_tmp->app_data.data_ptr = app_buff;
        queue_tmp->app_data.data_size = size;
        queue_tmp->handle = devicePtr->handle;

        /* increment producer bin by 1*/
        if (producer == (AUDIO_MAX_QUEUE_ELEMS -1))
        {
            devicePtr->audio_endpoint_data.ep[index].bin_producer = 0;
        }
        else
        {
            devicePtr->audio_endpoint_data.ep[index].bin_producer++;
        }
        devicePtr->audio_endpoint_data.ep[index].queue_num++;

        if(devicePtr->audio_endpoint_data.ep[index].queue_num == 1)
        {
#endif  
    /*send the IO if there is only one element in the queue */
    error = USB_Class_Send_Data(devicePtr->class_handle, ep_num, app_buff, size);
#if AUDIO_IMPLEMENT_QUEUING
}
}
else /* bin is full */
{
error = USBERR_DEVICE_BUSY;
}
#endif

    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Recv_Data
 *
 * @brief This functions receives Data from Host.
 *
 * @param handle          :   handle returned by USB_Class_Audio_Init
 * @param ep_num          :   endpoint num 
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer   
 *
 * @return status       
 *         USB_OK         : When Successfully
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Class_Audio_Recv_Data
(
    audio_handle_t audio_handle,
    uint8_t ep_num,
    uint8_t * buff_ptr, /* [IN] buffer to recv */
    uint32_t size /* [IN] length of the transfer */
    )
{
    audio_device_struct_t* audio_obj_ptr;
    usb_status error = USB_OK;

    audio_obj_ptr = (audio_device_struct_t*)audio_handle;

    error = usb_device_recv_data(audio_obj_ptr->handle, ep_num, buff_ptr, size);

    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Get_Speed
 *
 * @brief This functions get speed from Host.
 *
 * @param handle          :   handle returned by USB_Class_Audio_Init
 * @param speed           :   speed
 *
 * @return status       
 *         USB_OK         : When Successfull 
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Class_Audio_Get_Speed
(
    audio_handle_t audio_handle,
    uint16_t * speed/* [OUT] the requested error */
    )
{
    audio_device_struct_t* audio_obj_ptr;
    usb_status error = USB_OK;

    audio_obj_ptr = (audio_device_struct_t*)audio_handle;

    if (NULL == audio_obj_ptr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }
    error = USB_Class_Get_Status(audio_obj_ptr->class_handle, USB_STATUS_SPEED, speed);

    return error;
}

#endif /*AUDIO_CONFIG*/
/* EOF */
