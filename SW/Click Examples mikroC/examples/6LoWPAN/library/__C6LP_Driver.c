/**
 * @file 6LoWPAN_C_click.c
 * @brief 6LoWPAN C click driver
 *
 ******************************************************************************/

/*******************************************************************************
********************************************************************************
* Includes
********************************************************************************
*******************************************************************************/

#include <string.h>
#include "__C6LP_Driver.h"

/*******************************************************************************
********************************************************************************
* Preprocessor Constants
********************************************************************************
*******************************************************************************/

// Packet and packet part lengths
#define PKT_LEN_MIC                         8
#define PKT_LEN_SEC                         PKT_LEN_UNSEC + PKT_LEN_MIC
#define PKT_LEN_AUTH                        8
#define PKT_LEN_ENCR                        24

// Packet overhead ((frame control field, sequence number, PAN ID,
// destination and source) + (footer))
// Note that the length byte itself is not included included in packet length
#define C6LP_PACKET_OVERHEAD_SIZE   ((2 + 1 + 2 + 2 + 2) + (2))
#define C6LP_MAX_PAYLOAD_SIZE       (127 - C6LP_PACKET_OVERHEAD_SIZE - \
    C6LP_AUX_HDR_LENGTH - C6LP_LEN_MIC)
#define C6LP_ACK_PACKET_SIZE        5
#define C6LP_FOOTER_SIZE            2
#define C6LP_HDR_SIZE               10

// The time it takes for the acknowledgment packet to be received after the
// data packet has been transmitted.
#define C6LP_ACK_DURATION (0.5 * 32 * 2 * ((4 + 1) + (1) + (2 + 1) + (2)))
#define C6LP_SYMBOL_DURATION                (32 * 0.5)

// The length byte
#define C6LP_PLD_LEN_MASK               0x7F

// Frame control field
#define C6LP_FCF_NOACK               0x8841
#define C6LP_FCF_ACK                 0x8861
#define C6LP_FCF_ACK_BM              0x0020
#define C6LP_FCF_BM                  (~C6LP_FCF_ACK_BM)
#define C6LP_SEC_ENABLED_FCF_BM      0x0008

// Frame control field LSB
#define C6LP_FCF_NOACK_L             ((C6LP_FCF_NOACK) & 0xFF)
#define C6LP_FCF_ACK_L               ((C6LP_FCF_ACK) & 0xFF)
#define C6LP_FCF_ACK_BM_L            ((C6LP_FCF_ACK_BM) & 0xFF)
#define C6LP_FCF_BM_L                ((C6LP_FCF_BM) & 0xFF)
#define C6LP_SEC_ENABLED_FCF_BM_L    ((C6LP_SEC_ENABLED_FCF_BM) & 0xFF)

// Auxiliary Security header
#define C6LP_AUX_HDR_LENGTH             5
#define C6LP_LEN_AUTH                   C6LP_PACKET_OVERHEAD_SIZE + \
    C6LP_AUX_HDR_LENGTH - C6LP_FOOTER_SIZE
#define C6LP_SECURITY_M                 2
#define C6LP_LEN_MIC                    8

// Footer
#define C6LP_CRC_OK_BM                  0x80

/*******************************************************************************
********************************************************************************
* Typedefs
********************************************************************************
*******************************************************************************/

// The receive struct
typedef struct
{
    uint8_t seqNumber;
    uint16_t srcAddr;
    uint16_t srcPanId;
    int8_t length;
    uint8_t* pPayload;
    uint8_t ackRequest;
    int8_t rssi;
    volatile uint8_t isReady;
    uint8_t status;
}
T_C6LP_rxInfo;

// Tx state
typedef struct
{
    uint8_t txSeqNumber;
    volatile uint8_t ackReceived;
    uint8_t receiveOn;
    uint32_t frameCounter;
}
T_C6LP_txState;

// Basic RF packet header (IEEE 802.15.4)
typedef struct
{
    uint8_t   packetLength;
    uint8_t   fcf0;           // Frame control field LSB
    uint8_t   fcf1;           // Frame control field MSB
    uint8_t   seqNumber;
    uint16_t  panId;
    uint16_t  destAddr;
    uint16_t  srcAddr;
}
T_C6LP_pktHdr;

/*******************************************************************************
********************************************************************************
* Memory Declarations
********************************************************************************
*******************************************************************************/

static T_C6LP_rxInfo  rxi =      { 0xFF }; // Make sure sequence numbers are
static T_C6LP_txState txState =  { 0x00 }; // initialised and distinct.

static T_C6LP_cfg* pConfig;
static uint8_t txMpdu[C6LP_MAX_PAYLOAD_SIZE + C6LP_PACKET_OVERHEAD_SIZE + 1];
static uint8_t rxMpdu[128];

