/**HEADER********************************************************************
 *
 * Copyright (c) 2008, 2013 - 2015 Freescale Semiconductor;
 * All Rights Reserved
 *
 * Copyright (c) 1989-2008 ARC International;
 * All Rights Reserved
 *
 ***************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************
 *
 * $FileName: usb_cdc_pstn.h$
 * $Version :
 * $Date    :
 *
 * Comments:
 *
 * @brief The file contains USB stack CDC-PSTN class layer api header function.
 *
 *****************************************************************************/

#ifndef _USB_CDC_PSTN_H
#define _USB_CDC_PSTN_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_cdc.h"
/******************************************************************************
 * Constants
 *****************************************************************************/
/* Refer to Universal Serial Bus Communications Class Subclass Specification for PSTN Devices */
#define UART_STATE_RX_CARRIER             0x01
#define UART_STATE_TX_CARRIER             0x02
#define UART_STATE_BREAK                  0x04
#define UART_STATE_RING_SIGNAL            0x08
#define UART_STATE_FRAMING                0x10
#define UART_STATE_PARITY                 0x20
#define UART_STATE_OVERRUN                0x40

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define UART_BITMAP_SIZE           (0x02)
#define ABSTRACT_STATE_FEATURE     (0x01)
#define COUNTRY_SETTING_FEATURE    (0x02)
#define CARRIER_ACTIVATION_CHECK   (0x02)
#define DTE_PRESENCE_CHECK         (0x01)

/*****************************
 * RNDIS Message State Macros
 *****************************/
#define REMOTE_NDIS_INITIALIZE_MSG         (0x00000002)
#define REMOTE_NDIS_HALT_MSG               (0x00000003)
#define REMOTE_NDIS_QUERY_MSG              (0x00000004)
#define REMOTE_NDIS_SET_MSG                (0x00000005)
#define REMOTE_NDIS_RESET_MSG              (0x00000006)
#define REMOTE_NDIS_INDICATE_STATUS_MSG    (0x00000007)
#define REMOTE_NDIS_KEEPALIVE_MSG          (0x00000008)
#define REMOTE_NDIS_INITIALIZE_CMPLT       (0x80000002)
#define REMOTE_NDIS_QUERY_CMPLT            (0x80000004)
#define REMOTE_NDIS_SET_CMPLT              (0x80000005)
#define REMOTE_NDIS_RESET_CMPLT            (0x80000006)
#define REMOTE_NDIS_KEEPALIVE_CMPLT        (0x80000008)

/**********************
 * RNDIS status values
 **********************/
/*The requested operation completed successfully.*/
#define RNDIS_STATUS_SUCCESS                (0x00000000)
/*The underlying driver does not support the requested operation.*/
#define RNDIS_STATUS_NOT_RECOGNIZED         (0x00010001)
#define RNDIS_STATUS_NOT_SUPPORTED          (0xC00000BB)
/*The underlying driver attempted the requested operation, usually a set,
 on its NIC but it was failed by the netcard. For example, an attempt to set
 too many multicast addresses might cause the return of this value.*/
#define RNDIS_STATUS_NOT_ACCEPTED           (0x00010003)
/*This value usually is a nonspecific default, returned when none of the more
 specific NDIS_STATUS_XXX caused the underlying driver to fail the request.*/
#define RNDIS_STATUS_FAILURE                (0xC0000001)
/*The request could not be satisfied due to a resource shortage.
 Usually, this return indicates that an attempt to allocate memory was
 unsuccessful, but it does not necessarily indicate that the same request,
 submitted later, will be failed for the same reason.*/
#define RNDIS_STATUS_RESOURCES              (0xC000009A)
/*The underlying driver failed the requested operation because a close is in progress.*/
#define RNDIS_STATUS_CLOSING                (0xC0010002)
#define RNDIS_STATUS_CLOSING_INDICATING     (0xC001000E)
/*The underlying NIC driver cannot satisfy the request at this time because it
 is currently resetting the netcard.*/
