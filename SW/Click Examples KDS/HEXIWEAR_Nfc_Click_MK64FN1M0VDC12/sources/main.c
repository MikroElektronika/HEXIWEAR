/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
 *
 * [File Name]     main.c
 * [Platform]      MK64FN1M0VDC12
 * [Project]       HEXIWEAR_Relay_Click
 * [Version]       1.00
 * [Author]        marko.lainovic
 * [Date]          04/19/2016
 * [Language]      'C'
 * [History]       1.00 - Original Release
 *
 * [Description]   Put Relay Click into a MikroBus socket 1 on the docking station.
 * Toggle the relay terminals via the touch interface (left and right buttons)
 *
 */

//-----------------------------------------------------------------------
// Standard C/C++ Includes
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// KSDK Includes
//-----------------------------------------------------------------------
#include "main.h"
#include "OLED_driver.h"
#include "screens_common.h"
#include "generic_spi_driver.h"
#include "board.h"
#include "OLED_defs.h"
#include "GPIO.h"
#include "OLED_SPI.h"
#include "DMA_controller.h"
#include "gui_resources.h"

//-----------------------------------------------------------------------
// Application Includes
//-----------------------------------------------------------------------
#include "nfc.h"
#include "tool.h"

//-----------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------
static void PacketParser( uint32_t instance, void* uartState );

//-----------------------------------------------------------------------
// LEDs macros
//-----------------------------------------------------------------------
#define RED_LED_ON()   GPIO_DRV_ClearPinOutput( RED_LED );
#define GREEN_LED_ON() GPIO_DRV_ClearPinOutput( GREEN_LED );
#define BLUE_LED_ON()  GPIO_DRV_ClearPinOutput( BLUE_LED );

#define RED_LED_OFF()   GPIO_DRV_SetPinOutput( RED_LED );
#define GREEN_LED_OFF() GPIO_DRV_SetPinOutput( GREEN_LED );
#define BLUE_LED_OFF()  GPIO_DRV_SetPinOutput( BLUE_LED );

#define RED_LED_TOGGLE()   GPIO_DRV_TogglePinOutput( RED_LED );
#define GREEN_LED_TOGGLE() GPIO_DRV_TogglePinOutput( GREEN_LED );
#define BLUE_LED_TOGGLE()  GPIO_DRV_TogglePinOutput( BLUE_LED );

#define FLASH_Toggle() RED_LED_TOGGLE(); GREEN_LED_TOGGLE(); BLUE_LED_TOGGLE()
#define FLASH_SetON() RED_LED_ON(); GREEN_LED_ON(); BLUE_LED_ON()
#define FLASH_SetOFF() RED_LED_OFF(); GREEN_LED_OFF(); BLUE_LED_OFF()

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
#define gHostInterface_startByte1               0x55
#define gHostInterface_startByte2               0xAA
#define gHostInterface_trailerByte              0x45

#define gHostInterface_dataSize                 23
#define gHostInterface_headerSize               4

#define FSL_KW40_UART UART4_IDX

#define TASK_NFC_STACK_SIZE		1024
#define TASK_NFC_STACK_PRIO		5
OSA_TASK_DEFINE(task_nfc, TASK_NFC_STACK_SIZE);

#define TASK_APP_STACK_SIZE		1024
#define TASK_APP_STACK_PRIO		5
OSA_TASK_DEFINE(task_app, TASK_APP_STACK_SIZE);

unsigned char DiscoveryTechnologies[] = {
		MODE_POLL | TECH_PASSIVE_NFCA,
		MODE_POLL | TECH_PASSIVE_NFCF,
		MODE_POLL | TECH_PASSIVE_NFCB,
		MODE_POLL | TECH_PASSIVE_15693,
		MODE_POLL | TECH_ACTIVE_NFCA,
		MODE_LISTEN | TECH_PASSIVE_NFCA,
		MODE_LISTEN | TECH_PASSIVE_NFCB,
		MODE_LISTEN | TECH_PASSIVE_NFCF,
		MODE_LISTEN | TECH_ACTIVE_NFCA,
		MODE_LISTEN | TECH_ACTIVE_NFCF,
		};

