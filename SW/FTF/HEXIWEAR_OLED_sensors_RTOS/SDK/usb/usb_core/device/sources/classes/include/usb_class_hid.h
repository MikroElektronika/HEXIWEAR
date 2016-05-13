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
* $FileName: usb_hid.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains USB stack HID class layer api header function.
*
*****************************************************************************/

#ifndef _USB_CLASS_HID_H
#define _USB_CLASS_HID_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/

 
 /* class specific requests */
#define USB_HID_GET_REPORT_REQUEST     (0x01)
#define USB_HID_GET_IDLE_REQUEST       (0x02)
#define USB_HID_GET_PROTOCOL_REQUEST   (0x03)
#define USB_HID_SET_REPORT_REQUEST     (0x09)
#define USB_HID_SET_IDLE_REQUEST       (0x0A)
#define USB_HID_SET_PROTOCOL_REQUEST   (0x0B)
#define HIGH_BYTE_SHIFT                (8) 
#define MSB_MASK                       (0xFF00)
#define USB_HID_REQUEST_DIR_MASK       (0x08)
#define USB_HID_REQUEST_TYPE_MASK      (0x01)

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
#define USB_REQ_VAL_INVALID            (0xFFFF)

 /******************************************************************************
 * Types
 *****************************************************************************/
 typedef uint32_t hid_handle_t; 
 
/*!
 * @brief HID configuration structure.
 *
 * Structure used to configure HID class by APP
 *
 */
 typedef struct hid_config_struct
 {
    usb_application_callback_struct_t       hid_application_callback; /*!< application callback function to handle the Device status related event*/
    usb_vendor_req_callback_struct_t        vendor_req_callback;      /*!< application callback function to handle the vendor request related event, reserved for future use*/
    usb_class_specific_callback_struct_t    class_specific_callback;  /*!< application callback function to handle all the class related event*/
    usb_desc_request_notify_struct_t*       desc_callback_ptr;        /*!< descriptor related callback function data structure*/
 }hid_config_struct_t;

 
/******************************************************************************
 * Global Functions
 *****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*!
* @brief The function initializes the Device and Controller layer.
*
* The application calls this API function to initialize the HID class, the underlying layers, and
* the controller hardware.
*
* @param controller_id controller ID, such as USB_CONTROLLER_KHCI_0
* @param hid_config_ptr HID configuration structure
* @param hidHandle pointer point to the initialized HID class
* @return USB_OK-Success/Others-Fail
*/
extern  usb_status USB_Class_HID_Init
(
    uint8_t               controller_id,
    hid_config_struct_t*  hid_config_ptr,
    hid_handle_t *          hidHandle
);

/*!
 * @brief The function De-initializes the Device and Controller layer.
 *
 * The application calls this API function to de-initialize the HID class, the underlying layers, and
 * the controller hardware.
 * @param hidHandle HID class handler  
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_HID_Deinit
(
 hid_handle_t   handle
);

/*!
 * @brief Sends the HID data.
 *
 * The application calls this API function to send HID data specified by app_buff and size. Once
 * the data is sent, the application layer receives a callback event USB_DEV_EVENT_SEND_COMPLETE.
 * The application reserves the buffer until it receives a callback event indicating that the data is sent.
 *
 * @param handle HID class handler
 * @param ep_num endpoint number
 * @param buff_ptr buffer holding application data 
 * @param size length of the transfer
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_HID_Send_Data
(
    hid_handle_t         handle,        /* [IN]*/
    uint8_t            ep_num,        /* [IN]*/
    uint8_t*           app_buff,      /* [IN] buffer to send */      
    uint32_t           size           /* [IN] length of the transfer */
);

/*!
 * @brief Receives the HID data.
 *
 * The application calls this API function to send HID data specified by app_buff and size. Once
 * the data is sent, the application layer receives a callback event USB_DEV_EVENT_DATA_RECEIVED.
 * The application reserves the buffer until it receives a callback event indicating that the data is received.
 * 
 * @param handle HID class handler
 * @param ep_num endpoint number
 * @param buff_ptr buffer to save the data from the host
 * @param size buffer length to receive  
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_HID_Recv_Data
(
    hid_handle_t handle,/*[IN]*/
    uint8_t ep_num,/*[IN]*/
    uint8_t * app_buff,/*[IN]*/
    uint32_t size /*[IN]*/
);

#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE
/**************************************************************************//*!
 *
 * @name  USB_Class_HID_Cancel
 *
 * @brief 
 *
 * @param handle          :   handle returned by USB_Class_HID_Init
 * @param ep_num          :   endpoint num 
 * @param direction        :   direction of the endpoint 
 *
 * @return status       
 *         USB_OK           : When Successfull 
 *         Others           : Errors
 *****************************************************************************/

extern usb_status USB_Class_HID_Cancel
(
    hid_handle_t handle,/*[IN]*/
    uint8_t ep_num,/*[IN]*/
    uint8_t direction
);
#endif

/**************************************************************************//*!
 *
 * @name  USB_Class_HID_Get_Speed
 *
 * @brief This functions get speed from Host.
 *
 * @param handle          :   handle returned by USB_Class_HID_Init
 * @param speed           :   speed
 *
 * @return status       
 *         USB_OK         : When Successfull 
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Class_HID_Get_Speed
(
    hid_handle_t         handle,
    uint16_t *           speed/* [OUT] the requested error */
);

#ifdef __cplusplus
}
#endif

//extern void USB_Class_Periodic_Task(void);
#define USB_HID_Periodic_Task USB_Class_Periodic_Task

#endif

/* EOF */