#define RNDIS_STATUS_RESET_IN_PROGRESS      (0xC001000D)
/*The value specified in the InformationBufferLength member of the
 NDIS_REQUEST-structured buffer at NdisRequest does not match the
 requirements for the given OID_XXX code. If the information buffer
 is too small, the BytesNeeded member contains the correct value for
 InformationBufferLength on return from NdisRequest.*/
#define RNDIS_STATUS_INVALID_LENGTH         (0xC0010014)
#define RNDIS_STATUS_BUFFER_TOO_SHORT       (0xC0010016)
/*The data supplied at InformationBuffer in the given NDIS_REQUEST structure
 is invalid for the given OID_XXX code.*/
#define RNDIS_STATUS_INVALID_DATA           (0xC0010015)
/*The OID_XXX code specified in the Oid member of the NDIS_REQUEST-structured
 buffer at NdisRequest is invalid or unsupported by the underlying driver*/
#define RNDIS_STATUS_INVALID_OID            (0xC0010017)
#define RNDIS_STATUS_MEDIA_CONNECT          (0x4001000B)
#define RNDIS_STATUS_MEDIA_DISCONNECT       (0x4001000C)

/***********************
 * RNDIS Response sizes
 ***********************/
#define RESPONSE_RNDIS_INITIALIZE_MSG_SIZE       (52)
#define RESPONSE_RNDIS_QUERY_MSG_SIZE            (24)
#define RESPONSE_RNDIS_SET_MSG_SIZE              (16)
#define RESPONSE_RNDIS_RESET_MSG_SIZE            (16)
#define RESPONSE_RNDIS_KEEPALIVE_MSG_SIZE        (16)

/*********************
 * RNDIS Other Macros
 *********************/
#define RNDIS_DF_CONNECTIONLESS            (0x00000001)
#define RNDIS_DF_CONNECTION_ORIENTED       (0x00000002)
#define RNDIS_MEDIUM_802_3                 (0x00000000)
#define RNDIS_SINGLE_PACKET_TRANSFER       (0x00000001)
#define PACKET_ALIGNMENT_FACTOR            (0x00000003)
#define NUM_OIDS_SUPPORTED                 (25)
#define RNDIS_VENDOR_ID                    (0xFFFFFF)
#define NIC_IDENTIFIER_VENDOR              (0x01)
/* Randomly selected mac address for reference design */
/* Following two defines are reserved for connection oriented devices. Set value to zero */
#define AF_LIST_OFFSET                     (0x00000000)
#define AF_LIST_SIZE                       (0x00000000)
/* Size of Ethernet address*/
#define RNDIS_ETHER_ADDR_SIZE              (6)
/* Size of ethernet header*/
#define RNDIS_USB_HEADER_SIZE              (44)
#define RNDIS_ETHER_HDR_SIZE               (14)
#define RNDIS_ETH_MIN_PACKET               (60)
#define RNDIS_ETH_MAX_PACKET               (1514)
#define RNDIS_MCAST_LIST_SIZE              (32)
#define RNDIS_ETH_MIN_FRAME                (16)
#define RNDIS_MULTICAST_LIST_SIZE          (0)
#define REMOTE_NDIS_PACKET_MSG             (0x00000001)

/*******************************************************
 * NDIS Hardware status codes (OID_GEN_HARDWARE_STATUS)
 *******************************************************/
/* Available and capable of sending and receiving data over the wire */
#define NdisHardwareStatusReady             (0x00000000)
/* Initializing */
#define NdisHardwareStatusInitializing      (0x00000001)
/* Resetting */
#define NdisHardwareStatusReset             (0x00000002)
/* Closing */
#define NdisHardwareStatusClosing           (0x00000003)
/* Not ready */
#define NdisHardwareStatusNotReady          (0x00000004)

/************************************************
 * NDIS media types that the NIC can support
 ************************************************/
/* Ethernet (802.3) is not supported for NDIS 6.0 drivers.*/
/* Note  NDIS 5.x miniport drivers that conform to the 802.11 interface must
 use this media type. For more information about the 802.11 interface,
 see 802.11 Wireless LAN Miniport Drivers.*/
