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
* $FileName: usb_cdc_pstn.c$
* $Version :
* $Date    :
*
* Comments:
*
* @brief The file contains USB CDC_PSTN module implementation.
*
*****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"
#include "usb_class_internal.h"

#if USBCFG_DEV_CDC
#include "usb_class_cdc.h"
#include "usb_cdc_pstn.h"
#include "usb_cdc.h"
/*****************************************************************************
* Constant and Macro's
*****************************************************************************/

/* left shifted by 2 to have effect of multiplication by 4 i.e. size of uint32_t */
/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
cdc_pstn_struct_t g_pstn;

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Local Variables
 *****************************************************************************/
uint8_t g_serial_state_buf[NOTIF_PACKET_SIZE+UART_BITMAP_SIZE] =
{
    NOTIF_REQUEST_TYPE,SERIAL_STATE_NOTIF,
    0x00,0x00,/*wValue*/
    0x00,0x00,/*interface - modifies*/
    UART_BITMAP_SIZE,0x00,/* wlength*/
    0x00,0x00 /*data initialized - modifies*/
};/*uart bitmap*/

uint8_t g_response_available_data[NOTIF_PACKET_SIZE] =
{
    NOTIF_REQUEST_TYPE, RESPONSE_AVAIL_NOTIF,
    0x00, 0x00,/*wValue*/
    0x00,0x00,/*interface - modifies*/
    0x00,0x00,/* wlength*/
};

#if CDC_RNDIS_SUPPORT
static uint32_t g_list_supp_oid[NUM_OIDS_SUPPORTED] =
{
    OID_GEN_SUPPORTED_LIST,
    OID_GEN_HARDWARE_STATUS,
    OID_GEN_MEDIA_SUPPORTED,
    OID_GEN_MEDIA_IN_USE,
    OID_GEN_MAXIMUM_FRAME_SIZE,
    OID_GEN_LINK_SPEED,
    OID_GEN_TRANSMIT_BLOCK_SIZE,
    OID_GEN_RECEIVE_BLOCK_SIZE,
    OID_GEN_VENDOR_ID,
    OID_GEN_VENDOR_DESCRIPTION,
    OID_GEN_CURRENT_PACKET_FILTER,
    OID_GEN_MAXIMUM_TOTAL_SIZE,
    OID_GEN_MEDIA_CONNECT_STATUS,
    OID_GEN_XMIT_OK,
    OID_GEN_RCV_OK,
    OID_GEN_XMIT_ERROR,
    OID_GEN_RCV_ERROR,
    OID_GEN_RCV_NO_BUFFER,
    OID_802_3_PERMANENT_ADDRESS,
    OID_802_3_CURRENT_ADDRESS,
    OID_802_3_MULTICAST_LIST,
    OID_802_3_MAXIMUM_LIST_SIZE,
    OID_802_3_RCV_ERROR_ALIGNMENT,
    OID_802_3_XMIT_ONE_COLLISION,
    OID_802_3_XMIT_MORE_COLLISIONS
};
#define VENDOR_INFO_SIZE        (16)
static uint8_t g_vendor_info[VENDOR_INFO_SIZE] = " FSL RNDIS PORT ";
#endif

/*****************************************************************************
* Local Functions
*****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Pstn_Init
 *
 * @brief The function initializes the Pstn Module
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param class_callback:       event callback
 *
 * @return status
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/
usb_status USB_Pstn_Init
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_application_callback_struct_t* pstn_cb
)
{
    cdc_pstn_struct_t * cdc_pstn_ptr = NULL;
    usb_status error = USB_OK;
    /* initialize the Global Variable Structure */
    cdc_pstn_ptr = &g_pstn;

    OS_Mem_zero(cdc_pstn_ptr, sizeof(cdc_pstn_struct_t));
    OS_Mem_copy(g_serial_state_buf,
                cdc_pstn_ptr->serial_state_buf,(NOTIF_PACKET_SIZE+UART_BITMAP_SIZE));

    /* save input parameters */
    cdc_pstn_ptr->pstn_callback.callback = pstn_cb->callback;
    cdc_pstn_ptr->pstn_callback.arg = (void *)pstn_cb->arg;

    cdc_obj_ptr->pstn_obj_ptr = (void *)cdc_pstn_ptr;
    cdc_obj_ptr->has_sent_state = FALSE;
#if CDC_RNDIS_SUPPORT
    /* Initially RNDIS is in Uninitialized state */
    cdc_pstn_ptr->rndis_device_state = RNDIS_UNINITIALIZED;
    cdc_pstn_ptr->rndis_hw_state = NdisHardwareStatusNotReady;
    cdc_pstn_ptr->rndis_media_connect_status = NdisMediaStateUnknown;
    cdc_pstn_ptr->rndis_dev_max_tx_size =
        cdc_obj_ptr->rndis_info.rndis_max_frame_size + RNDIS_USB_HEADER_SIZE;


    cdc_pstn_ptr->status_mutex = OS_Mutex_create();
    if(NULL == cdc_pstn_ptr->status_mutex)
    {
#if _DEBUG
        USB_PRINTF("OS_Mutex_create fail\r\n");
#endif
    }
#endif

    return error;
}

/**************************************************************************//*!
 *
 * @name  USB_Pstn_Deinit
 *
 * @brief The function initializes the Pstn Module
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 *
 * @return status
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/
usb_status USB_Pstn_Deinit
(
    cdc_device_struct_t * cdc_obj_ptr
)
{
    usb_status error = USB_OK;
#if CDC_RNDIS_SUPPORT
    cdc_pstn_struct_t * cdc_pstn_ptr = NULL;
    cdc_pstn_ptr = cdc_obj_ptr->pstn_obj_ptr;
    if(cdc_pstn_ptr->status_mutex)
    {
        if(OS_MUTEX_OK == OS_Mutex_destroy(cdc_pstn_ptr->status_mutex))
        {
            cdc_pstn_ptr->status_mutex = NULL;
        }
    }
#endif
    return error;
}

/**************************************************************************//*!
 *
 * @name  PSTN_Get_Line_Coding
 *
 * @brief  This function is called in response to GetLineCoding request
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
usb_status PSTN_Get_Line_Coding
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size
)
{
    cdc_pstn_struct_t * cdc_pstn_ptr;
    usb_status error;
    //UNUSED_ARGUMENT (size)
    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    /*  *size is equal to LINE_CODING_SIZE; */
    error = cdc_obj_ptr->class_specific_callback.callback(GET_LINE_CODING,
            cdc_pstn_ptr->current_interface,
            data,
            size,
            cdc_obj_ptr->class_specific_callback.arg);
    return error;
}

