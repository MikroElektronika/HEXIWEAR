// File: dspi_edma_shared_function.c

// Definitions of shared functionalities in the DSPI module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "dspi_edma_shared_function.h"
#include "dspi_edma_master_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

void SPI2_IrqHandler() iv IVT_INT_SPI2 ics ICS_AUTO
{
    DSPI_DRV_EdmaIRQHandler( 2 );
}

// Passes IRQ control to either the master or slave driver.
void DSPI_DRV_EdmaIRQHandler( uint32_t instance )
{
    uint32_t *base;

    if( !( instance < SPI_INSTANCE_COUNT ) ) return;
    
    base = g_dspiBase[instance];

    if( DSPI_HAL_IsMaster( base ) )
    {
        // Master mode.
        DSPI_DRV_EdmaMasterIRQHandler( instance );
    }
    else
    {
        // Slave mode.
        // DSPI_DRV_EdmaSlaveIRQHandler( instance );
    }
}