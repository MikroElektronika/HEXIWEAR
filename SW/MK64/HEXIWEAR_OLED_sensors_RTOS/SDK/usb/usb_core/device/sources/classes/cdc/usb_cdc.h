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
 * $FileName: usb_cdc.h$
 * $Version :
 * $Date    :
 *
 * Comments:
 *
 * @brief The file contains USB stack CDC class layer api header function.
 *
 *****************************************************************************/

#ifndef _USB_CDC_H
#define _USB_CDC_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class.h"
#include "usb_cdc_config.h"

/******************************************************************************
 * Macro's
 *****************************************************************************/
/* other macros */
#define NOTIF_PACKET_SIZE                (0x08)
#define NOTIF_REQUEST_TYPE               (0xA1)

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
void USB_Service_Cdc_Notif(usb_event_struct_t* event, void* arg);
void USB_Service_Dic_Bulk_In(usb_event_struct_t* event, void* arg);
void USB_Service_Dic_Bulk_Out(usb_event_struct_t* event, void* arg);

void USB_Class_CDC_Event(uint8_t event, void* val, void* arg);
usb_status USB_CDC_Other_Requests(usb_setup_struct_t * setup_packet, uint8_t * *data, uint32_t *size, void* arg);

/******************************************************************************
 * Types
 *****************************************************************************/
typedef enum
{
    USB_EP_COUNT = 0,
    USB_CDC_EP_COUNT,
    USB_INTERFACE_COUNT,
    USB_CDC_INTERFACE_COUNT
} USB_DESC_INFO_T;

#if CDC_IMPLEMENT_QUEUING
/* structure to hold a request in the endpoint queue */
typedef struct _cdc_queue_struct
{
    usb_device_handle handle;
    uint8_t channel;
    cdc_app_data_struct_t app_data;
}cdc_queue_struct_t;
#endif

/* USB class cdc endpoint data */
typedef struct _cdc_endpoint_struct
{
    uint8_t endpoint; /* endpoint num */
    uint8_t type; /* type of endpoint (interrupt, bulk or isochronous) */
#if CDC_IMPLEMENT_QUEUING
    volatile uint8_t bin_consumer;/* the num of queued elements */
    volatile uint8_t bin_producer;/* the num of de-queued elements */
    cdc_queue_struct_t queue[CDC_MAX_QUEUE_ELEMS]; /* queue data */
#endif
    uint8_t direction;
} cdc_endpoint_struct_t;

typedef struct _cdc_variable_struct
{
    class_handle_t class_handle;
    usb_device_handle controller_handle;
    usb_endpoints_t* usb_ep_data;
    uint32_t comm_feature_data_size;
    uint8_t cic_send_endpoint;
    uint8_t cic_recv_endpoint;
    uint8_t dic_send_endpoint;
    uint8_t dic_recv_endpoint;
    uint32_t dic_recv_pkt_size;
    uint32_t dic_send_pkt_size;
    uint32_t cic_send_pkt_size;
    /* Holds the PSTN object*/
    void* pstn_obj_ptr;
    usb_application_callback_struct_t cdc_application_callback;
    usb_vendor_req_callback_struct_t vendor_req_callback;
    usb_class_specific_callback_struct_t class_specific_callback;
    /* contains the endpoint info */
    cdc_endpoint_struct_t ep[MAX_CDC_EP_NUM];
    usb_desc_request_notify_struct_t desc_callback;
#if CDC_RNDIS_SUPPORT
    uint8_t max_supported_interfaces;
    /* rndis specific configuration */
    usb_rndis_info_struct_t rndis_info;
#endif
    os_mutex_handle send_mutex;
    os_mutex_handle recv_mutex;
    bool has_sent_state;
} cdc_device_struct_t;

/******************************************************************************
 * Global Functions of Subclass
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  USB_Pstn_Init
 *
 * @brief The function initializes the Pstn Module
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param class_callback:       event callback
 *
 * @return status
 *         USB_OK           : When Successful
 *         Others           : Errors
 *
 *****************************************************************************/
usb_status USB_Pstn_Init
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_application_callback_struct_t* pstn_cb
    );
/**************************************************************************//*!
 *
 * @name  USB_Pstn_Deinit
 *
 * @brief The function initializes the Pstn Module
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param class_callback:       event callback
 *
 * @return status
 *         USB_OK           : When Successful
 *         Others           : Errors
 *
 *****************************************************************************/
usb_status USB_Pstn_Deinit
(
    cdc_device_struct_t * cdc_obj_ptr
    );