const char NdefRecord_HexiwearApp[] = {
/* 	 	0xD4,
		0x0F,
		0x16,
		'a','n','d','r','o','i','d','.','c','o','m',':','p','k','g',
		'c','o','m','.','w','o','l','k','a','b','o','u','t','.','h','e','x','i','w','e','a','r'
};
*/
0x91, 0x01, 0x4A, 0x55, 0x03, 0x70, 0x6C, 0x61, 0x79, 0x2E, 0x67, 0x6F, 0x6F, 0x67, 0x6C, 0x65, 0x2E, 0x63, 0x6F, 0x6D, 0x2F, 0x73, 0x74, 0x6F, 0x72, 0x65, 0x2F, 0x61, 0x70, 0x70, 0x73, 0x2F, 0x64, 0x65, 0x74, 0x61, 0x69, 0x6C, 0x73, 0x3F, 0x69, 0x64, 0x3D, 0x63, 0x6F, 0x6D, 0x2E, 0x77, 0x6F, 0x6C, 0x6B, 0x61, 0x62, 0x6F, 0x75, 0x74, 0x2E, 0x68, 0x65, 0x78, 0x69, 0x77, 0x65, 0x61, 0x72, 0x26, 0x66, 0x65, 0x61, 0x74, 0x75, 0x72, 0x65, 0x3D, 0x62, 0x65, 0x61, 0x6D, 0x54, 0x0F, 0x16, 0x61, 0x6E, 0x64, 0x72, 0x6F, 0x69, 0x64, 0x2E, 0x63, 0x6F, 0x6D, 0x3A, 0x70, 0x6B, 0x67, 0x63, 0x6F, 0x6D, 0x2E, 0x77, 0x6F, 0x6C, 0x6B, 0x61, 0x62, 0x6F, 0x75, 0x74, 0x2E, 0x68, 0x65, 0x78, 0x69, 0x77, 0x65, 0x61, 0x72};

const char NdefRecord_BluetoothHandover[] = { 0xD2,
		0x20, // type length
		0x12, // payload length
		'a','p','p','l','i','c','a','t','i','o','n','/','v','n','d','.','b','l','u','e','t','o','o','t','h','.','e','p','.','o','o','b',
		0x12, 0x00, // OOB data length
		0x45, 0x00, 0x0B, 0x40, 0x36, 0x00, // BT address (little-endian)
		0x09, 0x09,	'H','E','X','I','W','E','A','R' // BT local name
};

//-----------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------
typedef enum
{
    touch_left  = 0,
    touch_right = 1,
    touch_invalid = 0xFF

} touch_type_t;

typedef enum
{
	first = 0,
	hexiwear,
	mood,
	bluetooth,
	last
} app_mode_t;

/**
 * @enum Packet definitions
 *
 * Types of packets exchanged.
 */
typedef enum
{
    packetType_pressUp          = 0, /**< Press up event */
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

} hostInterface_packet_t;

typedef enum
{
    hostInterface_rxState_idle           = 0,
    hostInterface_rxState_headerReceived = 3,
    hostInterface_rxState_dataWait       = 4,
    hostInterface_rxState_trailerWait    = 5

} hostInterface_rxState_t;

#define NDEF_RECORD_MB_MASK		0x80
#define NDEF_RECORD_ME_MASK		0x40
#define NDEF_RECORD_CF_MASK		0x20
#define NDEF_RECORD_SR_MASK		0x10
#define NDEF_RECORD_IL_MASK		0x08
#define NDEF_RECORD_TNF_MASK	0x07

