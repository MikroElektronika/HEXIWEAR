/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_USB_EHCI_HAL_H__
#define __FSL_USB_EHCI_HAL_H__

#include "adapter.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
#define  NEW_USB_EHCI_HAL_ENABLE                 (1)
#define  HW_USB_INSTANCE_COUNT              (1U)
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_usb_features.h"
#include "fsl_device_registers.h"
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM)
#define  NEW_USB_EHCI_HAL_ENABLE                 (1)
#define  HW_USB_INSTANCE_COUNT              (1U)
#if (defined(CPU_MK65F18))
    #include "MK65F18.h"
#elif (defined(CPU_MK70F12))
    #include "MK70F12.h"
#elif (defined(CPU_MK60FN1M012))
    #include "MK60F12.h"
#endif
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
#define  NEW_USB_EHCI_HAL_ENABLE                 (1)
#define  HW_USB_INSTANCE_COUNT              (1U)
#if (defined(CPU_MK70F12))
    #include "MK70F12.h"
#elif (defined(CPU_MK60FN1M012))
    #include "MK60F12.h"
#elif (defined(CPU_MK65F18))
    #include "MK65F18.h"
#elif (defined(CPU_VF65GS10_A5)) || (defined(CPU_VF65GS10_M4))
    #include "MVF61NS151MK50.h"
    #define  NEW_USB_EHCI_HAL_ENABLE             (0)
    #define  HW_USB_INSTANCE_COUNT          (1U)
#elif (defined(CPU_SVF522R3K_M4) || defined(CPU_SVF522R3K_A5))
    #include "SVF522R3MK4.h"
    #define  NEW_USB_EHCI_HAL_ENABLE             (0)
    #define  HW_USB_INSTANCE_COUNT          (2U)
#endif
#endif

//#include <stdint.h>
//#include <stdbool.h>
#include <assert.h>
//#include "fsl_usb_features.h"
//#include "device/fsl_device_registers.h"

/*!
 * @addtogroup usb_ehci_hal
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Get the ehci base addr.
 *
 * This function enables get the base addr of ehci
 *
 * @param the instance number
 */
#if (HW_USB_INSTANCE_COUNT > 1)
static USB_MemMapPtr _usb_hal_ehci_get_base_addr(uint32_t instance)
{
    USB_MemMapPtr base;
    switch(instance)
    {
        case 0:
            base = USB0_BASE_PTR;
            break;
        case 1:
            base = USB1_BASE_PTR;
            break;
        default:
            break;
        }
        return base;
}
#endif

#if (NEW_USB_EHCI_HAL_ENABLE)
/*!
 * @brief Set the controller mode to host.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_controller_host_mode(uint32_t baseAddr)
{
    USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) = (USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) & ~USBHS_USBMODE_CM_MASK) | USBHS_USBMODE_CM(0x3); 
}

/*!
 * @brief Set the controller mode to device.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_controller_device_mode(uint32_t baseAddr)
{
    USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) = (USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) & ~USBHS_USBMODE_CM_MASK) | USBHS_USBMODE_CM(0x2); 
}

/*!
 * @brief Set the controller mode to big endian.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_big_endian(uint32_t baseAddr)
{
    USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) = (USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) & ~USBHS_USBMODE_ES_MASK)|(1 << USBHS_USBMODE_ES_SHIFT);
}

/*!
 * @brief Set the controller mode to little endian.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_little_endian(uint32_t baseAddr)
{
    USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) = (USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) & ~USBHS_USBMODE_ES_MASK)|(0 << USBHS_USBMODE_ES_SHIFT);
}

/*!
 * @brief Set the controller mode to disable lock clock.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_disable_setup_lock(uint32_t baseAddr)
{
    USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) = (USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) & ~USBHS_USBMODE_SLOM_MASK)|(1 << USBHS_USBMODE_SLOM_SHIFT);
}

/*!
 * @brief Set the controller mode to enable lock clock.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_enable_setup_lock(uint32_t baseAddr)
{
    USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) = (USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) & ~USBHS_USBMODE_SLOM_MASK)|(0 << USBHS_USBMODE_SLOM_SHIFT);
}

/*!
 * @brief Set the controller mode to specific mode.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 * @param the mode
 */
static inline void usb_hal_ehci_set_usb_mode(uint32_t baseAddr, uint32_t mode)
{
    USBHS_USBMODE_REG((USBHS_MemMapPtr)baseAddr) = mode;
}

/*!
 * @brief Get the dcc params.
 *
 * This function gets the dcc params
 *
 * @param the baseAddr
 * @return Current dcc params
 */
static inline uint32_t usb_hal_ehci_get_dcc_params(uint32_t baseAddr)
{
    return USBHS_DCCPARAMS_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Clear epsetup status.
 *
 * This function clears the epsetup status
 *
 * @param the baseAddr
 * @param the epSetupStatus
 */
static inline void usb_hal_ehci_clear_ep_setup_status(uint32_t baseAddr, uint32_t epSetupStatus)
{   
    USBHS_EPSETUPSR_REG((USBHS_MemMapPtr)baseAddr) |= (epSetupStatus << USBHS_EPSETUPSR_EPSETUPSTAT_SHIFT) & USBHS_EPSETUPSR_EPSETUPSTAT_MASK;
}

/*!
 * @brief Clear epsetup epnum.
 *
 * This function clears the epsetup epnum
 *
 * @param the baseAddr
 * @param the ep_num
 */
static inline void usb_hal_ehci_clear_setup_stat_ep_num(uint32_t baseAddr, uint32_t ep_num)
{
    USBHS_EPSETUPSR_REG((USBHS_MemMapPtr)baseAddr) = ep_num;
}

/*!
 * @brief Get epsetup status.
 *
 * This function gets the epsetup status
 *
 * @param the baseAddr
 * @return the epSetupStatus
 */
static inline uint32_t usb_hal_ehci_get_ep_setup_status(uint32_t baseAddr)
{   
    return USBHS_EPSETUPSR_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Get ep complete status.
 *
 * This function gets the complete status
 *
 * @param the baseAddr
 * @return the complete status
 */
static inline uint32_t usb_hal_ehci_get_ep_complete_status(uint32_t baseAddr)
{
    return USBHS_EPCOMPLETE_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Clear ep complete status.
 *
 * This function clears the complete status
 *
 * @param the baseAddr
 * @param the epCompleteStatus
 */
static inline void usb_hal_ehci_clear_ep_complete_status(uint32_t baseAddr, uint32_t epCompleteStatus)
{
    USBHS_EPCOMPLETE_REG((USBHS_MemMapPtr)baseAddr) = epCompleteStatus;
}

/*!
 * @brief Set eplist address.
 *
 * This function Set eplist address
 *
 * @param the baseAddr
 * @param the epQHAddress
 */
static inline void usb_hal_ehci_set_eplist_address(uint32_t baseAddr, uint32_t epQHAddress)
{
    USBHS_EPLISTADDR_REG((USBHS_MemMapPtr)baseAddr) = epQHAddress;
}

/*!
 * @brief Get eplist address.
 *
 * This function Get eplist address
 *
 * @param the baseAddr
 * @return the epQHAddress
 */
static inline uint32_t usb_hal_ehci_get_eplist_address(uint32_t baseAddr)
{
    return USBHS_EPLISTADDR_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Get the interrupt enable register status.
 *
 * This function Get the interrupt enable register status
 *
 * @param the baseAddr
 * @return the interrupt enable register status
 */
static inline uint32_t usb_hal_ehci_get_interrupt_enable_status(uint32_t baseAddr)
{
    return USBHS_USBINTR_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Enable the specific interrupt.
 *
 * This function Enable the specific interrupt
 *
 * @param the baseAddr
 * @return the specific interrupt
 */
static inline void usb_hal_ehci_enable_interrupts(uint32_t baseAddr, uint32_t intrType)
{
    USBHS_USBINTR_REG((USBHS_MemMapPtr)baseAddr) |= intrType;
}

/*!
 * @brief Set the interrupt register to a specific value.
 *
 * This function Set the interrupt register to a specific value
 *
 * @param the baseAddr
 * @param the specific value
 */
static inline void usb_hal_ehci_interrupts_set(uint32_t baseAddr, uint32_t intrType)
{
   USBHS_USBINTR_REG((USBHS_MemMapPtr)baseAddr) = intrType;
}

/*!
 * @brief Disable the specific interrupts.
 *
 * This function Disable the specific interrupts
 *
 * @param the baseAddr
 * @param the specific interrupts
 */
static inline void usb_hal_ehci_disable_interrupts(uint32_t baseAddr, uint32_t intrType)
{
    USBHS_USBINTR_REG((USBHS_MemMapPtr)baseAddr) &= ~intrType;
}

/*!
 * @brief Initiate attach event.
 *
 * This function Initiate attach event
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_initiate_attach_event(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) |= EHCI_CMD_RUN_STOP;
}

/*!
 * @brief Initiate deattach event.
 *
 * This function Initiate deattach event
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_initiate_detach_event(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) &= (uint32_t)(~(uint32_t)EHCI_CMD_RUN_STOP);
}

/*!
 * @brief Reset the controller.
 *
 * This function Reset the controller
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_reset_controller(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) = EHCI_CMD_CTRL_RESET;
}

/*!
 * @brief Set the dtd tripwire.
 *
 * This function Reset the controller
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_dtd_tripwire(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) |= EHCI_CMD_ATDTW_TRIPWIRE_SET;
}

/*!
 * @brief Clear the dtd tripwire.
 *
 * This function Clear the controller
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_clear_dtd_tripwire(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) &= (uint32_t)(~(uint32_t)EHCI_CMD_ATDTW_TRIPWIRE_SET);
}

/*!
 * @brief Disable the usb cmd async sched.
 *
 * This function Disable the usb cmd async sched
 *
 * @param the baseAddr
 */
static inline void usb_hal_echi_disable_usb_cmd_async_sched(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) &= (uint32_t)(~(uint32_t)EHCI_USBCMD_ASYNC_SCHED_ENABLE);
}

/*!
 * @brief Enable the usb cmd async sched.
 *
 * This function Enable the usb cmd async sched
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_enable_usb_cmd_async_sched(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) |= EHCI_USBCMD_ASYNC_SCHED_ENABLE;
}

/*!
 * @brief Disable the usb cmd periodic sched.
 *
 * This function Disable the usb periodic async sched
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_disable_usb_cmd_periodic_sched(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) &= (uint32_t)(~(uint32_t)EHCI_USBCMD_PERIODIC_SCHED_ENABLE);
}

/*!
 * @brief Get the dtd tripwire status.
 *
 * This function Get the dtd tripwire status
 *
 * @param the baseAddr
 * @return the dtd tripwire status
 */
static inline uint32_t usb_hal_ehci_is_tripwire_set(uint32_t baseAddr)
{
    return (USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) & EHCI_CMD_ATDTW_TRIPWIRE_SET);
}

/*!
 * @brief Clear the dtd tripwire status.
 *
 * This function Clear the dtd tripwire status
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_clear_usb_cmd_setup_trip_wire(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) &= (uint32_t)(~(uint32_t)EHCI_CMD_SETUP_TRIPWIRE_SET);
}

/*!
 * @brief Set the dtd tripwire status.
 *
 * This function Clear the dtd tripwire status
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_usb_cmd_setup_trip_wire(uint32_t baseAddr)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) |= EHCI_CMD_SETUP_TRIPWIRE_SET;
}

/*!
 * @brief Set the usb cmd register to a specific value.
 *
 * This function Set the usb cmd register to a specific value
 *
 * @param the baseAddr
 * @param the specific value
 */
static inline void usb_hal_ehci_set_usb_cmd(uint32_t baseAddr, uint32_t value)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) = value;
}

/*!
 * @brief Clear the usb cmd register.
 *
 * This function Clear the usb cmd register
 *
 * @param the baseAddr
 * @param the specific value
 */
static inline void usb_hal_ehci_clear_usb_cmd(uint32_t baseAddr, uint32_t value)
{
    USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr) &= ~(value);
}


/*!
 * @brief Get the usb cmd value.
 *
 * This function Get the usb cmd register value
 *
 * @param the baseAddr
 * @return the specific value
 */
static inline uint32_t  usb_hal_ehci_get_usb_cmd(uint32_t baseAddr)
{
    return USBHS_USBCMD_REG((USBHS_MemMapPtr)baseAddr);
}


/*!
 * @brief Get the usb cap_length.
 *
 * This function Get the usb cap_length
 *
 * @param the baseAddr
 * @return the cap length
 */
static inline uint8_t usb_hal_ehci_get_cap_length(uint32_t baseAddr)
{
    return 0;
}

/*!
 * @brief Set the usb config register to a specific value.
 *
 * This function Set the usb config register to a specific value
 *
 * @param the baseAddr
 * @param the value
 */
static inline void usb_hal_ehci_set_usb_config(uint32_t baseAddr, uint32_t value)
{
    //USBHS_CONFIGFLAG = value;
}

/*!
 * @brief Set the usb endpoint prime to a specific value.
 *
 * This function Set the usb endpoint prime to a specific value
 *
 * @param the baseAddr
 * @param the value
 */
static inline void usb_hal_ehci_set_endpoint_prime(uint32_t baseAddr, uint32_t value)
{   
    USBHS_EPPRIME_REG((USBHS_MemMapPtr)baseAddr) = value;
}

/*!
 * @brief Get the usb endpoint prime  value.
 *
 * This function Get the usb endpoint prime  value
 *
 * @param the baseAddr
 * @return the value
 */
