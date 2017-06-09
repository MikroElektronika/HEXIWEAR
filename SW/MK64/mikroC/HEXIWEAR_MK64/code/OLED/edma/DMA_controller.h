// File: DMA_controller.h

// Declarations of interrupt routines in the eDMA module.

#ifndef _DMA_controller_h_
#define _DMA_controller_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "edma_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// Device instance number
#define FSL_DMA_CONTROLLER 0

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Driver state structure which holds driver runtime data
extern edma_state_t DMA_controller_State;

// Configuration declaration
extern const edma_user_config_t DMA_controller_InitConfig0;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Dma channel 0 ISR
void DMA0_IRQHandler();

// Dma channel 1 ISR
void DMA1_IRQHandler();

// Dma channel 2 ISR
void DMA2_IRQHandler();

// Dma channel 3 ISR
void DMA3_IRQHandler();

// Dma channel 4 ISR
void DMA4_IRQHandler();

// Dma channel 5 ISR
void DMA5_IRQHandler();

// Dma channel 6 ISR
void DMA6_IRQHandler();

// Dma channel 7 ISR
void DMA7_IRQHandler();

// Dma channel 8 ISR
void DMA8_IRQHandler();

// Dma channel 9 ISR
void DMA9_IRQHandler();

// Dma channel 10 ISR
void DMA10_IRQHandler();

// Dma channel 11 ISR
void DMA11_IRQHandler();

// Dma channel 12 ISR
void DMA12_IRQHandler();

// Dma channel 13 ISR
void DMA13_IRQHandler();

// Dma channel 14 ISR
void DMA14_IRQHandler();

// Dma channel 15 ISR
void DMA15_IRQHandler();

// Dma error ISR
void DMA_Error_IRQHandler();

#endif