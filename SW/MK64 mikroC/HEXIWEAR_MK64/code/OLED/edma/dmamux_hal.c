// File: dmamux_hal.c

// Definiations of main functionalities in the DMAMUX hal module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "dmamux_hal.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define DMAMUXx_CHCFGn( base, channel )                                        \
    ( ( uint8_t* )( ( uint8_t* )base + channel ) )
    
#define DMAMUXx_CHCFGnbits( base, channel )                                    \
    ( ( typeDMAMUX_CHCFGnBITS* )DMAMUXx_CHCFGn( base, channel ) )

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef struct tagDMAMUX_CHCFGnBITS {
    unsigned SOURCE : 6;
    unsigned TRIG : 1;
    unsigned ENBL : 1;
} typeDMAMUX_CHCFGnBITS;

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initializes the DMAMUX module to the reset state.
void DMAMUX_HAL_Init( uint32_t *base )
{
    int i;

    for( i = 0; i < FSL_FEATURE_DMAMUX_MODULE_CHANNEL; i++ )
    {
        DMAMUXx_CHCFGnbits( base, i )->ENBL = 0U;
        DMAMUXx_CHCFGnbits( base, i )->SOURCE = 0U;
    }
}

// Enables/Disables the DMAMUX channel.
void DMAMUX_HAL_SetChannelCmd( uint32_t *base, uint32_t channel, bool enable )
{
    if( !( channel < FSL_FEATURE_DMAMUX_MODULE_CHANNEL ) ) return;

    DMAMUXx_CHCFGnbits( base, channel )->ENBL = enable;
}

// Enables/Disables the period trigger.
void DMAMUX_HAL_SetPeriodTriggerCmd( uint32_t *base,
    uint32_t channel, bool enable )
{
    if( !( channel < FSL_FEATURE_DMAMUX_MODULE_CHANNEL ) ) return;

    DMAMUXx_CHCFGnbits( base, channel )->TRIG = enable;
}

// Configures the DMA request for the DMAMUX channel.
void DMAMUX_HAL_SetTriggerSource( uint32_t *base,
    uint32_t channel, uint8_t source )
{
    if( !( channel < FSL_FEATURE_DMAMUX_MODULE_CHANNEL ) ) return;

    DMAMUXx_CHCFGnbits( base, channel )->SOURCE = source;
}