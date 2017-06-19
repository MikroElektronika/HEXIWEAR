/*! *********************************************************************************
 * \defgroup FSCI BLE OTAP
 * @{
 ********************************************************************************** */
/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * \file fsci_ble_otap.h
 * This file is the interface file for the BLE OTAP FSCI module
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
 */

#ifndef _FSCI_BLE_OTAP_H_
#define _FSCI_BLE_OTAP_H_

/*************************************************************************************
**************************************************************************************
* Public macros
**************************************************************************************
*************************************************************************************/

#define gFsciBleOtapOpcodeGroup_c       0x4F

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
* \brief  Registers an interface to be used with the BLE OTAP FSCI module.
*
* \param[in]    fsciInterfaceId     Interface to be registered.
*
********************************************************************************** */
void FsciBleOtap_Register (uint32_t fsciInterfaceId);

/*! *********************************************************************************
* \brief  Handles BLE OTAP FSCI messages received on the FSCI interface
*         and associated with the BLE OTAP FACI Opcode Group.
*
* \param[in]    pData               Packet (containing FSCI header and FSCI 
*                                   payload) received over UART   
* \param[in]    param               Pointer given when this function is registered
*                                   in FSCI
* \param[in]    fsciInterfaceId     FSCI interface on which the packet was received  
*
********************************************************************************** */
void FsciBleOtap_Handler (void*     pData, 
                          void*     param,
                          uint32_t  fsciInterface);

/*! *********************************************************************************
* \brief  Allocates a FSCI packet for the BLE OTAP FSCI module.
*
* \param[in]    opCode      FSCI BLE OTAP operation code.
* \param[in]    dataSize    Size of the payload.
*
* \return       Returns a pointer to the allocated packet or NULL if it could
*               not be allocated.
*
********************************************************************************** */
clientPacketStructured_t* FsciBleOtap_AllocatePacket (opCode_t  opCode, 
                                                      uint16_t  dataSize);
                                                      
/*! *********************************************************************************
* \details  Allocates a FSCI BLE OTAP packet with the specified opcode, payload
*           and payload length and sends it over the FSCI interface.
*
********************************************************************************** */
/*! *********************************************************************************
* \brief  Allocates and send a FSCI packet for the BLE OTAP FSCI module
*         having the specified opcode and the given payload and length.
*
* \param[in]    pOpCode     Pointer to the FSCI BLE OTAP operation code.
* \param[in]    pPayload    Pointer to the packet payload.
* \param[in]    payloadLen  Payload length.
*
********************************************************************************** */
void FsciBleOtap_SendPkt (opCode_t* pOpCode,
                          uint8_t*  pPayload,
                          uint16_t  payloadLen);

#ifdef __cplusplus
}
#endif 


#endif /* _FSCI_BLE_OTAP_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */