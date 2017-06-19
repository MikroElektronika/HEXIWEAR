// File: edma_hal.h

// Declarations of main functionalities in the eDMA HAL module.

#ifndef _edma_hal_h_
#define _edma_hal_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define DMA_BASE                                 ( 0x40008000u )

// Array initializer of DMA peripheral base addresses
#define DMA_BASE_ADDRS                           { DMA_BASE }
// Interrupt vectors for the DMA peripheral type
#define DMA_CHN_IRQS {                                                         \
    IVT_INT_DMA0, IVT_INT_DMA1, IVT_INT_DMA2, IVT_INT_DMA3,                    \
    IVT_INT_DMA4, IVT_INT_DMA5, IVT_INT_DMA6, IVT_INT_DMA7,                    \
    IVT_INT_DMA8, IVT_INT_DMA9, IVT_INT_DMA10, IVT_INT_DMA11,                  \
    IVT_INT_DMA12, IVT_INT_DMA13, IVT_INT_DMA14, IVT_INT_DMA15 }

#define DMA_ERROR_IRQS { IVT_INT_DMA_Error }

// Number of DMA channels
// (related to number of registers TCD, DCHPRI, bit fields ERQ[ERQn], EEI[EEIn],
// INT[INTn], ERR[ERRn], HRS[HRSn] and bit field widths ES[ERRCHN], CEEI[CEEI],
// SEEI[SEEI], CERQ[CERQ], SERQ[SERQ], CDNE[CDNE], SSRT[SSRT], CERR[CERR],
// CINT[CINT], TCDn_CITER_ELINKYES[LINKCH], TCDn_CSR[MAJORLINKCH],
// TCDn_BITER_ELINKYES[LINKCH]). (Valid only for eDMA modules.)
#define FSL_FEATURE_EDMA_MODULE_CHANNEL (16)
// Total number of DMA channels on all modules.
#define FSL_FEATURE_EDMA_DMAMUX_CHANNELS (DMA_INSTANCE_COUNT * 16)
// Number of DMA channel groups
// (register bit fields CR[ERGA], CR[GRPnPRI], ES[GPE], DCHPRIn[GRPPRI]).
// (Valid only for eDMA modules.)
#define FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT (1)
// Number of DMA channels with asynchronous request capability (register EARS).
// (Valid only for eDMA modules.)
#define FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT (0)

// Number of instances of the DMA module.
#define DMA_INSTANCE_COUNT (1U)
// Instance number for DMA.
#define DMA_IDX (0U)

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////
 
// Error code for the eDMA Driver.
typedef enum _edma_status {
    kStatus_EDMA_Success = 0U,
    kStatus_EDMA_InvalidArgument = 1U,  // Parameter is invalid.
    kStatus_EDMA_Fail = 2U              // Failed operation.
} edma_status_t;

// eDMA channel arbitration algorithm used for selection among channels.
typedef enum _edma_channel_arbitration {
    // Fixed Priority arbitration is used for selection among channels.
    kEDMAChnArbitrationFixedPriority = 0U,
    // Round-Robin arbitration is used for selection among channels.
    kEDMAChnArbitrationRoundrobin
} edma_channel_arbitration_t;

// eDMA channel priority setting
typedef enum _edma_chn_priority {
    kEDMAChnPriority0 = 0U,
    kEDMAChnPriority1,
    kEDMAChnPriority2,
    kEDMAChnPriority3,
    kEDMAChnPriority4,
    kEDMAChnPriority5,
    kEDMAChnPriority6,
    kEDMAChnPriority7,
    kEDMAChnPriority8,
    kEDMAChnPriority9,
    kEDMAChnPriority10,
    kEDMAChnPriority11,
    kEDMAChnPriority12,
    kEDMAChnPriority13,
    kEDMAChnPriority14,
    kEDMAChnPriority15
} edma_channel_priority_t;