static inline uint32_t usb_hal_ehci_get_endpoint_prime(uint32_t baseAddr)
{
    return USBHS_EPPRIME_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Get the usb endpoint status
 *
 * This function Get the usb endpoint status
 *
 * @param the baseAddr
 * @return the value
 */
static inline uint32_t usb_hal_echi_get_endpoint_status(uint32_t baseAddr)
{
    return USBHS_EPSR_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Flush the endpoint buffer
 *
 * This function Flush the endpoint buffer
 *
 * @param the baseAddr
 * @param the epNumber
 */
static inline void usb_hal_ehci_flush_endpoint_buffer(uint32_t baseAddr, uint32_t epNumber)
{
    USBHS_EPFLUSH_REG((USBHS_MemMapPtr)baseAddr) = epNumber;
}

/*!
 * @brief Get the endpoint transfer buffer status
 *
 * This function Get the endpoint transfer buffer status
 *
 * @param the baseAddr
 * @param the epNumber
 * @return the transfer buffer status
 */
static inline uint32_t usb_hal_ehci_is_endpoint_transfer_flushed(uint32_t baseAddr, uint32_t epNumber)
{
    return (USBHS_EPFLUSH_REG((USBHS_MemMapPtr)baseAddr) & epNumber);
}

/*!
 * @brief Get the frame index
 *
 * This function Get the frame index
 *
 * @param the baseAddr
 * @return the frame index
 */
static inline uint32_t usb_hal_ehci_get_frame_index(uint32_t baseAddr)
{
    return USBHS_FRINDEX_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Get the port status
 *
 * This function Get the port status
 *
 * @param the baseAddr
 * @return the port status
 */
static inline uint32_t usb_hal_ehci_get_port_status(uint32_t baseAddr)
{
    return USBHS_PORTSC1_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Set the port status
 *
 * This function Set the port status
 *
 * @param the baseAddr
 * @param the port status
 */
static inline void usb_hal_ehci_set_port_status(uint32_t baseAddr, uint32_t status)
{
    USBHS_PORTSC1_REG((USBHS_MemMapPtr)baseAddr) = status;
}

/*!
 * @brief Get the usb interrupt status register value
 *
 * This function Get the usb interrupt status register value
 *
 * @param the baseAddr
 * @return  the usb interrupt status register value
 */
static inline uint32_t usb_hal_ehci_get_usb_interrupt_status(uint32_t baseAddr)
{
    return USBHS_USBSTS_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Clear the usb interrupt status register value
 *
 * This function Clear the usb interrupt status register value
 *
 * @param the baseAddr
 * @param  the usb interrupt status register value
 */
static inline void usb_hal_ehci_clear_usb_interrupt_status(uint32_t baseAddr, uint32_t status)
{
    USBHS_USBSTS_REG((USBHS_MemMapPtr)baseAddr) = status;
}

/*!
 * @brief Get the hcsparams value
 *
 * This function Get the hcsparams value
 *
 * @param the baseAddr
 * @return the hcsparams value
 */
static inline uint32_t usb_hal_ehci_get_hcsparams(uint32_t baseAddr)
{
    return USBHS_HCSPARAMS_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Get the hccparams value
 *
 * This function Get the hccparams value
 *
 * @param the baseAddr
 * @return the hccparams value
 */
static inline uint32_t usb_hal_ehci_get_hccparams(uint32_t baseAddr)
{
    return USBHS_HCCPARAMS_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Clear the device address
 *
 * This function Clear the device address
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_clear_device_address(uint32_t baseAddr)
{
    USBHS_DEVICEADDR_REG((USBHS_MemMapPtr)baseAddr) &= ~0xFE000000;
}

/*!
 * @brief Set qh to curr async list
 *
 * This function Set qh to curr async list
 *
 * @param the baseAddr
 * @param the qh address
 */
static inline void usb_hal_ehci_set_qh_to_curr_async_list(uint32_t baseAddr, uint32_t qh_addr)
{
    USBHS_ASYNCLISTADDR_REG((USBHS_MemMapPtr)baseAddr) = qh_addr;
}

/*!
 * @brief Get qh from curr async list
 *
 * This function Get qh from curr async list
 *
 * @param the baseAddr
 * @return the qh address
 */
static inline uint32_t usb_hal_ehci_get_curr_async_list(uint32_t baseAddr)
{
   return USBHS_ASYNCLISTADDR_REG((USBHS_MemMapPtr)baseAddr);
}

/*!
 * @brief Set the periodic list base address
 *
 * This function Set the periodic list base address
 *
 * @param the baseAddr
 * @param the periodic list base address
 */
static inline void usb_hal_ehci_set_periodic_list_base_addr(uint32_t baseAddr, uint32_t base_addr)
{
    USBHS_PERIODICLISTBASE_REG((USBHS_MemMapPtr)baseAddr) = base_addr;
}

/*!
 * @brief Enable the specific endpoint
 *
 * This function Enable the specific endpoint
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 * @param the type
 */
static inline void usb_hal_ehci_enable_endpoint(uint32_t baseAddr, uint32_t epNumber, uint32_t direction, uint32_t type)
{
    if (epNumber == 0)
    {
        USBHS_EPCR0_REG((USBHS_MemMapPtr)baseAddr) |= ((direction ? (uint32_t)(EHCI_EPCTRL_TX_ENABLE |
            EHCI_EPCTRL_TX_DATA_TOGGLE_RST) :
            (uint32_t)(EHCI_EPCTRL_RX_ENABLE | EHCI_EPCTRL_RX_DATA_TOGGLE_RST)) |
            (type << (direction ?
            EHCI_EPCTRL_TX_EP_TYPE_SHIFT : EHCI_EPCTRL_RX_EP_TYPE_SHIFT)));
    }
    else
    {
        USBHS_EPCR_REG((USBHS_MemMapPtr)baseAddr,epNumber - 1) |= ((direction ? (uint32_t)(EHCI_EPCTRL_TX_ENABLE |
            EHCI_EPCTRL_TX_DATA_TOGGLE_RST) :
            (uint32_t)(EHCI_EPCTRL_RX_ENABLE | EHCI_EPCTRL_RX_DATA_TOGGLE_RST)) |
            (type << (direction ?
            EHCI_EPCTRL_TX_EP_TYPE_SHIFT : EHCI_EPCTRL_RX_EP_TYPE_SHIFT)));
    }
}

/*!
 * @brief Disable the specific endpoint
 *
 * This function Disable the specific endpoint
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 */
static inline void usb_hal_ehci_disable_endpoint(uint32_t baseAddr, uint32_t epNumber, uint32_t direction)
{
    USBHS_EPCR_REG((USBHS_MemMapPtr)baseAddr, epNumber) &= ~(direction ? ((uint32_t)EHCI_EPCTRL_TX_ENABLE|EHCI_EPCTRL_TX_TYPE):((uint32_t)EHCI_EPCTRL_RX_ENABLE|EHCI_EPCTRL_RX_TYPE));
}

/*!
 * @brief Get the endpoint ep control value
 *
 * This function Get the endpoint ep control value
 *
 * @param the baseAddr
 * @param the epNumber
 * @return the control value
 */
static inline uint32_t usb_hal_ehci_get_endpoint_control(uint32_t baseAddr, uint32_t epNumber)
{
    return (epNumber == 0 ? USBHS_EPCR0_REG((USBHS_MemMapPtr)baseAddr) : USBHS_EPCR_REG((USBHS_MemMapPtr)baseAddr,epNumber - 1));
}   

/*!
 * @brief Clear the endpoint  stall status
 *
 * This function Clear the endpoint  stall status
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 */
static inline void usb_hal_ehci_clear_endpoint_stall(uint32_t baseAddr, uint32_t epNumber, uint32_t direction)
{
    if (epNumber == 0)
    {
        USBHS_EPCR0_REG((USBHS_MemMapPtr)baseAddr) &= ~(direction ? (uint32_t)EHCI_EPCTRL_TX_EP_STALL : EHCI_EPCTRL_RX_EP_STALL);
    }
    else
    {
        USBHS_EPCR_REG((USBHS_MemMapPtr)baseAddr,epNumber - 1) &= ~(direction ? (uint32_t)EHCI_EPCTRL_TX_EP_STALL : EHCI_EPCTRL_RX_EP_STALL);
    }
}

/*!
 * @brief Reset the endpoint data toggle
 *
 * This function Reset the endpoint data toggle
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 */
static inline void usb_hal_ehci_reset_endpoint_data_toggle(uint32_t baseAddr, uint32_t epNumber, uint32_t direction)
{
    if (epNumber != 0)
    {
        USBHS_EPCR_REG((USBHS_MemMapPtr)baseAddr,epNumber - 1) |= (direction ? (uint32_t)EHCI_EPCTRL_TX_DATA_TOGGLE_RST : EHCI_EPCTRL_RX_DATA_TOGGLE_RST);
    }
}

/*!
 * @brief Stall the endpoint both directions
 *
 * This function Stall the endpoint both directions
 *
 * @param the baseAddr
 * @param the epNumber
 */
static inline void usb_hal_ehci_stall_both_directions(uint32_t baseAddr, uint32_t epNumber)
{
    if (epNumber == 0)
    {
        USBHS_EPCR0_REG((USBHS_MemMapPtr)baseAddr) |= (EHCI_EPCTRL_TX_EP_STALL | EHCI_EPCTRL_RX_EP_STALL);
    }
    else
    {
        USBHS_EPCR_REG((USBHS_MemMapPtr)baseAddr,epNumber - 1) |= (EHCI_EPCTRL_TX_EP_STALL | EHCI_EPCTRL_RX_EP_STALL);
    }
}

/*!
 * @brief Stall the endpoint specific directions
 *
 * This function Stall the endpoint specific directions
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 */
static inline void usb_hal_ehci_stall_specific_direction(uint32_t baseAddr, uint32_t epNumber, uint32_t direction)
{
    if (epNumber == 0)
    {
        USBHS_EPCR0_REG((USBHS_MemMapPtr)baseAddr) |= (uint32_t)(direction ? EHCI_EPCTRL_TX_EP_STALL : EHCI_EPCTRL_RX_EP_STALL);
    }
    else
    {
        USBHS_EPCR_REG((USBHS_MemMapPtr)baseAddr,epNumber - 1) |= (uint32_t)(direction ? EHCI_EPCTRL_TX_EP_STALL : EHCI_EPCTRL_RX_EP_STALL);
    }
}


/*!
 * @brief Set the device address register to a specific value
 *
 * This function Set the device address register to a specific value
 *
 * @param the baseAddr
 * @param the address
 */
static inline void usb_hal_ehci_set_device_address(uint32_t baseAddr, uint32_t address)
{
    USBHS_DEVICEADDR_REG((USBHS_MemMapPtr)baseAddr) = (uint32_t)(address << USBHS_ADDRESS_BIT_SHIFT);
}

/*!
 * @brief Clear the ep QH max packet length
 *
 * This function Clear the ep QH max packet length
 *
 * @param the epQueueHeadAddr
 */
static inline void usb_hal_ehci_clear_max_packet_length(usb_ehc_dev_qh_struct_t * epQueueHeadAddr)
{
    epQueueHeadAddr->MAX_PKT_LENGTH = 0;
}

/*!
 * @brief Set the ep QH max packet length
 *
 * This function Set the ep QH max packet length
 *
 * @param the epQueueHeadAddr
 * @param the maxPacketSize
 */
static inline void usb_hal_ehci_set_max_packet_length(usb_ehc_dev_qh_struct_t * epQueueHeadAddr, uint32_t maxPacketSize)
{
    epQueueHeadAddr->MAX_PKT_LENGTH = ((uint32_t)maxPacketSize) ;
}

/*!
 * @brief Set the ep QH max packet length for non iso
 *
 * This function Set the ep QH max packet length for non iso
 *
 * @param the epQueueHeadAddr
 * @param the value
 */
static inline void usb_hal_ehci_set_max_packet_length_for_non_iso(usb_ehc_dev_qh_struct_t * epQueueHeadAddr, uint32_t value)
{
    epQueueHeadAddr->MAX_PKT_LENGTH = value;
}

/*!
 * @brief Get the ehci iso set value
 *
 * This function Get the ehci iso set value
 *
 * @param the epQueueHeadAddr
 * @return the value
 */
static inline uint32_t usb_hal_ehci_is_ios_set( usb_ehc_dev_qh_struct_t * epQueueHeadAddr)
{
    return (epQueueHeadAddr->MAX_PKT_LENGTH & VUSB_EP_QUEUE_HEAD_IOS);
}

/*!
 * @brief Set the dtd terminate value
 *
 * This function Set the dtd terminate value
 *
 * @param the epQueueHeadAddr
 * @return the value
 */
static inline void usb_hal_ehci_set_next_dtd_terminate(usb_ehc_dev_qh_struct_t * epQueueHeadAddr)
{
    epQueueHeadAddr->NEXT_DTD_PTR = VUSB_EP_QUEUE_HEAD_NEXT_TERMINATE;
}

/*!
 * @brief Set the next tr elem dtd terminate value
 *
 * This function Set the next tr elem dtd terminate value
 *
 * @param the epQueueHeadAddr
 * @param the dTD_ptr
 */
static inline void usb_hal_ehci_set_dtd_next_tr_elem_terminate(volatile usb_ehci_dev_dtd_struct_t * dTD_ptr)
{
   dTD_ptr->NEXT_TR_ELEM_PTR = VUSB_EP_QUEUE_HEAD_NEXT_TERMINATE;
}

/*!
 * @brief Set the next tr elem dtd ptr
 *
 * This function Set the next tr elem dtd ptr
 *
 * @param the temp_dTD_ptr
 * @param the dTD_ptr
 */
static inline void usb_hal_ehci_set_dtd_next_tr_elem_ptr(volatile usb_ehci_dev_dtd_struct_t * temp_dTD_ptr, uint32_t dTD_ptr)
{
   temp_dTD_ptr->NEXT_TR_ELEM_PTR = dTD_ptr;
}

/*!
 * @brief Set the epQueueHeadAddr next dtd ptr
 *
 * This function Set the epQueueHeadAddr next dtd ptr
 *
 * @param the epQueueHeadAddr
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_set_qh_next_dtd(usb_ehc_dev_qh_struct_t * epQueueHeadAddr, uint32_t dtdAddr)
{
    epQueueHeadAddr->NEXT_DTD_PTR = dtdAddr;
}

/*!
 * @brief Set the next dtd invalid
 *
 * This function Set the next dtd invalid
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_set_next_dtd_invalid(usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    dtdAddr->NEXT_TR_ELEM_PTR = USBHS_TD_NEXT_TERMINATE;
}

/*!
 * @brief Clear the dtd size ioc status
 *
 * This function Clear the dtd size ioc status
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_clear_size_ioc_sts( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    dtdAddr->SIZE_IOC_STS = 0;
}

/*!
 * @brief Clear the dtd size ioc status reserved fields
 *
 * This function Clear the dtd size ioc status reserved fields
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_clear_ioc_reserved_fields(volatile usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    dtdAddr->SIZE_IOC_STS &= ~((uint32_t)USBHS_TD_RESERVED_FIELDS);
}

/*!
 * @brief Clear the dtd 
 *
 * This function Clear the dtd 
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_clear_dtd(volatile usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    dtdAddr->NEXT_TR_ELEM_PTR = 0;
    dtdAddr->SIZE_IOC_STS = 0;
    dtdAddr->BUFF_PTR0 = 0;
    dtdAddr->BUFF_PTR1 = 0;
    dtdAddr->BUFF_PTR2 = 0;
    dtdAddr->BUFF_PTR3 = 0;
    dtdAddr->BUFF_PTR4 = 0;
}

/*!
 * @brief Set the dtd buffer address
 *
 * This function Set the dtd buffer address
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_set_dtd_buffer_address(volatile usb_ehci_dev_dtd_struct_t * dtdAddr, uint32_t addr)
{
    dtdAddr->BUFF_PTR0 = addr;
    dtdAddr->BUFF_PTR1 = addr + 4096;
    dtdAddr->BUFF_PTR2 = addr + (4096*2);
    dtdAddr->BUFF_PTR3 = addr + (4096*3);
    dtdAddr->BUFF_PTR4 = addr + (4096*4);
}

/*!
 * @brief Set the dtd size ioc status value
 *
 * This function Set the dtd size ioc status value
 *
 * @param the dtdAddr
 * @param the value
 */
static inline void usb_hal_ehci_set_dtd_size_ioc_status(volatile usb_ehci_dev_dtd_struct_t * dtdAddr, uint32_t value)
{
    dtdAddr->SIZE_IOC_STS = value;
}

/*!
 * @brief Get the dtd size ioc status value
 *
 * This function Get the dtd size ioc status value
 *
 * @param the dtdAddr
 * @return the value
 */
static inline uint32_t usb_hal_ehci_get_dtd_size_ioc_status(volatile usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return dtdAddr->SIZE_IOC_STS;
}

/*!
 * @brief Get the next dtd address
 *
 * This function Get the next dtd address
 *
 * @param the dtdAddr
 * @return the next dtd address
 */
static inline uint32_t usb_hal_ehci_get_next_dtd_address(volatile usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return (dtdAddr->NEXT_TR_ELEM_PTR & USBHS_TD_ADDR_MASK);
}

/*!
 * @brief Get the dtd error status
 *
 * This function Get the dtd error status
 *
 * @param the dtdAddr
 * @return the dtd error status
 */
static inline uint32_t usb_hal_ehci_get_dtd_error_status( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return (dtdAddr->SIZE_IOC_STS & USBHS_TD_ERROR_MASK);
}

/*!
 * @brief Clear the qh error status
 *
 * This function Clear the qh error status
 *
 * @param the epQueueHeadAddr
 * @param the errors
 */
static inline void usb_hal_ehci_clear_qh_error_status( usb_ehc_dev_qh_struct_t * epQueueHeadAddr, uint32_t errors)
{
    epQueueHeadAddr->SIZE_IOC_INT_STS &= ~errors;
}

/*!
 * @brief Get the tr packet size
 *
 * This function Get the tr packet size
 *
 * @param the dtdAddr
 */
static inline uint32_t usb_hal_ehci_get_tr_packet_size(usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return ((dtdAddr->SIZE_IOC_STS & VUSB_EP_TR_PACKET_SIZE) >> 16);
}

/*!
 * @brief Get the xd for this dtd
 *
 * This function Get the xd for this dtd
 *
 * @param the dtdAddr
 * @return the xd for this dtd
 */
static inline uint32_t usb_hal_ehci_get_xd_for_this_dtd( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return (uint32_t)dtdAddr->xd_for_this_dtd;
}

/*!
 * @brief Clear the ioc int status
 *
 * This function Clear the ioc int status
 *
 * @param the epQueueHeadAddr
 */
static inline void usb_hal_ehci_clear_size_ioc_int_sts( usb_ehc_dev_qh_struct_t * epQueueHeadAddr)
{
    epQueueHeadAddr->SIZE_IOC_INT_STS = 0;
}


/*!
 * @brief Get the fstn normal path link ptr
 *
 * This function Get the fstn normal path link ptr
 *
 * @param the FSTN_ptr
 * @return the normal path link ptr
 */
static inline uint32_t usb_hal_ehci_get_fstn_normal_path_link_ptr(ehci_fstn_struct_t* FSTN_ptr)
{
   return FSTN_ptr->normal_path_link_ptr;
}

/*!
 * @brief Set the fstn normal path link ptr
 *
 * This function Set the fstn normal path link ptr
 *
 * @param the FSTN_ptr
 * @param the normal path link ptr value
 */
static inline void  usb_hal_ehci_set_fstn_normal_path_link_ptr(ehci_fstn_struct_t* FSTN_ptr, uint32_t next)
{
   FSTN_ptr->normal_path_link_ptr = next;
}

/*!
 * @brief Add the frame list pointer itd
 *
 * This function Add the frame list pointer itd
 *
 * @param the transaction_descriptor
 * @param the itd_ptr
 */
static inline void usb_hal_ehci_add_frame_list_pointer_itd( uint32_t *transaction_descriptor, ehci_itd_struct_t* itd_ptr)
{
   *transaction_descriptor = (uint32_t) itd_ptr | (EHCI_FRAME_LIST_ELEMENT_TYPE_ITD << EHCI_FRAME_LIST_ELEMENT_TYPE_BIT_POS);
}

/*!
 * @brief Add the frame list pointer sitd
 *
 * This function Add the frame list pointer sitd
 *
 * @param the transaction_descriptor
 * @param the sitd_ptr
 */
static inline void usb_hal_ehci_add_frame_list_pointer_sitd( uint32_t *transaction_descriptor, ehci_sitd_struct_t* sitd_ptr)
{
   *transaction_descriptor = (uint32_t) sitd_ptr | (EHCI_FRAME_LIST_ELEMENT_TYPE_SITD << EHCI_FRAME_LIST_ELEMENT_TYPE_BIT_POS);
}

/*!
 * @brief Get the periodic list address
 *
 * This function Get the periodic list address
 *
 * @param the transaction_descriptor
 * @return  the transaction_descriptor pointer
 */
static inline uint32_t usb_hal_ehci_get_periodic_list_addr( volatile uint32_t*  transfer_data_struct_ptr)
{
   return (*transfer_data_struct_ptr);
}

/*!
 * @brief Get the periodic list address
 *
 * This function Get the periodic list address
 *
 * @param the transaction_descriptor
 * @return  the transaction_descriptor pointer
 */
static inline void usb_hal_ehci_set_periodic_list_addr( volatile uint32_t*  transfer_data_struct_ptr, ehci_qh_struct_t* qh_ptr)
{
   *transfer_data_struct_ptr = ((uint32_t)qh_ptr | (EHCI_FRAME_LIST_ELEMENT_TYPE_QH << EHCI_QH_ELEMENT_TYPE_BIT_POS));
}

/*!
 * @brief Set the transfer data struct
 *
 * This function Set the transfer data struct
 *
 * @param the transaction_descriptor
 * @param  the temp_transfer_struct_ptr pointer
 */
static inline void usb_hal_ehci_set_transfer_data_struct( volatile uint32_t*  transfer_data_struct_ptr, uint32_t temp_transfer_struct_ptr)
{
  *transfer_data_struct_ptr = temp_transfer_struct_ptr;
}

//static inline void usb_hal_ehci_store_device_address( ehci_itd_struct_t* itd_ptr)
//{
//   itd_ptr->buffer_page_ptr_list[0] |= (uint32_t)(pipe_descr_ptr->G.DEVICE_ADDRESS);
//}

/*!
 * @brief Set the itd next link pointer
 *
 * This function Set the itd next link pointer
 *
 * @param the itd_ptr
 * @param  the transaction_descriptor pointer
 */
static inline void usb_hal_ehci_set_itd_next_link_pointer(ehci_itd_struct_t* itd_ptr, uint32_t transaction_descriptor )
{
    itd_ptr->next_link_ptr = (uint32_t)transaction_descriptor;
}

/*!
 * @brief Get the itd next link pointer
 *
 * This function Get the itd next link pointer
 *
 * @param the itd_ptr
 * @return  the next link pointer
 */
static inline uint32_t usb_hal_ehci_get_itd_next_link_pointer(ehci_itd_struct_t* itd_ptr)
{
   return itd_ptr->next_link_ptr;
}

/*!
 * @brief Set the itd next link pointer terminate bit
 *
 * This function Set the itd next link pointer terminate bit
 *
 * @param the itd_ptr
 */
static inline void usb_hal_ehci_set_ITD_terminate_bit(ehci_itd_struct_t* itd_ptr)
{
   itd_ptr->next_link_ptr = EHCI_ITD_T_BIT;
}

/*!
 * @brief Store the endpoint number and device address
 *
 * This function Store the endpoint number and device address
 *
 * @param the itd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_store_endpoint_number_and_device_addr( ehci_itd_struct_t* itd_ptr, uint32_t value)
{
    itd_ptr->buffer_page_ptr_list[0] = value;
}

/*!
 * @brief Store the max packet size and direction
 *
 * This function Store the max packet size and direction
 *
 * @param the itd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_store_max_packet_size_and_direction( ehci_itd_struct_t* itd_ptr, uint32_t value)
{
    itd_ptr->buffer_page_ptr_list[1] = value;
}

/*!
 * @brief Store the  direction
 *
 * This function Store the direction
 *
 * @param the itd_ptr
 * @param the direction
 */
static inline void usb_hal_ehci_store_direction( ehci_itd_struct_t* itd_ptr, uint32_t direction)
{
    itd_ptr->buffer_page_ptr_list[1] |= (uint32_t)(direction << EHCI_ITD_DIRECTION_BIT_POS);
}

/*!
 * @brief Store the transaction number per micro frame
 *
 * This function Store the transaction number per micro frame
 *
 * @param the itd_ptr
 * @param the number
 */
static inline void usb_hal_ehci_set_transaction_number_per_micro_frame( ehci_itd_struct_t* itd_ptr, uint32_t number)
{
   itd_ptr->buffer_page_ptr_list[2] = number;
}

/*!
 * @brief Set buffer page pointer
 *
 * This function Set buffer page pointer
 *
 * @param the itd_ptr
 * @param the page_number
 * @param the buffer ptr pointer
 */
static inline void usb_hal_ehci_set_buffer_page_pointer( ehci_itd_struct_t* itd_ptr, uint32_t page_number, uint32_t buffer_ptr)
{
   itd_ptr->buffer_page_ptr_list[page_number] = buffer_ptr;
}

/*!
 * @brief Get buffer page pointer
 *
 * This function Get buffer page pointer
 *
 * @param the itd_ptr
 * @param the page_number
 * @return the buffer ptr pointer
 */
static inline uint32_t usb_hal_ehci_get_buffer_page_pointer( ehci_itd_struct_t* itd_ptr, uint32_t page_number)
{
   return itd_ptr->buffer_page_ptr_list[page_number];
}

/*!
 * @brief Set the transcation and control bit
 *
 * This function Set the transcation and control bit
 *
 * @param the itd_ptr
 * @param the number
 * @param the value
 */
static inline void usb_hal_ehci_set_transcation_status_and_control_bit( ehci_itd_struct_t* itd_ptr, uint32_t number, uint32_t value)
{
  itd_ptr->tr_status_ctl_list[number] = value;
}

/*!
 * @brief Set the transcation status active bit
 *
 * This function Set the transcation status active bit
 *
 * @param the itd_ptr
 * @param the number
 */
static inline void usb_hal_ehci_set_transcation_status_active_bit( ehci_itd_struct_t* itd_ptr, uint32_t number)
{
   itd_ptr->tr_status_ctl_list[number] = itd_ptr->tr_status_ctl_list[number] | EHCI_ITD_ACTIVE_BIT;
}

/*!
 * @brief Get the transcation status control bit
 *
 * This function Get the transcation status control bit
 *
 * @param the itd_ptr
 * @param the transaction_number
 * @return the transcation status control bit
 */
static inline uint32_t usb_hal_ehci_get_transcation_status_ctl_list( ehci_itd_struct_t* itd_ptr, uint32_t transaction_number)
{
   return itd_ptr->tr_status_ctl_list[transaction_number];
}

/*!
 * @brief Set the itd lenght scheduled
 *
 * This function Set the itd lenght scheduled
 *
 * @param the itd_ptr
 * @param the length_scheduled
 */
static inline void usb_hal_ehci_set_itd_length_scheduled( ehci_itd_struct_t* itd_ptr, uint32_t length_scheduled)
{
  itd_ptr->reserved[MEM_SIZE_INDEX] = length_scheduled;
}

/*!
 * @brief Set the sitd next link pointer
 *
 * This function Set the sitd next link pointer
 *
 * @param the sitd_ptr
 * @param the transaction_descriptor
 */
static inline void usb_hal_ehci_set_sitd_next_link_pointer(ehci_sitd_struct_t* sitd_ptr, uint32_t transaction_descriptor )
{
    sitd_ptr->next_link_ptr =  (uint32_t)transaction_descriptor;
}

/*!
 * @brief Get the sitd next link pointer
 *
 * This function Get the sitd next link pointer
 *
 * @param the sitd_ptr
 * @return the transaction_descriptor
 */
static inline uint32_t usb_hal_ehci_get_sitd_next_link_pointer(ehci_sitd_struct_t* sitd_ptr)
{
   return sitd_ptr->next_link_ptr;
}

/*!
 * @brief Get the sitd transfer status
 *
 * This function Get the sitd transfer status
 *
 * @param the sitd_ptr
 * @return the sitd transfer status
 */
static inline uint32_t usb_hal_ehci_get_sitd_transfer_state(ehci_sitd_struct_t* sitd_ptr)
{
    return sitd_ptr->transfer_state;
}

/*!
 * @brief Set the sitd next link terminate bit
 *
 * This function Set the sitd next link terminate bit
 *
 * @param the sitd_ptr
 */
static inline void usb_hal_ehci_set_sitd_next_link_terminate_bit( ehci_sitd_struct_t* sitd_ptr)
{
    sitd_ptr->next_link_ptr = EHCI_SITD_T_BIT;
}

/*!
 * @brief Set the sitd back link terminate bit
 *
 * This function Set the back next link terminate bit
 *
 * @param the sitd_ptr
 */
static inline void usb_hal_ehci_set_sitd_back_pointer_terminate_bit( ehci_sitd_struct_t* sitd_ptr)
{
    sitd_ptr->back_link_ptr = EHCI_SITD_T_BIT;
}

/*!
 * @brief Set the sitd ep capab charac register
 *
 * This function Set the sitd ep capab charac register
 *
 * @param the sitd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_set_sitd_ep_capab_charac( ehci_sitd_struct_t* sitd_ptr, uint32_t value)
{
   sitd_ptr->ep_capab_charac = value;
}

/*!
 * @brief Set the sitd uframe sched ctl register
 *
 * This function Set the sitd uframe sched ctl register
 *
 * @param the sitd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_set_sitd_uframe_sched_ctl( ehci_sitd_struct_t* sitd_ptr, uint32_t value)
{
   sitd_ptr->uframe_sched_ctl= value;
}

/*!
 * @brief Set the sitd transfer state
 *
 * This function Set the sitd transfer state
 *
 * @param the sitd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_set_sitd_transfer_state( ehci_sitd_struct_t* sitd_ptr, uint32_t value)
{
   sitd_ptr->transfer_state = value;
}

/*!
 * @brief Set the sitd length scheduled
 *
 * This function Set the sitd length scheduled
 *
 * @param the sitd_ptr
 * @param the length_scheduled
 */
static inline void usb_hal_ehci_set_sitd_length_scheduled( ehci_sitd_struct_t* sitd_ptr, uint32_t length_scheduled)
{
   sitd_ptr->reserved[MEM_SIZE_INDEX] = length_scheduled;
}

/*!
 * @brief Get the sitd length scheduled
 *
 * This function Get the sitd length scheduled
 *
 * @param the sitd_ptr
 * @return the length_scheduled
 */
static inline uint32_t usb_hal_ehci_get_sitd_length_scheduled( ehci_sitd_struct_t* sitd_ptr)
{
  return sitd_ptr->reserved[MEM_SIZE_INDEX];
}

/*!
 * @brief Get the sitd buffer ptr0
 *
 * This function Get the sitd buffer ptr0
 *
 * @param the sitd_ptr
 * @return the buffer ptr0
 */
static inline uint32_t usb_hal_ehci_get_sitd_buffer_ptr_0( ehci_sitd_struct_t* sitd_ptr)
{
  return sitd_ptr->buffer_ptr_0;
}

/*!
 * @brief Set the sitd buffer ptr0
 *
 * This function Set the sitd buffer ptr0
 *
 * @param the sitd_ptr
 * @param the buffer ptr0
 */
static inline void usb_hal_ehci_set_sitd_buffer_ptr_0( ehci_sitd_struct_t* sitd_ptr, uint32_t buffer_ptr)
{
   sitd_ptr->buffer_ptr_0 = buffer_ptr;
}

/*!
 * @brief Set the sitd buffer ptr1
 *
 * This function Set the sitd buffer ptr1
 *
 * @param the sitd_ptr
 * @param the buffer ptr1
 */
static inline void usb_hal_ehci_set_sitd_buffer_ptr_1( ehci_sitd_struct_t* sitd_ptr, uint32_t buffer_ptr)
{
   sitd_ptr->buffer_ptr_1 = buffer_ptr;
}

/*!
 * @brief Set the sitd alt qtd link pointer terminate bit
 *
 * This function Set the sitd alt qtd link pointer terminate bit
 *
 * @param the qh_ptr
 */
static inline void usb_hal_ehci_set_qh_next_alt_qtd_link_terminate( ehci_qh_struct_t* qh_ptr)
{
   qh_ptr->alt_next_qtd_link_ptr = EHCI_QTD_T_BIT;
}

/*!
 * @brief Set the qh next qtd link pointer
 *
 * This function Set the qh next qtd link pointer
 *
 * @param the qh_ptr
 * @param the first_qtd_ptr
 */
static inline void usb_hal_ehci_set_qh_next_qtd_link_ptr( ehci_qh_struct_t* qh_ptr, uint32_t first_qtd_ptr)
{

   qh_ptr->next_qtd_link_ptr = (uint32_t)first_qtd_ptr;
}

/*!
 * @brief Set the qh next qtd link terminate bit
 *
 * This function Set the qh next qtd link terminate bit
 *
 * @param the qh_ptr
 */
static inline void usb_hal_ehci_set_qh_next_qtd_link_terminate( ehci_qh_struct_t* qh_ptr)

{
   qh_ptr->next_qtd_link_ptr = EHCI_QTD_T_BIT;
}

/*!
 * @brief Get the qh next qtd link pointer
 *
 * This function Get the qh next qtd link pointer
 *
 * @param the qh_ptr
 * @return the qh_ptr next qtd link pointer
 */
static inline uint32_t usb_hal_ehci_get_next_qtd_link_ptr( ehci_qh_struct_t* qh_ptr)
{
  return (uint32_t)qh_ptr->next_qtd_link_ptr;
}

/*!
 * @brief Clear the qh status
 *
 * This function Clear the qh status
 *
 * @param the qh_ptr
 */
static inline void usb_hal_ehci_clear_qh_status( ehci_qh_struct_t* qh_ptr)
{
  qh_ptr->status = 0;
}

/*!
 * @brief Return the qh status
 *
 * This function Clear the qh status
 *
 * @param the qh_ptr
 * @return the qh_ptr status
 */
static inline uint32_t usb_hal_ehci_get_qh_status( ehci_qh_struct_t* qh_ptr)
{
   return qh_ptr->status;
}

/*!
 * @brief Set the qh status
 *
 * This function Set the qh status
 *
 * @param the qh_ptr
 * @param the qh_ptr status
 */
static inline void usb_hal_ehci_set_qh_status( ehci_qh_struct_t* qh_ptr, uint32_t status)
{
   qh_ptr->status = status;
}

/*!
 * @brief Get the qh horiz link ptr
 *
 * This function Get the qh horiz link ptr
 *
 * @param the qh_ptr
 * @return the qh horiz link ptr
 */
static inline uint32_t usb_hal_ehci_get_qh_horiz_link_ptr( ehci_qh_struct_t* qh_ptr)
{
  return qh_ptr->horiz_link_ptr;
}

/*!
 * @brief Set the qh horiz link ptr
 *
 * This function Set  the qh horiz link ptr
 *
 * @param the qh_ptr
 * @param the link_ptr
 */
static inline void usb_hal_ehci_set_qh_horiz_link_ptr( ehci_qh_struct_t* qh_ptr, uint32_t link_ptr)
{

   qh_ptr->horiz_link_ptr = link_ptr;
}

/*!
 * @brief Init the qh
 *
 * This function Init the qh
 *
 * @param the qh_ptr
 */
static inline void usb_hal_ehci_init_qh( ehci_qh_struct_t* qh_ptr)
{
    qh_ptr->curr_qtd_link_ptr = EHCI_QTD_T_BIT;
    qh_ptr->alt_next_qtd_link_ptr = EHCI_QTD_T_BIT;
    qh_ptr->status = 0;
    qh_ptr->buffer_ptr_0 = 0;
    qh_ptr->buffer_ptr_1 = 0;
    qh_ptr->buffer_ptr_2 = 0;
    qh_ptr->buffer_ptr_3 = 0;
    qh_ptr->buffer_ptr_4 = 0;
}

/*!
 * @brief Set the ep capab charac1
 *
 * This function Set the ep capab charac1
 *
 * @param the qh_ptr
 * @param the temp_ep_capab
 */
static inline void usb_hal_ehci_set_ep_capab_charac1( ehci_qh_struct_t* qh_ptr, uint32_t temp_ep_capab)
{
   qh_ptr->ep_capab_charac1 = temp_ep_capab;
}

/*!
 * @brief Get the ep capab charac1
 *
 * This function Get the ep capab charac1
 *
 * @param the qh_ptr
 * @return the ep_capab1
 */
static inline uint32_t usb_hal_ehci_get_ep_capab_charac1( ehci_qh_struct_t* qh_ptr)
{
   return qh_ptr->ep_capab_charac1;
}

/*!
 * @brief Set the ep capab charac2
 *
 * This function Set the ep capab charac2
 *
 * @param the qh_ptr
 * @param the temp_ep_capab
 */
static inline void usb_hal_ehci_set_ep_capab_charac2( ehci_qh_struct_t* qh_ptr, uint32_t temp_ep_capab)
{
   qh_ptr->ep_capab_charac2 = temp_ep_capab;
}

/*!
 * @brief Get the ep capab charac2
 *
 * This function Get the ep capab charac2
 *
 * @param the qh_ptr
 * @return the ep_capab2
 */
static inline uint32_t usb_hal_ehci_get_ep_capab_charac2( ehci_qh_struct_t* qh_ptr)
{
   return qh_ptr->ep_capab_charac2;
}

/*!
 * @brief Set the horiz link ptr terminate 
 *
 * This function Set the horiz link ptr terminate 
 *
 * @param the qh_ptr 
 */
static inline void usb_hal_ehci_set_qh_horiz_link_ptr_head_pointer_terminate( ehci_qh_struct_t* qh_ptr)
{
   qh_ptr->horiz_link_ptr = EHCI_QUEUE_HEAD_POINTER_T_BIT;
}

/*!
 * @brief Set the buffer page pointer
 *
 * This function Set the buffer page pointer
 *
 * @param the qh_ptr 
 * @param the buffer_start_address 
 */
static inline void usb_hal_ehci_set_qtd_buffer_page_pointer( ehci_qtd_struct_t* qtd_ptr, uint32_t buffer_start_address)
{
   qtd_ptr->buffer_ptr_0 = buffer_start_address;
   qtd_ptr->buffer_ptr_1 = qtd_ptr->buffer_ptr_0 + 4096;
   qtd_ptr->buffer_ptr_2 = qtd_ptr->buffer_ptr_1 + 4096;
   qtd_ptr->buffer_ptr_3 = qtd_ptr->buffer_ptr_2 + 4096;
   qtd_ptr->buffer_ptr_4 = qtd_ptr->buffer_ptr_3 + 4096;
}

/*!
 * @brief Set the qtd token
 *
 * This function Set the qtd token
 *
 * @param the qh_ptr 
 * @param the token 
 */
static inline void usb_hal_ehci_set_qtd_token( ehci_qtd_struct_t* qtd_ptr, uint32_t token)
{

   qtd_ptr->token = token;
}

/*!
 * @brief Clear the qtd token bits
 *
 * This function Clear the qtd token bits
 *
 * @param the qh_ptr 
 * @param the token_bits 
 */
static inline void usb_hal_ehci_clear_qtd_token_bits( ehci_qtd_struct_t* qtd_ptr, uint32_t token_bits)
{
   qtd_ptr->token &= ~token_bits;
}

/*!
 * @brief Get the qtd token
 *
 * This function Get the qtd token
 *
 * @param the qtd_ptr
 */
static inline uint32_t usb_hal_ehci_get_qtd_token( ehci_qtd_struct_t* qtd_ptr)
{

   return qtd_ptr->token;
}

/*!
 * @brief Set the qtd next ptr terminate
 *
 * This function Set the qtd next ptr terminate
 *
 * @param the qtd_ptr
 */
static inline void usb_hal_ehci_set_qtd_terminate_bit( ehci_qtd_struct_t* qtd_ptr)
{
    qtd_ptr->next_qtd_ptr = EHCI_QTD_T_BIT;
}

/*!
 * @brief Get the qtd next ptr 
 *
 * This function Get the qtd next ptr 
 *
 * @param the qtd_ptr
 * @return the qtd next ptr
 */
static inline uint32_t usb_hal_ehci_get_next_qtd_ptr(ehci_qtd_struct_t* qtd_ptr)
{
    return qtd_ptr->next_qtd_ptr;
}

/*!
 * @brief Set the alt next qtd terminate bit
 *
 * This function Set the alt next qtd terminate bit
 *
 * @param the qtd_ptr
 */
static inline void usb_hal_ehci_set_alt_next_qtd_terminate_bit( ehci_qtd_struct_t* qtd_ptr)
{
  qtd_ptr->alt_next_qtd_ptr = EHCI_QTD_T_BIT;
}

/*!
 * @brief Set the next qtd ptr
 *
 * This function Set the next qtd ptr
 *
 * @param the prev_qtd_ptr
 * @param the qtd_ptr
 */
static inline void usb_hal_ehci_link_qtd( ehci_qtd_struct_t* prev_qtd_ptr,uint32_t qtd_ptr)
{
   prev_qtd_ptr->next_qtd_ptr = qtd_ptr;
}

/*!
 * @brief Enable the otg interrupts
 *
 * This function Enable the otg interrupts
 *
 * @param the baseAddr
 * @param the intrType
 */
static inline void usb_hal_ehci_enable_otg_interrupts(uint32_t baseAddr, uint32_t intrType)
{
    USBHS_OTGSC_REG((USBHS_MemMapPtr)baseAddr) |= intrType;
}

/*!
 * @brief Disable the otg interrupts
 *
 * This function Disable the otg interrupts
 *
 * @param the baseAddr
 * @param the intrType
 */
static inline void usb_hal_ehci_disable_otg_interrupts(uint32_t baseAddr, uint32_t intrType)
{
    USBHS_OTGSC_REG((USBHS_MemMapPtr)baseAddr) &= ~intrType;
}

/*!
 * @brief Clear the otg interrupts
 *
 * This function Clear the otg interrupts
 *
 * @param the baseAddr
 * @param the intrType
 */
static inline void usb_hal_ehci_clear_otg_interrupts(uint32_t baseAddr, uint32_t intrType)
{
    USBHS_OTGSC_REG((USBHS_MemMapPtr)baseAddr)|= intrType;
}

/*!
 * @brief Get the otg status
 *
 * This function Get the otg status
 *
 * @param the baseAddr
 * @return the otg status
 */
static inline uint32_t usb_hal_ehci_get_otg_status(uint32_t baseAddr)
{
    return USBHS_OTGSC_REG((USBHS_MemMapPtr)baseAddr);
    
}
#else
/*!
 * @brief Set the controller mode to host.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_controller_host_mode(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBMODE = (usb_reg_base_ptr->USBMODE & ~USB_USBMODE_CM_MASK) | USB_USBMODE_CM(0x3); 
}

/*!
 * @brief Set the controller mode to device.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_controller_device_mode(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBMODE = (usb_reg_base_ptr->USBMODE & ~USB_USBMODE_CM_MASK) | USB_USBMODE_CM(0x2); 
}

/*!
 * @brief Set the controller mode to big endian.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_big_endian(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBMODE = (usb_reg_base_ptr->USBMODE & ~USB_USBMODE_ES_MASK)|(1 << USB_USBMODE_ES_SHIFT);
}

/*!
 * @brief Set the controller mode to little endian.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_little_endian(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBMODE = (usb_reg_base_ptr->USBMODE & ~USB_USBMODE_ES_MASK)|(0 << USB_USBMODE_ES_SHIFT);
}

/*!
 * @brief Set the controller mode to disable lock clock.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_disable_setup_lock(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBMODE = (usb_reg_base_ptr->USBMODE & ~USB_USBMODE_SLOM_MASK)|(1 << USB_USBMODE_SLOM_SHIFT);
}

/*!
 * @brief Set the controller mode to enable lock clock.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_enable_setup_lock(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBMODE = (usb_reg_base_ptr->USBMODE & ~USB_USBMODE_SLOM_MASK)|(0 << USB_USBMODE_SLOM_SHIFT);
}

/*!
 * @brief Set the controller mode to specific mode.
 *
 * This function enables get the base addr of ehci
 *
 * @param the baseAddr
 * @param the mode
 */
static inline void usb_hal_ehci_set_usb_mode(uint32_t baseAddr, uint32_t mode)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBMODE = mode;
}

/*!
 * @brief Get the dcc params.
 *
 * This function gets the dcc params
 *
 * @param the baseAddr
 * @return Current dcc params
 */
static inline uint32_t usb_hal_ehci_get_dcc_params(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->DCCPARAMS;
}

/*!
 * @brief Clear epsetup status.
 *
 * This function clears the epsetup status
 *
 * @param the baseAddr
 * @param the epSetupStatus
 */
static inline void usb_hal_ehci_clear_ep_setup_status(uint32_t baseAddr, uint32_t epSetupStatus)
{   
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->ENDPTSETUPSTAT |= (epSetupStatus << USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_SHIFT) & USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_MASK;
}

/*!
 * @brief Clear epsetup epnum.
 *
 * This function clears the epsetup epnum
 *
 * @param the baseAddr
 * @param the ep_num
 */
static inline void usb_hal_ehci_clear_setup_stat_ep_num(uint32_t baseAddr, uint32_t ep_num)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->ENDPTSETUPSTAT = ep_num;
}

/*!
 * @brief Get epsetup status.
 *
 * This function gets the epsetup status
 *
 * @param the baseAddr
 * @return the epSetupStatus
 */
static inline uint32_t usb_hal_ehci_get_ep_setup_status(uint32_t baseAddr)
{   
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->ENDPTSETUPSTAT;
}

/*!
 * @brief Get ep complete status.
 *
 * This function gets the complete status
 *
 * @param the baseAddr
 * @return the complete status
 */
static inline uint32_t usb_hal_ehci_get_ep_complete_status(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->ENDPTCOMPLETE;
}

/*!
 * @brief Clear ep complete status.
 *
 * This function clears the complete status
 *
 * @param the baseAddr
 * @param the epCompleteStatus
 */
static inline void usb_hal_ehci_clear_ep_complete_status(uint32_t baseAddr, uint32_t epCompleteStatus)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->ENDPTCOMPLETE = epCompleteStatus;
}

/*!
 * @brief Set eplist address.
 *
 * This function Set eplist address
 *
 * @param the baseAddr
 * @param the epQHAddress
 */
static inline void usb_hal_ehci_set_eplist_address(uint32_t baseAddr, uint32_t epQHAddress)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->ENDPTLISTADDR = epQHAddress;
}

/*!
 * @brief Get eplist address.
 *
 * This function Get eplist address
 *
 * @param the baseAddr
 * @return the epQHAddress
 */
static inline uint32_t usb_hal_ehci_get_eplist_address(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->ENDPTLISTADDR;
}

/*!
 * @brief Get the interrupt enable register status.
 *
 * This function Get the interrupt enable register status
 *
 * @param the baseAddr
 * @return the interrupt enable register status
 */
static inline uint32_t usb_hal_ehci_get_interrupt_enable_status(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
        return usb_reg_base_ptr->USBINTR;
}

/*!
 * @brief Enable the specific interrupt.
 *
 * This function Enable the specific interrupt
 *
 * @param the baseAddr
 * @return the specific interrupt
 */
static inline void usb_hal_ehci_enable_interrupts(uint32_t baseAddr, uint32_t intrType)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBINTR |= intrType;
}

/*!
 * @brief Set the interrupt register to a specific value.
 *
 * This function Set the interrupt register to a specific value
 *
 * @param the baseAddr
 * @param the specific value
 */
static inline void usb_hal_ehci_interrupts_set(uint32_t baseAddr, uint32_t intrType)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBINTR = intrType;
}

/*!
 * @brief Disable the specific interrupts.
 *
 * This function Disable the specific interrupts
 *
 * @param the baseAddr
 * @param the specific interrupts
 */
static inline void usb_hal_ehci_disable_interrupts(uint32_t baseAddr, uint32_t intrType)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBINTR &= ~intrType;
}

