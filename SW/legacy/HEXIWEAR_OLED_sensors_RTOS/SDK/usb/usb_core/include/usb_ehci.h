/**HEADER********************************************************************
* 
* Copyright (c) 2008, 2013-2014 Freescale Semiconductor;
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
* $FileName: 
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file contains the defines, externs and
*   data structure definitions required by the VUSB_HS Device
*   driver.
*
*END************************************************************************/
#ifndef __ehci_h__
#define __ehci_h__


typedef  uint32_t  USB_REGISTER;


#define  EHCI_BANDWIDTH_RECORD_ENABLE             (0)

/* should only define these macros if using HIGH SPEED device */
#define USB_OTG_UOCSR_BVLD                  (0x0040)

/* usbhs specific defines */
#define  USBHS_MAX_PORTS                          (8)
#define  EHCI_CAP_LEN_MASK                        (0x000000FF)
#define  EHCI_DATA_STRUCTURE_BASE_ADDRESS         (0)

/* Command Register Bit Masks */
#define  EHCI_CMD_RUN_STOP                         (0x00000001)
#define  EHCI_CMD_CTRL_RESET                       (0x00000002)

/*bit 15,3,2 are for frame list size */
#define  EHCI_CMD_FRAME_SIZE_1024                  (0x00000000) /* 000 */
#define  EHCI_CMD_FRAME_SIZE_512                   (0x00000004) /* 001 */
#define  EHCI_CMD_FRAME_SIZE_256                   (0x00000008) /* 010 */
#define  EHCI_CMD_FRAME_SIZE_128                   (0x0000000C) /* 011 */
#define  EHCI_CMD_FRAME_SIZE_64                    (0x00008000) /* 100 */
#define  EHCI_CMD_FRAME_SIZE_32                    (0x00008004) /* 101 */
#define  EHCI_CMD_FRAME_SIZE_16                    (0x00008008) /* 110 */
#define  EHCI_CMD_FRAME_SIZE_8                     (0x0000800C) /* 111 */

#define  EHCI_CMD_ATDTW_TRIPWIRE_SET               (0x00004000)
#define  EHCI_CMD_ATDTW_TRIPWIRE_CLEAR             ~EHCI_CMD_SETUP_TRIPWIRE_CLEAR
#define  EHCI_CMD_SETUP_TRIPWIRE_SET               (0x00002000)
#define  EHCI_CMD_SETUP_TRIPWIRE_CLEAR             ~EHCI_CMD_SETUP_TRIPWIRE_SET
#define  EHCI_STS_NAK                              (0x00010000)
#define  EHCI_STS_TIMER0                           (0x01000000)
#define  EHCI_QTD_CERR_BITS_MASK                   (0x00000C00)
#define  EHCI_QTD_STATUS_BABBLE_DETECTED           (0X0010)
#define  EHCI_QTD_CERR_BITS_MASK                   (0x00000C00)

/* Mode Register Bit Masks */
#define  USBHS_MODE_CTRL_MODE_IDLE                (0x00000000)
#define  USBHS_MODE_CTRL_MODE_DEV                 (0x00000002)
#define  USBHS_MODE_CTRL_MODE_HOST                (0x00000003)
#define  USBHS_MODE_BIG_ENDIAN                    (0x00000004)
#define  USBHS_MODE_SETUP_LOCK_DISABLE            (0x00000008)

/* Interrupt Enable Register Bit Masks */
#define  EHCI_INTR_INT_EN                          (0x00000001)
#define  EHCI_INTR_ERR_INT_EN                      (0x00000002)
#define  EHCI_INTR_PORT_CHANGE_DETECT_EN           (0x00000004)

#define  EHCI_INTR_ASYNC_ADV_AAE                   (0x00000020)
         #define  EHCI_INTR_ASYNC_ADV_AAE_ENABLE   (0x00000020) /* | with this to enable */
         #define  EHCI_INTR_ASYNC_ADV_AAE_DISABLE  (0xFFFFFFDF) /* & with this to disable */

#define  EHCI_INTR_RESET_EN                        (0x00000040)
#define  EHCI_INTR_SOF_UFRAME_EN                   (0x00000080)
#define  EHCI_INTR_DEVICE_SUSPEND                  (0x00000100)
#define  USB_INTR_ULPII_EN                         (0x00000400)
/* Interrupt Status Register Masks */
#define  EHCI_STS_SOF                              (0x00000080)
#define  EHCI_STS_RESET                            (0x00000040)
#define  EHCI_STS_PORT_CHANGE                      (0x00000004)
#define  EHCI_STS_ERR                              (0x00000002)
#define  EHCI_STS_INT                              (0x00000001)
#define  EHCI_STS_SUSPEND                          (0x00000100)
#define  EHCI_STS_HC_HALTED                        (0x00001000)
#define  USB_STS_ULPII                             (0x00000400)

/* Endpoint Queue Head Bit Masks */
#define  VUSB_EP_QUEUE_HEAD_IOS                    (0x00008000)
#define  VUSB_EP_QUEUE_HEAD_IOC                    (0x00008000)
#define  VUSB_EP_QUEUE_HEAD_INT                    (0x00000100)
#define  VUSB_EP_QUEUE_HEAD_NEXT_TERMINATE         (0x00000001)
#define  VUSB_EP_QUEUE_HEAD_MAX_PKT_LEN_POS        (16)
#define  VUSB_EP_QUEUE_HEAD_ZERO_LEN_TER_SEL       (0x20000000)
#define  VUSB_EP_QUEUE_HEAD_MULT_POS               (30)
#define  VUSB_EP_MAX_LENGTH_TRANSFER               (0x4000)

#define  VUSB_EP_QUEUE_HEAD_STATUS_ACTIVE          (0x00000080)

