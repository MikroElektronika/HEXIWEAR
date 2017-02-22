/**HEADER********************************************************************
* 
* Copyright (c) 2008, 2013 Freescale Semiconductor;
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
* $FileName: usb_desc.h$
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file contains struct definitions for USB descriptors.
*
*END************************************************************************/
#ifndef __usb_desc_h__
#define __usb_desc_h__

//#include "compiler.h"

/* USB Descriptor Endpoint types */
#define USB_CONTROL_PIPE                    (0x00)
#define USB_ISOCHRONOUS_PIPE                (0x01)
#define USB_BULK_PIPE                       (0x02)
#define USB_INTERRUPT_PIPE                  (0x03)

/* USB Descriptor Direction constants */
#define USB_RECV                            (0)
#define USB_SEND                            (1)

/* USB Descriptor Lengths */
#define USB_DESC_LEN_DEV               (18)
#define USB_DESC_LEN_CFG               (9)
#define USB_DESC_LEN_STR               (2)  /* minimum length */
#define USB_DESC_LEN_IF                (9)
#define USB_DESC_LEN_EP                (7)
#define USB_DESC_LEN_DEV_QUALIFIER     (10)
#define USB_DESC_LEN_OTHER_SPEED_CFG   (USB_DESC_LEN_CFG)

/* USB Descriptor Types */
#define USB_DESC_TYPE_DEV              (1)
#define USB_DESC_TYPE_CFG              (2)
#define USB_DESC_TYPE_STR              (3)
#define USB_DESC_TYPE_IF               (4)
#define USB_DESC_TYPE_EP               (5)
#define USB_DESC_TYPE_DEV_QUALIFIER    (6)
#define USB_DESC_TYPE_OTHER_SPEED_CFG  (7)
#define USB_DESC_TYPE_IF_POWER         (8)
#define USB_DESC_TYPE_OTG              (9)
#define USB_DESC_TYPE_HID              (0x21)
#define USB_DESC_TYPE_REPORT           (0x22)

/* USB Functional Descriptor Types */
#define USB_DESC_TYPE_CS_INTERFACE     (0x24)
#define USB_DESC_TYPE_CS_ENDPOINT      (0x25)


/* USB Standard Device Requests - bmRequestType */
#define USB_DEV_REQ_STD_REQUEST_TYPE_DIR_MASK   (0x1)
#define USB_DEV_REQ_STD_REQUEST_TYPE_DIR_SHIFT  (7)
#define USB_DEV_REQ_STD_REQUEST_TYPE_DIR_POS    (USB_DEV_REQ_STD_REQUEST_TYPE_DIR_MASK << USB_DEV_REQ_STD_REQUEST_TYPE_DIR_SHIFT)

#define USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_MASK  (0x3)
#define USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_SHIFT (5)
#define USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_POS   (USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_MASK << USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_SHIFT)

#define USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_MASK  (0x1F)
#define USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_SHIFT (0)
#define USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_POS   (USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_MASK << USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_SHIFT)

#define USB_DEV_REQ_STD_REQUEST_TYPE_DIR_OUT ((0x0 & USB_DEV_REQ_STD_REQUEST_TYPE_DIR_MASK) << USB_DEV_REQ_STD_REQUEST_TYPE_DIR_SHIFT)
#define USB_DEV_REQ_STD_REQUEST_TYPE_DIR_IN  ((0x1 & USB_DEV_REQ_STD_REQUEST_TYPE_DIR_MASK) << USB_DEV_REQ_STD_REQUEST_TYPE_DIR_SHIFT)

#define USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_STANDARD ((0x0 & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_MASK) << USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_SHIFT)
#define USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_CLASS    ((0x1 & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_MASK) << USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_SHIFT)
#define USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_VENDOR   ((0x2 & USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_MASK) << USB_DEV_REQ_STD_REQUEST_TYPE_TYPE_SHIFT)

#define USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_DEVICE    ((0x00 & USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_MASK) << USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_SHIFT)
#define USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_INTERFACE ((0x01 & USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_MASK) << USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_SHIFT)
#define USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_ENDPOINT  ((0x02 & USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_MASK) << USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_SHIFT)
#define USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_OTHER     ((0x03 & USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_MASK) << USB_DEV_REQ_STD_REQUEST_TYPE_RECIPIENT_SHIFT)

