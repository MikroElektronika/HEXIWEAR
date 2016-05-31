/**
 *    @file host_mcu_interface.h
 */

#ifndef _HOST_MCU_INTERFACE_H_
#define _HOST_MCU_INTERFACE_H_

#include "fsl_os_abstraction.h"

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

#define gHostInterfaceRxTaskStackSize_c         400                          /** Stack Sizes of Rx task. */
#define gHostInterfaceTxTaskStackSize_c         300                          /** Stack Sizes of Tx task. */
#define gHostInterfaceOkTaskStackSize_c         300                          /** Stack Sizes of Ok task. */

#define gHostInterfaceRxHandlerPriority_c       6                            /** Priority of Rx task. */
#define gHostInterfaceTxPriority_c              8                            /** Priority of Tx task. */
#define gHostInterfaceOkPriority_c              7                            /** Priority of Ok task. */


#define gHostInterface_msgNum                   3                              /** Number of elements in the queue. */
#define gHostInterface_waitTimeout              OSA_WAIT_FOREVER               /** The number of milliseconds to wait for a message. */

#define gHostInterface_instance                 APP_SERIAL_INTERFACE_INSTANCE  /** The LPUART instance number. */

#define gHostInterface_startByte1               0x55                           /** Definition of host interface packet first byte. */
#define gHostInterface_startByte2               0xAA                           /** Definition of host interface packet second byte. */
#define gHostInterface_trailerByte              0x45                           /** Definition of host interface packet end byte. */

#define gHostInterface_dataSize                 23                             /** Maximum number of data bytes into packet. */ 
#define gHostInterface_headerSize               4                              /** Size of header into packet. */

#define gHostInterface_retransmitCount          3                              /** Maximum number of retransmitions. */
#define gHostInterface_retransmitTimeout        1000                           /** Retramsmition timeout in milliseconds. */

#define gHostInterface_TxConfirmationEnable     1                              /** Send confirmation when receive packet. */
#define gHostInterface_RxConfirmationEnable     1                              /** Wait on confirmation from remote side (do retransmit). */


/***********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */

/*! Possible values for packet type field. */
typedef enum 
{
    packetType_pressUp          = 0,        /**< Electrode touch detected */ 
    packetType_pressDown        = 1,        /**< Electrode touch detected */ 
    packetType_pressLeft        = 2,        /**< Electrode touch detected */ 
    packetType_pressRight       = 3,        /**< Electrode touch detected */ 
    packetType_slide            = 4,        /**< Electrode touch detected */ 
    
    packetType_batteryLevel     = 5,        /**< Batterry Service */

    packetType_accel            = 6,        /**< Motion Service: Accel */
    packetType_gyro             = 9,        /**< Motion Service: Gyro */
    packetType_magnet           = 12,       /**< Motion Service: Magnet */
    
    packetType_ambiLight        = 7,        /**< Weather Service: Ambient Light */
    packetType_temperature      = 10,       /**< Weather Service: Temperature */
    packetType_humidity         = 11,       /**< Weather Service: Humidity */
    packetType_pressure         = 8,        /**< Weather Service: Pressure */

    packetType_heartRate        = 13,       /**< Health Service: Heart Rate */
    packetType_steps            = 14,       /**< Health Service: Pedometer */
    packetType_calorie          = 15,       /**< Health Service: Calorie counder */

    packetType_alertIn          = 16,       /**< Alert Service: Input */
    packetType_alertOut         = 17,       /**< Alert Service: Output */
    
    packetType_passDisplay      = 18,       /**< Type for password confirmation */
    
    packetType_otapKW40Started  = 19,       /**< OTAP State: OTAP for KW40 Started */
    packetType_otapMK64Started  = 20,       /**< OTAP State: OTAP for MK64 Started */
    packetType_otapCompleted    = 21,       /**< OTAP State: OTAP completed */        
    packetType_otapFailed       = 22,       /**< OTAP State: OTAP failed */
    
    packetType_tsiGroupToggleActive = 23,   /**< Toggle active group of electrodes */
    packetType_tsiGroupGetActive    = 24,   /**< Get active group of electrodes */
    packetType_tsiGroupSendActive   = 25,   /**< Send active group of electrodes */
    
    packetType_advModeGet    = 26,          /**< Get bluetooth advertising state*/
    packetType_advModeSend   = 27,          /**< Send bluetooth advertising state*/
    packetType_advModeToggle = 28,          /**< Toggle bluetooth advertising state*/
   
    packetType_appMode       = 29,          /**< App Mode Service */
    
    packetType_linkStateGet  = 30,          /**< Get link state (connected / disconnected) */
    packetType_linkStateSend = 31,          /**< Send link state (connected / disconnected) */
    
    packetType_notification  = 32,          /**< Notifications */
    
    packetType_buildVersion  = 33,          /**< Build version */
    
    packetType_OK            = 255,         /**< OK Packet */
}
hostInterface_packetType_t;

