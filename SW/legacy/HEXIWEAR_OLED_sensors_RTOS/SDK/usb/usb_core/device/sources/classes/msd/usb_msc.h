/**HEADER********************************************************************
 * 
 * Copyright (c) 2008, 2013 - 2015 Freescale Semiconductor;
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
 * $FileName: usb_msc.h$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief The file contains USB stack MSC class layer api header function.
 *
 *****************************************************************************/

#ifndef _USB_MSC_H
#define _USB_MSC_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_stack_interface.h"

#include "usb_class.h"

#include "usb_class_msc.h"

#include "usb_msc_config.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/

/* Class specific request Codes */
#define BULK_ONLY_MASS_STORAGE_RESET          (0xFF)
#define GET_MAX_LUN                           (0xFE)
#define PUT_REQUESTS                          (0xFD)
#define GET_REQUESTS                          (0xFC)

/* Events to the Application *//* 0 to 4 are reserved for class events */

/* other macros */
#define  USB_DCBWSIGNATURE       USB_LONG_BE_TO_HOST_CONST(0x55534243)
#define  USB_DCSWSIGNATURE       USB_LONG_BE_TO_HOST_CONST(0x55534253)
#define  USB_CBW_DIRECTION_BIT   (0x80)
#define  USB_CBW_DIRECTION_SHIFT (7)
#define  MSC_CBW_LENGTH          (31)
#define  MSC_CSW_LENGTH          (13)

#define COMMAND_PASSED                (0x00)
#define COMMAND_FAILED                (0x01)
#define PHASE_ERROR                   (0x02)

/* MACROS FOR COMMANDS SUPPORTED */
#define INQUIRY_COMMAND                    (0x12)
#define READ_10_COMMAND                    (0x28)
#define READ_12_COMMAND                    (0xA8)
#define REQUEST_SENSE_COMMAND              (0x03)
#define TEST_UNIT_READY_COMMAND            (0x00)
#define WRITE_10_COMMAND                   (0x2A)
#define WRITE_12_COMMAND                   (0xAA)
#define PREVENT_ALLOW_MEDIUM_REM_COMMAND   (0x1E)
#define FORMAT_UNIT_COMMAND                (0x04)
#define READ_CAPACITY_10_COMMAND           (0x25)
#define READ_CAPACITY_16_COMMAND           (0x9E)
#define READ_FORMAT_CAPACITIES_COMMAND     (0x23)
#define MODE_SENSE_10_COMMAND              (0x5A) 
#define MODE_SENSE_6_COMMAND               (0x1A)
#define MODE_SELECT_10_COMMAND             (0x55)
#define MODE_SELECT_6_COMMAND              (0x15)
#define SEND_DIAGNOSTIC_COMMAND            (0x1D)
#define VERIFY_COMMAND                     (0x2F)
#define START_STOP_UNIT_COMMAND            (0x1B)

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
void USB_Service_Bulk_In(usb_event_struct_t* event, void* arg);
void USB_Service_Bulk_Out(usb_event_struct_t* event, void* arg);
void USB_Class_MSC_Event(uint8_t event, void* val, void* arg);
usb_status USB_MSC_Requests(usb_setup_struct_t * setup_packet, uint8_t * *data, uint32_t *size, void* arg);

/******************************************************************************
 * Types
 *****************************************************************************/
typedef enum
{
    USB_MSD_EP_COUNT = 1,
    USB_MSD_INTERFACE_COUNT,
    USB_MSD_CLASS_INFO,
} USB_MSD_DESC_INFO_T;

typedef enum
{
    STALL_IN_CBW = 1,
    STALL_IN_DATA_PHASE,
    STALL_IN_CSW,
} STALL_TYPES_T;

typedef struct _usb_msc_cbw /* Command Block Wrapper -- 31 bytes */
{
    uint32_t             signature;        /*0-3  : dCBWSignature*/
    uint32_t             tag;              /*4-7  : dCBWTag*/
    uint32_t             data_length;      /*8-11 : dCBWDataTransferLength*/
    uint8_t              flag;             /*12   : bmCBWFlags*/
    uint8_t              lun;              /*13   : bCBWLUN(bits 3 to 0)*/
    uint8_t              cb_length;        /*14   : bCBWCBLength*/
    uint8_t              command_block[16];/*15-30 : CBWCB*/
}cbw_t;

typedef struct _usb_msc_csw /* Command Status Wrapper -- 13 bytes */
{
    uint32_t             signature; /*0-3  : dCSWSignature*/
    uint32_t             tag;       /*4-7 : dCSWTag*/
    uint32_t             residue;   /*8-11 : dCSWDataResidue*/
    uint8_t              csw_status; /*12 : bCSWStatus*/
}csw_t;

