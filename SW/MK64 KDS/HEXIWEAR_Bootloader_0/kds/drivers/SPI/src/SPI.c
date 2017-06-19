/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file SPI.c
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


/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#include "EmbeddedTypes.h"
#include "SPI.h"


/*! *********************************************************************************
*************************************************************************************
* Public Functions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
* \brief   This function initialized the SPI module
*
* \param[in]  interfaceId        SPI module number
*
********************************************************************************** */
void spi_master_init(uint32_t instance)
{
    (void)instance;
    /* Enable SPI PORT clock */
    BOOT_SPI_PORT_SIM_SCG |= cSPI_PORT_SIM_SCG_Config_c;
    /* Enable SPI clock */
    BOOT_SPI_SIM_SCG |= cSPI_SIM_SCG_Config_c;
    /* Initialize SPI Pin Control registers */
    BOOT_SPI_SCLK_PCR &= ~PORT_PCR_MUX_MASK;
    BOOT_SPI_SCLK_PCR |= PORT_PCR_MUX(7);
    BOOT_SPI_MOSI_PCR &= ~PORT_PCR_MUX_MASK;
    BOOT_SPI_MOSI_PCR |= PORT_PCR_MUX(7);
    BOOT_SPI_MISO_PCR &= ~PORT_PCR_MUX_MASK;
    BOOT_SPI_MISO_PCR |= PORT_PCR_MUX(7);
    //  BOOT_SPI_SSEL_PCR &= ~PORT_PCR_MUX_MASK;
    //  BOOT_SPI_SSEL_PCR |= PORT_PCR_MUX(2);
    /* CS is used as a GPIO */
    BOOT_SPI_SSEL_PCR &= ~PORT_PCR_MUX_MASK;
    BOOT_SPI_SSEL_PCR |= PORT_PCR_MUX(1);
    BOOT_SPI_SSEL_PDDR |= 1 << BOOT_SPI_SSEL_PIN_Number_c;
    deassert_cs();

    /* Initialize SPI module */
#if gSPI_HW_TYPE_c == gDSPI_HW_c
    SPI_MCR_REG(BOOT_SPI_BaseAddr) = SPI_MCR_MSTR_MASK    |
                                     SPI_MCR_ROOE_MASK    |
                                     SPI_MCR_CLR_RXF_MASK |
                                     SPI_MCR_CLR_TXF_MASK |
                                     SPI_MCR_PCSIS(1)     |
                                     SPI_MCR_SMPL_PT(2)   |
                                     SPI_MCR_HALT_MASK;
#else
    SPI_C1_REG(BOOT_SPI_BaseAddr) = SPI_C1_MSTR_MASK;
    SPI_C2_REG(BOOT_SPI_BaseAddr) = 0x00;
    SPI_C1_REG(BOOT_SPI_BaseAddr) |= SPI_C1_SPE_MASK;
#endif
}

/*! *********************************************************************************
* \brief   This function configures the SPI interface
*
* \param[in]  interfaceId        SPI module number
* \param[in]  device             device config strucure
*
********************************************************************************** */
void spi_master_configure_bus(uint32_t instance, const spi_user_config_t * device)
{
#if gSPI_HW_TYPE_c == gDSPI_HW_c
    SPI_CTAR_REG(BOOT_SPI_BaseAddr,0) = SPI_CTAR_PBR(0)    | SPI_CTAR_BR(0x01)    |
                                        SPI_CTAR_PCSSCK(1) | SPI_CTAR_CSSCK(0x04) |
                                        SPI_CTAR_PASC(3)   | SPI_CTAR_ASC(0x04)   |
                                        SPI_CTAR_PDT(3)    | SPI_CTAR_DT(0x05)    |
                                        SPI_CTAR_FMSZ(7);
#else
    SPI_BR_REG(BOOT_SPI_BaseAddr) = SPI_BR_SPPR(1) | SPI_BR_SPR(0);
#endif
}


/*! *********************************************************************************
* \brief   This function transferes bytes over the SPI interface
*
* \param[in]  interfaceId        SPI module number
* \param[in]  device             device config strucure
* \param[in]  sendBuffer         location of data to be Tx. NULL if no Tx needed
* \param[out] receiveBuffer      location where Rx data is stored. NULL if no Rx needed
* \param[in]  transferByteCount  number of bytes to be transfered
*
* \return spi_status_t
*
********************************************************************************** */
spi_status_t spi_master_transfer(uint32_t instance,
                                 const uint8_t * sendBuffer,
                                 uint8_t * receiveBuffer,
                                 uint32_t transferByteCount)
{
    volatile uint8_t dummy = 0;

    if( !transferByteCount )
        return 0;

    if( !sendBuffer && !receiveBuffer )
        return 1;

#if gSPI_HW_TYPE_c == gDSPI_HW_c
    /* Flush SPI FIFOs */
    SPI_MCR_REG(BOOT_SPI_BaseAddr) |= SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK;
    /* Clear the EOQF, TCF and RFDF flags by writting a 1 to them */
    SPI_SR_REG(BOOT_SPI_BaseAddr)  |= SPI_SR_EOQF_MASK | SPI_SR_TCF_MASK | SPI_SR_RFDF_MASK;
#else
    dummy = SPI_S_REG(BOOT_SPI_BaseAddr);
#endif

    while( transferByteCount-- )
    {
        if( sendBuffer )
        {
            dummy = *sendBuffer;
            sendBuffer++;
        }
        else
        {
            dummy = 0xFF;
        }

#if gSPI_HW_TYPE_c == gDSPI_HW_c
        /* Write data */
        SPI_PUSHR_REG(BOOT_SPI_BaseAddr) = dummy;
        /* Start SPI Transfer */
        SPI_MCR_REG(BOOT_SPI_BaseAddr) &= ~SPI_MCR_HALT_MASK;
        /* Wait Transfer complete */
        while( !(SPI_SR_REG(BOOT_SPI_BaseAddr) & SPI_SR_TCF_MASK) );
        /* Clear Transfer complete flag */
        SPI_SR_REG(BOOT_SPI_BaseAddr) |= SPI_SR_TCF_MASK;
        /* Stop SPI transfer */
        SPI_MCR_REG(BOOT_SPI_BaseAddr) |= SPI_MCR_HALT_MASK;
        /* Get received datad */
        dummy = SPI_POPR_REG(BOOT_SPI_BaseAddr);
#else
        /* Write data */
        SPI_DL_REG(BOOT_SPI_BaseAddr) = dummy;
        /* Wait for transfer complete */
        //        while(!(SPI1_S & SPI_S_SPTEF_MASK));
        while(!(SPI_S_REG(BOOT_SPI_BaseAddr) & SPI_S_SPRF_MASK));
        /* Get received datad */
        dummy = SPI_DL_REG(BOOT_SPI_BaseAddr);
#endif

        if( receiveBuffer )
        {
            *receiveBuffer = dummy;
            receiveBuffer++;
        }
    }

    (void)dummy;
    return 0;
}
