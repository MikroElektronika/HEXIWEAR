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
* $FileName: usb_dev.h$
* $Version : 
* $Date    : 
*
* Comments:
*
*  This file contains the declarations specific to the USB Device API
*
*END*********************************************************************/
#ifndef __USB_DEV_H__
#define __USB_DEV_H__ 1

#include "usb_framework.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM)

#undef USBCFG_DEV_USE_TASK
#define USBCFG_DEV_USE_TASK 0

#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)

#undef USBCFG_DEV_USE_TASK
#define USBCFG_DEV_USE_TASK 1

#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
#if USE_RTOS
#define USBCFG_DEV_USE_TASK 1
#else
#define USBCFG_DEV_USE_TASK 0
#endif

#endif
#define MAX_DEVICE_SERVICE_NUMBER     8

/* Callback function storage structure */
typedef struct service_struct 
{
   usb_event_service_t              service;
   void*                            arg;
   uint8_t                          type;
} service_struct_t;

typedef struct usb_dev_interface_functions_struct
{
   /* The Host/Device init function */
   usb_status (_CODE_PTR_ dev_preint)(usb_device_handle upper_layer_handle, usb_device_handle *handle_ptr);

   /* The Host/Device init function */
   usb_status (_CODE_PTR_ dev_init)(uint8_t controller_id, usb_device_handle handle);
   
   /* The Host/Device init function */
   usb_status (_CODE_PTR_ dev_postinit)( uint8_t controller_id, usb_device_handle handle);

   /* The function to send data */
   usb_status (_CODE_PTR_ dev_send)(usb_device_handle handle, xd_struct_t* xd);

   /* The function to receive data */
   usb_status (_CODE_PTR_ dev_recv)(usb_device_handle handle, xd_struct_t* xd);
#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE   
   /* The function to cancel the transfer */
   usb_status (_CODE_PTR_ dev_cancel_transfer)(usb_device_handle handle, uint8_t ep_num, uint8_t direction);
#endif
   
   usb_status (_CODE_PTR_ dev_init_endoint)(usb_device_handle handle, xd_struct_t* xd);
   
   usb_status (_CODE_PTR_ dev_deinit_endoint)(usb_device_handle handle, uint8_t ep_num, uint8_t direction);
   
   usb_status (_CODE_PTR_ dev_unstall_endpoint)(usb_device_handle handle, uint8_t ep_num, uint8_t direction);
   
   usb_status (_CODE_PTR_ dev_get_endpoint_status)(usb_device_handle handle, uint8_t component, uint16_t *endp_status);
   
   usb_status (_CODE_PTR_ dev_set_endpoint_status)(usb_device_handle handle, uint8_t component, uint16_t endp_status);

   usb_status (_CODE_PTR_ dev_get_transfer_status)(usb_device_handle handle, uint8_t component, uint8_t status);
   
   usb_status (_CODE_PTR_ dev_set_address)(usb_device_handle handle, uint8_t addr);
   
   usb_status (_CODE_PTR_ dev_shutdown)(usb_device_handle handle);
   
   usb_status (_CODE_PTR_ dev_get_setup_data)(usb_device_handle handle, uint8_t component, uint8_t *data);
#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME  
   usb_status (_CODE_PTR_ dev_assert_resume)(usb_device_handle handle);
#endif
   
   usb_status (_CODE_PTR_ dev_stall_endpoint)(usb_device_handle handle, uint8_t ep_num, uint8_t direction);
   
   usb_status (_CODE_PTR_ dev_set_device_status)(usb_device_handle handle, uint8_t component, uint16_t setting);
   
   usb_status (_CODE_PTR_ dev_get_device_status)(usb_device_handle handle, uint8_t component, uint16_t *error);

   usb_status (_CODE_PTR_ dev_get_xd)(usb_device_handle handle, xd_struct_t** xd);

   usb_status (_CODE_PTR_ dev_reset)(usb_device_handle handle);
} usb_dev_interface_functions_struct_t;

typedef struct usb_dev_state_struct
{
    usb_device_handle               controller_handle;
    const usb_dev_interface_functions_struct_t* usb_dev_interface;
#if USBCFG_DEV_USE_TASK
    os_msgq_handle                  usb_dev_service_que;
    uint32_t                        task_id;
#endif
    usb_class_fw_object_struct_t    usb_framework;
    service_struct_t                services[MAX_DEVICE_SERVICE_NUMBER];
    os_mutex_handle                 mutex;
    uint8_t                         occupied;
    uint8_t                         controller_id;       /* Device controller ID */
    uint8_t                         dev_index;
} usb_dev_state_struct_t;

#endif
/* EOF */
