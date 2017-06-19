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


/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "flash_boot_kinetis.h"
#include "MK64F12.h"
#include "MK64F12_cfg.h"

/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */

#if (gEepromParams_WriteAlignment_c > 4) 
    #define FLASH_PGM_SIZE (gEepromParams_WriteAlignment_c)
#else
    #define FLASH_PGM_SIZE (8)
#endif

#define NoOfElements(x) (sizeof(x)/sizeof(x[0]))


/*! *********************************************************************************
*************************************************************************************
* Private Memory Declarations
*************************************************************************************
********************************************************************************** */
uint8_t pCommandArray[FCCOB_REGS];
static FCC0B_STR CommandObj;
void (*ExecuteOnStack)(void) = NULL;
uint8_t buffer[128];
//uint8_t buffer[129];

#if defined(__IAR_SYSTEMS_ICC__)
__no_init uint32_t programbuffer[512] @0x14000000;
#elif defined(__GNUC__)
uint32_t programbuffer[512] __attribute__ ((section(".progBuffer")));
#endif

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */
//  internal driver function
static uint8_t FLASH_FlashCommandSequence(uint8_t index);
static void ExecuteOnStackStart();


/*! *********************************************************************************
*************************************************************************************
* Public Functions
*************************************************************************************
********************************************************************************** */

volatile uint32_t
  foo,
  bar;

/********************************************************
* Init Function
*
********************************************************/
void FlashInitialization(void)
{
  uint16_t
    i,
    size;

  foo = (uint32_t)ExecuteOnStackStart;

  //  RAM function should have the same alignment as one from ROM
  if ( 0 != ( ( (uint32_t)ExecuteOnStackStart- 1 ) & 0x03 ) )
  {
    i = 2;
  }

  else
  {
    i = 0;
  }

  size = sizeof(buffer) - i;

  //  initialize pointer to ram function
  ExecuteOnStack = ( void(*)(void) ) &( buffer[i+1] );
//  ExecuteOnStack = ( void(*)(void) ) &( buffer[0] );

  //  copy function from ROM to RAM
  for( ; i < size; i++ )
  {
    buffer[i] = ( (uint8_t*)ExecuteOnStackStart )[i-1];
  }

  //  initialize the flash clock module
  FLASH_INIT_FLASH_CLOCK;
}

//void FlashInitialization()
//{
////    uint16_t i, size;
//
////    size = sizeof(buffer) - i;
//
//    //  initialize pointer to ram function
//    ExecuteOnStack = (void(*)(void))&buffer[1];
//
//    //  copy function from ROM to RAM
//    for( uint16_t i = 0 ; i < 128; i++ )
//    {
//      buffer[i] = ( (uint8_t*)ExecuteOnStackStart )[i-1];
//    }
//
//    //  initialize the flash clock module
//    FLASH_INIT_FLASH_CLOCK;
//}

/********************************************************
* Generic FLASH programing function
*
********************************************************/
uint8_t FLASH_Program(uint32_t dest, uint32_t source, uint32_t size)
{
    uint32_t i;
    uint8_t* pSource = (uint8_t*)source;
    uint8_t temp[ FLASH_PGM_SIZE ];

    /* Check for unaligned destination address */
    if (dest & (FLASH_PGM_SIZE - 0x01U))
    {
       return FLASH_FAIL;
    }
    
    while( size )
    {
        /* data must be multiple of FLASH_PGM_SIZE */
        if( size > 0 && size < FLASH_PGM_SIZE  )
        {
            for( i=0; i<size; i++ )
            {
                temp[i] = *pSource++;
            }
                
            for( i=size; i<FLASH_PGM_SIZE; i++ )
            {
                temp[i] = 0xFF;
            }
                
            pSource = temp;
            size = FLASH_PGM_SIZE;
        }

        /* preparing passing parameter to program the flash block */
        CommandObj.regsLong.fccob3210 = dest;
#if (FLASH_PGM_SIZE==8)
        CommandObj.regs.fccob0 = FLASH_PROGRAM_PHRASE;
        
#else
        CommandObj.regs.fccob0 = FLASH_PROGRAM_LONGWORD;
#endif
        for( i=4; i<FLASH_PGM_SIZE+4; i++ )
        {
            CommandObj.all[i] = *pSource++;
        }

        /* calling flash command sequence function to execute the command */
        if( FLASH_OK != FLASH_FlashCommandSequence(i) )
            return FLASH_FAIL;
    
        /* update destination address for next iteration */
        dest += FLASH_PGM_SIZE;
        /* update size for next iteration */
        size -= FLASH_PGM_SIZE;
    }

    return FLASH_OK;
}

