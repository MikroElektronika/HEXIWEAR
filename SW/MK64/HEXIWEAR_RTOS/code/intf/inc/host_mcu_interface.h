/**
 * \file host_mcu_interface.h
 * \version 1.00
 * \brief this file contains MCU-to-MCU interface info and routines' declarations
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

#include "fsl_os_abstraction.h"
#include "KW40_UART.h"
#include "hexiwear_info.h"

/** packet constants */

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

#define gHostInterface_TxConfirmationEnable     1 // send confirmation when receive packet
#define gHostInterface_RxConfirmationEnable     1 // wait on confirmation from remote side (do retransmit)


/** packet types */

typedef enum
{
    packetType_pressUp          = 0, /**< touch press up */
    packetType_pressDown        = 1, /**< touch press down */
    packetType_pressLeft        = 2, /**< touch press left */
    packetType_pressRight       = 3, /**< touch press right */
    packetType_slide            = 4, /**< touch slide */

    packetType_batteryLevel     = 5, /**< battery Service */

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
    packetType_alertIn          = 16, /**<  incoming alerts */
    packetType_alertOut         = 17, /**<  outcoming alerts */

    packetType_passDisplay      = 18, /**< key display type */

    // OTAP procedure types
    packetType_otapKW40Started  = 19,
    packetType_otapMK64Started  = 20,
    packetType_otapCompleted    = 21,
    packetType_otapFailed       = 22,

	// active buttons types
	packetType_buttonsGroupToggleActive = 23,
	packetType_buttonsGroupGetActive    = 24,
	packetType_buttonsGroupSendActive   = 25,

    // Turn off/on bluetooth advertising
	packetType_advModeGet    = 26,
	packetType_advModeSend   = 27,
	packetType_advModeToggle = 28,

    packetType_appMode       = 29, /**< app mode service */

	// Link State
	packetType_linkStateGet  = 30, /**< connected */
	packetType_linkStateSend = 31, /**< disconnected */

    packetType_notification  = 32, /* notifications */

    packetType_buildVersion = 33, /**< build version */

	packetType_sleepON = 34,  /**< sleep ON */

	packetType_sleepOFF = 35, /**< sleep OFF */

    packetType_OK = 255       /**< OK packet */

} hostInterface_packetType_t;

/** data-packet structure */
typedef struct
{
    // NOTE: Size of struct must be multiplier of 4 !
    uint8_t start1;
    uint8_t start2;
    hostInterface_packetType_t type;
    uint8_t length;
    uint8_t data[gHostInterface_dataSize + 1];

} hostInterface_packet_t;

/** incoming alert types */
typedef enum
{
	alertIn_type_notification  		 = 1,
	alertIn_type_settings            = 2,
	alertIn_type_timeUpdate    	     = 3,

} hostInterface_alertIn_type_t;

/** Public prototypes */
osa_status_t HostInterface_Init(void);

osa_status_t HostInterface_TxInit(void);

osa_status_t HostInterface_RxInit(void);
osa_status_t HostInterface_RxQueueMsgPut(hostInterface_packet_t * pHostInterface_packet);
osa_status_t HostInterface_CmdQueueMsgGet(hostInterface_packet_t* pHostInterface_packet);

osa_status_t HostInterface_EventsInit(void);

osa_status_t HostInterface_EventSendOkPacketSet(void);
osa_status_t HostInterface_EventSendOkPacketWait(void);

void HostInterface_SetWakingTouch();
