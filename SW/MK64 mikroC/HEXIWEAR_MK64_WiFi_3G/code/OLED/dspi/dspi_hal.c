// File: dspi_hal.c

// Definitions of main functionalities in the DSPI HAL module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "dspi_hal.h"
#include "dspi_edma_shared_function.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// offsets
#define SPI_MCR_OFFSET          0x00
#define SPI_TCR_OFFSET          0x08
#define SPI_CTAR0_OFFSET        0x0C
#define SPI_CTAR1_OFFSET        0x10
#define SPI_SR_OFFSET           0x2C
#define SPI_RSER_OFFSET         0x30
#define SPI_PUSHR_OFFSET        0x34
#define SPI_POPR_OFFSET         0x38

#define SPIx_MCR( base )                                                       \
    ( ( uint32_t* )( ( uint8_t* )base + SPI_MCR_OFFSET ) )

#define SPIx_MCRbits( base )                                                   \
    ( ( typeSPI_MCRBITS* )SPIx_MCR( base ) )

#define SPIx_TCR( base )                                                       \
    ( ( uint32_t* )( ( uint8_t* )base + SPI_TCR_OFFSET ) )

#define SPIx_TCRbits( base )                                                   \
    ( ( typeSPI_TCRBITS* )SPIx_TCR( base ) )

#define SPIx_CTARn( base, index )                                              \
    ( ( uint32_t* )( ( uint8_t* )base + SPI_CTAR0_OFFSET + 4 * index ) )

#define SPIx_CTARnbits( base, index )                                          \
    ( ( typeSPI_CTAR0BITS* )SPIx_CTARn( base, index ) )

#define SPIx_CTAR0( base )                                                     \
    ( SPIx_CTARn( base, 0 ) )

#define SPIx_CTAR0bits( base )                                                 \
    ( ( typeSPI_CTAR0BITS* )SPIx_CTAR0( base ) )

#define SPIx_CTAR1( base )                                                     \
    ( SPIx_CTARn( base, 1 ) )

#define SPIx_CTAR1bits( base )                                                 \
    ( ( typeSPI_CTAR1BITS* )SPIx_CTAR1( base ) )

#define SPIx_SR( base )                                                        \
    ( ( uint32_t* )( ( uint8_t* )base + SPI_SR_OFFSET ) )

#define SPIx_SRbits( base )                                                    \
    ( ( typeSPI_SRBITS* )SPIx_SR( base ) )

#define SPIx_RSER( base )                                                      \
    ( ( uint32_t* )( ( uint8_t* )base + SPI_RSER_OFFSET ) )

#define SPIx_RSERbits( base )                                                  \
    ( ( typeSPI_RSERBITS* )SPIx_RSER( base ) )

#define SPIx_PUSHR( base )                                                     \
    ( ( uint32_t* )( ( uint8_t* )base + SPI_PUSHR_OFFSET ) )

#define SPIx_PUSHRbits( base )                                                 \
    ( ( typeSPI_PUSHRBITS* )SPIx_PUSHR( base ) )

#define SPIx_POPR( base )                                                      \
    ( ( uint32_t* )( ( uint8_t* )base + SPI_POPR_OFFSET ) )

#define SPIx_POPRbits( base )                                                  \
    ( ( typeSPI_POPRBITS* )SPIx_POPR( base ) )

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

typedef struct tagSPI_MCRBITS {
    unsigned HALT : 1;
    unsigned : 7;
    unsigned SMPL_PT : 2;
    unsigned CLR_RXF : 1;
    unsigned CLR_TXF : 1;
    unsigned DIS_RXF : 1;
    unsigned DIS_TXF : 1;
    unsigned MDIS : 1;
    unsigned DOZE : 1;
    unsigned PCSIS : 6;
    unsigned : 2;
    unsigned ROOE : 1;
    unsigned PCSSE : 1;
    unsigned MTFE : 1;
    unsigned FRZ : 1;
    unsigned DCONF : 2;
    unsigned CONT_SCKE : 1;
    unsigned MSTR : 1;
} typeSPI_MCRBITS;

typedef struct tagSPI_TCRBITS {
    unsigned : 16;
    unsigned SPI_TCNT : 16;
} typeSPI_TCRBITS;

typedef struct tagSPI_CTAR0BITS {
    unsigned BR : 4;
    unsigned DT : 4;
    unsigned ASC : 4;
    unsigned CSSCK : 4;
    unsigned PBR : 2;
    unsigned PDT : 2;
    unsigned PASC : 2;
    unsigned PCSSCK : 2;
    unsigned LSBFE : 1;
    unsigned CPHA : 1;
    unsigned CPOL : 1;
    unsigned FMSZ : 4;
    unsigned DBR : 1;
} typeSPI_CTAR0BITS;

typedef struct tagSPI_CTAR1BITS {
    unsigned BR : 4;
    unsigned DT : 4;
    unsigned ASC : 4;
    unsigned CSSCK : 4;
    unsigned PBR : 2;
    unsigned PDT : 2;
    unsigned PASC : 2;
    unsigned PCSSCK : 2;
    unsigned LSBFE : 1;
    unsigned CPHA : 1;
    unsigned CPOL : 1;
    unsigned FMSZ : 4;
    unsigned DBR : 1;
} typeSPI_CTAR1BITS;

typedef struct tagSPI_SRBITS {
    unsigned POPNXTPTR : 4;
    unsigned RXCTR : 4;
    unsigned TXNXTPTR : 4;
    unsigned TXCTR : 4;
    unsigned : 1;
    unsigned RFDF : 1;
    unsigned : 1;
    unsigned RFOF : 1;
    unsigned : 5;
    unsigned TFFF : 1;
    unsigned : 1;
    unsigned TFUF : 1;
    unsigned EOQF : 1;
    unsigned : 1;
    unsigned TXRXS : 1;
    unsigned TCF : 1;
} typeSPI_SRBITS;

typedef struct tagSPI_RSERBITS {
    unsigned : 16;
    unsigned RFDF_DIRS : 1;
    unsigned RFDF_RE : 1;
    unsigned : 1;
    unsigned RFOF_RE : 1;
    unsigned : 4;
    unsigned TFFF_DIRS : 1;
    unsigned TFFF_RE : 1;
    unsigned : 1;
    unsigned TFUF_RE : 1;
    unsigned EOQF_RE : 1;
    unsigned : 2;
    unsigned TCF_RE : 1;
} typeSPI_RSERBITS;

typedef struct tagSPI_PUSHRBITS {
    unsigned TXDATA : 16;
    unsigned PCS : 6;
    unsigned : 4;
    unsigned CTCNT : 1;
    unsigned EOQ : 1;
    unsigned CTAS : 3;
    unsigned CONT : 1;
} typeSPI_PUSHRBITS;

typedef struct tagSPI_POPRBITS {
    unsigned RXDATA : 32;
} typeSPI_POPRBITS;

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Configuration

// Restores the DSPI to reset the configuration.
void DSPI_HAL_Init( uint32_t* base )
{
    // First, make sure the module is enabled
    // to allow writes to certain registers.
    SPIx_MCRbits( base )->MDIS = 0;

    // Halt all transfers.
    SPIx_MCRbits( base )->HALT = 1;

    // Set the registers to their default states.
    // Clear the status bits (write-1-to-clear).
    *SPIx_SR( base ) = SPI_SR_TCF_MASK | SPI_SR_EOQF_MASK | SPI_SR_TFUF_MASK |
        SPI_SR_TFFF_MASK | SPI_SR_RFOF_MASK | SPI_SR_RFDF_MASK;

    *SPIx_TCR( base ) = 0;
    *SPIx_CTAR0( base ) = 0x78000000;
    *SPIx_CTAR1( base ) = 0x78000000;
    *SPIx_RSER( base ) = 0;

    // Clear out PUSHR register. Since DSPI is halted,
    // nothing should be transmitted. Be sure to flush the FIFOs afterwards.
    *SPIx_PUSHR( base ) = 0;

    // Flush the fifos.
    SPIx_MCRbits( base )->CLR_TXF = true;
    SPIx_MCRbits( base )->CLR_RXF = true;

    // Now set MCR to default value, which disables module:
    // set MDIS and HALT, clear other bits.
    *SPIx_MCR( base ) = SPI_MCR_MDIS_MASK | SPI_MCR_HALT_MASK;
}

