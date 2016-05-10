/**HEADER**********************************************************************
 *
 * Copyright (c) 2009, 2013 - 2015 Freescale Semiconductor;
 * All Rights Reserved
 *
 *******************************************************************************
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
 * $FileName: khci_dev.c$
 * $Version :
 * $Date    :
 *
 * Comments:
 *
 *   This file contains the main usbfs USB Device Controller interface
 *   functions.
 *
 *END************************************************************************/

/******************************************************************************
 *               BUFFER DISCRIPTOR TABLE (BDT) DISCRIPTION                    *
 ******************************************************************************/
/**
 * The USB-FS implements a Buffer Descriptor Table (BDT) in system memory. The
 * BDT resides on a 512 byte boundary in system memory and is pointed to by the
 * BDT Page Registers. Every endpoint direction requires two eight-byte Buffer
 * Descriptor entries.Therefore, a system with 16 fully bidirectional endpoints
 * would require 512 bytes of system memory to implement the BDT.The two Buffer
 * Descriptor (BD) entries allows for an EVEN BD and ODD BD entry for each
 * endpoint direction. This allows the microprocessor to process one BD while
 * the USB-FS is processing the other BD. Double buffering BDs in this way
 * allows the USB-FS to easily transfer data at the maximum throughput provided
 * by USB.
 *
 * Because the buffers are shared between the microprocessor and the USB-FS a
 * simple semaphore mechanism is used to distinguish who is allowed to update
 * the BDT and buffers in system memory. A semaphore bit, the OWN bit, is
 * cleared to 0 when the BD entry is owned by the microprocessor. The
 * microprocessor is allowed read and write access to the BD entry and the
 * buffer in system memory when the OWN bit is 0.
 * When the OWN bit is set to 1, the BD entry and the buffer in system memory
 * are owned by the USB-FS. The USB-FS now has full read and write access and
 * the microprocessor should not modify the BD or its corresponding data buffer.
 * The BD also contains indirect address pointers to where the actual buffer
 * resides in system memory.
 ******************************************************************************
 *                 BUFFER DISCRIPTOR FORMAT DISCRIPTION
 ******************************************************************************
 * The Buffer Descriptors have different meaning based on who is reading the BD
 * in memory.The USB-FS Controller uses the data stored in BDs to determine:
 *
 *       # Who owns the buffer in system memory
 *       # Data0 or Data1 PID
 *       # Release Own upon packet completion
 *       # No address increment (FIFO Mode)
 *       # Data toggle synchronization enable
 *       # How much data is to be transmitted or received
 *       # Where the buffer resides in system memory
 *
 * While the microprocessor uses the data stored in the BDs to determine:
 *       # Who owns the buffer in system memory
 *       # Data0 or Data1 PID
 *       # The received TOKEN PID
 *       # How much data was transmitted or received
 *       # Where the buffer resides in system memory
 *
 *    ------ ------ ------ ------ -------- ---------- ---------- ---------- ---------- ---------- ----------
 *   |31-26 |25-16 | 15-8 |  7   |   6    |   5      |   4      |   3      |   2      |   1      |   0      |
 *   |RSVD  | BC   | RSVD | OWN  |DATA0/1 |TOK_PID[3]|TOK_PID[2]|TOK_PID[1]|TOK_PID[0]|TOK_PID[n]| reserved |
 *    ------ ------ ------ ------ -------- ---------- ---------- ---------- ---------- ---------- ----------
 *   |                             ADDRESS[31--0]                                                           |
 *   |                                                                                                      |
 *    -------------------------------------------------------------------------------------------------------
 *
 * This Buffer Descriptor table is represented by the variable "BDT_BASE"
 * defined in file usbfs_dev_main.h. Macros such as "BD_ADDR_RX" and
 * "BD_ADDR_TX" is used to manipulate the address field and Macros such as
 * BD_CTRL_RX and BD_CTRL_TX is used to manipulate the control fields.
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#if USBCFG_DEV_KHCI
#include "usb.h"
#include "usb_device_stack_interface.h"
#include "khci_dev.h"
#include "khci_dev_misc.h"
#include "fsl_usb_khci_hal.h"
#ifdef   USBCFG_OTG
#include "usb_otg_main.h"
#include "usb_otg_private.h"
#endif

/****************************************************************************
 * Global Variables
 ****************************************************************************/
static uint8_t *bdt;

#if (FSL_FEATURE_USB_KHCI_USB_RAM == 0)
#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK))
#if defined( __ICCARM__ )
    #pragma data_alignment=512
    __no_init uint8_t g_khci_bdt_buffer[512];
#elif defined (__CC_ARM) || defined(__GNUC__)
    __attribute__((aligned(512))) uint8_t g_khci_bdt_buffer[512];
#else
    #error Unsupported compiler, please use IAR, Keil or arm gcc compiler and rebuild the project.
#endif
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    uint8_t*                g_khci_bdt_ptr = NULL;
#endif
#endif

#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK))
    static usb_device_khci_data_t g_khci_data;
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    usb_device_khci_data_t* g_khci_data_ptr = NULL;
#endif

static bool g_zero_pkt_send = FALSE;

static usb_khci_dev_state_struct_t g_khci_dev[USBCFG_DEV_KHCI_NUM];

#if USBCFG_KHCI_4BYTE_ALIGN_FIX
static uint8_t *_usb_khci_dev_swap_buf_ptr = NULL;
#endif

extern usb_status _usb_device_call_service(uint8_t type, usb_event_struct_t* event);
extern uint32_t soc_get_usb_base_address(uint8_t controller_id);

#ifdef USBCFG_OTG
extern usb_otg_handle * g_usb_otg_handle;
#endif
extern uint8_t soc_get_usb_vector_number(uint8_t controller_id);
#if USBCFG_DEV_DETACH_ENABLE
/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_dci_khci_detach
 *  Returned Value : void
 *  Comments       :
 *        this function is called if device known it's detached.
 *
 *END*-----------------------------------------------------------------*/
void usb_dci_khci_detach(void)
{
    usb_event_struct_t event;
    usb_khci_dev_state_struct_t* state_ptr;
    state_ptr = (usb_khci_dev_state_struct_t*)(&g_khci_dev[0]);

    /* Initialize the event structure to be passed to the upper layer*/
    event.handle = (usb_device_handle)state_ptr->upper_layer_handle;
    event.ep_num = 0;
    event.setup = 0;
    event.direction = 0;

    /* propagate control to upper layers for processing */
    _usb_device_call_service(USB_SERVICE_DETACH, &event);
}
#endif

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_dci_khci_free_xd
 *  Returned Value : void
 *  Comments       :
 *        Enqueues a XD onto the free XD ring.
 *
 *END*-----------------------------------------------------------------*/
void usb_dci_khci_free_xd
(
    usb_device_handle handle,
    /* [IN] the dTD to enqueue */
    xd_struct_t* xd_ptr
)
{ /* Body */
    usb_khci_dev_state_struct_t* usb_dev_ptr = (usb_khci_dev_state_struct_t*)handle;

    /*
     ** This function can be called from any context, and it needs mutual
     ** exclusion with itself.
     */
    OS_Lock();

    /*
     ** Add the XD to the free XD queue (linked via PRIVATE) and
     ** increment the tail to the next descriptor
     */
    if (usb_dev_ptr->xd_head == NULL)
    {
        usb_dev_ptr->xd_head = xd_ptr;
    }
    else
    {
        usb_dev_ptr->xd_tail->next = xd_ptr;
    }
    usb_dev_ptr->xd_tail = xd_ptr;
    xd_ptr->next = NULL;
    usb_dev_ptr->xd_entries++;

    OS_Unlock();
} /* Endbody */

/*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_dci_khci_get_xd
 *  Returned Value : void
 *  Comments       :
 *        get an XD from the free XD ring.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_dci_khci_get_xd
(
    usb_device_handle handle,
    /* [IN] the dTD to enqueue */
    xd_struct_t** xd_ptr_ptr
)
{ /* Body */
    usb_khci_dev_state_struct_t* usb_dev_ptr = (usb_khci_dev_state_struct_t*)handle;

    /* This function can be called from any context, and it needs mutual
     exclusion with itself.*/
    OS_Lock();

    /* Get a transfer descriptor for the specified endpoint 
     ** and direction 
     */
    if (!usb_dev_ptr->xd_entries)
    {
        OS_Unlock();
        return USBERR_DEVICE_BUSY;
    }

    *xd_ptr_ptr = usb_dev_ptr->xd_head;
    if (usb_dev_ptr->xd_head)
    {
        usb_dev_ptr->xd_head = usb_dev_ptr->xd_head->next;
        if (usb_dev_ptr->xd_head == NULL)
        {
            usb_dev_ptr->xd_tail = NULL;
        }
    }
    usb_dev_ptr->xd_entries--;
    OS_Unlock();

    return USB_OK;
} /* Endbody */

/**************************************************************************//*!
 *
 * @name        : usb_dci_khci_init_xd
 * @brief       : initialize the xd.
 * @param handle: Handle to USB Device to be filled
 * @return   USB_OK on successful.
 ******************************************************************************/
usb_status usb_dci_khci_init_xd
(
    /* [IN] the USB device handle */
    usb_device_handle handle
)
{
    usb_khci_dev_state_struct_t* usb_dev_ptr = (usb_khci_dev_state_struct_t*)handle;
    xd_struct_t* xd_ptr;
    uint32_t j;

#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK))
    usb_dev_ptr->setup_buff = (uint8_t *)(&g_khci_data.setup_packet);
    usb_dev_ptr->xd_head = usb_dev_ptr->xd_base = (xd_struct_t*)(&g_khci_data.xd_base);
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    usb_dev_ptr->setup_buff = (uint8_t *) g_khci_data_ptr->setup_packet;
    usb_dev_ptr->xd_head = usb_dev_ptr->xd_base = (xd_struct_t*) g_khci_data_ptr->xd_base;
#endif
#if FSL_FEATURE_USB_KHCI_USB_RAM
    usb_dev_ptr->setup_buff = (uint8_t *)(usb_hal_khci_get_usbram_add(usb_dev_ptr->usbRegBase) + 480);
#endif
    usb_dev_ptr->xd_entries = USBCFG_DEV_MAX_XDS;

    /* Enqueue all the XDs */
    xd_ptr = (xd_struct_t*)usb_dev_ptr->xd_base;

    for (j = 0; j < USBCFG_DEV_MAX_XDS - 1; j++)
    {
        xd_ptr->next = xd_ptr + 1;
        //usb_dci_khci_free_xd(usb_dev_ptr, xd_ptr);
        xd_ptr++;
    }
    xd_ptr->next = 0;
    usb_dev_ptr->xd_tail = xd_ptr;

    return USB_OK;
}

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/*****************************************************************************
 * Local Functions
 *****************************************************************************/

/******************************************************************************
 *
 * @name  _usb_khci_next_setup_token_prep
 *
 * @brief The function prepares for next setup token
 *
 * @param state_ptr:      Device info Structure.
 *
 * @return NONE
 *****************************************************************************/
