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
* $FileName: usb_class_msc.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief 
*
*****************************************************************************/

#ifndef _USB_CLASS_MSC_H
#define _USB_CLASS_MSC_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define MAX_MSC_CLASS_EP_NUM   2

#define USB_MSC_DEVICE_READ_REQUEST        (0x81)
#define USB_MSC_DEVICE_WRITE_REQUEST       (0x82) 
#define USB_MSC_DEVICE_FORMAT_COMPLETE     (0x83)
#define USB_MSC_DEVICE_REMOVAL_REQUEST     (0x84)
#define USB_MSC_DEVICE_GET_INFO            (0x85)
#define USB_MSC_START_STOP_EJECT_MEDIA     (0x86) 
#define USB_MSC_DEVICE_GET_SEND_BUFF_INFO  (0x87)
#define USB_MSC_DEVICE_GET_RECV_BUFF_INFO  (0x88)

/* macros for queuing */
 #define MSD_MAX_QUEUE_ELEMS  (4)

 #define USB_REQ_VAL_INVALID             (0xFFFF)
 
typedef uint32_t msd_handle_t;

/*!
 * @brief MSC app data structure.
 *
 * Holds the information of msc app data struct
 *
 */
typedef struct _msc_app_data_struct
{
    uint8_t*                data_ptr;         /*!< pointer to buffer */     
    uint32_t                data_size;        /*!< buffer size of endpoint*/
}msc_app_data_struct_t;

/*!
 * @brief MSC detailed information about the LAB structure.
 *
 * Holds the detailed information about the LAB
 *
 */
typedef struct _device_lba_info_struct
{
    uint32_t                total_lba_device_supports;    /*!< blocks number */ 
    uint32_t                length_of_each_lab_of_device; /*!< size of each block*/
    uint8_t                 num_lun_supported;            /*!< number of LUN*/
}device_lba_info_struct_t;

/*!
 * @brief MSC buffer information structure.
 *
 * Holds the detailed information about the buffer
 *
 */
typedef struct _msd_buffers_info
{
     uint8_t*               msc_bulk_in_ptr;  /*!< pointer to bulk in buffer*/
     uint8_t*               msc_bulk_out_ptr; /*!< pointer to bulk out buffer*/
     uint32_t               msc_bulk_in_size; /*!< size of bulk in buffer*/
     uint32_t               msc_bulk_out_size;/*!< size of bulk out buffer*/
}msc_buff_info_t;

/*!
 * @brief MSD Configuration structure to be passed by APP
 *
 * Holds the detailed information about the MSC configuration
 *
 */
typedef struct _msc_config_struct
{
    /* SCSI related initialization data. To be moved to SCSI layer.*/
     
     usb_application_callback_struct_t          msc_application_callback; /*!< application callback function to handle the Device status related event*/
     usb_vendor_req_callback_struct_t           vendor_req_callback;      /*!< application callback function to handle the vendor request related event, reserved for future use*/
     usb_class_specific_callback_struct_t       class_specific_callback;  /*!< application callback function to handle all the class related event*/
     usb_desc_request_notify_struct_t*          desc_callback_ptr;        /*!< descriptor related callback function data structure*/
}msc_config_struct_t;

/*!
 * @brief MSC  logical block access information structure.
 *
 * Holds the information used to perform the logical block access
 *
 */
typedef struct _lba_app_struct
{
    uint32_t             offset;   /*!< offset of target block need to access*/
    uint32_t             size;     /*!< size need to access*/
    uint8_t*             buff_ptr; /*!< used to save the content by access the target block*/
}lba_app_struct_t;
//extern void USB_Class_Periodic_Task(void);
#define USB_MSC_Periodic_Task USB_Class_Periodic_Task 
/******************************************************************************
 * Global Functions
 *****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif 
/*!
* @brief The function initializes the Device and Controller layer.
*
* The application calls this API function to initialize the MSD class, the underlying layers, and
* the controller hardware.
*
* @param controller_id controller ID, such as USB_CONTROLLER_KHCI_0
* @param msd_config_ptr MSD configuration structure
* @param msd_handle pointer point to the initialized MSD class
* @return USB_OK-Success/Others-Fail
*/
extern usb_status USB_Class_MSC_Init
(
    uint8_t controller_id,
    msc_config_struct_t* msd_config_ptr,
    msd_handle_t *  msd_handle
); 

/*!
 * @brief The function De-initializes the Device and Controller layer.
 *
 * The application calls this API function to de-initialize the MSD class, the underlying layers, and
 * the controller hardware.
 *
 * @param msd_handle MSC class handler  
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_MSC_Deinit
(
    msd_handle_t msd_handle
);


/**************************************************************************//*!
 *
 * @name  USB_Class_MSC_Get_Speed
 *
 * @brief This functions get speed from Host.
 *
 * @param handle          :   handle returned by USB_Class_MSC_Init
 * @param speed           :   speed
 *
 * @return status       
 *         USB_OK         : When Successfull 
 *         Others         : Errors
 *****************************************************************************/
extern usb_status USB_Class_MSC_Get_Speed
(
    msd_handle_t         handle,
    uint16_t *           speed/* [OUT] the requested error */
);
#ifdef __cplusplus
}
#endif

#endif