#define NDEF_EMPTY			0x00
#define NDEF_WELL_KNOWN		0x01
#define NDEF_MEDIA			0x02
#define NDEF_ABSOLUTE_URI	0x03
#define NDEF_EXTERNAL		0x04
#define NDEF_UNKNOWN		0x05
#define NDEF_UNCHANGED		0x06
#define NDEF_RESERVED		0x07

typedef enum {
	WELL_KNOWN_SIMPLE_TEXT,
	WELL_KNOWN_SIMPLE_URI,
	WELL_KNOWN_SMART_POSTER,
	WELL_KNOWN_HANDOVER_SELECT,
	MEDIA_VCARD,
	MEDIA_HANDOVER_WIFI,
	MEDIA_HANDOVER_BT,
	ABSOLUTE_URI,
	UNSUPPORTED_NDEF_RECORD = 0xFF
} NdefRecordType_e;

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
const gpio_output_pin_user_config_t
	GPIO_cfg[] = {
  {
    .pinName = KW40_RST,
    .config.outputLogic = 0,
    .config.slewRate = kPortSlowSlewRate,
    .config.isOpenDrainEnabled = false,
    .config.driveStrength = kPortLowDriveStrength,
  },
  {
    .pinName = GPIO_PINS_OUT_OF_RANGE,
  }
};

/*! KW40_UART configuration structure */
const uart_user_config_t KW40_UART_InitConfig = {
  .baudRate = 230400U,
  .parityMode = kUartParityDisabled,
  .stopBitCount = kUartTwoStopBit,
  .bitCountPerChar = kUart8BitsPerChar,
};

/*! Driver state structure without DMA */
uart_state_t KW40_UART_State;

volatile touch_type_t pressedTouch = touch_invalid;

static hostInterface_packet_t hostInterface_rxPacket;

static hostInterface_rxState_t hostInterface_rxState = hostInterface_rxState_idle;

static uint8_t mood_status=2;

static app_mode_t appMode = hexiwear;
//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define KW40_RST_SET()   GPIO_DRV_SetPinOutput( KW40_RST )
#define KW40_RST_CLEAR() GPIO_DRV_ClearPinOutput( KW40_RST )

//-----------------------------------------------------------------------
// Static functions
//-----------------------------------------------------------------------
static void Display_clean(void) {
	OLED_FillScreen(0x0000);
}

static void Display_logo(const uint8_t *logo) {
	oled_dynamic_area_t	IconArea =
		{
			.xCrd = 0,
			.yCrd = 0,
			.width = 96,
			.height = 96
		};
    OLED_SetDynamicArea(&IconArea);
    OLED_DrawImage(logo);
}

static void Display_icon(const uint8_t *icon) {
	oled_dynamic_area_t	IconArea =
		{
			.xCrd = 0,
			.yCrd = 48,
			.width = 96,
			.height = 48
		};
    OLED_SetDynamicArea(&IconArea);
    OLED_DrawImage(icon);
}

static void Display_head(unsigned char *head) {
	oled_text_properties_t HeadText = {
			.font = guiFont_Tahoma_10_Regular,
			.fontColor = 0xFFFF,
			.alignParam = OLED_TEXT_ALIGN_CENTER,
			.background = NULL
	};
	oled_dynamic_area_t HeadArea = {
			.xCrd   = 0,
			.yCrd   = 0,
			.width  = 96,
			.height = 24
	};
	OLED_SetTextProperties(&HeadText);
	OLED_SetDynamicArea(&HeadArea);
	OLED_DrawText(head);
}

static void Display_data(unsigned char *data) {
	oled_text_properties_t DataText = {
			.font = guiFont_Tahoma_7_Regular,
			.fontColor = 0xFFFF,
			.alignParam = OLED_TEXT_ALIGN_CENTER,
			.background = NULL
	};
	oled_dynamic_area_t DataArea = {
			.xCrd   = 0,
			.yCrd   = 24,
			.width  = 96,
			.height = 24
	};
	uint8_t caption[20];
	strncpy((char*)caption, (const char*)data, sizeof(caption));
	if(strlen((char*)caption) > 16) strcpy((char *) &caption[16], "...\0");
	OLED_SetTextProperties(&DataText);
	OLED_SetDynamicArea(&DataArea);
	OLED_DrawText(caption);
}