/**************************************************************************//*!
 *
 * @name  PSTN_Set_Line_Coding
 *
 * @brief  This function is called in response to SetLineCoding request
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
usb_status PSTN_Set_Line_Coding
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size
)
{
    cdc_pstn_struct_t * cdc_pstn_ptr;
    usb_status error;
    //UNUSED_ARGUMENT(data)

    *size = 0;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    /* send the data to the host */
    cdc_pstn_ptr->current_interface =  (uint8_t)setup_packet->index ;
    error = cdc_obj_ptr->class_specific_callback.callback(SET_LINE_CODING,
            cdc_pstn_ptr->current_interface,
            (uint8_t * *)&setup_packet,
            size,
            cdc_obj_ptr->class_specific_callback.arg);
    return error;
}

/**************************************************************************//*!
 *
 * @name  PSTN_Set_Ctrl_Line_State
 *
 * @brief  This function is called in response to Set Control Line State
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status PSTN_Set_Ctrl_Line_State
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size
)
{
    cdc_pstn_struct_t * cdc_pstn_ptr;
    //UNUSED_ARGUMENT(data)
    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    *size = 0;

    cdc_pstn_ptr->dte_status = (uint8_t)setup_packet->value ;
    cdc_pstn_ptr->uart_state= 0x00; /* initialize */
    if(cdc_obj_ptr->class_specific_callback.callback != NULL)
    {
        /* activate/deactivate Tx carrier */
        if(cdc_pstn_ptr->dte_status & CARRIER_ACTIVATION_CHECK)
        {
            cdc_pstn_ptr->uart_state |= UART_STATE_TX_CARRIER;
        }
        else
        {
            cdc_pstn_ptr->uart_state &= (uint16_t)~UART_STATE_TX_CARRIER;
        }

        /* activate carrier and DTE */
        if(cdc_pstn_ptr->dte_status & DTE_PRESENCE_CHECK)
        {
            cdc_pstn_ptr->uart_state |= UART_STATE_RX_CARRIER;
        }
        else
        {
            cdc_pstn_ptr->uart_state &= (uint16_t)~UART_STATE_RX_CARRIER;
        }

        /* Indicates to DCE if DTE is present or not */
        cdc_pstn_ptr->dte_present = (cdc_pstn_ptr->dte_status & DTE_PRESENCE_CHECK)?TRUE:FALSE;

        PSTN_Send_Serial_State(cdc_obj_ptr);/* send notification to host*/

        if(cdc_pstn_ptr->dte_status & CARRIER_ACTIVATION_CHECK)
        {
            cdc_obj_ptr->class_specific_callback.callback(USB_APP_CDC_CARRIER_ACTIVATED,
                    USB_REQ_VAL_INVALID,
                    NULL,
                    NULL,
                    cdc_obj_ptr->class_specific_callback.arg);
        }
        else
        {
            cdc_obj_ptr->class_specific_callback.callback(USB_APP_CDC_CARRIER_DEACTIVATED,
                    USB_REQ_VAL_INVALID,
                    NULL,
                    NULL,
                    cdc_obj_ptr->class_specific_callback.arg);
        }
        if(cdc_pstn_ptr->dte_status & DTE_PRESENCE_CHECK)
        {
            cdc_obj_ptr->class_specific_callback.callback(USB_APP_CDC_DTE_ACTIVATED,
                    USB_REQ_VAL_INVALID,
                    NULL,
                    NULL,
                    cdc_obj_ptr->class_specific_callback.arg);
        }
        else
        {
            cdc_obj_ptr->class_specific_callback.callback(USB_APP_CDC_DTE_DEACTIVATED,
                    USB_REQ_VAL_INVALID,
                    NULL,
                    NULL,
                    cdc_obj_ptr->class_specific_callback.arg);
        }
    }
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  PSTN_Send_Break
 *
 * @brief  This function is called in response to Set Config request
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : When Successfully
 *                        Others : When Error
 *
 *****************************************************************************/