static void _usb_khci_next_setup_token_prep
(
    usb_khci_dev_state_struct_t* state_ptr
)
{
    xd_struct_t* xd_ptr_temp;
    usb_dci_khci_get_xd(state_ptr, &xd_ptr_temp);
    /* prepare XD queue for RECV CONTROL ENDPOINT*/
    if (state_ptr->ep_info[USB_CONTROL_ENDPOINT].rx_buf_odd == 0x0)
    {
        //BD_ADDR_RX(USB_CONTROL_ENDPOINT, state_ptr->ep_info[USB_CONTROL_ENDPOINT].rx_buf_odd) =
        //    USB_LONG_LE_TO_HOST((uint32_t)state_ptr->setup_buff);
        usb_hal_khci_bdt_set_address((uint32_t )bdt, USB_CONTROL_ENDPOINT, USB_RECV, 0, (uint32_t )state_ptr->setup_buff);
        xd_ptr_temp->wstartaddress = state_ptr->setup_buff;
    }
    else
    {
        //BD_ADDR_RX(USB_CONTROL_ENDPOINT, state_ptr->ep_info[USB_CONTROL_ENDPOINT].rx_buf_odd) =
        //    USB_LONG_LE_TO_HOST((uint32_t)state_ptr->setup_buff+ SETUP_PACKET_LENGTH);
        usb_hal_khci_bdt_set_address((uint32_t )bdt, USB_CONTROL_ENDPOINT, USB_RECV, 1, (uint32_t)(state_ptr->setup_buff+SETUP_PACKET_LENGTH));
        xd_ptr_temp->wstartaddress = state_ptr->setup_buff + SETUP_PACKET_LENGTH;
    }
    xd_ptr_temp->ep_num = USB_CONTROL_ENDPOINT;
    xd_ptr_temp->bdirection = USB_RECV;
    xd_ptr_temp->wtotallength = ZERO_LENGTH;
    xd_ptr_temp->ep_type = USB_CONTROL_PIPE;
#if USBCFG_KHCI_4BYTE_ALIGN_FIX
    xd_ptr_temp->internal_dma_align = TRUE;
#endif
    //USB_XD_QUEUE_ENQUEUE(&state_ptr->ep_info[USB_CONTROL_ENDPOINT].xd_queue_recv, xd_ptr_temp);
    state_ptr->ep_info[USB_CONTROL_ENDPOINT].recv_xd = xd_ptr_temp;
    /* toggle send buffer */
    //state_ptr->ep_info[USB_CONTROL_ENDPOINT].tx_buf_odd ^= 1;
    /* configure data pid for setup token and give control to SEI*/
    state_ptr->ep_info[USB_CONTROL_ENDPOINT].rx_data0 = 0;
    usb_hal_khci_bdt_set_control((uint32_t )bdt, USB_CONTROL_ENDPOINT, USB_RECV, state_ptr->ep_info[USB_CONTROL_ENDPOINT].rx_buf_odd,
        USB_LONG_LE_TO_HOST((uint32_t)((uint32_t)USB_BD_BC(SETUP_PACKET_LENGTH)| (uint32_t)USB_BD_OWN | (uint32_t)USB_BD_DTS | (uint32_t)USB_BD_DATA01(state_ptr->ep_info[USB_CONTROL_ENDPOINT].rx_data0))));
    //BD_CTRL_RX(USB_CONTROL_ENDPOINT, state_ptr->ep_info[USB_CONTROL_ENDPOINT].rx_buf_odd) =
    //USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(SETUP_PACKET_LENGTH)|
    //    USB_BD_OWN | USB_BD_DTS | USB_BD_DATA01(state_ptr->ep_info[USB_CONTROL_ENDPOINT].rx_data0)));
    //USB_PRINTF("ready to receive on EP0 setup\n");
    /* setup token is always on DATA0 PID */
    return;
}

/**************************************************************************//*!
 *
 * @name  _usb_khci_ep_read
 *
 * @brief The function reads the endpoint buffers
 *
 * @param state_ptr:      Device info Structure.
 * @param ep_num:         endpoint number
 * @param buf_ptr:        buffer to receive in
 * @param buf_num_bytes:  number of bytes to read
 *
 * @return USB_OK         When Successfully
 *****************************************************************************/
static usb_status _usb_khci_ep_read
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr,
    /*[IN]*/
    uint8_t ep_num,
    /*[OUT]*/
    uint8_t * buf_ptr,
    /*[IN]*/
    uint32_t buf_num_bytes
)
{
    OS_Lock();

    /* USB data is directly transferred to App Buffer to Avoid one level of
     * memcpy. (i.e from Endpoint buffer to App buffer). So a hack here
     * is been provided. This hack stores the current endpoint buffer
     * address to a variable and programs the buffer address in the BDT
     * as APP buffer. Later when TOKEN_DNE interrupt is received for this Token
     * this buffer address saved is restored. Please note that at present
     * App should not release the buffer passed till he gets a notification from
     * interrupt handler.
     */

    usb_hal_khci_bdt_set_address((uint32_t )bdt, ep_num, USB_RECV, state_ptr->ep_info[ep_num].rx_buf_odd, (uint32_t )buf_ptr);
    //BD_ADDR_RX(ep_num, state_ptr->ep_info[ep_num].rx_buf_odd) =
    //    USB_LONG_LE_TO_HOST((uint32_t)buf_ptr);

    /* Program number of bytes to be received and give
     * the Control to the SEI
     */
    usb_hal_khci_bdt_set_control((uint32_t )bdt, ep_num, USB_RECV, state_ptr->ep_info[ep_num].rx_buf_odd,
        USB_LONG_LE_TO_HOST(USB_BD_BC(buf_num_bytes) | USB_BD_OWN | USB_BD_DTS | USB_BD_DATA01(state_ptr->ep_info[ep_num].rx_data0)));
    //BD_CTRL_RX(ep_num, state_ptr->ep_info[ep_num].rx_buf_odd) =
    //    USB_LONG_LE_TO_HOST(USB_BD_BC(buf_num_bytes) |
    //        USB_BD_OWN | USB_BD_DTS | USB_BD_DATA01(state_ptr->ep_info[ep_num].rx_data0));

    OS_Unlock();

    usb_hal_khci_clr_token_busy(state_ptr->usbRegBase);
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  _usb_khci_ep_write
 *
 * @brief The function writes the endpoint buffers
 *
 * @param state_ptr:      Device info Structure.
 * @param ep_num:         endpoint number
 * @param buf_ptr:        buffer to send from
 * @param buf_num_bytes:  number of bytes to write
 * @param bytes_written_ptr: buffer that will  contain Number of bytes written
 *                           to device.
 *
 * @return USB_OK         When Successfully
 *****************************************************************************/
static usb_status _usb_khci_ep_write
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr,
    /*[IN]*/
    uint8_t ep_num,
    /*[IN]*/
    uint8_t * buf_ptr,
    /*[IN]*/
    uint32_t buf_num_bytes,
    /*[OUT]*/
    uint32_t* bytes_written_ptr
)
{
    uint16_t max_packet_size;

    /* If the number of bytes to be sent is greater than the
     * maximum data that can be sent on the USB bus, then split the
     * transaction, into multiple transaction.
     */
    max_packet_size = state_ptr->ep_info[ep_num].max_packet_size;

    if (buf_num_bytes > max_packet_size)
    {
        buf_num_bytes = max_packet_size;
    }

    *bytes_written_ptr = buf_num_bytes;

    /* Program the endpoint buffer address in BDT
     * from where DMA will pick the Data to be sent over USB bus.
     */
    //BD_ADDR_TX(ep_num, state_ptr->ep_info[ep_num].tx_buf_odd) =
    //    USB_LONG_LE_TO_HOST((uint32_t)buf_ptr);
    usb_hal_khci_bdt_set_address((uint32_t )bdt, ep_num, USB_SEND, state_ptr->ep_info[ep_num].tx_buf_odd, (uint32_t )buf_ptr);
    /* Program the number of bytes to be sent in BDT and Give
     * the ownership to SEI
     */
    //BD_CTRL_TX(ep_num, state_ptr->ep_info[ep_num].tx_buf_odd) =
    //    USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(buf_num_bytes) |
    //        USB_BD_OWN | USB_BD_DTS | USB_BD_DATA01(state_ptr->ep_info[ep_num].tx_data0)));
    usb_hal_khci_bdt_set_control((uint32_t )bdt, ep_num, USB_SEND, state_ptr->ep_info[ep_num].tx_buf_odd,
        USB_LONG_LE_TO_HOST(USB_BD_BC(buf_num_bytes) | USB_BD_OWN | USB_BD_DTS | USB_BD_DATA01(state_ptr->ep_info[ep_num].tx_data0)));

    usb_hal_khci_clr_token_busy(state_ptr->usbRegBase);
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  _usb_khci_reset_ep_state
 *
 * @brief This Function Resets all the parameters required for End Point
 *        Initialization
 *
 * @param state_ptr: Device info Structure.
 * @return USB_OK         When Successfully
 *****************************************************************************/
static usb_status _usb_khci_reset_ep_state
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr
)
{
    //volatile USB_MemMapPtr usb_ptr;
    uint32_t ep;

    uint8_t interrupt_enable;

    /* Clear all the error Status register */
    usb_hal_khci_clr_all_error_interrupts(state_ptr->usbRegBase);

    /*Reset all ODD and Even BDTs to Zero */
    usb_hal_khci_set_oddrst(state_ptr->usbRegBase);

    /* Initialize the address as zero in the Address register of USB IP*/
    usb_hal_khci_set_device_addr(state_ptr->usbRegBase, 0);

    for (ep = 0; ep < USBCFG_DEV_MAX_ENDPOINTS; ep++)
    {
        /* Clearing all buffer descriptors for both ODD and even
         * for Both Receive and Transmit direction
         */
        usb_hal_khci_bdt_set_control((uint32_t )bdt, ep, USB_RECV, 0, 0);
        usb_hal_khci_bdt_set_control((uint32_t )bdt, ep, USB_RECV, 1, 0);
        usb_hal_khci_bdt_set_control((uint32_t )bdt, ep, USB_SEND, 0, 0);
        usb_hal_khci_bdt_set_control((uint32_t )bdt, ep, USB_SEND, 1, 0);
        //BD_CTRL_RX(ep, EVEN_BUFF) = 0;
        //BD_CTRL_RX(ep, ODD_BUFF) = 0;

        //BD_CTRL_TX(ep, EVEN_BUFF) = 0;
        //BD_CTRL_TX(ep, ODD_BUFF) = 0;

        state_ptr->ep_info[ep].rx_buf_odd = EVEN_BUFF;
        state_ptr->ep_info[ep].tx_buf_odd = EVEN_BUFF;
        //state_ptr->ep_info[ep].data_buffer = NULL;
#if 0        
        if(ep == USB_CONTROL_ENDPOINT)
        {
            state_ptr->ep_info[ep].tx_buf_odd = ODD_BUFF;
        }
#endif
        /* Initialize All End Point Control Registers with default value of 0*/
        usb_hal_khci_endpoint_shut_down(state_ptr->usbRegBase, ep);
    }

    g_zero_pkt_send = FALSE;

    /* Clear Reset Interrupt */
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_USBRST);

    usb_hal_khci_clr_oddrst(state_ptr->usbRegBase);

    /* initializing device address to default  address
     * value for USB in Device structure.
     */
    state_ptr->device_address = 0;

    /* Set Default state of USB in Device Structure.*/
    state_ptr->usb_state = USB_STATE_DEFAULT;

    /* Set Default device status */
    state_ptr->usb_device_status =
    (USBCFG_DEV_SELF_POWER << (USB_GET_STATUS_ATTRIBUTES_SELF_POWERED_SHIFT)) |
    (USBCFG_DEV_REMOTE_WAKEUP << (USB_GET_STATUS_ATTRIBUTES_REMOTE_WAKEUP_SHIFT));

    /* Enable All Error Interrupts */
    usb_hal_khci_enable_all_error_interrupts(state_ptr->usbRegBase);

    interrupt_enable = INTR_USBRST | INTR_SOFTOK | INTR_TOKDNE | INTR_STALL;

    /* Enable All Interrupts except RESUME */
