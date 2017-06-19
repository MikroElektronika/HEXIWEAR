// File: edma_driver.h

// Declarations of main functionalities in the eDMA module.

#ifndef _edma_driver_h_
#define _edma_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "edma_request.h"
#include "edma_hal.h"
#include "dmamux_hal.h"
#include "OSA.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define STCD_SIZE(number)           ( ( number + 1 ) * 32 )
#define STCD_ADDR(address)                                                     \
    ( edma_software_tcd_t* )( ( ( uint32_t )address + 32 ) & ~0x1FU )
    
// Macro to get the eDMA physical module indicator
// from the virtual channel indicator.
#define VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE( channel )                          \
    g_edmaBase[ channel / FSL_FEATURE_EDMA_MODULE_CHANNEL ]

// Macro to get the eDMA physical channel indicator
// from the virtual channel indicator.
#define VIRTUAL_CHN_TO_EDMA_CHN( channel )                                     \
    ( channel % FSL_FEATURE_EDMA_MODULE_CHANNEL )

// Macro to get the DMAMUX physical module indicator
// from the virtual channel indicator.
#define VIRTUAL_CHN_TO_DMAMUX_MODULE_REGBASE( channel )                        \
    g_dmamuxBase[ channel / FSL_FEATURE_DMAMUX_MODULE_CHANNEL ]

// to get the DMAMUX physical channel indicator
// from the virtual channel indicator.
#define VIRTUAL_CHN_TO_DMAMUX_CHN( channel )                                   \
    ( channel % FSL_FEATURE_DMAMUX_MODULE_CHANNEL )

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// The user configuration structure for the eDMA driver.
typedef struct EDMAUserConfig {
    // eDMA channel arbitration.
    edma_channel_arbitration_t chnArbitration;
    //  Any error causes the HALT bit to set.
    // Subsequently, all service requests are ignored
    // until the HALT bit is cleared.
    bool notHaltOnError;
} edma_user_config_t;

// Channel status for eDMA channel.
typedef enum _edma_chn_status {
    kEDMAChnNormal = 0U,           // eDMA channel is occupied.
    kEDMAChnIdle,                  // eDMA channel is idle.
    kEDMAChnError                  // An error occurs in the eDMA channel.
} edma_chn_status_t;

// Definition for the eDMA channel callback function.
typedef void ( *edma_callback_t )( void *parameter, edma_chn_status_t status );

// Data structure for the eDMA channel.
typedef struct EDMAChnState {
    // Virtual channel indicator.
    uint8_t channel;
    // Callback function pointer for the eDMA channel.
    // It will be called at the eDMA channel complete and eDMA channel error.
    edma_callback_t callback;
    // Parameter for the callback function pointer.
    void *parameter;
    // eDMA channel status.
    volatile edma_chn_status_t status;
} edma_chn_state_t;

// Enum type for channel allocation.
typedef enum _edma_chn_state_type {
    // Macros indicate the failure of the channel request.
    kEDMAInvalidChannel = 0xFFU,
    // Macros used when requesting channel dynamically.
    kEDMAAnyChannel = 0xFEU
} edma_chn_state_type_t;

// A type for the DMA transfer.
typedef enum _edma_transfer_type {
    kEDMAPeripheralToMemory,        // Transfer from peripheral to memory
    kEDMAMemoryToPeripheral,        // Transfer from memory to peripheral
    kEDMAMemoryToMemory,            // Transfer from memory to memory
} edma_transfer_type_t;

// Data structure for configuring a discrete memory transfer.
typedef struct EDMAScatterGatherList {
    uint32_t address;           // Address of buffer.
    uint32_t length;            // Length of buffer.
} edma_scatter_gather_list_t;

// Runtime state structure for the eDMA driver.
typedef struct EDMAState {
    // Lock for channel allocation and release.
    mutex_t lock;
    // Pointer array storing channel state.
    edma_chn_state_t* volatile chn[ FSL_FEATURE_EDMA_DMAMUX_CHANNELS ];
} edma_state_t;

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// @brief Array for the eDMA module register base address. */
extern uint32_t* const g_edmaBase[];

// @brief Array for DMAMUX module register base address. */
extern uint32_t* const g_dmamuxBase[];