// eDMA modulo configuration
typedef enum _edma_modulo {
    kEDMAModuloDisable = 0U,
    kEDMAModulo2bytes,
    kEDMAModulo4bytes,
    kEDMAModulo8bytes,
    kEDMAModulo16bytes,
    kEDMAModulo32bytes,
    kEDMAModulo64bytes,
    kEDMAModulo128bytes,
    kEDMAModulo256bytes,
    kEDMAModulo512bytes,
    kEDMAModulo1Kbytes,
    kEDMAModulo2Kbytes,
    kEDMAModulo4Kbytes,
    kEDMAModulo8Kbytes,
    kEDMAModulo16Kbytes,
    kEDMAModulo32Kbytes,
    kEDMAModulo64Kbytes,
    kEDMAModulo128Kbytes,
    kEDMAModulo256Kbytes,
    kEDMAModulo512Kbytes,
    kEDMAModulo1Mbytes,
    kEDMAModulo2Mbytes,
    kEDMAModulo4Mbytes,
    kEDMAModulo8Mbytes,
    kEDMAModulo16Mbytes,
    kEDMAModulo32Mbytes,
    kEDMAModulo64Mbytes,
    kEDMAModulo128Mbytes,
    kEDMAModulo256Mbytes,
    kEDMAModulo512Mbytes,
    kEDMAModulo1Gbytes,
    kEDMAModulo2Gbytes
} edma_modulo_t;

// eDMA transfer configuration
typedef enum _edma_transfer_size {
    kEDMATransferSize_1Bytes = 0x0U,
    kEDMATransferSize_2Bytes = 0x1U,
    kEDMATransferSize_4Bytes = 0x2U,
    kEDMATransferSize_16Bytes = 0x4U,
    kEDMATransferSize_32Bytes = 0x5U
} edma_transfer_size_t;

// eDMA transfer size configuration.

// This structure configures the basic source/destination transfer attribute.
// This figure shows the eDMA's transfer model:
//  _________________________________________________
//              | Transfer Size |                    |
//   Minor Loop |_______________| Major loop Count 1 |
//     Count    | Transfer Size |                    |
//  ____________|_______________|____________________|--> Minor loop complete
//               ____________________________________
//              |               |                    |
//              |_______________| Major Loop Count 2 |
//              |               |                    |
//              |_______________|____________________|--> Minor loop  Complete
//
// -----------------------------------------------------> Major loop complete

typedef struct EDMATransferConfig {
    uint32_t srcAddr;       // Memory address pointing to the source data.
    uint32_t destAddr;      // Memory address pointing to the destination data.
    edma_transfer_size_t srcTransferSize;   // Source data transfer size.
    edma_transfer_size_t destTransferSize;  // Destination data transfer size.
    int16_t srcOffset;      // Sign-extended offset applied to the current
                            // source address to form the next-state value as
                            // each source read/write is completed.
    int16_t destOffset;
    uint32_t srcLastAddrAdjust;  // Last source address adjustment.
    uint32_t destLastAddrAdjust; // Last destination address adjustment.
                                 // Note here it is only valid when
                                 // scatter/gather feature is not enabled.
    edma_modulo_t srcModulo;     // Source address modulo.
    edma_modulo_t destModulo;    // Destination address modulo.
    uint32_t minorLoopCount;     // Minor bytes transfer count. Number of bytes
                                 // to be transferred in each service request
                                 // of the channel.
    uint16_t majorLoopCount;     // Major iteration count.
} edma_transfer_config_t;

// eDMA channel configuration.
typedef enum _edma_channel_indicator {
    kEDMAChannel0 = 0U,     // Channel 0.
    kEDMAChannel1 = 1U,
    kEDMAChannel2 = 2U,
    kEDMAChannel3 = 3U,
    kEDMAChannel4 = 4U,
    kEDMAChannel5 = 5U,
    kEDMAChannel6 = 6U,
    kEDMAChannel7 = 7U,
    kEDMAChannel8 = 8U,
    kEDMAChannel9 = 9U,
    kEDMAChannel10 = 10U,
    kEDMAChannel11 = 11U,
    kEDMAChannel12 = 12U,
    kEDMAChannel13 = 13U,
    kEDMAChannel14 = 14U,
    kEDMAChannel15 = 15U,
    kEDMAAllChannel = 64U
} edma_channel_indicator_t;

// eDMA TCD Minor loop mapping configuration
typedef struct EDMAMinorLoopOffsetConfig {
    // Enable(true) or Disable(false) source minor loop offset.
    bool enableSrcMinorloop;
    // Enable(true) or Disable(false) destination minor loop offset.
    bool enableDestMinorloop;
    // Offset for minor loop mapping.
    uint32_t offset;
} edma_minorloop_offset_config_t;