#define NdisMedium802_3                     (0x00000000)
/*Token Ring (802.5) is not supported for NDIS 6.0 drivers.*/
#define NdisMedium802_5                     (0x00000001)
/*FDDI is not supported on Windows Vista.*/
#define NdisMediumFddi                      (0x00000002)
/*WAN*/
#define NdisMediumWan                       (0x00000003)
/*LocalTalk*/
#define NdisMediumLocalTalk                 (0x00000004)
/*DEC/Intel/Xerox (DIX) Ethernet*/
#define NdisMediumDix                       (0x00000005)
/*ARCNET (raw) is not supported on Windows Vista.*/
#define NdisMediumArcnetRaw                 (0x00000006)
/*ARCNET (878.2) is not supported on Windows Vista.*/
#define NdisMediumArcnet878_2               (0x00000007)
/*ATM is not supported for NDIS 6.0 drivers.*/
#define NdisMediumAtm                       (0x00000008)
/*Native 802.11. This media type is used by miniport drivers that conform to
 the Native 802.11 interface. For more information about this interface, see
 Native 802.11 Wireless LAN Miniport Drivers.
 Note: Native 802.11 interface is supported in NDIS 6.0 and later versions*/
#define NdisMediumNative802_11              (0x00000009)
/*Various types of NdisWirelessXxx media
 Note  This media type is not available for use beginning with Windows Vista*/
#define NdisMediumWirelessWan               (0x0000000A)
/*Infrared (IrDA)*/
#define NdisMediumIrda                      (0x0000000B)
/*Connection-oriented WAN */
#define NdisMediumCoWan                     (0x0000000C)
/*IEEE 1394 (firewire) bus*/
#define NdisMedium1394                      (0x0000000D)
/*Broadcast PC network.*/
#define NdisMediumBpc                       (0x0000000E)
/*InfiniBand network.*/
#define NdisMediumInfiniBand                (0x0000000F)
/*Tunnel network.*/
#define NdisMediumTunnel                    (0x00000010)
/*  NDIS loopback network. */
#define NdisMediumLoopback                  (0x00000011)

/***********************************************************
 * Ndis Packet Filter Bits (OID_GEN_CURRENT_PACKET_FILTER).
 ***********************************************************/
/*Directed packets. Directed packets contain a destination address
 equal to the station address of the NIC. */
#define NDIS_PACKET_TYPE_DIRECTED               (0x0001)
/*Multicast address packets sent to addresses in the multicast address list.
 A protocol driver can receive Ethernet (802.3) multicast packets or
 Token Ring (802.5) functional address packets by specifying the multicast or
 functional address packet type. Setting the multicast address list or
 functional address determines which multicast address
 groups the NIC driver enables.*/
#define NDIS_PACKET_TYPE_MULTICAST              (0x0002)
/*All multicast address packets, not just the ones enumerated in the
 multicast address list.*/
#define NDIS_PACKET_TYPE_ALL_MULTICAST          (0x0004)
/*Broadcast packets. */
#define NDIS_PACKET_TYPE_BROADCAST              (0x0008)
/*All source routing packets. If the protocol driver sets this bit,
 the NDIS library attempts to act as a source routing bridge. */
#define NDIS_PACKET_TYPE_SOURCE_ROUTING         (0x0010)
/*Specifies all packets.*/
#define NDIS_PACKET_TYPE_PROMISCUOUS            (0x0020)
/*SMT packets that an FDDI NIC receives. */
#define NDIS_PACKET_TYPE_SMT                    (0x0040)
/*All packets sent by installed protocols and all packets indicated by the NIC
 that is identified by a given NdisBindingHandle*/
#define NDIS_PACKET_TYPE_ALL_LOCAL              (0x0080)
/*NIC driver frames that a Token Ring NIC receives. */
#define NDIS_PACKET_TYPE_MAC_FRAME              (0x8000)
/*Functional address packets sent to addresses
 included in the current functional address. */
