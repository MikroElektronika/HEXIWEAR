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
* $FileName: usb_class_phdc.h$
* $Version : 3.8.2.0$
* $Date    : Sep-19-2011$
*
* Comments:
*
* @brief The file contains USB stack PHDC class layer api header function.
*
*****************************************************************************/

#ifndef _USB_CLASS_PHDC_H
#define _USB_CLASS_PHDC_H 1

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
#define USB_METADATA_SUPPORTED                  (0)
#define USB_DEV_EVENT_META_DATA_PARAMS_CHANGED  (0xF2)
#define USB_DEV_EVENT_FEATURE_CHANGED           (0xF3)

#if USB_METADATA_SUPPORTED
    #define META_DATA_MSG_PRE_IMPLEMENTED       (1)/*TRUE:1; FALSE:0*/
#else
    #define META_DATA_MSG_PRE_IMPLEMENTED       (0)/*TRUE:1; FALSE:0*/
#endif
/* Exception */
#define USB_REQ_VAL_INVALID             (0xFFFF)
/*****************************************************************************
 * Local Functions
 *****************************************************************************/

 /******************************************************************************
 * Types
 *****************************************************************************/
typedef uint32_t phdc_handle_t;

/*!
 * @brief Data structure for app.
 *
 * Holds the buffer information along with the send complete event.
 *
 */
typedef struct _phdc_app_data_struct 
{
    uint8_t   qos;        /*!< the qos of the transfer*/
    uint8_t*  buffer_ptr; /*!< the buffer point*/
    uint32_t  size;       /*!< the buffer size*/
} phdc_app_data_struct_t;

/*!
 * @brief  Structures used to configure PHDC class by  APP
 *
 * Holds the detailed information about the PHDC configuration.
 *
 */
typedef struct _phdc_config_struct
{
    usb_application_callback_struct_t           phdc_application_callback; /*!< application callback function to handle the Device status related event*/
    usb_vendor_req_callback_struct_t            vendor_req_callback;       /*!< application callback function to handle the vendor request related event, reserved for future use*/
    usb_class_specific_callback_struct_t        class_specific_callback;   /*!< application callback function to handle all the class related event*/
    usb_desc_request_notify_struct_t*           desc_callback_ptr;         /*!< descriptor related callback function data structure.*/
} phdc_config_struct_t;
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
 * Global Functions
 *****************************************************************************/
/*!
 * @brief The function initializes the Device and Controller layer.
 *
 * The application calls this API function to initialize the PHDC class, the underlying layers, and
 * the controller hardware.
 *
 * @param controller_id controller ID, such as USB_CONTROLLER_KHCI_0
 * @param phdc_config_ptr PHDC configuration structure
 * @param phdcHandle pointer point to the initialized PHDC class
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_PHDC_Init
(
    uint8_t                 controller_id,   /*[IN]*/
    phdc_config_struct_t*   phdc_config_ptr, /*[IN]*/
    phdc_handle_t *           phdcHandle /*[OUT]*/
);

/*!
 * @brief The function de-initializes the Device and Controller layer.
 *
 * The application calls this API function to de-initialize the PHDC class, the underlying layers, and
 * the controller hardware.
 * @param phdcHandle PHDC class handler  
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_PHDC_Deinit
(
    phdc_handle_t   handle
);

/*!
 * @brief Receives the PHDC data.
 *
 * The application calls this API function to receive data from host. Once the data is received, the
 * application layer receives a callback event USB_DEV_EVENT_DATA_RECEIVED.
 * 
 * @param handle PHDC class handler
 * @param qos the qos of the transfer
 * @param buff_ptr buffer to save the data from the host
 * @param size buffer length to receive  
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_PHDC_Recv_Data
(
    phdc_handle_t       handle,
    uint8_t             qos, 
    uint8_t*            buff_ptr,      /* [IN] buffer to send */      
    uint32_t            size           /* [IN] length of the transfer */
);

/*!
 * @brief Sends the PHDC data.
 *
 * The application calls this API function to send data specified by app_buff and size. Once the data is
 * sent, the application layer receives a callback event USB_DEV_EVENT_SEND_COMPLETE.
 * The application reserves the buffer until it receives a callback event stating that the data is sent.
 *
 * @param handle            PHDC class handler
 * @param meta_data         opaque meta data in app buffer
 * @param num_tfr           no. of transfers to follow with given channel--only valid if meta data is true
 * @param current_qos       qos of the transfers to follow--only valid if meta data is true
 * @param app_buff buffer   holding application data 
 * @param size              length of the transfer
 * @return                  USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_PHDC_Send_Data
(
    phdc_handle_t    handle,    
    bool             meta_data,    /* opaque meta data in app buffer */
    uint8_t          num_tfr,      /* no. of transfers to follow with given 
                                                            channel--only valid if meta data is 
                                                            true */
    uint8_t          qos,  /* qos of the transfers to follow--only 
                                                             valid if meta data is true */
    uint8_t*         app_buff,     /* buffer holding application data */
    uint32_t         size          /* [IN] length of the transfer */
);

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
 *         USB_OK           : When Successfull 
 *         Others           : Errors
 *****************************************************************************/
extern usb_status USB_Class_PHDC_Cancel
(
    phdc_handle_t handle,/*[IN]*/
    uint8_t ep_num,/*[IN]*/
    uint8_t direction
);
#endif

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
extern usb_status USB_Class_PHDC_Get_Speed
(
    phdc_handle_t         handle,
    uint16_t *            speed/* [OUT] the requested error */
);

extern void USB_Class_Periodic_Task(void);                               
#define USB_PHDC_Periodic_Task USB_Class_Periodic_Task
#define USB_Class_PHDC_Periodic_Task USB_Class_Periodic_Task
#ifdef __cplusplus
    }
#endif
#endif

/* EOF */
