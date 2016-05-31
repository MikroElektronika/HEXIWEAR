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
* $FileName: ehci_dev_main.c$
* $Version : 3.8.14.0$
* $Date    : Jul-2-2012$
*
* Comments:
*
*   This file contains the main VUSBHS USB Device Controller interface
*   functions.
*
*END*********************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "usb_device_config.h"
#if USBCFG_DEV_EHCI
#include "usb.h"

#include "usb_device_stack_interface.h"

#include "ehci_dev_main.h"
#include "ehci_usbprv.h"

#include "fsl_usb_ehci_hal.h"
#include "usb_dev.h"

#if USBCFG_DEV_EHCI_PIN_DETECT_ENABLE
#include "usb_pin_detect.h"
usb_pin_detect_service_t device_pin_detect_service[USBCFG_DEV_EHCI_NUM];
#endif

#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK))

#if defined( __ICCARM__ )
    #pragma data_alignment=2048
    __no_init usb_device_ehci_data_t g_ehci_data[USBCFG_DEV_EHCI_NUM];
#elif defined (__CC_ARM) || defined(__GNUC__)
    __attribute__((aligned(2048))) usb_device_ehci_data_t g_ehci_data[USBCFG_DEV_EHCI_NUM];
#else
    #error Unsupported compiler, please use IAR, Keil or arm gcc compiler and rebuild the project.
#endif

#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    usb_device_ehci_data_t* g_ehci_data_ptr[USBCFG_DEV_EHCI_NUM] = {NULL};
#endif

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/

/****************************************************************************
 * Global Functions
 ****************************************************************************/

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM))             /* USB stack running on MQX */
    void _usb_dci_usbhs_isr(usb_device_handle handle);
#endif
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
void _usb_dci_usbhs_isr
   (
      /* [IN] the USB Host state structure */
      void
   );
#endif
/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Local Variables
 *****************************************************************************/

extern usb_status _usb_device_call_service(uint8_t type,usb_event_struct_t* event);
extern uint8_t soc_get_usb_vector_number(uint8_t controller_id);
extern uint32_t soc_get_usb_base_address(uint8_t controller_id);

usb_ehci_dev_state_struct_t g_ehci_dev[USBCFG_DEV_EHCI_NUM];
#if USBCFG_DEV_EHCI_PIN_DETECT_ENABLE 
/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_device_register_pin_detect_service
*  @return   USB_OK on successful.
*  Comments       :
*        get id detector pin status 
*END*-----------------------------------------------------------------*/
usb_status usb_device_register_pin_detect_service
(
    /* [IN] type of event or endpoint number to service */
    uint8_t                    controller_id,
    /* [IN] Pointer to the service's callback function */
    usb_pin_detect_service_t        service,
    /*[IN] User Argument to be passed to Services when invoked.*/
    void*                      arg
)
{
    if (controller_id < USB_CONTROLLER_EHCI_0)
    {
        return USBERR_INVALID_DEVICE_NUM;
    }
    if (service != NULL)
    {
        device_pin_detect_service[controller_id - USB_CONTROLLER_EHCI_0] = service;
    }
    
    return USB_OK;
}
/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_pin_detector_get_id_status
*  Returned Value : id is 0 indicate host mode, 1 indicate device mode
*  Comments       :
*        get id detector pin status 
*END*-----------------------------------------------------------------*/
uint8_t usb_pin_detector_get_id_status
(
    /* [IN] usb controller  id  */
    uint8_t                    controller_id
)
{
    if (controller_id < USB_CONTROLLER_EHCI_0)
    {
        return USBERR_INVALID_DEVICE_NUM;
    }
    return (usb_hal_ehci_get_otg_status(soc_get_usb_base_address(controller_id))& USBHS_OTGSC_ID_MASK) >> USBHS_OTGSC_ID_SHIFT;

}
#endif
/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_khci_free_XD
*  Returned Value : void
*  Comments       :
*        Enqueues a XD onto the free XD ring.
*
*END*-----------------------------------------------------------------*/

