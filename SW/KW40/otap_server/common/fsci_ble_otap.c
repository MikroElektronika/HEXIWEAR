/*! *********************************************************************************
* \addtogroup FSCI BLE OTAP
* @{
********************************************************************************** */
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
* \file app.c
* This file is the source file for the BLE OTAP FSCI module
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

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "panic.h"
#include "FsciInterface.h"
#include "MemManager.h"
#include "FunctionLib.h"

#include "fsci_ble_otap.h"



/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/

#define FsciBleOtap_IsInterfaceValid(interface)     ((interface) < gFsciMaxInterfaces_c? TRUE : FALSE)

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static uint32_t mFsciBleOtapInterfaceId = mFsciInvalidInterface_c;

/************************************************************************************
*************************************************************************************
* External memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* External functions prototypes
*************************************************************************************
************************************************************************************/

/*! This is the application function which handles commands received for the
*   BLE OTAP module via the FSCI interface.
*/
extern void BleApp_HandleFsciBleOtapCommand (clientPacket_t*    pData,
                                             uint32_t           fsciInterface);

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \details  Register a FSCI interface for the BLE OTAP FSCI module.
*
********************************************************************************** */
void FsciBleOtap_Register (uint32_t fsciInterfaceId)
{
#if gFsciBleOtapEnabled_d
    if (gFsciSuccess_c != FSCI_RegisterOpGroup (gFsciBleOtapOpcodeGroup_c, 
                                                gFsciMonitorMode_c, 
                                                FsciBleOtap_Handler, 
                                                NULL,
                                                fsciInterfaceId))
    {
        panic(0, (uint32_t)FsciBleOtap_Register, 0, 0);
    }
    else
    {
        mFsciBleOtapInterfaceId = fsciInterfaceId;
    }
#endif /* gFsciBleOtapEnabled_d */
}


#if gFsciBleOtapEnabled_d
/*! *********************************************************************************
* \details  BLE OTAP FSCI messages handler.
*
********************************************************************************** */
void FsciBleOtap_Handler (void*     pData, 
                          void*     param,
                          uint32_t  fsciInterface)
{
    BleApp_HandleFsciBleOtapCommand ((clientPacket_t*)pData,
                                     fsciInterface);
    
    MEM_BufferFree (pData);
}
#endif /* gFsciBleOtapEnabled_d */


#if gFsciBleOtapEnabled_d
/*! *********************************************************************************
* \details  Allocates a FSCI packet for the BLE OTAP FSCI module using the
*           set up memory allocator and retruns a pointer to theat packet.
*           Allocated length: FSCI header size + data size + FSCI packet CRC size.
*
********************************************************************************** */
clientPacketStructured_t* FsciBleOtap_AllocatePacket (opCode_t  opCode, 
                                                      uint16_t  dataSize)
{
    clientPacketStructured_t* pClientPacket;
    
    pClientPacket = (clientPacketStructured_t*)MEM_BufferAlloc (sizeof(clientPacketHdr_t) + 
                                                                dataSize + 
                                                                sizeof(uint8_t));
    
    if(NULL == pClientPacket)
    {
        /* If the buffer can not be allocated try to send a FSCI error if the
         * BLE OTAP FSCI interface was initialized. */
        if (!FsciBleOtap_IsInterfaceValid (mFsciBleOtapInterfaceId))
        {
            FSCI_Error(gFsciOutOfMessages_c, mFsciBleOtapInterfaceId);
        }
        return NULL;
    }
    
    /* Fill in the FSCI packet header components */
    pClientPacket->header.opGroup   = gFsciBleOtapOpcodeGroup_c;
    pClientPacket->header.opCode    = opCode;
    pClientPacket->header.len       = dataSize;
    
    /* Return the allocated FSCI packet */
    return pClientPacket;
}
#endif /* gFsciBleOtapEnabled_d */

#if gFsciBleOtapEnabled_d
/*! *********************************************************************************
* \details  Allocates a FSCI BLE OTAP packet with the specified opcode, payload
*           and payload length and sends it over the FSCI interface.
*
********************************************************************************** */
void FsciBleOtap_SendPkt (opCode_t* pOpCode,
                          uint8_t*  pPayload,
                          uint16_t  payloadLen)
{
    clientPacketStructured_t*   pFsciOtapPkt;
    
    pFsciOtapPkt = FsciBleOtap_AllocatePacket (*pOpCode,
                                               payloadLen);
    
    if (NULL != pFsciOtapPkt)
    {
        /* If memory allocation for the packet was succesful then fill in the 
         * payload and try to send the packet. */
        FLib_MemCpy (pFsciOtapPkt->payload,
                     pPayload,
                     payloadLen);
        
        if (FsciBleOtap_IsInterfaceValid (mFsciBleOtapInterfaceId))
        {
            FSCI_transmitFormatedPacket (pFsciOtapPkt, mFsciBleOtapInterfaceId);
        }
    }
    else
    {
        /* The FsciBleOtap_AllocatePacket() function tries to send a FSCI Error
         * if the packet cannot be allocated so there is noting to do here
         * at this moment.*/
    }
}
#endif /* gFsciBleOtapEnabled_d */

/*! *********************************************************************************
* @}
********************************************************************************** */
