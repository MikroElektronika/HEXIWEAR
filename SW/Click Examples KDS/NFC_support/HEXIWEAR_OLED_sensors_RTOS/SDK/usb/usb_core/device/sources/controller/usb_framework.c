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
 * $FileName: usb_framework.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief The file contains USB stack framework module implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#if USBCFG_DEV_KHCI || USBCFG_DEV_EHCI
#include "usb.h"
#include "usb_device_stack_interface.h"
#include "usb_framework.h"

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
//usb_class_fw_object_struct_t*  usb_class_fw_object[USB_MAX_CLASS_FW_OBJECT];
#ifdef DELAYED_PROCESSING
usb_event_struct_t g_f_event;
bool g_control_pending=FALSE;
#endif
#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)) 
static bool g_validate_request[MAX_STRD_REQ][3] =
#else
static uint8_t g_validate_request[MAX_STRD_REQ][3] =
#endif

{ 
  {1,   1,   0,}, /*USB_Strd_Req_Get_Status*/
         /* configured state: valid for existing interfaces/endpoints
            address state   : valid only for interface or endpoint 0
            default state   : not specified
         */ 
  {1,   1,   0,}, /* Clear Feature */
         /* configured state: valid only for device in configured state
            address state   : valid only for device (in address state), 
                              interface and endpoint 0 
            default state   : not specified
         */
  {0,   0,   0,}, /*reserved for future use*/
         /* configured state: request not supported
            address state   : request not supported
            default state   : request not supported
         */ 
#ifdef USBCFG_OTG
  {1,   1,   1,}, /* Set Feature */
        /*  configured state: valid only for device in configured state
            address state   : valid only for interface or endpoint 0
            default state   : not specified
        */
#else 
  {1,   1,   0,}, /* Set Feature */
          /*  configured state: valid only for device in configured state
              address state   : valid only for interface or endpoint 0
              default state   : not specified
          */
#endif
  {0,   0,   0,},/*reserved for future use*/
        /*  configured state: request not supported            
            address state   : request not supported
            default state   : request not supported
         */ 
  {0,   1,   1,}, /*USB_Strd_Req_Set_Address*/
        /*  configured state: not specified            
            address state   : changes to default state if specified addr == 0,
                              but uses newly specified address
            default state   : changes to address state if specified addr != 0
         */
  {1,   1,   1,}, /*USB_Strd_Req_Get_Descriptor*/
         /* configured state: valid request            
            address state   : valid request
            default state   : valid request
         */
  {0,   0,   0,}, /*Set Descriptor*/
         /* configured state: request not supported
            address state   : request not supported
            default state   : request not supported
         */
  {1,   1,   0,}, /*USB_Strd_Req_Get_Config*/
         /* configured state: bConfiguration Value of current config returned
            address state   : value zero must be returned
            default state   : not specified            
         */
  {1,   1,   0,}, /*USB_Strd_Req_Set_Config*/
         /* configured state: If the specified configuration value is zero, 
                              then the device enters the Address state.If the 
                              specified configuration value matches the 
                              configuration value from a config descriptor, 
                              then that config is selected and the device
                              remains in the Configured state. Otherwise, the 
                              device responds with a Request Error.
         
            address state   : If the specified configuration value is zero, 
                              then the device remains in the Address state. If 
                              the specified configuration value matches the 
                              configuration value from a configuration 
                              descriptor, then that configuration is selected 
                              and the device enters the Configured state. 
                              Otherwise,response is Request Error.
            default state   : not specified
         */
  {1,   0,   0,}, /*USB_Strd_Req_Get_Interface*/
         /* configured state: valid request          
            address state   : request error
            default state   : not specified
         */
  {1,   0,   0,}, /*USB_Strd_Req_Set_Interface*/
         /* configured state: valid request
            address state   : request error
            default state   : not specified
         */
  {1,   0,   0,}, /*USB_Strd_Req_Sync_Frame*/
         /* configured state: valid request
            address state   : request error
            default state   : not specified
         */ 
};

/****************************************************************************
 * Global Functions
 ****************************************************************************/

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
usb_class_fw_handle USB_Framework_Init( usb_device_handle handle, /*[IN]*/
usb_device_notify_t class_callback,/*[IN]*/
usb_request_notify_t other_req_callback,/*[IN]*/
void* callback_data,/*[IN]*/
int32_t data,/*[IN]*/
usb_desc_request_notify_struct_t* desc_callback_ptr /*[IN]*/);
uint8_t USB_Framework_Deinit( usb_device_handle handle, /*[IN]*/
usb_class_fw_handle fw_handle /*[IN]*/);
uint8_t USB_Framework_Reset(usb_device_handle handle);
void USB_Control_Service (void* handle, usb_event_struct_t* event,void* arg );
void USB_Control_Service_Handler( usb_class_fw_object_struct_t* usb_fw_ptr,
uint8_t error,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);