/* USB Standard Request Codes - bRequest */
#define USB_DEV_REQ_STD_REQUEST_GET_STATUS         (0)
#define USB_DEV_REQ_STD_REQUEST_CLEAR_FEATURE      (1)
#define USB_DEV_REQ_STD_REQUEST_SET_FEATURE        (3)
#define USB_DEV_REQ_STD_REQUEST_SET_ADDRESS        (5)
#define USB_DEV_REQ_STD_REQUEST_GET_DESCRIPTOR     (6)
#define USB_DEV_REQ_STD_REQUEST_SET_DESCRIPTOR     (7)
#define USB_DEV_REQ_STD_REQUEST_GET_CONFIGURATION  (8)
#define USB_DEV_REQ_STD_REQUEST_SET_CONFIGURATION  (9)
#define USB_DEV_REQ_STD_REQUEST_GET_INTERFACE      (10)
#define USB_DEV_REQ_STD_REQUEST_SET_INTERFACE      (11)
#define USB_DEV_REQ_STD_REQUEST_SYNCH_FRAME        (12)

#define GET_STATUS_DEVICE_MASK           (0x0003)  
#define REMOTE_WAKEUP_STATUS_MASK        (0x0002) 
/* identification values and masks to identify request types  */
//#define USB_REQUEST_CLASS_MASK   (0x60) 
//#define USB_REQUEST_CLASS_STRD   (0x00) 
//#define USB_REQUEST_CLASS_CLASS  (0x20) 
//#define USB_REQUEST_CLASS_VENDOR (0x40) 
#define USB_GET_STATUS_ATTRIBUTES_SELF_POWERED_SHIFT (0)
#define USB_GET_STATUS_ATTRIBUTES_REMOTE_WAKEUP_SHIFT (1)
/* Configuration bmAttributes fields */
#define USB_DESC_CFG_ATTRIBUTES_D7_MASK  (0x1)
#define USB_DESC_CFG_ATTRIBUTES_D7_SHIFT (7)
#define USB_DESC_CFG_ATTRIBUTES_D7_POS   (USB_DESC_CFG_ATTRIBUTES_D7_MASK << USB_DESC_CFG_ATTRIBUTES_D7_SHIFT)
                                                         
#define USB_DESC_CFG_ATTRIBUTES_SELF_POWERED_MASK  (0x1)
#define USB_DESC_CFG_ATTRIBUTES_SELF_POWERED_SHIFT (6)
#define USB_DESC_CFG_ATTRIBUTES_SELF_POWERED_POS   (USB_DESC_CFG_ATTRIBUTES_SELF_POWERED_MASK << USB_DESC_CFG_ATTRIBUTES_SELF_POWERED_SHIFT)

#define USB_DESC_CFG_ATTRIBUTES_REMOTE_WAKEUP_MASK  (0x1)
#define USB_DESC_CFG_ATTRIBUTES_REMOTE_WAKEUP_SHIFT (5)
#define USB_DESC_CFG_ATTRIBUTES_REMOTE_WAKEUP_POS   (USB_DESC_CFG_ATTRIBUTES_REMOTE_WAKEUP_MASK << USB_DESC_CFG_ATTRIBUTES_REMOTE_WAKEUP_SHIFT)

/* Endpoint bEndpointAddress fields */
#define USB_DESC_EP_ENDPOINT_ADDRESS_DIR_MASK  (0x1)
#define USB_DESC_EP_ENDPOINT_ADDRESS_DIR_SHIFT (7)
#define USB_DESC_EP_ENDPOINT_ADDRESS_DIR_POS   (USB_DESC_EP_ENDPOINT_ADDRESS_DIR_MASK << USB_DESC_EP_ENDPOINT_ADDRESS_DIR_SHIFT)

