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
 * $FileName: usb_device_stack_interface.h$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * 
 *
 *END************************************************************************/
/* Prototypes */
#ifndef __usb_device_stack_interface_h__
#define __usb_device_stack_interface_h__

#include "usb_types.h"

/* Informational Request/Set Types */
#define  USB_STATUS_DEVICE_STATE               (0x01)
#define  USB_STATUS_INTERFACE                  (0x02)
#define  USB_STATUS_ADDRESS                    (0x03)
#define  USB_STATUS_CURRENT_CONFIG             (0x04)
#define  USB_STATUS_SOF_COUNT                  (0x05)
#define  USB_STATUS_DEVICE                     (0x06)
#define  USB_STATUS_TEST_MODE                  (0x07)
#define  USB_STATUS_SPEED                      (0x08)

#ifdef USBCFG_OTG
#define  USB_STATUS_OTG                        (0x09)
#endif
#define  USB_STATUS_ENDPOINT                   (0x10)
#define  USB_STATUS_ENDPOINT_NUMBER_MASK       (0x0F)

#define  USB_TEST_MODE_TEST_PACKET             (0x0400)

/* Available service types */
/* Services 0 through 15 are reserved for endpoints */
#define  USB_SERVICE_EP0                       (0x00)
#define  USB_SERVICE_EP1                       (0x01)
#define  USB_SERVICE_EP2                       (0x02)
#define  USB_SERVICE_EP3                       (0x03)
#define  USB_SERVICE_BUS_RESET                 (0x10)
#define  USB_SERVICE_SUSPEND                   (0x11)
//#define  USB_SERVICE_SOF                                   (0x12)
#define  USB_SERVICE_RESUME                    (0x13)
#define  USB_SERVICE_SLEEP                     (0x14)
#define  USB_SERVICE_SPEED_DETECTION           (0x15)
#define  USB_SERVICE_ERROR                     (0x16)
//#define  USB_SERVICE_STALL                                (0x17)
#define  USB_SERVICE_REQUEST                   (0x18)
#define  USB_SERVICE_DETACH                    (0x19)

#define  USB_CONTROL_ENDPOINT                  (0)
#define  USB_SETUP_PKT_SIZE                    (8)/* Setup Packet Size */
#define  USB_UNINITIALIZED_VAL_32              (0xFFFFFFFF)

#define  USB_DEV_EVENT_BUS_RESET               (0)
#define  USB_DEV_EVENT_CONFIG_CHANGED          (1)
#define  USB_DEV_EVENT_INTERFACE_CHANGED       (2)
#define  USB_DEV_EVENT_ENUM_COMPLETE           (3)
#define  USB_DEV_EVENT_SEND_COMPLETE           (4)
#define  USB_DEV_EVENT_DATA_RECEIVED           (5)
#define  USB_DEV_EVENT_ERROR                   (6)
#define  USB_DEV_EVENT_GET_DATA_BUFF           (7)
#define  USB_DEV_EVENT_EP_STALLED              (8)
#define  USB_DEV_EVENT_EP_UNSTALLED            (9)
#define  USB_DEV_EVENT_GET_TRANSFER_SIZE       (0x10)
#define  USB_DEV_EVENT_TYPE_SET_REMOTE_WAKEUP  (0x11)
#define  USB_DEV_EVENT_TYPE_CLR_REMOTE_WAKEUP  (0x12)
#define  USB_DEV_EVENT_TYPE_SET_EP_HALT        (0x13)
#define  USB_DEV_EVENT_TYPE_CLR_EP_HALT        (0x14)
#define  USB_DEV_EVENT_DETACH                  (0x15)

/* Macros for description of class, configuration, interface */
#define  USB_DESC_INTERFACE(index, ep_cnt, ep) \
{ \
    index, \
    { \
        ep_cnt, \
        ep \
    } \
}
#define  USB_DESC_CONFIGURATION(intf_cnt, intf) \
{ \
    intf_cnt, \
    intf \
}
#define  USB_DESC_CLASS(type, config) \
{ \
    type, \
    config, \
}

