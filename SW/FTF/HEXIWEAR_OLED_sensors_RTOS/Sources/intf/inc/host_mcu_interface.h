
#ifndef _HOST_MCU_INTERFACE_H_
#define _HOST_MCU_INTERFACE_H_

#include "fsl_os_abstraction.h"
#include "KW40_UART.h"
#include "hexiwear_info.h"

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

#define gHostInterfaceRxTaskStackSize_c         ( 0x1000 )
#define gHostInterfaceTxTaskStackSize_c         500
#define gHostInterfaceOkTaskStackSize_c         500

#define gHostInterfaceIRQPriority_c             HEXIWEAR_KW40_UART_IRQ_PRIO

#define gHostInterfaceOkPriority_c              2
#define gHostInterfaceTxPriority_c              3
#define gHostInterfaceRxPriority_c              4

#define gHostInterface_msgNum                   3
#define gHostInterface_waitTimeout              OSA_WAIT_FOREVER

#define gHostInterface_instance                 ( FSL_KW40_UART )
#define gHostInterface_irqn                     ( UART4_RX_TX_IRQn )

#define gHostInterface_startByte1               0x55
#define gHostInterface_startByte2               0xAA
#define gHostInterface_trailerByte              0x45

#define gHostInterface_dataSize                 23
#define gHostInterface_headerSize               4

#define gHostInterface_retransmitCount          3
#define gHostInterface_retransmitTimeout        100

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

    // Battery Service
    packetType_batteryLevel     = 5,

    packetType_accel            = 6, /**< motion service */
    packetType_ambiLight        = 7, /**< weather service */
    packetType_pressure         = 8, /**< weather service */


    packetType_gyro             = 9,  /**< motion service */
    packetType_temperature      = 10, /**< weather service */
    packetType_humidity         = 11, /**< weather service */
    packetType_magnet           = 12, /**< motion service */

    packetType_heartRate        = 13, /**< health service */
    packetType_steps            = 14, /**< health service */
    packetType_calories         = 15, /**< health service */

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

	// Active slider
	packetType_buttonsGroupToggleActive = 23,
	packetType_buttonsGroupGetActive    = 24,
	packetType_buttonsGroupSendActive   = 25,

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
    packetType_buildVersion = 33,

	// SLEEP ON
	packetType_sleepON = 34,

	// SLEEP OFF
	packetType_sleepOFF = 35,

    // OK Packet
    packetType_OK = 255

} hostInterface_packetType_t;

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

typedef enum
{
	alertIn_type_notification  		 = 1,
	alertIn_type_settings            = 2,
	alertIn_type_timeUpdate    	     = 3,

}
hostInterface_alertIn_type_t;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
osa_status_t HostInterface_Init(void);
osa_status_t HostInterface_TxQueueMsgPut(hostInterface_packet_t * hostInterface_Packet, bool confirmationReq );
osa_status_t HostInterface_TxInit(void);

osa_status_t HostInterface_RxInit(void);
osa_status_t HostInterface_RxQueueMsgPut(hostInterface_packet_t * pHostInterface_packet);

osa_status_t HostInterface_EventsInit(void);

osa_status_t HostInterface_EventConfirmAttPacketSet(void);
osa_status_t HostInterface_EventConfirmAttPacketWait(void);
osa_status_t HostInterface_EventConfirmAttPacketClear(void);

osa_status_t HostInterface_EventConfirmPacketWait(void);
osa_status_t HostInterface_EventConfirmPacketSet(void);
osa_status_t HostInterface_EventConfirmPacketClear(void);

osa_status_t HostInterface_EventSendOkPacketSet(void);
osa_status_t HostInterface_EventSendOkPacketWait(void);

void HostInterface_SetWakingTouch();

#endif /* _EXT_HOST_INTERFACE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

