// File: uart_driver.c

// Definitions of main functionalities in the UART module.

#include <string.h>
#include "uart/uart_driver.h"
#include "OSA.h"
#include "initialise.h"

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static uint32_t CLOCK_HAL_GetMcgExternalClkFreq()
{
    uint8_t oscselVal;
    uint32_t extFreq = 0;
    
    oscselVal = MCG_C7 & 0x3;
    switch( oscselVal )
    {
        case 0:
            extFreq = g_xtal0ClkFreq;
            break;
        case 1:
            extFreq = g_xtalRtcClkFreq;
            break;
        case 2:
            extFreq = 48000000;
            break;
        default:
            extFreq = 0;
            break;
    }
    
    return extFreq;
}

static uint32_t CLOCK_HAL_GetPll0Clk()
{
    uint32_t mcgpll0clk;
    uint8_t  divider;
    
    if( !( ( PLLST_bit == 1 ) || ( PLLCLKEN0_bit == 1 ) ) )
        return 0;

    mcgpll0clk = CLOCK_HAL_GetMcgExternalClkFreq();
    
    divider = ( 1 + ( MCG_C5 & 0x1F ) );
    mcgpll0clk /= divider;
    
    divider = ( ( MCG_C6 & 0x1F ) + 24 );
    mcgpll0clk = ( mcgpll0clk * divider );
    
    return mcgpll0clk;
}

static uint32_t CLOCK_HAL_GetFllRefClk()
{
    uint32_t mcgffclk;
    uint8_t frdiv;
    uint8_t range;
    uint8_t oscsel;
    
    if( IREFS_bit == 0 )
    {
        mcgffclk = CLOCK_HAL_GetMcgExternalClkFreq();
        frdiv = ( MCG_C1 >> 3 ) & 0x7;
        range = ( MCG_C2 >> 4 ) & 0x3;
        oscsel = MCG_C7 & 0x3;
        
        mcgffclk >>= frdiv;
        if( ( range != 0 ) && ( oscsel != 1 ) )
        {
            switch( frdiv )
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    mcgffclk >>= 5U;
                    break;
                case 6:
                    mcgffclk /= 20U; // 64*20=1280
                    break;
                case 7:
                    mcgffclk /= 12U; // 128*12=1536
                    break;
                default:
                    mcgffclk = 0U;  // Reserved.
                    break;
            }
        }
    }
    else
    {
        mcgffclk = 32768U;
    }
    return mcgffclk;
}

uint32_t CLOCK_HAL_TestFllFreq( uint32_t fllRef, uint8_t dmx32, uint8_t drs )
{
    static const uint16_t fllFactorTable[4][2] = {
        { 640,  732 },
        { 1280, 1464 },
        { 1920, 2197 },
        { 2560, 2929 }
    };
    
    if( dmx32 != 0 )
    {
        if( fllRef > 32768 )
            return 0;
    }
    else
    {
        if( ( fllRef < 31250 ) || ( fllRef > 39063 ) )
            return 0;
    }
    
    return fllRef * fllFactorTable[drs][dmx32];
}

static uint32_t CLOCK_HAL_GetFllClk()
{
    uint32_t mcgfllclk;
    uint8_t dmx32;
    uint8_t drs;
    
    if( PLLST_bit == 1 )
        return 0;

    mcgfllclk = CLOCK_HAL_GetFllRefClk();
    if( mcgfllclk == 0 )
        return 0;

    dmx32 = DMX32_bit;
    drs   = ( MCG_C4 >> 5 ) & 0x3;
    
    mcgfllclk = CLOCK_HAL_TestFllFreq( mcgfllclk, dmx32, drs );

    return mcgfllclk;
}

uint32_t CLOCK_HAL_GetInternalRefClk()
{
    uint32_t mcgirclk;
    
    if ( IRCLKEN_bit == 0 )
    {
        return 0U;
    }
    
    if( IRCS_bit == 0 )
    {
        mcgirclk = 32768U;
    }
    else
    {
        mcgirclk = 4000000U >> ( MCG_SC >> 1 ) & 0x7;
    }
    
    return mcgirclk;
}

static uint32_t CLOCK_HAL_GetOutClk() // MCG
{
    uint32_t mcgoutclk = 0;
    uint8_t src;
    
    src = ( ( ( uint8_t )CLKST1_bit ) << 1 ) | CLKST0_bit;
    
    switch( src )
    {
        case 3:
            mcgoutclk = CLOCK_HAL_GetPll0Clk();
            break;
        case 0:
            mcgoutclk = CLOCK_HAL_GetFllClk();
            break;
        case 1:
            mcgoutclk = CLOCK_HAL_GetInternalRefClk();
            break;
        case 2:
            mcgoutclk = CLOCK_HAL_GetMcgExternalClkFreq();
            break;
        default:
            mcgoutclk = 0;
            break;
    }
    
    return mcgoutclk;
}

static uint8_t CLOCK_HAL_GetOutDiv2() // SIM
{
    return ( SIM_CLKDIV1 >> 24 ) & 0xf;
}