#define USB_DESC_EP_ENDPOINT_ADDRESS_EP_NUMBER_MASK  (0xF)
#define USB_DESC_EP_ENDPOINT_ADDRESS_EP_NUMBER_SHIFT (0)
#define USB_DESC_EP_ENDPOINT_ADDRESS_EP_NUMBER_POS   (USB_DESC_EP_ENDPOINT_ADDRESS_EP_NUMBER_MASK << USB_DESC_EP_ENDPOINT_ADDRESS_EP_NUMBER_SHIFT)

#define USB_DESC_EP_ENDPOINT_ADDRESS_DIR_OUT ((0x0 & USB_DESC_EP_ENDPOINT_ADDRESS_DIR_MASK) << USB_DESC_EP_ENDPOINT_ADDRESS_DIR_SHIFT)
#define USB_DESC_EP_ENDPOINT_ADDRESS_DIR_IN  ((0x1 & USB_DESC_EP_ENDPOINT_ADDRESS_DIR_MASK) << USB_DESC_EP_ENDPOINT_ADDRESS_DIR_SHIFT)

/* Endpoint bmAttributes fields */
#define USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_MASK  (0x3)
#define USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_SHIFT (0)
#define USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_POS   (USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_MASK << USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_SHIFT)

#define USB_DESC_EP_ATTRIBUTES_SYNC_TYPE_MASK  (0x3)
#define USB_DESC_EP_ATTRIBUTES_SYNC_TYPE_SHIFT (2)
#define USB_DESC_EP_ATTRIBUTES_SYNC_TYPE_POS   (USB_DESC_EP_ATTRIBUTES_SYNC_TYPE_MASK << USB_DESC_EP_ATTRIBUTES_SYNC_TYPE_SHIFT)

#define USB_DESC_EP_ATTRIBUTES_USAGE_TYPE_MASK  (0x3)
#define USB_DESC_EP_ATTRIBUTES_USAGE_TYPE_SHIFT (4)
#define USB_DESC_EP_ATTRIBUTES_USAGE_TYPE_POS   (USB_DESC_EP_ATTRIBUTES_USAGE_TYPE_MASK << USB_DESC_EP_ATTRIBUTES_USAGE_TYPE_SHIFT)

#define USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_CONTROL     ((0x0 & USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_MASK) << USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_SHIFT)
#define USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_ISOCHRONOUS ((0x1 & USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_MASK) << USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_SHIFT)
#define USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_BULK        ((0x2 & USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_MASK) << USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_SHIFT)
#define USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_INTERRUPT   ((0x3 & USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_MASK) << USB_DESC_EP_ATTRIBUTES_TRANSFER_TYPE_SHIFT)

/* Standard Feature Selectors */
#define USB_DEV_REQ_STD_FEATURE_SELECTOR_MASK   (0x3)
#define USB_DEV_REQ_STD_FEATURE_SELECTOR_SHIFT  (0x0)
#define USB_DEV_REQ_STD_FEATURE_SELECTOR_ENDPOINT_HALT         (0)
#define USB_DEV_REQ_STD_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP  (1)
#define USB_DEV_REQ_STD_FEATURE_SELECTOR_TEST_MODE             (2)

#define USB_DEV_REQ_STD_FEATURE_B_HNP_ENABLE       (0x0003) /* B HNP enable  SET/CLEAR feature value */
#define USB_DEV_REQ_STD_FEATURE_A_HNP_SUPPORT      (0x0004) /* A HNP support SET/CLEAR feature value */

 typedef struct _usb_language 
{
    uint16_t language_id;
    uint8_t ** lang_desc;
    uint8_t * lang_desc_size;    
} usb_language_t;
 
typedef struct _usb_all_languages
{
    uint8_t *languages_supported_string;
    uint8_t  languages_supported_size;
    uint8_t  languages_number;
    /*Allocate Memory In App Layer*/
    usb_language_t *usb_language;
} usb_all_languages_t;