typedef struct _lba_info_struct
{
    uint32_t             starting_lba;/* LBA to start transferring with */
    uint32_t             lba_transfer_num;/* number of LBAs to transfer */    
} lba_info_struct_t;

typedef struct _msc_thirteen_case_check
{
    usb_device_handle    handle;
    uint32_t             host_expected_data_len;
    uint32_t             device_expected_data_len;
    uint8_t*             csw_status_ptr;
    uint32_t*            csw_residue_ptr;
    uint8_t*             buffer_ptr;
    lba_info_struct_t    lba_info;
    bool                 lba_txrx_select;
    uint8_t              host_expected_direction;
    uint8_t              device_expected_direction;
} msc_thirteen_case_struct_t;

/* USB class msc endpoint data */
typedef struct _msc_endpoint_struct
{
    uint8_t endpoint; /* endpoint num */
    uint8_t type; /* type of endpoint (interrupt, bulk or isochronous) */
} msc_endpoint_struct_t;

typedef struct _msc_endpoint_data_struct
{
    uint8_t count;
    msc_endpoint_struct_t ep[MAX_MSC_CLASS_EP_NUM];
} msc_endpoint_data_struct_t;

/* MSD Device Structure */
typedef struct _msc_variable_struct
{
    usb_device_handle                           controller_handle;
    uint32_t                                    user_handle;
    msd_handle_t                                msc_handle;
    class_handle_t                              class_handle;
    usb_endpoints_t*                            ep_desc_data;
    usb_application_callback_struct_t           msc_application_callback;
    usb_vendor_req_callback_struct_t            vendor_req_callback;            
    usb_class_specific_callback_struct_t        class_specific_callback;
    usb_desc_request_notify_struct_t            desc_callback;  
    /* contains the endpoint info */
    /* Memory Allocation for endpoint done at App layer. Only App
       Knows how many endpoints to allocate.
      */
    void*                                       scsi_object_ptr;
    msc_endpoint_data_struct_t                  msc_endpoint_data;
    /* macro configured by user*/
    /* global structure for command status wrapper */
    csw_t *                                     csw_ptr;
    /* global structure for command block wrapper */
    cbw_t *                                     cbw_ptr;    
    device_lba_info_struct_t                    device_info;
    msc_buff_info_t                             msd_buff;
    /* following two macros are used to manage transfers involving read/write 
       on APPLICATION MASS STORAGE DEVICE */
    uint32_t                                    transfer_remaining;
    uint32_t                                    current_offset;
    uint32_t                                    bulk_in_endpoint_packet_size;
    uint32_t                                    usb_max_suported_interfaces;
    uint8_t                                     bulk_in_endpoint;
    uint8_t                                     bulk_out_endpoint;
    /* flag to track bulk out data processing after CBW if needed*/
    bool                                        out_flag; 
    /* flag to track bulk in data processing before CSW if needed*/
    bool                                        in_flag;
    /* flag to track if there is stall BULK IN ENDPOINT because of BULK COMMAND*/
    bool                                        in_stall_flag;
    /* flag to track if there is stall BULK OUT ENDPOIN because of BULK COMMAND */
    bool                                        out_stall_flag;
    /* flag to validate CBW */
    bool                                        cbw_valid_flag;
    bool                                        re_stall_flag;
    bool                                        wait_for_reset_recovery;
    bool                                        need_to_prepare_next;
    /* flag to track if there is need to stall BULK IN ENDPOINT because of BULK COMMAND*/
    bool                                        need_in_stall_flag;
    /* flag to track if there is need to stall BULK OUT ENDPOIN because of BULK COMMAND */
    bool                                        need_out_stall_flag;
    bool                                        cbw_prime_flag;
    bool                                        csw_prime_flag;
    uint8_t                                     stall_status;
    /* LUN can have value only from 0 to 15 decimal */
    uint8_t                                     lun;
}msc_device_struct_t; 

/**************************************************************************//*!
 *
 * @name  USB_Class_MSC_Send_Data
 *
 * @brief 
 *
 * @param msc_handle   :   handle returned from USB_Class_MSC_Init
 * @param ep_num          :   endpoint num 
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer   
 *
 * @return status       
 *         USB_OK           : When Successfull 
 *         Others           : Errors
 *****************************************************************************/
extern usb_status USB_Class_MSC_Send_Data
(
    msd_handle_t msc_handle,
    uint8_t ep_num,
    uint8_t * app_buff, /* [IN] buffer to send */
    uint32_t size /* [IN] length of the transfer */
    );

