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
* $FileName: usb_class_cdc.h$
* $Version :
* $Date    :
*
* Comments:
*
* @brief The file contains USB stack CDC class layer api header function.
*
*****************************************************************************/

#ifndef _USB_CLASS_CDC_H
#define _USB_CLASS_CDC_H 1


/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class.h"
/******************************************************************************
 * Macro's
 *****************************************************************************/
/* Class specific request Codes */
#define SEND_ENCAPSULATED_COMMAND       (0x00)
#define GET_ENCAPSULATED_RESPONSE       (0x01)
#define SET_COMM_FEATURE                (0x02)
#define GET_COMM_FEATURE                (0x03)
#define CLEAR_COMM_FEATURE              (0x04)
#define SET_AUX_LINE_STATE              (0x10)
#define SET_HOOK_STATE                  (0x11)
#define PULSE_SETUP                     (0x12)
#define SEND_PULSE                      (0x13)
#define SET_PULSE_TIME                  (0x14)
#define RING_AUX_JACK                   (0x15)
#define SET_LINE_CODING                 (0x20)
#define GET_LINE_CODING                 (0x21)
#define SET_CONTROL_LINE_STATE          (0x22)
#define SEND_BREAK                      (0x23)
#define SET_RINGER_PARAMS               (0x30)
#define GET_RINGER_PARAMS               (0x31)
#define SET_OPERATION_PARAM             (0x32)
#define GET_OPERATION_PARAM             (0x33)
#define SET_LINE_PARAMS                 (0x34)
#define GET_LINE_PARAMS                 (0x35)
#define DIAL_DIGITS                     (0x36)
#define SET_UNIT_PARAMETER              (0x37)
#define GET_UNIT_PARAMETER              (0x38)
#define CLEAR_UNIT_PARAMETER            (0x39)
#define GET_PROFILE                     (0x3A)
#define SET_ETHERNET_MULTICAST_FILTERS  (0x40)
#define SET_ETHERNET_POW_PATTER_FILTER  (0x41)
#define GET_ETHERNET_POW_PATTER_FILTER  (0x42)
#define SET_ETHERNET_PACKET_FILTER      (0x43)
#define GET_ETHERNET_STATISTIC          (0x44)
#define SET_ATM_DATA_FORMAT             (0x50)
#define GET_ATM_DEVICE_STATISTICS       (0x51)
#define SET_ATM_DEFAULT_VC              (0x52)
#define GET_ATM_VC_STATISTICS           (0x53)
#define MDLM_SPECIFIC_REQUESTS_MASK     (0x7F)

#define GET_ABSTRACT_STATE              (0x23)
#define GET_COUNTRY_SETTING             (0x24)
#define SET_ABSTRACT_STATE              (0x25)
#define SET_COUNTRY_SETTING             (0x26)
/* Class Specific Notification Codes */
#define NETWORK_CONNECTION_NOTIF        (0x00)
#define RESPONSE_AVAIL_NOTIF            (0x01)
#define AUX_JACK_HOOK_STATE_NOTIF       (0x08)
#define RING_DETECT_NOTIF               (0x09)
#define SERIAL_STATE_NOTIF              (0x20)
#define CALL_STATE_CHANGE_NOTIF         (0x28)
#define LINE_STATE_CHANGE_NOTIF         (0x29)
#define CONNECTION_SPEED_CHANGE_NOTIF   (0x2A)
/* Events to the Application */ /* 0 to 4 are reserved for class events */
#define USB_APP_CDC_CARRIER_DEACTIVATED (0x61)
#define USB_APP_CDC_CARRIER_ACTIVATED   (0x62)
#define USB_APP_CDC_DTE_DEACTIVATED     (0x63)
#define USB_APP_CDC_DTE_ACTIVATED       (0x64)
#define USB_APP_GET_LINK_SPEED          (0x65)
#define USB_APP_GET_LINK_STATUS         (0x66)
#define USB_APP_CDC_SERIAL_STATE_NOTIF  (0x67)

/* Exception */
#define USB_REQ_VAL_INVALID             (0xFFFF)

/**********************
 * RNDIS Device States
 **********************/
#define RNDIS_UNINITIALIZED                (0x01)
#define RNDIS_INITIALIZED                  (0x02)
#define RNDIS_DATA_INITIALIZED             (0x03)

//extern void USB_Class_Periodic_Task(void);
#define USB_CDC_Periodic_Task USB_Class_Periodic_Task
/******************************************************************************
 * Types
 *****************************************************************************/
