// File: edma_driver.c

// Definitions of main functionalities in the eDMA module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include "edma_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define EDMA_DRV_LOCK()         OSA_MutexLock( &g_edma->lock, OSA_WAIT_FOREVER )
#define EDMA_DRV_UNLOCK()       OSA_MutexUnlock( &g_edma->lock )

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static edma_state_t *g_edma = NULL;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Claims an eDMA channel.
static edma_status_t EDMA_DRV_ClaimChannel(
    uint8_t channel, dma_request_source_t source, edma_chn_state_t *chn )
{
    uint8_t src = ( uint32_t )source & 0xFF;
    uint32_t *edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE( channel );
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN( channel );
    uint32_t *dmamuxRegBase = VIRTUAL_CHN_TO_DMAMUX_MODULE_REGBASE( channel );
    uint32_t dmamuxChannel = VIRTUAL_CHN_TO_DMAMUX_CHN( channel );

    // Reset the channel state structure to default value.
    memset( chn, 0, sizeof( edma_chn_state_t ) );

    // Init the channel state structure to the allocated channel number.
    chn->channel = channel;

    // Enable error interrupt for this channel.
    EDMA_HAL_SetErrorIntCmd(
        edmaRegBase, true, ( edma_channel_indicator_t )edmaChannel );

    // Configure the DMAMUX for edma channel
    DMAMUX_HAL_SetChannelCmd( dmamuxRegBase, dmamuxChannel, false );
    DMAMUX_HAL_SetTriggerSource( dmamuxRegBase, dmamuxChannel,
        src % ( uint8_t )kDmamuxDmaRequestSource );
    DMAMUX_HAL_SetChannelCmd( dmamuxRegBase, dmamuxChannel, true );

    // Clear the TCD registers for this channel
    EDMA_HAL_HTCDClearReg( edmaRegBase, edmaChannel );

    return kStatus_EDMA_Success;
}

// Clears done and interrupt status.
static void EDMA_DRV_ClearIntStatus(uint8_t channel)
{
    uint32_t *edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE( channel );
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN( channel );

    EDMA_HAL_ClearDoneStatusFlag(
        edmaRegBase, ( edma_channel_indicator_t )edmaChannel );
    EDMA_HAL_ClearIntStatusFlag(
        edmaRegBase, ( edma_channel_indicator_t )edmaChannel );
}

// Enables DMA clock.
CLOCK_SYS_EnableDmaClock( uint32_t i )
{
    DMA_SIM_SCGC7_bit = 1;
}

// Disables DMA clock.
CLOCK_SYS_DisableDmaClock( uint32_t i )
{
    DMA_SIM_SCGC7_bit = 0;
}

// Enables DMAMUX clock.
CLOCK_SYS_EnableDmamuxClock( uint32_t i )
{
    DMAMUX_bit = 1;
}

