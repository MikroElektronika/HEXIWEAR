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
 * $FileName: usb_types.h$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 *   This file contains appropriate processor specific header file include.
 *
 *END************************************************************************/
#ifndef __usb_types_h__
#define __usb_types_h__

/*--------------------------------------------------------------------------*/
/*
 **                            STANDARD TYPES
 */

typedef uint32_t usb_status;
/* forward declarations */
struct usb_interface_descriptor;
struct pipe_struct;
struct tr_struct;

typedef void* usb_device_handle; /* device state struct */
typedef void* usb_host_handle; /* host state struct   */
typedef void* usb_otg_handle; /* otg state struct   */

typedef void* usb_device_instance_handle; /* item on host's list */
typedef void* usb_interface_descriptor_handle; /* Chapter 9 interface descriptor */
typedef void* usb_pipe_handle; /* pipe or pipe-bundle */
typedef void* usb_class_intf_handle; /* interface state struct (general data + class driver specific data) */

#define UNUSED_ARGUMENT(x)   (void)x;

#endif
