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
* $FileName: usb_hid.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains USB stack HID class layer api header function.
*
*****************************************************************************/

#ifndef _USB_HID_H
#define _USB_HID_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class_hid.h"
#include "usb_hid_config.h"

/******************************************************************************
 * Macro's
 *****************************************************************************/
/* for class specific requests */
#define REPORT_SIZE                       (4)


/*****************************************************************************
 * Local Functions
 *****************************************************************************/
void    USB_Service_Hid(usb_event_struct_t* event,void* arg);
void    USB_Class_Hid_Event(uint8_t event, void* val,void* arg);
usb_status USB_HID_Requests(usb_setup_struct_t * setup_packet, uint8_t * *data, uint32_t *size,void* arg);


 /******************************************************************************
 * Types
 *****************************************************************************/

/* USB class hid endpoint data */
typedef struct _hid_endpoint_struct
{
    uint8_t                                  endpoint; /* endpoint num */
    uint8_t                                  type;     /* type of endpoint (interrupt, bulk or isochronous) */ 
}hid_endpoint_struct_t;

/* contains the endpoint data for non control endpoints */
typedef struct _hid_endpoint_data_struct
{
    hid_endpoint_struct_t                    ep[MAX_HID_CLASS_EP_NUM];
}hid_endpoint_data_struct_t;

/* Structure holding HID class state information*/
typedef struct hid_device_struct
{
    usb_device_handle                            handle;
    uint32_t                                     user_handle;
    class_handle_t                               class_handle;
    usb_endpoints_t*                             ep_desc_data;
    usb_application_callback_struct_t            hid_application_callback;
    usb_vendor_req_callback_struct_t             vendor_req_callback;
    usb_class_specific_callback_struct_t         class_specific_callback;
    usb_desc_request_notify_struct_t             desc_callback;
    hid_endpoint_data_struct_t                   hid_endpoint_data;
}hid_device_struct_t;
 
/******************************************************************************
 * Global Functions
 *****************************************************************************/

#endif
/* EOF */