// Error status of the eDMA module
typedef struct EDMAErrorStatusAll {
    // Error channel number of the cancelled channel number
    uint8_t errorChannel;
    // Bus error on destination address
    bool destinationBusError;
    // Bus error on the SRC address
    bool sourceBusError;
    // Error on the Scatter/Gather address
    bool scatterOrGatherConfigurationError;
    // NBYTES/CITER configuration error
    bool nbyteOrCiterConfigurationError;
    // Destination offset error
    bool destinationOffsetError;
    // Destination address error
    bool destinationAddressError;
    // Source offset error
    bool sourceOffsetError;
    // Source address error
    bool sourceAddressError;
    // Channel priority error
    bool channelPriorityError;
    // Transfer cancelled
    bool transferCancelledError;
    // Logical OR  all ERR status bits
    bool orOfAllError;
} edma_error_status_all_t;

// Bandwidth control configuration
typedef enum _edma_bandwidth_config {
    // No eDMA engine stalls.
    kEDMABandwidthStallNone = 0U,
    // eDMA engine stalls for 4 cycles after each read/write.
    kEDMABandwidthStall4Cycle = 2U,
    // eDMA engine stalls for 8 cycles after each read/write.
    kEDMABandwidthStall8Cycle = 3U
} edma_bandwidth_config_t;

// eDMA TCD
typedef struct EDMASoftwareTcd {
    uint32_t SADDR;
    uint16_t SOFF;
    uint16_t ATTR;
    uint32_t NBYTES;
    uint32_t SLAST;
    uint32_t DADDR;
    uint16_t DOFF;
    uint16_t CITER;
    uint32_t DLAST_SGA;
    uint16_t CSR;
    uint16_t BITER;
} edma_software_tcd_t;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// eDMA HAL driver module level operation

// Initializes eDMA module to known state.
void EDMA_HAL_Init( uint32_t* base );

// Cancels the remaining data transfer.
void EDMA_HAL_CancelTransfer( uint32_t* base );

// Cancels the remaining data transfer and treats it as an error condition.
void EDMA_HAL_ErrorCancelTransfer( uint32_t* base );

// Halts/Un-halts the DMA Operations.
void EDMA_HAL_SetHaltCmd( uint32_t* base, bool halt );

// Halts or does not halt the eDMA module when an error occurs.
void EDMA_HAL_SetHaltOnErrorCmd( uint32_t* base, bool haltOnError );

// Enables/Disables the eDMA DEBUG mode.
void EDMA_HAL_SetDebugCmd( uint32_t* base, bool enable );

// eDMA HAL driver channel priority and arbitration configuration.

// Sets the preempt and preemption feature for the eDMA channel.
void EDMA_HAL_SetChannelPreemptMode( uint32_t* base,
    uint32_t channel, bool preempt, bool preemption );

// Sets the eDMA channel priority.
void EDMA_HAL_SetChannelPriority( uint32_t* base,
    uint32_t channel, edma_channel_priority_t priority );

// Sets the channel arbitration algorithm.
void EDMA_HAL_SetChannelArbitrationMode( uint32_t* base,
    edma_channel_arbitration_t channelArbitration );

// eDMA HAL driver configuration and operation.

// Enables/Disables the minor loop mapping.
void EDMA_HAL_SetMinorLoopMappingCmd( uint32_t* base, bool enable );

// Enables or disables the continuous transfer mode.
void EDMA_HAL_SetContinuousLinkCmd( uint32_t* base, bool continuous );

// Gets the error status of the eDMA module.
edma_error_status_all_t EDMA_HAL_GetErrorStatus( uint32_t* base );

// Enables/Disables the error interrupt for channels.
void EDMA_HAL_SetErrorIntCmd( uint32_t* base,
    bool enable, edma_channel_indicator_t channel );

// Gets the eDMA error interrupt status.
uint32_t EDMA_HAL_GetErrorIntStatusFlag( uint32_t* base );

// Clears the error interrupt status for the eDMA channel or channels.
void EDMA_HAL_ClearErrorIntStatusFlag( uint32_t* base,
    edma_channel_indicator_t channel );

// Enables/Disables the DMA request for the channel or all channels.
void EDMA_HAL_SetDmaRequestCmd( uint32_t* base,
    edma_channel_indicator_t channel, bool enable );

// Gets the eDMA channel DMA request status.
bool EDMA_HAL_GetDmaRequestStatusFlag( uint32_t* base, uint32_t channel );

// Clears the done status for a channel or all channels.
void EDMA_HAL_ClearDoneStatusFlag( uint32_t* base,
    edma_channel_indicator_t channel );
    
// Triggers the eDMA channel.
void EDMA_HAL_TriggerChannelStart( uint32_t* base,
    edma_channel_indicator_t channel );

// Gets the eDMA channel interrupt request status.
bool EDMA_HAL_GetIntStatusFlag( uint32_t* base, uint32_t channel );