/*!
 * @brief Initiate attach event.
 *
 * This function Initiate attach event
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_initiate_attach_event(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD |= EHCI_CMD_RUN_STOP;
}

/*!
 * @brief Initiate deattach event.
 *
 * This function Initiate deattach event
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_initiate_detach_event(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD &= ~EHCI_CMD_RUN_STOP;
}

/*!
 * @brief Reset the controller.
 *
 * This function Reset the controller
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_reset_controller(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD = EHCI_CMD_CTRL_RESET;
}

/*!
 * @brief Set the dtd tripwire.
 *
 * This function Reset the controller
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_dtd_tripwire(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD |= EHCI_CMD_ATDTW_TRIPWIRE_SET;
}

/*!
 * @brief Clear the dtd tripwire.
 *
 * This function Clear the controller
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_clear_dtd_tripwire(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD &= ~EHCI_CMD_ATDTW_TRIPWIRE_SET;
}

/*!
 * @brief Disable the usb cmd async sched.
 *
 * This function Disable the usb cmd async sched
 *
 * @param the baseAddr
 */
static inline void usb_hal_echi_disable_usb_cmd_async_sched(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD &= ~EHCI_USBCMD_ASYNC_SCHED_ENABLE;
}

/*!
 * @brief Enable the usb cmd async sched.
 *
 * This function Enable the usb cmd async sched
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_enable_usb_cmd_async_sched(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD |= EHCI_USBCMD_ASYNC_SCHED_ENABLE;
}

/*!
 * @brief Disable the usb cmd periodic sched.
 *
 * This function Disable the usb periodic async sched
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_disable_usb_cmd_periodic_sched(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD &= ~EHCI_USBCMD_PERIODIC_SCHED_ENABLE;
}

/*!
 * @brief Get the dtd tripwire status.
 *
 * This function Get the dtd tripwire status
 *
 * @param the baseAddr
 * @return the dtd tripwire status
 */