#define  USBHS_TD_NEXT_TERMINATE                  (0x00000001)
#define  USBHS_TD_IOC                             (0x00008000)
#define  USBHS_TD_STATUS_ACTIVE                   (0x00000080)
#define  USBHS_TD_STATUS_HALTED                   (0x00000040)
#define  USBHS_TD_RESERVED_FIELDS                 (0x00007F00)
#define  USBHS_TD_ERROR_MASK                      (0x68)
#define  USBHS_TD_ADDR_MASK                       (0xFFFFFFE0)
#define  USBHS_TD_LENGTH_BIT_POS                  (16)

#define  EHCI_EPCTRL_TX_DATA_TOGGLE_RST            (0x00400000)
#define  EHCI_EPCTRL_TX_EP_STALL                   (0x00010000)
#define  EHCI_EPCTRL_RX_EP_STALL                   (0x00000001)
#define  EHCI_EPCTRL_RX_DATA_TOGGLE_RST            (0x00000040)
#define  EHCI_EPCTRL_RX_ENABLE                     (0x00000080)
#define  EHCI_EPCTRL_TX_ENABLE                     (0x00800000)
#define  EHCI_EPCTRL_CONTROL                       (0x00000000)
#define  EHCI_EPCTRL_ISOCHRONOUS                   (0x00040000)
#define  EHCI_EPCTRL_BULK                          (0x00080000)
#define  EHCI_EPCTRL_INT                           (0x000C0000)
#define  EHCI_EPCTRL_TX_TYPE                       (0x000C0000)
#define  EHCI_EPCTRL_RX_TYPE                       (0x0000000C)
#define  EHCI_EPCTRL_DATA_TOGGLE_INHIBIT           (0x00000020)
#define  EHCI_EPCTRL_TX_EP_TYPE_SHIFT              (18)
#define  EHCI_EPCTRL_RX_EP_TYPE_SHIFT              (2)

#define  EHCI_PORTSCX_PORT_POWER                   (0x00001000)
#define  EHCI_PORTSCX_LINE_STATUS_BITS             (0x00000C00)
#define  EHCI_PORTSCX_LINE_STATUS_SE0              (0x00000000)
#define  EHCI_PORTSCX_LINE_STATUS_KSTATE           (0x00000400)
#define  EHCI_PORTSCX_LINE_STATUS_JSTATE           (0x00000800)
#define  EHCI_PORTSCX_PORT_HIGH_SPEED              (0x00000200)
#define  EHCI_PORTSCX_PORT_RESET                   (0x00000100)
#define  EHCI_PORTSCX_PORT_SUSPEND                 (0x00000080)
#define  EHCI_PORTSCX_PORT_FORCE_RESUME            (0x00000040)
#define  EHCI_PORTSCX_PORT_EN_DIS_CHANGE           (0x00000008)
#define  EHCI_PORTSCX_PORT_ENABLE                  (0x00000004)
#define  EHCI_PORTSCX_CONNECT_STATUS_CHANGE        (0x00000002)
#define  EHCI_PORTSCX_CURRENT_CONNECT_STATUS       (0x00000001)

#define  USBHS_PORTSCX_PORT_SPEED_FULL            (0x00000000)
#define  USBHS_PORTSCX_PORT_SPEED_LOW             (0x04000000)
#define  USBHS_PORTSCX_PORT_SPEED_HIGH            (0x08000000)
#define  USBHS_SPEED_MASK                         (0x0C000000)
#define  USBHS_SPEED_BIT_POS                      (26)

#define  EHCI_PORTSCX_W1C_BITS                     (0x2A)

#define  VUSB_EP_TR_PACKET_SIZE                    (0x7FFF0000)

#define  USBHS_FRINDEX_MS_MASK                    (0xFFFFFFF8)
#define  USBHS_ADDRESS_BIT_SHIFT                  (25)

#define  USBHS_MAX_ENDPTS_SUPPORTED               (0x1F)
#define  EHCI_HCC_PARAMS_64_BIT_ADDR_CAP           (0x01)
#define  EHCI_HCC_PARAMS_PGM_FRM_LIST_FLAG         (0x02)
#define  EHCI_HCC_PARAMS_ASYNC_PARK_CAP            (0x04)
#define  EHCI_HCC_PARAMS_ISOCH_SCHED_THRESHOLD     (0xF0)
#define  EHCI_HCC_PARAMS_ISOCH_FRAME_CACHED        (0x80)

#define  USBHS_HCS_PARAMS_PORT_POWER_CONTROL_FLAG (0x10)

#define  USBHS_HOST_INTR_EN_BITS                  (0x37)

#define  USBHS_DEFAULT_PERIODIC_FRAME_LIST_SIZE   (1024)
#define  USBHS_NEW_PERIODIC_FRAME_LIST_BITS       (2)
#define  EHCI_FRAME_LIST_ELEMENT_POINTER_T_BIT     (0x01)
#define  EHCI_ITD_T_BIT                            (0x01)
#define  EHCI_SITD_T_BIT                           (0x01)
#define  EHCI_QUEUE_HEAD_POINTER_T_BIT             (0x01)


/************************************************************
Split transatcions specific defines
************************************************************/
#define  EHCI_START_SPLIT_MAX_BUDGET               188

#define  EHCI_ELEMENT_TYPE_ITD                     (0x00)
#define  EHCI_ELEMENT_TYPE_QH                      (0x02)
#define  EHCI_ELEMENT_TYPE_SITD                    (0x04)
#define  EHCI_ELEMENT_TYPE_FSTN                    (0x06)
#define  EHCI_ELEMENT_TYPE_MASK                    (0x06)

#define  EHCI_FRAME_LIST_ELEMENT_TYPE_ITD          (0x00)
#define  EHCI_FRAME_LIST_ELEMENT_TYPE_QH           (0x01)
#define  EHCI_FRAME_LIST_ELEMENT_TYPE_SITD         (0x02)
#define  EHCI_FRAME_LIST_ELEMENT_TYPE_FSTN         (0x03)
#define  EHCI_FRAME_LIST_ELEMENT_TYPE_BIT_POS      (1)