// Clears the interrupt status for the eDMA channel or all channels.
void EDMA_HAL_ClearIntStatusFlag( uint32_t* base,
    edma_channel_indicator_t channel );

// eDMA HAL driver hardware TCD configuration functions.

// Clears all registers to 0 for the hardware TCD.
void EDMA_HAL_HTCDClearReg( uint32_t* base, uint32_t channel );

// Configures the source address for the hardware TCD.
void EDMA_HAL_HTCDSetSrcAddr( uint32_t* base,
    uint32_t channel, uint32_t address );

// Configures the source address signed offset for the hardware TCD.
void EDMA_HAL_HTCDSetSrcOffset( uint32_t* base,
    uint32_t channel, int16_t offset );

// Configures the transfer attribute for the eDMA channel.
void EDMA_HAL_HTCDSetAttribute( uint32_t* base, uint32_t channel,
    edma_modulo_t srcModulo, edma_modulo_t destModulo,
    edma_transfer_size_t srcTransferSize,
    edma_transfer_size_t destTransferSize );

// Configures the nbytes for the eDMA channel.
void EDMA_HAL_HTCDSetNbytes( uint32_t* base,
    uint32_t channel, uint32_t nbytes );

// Gets the nbytes configuration data for the hardware TCD.
uint32_t EDMA_HAL_HTCDGetNbytes( uint32_t* base, uint32_t channel );

// Configures the minor loop offset for the hardware TCD.
void EDMA_HAL_HTCDSetMinorLoopOffset( uint32_t* base,
    uint32_t channel, edma_minorloop_offset_config_t *config );

// Configures the last source address adjustment for the hardware TCD.
void EDMA_HAL_HTCDSetSrcLastAdjust( uint32_t* base,
    uint32_t channel, int32_t size );

// Configures the destination address for the hardware TCD.
void EDMA_HAL_HTCDSetDestAddr( uint32_t* base,
    uint32_t channel, uint32_t address );

// Configures the destination address signed offset for the hardware TCD.
void EDMA_HAL_HTCDSetDestOffset( uint32_t* base,
    uint32_t channel, int16_t offset );

// Configures the last source address adjustment.
void EDMA_HAL_HTCDSetDestLastAdjust( uint32_t* base,
    uint32_t channel, uint32_t adjust );

// Configures the memory address for the next transfer TCD for the hardware TCD.
void EDMA_HAL_HTCDSetScatterGatherLink( uint32_t* base,
    uint32_t channel, edma_software_tcd_t *stcd );

// Configures the bandwidth for the hardware TCD.
void EDMA_HAL_HTCDSetBandwidth( uint32_t* base,
    uint32_t channel, edma_bandwidth_config_t bandwidth );
    
// Configures the major channel link the hardware TCD.
void EDMA_HAL_HTCDSetChannelMajorLink( uint32_t* base,
    uint32_t channel, uint32_t majorChannel, bool enable );

// Enables/Disables the scatter/gather feature for the hardware TCD.
void EDMA_HAL_HTCDSetScatterGatherCmd( uint32_t* base,
    uint32_t channel, bool enable );

// Disables/Enables the DMA request
// after the major loop completes for the hardware TCD.
void EDMA_HAL_HTCDSetDisableDmaRequestAfterTCDDoneCmd( uint32_t* base,
    uint32_t channel, bool disable );

// Enables/Disables the half complete interrupt for the hardware TCD.
void EDMA_HAL_HTCDSetHalfCompleteIntCmd( uint32_t* base,
    uint32_t channel, bool enable );

// Enables/Disables the interrupt
// after the major loop completes for the hardware TCD.
void EDMA_HAL_HTCDSetIntCmd( uint32_t* base, uint32_t channel, bool enable );

// Triggers the start bits for the hardware TCD.
void EDMA_HAL_HTCDTriggerChannelStart( uint32_t* base, uint32_t channel );

// Checks whether the channel is running for the hardware TCD.
bool EDMA_HAL_HTCDGetChannelActiveStatus( uint32_t* base, uint32_t channel );

// Sets the channel minor link for the hardware TCD.
void EDMA_HAL_HTCDSetChannelMinorLink( uint32_t* base,
    uint32_t channel, uint32_t linkChannel, bool enable );

// Sets the major iteration count according to minor loop channel link setting.
void EDMA_HAL_HTCDSetMajorCount( uint32_t* base,
    uint32_t channel, uint32_t count );