static unsigned char* GetNextRecord(unsigned char *pNdefRecord)
{
	unsigned char *temp = NULL;

	/* Message End ?*/
	if (!(pNdefRecord[0] & NDEF_RECORD_ME_MASK)) {
		/* Short or normal record ?*/
		if (pNdefRecord[0] & NDEF_RECORD_SR_MASK)
		{
			/* ID present ?*/
			if(pNdefRecord[0] & NDEF_RECORD_IL_MASK)
				temp = (pNdefRecord + 4 + pNdefRecord[1] + pNdefRecord[2] + pNdefRecord[3]);
			else
				temp = (pNdefRecord + 3 + pNdefRecord[1] + pNdefRecord[2]);
		}
		else
		{
			/* ID present ?*/
			if(pNdefRecord[0] & NDEF_RECORD_IL_MASK)
				temp = (pNdefRecord + 7 + pNdefRecord[1] + (pNdefRecord[2]<<24) + (pNdefRecord[3]<<16) + (pNdefRecord[4]<<8) + pNdefRecord[5] + pNdefRecord[6]);
			else
				temp = (pNdefRecord + 6 + pNdefRecord[1] + (pNdefRecord[2]<<24) + (pNdefRecord[3]<<16) + (pNdefRecord[4]<<8) + pNdefRecord[5]);
		}
	}
	return temp;
}

static NdefRecordType_e DetectNdefRecordType(unsigned char *pNdefRecord, unsigned char **ppPayload, unsigned int *pPayloadSize)
{
	uint8_t typeField;

	/* Short or normal record ?*/
	if (pNdefRecord[0] & NDEF_RECORD_SR_MASK)
	{
		*pPayloadSize = pNdefRecord[2];
		typeField = 3;
	}
	else
	{
		*pPayloadSize = (pNdefRecord[2]<<24) + (pNdefRecord[3]<<16) + (pNdefRecord[4]<<8) + pNdefRecord[5];
		typeField = 6;
	}

	/* ID present ?*/
	if(pNdefRecord[0] & NDEF_RECORD_IL_MASK)
	{
		*ppPayload = pNdefRecord + typeField + 2 + pNdefRecord[typeField];
		typeField++;
	}
	else
	{
		*ppPayload = pNdefRecord + typeField + 1;
	}

	/* Well known Record Type ?*/
	if ((pNdefRecord[0] & NDEF_RECORD_TNF_MASK) == NDEF_WELL_KNOWN) {
		if (pNdefRecord[1] == 0x1) {
			switch (pNdefRecord[typeField]) {
			case 'T':
				return WELL_KNOWN_SIMPLE_TEXT;
				break;
			case 'U':
				return WELL_KNOWN_SIMPLE_URI;
				break;
			}
		} else if (pNdefRecord[1] == 0x2) {
			if (memcmp(&pNdefRecord[typeField], "Sp", pNdefRecord[1]) == 0x0) {
				return WELL_KNOWN_SMART_POSTER;
			}
			if (memcmp(&pNdefRecord[typeField], "Hs", pNdefRecord[1]) == 0x0) {
				return WELL_KNOWN_HANDOVER_SELECT;
			}
		}
	}
	/* Media Record Type ?*/
	else if ((pNdefRecord[0] & NDEF_RECORD_TNF_MASK) == NDEF_MEDIA) {
		if ((memcmp(&pNdefRecord[typeField], "text/x-vCard", pNdefRecord[1]) == 0x0)
				|| (memcmp(&pNdefRecord[typeField], "text/vcard", pNdefRecord[1]) == 0x0)) {
			return MEDIA_VCARD;
		} else if (memcmp(&pNdefRecord[typeField], "application/vnd.wfa.wsc", pNdefRecord[1]) == 0x0) {
			return MEDIA_HANDOVER_WIFI;
		} else if (memcmp(&pNdefRecord[typeField], "application/vnd.bluetooth.ep.oob", pNdefRecord[1]) == 0x0) {
			return MEDIA_HANDOVER_WIFI;
		}
	}
	/* Absolute URI Record Type ?*/
	else if ((pNdefRecord[0] & NDEF_RECORD_TNF_MASK) == NDEF_ABSOLUTE_URI) {
		return ABSOLUTE_URI;
	}

	return UNSUPPORTED_NDEF_RECORD;
}

