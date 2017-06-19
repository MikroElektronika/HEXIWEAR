// File: dmamux_hal.h

// Declarations of main functionalities in the DMAMUX hal module.

#ifndef _dmamux_hal_h_
#define _dmamux_hal_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define DMAMUX_BASE                              ( 0x40021000u )

#define DMAMUX_BASE_ADDRS                        { DMAMUX_BASE }

#define DMAMUX_INSTANCE_COUNT (1U) // Number of instances of the DMAMUX module.
#define DMAMUX_IDX (0U)            // Instance number for DMAMUX.

// Number of DMA channels (related to number of register CHCFGn).
#define FSL_FEATURE_DMAMUX_MODULE_CHANNEL (16)
// Total number of DMA channels on all modules.
#define FSL_FEATURE_DMAMUX_DMAMUX_CHANNELS (DMAMUX_INSTANCE_COUNT * 16)
// Has the periodic trigger capability for the triggered DMA channel 0
// (register bit CHCFG0[TRIG]).
#define FSL_FEATURE_DMAMUX_HAS_TRIG (1)

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum _dmamux_source {
    // Maximum number of the DMA requests allowed for the DMA mux.
    kDmamuxDmaRequestSource = 64U
} dmamux_dma_request_source;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initializes the DMAMUX module to the reset state.
void DMAMUX_HAL_Init( uint32_t *base );

// Enables/Disables the DMAMUX channel.
void DMAMUX_HAL_SetChannelCmd( uint32_t *base, uint32_t channel, bool enable );

// Enables/Disables the period trigger.
void DMAMUX_HAL_SetPeriodTriggerCmd(
    uint32_t *base, uint32_t channel, bool enable );

// Configures the DMA request for the DMAMUX channel.
void DMAMUX_HAL_SetTriggerSource(
    uint32_t *base, uint32_t channel, uint8_t source );

#endif