#define NDIS_PACKET_TYPE_FUNCTIONAL             (0x4000)
/*All functional address packets, not just the ones in the
 current functional address. */
#define NDIS_PACKET_TYPE_ALL_FUNCTIONAL         (0x2000)
/*Packets sent to the current group address. */
#define NDIS_PACKET_TYPE_GROUP                  (0x1000)

/***************************************************************
 * Object Identifiers used by NdisRequest Query/Set Information
 ***************************************************************/
/* General Objects */
#define OID_GEN_SUPPORTED_LIST                  0x00010101
#define OID_GEN_HARDWARE_STATUS                 0x00010102
#define OID_GEN_MEDIA_SUPPORTED                 0x00010103
#define OID_GEN_MEDIA_IN_USE                    0x00010104
#define OID_GEN_MAXIMUM_LOOKAHEAD               0x00010105
#define OID_GEN_MAXIMUM_FRAME_SIZE              0x00010106
#define OID_GEN_LINK_SPEED                      0x00010107
#define OID_GEN_TRANSMIT_BUFFER_SPACE           0x00010108
#define OID_GEN_RECEIVE_BUFFER_SPACE            0x00010109
#define OID_GEN_TRANSMIT_BLOCK_SIZE             0x0001010A
#define OID_GEN_RECEIVE_BLOCK_SIZE              0x0001010B
#define OID_GEN_VENDOR_ID                       0x0001010C
#define OID_GEN_VENDOR_DESCRIPTION              0x0001010D
#define OID_GEN_CURRENT_PACKET_FILTER           0x0001010E
#define OID_GEN_CURRENT_LOOKAHEAD               0x0001010F
#define OID_GEN_DRIVER_VERSION                  0x00010110
#define OID_GEN_MAXIMUM_TOTAL_SIZE              0x00010111
#define OID_GEN_PROTOCOL_OPTIONS                0x00010112
#define OID_GEN_MAC_OPTIONS                     0x00010113
#define OID_GEN_MEDIA_CONNECT_STATUS            0x00010114
#define OID_GEN_MAXIMUM_SEND_PACKETS            0x00010115
#define OID_GEN_VENDOR_DRIVER_VERSION           0x00010116
#define OID_GEN_XMIT_OK                         0x00020101
#define OID_GEN_RCV_OK                          0x00020102
#define OID_GEN_XMIT_ERROR                      0x00020103
#define OID_GEN_RCV_ERROR                       0x00020104
#define OID_GEN_RCV_NO_BUFFER                   0x00020105
#define OID_GEN_DIRECTED_BYTES_XMIT             0x00020201
#define OID_GEN_DIRECTED_FRAMES_XMIT            0x00020202
#define OID_GEN_MULTICAST_BYTES_XMIT            0x00020203
#define OID_GEN_MULTICAST_FRAMES_XMIT           0x00020204
#define OID_GEN_BROADCAST_BYTES_XMIT            0x00020205
#define OID_GEN_BROADCAST_FRAMES_XMIT           0x00020206
#define OID_GEN_DIRECTED_BYTES_RCV              0x00020207
#define OID_GEN_DIRECTED_FRAMES_RCV             0x00020208
#define OID_GEN_MULTICAST_BYTES_RCV             0x00020209
#define OID_GEN_MULTICAST_FRAMES_RCV            0x0002020A
#define OID_GEN_BROADCAST_BYTES_RCV             0x0002020B
#define OID_GEN_BROADCAST_FRAMES_RCV            0x0002020C
#define OID_GEN_RCV_CRC_ERROR                   0x0002020D
#define OID_GEN_TRANSMIT_QUEUE_LENGTH           0x0002020E
#define OID_GEN_GET_TIME_CAPS                   0x0002020F
#define OID_GEN_GET_NETCARD_TIME                0x00020210
/* 802.3 Objects (Ethernet) */
#define OID_802_3_PERMANENT_ADDRESS             0x01010101
#define OID_802_3_CURRENT_ADDRESS               0x01010102
#define OID_802_3_MULTICAST_LIST                0x01010103
#define OID_802_3_MAXIMUM_LIST_SIZE             0x01010104
#define OID_802_3_MAC_OPTIONS                   0x01010105