// Enables the DSPI peripheral and sets the MCR MDIS to 0.
void DSPI_HAL_Enable( uint32_t* base )
{
    SPIx_MCRbits( base )->MDIS = 0;
}

// Disables the DSPI peripheral, sets MCR MDIS to 1.
void DSPI_HAL_Disable( uint32_t* base )
{
    SPIx_MCRbits( base )->MDIS = 1;
}

// Sets the DSPI baud rate in bits per second.
uint32_t DSPI_HAL_SetBaudRate( uint32_t* base, dspi_ctar_selection_t whichCtar,
    uint32_t bitsPerSec, uint32_t sourceClockInHz )
{
    uint32_t prescaler, bestPrescaler;
    uint32_t scaler, bestScaler;
    uint32_t dbr, bestDbr;
    uint32_t realBaudrate, bestBaudrate;
    uint32_t diff, min_diff;
    uint32_t baudrate = bitsPerSec;
    
    // For master mode configuration, if slave mode detected, return 0.
    if( !DSPI_HAL_IsMaster( base ) )
        return 0;

    // Find combination of prescaler and scaler
    // resulting in baudrate closest to the requested value.
    min_diff = 0xFFFFFFFFU;
    bestPrescaler = 0;
    bestScaler = 0;
    bestDbr = 1;
    bestBaudrate = 0;  // Required to avoid compilation warning.

    // In all for loops, if min_diff = 0, then exit for loop.
    for( prescaler = 0; ( prescaler < 4 ) && min_diff; prescaler++ )
    {
        for( scaler = 0; ( scaler < 16 ) && min_diff; scaler++ )
        {
            for( dbr = 1; ( dbr < 3 ) && min_diff; dbr++ )
            {
                realBaudrate = ( ( sourceClockInHz * dbr ) /
                               ( s_baudratePrescaler[ prescaler ] *
                               ( s_baudrateScaler[ scaler ] ) ) );

                // Calculate the baud rate difference based on the conditional
                // statement that states that the calculated baud rate
                // must not exceed the desired baud rate.
                if( baudrate >= realBaudrate )
                {
                    diff = baudrate - realBaudrate;
                    if( min_diff > diff )
                    {
                        // A better match found.
                        min_diff = diff;
                        bestPrescaler = prescaler;
                        bestScaler = scaler;
                        bestBaudrate = realBaudrate;
                        bestDbr = dbr;
                    }
                }
            }
        }
    }

    // Write the best dbr, prescalar, and baud rate scalar to the CTAR.
    SPIx_CTARnbits( base, whichCtar )->DBR = bestDbr - 1;
    SPIx_CTARnbits( base, whichCtar )->PBR = bestPrescaler;
    SPIx_CTARnbits( base, whichCtar )->BR  = bestScaler;

    // Return the actual calculated baud rate.
    return bestBaudrate;
}

// Configures the baud rate divisors manually.
void DSPI_HAL_SetBaudDivisors( uint32_t* base, dspi_ctar_selection_t whichCtar,
    const dspi_baud_rate_divisors_t * divisors )
{
    // These settings are only relevant in master mode.
    if( DSPI_HAL_IsMaster( base ) )
    {
        SPIx_CTARnbits( base, whichCtar )->DBR = divisors->doubleBaudRate;
        SPIx_CTARnbits( base, whichCtar )->PBR = divisors->prescaleDivisor;
        SPIx_CTARnbits( base, whichCtar )->BR  = divisors->baudRateDivisor;
    }
}

// Configures the DSPI for master or slave.
void DSPI_HAL_SetMasterSlaveMode(
    uint32_t* base, dspi_master_slave_mode_t mode )
{
    SPIx_MCRbits( base )->MSTR = mode;
}

