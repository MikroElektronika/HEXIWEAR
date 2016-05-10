/**HEADER********************************************************************
 * 
 * Copyright (c) 2004 -2010, 2013 - 2014 Freescale Semiconductor;
 * All Rights Reserved
 *
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
 * @file usb_composite.c
 *
 * @author
 *
 * @version
 *
 * @date 
 *
 * @brief The file contains USB composite layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"

#include "usb_device_stack_interface.h"
#include "usb_class_composite.h"
#include "usb_composite.h"
#include "usb_class_internal.h"

#if USBCFG_DEV_COMPOSITE
#if USBCFG_DEV_HID
#include "usb_hid_config.h"
#include "usb_class_hid.h"
#include "usb_hid.h"
#endif

#if USBCFG_DEV_MSC
#include "usb_msc_config.h"
#include "usb_class_msc.h"
#include "usb_msc.h"
#endif

#if ((defined USBCFG_DEV_AUDIO) && USBCFG_DEV_AUDIO)
#include "usb_audio_config.h"
#include "usb_class_audio.h"
#include "usb_audio.h"
#endif

#if ((defined USBCFG_DEV_VIDEO) && (USBCFG_DEV_VIDEO))
#include "usb_video_config.h"
#include "usb_class_video.h"
#include "usb_video.h"
#endif

#if USBCFG_DEV_PHDC
#include "usb_phdc_config.h"
#include "usb_class_phdc.h"
#include "usb_phdc.h"
#endif

#if USBCFG_DEV_CDC
#include "usb_cdc_config.h"
#include "usb_class_cdc.h"
#include "usb_cdc.h"
#endif

#if ((defined USBCFG_DEV_DFU) && USBCFG_DEV_DFU)
#include "usb_dfu.h"
#endif
/*****************************************************************************
 * Local variables
 *****************************************************************************/ 
static composite_device_struct_t s_composite_device_struct = {0};
static class_config_struct_t     s_composite_config_struct[CONFIG_MAX];
static usb_composite_info_struct_t s_usb_composite_info_struct = {0};

/*****************************************************************************
 * Local functions prototypes
 *****************************************************************************/
void USB_Composite_Event (uint8_t event, void* val,void * arg);

usb_status USB_Composite_Requests (
usb_setup_struct_t * setup_packet, /* [IN] Setup packet received */
uint8_t * *data,
uint32_t *size,
void* arg );

/*****************************************************************************
 * Global functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Composite_Init
 *
 * @brief   The function initializes the Device and Controller layer
 *
 * @param   controller_id               : Controller ID
 * @param   composite_callback_ptr      : Pointer to app callback  
 *
 * @return status:
 *                        USB_OK        : When Successfully
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function initializes the Composite layer
 *****************************************************************************/