#define  EHCI_QH_ELEMENT_TYPE_ITD                  (0x00)
#define  EHCI_QH_ELEMENT_TYPE_QH                   (0x01)
#define  EHCI_QH_ELEMENT_TYPE_SITD                 (0x02)
#define  EHCI_QH_ELEMENT_TYPE_FSTN                 (0x03)

#define  EHCI_QH_ELEMENT_TYPE_BIT_POS              (1)

#define  EHCI_QTD_PID_OUT_TOKEN                    (0x000)
#define  EHCI_QTD_PID_IN_TOKEN                     (0x100)
#define  EHCI_QTD_PID_SETUP_TOKEN                  (0x200)
#define  EHCI_QTD_IOC                              (0x8000)
#define  EHCI_QTD_STATUS_ACTIVE                    (0x0080)
#define  EHCI_QTD_STATUS_HALTED                    (0x0040)
#define  EHCI_QTD_PID_SETUP                        (0x0200)
#define  EHCI_QTD_PID_IN                           (0x0100)
#define  EHCI_QTD_PID_OUT                          (0x0000)
#define  EHCI_QTD_LENGTH_BIT_POS                   (16)
#define  EHCI_QTD_DATA_TOGGLE                      (0x80000000)
#define  EHCI_QTD_DATA_TOGGLE_BIT_POS              (31)
#define  EHCI_QTD_LENGTH_BIT_MASK                  (0x7FFF0000)
#define  EHCI_QTD_ERROR_BITS_MASK                  (0x0000003E)
#define  EHCI_QTD_DEFAULT_CERR_VALUE               (0xC00)

#define  EHCI_SETUP_TOKEN                          (2)
#define  EHCI_OUT_TOKEN                            (0)
#define  EHCI_IN_TOKEN                             (1)

#define  EHCI_QTD_T_BIT                            (0x01)

#define  EHCI_QH_ENDPOINT_SPEED_FULL               (0x00)
#define  EHCI_QH_ENDPOINT_SPEED_LOW                (0x01)
#define  EHCI_QH_ENDPOINT_SPEED_HIGH               (0x02)
#define  EHCI_QH_ENDPOINT_SPEED_RESERVED           (0x03)

#define  EHCI_ITD_LENGTH_BIT_POS                   (16)
#define  EHCI_ITD_IOC_BIT                          (0x00008000)
#define  EHCI_ITD_ACTIVE_BIT                       (0x80000000)
#define  EHCI_ITD_PG_SELECT_BIT_POS                (12)
#define  EHCI_ITD_DIRECTION_BIT_POS                (11)
#define  EHCI_ITD_EP_BIT_POS                       (8)
#define  EHCI_ITD_STATUS                           (0xF0000000)
        #define  EHCI_ITD_STATUS_ACTIVE            (0x80000000) /*bit 4 = 1000*/
        #define  EHCI_ITD_STATUS_DATA_BUFFER_ERR   (0x40000000) /*bit 3 = 0100*/
        #define  EHCI_ITD_STATUS_BABBLE_ERROR      (0x20000000) /*bit 2 = 0010*/
        #define  EHCI_ITD_STATUS_TRANSACTION_ERR   (0x10000000) /*bit 4 = 0001*/

#define  EHCI_ITD_LENGTH_TRANSMITTED               (0x0FFF0000)
#define  EHCI_ITD_BUFFER_OFFSET                    (0x00000FFF)
#define  EHCI_ITD_PAGE_NUMBER                      (0x00007000)
#define  EHCI_ITD_BUFFER_POINTER                   (0xFFFFF000)
#define  EHCI_ITD_MULTI_TRANSACTION_BITS           (0x00000003)



/* SITD position bits */
#define  EHCI_SITD_DIRECTION_BIT_POS                (31)
#define  EHCI_SITD_PORT_NUMBER_BIT_POS              (24)
#define  EHCI_SITD_HUB_ADDR_BIT_POS                 (16)
#define  EHCI_SITD_EP_ADDR_BIT_POS                  (8)

#define  EHCI_SITD_COMPLETE_SPLIT_MASK_BIT_POS      (8)

#define  EHCI_SITD_IOC_BIT_SET                      (0x80000000)
#define  EHCI_SITD_PAGE_SELECT_BIT_POS              (30)
#define  EHCI_SITD_TRANSFER_LENGTH_BIT_POS          (16)
#define  EHCI_SITD_STATUS_ACTIVE                    (0x80)

#define  EHCI_SITD_STATUS                           (0xFF)
#define  EHCI_SITD_LENGTH_TRANSMITTED               (0x03FF0000)
#define  EHCI_SITD_BUFFER_OFFSET                    (0x00000FFF)
#define  EHCI_SITD_PAGE_NUMBER                      (0x40000000)
#define  EHCI_SITD_BUFFER_POINTER                   (0xFFFFF000)



#define  EHCI_SITD_BUFFER_PTR_BIT_POS                 (12)
#define  EHCI_SITD_TP_BIT_POS                         (3)
    #define  EHCI_SITD_TP_ALL                         (0)
    #define  EHCI_SITD_TP_BEGIN                       (1)
    #define  EHCI_SITD_TP_MID                         (2)
    #define  EHCI_SITD_TP_END                         (3)



/* Interrupt enable bit masks */
#define  EHCI_IER_ASYNCH_ADVANCE                   (0x00000020)
#define  EHCI_IER_HOST_SYS_ERROR                   (0x00000010)
#define  EHCI_IER_FRAME_LIST_ROLLOVER              (0x00000008)
#define  EHCI_IER_PORT_CHANGE                      (0x00000004)
#define  EHCI_IER_USB_ERROR                        (0x00000002)
#define  EHCI_IER_USB_INTERRUPT                    (0x00000001)

/* Interrupt status bit masks */
#define  EHCI_STS_RECLAIMATION                     (0x00002000)
#define  EHCI_STS_SOF_COUNT                        (0x00000080)
#define  EHCI_STS_ASYNCH_ADVANCE                   (0x00000020)
#define  EHCI_STS_HOST_SYS_ERROR                   (0x00000010)
#define  EHCI_STS_FRAME_LIST_ROLLOVER              (0x00000008)
#define  EHCI_STS_PORT_CHANGE                      (0x00000004)
#define  EHCI_STS_USB_ERROR                        (0x00000002)
#define  EHCI_STS_USB_INTERRUPT                    (0x00000001)