#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME
    interrupt_enable |= INTR_SLEEP;
#endif

#if USBCFG_DEV_KHCI_ADVANCED_ERROR_HANDLING
    interrupt_enable |= INTR_ERROR;
#endif
    usb_hal_khci_enable_interrupts(state_ptr->usbRegBase, interrupt_enable);
    /* SEI if, has suspended packet transmission resume packet transmission by
     * clearing TXD_SUSPEND in CTL register.
     */
    usb_hal_khci_clr_token_busy(state_ptr->usbRegBase);

    return USB_OK;
}

#if 0
/**************************************************************************//*!
 *
 * @name  _usb_khci_process_transmit_request
 *
 * @brief : Service TOKEN DONE Interrupt when there is transmission of packet.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function OS_install_isr
 *                   During ISR installation.
 * @param ep_num:    endpoint number
 * @param buffer_ptr:Holds Data that is send to Host.
 * @return USB_STATUS_TRANSFER_PENDING when there is split transaction or
 *                   USB_OK.
 *****************************************************************************/
static usb_status _usb_khci_process_transmit_request
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr, 
    /*[IN]*/
    uint8_t ep_num,
    /*[OUT]*/
    uint8_t** buffer_ptr
)
{
    xd_struct_t* xd_ptr = state_ptr->ep_info[ep_num].send_xd;

    //USB_XD_QUEUE_GET_HEAD(&state_ptr->ep_info[ep_num].xd_queue_send,&xd_ptr);

    //*buffer_ptr = (uint8_t *) USB_LONG_LE_TO_HOST(BD_ADDR_TX(ep_num,
    //    state_ptr->ep_info[ep_num].tx_buf_odd));

    //*buffer_ptr = (uint8_t *)USB_LONG_LE_TO_HOST(usb_hal_khci_bdt_get_address(usb_dev_ptr->usbRegBase, (uint32_t)bdt, ep_num, USB_SEND, state_ptr->ep_info[ep_num].tx_buf_odd));

    usb_dci_khci_send(state_ptr, xd_ptr);

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  _usb_khci_process_receive_request
 *
 * @brief : Service TOKEN DONE Interrupt when there is receive packet scenario.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function
 *                   OS_install_isr during ISR installation.
 * @param ep_num:    endpoint number
 * @param stat:      status of last transaction.
 * @param buffer_ptr:buffer holding data received from Host.
 *
 * @return USB_STATUS_TRANSFER_PENDING when there is split transaction else
 *                   USB_OK
 *****************************************************************************/
static usb_status _usb_khci_process_receive_request
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr, 
    /*[IN]*/
    uint8_t ep_num, 
    /*[IN]*/
    uint8_t stat, 
    /*[OUT]*/
    uint8_t** buffer_ptr
)
{
    xd_struct_t* xd_ptr = state_ptr->ep_info[ep_num].recv_xd;

    //*buffer_ptr = (uint8_t *) USB_LONG_LE_TO_HOST(BD_ADDR_RX(ep_num,
    //    state_ptr->ep_info[ep_num].rx_buf_odd));
    //*buffer_ptr = (uint8_t *)USB_LONG_LE_TO_HOST(usb_hal_khci_bdt_get_address(usb_dev_ptr->usbRegBase, (uint32_t)bdt, ep_num, USB_RECV, state_ptr->ep_info[ep_num].rx_buf_odd));

    usb_dci_khci_recv(state_ptr, xd_ptr);
    return USB_OK;
}
#endif

#if USBCFG_DEV_KHCI_ADVANCED_ERROR_HANDLING
/**************************************************************************//*!
 *
 * @name  _usb_khci_service_err_intr
 *
 * @brief : Service Error Interrupt.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function OS_install_isr
 *                   During ISR installation.
 *
 * @return NONE
 *****************************************************************************/
static void _usb_khci_service_err_intr
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr 
)
{
    uint8_t device_error = 0, stat, ep_num;
    //volatile USB_MemMapPtr usb_ptr;
    usb_event_struct_t event;

    stat = usb_hal_khci_get_transfer_status(state_ptr->usbRegBase);

    /* Clear the Error Interrupt */
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_ERROR);

    /* Get the Endpoint number on which the transaction occurred.
     * This is (7 - 5) [3:0] bit in STAT register.
     */
    ep_num = usb_hal_khci_get_transfer_done_ep_number(state_ptr->usbRegBase);

    /* Read the ERRSTAT register to determine the source of the error
     * It is Added with ERREN register to find out which of the
     * Error was enabled and report only the enabled error to the App layer
     */
    device_error = (uint8_t)(usb_hal_khci_get_error_interrupt_status(state_ptr->usbRegBase) &
    usb_hal_khci_get_error_interrupt_enable_status(state_ptr->usbRegBase));

#if _DEBUG
    USB_PRINTF("USB Err: 0x%x\n", device_error);
#endif

    /* Initialize the event structure to be passed to the upper layer*/
    event.handle = (usb_device_handle)state_ptr->upper_layer_handle;
    event.ep_num = ep_num;
    event.setup = FALSE;
    event.direction = (bool)(stat >> 3 & 1);
    event.buffer_ptr = (uint8_t*)device_error;
    event.len = ZERO_LENGTH;

    /* Invoke Service Call */
    (void)_usb_device_call_service(USB_SERVICE_ERROR,&event);

    /*clear all errors*/
    usb_hal_khci_clr_all_error_interrupts(state_ptr->usbRegBase);
}
#endif

/**************************************************************************//*!
 *
 * @name  _usb_khci_service_reset_intr
 *
 * @brief : Service reset Interrupt.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function OS_install_isr
 *                   During ISR installation.
 *
 * @return NONE
 *****************************************************************************/
static void _usb_khci_service_reset_intr
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr
)
{
    uint8_t ep_num;
    //volatile USB_MemMapPtr usb_ptr;
    usb_event_struct_t event;

    state_ptr->is_reseting = 1;
    /* Clear Reset Interrupt */
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_USBRST);

    /* Get the Endpoint number on which the transaction occurred.
     * This is (7 - 5) [3:0] bit in STAT register.
     */
    ep_num = usb_hal_khci_get_transfer_done_ep_number(state_ptr->usbRegBase);

    /* Initialize the event structure to be passed to the upper layer*/
    event.handle = (usb_device_handle)state_ptr->upper_layer_handle;
    event.ep_num = ep_num;
    event.setup = FALSE;
    event.direction = USB_RECV;
    event.buffer_ptr = (uint8_t*)NULL;
    event.len = ZERO_LENGTH;
    /* Inform Upper Layer of Reset Signal.
     * Remember Upper layer i.e class driver invokes
     * usb_dci_khci_init_endpoint() as part of reset callback
     */
    (void)_usb_device_call_service(USB_SERVICE_BUS_RESET, &event);
}

/**************************************************************************//*!
 *
 * @name  _usb_khci_service_tk_dne_intr
 *
 * @brief : Service Error Interrupt.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. It is the same
 *                   structure which was passed in function OS_install_isr
 *                   During ISR installation.
 *
 * @return NONE
 *****************************************************************************/