static inline uint32_t usb_hal_ehci_is_tripwire_set(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return (usb_reg_base_ptr->USBCMD & EHCI_CMD_ATDTW_TRIPWIRE_SET);
}

/*!
 * @brief Clear the dtd tripwire status.
 *
 * This function Clear the dtd tripwire status
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_clear_usb_cmd_setup_trip_wire(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD &= ~EHCI_CMD_SETUP_TRIPWIRE_SET;
}

/*!
 * @brief Set the dtd tripwire status.
 *
 * This function Clear the dtd tripwire status
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_set_usb_cmd_setup_trip_wire(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD |= EHCI_CMD_SETUP_TRIPWIRE_SET;
}

/*!
 * @brief Set the usb cmd register to a specific value.
 *
 * This function Set the usb cmd register to a specific value
 *
 * @param the baseAddr
 * @param the specific value
 */
static inline void usb_hal_ehci_set_usb_cmd(uint32_t baseAddr, uint32_t value)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBCMD = value;
}

/*!
 * @brief Get the usb cmd value.
 *
 * This function Get the usb cmd register value
 *
 * @param the baseAddr
 * @return the specific value
 */
static inline uint32_t  usb_hal_ehci_get_usb_cmd(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->USBCMD;
}

/*!
 * @brief Set the usb config register to a specific value.
 *
 * This function Set the usb config register to a specific value
 *
 * @param the baseAddr
 * @param the value
 */
