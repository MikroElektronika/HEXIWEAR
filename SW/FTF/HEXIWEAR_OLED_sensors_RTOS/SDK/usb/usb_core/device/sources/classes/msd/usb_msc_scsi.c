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
 * $FileName: usb_msc_scsi.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief The file contains USB Mass Storage SCSI command set.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"

#if USBCFG_DEV_MSC
#include "usb_class_internal.h"
#include "usb_msc_scsi.h"

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/
inquiry_data_struct_t inquiry_info = /* constant */
{
    (PERIPHERAL_QUALIFIER << PERIPHERAL_QUALIFIER_SHIFT)|PERIPHERAL_DEVICE_TYPE,
    (uint8_t)(REMOVABLE_MEDIUM_BIT << REMOVABLE_MEDIUM_BIT_SHIFT),
    SPC_VERSION, 0x02, ADDITIONAL_LENGTH, 0x00,0x00,0x00,
    {   'F', 'S', 'L', ' ', 'S', 'E', 'M', 'I'},
    {   'F','S','L',' ','M','A','S','S',' ','S','T','O','R','A','G','E'},
    {   '0', '0', '0', '1'}
};

mode_parameter_header_struct_t mode_param_header =
{
    0x0000,/*no following data available because of reason given below*/
    0x00,/* 0x00 indicates current/default medium */
    0x00,/* for write_protect and DPOFUA - no write protection available*/
    {   0x00,0x00,0x00,0x00} /* reserved bytes are always to be set to zero */
};

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
/****************************************************************************
 * Global Variables
 ****************************************************************************/
msc_scsi_struct_t g_msc_scsi[MAX_MSC_DEVICE];
/* Add all the variables needed for usb_msc.c to this structure */
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
usb_status msc_thirteen_cases_check(msc_device_struct_t * msc_obj_ptr,msc_thirteen_case_struct_t* msc_check_event);
/*****************************************************************************
 * Local Variables
 *****************************************************************************/
//static read_capacity_data_struct_t read_capacity;
//static read_capacity16_data_struct_t read_capacity16;
//static uint8_t format_capacity_response_data[sizeof(capacity_list_header_struct_t) + sizeof(curr_max_capacity_desc_struct_t)+
//        sizeof(formattable_cap_desc_t) * 3];
/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/*************************************************************************//*!
 *
 * @name  USB_SCSI_Allocate_Handle
 *
 * @brief The funtion reserves entry in device array and returns the index.
 *
 * @param none.
 * @return returns the reserved handle or if no entry found device busy.      
 *
 *****************************************************************************/
static usb_status USB_SCSI_Allocate_Handle(msc_scsi_struct_t** handle)
{
    uint32_t cnt = 0;
    for (;cnt< MAX_MSC_DEVICE;cnt++)
    {
        if (g_msc_scsi[cnt].is_used == 0)
        {
            g_msc_scsi[cnt].is_used = 1;
            *handle = (msc_scsi_struct_t*)&g_msc_scsi[cnt];
            return USB_OK;
        }
    }
    return USBERR_DEVICE_BUSY;
}
/*************************************************************************//*!
 *
 * @name  USB_SCSI_Free_Handle
 *
 * @brief The funtion releases entry in device array .
 *
 * @param handle  index in device array to be released..
 * @return returns and error code or USB_OK.      
 *
 *****************************************************************************/