void _usb_ehci_free_XD
   (
     usb_device_handle  handle,
      /* [IN] the dTD to enqueue */
     xd_struct_t*       xd_ptr
   )
{ /* Body */
    usb_ehci_dev_state_struct_t * usb_dev_ptr = (usb_ehci_dev_state_struct_t *)
        handle;
    struct xd_struct*      xd_ptr_tmp;

    /*
     ** This function can be called from any context, and it needs mutual
     ** exclusion with itself.
     */
    OS_Lock();

    xd_ptr_tmp = usb_dev_ptr->xd_head;
    while(xd_ptr_tmp)
    {
        if(xd_ptr == xd_ptr_tmp)
        {
            /* Already in free list */
            OS_Unlock();
            return;
        }
        xd_ptr_tmp = xd_ptr_tmp->next;
    }
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
    usb_dev_ptr->xd_entries ++;
    
    OS_Unlock();
} /* Endbody */

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
/********************************************************************/
/**************************************************************************//*!
*
* @name        : usb_dci_usbhs_preinit
* @brief       : Allocates space for the USB device controller.
* @param handle: Handle to USB Device to be filled
* @return   USB_OK on successful.
******************************************************************************/
usb_status usb_dci_usbhs_preinit
(
    /* [IN] the USB device handle */
    usb_device_handle upper_layer_handle,
    /* [IN] the USB device handle */
    usb_device_handle  *handle_ptr
)
{
  
  usb_dev_state_struct_t*                 usb_dev_state_ptr;
  usb_ehci_dev_state_struct_t *           usb_dev_ptr;
  xd_struct_t*                            xd_ptr;
  uint32_t                                j;
  
  usb_dev_state_ptr = (usb_dev_state_struct_t*)upper_layer_handle;
  usb_dev_ptr = (usb_ehci_dev_state_struct_t *) (&g_ehci_dev[usb_dev_state_ptr->controller_id - USB_CONTROLLER_EHCI_0]);
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
  for(j = 0; j < USBCFG_DEV_EHCI_NUM; j++)
  {
      if(NULL == g_ehci_data_ptr[j])
      {
          g_ehci_data_ptr[j] = OS_Mem_alloc_uncached_align(sizeof(usb_device_ehci_data_t), 2048);
      }
  }
#endif    
  if (NULL != usb_dev_ptr)
  {
    usb_dev_ptr->controller_id = usb_dev_state_ptr->controller_id - USB_CONTROLLER_EHCI_0;

#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK))
    usb_dev_ptr->xd_base = (xd_struct_t*)(&g_ehci_data[usb_dev_ptr->controller_id].xd_base[0]);
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    usb_dev_ptr->xd_base = (xd_struct_t*)g_ehci_data_ptr[usb_dev_ptr->controller_id]->xd_base;
#endif

    usb_dev_ptr->xd_head = NULL;
    usb_dev_ptr->xd_tail = NULL;
    usb_dev_ptr->xd_entries = 0;

    /* Enqueue all the XDs */   
    xd_ptr = (xd_struct_t*) usb_dev_ptr->xd_base;

    for (j = 0; j < USBCFG_DEV_MAX_XDS; j++) 
    {
        _usb_ehci_free_XD(usb_dev_ptr, xd_ptr);
        xd_ptr++;
    }

    *handle_ptr = (usb_device_handle) usb_dev_ptr;
    usb_dev_ptr->upper_layer_handle = upper_layer_handle;
  }
  else
  {
      return USBERR_ALLOC;
  }
  
  return USB_OK;
  
}

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_init
*  Returned Value : USB_OK or error code
*  Comments       :
*        Initializes the USB device controller.
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_init
(
    uint8_t     controller_id,
    /* [IN] the USB device handle */
    usb_device_handle         handle
)
{   /* Body */
    usb_ehci_dev_state_struct_t * usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    if (usb_dev_ptr == NULL) {
        return USBERR_INVALID_DEVICE_NUM;
    }

    usb_dev_ptr->dev_vec = soc_get_usb_vector_number(controller_id);
   
    /* Get the maximum number of endpoints supported by this USB controller */
    usb_dev_ptr->usb_state = USB_STATE_UNKNOWN;

    usb_dev_ptr->usbRegBase = soc_get_usb_base_address(controller_id);
   
    usb_dev_ptr->cap_base_ptr = (void *)((uint8_t*)soc_get_usb_base_address(controller_id)+ 0x100);
   
    /* Get the maximum number of endpoints supported by this USB controller */
    usb_dev_ptr->max_endpoints =
        (uint8_t)((usb_hal_ehci_get_dcc_params(usb_dev_ptr->usbRegBase)&
         USBHS_MAX_ENDPTS_SUPPORTED) & 0x000000FF);

    if(((uint8_t)USBCFG_DEV_EHCI_MAX_ENDPOINTS) < usb_dev_ptr->max_endpoints)
    {
         USB_PRINTF("EHCI: Endpoint num large than USBCFG_DEV_EHCI_MAX_ENDPOINTS\n");
         return USBERR_ERROR;
    }

    /****************************************************************
     Assign QH base
     ****************************************************************/
#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK))
    usb_dev_ptr->qh_base_ptr = (usb_ehc_dev_qh_struct_t *)(&g_ehci_data[controller_id - USB_CONTROLLER_EHCI_0].qh_base[0]);
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    usb_dev_ptr->qh_base_ptr = (usb_ehc_dev_qh_struct_t *)g_ehci_data_ptr[controller_id - USB_CONTROLLER_EHCI_0]->qh_base;
#endif

    /****************************************************************
     Assign DTD base
     ****************************************************************/
#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK))
    usb_dev_ptr->dtd_base_ptr = (usb_ehci_dev_dtd_struct_t *)(&g_ehci_data[controller_id - USB_CONTROLLER_EHCI_0].dtd_base[0]);
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    usb_dev_ptr->dtd_base_ptr = (usb_ehci_dev_dtd_struct_t *)g_ehci_data_ptr[controller_id - USB_CONTROLLER_EHCI_0]->dtd_base;
#endif

    /* Install the interrupt service routine */
#if (OS_ADAPTER_ACTIVE_OS != OS_ADAPTER_SDK)
    if (!(OS_install_isr(usb_dev_ptr->dev_vec,_usb_dci_usbhs_isr,(void *)usb_dev_ptr)))
    {
        #ifdef _DEV_DEBUG
            USB_PRINTF("USB_Install_isr failed.\n");
        #endif
        return USBERR_INSTALL_ISR;
    }
#else
    OS_install_isr(usb_dev_ptr->dev_vec, _usb_dci_usbhs_isr, (void*)usb_dev_ptr);
#endif
    usb_dev_ptr->usb_state = USB_STATE_UNKNOWN;

    /* Initialize the VUSB_HS controller */
    _usb_dci_usbhs_chip_initialize(usb_dev_ptr);
#if USBCFG_DEV_EHCI_PIN_DETECT_ENABLE
    usb_hal_ehci_disable_otg_interrupts(usb_dev_ptr->usbRegBase, 0xff000000);
    usb_hal_ehci_enable_otg_interrupts(usb_dev_ptr->usbRegBase, USBHS_OTGSC_IDIE_MASK);
#endif

    return USB_OK;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_chip_initialize
*  Returned Value : USB_OK or error code
*  Comments       :
*        Initializes the USB device controller.
*
*END*-----------------------------------------------------------------*/
void _usb_dci_usbhs_chip_initialize
(
    /* [IN] the USB_dev_initialize state structure */
    usb_ehci_dev_state_struct_t *       handle
)
{   /* Body */
    usb_ehci_dev_state_struct_t *          usb_dev_ptr;
    volatile usb_ehc_dev_reg_struct_t *             cap_dev_ptr;
    volatile usb_ehc_dev_qh_struct_t *              ep_queue_head_ptr;
    usb_ehci_dev_dtd_struct_t *            dTD_ptr;
    uint8_t                                         temp;
    uint8_t                                         i;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *) handle;
    if (usb_dev_ptr == NULL) {
        return;
    }

    OS_Lock();

    cap_dev_ptr = (usb_ehc_dev_reg_struct_t *)usb_dev_ptr->cap_base_ptr;
    /* Modify the base address of the VUSB_HS registers, do not use the old one anymore */
    usb_dev_ptr->dev_ptr = (void *) ((uint32_t)cap_dev_ptr +
        (EHCI_REG_READ(cap_dev_ptr->REGISTERS.CAPABILITY_REGISTERS.CAPLENGTH_HCIVER) &
         EHCI_CAP_LEN_MASK));

    /* Program the controller to be the USB device controller */
    usb_hal_ehci_set_controller_device_mode(usb_dev_ptr->usbRegBase);
    usb_hal_ehci_disable_setup_lock(usb_dev_ptr->usbRegBase);
#if (ENDIANNESS == BIG_ENDIAN)
    usb_hal_ehci_set_big_endian(usb_dev_ptr->usbRegBase);
#else
    usb_hal_ehci_set_little_endian(usb_dev_ptr->usbRegBase);
#endif

    temp = (uint8_t)(usb_dev_ptr->max_endpoints * 2);

    /* Initialize the internal dTD head and tail to NULL */
    usb_dev_ptr->dtd_head = NULL;
    usb_dev_ptr->dtd_tail = NULL;

    ep_queue_head_ptr = usb_dev_ptr->qh_base_ptr;

    /* Initialize all device queue heads */
    for (i = 0; i < temp; i++)
    {
        /* Interrupt on Setup packet */
        /*EHCI_MEM_WRITE((ep_queue_head_ptr + i)->MAX_PKT_LENGTH,
            ((uint32_t)USB_MAX_CTRL_PAYLOAD <<
                VUSB_EP_QUEUE_HEAD_MAX_PKT_LEN_POS)
            | VUSB_EP_QUEUE_HEAD_IOS);
            */
        usb_hal_ehci_set_max_packet_length((ep_queue_head_ptr + i),USB_MAX_CTRL_PAYLOAD);
        usb_hal_ehci_set_next_dtd_terminate((ep_queue_head_ptr + i));
    }

    /* Configure the Endpoint List Address */
    usb_hal_ehci_set_eplist_address(usb_dev_ptr->usbRegBase, (uint32_t)ep_queue_head_ptr);

    dTD_ptr = usb_dev_ptr->dtd_base_ptr;
    usb_dev_ptr->dtd_entries = 0;

    /* Enqueue all the dTDs */
    for (i=0;i<USBCFG_DEV_EHCI_MAX_DTD;i++)
    {
        /* Set the dTD to be invalid */
        usb_hal_ehci_set_next_dtd_invalid(dTD_ptr);
        /* Set the Reserved fields to 0 */
        usb_hal_ehci_clear_ioc_reserved_fields(dTD_ptr);
        _usb_dci_usbhs_free_dTD(usb_dev_ptr, dTD_ptr);
        dTD_ptr++;
    }

    /*--- Initial Configuration ---*/
    /* Initialize the endpoint 0 properties */
#if 0
    EHCI_REG_WRITE(dev_ptr->REGISTERS.OPERATIONAL_DEVICE_REGISTERS.ENDPTCTRLX[0],
        (EHCI_EPCTRL_TX_DATA_TOGGLE_RST | EHCI_EPCTRL_RX_DATA_TOGGLE_RST));
    EHCI_REG_CLEAR_BITS(dev_ptr->REGISTERS.OPERATIONAL_DEVICE_REGISTERS.ENDPTCTRLX[0],
        0 );
#endif

    /* Enable interrupts */
    /* There is no need to enable SOF Interrupt as its generated automatically
       by hardware irrespective of device attachment status */
    usb_hal_ehci_enable_interrupts((usb_dev_ptr->usbRegBase), (EHCI_INTR_INT_EN | EHCI_INTR_ERR_INT_EN |
        EHCI_INTR_PORT_CHANGE_DETECT_EN | EHCI_INTR_RESET_EN
        |EHCI_INTR_DEVICE_SUSPEND));
 
    /* Enable the interrupts */
    OS_Unlock();

    usb_dev_ptr->usb_state = USB_STATE_UNKNOWN;

    /* Set the OTG Termination bit: not needed; the device termination is done with USBCMD:RS bit
        ** when B session is active: see below
        */
    /* Set the Run bit in the command register */
    usb_hal_ehci_initiate_attach_event(usb_dev_ptr->usbRegBase);

} /* EndBody */


/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_free_dTD
*  Returned Value : void
*  Comments       :
*        Enqueues a dTD onto the free DTD ring.
*
*END*-----------------------------------------------------------------*/