/**************************************************************************//*!
 *
 * @name  USB_MSC_LBA_Transfer
 *
 * @brief 
 *
 * @param msc_device_struct_t *   
 * @param direction       :   transfer direction
 * @param lba_info_ptr    :   buffer to send
 *
 * @return status       
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/
extern usb_status USB_MSC_LBA_Transfer
(
    msc_device_struct_t * msc_obj_ptr,
    bool direction,
    lba_info_struct_t * lba_info_ptr
    );

#define USB_MSC_Bulk_Send_Data(a,b,c)  USB_Class_MSC_Send_Data(a,msc_obj_ptr->bulk_in_endpoint,b,c)
#define USB_MSC_Bulk_Recv_Data(a,b,c)  usb_device_recv_data(a,msc_obj_ptr->bulk_out_endpoint,b,c)

/* Sub Class Functions */

/**************************************************************************//*!
 *
 * @name  USB_MSC_SCSI_Init
 *
 * @brief The function initializes the SCSI parameters and callbacks
 *
 * @param msc_obj_ptr         MSD class object pointer.
 * @param cb:                 event callback
 * @param storage_disk        Ramdisk Memory pointer.
 * @param lb                  logical block
 * @param lab_len             length of each logical blocks
 *
 * @return status
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *
 *****************************************************************************/
extern usb_status USB_MSC_SCSI_Init
(
    msc_device_struct_t * msc_obj_ptr,
    usb_class_specific_callback_struct_t* cb,
    device_lba_info_struct_t* device_info_ptr,
    uint32_t implementing_disk_drive
    );

/**************************************************************************//*!
 *
 * @name  USB_MSC_SCSI_Deinit
 *
 * @brief The function de-initializes the SCSI parameters and callbacks
 *
 * @param msc_obj_ptr         MSD class object pointer.
 * @return status
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *
 *****************************************************************************/
extern usb_status USB_MSC_SCSI_Deinit
(
    msc_device_struct_t * msc_obj_ptr
    );

/**************************************************************************//*!
 *
 * @name  msc_inquiry_command
 *
 * @brief It requests that information regarding parameters of the Device be
 *        sent to the Host Computer
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/

extern usb_status msc_inquiry_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_read_command
 *
 * @brief command requests that device transfer data to the host computer
 *        (read (10) command)
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_read_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_request_sense_command
 *
 * @brief command instructs the Device to transfer sense data to host computer
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return NONE
 *
 *****************************************************************************/
extern usb_status msc_request_sense_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_test_unit_ready_command
 *
 * @brief It provides a means to check if the device is ready
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_test_unit_ready_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_verify_command
 *
 * @brief requests that device verifies the data on medium
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_verify_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_mode_sense_command
 *
 * @brief command provides a means for a Device to report parameters to Host
 *        Computer.It is a complementary command to the MODE SELECT command.
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_mode_sense_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_mode_select_command
 *
 * @brief command provides a means for a Device to report parameters to Host
 *        Computer.It is a complementary command to the MODE SENSE command.
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_mode_select_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_read_capacity_command
 *
 * @brief command provides a means for the host computer to request information
 *        regarding the capacity of the installed medium of the device.
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_read_capacity_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_format_unit_command
 *
 * @brief host sends the FORMAT UNIT command to physically format a diskette
 *        according to selected options
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_format_unit_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_write_command
 *
 * @brief command requests that the Device write the data transferred by the
 *        Host Computer to the medium.
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_write_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_start_stop_unit_command
 *
 * @brief command instructs device to enable or disable media access operations
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_start_stop_unit_command
(
    msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr
    );

/**************************************************************************//*!
 *
 * @name  msc_prevent_allow_medium_removal
 *
 * @brief command tells the UFI device to enable or disable the removal of the
 *        medium in the logical unit.
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_prevent_allow_medium_removal(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);
/**************************************************************************//*!
 *
 * @name  msc_read_format_capacity_command
 *
 * @brief allows the host to request a list of the possible capacities that
 *        can be formatted on the currently installed medium
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_read_format_capacity_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);

/**************************************************************************//*!
 *
 * @name  msc_send_diagnostic_command
 *
 * @brief requests the device to perform self test
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_send_diagnostic_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);

/**************************************************************************//*!
 *
 * @name  msc_unsupported_command
 *
 * @brief Responds appropriately to unsupported commands
 *
 * @param msc_obj_ptr 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
extern usb_status msc_unsupported_command(msc_device_struct_t * msc_obj_ptr,
    cbw_t * cbw_ptr,
    uint32_t* csw_residue_ptr,
    uint8_t* csw_status_ptr);

/* EOF */
#endif

/* EOF */