static usb_status USB_SCSI_Free_Handle(msc_scsi_struct_t* handle)
{
    int32_t cnt = 0;
    for (;cnt< MAX_MSC_DEVICE;cnt++)
    {
        if ((&g_msc_scsi[cnt]) == handle)
        {
            OS_Mem_zero((void*)handle, sizeof(msc_scsi_struct_t));
            return USB_OK;
        }
    }
    return USBERR_INVALID_PARAM;
}
/**************************************************************************//*!
 *
 * @name  msc_thirteen_cases_check
 *
 * @brief The funtion checks for thirteen error case of MSC and takes action 
 *        appropriately
 *
 * @param scsi_ptr->thirteen_case: structure containing all necessary parameter to 
 *        evaluate error scenarios
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_thirteen_cases_check(msc_device_struct_t * msc_obj_ptr,
msc_thirteen_case_struct_t* msc_check_event
)
{
    usb_status error = USB_OK;
    msc_scsi_struct_t* scsi_ptr;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    if(!msc_check_event->host_expected_data_len)
    { /* host expects no data transfer */
        *(msc_check_event->csw_residue_ptr) = 0;

        if(!msc_check_event->device_expected_data_len)
        { /* CASE 1: Device intends no data transfer : Thin Diagonal Case*/
            *(msc_check_event->csw_status_ptr) = COMMAND_PASSED;
        }
        else
        { /* if(msc_check_event->device_expected_direction) :
         CASE 2: Device intends to send data to host
         else
         CASE 3: Device intends to receive data from host */
            *(msc_check_event->csw_status_ptr) = PHASE_ERROR;
        }
    }
    else if(msc_check_event->host_expected_direction)
    { /* host expects to receive data from device (USB_SEND direction)*/
        if(!msc_check_event->device_expected_data_len)
        { /* CASE 4:  Device intends no data transfer */
            *(msc_check_event->csw_residue_ptr) =
            msc_check_event->host_expected_data_len -
            msc_check_event->device_expected_data_len;
            /* sending zero bytes of data */
            error = USB_MSC_Bulk_Send_Data(msc_obj_ptr->msc_handle,
            msc_check_event->buffer_ptr,
            msc_check_event->device_expected_data_len);

            if(error == USB_OK)
            {
                *(msc_check_event->csw_status_ptr) = COMMAND_PASSED;
            }
            else
            {
                *(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
                scsi_ptr->request_sense.sense_key = MEDIUM_ERROR;
                scsi_ptr->request_sense.add_sense_code = UNRECOVERED_READ_ERROR;
            }

            /* BULK IN PIPE TO BE STALLED for status phase */
            error = USBERR_ENDPOINT_STALLED;
        }
        else if(msc_check_event->device_expected_direction)
        { /* device intends to send data to host */
            if(msc_check_event->host_expected_data_len >
            msc_check_event->device_expected_data_len)
            { /* CASE 5: Host intends more data to receive than device 
             intends to send*/
                *(msc_check_event->csw_residue_ptr) =
                msc_check_event->host_expected_data_len -
                msc_check_event->device_expected_data_len;

                if(scsi_ptr->thirteen_case.lba_txrx_select == TRUE)
                {
                    error = USB_MSC_LBA_Transfer(msc_obj_ptr,USB_SEND,
                    &msc_check_event->lba_info);
                }
                else
                {
                    error = USB_MSC_Bulk_Send_Data(msc_obj_ptr->msc_handle,
                    msc_check_event->buffer_ptr,
                    msc_check_event->device_expected_data_len);
                }

//            if ((READ_10_COMMAND != msc_obj_ptr->cbw_ptr->command_block[0]) &&
//                (READ_12_COMMAND != msc_obj_ptr->cbw_ptr->command_block[0]) &&
//                (msc_check_event->device_expected_data_len%
//                    msc_obj_ptr->bulk_in_endpoint_packet_size == 0))
//                {   /* need to send zero bytes of data to tell host that device
//                       does not have any more data. This is needed only if the 
//                       bytes send to host are integral multiple of max packet 
//                       size of Bulk In endpoint */
//                    error |= USB_MSC_Bulk_Send_Data(msc_obj_ptr->msc_handle,
//                        msc_check_event->buffer_ptr,0);                                 
//                }

                if(error == USB_OK)
                {
                    *(msc_check_event->csw_status_ptr) = COMMAND_PASSED;
                }
                else
                {
                    *(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
                    scsi_ptr->request_sense.sense_key = MEDIUM_ERROR;
                    scsi_ptr->request_sense.add_sense_code = UNRECOVERED_READ_ERROR;
                }
                /* BULK IN PIPE TO BE STALLED for status phase */
                error = USBERR_ENDPOINT_STALLED;
            }
            else if(msc_check_event->host_expected_data_len ==
            msc_check_event->device_expected_data_len)
            { /* CASE 6: Host intends exact amount of data to receive 
             as device intends to send : Thin Diagonal Case*/
                *(msc_check_event->csw_residue_ptr) = 0;

                if(scsi_ptr->thirteen_case.lba_txrx_select == TRUE)
                {
                    error = USB_MSC_LBA_Transfer(msc_obj_ptr,USB_SEND,
                    &msc_check_event->lba_info);
                }
                else
                {
                    error = USB_MSC_Bulk_Send_Data(msc_obj_ptr->msc_handle,
                    msc_check_event->buffer_ptr,
                    msc_check_event->device_expected_data_len);
                }

                if(error == USB_OK)
                {
                    *(msc_check_event->csw_status_ptr) = COMMAND_PASSED;
                }
                else
                {
                    *(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
                    scsi_ptr->request_sense.sense_key = MEDIUM_ERROR;
                    scsi_ptr->request_sense.add_sense_code = UNRECOVERED_READ_ERROR;
                }
            }
            else
            {
                /* CASE 7: Host intends less data to receive than device 
                 intends to send*/
                *(msc_check_event->csw_residue_ptr) = 0;

                if (scsi_ptr->thirteen_case.lba_txrx_select == TRUE)
                {
                    msc_check_event->lba_info.lba_transfer_num =
                    msc_check_event->host_expected_data_len /
                    scsi_ptr->length_of_each_lab;
                    *(msc_check_event->csw_residue_ptr) = msc_check_event->host_expected_data_len - msc_check_event->lba_info.lba_transfer_num * scsi_ptr->length_of_each_lab;
                    error = USB_MSC_LBA_Transfer(msc_obj_ptr,USB_SEND,
                    &msc_check_event->lba_info);
                }
                else
                {
                    error = USB_MSC_Bulk_Send_Data(msc_obj_ptr->msc_handle,
                    msc_check_event->buffer_ptr,
                    msc_check_event->host_expected_data_len);
                }

                if(error == USB_OK)
                {
                    if (scsi_ptr->thirteen_case.lba_txrx_select == TRUE) /* READ_COMMAND OR WRITE_COMMAND */
                    {
                        *(msc_check_event->csw_status_ptr) = PHASE_ERROR;
                    }
                    else
                    {
                        *(msc_check_event->csw_status_ptr) = COMMAND_PASSED;
                    }
                }
                else
                {
                    *(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
                    scsi_ptr->request_sense.sense_key = MEDIUM_ERROR;
                    scsi_ptr->request_sense.add_sense_code = UNRECOVERED_READ_ERROR;
                }
            }
        }
        else
        { /* CASE 8: Device intends to receive data from host */
            *(msc_check_event->csw_residue_ptr) =
            msc_check_event->host_expected_data_len;
            /* device has no data to send */
            error = USB_MSC_Bulk_Send_Data(msc_obj_ptr->msc_handle,
            msc_check_event->buffer_ptr,0);
            *(msc_check_event->csw_status_ptr) = PHASE_ERROR;
            /* BULK IN PIPE TO BE STALLED for status phase */
            error = USBERR_ENDPOINT_STALLED;
        }
    }
    else
    { /* host expects to send data to device (USB_RECV direction)*/
        if(!msc_check_event->device_expected_data_len)
        { /* CASE 9:  Device intends no data transfer */
            usb_device_stall_endpoint(msc_obj_ptr->controller_handle,msc_obj_ptr->bulk_out_endpoint, USB_RECV);
            *(msc_check_event->csw_residue_ptr) =
            msc_check_event->host_expected_data_len;
            *(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
            /* BULK OUT PIPE STALLED */
            msc_obj_ptr->out_stall_flag = TRUE;
            error = USBERR_ENDPOINT_STALLED;
        }
        else if(msc_check_event->device_expected_direction)
        { /*CASE10: device intends to send data to host */
            usb_device_stall_endpoint(msc_obj_ptr->controller_handle,msc_obj_ptr->bulk_out_endpoint, USB_RECV);
            *(msc_check_event->csw_residue_ptr) =
            msc_check_event->host_expected_data_len;
            *(msc_check_event->csw_status_ptr) = PHASE_ERROR;
            /* BULK OUT PIPE STALLED */
            msc_obj_ptr->out_stall_flag = TRUE;
            error = USBERR_ENDPOINT_STALLED;
        }
        else
        { /*Device intends to receive data from host */
            if(msc_check_event->host_expected_data_len >
            msc_check_event->device_expected_data_len)
            { /* CASE 11: Host intends more data to send than device 
             intends to receive*/
                *(msc_check_event->csw_residue_ptr) =
                msc_check_event->host_expected_data_len -
                msc_check_event->device_expected_data_len;

                if(scsi_ptr->thirteen_case.lba_txrx_select == TRUE)
                {
                    error = USB_MSC_LBA_Transfer(msc_obj_ptr,USB_RECV,
                    &msc_check_event->lba_info);
                }
                else
                {
                    error = USB_MSC_Bulk_Recv_Data(msc_obj_ptr->controller_handle,
                    msc_check_event->buffer_ptr,
                    msc_check_event->device_expected_data_len);
                }

                if(error == USB_OK)
                {
                    *(msc_check_event->csw_status_ptr) = COMMAND_PASSED;
                }
                else
                {
                    *(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
                    scsi_ptr->request_sense.sense_key = MEDIUM_ERROR;
                    scsi_ptr->request_sense.add_sense_code = WRITE_FAULT;
                }
                /* BULK OUT PIPE TO BE STALLED for status phase */
                error = USBERR_ENDPOINT_STALLED;
            }
            else if(msc_check_event->host_expected_data_len ==
            msc_check_event->device_expected_data_len)
            { /* CASE 12: Host intends exact amount of data to send 
             as device intends to receive : Thin Diagonal Case*/
                *(msc_check_event->csw_residue_ptr) = 0;

                if(scsi_ptr->thirteen_case.lba_txrx_select == TRUE)
                {
                    error = USB_MSC_LBA_Transfer(msc_obj_ptr,USB_RECV,
                    &msc_check_event->lba_info);
                }
                else
                {
                    error = USB_MSC_Bulk_Recv_Data(msc_obj_ptr->controller_handle,
                    msc_check_event->buffer_ptr,
                    msc_check_event->device_expected_data_len);
                }

                if(error == USB_OK)
                {
                    *(msc_check_event->csw_status_ptr) = COMMAND_PASSED;
                }
                else
                {
                    *(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
                    scsi_ptr->request_sense.sense_key = MEDIUM_ERROR;
                    scsi_ptr->request_sense.add_sense_code = WRITE_FAULT;
                }
            }
            else
            {
                /* CASE 13: Host intends less data to send than device 
                 intends to receive*/
                *(msc_check_event->csw_residue_ptr) = 0;

                if(scsi_ptr->thirteen_case.lba_txrx_select == TRUE)
                {
                    msc_check_event->lba_info.lba_transfer_num =
                    msc_check_event->host_expected_data_len /
                    scsi_ptr->length_of_each_lab;
                    *(msc_check_event->csw_residue_ptr) = msc_check_event->host_expected_data_len - msc_check_event->lba_info.lba_transfer_num * scsi_ptr->length_of_each_lab;
                    error = USB_MSC_LBA_Transfer(msc_obj_ptr,USB_RECV,
                    &msc_check_event->lba_info);
                }
                else
                {
                    error = USB_MSC_Bulk_Recv_Data(msc_obj_ptr->controller_handle,
                    msc_check_event->buffer_ptr,
                    msc_check_event->host_expected_data_len);
                }

                if (error == USB_OK)
                {
                    if (scsi_ptr->thirteen_case.lba_txrx_select == TRUE) /* READ_COMMAND OR WRITE_COMMAND */
                    {
                        *(msc_check_event->csw_status_ptr) = PHASE_ERROR;
                    }
                    else
                    {
                        *(msc_check_event->csw_status_ptr) = COMMAND_PASSED;
                    }
                }
                else
                {
                    scsi_ptr->request_sense.sense_key = MEDIUM_ERROR;
                    scsi_ptr->request_sense.add_sense_code = WRITE_FAULT;
                }
            }
        }
    }
    return error;
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_MSC_SCSI_Init
 *
 * @brief The funtion initializes the SCSI parameters and callbacks
 *
 * @param msc_obj_ptr         MSD class object pointer.
 * @param cb:                 event callback
 * @param device_info_ptr   : Contains MSD device info like number of LBA, etc
 * @return status
 *         USB_OK           : When Successfull
 *         Others           : Errors
 *
 *****************************************************************************/
usb_status USB_MSC_SCSI_Init
(
msc_device_struct_t * msc_obj_ptr,
usb_class_specific_callback_struct_t* cb,
device_lba_info_struct_t* device_info_ptr,
uint32_t implementing_disk_drive
)
{
    msc_scsi_struct_t* scsi_ptr = NULL;
    usb_status error = USBERR_ERROR;
    /* initialize the Global Variable Structure */

    error = USB_SCSI_Allocate_Handle(&scsi_ptr);
    if (USB_OK != error)
    {
        return error;
    }

    /* save input parameters */
    scsi_ptr->scsi_callback.callback = cb->callback;
    scsi_ptr->scsi_callback.arg = cb->arg;
    scsi_ptr->total_logical_add_block =
    device_info_ptr->total_lba_device_supports;
    scsi_ptr->length_of_each_lab =
    device_info_ptr->length_of_each_lab_of_device;
    scsi_ptr->implementing_disk_drive = implementing_disk_drive;

    /* no need to initialize other structure fields as g_resquest_sense has
     been declared as static */
    scsi_ptr->request_sense.valid_error_code = REQ_SENSE_VALID_ERROR_CODE;
    scsi_ptr->request_sense.add_sense_len = REQ_SENSE_ADDITIONAL_SENSE_LEN;
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    if(scsi_ptr->scsi_callback.callback != NULL)
    {
        scsi_ptr->scsi_callback.callback(USB_MSC_DEVICE_GET_INFO,USB_REQ_VAL_INVALID,NULL,(uint32_t *)device_info_ptr,NULL);
    }

    scsi_ptr->total_logical_add_block =
    device_info_ptr->total_lba_device_supports;
    scsi_ptr->length_of_each_lab =
    device_info_ptr->length_of_each_lab_of_device;

    scsi_ptr->read_capacity.last_logical_block_address = USB_LONG_BE_TO_HOST(scsi_ptr->total_logical_add_block -1);
    scsi_ptr->read_capacity.block_size = USB_LONG_BE_TO_HOST((uint32_t) scsi_ptr->length_of_each_lab);
    scsi_ptr->read_capacity16.last_logical_block_address1 = USB_LONG_BE_TO_HOST(scsi_ptr->total_logical_add_block -1);
    scsi_ptr->read_capacity16.block_size = USB_LONG_BE_TO_HOST((uint32_t) scsi_ptr->length_of_each_lab);

    msc_obj_ptr->scsi_object_ptr = scsi_ptr;
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_MSC_SCSI_Deinit
 *
 * @brief The funtion deinitializes the SCSI parameters and callbacks
 *
 * @param msc_obj_ptr         MSD class object pointer.
 * @return status
 *         USB_OK           : When Successfull
 *         Others           : Errors
 *
 *****************************************************************************/
usb_status USB_MSC_SCSI_Deinit
(
msc_device_struct_t * msc_obj_ptr
)
{
    if(NULL == msc_obj_ptr)
    {
        return USBERR_ERROR;
    }
    USB_SCSI_Free_Handle((msc_scsi_struct_t* )msc_obj_ptr->scsi_object_ptr);

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  msc_request_sense_command
 *
 * @brief command instructs the Device to transfer sense data to host computer
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return NONE
 *
 *****************************************************************************/
usb_status msc_request_sense_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    usb_status error;
    msc_scsi_struct_t* scsi_ptr;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_data_len = REQ_SENSE_DATA_LENGTH;
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = (uint8_t *)&scsi_ptr->request_sense;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_inquiry_command
 *
 * @brief It requests that information regarding parameters of the Device be
 *        sent to the Host Computer
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_inquiry_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    usb_status error = USBERR_TX_FAILED;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_data_len = INQUIRY_ALLOCATION_LENGTH;
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = (uint8_t *)&inquiry_info;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_read_command
 *
 * @brief command requests that device transfer data to the host computer
 *        (read (10) command)
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_read_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    uint32_t lba = 0;
    uint32_t num_lba_tx = 0;
    usb_status error = USBERR_TX_FAILED;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    lba = ((uint32_t)cbw_ptr->command_block[2] << 24);
    lba |= ((uint32_t)cbw_ptr->command_block[3] << 16);
    lba |= ((uint32_t)cbw_ptr->command_block[4] << 8);
    lba |= ((uint32_t)cbw_ptr->command_block[5]);

    if(cbw_ptr->command_block[0] == READ_10_COMMAND)
    {
        num_lba_tx = (uint16_t)((uint16_t)cbw_ptr->command_block[7] << 8);
        num_lba_tx |= (uint16_t)cbw_ptr->command_block[8];
    }
    else if(cbw_ptr->command_block[0] == READ_12_COMMAND)
    {
        num_lba_tx = ((uint32_t)cbw_ptr->command_block[6] << 24);
        num_lba_tx |= ((uint32_t)cbw_ptr->command_block[7] << 16);
        num_lba_tx |= ((uint32_t)cbw_ptr->command_block[8] << 8);
        num_lba_tx |= ((uint32_t)cbw_ptr->command_block[9]);
    }

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;

    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;

    scsi_ptr->thirteen_case.device_expected_data_len =
    scsi_ptr->length_of_each_lab * num_lba_tx;
    scsi_ptr->thirteen_case.buffer_ptr = NULL;

    scsi_ptr->thirteen_case.lba_txrx_select = TRUE;
    scsi_ptr->thirteen_case.lba_info.starting_lba = lba;
    scsi_ptr->thirteen_case.lba_info.lba_transfer_num = num_lba_tx;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_write_command
 *
 * @brief command requests that the Device write the data transferred by the
 *        Host Computer to the medium.
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_write_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    uint32_t lba = 0;
    uint32_t num_lba_rx = 0;
    usb_status error = USBERR_RX_FAILED;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    lba = ((uint32_t)cbw_ptr->command_block[2] << 24);
    lba |= ((uint32_t)cbw_ptr->command_block[3] << 16);
    lba |= ((uint32_t)cbw_ptr->command_block[4] << 8);
    lba |= ((uint32_t)cbw_ptr->command_block[5]);

    if(cbw_ptr->command_block[0] == WRITE_10_COMMAND)
    {
        num_lba_rx = (uint16_t)((uint16_t)cbw_ptr->command_block[7] << 8);
        num_lba_rx |= (uint16_t)cbw_ptr->command_block[8];
    }
    else if(cbw_ptr->command_block[0] == WRITE_12_COMMAND)
    {
        num_lba_rx = ((uint32_t)cbw_ptr->command_block[6] << 24);
        num_lba_rx |= ((uint32_t)cbw_ptr->command_block[7] << 16);
        num_lba_rx |= ((uint32_t)cbw_ptr->command_block[8] << 8);
        num_lba_rx |= ((uint32_t)cbw_ptr->command_block[9]);
    }

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_direction = USB_RECV;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;

    scsi_ptr->thirteen_case.buffer_ptr = NULL;

#if 0
    if(usb_device_get_transfer_status(msc_obj_ptr->controller_handle,
    BULK_OUT_ENDPOINT, USB_RECV) != USB_STATUS_IDLE)
    {
        (void)usb_device_cancel_transfer(msc_obj_ptr->controller_handle,BULK_OUT_ENDPOINT,
        USB_RECV);
    }
#endif

    scsi_ptr->thirteen_case.device_expected_data_len =
    scsi_ptr->length_of_each_lab * num_lba_rx;

    scsi_ptr->thirteen_case.lba_txrx_select = TRUE;
    scsi_ptr->thirteen_case.lba_info.starting_lba = lba;
    scsi_ptr->thirteen_case.lba_info.lba_transfer_num = num_lba_rx;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_test_unit_ready_command
 *
 * @brief It provides a means to check if the device is ready
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_test_unit_ready_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    usb_status error;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;
    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);

    scsi_ptr->thirteen_case.device_expected_data_len = 0;
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = NULL;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_verify_command
 *
 * @brief requests that device verifies the data on medium
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_verify_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    usb_status error;
    /* Our Device has no mechanism to verify the blocks, 
     so just returning success status to host*/

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;
    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);

    scsi_ptr->thirteen_case.device_expected_data_len = 0;
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = NULL;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_mode_sense_command
 *
 * @brief command provides a means for a Device to report parameters to Host
 *        Computer.It is a complementary command to the MODE SELECT command.
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_mode_sense_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    usb_status error = USBERR_TX_FAILED;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;
    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    /* irrespective of DBD(Disable block descriptor) bit in Command Block
     Wrapper we are not returning any block descriptors in the returned mode
     sense data.Presently, we are just returning Mode Parameter Header */

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_data_len = sizeof(mode_param_header);
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = (uint8_t *)&mode_param_header;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_mode_select_command
 *
 * @brief command provides a means for a Device to report parameters to Host
 *        Computer.It is a complementary command to the MODE SENSE command.
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_mode_select_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    usb_status error = USBERR_TX_FAILED;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;
    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);

    scsi_ptr->thirteen_case.device_expected_data_len = sizeof(mode_param_header);
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = (uint8_t *)&mode_param_header;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    if(cbw_ptr->command_block[1] & 0x01)/* checking Save Pages Bit in command*/
    {
        scsi_ptr->request_sense.sense_key = ILLEGAL_REQUEST;
        scsi_ptr->request_sense.add_sense_code = INVALID_FIELD_IN_COMMAND_PKT;
        /*logical unit does not implement save mode pages in our case*/
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_read_capacity_command
 *
 * @brief command provides a means for the host computer to request information
 *        regarding the capacity of the installed medium of the device.
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_read_capacity_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    usb_status error = USBERR_TX_FAILED;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    if(cbw_ptr->command_block[0] == READ_CAPACITY_10_COMMAND)
    {
        scsi_ptr->thirteen_case.device_expected_data_len = READ_CAPACITY_DATA_LENGTH;
        scsi_ptr->thirteen_case.buffer_ptr = (uint8_t *)&(scsi_ptr->read_capacity);
    }
    else
    {
        scsi_ptr->thirteen_case.device_expected_data_len = READ_CAPACITY16_DATA_LENGTH;
        scsi_ptr->thirteen_case.buffer_ptr = (uint8_t *)&(scsi_ptr->read_capacity16);
    }
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_read_format_capacity_command
 *
 * @brief allows the host to request a list of the possible capacities that
 *        can be formatted on the currently installed medium
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_read_format_capacity_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    uint8_t num_formattable_cap_desc;
    uint16_t allocation_length;
    /* pointer to data to be sent in data phase for this command*/
    //uint8_t * response_data_ptr = NULL;
    /* size of data to be sent in data phase for this command*/
    uint32_t response_size;
    /* general variable for counting in loop */
    uint8_t i;
    curr_max_capacity_desc_struct_t curr_max_cap_header;
    uint8_t desc_code;
    formattable_cap_desc_t formattable_cap_descriptor;
    capacity_list_header_struct_t capacity_list_header= {{0x00,0x00,0x00},0x00};
    usb_status error = USBERR_TX_FAILED;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;
    allocation_length = (uint16_t)((uint8_t)(cbw_ptr->command_block[7] << 8) |
    cbw_ptr->command_block[8]);

    num_formattable_cap_desc = (uint8_t)(scsi_ptr->formatted_disk ?
    (scsi_ptr->implementing_disk_drive?0x02:0x03):0x00);
    /*
     * gives the number of Formattable Capacity Descriptor to be sent by device
     * in response to read format capacities command
     */

    /* 
     * 0x03 is number of formattable capcity desc for HD while for DD its 2 if
     * formatted drive is there
     */

    formattable_cap_descriptor.num_blocks = scsi_ptr->total_logical_add_block;
    formattable_cap_descriptor.block_len = scsi_ptr->length_of_each_lab;

    desc_code = (uint8_t)(scsi_ptr->formatted_disk?FORMATTED_MEDIA:UNFORMATTED_MEDIA);
    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    capacity_list_header.capacity_list_len = (uint8_t)(num_formattable_cap_desc * 8);
    curr_max_cap_header.num_blocks = scsi_ptr->total_logical_add_block;
    curr_max_cap_header.desc_code_and_block_len = (uint8_t)(desc_code << 24)|
    scsi_ptr->length_of_each_lab;
    response_size = sizeof(capacity_list_header) + sizeof(curr_max_cap_header)+
    sizeof(formattable_cap_descriptor) * num_formattable_cap_desc;

    if(response_size > allocation_length)
    { /* comapring the length of data available with allocation length value
     sent in CBW which indicates the length of buffer host has reserved
     for data phase of this command */
        response_size = allocation_length;
    }

    if(sizeof(scsi_ptr->format_capacity_response_data) < response_size)
    {
        USB_PRINTF("format_capacity_response_data buff size less than need\n");
    }
    OS_Mem_zero(scsi_ptr->format_capacity_response_data, response_size);

    OS_Mem_copy(&capacity_list_header, scsi_ptr->format_capacity_response_data,
    sizeof(capacity_list_header));
    OS_Mem_copy(&curr_max_cap_header, scsi_ptr->format_capacity_response_data +
    sizeof(capacity_list_header),sizeof(curr_max_cap_header));

    if(scsi_ptr->formatted_disk)
    {
        for(i = 0; i < num_formattable_cap_desc; i++)
        {
            OS_Mem_copy(&formattable_cap_descriptor, scsi_ptr->format_capacity_response_data +
            sizeof(capacity_list_header) + sizeof(curr_max_cap_header)+
            sizeof(formattable_cap_descriptor) * i,
            sizeof(formattable_cap_descriptor));
        }
    }

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_data_len = response_size;
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = scsi_ptr->format_capacity_response_data;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_format_unit_command
 *
 * @brief host sends the FORMAT UNIT command to physically format a diskette
 *        according to selected options
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_format_unit_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    usb_status error;
    *csw_residue_ptr = 0;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_data_len = 0;
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = NULL;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    if(*csw_status_ptr != PHASE_ERROR)
    {
        /* FmtData = 1, CmpList = 0, Defect List Format = 7 */
        if((cbw_ptr->command_block[1] & 0x1F) == 0x17)
        {
            *csw_status_ptr = COMMAND_PASSED;
        }
        else
        {
            *csw_status_ptr = COMMAND_FAILED;
            scsi_ptr->request_sense.sense_key = ILLEGAL_REQUEST;
            scsi_ptr->request_sense.add_sense_code = INVALID_FIELD_IN_COMMAND_PKT;
        }
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_prevent_allow_medium_removal
 *
 * @brief command tells the UFI device to enable or disable the removal of the
 *        medium in the logical unit.
 *
 * @param handle 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_prevent_allow_medium_removal
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    usb_status error;
    uint8_t prevent_removal = 0;
    /* masking to obtain value of last bit */
    prevent_removal = (uint8_t)(cbw_ptr->command_block[4] &
    PREVENT_ALLOW_REMOVAL_MASK);

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;
    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_data_len = 0;
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = NULL;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    if(*csw_status_ptr != PHASE_ERROR)
    {
        if((!SUPPORT_DISK_LOCKING_MECHANISM)&&(prevent_removal))
        {/*there is no support for disk locking and removal of medium is disabled*/
            scsi_ptr->request_sense.sense_key = ILLEGAL_REQUEST;
            scsi_ptr->request_sense.add_sense_code = INVALID_FIELD_IN_COMMAND_PKT;
            *csw_status_ptr = COMMAND_FAILED;
        }
    }

    if(scsi_ptr->scsi_callback.callback != NULL)
    {
        scsi_ptr->scsi_callback.callback(USB_MSC_DEVICE_REMOVAL_REQUEST,
        USB_REQ_VAL_INVALID,NULL,(uint32_t *)&prevent_removal, scsi_ptr->scsi_callback.arg);
    }

    return error;
}

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
usb_status msc_send_diagnostic_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    /* No Self Test Procedure available */
    usb_status error;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_data_len = 0;
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = NULL;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_start_stop_unit_command
 *
 * @brief command instructs device to enable or disable media access operations
 *
 * @param msc_obj_ptr:    
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
usb_status msc_start_stop_unit_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;
    usb_status error;
    uint8_t load_eject_start;

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    /* masking to obtain value of last bit */
    load_eject_start = (uint8_t)(cbw_ptr->command_block[4] &
    LOAD_EJECT_START_MASK);
    /* initialize sense code values */
    scsi_ptr->request_sense.sense_key = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code = NO_SENSE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    scsi_ptr->thirteen_case.handle = msc_obj_ptr->controller_handle;
    scsi_ptr->thirteen_case.host_expected_data_len = cbw_ptr->data_length;
    scsi_ptr->thirteen_case.host_expected_direction =
    (uint8_t)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    scsi_ptr->thirteen_case.device_expected_data_len = 0;
    scsi_ptr->thirteen_case.device_expected_direction = USB_SEND;
    scsi_ptr->thirteen_case.csw_status_ptr = csw_status_ptr;
    scsi_ptr->thirteen_case.csw_residue_ptr = csw_residue_ptr;
    scsi_ptr->thirteen_case.buffer_ptr = NULL;
    scsi_ptr->thirteen_case.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(msc_obj_ptr, &scsi_ptr->thirteen_case);

    if(*csw_status_ptr != PHASE_ERROR)
    {
        if(scsi_ptr->scsi_callback.callback != NULL)
        {
            scsi_ptr->scsi_callback.callback(USB_MSC_START_STOP_EJECT_MEDIA,
            USB_REQ_VAL_INVALID,NULL,(uint32_t *)&load_eject_start, scsi_ptr->scsi_callback.arg);
        }
    }
    return error;
}

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
usb_status msc_unsupported_command
(
msc_device_struct_t * msc_obj_ptr,
cbw_t * cbw_ptr,
uint32_t* csw_residue_ptr,
uint8_t* csw_status_ptr
)
{
    msc_scsi_struct_t* scsi_ptr;

    //UNUSED_ARGUMENT(cbw_ptr)   

    scsi_ptr = (msc_scsi_struct_t*)msc_obj_ptr->scsi_object_ptr;

    *csw_residue_ptr = 0;
    *csw_status_ptr = COMMAND_FAILED;

    scsi_ptr->request_sense.sense_key = ILLEGAL_REQUEST;
    scsi_ptr->request_sense.add_sense_code = INVALID_COMMAND_OPCODE;
    scsi_ptr->request_sense.add_sense_code_qual = NO_SENSE;

    return USB_OK;
}
#endif /*MSD_CONFIG*/
/* EOF */