static inline void usb_hal_ehci_set_usb_config(uint32_t baseAddr, uint32_t value)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    //usb_reg_base_ptr->CONFIGFLAG = value;
}

/*!
 * @brief Set the usb endpoint prime to a specific value.
 *
 * This function Set the usb endpoint prime to a specific value
 *
 * @param the baseAddr
 * @param the value
 */
static inline void usb_hal_ehci_set_endpoint_prime(uint32_t baseAddr, uint32_t value)
{   
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->ENDPTPRIME = value;
}

/*!
 * @brief Get the usb endpoint prime  value.
 *
 * This function Get the usb endpoint prime  value
 *
 * @param the baseAddr
 * @return the value
 */
static inline uint32_t usb_hal_ehci_get_endpoint_prime(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->ENDPTPRIME;
}

/*!
 * @brief Get the usb endpoint status
 *
 * This function Get the usb endpoint status
 *
 * @param the baseAddr
 * @return the value
 */
static inline uint32_t usb_hal_echi_get_endpoint_status(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->ENDPTSTAT;
}

/*!
 * @brief Flush the endpoint buffer
 *
 * This function Flush the endpoint buffer
 *
 * @param the baseAddr
 * @param the epNumber
 */
static inline void usb_hal_ehci_flush_endpoint_buffer(uint32_t baseAddr, uint32_t epNumber)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->ENDPTFLUSH = epNumber;
}