usb_status PSTN_Send_Break
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size
)
{
    cdc_pstn_struct_t * cdc_pstn_ptr;
    //UNUSED_ARGUMENT (data)

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    *size = 0;
    cdc_pstn_ptr->break_duration =  setup_packet->value;
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  PSTN_Get_Comm_Feature
 *
 * @brief  This function is called in response to GetCommFeature request
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
usb_status PSTN_Get_Comm_Feature
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size
)
{
    usb_status error;
    cdc_pstn_struct_t * cdc_pstn_ptr;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    error = USB_OK;
    *size = cdc_obj_ptr->comm_feature_data_size;
    cdc_pstn_ptr->current_interface =  (uint8_t)setup_packet->index ;
    if(setup_packet->value == ABSTRACT_STATE_FEATURE)
    {

        error = cdc_obj_ptr->class_specific_callback.callback(GET_ABSTRACT_STATE,
                cdc_pstn_ptr->current_interface,
                data,
                size,
                cdc_obj_ptr->class_specific_callback.arg);
    }
    else if(setup_packet->value == COUNTRY_SETTING_FEATURE)
    {

        error = cdc_obj_ptr->class_specific_callback.callback(GET_COUNTRY_SETTING,
                cdc_pstn_ptr->current_interface,
                data,
                size,
                cdc_obj_ptr->class_specific_callback.arg);
    }
    else
    {
        *size = 0; /* for Reserved/Invalid Feature Selector Value */
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  PSTN_Set_Comm_Feature
 *
 * @brief  This function is called in response to SetCommFeature request
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
usb_status PSTN_Set_Comm_Feature
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size
)
{
    usb_status error;
    cdc_pstn_struct_t * cdc_pstn_ptr;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    error = USB_OK;
    *size = cdc_obj_ptr->comm_feature_data_size;
    cdc_pstn_ptr->current_interface =  (uint8_t)setup_packet->index ;
    if(setup_packet->value == ABSTRACT_STATE_FEATURE)
    {
        error = cdc_obj_ptr->class_specific_callback.callback(SET_ABSTRACT_STATE,
                cdc_pstn_ptr->current_interface,
                data,
                size,
                cdc_obj_ptr->class_specific_callback.arg);
    }
    else if(setup_packet->value == COUNTRY_SETTING_FEATURE)
    {
        error = cdc_obj_ptr->class_specific_callback.callback(SET_COUNTRY_SETTING,
                cdc_pstn_ptr->current_interface,
                data,
                size,
                cdc_obj_ptr->class_specific_callback.arg);
    }
    else
    {
        *size = 0; /* for Reserved/Invalid Feature Selector Value */
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  PSTN_Send_Serial_State
 *
 * @brief  This function is called to send serial state notification
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 *
 * @return NONE
 *****************************************************************************/
void PSTN_Send_Serial_State(cdc_device_struct_t * cdc_obj_ptr)
{
    cdc_pstn_struct_t * cdc_pstn_ptr;
    uint32_t val;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    /* update array for current interface */
    cdc_pstn_ptr->serial_state_buf[4] = cdc_pstn_ptr->current_interface;
    /* Lower byte of UART BITMAP */
    *(uint16_t*)&cdc_pstn_ptr->serial_state_buf[NOTIF_PACKET_SIZE+UART_BITMAP_SIZE-2] =
        cdc_pstn_ptr->uart_state;
    val = (uint32_t)(NOTIF_PACKET_SIZE + UART_BITMAP_SIZE);
    if(FALSE == cdc_obj_ptr->has_sent_state)
    {
        (void)USB_Class_CDC_Send_Data((uint32_t)cdc_obj_ptr,
                                      cdc_obj_ptr->cic_send_endpoint,cdc_pstn_ptr->serial_state_buf,val);
        cdc_obj_ptr->has_sent_state = TRUE;
    }
}

/**************************************************************************//*!
 *
 * @name  PSTN_Response_Available
 *
 * @brief  This function is called to send notification to host that a
 *         response is available
 *
 * @param cdc_obj_ptr
 *
 * @return NONE
 *****************************************************************************/
void PSTN_Response_Available(cdc_device_struct_t * cdc_obj_ptr)
{
    cdc_pstn_struct_t * cdc_pstn_ptr;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    /* update array for current interface */
    g_response_available_data[4] = cdc_pstn_ptr->current_interface;

    (void)USB_Class_CDC_Send_Data((uint32_t)cdc_obj_ptr,
                                  cdc_obj_ptr->cic_send_endpoint,
                                  g_response_available_data,NOTIF_PACKET_SIZE);
}


#if CDC_RNDIS_SUPPORT
/**************************************************************************//*!
 *
 * @name  PSTN_Rndis_Message_Set
 *
 * @brief  This function is called in response to PSTN_Rndis_Message_Set
 *
 * @param handle            handle to Identify the controller
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
usb_status PSTN_Rndis_Message_Set
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size
)
{
    uint32_t message_type;
    cdc_pstn_struct_t * cdc_pstn_ptr;
    UNUSED_ARGUMENT(data)
    UNUSED_ARGUMENT(size)
    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    cdc_pstn_ptr->current_interface =  (uint8_t)setup_packet->index ;

    if(!(cdc_pstn_ptr->current_interface <
            cdc_obj_ptr->max_supported_interfaces))
    {
#if _DEBUG
        USB_PRINTF("PSTN_Rndis_Message_Set:  %d interface not supported\n", cdc_pstn_ptr->current_interface);
#endif
        return USBERR_INVALID_REQ_TYPE;
    }

    if(setup_packet->length > MAX_EXPECTED_COMMAND_SIZE)
    {
#if _DEBUG
        USB_PRINTF("MAX_EXPECTED_COMMAND_SIZE insufficient, needed %d\n", setup_packet->length);
#endif
        return USBERR_ERROR;
    }

    /* Command data has been appended at the end of setup token in framework.c
       Copy data from that buffer to buffer in pstn.c memory for that buffer
       will be freed on completion of setup transfer*/
    OS_Mem_copy(setup_packet+1, cdc_pstn_ptr->rndis_command_ptr,
                setup_packet->length);

    message_type = USB_LONG_LE_TO_HOST(*((uint32_t*)(cdc_pstn_ptr->rndis_command_ptr)));

    if(message_type == REMOTE_NDIS_HALT_MSG)
    {
        /* No response is send to host on receiving Halt Command */
        RNDIS_Halt_Command(cdc_obj_ptr);
    }
    else
    {
        PSTN_Response_Available(cdc_obj_ptr);
    }

    if(message_type == REMOTE_NDIS_INITIALIZE_MSG)
    {
        /* Update the NDIS HW status */
        cdc_pstn_ptr->rndis_hw_state = NdisHardwareStatusInitializing;
    }

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  PSTN_Rndis_Message_Get
 *
 * @brief  This function is called in response to PSTN_Rndis_Message_Get
 *
 * @param handle            handle to Identify the controller
 * @param setup_packet:     setup packet received
 * @param data:             data to be send back
 * @param size:             size to be returned
 *
 * @return status:
 *                        USB_OK : Always
 *
 *****************************************************************************/
usb_status PSTN_Rndis_Message_Get
(
    cdc_device_struct_t * cdc_obj_ptr,
    usb_setup_struct_t * setup_packet,
    uint8_t * *data,
    uint32_t *size
)
{
    uint32_t* message_type_ptr;
    uint16_t setup_pkt_len =  setup_packet->length;
    cdc_pstn_struct_t * cdc_pstn_ptr;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    *size = 0;

    message_type_ptr = (uint32_t*)(cdc_pstn_ptr->rndis_command_ptr);
    /* we can avoid one swap operation by using message_type_ptr in
       PSTN_Rndis_Message_Set instead of message_type, but this gives
       cleaner implementation as all manipulations and parsing on command
       are done in this function */
    *message_type_ptr = USB_LONG_LE_TO_HOST(*message_type_ptr);

    switch(*message_type_ptr)
    {
    case REMOTE_NDIS_INITIALIZE_MSG:
        /* Preparing for response to REMOTE_NDIS_INITIALIZE_MSG command
           i.e. REMOTE_NDIS_INITIALIZE_CMPLT data */
        RNDIS_Initialize_Command(cdc_obj_ptr,data,size);
        break;
    case REMOTE_NDIS_QUERY_MSG:
        /* Preparing for response to REMOTE_NDIS_QUERY_MSG command
           i.e. REMOTE_NDIS_QUERY_CMPLT data */
        /* correct the endianness of OID */
        *((uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 3) = USB_LONG_LE_TO_HOST(*((uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 3));
        RNDIS_Query_Command(cdc_obj_ptr,data,size);
        break;
    case REMOTE_NDIS_SET_MSG :
        /* Preparing for response to REMOTE_NDIS_SET_MSG command
           i.e. REMOTE_NDIS_SET_CMPLT data */
        /* Correct the endianness of OID and InformationBufferLength
           and InformationBufferOffset*/
        *((uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 3) = USB_LONG_LE_TO_HOST(*((uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 3));
        *((uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 4) = USB_LONG_LE_TO_HOST(*((uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 4));
        *((uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 5) = USB_LONG_LE_TO_HOST(*((uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 5));
        RNDIS_Set_Command(cdc_obj_ptr,data,size);
        break;
    case REMOTE_NDIS_RESET_MSG :
        /* Preparing for response to REMOTE_NDIS_RESET_MSG command
           i.e. REMOTE_NDIS_RESET_CMPLT data */
        RNDIS_Reset_Command(cdc_obj_ptr,data,size);
        break;
    case REMOTE_NDIS_INDICATE_STATUS_MSG :
        /* Preparing for response to REMOTE_NDIS_INDICATE_STATUS_MSG
           command */
        RNDIS_Indicate_Status_Command(cdc_obj_ptr,data,size);
        break;
    case REMOTE_NDIS_KEEPALIVE_MSG :
        /* Preparing for response to REMOTE_NDIS_KEEPALIVE_MSG command
           i.e. REMOTE_NDIS_KEEPALIVE_CMPLT data */
        RNDIS_Keepalive_Command(cdc_obj_ptr,data,size);
        break;
    default :
#if _DEBUG
        USB_PRINTF("UNSUPPORTED RNDIS Command : 0x%x\n",*message_type_ptr);
#endif
        return USBERR_INVALID_REQ_TYPE;
    }

    if(*size > MAX_EXPECTED_RESPONSE_SIZE)
    {
#if _DEBUG
        USB_PRINTF("MAX_EXPECTED_RESPONSE_SIZE insufficient\n");
#endif
    }

    if(setup_pkt_len < *size)
    {
#if _DEBUG
        USB_PRINTF("Error : Device has more data to send than Host needs.\n");
#endif
        return USBERR_INVALID_REQ_TYPE;
    }
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  RNDIS_Initialize_Command
 *
 * @brief  This function is called to initialize the RNDIS device and prepare
 *         data to be sent to host as Remote_NDIS_INITIALIZE_CMPLT
 *
 * @param handle   handle to Identify the controller
 * @param data:    data to be send back
 * @param size:    size to be returned
 *
 * @return NONE
 *
 *****************************************************************************/
void RNDIS_Initialize_Command
(
    cdc_device_struct_t * cdc_obj_ptr,
    uint8_t * *data,
    uint32_t *size
)
{
    cdc_pstn_struct_t * cdc_pstn_ptr;
    uint32_t max_tx_size ;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    /* preparing for Byte 0-3 : MessageType*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr) = USB_LONG_LE_TO_HOST_CONST(REMOTE_NDIS_INITIALIZE_CMPLT);

    /* preparing for Byte 4-7 : MessageLength*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 1) = USB_LONG_LE_TO_HOST_CONST(RESPONSE_RNDIS_INITIALIZE_MSG_SIZE);

    /* preparing for Byte 8-11 : RequestID*/
    OS_Mem_copy(((uint32_t*)(cdc_pstn_ptr->rndis_command_ptr) + 2),
                ((uint32_t*)cdc_pstn_ptr->response_data_ptr + 2),sizeof(uint32_t));

    /* preparing for Byte 12-15 : Status*/
    if(cdc_pstn_ptr->rndis_device_state == RNDIS_UNINITIALIZED)
    {
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 3) = USB_LONG_LE_TO_HOST_CONST(RNDIS_STATUS_SUCCESS);
    }
    else
    {
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 3) = USB_LONG_LE_TO_HOST_CONST(RNDIS_STATUS_FAILURE);
    }

    /* preparing for Byte 16-19 ; MajorVersion*/
    /* We are currently returning the same driver version to host in
       response to initialization command as reported by host driver */
    OS_Mem_copy(((uint32_t*)(cdc_pstn_ptr->rndis_command_ptr) + 3),
                ((uint32_t*)cdc_pstn_ptr->response_data_ptr + 4),sizeof(uint32_t));

    /* preparing for Byte 20-23 : MinorVersion*/
    OS_Mem_copy(((uint32_t*)(cdc_pstn_ptr->rndis_command_ptr) + 4),
                ((uint32_t*)cdc_pstn_ptr->response_data_ptr + 5),sizeof(uint32_t));

    /* preparing for Byte 24-27 : DeviceFlags*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST_CONST(RNDIS_DF_CONNECTIONLESS);

    /* preparing for Byte 28-31 : Medium*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 7) = USB_LONG_LE_TO_HOST(NdisMedium802_3);

    /* preparing for Byte 32-35 : MaxPacketsPerTransfer*/
    /* We are not implementing multiple packet transfer support in our RNDIS */
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 8) = USB_LONG_LE_TO_HOST_CONST(RNDIS_SINGLE_PACKET_TRANSFER);

    /* preparing for Byte 36-39 : MaxTransferSize*/
    /* We are currently returning the same max transfer size to host
       as it send to device in its corresponding filed in
       initialization command */
    cdc_pstn_ptr->rndis_host_max_tx_size = USB_LONG_LE_TO_HOST(*((uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 5));
    max_tx_size = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->rndis_dev_max_tx_size);
    OS_Mem_copy(&max_tx_size,
                ((uint32_t*)cdc_pstn_ptr->response_data_ptr + 9),sizeof(uint32_t));

    /* preparing for Byte 40-43 : PacketAlignmentFactor*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 10) = USB_LONG_LE_TO_HOST_CONST(PACKET_ALIGNMENT_FACTOR);

    /* preparing for Byte 44-47 : PacketAlignmentFactor*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 11) = AF_LIST_OFFSET;

    /* preparing for Byte 48-51 : PacketAlignmentFactor*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 12) = AF_LIST_SIZE;

    *data = cdc_pstn_ptr->response_data_ptr;
    *size = RESPONSE_RNDIS_INITIALIZE_MSG_SIZE;

    /* initializing RNDIS variables */
    cdc_pstn_ptr->rndis_device_state = RNDIS_INITIALIZED;
    cdc_pstn_ptr->rndis_hw_state = NdisHardwareStatusReady;
    cdc_pstn_ptr->rndis_media_connect_status = NdisMediaStateDisconnected;
    cdc_pstn_ptr->num_frames_tx_ok = 0;
    cdc_pstn_ptr->num_frames_rx_ok = 0;
    cdc_pstn_ptr->num_frames_tx_error = 0;
    cdc_pstn_ptr->num_frames_rx_error = 0;
    cdc_pstn_ptr->num_recv_frames_missed = 0;
    cdc_pstn_ptr->num_recv_frames_alignment_error = 0;
    cdc_pstn_ptr->num_frames_tx_one_collision = 0;
    cdc_pstn_ptr->num_frames_tx_many_collision = 0;
}

/**************************************************************************//*!
 *
 * @name  RNDIS_Keepalive_Command
 *
 * @brief  This function is called to check the health of RNDIS device and prepare
 *         data to be sent to host as REMOTE_NDIS_KEEPALIVE_CMPLT
 *
 * @param handle   handle to Identify the controller
 * @param data:    data to be send back
 * @param size:    size to be returned
 *
 * @return NONE
 *
 *****************************************************************************/
void RNDIS_Keepalive_Command
(
    cdc_device_struct_t * cdc_obj_ptr,
    uint8_t * *data,
    uint32_t *size
)
{
    cdc_pstn_struct_t * cdc_pstn_ptr;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    /* preparing for Byte 0-3 : MessageType*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr) = USB_LONG_LE_TO_HOST_CONST(REMOTE_NDIS_KEEPALIVE_CMPLT);

    /* preparing for Byte 4-7 : MessageLength*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 1) = USB_LONG_LE_TO_HOST_CONST(RESPONSE_RNDIS_KEEPALIVE_MSG_SIZE);

    /* preparing for Byte 8-11 : RequestID*/
    OS_Mem_copy(((uint32_t*)(cdc_pstn_ptr->rndis_command_ptr) + 2),
                ((uint32_t*)cdc_pstn_ptr->response_data_ptr + 2),sizeof(uint32_t));

    /* preparing for Byte 12-15 : Status*/
    USB_Cdc_Mutex_Lock(cdc_pstn_ptr->status_mutex);
    if(cdc_pstn_ptr->rndis_device_state == RNDIS_DATA_INITIALIZED)
    {
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 3) = USB_LONG_LE_TO_HOST_CONST(RNDIS_STATUS_SUCCESS);
    }
    else
    {
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 3) = USB_LONG_LE_TO_HOST_CONST(RNDIS_STATUS_FAILURE);
    }
    USB_Cdc_Mutex_Unlock(cdc_pstn_ptr->status_mutex);

    *data = cdc_pstn_ptr->response_data_ptr;
    *size = RESPONSE_RNDIS_KEEPALIVE_MSG_SIZE;
}

/**************************************************************************//*!
 *
 * @name  RNDIS_Query_Command
 *
 * @brief  This function is called to query the RNDIS device for its
 *         characteristics or statistics information or status and prepare
 *         data to be sent to host as Remote_NDIS_Query_CMPLT
 *
 * @param handle   handle to Identify the controller
 * @param data:    data to be send back
 * @param size:    size to be returned
 *
 * @return NONE
 *
 *****************************************************************************/
void RNDIS_Query_Command
(
    cdc_device_struct_t * cdc_obj_ptr,
    uint8_t * *data,
    uint32_t *size
)
{
    uint32_t* oid_ptr;
    uint8_t i;
    uint32_t info_buf_len = 0;
    uint32_t return_status = RNDIS_STATUS_SUCCESS;
    cdc_pstn_struct_t * cdc_pstn_ptr;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    oid_ptr = (uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 3;

    /* preparing for Byte 0-3 : MessageType*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr) = USB_LONG_LE_TO_HOST_CONST(REMOTE_NDIS_QUERY_CMPLT);

    /* preparing for Byte 8-11 : RequestID*/
    OS_Mem_copy(((uint32_t*)(cdc_pstn_ptr->rndis_command_ptr) + 2),
                ((uint32_t*)cdc_pstn_ptr->response_data_ptr + 2),sizeof(uint32_t));


    /* preparing for Byte 20-23 : InformationBufferOffset*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 5) = USB_LONG_LE_TO_HOST_CONST(0x00000010);

    switch(*oid_ptr)
    {
    case OID_GEN_SUPPORTED_LIST :
        /* List of supported OIDs - Query Mandatory - General Operational Characteristic */
        for(i=0; i<NUM_OIDS_SUPPORTED; i++)
        {
            /* change the endianness of data before sending on USB Bus */
            g_list_supp_oid[i] = USB_LONG_LE_TO_HOST(g_list_supp_oid[i]);
        }
        info_buf_len = sizeof(g_list_supp_oid);
        OS_Mem_copy(g_list_supp_oid,
                    (uint32_t*)cdc_pstn_ptr->response_data_ptr + 6, info_buf_len);
        break;
    case OID_GEN_HARDWARE_STATUS :
        /* Hardware status  - Query Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->rndis_hw_state);
        break;
    case OID_GEN_MEDIA_SUPPORTED :
        /* Media types supported (encoded) - Query Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(NdisMedium802_3);
        break;
    case OID_GEN_MEDIA_IN_USE :
        /* Media types in use (encoded) - Query Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(NdisMedium802_3);
        break;
    case OID_GEN_MAXIMUM_FRAME_SIZE :
        /* Maximum in bytes, frame size - Query Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_obj_ptr->rndis_info.rndis_max_frame_size);
        break;
    case OID_GEN_LINK_SPEED :
        /* Link speed in units of 100 bps - Query Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        if(cdc_obj_ptr->class_specific_callback.callback != NULL)
        {
            cdc_obj_ptr->class_specific_callback.callback(USB_APP_GET_LINK_SPEED,
                    USB_REQ_VAL_INVALID,
                    NULL,
                    ((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6),
                    cdc_obj_ptr->class_specific_callback.arg);
        }

        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(*((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6));
        break;
    case OID_GEN_TRANSMIT_BLOCK_SIZE :
        /* Minimum amount of storage, in bytes, that a single packet
           occupies in the transmit buffer space of the NIC -
           Query Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST((uint32_t)cdc_obj_ptr->dic_send_pkt_size);
        break;
    case OID_GEN_RECEIVE_BLOCK_SIZE :
        /* Amount of storage, in bytes, that a single packet occupies in
           the receive buffer space of the NIC - Query Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST((uint32_t)cdc_obj_ptr->dic_recv_pkt_size);
        break;
    case OID_GEN_VENDOR_ID :
        /* Vendor NIC code - Query Mandatory - General Operational Characteristic*/
        /* This object specifies a three-byte IEEE-registered vendor code,
           followed by a single byte that the vendor assigns to identify
           a particular NIC. The IEEE code uniquely identifies the vendor
           and is the same as the three bytes appearing at the beginning
           of the NIC hardware address.Vendors without an IEEE-registered
           code should use the value 0xFFFFFF. */
        info_buf_len = sizeof(uint32_t);

        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST_CONST(
                    (uint32_t) (((uint32_t) RNDIS_VENDOR_ID << 8) | (uint32_t) NIC_IDENTIFIER_VENDOR));
        break;
    case OID_GEN_VENDOR_DESCRIPTION :
        /* Vendor network card description - Query Mandatory - General Operational Characteristic*/
        info_buf_len = VENDOR_INFO_SIZE;
        OS_Mem_copy(g_vendor_info, (uint32_t*)cdc_pstn_ptr->response_data_ptr + 6, info_buf_len);
        break;
    case OID_GEN_CURRENT_PACKET_FILTER :
        /* Current packet filter (encoded) - Query and Set Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->rndis_packet_filter);
        break;
    case OID_GEN_MAXIMUM_TOTAL_SIZE :
        /* Maximum total packet length in bytes - Query Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->rndis_dev_max_tx_size);
        break;
    case OID_GEN_MEDIA_CONNECT_STATUS :
        /* Whether the NIC is connected to the network - Query Mandatory - General Operational Characteristic*/
    {
        bool media_connected;
        /* Whether the NIC is connected to the network - Query Mandatory - General Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        if(cdc_obj_ptr->class_specific_callback.callback != NULL)
        {
            cdc_obj_ptr->class_specific_callback.callback(USB_APP_GET_LINK_STATUS,
                    USB_REQ_VAL_INVALID,
                    NULL,
                    (uint32_t*)(&media_connected),
                    cdc_obj_ptr->class_specific_callback.arg);
        }
        if(media_connected)
        {
            cdc_pstn_ptr->rndis_media_connect_status = NdisMediaStateConnected;
        }
        else
        {
            cdc_pstn_ptr->rndis_media_connect_status = NdisMediaStateDisconnected;
        }
        *((uint32_t *)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->rndis_media_connect_status);
    }
    break;
    case OID_GEN_XMIT_OK :
        /* Frames transmitted without errors - Query Mandatory - General Statistics*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->num_frames_tx_ok);
        break;
    case OID_GEN_RCV_OK :
        /* Frames received without errors - Query Mandatory - General Statistics*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->num_frames_rx_ok);
        break;
    case OID_GEN_XMIT_ERROR :
        /* Frames not transmitted or transmitted with errors - Query Mandatory - General Statistics*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->num_frames_tx_error);
        break;
    case OID_GEN_RCV_ERROR :
        /* Frames received with errors - Query Mandatory - General Statistics*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->num_frames_rx_error);
        break;
    case OID_GEN_RCV_NO_BUFFER :
        /* Frame missed, no buffers - Query Mandatory - General Statistics*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->num_recv_frames_missed);
        break;
    case OID_802_3_PERMANENT_ADDRESS :
        /* Permanent station address - Query Mandatory - Ethernet Operational Characteristic*/
        info_buf_len = RNDIS_ETHER_ADDR_SIZE;
        OS_Mem_copy(cdc_obj_ptr->rndis_info.mac_address,
                    (uint8_t *)((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6),
                    info_buf_len);

        break;
    case OID_802_3_CURRENT_ADDRESS :
        /* Current station address - Query Mandatory - Ethernet Operational Characteristic*/
        info_buf_len = RNDIS_ETHER_ADDR_SIZE;
        OS_Mem_copy(cdc_obj_ptr->rndis_info.mac_address,
                    (uint8_t *)((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6),
                    info_buf_len);

        break;
    case OID_802_3_MULTICAST_LIST :
        /* Current multicast address list - Query and Set Mandatory - Ethernet Operational Characteristic*/
        info_buf_len = RNDIS_ETHER_ADDR_SIZE;
        /* Currently Our RNDIS driver does not support multicast addressing */
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST_CONST(0x00000000);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 7) = USB_LONG_LE_TO_HOST_CONST(0x00000000);
        break;
    case OID_802_3_MAXIMUM_LIST_SIZE :
        /* Maximum size of multicast address list - Query Mandatory - Ethernet Operational Characteristic*/
        info_buf_len = sizeof(uint32_t);
        /* Currently Our RNDIS driver does not support multicast addressing */
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST_CONST(RNDIS_MULTICAST_LIST_SIZE);
        break;
    case OID_802_3_RCV_ERROR_ALIGNMENT :
        /* Frames received with alignment error - Query Mandatory - Ethernet Statistics*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->num_recv_frames_alignment_error);
        break;
    case OID_802_3_XMIT_ONE_COLLISION :
        /* Frames transmitted with one collision - Query Mandatory - Ethernet Statistics*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->num_frames_tx_one_collision);
        break;
    case OID_802_3_XMIT_MORE_COLLISIONS :
        /* Frames transmitted with more than one collision - Query Mandatory - Ethernet Statistics*/
        info_buf_len = sizeof(uint32_t);
        *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 6) = USB_LONG_LE_TO_HOST(cdc_pstn_ptr->num_frames_tx_many_collision);
        break;
    default :
#if _DEBUG
        USB_PRINTF("OID 0x%x NOT SUPPORTED(QUERY)\n",*oid_ptr);
#endif
        return_status = RNDIS_STATUS_NOT_SUPPORTED;
        break;
    }

    /* preparing for Byte 12-15 : Status*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 3) = USB_LONG_LE_TO_HOST(return_status);

    *size = RESPONSE_RNDIS_QUERY_MSG_SIZE + info_buf_len;
    /* preparing for Byte 4-7 : MessageLength*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 1) = USB_LONG_LE_TO_HOST(*size);
    /* preparing for Byte 16-19 : InformationBufferLength*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 4) = USB_LONG_LE_TO_HOST(info_buf_len);
    *data = cdc_pstn_ptr->response_data_ptr;
}

/**************************************************************************//*!
 *
 * @name  RNDIS_Set_Command
 *
 * @brief  This function is called to Configure the operational parameters of
 *         RNDIS device.
 *
 * @param handle   handle to Identify the controller
 * @param data:    data to be send back
 * @param size:    size to be returned
 *
 * @return NONE
 *
 *****************************************************************************/
void RNDIS_Set_Command
(
    cdc_device_struct_t * cdc_obj_ptr,
    uint8_t * *data,
    uint32_t *size
)
{
    uint32_t* oid_ptr;
    uint32_t* info_buf_len_ptr;
    uint32_t* info_buf_offset_ptr;
    uint32_t return_status = RNDIS_STATUS_SUCCESS;
    cdc_pstn_struct_t * cdc_pstn_ptr;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

    oid_ptr = (uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 3;
    info_buf_len_ptr = (uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 4;
    info_buf_offset_ptr = (uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 5;

    /* preparing for Byte 0-3 : MessageType*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr) = USB_LONG_LE_TO_HOST_CONST(REMOTE_NDIS_SET_CMPLT);

    *size = RESPONSE_RNDIS_SET_MSG_SIZE;
    /* preparing for Byte 4-7 : MessageLength*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 1) = USB_LONG_LE_TO_HOST(*size);

    /* preparing for Byte 8-11 : RequestID*/
    OS_Mem_copy(((uint32_t*)(cdc_pstn_ptr->rndis_command_ptr) + 2),
                ((uint32_t*)cdc_pstn_ptr->response_data_ptr + 2),sizeof(uint32_t));

    switch(*oid_ptr)
    {
    case OID_GEN_CURRENT_PACKET_FILTER :
        /* Current packet filter (encoded) - Query and Set Mandatory - General Operational Characteristic*/
        if(*info_buf_len_ptr != 4 )
        {
            return_status = RNDIS_STATUS_INVALID_DATA;
        }
        else
        {
            uint32_t media_connected = 0;

            cdc_pstn_ptr->rndis_packet_filter = USB_LONG_LE_TO_HOST( *((uint32_t*)((uint8_t *)((uint32_t*)
                                                cdc_pstn_ptr->rndis_command_ptr + 2) + *info_buf_offset_ptr)));
            if(cdc_obj_ptr->class_specific_callback.callback != NULL)
            {
                cdc_obj_ptr->class_specific_callback.callback(USB_APP_GET_LINK_STATUS,
                        USB_REQ_VAL_INVALID,
                        NULL,
                        (&media_connected),
                        cdc_obj_ptr->class_specific_callback.arg);
            }

            USB_Cdc_Mutex_Lock(cdc_pstn_ptr->status_mutex);
            if((cdc_pstn_ptr->rndis_packet_filter)&&(media_connected == 1))
            {
                cdc_pstn_ptr->rndis_device_state = RNDIS_DATA_INITIALIZED;
                cdc_pstn_ptr->rndis_media_connect_status = NdisMediaStateConnected;
            }
            else
            {
                cdc_pstn_ptr->rndis_device_state = RNDIS_INITIALIZED;
                cdc_pstn_ptr->rndis_media_connect_status = NdisMediaStateDisconnected;
            }
            USB_Cdc_Mutex_Unlock(cdc_pstn_ptr->status_mutex);
        }
        break;
    case OID_802_3_MULTICAST_LIST :
        /* Current multicast address list - Query and Set Mandatory - Ethernet Operational Characteristic*/
        if(*info_buf_len_ptr != RNDIS_ETHER_ADDR_SIZE)
        {
            return_status = RNDIS_STATUS_INVALID_DATA;
        }
        else
        {
            uint64_t multi_cast_list;
            multi_cast_list = *((uint64_t *)((uint8_t *)((uint32_t*)
                                             cdc_pstn_ptr->rndis_command_ptr + 2) + *info_buf_offset_ptr));
            if(multi_cast_list)
            {
                /* Currently Our RNDIS driver does not support multicast addressing */
                return_status = RNDIS_STATUS_NOT_SUPPORTED;
            }
        }

        break;
    default :
#if _DEBUG
        USB_PRINTF("OID 0x%x NOT SUPPORTED(SET)\n",*oid_ptr);
#endif
        return_status = RNDIS_STATUS_NOT_SUPPORTED;
        break;
    }
    /* preparing for Byte 12-15 : Status*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 3) = USB_LONG_LE_TO_HOST(return_status);
    *data = cdc_pstn_ptr->response_data_ptr;
}

/**************************************************************************//*!
 *
 * @name  RNDIS_Reset_Command
 *
 * @brief  This function is called to soft reset the RNDIS device.
 *
 * @param handle   handle to Identify the controller
 * @param data:    data to be send back
 * @param size:    size to be returned
 *
 * @return NONE
 *
 *****************************************************************************/
void RNDIS_Reset_Command
(
    cdc_device_struct_t * cdc_obj_ptr,
    uint8_t * *data,
    uint32_t *size
)
{
//    uint32_t* oid_ptr;
    cdc_pstn_struct_t * cdc_pstn_ptr;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

//    oid_ptr = (uint32_t*)cdc_pstn_ptr->rndis_command_ptr + 3;

    /* preparing for Byte 0-3 : MessageType*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr) = USB_LONG_LE_TO_HOST_CONST(REMOTE_NDIS_RESET_CMPLT);

    *size = RESPONSE_RNDIS_RESET_MSG_SIZE;
    /* preparing for Byte 4-7 : MessageLength*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 1) = USB_LONG_LE_TO_HOST(*size);

    /* preparing for Byte 8-11 : Status*/
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 2) = USB_LONG_LE_TO_HOST_CONST(RNDIS_STATUS_SUCCESS);

    /* preparing for Byte 12-15 : AddressingReset*/
    /* No need for host to resend addressing information */
    *((uint32_t*)cdc_pstn_ptr->response_data_ptr + 3) = USB_LONG_LE_TO_HOST_CONST(0x00000000);

    *data = cdc_pstn_ptr->response_data_ptr;
    USB_Cdc_Mutex_Lock(cdc_pstn_ptr->status_mutex);
    cdc_pstn_ptr->rndis_hw_state = NdisHardwareStatusReset;
    cdc_pstn_ptr->rndis_device_state = RNDIS_UNINITIALIZED;
    cdc_pstn_ptr->rndis_media_connect_status = NdisMediaStateUnknown;
    USB_Cdc_Mutex_Unlock(cdc_pstn_ptr->status_mutex);
}

/**************************************************************************//*!
 *
 * @name  RNDIS_Indicate_Status_Command
 *
 * @brief  Used to indicate change in status of device
 *
 * @param handle   handle to Identify the controller
 * @param data:    data to be send back
 * @param size:    size to be returned
 *
 * @return NONE
 *
 *****************************************************************************/
void RNDIS_Indicate_Status_Command
(
    cdc_device_struct_t * cdc_obj_ptr,
    uint8_t * *data,
    uint32_t *size
)
{
    UNUSED_ARGUMENT(cdc_obj_ptr)
    UNUSED_ARGUMENT(data)
    UNUSED_ARGUMENT(size)
    return;
}

/**************************************************************************//*!
 *
 * @name  RNDIS_Halt_Command
 *
 * @brief  This function is called to halt the RNDIS device.
 *         i.e. to terminate the network connection
 *
 * @param handle   handle to Identify the controller
 * @param data:    data to be send back
 * @param size:    size to be returned
 *
 * @return NONE
 *
 *****************************************************************************/
void RNDIS_Halt_Command(cdc_device_struct_t * cdc_obj_ptr)
{
    cdc_pstn_struct_t * cdc_pstn_ptr;
    uint8_t index, ep_num;
    uint32_t ep_count;

    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;

#if _DEBUG
    USB_PRINTF("RNDIS_Halt_Command\n");
#endif
    USB_Cdc_Mutex_Lock(cdc_pstn_ptr->status_mutex);
    cdc_pstn_ptr->rndis_device_state = RNDIS_UNINITIALIZED;
    cdc_pstn_ptr->rndis_media_connect_status = NdisMediaStateDisconnected;
    cdc_pstn_ptr->rndis_hw_state = NdisHardwareStatusClosing;
    cdc_pstn_ptr->rndis_hw_state = NdisHardwareStatusNotReady;
    USB_Cdc_Mutex_Unlock(cdc_pstn_ptr->status_mutex);
    /* Clear the queue */

    USB_Cdc_Get_Desc_Info(cdc_obj_ptr, USB_CDC_EP_COUNT, &ep_count);
    for(ep_num = 1; ep_num <= ep_count; ep_num++)
    {
        index = USB_Map_Ep_To_Struct_Index(cdc_obj_ptr, ep_num);
        USB_Class_CDC_Cancel((uint32_t)cdc_obj_ptr, ep_num, cdc_obj_ptr->ep[index].type, cdc_obj_ptr->ep[index].direction);
    }
}

/**************************************************************************//*!
 *
 * @name  RNDIS_Get_Device_Status
 *
 * @brief The function returns the RNDIS device status
 *
 * @param cdc_obj_ptr :   Pointer to CDC class object.
 *
 * @return status
 *         USB_OK           : When Successfully
 *         Others           : Errors
 *****************************************************************************/
uint8_t RNDIS_Get_Device_Status
(
    cdc_device_struct_t * cdc_obj_ptr
)
{
    uint8_t status;
    cdc_pstn_struct_t * cdc_pstn_ptr;
    cdc_pstn_ptr = (cdc_pstn_struct_t *)cdc_obj_ptr->pstn_obj_ptr;
    USB_Cdc_Mutex_Lock(cdc_pstn_ptr->status_mutex);

    status = cdc_pstn_ptr->rndis_device_state;

    USB_Cdc_Mutex_Unlock(cdc_pstn_ptr->status_mutex);

    return status;
}

#endif/* rndis support */

#endif /*CDC_CONFIG*/
/* EOF */