// Disables DMAMUX clock.
CLOCK_SYS_DisableDmamuxClock( uint32_t i )
{
    DMAMUX_bit = 0;
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// eDMA peripheral driver module level functions

// Initializes all eDMA modules in an SOC.
edma_status_t EDMA_DRV_Init(
    edma_state_t *edmaState, const edma_user_config_t *userConfig )
{
    uint32_t i, j;
    uint32_t *edmaRegBase;
    uint32_t *dmamuxRegBase;
    uint32_t irqNumber;

    if( g_edma )
        return kStatus_EDMA_Success;

    g_edma = edmaState;
    memset( g_edma, 0, sizeof( edma_state_t ) );
    // Init mutex object for the access control of edma data structure.
    OSA_MutexCreate( &g_edma->lock );

    for( i = 0; i < DMA_INSTANCE_COUNT; i++ )
    {
        edmaRegBase = g_edmaBase[i];
        // Enable clock gate of eDMA module.
        CLOCK_SYS_EnableDmaClock( i );

        // Init eDMA module in hardware level.
        EDMA_HAL_Init( edmaRegBase );

        EDMA_HAL_SetChannelArbitrationMode(
            edmaRegBase, userConfig->chnArbitration );
        EDMA_HAL_SetHaltOnErrorCmd( edmaRegBase, !userConfig->notHaltOnError );

        // Enable the error interrupt for eDMA module.
        irqNumber = g_edmaErrIrqId[i];
        NVIC_IntEnable( irqNumber );

        // Register all edma channl interrupt handler into vector table.
        for( j = 0; j < FSL_FEATURE_EDMA_MODULE_CHANNEL; j++ )
        {
            // Enable channel interrupt ID.
            irqNumber = g_edmaIrqId[i][j];
            NVIC_IntEnable( irqNumber );
        }
    }

    for( i = 0; i < DMAMUX_INSTANCE_COUNT; i++ )
    {
        dmamuxRegBase = g_dmamuxBase[i];
        // Enable dmamux clock gate
        CLOCK_SYS_EnableDmamuxClock( i );

        // Init dmamux module in hardware level
        DMAMUX_HAL_Init( dmamuxRegBase );
    }

    return kStatus_EDMA_Success;
}

// Shuts down all eDMA modules.
edma_status_t EDMA_DRV_Deinit()
{
    uint32_t i, j;
    uint32_t irqNumber;
    edma_chn_state_t *chn;

    // Release all edma channels.
    for( i = 0; i < DMA_INSTANCE_COUNT; i++ )
    {
        // Disable the error interrupt for eDMA module.
        irqNumber = g_edmaErrIrqId[i];
        NVIC_IntDisable( irqNumber );

        for( j = i * FSL_FEATURE_EDMA_MODULE_CHANNEL;
             j < ( i + 1 ) * FSL_FEATURE_EDMA_MODULE_CHANNEL; j++ )
        {
            // Release all channel.
            chn = g_edma->chn[j];
            if( chn )
            {
                EDMA_DRV_ReleaseChannel( chn );
            }

            // Enable channel interrupt ID.
            irqNumber = g_edmaIrqId[i][j];
            NVIC_IntDisable( irqNumber );
        }

        // Disable edma clock gate.
        CLOCK_SYS_DisableDmaClock( i );
    }

    // Disable dmamux clock gate.
    for( i = 0; i < DMAMUX_INSTANCE_COUNT; i++ )
    {
        CLOCK_SYS_DisableDmamuxClock( i );
    }

    OSA_MutexDestroy( &g_edma->lock );

    g_edma = NULL;

    return kStatus_EDMA_Success;
}

// eDMA peripheral driver channel management functions

// Requests an eDMA channel dynamically or statically.
uint8_t EDMA_DRV_RequestChannel(
    uint8_t channel, dma_request_source_t source, edma_chn_state_t *chn )
{

    // Check if dynamic allocation is requested
    if( channel == kEDMAAnyChannel )
    {
        uint32_t i = 0, j;
        uint32_t map;
        map = ( ( uint32_t )source >> 8 );

        while( map != 0 )
        {
            if( map & ( 1U << i ) )
            {
                for( j = i * FSL_FEATURE_DMAMUX_MODULE_CHANNEL;
                     j < ( i + 1 ) * FSL_FEATURE_DMAMUX_MODULE_CHANNEL; j++ )
                {
                    EDMA_DRV_LOCK();
                    if ( !g_edma->chn[j] )
                    {
                        g_edma->chn[j] = chn;
                        EDMA_DRV_UNLOCK();
                        EDMA_DRV_ClaimChannel( j, source, chn );
                        return j;
                    }
                    EDMA_DRV_UNLOCK();
                }

            }
            map &= ~( 0x1U << i );
            i++;
        }

        // No available channel.
        return kEDMAInvalidChannel;
    }

    // static allocation
    EDMA_DRV_LOCK();
    if( !g_edma->chn[channel] )
    {
        g_edma->chn[channel] = chn;
        EDMA_DRV_UNLOCK();
        EDMA_DRV_ClaimChannel( channel, source, chn );
        return channel;
    }
    EDMA_DRV_UNLOCK();

    return kEDMAInvalidChannel;
}

// Releases an eDMA channel.
edma_status_t EDMA_DRV_ReleaseChannel( edma_chn_state_t *chn )
{
    uint32_t channel = chn->channel;
    uint32_t *edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE( channel );
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN( channel );

    if( !g_edma->chn[channel] )
    {
        return kStatus_EDMA_InvalidArgument;
    }

    // Stop edma channel.
    EDMA_HAL_SetDmaRequestCmd(
        edmaRegBase, ( edma_channel_indicator_t )edmaChannel, false );

    memset( chn, 0x0, sizeof( edma_chn_state_t ) );

    EDMA_DRV_LOCK();
    g_edma->chn[channel] = NULL;
    EDMA_DRV_UNLOCK();
    return kStatus_EDMA_Success;
}

// eDMA peripheral driver transfer setup functions

// Sets the descriptor basic transfer for the descriptor.
edma_status_t EDMA_DRV_PrepareDescriptorTransfer(
    edma_chn_state_t *chn, edma_software_tcd_t *stcd,
    edma_transfer_config_t *config,
    bool enableInt, bool disableDmaRequest )
{
    EDMA_HAL_STCDSetBasicTransfer(
        VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(chn->channel),
        stcd, config, enableInt, disableDmaRequest );
    return kStatus_EDMA_Success;
}

// Configures the memory address for the next transfer TCD for the software TCD.
edma_status_t EDMA_DRV_PrepareDescriptorScatterGather(
    edma_software_tcd_t *stcd, edma_software_tcd_t *nextStcd )
{
    EDMA_HAL_STCDSetScatterGatherLink( stcd, nextStcd );
    return kStatus_EDMA_Success;
}

// Configures the major channel link the software TCD.
edma_status_t EDMA_DRV_PrepareDescriptorChannelLink(
    edma_software_tcd_t *stcd, uint32_t linkChn )
{
    EDMA_HAL_STCDSetChannelMajorLink( stcd, linkChn, true );
    return kStatus_EDMA_Success;
}

// Copies the software TCD configuration to the hardware TCD.
edma_status_t EDMA_DRV_PushDescriptorToReg(
    edma_chn_state_t *chn, edma_software_tcd_t *stcd )
{
    uint32_t channel = chn->channel;
    uint32_t *edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE( channel );
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN( channel );

    EDMA_HAL_HTCDClearReg( edmaRegBase, edmaChannel );
    EDMA_HAL_PushSTCDToHTCD( edmaRegBase, edmaChannel, stcd );
    
    return kStatus_EDMA_Success;
}

// Configures the DMA transfer in a scatter-gather mode.
edma_status_t EDMA_DRV_ConfigLoopTransfer(
    edma_chn_state_t *chn, edma_software_tcd_t *stcd,
    edma_transfer_type_t type,
    uint32_t srcAddr, uint32_t destAddr, uint32_t size,
    uint32_t bytesOnEachRequest, uint32_t totalLength, uint8_t number )
{
    uint8_t i;
    edma_software_tcd_t *stcdAddr = ( edma_software_tcd_t* )STCD_ADDR( stcd );
    edma_transfer_size_t transfersize;
    edma_transfer_config_t config;

    if( !stcd ) return kStatus_EDMA_InvalidArgument;

    // Set the software TCD memory to default value.
    memset( stcdAddr, 0, number * sizeof( edma_software_tcd_t ) );

    // Translate the transfer size to eDMA allowed transfer size enum type.
    switch( size )
    {
        case 1:
            transfersize = kEDMATransferSize_1Bytes;
            break;
        case 2:
            transfersize = kEDMATransferSize_2Bytes;
            break;
        case 4:
            transfersize = kEDMATransferSize_4Bytes;
            break;
        case 16:
            transfersize = kEDMATransferSize_16Bytes;
            break;
        case 32:
            transfersize = kEDMATransferSize_32Bytes;
            break;
        default:
            return kStatus_EDMA_InvalidArgument;
    }

    // Configure the software TCD one by one.
    config.srcLastAddrAdjust = 0;
    config.destLastAddrAdjust = 0;
    config.srcModulo = kEDMAModuloDisable;
    config.destModulo = kEDMAModuloDisable;
    config.srcTransferSize = transfersize;
    config.destTransferSize = transfersize;
    config.minorLoopCount = bytesOnEachRequest;
    config.majorLoopCount = totalLength / (bytesOnEachRequest * number);
    for( i = 0; i < number; i++ )
    {
        switch( type )
        {
            case kEDMAPeripheralToMemory:
                // Configure Source Read.
                config.srcAddr = srcAddr;
                config.srcOffset = 0;

                // Configure Dest Write.
                config.destAddr = destAddr + i * ( totalLength / number );
                config.destOffset = size;
                break;
                
            case kEDMAMemoryToPeripheral:
                // Configure Source Read.
                config.srcAddr = srcAddr + i * ( totalLength / number );
                config.srcOffset = size;

                // Configure Dest Write.
                config.destAddr = destAddr;
                config.destOffset = 0;
                break;
                
            case kEDMAMemoryToMemory:
                // Configure Source Read.
                config.srcAddr = srcAddr + i * ( totalLength / number );
                config.srcOffset = size;

                // Configure Dest Write.
                config.destAddr = destAddr + i * ( totalLength / number );
                config.destOffset = size;
                break;
                
            default:
                return kStatus_EDMA_InvalidArgument;
        }

        EDMA_DRV_PrepareDescriptorTransfer(
            chn, &stcdAddr[i], &config, true, false );
        EDMA_DRV_PrepareDescriptorScatterGather(
            &stcdAddr[i], &stcdAddr[ ( i + 1 ) % number ] );
    }

    EDMA_DRV_PushDescriptorToReg( chn, &stcdAddr[0] );

    return kStatus_EDMA_Success;
}

// Configures the DMA transfer in a scatter-gather mode.
edma_status_t EDMA_DRV_ConfigScatterGatherTransfer(
    edma_chn_state_t *chn, edma_software_tcd_t *stcd,
    edma_transfer_type_t type,
    uint32_t size, uint32_t bytesOnEachRequest,
    edma_scatter_gather_list_t *srcList, edma_scatter_gather_list_t *destList,
    uint8_t number )
{
    uint8_t i;
    edma_transfer_size_t transfersize;
    edma_software_tcd_t *stcdAddr = ( edma_software_tcd_t* )STCD_ADDR( stcd );
    edma_transfer_config_t config;
    
    if( !stcd ) return kStatus_EDMA_InvalidArgument;

    if( number > 1 )
    {
        memset( stcdAddr, 0, number * sizeof( edma_software_tcd_t ) );
    }

    switch( size )
    {
        case 1:
            transfersize = kEDMATransferSize_1Bytes;
            break;
        case 2:
            transfersize = kEDMATransferSize_2Bytes;
            break;
        case 4:
            transfersize = kEDMATransferSize_4Bytes;
            break;
        case 16:
            transfersize = kEDMATransferSize_16Bytes;
            break;
        case 32:
            transfersize = kEDMATransferSize_32Bytes;
            break;
        default:
            return kStatus_EDMA_InvalidArgument;
    }

    // Configure the software TCD one by one.
    config.srcLastAddrAdjust = 0;
    config.destLastAddrAdjust = 0;
    config.srcModulo = kEDMAModuloDisable;
    config.destModulo = kEDMAModuloDisable;
    config.srcTransferSize = transfersize;
    config.destTransferSize = transfersize;
    config.minorLoopCount = bytesOnEachRequest;

    for( i = 0; i < number; i++ )
    {
        config.srcAddr = srcList[i].address;
        config.destAddr = destList[i].address;
        if( srcList[i].length != destList[i].length )
        {
            return kStatus_EDMA_InvalidArgument;
        }
        config.majorLoopCount = srcList[i].length / bytesOnEachRequest;

        switch( type )
        {
            case kEDMAPeripheralToMemory:
                // Configure Source Read.
                config.srcOffset = 0;

                // Configure Dest Write.
                config.destOffset = size;
                break;
                
            case kEDMAMemoryToPeripheral:
                // Configure Source Read.
                config.srcOffset = size;

                // Configure Dest Write.
                config.destOffset = 0;
                break;
                
            case kEDMAMemoryToMemory:
                // Configure Source Read.
                config.srcOffset = size;

                // Configure Dest Write.
                config.destOffset = size;
                break;
                
            default:
                return kStatus_EDMA_InvalidArgument;
        }

        if( number == 1 )
        {
            // If only one TCD is required, only hardware TCD is required
            // and user is not required to prepare the software TCD memory.
            edma_software_tcd_t temp[2];
            edma_software_tcd_t *tempTCD = STCD_ADDR( temp );
            memset( ( void* )tempTCD, 0, sizeof( edma_software_tcd_t ) );
            EDMA_DRV_PrepareDescriptorTransfer(
                chn, tempTCD, &config, true, true );
            EDMA_DRV_PushDescriptorToReg( chn, tempTCD );
        }
        else if( i == ( number - 1 ) )
        {
            EDMA_DRV_PrepareDescriptorTransfer( 
                chn, &stcdAddr[i], &config, true, true );
            EDMA_DRV_PushDescriptorToReg( chn, &stcdAddr[0] );
        }
        else
        {
            EDMA_DRV_PrepareDescriptorTransfer(
                chn, &stcdAddr[i], &config, false, false );
            EDMA_DRV_PrepareDescriptorScatterGather(
                &stcdAddr[i], &stcdAddr[ i + 1 ] );
        }
    }

    return kStatus_EDMA_Success;
}

// eDMA Peripheral driver channel operation functions

// Starts an eDMA channel.
edma_status_t EDMA_DRV_StartChannel( edma_chn_state_t *chn )
{
    uint32_t channel = chn->channel;
    uint32_t *edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE( channel );
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN( channel );

    EDMA_HAL_SetDmaRequestCmd(
        edmaRegBase, ( edma_channel_indicator_t )edmaChannel, true );
        
    return kStatus_EDMA_Success;
}

// Stops the eDMA channel.
edma_status_t EDMA_DRV_StopChannel( edma_chn_state_t *chn )
{
    uint32_t channel = chn->channel;
    uint32_t *edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE( channel );
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN( channel );

    EDMA_HAL_SetDmaRequestCmd(
        edmaRegBase, (edma_channel_indicator_t)edmaChannel, false );

    return kStatus_EDMA_Success;
}

// eDMA Peripheral callback and interrupt functions

// Registers the callback function and the parameter for eDMA channel.
edma_status_t EDMA_DRV_InstallCallback(
    edma_chn_state_t *chn, edma_callback_t callback, void *parameter )
{
    chn->callback = callback;
    chn->parameter = parameter;

    return kStatus_EDMA_Success;
}

// IRQ Handler for eDMA channel interrupt.
void EDMA_DRV_IRQHandler( uint8_t channel )
{
    edma_chn_state_t *chn = g_edma->chn[channel];

    if( !chn )
    {
        return;
    }

    EDMA_DRV_ClearIntStatus( channel );

    if( chn->callback )
    {
        chn->callback( chn->parameter, chn->status );
    }
}

// ERROR IRQ Handler for eDMA channel interrupt.
void EDMA_DRV_ErrorIRQHandler( uint8_t instance )
{
    uint32_t channel, error, j;
    uint32_t *edmaRegBase = g_edmaBase[ instance ];
    edma_chn_state_t *chn;
    
    j = 0;

    error = EDMA_HAL_GetErrorIntStatusFlag( edmaRegBase );

    while( error && ( j < FSL_FEATURE_EDMA_MODULE_CHANNEL ) )
    {
        if( error & 1U )
        {
            channel = instance * FSL_FEATURE_EDMA_MODULE_CHANNEL + j;
            EDMA_HAL_SetDmaRequestCmd(
                edmaRegBase, ( edma_channel_indicator_t )j, false );
            chn = g_edma->chn[channel];
            if( chn )
            {
                EDMA_DRV_ClearIntStatus( channel );
                chn->status = kEDMAChnError;
                if( chn->callback )
                {
                    chn->callback( chn->parameter, chn->status );
                }
            }
        }
        error = error >> 1U;
        j++;
    }
    EDMA_HAL_SetHaltCmd( edmaRegBase, false );
}

// eDMA Peripheral driver miscellaneous functions

// Gets the eDMA channel status.
edma_chn_status_t EDMA_DRV_GetChannelStatus( edma_chn_state_t *chn )
{
    return chn->status;
}

// Gets the unfinished bytes for the eDMA channel current TCD.
uint32_t EDMA_DRV_GetUnfinishedBytes( edma_chn_state_t *chn )
{
    uint32_t channel = chn->channel;

    return EDMA_HAL_HTCDGetUnfinishedBytes(
        VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE( channel ),
        VIRTUAL_CHN_TO_EDMA_CHN( channel ) );
}

// Gets the bytes already transferred for the eDMA channel current TCD.
uint32_t EDMA_DRV_GetFinishedBytes( edma_chn_state_t *chn )
{
    uint32_t channel = chn->channel;

    return EDMA_HAL_HTCDGetFinishedBytes(
        VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE( channel ),
        VIRTUAL_CHN_TO_EDMA_CHN( channel ) );
}