void NdefPull_Cb(unsigned char *pNdefMessage, unsigned short NdefMessageSize) {
	unsigned char *pNdefRecord = pNdefMessage, *pPayload;
	unsigned char *temp, *tmp;
	unsigned int PayloadSize;
	unsigned int red, green, blue;

	Display_logo(nfc_logo_bmp);

	do
	{
		if (pNdefRecord == NULL) return;

		switch (DetectNdefRecordType(pNdefRecord, &pPayload, &PayloadSize))
		{
		case MEDIA_VCARD:
			temp = (unsigned char*) strstr((const char*)pPayload, "FN:");
			if(temp != NULL)
			{
				temp+=3;
				tmp = (unsigned char*)strpbrk ((const char*)temp, "\r\n");
				if(tmp != NULL) *tmp = '\0';
				Display_clean();
				Display_head((unsigned char*) "VCARD");
				Display_data(temp);
			}
			break;

		case WELL_KNOWN_SIMPLE_TEXT:
			PayloadSize = PayloadSize - (pPayload[0]+1);
			pPayload = pPayload+pPayload[0]+1;
			if(!strncmp("RGB:", (const char*)pPayload, 4))
			{
				sscanf((const char*)pPayload+4, "%2x%2x%2x", &red, &green, &blue);
				if(red) {RED_LED_ON();} else {RED_LED_OFF()};
				if(green) {GREEN_LED_ON();} else {GREEN_LED_OFF()};
				if(blue) {BLUE_LED_ON();} else {BLUE_LED_OFF()};
			}
			else if(!strncmp("ACCESS GRANTED", (const char*)pPayload, 13))
			{
				Display_icon(access_granted_bmp);
			}
			else if(!strncmp("ACCESS DENIED", (const char*)pPayload, 12))
			{
				Display_icon(access_denied_bmp);
			}
			else if(!strncmp("MOOD DECREASE", (const char*)pPayload, 13))
			{
				if(mood_status != 0) mood_status--;
			}
			else if(!strncmp("MOOD INCREASE", (const char*)pPayload, 12))
			{
				if(mood_status != 4) mood_status++;
			}
			else
			{
				pPayload[PayloadSize] = '\0';
				Display_clean();
				Display_head((unsigned char *) "TEXT");
				Display_data(pPayload);
			}
			break;

		case WELL_KNOWN_SIMPLE_URI:
			pPayload[PayloadSize] = '\0';
			Display_clean();
			Display_head((unsigned char *) "URL");
			Display_data(pPayload+1);
			break;

		default:
			break;
		}
		pNdefRecord = GetNextRecord(pNdefRecord);
	}
	while (1);
}