PACKED_STRUCT_BEGIN
struct usb_device_descriptor
{
   uint8_t   bLength;          /* Descriptor size in bytes = 18 */
   uint8_t   bDescriptorType;  /* DEVICE descriptor type = 1 */
   uint8_t   bcdUSD[2];        /* USB spec in BCD, e.g. 0x0200 */
   uint8_t   bDeviceClass;     /* Class code, if 0 see interface */
   uint8_t   bDeviceSubClass;  /* Sub-Class code, 0 if class = 0 */
   uint8_t   bDeviceProtocol;  /* Protocol, if 0 see interface */
   uint8_t   bMaxPacketSize;   /* Endpoint 0 max. size */
   uint8_t   idVendor[2];      /* Vendor ID per USB-IF */
   uint8_t   idProduct[2];     /* Product ID per manufacturer */
   uint8_t   bcdDevice[2];     /* Device release # in BCD */
   uint8_t   iManufacturer;    /* Index to manufacturer string */
   uint8_t   iProduct;         /* Index to product string */
   uint8_t   iSerialNumber;    /* Index to serial number string */
   uint8_t   bNumConfigurations; /* Number of possible configurations */ 
} PACKED_STRUCT_END;
typedef struct usb_device_descriptor device_descriptor_t;

PACKED_STRUCT_BEGIN
struct usb_configuration_descriptor
{
   uint8_t   bLength;          /* Descriptor size in bytes = 9 */
   uint8_t   bDescriptorType;  /* CONFIGURATION type = 2 or 7 */
   uint8_t   wTotalLength[2];  /* Length of concatenated descriptors */
   uint8_t   bNumInterfaces;   /* Number of interfaces, this config. */
   uint8_t   bConfigurationValue;  /* Value to set this config. */ 
   uint8_t   iConfig;          /* Index to configuration string */
   uint8_t   bmAttributes;     /* Config. characteristics */
   #define  CONFIG_RES7       (0x80)  /* Reserved, always = 1 */
   #define  CONFIG_SELF_PWR   (0x40)  /* Self-powered device */
   #define  CONFIG_WAKEUP     (0x20)  /* Remote wakeup */
   uint8_t   bMaxPower;        /* Max.power from bus, 2mA units */
} PACKED_STRUCT_END;
typedef struct usb_configuration_descriptor usb_configuration_descriptor_t;  

PACKED_STRUCT_BEGIN
struct usb_interface_descriptor
{
   uint8_t   bLength;          /* Descriptor size in bytes = 9 */
   uint8_t   bDescriptorType;  /* INTERFACE descriptor type = 4 */
   uint8_t   bInterfaceNumber; /* Interface no.*/
   uint8_t   bAlternateSetting;  /* Value to select this IF */
   uint8_t   bNumEndpoints;    /* Number of endpoints excluding 0 */
   uint8_t   bInterfaceClass;  /* Class code, 0xFF = vendor */
   uint8_t   bInterfaceSubClass;  /* Sub-Class code, 0 if class = 0 */
   uint8_t   bInterfaceProtocol;  /* Protocol, 0xFF = vendor */
   uint8_t   iInterface;       /* Index to interface string */
} PACKED_STRUCT_END;
typedef struct usb_interface_descriptor interface_descriptor_t;  

