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
* $FileName: usb_phdc.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains USB stack PHDC class layer api header function.
*
*****************************************************************************/
#ifndef _USB_PHDC_H
#define _USB_PHDC_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class_phdc.h"
#include "usb_phdc_config.h"
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/ 
#define SET_FEATURE_REQUEST               (3)
#define CLEAR_FEATURE_REQUEST             (1)
#define GET_STATUS_REQUEST                (0)
#define INVALID_VAL                       (0xFF)
#define USB_SET_REQUEST_MASK              (0x02)


/******************************************************************************
 * Types
 *****************************************************************************/
 
/* structure to hold a request in the endpoint QOS bin */

PACKED_STRUCT_BEGIN
struct _usb_class_phdc_qos_bin 
{
    uint8_t*                    app_buff;   /* buffer to send */
    uint32_t                    size;       /* size of the transfer */
    bool                        meta_data;  /* packet is a meta data or not */
    uint8_t                     channel;    /* endpoint num */
    uint8_t                     num_tfr;    /* num of transfers that follow the meta data packet.
                                                                           used only when meta_data is TRUE */                               
    uint8_t                     qos;        /* qos of the transfers that follow the meta data packet */
} 
PACKED_STRUCT_END;

typedef struct _usb_class_phdc_qos_bin usb_class_phdc_qos_bin_t;

/* USB class phdc endpoint data */
typedef struct _usb_class_phdc_tx_endpoint 
{
    uint32_t                    size;               /* from the application */
    usb_class_phdc_qos_bin_t    qos_bin[MAX_QOS_BIN_ELEMS]; 
    uint8_t                     endpoint;           /* from the application */
    uint8_t                     type;               /* from the application */ 
    uint8_t                     qos;                /* from the application */
    uint8_t                     current_qos;        /* from received meta data */
    uint8_t                     transfers_left;     /* from application meta data */
    uint8_t                     bin_consumer;       /* num of dequeued transfers */
    uint8_t                     bin_producer;       /* num of queued transfers */
} usb_class_phdc_tx_endpoint_t;

typedef struct _usb_class_phdc_rx_endpoint 
{
    uint8_t*                    buff_ptr;
    uint32_t                    size;               /* from the application */
    uint16_t                    buffer_size;
    uint8_t                     endpoint;           /* from the application */
    uint8_t                     type;               /* from the application */
    uint8_t                     qos;                /* from the application */
    uint8_t                     current_qos;        /* from received meta data */    
    uint8_t                     transfers_left;     /* from received meta data */
} usb_class_phdc_rx_endpoint_t;
  
typedef struct _usb_class_phdc_endpoint_data 
{
    usb_device_handle               handle;
    usb_class_phdc_rx_endpoint_t    ep_rx[MAX_ENDPOINT_SUPPORT];  
    usb_class_phdc_tx_endpoint_t    ep_tx[MAX_ENDPOINT_SUPPORT];
    uint8_t                         count_rx;
    uint8_t                         count_tx;
} usb_class_phdc_endpoint_data_t; 

#if USB_METADATA_SUPPORTED
#define METADATA_PREAMBLE_SIGNATURE     (16)
#define METADATA_QOSENCODING_VERSION    (1)
#define METADATA_HEADER_SIZE            (21)
/* structure for meta_data msg preamble */
typedef struct _usb_meta_data_msg_preamble 
{
    char                        signature[METADATA_PREAMBLE_SIGNATURE];
    uint8_t                     num_tfr;
    uint8_t                     version;
    uint8_t                     qos;
    uint8_t                     opaque_data_size;
    uint8_t                     opaque_data[1];
} usb_meta_data_msg_preamble_t;

typedef struct _usb_app_event_metadata_params 
{
    uint8_t*                    metadata_ptr;
    uint32_t                    size;
    uint8_t                     channel;
    uint8_t                     num_tfr;
    uint8_t                     qos;
} usb_app_event_metadata_params_t;
#endif

/* Structure Representing PHDC class */
typedef struct _phdc_device_struct
{
    usb_device_handle                               handle;
    uint32_t                                        user_handle;
    class_handle_t                                  class_handle;
    usb_endpoints_t*                                ep_desc_data;
    usb_application_callback_struct_t               phdc_application_callback;
    usb_vendor_req_callback_struct_t                vendor_req_callback; 
    usb_class_specific_callback_struct_t            class_specific_callback;
    usb_desc_request_notify_struct_t                desc_callback;
    /* RAM buffer for configuring next receive */
    uint8_t*                                        service_buff_ptr; 
    usb_class_phdc_endpoint_data_t                  phdc_endpoint_data;
#if META_DATA_MSG_PRE_IMPLEMENTED
    usb_meta_data_msg_preamble_t                    meta_data_msg_preamble; 
#endif
    /* used to store a bit map of the active endpoints */
    os_mutex_handle                                 mutex;
    uint16_t                                        phdc_ep_has_data;
#if USB_METADATA_SUPPORTED
    /* used to store whether meta-data feature is active or not */
    bool                                            phdc_metadata;
#endif
} phdc_device_struct_t;

/******************************************************************************
 * Global Functions
 *****************************************************************************/
void    USB_Class_PHDC_Event( uint8_t event, void* val, void* arg);
usb_status USB_PHDC_Requests ( usb_setup_struct_t * setup_packet, uint8_t **data, uint32_t *size, void* arg); 
#endif