void MIFARE_scenario(void) {
	unsigned char Resp[256];
	unsigned char RespSize;
	unsigned char Auth[] = { 0x40, 0x01, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	unsigned char Read[] = { 0x10, 0x30, 0x04};

	if ((NxpNci_ReaderTagCmd(Auth, sizeof(Auth), Resp, &RespSize) == NFC_ERROR) || (Resp[RespSize - 1] != 0)) {
		return;
	}

	/* Perform presence check */
	while ((NxpNci_ReaderTagCmd(Read, sizeof(Read), Resp, &RespSize) == NFC_SUCCESS) && (Resp[RespSize-1] == 0x00)) Sleep(500);
}

void ISO15693_scenario (void)
{
	bool status;
	unsigned char Resp[256];
	unsigned char RespSize;
	unsigned char Inventory[] = {0x26, 0x01, 0x00};

	/* Perform presence check */
	while (1)
	{
		Sleep(500);
		status = NxpNci_ReaderTagCmd(Inventory, sizeof(Inventory), Resp, &RespSize);
		if((status == NFC_ERROR) || (Resp[RespSize-1] == 0xb2)) break;
	}
}

void nfc_init(void)
{
	unsigned char mode = 0;

	/* Open connection to NXPNCI device */
	if (NxpNci_Connect() == NFC_ERROR) {
		return;
	}

	if (NxpNci_ConfigureSettings() == NFC_ERROR) {
		return;
	}

	/* Set NXPNCI in all modes */
	#ifdef CARDEMU_SUPPORT
	mode |= NXPNCI_MODE_CARDEMU;
	#endif
	#ifdef P2P_SUPPORT
	mode |= NXPNCI_MODE_P2P;
	#endif
	#ifdef RW_SUPPORT
	mode |= NXPNCI_MODE_RW;
	#endif
	if (NxpNci_ConfigureMode(mode) == NFC_ERROR)
	{
		return;
	}

	/* Start Discovery */
	if (NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies)) != NFC_SUCCESS)
	{
		return;
	}

	/* Register callback for reception of NDEF message */
	/* Register NDEF message to be sent to remote peer */
	RW_NDEF_RegisterPullCallback(*NdefPull_Cb);
}

void task_nfc(void)
{
	NxpNci_RfIntf_t RfInterface;

	if(NxpNci_WaitForDiscoveryNotification(&RfInterface) == NFC_ERROR) return;

#ifdef CARDEMU_SUPPORT
	/* Is activated from remote T4T ? */
	if ((RfInterface.Interface == INTF_ISODEP) && ((RfInterface.ModeTech & MODE_MASK) == MODE_LISTEN))
	{
#ifndef CARDEMU_RAW_EXCHANGE
		NxpNci_ProcessCardMode(RfInterface);
#else
		PICC_ISO14443_4_scenario();
#endif
	}
	else
#endif

#ifdef P2P_SUPPORT
	/* Is activated from remote T4T ? */
	if (RfInterface.Interface == INTF_NFCDEP)
	{
		/* Process with SNEP for NDEF exchange */
		NxpNci_ProcessP2pMode(RfInterface);
	}
	else
#endif
#ifdef RW_SUPPORT
	if ((RfInterface.ModeTech & MODE_MASK) == MODE_POLL)
	{
	    /* Is card detected MIFARE ?*/
		if(RfInterface.Protocol == PROT_MIFARE)
		{
			/* Run dedicated scenario to demonstrate MIFARE card management */
			MIFARE_scenario();
			/* Restart discovery loop */
			NxpNci_RestartDiscovery();
		}
		/* Is card detected ISO15693 ?*/
		else if (RfInterface.ModeTech == TECH_PASSIVE_15693)
		{
			/* Run dedicated scenario to demonstrate ISO15693 card management */
			ISO15693_scenario();
			/* Restart discovery loop */
			NxpNci_RestartDiscovery();
		}
		/* Is known target ?*/
		else if ((RfInterface.Protocol != PROT_NFCDEP) && (RfInterface.Interface != INTF_UNDETERMINED))
		{
			/* Process NDEF message read */
			NxpNci_ProcessReaderMode(RfInterface, READ_NDEF);
#ifdef T4T_RAW_EXCHANGE
			if (RfInterface.Protocol == PROT_ISODEP)
				PCD_ISO14443_4_scenario();
#endif
			/* Process card Presence check */
			NxpNci_ProcessReaderMode(RfInterface, PRESENCE_CHECK);
			/* Restart the discovery loop */
			NxpNci_RestartDiscovery();
		}
		else
		{
			/* Restart discovery loop */
			NxpNci_StopDiscovery();
			NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies));
		}
	}
	else