void _usb_dci_usbhs_free_dTD
(
    usb_ehci_dev_state_struct_t* handle,
    /* [IN] the dTD to enqueue */
    usb_ehci_dev_dtd_struct_t*  dTD_ptr
)
{   /* Body */
    usb_ehci_dev_state_struct_t * usb_dev_ptr = (usb_ehci_dev_state_struct_t *) handle;

    /*
    ** This function can be called from any context, and it needs mutual
    ** exclusion with itself.
    */
    OS_Lock();

    /*
    ** Add the dTD to the free dTD queue (linked via PRIVATE) and
    ** increment the tail to the next descriptor
    */    
    if ((usb_dev_ptr->dtd_head) == NULL) 
    {
        (usb_dev_ptr->dtd_head) = (dTD_ptr);
    }
    else
    {
        (usb_dev_ptr->dtd_tail)->NEXT_TR_ELEM_PTR = (uint32_t) (dTD_ptr);
    } /* Endif */
    (usb_dev_ptr->dtd_tail) = (dTD_ptr);
    ((usb_ehci_dev_dtd_struct_t*)dTD_ptr)->NEXT_TR_ELEM_PTR = 0;
   
    usb_dev_ptr->dtd_entries++;
    OS_Unlock();
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_add_dTD
*  Returned Value : USB_OK or error code
*  Comments       :
*        Adds a device transfer descriptor(s) to the queue.
*
*END*-----------------------------------------------------------------*/
uint8_t _usb_dci_usbhs_add_dTD
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle,

    /* [IN] The transfer descriptor address */
    xd_struct_t*              xd_ptr
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *  usb_dev_ptr;
    usb_ehci_dev_dtd_struct_t *    dTD_ptr = NULL;
    usb_ehci_dev_dtd_struct_t *    temp_dTD_ptr = NULL;
    usb_ehci_dev_dtd_struct_t *    first_dTD_ptr = NULL;
    usb_ehc_dev_qh_struct_t *      ep_queue_head_ptr;
    uint32_t                                curr_pkt_len;
    uint32_t                                remaining_len;
    uint32_t                                curr_offset;
    uint32_t                                bit_pos;
    uint32_t                                addr;
    uint32_t                                ep_status;
    uint8_t                                 temp;

    /*********************************************************************
     For a optimal implementation, we need to detect the fact that
     we are adding DTD to an empty list. If list is empty, we can
     actually skip several programming steps esp. those for ensuring
     that there is no race condition.The following bool will be useful
     in skipping some code here.
     *********************************************************************/
    bool                                    list_empty = FALSE;
    bool                                    read_safe;

    OS_Lock();

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    remaining_len = xd_ptr->wtotallength;

    curr_offset = 0;
    temp = (uint8_t)(2 * xd_ptr->ep_num + xd_ptr->bdirection);
    bit_pos = (uint32_t)(1 << (16 * xd_ptr->bdirection + xd_ptr->ep_num));

    ep_queue_head_ptr = (usb_ehc_dev_qh_struct_t *)
        usb_hal_ehci_get_eplist_address(usb_dev_ptr->usbRegBase) +
        temp;

   /*********************************************************************
    This loops iterates through the length of the transfer and divides
    the data in to DTDs each handling the a max of 0x4000 bytes of data.
    The first DTD in the list is stored in a void *called first_dTD_ptr.
    This void *is later linked in to QH for processing by the hardware.
    *********************************************************************/

    do
    {
        /* Check if we need to split the transfer into multiple dTDs */
        if(remaining_len > VUSB_EP_MAX_LENGTH_TRANSFER)
        {
            curr_pkt_len = VUSB_EP_MAX_LENGTH_TRANSFER;
        }
        else
        {
            curr_pkt_len = remaining_len;
        }

        remaining_len -= curr_pkt_len;
    
        /* Get a dTD from the queue */
        dTD_ptr = usb_dev_ptr->dtd_head;
        if (usb_dev_ptr->dtd_head)
        {
            usb_dev_ptr->dtd_head = (usb_ehci_dev_dtd_struct_t *)(usb_dev_ptr->dtd_head->NEXT_TR_ELEM_PTR);
            if (usb_dev_ptr->dtd_head == NULL)
            {
                usb_dev_ptr->dtd_tail = NULL;
            } /* Endif */
        } /* Endif */
       
        if (!dTD_ptr)
        {
            OS_Unlock();
            return USBERR_TR_FAILED;
        }

        usb_dev_ptr->dtd_entries--;

        if (curr_offset == 0)
        {
            first_dTD_ptr = dTD_ptr;
        }

        usb_hal_ehci_clear_dtd(dTD_ptr);

        /* Initialize the dTD */

        /* Set the Terminate bit */
        usb_hal_ehci_set_dtd_next_tr_elem_terminate(dTD_ptr);

        /*************************************************************
         FIX ME: For high-speed and high-bandwidth ISO IN endpoints,
         we must initialize the multiplied field so that Host can issues
         multiple IN transactions on the endpoint. See the DTD data
         structure for MultiIO field.

         S Garg 11/06/2003
         *************************************************************/

        /* Set the reserved field to 0 */
        usb_hal_ehci_clear_ioc_reserved_fields(dTD_ptr);
        
        /* 4K apart buffer page pointers */
        
        addr = (uint32_t)(xd_ptr->wstartaddress + curr_offset);

        usb_hal_ehci_set_dtd_buffer_address(dTD_ptr,addr);
        curr_offset += curr_pkt_len;

        /* Fill in the transfer size */
        if (!remaining_len)
        {
            usb_hal_ehci_set_dtd_size_ioc_status(dTD_ptr,((curr_pkt_len << USBHS_TD_LENGTH_BIT_POS) | USBHS_TD_IOC | USBHS_TD_STATUS_ACTIVE));
        }
        else
        {
            usb_hal_ehci_set_dtd_size_ioc_status(dTD_ptr,((curr_pkt_len << USBHS_TD_LENGTH_BIT_POS) | USBHS_TD_STATUS_ACTIVE));
        }
        /* Maintain the first and last device transfer descriptor per
              endpoint and direction */
        if (!usb_dev_ptr->dtd_heads[temp])
        {
            usb_dev_ptr->dtd_heads[temp] = dTD_ptr;
            /***********************************************
             If list does not have a head, it means that list
             is empty. An empty condition is detected.
             ***********************************************/
            list_empty = TRUE;
        }

        /* Check if the transfer is to be queued at the end or beginning */
        temp_dTD_ptr = usb_dev_ptr->dtd_tails[temp];

        /* Remember which XD to use for this dTD */
        dTD_ptr->xd_for_this_dtd = (void *)xd_ptr;

        /* New tail */
        usb_dev_ptr->dtd_tails[temp] = dTD_ptr;

        if (temp_dTD_ptr)
        {
            /* Should not do |=. The Terminate bit should be zero */
            usb_hal_ehci_set_dtd_next_tr_elem_ptr(temp_dTD_ptr, (uint32_t)dTD_ptr);
        }

    } while (remaining_len); /* EndWhile */


    /**************************************************************
     In the loop above DTD has already been added to the list
     However endpoint has not been primed yet. If list is not empty
     we need safer ways to add DTD to the
     existing list. Else we just skip to adding DTD to QH safely.
     **************************************************************/
    if(list_empty) /* If List is Empty : case 1*/
    {
        /* No other transfers on the queue */
        /* Step 1 of Executing a Transfer Descriptor documentation */
        usb_hal_ehci_set_qh_next_dtd(ep_queue_head_ptr, (uint32_t)first_dTD_ptr);
        
        /* Step 2 of Executing a Transfer Descriptor documentation */
        usb_hal_ehci_clear_size_ioc_int_sts( ep_queue_head_ptr);
    
        /* Prime the Endpoint */
        /* Step 3 of Executing a Transfer Descriptor documentation */
        usb_hal_ehci_set_endpoint_prime((usb_dev_ptr->usbRegBase), bit_pos);
    }
    else /* If list is not empty : case 2*/
    {
        /*********************************************************
         Hardware v3.2+ require the use of semaphore to ensure that
         QH is safely updated.
         *********************************************************/

        /*********************************************************
         Check the prime bit. If set return USB_OK
         *********************************************************/
        if (usb_hal_ehci_get_endpoint_prime(usb_dev_ptr->usbRegBase) &
            bit_pos)
        {
            OS_Unlock();
            return USB_OK;
        }

        read_safe = FALSE;
        while(!read_safe)
        {
            /*********************************************************
             start with setting the semaphores
             *********************************************************/
            usb_hal_ehci_set_dtd_tripwire(usb_dev_ptr->usbRegBase);

            /*********************************************************
             read endpoint status, store for later usage
             *********************************************************/
            ep_status = usb_hal_echi_get_endpoint_status(usb_dev_ptr->usbRegBase);
            
            /*********************************************************
             Check the tripwire status
             *********************************************************/
            if(usb_hal_ehci_is_tripwire_set(usb_dev_ptr->usbRegBase))
            {
                read_safe = TRUE;
            }
        } /*end while loop */

        /*********************************************************
                Clear the semaphore
                *********************************************************/
        usb_hal_ehci_clear_dtd_tripwire(usb_dev_ptr->usbRegBase);
        /*********************************************************
                Check endpoint status
                *********************************************************/
        if (!(ep_status & bit_pos)) {
            /* No other transfers on the queue */
            /* Step 1 of Executing a Transfer Descriptor documentation */
            usb_hal_ehci_set_qh_next_dtd(ep_queue_head_ptr, (uint32_t)first_dTD_ptr);
            /* Step 2 of Executing a Transfer Descriptor documentation */
            usb_hal_ehci_clear_size_ioc_int_sts(ep_queue_head_ptr);
            /* Prime the Endpoint */
            /* Step 3 of Executing a Transfer Descriptor documentation */
            usb_hal_ehci_set_endpoint_prime((usb_dev_ptr->usbRegBase), bit_pos);
        }
    }
    
    OS_Unlock();
    return USB_OK;
   /* End CR 1015 */
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_send_data
*  Returned Value : USB_OK or error code
*  Comments       :
*        Sends data by adding and executing the dTD. Non-blocking.
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_send_data
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle,

    /* [IN] The transfer descriptor address */
    xd_struct_t*              xd_ptr
)
{   /* Body */
    /* Add and execute the device transfer descriptor */
    return(_usb_dci_usbhs_add_dTD(handle, xd_ptr));
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_recv_data
*  Returned Value : USB_OK or error code
*  Comments       :
*        Receives data by adding and executing the dTD. Non-blocking.
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_recv_data
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle,

    /* [IN] The transfer descriptor address */
    xd_struct_t*              xd_ptr
)
{   /* Body */
    /* Add and execute the device transfer descriptor */
    return(_usb_dci_usbhs_add_dTD(handle, xd_ptr));
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_process_tr_complete
*  Returned Value : None
*  Comments       :
*        Services transaction complete interrupt
*
*END*-----------------------------------------------------------------*/
void _usb_dci_usbhs_process_tr_complete
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle
)
{   /* Body */
    usb_ehci_dev_state_struct_t *  usb_dev_ptr;
    usb_ehci_dev_dtd_struct_t *    dTD_ptr;
    usb_ehci_dev_dtd_struct_t *    temp_dTD_ptr;
    volatile usb_ehc_dev_qh_struct_t *      ep_queue_head_ptr;
    uint32_t                                remaining_length = 0;
    uint32_t                                actual_transfer_length = 0;
    uint32_t                                errors = 0;
    xd_struct_t*                   xd_ptr;
    xd_struct_t*                   temp_xd_ptr = NULL;
    usb_event_struct_t                      event;
    uint32_t                                bit_pos = 0;
    uint8_t                                 temp;
    uint8_t                                 i;
    uint8_t                                 ep_num;
    uint8_t                                 direction;

//    OS_Lock();
    OS_Mem_zero(&event, sizeof(usb_event_struct_t)); /* Initialize event structure */
     
    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;
    event.handle = (usb_device_handle)usb_dev_ptr->upper_layer_handle;
    /* We use separate loops for ENDPTSETUPSTAT and ENDPTCOMPLETE because the
       setup packets are to be read ASAP */
    /* Process all Setup packet received interrupts */
    bit_pos = usb_hal_ehci_get_ep_setup_status(usb_dev_ptr->usbRegBase);
    if (bit_pos)
    {
        for (i = 0; i < 16; i++)
        {
            if (bit_pos & (uint32_t)(1 << i))
            {
                event.ep_num = USB_CONTROL_ENDPOINT;
                event.setup = TRUE;
                event.direction = USB_RECV;
                event.len = USB_SETUP_PKT_SIZE;
                event.buffer_ptr =
                    (uint8_t *)(&(usb_dev_ptr->setup_buff[0]));
                if(event.buffer_ptr == NULL)
                {
                    #ifdef _DEV_DEBUG
                        USB_PRINTF("1 memalloc failed in _usb_dci_usbhs_process_tr_complete\n");
                    #endif
                    return;
                }
                (void)usb_dci_usbhs_get_setup_data(handle,
                    USB_CONTROL_ENDPOINT,event.buffer_ptr);

                (void)_usb_device_call_service(i, &event);

             } /* Endif */
         } /* Endfor */
    } /* Endif */

   /* Don't clear the endpoint setup status register here. It is cleared as a
      setup packet is read out of the buffer */

    /* Process non-setup transaction complete interrupts */
    bit_pos = usb_hal_ehci_get_ep_complete_status(usb_dev_ptr->usbRegBase);

    /* Clear the bits in the register */
    usb_hal_ehci_clear_ep_complete_status((usb_dev_ptr->usbRegBase), bit_pos);
    
    if (bit_pos)
    {
     
        /* Get the endpoint number and the direction of transfer */
        for (i = 0; i < 32; i++)
        {
            if (bit_pos & (uint32_t)(1 << i))
            {
                if (i > 15)
                {
                    ep_num = (uint8_t)(i - 16);
                    direction = 1;
                }
                else
                {
                    ep_num = i;
                    direction = 0;
                } /* Endif */

                temp = (uint8_t)(2*ep_num + direction);

                /* Get the first dTD */
                dTD_ptr = usb_dev_ptr->dtd_heads[temp];

                ep_queue_head_ptr = (usb_ehc_dev_qh_struct_t *)
                usb_hal_ehci_get_eplist_address(usb_dev_ptr->usbRegBase) +
                temp;

                /* Process all the dTDs for respective transfers */
                while (dTD_ptr)
                {

                    if (usb_hal_ehci_get_dtd_size_ioc_status(dTD_ptr) & USBHS_TD_STATUS_ACTIVE)
                    {
                        /*No more dTDs to process. Next one is owned by VUSB*/
                        break;
                    } /* Endif */

                    /* Get the correct internal transfer descriptor */
                    xd_ptr = (xd_struct_t *)usb_hal_ehci_get_xd_for_this_dtd(dTD_ptr);

                    if (xd_ptr)
                    {
                        actual_transfer_length = xd_ptr->wtotallength;
                        event.buffer_ptr = xd_ptr->wstartaddress;
                        temp_xd_ptr = xd_ptr;
                    } /* Endif */

                    /* Get the address of the next dTD */
                    temp_dTD_ptr = (usb_ehci_dev_dtd_struct_t *)
                    usb_hal_ehci_get_next_dtd_address(dTD_ptr);

                    /* Read the errors */
                    errors = usb_hal_ehci_get_dtd_error_status(dTD_ptr);

                    if (!errors)
                    {
                        /* No errors */
                        /* Get the length of transfer from the current dTD */
                        remaining_length += usb_hal_ehci_get_tr_packet_size(dTD_ptr);
                        actual_transfer_length -= remaining_length;
                    }
                    else
                    {
                        if (errors & USBHS_TD_STATUS_HALTED)
                        {
                            /* Clear the errors and Halt condition */
                            usb_hal_ehci_clear_qh_error_status(ep_queue_head_ptr,errors);
                        } /* Endif */
                    } /* Endif */

                    (void)usb_dci_usbhs_cancel_transfer(handle, ep_num,
                        direction);
                    event.ep_num = ep_num;
                    event.setup = FALSE;
                    event.direction = direction;
                    event.len = actual_transfer_length;
                    if (temp_dTD_ptr)
                    {
                        if((uint32_t)usb_hal_ehci_get_xd_for_this_dtd(temp_dTD_ptr) != (uint32_t)temp_xd_ptr)
                        {
                            /* Transfer complete. Call the register service
                                                function for the endpoint */
                            (void)_usb_device_call_service(ep_num,&event);
                            remaining_length = 0;
                        } /* Endif */
                    }
                    else
                    {
                        if (xd_ptr != NULL)
                        {
                            _usb_ehci_free_XD(usb_dev_ptr, xd_ptr);
							//USB_PRINTF("tf: %d\n\r",usb_dev_ptr->xd_entries);
                        }
                        /* Transfer complete. Call the register service
                           function for the endpoint */
                        (void)_usb_device_call_service(ep_num,&event);
                        remaining_length = 0;
                    } /* Endif */

                    dTD_ptr = temp_dTD_ptr;
                    errors = 0;
                } /* Endwhile */
            } /* Endif */
        } /* Endfor */
    }/* Endif */
//    OS_Unlock();
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_process_reset
*  Returned Value : None
*  Comments       :
*        Services reset interrupt
*
*END*-----------------------------------------------------------------*/
void _usb_dci_usbhs_process_reset
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle
)
{   /* Body */
    usb_ehci_dev_state_struct_t *  usb_dev_ptr;
    uint32_t                                temp;
    uint8_t                                 cnt=0;
    usb_event_struct_t                      event;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* De-Init All the End Point.  */
    for (cnt = 0; cnt < USBCFG_DEV_EHCI_MAX_ENDPOINTS; cnt++)
    {
        usb_dci_usbhs_deinit_endpoint(handle,cnt,USB_RECV);
        usb_dci_usbhs_deinit_endpoint(handle,cnt,USB_SEND);
    }

    /* The address bits are past bit 25-31. Set the address */
    usb_hal_ehci_clear_device_address((usb_dev_ptr->usbRegBase));
    
    /* Clear all the setup token semaphores */
    temp = usb_hal_ehci_get_ep_setup_status(usb_dev_ptr->usbRegBase);
    usb_hal_ehci_clear_ep_setup_status((usb_dev_ptr->usbRegBase), temp);

    /* Clear all the endpoint complete status bits */
    temp = usb_hal_ehci_get_ep_complete_status(usb_dev_ptr->usbRegBase);
    usb_hal_ehci_clear_ep_complete_status((usb_dev_ptr->usbRegBase), temp);

    while (usb_hal_ehci_get_endpoint_prime(usb_dev_ptr->usbRegBase) & 0xFFFFFFFF)
    {
        /* Wait until all ENDPTPRIME bits cleared */
    } /* Endif */

    /* Write 1s to the Flush register */
    usb_hal_ehci_flush_endpoint_buffer((usb_dev_ptr->usbRegBase), 0xFFFFFFFF);

    if (usb_hal_ehci_get_port_status(usb_dev_ptr->usbRegBase) &
        EHCI_PORTSCX_PORT_RESET)
    {
        usb_dev_ptr->bus_resetting = TRUE;
        usb_dev_ptr->usb_state = USB_STATE_POWERED;
    }
    else
    {
        /* re-initialize */
        _usb_dci_usbhs_chip_initialize(usb_dev_ptr);
    } /* Endif */
    event.handle = (usb_device_handle)usb_dev_ptr->upper_layer_handle;
    event.ep_num = USB_CONTROL_ENDPOINT;
    event.setup = FALSE;
    event.direction = USB_RECV;
    event.buffer_ptr = NULL;
    event.len = ZERO_LENGTH;
    /* Inform the application so that it can cancel all previously queued transfers */
    _usb_device_call_service(USB_SERVICE_BUS_RESET,&event);

} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_process_suspend
*  Returned Value : None
*  Comments       :
*        Services suspend interrupt
*
*END*-----------------------------------------------------------------*/
void _usb_dci_usbhs_process_suspend
(
      /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t * usb_dev_ptr;
    usb_event_struct_t                     event;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    usb_dev_ptr->usb_dev_state_b4_suspend = usb_dev_ptr->usb_state;

    usb_dev_ptr->usb_state = USB_STATE_SUSPEND;

    /* Initialize the event structure to be passed to the upper layer*/
    event.handle = (usb_device_handle)usb_dev_ptr->upper_layer_handle;
    event.ep_num = (uint8_t)USB_UNINITIALIZED_VAL_32;
    event.setup = 0;
    event.direction = 0;
    event.buffer_ptr = (uint8_t*)NULL;
    event.len = ZERO_LENGTH;
    /* Inform the upper layers */
    (void)_usb_device_call_service(USB_SERVICE_SLEEP,&event);

} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_process_SOF
*  Returned Value : None
*  Comments       :
*        Services SOF interrupt
*
*END*-----------------------------------------------------------------*/
void _usb_dci_usbhs_process_SOF
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle
)
{   /* Body */
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_process_port_change
*  Returned Value : None
*  Comments       :
*        Services port change detect interrupt
*
*END*-----------------------------------------------------------------*/
void _usb_dci_usbhs_process_port_change
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t * usb_dev_ptr;
    usb_event_struct_t                     event;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* Initialize the event structure to be passed to the upper layer*/
    event.handle = (usb_device_handle)usb_dev_ptr->upper_layer_handle;
    event.ep_num = (uint8_t)USB_UNINITIALIZED_VAL_32;
    event.setup = 0;
    event.direction = 0;

    if (usb_dev_ptr->bus_resetting)
    {
        /* Bus reset operation complete */
        usb_dev_ptr->bus_resetting = FALSE;
    } /* Endif */

    if (!(usb_hal_ehci_get_port_status(usb_dev_ptr->usbRegBase) &
        EHCI_PORTSCX_PORT_RESET))
    {
        /* Get the speed */
        if (usb_hal_ehci_get_port_status(usb_dev_ptr->usbRegBase) &
            EHCI_PORTSCX_PORT_HIGH_SPEED)
        {
            usb_dev_ptr->speed = USB_SPEED_HIGH;
        }
        else
        {
            usb_dev_ptr->speed = USB_SPEED_FULL;
        } /* Endif */
    } /* Endif */

#if USBCFG_DEV_DETACH_ENABLE
    if ((!(usb_hal_ehci_get_port_status(usb_dev_ptr->usbRegBase) &
        EHCI_PORTSCX_CURRENT_CONNECT_STATUS)) &&
        (usb_dev_ptr->usb_state == USB_STATE_CONFIG))
    {
        event.len = ZERO_LENGTH;
        event.buffer_ptr = (uint8_t*)NULL;
        /* Inform the upper layers */
        (void)_usb_device_call_service(USB_SERVICE_DETACH,&event);
    } /* Endif */
#endif

    if (usb_hal_ehci_get_port_status(usb_dev_ptr->usbRegBase) &
        EHCI_PORTSCX_PORT_SUSPEND)
    {
        usb_dev_ptr->usb_dev_state_b4_suspend = usb_dev_ptr->usb_state;
        usb_dev_ptr->usb_state = USB_STATE_SUSPEND;

        event.len = ZERO_LENGTH;
        event.buffer_ptr = (uint8_t*)NULL;
        /* Inform the upper layers */
        (void)_usb_device_call_service(USB_SERVICE_SUSPEND,&event);
    } /* Endif */

    if((!(usb_hal_ehci_get_port_status(usb_dev_ptr->usbRegBase) &
        EHCI_PORTSCX_PORT_SUSPEND)) &&
        (usb_dev_ptr->usb_state == USB_STATE_SUSPEND))
    {
        usb_dev_ptr->usb_state = usb_dev_ptr->usb_dev_state_b4_suspend;

        event.len = ZERO_LENGTH;
        event.buffer_ptr = (uint8_t*)NULL;
        /* Inform the upper layers */
        (void)_usb_device_call_service(USB_SERVICE_RESUME,&event);

        return;
    } /* Endif */

    usb_dev_ptr->usb_state = USB_STATE_DEFAULT;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_process_error
*  Returned Value : None
*  Comments       :
*        Services error interrupt
*
*END*-----------------------------------------------------------------*/
void _usb_dci_usbhs_process_error
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *  usb_dev_ptr;
    
    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* Increment the error count */
    usb_dev_ptr->errors++;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : _usb_dci_usbhs_isr
*  Returned Value : None
*  Comments       :
*        Services all the VUSB_HS interrupt sources
*
*END*-----------------------------------------------------------------*/
#if ((OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX) || (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM))             /* USB stack running on MQX */
    void _usb_dci_usbhs_isr(usb_device_handle handle)
#endif
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
void _usb_dci_usbhs_isr
   (
      /* [IN] the USB Host state structure */
      void
   )
#endif

{   /* Body */
    usb_ehci_dev_state_struct_t *   usb_dev_ptr;
    uint32_t                                 status;
#if (OS_ADAPTER_ACTIVE_OS != OS_ADAPTER_SDK)
    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;
#else
    usb_dev_ptr = (usb_ehci_dev_state_struct_t *) (&g_ehci_dev[0]);
#endif


    status = usb_hal_ehci_get_usb_interrupt_status((usb_dev_ptr->usbRegBase)) &
       usb_hal_ehci_get_interrupt_enable_status((usb_dev_ptr->usbRegBase));
    /* Clear all the interrupts occurred */
    usb_hal_ehci_clear_usb_interrupt_status((usb_dev_ptr->usbRegBase), status);
    if(status & EHCI_STS_RESET)
    {
        /* Print so that user can be notified of reset in general */
        _usb_dci_usbhs_process_reset((void *)usb_dev_ptr);
    }

    if (status & EHCI_STS_INT)
    {
        _usb_dci_usbhs_process_tr_complete((void *)usb_dev_ptr);
    }

    if (status & EHCI_STS_PORT_CHANGE)
    {
        _usb_dci_usbhs_process_port_change((void *)usb_dev_ptr);
    }

    if (status & EHCI_STS_ERR)
    {
        #ifdef _DEV_DEBUG
            USB_PRINTF("USB Error\n");
        #endif
        _usb_dci_usbhs_process_error((void *)usb_dev_ptr);
    }

    if (status & EHCI_STS_SOF)
    {
        _usb_dci_usbhs_process_SOF((void *)usb_dev_ptr);
    }

    if (status & EHCI_STS_SUSPEND)
    {
         //USB_PRINTF("USB EHCI_STS_SUSPEND\n");
        _usb_dci_usbhs_process_suspend((void *)usb_dev_ptr);
        return;
    }
#if USBCFG_DEV_EHCI_PIN_DETECT_ENABLE 
    status = (((usb_hal_ehci_get_otg_status(usb_dev_ptr->usbRegBase)& USBHS_OTGSC_IDIE_MASK) >> USBHS_OTGSC_IDIE_SHIFT))
                    && (((usb_hal_ehci_get_otg_status(usb_dev_ptr->usbRegBase)& USBHS_OTGSC_IDIS_MASK) >> USBHS_OTGSC_IDIS_SHIFT));
    if (status)
    {
         usb_hal_ehci_clear_otg_interrupts(usb_dev_ptr->usbRegBase, USBHS_OTGSC_IDIS_MASK);
        if( device_pin_detect_service[usb_dev_ptr->controller_id ] != NULL)
        {
            device_pin_detect_service[usb_dev_ptr->controller_id ](USB_DEVICE_ID_CHANGE);
        }
        return;
    }
#endif
} /* EndBody */


/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_set_address
*  Returned Value : None
*  Comments       :
*        Sets the newly assigned device address
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_set_address
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle           handle,

    /* Address of the device assigned by the host */
    uint8_t                     address
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *   usb_dev_ptr;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* The address bits are past bit 25-31. Set the address */
    usb_hal_ehci_set_device_address(usb_dev_ptr->usbRegBase,address);
    usb_dev_ptr->device_address = address;
    usb_dev_ptr->usb_state = USB_STATE_ADDRESS;
    return USB_OK;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_get_setup_data
*  Returned Value : None
*  Comments       :
*        Reads the Setup data from the 8-byte setup buffer
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_get_setup_data
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle,

    /* [IN] the Endpoint number */
    uint8_t                   ep_num,

    /* [OUT] address of the buffer to read the setup data into */
    uint8_t                  *buffer_ptr
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *         usb_dev_ptr;
    volatile usb_ehc_dev_qh_struct_t *             ep_queue_head_ptr;
    bool                                           read_safe;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* Get the endpoint queue head */
    ep_queue_head_ptr = (usb_ehc_dev_qh_struct_t *)
        usb_hal_ehci_get_eplist_address(usb_dev_ptr->usbRegBase) +
        2*ep_num + USB_RECV;

    /********************************************************************
     CR 1219. Hardware versions 2.3+ have a implementation of tripwire
     semaphore mechanism that requires that we read the contents of
     QH safely by using the semaphore. Read the USBHS document to under
     stand how the code uses the semaphore mechanism. The following are
     the steps in brief

     1. USBCMD Write ‘1’ to Setup Tripwire in register.
     2. Duplicate contents of dQH.StatusBuffer into local software byte
        array.
     3  Read Setup TripWire in register. (if set - continue; if
        cleared goto 1.)
     4. Write '0' to clear Setup Tripwire in register.
     5. Process setup packet using local software byte array copy and
        execute status/handshake phases.
     ********************************************************************/

    /*if semaphore mechanism is used the following code is compiled in*/
    read_safe = FALSE;
    while(!read_safe)
    {
        /*********************************************************
         start with setting the semaphores
         *********************************************************/

        usb_hal_ehci_set_usb_cmd_setup_trip_wire(usb_dev_ptr->usbRegBase);
        /*********************************************************
         Duplicate the contents of SETUP buffer to our buffer
         Note:On 5329 the data returned is little endian so it needs
         to be byte swapped.Here while copying it is been takencare.
         If you are using this as reference code care should be taken
         while copying the setup packet on your chip.
         *********************************************************/
#if (ENDIANNESS == BIG_ENDIAN)
        buffer_ptr[0]= ep_queue_head_ptr->SETUP_BUFFER[3];
        buffer_ptr[1]= ep_queue_head_ptr->SETUP_BUFFER[2];
        buffer_ptr[2]= ep_queue_head_ptr->SETUP_BUFFER[1];
        buffer_ptr[3]= ep_queue_head_ptr->SETUP_BUFFER[0];
        buffer_ptr[4]= ep_queue_head_ptr->SETUP_BUFFER[7];
        buffer_ptr[5]= ep_queue_head_ptr->SETUP_BUFFER[6];
        buffer_ptr[6]= ep_queue_head_ptr->SETUP_BUFFER[5];
        buffer_ptr[7]= ep_queue_head_ptr->SETUP_BUFFER[4];
#else
        OS_Mem_copy((void *)ep_queue_head_ptr->SETUP_BUFFER,buffer_ptr, 8);
#endif
        /*********************************************************
         If setup tripwire semaphore is cleared by hardware it means
         that we have a danger and we need to restart.
         else we can exit out of loop safely.
         *********************************************************/
        if(usb_hal_ehci_get_usb_cmd(usb_dev_ptr->usbRegBase) &
            EHCI_CMD_SETUP_TRIPWIRE_SET)
        {
            /* we can proceed exiting out of loop*/
            read_safe = TRUE;
        }
    }

    /*********************************************************
     Clear the semaphore bit now
     *********************************************************/
    usb_hal_ehci_clear_usb_cmd_setup_trip_wire(usb_dev_ptr->usbRegBase);

    /* Clear the bit in the ENDPTSETUPSTAT */
    usb_hal_ehci_clear_setup_stat_ep_num(usb_dev_ptr->usbRegBase, (uint32_t)(1 << ep_num));

    return USB_OK;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_init_endpoint
*  Returned Value : None
*  Comments       :
*        Initializes the specified endpoint and the endpoint queue head
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_init_endpoint
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle,

    /* [IN] the transaction descriptor address */
    xd_struct_t*              xd_p
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *       usb_dev_ptr;
    volatile usb_ehc_dev_qh_struct_t *           ep_queue_head_ptr;
    uint32_t                                     bit_pos;
    xd_struct_t*                                 xd_ptr = (xd_struct_t*)xd_p;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    xd_ptr->max_pkts_per_uframe =
      (uint8_t)(((uint8_t)xd_ptr->dont_zero_terminate & (uint8_t)USB_MAX_PKTS_PER_UFRAME) >> 1);

    if((xd_ptr->ep_type > USB_INTERRUPT_PIPE) ||
        (xd_ptr->bdirection > USB_SEND))
    {
        return USBERR_EP_INIT_FAILED;
    }

    /* before initializing cancel all transfers on EP as there may be calls
       for endpoint initialization more than once. This will free any allocated
       queue */
    usb_dci_usbhs_cancel_transfer(handle, xd_ptr->ep_num, xd_ptr->bdirection);
    /* Get the endpoint queue head address */
    ep_queue_head_ptr = (usb_ehc_dev_qh_struct_t *)
        usb_hal_ehci_get_eplist_address(usb_dev_ptr->usbRegBase) +
        2 * xd_ptr->ep_num + xd_ptr->bdirection;

    bit_pos = (uint32_t)(1 << (16 * xd_ptr->bdirection + xd_ptr->ep_num));

    /* Check if the Endpoint is Primed */
    if((!(usb_hal_ehci_get_endpoint_prime(usb_dev_ptr->usbRegBase) & bit_pos))
      &&
      (!(usb_hal_echi_get_endpoint_status(usb_dev_ptr->usbRegBase) & bit_pos)))
    {
        /* Set the max packet length, interrupt on Setup and Mult fields */
        if (xd_ptr->ep_type == USB_ISOCHRONOUS_PIPE)
        {
            /* Mult bit should be set for isochronous endpoints */
            usb_hal_ehci_set_max_packet_length(ep_queue_head_ptr, (uint32_t)(((uint32_t)xd_ptr->wmaxpacketsize << 16) |
               ((uint32_t)(xd_ptr->max_pkts_per_uframe ? xd_ptr->max_pkts_per_uframe : 1)
                << VUSB_EP_QUEUE_HEAD_MULT_POS)));
        }
        else
        {
            if (USB_CONTROL_ENDPOINT == xd_ptr->ep_num)
            {
            usb_hal_ehci_set_max_packet_length_for_non_iso(ep_queue_head_ptr, (uint32_t)
                    (((uint32_t)xd_ptr->wmaxpacketsize << 16) | VUSB_EP_QUEUE_HEAD_IOS | VUSB_EP_QUEUE_HEAD_ZERO_LEN_TER_SEL));
            }
            else
            {
                usb_hal_ehci_set_max_packet_length_for_non_iso(ep_queue_head_ptr, (uint32_t)
                    (((uint32_t)xd_ptr->wmaxpacketsize << 16) |VUSB_EP_QUEUE_HEAD_ZERO_LEN_TER_SEL));
            }
        } /* Endif */

        /* Enable the endpoint for Rx and Tx and set the endpoint type */
        usb_hal_ehci_enable_endpoint(usb_dev_ptr->usbRegBase, xd_ptr->ep_num, xd_ptr->bdirection, xd_ptr->ep_type);
    }
    else
    {
        return USBERR_EP_INIT_FAILED;
    } /* Endif */

    return USB_OK;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_deinit_endpoint
*  Returned Value : None
*  Comments       :
*        Disables the specified endpoint and the endpoint queue head
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_deinit_endpoint
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle           handle,

    /* [IN] the Endpoint number */
    uint8_t                     ep_num,

    /* [IN] direction */
    uint8_t                     direction
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *             usb_dev_ptr;
    volatile usb_ehc_dev_qh_struct_t *                 ep_queue_head_ptr;
    uint32_t                                           bit_pos;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /*before de-initializing cancel all transfers on EP */
    usb_dci_usbhs_cancel_transfer(handle, ep_num, direction);
    /* Ger the endpoint queue head address */
    ep_queue_head_ptr = (usb_ehc_dev_qh_struct_t *)
        usb_hal_ehci_get_eplist_address(usb_dev_ptr->usbRegBase) +
        (2*ep_num + direction);

    bit_pos = (uint32_t)(1 << (16 * direction + ep_num));

    /* Check if the Endpoint is Primed */
    if((!(usb_hal_ehci_get_endpoint_prime(usb_dev_ptr->usbRegBase) & bit_pos))
      &&
      (!(usb_hal_echi_get_endpoint_status(usb_dev_ptr->usbRegBase) & bit_pos)))
    {
        /* Reset the max packet length and the interrupt on Setup */
        usb_hal_ehci_clear_max_packet_length(ep_queue_head_ptr);

        /* Disable the endpoint for Rx or Tx and reset the endpoint type */
        usb_hal_ehci_disable_endpoint(usb_dev_ptr->usbRegBase, ep_num, direction);

        /* TODO: flush buffers. See EHCI EPFLUSH register */
    }
    else
    {
        return USBERR_EP_DEINIT_FAILED;
    }

    return USB_OK;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_get_transfer_status
*  Returned Value : USB_OK or error code
*  Comments       :
*        Gets the status of a transfer
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_get_transfer_status
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle           handle,

    /* [IN] the Endpoint number */
    uint8_t                     ep_num,

    /* [IN] direction */
    uint8_t                     direction
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *    usb_dev_ptr;
    volatile usb_ehci_dev_dtd_struct_t *      dTD_ptr;
    volatile xd_struct_t*                     xd_ptr;
    uint8_t                                   error;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* Unlink the dTD */
    dTD_ptr = usb_dev_ptr->dtd_heads[2*ep_num + direction];

    if (dTD_ptr)
    {
        /* Get the transfer descriptor for the dTD */
        xd_ptr = (xd_struct_t*)dTD_ptr->xd_for_this_dtd;
        error = xd_ptr->bstatus;
    }
    else
    {
        error = USB_STATUS_IDLE;
    }

    return (error);
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_cancel_transfer
*  Returned Value : USB_OK or error code
*  Comments       :
*        Cancels a transfer
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_cancel_transfer
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle           handle,

    /* [IN] the Endpoint number */
    uint8_t                     ep_num,

    /* [IN] direction */
    uint8_t                     direction
)
{   /* Body */
    usb_ehci_dev_state_struct_t *    usb_dev_ptr;
    usb_ehci_dev_dtd_struct_t *      dTD_ptr;
    usb_ehci_dev_dtd_struct_t *      check_dTD_ptr;
    volatile usb_ehc_dev_qh_struct_t *        ep_queue_head_ptr;
    xd_struct_t*                     xd_ptr;
    uint32_t                                  temp;
    uint32_t                                  bit_pos;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    bit_pos = (uint32_t)(1 << (16 * direction + ep_num));
    temp = (uint32_t)(2*ep_num + direction);

    ep_queue_head_ptr = (usb_ehc_dev_qh_struct_t *)
        usb_hal_ehci_get_eplist_address(usb_dev_ptr->usbRegBase) +
        temp;

    /* Unlink the dTD */
    dTD_ptr = usb_dev_ptr->dtd_heads[temp];

    if (dTD_ptr)
    {
        check_dTD_ptr = (usb_ehci_dev_dtd_struct_t *) \
            ((uint32_t)usb_hal_ehci_get_next_dtd_address(dTD_ptr));

        if (usb_hal_ehci_get_dtd_size_ioc_status(dTD_ptr) & USBHS_TD_STATUS_ACTIVE)
        {
            /* Flushing will halt the pipe */
            /* Write 1 to the Flush register */
            usb_hal_ehci_flush_endpoint_buffer(usb_dev_ptr->usbRegBase, bit_pos);
            
            /* Wait until flushing completed */
            while (usb_hal_ehci_is_endpoint_transfer_flushed(usb_dev_ptr->usbRegBase, bit_pos))
            {
                /* ENDPTFLUSH bit should be cleared to indicate this
                   operation is complete */
            }

            while (usb_hal_echi_get_endpoint_status(usb_dev_ptr->usbRegBase) & bit_pos)
            {
                /* Write 1 to the Flush register */
                usb_hal_ehci_flush_endpoint_buffer(usb_dev_ptr->usbRegBase, bit_pos);

                /* Wait until flushing completed */
                while (usb_hal_ehci_is_endpoint_transfer_flushed(usb_dev_ptr->usbRegBase, bit_pos))
                {
                    /* ENDPTFLUSH bit should be cleared to indicate this
                       operation is complete */
                }
            }
        }

        /* Retire the current dTD */
        usb_hal_ehci_clear_size_ioc_sts(dTD_ptr);
        usb_hal_ehci_set_next_dtd_invalid(dTD_ptr);

        /* The transfer descriptor for this dTD */
        xd_ptr = (xd_struct_t*)dTD_ptr->xd_for_this_dtd;
        /* Free the dTD */
        _usb_dci_usbhs_free_dTD(usb_dev_ptr, dTD_ptr);

        /* Update the dTD head and tail for specific endpoint/direction */
        if (!check_dTD_ptr)
        {
            usb_dev_ptr->dtd_heads[temp] = NULL;
            usb_dev_ptr->dtd_tails[temp] = NULL;

            if (xd_ptr)
            {
                /* Free the transfer descriptor */
                _usb_ehci_free_XD(usb_dev_ptr, xd_ptr);
				//USB_PRINTF("cf: %d\n\r",usb_dev_ptr->xd_entries);
            }

            /* No other transfers on the queue */
            usb_hal_ehci_set_next_dtd_terminate(ep_queue_head_ptr);
            usb_hal_ehci_clear_size_ioc_int_sts(ep_queue_head_ptr);
        }
        else
        {
            usb_dev_ptr->dtd_heads[temp] = check_dTD_ptr;

            if (xd_ptr)
            {
                if ((uint32_t)check_dTD_ptr->\
                    xd_for_this_dtd != (uint32_t)xd_ptr)
                {
                    /* Free the transfer descriptor */
                    _usb_ehci_free_XD(usb_dev_ptr, xd_ptr);
					//USB_PRINTF("cf: %d\n\r",usb_dev_ptr->xd_entries);
                }
            }

            if (usb_hal_ehci_get_dtd_size_ioc_status(check_dTD_ptr) & USBHS_TD_STATUS_ACTIVE)
            {
                /* Start CR 1015 */
                /* Prime the Endpoint */
                usb_hal_ehci_set_endpoint_prime(usb_dev_ptr->usbRegBase,bit_pos);

                if (!(usb_hal_echi_get_endpoint_status(usb_dev_ptr->usbRegBase) & bit_pos))
                {
                    while(usb_hal_ehci_get_endpoint_prime(usb_dev_ptr->usbRegBase) & bit_pos)
                    {
                        /* Wait for the ENDPTPRIME to go to zero */
                    }

                    if (usb_hal_echi_get_endpoint_status(usb_dev_ptr->usbRegBase) & bit_pos)
                    {
                        /* The endpoint was not not primed so no other
                        transfers on the queue */
                        return USB_OK;
                    }
                }
                else
                {
                    return USB_OK;
                }

                /* No other transfers on the queue */
                usb_hal_ehci_set_qh_next_dtd(ep_queue_head_ptr,(uint32_t)check_dTD_ptr);
                usb_hal_ehci_clear_size_ioc_int_sts(ep_queue_head_ptr);
               
                /* Prime the Endpoint */
                usb_hal_ehci_set_endpoint_prime(usb_dev_ptr->usbRegBase,bit_pos);
            }
        }
    }

    return USB_OK;
    /* End CR 1015 */
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_shutdown
*  Returned Value : None
*  Comments       :
*        Shuts down the VUSB_HS Device
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_shutdown
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *              usb_dev_ptr;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* Disable interrupts */
    usb_hal_ehci_disable_interrupts(usb_dev_ptr->usbRegBase,
        (EHCI_INTR_INT_EN | EHCI_INTR_ERR_INT_EN | EHCI_INTR_PORT_CHANGE_DETECT_EN | EHCI_INTR_RESET_EN));

    /* Reset the Run the bit in the command register to stop VUSB */
    usb_hal_ehci_initiate_detach_event(usb_dev_ptr->usbRegBase);

    /* Reset the controller to get default values */
    usb_hal_ehci_reset_controller(usb_dev_ptr->usbRegBase);

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
    if(NULL != g_ehci_data_ptr[usb_dev_ptr->controller_id])
    {
        OS_Mem_free(g_ehci_data_ptr[usb_dev_ptr->controller_id]);
        g_ehci_data_ptr[usb_dev_ptr->controller_id] = NULL;
    }
#endif
    return USB_OK;
} /* EndBody */