/* Status bit masks */
#define  EHCI_STS_ASYNCH_SCHEDULE                  (0x00008000)
#define  EHCI_STS_PERIODIC_SCHEDULE                (0x00004000)
#define  EHCI_STS_RECLAMATION                      (0x00002000)
#define  EHCI_STS_HC_HALTED                        (0x00001000)

/* USB command bit masks */
#define  EHCI_USBCMD_ASYNC_SCHED_ENABLE            (0x00000020)
#define  EHCI_USBCMD_PERIODIC_SCHED_ENABLE         (0x00000010)

#define  EHCI_HCS_PARAMS_N_PORTS                   (0x0F)

#define  VUSB_HS_DELAY                             (3500)
#define  HUB_LS_SETUP                              (333L)
#define  MIN_THINK_TIME                            (2)

#define  EHCI_QH_EP_NUM_MASK                       (0x0F00)
#define  EHCI_QH_EP_NUM_BITS_POS                   (8)
#define  EHCI_QH_DEVICE_ADDRESS_MASK               (0x7F)
#define  EHCI_QH_SPEED_BITS_POS                    (12)
#define  EHCI_QH_MAX_PKT_SIZE_BITS_POS             (16)
#define  EHCI_QH_NAK_COUNT_RL_BITS_POS             (28)
#define  EHCI_QH_EP_CTRL_FLAG_BIT_POS              (27)
#define  EHCI_QH_HEAD_RECLAMATION_BIT_POS          (15)
#define  EHCI_QH_DTC_BIT_POS                       (14)
#define  EHCI_QH_HIGH_BW_MULT_BIT_POS              (30)
#define  EHCI_QH_HUB_PORT_NUM_BITS_POS             (23)
#define  EHCI_QH_HUB_ADDR_BITS_POS                 (16)
#define  EHCI_QH_SPLIT_COMPLETION_MASK_BITS_POS    (8)
#define  EHCI_QH_SPLIT_COMPLETION_MASK             (0xFF00)
#define  EHCI_QH_INTR_SCHED_MASK                   (0xFF)
#define  EHCI_QH_INACTIVATE_NEXT_TR_BIT_POS        (7)
#define  EHCI_QH_HORIZ_PHY_ADDRESS_MASK            (0xFFFFFFE0)
#define  EHCI_QH_TR_OVERLAY_DT_BIT                 (0x80000000)

#define  EHCI_SITD_SPLIT_COMPLETION_MASK_BITS_POS  (8)

#define  EHCI_INTR_NO_THRESHOLD_IMMEDIATE          (0x00000000)
#define  EHCI_NEW_PERIODIC_FRAME_LIST_SIZE         (1024)
#define  EHCI_FRAME_LIST_SIZE_BITS_POS             (2)
#define  EHCI_HORIZ_PHY_ADDRESS_MASK              (0xFFFFFFE0)

#define  DEFAULT_MAX_NAK_COUNT                     (15)

#if (OS_ADAPTER_ACTIVE_OS != OS_ADAPTER_SDK)
/* OTG Status and control register bit masks */

/* OTG interrupt enable bit masks */
#define  USBHS_OTGSC_INTERRUPT_ENABLE_BITS_MASK   (0x5F000000)
#define  USBHS_OTGSC_DPIE                         (0x40000000)   /* Data-line pulsing IE */
#define  USBHS_OTGSC_1MSIE                        (0x20000000)
#define  USBHS_OTGSC_BSEIE                        (0x10000000)   /* B-session end IE */
#define  USBHS_OTGSC_BSVIE                        (0x08000000)   /* B-session valid IE */
#define  USBHS_OTGSC_ASVIE                        (0x04000000)   /* A-session valid IE */
#define  USBHS_OTGSC_AVVIE                        (0x02000000)   /* A-V-bus valid IE */
#define  USBHS_OTGSC_IDIE                         (0x01000000)   /* OTG ID IE */

/* OTG interrupt status bit masks */
#define  USBHS_OTGSC_INTERRUPT_STATUS_BITS_MASK   (0x005F0000)
#define  USBHS_OTGSC_DPIS                         (0x00400000)   /* Data-line pulsing IS */
#define  USBHS_OTGSC_1MSIS                        (0x00200000)
#define  USBHS_OTGSC_BSEIS                        (0x00100000)   /* B-session end IS */
#define  USBHS_OTGSC_BSVIS                        (0x00080000)   /* B-session valid IS */
#define  USBHS_OTGSC_ASVIS                        (0x00040000)   /* A-session valid IS */
#define  USBHS_OTGSC_AVVIS                        (0x00020000)   /* A-Vbus valid IS */
#define  USBHS_OTGSC_IDIS                         (0x00010000)   /* OTG ID IS */

/* OTG status bit masks */
#define  USBHS_OTGSC_DPS                          (0x00004000)
#define  USBHS_OTGSC_BSE                          (0x00001000)   /* B-session end */
#define  USBHS_OTGSC_BSV                          (0x00000800)   /* B-session valid */
#define  USBHS_OTGSC_ASV                          (0x00000400)   /* A-session valid */
#define  USBHS_OTGSC_AVV                          (0x00000200)   /* A-Vbus Valid */
#define  USBHS_OTGSC_ID                           (0x00000100)   /* OTG ID */

/* OTG control bit masks */
#define  USBHS_OTGSC_CTL_BITS                     (0x2F)
#define  USBHS_OTGSC_B_HOST_EN                    (0x00000020)   /* B_host_enable */
#define  USBHS_OTGSC_DP                           (0x00000010)   /* Data-pulsing */
#define  USBHS_OTGSC_OT                           (0x00000008)   /* OTG termination */
#define  USBHS_OTGSC_VO                           (0x00000004)   /* Vbus on */
#define  USBHS_OTGSC_VC                           (0x00000002)   /* Vbus charge */
#define  USBHS_OTGSC_VD                           (0x00000001)   /* Vbus discharge */
#endif
#if (OS_ADAPTER_ACTIVE_OS != OS_ADAPTER_MQX)
#define _PSP_SYNC() 
#endif