/** Definition of Host Interface Packet structure. */
typedef struct
{
    // NOTE: Size of struct must be multiplier of 4 !
    uint8_t start1;                                        /**< First start byte. */
    uint8_t start2;                                        /**< Second start byte. */
    hostInterface_packetType_t type;                       /**< Packet type. */
    uint8_t length;                                        /**< Number of data bytes. */
    uint8_t data[gHostInterface_dataSize + 1];             /**< Data array. */
}
hostInterface_packet_t;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
/**
 *    Initialize module.
 *
 *    @return                          osaStatus_Success  Successfully created tasks and  message queues.
 *                                     osaStatus_Error    Initialization fail.                  
 */
osaStatus_t HostInterface_Init(void);

/**
 *    This function puts a message to the end of the Tx message queue.
 *
 *    @param    pHostInterface_packet   Packet that will be placed into Tx message queue.
 *
 *    @return                          osaStatus_Success  Message successfully put into the queue.
 *                                     osaStatus_Error    Process fail.
 */
osaStatus_t HostInterface_TxQueueMsgPut(hostInterface_packet_t * hostInterface_Packet, bool confirmationReq);

/**
 *    This function initialize Tx queue and create corresponding task.
 *
 *
 *    @return                          osaStatus_Success  
 *                                     osaStatus_Error    
 */
osaStatus_t HostInterface_TxInit(void);

/**
 *    Initialize Rx path of host interface driver.
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_RxInit(void);

/**
 *    This function puts a message to the end of the Rx message queue.
 *
 *    @param    pHostInterface_packet   Packet that will be placed into Tx message queue.
 *
 *    @return                          osaStatus_Success  Message successfully put into the queue.
 *                                     osaStatus_Error    Process fail.
 */
osaStatus_t HostInterface_RxQueueMsgPut(hostInterface_packet_t * pHostInterface_packet);

/**
 *    This function creates event object which will be used to wait for confirmation 
 *    (OK packet) for previously sent pakcet.
 *
 *    @return  status of OSA's functions
 */
osaStatus_t HostInterface_EventsInit(void);

/**
 *    This function waits for a combination of flags to be set in an event object.
 *
 *    @param    flagsToWait   Flags that to wait.
 *    @param    timeout       The maximum number of milliseconds to wait for the event.
 *    @param    setFlags      Flags that wakeup the waiting task are obtained by this parameter.
 *
 *    @return                 osaStatus_Success    Success
 *                            osaStatus_Error      Failed
 *                            osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventWait(event_flags_t flagsToWait, uint32_t timeout, event_flags_t *setFlags);

/**
 *    Sets specified flags of an event object.
 *
 *    @param    flagsToSet   Flags to be set.
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventSet(event_flags_t flagsToSet);

/**
 *    Clears specified flags of an event object.
 *
 *    @param    flagsToClear   Flags to be clear.
 *
 *    @return                  osaStatus_Success    Success
 *                             osaStatus_Error      Failed
 *                             osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventClear(event_flags_t flagsToClear);

/**
 *    Wait for confirm packet to be received.
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventConfirmPacketWait(void);

/**
 *    Set flag about confirm packet received.
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventConfirmPacketSet(void);

/**
 *    Clear flag about confirm packet received.
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventConfirmPacketClear(void);

/**
 *    Set flag about confirm packet received (used for Attribute Written operation).
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventConfirmAttPacketSet(void);

/**
 *    Wait for confirm packet to be received (used for Attribute Written operation).
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventConfirmAttPacketWait(void);

/**
 *    Clear flag about confirm packet received (used for Attribute Written operation).
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventConfirmAttPacketClear(void);

/**
 *    Trigger event for start sending confirm pakcet.
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventSendOkPacketSet(void);

/**
 *    Wait for start sending confirm pakcet.
 *
 *    @return                osaStatus_Success    Success
 *                           osaStatus_Error      Failed
 *                           osaStatus_Timeout    Timeout occurs while waiting
 */
osaStatus_t HostInterface_EventSendOkPacketWait(void);

/**
 *    Initialize UART module.
 */
void HostInterface_UartInit(void);

#endif /* _EXT_HOST_INTERFACE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

