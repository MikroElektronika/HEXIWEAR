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
* $FileName: usb_class_internal.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains USB stack class layer api header function.
*
*****************************************************************************/

#ifndef _USB_CLASS_INTERNAL_H
#define _USB_CLASS_INTERNAL_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class.h"


/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/

/******************************************************************************
 * Types
 *****************************************************************************/
/* Structure holding USB class object state*/
typedef struct _usb_class_object
{
   uint32_t             usb_fw_handle;
   usb_device_handle    controller_handle;
   void*                arg;
   usb_device_notify_t  class_callback;   
} usb_class_object_struct_t;

/******************************************************************************
 * Global Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  USB_Class_Init
 *
 * @brief The function initializes the Class Module
 *
 * @param handle             :handle to Identify the controller
 * @param class_callback     :event callback      
 * @param other_req_callback :call back for class/vendor specific requests on 
 *                            CONTROL ENDPOINT
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *
 *****************************************************************************/
class_handle_t USB_Class_Init
(
    usb_device_handle                   handle,            /* [IN] the USB device controller to initialize */                  
    usb_device_notify_t                 class_callback,    /*[IN]*/
    usb_request_notify_t                other_req_callback,/*[IN]*/
    void*                               user_arg,          /*[IN]*/
    usb_desc_request_notify_struct_t*   desc_callback_ptr  /*[IN]*/
); 

/**************************************************************************//*!
 *
 * @name  USB_Class_Deinit
 *
 * @brief The function initializes the Class Module
 *
 * @param handle             :handle to Identify the controller
 * @param class_handle       :class handle      
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *
 *****************************************************************************/
usb_status USB_Class_Deinit
(
    usb_device_handle              handle, /* [IN] the USB device controller to initialize */                  
    class_handle_t                 class_handle
 );
 /**************************************************************************//*!
 *
 * @name  USB_Class_Send_Data
 *
 * @brief The function calls the device to send data upon receiving an IN token
 *
 * @param handle:               handle to Identify the controller
 * @param ep_num:               The endpoint number     
 * @param buff_ptr:             buffer to send
 * @param size:                 length of transfer
 * 
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *
 *****************************************************************************/
usb_status USB_Class_Send_Data
(
    class_handle_t                  handle,   /*[IN]*/
    uint8_t                         ep_num,   /* [IN] the Endpoint number */                  
    uint8_t*                        buff_ptr, /* [IN] buffer to send */      
    uint32_t                        size      /* [IN] length of the transfer */
); 

/**************************************************************************//*!
 *
 * @name  USB_Class_Get_Status
 *
 * @brief The funtion calls the device to send data upon recieving an IN token 
 *
 * @param handle:               handle to Identify the controller
 * @param component:            component code   
 * @param error_code:           the requested error
 * 
 * @return status       
 *         USB_OK           : When Successfull 
 *         Others           : Errors
 *
 *****************************************************************************/
usb_status USB_Class_Get_Status
(
    class_handle_t handle,     /* [IN] */
    uint8_t        component,  /* [IN] component code */
    uint16_t *     error_code /* [OUT] the requested error */
);


#ifdef USBCFG_DEV_COMPOSITE
/**************************************************************************//*!
 *
 * @name  USB_Class_Get_Class_Handle
 *
 * @brief  This function is called to return class handle.
 *
 * @return value:
 *                        class handle
 *
 *****************************************************************************/
class_handle_t USB_Class_Get_Class_Handle(void);

/**************************************************************************//*!
 *
 * @name  USB_Class_Get_Ctrler_Handle
 *
 * @brief  This function is called to return controller handle.
 *
 * @return value:
 *                        controller handle
 *
 *****************************************************************************/
usb_device_handle USB_Class_Get_Ctrler_Handle(class_handle_t class_handle);
#endif

#endif

/* EOF */