#if (ENDIANNESS == BIG_ENDIAN)
   #define ehci_reg_read(r,n)           USB_LONG_BE_TO_HOST((uint32_t)r)
   #define ehci_reg_write(r,v,n)       {r = USB_HOST_TO_BE_LONG(v);_PSP_SYNC()}
#else
   #define ehci_reg_read(r,n)           USB_LONG_LE_TO_HOST((uint32_t)r)
   #define ehci_reg_write(r,v,n)       {r = USB_HOST_TO_LE_LONG(v);_PSP_SYNC()}
#endif

#if (ENDIANNESS == BIG_ENDIAN)
   #define ehci_mem_read(r,n)           USB_LONG_BE_TO_HOST((uint32_t)r)
   #define ehci_mem_write(r,v,n)       {r = USB_HOST_TO_BE_LONG(v);_PSP_SYNC()}
#else
   #define ehci_mem_read(r,n)           USB_LONG_LE_TO_HOST((uint32_t)r)
   #define ehci_mem_write(r,v,n)       {r = USB_HOST_TO_LE_LONG(v);_PSP_SYNC()}
#endif

#define ehci_reg_clear_bits(r,v,n)  ehci_reg_write(r, ehci_reg_read(r,n) & ~v,n)
#define ehci_reg_set_bits(r,v,n)    ehci_reg_write(r, ehci_reg_read(r,n) | v,n)
#define ehci_mem_clear_bits(r,v,n)  ehci_mem_write(r, ehci_mem_read(r,n) & ~v,n)
#define ehci_mem_set_bits(r,v,n)    ehci_mem_write(r, ehci_mem_read(r,n) | v,n)

#define EHCI_REG_READ(r)            ehci_reg_read(r,#r)
#define EHCI_REG_WRITE(r,v)         ehci_reg_write(r,v,#r)
#define EHCI_REG_CLEAR_BITS(r,v)    ehci_reg_clear_bits(r,v,#r)
#define EHCI_REG_SET_BITS(r,v)      ehci_reg_set_bits(r,v,#r)

#define EHCI_MEM_READ(r)            ehci_mem_read(r,#r)
#define EHCI_MEM_WRITE(r,v)         ehci_mem_write(r,v,#r)
#define EHCI_MEM_CLEAR_BITS(r,v)    ehci_mem_clear_bits(r,v,#r)
#define EHCI_MEM_SET_BITS(r,v)      ehci_mem_set_bits(r,v,#r)


/* The VUSB register structure */
typedef volatile struct {
   union  {
      struct  {
         USB_REGISTER   CAPLENGTH_HCIVER;
         USB_REGISTER   HCS_PARAMS;       /* HC structural parameters */
         USB_REGISTER   HCC_PARAMS;       /* HC Capability Parameters*/
         USB_REGISTER   RESERVED1[5];
         USB_REGISTER   DCI_VERSION;      /* DC version number and reserved 16 bits */
         USB_REGISTER   DCC_PARAMS;       /* DC Capability Parameters */
      } CAPABILITY_REGISTERS;

      struct  {
         USB_REGISTER   USB_CMD;                   /* Command register */
         USB_REGISTER   USB_STS;                   /* Status register */
         USB_REGISTER   USB_INTR;                  /* Interrupt enable */
         USB_REGISTER   USB_FRINDEX;               /* Frame index */
         USB_REGISTER   CTRLDSSEGMENT;             /* 4G segment selector */
         USB_REGISTER   DEVICE_ADDR;               /* Device Address */
         USB_REGISTER   EP_LIST_ADDR;              /* Endpoint List Address */
         USB_REGISTER   RESERVED0[9];
         USB_REGISTER   CONFIG_FLAG;               /* Configured Flag register */
         USB_REGISTER   PORTSCX[USBHS_MAX_PORTS]; /* Port Status/Control x, x = 1..8 */
         USB_REGISTER   OTGSC;
         USB_REGISTER   USB_MODE;                  /* USB Host/Device mode */
         USB_REGISTER   ENDPT_SETUP_STAT;          /* Endpoint Setup Status */
         USB_REGISTER   ENDPTPRIME;                /* Endpoint Initialize */
         USB_REGISTER   ENDPTFLUSH;                /* Endpoint De-initialize */
         USB_REGISTER   ENDPTSTATUS;               /* Endpoint Status */
         USB_REGISTER   ENDPTCOMPLETE;             /* Endpoint Interrupt On Complete */
         USB_REGISTER   ENDPTCTRLX[16];            /* Endpoint Control, where x = 0.. 15 */
      } OPERATIONAL_DEVICE_REGISTERS;

      struct  {
         USB_REGISTER   USB_CMD;                   /* Command register */
         USB_REGISTER   USB_STS;                   /* Status register */
         USB_REGISTER   USB_INTR;                  /* Interrupt enable */
         USB_REGISTER   USB_FRINDEX;               /* Frame index */
         USB_REGISTER   CTRLDSSEGMENT;             /* 4G segment selector */
         USB_REGISTER   PERIODIC_LIST_BASE_ADDR;   /* Periodic schedule list */
         USB_REGISTER   CURR_ASYNC_LIST_ADDR;      /* Current Asynch schedule list */
         USB_REGISTER   ASYNCTTSTS;                /* Async buffer in embedded TT control */
         USB_REGISTER   RESERVED0[8];
         USB_REGISTER   CONFIG_FLAG;               /* Configured Flag register */
         USB_REGISTER   PORTSCX[USBHS_MAX_PORTS]; /* Port Status/Control x, x = 1..8 */
         USB_REGISTER   OTGSC;                     /* OTG status and control register */
         USB_REGISTER   USB_MODE;                  /* USB Host/Device mode */
      } OPERATIONAL_HOST_REGISTERS;
   } REGISTERS;
} usb_ehc_dev_reg_struct_t;

