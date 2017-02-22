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
 * $FileName: usb_error.h$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 *   This file contains USB Device API defines for state and function
 *   returns.
 *
 *END************************************************************************/
#ifndef __usb_error_h__
#define __usb_error_h__ 1

/* Error codes */
#define USB_OK                              (0x00)
#define USBERR_ALLOC                        (0x81)
#define USBERR_BAD_STATUS                   (0x82)
#define USBERR_CLOSED_SERVICE               (0x83)
#define USBERR_OPEN_SERVICE                 (0x84)
#define USBERR_TRANSFER_IN_PROGRESS         (0x85)
#define USBERR_ENDPOINT_STALLED             (0x86)
#define USBERR_ALLOC_STATE                  (0x87)
#define USBERR_DRIVER_INSTALL_FAILED        (0x88)
#define USBERR_DRIVER_NOT_INSTALLED         (0x89)
#define USBERR_INSTALL_ISR                  (0x8A)
#define USBERR_INVALID_DEVICE_NUM           (0x8B)
#define USBERR_ALLOC_SERVICE                (0x8C)
#define USBERR_INIT_FAILED                  (0x8D)
#define USBERR_SHUTDOWN                     (0x8E)
#define USBERR_INVALID_PIPE_HANDLE          (0x8F)
#define USBERR_OPEN_PIPE_FAILED             (0x90)
#define USBERR_INIT_DATA                    (0x91)
#define USBERR_SRP_REQ_INVALID_STATE        (0x92)
#define USBERR_TX_FAILED                    (0x93)
#define USBERR_RX_FAILED                    (0x94)
#define USBERR_EP_INIT_FAILED               (0x95)
#define USBERR_EP_DEINIT_FAILED             (0x96)
#define USBERR_TR_FAILED                    (0x97)
#define USBERR_BANDWIDTH_ALLOC_FAILED       (0x98)
#define USBERR_INVALID_NUM_OF_ENDPOINTS     (0x99)
#define USBERR_ADDRESS_ALLOC_FAILED         (0x9A)
#define USBERR_PIPE_OPENED_FAILED           (0x9B)
#define USBERR_NOT_FOUND                    (0x9C)
#define USBERR_HOST_BUSY                    (0x9D)
#define USBERR_INVALID_PARAM                (0x9E)
#define USBERR_TR_RETRY_FAILED              (0x9F)

#define USBERR_DEVICE_NOT_FOUND             (0xC0)
#define USBERR_DEVICE_BUSY                  (0xC1)
#define USBERR_NO_DEVICE_CLASS              (0xC3)
#define USBERR_UNKNOWN_ERROR                (0xC4)
#define USBERR_INVALID_BMREQ_TYPE           (0xC5)
#define USBERR_GET_MEMORY_FAILED            (0xC6)
#define USBERR_BAD_ALIGNMENT                (0xC7)
#define USBERR_INVALID_MEM_TYPE             (0xC8)
#define USBERR_NO_DESCRIPTOR                (0xC9)
#define USBERR_NULL_CALLBACK                (0xCA)
#define USBERR_NO_INTERFACE                 (0xCB)
#define USBERR_INVALID_CFIG_NUM             (0xCC)
#define USBERR_INVALID_ANCHOR               (0xCD)
#define USBERR_INVALID_REQ_TYPE             (0xCE)
#define USBERR_DEVICE_DETACH                (0xCF)
#define USBERR_INTERFACE_NOT_OPENED         (0xD0)
#define USBERR_LACK_OF_SWAP_BUFFER          (0xD1)
#define USBERR_LEAK_OF_SWAP_BUFFER          (0xD2)

#define USBERR_ERROR                        (0xFF)

/* Error Codes for lower-layer */
#define USBERR_ALLOC_EP_QUEUE_HEAD          (0xA8)
#define USBERR_ALLOC_TR                     (0xA9)
#define USBERR_ALLOC_DTD_BASE               (0xAA)
#define USBERR_CLASS_DRIVER_INSTALL         (0xAB)
#define USBERR_TR_CANCEL                    (0xAC)

#endif