static void _usb_khci_service_tk_dne_intr
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr
)
{
    uint8_t ep_num, stat, dir, buf_odd, setup, token_pid;
    uint32_t len = 0;
    //usb_status error;
    uint32_t buf_num_bytes;
    //volatile USB_MemMapPtr usb_ptr;
    xd_struct_t* xd_ptr;
//    uint8_t * buffer_ptr = NULL;
    uint32_t control = 0;
#if USBCFG_KHCI_4BYTE_ALIGN_FIX
    uint8_t *src, *dst = NULL;
#endif
    usb_event_struct_t event;

    /* Get the status of previous transaction*/
    stat = usb_hal_khci_get_transfer_status(state_ptr->usbRegBase);

    /* Get the Endpoint number on which the transaction occurred.
     * This is (7 - 5) [3:0] bit in STAT register.
     */
    ep_num = usb_hal_khci_get_transfer_done_ep_number(state_ptr->usbRegBase);

    /* Get the Direction of transaction. (i.e the transaction was a receive
     * operation or transaction was a Transmit operation).It is Bit [3] in STAT
     * register.
     */
    dir = usb_hal_khci_get_transfer_done_direction(state_ptr->usbRegBase);

    /* Get the last buffer transaction was in ODD buffer or Even Buffer*/
    buf_odd = usb_hal_khci_get_transfer_done_odd(state_ptr->usbRegBase);

    /* Clear TOKEN  Done Interrupt. This clearing of TOKEN_DONE
     * should happen after STAT register is read. This is because
     * STAT register has four byte fifo and if TOKEN_DONE is cleared
     * in INT_STAT then the content of STAT register is updated with
     * the next value in the STAT fifo.
     */
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_TOKDNE);

    control = usb_hal_khci_bdt_get_control((uint32_t )bdt, ep_num, dir, buf_odd);

    /* Get length of Data transmitted or received in the last transaction. */
    len = (USB_HOST_TO_LE_LONG(control) >> 16) & 0x3ff;

    /* Get PID for this token */
    token_pid = (uint8_t)((USB_HOST_TO_LE_LONG(control) >> 2) & 0x0000000f);

    /* if token PID is a setup token */
    setup = (token_pid == USB_SETUP_TOKEN) ? TRUE : FALSE;

    //USB_PRINTF("23tk_dne ep %d dir %d len %d buff_odd %d\n", ep_num, dir, len, buf_odd);
    if (dir)
    {
        /* direction is USB_SEND*/
        /* Get head of the send queue */
        //USB_XD_QUEUE_GET_HEAD(&state_ptr->ep_info[ep_num].xd_queue_send,&xd_ptr);
        //USB_PRINTF("get send xd_ptr 0x%x\n", xd_ptr);
        /* updating the WSOFAR field */
        xd_ptr = state_ptr->ep_info[ep_num].send_xd;
        if (xd_ptr == NULL)
        {
            return;
        }
        xd_ptr->wsofar += len;

        buf_num_bytes = (uint32_t)(xd_ptr->wtotallength - xd_ptr->wsofar);

        /* dequeue if all bytes have been send or the last send transaction was
         of length less then the max packet size length configured for
         corresponding endpoint */
        state_ptr->ep_info[ep_num].tx_buf_odd ^= 1;
        state_ptr->ep_info[ep_num].tx_data0 ^= 1;
        if ((buf_num_bytes == 0) || (state_ptr->ep_info[ep_num].max_packet_size > len))
        {
            event.len = xd_ptr->wsofar;
            /* buffer address is updated for upper layer */
            event.buffer_ptr = xd_ptr->wstartaddress;
            state_ptr->ep_info[ep_num].send_xd = NULL;
            usb_dci_khci_free_xd(state_ptr, xd_ptr);
            if ((len == state_ptr->ep_info[ep_num].max_packet_size) &&
            (ep_num == USB_CONTROL_ENDPOINT))
            {
                g_zero_pkt_send = TRUE;
                usb_device_send_data((usb_device_handle)state_ptr->upper_layer_handle, ep_num, NULL, 0);
                return;
            }
        }
        else
        {
            usb_dci_khci_send(state_ptr, xd_ptr);
            //_usb_khci_process_transmit_request(state_ptr, ep_num, &buffer_ptr);
            return;/*if above call returned USB_STATUS_TRANSFER_PENDING */
        }
    }
    else
    {

        if ((ep_num == USB_CONTROL_ENDPOINT) && (!len))
        {
            /* Initialize the event structure to be passed to the upper layer*/
            event.handle = (usb_device_handle)state_ptr->upper_layer_handle;
            event.ep_num = ep_num;
            event.setup = setup;
            event.direction = (bool)(stat >> 3 & 1U);

            /* propagate control to upper layers for processing */
            _usb_device_call_service(ep_num, &event);
            usb_hal_khci_clr_token_busy(state_ptr->usbRegBase);
            return;
        }
        /* direction is USB_RECV*/
        if (g_zero_pkt_send == TRUE)
        {
            g_zero_pkt_send = FALSE;
        }
        //USB_PRINTF("before ep %d : xd_head_ptr 0x%x xd_tail_ptr 0x%x\n", ep_num,
        //          state_ptr->EP_INFO[ep_num].xd_queue_recv.xd_head_ptr,
        //          state_ptr->EP_INFO[ep_num].xd_queue_recv.xd_tail_ptr);
        /* Get head of the send queue */
        //USB_XD_QUEUE_GET_HEAD(&state_ptr->ep_info[ep_num].xd_queue_recv, &xd_ptr);
        xd_ptr = state_ptr->ep_info[ep_num].recv_xd;
        if (xd_ptr == NULL)
        {
            return;
        }
#if USBCFG_KHCI_4BYTE_ALIGN_FIX
        if (!xd_ptr->internal_dma_align)
        {
            //src = (uint8_t *)USB_LONG_LE_TO_HOST(BD_ADDR_RX(ep_num, state_ptr->ep_info[ep_num].rx_buf_odd));
            src = (uint8_t*)USB_LONG_LE_TO_HOST(usb_hal_khci_bdt_get_address( (uint32_t)bdt, ep_num, USB_RECV, state_ptr->ep_info[ep_num].rx_buf_odd));
            dst = xd_ptr->wstartaddress + xd_ptr->wsofar;
            if (src != dst)
            {
                OS_Mem_copy(src, dst, len);
            }
        }
#endif
        xd_ptr->wsofar += len;/* updating the WSOFAR field */

        buf_num_bytes = (uint32_t)(xd_ptr->wtotallength - xd_ptr->wsofar);

        if ((ep_num == USB_CONTROL_ENDPOINT) && (token_pid == USB_SETUP_TOKEN))
        {
            /* cancel any pending transfers in SEND QUEUE if present*/
            usb_dci_khci_cancel((usb_device_handle)state_ptr, ep_num, USB_SEND);
            /* for first In/OUT after setup token DATA PID has to be always one */
            state_ptr->ep_info[ep_num].tx_data0 = 1;
            state_ptr->ep_info[ep_num].rx_data0 = 1;
            state_ptr->ep_info[ep_num].rx_buf_odd ^= 1;
            //state_ptr->ep_info[ep_num].tx_buf_odd ^= 1;
        }
        else
        {
            /* set DATA PID and buffer for next recv transaction */
            state_ptr->ep_info[ep_num].rx_data0 ^= 1;
            state_ptr->ep_info[ep_num].rx_buf_odd ^= 1;
        }

        //USB_PRINTF("max packet size %d\n",state_ptr->EP_INFO[ep_num].max_packet_size);
        /* dequeue if all bytes have been received or the last send transaction
         was of length less then the max packet size length configured for
         corresponding endpoint */
        if ((!xd_ptr->wtotallength) || (buf_num_bytes == 0) ||
        (state_ptr->ep_info[ep_num].max_packet_size > len))
        {
            event.len = xd_ptr->wsofar;
            /* buffer address is updated for upper layer */
            event.buffer_ptr = xd_ptr->wstartaddress;
            state_ptr->ep_info[ep_num].recv_xd = NULL;
            usb_dci_khci_free_xd(state_ptr, xd_ptr);
        }
        else
        {
            usb_dci_khci_recv(state_ptr, xd_ptr);
            //_usb_khci_process_receive_request(state_ptr,ep_num, stat, &buffer_ptr);
            return;/*if above call returned USB_STATUS_TRANSFER_PENDING */
        }
    }

    /* prepare for next setup token if needed*/
    if ((ep_num == USB_CONTROL_ENDPOINT) && (!len) && (g_zero_pkt_send == FALSE))
    {
        _usb_khci_next_setup_token_prep(state_ptr);
    }
    /* Initialize the event structure to be passed to the upper layer*/
    event.handle = (usb_device_handle)state_ptr->upper_layer_handle;
    event.ep_num = ep_num;
    event.setup = setup;
    event.direction = (bool)(stat >> 3 & 1U);

    /* propagate control to upper layers for processing */
    _usb_device_call_service(ep_num, &event);

    //USB_PRINTF("_usb_khci_service_tk_dne_intr 3-- :%d \n",ep_num);

    usb_hal_khci_clr_token_busy(state_ptr->usbRegBase);

}

#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME
/**************************************************************************//*!
 *
 * @name  _usb_khci_service_sleep_intr
 *
 * @brief : Service Sleep Interrupt.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function OS_install_isr
 *                   During ISR installation.
 *
 * @return NONE
 *****************************************************************************/
static void _usb_khci_service_sleep_intr
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr
)
{
    //volatile USB_MemMapPtr usb_ptr;
    usb_event_struct_t event;

    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_RESUME);

    /* clear suspend interrupt */
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_SLEEP);

    state_ptr->usb_dev_state_b4_suspend = state_ptr->usb_state;

    state_ptr->usb_state = USB_STATE_SUSPEND;

    /* Initialize the event structure to be passed to the upper layer*/
    event.handle = (usb_device_handle)state_ptr->upper_layer_handle;
    event.ep_num = (uint8_t)USB_UNINITIALIZED_VAL_32;
    event.setup = 0;
    event.direction = 0;
    event.buffer_ptr = (uint8_t*)NULL;
    event.len = ZERO_LENGTH;

    /* Notify Device Layer of SLEEP Event */
    /* this callback need only handle and type -
     all other arguments are redundant */
    (void)_usb_device_call_service(USB_SERVICE_SUSPEND, &event);

    /* Enable RESUME Interrupt */
    usb_hal_khci_enable_interrupts(state_ptr->usbRegBase, (INTR_RESUME));
}

/************************************************************************//*!
 *
 * @name  _usb_khci_service_resume_intr
 *
 * @brief : Service resume Interrupt.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function OS_install_isr
 *                   During ISR installation.
 *
 * @return NONE
 *****************************************************************************/
static void _usb_khci_service_resume_intr
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr
)
{
    usb_event_struct_t event;

    /* clear resume interrupt status bit */
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_RESUME);

    state_ptr->usb_state = state_ptr->usb_dev_state_b4_suspend;

    /* Initialize the event structure to be passed to the upper layer*/
    event.handle = (usb_device_handle)state_ptr->upper_layer_handle;
    event.ep_num = (uint8_t)USB_UNINITIALIZED_VAL_32;
    event.setup = 0;
    event.direction = 0;
    event.buffer_ptr = (uint8_t*)NULL;
    event.len = ZERO_LENGTH;

    /* Notify Device Layer of RESUME Event */
    /* this callback need only handle and type -
     all other arguments are redundant */
    (void)_usb_device_call_service(USB_SERVICE_RESUME,&event);

    /* Disable RESUME Interrupt */
    usb_hal_khci_disable_interrupts(state_ptr->usbRegBase, INTR_RESUME);
}
#endif
/***********************************************************************//*!
 *
 * @name  _usb_khci_service_sof_token_intr
 *
 * @brief : Service SOF Interrupt.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function OS_install_isr
 *                   During ISR installation.
 *
 * @return NONE
 *****************************************************************************/
static void _usb_khci_service_sof_token_intr
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr
)
{
    /* Clear SOF Interrupt */
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_SOFTOK);

    state_ptr->usb_sof_count = usb_hal_khci_get_frame_number(state_ptr->usbRegBase);

    /* address of Lower byte of Frame number.
     */
    //buffer_ptr = (uint8_t *)&(state_ptr->USB_SOF_COUNT);
    /* clear resume interrupt status bit */
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_RESUME);
}

#if 0
/**************************************************************************//*!
 *
 * @name  _usb_khci_service_attach_intr
 *
 * @brief : Service attach Interrupt.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function OS_install_isr
 *                   During ISR installation.
 *
 * @return NONE
 *****************************************************************************/
static void _usb_khci_service_attach_intr
(
/*[IN]*/
usb_khci_dev_state_struct_t* state_ptr
)
{
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_ATTACH);
}
#endif

/************************************************************************//*!
 *
 * @name  _usb_khci_service_stall_intr
 *
 * @brief : Service stall Interrupt.
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function OS_install_isr
 *                   During ISR installation.
 *
 * @return NONE
 *****************************************************************************/
static void _usb_khci_service_stall_intr
(
    /*[IN]*/
    usb_khci_dev_state_struct_t* state_ptr
)
{

    uint8_t ep;

    for (ep = 0; ep < USBCFG_DEV_MAX_ENDPOINTS; ep++)
    {
        if (state_ptr->ep_info[ep].endpoint_status == USB_STATUS_STALLED)
        {
            usb_hal_khci_endpoint_clr_stall(state_ptr->usbRegBase, ep);
            usb_hal_khci_bdt_set_control((uint32_t )bdt, ep, USB_SEND, state_ptr->ep_info[ep].tx_buf_odd,
                USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(state_ptr->ep_info[ep].max_packet_size)| USB_BD_DTS | USB_BD_DATA01(0))));
            usb_hal_khci_bdt_set_control((uint32_t )bdt, ep, USB_RECV, state_ptr->ep_info[ep].rx_buf_odd,
                USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(state_ptr->ep_info[ep].max_packet_size)| USB_BD_DTS | USB_BD_DATA01(0))));
        }
    }

    /* Clear Stall Interrupt */
    usb_hal_khci_clr_interrupt(state_ptr->usbRegBase, INTR_STALL);

    /* check if the stall interrupt received was for CONTROL ENDPOINT */
    if (state_ptr->ep_info[USB_CONTROL_ENDPOINT].endpoint_status == USB_STATUS_STALLED)
    {
        state_ptr->ep_info[USB_CONTROL_ENDPOINT].endpoint_status = USB_STATUS_IDLE;
        _usb_khci_next_setup_token_prep(state_ptr);
    }

}