/* Type representing CDC class handle*/
typedef uint32_t  cdc_handle_t;
typedef uint32_t  _ip_address;
typedef uint8_t   enet_address_t[6];

/*!
 * @brief structure used to configure CDC class by APP.
 *
 * Define the structure of the CDC class configuration.
 *
 */
typedef struct _cdc_config_struct
{
    usb_application_callback_struct_t        cdc_application_callback;        /*!< application callback function to handle the Device status related event*/
    usb_vendor_req_callback_struct_t         vendor_req_callback;             /*!< application callback function to handle the vendor request related event, reserved for future use*/
    usb_class_specific_callback_struct_t     class_specific_callback;         /*!< application callback function to handle all the class related event*/
    usb_desc_request_notify_struct_t*        desc_callback_ptr;               /*!< descriptor related callback function data structure*/
} cdc_config_struct_t;

/*!
 * @brief structure to hold the information of CDC app data struct.
 *
 * Define the structure of the CDC app data.
 *
 */
typedef struct _cdc_app_data_struct
{
    uint8_t*                                  data_ptr;     /* pointer to buffer       */
    uint32_t                                  data_size;    /* buffer size of endpoint */
} cdc_app_data_struct_t;

/*!
 * @brief structure to hold the information of CDC rndis information data struct.
 *
 * Define the structure of the CDC rndis information data.
 *
 */
typedef struct _usb_rndis_info_struct
{
    enet_address_t mac_address;
    _ip_address   ip_address;
    uint32_t      rndis_max_frame_size;
} usb_rndis_info_struct_t;
/******************************************************************************
 * Global Functions
 *****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*!
* @brief The function initializes the Device and Controller layer
*
* This function initializes the CDC Class layer and layers it is dependednt on
*
* @param controller_id    [in] - controller ID, such as USB_CONTROLLER_KHCI_0
* @param *cdc_config_ptr[IN]:  This structure contains configuration parameter
* @param cdc_handle_ptr    [out] - pointer point to the initialized CDC class, refer to cdc_handle_t
*
*
* @return USB_OK-Success/Others-Fail
*/
extern usb_status USB_Class_CDC_Init
(
    uint8_t controller_id,
    cdc_config_struct_t * cdc_config_ptr,
    cdc_handle_t *    cdc_handle_ptr
);

/*!
 * @brief The function de-initializes the Device and Controller layer
 *
 * @param cdc_handle        [in] - The CDC class handler
 *
 * This function de-initializes the CDC Class layer and layers it is dependent on
 *
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_CDC_Deinit
(
    cdc_handle_t cdc_handle
);

#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Cancel
 *
 * @brief
 *
 * @param handle           :   handle returned by USB_Class_CDC_Init
 * @param ep_num           :   endpoint num
 * @param direction        :   direction of the endpoint
 *
 * @return status
 *         USB_OK             : When Successfully
 *         Others             : Errors
 *****************************************************************************/

usb_status USB_Class_CDC_Cancel
(
    cdc_handle_t cdc_handle,/*[IN]*/
    uint8_t ep_num,/*[IN]*/
    uint8_t type,
    uint8_t direction
);
#endif

/*!
* @brief  This function sends data to Host.
*
* @param cdc_handle          :   handle returned by USB_Class_CDC_Init
* @param ep_num          :   endpoint num
* @param buff_ptr        :   buffer to send
* @param size            :   length of the transfer
*
* @return USB_OK-Success/Others-Fail
*/
extern usb_status USB_Class_CDC_Send_Data
(
    cdc_handle_t          handle,
    uint8_t             ep_num,
    uint8_t*            app_buff,      /* [IN] buffer to send */
    uint32_t            size           /* [IN] length of the transfer */
);

/*!
* @brief This functions receives Data from Host.
*
* @param cdc_handle          :   handle returned by USB_Class_CDC_Init
* @param ep_num          :   endpoint num
* @param buff_ptr        :   buffer to send
* @param size            :   length of the transfer
*
* @return USB_OK-Success/Others-Fail
*/
extern usb_status USB_Class_CDC_Recv_Data
(
    cdc_handle_t          cdc_handle,
    uint8_t             ep_num,
    uint8_t*            buff_ptr,      /* [IN] buffer to send */
    uint32_t            size           /* [IN] length of the transfer */
);


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
extern usb_status USB_Class_CDC_Get_Speed
(
    cdc_handle_t         cdc_handle,
    uint16_t *           speed/* [OUT] the requested error */
);

#ifdef __cplusplus
}
#endif
#endif