/**************************************************************************//*!
 *
 * @name  PSTN_Get_Line_Coding
 *
 * @brief  This function is called in response to GetLineCoding request
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
extern usb_status PSTN_Get_Line_Coding(cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size);

/**************************************************************************//*!
 *
 * @name  PSTN_Set_Line_Coding
 *
 * @brief  This function is called in response to SetLineCoding request
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
extern usb_status PSTN_Set_Line_Coding(cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size);

/**************************************************************************//*!
 *
 * @name  PSTN_Set_Ctrl_Line_State
 *
 * @brief  This function is called in response to Set Control Line State
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : When Successful
 *                        Others : When Error
 *
 *****************************************************************************/
extern usb_status PSTN_Set_Ctrl_Line_State(cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size);

/**************************************************************************//*!
 *
 * @name  PSTN_Send_Break
 *
 * @brief  This function is called in response to Set Config request
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : When Successful
 *                        Others : When Error
 *
 *****************************************************************************/
extern usb_status PSTN_Send_Break(cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size);

/**************************************************************************//*!
 *
 * @name  PSTN_Get_Comm_Feature
 *
 * @brief  This function is called in response to GetCommFeature request
 *
 * @param cdc_obj_ptr :     Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
extern usb_status PSTN_Get_Comm_Feature(cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size);

/**************************************************************************//*!
 *
 * @name  PSTN_Set_Comm_Feature
 *
 * @brief  This function is called in response to SetCommFeature request
 *
 * @param cdc_obj_ptr :     Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
extern usb_status PSTN_Set_Comm_Feature(cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size);

/**************************************************************************//*!
 *
 * @name  PSTN_Send_Serial_State
 *
 * @brief  This function is called to send serial state notification
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 *
 * @return NONE
 *****************************************************************************/
extern void PSTN_Send_Serial_State(cdc_device_struct_t * cdc_obj_ptr);

/**************************************************************************//*!
 *
 * @name  PSTN_Response_Available
 *
 * @brief  This function is called to send notification to host that a
 *         response is available
 *
 * @param cdc_obj_ptr
 *
 * @return NONE
 *****************************************************************************/
extern void PSTN_Response_Available(cdc_device_struct_t * cdc_obj_ptr);
#if CDC_RNDIS_SUPPORT
/**************************************************************************//*!
 *
 * @name  PSTN_Rndis_Message_Set
 *
 * @brief  This function is called in response to PSTN_Rndis_Message_Set
 *
 * @param cdc_obj_ptr :     Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
extern usb_status PSTN_Rndis_Message_Set(cdc_device_struct_t * cdc_obj_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);
/**************************************************************************//*!
 *
 * @name  PSTN_Rndis_Message_Get
 *
 * @brief  This function is called in response to PSTN_Rndis_Message_Get
 *
 * @param cdc_obj_ptr :     Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
extern usb_status PSTN_Rndis_Message_Get(cdc_device_struct_t * cdc_obj_ptr,
usb_setup_struct_t * setup_packet,
uint8_t * *data,
uint32_t *size);

extern void RNDIS_Initialize_Command
(
cdc_device_struct_t * cdc_obj_ptr,
uint8_t * *data,
uint32_t *size
);
extern void RNDIS_Query_Command
(
cdc_device_struct_t * cdc_obj_ptr,
uint8_t * *data,
uint32_t *size
);
extern void RNDIS_Set_Command
(
cdc_device_struct_t * cdc_obj_ptr,
uint8_t * *data,
uint32_t *size
);
extern void RNDIS_Reset_Command
(
cdc_device_struct_t * cdc_obj_ptr,
uint8_t * *data,
uint32_t *size
);
extern void RNDIS_Indicate_Status_Command
(
cdc_device_struct_t * cdc_obj_ptr,
uint8_t * *data,
uint32_t *size
);
extern void RNDIS_Keepalive_Command
(
cdc_device_struct_t * cdc_obj_ptr,
uint8_t * *data,
uint32_t *size
);
extern void RNDIS_Halt_Command
(
cdc_device_struct_t * cdc_obj_ptr
);

#endif/*endif CDC_RNDIS_SUPPORT*/
/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/
/*************************************************************************//*!
 *
 * @name	USB_Cdc_Mutex_Lock
 *
 * @brief The function locks the mutex for RTOS. For BM, disable interrupt.
 *
 * @param none.
 * @return none.
 *
 *****************************************************************************/
void USB_Cdc_Mutex_Lock(os_mutex_handle handle);
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
void USB_Cdc_Mutex_Unlock(os_mutex_handle handle);
#endif

/* EOF */