/* Go through each endpoint in class */
#define  for_each_ep_in_class_begin(epPtr, usbclassPtr, classtype) \
    for(uint32_t class_i = 0; usbclassPtr[class_i].type != USB_CLASS_INVALID; class_i++) \
    { \
        if((usbclassPtr[class_i].type == classtype) || (classtype == USB_CLASS_ALL)) \
        { \
        for(uint32_t intf_i = 0; intf_i < usbclassPtr[class_i].interfaces.count; intf_i++) \
        { \
            for(uint32_t ep_i = 0; \
                ((ep_i < usbclassPtr[class_i].interfaces.interface[intf_i].endpoints.count) && \
                ((epPtr = usbclassPtr[class_i].interfaces.interface[intf_i].endpoints.ep + ep_i) != NULL)); \
                ep_i++) \
            { 
#define  for_each_ep_in_class_end() }}}}

/* Go through each interface in class */
#define  for_each_if_in_class_begin(ifPtr, usbclassPtr, classtype) \
                for(uint32_t class_i = 0; usbclassPtr[class_i].type != USB_CLASS_INVALID; class_i++) \
                { \
                    if((usbclassPtr[class_i].type == classtype) || (classtype == USB_CLASS_ALL)) \
                    { \
                    for(uint32_t intf_i = 0; ((intf_i < usbclassPtr[class_i].interfaces.count) \
                        && ((ifPtr = usbclassPtr[class_i].interfaces.interface + intf_i) != NULL)); \
                        intf_i++) \
                    {
#define  for_each_if_in_class_end() }}}

typedef enum
{
    USB_CLASS_INFO = 0,
    USB_COMPOSITE_INFO,
    USB_AUDIO_UNITS,
    USB_RNDIS_INFO,
    USB_PHDC_QOS_INFO,
    USB_MSC_LBA_INFO,
    USB_CLASS_INTERFACE_INDEX_INFO,
} entity_type;

typedef enum
{
    USB_CLASS_HID = 0,
    USB_CLASS_CDC,
    USB_CLASS_MSC,
    USB_CLASS_AUDIO,
    USB_CLASS_PHDC,
    USB_CLASS_ALL,
    USB_CLASS_INVALID
} class_type;
/*!
 * @brief Obtains the endpoint data structure.
 *
 * Define the endpoint data structure. 
 *
 */
typedef struct _usb_ep_struct
{
    uint8_t               ep_num;      /*!< endpoint number*/
    uint8_t               type;        /*!< type of endpoint*/
    uint8_t               direction;   /*!< direction of endpoint*/
    uint32_t              size;        /*!< maximum packet size of endpoint*/
} usb_ep_struct_t;

/*!
 * @brief Obtains the endpoint group.
 *
 * Structure Representing Endpoints and number of endpoints user want.
 *
 */
typedef struct _usb_endpoints
{
    uint8_t               count;    /*!< how many endpoints are described*/
    usb_ep_struct_t*      ep;       /*!< detailed information of each endpoint*/
} usb_endpoints_t;

/*!
 * @brief Obtains the interface data structure.
 *
 * Structure Representing interface.
 *
 */
typedef struct _usb_if_struct
{
    uint8_t               index;        /*!< interface index*/
    usb_endpoints_t       endpoints;    /*!< endpoints in this interface*/
} usb_if_struct_t;

/*!
 * @brief Obtains the interface group.
 *
 * Structure Representing how many interfaces in one class type.
 *
 */
typedef struct _usb_interfaces_struct
{
    uint8_t               count;        /*!< how many interfaces are described*/
    usb_if_struct_t*      interface;    /*!< detailed information of each interface*/
} usb_interfaces_struct_t;

/*!
 * @brief Obtains the class data structure.
 *
 * Structure Representing class info.
 *
 */
typedef struct _usb_class_struct
{
    class_type              type;          /*!< class type*/
    usb_interfaces_struct_t interfaces;    /*!< interfaces in this class*/
} usb_class_struct_t;

/*!
 * @brief Obtains the composite information data structure.
 *
 * Structure Representing composite info.
 *
 */
typedef struct _usb_composite_info_struct
{
    uint8_t               count;    /*!< how many classes in the composite device*/
    usb_class_struct_t *  class_handle;    /*!< detailed information of each class*/
} usb_composite_info_struct_t;

/*!
 * @brief Obtains the setup packet information data structure.
 *
 * Structure Representing setup packet.
 *
 */
typedef struct _usb_setup_struct
{
    uint8_t               request_type;    /*!< type of request*/
    uint8_t               request;         /*!< id of request*/
    uint16_t              value;           /*!< value of request*/
    uint16_t              index;           /*!< interface index*/
    uint16_t              length;          /*!< data length of request*/
} usb_setup_struct_t;

/* USB Specs define CONTROL_MAX_PACKET_SIZE for High Speed device as only 64,
 whereas for FS its allowed to be 8, 16, 32 or 64 */
#define CONTROL_MAX_PACKET_SIZE       (64)

#if (USBCFG_DEV_EHCI && (CONTROL_MAX_PACKET_SIZE != 64))
#error "For High Speed CONTROL_MAX_PACKET_SIZE should be 64"
#endif

/*!
 * @brief Obtains the event information.
 *
 * Structure Representing event for an endpoint.
 *
 */
typedef struct _usb_event_struct
{
    usb_device_handle     handle;             /* controller device handle*/
    uint8_t*              buffer_ptr;         /* void* to buffer       */
    uint32_t              len;                /* the buffer len had been done
                                                                              * special case: 0xFFFFFFFF means transfer cancel
                                                                              * 0xFFFFFFFE means tansfer error */
    uint8_t               ep_num;             /* endpoint number */
    uint8_t               type;
    bool                  setup;              /* is setup packet         */
    bool                  direction;          /* direction of endpoint   */
} usb_event_struct_t;

/* callback function pointer structure for Application to handle events */
typedef void(_CODE_PTR_ usb_device_notify_t)(uint8_t event, void* val, void* arg);

/* callback function pointer structure to handle USB framework request */
typedef usb_status (_CODE_PTR_ usb_request_notify_t)(usb_setup_struct_t * setup,
uint8_t **data,
uint32_t *size,void* arg);

typedef void(_CODE_PTR_ usb_event_service_t)(usb_event_struct_t* event, void* arg);

/*!
 * @brief Obtains the data structure of the descriptor related callback function. The application needs to implement them and passes it as the configuration parameter.
 *
 * Structure Representing the descriptor related callback function.
 *
 */
typedef struct _usb_desc_request_notify_struct
{
#ifdef USBCFG_OTG
    uint32_t handle;
#endif
    uint8_t (_CODE_PTR_ get_desc)(uint32_t class_handle,uint8_t type,uint8_t desc_index,
    uint16_t index,uint8_t * *descriptor,uint32_t *size); /*!< to get the descriptor whose type is specified by the type*/
    uint8_t (_CODE_PTR_ get_desc_interface)(uint32_t class_handle,uint8_t interface,
    uint8_t * alt_interface); /*!< to get the interface's alternate setting*/
    uint8_t (_CODE_PTR_ set_desc_interface)(uint32_t class_handle,uint8_t interface,
    uint8_t alt_interface); /*!< to set the interface's alternate setting*/
    uint8_t (_CODE_PTR_ set_configuration)(uint32_t class_handle, uint8_t config); /*!< to inform the application whose configuration is active */
    uint8_t (_CODE_PTR_ get_desc_entity)(uint32_t class_handle, entity_type type, uint32_t * object);    /*!< to get the descriptor/device related information*/
} usb_desc_request_notify_struct_t;

/*!
 * @brief Obtains the callback for application.
 *
 * Structure Representing information for application callback.
 *
 */
typedef struct usb_application_callback_struct
{
    usb_device_notify_t     callback;    /*!< application callback function*/
    void*                 arg;           /*!< parameter for callback function*/
}usb_application_callback_struct_t;

/*!
 * @brief Obtains the callback for vendor request.
 *
 * Structure Representing information for vendor request callback.
 *
 */
typedef struct usb_vendor_req_callback_struct
{
    usb_request_notify_t  callback;    /*!< vendor request callback function*/
    void*                 arg;         /*!< parameter for callback function*/
}usb_vendor_req_callback_struct_t;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initializes the USB device controller.
 *
 * The function initializes the device controller specified by the controller_id and a device
 * handle can be returned from the handle.
 *
 * @param controller_id controller ID, such as USB_CONTROLLER_KHCI_0
 * @param handle  USB Device handle
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_init(uint8_t controller_id, usb_device_handle * handle);

/*!
 * @brief Un-initializes the USB device controller.
 *
 * The function un-initializes the device controller specified bcontroller_idy the handle.
 *
 * @param handle  USB Device handle
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_deinit(usb_device_handle handle);

/*!
 * @brief Receives data from a specified endpoint.
 *
 * The function is used to receive data from a specified endpoint.
 *
 * @param handle USB Device handle
 * @param ep_index endpoint index
 * @param buff_ptr memory address to receive the data
 * @param size length of the packet to be received
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_recv_data(usb_device_handle handle, uint8_t ep_num, uint8_t * buff_ptr, uint32_t size);

/*!
 * @brief Sends data from a specified endpoint.
 *
 * The function is used to send data to a specified endpoint.
 *
 * @param handle USB Device handle
 * @param ep_index endpoint index
 * @param buff_ptr memory address hold the data need to be sent
 * @param size length of the packet to be sent
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_send_data(usb_device_handle handle, uint8_t ep_num, uint8_t * buff_ptr, uint32_t size);

#if ((defined USBCFG_DEV_ADVANCED_CANCEL_ENABLE) && (USBCFG_DEV_ADVANCED_CANCEL_ENABLE))
/*!
 * @brief Cancels all the pending transfers in a specified endpoint.
 *
 * The function is used to cancel all the pending transfer in a specified endpoint which
 * is determined by the endpoint index and the direction
 *
 * @param handle USB Device handle
 * @param ep_index endpoint index
 * @param direction direction of the endpoint
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_cancel_transfer(usb_device_handle handle, uint8_t ep_num, uint8_t direction);

#endif
/*!
 * @brief Registers a callback function for one specified endpoint.
 *
 * The function is used to register a callback function for one specified endpoint.
 *
 * @param handle USB Device handle
 * @param type service type, type & 0xF is the endpoint index
 * @param service callback function
 * @param arg second parameter for the callback function
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_register_service(usb_device_handle handle, uint8_t type, usb_event_service_t service, void* arg);

/*!
 * @brief Unregisters a callback function for one specified endpoint.
 *
 * The function is used to unregister a callback function for one specified endpoint.
 *
 * @param handle USB Device handle
 * @param type service type, type & 0xF is the endpoint index
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_unregister_service(usb_device_handle handle, uint8_t type);

#if ((defined USBCFG_DEV_ADVANCED_SUSPEND_RESUME) && (USBCFG_DEV_ADVANCED_SUSPEND_RESUME))
/*!
 * @brief Resume the process of usb.
 *
 * The function resumes the process of usb.
 *
 * @param handle  USB Device handle
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_assert_resume(usb_device_handle handle);

#endif
/*!
 * @brief Initializes the specified endpoint.
 *
 * The function is used to initialize a specific endpoint which is determined by the ep_ptr.
 *
 * @param handle USB Device handle
 * @param ep_ptr endpoint information
 * @param flag whether the ZLT is enabled for this endpoint
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_init_endpoint(usb_device_handle handle, usb_ep_struct_t* ep_ptr, uint8_t flag);

/*!
 * @brief Stalls the specified endpoint.
 *
 * The function is used to stall a specific endpoint which is determined by the endpoint
 * index and endpoint direction.
 *
 * @param handle USB Device handle
 * @param ep_num endpoint index
 * @param direction endpoint direction
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_stall_endpoint(usb_device_handle handle, uint8_t ep_num, uint8_t direction);

/*!
 * @brief Un-stalls the specified endpoint.
 *
 * The function is used to un-stall a specific endpoint which is determined by the endpoint
 * index and endpoint direction
 *
 * @param handle USB Device handle
 * @param ep_num endpoint index
 * @param direction endpoint direction
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_unstall_endpoint(usb_device_handle handle, uint8_t ep_num, uint8_t direction);

/*!
 * @brief Un-initializes the specified endpoint.
 *
 * The function is used to un-initialize a specific endpoint which is determined by the endpoint
 * index and endpoint direction.
 *
 * @param handle USB Device handle
 * @param ep_num endpoint index
 * @param direction endpoint direction
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_deinit_endpoint(usb_device_handle handle, uint8_t ep_num, uint8_t direction);

/*!
 * @brief Registers the callback function for the application related event.
 *
 * The function is used to register a callback function for the application related event.
 * Currently the following events are supported:
 * Event                                                  Description
 * USB_DEV_EVENT_BUS_RESET A BUS      reset is received.
 * USB_DEV_EVENT_ENUM_COMPLETE       The device enumerated process completes.
 * USB_DEV_EVENT_CONFIG_CHANGED    Host sends a set_configuration.
 * USB_DEV_EVENT_ERROR                      Error.
 *
 * @param handle USB Device handle
 * @param device_notify_callback callback function
 * @param device_notify_param parameter for the callback function
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_register_application_notify(usb_device_handle handle, usb_device_notify_t device_notify_callback, void* device_notify_param);

/*!
 * @brief Registers the callback function for the vendor class related event.
 *
 * The function is used to register a callback function for the vendor class request related event.
 * Currently the vendor class is not implemented, so both the request_notify_callback and
 * request_notify_param can be set to NULL.
 * 
 * @param handle USB Device handle
 * @param request_notify_callback callback function
 * @param request_notify_param parameter for the callback function
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_register_vendor_class_request_notify(usb_device_handle handle, usb_request_notify_t request_notify_callback, void* request_notify_param);

/*!
 * @brief Registers the callback functions for the device descriptor related request.
 *
 * The function is used to register a set of callback functions for the device descriptor related event.
 *
 * @param handle USB Device handle
 * @param desc_request_notify_callback callback function
 * @param desc_request_notify_param parameter for the callback function
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_register_desc_request_notify(usb_device_handle handle,usb_desc_request_notify_struct_t* desc_request_notify_callback, void* desc_request_notify_param);

/*!
 * @brief Gets the internal USB device state.
 *
 * The function is used to get the status of the specified component. The supported components include:
 *      USB_STATUS_DEVICE_STATE
 *      USB_STATUS_OTG
 *      USB_STATUS_DEVICE
 *      USB_STATUS_ENDPOINT, the LSB nibble carries the endpoint number
 * 
 * @param handle USB Device handle
 * @param component callback function
 * @param status requested status
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_get_status(usb_device_handle handle, uint8_t component, uint16_t* error);

/*!
 * @brief Sets the internal USB device state.
 *
 * The function is used to set the status of the specified component. The supported components include:
 *      USB_STATUS_DEVICE_STATE
 *      USB_STATUS_OTG
 *      USB_STATUS_DEVICE
 *
 * @param handle USB Device handle
 * @param component callback function
 * @param status status to set
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_set_status(usb_device_handle handle, uint8_t component, uint16_t setting);

/*!
 * @brief Initializes the USB device controller.
 *
 * The function starts the initialization process that cannot be done in the usb_device_init() API.
 * For example, the call back functions need to be registered after the device handle can be
 * obtained from the usb_device_init() API. Therefore, the USB interrupt cannot be enabled in
 * usb_device_init(); otherwise, the USB interrupt can be issued before the callback functions are
 * registered. To avoid this issue, the USB interrupt will be enabled in the post initialization process.
 *
 * @param controller_id controller ID, such as USB_CONTROLLER_KHCI_0
 * @param handle  USB Device handle
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_postinit(uint8_t controller_id, usb_device_handle handle);

#ifdef USBCFG_OTG
/*!
 * @brief Initializes the USB device OTG.
 *
 * The function initializes the device OTG specified by the device handle.
 *
 * @param handle  USB Device handle
 * @param otg_attributes Attributes used to initialize otg. Currently supported are
 * OTG_SRP_SUPPORT OTG_HNP_SUPPORT
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_otg_init(usb_device_handle handle, uint8_t otg_attributes);

/*!
 * @brief Get the status of whether OTG hnp is supported.
 *
 * The function get the status of whether OTG hnp is supported.
 *
 * @param handle  USB Device handle
 * @param hnp_support_ptr  TRUE-supported/FALSE-not supported
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_otg_get_hnp_support(usb_device_handle handle, uint8_t* hnp_support_ptr);

/*!
 * @brief Enable the OTG hnp.
 *
 * The function enable the OTG hnp feature.
 *
 * @param handle  USB Device handle
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_otg_set_hnp_enable(usb_device_handle handle);

#endif
#ifdef __cplusplus
}
#endif

#endif
