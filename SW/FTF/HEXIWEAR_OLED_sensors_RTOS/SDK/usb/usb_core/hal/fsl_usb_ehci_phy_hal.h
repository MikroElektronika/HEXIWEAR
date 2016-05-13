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

#ifndef __FSL_USB_EHCI_PHY_HAL_H__
#define __FSL_USB_EHCI_PHY_HAL_H__

#include "adapter.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_SDK)
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_usb_features.h"
#include "fsl_device_registers.h"
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM)
    #if (defined(CPU_MK65F18))
      #include "MK65F18.h"
    #endif
#endif

//#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#if (defined(CPU_MK65F18))
#include "MK65F18.h"
#endif
//#include "fsl_usb_features.h"
//#include "device/fsl_device_registers.h"

/*!
 * @addtogroup usb_ehci_phy_hal
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif
#define HW_USB_INSTANCE_COUNT (1U)

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Set the ehci phy trim override enable
 *
 * This function Set the ehci phy trim override enable
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_trim_override_enable(uint32_t instance)
{
    USBPHY_TRIM_OVERRIDE_EN = 0x001f;
}

/*!
 * @brief Enable the ehci phy pll power up
 *
 * This function Enable the ehci phy pll power up
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_pll_enalbe_power_up(uint32_t instance)
{
    USBPHY_PLL_SIC |= USBPHY_PLL_SIC_PLL_POWER_MASK;    //power up PLL
}

/*!
 * @brief Enable the ehci phy pll bypass
 *
 * This function Enable the ehci phy pll bypass
 *
 * @param the instance number
 */
static inline void usb_hal_ehci_phy_pll_enable_bypass(uint32_t instance)
{
    USBPHY_PLL_SIC |= USBPHY_PLL_SIC_PLL_BYPASS_MASK;   
}


/*!
 * @brief Disable the ehci phy pll bypass
 *
 * This function Disable the ehci phy pll bypass
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_pll_clear_bypass(uint32_t instance)
{
    USBPHY_PLL_SIC &= ~USBPHY_PLL_SIC_PLL_BYPASS_MASK;    //clear bypass bit
}

/*!
 * @brief Enable the ehci phy usb clock
 *
 * This function Enable the ehci phy usb clock
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_enable_usb_clock(uint32_t instance)
{
    USBPHY_PLL_SIC |= USBPHY_PLL_SIC_PLL_EN_USB_CLKS_MASK;    //enable USB clock output from USB PHY PLL
}

/*!
 * @brief Select the ehci phy pll reference clock
 *
 * This function Select the ehci phy pll reference clock
 *
 * @param the instance number
 * @param the frequency
 */
static void usb_hal_ehci_phy_select_pll_reference_clock(uint32_t instance,uint32_t frequency)
{
    if(frequency == 24000000) 
    {
        USBPHY_PLL_SIC |= USBPHY_PLL_SIC_PLL_DIV_SEL(0);
    }
    else if(frequency == 16000000) 
    {
        USBPHY_PLL_SIC |= USBPHY_PLL_SIC_PLL_DIV_SEL(1);
    }
    else if(frequency == 12000000) 
    {
        USBPHY_PLL_SIC |= USBPHY_PLL_SIC_PLL_DIV_SEL(2);
    }
}

/*!
 * @brief Wait the ehci phy pll to lock
 *
 * This function Wait the ehci phy pll to lock
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_wait_pll_lock(uint32_t instance)
{
    while (!(USBPHY_PLL_SIC & USBPHY_PLL_SIC_PLL_LOCK_MASK))
    {}
}

/*!
 * @brief Release the ehci phy from reset
 *
 * This function Release the ehci phy from reset
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_release_from_reset(uint32_t instance)
{
    USBPHY_CTRL &= ~USBPHY_CTRL_SFTRST_MASK; 
}

/*!
 * @brief Run the utmi clock
 *
 * This function Run the utmi clock
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_run_clock(uint32_t instance)
{
    USBPHY_CTRL &= ~USBPHY_CTRL_CLKGATE_MASK;
}

/*!
 * @brief Enable the utmi level2 clock
 *
 * This function Enable the utmi level2 clock
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_enable_utmi_level2(uint32_t instance)
{
    USBPHY_CTRL |= USBPHY_CTRL_SET_ENUTMILEVEL2_MASK;
}

/*!
 * @brief Enable the utmi level3 clock
 *
 * This function Enable the utmi level3 clock
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_enable_utmi_level3(uint32_t instance)
{
    USBPHY_CTRL |= USBPHY_CTRL_SET_ENUTMILEVEL3_MASK;
}

/*!
 * @brief Enable the ehci phy disconnect detect
 *
 * This function Enable the ehci phy disconnect detect
 *
 * @param the instance number
 */
static inline void usb_hal_ehci_phy_enable_disconnect_detect(uint32_t instance)
{
    USBPHY_CTRL |= USBPHY_CTRL_SET_ENHOSTDISCONDETECT_MASK;
}

/*!
 * @brief Disable the ehci phy disconnect detect
 *
 * This function Disable the ehci phy disconnect detect
 *
 * @param the instance number
 */

static inline void usb_hal_ehci_phy_disable_disconnect_detect(uint32_t instance)
{
    USBPHY_CTRL &= ~ USBPHY_CTRL_SET_ENHOSTDISCONDETECT_MASK;

}

/*!
 * @brief Set the ehci phy power state to normal
 *
 * This function Set the ehci phy power state to normal
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_set_power_state_to_normal(uint32_t instance)
{
    USBPHY_PWD = 0;
}

/*!
 * @brief Set the ehci phy pfd frac value
 *
 * This function Set the ehci phy pfd frac value
 *
 * @param the instance number
 * @param the frac_value
 */
static void usb_hal_ehci_phy_set_pfd_frac_value(uint32_t instance,uint32_t frac_value)
{
    USBPHY_ANACTRL |= USBPHY_ANACTRL_PFD_FRAC(frac_value);
}

/*!
 * @brief Select the pfd clock divider
 *
 * This function Select the pfd clock divider
 *
 * @param the instance number
 * @param the divider
 */
static void usb_hal_ehci_phy_select_pfd_clock_divider(uint32_t instance,uint32_t divider)
{
    USBPHY_ANACTRL |=USBPHY_ANACTRL_PFD_CLK_SEL(divider);    
}

/*!
 * @brief Disable the ehci phy pull down resistor
 *
 * This function Disable the ehci phy pull down resistor
 *
 * @param the instance number
 * @param the divider
 */
static void usb_hal_ehci_phy_disable_pulldown_resistor(uint32_t instance)
{
    USBPHY_ANACTRL &= ~USBPHY_ANACTRL_DEV_PULLDOWN_MASK;
}

/*!
 * @brief Disable the ehci phy pfd clock gate
 *
 * This function Disable the ehci phy pfd clock gate
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_disable_pfd_clock_gate(uint32_t instance)
{
    USBPHY_ANACTRL &= ~USBPHY_ANACTRL_PFD_CLKGATE_MASK;
}

/*!
 * @brief Wait the ehci phy clock to be stable
 *
 * This function Wait the ehci phy clock to be stable
 *
 * @param the instance number
 */
static void usb_hal_ehci_phy_wait_pfd_stable(uint32_t instance)
{
    while (!(USBPHY_ANACTRL & USBPHY_ANACTRL_PFD_STABLE_MASK))
    {}
}
#endif

/* EOF */