/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_assert_resume
*  Returned Value : None
*  Comments       :
*        Resume signaling for remote wakeup
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_assert_resume
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle         handle
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *  usb_dev_ptr;
    uint32_t                                temp;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* Assert the Resume signal */
    temp = usb_hal_ehci_get_port_status(usb_dev_ptr->usbRegBase);
    temp &= ~((uint32_t)EHCI_PORTSCX_W1C_BITS);
    temp |= EHCI_PORTSCX_PORT_FORCE_RESUME;
    usb_hal_ehci_set_port_status(usb_dev_ptr->usbRegBase, temp);

    /* Port change interrupt will be asserted at the end of resume
       operation */

   return USB_OK;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_stall_endpoint
*  Returned Value : None
*  Comments       :
*        Stalls the specified endpoint
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_stall_endpoint
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle           handle,

    /* [IN] the Endpoint number */
    uint8_t                     ep_num,

    /* [IN] direction */
    uint8_t                     direction
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *    usb_dev_ptr;
    volatile usb_ehc_dev_qh_struct_t *        ep_queue_head_ptr;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* Get the endpoint queue head address */
    ep_queue_head_ptr = (usb_ehc_dev_qh_struct_t *)
        usb_hal_ehci_get_eplist_address(usb_dev_ptr->usbRegBase) + 2 * ep_num + direction;

    /* Stall the endpoint for Rx or Tx and set the endpoint type */
    if (usb_hal_ehci_is_ios_set(ep_queue_head_ptr))
    {
        /* This is a control endpoint so STALL both directions */
        usb_hal_ehci_stall_both_directions(usb_dev_ptr->usbRegBase, ep_num);
    }
    else
    {
        usb_hal_ehci_stall_specific_direction(usb_dev_ptr->usbRegBase, ep_num, direction);
    }

    return USB_OK;
} /* EndBody */

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : usb_dci_usbhs_unstall_endpoint
*  Returned Value : None
*  Comments       :
*        Unstall the specified endpoint in the specified direction
*
*END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_unstall_endpoint
(
    /* [IN] the USB_dev_initialize state structure */
    usb_device_handle           handle,

    /* [IN] the Endpoint number */
    uint8_t                     ep_num,

    /* [IN] direction */
    uint8_t                     direction
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *  usb_dev_ptr;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    /* Enable the endpoint for Rx or Tx and set the endpoint type */
    usb_hal_ehci_clear_endpoint_stall(usb_dev_ptr->usbRegBase, ep_num, direction);
    usb_hal_ehci_reset_endpoint_data_toggle(usb_dev_ptr->usbRegBase, ep_num, direction);
    return USB_OK;
} /* EndBody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_dci_usbhs_get_endpoint_status
* Returned Value : None
* Comments       :
*     Gets the endpoint status
*
*END*--------------------------------------------------------------------*/
usb_status usb_dci_usbhs_get_endpoint_status
(
    /* [IN] Handle to the USB device */
    usb_device_handle     handle,

    /* [IN] Endpoint to get */
    uint8_t               ep,
    /* [OUT] Status to get */
    uint16_t *error
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t * usb_dev_ptr;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    *error = (uint16_t)((usb_hal_ehci_get_endpoint_control(usb_dev_ptr->usbRegBase, 
            ep & USB_STATUS_ENDPOINT_NUMBER_MASK) &
           (uint32_t)((ep & 0x80) ? (uint32_t)EHCI_EPCTRL_TX_EP_STALL : (uint32_t)EHCI_EPCTRL_RX_EP_STALL)) ? 1 : 0);

    return USB_OK;
} /* EndBody */