typedef volatile struct {
   uint32_t   MAX_PKT_LENGTH;      /* Bits 16..26 Bit 15 is Interrupt
                                          ** On Setup
                                          */
   uint32_t   CURR_DTD_PTR;        /* Current dTD Pointer - not used */
   uint32_t   NEXT_DTD_PTR;        /* Next dTD Pointer */
   uint32_t   SIZE_IOC_INT_STS;    /* Total bytes (16..30), IOC (15),
                                          ** INT (8), STS (0-7)
                                          */
   uint32_t   BUFF_PTR0;           /* Buffer pointer Page 0 (12-31) */
   uint32_t   BUFF_PTR1;           /* Buffer pointer Page 1 (12-31) */
   uint32_t   BUFF_PTR2;           /* Buffer pointer Page 2 (12-31) */
   uint32_t   BUFF_PTR3;           /* Buffer pointer Page 3 (12-31) */
   uint32_t   BUFF_PTR4;           /* Buffer pointer Page 4 (12-31) */
   uint32_t   RESERVED1;
   uint8_t    SETUP_BUFFER[8];     /* 8 bytes of setup data that follows
                                  ** the Setup PID
                                  */
   uint32_t   RESERVED2[4];
} usb_ehc_dev_qh_struct_t;


typedef volatile struct ep_dtd_struct {
   uint32_t      NEXT_TR_ELEM_PTR; /* Memory address of next
                                          ** dTD to be processed (5-31)
                                          ** and the T (bit 0) indicating
                                          ** pointer validity
                                          */
   uint32_t      SIZE_IOC_STS;     /* total bytes (16-30),
                                          ** IOC (15), Status (0-7)
                                          */
   uint32_t      BUFF_PTR0;        /* Buffer pointer Page 0 */
   uint32_t      BUFF_PTR1;        /* Buffer pointer Page 1 */
   uint32_t      BUFF_PTR2;        /* Buffer pointer Page 2 */
   uint32_t      BUFF_PTR3;        /* Buffer pointer Page 3 */
   uint32_t      BUFF_PTR4;        /* Buffer pointer Page 4 */ 
   void*         xd_for_this_dtd;
} usb_ehci_dev_dtd_struct_t;



#define ehci_reg_clear_bits(r,v,n)  ehci_reg_write(r, ehci_reg_read(r,n) & ~v,n)
#define ehci_reg_set_bits(r,v,n)    ehci_reg_write(r, ehci_reg_read(r,n) | v,n)
#define ehci_mem_clear_bits(r,v,n)  ehci_mem_write(r, ehci_mem_read(r,n) & ~v,n)
#define ehci_mem_set_bits(r,v,n)    ehci_mem_write(r, ehci_mem_read(r,n) | v,n)

#define EHCI_REG_READ(r)            ehci_reg_read(r,#r)
#define EHCI_REG_WRITE(r,v)         ehci_reg_write(r,v,#r)
#define EHCI_REG_CLEAR_BITS(r,v)    ehci_reg_clear_bits(r,v,#r)
#define EHCI_REG_SET_BITS(r,v)      ehci_reg_set_bits(r,v,#r)

#define EHCI_MEM_READ(r)            ehci_mem_read(r,#r)
#define EHCI_MEM_WRITE(r,v)         ehci_mem_write(r,v,#r)
#define EHCI_MEM_CLEAR_BITS(r,v)    ehci_mem_clear_bits(r,v,#r)
#define EHCI_MEM_SET_BITS(r,v)      ehci_mem_set_bits(r,v,#r)

#define  MEM_UNCACHE_INDEX (0)
#define  MEM_CACHE_INDEX   (1)
#define  MEM_SIZE_INDEX    (2)
#define  SITD_ITD_UNCACHE_MEM_HEAD (3)

/* The VUSB register structure */
typedef volatile struct {
   union  {
      struct  {
         USB_REGISTER   CAPLENGTH_HCIVER;
         USB_REGISTER   HCS_PARAMS;       /* HC structural parameters */
         USB_REGISTER   HCC_PARAMS;       /* HC Capability Parameters*/
         USB_REGISTER   RESERVED1[5];
         USB_REGISTER   DCI_VERSION;      /* DC version number and reserved 16 bits */
         USB_REGISTER   DCC_PARAMS;       /* DC Capability Parameters */
      } CAPABILITY_REGISTERS;

      struct  {
         USB_REGISTER   GPTIMER0LD;
         USB_REGISTER   GPTIMER0CTL;
         USB_REGISTER   GPTIMER1LD;
         USB_REGISTER   GPTIMER1CTL;
      } TIMER_REGISTERS;
      
      struct  {
         USB_REGISTER   USB_CMD;                   /* Command register */
         USB_REGISTER   USB_STS;                   /* Status register */
         USB_REGISTER   USB_INTR;                  /* Interrupt enable */
         USB_REGISTER   USB_FRINDEX;               /* Frame index */
         USB_REGISTER   CTRLDSSEGMENT;             /* 4G segment selector */
         USB_REGISTER   DEVICE_ADDR;               /* Device Address */
         USB_REGISTER   EP_LIST_ADDR;              /* Endpoint List Address */
         USB_REGISTER   RESERVED0[9];
         USB_REGISTER   CONFIG_FLAG;               /* Configured Flag register */
         USB_REGISTER   PORTSCX[USBHS_MAX_PORTS]; /* Port Status/Control x, x = 1..8 */
         USB_REGISTER   OTGSC;
         USB_REGISTER   USB_MODE;                  /* USB Host/Device mode */
         USB_REGISTER   ENDPT_SETUP_STAT;          /* Endpoint Setup Status */
         USB_REGISTER   ENDPTPRIME;                /* Endpoint Initialize */
         USB_REGISTER   ENDPTFLUSH;                /* Endpoint De-initialize */
         USB_REGISTER   ENDPTSTATUS;               /* Endpoint Status */
         USB_REGISTER   ENDPTCOMPLETE;             /* Endpoint Interrupt On Complete */
         USB_REGISTER   ENDPTCTRLX[16];            /* Endpoint Control, where x = 0.. 15 */
      } OPERATIONAL_DEVICE_REGISTERS;
      
      struct  {
         USB_REGISTER   USB_CMD;                   /* Command register */
         USB_REGISTER   USB_STS;                   /* Status register */
         USB_REGISTER   USB_INTR;                  /* Interrupt enable */
         USB_REGISTER   USB_FRINDEX;               /* Frame index */
         USB_REGISTER   CTRLDSSEGMENT;             /* 4G segment selector */
         USB_REGISTER   PERIODIC_LIST_BASE_ADDR;   /* Periodic schedule list */
         USB_REGISTER   CURR_ASYNC_LIST_ADDR;      /* Current Asynch schedule list */
         USB_REGISTER   ASYNCTTSTS;                /* Async buffer in embedded TT control */
         USB_REGISTER   RESERVED0[4];
         USB_REGISTER   ULPIVIEWPORT;
         USB_REGISTER   RESERVED1[3];
         USB_REGISTER   CONFIG_FLAG;               /* Configured Flag register */
         USB_REGISTER   PORTSCX[USBHS_MAX_PORTS]; /* Port Status/Control x, x = 1..8 */
         USB_REGISTER   OTGSC;                     /* OTG status and control register */
         USB_REGISTER   USB_MODE;                  /* USB Host/Device mode */
      } OPERATIONAL_HOST_REGISTERS;
   } REGISTERS;
} vusb20_reg_struct_t;