static uint8_t USB_Strd_Req_Get_Status(usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);
static uint8_t USB_Strd_Req_Feature(usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);
static uint8_t USB_Strd_Req_Set_Address(usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);
static uint8_t USB_Strd_Req_Assign_Address(usb_class_fw_object_struct_t* usb_fw_ptr);
static uint8_t USB_Strd_Req_Get_Config(usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);
static uint8_t USB_Strd_Req_Set_Config(usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);
static uint8_t USB_Strd_Req_Get_Interface(usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);
static uint8_t USB_Strd_Req_Set_Interface(usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);
static uint8_t USB_Strd_Req_Sync_Frame(usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);
static uint8_t USB_Strd_Req_Get_Descriptor(usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);

#ifdef DELAYED_PROCESSING
void USB_Control_Service_Callback( usb_event_struct_t* event,void* arg );
#endif

extern usb_status usb_device_set_address(usb_device_handle handle, uint8_t address);
extern usb_status usb_device_reset(usb_device_handle handle);

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Local Variables 
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
static USB_FW_REQ_FUNC g_standard_request[MAX_STRD_REQ] =
{
    USB_Strd_Req_Get_Status,
    USB_Strd_Req_Feature,
    NULL,
    USB_Strd_Req_Feature,
    NULL,
    USB_Strd_Req_Set_Address,
    USB_Strd_Req_Get_Descriptor,
    NULL,
    USB_Strd_Req_Get_Config,
    USB_Strd_Req_Set_Config,
    USB_Strd_Req_Get_Interface,
    USB_Strd_Req_Set_Interface,
    USB_Strd_Req_Sync_Frame
};

#ifdef DELAYED_PROCESSING
/**************************************************************************//*!
 *
 * @name  USB_Framework_Periodic_Task
 *
 * @brief The function is called to respond to any control request
 *
 * @param None
 *
 * @return None
 *
 *****************************************************************************/
