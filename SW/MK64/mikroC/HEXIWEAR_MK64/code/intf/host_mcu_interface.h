// File: host_mcu_interface.h

// Declarations of functionalities of the MCU interface module.

#ifndef _host_mcu_interface_h_
#define _host_mcu_interface_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "OSA.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// Packet constants.

#define gHostInterfaceRxTaskStackSize_c         ( 0x1000 )
#define gHostInterfaceTxTaskStackSize_c         500
#define gHostInterfaceOkTaskStackSize_c         500

#define gHostInterfaceIRQPriority_c             HEXIWEAR_KW40_UART_IRQ_PRIO

#define gHostInterfaceOkPriority_c              2
#define gHostInterfaceTxPriority_c              3
#define gHostInterfaceRxPriority_c              4

#define gHostInterface_msgNum                   3
#define gHostInterface_waitTimeout              OSA_WAIT_FOREVER

#define gHostInterface_instance                 4U //( FSL_KW40_UART )
#define gHostInterface_irqn                     66 //( UART4_RX_TX_IRQn )

#define gHostInterface_startByte1               0x55
#define gHostInterface_startByte2               0xAA
#define gHostInterface_trailerByte              0x45

#define gHostInterface_dataSize                 23
#define gHostInterface_headerSize               4

#define gHostInterface_retransmitCount          3
#define gHostInterface_retransmitTimeout        100

// Send confirmation when receiving a packet.
#define gHostInterface_TxConfirmationEnable     1
// Wait on confirmation from remote side (do retransmit).
#define gHostInterface_RxConfirmationEnable     1

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// Packet types.
typedef enum
{
    packetType_pressUp          = 0, // touch press up
    packetType_pressDown        = 1, // touch press down
    packetType_pressLeft        = 2, // touch press left
    packetType_pressRight       = 3, // touch press right
    packetType_slide            = 4, // touch slide

    packetType_batteryLevel     = 5, // battery Service

    packetType_accel            = 6, // motion service
    packetType_ambiLight        = 7, // weather service
    packetType_pressure         = 8, // weather service


    packetType_gyro             = 9,  // motion service
    packetType_temperature      = 10, // weather service
    packetType_humidity         = 11, // weather service
    packetType_magnet           = 12, // motion service

    packetType_heartRate        = 13, // health service
    packetType_steps            = 14, // health service
    packetType_calories         = 15, // health service

    // Alert service.
    packetType_alertIn          = 16, //  incoming alerts
    packetType_alertOut         = 17, //  outcoming alerts

    packetType_passDisplay      = 18, // key display type

    // OTAP procedure types.
    packetType_otapKW40Started  = 19,
    packetType_otapMK64Started  = 20,
    packetType_otapCompleted    = 21,
    packetType_otapFailed       = 22,

    // Active buttons types.
    packetType_buttonsGroupToggleActive = 23,
    packetType_buttonsGroupGetActive    = 24,
    packetType_buttonsGroupSendActive   = 25,

    // Turn off/on bluetooth advertising.
    packetType_advModeGet    = 26,
    packetType_advModeSend   = 27,
    packetType_advModeToggle = 28,

    packetType_appMode       = 29, // app mode service

    // Link State
    packetType_linkStateGet  = 30, // connected
    packetType_linkStateSend = 31, // disconnected

    packetType_notification  = 32, // notifications

    packetType_buildVersion = 33, // build version

    packetType_sleepON = 34,  // sleep ON

    packetType_sleepOFF = 35, // sleep OFF

    packetType_OK = 255       // OK packet
} hostInterface_packetType_t;

// Data-packet structure.
typedef struct
{
    // NOTE: Size of struct must be a multiplier of 4!
    uint8_t start1;
    uint8_t start2;
    hostInterface_packetType_t type;
    uint8_t length;
    uint8_t _data[ gHostInterface_dataSize + 1 ];
} hostInterface_packet_t;

// Incoming alert types.
typedef enum
{
    alertIn_type_notification = 1,
    alertIn_type_settings     = 2,
    alertIn_type_timeUpdate   = 3,
} hostInterface_alertIn_type_t;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

osa_status_t HostInterface_Init();

osa_status_t HostInterface_TxInit();
osa_status_t HostInterface_TxQueueMsgPut(
    hostInterface_packet_t * hostInterface_Packet, bool confirmationReq );
void HostInterface_TxCallback();

osa_status_t HostInterface_RxInit();
osa_status_t HostInterface_RxQueueMsgPut(
    hostInterface_packet_t * pHostInterface_packet );
void HostInterface_RxCallback();

osa_status_t HostInterface_EventsInit();

//osa_status_t HostInterface_EventConfirmAttPacketSet();
//osa_status_t HostInterface_EventConfirmAttPacketWait();
//osa_status_t HostInterface_EventConfirmAttPacketClear();

osa_status_t HostInterface_EventConfirmPacketWait();
osa_status_t HostInterface_EventConfirmPacketSet();
osa_status_t HostInterface_EventConfirmPacketClear();

osa_status_t HostInterface_EventSendOkPacketSet();
osa_status_t HostInterface_EventSendOkPacketWait();

void HostInterface_SetWakingTouch();

#endif