// @brief Two dimensional array for eDMA channel interrupt vector number. */
extern const uint32_t g_edmaIrqId
    [ DMA_INSTANCE_COUNT ][ FSL_FEATURE_EDMA_MODULE_CHANNEL ];

// @brief Array for eDMA module's error interrupt vector number. */
extern const uint32_t g_edmaErrIrqId[ DMA_INSTANCE_COUNT ];

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// eDMA peripheral driver module level functions

// Initializes all eDMA modules in an SOC.
edma_status_t EDMA_DRV_Init(
    edma_state_t *edmaState, const edma_user_config_t *userConfig );
    
// Shuts down all eDMA modules.
edma_status_t EDMA_DRV_Deinit();

// eDMA peripheral driver channel management functions

// Requests an eDMA channel dynamically or statically.
uint8_t EDMA_DRV_RequestChannel(
    uint8_t channel, dma_request_source_t source, edma_chn_state_t *chn );
    
// Releases an eDMA channel.
edma_status_t EDMA_DRV_ReleaseChannel( edma_chn_state_t *chn );

// eDMA peripheral driver transfer setup functions

// Sets the descriptor basic transfer for the descriptor.
edma_status_t EDMA_DRV_PrepareDescriptorTransfer(
    edma_chn_state_t *chn, edma_software_tcd_t *stcd,
    edma_transfer_config_t *config,
    bool enableInt, bool disableDmaRequest );

// Configures the memory address for the next transfer TCD for the software TCD.
edma_status_t EDMA_DRV_PrepareDescriptorScatterGather(
    edma_software_tcd_t *stcd, edma_software_tcd_t *nextStcd );

// Configures the major channel link the software TCD.
edma_status_t EDMA_DRV_PrepareDescriptorChannelLink(
    edma_software_tcd_t *stcd, uint32_t linkChn );

// Copies the software TCD configuration to the hardware TCD.
edma_status_t EDMA_DRV_PushDescriptorToReg(
    edma_chn_state_t *chn, edma_software_tcd_t *stcd );

// Configures the DMA transfer in a scatter-gather mode.
edma_status_t EDMA_DRV_ConfigLoopTransfer(
    edma_chn_state_t *chn, edma_software_tcd_t *stcd,
    edma_transfer_type_t type,
    uint32_t srcAddr, uint32_t destAddr, uint32_t size,
    uint32_t bytesOnEachRequest, uint32_t totalLength, uint8_t number );

// Configures the DMA transfer in a scatter-gather mode.
edma_status_t EDMA_DRV_ConfigScatterGatherTransfer(
    edma_chn_state_t *chn, edma_software_tcd_t *stcd,
    edma_transfer_type_t type,
    uint32_t size, uint32_t bytesOnEachRequest,
    edma_scatter_gather_list_t *srcList, edma_scatter_gather_list_t *destList,
    uint8_t number );

// eDMA Peripheral driver channel operation functions

// Starts an eDMA channel.
edma_status_t EDMA_DRV_StartChannel( edma_chn_state_t *chn );

// Stops the eDMA channel.
edma_status_t EDMA_DRV_StopChannel( edma_chn_state_t *chn );

// eDMA Peripheral callback and interrupt functions

// Registers the callback function and the parameter for eDMA channel.
edma_status_t EDMA_DRV_InstallCallback(
    edma_chn_state_t *chn, edma_callback_t callback, void *parameter );

// IRQ Handler for eDMA channel interrupt.
void EDMA_DRV_IRQHandler( uint8_t channel );
    
// ERROR IRQ Handler for eDMA channel interrupt.
void EDMA_DRV_ErrorIRQHandler( uint8_t instance );

// eDMA Peripheral driver miscellaneous functions

// Gets the eDMA channel status.
edma_chn_status_t EDMA_DRV_GetChannelStatus( edma_chn_state_t *chn );

// Gets the unfinished bytes for the eDMA channel current TCD.
uint32_t EDMA_DRV_GetUnfinishedBytes( edma_chn_state_t *chn );

// Gets the bytes already transferred for the eDMA channel current TCD.
uint32_t EDMA_DRV_GetFinishedBytes( edma_chn_state_t *chn );

#endif