/********************************************************
* Function for Programming multiple Long Word
*
********************************************************/
uint8_t FLASH_ProgramLongWords(uint32_t destination, uint32_t source, uint32_t size)
{
    uint8_t ret = FLASH_OK;
    uint8_t bytes;
    uint32_t alignedWord;
    uint8_t* pbSource = (uint8_t*)source;
    
    bytes = destination & 0x03;
    destination &= ~((uint32_t)0x03);
    if( bytes )
    {
        /* Go to previous aligned address */
        alignedWord = *((uint32_t*)destination);
        
    }
    while(size)
    {
        ((uint8_t*)&alignedWord)[bytes] = *pbSource++;
        size--;
        if((bytes == 3)||(size == 0))
        {
            ret = FLASH_ProgramLongWord(destination, alignedWord);
            if(FLASH_OK != ret )
            {
                return ret;
            }
            if(size)
            {
                destination += 4;
                if(size < 4)
                {
                    alignedWord = *((uint32_t*)destination);
                }
            }
        }  
        bytes = (bytes+1) & 0x3;
    }
    
    
    return FLASH_OK;
}
/********************************************************
* Function for Programming of one Long Word
*
********************************************************/
uint8_t FLASH_ProgramLongWord(uint32_t destination, uint32_t data32b)
{
    /* preparing passing parameter to program the flash block */
    
    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_PROGRAM_LONGWORD;
    CommandObj.regsLong.fccob7654 = data32b;
    
    return FLASH_FlashCommandSequence(PROGRAM_LONGWORD_INDEX);
}

/********************************************************
* Function for Programming of one section (maximum is 2048 Bytes)
*
********************************************************/
uint8_t FLASH_ProgramSection(uint32_t destination, uint32_t* pSource, uint32_t size)
{
    uint8_t* pProgBuff = (uint8_t*)&programbuffer[0];
    uint8_t* pSrc = (uint8_t*)pSource;
    uint32_t phases = size / FLASH_PHASE_SEZE;
    uint8_t  r = size % FLASH_PHASE_SEZE;
    
    // check the size of memory
    if((size > sizeof(programbuffer)) || (size == 0))
        return FLASH_FAIL;
    
    if(destination & 0x00000003)
        return FLASH_FAIL;
    
    if (r > 0)
    {
        phases++;
        r = FLASH_PHASE_SEZE - r;
    }
    
    /* preparing passing parameter to program the flash block */
    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_PROGRAM_SECTION;
    CommandObj.regs.fccob4 = (uint8_t)(phases >> 8);
    CommandObj.regs.fccob5 = (uint8_t)(phases & 0xff);
    
    //  copy source data to program buffer
    while(size--)
        *pProgBuff++ = *pSrc++;
    
    while(r--)
        *pProgBuff++ = 0xFF;
    
    //  call flash sequence
    return FLASH_FlashCommandSequence(PROGRAM_SECTION_INDEX);
}