#endif
	{
	}
}

void task_app(void)
{
	if (touch_invalid != pressedTouch)
	{
		switch (pressedTouch)
		{
		case touch_left:
			if (--appMode == first) appMode = last-1;
			break;

		case touch_right:
			if (++appMode == last) appMode = first+1;
			break;

		default:
			break;
		}
		pressedTouch = touch_invalid;
	}

	switch(appMode)
	{
	case hexiwear:
		Display_logo(hexiwear_logo_bmp);
		P2P_NDEF_SetMessage((unsigned char *) NdefRecord_HexiwearApp, sizeof(NdefRecord_HexiwearApp), NULL);
		break;
	case mood:
		Display_logo(mood_status_bmp[mood_status]);
		P2P_NDEF_SetMessage((unsigned char *) NULL, 0, NULL);
		break;
	case bluetooth:
		Display_logo(bluetooth_logo_bmp);
		P2P_NDEF_SetMessage((unsigned char *) NdefRecord_BluetoothHandover, sizeof(NdefRecord_BluetoothHandover), NULL);
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------

int main(void)
{
	CLOCK_SYS_EnablePortClock(PORTA_IDX);
	CLOCK_SYS_EnablePortClock(PORTB_IDX);
    CLOCK_SYS_EnablePortClock(PORTC_IDX);
	CLOCK_SYS_EnablePortClock(PORTD_IDX);
	CLOCK_SYS_EnablePortClock(PORTE_IDX);

    g_xtal0ClkFreq = 12000000U;
    g_xtalRtcClkFreq = 32768U;

	/** configure UART pins */
    PORT_HAL_SetMuxMode( PORTE, 24u, kPortMuxAlt3 );
    PORT_HAL_SetMuxMode( PORTE, 25u, kPortMuxAlt3 );

    /** configure SPI2 pins */
    PORT_HAL_SetMuxMode( PORTB, 21UL, kPortMuxAlt2 );
    PORT_HAL_SetMuxMode( PORTB, 22UL, kPortMuxAlt2 );

    /** configure I2C pins */
    PORT_HAL_SetMuxMode( PORTD, 8UL, kPortMuxAlt2 );
    PORT_HAL_SetMuxMode( PORTD, 9UL, kPortMuxAlt2 );

    OSA_Init();

    GPIO_DRV_Init( pir_input_cfg, pir_output_cfg );
    GPIO_DRV_Init( NULL, OLED_cfg );
    GPIO_DRV_Init( NULL, PWR_cfg );
    GPIO_DRV_Init( NULL, RGB_cfg );
	GPIO_DRV_Init( NULL, GPIO_cfg );
    GPIO_DRV_Init( nfcInPins, nfcOutPins );

    EDMA_DRV_Init( &DMA_controller_State, &DMA_controller_InitConfig0 );
    DSPI_DRV_EdmaMasterInit(FSL_OLED_SPI, &OLED_SPI_MasterState, &OLED_SPI_MasterConfig, &OLED_SPI_dmaTcd);
    DSPI_DRV_EdmaMasterConfigureBus(FSL_OLED_SPI, &OLED_SPI_BusConfig, &OLED_SPI_calculatedBaudRate);

    OLED_Init( &oledModule, &oledSettings );

    // initialize UART to KW40
	UART_DRV_Init( FSL_KW40_UART, &KW40_UART_State, &KW40_UART_InitConfig );

	__enable_irq();
	NVIC_EnableIRQ( UART4_RX_TX_IRQn );
	NVIC_EnableIRQ( PORTB_IRQn );

	UART_DRV_InstallRxCallback( FSL_KW40_UART, PacketParser, (uint8_t*)&hostInterface_rxPacket, NULL, true );

    // Reset KW40
    KW40_RST_CLEAR();
    OSA_TimeDelay( 10 );
    KW40_RST_SET();
    OSA_TimeDelay( 200 );

    nfc_init();

	/* Create NFC task */
	if (OSA_TaskCreate((task_t) task_nfc, (uint8_t*) "NFC task",
					   TASK_NFC_STACK_SIZE, task_nfc_stack,
					   TASK_NFC_STACK_PRIO, (task_param_t) 0,
					   false, &task_nfc_task_handler) != kStatus_OSA_Success) {
		return 1;
	}

	/* Create Application task */
	if (OSA_TaskCreate((task_t) task_app, (uint8_t*) "APP task",
					   TASK_APP_STACK_SIZE, task_app_stack,
					   TASK_APP_STACK_PRIO, (task_param_t) 0,
					   false, &task_app_task_handler) != kStatus_OSA_Success) {
		return 1;
	}

	OSA_Start();

	return 0;
}

static void PacketParser(
							uint32_t instance,
							void* uartState
						)
{
    static uint8_t byteCount;

    uart_state_t* state = (uart_state_t*)uartState;

    switch ( hostInterface_rxState )
    {
        case hostInterface_rxState_idle:
        {
            if ( gHostInterface_startByte1 == hostInterface_rxPacket.start1 )
            {
                hostInterface_rxState++;
                state->rxBuff++;
            }

            break;
        }

        case hostInterface_rxState_headerReceived:
        {
            if  (
                ( gHostInterface_startByte1 != hostInterface_rxPacket.start1 )
                ||     ( gHostInterface_startByte2 != ( hostInterface_rxPacket.start2 &
                         0xFE ) )
                || ( hostInterface_rxPacket.length >  gHostInterface_dataSize )
            )
            {
                // return to idle state
                hostInterface_rxState = hostInterface_rxState_idle;
                // reset the RX buffer pointer
                state->rxBuff = ( uint8_t * )&hostInterface_rxPacket;
            }

            else
            {
                // advance the buffer pointer
            	state->rxBuff++;

                if ( 0 == hostInterface_rxPacket.length )
                {
                    // advance to "wait-trailer-bit" state
                    hostInterface_rxState = hostInterface_rxState_trailerWait;
                }

                else
                {
                    byteCount = 0;
                    // advance to "data-wait" state
                    hostInterface_rxState = hostInterface_rxState_dataWait;
                }
            }

            break;
        }

        case hostInterface_rxState_dataWait:
        {
            byteCount++;
            state->rxBuff++;

            // if we reached the byte-count
            if  ( hostInterface_rxPacket.length == byteCount )
            {
                // advance to "wait-trailer-bit" state
                hostInterface_rxState = hostInterface_rxState_trailerWait;
            }

            break;
        }

        case hostInterface_rxState_trailerWait:
        {
            if ( gHostInterface_trailerByte == *(state->rxBuff) )
            {
                switch ( hostInterface_rxPacket.type )
                {
                    case packetType_pressRight:
                    {
                        pressedTouch = touch_right;
                        break;
                    }
                    case packetType_pressUp:
                    {
                        pressedTouch = touch_right;
                        break;
                    }
                    case packetType_pressLeft:
                    {
                        pressedTouch = touch_left;
                        break;
                    }
                    case packetType_pressDown:
                    {
                        pressedTouch = touch_left;
                        break;
                    }
                    default:
                    {
                        pressedTouch = touch_invalid;
                    }
                }
            }

            // go back to the idle state
            hostInterface_rxState = hostInterface_rxState_idle;
            // reset the RX buffer pointer
            state->rxBuff = ( uint8_t * )&hostInterface_rxPacket;
            break;
        }

        default:
        {
            hostInterface_rxState++;
            state->rxBuff++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////