typedef volatile struct
{
    uint32_t     next_link_ptr;
}link_obj_t;

typedef volatile struct ehci_itd_struct
{
   // ehci defined
   // these should be accessed via macros                                           
   uint32_t      next_link_ptr;    /* (5-31) memory address of 
                                          ** next schedule data structure 
                                          ** item type (1..2 ) and the 
                                          ** t (bit 0) indicating pointer 
                                          ** validity
                                          */
   uint32_t      tr_status_ctl_list[8];  /* bits 31-28: status,
                                                ** bits 27-16: tr x length
                                                ** bit 15: int on complete
                                                ** bits 14-12: page select
                                                ** bits 11-0: tr x offset
                                                */
   uint32_t      buffer_page_ptr_list[7];  /* bits 31-12 4k aligned pointer 
                                                ** to physical memory 
                                                ** bits 11-8 endpoint no.
                                                ** bit 7: reserved
                                                ** bits 6-0 device address*/
                                                
   // usb host stack specific extensions (not read by controller)  
   // these can be accessed directly                                           
   volatile struct ehci_itd_struct*      scratch_ptr;
   void*      pipe_descr_for_this_itd;
   void*      pipe_tr_descr_for_this_itd;
   uint32_t*  frame_list_ptr;
   uint32_t      number_of_transactions;
   uint32_t      interval;
   /* 32-byte aligned structures */
   uint32_t      reserved[10];
} ehci_itd_struct_t;

typedef volatile struct ehci_sitd_struct
{
   // ehci defined
   // these should be accessed via macros                                           
   uint32_t      next_link_ptr;    /* (5-31) memory address of 
                                          ** next schedule data structure 
                                          ** item type (1..2 ) and the 
                                          ** t (bit 0) indicating pointer 
                                          ** validity
                                          */
   uint32_t      ep_capab_charac;  /* bits 31: direction (i/o),
                                          ** bits 30-24: port number
                                          ** bit 23: reserved
                                          ** bits 22-16: hub address
                                          ** bits 15-12: reserved
                                          ** bits 11-8: endpoint number
                                          ** bit 7: reserved
                                          ** bits 6-0: device address
                                          */
   uint32_t      uframe_sched_ctl; /* bits 31-16: reserved 
                                          ** bits 15-8: split completion mask
                                          ** bits 7-0: split start mask
                                          */
   uint32_t      transfer_state;   /* bit 31: int on complete
                                          ** bit 30: page select
                                          ** bits 29-26: reserved
                                          ** bits 25-16: total bytes to 
                                          ** transfer
                                          ** bits 15-8: uframe 
                                          ** complete-split progress mask
                                          ** bits 7-0: status
                                          */
   uint32_t      buffer_ptr_0;     /* bits 31-12: 4k aligned pointer 
                                          ** to physical memory 
                                          ** bits 11-0: current offset
                                          */
   uint32_t      buffer_ptr_1;     /* bits 31-12: 4k aligned pointer 
                                          ** to physical memory 
                                          ** bits 11-5 reserved
                                          ** bits 4-3 tr position
                                          ** bits 2-0 tr count
                                          */
   uint32_t      back_link_ptr;    /* bits 31-5 back pointer points to sitd 
                                          ** bits 4-1: reserved
                                          ** bit 0: terminate
                                          */
   // usb host stack specific extensions (not read by controller)  
   // these can be accessed directly                                           
   volatile struct ehci_sitd_struct*      scratch_ptr;
   void*      pipe_descr_for_this_sitd;
   void*      pipe_tr_descr_for_this_sitd;
   uint32_t  *frame_list_ptr;
   uint32_t   interval;
   /* align to 16 word boundary */
   uint32_t      reserved[4];

} ehci_sitd_struct_t;

