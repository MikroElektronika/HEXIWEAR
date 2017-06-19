// File: edma_common.c

// Definitions of some commonly used macros in the eDMA module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "edma_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// Device specific interrupts
#define DMA0_IRQn      16 // DMA Channel 0 Transfer Complete
#define DMA1_IRQn      17 // DMA Channel 1 Transfer Complete
#define DMA2_IRQn      18 // DMA Channel 2 Transfer Complete
#define DMA3_IRQn      19 // DMA Channel 3 Transfer Complete
#define DMA4_IRQn      20 // DMA Channel 4 Transfer Complete
#define DMA5_IRQn      21 // DMA Channel 5 Transfer Complete
#define DMA6_IRQn      22 // DMA Channel 6 Transfer Complete
#define DMA7_IRQn      23 // DMA Channel 7 Transfer Complete
#define DMA8_IRQn      24 // DMA Channel 8 Transfer Complete
#define DMA9_IRQn      25 // DMA Channel 9 Transfer Complete
#define DMA10_IRQn     26 // DMA Channel 10 Transfer Complete
#define DMA11_IRQn     27 // DMA Channel 11 Transfer Complete
#define DMA12_IRQn     28 // DMA Channel 12 Transfer Complete
#define DMA13_IRQn     29 // DMA Channel 13 Transfer Complete
#define DMA14_IRQn     30 // DMA Channel 14 Transfer Complete
#define DMA15_IRQn     31 // DMA Channel 15 Transfer Complete
#define DMA_Error_IRQn 32 // DMA Error Interrupt

#define DMA_CHN_IRQS   { DMA0_IRQn, DMA1_IRQn, DMA2_IRQn, DMA3_IRQn,           \
                         DMA4_IRQn, DMA5_IRQn, DMA6_IRQn, DMA7_IRQn,           \
                         DMA8_IRQn, DMA9_IRQn, DMA10_IRQn, DMA11_IRQn,         \
                         DMA12_IRQn, DMA13_IRQn, DMA14_IRQn, DMA15_IRQn }
#define DMA_ERROR_IRQS { DMA_Error_IRQn }

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

uint32_t* const g_edmaBase[] = DMA_BASE_ADDRS;
uint32_t* const g_dmamuxBase[] = DMAMUX_BASE_ADDRS;
const uint32_t
    g_edmaIrqId[ DMA_INSTANCE_COUNT ][ FSL_FEATURE_EDMA_MODULE_CHANNEL ] =
{
    DMA_CHN_IRQS
};

const uint32_t g_edmaErrIrqId[ DMA_INSTANCE_COUNT ] = DMA_ERROR_IRQS;
