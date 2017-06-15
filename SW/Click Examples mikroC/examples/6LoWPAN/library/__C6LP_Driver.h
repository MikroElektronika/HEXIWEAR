/**
 * @file 6LoWPAN_C_click.h
 * @brief 6LoWPAN C click driver
 *
 ******************************************************************************/

#ifndef __C6LP_H_
#define __C6LP_H_

/*******************************************************************************
********************************************************************************
* Includes
********************************************************************************
*******************************************************************************/

#include "__C6LP_Hal.h"

/*******************************************************************************
********************************************************************************
* Typedefs
********************************************************************************
*******************************************************************************/

/**
* @struct 6LoWPAN click configuration
*
* Configures the click with all the required parameters.
*/
typedef struct
{
    uint16_t myAddr; /**< Short address of this device */
    uint16_t panId; /**< ID of the PAN that this device belongs to */
    uint8_t channel; /**< Channel to use */
    uint8_t ackRequest; /**< Indicates whether we request ack */
}
T_C6LP_cfg;

/*******************************************************************************
********************************************************************************
* Public Function Prototypes
********************************************************************************
*******************************************************************************/

/**
* @brief Chip init.
*
* @param[in] pRfConfig pointer to BASIC_RF_CONFIG struct,
* must be allocated by user
*
* @return none
*
* Function initialises basic RF datastructures. Sets channel, short address
* and PAN id in the chip and configures interrupt on packet reception.
*/
uint8_t C6LP_init(T_C6LP_cfg* pRfConfig);

/**
* @brief Sends a packet.
*
* @param[in] destAddr destination short address
* @param[in] pPayload pointer to payload buffer, must be allocated by user
* @param[in] length length of payload
*
* @retval SUCCESS send successful
* @retval FAILED send unsuccessful
*
* Function writes a packet to the TX buffer and transmits it.
* It will also wait if acknowledge is to be received.
*/
uint8_t C6LP_sendPacket(uint16_t destAddr, uint8_t* pPayload, uint8_t length);

/**
* @brief Checks if a new packet is ready.
*
* @return packet ready indication
*
* Function checks if a new packet is ready to be read by next higher layer.
*/
uint8_t C6LP_isPacketReady(void);

/**
* @brief Returns the last incoming packet.
*
* @param[out] pRxData pointer to data buffer to fill, must be allocated by user
* @param[in] number of bytes to read to buffer
* @param[out] pRssi pointer to the rssi value return location
*
* @return number of bytes actually copied into buffer
*
* Function  copies the payload of the last incoming packer into a buffer.
*/
uint8_t C6LP_receive(uint8_t* pRxData, uint8_t len, int16_t* pRssi);

/**
* @brief Returns the rssi value.
*
* @return RSSI value
*
* Function returns the rssi value from the chip.
*/
int8_t C6LP_getRssi(void);

/**
* @brief Turns on the receiver on radio.
*
* @return none
*
* Function turns the chip receiver on, so packets can be received.
*/
void C6LP_receiveOn(void);

/**
* @brief Turns off the receiver on radio.
*
* @return none
*
* Function turns the chip receiver off, so packets can't be received.
* This is done to preserve power when reception is not necessarry.
*/
void C6LP_receiveOff(void);

/**
* @brief Rx interrupt service routine.
*
* @return none
*
* Interrupt service routine for received frame from radio
* (either data or acknowlegdement).
*
* @note The user needs to call this routine from their interrupt routine
* which is bound to the INT pin of the mikroBUS socket
* that the 6LoWPAN C click is attached to.
*/
void C6LP_rxFrmDoneIsr(void);

/**
* @brief Disables rx interrupt.
*
* @return none
*
* Function disables the rx interrupt.
*
* @note The user needs to define this function
* according to the interrupt assigned to the rx of the 6LoWPAN click.
*/
void C6LP_userDisableRxInterrupt(void);

/**
* @brief Enables rx interrupt.
*
* @return none
*
* Function enables the rx interrupt.
*
* @note The user needs to define this function
* according to the interrupt assigned to the rx of the 6LoWPAN click.
*/
void C6LP_userEnableRxInterrupt(void);

/**
* @brief SPI send/receive.
*
* @param[in] x byte to send
*
* @return received byte
*
* Function performs a SPI transfer, sending one byte to the click,
* and receiving a byte from the click.
*
* @note The user needs to define this function
* according to the SPI that communicates with the 6LoWPAN click.
*/
uint8_t C6LP_spiRxTx(uint8_t x);

#endif