/**HEADER********************************************************************
 *
 * Copyright (c) 2009, 2013 Freescale Semiconductor;
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
 * $FileName: khci_interface.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 *
 *END************************************************************************/
#include "usb_device_config.h"
#if USBCFG_DEV_KHCI
//#include "types.h"
#include "adapter.h"
#include "adapter_cfg.h"
#include "usb_types.h" //USB error definitions
#include "compiler.h"
#include "usb_desc.h"  //USB descriptor macros
#include "usb_misc.h"
#include "adapter_types.h"
#include "khci_dev.h"
#include "usb_device_stack_interface.h"
#include "usb_dev.h"
#if defined(__cplusplus)
extern const usb_dev_interface_functions_struct_t _usb_khci_dev_function_table =
#else
const usb_dev_interface_functions_struct_t _usb_khci_dev_function_table =
#endif
{
    usb_dci_khci_preinit,
    usb_dci_khci_init,
    usb_dci_khci_postinit,
    usb_dci_khci_send,
    usb_dci_khci_recv,
#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE
    usb_dci_khci_cancel,
#endif
    usb_dci_khci_init_endpoint,
    usb_dci_khci_deinit_endpoint,
    usb_dci_khci_unstall_endpoint,
    usb_dci_khci_get_endpoint_status,
    usb_dci_khci_set_endpoint_status,
    NULL,
    usb_dci_khci_set_addr,
    usb_dci_khci_shutdown,
    NULL,
#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME
    usb_dci_khci_assert_resume,
#endif
    usb_dci_khci_stall_endpoint,
    usb_dci_khci_set_status,
    usb_dci_khci_get_status,
    usb_dci_khci_get_xd,
    usb_dci_khci_reset,
};
#endif
