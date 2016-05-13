/**HEADER********************************************************************
*
* Copyright (c) 2009, 2013 - 2014 Freescale Semiconductor;
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
* $FileName: khci_dev_misc.h$
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file contains the private defines, externs and data structure
*   definitions required by the Full Speed USB Device driver.
*
*END************************************************************************/

#ifndef __khci_dev_misc_h__
#define __khci_dev_misc_h__ 1 

#define EP_DISABLE                      (0)
#define ASSERT_RESUME_DELAY_COUNT       (8000)/* Delay for assert resume */
#define BYTES_512                       (512)
#define BYTES_1024                      (1024)
#define ENDPOINT_NUMBER_SHIFT           (4)   /* endpoint shift & mask to */
#define ENDPOINT_NUMBER_MASK            (0xf0)/* use in setting and getting status */
#define MAX_FS_NON_ISO_EP_BUFFER_SIZE   (64)
#define MAX_FS_ISO_EP_BUFFER_SIZE       (1023)
#define SETUP_PACKET_LENGTH             (8)
#define COMPONENT_PREPARE_SHIFT         (7)

#define ZERO_LENGTH                     (0)
#define USB_SETUP_TOKEN                 (0x0d)/* Setup Token PID */
#define FRAME_HIGH_BYTE_SHIFT           (8)

#define MAX_USB_DEVICES                 (1)
#define ODD_BUFF                        (1)
#define EVEN_BUFF                       (0)

/* Define USB buffer descriptor definitions in case of their lack */
#ifndef USB_BD_BC
#   define USB_BD_BC(n)                 (((uint32_t)n & 0x3ff) << 16)
#   define USB_BD_OWN                   0x80
#   define USB_BD_DATA01(n)             (((uint32_t)n & 1) << 6)
#   define USB_BD_DATA0                 USB_BD_DATA01(0)
#   define USB_BD_DATA1                 USB_BD_DATA01(1)
#   define USB_BD_KEEP                  0x20
#   define USB_BD_NINC                  0x10
#   define USB_BD_DTS                   0x08
#   define USB_BD_STALL                 0x04
#   define USB_BD_PID(n)                (((uint32_t)n & 0x0f) << 2)
#endif

#ifndef USB_TOKEN_TOKENPID_SETUP
#   define USB_TOKEN_TOKENPID_OUT                   USB_TOKEN_TOKENPID(0x1)
#   define USB_TOKEN_TOKENPID_IN                    USB_TOKEN_TOKENPID(0x9)
#   define USB_TOKEN_TOKENPID_SETUP                 USB_TOKEN_TOKENPID(0xD)
#endif

typedef struct _usb_ep_info_struct
{
    //USB_XD_QUEUE         xd_queue_send;  /* FIFO queue for all XDs on this endpoint */   
    //USB_XD_QUEUE         xd_queue_recv;
    struct xd_struct*    send_xd;
    struct xd_struct*    recv_xd;
    uint16_t             max_packet_size;
    uint8_t              endpoint_status;
    uint8_t              stall_flag;
    /* Endpoint initialization flag for both direction */
    uint8_t              ep_init_flag[2];
    uint8_t              type;
    uint8_t              direction; /* for usb_device_call_service */
    uint8_t              tx_data0;
    uint8_t              rx_data0;
    uint8_t              tx_buf_odd;
    uint8_t              rx_buf_odd;   /* next buffer is odd */
} usb_ep_info_struct_t;

/* The USB Device State Structure */
typedef struct _usb_khci_device_state_struct 
{
    uint32_t              controller_id;       /* Device controller ID */
    usb_device_handle     upper_layer_handle;
    void*                 dev_ptr;             /* Device Controller Register base address */
    struct xd_struct*     xd_base;
    struct xd_struct*     xd_head;             /* Head Transaction descriptors */
    struct xd_struct*     xd_tail;             /* Tail Transaction descriptors */
    uint32_t              xd_entries;
    os_mutex_handle       mutex;
    uint32_t              usbRegBase;

    /* These fields are kept only for USB_shutdown() */
    uint16_t              usb_state;
    uint16_t              usb_device_status;
    uint16_t              usb_sof_count;
    uint16_t              errors;
    uint16_t              usb_dev_state_b4_suspend;
    uint16_t              usb_curr_config;
    uint8_t               dev_vec;             /* Interrupt vector number for USB OTG */
    uint8_t               speed;               /* Low Speed, High Speed, Full Speed */
    uint8_t               max_endpoints;       /* Max endpoints supported by this device */
    uint8_t               device_address;                                     
    uint8_t *             setup_buff;
    usb_ep_info_struct_t  ep_info[USBCFG_DEV_MAX_ENDPOINTS];
#ifdef USBCFG_OTG
    uint16_t              usb_otg_status;
    usb_otg_handle        otg_handle; 
    uint8_t               otg_attr_srp;
    uint8_t               otg_attr_hnp;
#endif
    uint8_t               is_reseting;
} usb_khci_dev_state_struct_t;

/***************************************
**
** Prototypes
**
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