/*!
 * @brief Get the endpoint transfer buffer status
 *
 * This function Get the endpoint transfer buffer status
 *
 * @param the baseAddr
 * @param the epNumber
 * @return the transfer buffer status
 */
static inline uint32_t usb_hal_ehci_is_endpoint_transfer_flushed(uint32_t baseAddr, uint32_t epNumber)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return (usb_reg_base_ptr->ENDPTFLUSH & epNumber);
}

/*!
 * @brief Get the frame index
 *
 * This function Get the frame index
 *
 * @param the baseAddr
 * @return the frame index
 */
static inline uint32_t usb_hal_ehci_get_frame_index(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->FRINDEX;
}

/*!
 * @brief Get the port status
 *
 * This function Get the port status
 *
 * @param the baseAddr
 * @return the port status
 */
static inline uint32_t usb_hal_ehci_get_port_status(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->PORTSC1;
}

/*!
 * @brief Set the port status
 *
 * This function Set the port status
 *
 * @param the baseAddr
 * @param the port status
 */
static inline void usb_hal_ehci_set_port_status(uint32_t baseAddr, uint32_t status)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->PORTSC1 = status;
}

/*!
 * @brief Get the usb interrupt status register value
 *
 * This function Get the usb interrupt status register value
 *
 * @param the baseAddr
 * @return  the usb interrupt status register value
 */
static inline uint32_t usb_hal_ehci_get_usb_interrupt_status(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->USBSTS;
}

/*!
 * @brief Clear the usb interrupt status register value
 *
 * This function Clear the usb interrupt status register value
 *
 * @param the baseAddr
 * @param  the usb interrupt status register value
 */
static inline void usb_hal_ehci_clear_usb_interrupt_status(uint32_t baseAddr, uint32_t status)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->USBSTS = status;
}


static inline void usb_hal_ehci_set_device_address(uint32_t baseAddr, uint32_t address)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->DEVICEADDR = (uint32_t)(address << USB_DEVICEADDR_USBADR_SHIFT);
}

/*!
 * @brief Get the hcsparams value
 *
 * This function Get the hcsparams value
 *
 * @param the baseAddr
 * @return the hcsparams value
 */
static inline uint32_t usb_hal_ehci_get_hcsparams(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->HCSPARAMS;
}

/*!
 * @brief Get the hccparams value
 *
 * This function Get the hccparams value
 *
 * @param the baseAddr
 * @return the hccparams value
 */
static inline uint32_t usb_hal_ehci_get_hccparams(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return usb_reg_base_ptr->HCCPARAMS;
}

/*!
 * @brief Clear the device address
 *
 * This function Clear the device address
 *
 * @param the baseAddr
 */
static inline void usb_hal_ehci_clear_device_address(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->DEVICEADDR &= ~0xFE000000;
}

/*!
 * @brief Set qh to curr async list
 *
 * This function Set qh to curr async list
 *
 * @param the baseAddr
 * @param the qh address
 */
static inline void usb_hal_ehci_set_qh_to_curr_async_list(uint32_t baseAddr, uint32_t qh_addr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->ASYNCLISTADDR = qh_addr;
}

/*!
 * @brief Get qh from curr async list
 *
 * This function Get qh from curr async list
 *
 * @param the baseAddr
 * @return the qh address
 */
static inline uint32_t usb_hal_ehci_get_curr_async_list(uint32_t baseAddr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
   return   usb_reg_base_ptr->ASYNCLISTADDR;
}

/*!
 * @brief Set the periodic list base address
 *
 * This function Set the periodic list base address
 *
 * @param the baseAddr
 * @param the periodic list base address
 */
static inline void usb_hal_ehci_set_periodic_list_base_addr(uint32_t baseAddr, uint32_t base_addr)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    usb_reg_base_ptr->PERIODICLISTBASE = base_addr;
}

/*!
 * @brief Enable the specific endpoint
 *
 * This function Enable the specific endpoint
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 * @param the type
 */
static inline void usb_hal_ehci_enable_endpoint(uint32_t baseAddr, uint32_t epNumber, uint32_t direction, uint32_t type)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    
    if (epNumber == 0)
        usb_reg_base_ptr->ENDPTCTRL0 |= ((direction ? (EHCI_EPCTRL_TX_ENABLE |
            EHCI_EPCTRL_TX_DATA_TOGGLE_RST) :
            (EHCI_EPCTRL_RX_ENABLE | EHCI_EPCTRL_RX_DATA_TOGGLE_RST)) |
            (type << (direction ?
            EHCI_EPCTRL_TX_EP_TYPE_SHIFT : EHCI_EPCTRL_RX_EP_TYPE_SHIFT)));
    else
        usb_reg_base_ptr->ENDPTCTRL[epNumber - 1] |= ((direction ? (EHCI_EPCTRL_TX_ENABLE |
            EHCI_EPCTRL_TX_DATA_TOGGLE_RST) :
            (EHCI_EPCTRL_RX_ENABLE | EHCI_EPCTRL_RX_DATA_TOGGLE_RST)) |
            (type << (direction ?
            EHCI_EPCTRL_TX_EP_TYPE_SHIFT : EHCI_EPCTRL_RX_EP_TYPE_SHIFT)));
}

/*!
 * @brief Disable the specific endpoint
 *
 * This function Disable the specific endpoint
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 */
static inline void usb_hal_ehci_disable_endpoint(uint32_t baseAddr, uint32_t epNumber, uint32_t direction)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;

    usb_reg_base_ptr->ENDPTCTRL[epNumber] &= ~(direction ? (EHCI_EPCTRL_TX_ENABLE|EHCI_EPCTRL_TX_TYPE):(EHCI_EPCTRL_RX_ENABLE|EHCI_EPCTRL_RX_TYPE));
}

/*!
 * @brief Get the endpoint ep control value
 *
 * This function Get the endpoint ep control value
 *
 * @param the baseAddr
 * @param the epNumber
 * @return the control value
 */
static inline uint32_t usb_hal_ehci_get_endpoint_control(uint32_t baseAddr, uint32_t epNumber)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    return (epNumber == 0 ? usb_reg_base_ptr->ENDPTCTRL0 : usb_reg_base_ptr->ENDPTCTRL[epNumber - 1]);
}

/*!
 * @brief Clear the endpoint  stall status
 *
 * This function Clear the endpoint  stall status
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 */
static inline void usb_hal_ehci_clear_endpoint_stall(uint32_t baseAddr, uint32_t epNumber, uint32_t direction)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    if (epNumber == 0)
        usb_reg_base_ptr->ENDPTCTRL0 &= ~(direction ? EHCI_EPCTRL_TX_EP_STALL : EHCI_EPCTRL_RX_EP_STALL);
    else
        usb_reg_base_ptr->ENDPTCTRL[epNumber - 1] &= ~(direction ? EHCI_EPCTRL_TX_EP_STALL : EHCI_EPCTRL_RX_EP_STALL);
}

/*!
 * @brief Reset the endpoint data toggle
 *
 * This function Reset the endpoint data toggle
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 */
static inline void usb_hal_ehci_reset_endpoint_data_toggle(uint32_t baseAddr, uint32_t epNumber, uint32_t direction)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    if (epNumber != 0)
        usb_reg_base_ptr->ENDPTCTRL[epNumber - 1] |= (direction ? EHCI_EPCTRL_TX_DATA_TOGGLE_RST : EHCI_EPCTRL_RX_DATA_TOGGLE_RST);
}

/*!
 * @brief Stall the endpoint both directions
 *
 * This function Stall the endpoint both directions
 *
 * @param the baseAddr
 * @param the epNumber
 */
static inline void usb_hal_ehci_stall_both_directions(uint32_t baseAddr, uint32_t epNumber)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    if (epNumber == 0)
        usb_reg_base_ptr->ENDPTCTRL0 |= (EHCI_EPCTRL_TX_EP_STALL | EHCI_EPCTRL_RX_EP_STALL);
    else
        usb_reg_base_ptr->ENDPTCTRL[epNumber - 1] |= (EHCI_EPCTRL_TX_EP_STALL | EHCI_EPCTRL_RX_EP_STALL);
}

/*!
 * @brief Stall the endpoint specific directions
 *
 * This function Stall the endpoint specific directions
 *
 * @param the baseAddr
 * @param the epNumber
 * @param the direction
 */
static inline void usb_hal_ehci_stall_specific_direction(uint32_t baseAddr, uint32_t epNumber, uint32_t direction)
{
    USB_MemMapPtr usb_reg_base_ptr;
    usb_reg_base_ptr = (USB_MemMapPtr)baseAddr;
    if (epNumber == 0)
        usb_reg_base_ptr->ENDPTCTRL0 |= (direction ? EHCI_EPCTRL_TX_EP_STALL : EHCI_EPCTRL_RX_EP_STALL);
    else
        usb_reg_base_ptr->ENDPTCTRL[epNumber - 1] |= (direction ? EHCI_EPCTRL_TX_EP_STALL : EHCI_EPCTRL_RX_EP_STALL);
        
}

/*!
 * @brief Clear the ep QH max packet length
 *
 * This function Clear the ep QH max packet length
 *
 * @param the epQueueHeadAddr
 */
static inline void usb_hal_ehci_clear_max_packet_length(usb_ehc_dev_qh_struct_t * epQueueHeadAddr)
{
    epQueueHeadAddr->MAX_PKT_LENGTH = 0;
}

/*!
 * @brief Set the ep QH max packet length
 *
 * This function Set the ep QH max packet length
 *
 * @param the epQueueHeadAddr
 * @param the maxPacketSize
 */
static inline void usb_hal_ehci_set_max_packet_length(usb_ehc_dev_qh_struct_t * epQueueHeadAddr, uint32_t maxPacketSize)
{
    epQueueHeadAddr->MAX_PKT_LENGTH = ((uint32_t)maxPacketSize);
}

/*!
 * @brief Set the ep QH max packet length for non iso
 *
 * This function Set the ep QH max packet length for non iso
 *
 * @param the epQueueHeadAddr
 * @param the value
 */
static inline void usb_hal_ehci_set_max_packet_length_for_non_iso(usb_ehc_dev_qh_struct_t * epQueueHeadAddr, uint32_t value)
{
    epQueueHeadAddr->MAX_PKT_LENGTH = value;
}

/*!
 * @brief Get the ehci iso set value
 *
 * This function Get the ehci iso set value
 *
 * @param the epQueueHeadAddr
 * @return the value
 */
static inline uint32_t usb_hal_ehci_is_ios_set( usb_ehc_dev_qh_struct_t * epQueueHeadAddr)
{
    return (epQueueHeadAddr->MAX_PKT_LENGTH & VUSB_EP_QUEUE_HEAD_IOS);
}

/*!
 * @brief Set the dtd terminate value
 *
 * This function Set the dtd terminate value
 *
 * @param the epQueueHeadAddr
 * @return the value
 */
static inline void usb_hal_ehci_set_next_dtd_terminate(usb_ehc_dev_qh_struct_t * epQueueHeadAddr)
{
    epQueueHeadAddr->NEXT_DTD_PTR = VUSB_EP_QUEUE_HEAD_NEXT_TERMINATE;
}

/*!
 * @brief Set the next tr elem dtd terminate value
 *
 * This function Set the next tr elem dtd terminate value
 *
 * @param the epQueueHeadAddr
 * @param the dTD_ptr
 */
static inline void usb_hal_ehci_set_dtd_next_tr_elem_terminate( usb_ehci_dev_dtd_struct_t * dTD_ptr)
{
   dTD_ptr->NEXT_TR_ELEM_PTR = VUSB_EP_QUEUE_HEAD_NEXT_TERMINATE;
}

/*!
 * @brief Set the next tr elem dtd ptr
 *
 * This function Set the next tr elem dtd ptr
 *
 * @param the temp_dTD_ptr
 * @param the dTD_ptr
 */
static inline void usb_hal_ehci_set_dtd_next_tr_elem_ptr( usb_ehci_dev_dtd_struct_t * temp_dTD_ptr, uint32_t dTD_ptr)
{
   temp_dTD_ptr->NEXT_TR_ELEM_PTR = dTD_ptr;
}

/*!
 * @brief Set the epQueueHeadAddr next dtd ptr
 *
 * This function Set the epQueueHeadAddr next dtd ptr
 *
 * @param the epQueueHeadAddr
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_set_qh_next_dtd(usb_ehc_dev_qh_struct_t * epQueueHeadAddr, uint32_t dtdAddr)
{
    epQueueHeadAddr->NEXT_DTD_PTR = dtdAddr;
}

/*!
 * @brief Set the next dtd invalid
 *
 * This function Set the next dtd invalid
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_set_next_dtd_invalid( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    dtdAddr->NEXT_TR_ELEM_PTR = USBHS_TD_NEXT_TERMINATE;
}

/*!
 * @brief Clear the dtd size ioc status
 *
 * This function Clear the dtd size ioc status
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_clear_size_ioc_sts( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    dtdAddr->SIZE_IOC_STS = 0;
}

/*!
 * @brief Clear the dtd size ioc status reserved fields
 *
 * This function Clear the dtd size ioc status reserved fields
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_clear_ioc_reserved_fields( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    dtdAddr->SIZE_IOC_STS &= ~USBHS_TD_RESERVED_FIELDS;
}

/*!
 * @brief Clear the dtd 
 *
 * This function Clear the dtd 
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_clear_dtd( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    dtdAddr->NEXT_TR_ELEM_PTR = 0;
    dtdAddr->SIZE_IOC_STS = 0;
    dtdAddr->BUFF_PTR0 = 0;
    dtdAddr->BUFF_PTR1 = 0;
    dtdAddr->BUFF_PTR2 = 0;
    dtdAddr->BUFF_PTR3 = 0;
    dtdAddr->BUFF_PTR4 = 0;
}

/*!
 * @brief Set the dtd buffer address
 *
 * This function Set the dtd buffer address
 *
 * @param the dtdAddr
 */
