// File: DMA_controller.c

// Definitions of interrupt routines in the eDMA module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "DMA_controller.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

edma_state_t DMA_controller_State;

const edma_user_config_t DMA_controller_InitConfig0 = {
    kEDMAChnArbitrationFixedPriority, // .chnArbitration
    false                             // .notHaltOnError
};

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

/// Dma channel 0 ISR
void DMA0_IRQHandler() iv IVT_INT_DMA0 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 0U );
}

// Dma channel 1 ISR
void DMA1_IRQHandler() iv IVT_INT_DMA1 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 1U );
}

// Dma channel 2 ISR
void DMA2_IRQHandler() iv IVT_INT_DMA2 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 2U );
}

// Dma channel 3 ISR
void DMA3_IRQHandler() iv IVT_INT_DMA3 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 3U );
}

// Dma channel 4 ISR
void DMA4_IRQHandler() iv IVT_INT_DMA4 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 4U );
}

// Dma channel 5 ISR
void DMA5_IRQHandler() iv IVT_INT_DMA5 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 5U );
}

// Dma channel 6 ISR
void DMA6_IRQHandler() iv IVT_INT_DMA6 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 6U );
}

// Dma channel 7 ISR
void DMA7_IRQHandler() iv IVT_INT_DMA7 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 7U );
}

// Dma channel 8 ISR
void DMA8_IRQHandler() iv IVT_INT_DMA8 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 8U );
}

// Dma channel 9 ISR
void DMA9_IRQHandler() iv IVT_INT_DMA9 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 9U );
}

// Dma channel 10 ISR
void DMA10_IRQHandler() iv IVT_INT_DMA10 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 10U );
}

// Dma channel 11 ISR
void DMA11_IRQHandler() iv IVT_INT_DMA11 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 11U );
}

// Dma channel 12 ISR
void DMA12_IRQHandler() iv IVT_INT_DMA12 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 12U );
}

// Dma channel 13 ISR
void DMA13_IRQHandler() iv IVT_INT_DMA13 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 13U );
}

// Dma channel 14 ISR
void DMA14_IRQHandler() iv IVT_INT_DMA14 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 14U );
}

// Dma channel 15 ISR
void DMA15_IRQHandler() iv IVT_INT_DMA15 ics ICS_AUTO
{
    EDMA_DRV_IRQHandler( 15U );
}

// Dma error ISR
void DMA_Error_IRQHandler() iv IVT_INT_DMA_Error ics ICS_AUTO
{
    EDMA_DRV_ErrorIRQHandler( DMA_IDX );
}