typedef volatile struct _ehci_qtd_struct_t{
    // ehci defined
    // these should be accessed via macros                                           
    uint32_t      next_qtd_ptr;     /* (5-31) memory address of 
                                           ** next qtd to be processed
                                           ** (4..1) reserved 
                                           ** t (bit 0) indicating pointer 
                                           ** validity
                                           */
    uint32_t      alt_next_qtd_ptr; /* bits 31-5: alternate next 
                                           ** qtd if the above one encounters 
                                           ** a short packet
                                           ** (4..1) reserved 
                                           ** t (bit 0) indicating pointer 
                                           ** validity
                                           */
    uint32_t      token;            /* bits 31: data toggle 
                                           ** bits 30-16: total bytes to transfer
                                           ** bit 15: interrupt on complete
                                           ** bits 14-12: current page
                                           ** bits 11-10: error counter
                                           ** bits 9-8: pid code
                                           ** bits 7-0: status
                                           */
    uint32_t      buffer_ptr_0;     /* bit 31-12: 4k-page aligned 
                                           ** physical memory address
                                           ** bit 11-0: current offset
                                           */
    uint32_t      buffer_ptr_1;     /* bit 31-12: 4k-page aligned 
                                           ** physical memory address
                                           ** bit 11-0: reserved
                                           */
    uint32_t      buffer_ptr_2;     /* bit 31-12: 4k-page aligned 
                                           ** physical memory address
                                           ** bit 11-0: reserved
                                           */
    uint32_t      buffer_ptr_3;     /* bit 31-12: 4k-page aligned 
                                           ** physical memory address
                                           ** bit 11-0: reserved
                                           */
    uint32_t      buffer_ptr_4;     /* bit 31-12: 4k-page aligned 
                                           ** physical memory address
                                           ** bit 11-0: reserved
                                          */

    // usb host stack specific extensions (not read by controller)  
    // these can be accessed directly                                           
    volatile struct _ehci_qtd_struct_t*         next;
    void*         pipe;
    void*         tr;
    uint32_t      length;
    uint32_t      reserved[4];    
}ehci_qtd_struct_t;

typedef struct
{
    ehci_qtd_struct_t*    qtd;
    uint32_t            occupied;
}qtd_node_link_struct_t;

typedef volatile struct ehci_qh_struct
{
   // EHCI Defined
   // These should be accessed via macros                                           
   uint32_t      horiz_link_ptr;   /* (5-31) memory address of 
                                          ** next data object to be processed
                                          ** (4..3) reserved 
                                          ** (2..1) type of the item
                                          ** t (bit 0) indicating pointer 
                                          ** validity
                                          */
   uint32_t      ep_capab_charac1; /* bits 31-28: nak count reload,
                                          ** bit 27: control endpoint flag
                                          ** bit 26-16: maximum packet length
                                          ** bit 15: head of reclamation 
                                          ** list flag
                                          ** bit 14: data toggle control
                                          ** bits 13-12: endpoint speed
                                          ** bit 11-8: endpoint number
                                          ** bits 7: inactivate on next tr
                                          ** bits 6-0: device address
                                          */
   uint32_t      ep_capab_charac2; /* bits 31-30: high-bw pipe 
                                          ** multiplier, 
                                          ** bit 29-23: port number
                                          ** bit 22-16: hub address
                                          ** bit 15-8: split completion mask
                                          ** bit 7-0: interrupt schedule mask
                                          */
   uint32_t      curr_qtd_link_ptr;/* bits 31-5: physical memory address
                                          ** of the current xaction processed
                                          */
   uint32_t      next_qtd_link_ptr;/* bits 31-5: physical memory address
                                          ** of the current xaction processed
                                          ** bit 0: terminate bit
                                          */
   uint32_t      alt_next_qtd_link_ptr;  /* bits 31-5: physical memory address
                                                ** of the current xaction processed
                                                ** bits 4-1: nak counter
                                                ** bit 0: terminate bit
                                                */
   uint32_t      status;           /* bit 31: data-toggle
                                          ** bits 30-16: total bytes to transfer
                                          ** bit 15: interrupt on complete
                                          ** bits 11-10: error counter
                                          ** bit 0: ping state/err
                                          ** physical memory address
                                          ** bit 11-0: reserved
                                          */
   uint32_t      buffer_ptr_0;     /* bit 31-12: 4k-page aligned 
                                          ** physical memory address
                                          ** bit 11-0: reserved
                                          */
   uint32_t      buffer_ptr_1;     /* bit 31-12: 4k-page aligned 
                                          ** physical memory address
                                          ** bit 7-0: split-transaction, 
                                          ** complete-split progress
                                          */
   uint32_t      buffer_ptr_2;     /* bits 31-12: 4k-page aligned 
                                          ** physical memory address
                                          ** bits 11-5: s-bytes
                                          ** bits 4-0: split-transaction 
                                          ** frame tag
                                          */
   uint32_t      buffer_ptr_3;     /* bit 31-12: 4k-page aligned 
                                          ** physical memory address
                                          ** bit 11-0: reserved
                                          */
   uint32_t      buffer_ptr_4;     /* bit 31-12: 4k-page aligned 
                                          ** physical memory address
                                          ** bit 11-0: reserved
                                          */
   // usb host stack specific extensions (not read by controller)  
   // these can be accessed directly                                           
   volatile struct ehci_qh_struct*         next;
   void*                                   pipe;
   ehci_qtd_struct_t*                      qtd_head;
   uint32_t                                interval;
} ehci_qh_struct_t;

typedef volatile struct {
   // ehci defined
   // these should be accessed via macros                                           
   uint32_t      normal_path_link_ptr;   /* (5-31) memory address of 
                                                ** next data object to be processed
                                                ** in the periodic list
                                                ** bits 4-3: reserved 
                                                ** (2..1) type of the item
                                                ** t (bit 0) indicating pointer 
                                                ** validity
                                                */
   uint32_t      back_path_link_ptr;     /* bits 31-5: memory address of 
                                                ** the queue head,
                                                ** bit 4-3: reserved
                                                ** (2..1) type of the item
                                                ** t (bit 0) indicating pointer 
                                                ** validity
                                                */
   // usb host stack specific extensions (not read by controller)  
   // these can be accessed directly                                           
    void*      scratch_ptr;
   /* 32-bytes aligned */
   uint32_t              reserved[5];
} ehci_fstn_struct_t;

typedef uint32_t   ehci_frame_list_element_pointer;

typedef struct {
   // EHCI Defined
   // This should be accessed via macros                                           
   uint32_t  allocated_bw;  /* allocated bandwidth for this frame/uframe */
} frame_bw_struct_t;

#endif // __ehci_h__