// Returns whether the DSPI module is in master mode.
bool DSPI_HAL_IsMaster( uint32_t* base )
{
    return ( bool )SPIx_MCRbits( base )->MSTR;
}

// Configures the DSPI for the continuous SCK operation.
void DSPI_HAL_SetContinuousSckCmd( uint32_t* base, bool enable )
{
    SPIx_MCRbits( base )->CONT_SCKE = enable;
}

// Configures the DSPI peripheral chip select strobe enable.
// Configures the PCS[5] to be the active-low PCS Strobe output.
void DSPI_HAL_SetPcsStrobeCmd( uint32_t* base, bool enable )
{
    SPIx_MCRbits( base )->PCSSE = enable;
}

// Configures the DSPI received FIFO overflow overwrite enable.
void DSPI_HAL_SetRxFifoOverwriteCmd( uint32_t* base, bool enable )
{
    SPIx_MCRbits( base )->ROOE = enable;
}

// Configures the DSPI peripheral chip select polarity.
void DSPI_HAL_SetPcsPolarityMode( uint32_t* base, dspi_which_pcs_config_t pcs,
    dspi_pcs_polarity_config_t activeLowOrHigh )
{
    uint32_t temp;

    temp = SPIx_MCRbits( base )->PCSIS;

    if( activeLowOrHigh == kDspiPcs_ActiveLow )
    {
        temp |= pcs;
    }
    else   // kDspiPcsPolarity_ActiveHigh
    {
        temp &= ~( unsigned )pcs;
    }

    SPIx_MCRbits( base )->PCSIS = temp;
}

// Enables (or disables) the DSPI FIFOs.
void DSPI_HAL_SetFifoCmd(
    uint32_t* base, bool enableTxFifo, bool enableRxFifo )
{
    // First see if MDIS is set or cleared.
    uint32_t isMdisSet = SPIx_MCRbits( base )->MDIS;

    if( isMdisSet )
    {
        // Clear the MDIS bit (enable DSPI)
        // to allow us to write to the fifo disables.
        DSPI_HAL_Enable( base );
    }

    // Note, the bit definition is "disable FIFO", so a "1" would disable.
    // If user wants to enable the FIFOs, they pass in true,
    // which we must logically negate (turn to false) to enable the FIFO.
    SPIx_MCRbits( base )->DIS_TXF = !enableTxFifo;
    SPIx_MCRbits( base )->DIS_RXF = !enableRxFifo;

    // Set MDIS (disable DSPI) if it was set to begin with.
    if( isMdisSet )
    {
        DSPI_HAL_Disable( base );
    }
}

// Flushes the DSPI FIFOs.
void DSPI_HAL_SetFlushFifoCmd( uint32_t* base,
    bool enableFlushTxFifo, bool enableFlushRxFifo )
{
    SPIx_MCRbits( base )->CLR_TXF = enableFlushTxFifo;
    SPIx_MCRbits( base )->CLR_RXF = enableFlushRxFifo;
}

// Configures the time when the DSPI master samples SIN
// in the Modified Transfer Format.
void DSPI_HAL_SetDatainSamplepointMode( uint32_t* base,
    dspi_master_sample_point_t samplePnt )
{
    SPIx_MCRbits( base )->SMPL_PT = samplePnt;
}

// Starts the DSPI transfers, clears HALT bit in MCR.
void DSPI_HAL_StartTransfer( uint32_t* base )
{
    SPIx_MCRbits( base )->HALT = 0;
}

// Stops (halts) DSPI transfers, sets HALT bit in MCR.
void DSPI_HAL_StopTransfer( uint32_t* base )
{
    SPIx_MCRbits( base )->HALT = 1;
}