#if USBCFG_DEV_EHCI_TEST_MODE
/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_dci_usbhs_set_test_mode
* Returned Value : None
* Comments       :
*     sets/resets the test mode
*
*END*--------------------------------------------------------------------*/
usb_status usb_dci_usbhs_set_test_mode
(
    /* [IN] Handle to the USB device */
    usb_device_handle   handle,

    /* [IN] Test mode */
    uint16_t            test_mode
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *       usb_dev_ptr;
    uint32_t                                     temp;

    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;

    temp = usb_hal_ehci_get_endpoint_control(usb_dev_ptr->usbRegBase, 0);

  //  EHCI_REG_WRITE(dev_ptr->REGISTERS.OPERATIONAL_DEVICE_REGISTERS.ENDPTCTRLX[0], (temp | EHCI_EPCTRL_TX_DATA_TOGGLE_RST));

    temp = usb_hal_ehci_get_port_status(usb_dev_ptr->usbRegBase);
    usb_hal_ehci_set_port_status(usb_dev_ptr->usbRegBase, (temp | ((uint32_t)test_mode << 16)));
    return USB_OK;
} /* EndBody */
#endif

/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_dci_usbhs_set_endpoint_status
* Returned Value : None
* Comments       :
*     Sets the endpoint registers e.g. to enable TX, RX, control
*
*END*--------------------------------------------------------------------*/
usb_status usb_dci_usbhs_set_endpoint_status
(
    /* [IN] Handle to the USB device */
    usb_device_handle     handle,

    /* [IN] Endpoint to set */
    uint8_t               component,

    /* [IN] Endpoint characteristics */
    uint16_t              setting
)
{   /* Body */
    uint8_t error = USBERR_ERROR;
    uint8_t ep_num = (uint8_t)(component & USB_STATUS_ENDPOINT_NUMBER_MASK);
    uint8_t direction = 0;

    if (ep_num > USBCFG_DEV_EHCI_MAX_ENDPOINTS) {
        return error;
    }

    if(setting == USB_STATUS_STALLED)
    {
        error = usb_dci_usbhs_stall_endpoint(handle, ep_num, direction);

    }
    else if(setting == USB_STATUS_IDLE)
    {
        error = usb_dci_usbhs_unstall_endpoint(handle, ep_num, direction);
    } /* Endif */

    return USB_OK;
} /* EndBody */

