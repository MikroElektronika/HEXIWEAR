//-----------------------------------------------------------------------
// Standard C/C++ Includes
//-----------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <nfc_task.h>
#include <nfc.h>
#include <tool.h>
#include "error.h"
#include "fsl_os_abstraction.h"
#include "gui_pedometer.h"
#include "gui_heartRate.h"
#include "GPIO.h"
#include "flashlight.h"

static task_handler_t nfc_TaskHandler;
static bool isNfcActive = false;

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

const char NdefRecord_HexiwearApp[] = { 0xD4,
		0x0F,
		0x16,
		'a','n','d','r','o','i','d','.','c','o','m',':','p','k','g',
		'c','o','m','.','w','o','l','k','a','b','o','u','t','.','h','e','x','i','w','e','a','r'
};

const char NdefRecord_BluetoothHandover[] = { 0xD2,
		0x20, // type length
		0x12, // payload length
		'a','p','p','l','i','c','a','t','i','o','n','/','v','n','d','.','b','l','u','e','t','o','o','t','h','.','e','p','.','o','o','b',
		0x12, 0x00, // OOB data length
		0x45, 0x00, 0x0B, 0x40, 0x36, 0x00, // BT address (little-endian)
		0x09, 0x09,	'H','E','X','I','W','E','A','R' // BT local name
};

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

static void NdefPull_Cb(unsigned char *pNdefMessage, unsigned short NdefMessageSize) {
	unsigned char *pNdefRecord = pNdefMessage, *pPayload;
	unsigned int PayloadSize;
	uint32_t relay, led;

	if(DetectNdefRecordType(pNdefRecord, &pPayload, &PayloadSize) == WELL_KNOWN_SIMPLE_TEXT)
	{
		PayloadSize = PayloadSize - (pPayload[0]+1);
		pPayload = pPayload+pPayload[0]+1;
		if(!strncmp("Pedometer", (const char*)pPayload, 8))
		{
			/* Launch Pedometer application */
			GuiDriver_Navigation( GUI_NAVIGATION_DIRECT, &pedometerScreen);
		}
		else if(!strncmp("HeartRate", (const char*)pPayload, 8))
		{
			/* Launch Heart rate monitor application */
			GuiDriver_Navigation( GUI_NAVIGATION_DIRECT, &heartRateScreen);
		}
		else if(!strncmp("REL", (const char*)pPayload, 3))
		{
			/* retrieve relay number */
			if(!strncmp("1:", (const char*)pPayload+3, 2)) relay=REL1, led=GREEN_LED;
			else if(!strncmp("2:", (const char*)pPayload+3, 2)) relay=REL2, led=BLUE_LED;
			else return;

			/* retrieve action */
			if(!strncmp("ON", (const char*)pPayload+5, 2))
			{
				GPIO_DRV_ClearPinOutput(led);
				GPIO_DRV_SetPinOutput(relay);
			}
			else if(!strncmp("OFF", (const char*)pPayload+5, 3))
			{
				GPIO_DRV_SetPinOutput(led);
				GPIO_DRV_ClearPinOutput(relay);
			}
			else
			{
				/* toggle */
				GPIO_DRV_TogglePinOutput(led);
				GPIO_DRV_TogglePinOutput(relay);
			}
		}
	}
}

static void MIFARE_scenario(void) {
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

static void ISO15693_scenario (void)
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

unsigned char DiscoveryTechnologies[] = {
#if defined P2P_SUPPORT || defined RW_SUPPORT
		MODE_POLL | TECH_PASSIVE_NFCA,
		MODE_POLL | TECH_PASSIVE_NFCF,
#endif
#ifdef RW_SUPPORT
		MODE_POLL | TECH_PASSIVE_NFCB,
		MODE_POLL | TECH_PASSIVE_15693,
#endif
#ifdef P2P_SUPPORT
		MODE_POLL | TECH_ACTIVE_NFCA,
#endif
#if defined P2P_SUPPORT || defined CARDEMU_SUPPORT
		MODE_LISTEN | TECH_PASSIVE_NFCA,
#endif
#if defined CARDEMU_SUPPORT
		MODE_LISTEN | TECH_PASSIVE_NFCB,
#endif
#ifdef P2P_SUPPORT
		MODE_LISTEN | TECH_PASSIVE_NFCF,
		MODE_LISTEN | TECH_ACTIVE_NFCA,
		MODE_LISTEN | TECH_ACTIVE_NFCF,
#endif
		};

static bool init(void)
{
	/* Open connection to NXPNCI device */
	if (NxpNci_Connect() == NFC_ERROR) {
		return false;
	}

	#ifdef P2P_SUPPORT
	/* Register NDEF message to be sent to remote peer */
	P2P_NDEF_SetMessage((unsigned char *) NdefRecord_HexiwearApp, sizeof(NdefRecord_HexiwearApp), NULL);
	#endif

	#ifdef RW_SUPPORT
	/* Register callback for reception of NDEF message */
	RW_NDEF_RegisterPullCallback(*NdefPull_Cb);
	#endif

	return true;
}

static void nfc_Task(task_param_t param)
{
	NxpNci_RfIntf_t RfInterface;

	unsigned char mode = 0;

	if (NxpNci_ConfigureSettings() == NFC_ERROR) {
		NxpNci_Disconnect();
		isNfcActive = false;
		return;
	}

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
		NxpNci_Disconnect();
		isNfcActive = false;
		return;
	}

	/* Start Discovery */
	if (NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies)) != NFC_SUCCESS)
	{
		NxpNci_Disconnect();
		isNfcActive = false;
		return;
	}

	while(1)
	{
		if(NxpNci_WaitForDiscoveryNotification(&RfInterface) == NFC_ERROR) break;

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

	NxpNci_Disconnect();
	isNfcActive = false;
}

bool nfc_task_init(void)
{
	osa_status_t status;

	if(!init()) return false;

	status = OSA_TaskCreate ( nfc_Task, (uint8_t *) "nfc_Task", 1200, NULL,
							  10,
							  (task_param_t)0,
							  false,
							  &nfc_TaskHandler
						    );
	if ( kStatus_OSA_Success != status )
	{
		catch( CATCH_INIT );
	}

	isNfcActive = true;
	return true;
}

bool nfc_task_deinit(void)
{
	OSA_TaskDestroy(nfc_TaskHandler);

	NxpNci_Disconnect();

	isNfcActive = false;
	return true;
}

bool nfc_task_isActive(void)
{
	return isNfcActive;
}

