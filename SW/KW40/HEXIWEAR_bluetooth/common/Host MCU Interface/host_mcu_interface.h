
#ifndef _HOST_MCU_INTERFACE_H_
#define _HOST_MCU_INTERFACE_H_

#include "fsl_os_abstraction.h"

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

#define gHostInterfaceRxTaskStackSize_c         400
#define gHostInterfaceTxTaskStackSize_c         300
#define gHostInterfaceOkTaskStackSize_c         300

#define gHostInterfaceOkPriority_c              7
#define gHostInterfaceTxPriority_c              8
#define gHostInterfaceRxHandlerPriority_c       6

#define gHostInterface_msgNum                   3
#define gHostInterface_waitTimeout              OSA_WAIT_FOREVER

#define gHostInterface_instance                 APP_SERIAL_INTERFACE_INSTANCE

#define gHostInterface_startByte1               0x55
#define gHostInterface_startByte2               0xAA
#define gHostInterface_trailerByte              0x45

#define gHostInterface_dataSize                 23
#define gHostInterface_headerSize               4

#define gHostInterface_retransmitCount          3
#define gHostInterface_retransmitTimeout        1000

#define gHostInterface_TxConfirmationEnable     1             // Send confirmation when receive packet
#define gHostInterface_RxConfirmationEnable     1             // Wait on confirmation from remote side (do retransmit)


/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */

typedef enum 
{
    packetType_pressUp          = 0,
    packetType_pressDown        = 1,
    packetType_pressLeft        = 2,
    packetType_pressRight       = 3,
    packetType_slide            = 4,
    
    // Batterry Service
    packetType_batteryLevel     = 5,
    
    // Motion Service
    packetType_accel            = 6,
    packetType_gyro             = 9,
    packetType_magnet           = 12,
    
    // Weather Service
    packetType_ambiLight        = 7,
    packetType_temperature      = 10,
    packetType_humidity         = 11,
    packetType_pressure         = 8,

    // Health Service
    packetType_heartRate        = 13,
    packetType_steps            = 14,
    packetType_calorie          = 15,

    // Alert Service
    packetType_alertIn          = 16,
    packetType_alertOut         = 17,
    
    // Type for password confirmation
    packetType_passDisplay      = 18,
    
    // Types for OTAP
    packetType_otapKW40Started  = 19,
    packetType_otapMK64Started  = 20,
    packetType_otapCompleted    = 21,
    packetType_otapFailed       = 22,
    
    // Active tsi group
    packetType_tsiGroupToggleActive = 23,
    packetType_tsiGroupGetActive    = 24,
    packetType_tsiGroupSendActive   = 25,
    
    // Turn off/on bluetooth advertising
    packetType_advModeGet    = 26,
    packetType_advModeSend   = 27,
    packetType_advModeToggle = 28,
   
    // App Mode Service
    packetType_appMode       = 29,
    
    // Link state (connected / disconnected)
    packetType_linkStateGet  = 30,
    packetType_linkStateSend = 31,
    
    // Notifications
    packetType_notification  = 32,
    
    // Build version
    packetType_buildVersion  = 33,
    
    // OK Packet
    packetType_OK            = 255,
}
hostInterface_packetType_t;

typedef struct
{
    // NOTE: Size of struct must be multiplier of 4 !
    uint8_t start1;
    uint8_t start2;
    hostInterface_packetType_t type;
    uint8_t length;
    uint8_t data[gHostInterface_dataSize + 1];
}
hostInterface_packet_t;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
osaStatus_t HostInterface_Init(void);
osaStatus_t HostInterface_TxQueueMsgPut(hostInterface_packet_t * hostInterface_Packet, bool confirmationReq);
osaStatus_t HostInterface_TxInit(void);

osaStatus_t HostInterface_RxInit(void);
osaStatus_t HostInterface_RxQueueMsgPut(hostInterface_packet_t * pHostInterface_packet);


osaStatus_t HostInterface_EventsInit(void);
osaStatus_t HostInterface_EventWait(event_flags_t flagsToWait, uint32_t timeout, event_flags_t *setFlags);
osaStatus_t HostInterface_EventSet(event_flags_t flagsToSet);
osaStatus_t HostInterface_EventClear(event_flags_t flagsToClear);

osaStatus_t HostInterface_EventConfirmAttPacketSet(void);
osaStatus_t HostInterface_EventConfirmAttPacketWait(void);
osaStatus_t HostInterface_EventConfirmAttPacketClear(void);

osaStatus_t HostInterface_EventConfirmPacketWait(void);
osaStatus_t HostInterface_EventConfirmPacketSet(void);
osaStatus_t HostInterface_EventConfirmPacketClear(void);

osaStatus_t HostInterface_EventSendOkPacketSet(void);
osaStatus_t HostInterface_EventSendOkPacketWait(void);

void HostInterface_UartInit(void);
#endif /* _EXT_HOST_INTERFACE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

