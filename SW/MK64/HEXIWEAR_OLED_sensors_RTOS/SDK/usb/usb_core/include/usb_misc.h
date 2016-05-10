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
* $FileName: usb_misc.h$
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file contains USB Device API defines for state and function
*   returns.
*
*END************************************************************************/
#ifndef __usb_misc_h__
#define __usb_misc_h__ 1

/* Host specific */
#define USB_DEBOUNCE_DELAY                   (101)
#define USB_RESET_RECOVERY_DELAY             (11)
#define USB_RESET_DELAY                      (10)

/* USB device state- see USB 2.0 Documentation */
#define USB_STATE_UNKNOWN                    (0xff)
#define USB_STATE_PENDING_ADDRESS            (0x04) 
#define USB_STATE_POWERED                    (0x03)
#define USB_STATE_DEFAULT                    (0x02)
#define USB_STATE_ADDRESS                    (0x01)
#define USB_STATE_CONFIG                     (0x00)
#define USB_STATE_SUSPEND                    (0x80)

#define USB_STATUS_SELF_POWERED              (0x01)
#define USB_STATUS_REMOTE_WAKEUP             (0x02)

/* Bus Control values */
#define USB_NO_OPERATION                     (0x00)
#define USB_ASSERT_BUS_RESET                 (0x01)
#define USB_DEASSERT_BUS_RESET               (0x02)
#define USB_ASSERT_RESUME                    (0x03)
#define USB_DEASSERT_RESUME                  (0x04)
#define USB_SUSPEND_SOF                      (0x05)
#define USB_RESUME_SOF                       (0x06)

/* possible values of XD->bStatus */
#define USB_STATUS_IDLE                      (0)
#define USB_STATUS_STALLED                   (1) 
#define USB_STATUS_TRANSFER_PENDING          (2)
#define USB_STATUS_TRANSFER_IN_PROGRESS      (3)
#define USB_STATUS_ERROR                     (4)
#define USB_STATUS_DISABLED                  (5)
#define USB_STATUS_TRANSFER_ACCEPTED         (6)
#define USB_STATUS_TRANSFER_QUEUED           (7)
#define USB_STATUS_TRANSFER_DONE             (8)

#define USB_DEVICE_DONT_ZERO_TERMINATE       (0x1)

#define USB_SETUP_DATA_XFER_DIRECTION        (0x80)

/* Speed definitions */
#define USB_SPEED_FULL                       (0)
#define USB_SPEED_LOW                        (1)
#define USB_SPEED_HIGH                       (2)

#define USB_MAX_PKTS_PER_UFRAME              (0x6)

/* Event codes for attach/detach etc. callback */
#define  USB_ATTACH_EVENT                    (1)   /* device attach */
#define  USB_DETACH_EVENT                    (2)   /* device detach */
#define  USB_CONFIG_EVENT                    (3)   /* device reconfigured */
#define  USB_INTF_OPENED_EVENT               (4)   /* device interface opened */
#define  USB_ATTACH_INTF_NOT_SUPPORT         (5)   /* device attach while some interfaces not supported */
#define  USB_ATTACH_DEVICE_NOT_SUPPORT       (6)   /* device attach while all interfaces not supported */

/* Alignment of buffer for DMA transfer, needed in some cases,
** USB DMA bus could not possibly be initializes properly and
** first data transfered is the one aligned at 4-byte boundary
*/
#define USB_MEM4_ALIGN(n)               ((uint32_t)(n) + ((uint32_t)(-(n)) & 3U))
#define USB_DMA_ALIGN(n)                USB_MEM4_ALIGN(n)
#define USB_DMA_ALIGN_MASK              (0x03)
#define USB_SETUP_PKT_SIZE              (8)/* Setup Packet Size */
#define MAX_EXPECTED_CONTROL_OUT_SIZE   (76 + USB_SETUP_PKT_SIZE)

typedef struct xd_struct 
{
    uint8_t            ep_num;           /* Endpoint number */
    uint8_t            bdirection;       /* Direction : Send/Receive */
    uint8_t            ep_type;          /* Type of the endpoint: Ctrl, Isoch, Bulk, Int */
    uint8_t            bstatus;          /* Current transfer status */
    uint8_t *          wstartaddress;    /* Address of first byte */
    uint32_t           wtotallength;     /* number of bytes to send/recv */
    uint32_t           wsofar;           /* number of bytes recv'd so far */
    struct xd_struct*  next;
    uint16_t           wmaxpacketsize;   /* max packet size */   
    uint8_t            dont_zero_terminate;
#if (defined USBCFG_KHCI_4BYTE_ALIGN_FIX && USBCFG_KHCI_4BYTE_ALIGN_FIX)
    uint8_t               internal_dma_align;
#endif
    uint8_t            max_pkts_per_uframe;
} xd_struct_t;

typedef struct
{
    uint8_t*             name;
    uint8_t             instance;
} usb_instance_t;

#if (defined USBCFG_DEV_KHCI && USBCFG_DEV_KHCI) || (defined USBCFG_DEV_EHCI && USBCFG_DEV_EHCI)
typedef struct usb_dev_data
{
    uint8_t             control_out[(((MAX_EXPECTED_CONTROL_OUT_SIZE-1)/32) + 1) * 32];
                         /* control_out must be 32 byte align, 
                                        ** 96 = (((MAX_EXPECTED_CONTROL_OUT_SIZE-1)/32) + 1) * 32
                                        */
} usb_dev_data_t;
#endif

#if (defined USBCFG_DEV_KHCI && USBCFG_DEV_KHCI)
typedef struct usb_device_khci_data
{
    uint8_t             setup_packet[16];
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    uint8_t             reserver1[16];
#endif
#if USBCFG_KHCI_4BYTE_ALIGN_FIX
    uint8_t             swap_buf[USBCFG_DEV_KHCI_SWAP_BUF_MAX];
#endif
    uint8_t             xd_base[USBCFG_DEV_MAX_XDS * sizeof(xd_struct_t)];
}usb_device_khci_data_t;
#endif

#if (defined USBCFG_DEV_EHCI && USBCFG_DEV_EHCI)
typedef struct usb_device_ehci_data
{
    uint8_t             qh_base[USBCFG_DEV_EHCI_MAX_ENDPOINTS * 2 * 64];
    uint8_t             dtd_base[USBCFG_DEV_EHCI_MAX_DTD * 32];
    uint8_t             xd_base[USBCFG_DEV_MAX_XDS * sizeof(xd_struct_t)];
    uint8_t             reserved[688]; /* each ehci data should be 2048B aligned */
}usb_device_ehci_data_t;
#endif

typedef enum
{
    INTR_USBRST = 0x01,
    INTR_ERROR  = 0x02,
    INTR_SOFTOK = 0x04,
    INTR_TOKDNE = 0x08,
    INTR_SLEEP  = 0x10,
    INTR_RESUME = 0x20,
    INTR_ATTACH = 0x40,
    INTR_STALL  = 0x80, 
}INTR_TYPE;

typedef enum
{
    ERROR_PIDERR  = 0x01,
    ERROR_CRC5EOF = 0x02,
    ERROR_CRC16   = 0x04,
    ERROR_DFN8    = 0x08,
    ERROR_BTOERR  = 0x10,
    ERROR_DMAERR  = 0x20,
    ERROR_BTSERR  = 0x80,
}ERROR_TYPE;

typedef enum
{
    USB_CONTROLLER_KHCI_0 = 0x00,
    USB_CONTROLLER_KHCI_1,
    USB_CONTROLLER_EHCI_0,
    USB_CONTROLLER_EHCI_1
}CONTROLLER_INDEX;

#endif