/**************************************************************************//*!
 *
 * @name  _usb_khci_isr
 *
 * @brief : Service all the interrupts in the kirin usb hardware
 *
 * @param state_ptr: Device Structure Pointer Passed to ISR. The is the
 *                   same structure which was passed in function OS_install_isr
 *                   During ISR installation.
 *
 * @return NONE
 *****************************************************************************/
#ifdef USBCFG_OTG 
void _usb_dev_khci_isr
(
    usb_khci_dev_state_struct_t* state_ptr
)
{
    state_ptr = (usb_khci_dev_state_struct_t*)(&g_khci_dev[0]);
#else
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
static void _usb_khci_isr(void)
{
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)(&g_khci_dev[0]);
#else
static void _usb_khci_isr(usb_khci_dev_state_struct_t* state_ptr)
{
    state_ptr = (usb_khci_dev_state_struct_t*)(&g_khci_dev[0]);
#endif
#endif
    /* Get the USB IP base address in the controller */
    //error = (uint8_t)usb_hal_get_interrupt_status(state_ptr->usbRegBase);
#if FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED && USBCFG_DEV_KEEP_ALIVE_MODE
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
    if(usb_hal_khci_get_keepalive_wake_int_sts(state_ptr->usbRegBase))
    {
        usb_hal_khci_clr_keepalive_wake_int_sts(state_ptr->usbRegBase);
    }
#endif
#endif
    /* This interrupt comes when any of the error conditions within
     * the ERRSTAT register occur. The ColdFire core must
     * then read the ERRSTAT register to determine the source of the error.
     */
#if USBCFG_DEV_KHCI_ADVANCED_ERROR_HANDLING
    if (usb_hal_khci_is_interrupt_issued(state_ptr->usbRegBase, INTR_ERROR))
    {
        _usb_khci_service_err_intr(state_ptr);
    }
#endif
    /* This TOKEN_DONE interrupt comes when the current token being processed
     * has completed. The ColdFire core should immediately read the STAT register
     * to determine the EndPoint and BD used for this token. Clearing this bit
     * (by writing a one) causes the STAT register to be cleared or the
     * STAT holding register to be loaded into the STAT register.
     */
    if (usb_hal_khci_is_interrupt_issued(state_ptr->usbRegBase, INTR_TOKDNE))
    {
    //  USB_PRINTF("done ++");
        _usb_khci_service_tk_dne_intr(state_ptr);
    }
    /* This reset interrupt comes when the USB Module has decoded a valid USB reset.
     * This informs the Microprocessor that it should write 0x00 into the address
     * register and enable endpoint 0. USB_RST bit is set after a USB reset has been
     * detected for 2.5 microseconds. It is not asserted again until the USB reset
     * condition has been removed and then re-asserted.
     */
    if (usb_hal_khci_is_interrupt_issued(state_ptr->usbRegBase, INTR_USBRST))
    {
        _usb_khci_service_reset_intr(state_ptr);
    }
#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME    
    /* This sleep interrupt comes when the USB Module detects a constant idle
     * on the USB bus for 3 milliseconds.
     */
    if (usb_hal_khci_is_interrupt_issued(state_ptr->usbRegBase, INTR_SLEEP))
    {
        _usb_khci_service_sleep_intr(state_ptr);
    }
    
    /* This interrupt comes depending upon the DP/DM signals, and can be used
     * to signal remote wake-up signaling on the USB bus. When not in suspend
     * mode this interrupt should be disabled
     */
    if (usb_hal_khci_is_interrupt_issued(state_ptr->usbRegBase, INTR_RESUME))
    {
        _usb_khci_service_resume_intr(state_ptr);
    }
#endif
    /* This interrupt comes when the USB Module receives a Start Of Frame
     * (SOF) token.
     */
    if (usb_hal_khci_is_interrupt_issued(state_ptr->usbRegBase, INTR_SOFTOK))
    {
        _usb_khci_service_sof_token_intr(state_ptr);
    }

#if 0    
    /* This interrupt comes when the USB Module detects an attach of a 
     * USB device. This signal is only valid if HOST_MODE_EN is true. 
     * This interrupt signifies that a peripheral is now present and must
     * be configured.
     */
    if(usb_hal_khci_is_interrupt_issued(state_ptr->usbRegBase, INTR_ATTACH))
    {
        _usb_khci_service_attach_intr(state_ptr);
    }
#endif    
    /* In Target mode this interrupt comes when a STALL handshake is sent 
       by the SIE.*/
    if (usb_hal_khci_is_interrupt_issued(state_ptr->usbRegBase, INTR_STALL))
    {
        _usb_khci_service_stall_intr(state_ptr);
    }

    return;
}
/*****************************************************************************
 * Global Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name        : usb_dci_khci_preinit
 * @brief       : Allocates space for the USB device controller.
 * @param handle: Handle to USB Device to be filled
 * @return   USB_OK on successful.
 ******************************************************************************/
usb_status usb_dci_khci_preinit
(
    /* [IN] the USB device handle */
    usb_device_handle upper_layer_handle,

    usb_device_handle * handle_ptr
    )
{
    usb_khci_dev_state_struct_t* usb_dev_ptr = (usb_khci_dev_state_struct_t*)(&g_khci_dev[0]);

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    if (NULL == g_khci_data_ptr)
    {
        g_khci_data_ptr = OS_Mem_alloc_uncached(sizeof(usb_device_khci_data_t));
    }

#if (FSL_FEATURE_USB_KHCI_USB_RAM == 0)
    if (NULL == g_khci_bdt_ptr)
    {
        g_khci_bdt_ptr = OS_Mem_alloc_uncached_align(512, 512);
    }
#endif

#endif

    usb_dci_khci_init_xd((usb_device_handle)usb_dev_ptr);

#if USBCFG_KHCI_4BYTE_ALIGN_FIX

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
    _usb_khci_dev_swap_buf_ptr = g_khci_data.swap_buf;
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    _usb_khci_dev_swap_buf_ptr = g_khci_data_ptr->swap_buf;
#endif

#endif
    usb_dev_ptr->mutex = OS_Mutex_create();
    *handle_ptr = (usb_device_handle)usb_dev_ptr;
    usb_dev_ptr->upper_layer_handle = upper_layer_handle;

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name        : usb_dci_khci_init
 * @brief       : Initializes the USB device controller.
 * @param handle: USB device handle.
 * @param init_param: initialization parameters specific for device
 * @return   USB_OK on successful.
 ******************************************************************************/
usb_status usb_dci_khci_init
(
    uint8_t controller_id,
    /* [IN] the USB device handle */

    usb_device_handle handle
    )
{
#ifdef USBCFG_OTG
    usb_otg_state_struct_t * usb_otg_struct_ptr = (usb_otg_state_struct_t *)g_usb_otg_handle;
    usb_otg_status_t * otg_status_ptr = &usb_otg_struct_ptr->otg_status;
#endif
    usb_khci_dev_state_struct_t* usb_dev_ptr = (usb_khci_dev_state_struct_t*)handle;
    //volatile USB_MemMapPtr             usb_ptr;

    usb_dev_ptr->dev_vec = soc_get_usb_vector_number(controller_id);

    usb_dev_ptr->is_reseting = 0;

    usb_dev_ptr->usbRegBase = soc_get_usb_base_address(controller_id);
    /* Get the maximum number of endpoints supported by this USB controller */
    usb_dev_ptr->max_endpoints = KHCI_MAX_ENDPOINT;
    usb_dev_ptr->speed = USB_SPEED_FULL;

    /* Clear all interrupts and bring it to finite
     * state before device starts functioning.
     */
    usb_hal_khci_clr_all_interrupts(usb_dev_ptr->usbRegBase);
    usb_hal_khci_disable_dp_pull_up(usb_dev_ptr->usbRegBase);

#ifndef USBCFG_OTG 
    /* Install the ISR
     * Device Pointer is passed as an Argument when the
     * ISR is invoked.
     */
#if (OS_ADAPTER_ACTIVE_OS != OS_ADAPTER_SDK)
    if (!(OS_install_isr(usb_dev_ptr->dev_vec, (void (*)(void *))_usb_khci_isr, usb_dev_ptr)))
    return USBERR_INSTALL_ISR;
#else
    OS_install_isr(usb_dev_ptr->dev_vec, (void (*)(void) )_usb_khci_isr, usb_dev_ptr);
#endif
#endif

#if FSL_FEATURE_USB_KHCI_USB_RAM
    bdt = (uint8_t *)usb_hal_khci_get_usbram_add(usb_dev_ptr->usbRegBase);
#else

#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK))
    bdt = g_khci_bdt_buffer;
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    bdt = g_khci_bdt_ptr;
#endif

#endif

    /* Initialize BDT Page register 1,2,3. The Buffer
     * Descriptor Table Page Register 1 2,3 contains an
     * 8-bit value used to compute the address where
     * the current Buffer Descriptor Table (BDT)
     * resides in system memory.
     */
    usb_hal_khci_set_buffer_descriptor_table_addr(usb_dev_ptr->usbRegBase, (uint32_t)bdt);

    /* Initialize the end point state*/
    _usb_khci_reset_ep_state(usb_dev_ptr);

    //USB_PRINTF("11usb_dci_khci_init ++");
    /* Enable Sleep,Token Done,Error,USB Reset,Stall,
     * Resume and SOF Interrupt.
     */
    //usb_hal_khci_enable_interrupts(usb_dev_ptr->usbRegBase,(INTR_USBRST | INTR_ERROR | INTR_SOFTOK | INTR_TOKDNE | INTR_SLEEP | INTR_STALL));
#ifdef USBCFG_OTG
    usb_dev_ptr->otg_handle = g_usb_otg_handle;
    otg_status_ptr->active_stack = USB_ACTIVE_STACK_DEVICE;
    /* set otg status to 0 */
    usb_dci_khci_set_status(handle, USB_STATUS_OTG, 0);
    /**/
#endif
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name        : usb_dci_khci_init
 * @brief       : Initializes the USB device controller.
 * @param handle: USB device handle.
 * @param init_param: initialization parameters specific for device
 * @return   USB_OK on successful.
 ******************************************************************************/
usb_status usb_dci_khci_postinit
(
    uint8_t controller_id,
    /* [IN] the USB device handle */

    usb_device_handle handle
    )
{
    /* Enable D+ pull up register
     * Note, that this D+ external resistor is not applicable for some devices
     */
    usb_khci_dev_state_struct_t* usb_dev_ptr = (usb_khci_dev_state_struct_t*)(&g_khci_dev[controller_id - USB_CONTROLLER_KHCI_0]);
    //usb_khci_dev_state_struct_t* state_ptr = *usb_dev_ptr;

    usb_hal_khci_enable_dp_pull_up(usb_dev_ptr->usbRegBase);
    /* Enable USB module*/
    usb_hal_khci_enable_sof(usb_dev_ptr->usbRegBase);

    /* Remove suspend state */
    usb_hal_khci_clr_suspend(usb_dev_ptr->usbRegBase);
    return USB_OK;
}

/**************************************************************************//*!
 * @name        : usb_dci_khci_init_endpoint
 *
 * @brief       : Initialize the Endpoint
 * @param handle: Handle to USB Device.
 * @param xd_ptr: Transaction Descriptor.
 * @return      :  USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_init_endpoint
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    xd_struct_t* xd_ptr
    )
{
    //usb_status error = USB_OK;
    uint16_t max_pkt_size = 0;

    /* Get the device pointer initialized in usb_dci_khci_init*/
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;
    //volatile USB_MemMapPtr usb_ptr;
#if 0
    if (state_ptr == NULL)
    {
        return USBERR_ERROR;
    }

    if((xd_ptr->ep_type > USB_INTERRUPT_PIPE) ||
    (xd_ptr->bdirection > USB_SEND))
    {
        return USBERR_EP_INIT_FAILED;
    }
#endif
    //USB_PRINTF("init ep %d dir %d\n", xd_ptr->EP_NUM, xd_ptr->BDIRECTION);

    /* mark this endpoint as initialized */
    state_ptr->ep_info[xd_ptr->ep_num].ep_init_flag[xd_ptr->bdirection] = TRUE;

    /*before initializing cancel all transfers on EP as there may be calls
     for endpoint initialization more than once. This will free any allocated
     queue*/

    /*
     * Since this is endpoint initialization section there will
     * not be any pending transfers on this endpoint
     */

    /* The end point buffer size will be set as required by app.
     * but if the size crosses MAX_EP_BUFFER_SIZE size then truncate the
     * max packet size.
     */
    if (xd_ptr->ep_type == USB_ISOCHRONOUS_PIPE)
    {
        max_pkt_size = (uint16_t)((xd_ptr->wmaxpacketsize > MAX_FS_ISO_EP_BUFFER_SIZE)?
        MAX_FS_ISO_EP_BUFFER_SIZE:xd_ptr->wmaxpacketsize);
    }
    else
    {
        max_pkt_size = (uint16_t)((xd_ptr->wmaxpacketsize > MAX_FS_NON_ISO_EP_BUFFER_SIZE)?
        MAX_FS_NON_ISO_EP_BUFFER_SIZE:xd_ptr->wmaxpacketsize);
    }

    /* Initialize the End Point Information Structure which is part of device
     * structure. It is done so that it can be used at later point of time
     * like ISR handler, any other function call.
     */
    state_ptr->ep_info[xd_ptr->ep_num].type = xd_ptr->ep_type;
    state_ptr->ep_info[xd_ptr->ep_num].direction = xd_ptr->bdirection;
    state_ptr->ep_info[xd_ptr->ep_num].max_packet_size = max_pkt_size;
    state_ptr->ep_info[xd_ptr->ep_num].endpoint_status = USB_STATUS_IDLE;
    state_ptr->ep_info[xd_ptr->ep_num].stall_flag = FALSE;
    if (USB_RECV == xd_ptr->bdirection)
    {
        state_ptr->ep_info[xd_ptr->ep_num].rx_data0 = 0;
        state_ptr->ep_info[xd_ptr->ep_num].recv_xd = NULL;
    }
    else
    {
        state_ptr->ep_info[xd_ptr->ep_num].tx_data0 = 0;
        state_ptr->ep_info[xd_ptr->ep_num].send_xd = NULL;
    }

    usb_hal_khci_endpoint_enable_handshake(state_ptr->usbRegBase, xd_ptr->ep_num, ((xd_ptr->ep_type != USB_ISOCHRONOUS_PIPE) ? 1 : 0));
    usb_hal_khci_endpoint_set_direction(state_ptr->usbRegBase, xd_ptr->ep_num, (xd_ptr->bdirection ? 1 : 0));
    if ((USB_RECV == xd_ptr->bdirection) && (xd_ptr->ep_num == USB_CONTROL_ENDPOINT))
    {
        _usb_khci_next_setup_token_prep(state_ptr);
    }
#if 0
    /* Write the initialized control values to end point control register*/
    //usb_hal_set_endpoint_ephshk(state_ptr->usbRegBase, xd_ptr->ep_num, (xd_ptr->ep_type != USB_ISOCHRONOUS_PIPE ? 1 : 0));
    /*Configure this endpoint for receive or Send direction as required by APP*/
    //usb_hal_set_endpoint_direction(state_ptr->usbRegBase, xd_ptr->ep_num, (xd_ptr->bdirection ? 1: 0));
    /* Set the BDT and buffer data pointer for Receive Direction*/
    if ((USB_RECV == xd_ptr->bdirection) && (xd_ptr->ep_num == USB_CONTROL_ENDPOINT) )
    {
        const uint8_t control[2] =
        {
            USB_BD_DATA01(0) | USB_BD_DTS | USB_BD_OWN,
            USB_BD_DATA01(1) | USB_BD_DTS
        };

        /* configure first start address for recv transaction */
        usb_dci_khci_get_xd (state_ptr, &xd_temp_ptr);
        xd_temp_ptr->ep_num = xd_ptr->ep_num;
        xd_temp_ptr->bdirection = xd_ptr->bdirection;
        xd_temp_ptr->wtotallength =xd_ptr->wtotallength;
#if USBCFG_4BYTE_ALIGN_FIX
        xd_temp_ptr->internal_dma_align = TRUE;
#endif
        xd_temp_ptr->wsofar = xd_ptr->wsofar;
        xd_temp_ptr->ep_type = xd_ptr->ep_type;
        xd_temp_ptr->dont_zero_terminate = xd_ptr->dont_zero_terminate;
        xd_temp_ptr->wstartaddress = (uint8_t *)USB_LONG_LE_TO_HOST((uint32_t)state_ptr->setup_buff);
        USB_XD_QUEUE_ENQUEUE(&state_ptr->ep_info[xd_ptr->ep_num].xd_queue_recv, xd_temp_ptr);

        /*Configure Even buff for the end point*/
        BD_ADDR_RX(xd_ptr->ep_num, state_ptr->ep_info[xd_ptr->ep_num].rx_buf_odd) =
                USB_LONG_LE_TO_HOST((uint32_t)state_ptr->setup_buff);
        
        BD_CTRL_RX(xd_ptr->ep_num, state_ptr->ep_info[xd_ptr->ep_num].rx_buf_odd) =
                USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(SETUP_PACKET_LENGTH) | control[0]));

        /*Configure Even buff for odd end point*/
        BD_ADDR_RX(xd_ptr->ep_num, state_ptr->ep_info[xd_ptr->ep_num].rx_buf_odd ^ 1) =
                USB_LONG_LE_TO_HOST((uint32_t)
                (state_ptr->setup_buff + SETUP_PACKET_LENGTH));
        BD_CTRL_RX(xd_ptr->ep_num, state_ptr->ep_info[xd_ptr->ep_num].rx_buf_odd ^ 1) =
                USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(SETUP_PACKET_LENGTH) | control[1]));
    }
    else /* Set the BDT and buffer data pointer for Send direction */
    {
        /* Initialize the DATA PID to DATA0*/
        //state_ptr->EP_INFO[xd_ptr->EP_NUM].tx_data0 = 0;
    }