static void USB_Framework_Periodic_Task
(
void
)
{
    /* if control request pending to be completed */
    if (g_control_pending==TRUE)
    { /* handle pending control request */
        USB_Control_Service(&g_f_event);
        g_control_pending=FALSE;
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Control_Service_Callback
 *
 * @brief The function can be used as a callback function to the service.
 *
 * @param event:              from Service callback function
 *
 * @return None       
 *
 *****************************************************************************/
static void USB_Control_Service_Callback
(
usb_event_struct_t* event,
void* arg
)
{
    UNUSED_ARGUMENT(arg)
    /* save the event parameters */
    g_f_event.buffer_ptr = event->buffer_ptr;
    g_f_event.handle = event->handle;
    g_f_event.ep_num = event->ep_num;
    g_f_event.setup = event->setup;
    g_f_event.len = event->len;
    g_f_event.errors = event->errors;

    /* set the pending request flag */
    g_control_pending=TRUE;
}
#endif

/**************************************************************************//*!
 *
 * @name  USB_Framework_Reset
 *
 * @brief The function resets the framework
 *
 * @param handle: handle to Identify the controller
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *
 *****************************************************************************/
uint8_t USB_Framework_Reset
(
usb_device_handle handle
)
{
    //UNUSED_ARGUMENT(handle)
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Control_Service
 *
 * @brief Called upon a completed endpoint 0 (USB 1.1 Chapter 9) transfer 
 *
 * @param event:        from Service callback function
 *
 * @return None       
 *
 *****************************************************************************/
void USB_Control_Service
(
void* handle,
usb_event_struct_t* event,
void* arg
)
{
    uint16_t device_state = 0;
    uint8_t error = USBERR_INVALID_REQ_TYPE;
    uint8_t * data = NULL;
    uint32_t size;
    usb_class_fw_object_struct_t* usb_fw_ptr;

    usb_fw_ptr = (usb_class_fw_object_struct_t*)handle;

    /* get the device state  */
    (void)usb_device_get_status(usb_fw_ptr->dev_handle, (uint8_t)USB_STATUS_DEVICE_STATE,
    &device_state);
    //USB_PRINTF("USB_Control_Service ++ \n");
    if (event->setup == TRUE)
    {
        OS_Mem_copy(event->buffer_ptr,&usb_fw_ptr->setup_packet,USB_SETUP_PKT_SIZE);

        /* take care of endianness  of the 16 bit fields correctly */
        usb_fw_ptr->setup_packet.index = USB_SHORT_LE_TO_HOST(usb_fw_ptr->setup_packet.index);
        usb_fw_ptr->setup_packet.value = USB_SHORT_LE_TO_HOST(usb_fw_ptr->setup_packet.value);
        usb_fw_ptr->setup_packet.length = USB_SHORT_LE_TO_HOST(usb_fw_ptr->setup_packet.length);
        //  USB_PRINTF("00++ Enter ++ type:%d \n",usb_fw_ptr->setup_packet.request_type);
        /* if the request is standard request */
        if ((usb_fw_ptr->setup_packet.request_type & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_POS) ==
        USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_STANDARD)
        {
            //      USB_PRINTF("11++ Enter ++ :%d \n",usb_fw_ptr->setup_packet.request);
            /* if callback is not NULL */
            if (g_standard_request[usb_fw_ptr->setup_packet.request] != NULL)
            {
                //          USB_PRINTF("22++ Enter ++ :%d \n",usb_fw_ptr->setup_packet.request);
                /* if the request is valid in this device state */
                if((device_state < USB_STATE_POWERED) &&
                (g_validate_request[usb_fw_ptr->setup_packet.request][device_state]
                == (uint8_t)1))
                {
                    /* Standard Request function pointers */
                    error = g_standard_request[usb_fw_ptr->setup_packet.request]
                    (usb_fw_ptr,&usb_fw_ptr->setup_packet,&data,&size);
                }
            }
        }
        else /* for Class/Vendor requests */
        {
            /*get the length from the setup_request*/
            size = usb_fw_ptr->setup_packet.length;

            if( (size != 0) &&
            ((usb_fw_ptr->setup_packet.request_type & USB_DEV_REQ_STD_REQUEST_TYPE_DIR_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_DIR_OUT)
            )
            {
                /* we have gone for one time memory allocation of ext_req_to_host
                 to avoid memory fragmentation, as there was memory crunch in 
                 some of our Socs. */
                if((size + USB_SETUP_PKT_SIZE) > MAX_EXPECTED_CONTROL_OUT_SIZE)
                {
#if _DEBUG
                    USB_PRINTF("MAX_EXPECTED_CONTROL_OUT_SIZE insufficient, needed %d\n", size + USB_SETUP_PKT_SIZE);
                    USB_PRINTF("Please change the macro!!!\n");
#endif  
                    usb_device_stall_endpoint(usb_fw_ptr->dev_handle,USB_CONTROL_ENDPOINT,USB_RECV);
                    return;
                }

                /* copy setup token to ext_req_to_host */
                OS_Mem_copy(&usb_fw_ptr->setup_packet, usb_fw_ptr->ext_req_to_host,
                USB_SETUP_PKT_SIZE);
                /* expecting host to send data (OUT TRANSACTION)*/
                (void)usb_device_recv_data(event->handle,
                USB_CONTROL_ENDPOINT,(usb_fw_ptr->ext_req_to_host+USB_SETUP_PKT_SIZE),
                (uint32_t)(size));
                return;
            }
            /*call class/vendor request*/
            else if(usb_fw_ptr->request_notify_callback != NULL)
            {
                //    USB_PRINTF("USB_Control_Service_Handler ++ #### \n");
                error = usb_fw_ptr->request_notify_callback(
                &usb_fw_ptr->setup_packet,&data,&size,usb_fw_ptr->request_notify_param);
            }
        }
        USB_Control_Service_Handler(usb_fw_ptr,error,&usb_fw_ptr->setup_packet,
        &data,&size);
    }
    else if(device_state == USB_STATE_PENDING_ADDRESS)
    {
        /* Device state is PENDING_ADDRESS */
        /* Assign the new address to the Device */
        //USB_PRINTF("send ZLT done\n");
        (void)USB_Strd_Req_Assign_Address(usb_fw_ptr);
    }
    else if( ((usb_fw_ptr->setup_packet.request_type & USB_DEV_REQ_STD_REQUEST_TYPE_DIR_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_DIR_OUT) &&
    (event->direction == USB_RECV) &&
    (usb_fw_ptr->setup_packet.length)
    )
    {
        /* execution enters Control Service because of 
         OUT transaction on USB_CONTROL_ENDPOINT*/
        if(usb_fw_ptr->request_notify_callback != NULL)
        {
            /* class or vendor request */
            size = event->len+USB_SETUP_PKT_SIZE;
            error = usb_fw_ptr->request_notify_callback(
            (usb_setup_struct_t*) usb_fw_ptr->ext_req_to_host,
            &data,&size,usb_fw_ptr->request_notify_param);
        }
        /* if it is called by usb_dci_khci_cancel() in the reset procedure, there is no need to to prime the endpoint*/
        if(event->len != 0xFFFFFFFF)
        {
            USB_Control_Service_Handler(usb_fw_ptr,error,&usb_fw_ptr->setup_packet,
            &data,&size);
        }
    }
    return;
}

/**************************************************************************//*!
 *
 * @name  USB_Reset_Service
 *
 * @brief The function is called upon a bus reset event.
 Initializes the control endpoint.
 *
 * @param event:        for Service callback function     
 *
 * @return None       
 *****************************************************************************/
void USB_Reset_Service
(
void* handle,
usb_event_struct_t* event,
void* arg
)
{
    usb_ep_struct_t ep_struct;
    volatile usb_class_fw_object_struct_t* usb_fw_ptr;
    void* temp;

    usb_fw_ptr = (usb_class_fw_object_struct_t*)handle;

    usb_device_reset(usb_fw_ptr->dev_handle);

    /* Initialize the endpoint 0 in both directions */
    ep_struct.direction = USB_RECV;
    ep_struct.ep_num = USB_CONTROL_ENDPOINT;
    ep_struct.size = CONTROL_MAX_PACKET_SIZE;
    ep_struct.type = USB_CONTROL_PIPE;

    usb_device_init_endpoint(event->handle, &ep_struct, TRUE);

    ep_struct.direction = USB_SEND;
    usb_device_init_endpoint(event->handle, &ep_struct, TRUE);
    temp = usb_fw_ptr->device_notify_param;
    /* let the application know that bus reset has taken place */
    if (usb_fw_ptr->device_notify_callback != NULL)
    {
        usb_fw_ptr->device_notify_callback(USB_DEV_EVENT_BUS_RESET,NULL,temp);
    }

    return;
}

#if USBCFG_DEV_DETACH_ENABLE
/**************************************************************************//*!
 *
 * @name  USB_Detach_Service
 *
 * @brief The function is called upon a bus reset event.
 Initializes the control endpoint.
 *
 * @param event:        for Service callback function     
 *
 * @return None       
 *****************************************************************************/
void USB_Detach_Service
(
void* handle,
usb_event_struct_t* event,
void* arg
)
{
    volatile usb_class_fw_object_struct_t* usb_fw_ptr;

    usb_fw_ptr = (usb_class_fw_object_struct_t*)handle;

    usb_device_reset(usb_fw_ptr->dev_handle);

    /* let the application know that bus reset has taken place */
    if (usb_fw_ptr->device_notify_callback != NULL)
    {
        usb_fw_ptr->device_notify_callback(USB_DEV_EVENT_DETACH, NULL, usb_fw_ptr->device_notify_param);
    }

    return;
}
#endif

#if USBCFG_DEV_KHCI_ADVANCED_ERROR_HANDLING
/**************************************************************************//*!
 *
 * @name  USB_Error_Service
 *
 * @brief The function is called when an error has been detected
 *
 * @param event:        for Service callback function     
 *
 * @return None       
 *****************************************************************************/
void USB_Error_Service
(
void* handle,
usb_event_struct_t* event,
void* arg
)
{
    volatile usb_class_fw_object_struct_t* usb_fw_ptr;

    usb_fw_ptr = (usb_class_fw_object_struct_t*)handle;

    /* notify the application of the error */
    if (usb_fw_ptr->device_notify_callback != NULL)
    {
        usb_fw_ptr->device_notify_callback(USB_DEV_EVENT_ERROR,event->buffer_ptr,usb_fw_ptr->device_notify_param);
    }
    return;
}
#endif

#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME
/**************************************************************************//*!
 *
 * @name  USB_Suspend_Service
 *
 * @brief The function is called when host suspends the USB port
 *
 * @param event:        for Service callback function     
 *
 * @return None       
 *****************************************************************************/
void USB_Suspend_Service
(
void* handle,
usb_event_struct_t* event,
void* arg
)
{
    UNUSED_ARGUMENT(handle)
    UNUSED_ARGUMENT(event)
    UNUSED_ARGUMENT(arg)
    return;
}

/**************************************************************************//*!
 *
 * @name  USB_Resume_Service
 *
 * @brief The function is called when host resumes the USB port
 *
 * @param event:        for Service callback function     
 *
 * @return None       
 *****************************************************************************/
void USB_Resume_Service
(
void* handle,
usb_event_struct_t* event,
void* arg
)
{
    UNUSED_ARGUMENT(handle)
    UNUSED_ARGUMENT(event)
    UNUSED_ARGUMENT(arg)
    return;
}
#endif

/**************************************************************************//*!
 *
 * @name  USB_Control_Service_Handler
 *
 * @brief The function is used to send a response to the Host based. 
 *
 * @param status:           status of Device e.g USB_OK,USBERR_INVALID_REQ_TYPE
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return None       
 *
 *****************************************************************************/
void USB_Control_Service_Handler
(
usb_class_fw_object_struct_t* usb_fw_ptr,
uint8_t error,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    if (error == USBERR_INVALID_REQ_TYPE)
    {
        uint8_t direction = USB_SEND;
        uint8_t ep_num = USB_CONTROL_ENDPOINT;

        usb_device_stall_endpoint(usb_fw_ptr->dev_handle,ep_num,direction);
    }
    else /* Need to send Data to the USB Host */
    {
        /* send the data prepared by the handlers.*/
        if (*size > setup_packet->length)
        {
            *size = setup_packet->length;
        }

        /* send the data to the host */
        (void)usb_device_send_data(usb_fw_ptr->dev_handle,USB_CONTROL_ENDPOINT, *data, *size);
        //USB_PRINTF("send %d to host\n", *size);

        if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_DIR_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_DIR_IN)
        {
            /* Request was to Get Data from device */
            /* setup recv to get status from host */
            (void)usb_device_recv_data(usb_fw_ptr->dev_handle,
            USB_CONTROL_ENDPOINT,NULL,0);
            //USB_PRINTF("ready to receive ZLT on EP0\n");
        }
    }
    return;
}
/*************************************************************************//*!
 *
 * @name  USB_Strd_Req_Get_Status
 *
 * @brief  This function is called in response to Get Status request
 *
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Get_Status
(
usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    uint8_t endpoint;
    uint8_t error = USBERR_ERROR;

    if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_DEVICE)
    { /* request for Device */
#ifdef USBCFG_OTG
        if(setup_packet->index == USB_WINDEX_OTG_STATUS_SEL)
        {
            uint8_t hnp_support;
            (void)usb_device_otg_get_hnp_support(usb_fw_ptr->dev_handle, &hnp_support);
            if(hnp_support)
            {
                error = usb_device_get_status(usb_fw_ptr->dev_handle,
                (uint8_t)USB_STATUS_OTG, &usb_fw_ptr->std_framework_data);
                usb_fw_ptr->std_framework_data &= GET_STATUS_OTG_MASK;
                usb_fw_ptr->std_framework_data = USB_SHORT_LE_TO_HOST(usb_fw_ptr->std_framework_data);
                *size=OTG_STATUS_SIZE;
            }
            else
            {
                error = USBERR_INVALID_REQ_TYPE;
            }
        }
        else
#endif    
        {
            error = usb_device_get_status(usb_fw_ptr->dev_handle,
            (uint8_t)USB_STATUS_DEVICE, &usb_fw_ptr->std_framework_data);
            usb_fw_ptr->std_framework_data &= GET_STATUS_DEVICE_MASK;
            usb_fw_ptr->std_framework_data = USB_SHORT_LE_TO_HOST(usb_fw_ptr->std_framework_data);
            *size=DEVICE_STATUS_SIZE;
        }
    }
    else if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_INTERFACE)
    { /* request for Interface */
        usb_fw_ptr->std_framework_data = 0;
        *size=INTERFACE_STATUS_SIZE;
    }
    else if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_ENDPOINT)
    { /* request for Endpoint */
        endpoint =(uint8_t)(((uint8_t)setup_packet->index)|USB_STATUS_ENDPOINT);
        error = usb_device_get_status(usb_fw_ptr->dev_handle,
        (uint8_t)endpoint,
        &usb_fw_ptr->std_framework_data);
        usb_fw_ptr->std_framework_data = USB_SHORT_LE_TO_HOST(usb_fw_ptr->std_framework_data);
        *size=ENDP_STATUS_SIZE;
    }

    *data = (uint8_t *)&usb_fw_ptr->std_framework_data;
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Strd_Req_Feature
 *
 * @brief  This function is called in response to Clear or Set Feature request
 *
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Feature
(
usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    //uint16_t device_status;
    uint16_t set_request;
    uint8_t error=USBERR_INVALID_REQ_TYPE;
    uint8_t epinfo;
    uint8_t event;
    uint8_t feature;
#if USBCFG_DEV_EHCI && USBCFG_DEV_EHCI_TEST_MODE
    uint16_t ptc = 0;
    volatile uint32_t loop = 10*1000*1000;
#endif

    //UNUSED_ARGUMENT(data)
    *size=0;
    /* find whether its a clear feature request or a set feature request */
    set_request = (uint16_t)((uint16_t)(setup_packet->request & USB_SET_REQUEST_MASK)>>1);

    if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_DEVICE)
    {
#ifdef USBCFG_OTG
        if (set_request)
        {
            if ((setup_packet->value == USB_DEV_REQ_STD_FEATURE_B_HNP_ENABLE) || (setup_packet->value == USB_DEV_REQ_STD_FEATURE_A_HNP_SUPPORT))
            {
                uint8_t hnp_support;
                (void)usb_device_otg_get_hnp_support(usb_fw_ptr->dev_handle, &hnp_support);
                if (hnp_support)
                {
                    error = USB_OK;
                    if (setup_packet->value == USB_DEV_REQ_STD_FEATURE_B_HNP_ENABLE)
                    {
                        (void)usb_device_otg_set_hnp_enable(usb_fw_ptr->dev_handle);
                    }
                }
                else
                {
                    error = USBERR_INVALID_REQ_TYPE;
                }
            }
        }
#endif  
        /* request for Device */
        feature = setup_packet->value & USB_DEV_REQ_STD_FEATURE_SELECTOR_MASK;
        if (feature)
        {
            if (feature == USB_DEV_REQ_STD_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP)
            {
                if (set_request == (uint16_t)TRUE)
                {
                    event = USB_DEV_EVENT_TYPE_SET_REMOTE_WAKEUP;
                }
                else
                { /* remove the request to be cleared from device_status */
                    event = USB_DEV_EVENT_TYPE_CLR_REMOTE_WAKEUP;
                }
                error = USB_OK;
                if (usb_fw_ptr->device_notify_callback)
                {
                    usb_fw_ptr->device_notify_callback(event, NULL, usb_fw_ptr->request_notify_param);
                }
            }
            else if (feature == USB_DEV_REQ_STD_FEATURE_SELECTOR_TEST_MODE)
            {
#if USBCFG_DEV_EHCI && USBCFG_DEV_EHCI_TEST_MODE
                (void)usb_device_send_data(usb_fw_ptr->dev_handle,USB_CONTROL_ENDPOINT, NULL, 0);
                /* need add some delay to wait for zero length packet is sent complete */
                while(loop --)
                {
                    ;
                }
                ptc = setup_packet->index >> 8;
                usb_device_set_status(usb_fw_ptr->dev_handle, USB_STATUS_TEST_MODE, ptc);
                error = USB_OK;
#endif
            }
        }
        else
        {
            /* TODO */
            /* if the feature is 0, a request error need to be sent out*/

        }
    }
    else if ((setup_packet->request_type & USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_POS) == USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_ENDPOINT)
    {
        /* request for Endpoint */
        feature = setup_packet->value & USB_DEV_REQ_STD_FEATURE_SELECTOR_MASK;
        if (feature == 0)
        {
            epinfo = (uint8_t)(setup_packet->index & 0x00FF);
            if(set_request)
            {
                event = USB_DEV_EVENT_TYPE_SET_EP_HALT;
                error = usb_device_stall_endpoint(usb_fw_ptr->dev_handle,epinfo & 0x0F, (uint8_t)(epinfo & 0x80) >> 7);
            }
            else
            {
                event = USB_DEV_EVENT_TYPE_CLR_EP_HALT;
                if ((epinfo & 0x0f) == 0)
                {
                    error = usb_device_unstall_endpoint(usb_fw_ptr->dev_handle,epinfo & 0x0F, (uint8_t)(epinfo & 0x80) >> 7);
                }
            }
            if(usb_fw_ptr->device_notify_callback)
            {
                usb_fw_ptr->device_notify_callback(event, (void*)&epinfo, usb_fw_ptr->request_notify_param);
                error = USB_OK;
            }
        }
        else
        {
            /* TODO */
            /* if feature is not 0, request error need to be sent out */
        }

    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Strd_Req_Set_Address
 *
 * @brief  This function is called in response to Set Address request
 *
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Set_Address
(
usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    //UNUSED_ARGUMENT(data)
    *size=0;
    /* update device state */
    (void)usb_device_set_status(usb_fw_ptr->dev_handle,
    (uint8_t)USB_STATUS_DEVICE_STATE,
    (uint16_t)USB_STATE_PENDING_ADDRESS);
    /*store the address from setup_packet into assigned_address*/
    usb_fw_ptr->assigned_address = setup_packet->value;

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Strd_Req_Assign_Address
 *
 * @brief  This function assigns the address to the Device
 *
 * @param handle      
 *
 * @return status       
 *                       USB_OK: Always
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Assign_Address
(
usb_class_fw_object_struct_t* usb_fw_ptr
)
{
    /* Set Device Address */
    (void)usb_device_set_address(usb_fw_ptr->dev_handle,
    (uint8_t)(usb_fw_ptr->assigned_address&0x00FF));
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Strd_Req_Get_Config
 *
 * @brief  This function is called in response to Get Config request
 *
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return status:       
 *                        USB_OK : Always
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Get_Config
(
usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    //UNUSED_ARGUMENT(setup_packet)

    *size = CONFIG_SIZE;
    usb_fw_ptr->cur_config = USB_SHORT_LE_TO_HOST(usb_fw_ptr->cur_config);
    *data = (uint8_t *)(&usb_fw_ptr->cur_config);

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Strd_Req_Set_Config
 *
 * @brief  This function is called in response to Set Config request
 *
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Set_Config
( 
usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    uint8_t error = USBERR_INVALID_REQ_TYPE;
    uint16_t config_val;

    uint16_t device_state = USB_STATE_CONFIG;
    //UNUSED_ARGUMENT(data)     
    *size=0;
    error = USB_STATUS_ERROR;
    config_val = setup_packet->value;

    if (!config_val) /* if config_val is 0 */
    {
        device_state = USB_STATE_ADDRESS;
    }

    error = usb_device_set_status(usb_fw_ptr->dev_handle,
    (uint8_t)USB_STATUS_DEVICE_STATE,
    (uint16_t)device_state);

    usb_fw_ptr->cur_config = config_val;
    /* Set configuration according to config number*/
    if(NULL != usb_fw_ptr->desc_notify_callback->set_configuration)
    {
        usb_fw_ptr->desc_notify_callback->set_configuration((uint32_t)usb_fw_ptr->desc_notify_param,(uint8_t)config_val);
    }
    /* callback to the app. to let the application know about the new Config */
    if (usb_fw_ptr->device_notify_callback != NULL)
    {
        usb_fw_ptr->device_notify_callback(USB_DEV_EVENT_CONFIG_CHANGED,
        (void *)&config_val,usb_fw_ptr->device_notify_param);
        if(config_val)
        {
            usb_fw_ptr->device_notify_callback(USB_DEV_EVENT_ENUM_COMPLETE,NULL,
            usb_fw_ptr->device_notify_param);
        }
    }

    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Strd_Req_Get_Interface
 *
 * @brief  This function is called in response to Get Interface request
 *
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Get_Interface
(
usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    uint8_t error = USBERR_NULL_CALLBACK;

    *size = INTERFACE_STATUS_SIZE;

    if(!usb_fw_ptr->desc_notify_callback->get_desc_interface)
    {
        return error;
    }

    error = usb_fw_ptr->desc_notify_callback->get_desc_interface((uint32_t)(usb_fw_ptr->desc_notify_param),
    (uint8_t)setup_packet->index, (uint8_t *)&usb_fw_ptr->std_framework_data);
    usb_fw_ptr->std_framework_data = USB_SHORT_LE_TO_HOST(usb_fw_ptr->std_framework_data);
    *data = (uint8_t *)&usb_fw_ptr->std_framework_data;

    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Strd_Req_Set_Interface
 *
 * @brief  This function is called in response to Set Interface request
 *
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return status:       
 *                        USB_OK : Always       
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Set_Interface
(
usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    uint8_t error = USBERR_NULL_CALLBACK;
    //UNUSED_ARGUMENT(data)
    *size=0;

    /* Request type not for interface */
    if ((setup_packet->request_type & 0x03) != 0x01)
    {
        return USB_STATUS_ERROR;
    }

    if(!usb_fw_ptr->desc_notify_callback->set_desc_interface)
    {
        return error;
    }

    /* Get Interface and alternate interface from setup_packet */
    error = usb_fw_ptr->desc_notify_callback->set_desc_interface((uint32_t)(usb_fw_ptr->desc_notify_param),
    (uint8_t)setup_packet->index, (uint8_t)setup_packet->value);

    if (usb_fw_ptr->device_notify_callback != NULL)
    {
        usb_fw_ptr->device_notify_callback(USB_DEV_EVENT_INTERFACE_CHANGED,
        (void *)&setup_packet->value, usb_fw_ptr->device_notify_param);
    }

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Strd_Req_Sync_Frame
 *
 * @brief  This function is called in response to Sync Frame request
 *
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Sync_Frame
(
usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    uint8_t error;
    //UNUSED_ARGUMENT(setup_packet)

    *size=FRAME_SIZE;
    /* Get the frame number */
    error = usb_device_get_status(usb_fw_ptr->dev_handle,
    (uint8_t)USB_STATUS_SOF_COUNT,
    &usb_fw_ptr->std_framework_data);
    usb_fw_ptr->std_framework_data = USB_SHORT_LE_TO_HOST(usb_fw_ptr->std_framework_data);
    *data= (uint8_t *)&usb_fw_ptr->std_framework_data;

    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Std_Req_Get_Descriptor
 *
 * @brief  This function is called in response to Get Descriptor request
 *
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned 
 *
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
static uint8_t USB_Strd_Req_Get_Descriptor
(
usb_class_fw_object_struct_t* usb_fw_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size
)
{
    /*g_setup_packet.hValue*/
    uint8_t type = (uint8_t)(setup_packet->value >> 8) & 0xFF;
    uint16_t index = (uint8_t)USB_UNINITIALIZED_VAL_32;
    uint8_t str_num = (uint8_t)USB_UNINITIALIZED_VAL_32;
    uint8_t error = USBERR_NULL_CALLBACK;

    /* for string descriptor set the language and string number */
    index = setup_packet->index;
    /*g_setup_packet.lValue*/
    str_num = setup_packet->value & 0xFF;

    if(!usb_fw_ptr->desc_notify_callback->get_desc)
    {
        return error;
    }
    /* Call descriptor class to get descriptor */
    error = usb_fw_ptr->desc_notify_callback->get_desc((uint32_t)(usb_fw_ptr->desc_notify_param),
    type,str_num,index,data,size);

    return error;
}
#if 0
/**************************************************************************//*!
 *
 * @name  USB_Framework_GetDesc
 *
 * @brief  This function is called in to get the descriptor as specified in cmd.
 *
 * @param handle:           USB framework handle. Received from
 *                          USB_Framework_Init      
 * @param cmd:              command for USB descriptor to get.
 * @param in_data:          input to the Application functions.
 * @param in_buff           buffer which will contain the descriptors.
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
static uint8_t USB_Framework_GetDesc
(
usb_class_fw_handle handle, /*[IN]*/
int32_t cmd,/*[IN]*/
uint8_t in_data,/*[IN]*/
uint8_t * * in_buff/*[OUT]*/
)
{
    return 0;
}

/**************************************************************************//*!
 *
 * @name  USB_Framework_SetDesc
 *
 * @brief  This function is called in to get the descriptor as specified in cmd.
 *
 * @param handle:           USB framework handle. Received from
 *                          USB_Framework_Init      
 * @param cmd:              command for USB descriptor to get.
 * @param in_data:          input to the Application functions.
 * @param outBuf           buffer which will contain the descriptors.
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
static uint8_t USB_Framework_SetDesc
(
usb_class_fw_handle handle,/*[IN]*/
int32_t cmd,/*[IN]*/
uint8_t input_data,/*[IN]*/
uint8_t * * outBuf/*[IN]*/
)
{
    return 0;
}

/**************************************************************************//*!
 *
 * @name  USB_Framework_Remote_wakeup
 *
 * @brief  This function is called in to get the descriptor as specified in cmd.
 *
 * @param handle:           USB framework handle. Received from
 *                          USB_Framework_Init      
 * @param cmd:              command for USB descriptor to get.
 * @param in_data:          input to the Application functions.
 * @param in_buff           buffer which will contain the descriptors.
 * @return status:       
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
bool USB_Framework_Remote_wakeup
(
usb_class_fw_handle handle
)
{
    return 0;
}
#endif

#endif