// Configures the data format for a particular CTAR.
dspi_status_t DSPI_HAL_SetDataFormat( uint32_t* base,
    dspi_ctar_selection_t whichCtar, const dspi_data_format_config_t * config )
{
    // Check bits-per-frame value to make sure it it within the proper range
    // in either master or slave mode.
    if( ( config->bitsPerFrame < 4 ) ||
        ( ( config->bitsPerFrame > 16 ) &&
          ( SPIx_MCRbits( base )->MSTR == 1 ) ) ||
        ( ( config->bitsPerFrame > 32 ) &&
          ( SPIx_MCRbits( base )->MSTR == 0 ) ) )
    {
        return kStatus_DSPI_InvalidBitCount;
    }

    // For master mode configuration.
    if( DSPI_HAL_IsMaster( base ) )
    {
        SPIx_CTARnbits( base, whichCtar )->FMSZ  = config->bitsPerFrame - 1;
        SPIx_CTARnbits( base, whichCtar )->CPOL  = config->clkPolarity;
        SPIx_CTARnbits( base, whichCtar )->CPHA  = config->clkPhase;
        SPIx_CTARnbits( base, whichCtar )->LSBFE = config->direction;
    }
    else  // For slave mode configuration.
    {
        // Should always be CTAR0.
        SPIx_CTARnbits( base, whichCtar )->FMSZ = config->bitsPerFrame - 1;
        SPIx_CTARnbits( base, whichCtar )->CPOL = config->clkPolarity;
        SPIx_CTARnbits( base, whichCtar )->CPHA = config->clkPhase;
    }
    return kStatus_DSPI_Success;
}

// Manually configures the delay prescaler and scaler for a particular CTAR.
void DSPI_HAL_SetDelay( uint32_t* base, dspi_ctar_selection_t whichCtar,
    uint32_t prescaler, uint32_t scaler, dspi_delay_type_t whichDelay )
{
    // These settings are only relevant in master mode.
    if( ( bool )SPIx_MCRbits( base )->MSTR )
    {
        if( whichDelay == kDspiPcsToSck )
        {
            SPIx_CTARnbits( base, whichCtar )->PCSSCK = prescaler;
            SPIx_CTARnbits( base, whichCtar )->CSSCK  = scaler;
        }

        if( whichDelay == kDspiLastSckToPcs )
        {
            SPIx_CTARnbits( base, whichCtar )->PASC = prescaler;
            SPIx_CTARnbits( base, whichCtar )->ASC  = scaler;
        }

        if( whichDelay == kDspiAfterTransfer )
        {
            SPIx_CTARnbits( base, whichCtar )->PDT = prescaler;
            SPIx_CTARnbits( base, whichCtar )->DT  = scaler;
        }
    }
}

// Calculates the delay prescaler and scaler
// based on the desired delay input in nanoseconds.
uint32_t DSPI_HAL_CalculateDelay( uint32_t* base,
    dspi_ctar_selection_t whichCtar, dspi_delay_type_t whichDelay,
    uint32_t sourceClockInHz, uint32_t delayInNanoSec )
{
    uint32_t prescaler, bestPrescaler;
    uint32_t scaler, bestScaler;
    uint32_t realDelay, bestDelay;
    uint32_t diff, min_diff;
    uint32_t initialDelayNanoSec;
    
    // For master mode configuration, if slave mode detected, return 0.
    if( !( bool )SPIx_MCR( base )->MSTR )
    {
        return 0;
    }

    // Find combination of prescaler and scaler
    // resulting in the delay closest to the requested value.
    min_diff = 0xFFFFFFFFU;
    // Initialize prescaler and scaler to their max values
    // to generate the max delay.
    bestPrescaler = 0x3;
    bestScaler = 0xF;
    bestDelay = ( 1000000000 / sourceClockInHz ) *
                s_delayPrescaler[ bestPrescaler ] *
                s_delayScaler[ bestScaler ];

    // First calculate the initial, default delay.
    initialDelayNanoSec = 1000000000 / sourceClockInHz * 2;

    // If the initial, default delay is already greater than the desired delay,
    // then set the delays to their initial value (0) and return the delay.
    // In other words, there is no way to decrease the delay value further.
    if( initialDelayNanoSec >= delayInNanoSec )
    {
        DSPI_HAL_SetDelay( base, whichCtar, 0, 0, whichDelay );
        return initialDelayNanoSec;
    }

    // In all for loops, if min_diff = 0, the exit for loop.
    for( prescaler = 0; ( prescaler < 4 ) && min_diff; prescaler++ )
    {
        for( scaler = 0; ( scaler < 16 ) && min_diff; scaler++ )
        {
            realDelay = ( 1000000000 / sourceClockInHz ) *
                        s_delayPrescaler[ prescaler ] *
                        s_delayScaler[ scaler ];

            // Calculate the delay difference based on the conditional statement
            // that states that the calculated delay
            // must not be less then the desired delay.
            if( realDelay >= delayInNanoSec )
            {
                diff = realDelay-delayInNanoSec;
                if( min_diff > diff )
                {
                    // a better match found
                    min_diff = diff;
                    bestPrescaler = prescaler;
                    bestScaler = scaler;
                    bestDelay = realDelay;
                }
            }
        }
    }

    // Write the best dbr, prescalar, and baud rate scalar to the CTAR.
    DSPI_HAL_SetDelay( base, whichCtar, bestPrescaler, bestScaler, whichDelay );

    // return the actual calculated baud rate
    return bestDelay;
}

