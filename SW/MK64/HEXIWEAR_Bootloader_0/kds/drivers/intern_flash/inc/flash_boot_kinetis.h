/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file filename.h
* This file brief description
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

#ifndef _FLASH_KINETIS_H
#define _FLASH_KINETIS_H


/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "EmbeddedTypes.h"

#ifdef __cplusplus
    extern "C" {
#endif

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
//  Flash hardware algorithm operation commands
#define FLASH_PROGRAM_BYTE        0x04
#define FLASH_PROGRAM_WORD        0x05
#define FLASH_PROGRAM_LONGWORD    0x06
#define FLASH_PROGRAM_PHRASE      0x07
#define FLASH_ERASE_BLOCK         0x08
#define FLASH_ERASE_SECTOR        0x09
#define FLASH_PROGRAM_SECTION     0x0B
#define FLASH_ERASE_ALL_BLOCK     0x44
#define FLASH_SET_EERAM           0x81
#define FLASH_READ_RESOURCE       0x03

#define FLASH_LONG_WORD_SEZE     4
#define FLASH_PHASE_SEZE         8
#define FLASH_DOUBLE_PHASE_SEZE 16

#define FCCOB_REGS  12
#define FLASH_OK     0
#define FLASH_FAIL   1

#define FLASH_DFLASH_IFR_READRESOURCE_ADDRESS   0x8000FC
        
#define ERASE_MASS_INDEX       4
#define ERASE_BLOCK_INDEX      4
#define PROGRAM_BYTE_INDEX     5
#define PROGRAM_SECTION_INDEX  7
#define PROGRAM_LONGWORD_INDEX 8
#define SET_EERAM_INDEX        4

#define FLASH_FLEXRAM_FNC_CTRL_CODE    0x00


/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
//  FCOOB register structure
typedef union
{
  uint8_t all[FCCOB_REGS];
  struct
  {
    uint8_t fccob3;
    uint8_t fccob2;
    uint8_t fccob1;
    uint8_t fccob0;
    uint8_t fccob7;
    uint8_t fccob6;
    uint8_t fccob5;
    uint8_t fccob4;
    uint8_t fccobB;
    uint8_t fccobA;
    uint8_t fccob9;
    uint8_t fccob8;
  }regs;

  struct
  {
    uint32_t fccob3210;
    uint32_t fccob7654;
    uint32_t fccobBA98;
  }regsLong;
}FCC0B_STR;


/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */

//  API FUNCTION FOR KINETIS FLASH DRIVER
void FlashInitialization(void);
uint8_t FLASH_EraseSector(uint32_t destination);
uint8_t FLASH_Program(uint32_t dest, uint32_t source, uint32_t size);
uint8_t FLASH_ProgramLongWords(uint32_t destination, uint32_t source, uint32_t size);
uint8_t FLASH_ProgramLongWord(uint32_t destination, uint32_t data);
uint8_t FLASH_ProgramSection(uint32_t destination, uint32_t* pSource, uint32_t size);
uint8_t FLASH_ProgramSectionPhrases(uint32_t destination, uint32_t* pSource, uint32_t size);
uint8_t FLASH_ProgramSectionDoublePhrases(uint32_t destination, uint32_t* pSource, uint32_t size);
uint8_t FLASH_MassErase(void);
uint8_t FLASH_SetEEEEnable(uint8_t ctrl_code);

#ifdef __cplusplus
}
#endif

#endif
