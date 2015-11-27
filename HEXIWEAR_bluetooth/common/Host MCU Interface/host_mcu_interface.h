
#ifndef _HOST_MCU_INTERFACE_H_
#define _HOST_MCU_INTERFACE_H_

#include "fsl_os_abstraction.h"

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

#define gHostInterfaceRxTaskStackSize_c         500
#define gHostInterfaceTxTaskStackSize_c         500
#define gHostInterfaceOkTaskStackSize_c         300

#define gHostInterfaceOkPriority_c              7
#define gHostInterfaceTxPriority_c              8
#define gHostInterfaceRxHandlerPriority_c       10

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
    packetType_gyro             = 7,
    packetType_magnet           = 8,
    
    // Weather Service
    packetType_ambiLight        = 9,
    packetType_temperature      = 10,
    packetType_humidity         = 11,
    packetType_pressure         = 12,

    // Health Service
    packetType_heartRate        = 13,
    packetType_steps            = 14,
    packetType_activityTime     = 15,

    // Alert Service
    packetType_alertIn          = 16,
    packetType_alertOut         = 17,
    
    // OK Packet
    packetType_OK               = 255,
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
osaStatus_t HostInterface_TxQueueMsgPut(hostInterface_packet_t * hostInterface_Packet);
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


#endif /* _EXT_HOST_INTERFACE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

