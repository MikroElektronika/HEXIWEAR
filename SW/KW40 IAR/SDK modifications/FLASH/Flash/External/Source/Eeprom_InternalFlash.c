/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file EEPROM_InternalFlash.c
* This is the Source file for the EEPROM emulated inside the MCU's FLASH
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

#include "Eeprom.h"

#if gEepromType_d == gEepromDevice_InternalFlash_c

#include "Flash_Adapter.h"
#include "FunctionLib.h"

/******************************************************************************
*******************************************************************************
* Private Macros
*******************************************************************************
******************************************************************************/

/******************************************************************************
*******************************************************************************
* Private Prototypes
*******************************************************************************
******************************************************************************/
static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr);

/******************************************************************************
*******************************************************************************
* Private type definitions
*******************************************************************************
******************************************************************************/

/******************************************************************************
*******************************************************************************
* Private Memory Declarations
*******************************************************************************
******************************************************************************/
static uint8_t mEepromEraseBitmap[32];
#if (gEepromParams_WriteAlignment_c > 1)
static uint8_t  mWriteBuff[gEepromParams_WriteAlignment_c];
static uint8_t  mWriteBuffLevel=0;
static uint32_t mWriteBuffAddr=0;
#endif

/******************************************************************************
*******************************************************************************
* Public Memory
*******************************************************************************
******************************************************************************/

/******************************************************************************
*******************************************************************************
* Public Functions
*******************************************************************************
******************************************************************************/

/*****************************************************************************
*  EEPROM_Init
*
*  Initializes the EEPROM peripheral
*
*****************************************************************************/
ee_err_t EEPROM_Init(void)
{
    FLib_MemSet (mEepromEraseBitmap, 0x00, 32);
    
    NV_Init();
    
    return ee_ok;
}

/*****************************************************************************
*  EEPROM_ChipErase
*
*  Erase all memory to 0xFF
*
*****************************************************************************/
ee_err_t EEPROM_ChipErase(void)
{
    uint32_t i, endAddr;
    
    endAddr = gEepromParams_StartOffset_c + gEepromParams_TotalSize_c;

    for( i=gEepromParams_StartOffset_c; i<endAddr; i+=gEepromParams_SectorSize_c )
    {
        if( ee_ok != EEPROM_EraseBlock(i, gEepromParams_SectorSize_c) )
            return ee_error;
    }

    return ee_ok;
}

/*****************************************************************************
*  EEPROM_EraseSector4K
*
*  Erase 4K of memory to 0xFF
*
*****************************************************************************/
ee_err_t EEPROM_EraseBlock(uint32_t Addr, uint32_t size)
{
  if( size != gEepromParams_SectorSize_c )
    return ee_error;

  if( NV_FlashEraseSector(&gFlashConfig, gEepromParams_StartOffset_c + Addr, size, gFlashLaunchCommand) )
    return ee_error;

  return ee_ok;
}

/*****************************************************************************
*  EEPROM_WriteData
*
*  Writes a data buffer into EEPROM, at a given address
*
*****************************************************************************/
ee_err_t EEPROM_WriteData(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
{
    if( ee_ok != EEPROM_PrepareForWrite(NoOfBytes, Addr) )
        return ee_error;

#if (gEepromParams_WriteAlignment_c > 1)
    if( mWriteBuffLevel )
    {
        if( Addr >= mWriteBuffAddr &&
            Addr <  mWriteBuffAddr + gEepromParams_WriteAlignment_c )
        {
            uint32_t offset = Addr - mWriteBuffAddr;
            uint32_t size = gEepromParams_WriteAlignment_c - offset;

            FLib_MemCpy(&mWriteBuff[offset], Outbuf, size);
            Addr += size;
            Outbuf += size;
            NoOfBytes -= size;
        }
        else
        {
            FLib_MemSet(&mWriteBuff[mWriteBuffLevel], 0xFF, gEepromParams_WriteAlignment_c - mWriteBuffLevel);
        }
        
        NV_FlashProgramUnaligned(&gFlashConfig, gEepromParams_StartOffset_c + mWriteBuffAddr, sizeof(mWriteBuff), mWriteBuff, gFlashLaunchCommand);
        mWriteBuffLevel = 0;
    }

    if( Addr & (gEepromParams_WriteAlignment_c-1) )
        return ee_not_aligned;

    /* Store unaligned bytes for later processing */
    mWriteBuffLevel = NoOfBytes % gEepromParams_WriteAlignment_c;
    NoOfBytes -= mWriteBuffLevel;
    mWriteBuffAddr = Addr + NoOfBytes;
    FLib_MemCpy(mWriteBuff, &Outbuf[NoOfBytes], mWriteBuffLevel);
#endif

    /* Write data to FLASH */
    if( NV_FlashProgramUnaligned(&gFlashConfig, gEepromParams_StartOffset_c + Addr, NoOfBytes, Outbuf, gFlashLaunchCommand) )
        return ee_error;
    
    return ee_ok;    
}

/*****************************************************************************
*  EEPROM_ReadData
*
*  Reads a data buffer from EEPROM, from a given address
*
*****************************************************************************/
ee_err_t EEPROM_ReadData(uint16_t NoOfBytes, uint32_t Addr, uint8_t *inbuf)
{
  FLib_MemCpy(inbuf, (void*)(gEepromParams_StartOffset_c + Addr), NoOfBytes);

#if (gEepromParams_WriteAlignment_c > 1)
  uint32_t i;

  /* Copy data from write buffer if needed */
  for( i=0; i<mWriteBuffLevel; i++ )
  {
      if( (mWriteBuffAddr + i) >= Addr &&
          (mWriteBuffAddr + i) <  (Addr + NoOfBytes) )
      {
          inbuf[mWriteBuffAddr - Addr + i] = mWriteBuff[i];
      }
  }
#endif
  
  return ee_ok;
}

/*****************************************************************************
*  EEPROM_ReadStatusReq
*
*
*****************************************************************************/
uint8_t EEPROM_isBusy(void)
{
  return FALSE;
}

/******************************************************************************
*******************************************************************************
* Private Functions
*******************************************************************************
******************************************************************************/


/*****************************************************************************
*  EEPROM_WriteData
*
*  Writes a data buffer into the External Memory, at a given address
*
*****************************************************************************/
static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr)
{
  uint32_t i;
  uint32_t startBlk, endBlk;

  /* Obtain the first and last block that need to be erased */
  startBlk = Addr / gEepromParams_SectorSize_c;
  endBlk   = (Addr + NoOfBytes) / gEepromParams_SectorSize_c;

  /* Check if the block was previousley erased */
  for(i = startBlk; i <= endBlk; i++)
    if ( (mEepromEraseBitmap[i/8] & (1 << (i%8) ) ) == 0)
    {
      if (EEPROM_EraseBlock(i * gEepromParams_SectorSize_c, gEepromParams_SectorSize_c) != ee_ok)
        return ee_error;
      mEepromEraseBitmap[i/8] |= 1 << (i%8);
    }

  return ee_ok;
}

#endif /* gEepromDevice_InternalFlash_c */