/*
** ###################################################################
**     Version:             rev. 1.0, 2015-01-16
**     Build:               b150116
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2015-01-16)
**         Initial version.
**
** ###################################################################
*/

#if !defined(__FSL_USB_FEATURES_H__)
#define __FSL_USB_FEATURES_H__

#if defined(CPU_MK20DN512VLK10) || defined(CPU_MK20DX256VLK10) || defined(CPU_MK20DN512VLL10) || defined(CPU_MK20DX256VLL10) || \
    defined(CPU_MK20DX128VLQ10) || defined(CPU_MK20DX256VLQ10) || defined(CPU_MK20DN512VLQ10) || defined(CPU_MK20DX256VMC10) || \
    defined(CPU_MK20DN512VMC10) || defined(CPU_MK20DX128VMD10) || defined(CPU_MK20DX256VMD10) || defined(CPU_MK20DN512VMD10) || \
    defined(CPU_MK21DX128AVLK5) || defined(CPU_MK21DX256AVLK5) || defined(CPU_MK21DN512AVLK5) || defined(CPU_MK21DX128AVMC5) || \
    defined(CPU_MK21DX256AVMC5) || defined(CPU_MK21DN512AVMC5) || defined(CPU_MK21FX512AVLQ12) || defined(CPU_MK21FN1M0AVLQ12) || \
    defined(CPU_MK21FX512AVMC12) || defined(CPU_MK21FN1M0AVMC12) || defined(CPU_MK21FX512AVMD12) || defined(CPU_MK21FN1M0AVMD12) || \
    defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || defined(CPU_MK22FN128VLL10) || defined(CPU_MK22FN128VMP10) || \
    defined(CPU_MK22FN256CAH12) || defined(CPU_MK22FN128CAH12) || defined(CPU_MK22FN256VDC12) || defined(CPU_MK22FN256VLH12) || \
    defined(CPU_MK22FN256VLL12) || defined(CPU_MK22FN256VMP12) || defined(CPU_MK22FN512CAP12) || defined(CPU_MK22FN512VDC12) || \
    defined(CPU_MK22FN512VLH12) || defined(CPU_MK22FN512VLL12) || defined(CPU_MK22FN512VMP12) || defined(CPU_MK24FN1M0VDC12) || \
    defined(CPU_MK24FN1M0VLL12) || defined(CPU_MK24FN1M0VLQ12) || defined(CPU_MK24FN256VDC12) || defined(CPU_MK26FN2M0CAC18) || \
    defined(CPU_MK40DN512VLK10) || defined(CPU_MK40DN512VLL10) || defined(CPU_MK40DX128VLQ10) || defined(CPU_MK40DX256VLQ10) || \
    defined(CPU_MK40DN512VLQ10) || defined(CPU_MK40DN512VMC10) || defined(CPU_MK40DX128VMD10) || defined(CPU_MK40DX256VMD10) || \
    defined(CPU_MK40DN512VMD10) || defined(CPU_MK50DX256CLL10) || defined(CPU_MK50DN512CLL10) || defined(CPU_MK50DN512CLQ10) || \
    defined(CPU_MK50DX256CMC10) || defined(CPU_MK50DN512CMC10) || defined(CPU_MK50DN512CMD10) || defined(CPU_MK50DX256CMD10) || \
    defined(CPU_MK50DX256CLK10) || defined(CPU_MK51DX256CLL10) || defined(CPU_MK51DN512CLL10) || defined(CPU_MK51DN256CLQ10) || \
    defined(CPU_MK51DN512CLQ10) || defined(CPU_MK51DX256CMC10) || defined(CPU_MK51DN512CMC10) || defined(CPU_MK51DN256CMD10) || \
    defined(CPU_MK51DN512CMD10) || defined(CPU_MK51DX256CLK10) || defined(CPU_MK52DN512CLQ10) || defined(CPU_MK52DN512CMD10) || \
    defined(CPU_MK53DN512CLQ10) || defined(CPU_MK53DX256CLQ10) || defined(CPU_MK53DN512CMD10) || defined(CPU_MK53DX256CMD10) || \
    defined(CPU_MK60DN256VLL10) || defined(CPU_MK60DX256VLL10) || defined(CPU_MK60DN512VLL10) || defined(CPU_MK60DN256VLQ10) || \
    defined(CPU_MK60DX256VLQ10) || defined(CPU_MK60DN512VLQ10) || defined(CPU_MK60DN256VMC10) || defined(CPU_MK60DX256VMC10) || \
    defined(CPU_MK60DN512VMC10) || defined(CPU_MK60DN256VMD10) || defined(CPU_MK60DX256VMD10) || defined(CPU_MK60DN512VMD10) || \
    defined(CPU_MK63FN1M0VLQ12) || defined(CPU_MK63FN1M0VMD12) || defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || \
    defined(CPU_MK64FX512VLL12) || defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || \
    defined(CPU_MK64FX512VMD12) || defined(CPU_MK64FN1M0VMD12) || defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || \
    defined(CPU_MK65FN2M0VMI18) || defined(CPU_MK65FX1M0VMI18) || defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || \
    defined(CPU_MK66FN2M0VMD18) || defined(CPU_MK66FX1M0VMD18) || defined(CPU_MKL24Z32VFM4) || defined(CPU_MKL24Z64VFM4) || \
    defined(CPU_MKL24Z32VFT4) || defined(CPU_MKL24Z64VFT4) || defined(CPU_MKL24Z32VLH4) || defined(CPU_MKL24Z64VLH4) || \
    defined(CPU_MKL24Z32VLK4) || defined(CPU_MKL24Z64VLK4) || defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || \
    defined(CPU_MKL25Z128VFM4) || defined(CPU_MKL25Z32VFT4) || defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || \
    defined(CPU_MKL25Z32VLH4) || defined(CPU_MKL25Z64VLH4) || defined(CPU_MKL25Z128VLH4) || defined(CPU_MKL25Z32VLK4) || \
    defined(CPU_MKL25Z64VLK4) || defined(CPU_MKL25Z128VLK4) || defined(CPU_MKL26Z128CAL4) || defined(CPU_MKL26Z32VFM4) || \
    defined(CPU_MKL26Z64VFM4) || defined(CPU_MKL26Z128VFM4) || defined(CPU_MKL26Z32VFT4) || defined(CPU_MKL26Z64VFT4) || \
    defined(CPU_MKL26Z128VFT4) || defined(CPU_MKL26Z32VLH4) || defined(CPU_MKL26Z64VLH4) || defined(CPU_MKL26Z128VLH4) || \
    defined(CPU_MKL26Z256VLH4) || defined(CPU_MKL26Z128VLL4) || defined(CPU_MKL26Z256VLL4) || defined(CPU_MKL26Z128VMC4) || \
    defined(CPU_MKL26Z256VMC4) || defined(CPU_MKL26Z256VMP4) || defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || \
    defined(CPU_MKL46Z128VLL4) || defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4) || \
    defined(CPU_MKL46Z256VMP4) || defined(CPU_MKW22D512VHA5) || defined(CPU_MKW24D512VHA5)
    /* @brief HOST mode enabled */
    #define FSL_FEATURE_USB_KHCI_HOST_ENABLED (1)
    /* @brief OTG mode enabled */
    #define FSL_FEATURE_USB_KHCI_OTG_ENABLED (1)
    /* @brief Size of the USB dedicated RAM */
    #define FSL_FEATURE_USB_KHCI_USB_RAM (0)
    /* @brief Has KEEP_ALIVE_CTRL register */
    #define FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED (0)