static inline void usb_hal_ehci_set_dtd_buffer_address( usb_ehci_dev_dtd_struct_t * dtdAddr, uint32_t addr)
{
    dtdAddr->BUFF_PTR0 = addr;
    dtdAddr->BUFF_PTR1 = addr + 4096;
    dtdAddr->BUFF_PTR2 = addr + (4096*2);
    dtdAddr->BUFF_PTR3 = addr + (4096*3);
    dtdAddr->BUFF_PTR4 = addr + (4096*4);
}

/*!
 * @brief Set the dtd size ioc status value
 *
 * This function Set the dtd size ioc status value
 *
 * @param the dtdAddr
 * @param the value
 */
static inline void usb_hal_ehci_set_dtd_size_ioc_status( usb_ehci_dev_dtd_struct_t * dtdAddr, uint32_t value)
{
    dtdAddr->SIZE_IOC_STS = value;
}

/*!
 * @brief Get the dtd size ioc status value
 *
 * This function Get the dtd size ioc status value
 *
 * @param the dtdAddr
 * @return the value
 */
static inline uint32_t usb_hal_ehci_get_dtd_size_ioc_status( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return dtdAddr->SIZE_IOC_STS;
}

/*!
 * @brief Get the next dtd address
 *
 * This function Get the next dtd address
 *
 * @param the dtdAddr
 * @return the next dtd address
 */
static inline uint32_t usb_hal_ehci_get_next_dtd_address( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return (dtdAddr->NEXT_TR_ELEM_PTR & USBHS_TD_ADDR_MASK);
}

/*!
 * @brief Get the dtd error status
 *
 * This function Get the dtd error status
 *
 * @param the dtdAddr
 * @return the dtd error status
 */
static inline uint32_t usb_hal_ehci_get_dtd_error_status( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return (dtdAddr->SIZE_IOC_STS & USBHS_TD_ERROR_MASK);
}

/*!
 * @brief Clear the qh error status
 *
 * This function Clear the qh error status
 *
 * @param the epQueueHeadAddr
 * @param the errors
 */
static inline void usb_hal_ehci_clear_qh_error_status( usb_ehc_dev_qh_struct_t * epQueueHeadAddr, uint32_t errors)
{
    epQueueHeadAddr->SIZE_IOC_INT_STS &= ~errors;
}

/*!
 * @brief Get the tr packet size
 *
 * This function Get the tr packet size
 *
 * @param the dtdAddr
 */
static inline uint32_t usb_hal_ehci_get_tr_packet_size(usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return ((dtdAddr->SIZE_IOC_STS & VUSB_EP_TR_PACKET_SIZE) >> 16);
}

/*!
 * @brief Get the xd for this dtd
 *
 * This function Get the xd for this dtd
 *
 * @param the dtdAddr
 * @return the xd for this dtd
 */
static inline uint32_t usb_hal_ehci_get_xd_for_this_dtd( usb_ehci_dev_dtd_struct_t * dtdAddr)
{
    return (uint32_t)dtdAddr->xd_for_this_dtd;
}

/*!
 * @brief Clear the ioc int status
 *
 * This function Clear the ioc int status
 *
 * @param the epQueueHeadAddr
 */
static inline void usb_hal_ehci_clear_size_ioc_int_sts( usb_ehc_dev_qh_struct_t * epQueueHeadAddr)
{
    epQueueHeadAddr->SIZE_IOC_INT_STS = 0;
}


/*!
 * @brief Get the fstn normal path link ptr
 *
 * This function Get the fstn normal path link ptr
 *
 * @param the FSTN_ptr
 * @return the normal path link ptr
 */
static inline uint32_t usb_hal_ehci_get_fstn_normal_path_link_ptr(ehci_fstn_struct_t* FSTN_ptr)
{
   return FSTN_ptr->normal_path_link_ptr;
}

/*!
 * @brief Set the fstn normal path link ptr
 *
 * This function Set the fstn normal path link ptr
 *
 * @param the FSTN_ptr
 * @param the normal path link ptr value
 */
static inline void  usb_hal_ehci_set_fstn_normal_path_link_ptr(ehci_fstn_struct_t* FSTN_ptr, uint32_t next)
{
   FSTN_ptr->normal_path_link_ptr = next;
}

/*!
 * @brief Add the frame list pointer itd
 *
 * This function Add the frame list pointer itd
 *
 * @param the transaction_descriptor
 * @param the itd_ptr
 */
static inline void usb_hal_ehci_add_frame_list_pointer_itd( uint32_t *transaction_descriptor, ehci_itd_struct_t* itd_ptr)
{
   *transaction_descriptor = (uint32_t) itd_ptr | (EHCI_FRAME_LIST_ELEMENT_TYPE_ITD << EHCI_FRAME_LIST_ELEMENT_TYPE_BIT_POS);
}

/*!
 * @brief Add the frame list pointer sitd
 *
 * This function Add the frame list pointer sitd
 *
 * @param the transaction_descriptor
 * @param the sitd_ptr
 */
static inline void usb_hal_ehci_add_frame_list_pointer_sitd( uint32_t *transaction_descriptor, ehci_sitd_struct_t* sitd_ptr)
{
   *transaction_descriptor = (uint32_t) sitd_ptr | (EHCI_FRAME_LIST_ELEMENT_TYPE_SITD << EHCI_FRAME_LIST_ELEMENT_TYPE_BIT_POS);
}

/*!
 * @brief Get the periodic list address
 *
 * This function Get the periodic list address
 *
 * @param the transaction_descriptor
 * @return  the transaction_descriptor pointer
 */
static inline uint32_t usb_hal_ehci_get_periodic_list_addr( volatile uint32_t*  transfer_data_struct_ptr)
{
   return (*transfer_data_struct_ptr);
}

/*!
 * @brief Get the periodic list address
 *
 * This function Get the periodic list address
 *
 * @param the transaction_descriptor
 * @return  the transaction_descriptor pointer
 */
static inline void usb_hal_ehci_set_periodic_list_addr( volatile uint32_t*  transfer_data_struct_ptr, ehci_qh_struct_t* qh_ptr)
{
   *transfer_data_struct_ptr = ((uint32_t)qh_ptr | (EHCI_FRAME_LIST_ELEMENT_TYPE_QH << EHCI_QH_ELEMENT_TYPE_BIT_POS));
}

/*!
 * @brief Set the transfer data struct
 *
 * This function Set the transfer data struct
 *
 * @param the transaction_descriptor
 * @param  the temp_transfer_struct_ptr pointer
 */
static inline void usb_hal_ehci_set_transfer_data_struct( volatile uint32_t*  transfer_data_struct_ptr, uint32_t temp_transfer_struct_ptr)
{
  *transfer_data_struct_ptr = temp_transfer_struct_ptr;
}

//static inline void usb_hal_ehci_store_device_address( ehci_itd_struct_t* itd_ptr)
//{
//   itd_ptr->buffer_page_ptr_list[0] |= (uint32_t)(pipe_descr_ptr->G.DEVICE_ADDRESS);
//}

/*!
 * @brief Set the itd next link pointer
 *
 * This function Set the itd next link pointer
 *
 * @param the itd_ptr
 * @param  the transaction_descriptor pointer
 */
static inline void usb_hal_ehci_set_itd_next_link_pointer(ehci_itd_struct_t* itd_ptr, uint32_t transaction_descriptor )
{
    itd_ptr->next_link_ptr = (uint32_t)transaction_descriptor;
}

/*!
 * @brief Get the itd next link pointer
 *
 * This function Get the itd next link pointer
 *
 * @param the itd_ptr
 * @return  the next link pointer
 */
static inline uint32_t usb_hal_ehci_get_itd_next_link_pointer(ehci_itd_struct_t* itd_ptr)
{
   return itd_ptr->next_link_ptr;
}

/*!
 * @brief Set the itd next link pointer terminate bit
 *
 * This function Set the itd next link pointer terminate bit
 *
 * @param the itd_ptr
 */
static inline void usb_hal_ehci_set_ITD_terminate_bit(ehci_itd_struct_t* itd_ptr)
{
   itd_ptr->next_link_ptr = EHCI_ITD_T_BIT;
}

/*!
 * @brief Store the endpoint number and device address
 *
 * This function Store the endpoint number and device address
 *
 * @param the itd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_store_endpoint_number_and_device_addr( ehci_itd_struct_t* itd_ptr, uint32_t value)
{
    itd_ptr->buffer_page_ptr_list[0] = value;
}

/*!
 * @brief Store the max packet size and direction
 *
 * This function Store the max packet size and direction
 *
 * @param the itd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_store_max_packet_size_and_direction( ehci_itd_struct_t* itd_ptr, uint32_t value)
{
        itd_ptr->buffer_page_ptr_list[1] = value;
}

/*!
 * @brief Store the  direction
 *
 * This function Store the direction
 *
 * @param the itd_ptr
 * @param the direction
 */
static inline void usb_hal_ehci_store_direction( ehci_itd_struct_t* itd_ptr, uint32_t direction)
{
    itd_ptr->buffer_page_ptr_list[1] |= (uint32_t)(direction << EHCI_ITD_DIRECTION_BIT_POS);
}

/*!
 * @brief Store the transaction number per micro frame
 *
 * This function Store the transaction number per micro frame
 *
 * @param the itd_ptr
 * @param the number
 */
static inline void usb_hal_ehci_set_transaction_number_per_micro_frame( ehci_itd_struct_t* itd_ptr, uint32_t number)
{
   itd_ptr->buffer_page_ptr_list[2] = number;
}

/*!
 * @brief Set buffer page pointer
 *
 * This function Set buffer page pointer
 *
 * @param the itd_ptr
 * @param the page_number
 * @param the buffer ptr pointer
 */
static inline void usb_hal_ehci_set_buffer_page_pointer( ehci_itd_struct_t* itd_ptr, uint32_t page_number, uint32_t buffer_ptr)
{
   itd_ptr->buffer_page_ptr_list[page_number] = buffer_ptr;
}

/*!
 * @brief Get buffer page pointer
 *
 * This function Get buffer page pointer
 *
 * @param the itd_ptr
 * @param the page_number
 * @return the buffer ptr pointer
 */
static inline uint32_t usb_hal_ehci_get_buffer_page_pointer( ehci_itd_struct_t* itd_ptr, uint32_t page_number)
{
   return itd_ptr->buffer_page_ptr_list[page_number];
}

/*!
 * @brief Set the transcation and control bit
 *
 * This function Set the transcation and control bit
 *
 * @param the itd_ptr
 * @param the number
 * @param the value
 */
static inline void usb_hal_ehci_set_transcation_status_and_control_bit( ehci_itd_struct_t* itd_ptr, uint32_t number, uint32_t value)
{
  itd_ptr->tr_status_ctl_list[number] = value;
}

/*!
 * @brief Set the transcation status active bit
 *
 * This function Set the transcation status active bit
 *
 * @param the itd_ptr
 * @param the number
 */
static inline void usb_hal_ehci_set_transcation_status_active_bit( ehci_itd_struct_t* itd_ptr, uint32_t number)
{
   itd_ptr->tr_status_ctl_list[number] = itd_ptr->tr_status_ctl_list[number] | EHCI_ITD_ACTIVE_BIT;
}

/*!
 * @brief Get the transcation status control bit
 *
 * This function Get the transcation status control bit
 *
 * @param the itd_ptr
 * @param the transaction_number
 * @return the transcation status control bit
 */
static inline uint32_t usb_hal_ehci_get_transcation_status_ctl_list( ehci_itd_struct_t* itd_ptr, uint32_t transaction_number)
{
   return itd_ptr->tr_status_ctl_list[transaction_number];
}

/*!
 * @brief Set the itd lenght scheduled
 *
 * This function Set the itd lenght scheduled
 *
 * @param the itd_ptr
 * @param the length_scheduled
 */
static inline void usb_hal_ehci_set_itd_length_scheduled( ehci_itd_struct_t* itd_ptr, uint32_t length_scheduled)
{
  itd_ptr->reserved[MEM_SIZE_INDEX] = length_scheduled;
}

/*!
 * @brief Set the sitd next link pointer
 *
 * This function Set the sitd next link pointer
 *
 * @param the sitd_ptr
 * @param the transaction_descriptor
 */
static inline void usb_hal_ehci_set_sitd_next_link_pointer(ehci_sitd_struct_t* sitd_ptr, uint32_t transaction_descriptor )
{
    sitd_ptr->next_link_ptr =  (uint32_t)transaction_descriptor;
}

/*!
 * @brief Get the sitd next link pointer
 *
 * This function Get the sitd next link pointer
 *
 * @param the sitd_ptr
 * @return the transaction_descriptor
 */
static inline uint32_t usb_hal_ehci_get_sitd_next_link_pointer(ehci_sitd_struct_t* sitd_ptr)
{
   return sitd_ptr->next_link_ptr;
}

/*!
 * @brief Get the sitd transfer status
 *
 * This function Get the sitd transfer status
 *
 * @param the sitd_ptr
 * @return the sitd transfer status
 */
