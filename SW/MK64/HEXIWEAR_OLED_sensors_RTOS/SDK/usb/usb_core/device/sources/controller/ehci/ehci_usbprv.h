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
 * $FileName: ehci_usbprv.h$
 * $Version : 3.8.4.0$
 * $Date    : Jun-7-2012$
 *
 * Comments:
 *
 *  This file contains the private defines, externs and
 *  data structure definitions required by the VUSB_HS Device
 *  driver.
 *                                                               
 *END*********************************************************************/

#ifndef __ehci_dev_usbprv_h__
#define __ehci_dev_usbprv_h__ 1

#include "usb_ehci.h"

//#define  MAX_EP_TR_DESCRS                    (32) 
//#define  MAX_XDS_FOR_TR_CALLS                (32) 
#define  ZERO_LENGTH                         (0) 
//#define  USB_MAX_ENDPOINTS                   (4) 
#define  SETUP_PACKET_LENGTH                 (8)
#define  USB_MAX_CTRL_PAYLOAD                (64)

///* Macro for aligning the EP queue head to 32 byte boundary */
//#define USB_MEM32_ALIGN(n)                   ((n) + (-(n) & 31))
//
///* Macro for aligning the EP queue head to 1024 byte boundary */
//#define USB_MEM1024_ALIGN(n)                 ((n) + (-(n) & 1023))
//
///* Macro for aligning the EP queue head to 1024 byte boundary */
//#define USB_MEM2048_ALIGN(n)                 ((n) + (-(n) & 2047))

//#define EHCI_DTD_QADD(head,tail,dTD)      \//
//   if ((head) == NULL) {         \//
//      (head) = (dTD);            \//
//   } else {                      \//
//      (tail)->private = (void *) (dTD);   \//
//   } /* Endif */                 \//
//   (tail) = (dTD);               \//
//   (dTD)->private = NULL
//   
//#define EHCI_DTD_QGET(head,tail,dTD)      \//
//   (dTD) = (head);               \//
//   if (head) {                   \//
//      (head) = (head)->private;  \//
//      if ((head) == NULL) {      \//
//         (tail) = NULL;          \//
//      } /* Endif */              \//
//   } /* Endif */
//

/***************************************
 **
 ** Data structures
 **
 */

/* The USB Device State Structure */
typedef struct _usb_ehci_device_state_struct
{
    uint32_t controller_id; /* Device controller ID */
    uint32_t usbRegBase;
    usb_device_handle upper_layer_handle;
    void* dev_ptr; /* Device Controller Register base address */
    //SCRATCH_STRUCT_PTR    xd_scratch_struct_base;
    //SCRATCH_STRUCT_PTR    scratch_struct_base;
    struct xd_struct* xd_base;
    struct xd_struct* xd_head; /* Head Transaction descriptors */
    struct xd_struct* xd_tail; /* Tail Transaction descriptors */
    uint32_t xd_entries; /* Device Controller Register base address */
    void* cap_base_ptr;
    //void*                 DEV_PTR;
    usb_ehc_dev_qh_struct_t * qh_base_ptr; /* Endpoint Queue head */
    //uint8_t *                        DRIVER_MEMORY;       /* pointer to driver memory*/
    //uint32_t                         TOTAL_MEMORY;        /* total memory occupied by driver */
    //usb_ehc_dev_qh_struct_t *   EP_QUEUE_HEAD_BASE;
    //usb_ehci_dev_dtd_struct_t *           DTD_BASE_PTR;         /* Device transfer descriptor pool address */
    usb_ehci_dev_dtd_struct_t * dtd_base_ptr; /* Aligned transfer descriptor pool address */
    usb_ehci_dev_dtd_struct_t * dtd_head;
    usb_ehci_dev_dtd_struct_t * dtd_tail;
    usb_ehci_dev_dtd_struct_t * dtd_heads[USBCFG_DEV_EHCI_MAX_ENDPOINTS * 2];
    usb_ehci_dev_dtd_struct_t * dtd_tails[USBCFG_DEV_EHCI_MAX_ENDPOINTS * 2];
    uint16_t dtd_entries;
    uint16_t usb_state;
    uint16_t usb_device_status;
    uint16_t usb_sof_count;
    uint16_t errors;
    uint16_t usb_dev_state_b4_suspend;
    uint16_t usb_curr_config;
    uint8_t in_test_mode; /* Device is in test mode ? */
    uint8_t bus_resetting; /* Device is being reset */
    //uint8_t               TRANSFER_PENDING;    /* Transfer pending ? */
    uint8_t dev_vec; /* Interrupt vector number for USB OTG */
    uint8_t speed; /* Low Speed, High Speed, Full Speed */
    uint8_t max_endpoints; /* Max endpoints supported by this device */
    uint8_t device_address;
    uint8_t setup_buff[SETUP_PACKET_LENGTH];
} usb_ehci_dev_state_struct_t;




/***************************************
 **
 ** Prototypes
 **
 */
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#endif