PACKED_STRUCT_BEGIN
struct usb_endpoint_descriptor
{
   uint8_t   bLength;          /* Descriptor size in bytes = 7 */
   uint8_t   bDescriptorType;  /* ENDPOINT descriptor type = 5 */
   uint8_t   bEndpointAddress; /* Endpoint # 0 - 15 | IN/OUT */
   #define  IN_ENDPOINT    (0x80)   /* IN endpoint, device to host */
   #define  OUT_ENDPOINT   (0x00)   /* OUT endpoint, host to device */
   #define  ENDPOINT_MASK  (0x0F)   /* Mask endpoint # */
   uint8_t   bmAttributes;     /* Transfer type */
   #define  CONTROL_ENDPOINT  (0x00)   /* Control transfers */
   #define  ISOCH_ENDPOINT    (0x01)   /* Isochronous transfers */
   #define  BULK_ENDPOINT     (0x02)   /* Bulk transfers */
   #define  IRRPT_ENDPOINT    (0x03)   /* Interrupt transfers */
   #define  EP_TYPE_MASK      (0x03)   /* Mask type bits */
   /* Following must be zero except for isochronous endpoints */
   #define  ISOCH_NOSYNC      (0x00)   /* No synchronization */
   #define  ISOCH_ASYNC       (0x04)   /* Asynchronous */
   #define  ISOCH_ADAPT       (0x08)   /* Adaptive */
   #define  ISOCH_SYNCH       (0x0C)   /* Synchronous */
   #define  ISOCH_DATA        (0x00)   /* Data endpoint */
   #define  ISOCH_FEEDBACK    (0x10)   /* Feedback endpoint */
   #define  ISOCH_IMPLICIT    (0x20)   /* Implicit feedback */
   #define  ISOCH_RESERVED    (0x30)   /* Reserved */
   uint8_t   wMaxPacketSize[2];   /* Bits 10:0 = max. packet size */
   /* For high-speed interrupt or isochronous only, additional
   **   transaction opportunities per microframe follow.*/
   #define  PACKET_SIZE_MASK  (0x7FFu)  /* packet size bits */
   #define  NO_ADDITONAL      (0x0000)   /* 1 / microframe */
   #define  ONE_ADDITIONAL    (0x0800)   /* 2 / microframe */
   #define  TWO_ADDITIONAL    (0x1000)   /* 3 / microframe */
   #define  ADDITIONAL_MASK   (ONE_ADDITIONAL | TWO_ADDITIONAL)
   #define  ADDITIONAL_POWER  (11)   
   uint8_t   iInterval;        /* Polling interval in (micro) frames */
} PACKED_STRUCT_END;
typedef struct usb_endpoint_descriptor endpoint_descriptor_t;  

PACKED_STRUCT_BEGIN
struct usb_qualifier_descriptor
{
   uint8_t   bLength;          /* Descriptor size in bytes = 10 */
   uint8_t   bDescriptorType;  /* DEVICE QUALIFIER type = 6 */
   uint8_t   bcdUSD[2];        /* USB spec in BCD, e.g. 0x0200 */
   uint8_t   bDeviceClass;     /* Class code, if 0 see interface */
   uint8_t   bDeviceSubClass;  /* Sub-Class code, 0 if class = 0 */
   uint8_t   bDeviceProtocol;  /* Protocol, if 0 see interface */
   uint8_t   bMaxPacketSize;   /* Endpoint 0 max. size */
   uint8_t   bNumConfigurations; /* Number of possible configurations */
   uint8_t   bReserved;        /* Reserved = 0 */ 
} PACKED_STRUCT_END;
typedef struct usb_qualifier_descriptor qualifier_descriptor_t;  

/* Other-Config type 7 fields are identical to type 2 above */

/* Interface-Power descriptor  type 8 not used  in this version */

PACKED_STRUCT_BEGIN
struct usb_otg_descriptor
{
   uint8_t   bLength;          /* Descriptor size in bytes = 9 */
   uint8_t   bDescriptorType;  /* CONFIGURATION type = 2 or 7 */
   uint8_t   bmAttributes;     /* OTG characteristics */
   #define  OTG_SRP_SUPPORT   (0x01)  /* Supports SRP */
   #define  OTG_HNP_SUPPORT   (0x02)  /* Supports HNP */
} PACKED_STRUCT_END;
typedef struct usb_otg_descriptor otg_descriptor_t;  

PACKED_STRUCT_BEGIN
struct usb_common_descriptor
{
   uint8_t   bLength;          /* Descriptor size in bytes = 9 */
   uint8_t   bDescriptorType;  /* CONFIGURATION type = 2 or 7 */
} PACKED_STRUCT_END;
typedef struct usb_common_descriptor common_descriptor_t;


typedef union descriptor_union
{
   uint32_t                      word;
   uint8_t *                     bufr;
   void*                         pntr;
   device_descriptor_t         dvic;
   usb_configuration_descriptor_t*  cfig;
   interface_descriptor_t*      intf;
   endpoint_descriptor_t*       ndpt;
   qualifier_descriptor_t*      qual;
   otg_descriptor_t*            otg;
   common_descriptor_t*         common;
} descriptor_union_t;

#define USB_uint_16_low(x)          ((x) & 0xFF)
#define USB_uint_16_high(x)         ((uint8_t)((x) >> 8) & 0xFF)


/* Prototypes */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