// Gets the DSPI master PUSHR data register address for DMA operation.
uint32_t DSPI_HAL_GetMasterPushrRegAddr( uint32_t* base )
{
    return ( uint32_t )( SPIx_PUSHR( base ) );
}

// Gets the DSPI slave PUSHR data register address for DMA operation.
uint32_t DSPI_HAL_GetSlavePushrRegAddr( uint32_t* base )
{
    return ( uint32_t )( SPIx_PUSHR( base ) );
}

// Gets the DSPI POPR data register address for DMA operation.
uint32_t DSPI_HAL_GetPoprRegAddr( uint32_t* base )
{
    return ( uint32_t )( SPIx_POPR( base ) );
}

// Interrupts

// Configures the DSPI Tx FIFO fill request
// to generate DMA or interrupt requests.
void DSPI_HAL_SetTxFifoFillDmaIntMode( uint32_t* base,
    dspi_dma_or_int_mode_t mode, bool enable )
{
    SPIx_RSERbits( base )->TFFF_DIRS = mode; // Configure as DMA or interrupt.
    SPIx_RSERbits( base )->TFFF_RE = enable; // Enable or disable the request.
}

// Configures the DSPI Rx FIFO drain request
// to generate DMA or interrupt requests.
void DSPI_HAL_SetRxFifoDrainDmaIntMode( uint32_t* base,
    dspi_dma_or_int_mode_t mode, bool enable )
{
    SPIx_RSERbits( base )->RFDF_DIRS = mode; // Configure as DMA or interrupt.
    SPIx_RSERbits( base )->RFDF_RE = enable; // Enable or disable the request.
}

// Configures the DSPI interrupts.
void DSPI_HAL_SetIntMode( uint32_t* base,
    dspi_status_and_interrupt_request_t interruptSrc, bool enable )
{
    uint32_t temp;

    temp = ( *SPIx_RSER( base ) & ~( 0x1U << interruptSrc ) ) |
           ( ( uint32_t )enable << interruptSrc );
    *SPIx_RSER( base ) = temp;
}

// Gets DSPI interrupt configuration,
// returns if interrupt request is enabled or disabled.
bool DSPI_HAL_GetIntMode( uint32_t * base,
    dspi_status_and_interrupt_request_t interruptSrc )
{
    return ( ( *SPIx_RSER( base ) >> interruptSrc ) & 0x1 );
}

// Status

// Gets the DSPI status flag state.
bool DSPI_HAL_GetStatusFlag( uint32_t* base,
    dspi_status_and_interrupt_request_t statusFlag )
{
    return ( ( *SPIx_SR( base ) >> statusFlag ) & 0x1 );
}