#endif
    return USB_OK;
}

/**************************************************************************//*!
 * @name  : usb_dci_khci_deinit_endpoint
 *
 * @brief       : De-Initialize the Endpoint
 * @param handle: Handle to USB Device.
 * @param ep_num: End Point Number.
 * @param direction: USB_SEND or USB_RECV.
 * @return      :  USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_deinit_endpoint
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    uint8_t ep_num,
    /*[IN]*/
    uint8_t direction
)
{
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;
    //volatile USB_MemMapPtr usb_ptr;

    /*before de-initializing cancel all transfers on EP */
    usb_dci_khci_cancel(handle, ep_num, direction);

    /*Disable the transmit or receive endpoint*/
    usb_hal_khci_endpoint_shut_down(state_ptr->usbRegBase, ep_num);

    /* un-initialize the structure for this endpoint */
    usb_hal_khci_bdt_set_address((uint32_t )bdt, ep_num, direction, EVEN_BUFF, USB_LONG_LE_TO_HOST_CONST((uint32_t)USB_UNINITIALIZED_VAL_32));
    usb_hal_khci_bdt_set_address((uint32_t )bdt, ep_num, direction, ODD_BUFF, USB_LONG_LE_TO_HOST_CONST((uint32_t)USB_UNINITIALIZED_VAL_32));
    //BD_ADDR(ep_num,direction,EVEN_BUFF) =
    //    USB_LONG_LE_TO_HOST_CONST((uint32_t)USB_UNINITIALIZED_VAL_32);
    //BD_ADDR(ep_num,direction,ODD_BUFF) =
    //    USB_LONG_LE_TO_HOST_CONST((uint32_t)USB_UNINITIALIZED_VAL_32);

    state_ptr->ep_info[ep_num].max_packet_size =
    (uint16_t)USB_UNINITIALIZED_VAL_32;

    /* mark this endpoint as de-initialized */
    state_ptr->ep_info[ep_num].ep_init_flag[direction] = FALSE;

    return USB_OK;
}

/**************************************************************************//*!
 * @name  usb_dci_khci_send
 * @brief       : Sends data. Non-blocking.
 * @param handle: Handle to USB Device.
 * @param xd_ptr: Transaction Descriptor.
 * @return      :  USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_send
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    xd_struct_t* xd_ptr
    )
{
    usb_status error = USBERR_TX_FAILED;/* initializing to failed value */
    uint32_t buf_num_bytes = (uint32_t)(xd_ptr->wtotallength - xd_ptr->wsofar);
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;

    /* Allocate XD structure from Free List maintained by Device structure,
     * if it is not any split transaction.
     */
    if (xd_ptr->wsofar == 0)
    {
        state_ptr->ep_info[xd_ptr->ep_num].send_xd = xd_ptr;
        //USB_XD_QUEUE_ENQUEUE(&state_ptr->ep_info[xd_ptr->ep_num].xd_queue_send, xd_ptr);
        //USB_PRINTF("after send ep %d enqueue: xd_head_ptr 0x%x xd_tail_ptr 0x%x\n", xd_ptr->EP_NUM, 
        //        state_ptr->EP_INFO[xd_ptr->EP_NUM].xd_queue_send.xd_head_ptr,
        //        state_ptr->EP_INFO[xd_ptr->EP_NUM].xd_queue_send.xd_tail_ptr);

    }

#if 0
    /* Upper layer wants to send Zero Packet data
     * Note that this situation will only come when
     * Upper layer wants to send Zero packet data not
     * in case of split transaction
     */
    if (buf_num_bytes == 0)
    {
        error = _usb_khci_ep_write(state_ptr, xd_ptr->ep_num,
        xd_ptr->wstartaddress, buf_num_bytes, (uint32_t*)&buf_num_bytes);

        if (error != USB_OK)
        {
            /* If write returns error release the XD pointer
             * from Endpoint send queue and return it to Free list of XD pointers.
             */
            xd_ptr->bstatus = USB_STATUS_IDLE;
            //USB_XD_QUEUE_DEQUEUE (&state_ptr->ep_info[xd_ptr->ep_num].xd_queue_send, &xd_ptr);
            //if (xd_ptr != NULL)
            //    _usb_khci_free_XD(state_ptr, xd_ptr);
        }
        return error;
    }