/*******************************************************************************
********************************************************************************
* Private Function Prototypes
********************************************************************************
*******************************************************************************/

static uint8_t C6LP_BuildHeader(
    uint8_t* buffer, uint16_t destAddr, uint8_t payloadLength);
static uint8_t C6LP_buildMpdu(
    uint16_t destAddr, uint8_t* pPayload, uint8_t payloadLength);

static uint8_t C6LP_disableRxInterrupt(void);
static uint8_t C6LP_enableRxInterrupt(void);

/*******************************************************************************
********************************************************************************
* Private Functions
********************************************************************************
*******************************************************************************/

static uint8_t C6LP_BuildHeader(
    uint8_t* buffer, uint16_t destAddr, uint8_t payloadLength)
{
    T_C6LP_pktHdr *pHdr;
    uint16_t fcf;

    pHdr = (T_C6LP_pktHdr*)buffer;

    // Populate packet header
    pHdr->packetLength = payloadLength + C6LP_PACKET_OVERHEAD_SIZE;
    // pHdr->frameControlField =
    //     pConfig->ackRequest ? BASIC_RF_FCF_ACK : BASIC_RF_FCF_NOACK;
    fcf= pConfig->ackRequest ? C6LP_FCF_ACK : C6LP_FCF_NOACK;
    pHdr->fcf0 = fcf & 0xFF;
    pHdr->fcf1 = (fcf >> 8) & 0xFF;
    pHdr->seqNumber= txState.txSeqNumber;
    pHdr->panId= pConfig->panId;
    pHdr->destAddr= destAddr;
    pHdr->srcAddr= pConfig->myAddr;

    return C6LP_HDR_SIZE;
}

static uint8_t C6LP_buildMpdu(
    uint16_t destAddr, uint8_t* pPayload, uint8_t payloadLength)
{
    uint8_t hdrLength, n;

    hdrLength = C6LP_BuildHeader(txMpdu, destAddr, payloadLength);

    for (n=0; n<payloadLength; n++)
    {
        txMpdu[hdrLength + n] = pPayload[n];
    }
    return hdrLength + payloadLength; // total mpdu length
}

static uint8_t C6LP_disableRxInterrupt(void)
{
    C6LP_halDisableRxInterrupt();
    C6LP_userDisableRxInterrupt();
}

static uint8_t C6LP_enableRxInterrupt(void)
{
    C6LP_halEnableRxInterrupt();
    C6LP_userEnableRxInterrupt();
}

/*******************************************************************************
********************************************************************************
* Public Functions
********************************************************************************
*******************************************************************************/

uint8_t C6LP_init(T_C6LP_cfg* pRfConfig)
{
    C6LP_halInit();
    if (C6LP_halInit()==FAILED)
        return FAILED;

    DisableInterrupts();

    // Set the protocol configuration
    pConfig = pRfConfig;
    rxi.pPayload = 0;

    txState.receiveOn = TRUE;
    txState.frameCounter = 0;

    // Set channel
    C6LP_halSetChannel(pConfig->channel);

    // Write the short address and the PAN ID to the CC2520 RAM
    C6LP_halSetShortAddr(pConfig->myAddr);
    C6LP_halSetPanId(pConfig->panId);

    // Set up receive interrupt (received data or acknowlegment)
    C6LP_halRxInterruptConfig();

    EnableInterrupts();

    return SUCCESS;
}

uint8_t C6LP_sendPacket(uint16_t destAddr, uint8_t* pPayload, uint8_t length)
{
    uint8_t mpduLength;
    uint8_t status;

    // Turn on receiver if its not on
    if(!txState.receiveOn)
        C6LP_receiveOn();

    // Check packet length
    length = (length < C6LP_MAX_PAYLOAD_SIZE) ?
              length :
              C6LP_MAX_PAYLOAD_SIZE;
    
    // Wait until the transceiver is idle
    C6LP_halWaitTransceiverReady();

    // Turn off RX frame done interrupt
    // to avoid interference on the SPI interface
    C6LP_disableRxInterrupt();

    mpduLength = C6LP_buildMpdu(destAddr, pPayload, length);

    C6LP_halWriteTxBuf(txMpdu, mpduLength);

    // Turn on RX frame done interrupt for ACK reception
    C6LP_enableRxInterrupt();

    // Send frame with CCA. return FAILED if not successful
    if(C6LP_halTransmit() != SUCCESS)
        status = FAILED;

    // Wait for the acknowledge to be received, if any
    if (pConfig->ackRequest)
    {
        txState.ackReceived = FALSE;

        // We'll enter RX automatically, so just wait until we can be sure
        // that the ack reception should have finished
        // The timeout consists of a 12-symbol turnaround time,
        // the ack packet duration, and a small margin
        Delay_us((12 * 16) + (352) + (2 * 16) + 10);

        // If an acknowledgment has been received (by RxFrmDoneIsr),
        // the ackReceived flag should be set
        status = txState.ackReceived ? SUCCESS : FAILED;

    }
    else
    {
        status = SUCCESS;
    }

    // Turn off the receiver if it should not continue to be enabled
    if (!txState.receiveOn)
        C6LP_receiveOff();

    if(status == SUCCESS)
        txState.txSeqNumber++;

    return status;
}