/********************************************************
* Function for Programming of one section (maximum is 2048 Bytes)
*
********************************************************/
uint8_t FLASH_ProgramSectionPhrases(uint32_t destination, uint32_t* pSource, uint32_t size)
{
    uint8_t* pProgBuff = (uint8_t*)&programbuffer[0];
    uint8_t* pSrc = (uint8_t*)pSource;
    uint32_t phases = size / FLASH_PHASE_SEZE;
    uint8_t r = size % FLASH_PHASE_SEZE;
    
    // check the size of memory
    if(size >= sizeof(programbuffer) || (size == 0))
        return FLASH_FAIL;
    
    if(destination & 0x00000003)
    {
        if(size & 0x00000001)
            if(!FLASH_ProgramLongWord(destination, *pSource))
                return FLASH_FAIL;
    }
    
    if(destination & 0x00000004)
    {
        if(!FLASH_ProgramLongWord(destination, *pSource++))
            return FLASH_FAIL;
        size-=4;
        destination += 4;
    }
    
    if (r)
    {
        phases++;
        r = FLASH_PHASE_SEZE - r;
    }
    
    /* preparing passing parameter to program the flash block */
    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_PROGRAM_SECTION;
    CommandObj.regs.fccob4 = (uint8_t)(phases >> 8);
    CommandObj.regs.fccob5 = (uint8_t)(phases & 0xff);
    
    //  copy source data to program buffer
    while(size--)
        *pProgBuff++ = *pSrc++;
    
    while(r--)
        *pProgBuff++ = 0xFF;
    
    //  call flash sequence
    return FLASH_FlashCommandSequence(PROGRAM_SECTION_INDEX);
}

/********************************************************
*
*
********************************************************/
uint8_t FLASH_ProgramByte(uint32_t destination, uint8_t data8b)
{
    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_PROGRAM_BYTE;
    CommandObj.regs.fccob4 = data8b;
    
    return FLASH_FlashCommandSequence(PROGRAM_BYTE_INDEX);
}

/********************************************************
* Function for erasing of flash memory sector (0x800)
*
********************************************************/
uint8_t FLASH_EraseSector(uint32_t destination)
{
    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_ERASE_SECTOR;
    
    return FLASH_FlashCommandSequence(ERASE_BLOCK_INDEX);
}


/********************************************************
* Function for erasing of all block of memory
*
********************************************************/
uint8_t FLASH_MassErase(void)
{
    CommandObj.regs.fccob0 = FLASH_ERASE_ALL_BLOCK;
    return FLASH_FlashCommandSequence(ERASE_MASS_INDEX);
}

/********************************************************
* Function for enabling the EERAM
*
********************************************************/
uint8_t FLASH_SetEEEEnable(uint8_t ctrl_code)
{
    CommandObj.regs.fccob0 = FLASH_SET_EERAM;
    CommandObj.regs.fccob1 = ctrl_code;
    return FLASH_FlashCommandSequence(SET_EERAM_INDEX);
}


/*! *********************************************************************************
*************************************************************************************
* Private Functions
*************************************************************************************
********************************************************************************** */

/********************************************************
* Function for executing of the flash command
*
********************************************************/
static uint8_t FLASH_FlashCommandSequence(uint8_t index)
{
    uint8_t* ptrFccobReg = (uint8_t*)&FLASH_BASE_PTR->FCCOB3;
    uint8_t* ptrCommandObj = (uint8_t*)&CommandObj;
    
    
    /* wait till CCIF bit is set */
    while((FLASH_FSTAT&FLASH_FSTAT_CCIF_MASK) != FLASH_FSTAT_CCIF_MASK){};
    
    /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
    FLASH_FSTAT = FLASH_FSTAT_ACCERR_MASK|FLASH_FSTAT_FPVIOL_MASK|FLASH_FSTAT_RDCOLERR_MASK;
    
    /* load FCCOB registers */
    while(index--)
        *ptrFccobReg++ = *ptrCommandObj++;
    
    //  jump to RAM function
    ExecuteOnStack();
    
    /* Check error bits */
    /* Get flash status register value */
    if ( 0 != ( FLASH_FSTAT & (FLASH_FSTAT_ACCERR_MASK|FLASH_FSTAT_FPVIOL_MASK|FLASH_FSTAT_MGSTAT0_MASK) ) )
    {
      return FLASH_FAIL;
    }

    else
    {
      return FLASH_OK;
    }
}

/********************************************************
* Function for launching a FLASH command: will run from RAM
*
********************************************************/
static void ExecuteOnStackStart(void)
{
    //  launch a command
    FLASH_FSTAT |= FLASH_FSTAT_CCIF_MASK;
    
    //  waiting for the finishing of the command
    while( FLASH_FSTAT_CCIF_MASK != ( FLASH_FSTAT & FLASH_FSTAT_CCIF_MASK ) ) {}
}