#elif defined(CPU_MKL27Z128VFM4) || defined(CPU_MKL27Z256VFM4) || defined(CPU_MKL27Z128VFT4) || defined(CPU_MKL27Z256VFT4) || \
    defined(CPU_MKL27Z128VLH4) || defined(CPU_MKL27Z256VLH4) || defined(CPU_MKL27Z128VMP4) || defined(CPU_MKL27Z256VMP4) || \
    defined(CPU_MKL43Z128VLH4) || defined(CPU_MKL43Z256VLH4) || defined(CPU_MKL43Z128VMP4) || defined(CPU_MKL43Z256VMP4)
    /* @brief HOST mode enabled */
    #define FSL_FEATURE_USB_KHCI_HOST_ENABLED (0)
    /* @brief OTG mode enabled */
    #define FSL_FEATURE_USB_KHCI_OTG_ENABLED (0)
    /* @brief Size of the USB dedicated RAM */
    #define FSL_FEATURE_USB_KHCI_USB_RAM (0)
    /* @brief Has KEEP_ALIVE_CTRL register */
    #define FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED (0)
#elif defined(CPU_MKL27Z32VDA4) || defined(CPU_MKL27Z64VDA4) || defined(CPU_MKL27Z32VFM4) || defined(CPU_MKL27Z64VFM4) || \
    defined(CPU_MKL27Z32VFT4) || defined(CPU_MKL27Z64VFT4) || defined(CPU_MKL27Z32VLH4) || defined(CPU_MKL27Z64VLH4) || \
    defined(CPU_MKL27Z32VMP4) || defined(CPU_MKL27Z64VMP4)
    /* @brief HOST mode enabled */
    #define FSL_FEATURE_USB_KHCI_HOST_ENABLED (0)
    /* @brief OTG mode enabled */
    #define FSL_FEATURE_USB_KHCI_OTG_ENABLED (0)
    /* @brief Size of the USB dedicated RAM */
    #define FSL_FEATURE_USB_KHCI_USB_RAM (512)
    /* @brief Has KEEP_ALIVE_CTRL register */
    #define FSL_FEATURE_USB_KHCI_KEEP_ALIVE_ENABLED (1)
#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_USB_FEATURES_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