usb_status USB_Composite_Init(
uint8_t controller_id, /* [IN] Controller ID */
composite_config_struct_t *composite_callback_ptr, /* [IN] Pointer to class info */
composite_handle_t * compositeHandle
)
{
    uint8_t count;
    usb_status status = USB_OK;
    composite_device_struct_t *devicePtr;
    usb_composite_info_struct_t *usb_composite_info;

    if (NULL == composite_callback_ptr)
    {
        return USBERR_ERROR;
    }
    devicePtr = &s_composite_device_struct;
    if (NULL == devicePtr)
    {
#if _DEBUG
        USB_PRINTF("USB_Class_COMPOSITE_Init: Memalloc devicePtr failed\n");
#endif  
        return USBERR_ALLOC;
    }
    devicePtr->cl_count = composite_callback_ptr->count;
    devicePtr->class_app_callback = s_composite_config_struct;
    if (NULL == devicePtr->class_app_callback)
    {
#if _DEBUG
        USB_PRINTF("USB_Class_COMPOSITE_Init: Memalloc class_app_callback failed\n");
#endif  
        //OS_Mem_free(devicePtr);  
        return USBERR_ALLOC;
    }

    OS_Mem_copy(composite_callback_ptr->class_app_callback,
    devicePtr->class_app_callback,devicePtr->cl_count*sizeof(class_config_struct_t));

    devicePtr->class_composite_info = &s_usb_composite_info_struct;
    if (NULL == devicePtr->class_composite_info)
    {
#if _DEBUG
        USB_PRINTF("USB_Class_COMPOSITE_Init: Memalloc class_composite_info failed\n");
#endif  
        //OS_Mem_free(devicePtr->class_app_callback);
        //OS_Mem_free(devicePtr);
        return USBERR_ALLOC;
    }

    //status = usb_device_preinit(controller_id,&devicePtr->handle);

    status = usb_device_init(controller_id,&devicePtr->handle);
    devicePtr->class_app_callback->desc_callback_ptr->get_desc_entity((uint32_t)devicePtr->handle,
    USB_COMPOSITE_INFO,
    (uint32_t *)&usb_composite_info);
    OS_Mem_copy(usb_composite_info,
    devicePtr->class_composite_info , sizeof(usb_composite_info_struct_t));
    if(status == USB_OK)
    {
        /* Initialize the generic class functions */
        //class_handle = 
        devicePtr->class_handle = USB_Class_Init(devicePtr->handle,USB_Composite_Event, USB_Composite_Requests,(void *)devicePtr,
        composite_callback_ptr->class_app_callback[0].desc_callback_ptr);

        if(status == USB_OK)
        {
            for(count = 0; count < devicePtr->cl_count; count++)
            {
                /* Initializes sub_classes */
                switch(composite_callback_ptr->class_app_callback[count].type)
                {
#if USBCFG_DEV_HID 
                case USB_CLASS_HID:
                    (void)USB_Class_HID_Init(
                    controller_id,(struct hid_config_struct *)&devicePtr->class_app_callback[count],
                    &devicePtr->class_app_callback[count].class_handle);
                    composite_callback_ptr->class_app_callback[count].class_handle = devicePtr->class_app_callback[count].class_handle;
                    break;
#endif
#if USBCFG_DEV_AUDIO
                case USB_CLASS_AUDIO:
                    (void)USB_Class_Audio_Init(
                    controller_id,(struct audio_config_struct *)&devicePtr->class_app_callback[count],
                    &devicePtr->class_app_callback[count].class_handle);
                    composite_callback_ptr->class_app_callback[count].class_handle = devicePtr->class_app_callback[count].class_handle;
                    break;
#endif

#if USBCFG_DEV_CDC
                case USB_CLASS_CDC:
                    (void)USB_Class_CDC_Init(
                    controller_id, (cdc_config_struct_t *)&devicePtr->class_app_callback[count],
                    &devicePtr->class_app_callback[count].class_handle);
                    composite_callback_ptr->class_app_callback[count].class_handle = devicePtr->class_app_callback[count].class_handle;
                    break;
#endif
#if USBCFG_DEV_MSC
                case USB_CLASS_MSC:
                    (void)USB_Class_MSC_Init(
                    controller_id, (msc_config_struct_t*)&devicePtr->class_app_callback[count],
                    &devicePtr->class_app_callback[count].class_handle);
                    composite_callback_ptr->class_app_callback[count].class_handle = devicePtr->class_app_callback[count].class_handle;
                    break;
#endif
#if USBCFG_DEV_PHDC
                case USB_CLASS_PHDC:
                    (void)USB_Class_PHDC_Init(
                    controller_id,(phdc_config_struct_t*)&devicePtr->class_app_callback[count],
                    &devicePtr->class_app_callback[count].class_handle);
                    composite_callback_ptr->class_app_callback[count].class_handle = devicePtr->class_app_callback[count].class_handle;
                    break;
#endif
#if ((defined USBCFG_DEV_DFU) && (USBCFG_DEV_DFU))
                case DFU_COMP_CC:
                    (void)USB_Class_Dfu_Init(
                    controller_id,(dfu_config_struct_t*)&devicePtr->class_app_callback[count],
                    &devicePtr->class_app_callback[count].class_handle);
                    composite_callback_ptr->class_app_callback[count].class_handle = devicePtr->class_app_callback[count].class_handle;
                    break;
#endif
                default:
                    break;
                }
            }
        }
    }

    /* Initialize the device layer*/
    *compositeHandle = (composite_handle_t)devicePtr;

    status = usb_device_postinit(controller_id,devicePtr->handle);
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Composite_DeInit
 *
 * @brief   The function De-initializes the Device and Controller layer
 *
 * @param   controller_id               : Controller ID
 * @param   composite_callback_ptr      : Pointer to app callback  
 *
 * @return status:
 *                        USB_OK        : When Successfully
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function De-initializes the Composite layer
 *****************************************************************************/
usb_status USB_Composite_DeInit(
composite_handle_t handle /* [IN] Controller ID */
)
{
    composite_device_struct_t *devicePtr;
    uint8_t count;
    usb_status status = USB_OK;
    if (handle == 0)
    {
        return USBERR_ERROR;
    }

    devicePtr = (composite_device_struct_t *)handle;

    if (NULL == devicePtr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }

    for(count = 0; count < devicePtr->cl_count; count++)
    {

        switch(devicePtr->class_app_callback[count].type)
        {
#if USBCFG_DEV_HID
        case USB_CLASS_HID:
            //status = 
            USB_Class_HID_Deinit(devicePtr->class_app_callback[count].class_handle);
            break;
#endif
#if USBCFG_DEV_AUDIO   
        case USB_CLASS_AUDIO:
            //status = 
            USB_Class_Audio_Deinit(devicePtr->class_app_callback[count].class_handle);
            break;
#endif
#if USBCFG_DEV_CDC
        case USB_CLASS_CDC:
            //status = 
            USB_Class_CDC_Deinit(devicePtr->class_app_callback[count].class_handle);
            break;
#endif
#if USBCFG_DEV_MSC
            case USB_CLASS_MSC:
            //status = 
            USB_Class_MSC_Deinit(devicePtr->class_app_callback[count].class_handle);
            break;
#endif
#if USBCFG_DEV_PHDC
            case USB_CLASS_PHDC:
            //status = 
            USB_Class_PHDC_Deinit(devicePtr->class_app_callback[count].class_handle);
            break;
#endif
            default:
            break;
        }
    }

    if(status == USB_OK)
    {
        /* De-initialize the generic class functions */
        status = USB_Class_Deinit(devicePtr->handle,devicePtr->class_handle);
    }
    if(status == USB_OK)
    {
        /* De-initialize the device layer*/
        status = usb_device_deinit(devicePtr->handle);
    }

    //OS_Mem_free(devicePtr->class_app_callback);
    //OS_Mem_free(devicePtr->class_composite_info);
    //OS_Mem_free(devicePtr);
    devicePtr = NULL;

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Composite_Event
 *
 * @brief The function initializes composite endpoint
 *
 * @param controller_id     : Controller ID
 * @param event             : Event Type
 * @param val               : Pointer to configuration Value
 *
 * @return None
 *
 ******************************************************************************
 * 
 *****************************************************************************/
void USB_Composite_Event (uint8_t event, void* val,void * arg)
{
    uint8_t count;
    composite_device_struct_t *devicePtr;

    devicePtr = (composite_device_struct_t *)arg;

    if (NULL == devicePtr)
    {
        return;
    }

    for(count = 0; count < devicePtr->cl_count; count++)
    {
        switch(devicePtr->class_app_callback[count].type)
        {
#if USBCFG_DEV_HID
        case USB_CLASS_HID:
            USB_Class_Hid_Event(event,val,(void *)devicePtr->class_app_callback[count].class_handle);
            break;
#endif
#if USBCFG_DEV_AUDIO    
        case USB_CLASS_AUDIO:
            USB_Class_Audio_Event(event,val,(void *)devicePtr->class_app_callback[count].class_handle);
            break;
#endif
#if USBCFG_DEV_CDC
        case USB_CLASS_CDC:
            USB_Class_CDC_Event(event,val,(void *)devicePtr->class_app_callback[count].class_handle);
            break;
#endif
#if USBCFG_DEV_MSC
        case USB_CLASS_MSC:
            USB_Class_MSC_Event(event,val,(void *)devicePtr->class_app_callback[count].class_handle);
            break;
#endif
#if USBCFG_DEV_PHDC
        case USB_CLASS_PHDC:
            USB_Class_PHDC_Event(event,val,(void *)devicePtr->class_app_callback[count].class_handle);
            break;
#endif
        default:
            break;
        }
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Composite_Other_Requests
 *
 * @brief   The function provides flexibility to add class and vendor specific
 *              requests
 *
 * @param controller_id     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successfully
 *                        Others        : When Error
 *
 ******************************************************************************
 * Handles Class requests and forwards vendor specific request to the
 * application
 *****************************************************************************/
usb_status USB_Composite_Requests (
usb_setup_struct_t * setup_packet, /* [IN] Setup packet received */
uint8_t * *data,
uint32_t *size,
void* arg)
{
    uint8_t count;
    usb_status status = USB_OK;
    composite_device_struct_t *devicePtr;
    uint8_t itf_num = 0xFF;
    uint8_t type_sel;

    devicePtr = (composite_device_struct_t *)arg;

    if (NULL == devicePtr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }

    if(setup_packet->request_type & 0x01)
    {
        itf_num = (setup_packet->index);
    }

    for(count = 0; count < devicePtr->cl_count; count++)
    {
        switch(devicePtr->class_app_callback[count].type)
        {
#if USBCFG_DEV_HID
            /* Call Hid other request */
        case USB_CLASS_HID:
            for (type_sel = 0;type_sel < devicePtr->class_composite_info->count;type_sel++)
            {
                if (devicePtr->class_composite_info->class_handle[type_sel].type == USB_CLASS_HID)
                {
                    if (itf_num == devicePtr->class_composite_info->class_handle[type_sel].interfaces.interface->index)
                    {
                        status = USB_HID_Requests(setup_packet,data,size,(void *)devicePtr->class_app_callback[count].class_handle);
                    }
                }
            }
            break;
#endif
#if USBCFG_DEV_AUDIO  
            /* Call Audio other request */
        case USB_CLASS_AUDIO:
            for(type_sel = 0;type_sel < devicePtr->class_composite_info->count;type_sel++)
            {
                if(devicePtr->class_composite_info->class_handle[type_sel].type == USB_CLASS_AUDIO)
                {
                    if (itf_num == devicePtr->class_composite_info->class_handle[type_sel].interfaces.interface->index)
                    {
                        status = USB_Audio_Requests(setup_packet,data,size,(void *)devicePtr->class_app_callback[count].class_handle);
                    }
                }
            }
            break;
#endif
#if USBCFG_DEV_CDC  
            /* Call Cdc other request */
        case USB_CLASS_CDC:
            for (type_sel = 0;type_sel < devicePtr->class_composite_info->count;type_sel++)
            {
                if (devicePtr->class_composite_info->class_handle[type_sel].type == USB_CLASS_CDC)
                {
                    if (itf_num == devicePtr->class_composite_info->class_handle[type_sel].interfaces.interface->index)
                    {
                        status = USB_CDC_Other_Requests(setup_packet,data,size,(void *)devicePtr->class_app_callback[count].class_handle);
                    }
                }
            }
            break;
#endif
#if USBCFG_DEV_MSC
            /* Call Msd other request */
        case USB_CLASS_MSC:
            for (type_sel = 0;type_sel < devicePtr->class_composite_info->count;type_sel++)
            {
                if (devicePtr->class_composite_info->class_handle[type_sel].type == USB_CLASS_MSC)
                {
                    if (itf_num == devicePtr->class_composite_info->class_handle[type_sel].interfaces.interface->index)
                    {
                        status = USB_MSC_Requests(setup_packet,data,size,(void *)devicePtr->class_app_callback[count].class_handle);
                    }
                }
            }
            break;
#endif
#if USBCFG_DEV_PHDC
            /* Call Phdc other request */
        case USB_CLASS_PHDC:
            for(type_sel = 0;type_sel < devicePtr->class_composite_info->count;type_sel++)
            {
                if(devicePtr->class_composite_info->class_handle[type_sel].type == USB_CLASS_PHDC)
                {
                    if (itf_num == devicePtr->class_composite_info->class_handle[type_sel].interfaces.interface->index)
                    {
                        status = USB_PHDC_Requests(setup_packet,data,size,(void *)devicePtr->class_app_callback[count].class_handle);
                    }
                }
            }
            break;
#endif
        default:
            break;
        }
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Composite_Get_Speed
 *
 * @brief This functions get speed from Host.
 *
 * @param handle          :   handle returned by USB_Composite_Init
 * @param speed           :   speed
 *
 * @return status       
 *         USB_OK         : When Successfull 
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Composite_Get_Speed
(
composite_handle_t handle,
uint16_t * speed/* [OUT] the requested error */
)
{
    composite_device_struct_t * composite_obj_ptr;
    usb_status error = USB_OK;

    composite_obj_ptr = (composite_device_struct_t *)handle;
    if (NULL == composite_obj_ptr)
    {
        return USBERR_NO_DEVICE_CLASS;
    }
    error = USB_Class_Get_Status(composite_obj_ptr->class_handle, USB_STATUS_SPEED, speed);

    return error;
}

#endif
/* EOF */
