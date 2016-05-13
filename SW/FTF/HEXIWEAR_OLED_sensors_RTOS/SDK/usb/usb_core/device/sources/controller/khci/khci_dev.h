/**HEADER********************************************************************
 *
 * Copyright (c) 2009, 2015 Freescale Semiconductor;
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
 * $FileName: khci_dev.h$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 *   This file contains the macros, function prototypes and data structure
 *   definitions required by the Full Speed USB Device Controller driver.
 *
 *END************************************************************************/

#ifndef __khci_dev_h__
#define __khci_dev_h__

#define KHCI_MAX_ENDPOINT             (16)

/***************************************
 **
 ** Prototypes
 **/
#ifdef __cplusplus
extern "C"
{
#endif

    usb_status usb_dci_khci_preinit(usb_device_handle upper_layer_handle, usb_device_handle *handle_ptr);
    usb_status usb_dci_khci_postinit(uint8_t controller_id, usb_device_handle handle);
    usb_status usb_dci_khci_init(uint8_t controller_id, usb_device_handle handle);
    usb_status usb_dci_khci_send(usb_device_handle handle, xd_struct_t* xd_ptr);
    usb_status usb_dci_khci_recv(usb_device_handle handle, xd_struct_t* xd_ptr);
    usb_status usb_dci_khci_cancel(usb_device_handle handle, uint8_t ep_num, uint8_t direction);
    usb_status usb_dci_khci_set_addr(usb_device_handle handle, uint8_t addr);
    usb_status usb_dci_khci_shutdown(usb_device_handle handle);
//usb_status usb_dci_khci_get_setup_data(usb_device_handle handle, uint8_t, uint8_t *);
#if ((defined USBCFG_DEV_ADVANCED_SUSPEND_RESUME) && (USBCFG_DEV_ADVANCED_SUSPEND_RESUME))
    usb_status usb_dci_khci_assert_resume(usb_device_handle handle);
#endif
    usb_status usb_dci_khci_init_endpoint(usb_device_handle handle, xd_struct_t* xd_ptr);
    usb_status usb_dci_khci_stall_endpoint(usb_device_handle handle, uint8_t ep_num, uint8_t direction);
    usb_status usb_dci_khci_unstall_endpoint(usb_device_handle handle, uint8_t ep_num, uint8_t direction);
    usb_status usb_dci_khci_deinit_endpoint(usb_device_handle handle, uint8_t ep_num, uint8_t direction);
    usb_status usb_dci_khci_get_endpoint_status(usb_device_handle handle, uint8_t component, uint16_t *endp_status);
    usb_status usb_dci_khci_set_endpoint_status(usb_device_handle handle, uint8_t component, uint16_t setting);
//usb_status usb_dci_khci_get_transfer_status(usb_device_handle handle,uint8_t,uint8_t);
    usb_status usb_dci_khci_get_status(usb_device_handle handle, uint8_t component, uint16_t *error);
    usb_status usb_dci_khci_set_status(usb_device_handle handle, uint8_t component, uint16_t setting);
    usb_status usb_dci_khci_get_xd(usb_device_handle handle, xd_struct_t** xd_ptr_ptr);
    usb_status usb_dci_khci_reset(usb_device_handle handle);

#ifdef __cplusplus
}
#endif

#endif
