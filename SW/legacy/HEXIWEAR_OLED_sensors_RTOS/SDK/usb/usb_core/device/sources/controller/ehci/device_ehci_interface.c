/**HEADER********************************************************************
 * 
 * Copyright (c) 2008, 2013 - 2014 Freescale Semiconductor;
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
 * $FileName: ehci_interface.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 *
 *END************************************************************************/

#include "usb_device_config.h"
#if USBCFG_DEV_EHCI
//#include "types.h"
#include "adapter.h"
#include "usb_types.h" //USB error definitions
#include "compiler.h"
#include "usb_desc.h"  //USB descriptor macros
#include "usb_misc.h"
#include "adapter_types.h"
#include "usb_device_stack_interface.h"
#include "usb_dev.h"
#include "ehci_dev_main.h"
#include "ehci_usbprv.h"
#if defined(__cplusplus)
extern const usb_dev_interface_functions_struct_t _usb_ehci_dev_function_table =
#else
const usb_dev_interface_functions_struct_t _usb_ehci_dev_function_table =
#endif
{
    usb_dci_usbhs_preinit,
    usb_dci_usbhs_init,
    NULL,
    usb_dci_usbhs_send_data,
    usb_dci_usbhs_recv_data,
#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE  
    usb_dci_usbhs_cancel_transfer,
#endif
    usb_dci_usbhs_init_endpoint,
    usb_dci_usbhs_deinit_endpoint,
    usb_dci_usbhs_unstall_endpoint,
    usb_dci_usbhs_get_endpoint_status,
    usb_dci_usbhs_set_endpoint_status,
    usb_dci_usbhs_get_transfer_status,
    usb_dci_usbhs_set_address,
    usb_dci_usbhs_shutdown,
    usb_dci_usbhs_get_setup_data,
#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME
    usb_dci_usbhs_assert_resume,
#endif
    usb_dci_usbhs_stall_endpoint,
    usb_dci_usbhs_set_status,
    usb_dci_usbhs_get_status,
    usb_dci_usbhs_alloc_xd,
    NULL,
};
#endif