void UART_HAL_SetBaudRate( uint32_t sourceClockInHz, uint32_t baudRate )
{
    uint16_t sbr;
    uint16_t brfa;
    
    sbr = sourceClockInHz / (baudRate * 16);
    
    if ( (sbr > 0x1FFF) || (sbr < 1) )
    {
        return;
    }
    
    UART4_BDH &= ~( 0x1f );
    UART4_BDH |= ( sbr >> 8 ) & 0x1f;
    UART4_BDL = ( uint8_t )sbr;
    
    brfa = (32*sourceClockInHz/(baudRate*16)) - 32*sbr;
    
    UART4_C4 &= ~( 0x1f );
    UART4_C4 |= ( uint8_t )brfa;
}

static void UART_HAL_SetBitCountPerChar( uint8_t bitCountPerChar )
{
    M_UART4_C1_bit = bitCountPerChar;
}

static void UART_HAL_SetParityMode( uint8_t parityMode)
{
    PE_UART4_C1_bit = ( parityMode >> 1 ) & 0x1;
    PT_UART4_C1_bit = parityMode & 0x1;
}

void UART_HAL_SetStopBitCount( uint8_t stopBitCount )
{
    SBNS_UART4_BDH_bit = stopBitCount;
}

uint8_t UART_HAL_GetTxFifoSize()
{
    return ( UART4_PFIFO >> 4 ) & 0x7;
}

uint8_t UART_HAL_SetTxFifoWatermark( uint8_t watermark )
{
    if( TE_UART4_C2_bit != 0 )
    {
        return 5;
    }
    else
    {
        UART4_TWFIFO = watermark;
        return 0;
    }
}

uint8_t UART_HAL_SetRxFifoWatermark( uint8_t watermark )
{
    if( RE_UART4_C2_bit != 0 )
    {
        return 6;
    }
    else
    {
        UART4_RWFIFO = watermark;
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

uint32_t CLOCK_SYS_GetBusClockFreq()
{
    return CLOCK_HAL_GetOutClk() / ( CLOCK_HAL_GetOutDiv2() + 1 );
}
 
// Initialises UART4 module.
void UART_DRV_Init( uart_state_t* uartStatePtr )
{
    uint32_t uartSourceClock;
    uint8_t fifoSize;

    MUX0_PORTE_PCR25_bit = 1;
    MUX1_PORTE_PCR25_bit = 1;
    MUX2_PORTE_PCR25_bit = 0;
    
    MUX0_PORTE_PCR24_bit = 1;
    MUX1_PORTE_PCR24_bit = 1;
    MUX2_PORTE_PCR24_bit = 0;
    
    memset( uartStatePtr, 0, sizeof( uart_state_t ) );
    
    UART4_bit = 1;
    
    UART4_BDH = 0;
    UART4_BDL = 4;
    UART4_C1 = 0;
    UART4_C2 = 0;
    UART4_S2 = 0;
    UART4_C3 = 0;
    UART4_MA1 = 0;
    UART4_MA2 = 0;
    UART4_C4 = 0;
    UART4_MODEM = 0;
    UART4_IR = 0;
    UART4_PFIFO = 0;
    UART4_CFIFO = 0;
    UART4_SFIFO = 0xC0U;
    UART4_TWFIFO = 0;
    UART4_RWFIFO = 0;
    
    OSA_SemaCreate( &uartStatePtr->txIrqSync, 0 );
    OSA_SemaCreate( &uartStatePtr->rxIrqSync, 0 );
    
    uartSourceClock = CLOCK_SYS_GetBusClockFreq();
    UART_HAL_SetBaudRate( uartSourceClock, 230400U );
    UART_HAL_SetBitCountPerChar( 0 );
    UART_HAL_SetParityMode( 0 );
    UART_HAL_SetStopBitCount( 1 );
    
    fifoSize = UART_HAL_GetTxFifoSize();
    uartStatePtr->txFifoEntryCount = ( fifoSize == 0 ?
                                       1 :
                                       0x1 << ( fifoSize + 1 ) );
    if( uartStatePtr->txFifoEntryCount > 1 )
    {
        UART_HAL_SetTxFifoWatermark( uartStatePtr->txFifoEntryCount >> 1U );
    }
    else
    {
        UART_HAL_SetTxFifoWatermark( 0 );
    }
    UART_HAL_SetRxFifoWatermark( 1 );
    
    if( ( TE_UART4_C2_bit != 0 ) || ( RE_UART4_C2_bit != 0 ) )
    {
        TXFE_UART4_PFIFO_bit = 1;
        RXFE_UART4_PFIFO_bit = 1;
        TXFLUSH_UART4_CFIFO_bit = 1;
        RXFLUSH_UART4_CFIFO_bit = 1;
    }
    
    NVIC_IntEnable( IVT_INT_UART4_RX_TX );
    
    TE_UART4_C2_bit = 1;
    RE_UART4_C2_bit = 1;
}