#define NDIS_802_3_MAC_OPTION_PRIORITY          0x00000001
#define OID_802_3_RCV_ERROR_ALIGNMENT           0x01020101
#define OID_802_3_XMIT_ONE_COLLISION            0x01020102
#define OID_802_3_XMIT_MORE_COLLISIONS          0x01020103
#define OID_802_3_XMIT_DEFERRED                 0x01020201
#define OID_802_3_XMIT_MAX_COLLISIONS           0x01020202
#define OID_802_3_RCV_OVERRUN                   0x01020203
#define OID_802_3_XMIT_UNDERRUN                 0x01020204
#define OID_802_3_XMIT_HEARTBEAT_FAILURE        0x01020205
#define OID_802_3_XMIT_TIMES_CRS_LOST           0x01020206
#define OID_802_3_XMIT_LATE_COLLISIONS          0x01020207

/****************************
 * NDIS Media Connect Status
 ****************************/
#define NdisMediaStateConnected                 (0x00000000)
#define NdisMediaStateDisconnected              (0x00000001)
#define NdisMediaStateUnknown                   (0xFFFFFFFF)

/********************************************************************
 * DeviceState : Result of the NDISUIO query of OID_GEN_MEDIA_IN_USE.
 ********************************************************************/
#define RNDIS_DEVICE_STATE_CONNECTED           (0x00000001)
#define RNDIS_DEVICE_STATE_DISCONNECTED        (0x00000000)

/********************************************************************
 * DataLength : Data length of communication feature.
 ********************************************************************/
#define COMM_FEATURE_DATA_SIZE                  (0x02)
#define MAX_EXPECTED_COMMAND_SIZE               (76)
/* this is the max observed command size we get on control endpoint --
 we are allocating memory for command at initialization, instead of
 dynamically allocating it when command is received, to avoid memory
 fragmentation */
#define MAX_EXPECTED_RESPONSE_SIZE              (RESPONSE_RNDIS_QUERY_MSG_SIZE + \
                                                (NUM_OIDS_SUPPORTED << 2))

/******************************************************************************
 * Types
 *****************************************************************************/
/*
 * This Structure represents PSTN object
 */
typedef struct _cdc_pstn_struct
{
#if CDC_RNDIS_SUPPORT
    uint8_t rndis_command_ptr[MAX_EXPECTED_COMMAND_SIZE];
    uint8_t response_data_ptr[MAX_EXPECTED_RESPONSE_SIZE];
#endif
    uint8_t serial_state_buf[NOTIF_PACKET_SIZE + UART_BITMAP_SIZE];
    usb_application_callback_struct_t pstn_callback;
    bool dte_present;
    uint16_t break_duration;
    /* Status of DATA TERMINAL EQUIPMENT */
    uint8_t dte_status;
    /* Length of time in milliseconds of the break signal */
    uint8_t current_interface;
    uint16_t uart_state;
#if CDC_RNDIS_SUPPORT
    uint32_t rndis_host_max_tx_size;
    uint32_t rndis_dev_max_tx_size;
    uint32_t rndis_hw_state;
    uint32_t rndis_packet_filter;
    uint32_t rndis_media_connect_status;
    uint32_t num_frames_tx_ok;
    uint32_t num_frames_rx_ok;
    uint32_t num_frames_tx_error;
    uint32_t num_frames_rx_error;
    uint32_t num_recv_frames_missed;
    uint32_t num_recv_frames_alignment_error;
    uint32_t num_frames_tx_one_collision;
    uint32_t num_frames_tx_many_collision;
    uint8_t rndis_device_state;
    os_mutex_handle status_mutex;
#endif
} cdc_pstn_struct_t;
#endif

/* EOF */