#endif
    if (state_ptr->is_reseting == 0)
    {
        /* If not Zero Size packet send the data from here*/
        error = _usb_khci_ep_write(state_ptr, xd_ptr->ep_num,
            (uint8_t *)xd_ptr->wstartaddress + xd_ptr->wsofar, buf_num_bytes,
            (uint32_t*)&buf_num_bytes);
    }

    if (error != USB_OK)
    {
        /* If write returns error release the XD pointer
         * from Endpoint send queue and return it to Free list of XD pointers.
         */
        //xd_ptr->bstatus = USB_STATUS_IDLE;
        state_ptr->ep_info[xd_ptr->ep_num].send_xd = NULL;
        //USB_XD_QUEUE_DEQUEUE (&state_ptr->ep_info[xd_ptr->ep_num].xd_queue_send, &xd_ptr);
        //if (xd_ptr != NULL)
        usb_dci_khci_free_xd(state_ptr, xd_ptr);
    }
    return error;
}

/**************************************************************************//*!
 * @name        : usb_dci_khci_recv
 * @brief       : Receives data. Non-blocking.
 * @param handle: Handle to USB Device.
 * @param xd_ptr: Transaction Descriptor.
 * @return      : USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_recv
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    xd_struct_t* xd_ptr
)
{
    usb_status error = USBERR_RX_FAILED;/* initializing to failed value */
    uint32_t buf_num_bytes;
    uint8_t *buf_ptr;
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;

    buf_num_bytes = xd_ptr->wtotallength - xd_ptr->wsofar;

    /* Allocate XD structure from Free List maintained by Device structure,
     * if it is not any split transaction.
     */

    if (xd_ptr->wsofar == 0)
    {
        //USB_XD_QUEUE_ENQUEUE(&state_ptr->ep_info[xd_ptr->ep_num].xd_queue_recv, xd_ptr);
        state_ptr->ep_info[xd_ptr->ep_num].recv_xd = xd_ptr;
    }

    /* If the number of bytes to be received is greater than the
     * maximum data that can be received on the USB bus, then split the
     * transaction into multiple receive transaction.
     */
    if (buf_num_bytes > state_ptr->ep_info[xd_ptr->ep_num].max_packet_size)
    {
        buf_num_bytes = state_ptr->ep_info[xd_ptr->ep_num].max_packet_size;
    }

    /* Send the receive command to the device.*/
    buf_ptr = (uint8_t *)((uint32_t)xd_ptr->wstartaddress + (uint32_t)xd_ptr->wsofar);
#if USBCFG_KHCI_4BYTE_ALIGN_FIX
    if ((_usb_khci_dev_swap_buf_ptr) && ((buf_num_bytes & USB_DMA_ALIGN_MASK) || ((uint32_t)buf_ptr & USB_DMA_ALIGN_MASK)))
    {
        xd_ptr->internal_dma_align = FALSE;
        buf_ptr = (uint8_t*)USB_DMA_ALIGN((int32_t)_usb_khci_dev_swap_buf_ptr);
    }
#endif
    if (state_ptr->is_reseting == 0)
    {
        error = _usb_khci_ep_read((usb_khci_dev_state_struct_t*)handle, xd_ptr->ep_num, buf_ptr, buf_num_bytes);
    }

    if (error != USB_OK)
    {
        //USB_XD_QUEUE_DEQUEUE(&state_ptr->ep_info[xd_ptr->ep_num].xd_queue_recv, &xd_ptr);
        //_usb_khci_free_XD(state_ptr, xd_ptr);
        state_ptr->ep_info[xd_ptr->ep_num].recv_xd = NULL;
        usb_dci_khci_free_xd(state_ptr, xd_ptr);
    }

    if ((buf_num_bytes == 0) && (xd_ptr->ep_num == USB_CONTROL_ENDPOINT))
    {
        usb_dci_khci_free_xd(state_ptr, xd_ptr);

        state_ptr->ep_info[USB_CONTROL_ENDPOINT].rx_buf_odd ^= 1;
        _usb_khci_next_setup_token_prep(state_ptr);
        // prime the next setup transaction here
    }
    return error;
}

/**************************************************************************//*!*
 * @name  : usb_dci_khci_stall_endpoint
 * @brief      : Stalls the specified endpoint
 * @param handle: Handle to USB Device.
 * @param ep_num: End Point Number.
 * @param direction: USB_SEND or USB_RECV.
 * @return      :  USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_stall_endpoint
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    uint8_t ep_num,
    /*[IN]*/
    uint8_t direction
)
{
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;
    //USB_MemMapPtr usb_ptr;

    /* set  the stall flag in device structure to be true */
    state_ptr->ep_info[ep_num].stall_flag = TRUE;
    state_ptr->ep_info[ep_num].endpoint_status = USB_STATUS_STALLED;

    /* retiring pending IRPs on stall detection */
    usb_dci_khci_cancel(handle, ep_num, direction);

    /* If Stall is for Send packet update Send BDT */
    if (direction)
    {
        /* USB_SEND */
        usb_hal_khci_bdt_set_control((uint32_t )bdt, ep_num, USB_SEND, state_ptr->ep_info[ep_num].tx_buf_odd,
            USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(state_ptr->ep_info[ep_num].max_packet_size)| USB_BD_OWN | USB_BD_STALL | USB_BD_DTS)));
        //BD_CTRL_TX(ep_num, state_ptr->ep_info[ep_num].tx_buf_odd) =
        //    USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(state_ptr->ep_info[ep_num].max_packet_size)| USB_BD_OWN | USB_BD_STALL | USB_BD_DTS));
    }
    else
    {
        /* USB_RECV */
        usb_hal_khci_bdt_set_control((uint32_t )bdt, ep_num, USB_RECV, state_ptr->ep_info[ep_num].rx_buf_odd,
            USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(state_ptr->ep_info[ep_num].max_packet_size)| USB_BD_OWN | USB_BD_STALL | USB_BD_DTS)));
        /* If Stall is for Receive transaction, Update Receive BDT*/
        //BD_CTRL_RX(ep_num, state_ptr->ep_info[ep_num].rx_buf_odd) =
        //    USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(state_ptr->ep_info[ep_num].max_packet_size) | USB_BD_OWN | USB_BD_STALL | USB_BD_DTS));
    }

    /* Continue Further processing as the IP stops on receiving
     * Setup Token.
     */
    usb_hal_khci_clr_token_busy(state_ptr->usbRegBase);

    return USB_OK;
}

/**************************************************************************//*!*
 * @name  : usb_dci_khci_unstall_endpoint
 * @brief       : Unstall the Endpoint in specific direction
 * @param handle: Handle to USB Device.
 * @param ep_num: End Point Number.
 * @param direction: USB_SEND or USB_RECV.
 * @return      :  USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_unstall_endpoint
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    uint8_t ep_num,
    /*[IN]*/
    uint8_t direction
)
{
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;
    //USB_MemMapPtr usb_ptr;

    /* clear  the stall flag in device structure */
    state_ptr->ep_info[ep_num].stall_flag = FALSE;
    state_ptr->ep_info[ep_num].endpoint_status = USB_STATUS_IDLE;

    usb_hal_khci_endpoint_clr_stall(state_ptr->usbRegBase, ep_num);

    if (direction)
    {/* USB_SEND */
        usb_hal_khci_endpoint_enable_handshake(state_ptr->usbRegBase, ep_num, 1);
        usb_hal_khci_endpoint_set_direction(state_ptr->usbRegBase, ep_num, 1);
        state_ptr->ep_info[ep_num].tx_data0 = 0;
        /*BD_CTRL_TX(ep_num, state_ptr->ep_info[ep_num].tx_buf_odd) =
            USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(state_ptr->ep_info[ep_num].max_packet_size) |
            USB_BD_DTS | USB_BD_DATA01(0)));*/
        usb_hal_khci_bdt_set_control((uint32_t )bdt, ep_num, USB_SEND, state_ptr->ep_info[ep_num].tx_buf_odd,
            USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(state_ptr->ep_info[ep_num].max_packet_size)| USB_BD_DTS | USB_BD_DATA01(0))));
    }
    else
    {/* USB_RECV */
        usb_hal_khci_endpoint_enable_handshake(state_ptr->usbRegBase, ep_num, 1);
        usb_hal_khci_endpoint_set_direction(state_ptr->usbRegBase, ep_num, 0);
        state_ptr->ep_info[ep_num].rx_data0 = 0;
        if (ep_num == USB_CONTROL_ENDPOINT)
        {
            /* something important need to do is toggle the tx buffer odd */
            //state_ptr->ep_info[USB_CONTROL_ENDPOINT].tx_buf_odd ^= 1;
            _usb_khci_next_setup_token_prep(state_ptr);
        }
        else
        {
            usb_hal_khci_bdt_set_control((uint32_t )bdt, ep_num, USB_RECV, state_ptr->ep_info[ep_num].rx_buf_odd,
                USB_LONG_LE_TO_HOST((uint32_t)(USB_BD_BC(state_ptr->ep_info[ep_num].max_packet_size)| USB_BD_DTS | USB_BD_DATA01(0))));
        }
    }

    usb_hal_khci_clr_token_busy(state_ptr->usbRegBase);
    return USB_OK;
}

/**************************************************************************//*!*
 * @name  : usb_dci_khci_cancel
 * @brief : Cancels all pending transfers on an endpoint.
 * @param handle: Handle to USB Device.
 * @param ep_num: End Point Number.
 * @param direction: USB_SEND or USB_RECV.
 * @return      :  USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_cancel
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    uint8_t ep_num,
    /*[IN]*/
    uint8_t direction
)
{
    usb_event_struct_t event;
    xd_struct_t* xd_ptr = NULL;
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;

    if (direction == USB_RECV)
    {
        xd_ptr = state_ptr->ep_info[ep_num].recv_xd;
        state_ptr->ep_info[ep_num].recv_xd = NULL;
    }
    else
    {
        xd_ptr = state_ptr->ep_info[ep_num].send_xd;
        state_ptr->ep_info[ep_num].send_xd = NULL;
    }
    if (xd_ptr != NULL)
    {
        usb_dci_khci_free_xd(handle, xd_ptr);
        event.len = 0xFFFFFFFF;
        event.buffer_ptr = xd_ptr->wstartaddress;
        event.handle = (usb_device_handle)state_ptr->upper_layer_handle;
        event.ep_num = ep_num;
        event.setup = FALSE;
        event.direction = direction;
        _usb_device_call_service(ep_num, &event);
    }
#if 0
    if (direction)
    {
        tempQueue = &state_ptr->ep_info[ep_num].xd_queue_send;
    }
    else
    {
        tempQueue = &state_ptr->ep_info[ep_num].xd_queue_recv;
    }

    /* Empty the queue and add the XD release structure to the Free list*/
    do
    {
        USB_XD_QUEUE_DEQUEUE(tempQueue, &xd_temp_ptr);

        if (xd_temp_ptr)
        {
            xd_temp_ptr->bstatus = USB_STATUS_IDLE;
            event.len = 0xFFFFFFFF;
            event.buffer_ptr = xd_temp_ptr->wstartaddress;
            event.handle = (usb_device_handle)state_ptr->upper_layer_handle;
            event.ep_num = ep_num;
            event.setup = FALSE;
            event.direction = direction;
            _usb_khci_free_XD(state_ptr, xd_temp_ptr);
            _usb_device_call_service(ep_num,&event);
        }
    }
    while (xd_temp_ptr);
#endif
    return USB_OK;
}