static inline uint32_t usb_hal_ehci_get_sitd_transfer_state(ehci_sitd_struct_t* sitd_ptr)
{
    return sitd_ptr->transfer_state;
}

/*!
 * @brief Set the sitd next link terminate bit
 *
 * This function Set the sitd next link terminate bit
 *
 * @param the sitd_ptr
 */
static inline void usb_hal_ehci_set_sitd_next_link_terminate_bit( ehci_sitd_struct_t* sitd_ptr)
{
    sitd_ptr->next_link_ptr = EHCI_SITD_T_BIT;
}

/*!
 * @brief Set the sitd back link terminate bit
 *
 * This function Set the back next link terminate bit
 *
 * @param the sitd_ptr
 */
static inline void usb_hal_ehci_set_sitd_back_pointer_terminate_bit( ehci_sitd_struct_t* sitd_ptr)
{
    sitd_ptr->back_link_ptr = EHCI_SITD_T_BIT;
}

/*!
 * @brief Set the sitd ep capab charac register
 *
 * This function Set the sitd ep capab charac register
 *
 * @param the sitd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_set_sitd_ep_capab_charac( ehci_sitd_struct_t* sitd_ptr, uint32_t value)
{
   sitd_ptr->ep_capab_charac = value;
}

/*!
 * @brief Set the sitd uframe sched ctl register
 *
 * This function Set the sitd uframe sched ctl register
 *
 * @param the sitd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_set_sitd_uframe_sched_ctl( ehci_sitd_struct_t* sitd_ptr, uint32_t value)
{
   sitd_ptr->uframe_sched_ctl= value;
}

/*!
 * @brief Set the sitd transfer state
 *
 * This function Set the sitd transfer state
 *
 * @param the sitd_ptr
 * @param the value
 */
static inline void usb_hal_ehci_set_sitd_transfer_state( ehci_sitd_struct_t* sitd_ptr, uint32_t value)
{
   sitd_ptr->transfer_state = value;
}

/*!
 * @brief Set the sitd length scheduled
 *
 * This function Set the sitd length scheduled
 *
 * @param the sitd_ptr
 * @param the length_scheduled
 */
static inline void usb_hal_ehci_set_sitd_length_scheduled( ehci_sitd_struct_t* sitd_ptr, uint32_t length_scheduled)
{
   sitd_ptr->reserved[MEM_SIZE_INDEX] = length_scheduled;
}

/*!
 * @brief Get the sitd length scheduled
 *
 * This function Get the sitd length scheduled
 *
 * @param the sitd_ptr
 * @return the length_scheduled
 */
static inline uint32_t usb_hal_ehci_get_sitd_length_scheduled( ehci_sitd_struct_t* sitd_ptr)
{
  return sitd_ptr->reserved[MEM_SIZE_INDEX];
}

/*!
 * @brief Get the sitd buffer ptr0
 *
 * This function Get the sitd buffer ptr0
 *
 * @param the sitd_ptr
 * @return the buffer ptr0
 */
static inline uint32_t usb_hal_ehci_get_sitd_buffer_ptr_0( ehci_sitd_struct_t* sitd_ptr)
{
  return sitd_ptr->buffer_ptr_0;
}

/*!
 * @brief Set the sitd buffer ptr0
 *
 * This function Set the sitd buffer ptr0
 *
 * @param the sitd_ptr
 * @param the buffer ptr0
 */
static inline void usb_hal_ehci_set_sitd_buffer_ptr_0( ehci_sitd_struct_t* sitd_ptr, uint32_t buffer_ptr)
{
   sitd_ptr->buffer_ptr_0 = buffer_ptr;
}

/*!
 * @brief Set the sitd buffer ptr1
 *
 * This function Set the sitd buffer ptr1
 *
 * @param the sitd_ptr
 * @param the buffer ptr1
 */
static inline void usb_hal_ehci_set_sitd_buffer_ptr_1( ehci_sitd_struct_t* sitd_ptr, uint32_t buffer_ptr)
{
   sitd_ptr->buffer_ptr_1 = buffer_ptr;
}

/*!
 * @brief Set the sitd alt qtd link pointer terminate bit
 *
 * This function Set the sitd alt qtd link pointer terminate bit
 *
 * @param the qh_ptr
 */
static inline void usb_hal_ehci_set_qh_next_alt_qtd_link_terminate( ehci_qh_struct_t* qh_ptr)
{
   qh_ptr->alt_next_qtd_link_ptr = EHCI_QTD_T_BIT;
}

/*!
 * @brief Set the qh next qtd link pointer
 *
 * This function Set the qh next qtd link pointer
 *
 * @param the qh_ptr
 * @param the first_qtd_ptr
 */
static inline void usb_hal_ehci_set_qh_next_qtd_link_ptr( ehci_qh_struct_t* qh_ptr, uint32_t first_qtd_ptr)
{

   qh_ptr->next_qtd_link_ptr = (uint32_t)first_qtd_ptr;
}

/*!
 * @brief Set the qh next qtd link terminate bit
 *
 * This function Set the qh next qtd link terminate bit
 *
 * @param the qh_ptr
 */
static inline void usb_hal_ehci_set_qh_next_qtd_link_terminate( ehci_qh_struct_t* qh_ptr)

{
   qh_ptr->next_qtd_link_ptr = EHCI_QTD_T_BIT;
}

/*!
 * @brief Get the qh next qtd link pointer
 *
 * This function Get the qh next qtd link pointer
 *
 * @param the qh_ptr
 * @return the qh_ptr next qtd link pointer
 */
static inline uint32_t usb_hal_ehci_get_next_qtd_link_ptr( ehci_qh_struct_t* qh_ptr)
{
  return (uint32_t)qh_ptr->next_qtd_link_ptr;
}

/*!
 * @brief Clear the qh status
 *
 * This function Clear the qh status
 *
 * @param the qh_ptr
 */
static inline void usb_hal_ehci_clear_qh_status( ehci_qh_struct_t* qh_ptr)
{
  qh_ptr->status = 0;
}

/*!
 * @brief Return the qh status
 *
 * This function Clear the qh status
 *
 * @param the qh_ptr
 * @return the qh_ptr status
 */
static inline uint32_t usb_hal_ehci_get_qh_status( ehci_qh_struct_t* qh_ptr)
{
   return qh_ptr->status;
}

/*!
 * @brief Set the qh status
 *
 * This function Set the qh status
 *
 * @param the qh_ptr
 * @param the qh_ptr status
 */
static inline void usb_hal_ehci_set_qh_status( ehci_qh_struct_t* qh_ptr, uint32_t status)
{
   qh_ptr->status = status;
}

/*!
 * @brief Get the qh horiz link ptr
 *
 * This function Get the qh horiz link ptr
 *
 * @param the qh_ptr
 * @return the qh horiz link ptr
 */
static inline uint32_t usb_hal_ehci_get_qh_horiz_link_ptr( ehci_qh_struct_t* qh_ptr)
{
  return qh_ptr->horiz_link_ptr;
}

/*!
 * @brief Set the qh horiz link ptr
 *
 * This function Set  the qh horiz link ptr
 *
 * @param the qh_ptr
 * @param the link_ptr
 */
static inline void usb_hal_ehci_set_qh_horiz_link_ptr( ehci_qh_struct_t* qh_ptr, uint32_t link_ptr)
{

   qh_ptr->horiz_link_ptr = link_ptr;
}

/*!
 * @brief Init the qh
 *
 * This function Init the qh
 *
 * @param the qh_ptr
 */
static inline void usb_hal_ehci_init_qh(  ehci_qh_struct_t* qh_ptr)
{
    qh_ptr->curr_qtd_link_ptr = EHCI_QTD_T_BIT;
    qh_ptr->alt_next_qtd_link_ptr = EHCI_QTD_T_BIT;
    qh_ptr->status = 0;
    qh_ptr->buffer_ptr_0 = 0;
    qh_ptr->buffer_ptr_1 = 0;
    qh_ptr->buffer_ptr_2 = 0;
    qh_ptr->buffer_ptr_3 = 0;
    qh_ptr->buffer_ptr_4 = 0;
}

/*!
 * @brief Set the ep capab charac1
 *
 * This function Set the ep capab charac1
 *
 * @param the qh_ptr
 * @param the temp_ep_capab
 */
static inline void usb_hal_ehci_set_ep_capab_charac1(  ehci_qh_struct_t* qh_ptr, uint32_t temp_ep_capab)
{
   qh_ptr->ep_capab_charac1 = temp_ep_capab;
}

/*!
 * @brief Get the ep capab charac1
 *
 * This function Get the ep capab charac1
 *
 * @param the qh_ptr
 * @return the ep_capab1
 */
static inline uint32_t usb_hal_ehci_get_ep_capab_charac1(  ehci_qh_struct_t* qh_ptr)
{
   return qh_ptr->ep_capab_charac1;
}

/*!
 * @brief Set the ep capab charac2
 *
 * This function Set the ep capab charac2
 *
 * @param the qh_ptr
 * @param the temp_ep_capab
 */
static inline void usb_hal_ehci_set_ep_capab_charac2(  ehci_qh_struct_t* qh_ptr, uint32_t temp_ep_capab)
{
   qh_ptr->ep_capab_charac2 = temp_ep_capab;
}

/*!
 * @brief Get the ep capab charac2
 *
 * This function Get the ep capab charac2
 *
 * @param the qh_ptr
 * @return the ep_capab2
 */
static inline uint32_t usb_hal_ehci_get_ep_capab_charac2(  ehci_qh_struct_t* qh_ptr)
{
   return qh_ptr->ep_capab_charac2;
}

/*!
 * @brief Set the horiz link ptr terminate 
 *
 * This function Set the horiz link ptr terminate 
 *
 * @param the qh_ptr 
 */
static inline void usb_hal_ehci_set_qh_horiz_link_ptr_head_pointer_terminate(  ehci_qh_struct_t* qh_ptr)
{
   qh_ptr->horiz_link_ptr = EHCI_QUEUE_HEAD_POINTER_T_BIT;
}

/*!
 * @brief Set the buffer page pointer
 *
 * This function Set the buffer page pointer
 *
 * @param the qh_ptr 
 * @param the buffer_start_address 
 */
static inline void usb_hal_ehci_set_qtd_buffer_page_pointer( ehci_qtd_struct_t* qtd_ptr, uint32_t buffer_start_address)
{
   qtd_ptr->buffer_ptr_0 = buffer_start_address;
   qtd_ptr->buffer_ptr_1 = qtd_ptr->buffer_ptr_0 + 4096;
   qtd_ptr->buffer_ptr_2 = qtd_ptr->buffer_ptr_1 + 4096;
   qtd_ptr->buffer_ptr_3 = qtd_ptr->buffer_ptr_2 + 4096;
   qtd_ptr->buffer_ptr_4 = qtd_ptr->buffer_ptr_3 + 4096;
}

/*!
 * @brief Set the qtd token
 *
 * This function Set the qtd token
 *
 * @param the qh_ptr 
 * @param the token 
 */
static inline void usb_hal_ehci_set_qtd_token( ehci_qtd_struct_t* qtd_ptr, uint32_t token)
{

   qtd_ptr->token = token;
}

/*!
 * @brief Clear the qtd token bits
 *
 * This function Clear the qtd token bits
 *
 * @param the qh_ptr 
 * @param the token_bits 
 */
static inline void usb_hal_ehci_clear_qtd_token_bits( ehci_qtd_struct_t* qtd_ptr, uint32_t token_bits)
{
   qtd_ptr->token &= ~token_bits;
}

/*!
 * @brief Get the qtd token
 *
 * This function Get the qtd token
 *
 * @param the qtd_ptr
 */
static inline uint32_t usb_hal_ehci_get_qtd_token( ehci_qtd_struct_t* qtd_ptr)
{

   return qtd_ptr->token;
}

/*!
 * @brief Set the qtd next ptr terminate
 *
 * This function Set the qtd next ptr terminate
 *
 * @param the qtd_ptr
 */
static inline void usb_hal_ehci_set_qtd_terminate_bit( ehci_qtd_struct_t* qtd_ptr)
{
    qtd_ptr->next_qtd_ptr = EHCI_QTD_T_BIT;
}

/*!
 * @brief Get the qtd next ptr 
 *
 * This function Get the qtd next ptr 
 *
 * @param the qtd_ptr
 * @return the qtd next ptr
 */
static inline uint32_t usb_hal_ehci_get_next_qtd_ptr(ehci_qtd_struct_t* qtd_ptr)
{
    return qtd_ptr->next_qtd_ptr;
}

/*!
 * @brief Set the alt next qtd terminate bit
 *
 * This function Set the alt next qtd terminate bit
 *
 * @param the qtd_ptr
 */
static inline void usb_hal_ehci_set_alt_next_qtd_terminate_bit( ehci_qtd_struct_t* qtd_ptr)
{
  qtd_ptr->alt_next_qtd_ptr = EHCI_QTD_T_BIT;
}

/*!
 * @brief Set the next qtd ptr
 *
 * This function Set the next qtd ptr
 *
 * @param the prev_qtd_ptr
 * @param the qtd_ptr
 */
static inline void usb_hal_ehci_link_qtd( ehci_qtd_struct_t* prev_qtd_ptr,uint32_t qtd_ptr)
{
   prev_qtd_ptr->next_qtd_ptr = qtd_ptr;
}


#endif
#endif