// Gets the number of bytes already transferred for the hardware TCD.
uint32_t EDMA_HAL_HTCDGetFinishedBytes( uint32_t* base,
    uint32_t channel );

// Gets the number of bytes haven't transferred for the hardware TCD.
uint32_t EDMA_HAL_HTCDGetUnfinishedBytes( uint32_t* base, uint32_t channel );

// Gets the channel done status.
bool EDMA_HAL_HTCDGetDoneStatusFlag( uint32_t* base, uint32_t channel );

// EDMA HAL driver software TCD configuration functions.

// Configures the source address for the software TCD.
void EDMA_HAL_STCDSetSrcAddr( edma_software_tcd_t *stcd, uint32_t address );

// Configures the source address signed offset for the software TCD.
void EDMA_HAL_STCDSetSrcOffset( edma_software_tcd_t *stcd, int16_t offset );

// Configures the transfer attribute for software TCD.
void EDMA_HAL_STCDSetAttribute( edma_software_tcd_t *stcd,
    edma_modulo_t srcModulo, edma_modulo_t destModulo,
    edma_transfer_size_t srcTransferSize,
    edma_transfer_size_t destTransferSize );

// Configures the nbytes for software TCD.
void EDMA_HAL_STCDSetNbytes( uint32_t* base,
    edma_software_tcd_t *stcd, uint32_t nbytes );

// Configures the minorloop offset for the software TCD.
void EDMA_HAL_STCDSetMinorLoopOffset( uint32_t* base,
    edma_software_tcd_t *stcd, edma_minorloop_offset_config_t *config );

// Configures the last source address adjustment for the software TCD.
void EDMA_HAL_STCDSetSrcLastAdjust( edma_software_tcd_t *stcd, int32_t size );

// Configures the destination address for the software TCD.
void EDMA_HAL_STCDSetDestAddr( edma_software_tcd_t *stcd, uint32_t address );

// Configures the destination address signed offset for the software TCD.
void EDMA_HAL_STCDSetDestOffset( edma_software_tcd_t *stcd, int16_t offset );

// Configures the last source address adjustment.
void EDMA_HAL_STCDSetDestLastAdjust(
    edma_software_tcd_t *stcd, uint32_t adjust );

// Configures the memory address for the next transfer TCD for the software TCD.
void EDMA_HAL_STCDSetScatterGatherLink(
    edma_software_tcd_t *stcd, edma_software_tcd_t *nextStcd );

// Configures the bandwidth for the software TCD.
void EDMA_HAL_STCDSetBandwidth(
    edma_software_tcd_t *stcd, edma_bandwidth_config_t bandwidth );

// Configures the major channel link the software TCD.
void EDMA_HAL_STCDSetChannelMajorLink(
    edma_software_tcd_t *stcd, uint32_t majorChannel, bool enable );

// Enables/Disables the scatter/gather feature for the software TCD.
void EDMA_HAL_STCDSetScatterGatherCmd(
    edma_software_tcd_t *stcd, bool enable );

// Disables/Enables the DMA request
// after the major loop completes for the software TCD.
void EDMA_HAL_STCDSetDisableDmaRequestAfterTCDDoneCmd(
    edma_software_tcd_t *stcd, bool disable );

// Enables/Disables the half complete interrupt for the software TCD.
void EDMA_HAL_STCDSetHalfCompleteIntCmd(
    edma_software_tcd_t *stcd, bool enable );

// Enables/Disables the interrupt
// after the major loop completes for the software TCD.
void EDMA_HAL_STCDSetIntCmd( edma_software_tcd_t *stcd, bool enable );

// Triggers the start bits for the software TCD.
void EDMA_HAL_STCDTriggerChannelStart( edma_software_tcd_t *stcd );

// Set Channel minor link for software TCD.
void EDMA_HAL_STCDSetChannelMinorLink(
    edma_software_tcd_t *stcd, uint32_t linkChannel, bool enable );

// Sets the major iteration count according to minor loop channel link setting.
void EDMA_HAL_STCDSetMajorCount( edma_software_tcd_t *stcd, uint32_t count );

// Copy the software TCD configuration to the hardware TCD.
void EDMA_HAL_PushSTCDToHTCD( uint32_t* base,
    uint32_t channel, edma_software_tcd_t *stcd );

// Set the basic transfer for software TCD.
edma_status_t EDMA_HAL_STCDSetBasicTransfer( uint32_t* base,
    edma_software_tcd_t *stcd, edma_transfer_config_t *config,
    bool enableInt, bool disableDmaRequest );

#endif