// Clears the DSPI status flag.
void DSPI_HAL_ClearStatusFlag( uint32_t* base,
    dspi_status_and_interrupt_request_t statusFlag )
{
//    *SPIx_SR( base ) = 0x1U << statusFlag;
    
//    SPIx_SRtemp = 0;
//    SPIx_SRtemp = *SPIx_SR( base );
    uint32_t baseAddr = ( uint32_t )base;
    
    switch( baseAddr )
    {
        case SPI0_BASE:
            switch( statusFlag )
            {
                case kDspiTxComplete:
                    TCF_bit = 1;
                    break;
                case kDspiTxAndRxStatus:
                    TXRXS_bit = 1;
                    break;
                case kDspiEndOfQueue:
                    EOQF_bit = 1;
                    break;
                case kDspiTxFifoUnderflow:
                    TFUF_bit = 1;
                    break;
                case kDspiTxFifoFillRequest:
                    TFFF_bit = 1;
                    break;
                case kDspiRxFifoOverflow:
                    RFOF_bit = 1;
                    break;
                case kDspiRxFifoDrainRequest:
                    RFDF_bit = 1;
                    break;
                default:
                    break;
            }
            break;
        case SPI1_BASE:
            switch( statusFlag )
            {
                case kDspiTxComplete:
                    TCF_SPI1_SR_bit = 1;
                    break;
                case kDspiTxAndRxStatus:
                    TXRXS_SPI1_SR_bit = 1;
                    break;
                case kDspiEndOfQueue:
                    EOQF_SPI1_SR_bit = 1;
                    break;
                case kDspiTxFifoUnderflow:
                    TFUF_SPI1_SR_bit = 1;
                    break;
                case kDspiTxFifoFillRequest:
                    TFFF_SPI1_SR_bit = 1;
                    break;
                case kDspiRxFifoOverflow:
                    RFOF_SPI1_SR_bit = 1;
                    break;
                case kDspiRxFifoDrainRequest:
                    RFDF_SPI1_SR_bit = 1;
                    break;
                default:
                    break;
            }
            break;
        case SPI2_BASE:
            switch( statusFlag )
            {
                case kDspiTxComplete:
                    TCF_SPI2_SR_bit = 1;
                    break;
                case kDspiTxAndRxStatus:
                    TXRXS_SPI2_SR_bit = 1;
                    break;
                case kDspiEndOfQueue:
                    EOQF_SPI2_SR_bit = 1;
                    break;
                case kDspiTxFifoUnderflow:
                    TFUF_SPI2_SR_bit = 1;
                    break;
                case kDspiTxFifoFillRequest:
                    TFFF_SPI2_SR_bit = 1;
                    break;
                case kDspiRxFifoOverflow:
                    RFOF_SPI2_SR_bit = 1;
                    break;
                case kDspiRxFifoDrainRequest:
                    RFDF_SPI2_SR_bit = 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

// Data transfer

// Reads data from the data buffer.
uint32_t DSPI_HAL_ReadData( uint32_t* base )
{
    return *SPIx_POPR( base );
}

// Writes data into the data buffer, slave mode.
void DSPI_HAL_WriteDataSlavemode( uint32_t* base, uint32_t _data )
{
    *SPIx_PUSHR( base ) = _data;
}

// Writes data into the data buffer, slave mode
// and waits till data was transmitted and return.
void DSPI_HAL_WriteDataSlavemodeBlocking( uint32_t* base, uint32_t _data )
{
    // Firstly, clear transmit complete flag.
    SPIx_SRbits( base )->TCF = 1;
    // Write data into register.
    *SPIx_PUSHR( base ) = _data;
    // Wait till the data is transmitted.
    while( SPIx_SRbits( base )->TCF == 0 ) {}
}

// Writes data into the data buffer, master mode.
void DSPI_HAL_WriteDataMastermode( uint32_t* base,
    dspi_command_config_t * command, uint16_t _data )
{
    uint32_t temp;

    // First, build up the 32-bit word then write it to the PUSHR.
    // Note, to work around MISRA warnings typecast each variable
    // before the shift
    temp = ( ( uint32_t )( command->isChipSelectContinuous )
               << SPI_PUSHR_CONT_SHIFT ) |
           ( ( uint32_t )( command->whichCtar ) << SPI_PUSHR_CTAS_SHIFT ) |
           ( ( uint32_t )( command->whichPcs ) << SPI_PUSHR_PCS_SHIFT ) |
           ( ( uint32_t )( command->isEndOfQueue ) << SPI_PUSHR_EOQ_SHIFT ) |
           ( ( uint32_t )( command->clearTransferCount )
               << SPI_PUSHR_CTCNT_SHIFT ) |
           ( ( uint32_t )( _data ) << SPI_PUSHR_TXDATA_SHIFT );

    *SPIx_PUSHR( base ) = temp;
}

// Writes data into the data buffer, master mode
// and waits till complete to return.
void DSPI_HAL_WriteDataMastermodeBlocking( uint32_t* base,
    dspi_command_config_t* command, uint16_t _data )
{
    uint32_t temp;

    // First, clear Transmit Complete Flag (TCF).
    SPIx_SRbits( base )->TCF = 1;

    // First, build up the 32-bit word then write it to the PUSHR
    // Note, to work around MISRA warnings typecast each variable
    // before the shift
    temp = ( ( uint32_t )( command->isChipSelectContinuous )
               << SPI_PUSHR_CONT_SHIFT ) |
           ( ( uint32_t )( command->whichCtar ) << SPI_PUSHR_CTAS_SHIFT ) |
           ( ( uint32_t )( command->whichPcs ) << SPI_PUSHR_PCS_SHIFT ) |
           ( ( uint32_t )( command->isEndOfQueue ) << SPI_PUSHR_EOQ_SHIFT ) |
           ( ( uint32_t )( command->clearTransferCount )
               << SPI_PUSHR_CTCNT_SHIFT ) |
           ( ( uint32_t )( _data ) << SPI_PUSHR_TXDATA_SHIFT );

    *SPIx_PUSHR( base ) = temp;

    // Wait till TCF sets.
    while( SPIx_SRbits( base )->TCF == 0) {}
}

// Writes a 32-bit data word (16-bit command appended with 16-bit data)
// into the data buffer, master mode.
void DSPI_HAL_WriteCmdDataMastermode( uint32_t* base, uint32_t _data )
{
    *SPIx_PUSHR( base ) = _data;
}

// Writes a 32-bit data word (16-bit command appended with 16-bit data)
// into the data buffer, master mode and waits till complete to return.
void DSPI_HAL_WriteCmdDataMastermodeBlocking( uint32_t* base, uint32_t _data )
{
    // First, clear Transmit Complete Flag (TCF).
    SPIx_SRbits( base )->TCF = 1;

    *SPIx_PUSHR( base ) = _data;

    // Wait till TCF sets.
    while( SPIx_SRbits( base )->TCF == 0) {}
}

// Gets the transfer count.
uint32_t DSPI_HAL_GetTransferCount( uint32_t* base )
{
    return SPIx_TCRbits( base )->SPI_TCNT;
}

// Pre-sets the transfer count.
void DSPI_HAL_PresetTransferCount( uint32_t* base, uint16_t presetValue )
{
    SPIx_TCRbits( base )->SPI_TCNT = presetValue;
}

// Returns the DSPI command word formatted to the PUSHR data register bit field.
uint32_t DSPI_HAL_GetFormattedCommand( uint32_t* base,
    dspi_command_config_t* command )
{
    uint32_t temp;

    // Format the 16-bit command word
    // according to the PUSHR data register bit field
    // Note, to work around MISRA warnings typecast each variable
    // before the shift
    temp = ( ( uint32_t )( command->isChipSelectContinuous )
               << SPI_PUSHR_CONT_SHIFT ) |
           ( ( uint32_t )( command->whichCtar ) << SPI_PUSHR_CTAS_SHIFT ) |
           ( ( uint32_t )( command->whichPcs ) << SPI_PUSHR_PCS_SHIFT ) |
           ( ( uint32_t )( command->isEndOfQueue ) << SPI_PUSHR_EOQ_SHIFT ) |
           ( ( uint32_t )( command->clearTransferCount )
               << SPI_PUSHR_CTCNT_SHIFT );

    return temp;
}