/**************************************************************************//*!*
 * @name  : usb_dci_khci_set_addr
 * @brief       : Set device address.
 * @param handle : Device handle.
 * @param addr :   Address to be set into Device Address register.
 * @return     :   Returns USB_OK or error code.
 ******************************************************************************/
usb_status usb_dci_khci_set_addr
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    uint8_t addr
)
{
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;
    //volatile USB_MemMapPtr usb_ptr;

    /* Update USB address in Device registers. This 7-bit value
     * defines the USB address that the USB Module decodes
     * in device mode
     */
    usb_hal_khci_set_device_addr(state_ptr->usbRegBase, addr);

    /* Update the USB device address in Device Info structure for
     * Future References.
     */
    state_ptr->device_address = addr;
    /* Set the Device Start as Address Assigned State.*/
    state_ptr->usb_state = USB_STATE_ADDRESS;

    return USB_OK;
}

/**************************************************************************//*!*
 * @name : usb_dci_khci_shutdown
 * @brief      : Shuts down the usbfs Device Controller
 *                   Note: There is no function in MQX to uninstall ISR.
 *                         Hence ISR is not Uninstalled here.However, installing
 *                         ISR twice will not have any negative impact.
 * @param handle : Device handle.
 * @return     :   Returns USB_OK or error code.
 ******************************************************************************/
usb_status usb_dci_khci_shutdown
(
    /*[IN]*/
    usb_device_handle handle
    )
{
#ifdef USBCFG_OTG
    usb_otg_state_struct_t * usb_otg_struct_ptr = (usb_otg_state_struct_t *)g_usb_otg_handle;
    usb_otg_status_t * otg_status_ptr = &usb_otg_struct_ptr->otg_status;
#endif    
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;

    /* Reset the Control Register */
    //usb_hal_khci_reset_controller(handle->usbRegBase);/* disables the USB MODULE */
    usb_hal_khci_disable_interrupts(state_ptr->usbRegBase, 0xFF);
    usb_hal_khci_set_device_addr(state_ptr->usbRegBase, 0);

    usb_hal_khci_clear_control_register(state_ptr->usbRegBase);

    usb_hal_khci_enable_pull_down(state_ptr->usbRegBase);
    usb_hal_khci_set_suspend(state_ptr->usbRegBase);

    state_ptr->usb_state = USB_STATE_UNKNOWN;
    OS_Mutex_destroy(state_ptr->mutex);

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    if (NULL != g_khci_data_ptr)
    {
        OS_Mem_free(g_khci_data_ptr);
        g_khci_data_ptr = NULL;
    }

#if (FSL_FEATURE_USB_KHCI_USB_RAM == 0)
    if (NULL != g_khci_bdt_ptr)
    {
        OS_Mem_free(g_khci_bdt_ptr);
        g_khci_bdt_ptr = NULL;
    }
#endif

#endif
#ifdef USBCFG_OTG
    otg_status_ptr->active_stack = USB_ACTIVE_STACK_NONE;
    usb_otg_struct_ptr->dev_inst_ptr = NULL;
#endif
    return USB_OK;
}

#if USBCFG_DEV_ADVANCED_SUSPEND_RESUME
/**************************************************************************//*!*
 * @name  : usb_dci_khci_assert_resume
 * @brief : Resume signaling for remote wakeup
 * @param handle: Handle to USB Device.
 * @return      :  USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_assert_resume
(
    /*[IN]*/
    usb_device_handle handle 
)
{
    uint16_t delay_count;
    //volatile USB_MemMapPtr usb_ptr;
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;

    /* clear resume FLAG*/
    usb_hal_khci_clr_interrupt(handle->usbRegBase, INTR_RESUME);

    /* Disable RESUME Interrupt */
//    usb_ptr->INTEN &= ~USB_INTEN_RESUME_EN_MASK; //already done in RESUME interrupt
    /* continue processing */
    usb_hal_khci_clr_token_busy(handle->usbRegBase);

    /* Start RESUME signaling and make SUSPEND bit 0*/
    usb_hal_khci_start_resume(handle->usbRegBase);

    /* Set RESUME line for 1-15 ms*/
    delay_count = ASSERT_RESUME_DELAY_COUNT;
    do
    {
        delay_count--;
    }while (delay_count);

    /* Stop RESUME signaling */
    usb_hal_khci_stop_resume(handle->usbRegBase);

    return USB_OK;
}
#endif

/**************************************************************************//*!*
 * @name : usb_dci_khci_get_endpoint_status
 * @brief : Get Endpoint Transfer Status
 * @param handle: Handle to USB Device.
 * @param component: End Point Number.
 * @param endp_status: Variable containing endpint status..
 * @return      :  USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_get_endpoint_status
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    uint8_t component,
    /*[OUT]*/
    uint16_t* endp_status
)
{
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;

    *endp_status = state_ptr->ep_info[component & USB_STATUS_ENDPOINT_NUMBER_MASK].endpoint_status;
    return USB_OK;
}

/**************************************************************************//*!*
 * @name  : usb_dci_khci_set_endpoint_status
 * @brief   : Set Endpoint Transfer Status
 * @param handle: Handle to USB Device.
 * @param component: End Point Number.
 * @param setting: Variable containing new settings..
 * @return      :  USB_OK or error code
 ******************************************************************************/
usb_status usb_dci_khci_set_endpoint_status
(
    /*[IN]*/
    usb_device_handle handle,
    /*[IN]*/
    uint8_t component,
    /*[IN]*/
    uint16_t setting
)
{
    usb_khci_dev_state_struct_t* state_ptr = (usb_khci_dev_state_struct_t*)handle;
    usb_status error = USBERR_ERROR;/* initializing */
    uint8_t ep_num = (uint8_t)(component & USB_STATUS_ENDPOINT_NUMBER_MASK);
    /* direction is in most significant bit */
    uint8_t direction = (uint8_t)((component >> COMPONENT_PREPARE_SHIFT) & 1U);

    state_ptr->ep_info[ep_num].endpoint_status = setting;

    /* check if the setting was to halt endpoint or unhalt it*/
    if (setting == USB_STATUS_STALLED)
    { /* stall the endpoint */
        error = usb_dci_khci_stall_endpoint(handle, ep_num, direction);
    }
    else if ((setting == USB_STATUS_IDLE) && (state_ptr->ep_info[ep_num].stall_flag))
    {
        /* unstall the endpoint*/
        /* need to update the direction here for unstalling
           (as it was not passed from above layers for unstall because the
           STAT register doesn't get updated in STALL ISR and we need to unstall
           directly from STALL_SERVICE for CONTROL ENDPOINT. Therefore, this
           method of unstall was employed to make the structure generic)*/
        direction = state_ptr->ep_info[ep_num].direction;
        error = usb_dci_khci_unstall_endpoint(handle, ep_num, direction);
    }

    return error;
}

/*FUNCTION*----------------------------------------------------------------
 *
 * Function Name  : usb_dci_khci_set_status
 * Returned Value : USB_OK or error code
 * Comments       :
 *     Provides API to set internal state
 *
 *END*--------------------------------------------------------------------*/
usb_status usb_dci_khci_set_status
(
    /* [IN] Handle to the usb device */
    usb_device_handle handle,

    /* [IN] What to set the error of */
    uint8_t component,

    /* [IN] What to set the error to */
    uint16_t setting
)
{
    usb_khci_dev_state_struct_t* usb_dev_ptr;
    uint8_t error = USB_OK;

    usb_dev_ptr = (usb_khci_dev_state_struct_t*)handle;
    OS_Mutex_lock(usb_dev_ptr->mutex);

    switch(component)
    {
    case USB_STATUS_DEVICE_STATE:
        usb_dev_ptr->usb_state = setting;
        break;
    case USB_STATUS_DEVICE:
        usb_dev_ptr->usb_device_status = setting;
        break;
    case USB_STATUS_INTERFACE:
        break;
    case USB_STATUS_CURRENT_CONFIG:
        usb_dev_ptr->usb_curr_config = setting;
        break;
    case USB_STATUS_SOF_COUNT:
        usb_dev_ptr->usb_sof_count = setting;
        break;
#ifdef USBCFG_OTG
        case USB_STATUS_OTG:
        usb_dev_ptr->usb_otg_status = setting;
        break;
#endif  
    default:

        break;
    }/* Endswitch */

    OS_Mutex_unlock(usb_dev_ptr->mutex);
    return error;
} /* EndBody */

/*FUNCTION*----------------------------------------------------------------
 *
 * Function Name  : usb_dci_khci_get_status
 * Returned Value : USB_OK or error code
 * Comments       :
 *     Provides API to access the USB internal state.
 *
 *END*--------------------------------------------------------------------*/
usb_status usb_dci_khci_get_status
(
    /* [IN] Handle to the USB device */
    usb_device_handle handle,

    /* [IN] What to get the error of */
    uint8_t component,

    /* [OUT] The requested error */
    uint16_t* error
)
{
    usb_khci_dev_state_struct_t* usb_dev_ptr;

    usb_dev_ptr = (usb_khci_dev_state_struct_t*)handle;

    OS_Mutex_lock(usb_dev_ptr->mutex);
    switch(component)
    {
    case USB_STATUS_DEVICE_STATE:
        *error = usb_dev_ptr->usb_state;
        break;

    case USB_STATUS_DEVICE:
        *error = usb_dev_ptr->usb_device_status;
        break;

    case USB_STATUS_INTERFACE:
        break;

    case USB_STATUS_ADDRESS:
        *error = usb_dev_ptr->device_address;
        break;

    case USB_STATUS_CURRENT_CONFIG:
        *error = usb_dev_ptr->usb_curr_config;
        break;
    case USB_STATUS_SOF_COUNT:
        *error = usb_dev_ptr->usb_sof_count;
        break;
    case USB_STATUS_SPEED:
        *error = usb_dev_ptr->speed;
        break;
#ifdef USBCFG_OTG
        case USB_STATUS_OTG:
        *error = usb_dev_ptr->usb_otg_status;
        break;
#endif 
    default:
        break;
    } /* Endswitch */
    OS_Mutex_unlock(usb_dev_ptr->mutex);
    return USB_OK;
}

usb_status usb_dci_khci_reset
(
    /* [IN] Handle to the USB device */
    usb_device_handle handle
)
{
    usb_khci_dev_state_struct_t* usb_dev_ptr;
    uint8_t cnt = 0;

    usb_dev_ptr = (usb_khci_dev_state_struct_t*)handle;

    /* De-Init All the End Point.  */
    for (cnt = 0; cnt < USBCFG_DEV_MAX_ENDPOINTS; cnt++)
    {
        usb_dci_khci_deinit_endpoint(usb_dev_ptr, cnt, USB_RECV);
        usb_dci_khci_deinit_endpoint(usb_dev_ptr, cnt, USB_SEND);
    }

    /* Re-Initialize All the end point */
    _usb_khci_reset_ep_state((usb_khci_dev_state_struct_t*)usb_dev_ptr);
    usb_dci_khci_init_xd((usb_device_handle)usb_dev_ptr);
    usb_dev_ptr->is_reseting = 0;
    return USB_OK;
}
#endif
