/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file SPI.h
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

#ifndef __SPI_H__
#define __SPI_H__


/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "EmbeddedTypes.h"

#if defined(MCU_MK21DN512) || defined(MCU_MK21DX256)
  #include "MK21D5.h"
#elif defined(MCU_MKL46Z256)
  #include "MKL46Z4.h"
#elif defined(MCU_MKW40Z160)
  #include "MKW40Z4.h"
#elif defined(MCU_MK64FN1M)
  #include "MK64F12.h"
#endif

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
#define gDSPI_HW_c 0
#define gSPI_HW_c  1


#if defined(MCU_MK21DN512) || defined(MCU_MK21DX256)
#define gSPI_HW_TYPE_c             gDSPI_HW_c
#define BOOT_SPI_BaseAddr          SPI0_BASE_PTR
#define BOOT_SPI_PORT_SIM_SCG      SIM_SCGC5
#define cSPI_PORT_SIM_SCG_Config_c SIM_SCGC5_PORTC_MASK
#define BOOT_SPI_SIM_SCG           SIM_SCGC6
#define cSPI_SIM_SCG_Config_c      SIM_SCGC6_SPI0_MASK

#define BOOT_SPI_SCLK_PCR          PORTC_PCR5
#define BOOT_SPI_MOSI_PCR          PORTC_PCR6
#define BOOT_SPI_MISO_PCR          PORTC_PCR7
#define BOOT_SPI_SSEL_PCR          PORTC_PCR4

#define BOOT_SPI_SSEL_PCOR         GPIOC_PCOR
#define BOOT_SPI_SSEL_PSOR         GPIOC_PSOR
#define BOOT_SPI_SSEL_PDDR         GPIOC_PDDR
#define BOOT_SPI_SSEL_PIN_Number_c 4

/******************************************************************************/
#elif defined(MCU_MKL46Z256)
#define gSPI_HW_TYPE_c             gSPI_HW_c
#define BOOT_SPI_BaseAddr          SPI1_BASE_PTR
#define BOOT_SPI_PORT_SIM_SCG      SIM_SCGC5
#define cSPI_PORT_SIM_SCG_Config_c SIM_SCGC5_PORTC_MASK
#define BOOT_SPI_SIM_SCG           SIM_SCGC4
#define cSPI_SIM_SCG_Config_c      SIM_SCGC4_SPI1_MASK

#define BOOT_SPI_SCLK_PCR          PORTD_PCR5
#define BOOT_SPI_MOSI_PCR          PORTD_PCR6
#define BOOT_SPI_MISO_PCR          PORTD_PCR7
#define BOOT_SPI_SSEL_PCR          PORTD_PCR4

#define BOOT_SPI_SSEL_PCOR         GPIOD_PCOR
#define BOOT_SPI_SSEL_PSOR         GPIOD_PSOR
#define BOOT_SPI_SSEL_PDDR         GPIOD_PDDR
#define BOOT_SPI_SSEL_PIN_Number_c 4

/******************************************************************************/
#elif defined(MCU_MKW40Z160)
#define gSPI_HW_TYPE_c             gDSPI_HW_c
#define BOOT_SPI_BaseAddr          SPI1_BASE_PTR
#define BOOT_SPI_PORT_SIM_SCG      SIM_SCGC5
#define cSPI_PORT_SIM_SCG_Config_c SIM_SCGC5_PORTA_MASK
#define BOOT_SPI_SIM_SCG           SIM_SCGC6
#define cSPI_SIM_SCG_Config_c      SIM_SCGC6_SPI1_MASK

#define BOOT_SPI_SCLK_PCR          PORTA_PCR18
#define BOOT_SPI_MOSI_PCR          PORTA_PCR16
#define BOOT_SPI_MISO_PCR          PORTA_PCR17
#define BOOT_SPI_SSEL_PCR          PORTA_PCR19

#define BOOT_SPI_SSEL_PCOR         GPIOA_PCOR
#define BOOT_SPI_SSEL_PSOR         GPIOA_PSOR
#define BOOT_SPI_SSEL_PDDR         GPIOA_PDDR
#define BOOT_SPI_SSEL_PIN_Number_c 19

/******************************************************************************/
#elif defined(MCU_MK64FN1M)
#define gSPI_HW_TYPE_c             gDSPI_HW_c
#define BOOT_SPI_BaseAddr          SPI0_BASE_PTR
#define BOOT_SPI_PORT_SIM_SCG      SIM_SCGC5
#define cSPI_PORT_SIM_SCG_Config_c SIM_SCGC5_PORTC_MASK
#define BOOT_SPI_SIM_SCG           SIM_SCGC6
#define cSPI_SIM_SCG_Config_c      SIM_SCGC6_SPI0_MASK

#define BOOT_SPI_SCLK_PCR          PORTC_PCR5
#define BOOT_SPI_MOSI_PCR          PORTC_PCR6
#define BOOT_SPI_MISO_PCR          PORTC_PCR7
#define BOOT_SPI_SSEL_PCR          PORTC_PCR4

#define BOOT_SPI_SSEL_PCOR         GPIOC_PCOR
#define BOOT_SPI_SSEL_PSOR         GPIOC_PSOR
#define BOOT_SPI_SSEL_PDDR         GPIOC_PDDR
#define BOOT_SPI_SSEL_PIN_Number_c 4
#endif

#define  assert_cs()   {BOOT_SPI_SSEL_PCOR |= 1 << BOOT_SPI_SSEL_PIN_Number_c;}
#define  deassert_cs() {BOOT_SPI_SSEL_PSOR |= 1 << BOOT_SPI_SSEL_PIN_Number_c;}


/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */

/*! @brief SPI clock polarity configuration.*/
typedef enum _spi_clock_polarity {
    kSpiClockPolarity_ActiveHigh = 0,   /*!< Active-high SPI clock (idles low).*/
    kSpiClockPolarity_ActiveLow = 1     /*!< Active-low SPI clock (idles high).*/
} spi_clock_polarity_t;

/*! @brief SPI clock phase configuration.*/
typedef enum _spi_clock_phase {
    kSpiClockPhase_FirstEdge = 0,       /*!< First edge on SPSCK occurs at the middle of the first cycle of a data transfer.*/
    kSpiClockPhase_SecondEdge = 1       /*!< First edge on SPSCK occurs at the start of the first cycle of a data transfer.*/
} spi_clock_phase_t;

/*! @brief SPI data shifter direction options.*/
typedef enum _spi_shift_direction {
    kSpiMsbFirst = 0,    /*!< Data transfers start with most significant bit.*/
    kSpiLsbFirst = 1    /*!< Data transfers start with least significant bit.*/
} spi_shift_direction_t;

typedef uint8_t  spi_status_t;
typedef struct spi_user_config_tag{
    uint32_t busFrequencyKHz;
    spi_clock_polarity_t polarity;
    spi_clock_phase_t phase;
    spi_shift_direction_t direction;
}spi_user_config_t;


/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
void spi_master_init(uint32_t instance);
void spi_master_configure_bus(uint32_t instance, const spi_user_config_t * device);
spi_status_t spi_master_transfer(uint32_t instance,
                                 const uint8_t * sendBuffer,
                                 uint8_t * receiveBuffer,
                                 uint32_t transferByteCount);

#endif