/*FUNCTION*----------------------------------------------------------------
* 
* Function Name  : usb_dci_khci_set_status
* Returned Value : USB_OK or error code
* Comments       :
*     Provides API to set internal state
* 
*END*--------------------------------------------------------------------*/
usb_status usb_dci_usbhs_set_status
   (
      /* [IN] Handle to the usb device */
      usb_device_handle     handle,
      
      /* [IN] What to set the error of */
      uint8_t               component,
      
      /* [IN] What to set the error to */
      uint16_t              setting
   )
{ 
    volatile usb_ehci_dev_state_struct_t * usb_dev_ptr;
    uint8_t                                error = USB_OK;
    
    if (handle == NULL)
    {
        #if _DEBUG
            USB_PRINTF("usb_dci_khci_set_status: handle is NULL\n");
        #endif  
        return USBERR_ERROR;
    }
    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;
    OS_Lock();
    
    switch (component) 
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
#if USBCFG_DEV_EHCI_TEST_MODE
        case USB_STATUS_TEST_MODE:
            usb_dci_usbhs_set_test_mode(handle, setting);
            usb_dev_ptr->in_test_mode = 1;
            break;
#endif
        default:
            break;
   }/* Endswitch */

   OS_Unlock();
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
usb_status usb_dci_usbhs_get_status
   (
      /* [IN] Handle to the USB device */
      usb_device_handle    handle,
      
      /* [IN] What to get the error of */
      uint8_t              component,
      
      /* [OUT] The requested error */
      uint16_t*            error
   )
{
    volatile usb_ehci_dev_state_struct_t * usb_dev_ptr;

    if((handle == NULL)||(error == NULL))
    {
        #if _DEBUG
            USB_PRINTF("usb_dci_khci_get_status: NULL pointer\n");
        #endif  
        return USBERR_ERROR;
    }
    usb_dev_ptr = (usb_ehci_dev_state_struct_t *)handle;
   
    OS_Lock();
    switch (component) 
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

#if USBCFG_DEV_EHCI_TEST_MODE
        case USB_STATUS_TEST_MODE:
            *error = usb_dev_ptr->in_test_mode;
            break;
#endif
        default:
            break;
   } /* Endswitch */
   OS_Unlock();
   return USB_OK;   
}   
 /*FUNCTION*-------------------------------------------------------------
 *
 *  Function Name  : usb_dci_khci_alloc_xd
 *  Returned Value : void
 *  Comments       :
 *        Allocates an XD from the free XD ring.
 *
 *END*-----------------------------------------------------------------*/
usb_status usb_dci_usbhs_alloc_xd
(
    usb_device_handle handle,
    /* [IN] the dTD to enqueue */
    xd_struct_t* *    xd_ptr_ptr
)
{   /* Body */
    volatile usb_ehci_dev_state_struct_t *   usb_dev_ptr = handle;

    if(!usb_dev_ptr)
    {
        return USBERR_NOT_FOUND;
    }
    
    /* This function can be called from any context, and it needs mutual
       exclusion with itself.*/
    OS_Lock();
    
    /* Get a transfer descriptor for the specified endpoint 
     ** and direction 
     */
    if(!usb_dev_ptr->xd_entries)
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

    //USB_PRINTF("a: %d\n\r",usb_dev_ptr->xd_entries);

    
    OS_Unlock();

    return USB_OK;
} /* Endbody */

#endif
/* EOF */