uint8_t C6LP_isPacketReady(void)
{
    return rxi.isReady;
}

uint8_t C6LP_receive(uint8_t* pRxData, uint8_t len, int16_t* pRssi)
{
    // Accessing shared variables -> this is a critical region
    // Critical region start
    DisableInterrupts();
    memcpy(pRxData, rxi.pPayload, (rxi.length < len) ? rxi.length : len);
    if(pRssi != 0) {
        if(rxi.rssi < 128){
            *pRssi = rxi.rssi - C6LP_halGetRssiOffset();
        }
        else{
            *pRssi = (rxi.rssi - 256) - C6LP_halGetRssiOffset();
        }
    }
    rxi.isReady = FALSE;

    // Critical region end
    EnableInterrupts();

    return (rxi.length < len) ? rxi.length : len;
}

int8_t C6LP_getRssi(void)
{
    if(rxi.rssi < 128){
        return rxi.rssi - C6LP_halGetRssiOffset();
    }
    else{
        return (rxi.rssi - 256) - C6LP_halGetRssiOffset();
    }
}

void C6LP_receiveOn(void)
{
    txState.receiveOn = TRUE;
    C6LP_halReceiveOn();
}

void C6LP_receiveOff(void)
{
    txState.receiveOn = FALSE;
    C6LP_halReceiveOff();
}

void C6LP_rxFrmDoneIsr(void)
{
    T_C6LP_pktHdr *pHdr;
    uint8_t *pStatusWord;

    // Map header to packet buffer
    pHdr = (T_C6LP_pktHdr*)rxMpdu;

    // Clear interrupt and disable new RX frame done interrupt
    C6LP_disableRxInterrupt();

    // Enable all other interrupt sources (enables interrupt nesting)
    EnableInterrupts();

    // Read payload length.
    C6LP_halReadRxBuf(&pHdr->packetLength, 1);
    pHdr->packetLength &= C6LP_PLD_LEN_MASK; // Ignore MSB
    
    // Is this an acknowledgment packet?
    // Only ack packets may be 5 bytes in total.
    if (pHdr->packetLength == C6LP_ACK_PACKET_SIZE)
    {
        // Read the packet
        C6LP_halReadRxBuf(&rxMpdu[1], pHdr->packetLength);

        rxi.ackRequest = !!(pHdr->fcf0 & C6LP_FCF_ACK_BM_L);

        // Read the status word and check for CRC OK
        pStatusWord= rxMpdu + 4;

        // Indicate the successful ACK reception if CRC and sequence number OK
        if ((pStatusWord[1] & C6LP_CRC_OK_BM) &&
            (pHdr->seqNumber == txState.txSeqNumber))
        {
            txState.ackReceived = TRUE;
        }
    }
    else // No, it is data
    {
        // It is assumed that the radio rejects packets with invalid length.
        // Subtract the number of bytes in the frame overhead
        // to get actual payload.

        rxi.length = pHdr->packetLength - C6LP_PACKET_OVERHEAD_SIZE;

        C6LP_halReadRxBuf(&rxMpdu[1], pHdr->packetLength);

        rxi.ackRequest = !!(pHdr->fcf0 &C6LP_FCF_ACK_BM_L);

        // Read the source address
        rxi.srcAddr= pHdr->srcAddr;

        // Read the packet payload
        rxi.pPayload = rxMpdu + C6LP_HDR_SIZE;

        // Read the FCS to get the RSSI and CRC
        pStatusWord= rxi.pPayload + rxi.length;
        rxi.rssi = pStatusWord[0];

        // Notify the application about the received data packet
        // if the CRC is OK
        // Throw packet if the previous packet had the same sequence number
        if ((pStatusWord[1] & C6LP_CRC_OK_BM) &&
            (rxi.seqNumber != pHdr->seqNumber))
        {
            if ((pHdr->fcf0 & (C6LP_FCF_BM_L)) == C6LP_FCF_NOACK_L)
            {
                rxi.isReady = TRUE;
            }
        }
        rxi.seqNumber = pHdr->seqNumber;
    }
    
    // Enable RX frame done interrupt again
    DisableInterrupts();
    C6LP_enableRxInterrupt();
}