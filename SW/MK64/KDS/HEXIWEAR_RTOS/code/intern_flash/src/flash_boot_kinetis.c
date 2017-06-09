/*!
* Copyright (c) 2015, NXP Semiconductor, Inc.
* All rights reserved.
*
* \file flash_boot_kinetis.c
* \version 1.00
* \brief This file this file contains internal FLASH functionality
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
* o Neither the name of NXP Semiconductor, Inc. nor the names of its
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


/** include */
#include "FLASH_boot_kinetis.h"
#include "MK64F12.h"
#include "MK64F12_cfg.h"
#include "fsl_os_abstraction.h"

/** private macros */
#if (gEepromParams_WriteAlignment_c > 4)
    #define FLASH_PGM_SIZE (gEepromParams_WriteAlignment_c)
#else
    #define FLASH_PGM_SIZE (8)
#endif

#define NoOfElements(x) (sizeof(x)/sizeof(x[0]))


/** private memory declarations */
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

/** private prototypes */

//  internal driver function
static uint8_t INTFLASH_FLASHCommandSequence(uint8_t index);
static void ExecuteOnStackStart();

/** dummy variables */
volatile uint32_t
  foo,
  bar;

/** public API */

/**
 * initialize the FLASH module
 */
void INTFLASH_Init()
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

  //  initialize the FLASH clock module
  FLASH_INIT_FLASH_CLOCK;
}

/**
 * generically program FLASH
 * @param  dest   FLASH address
 * @param  source data address
 * @param  size   data size to program
 * @return        status flag
 */
uint8_t INTFLASH_Program(uint32_t dest, uint32_t source, uint32_t size)
{
    uint32_t i;
    uint8_t* pSource = (uint8_t*)source;
    uint8_t temp[ FLASH_PGM_SIZE ];

     /** Check for unaligned destination address */
    if (dest & (FLASH_PGM_SIZE - 0x01U))
    {
       return INTFLASH_FAIL;
    }

    while( size )
    {
         /** data must be multiple of FLASH_PGM_SIZE */
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

         /** preparing passing parameter to program the FLASH block */
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

         /** calling FLASH command sequence function to execute the command */
        if( INTFLASH_OK != INTFLASH_FLASHCommandSequence(i) )
            return INTFLASH_FAIL;

         /** update destination address for next iteration */
        dest += FLASH_PGM_SIZE;
         /** update size for next iteration */
        size -= FLASH_PGM_SIZE;
    }

    return INTFLASH_OK;
}

/**
 * program multiple long words
 * @param  dest   FLASH address
 * @param  source data address
 * @param  size   data size to program
 * @return        status flag
 */
uint8_t INTFLASH_ProgramLongWords(uint32_t destination, uint32_t source, uint32_t size)
{
    uint8_t ret = INTFLASH_OK;
    uint8_t bytes;
    uint32_t alignedWord;
    uint8_t* pbSource = (uint8_t*)source;

    bytes = destination & 0x03;
    destination &= ~((uint32_t)0x03);
    if( bytes )
    {
         /** Go to previous aligned address */
        alignedWord = *((uint32_t*)destination);

    }
    while(size)
    {
        ((uint8_t*)&alignedWord)[bytes] = *pbSource++;
        size--;
        if((bytes == 3)||(size == 0))
        {
            ret = INTFLASH_ProgramLongWord(destination, alignedWord);
            if(INTFLASH_OK != ret )
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


    return INTFLASH_OK;
}
/**
 * program one long word
 * @param  dest   FLASH address
 * @param  source data address
 * @param  size   data size to program
 * @return        status flag
 */
uint8_t INTFLASH_ProgramLongWord(uint32_t destination, uint32_t data32b)
{
     /** preparing passing parameter to program the FLASH block */

    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_PROGRAM_LONGWORD;
    CommandObj.regsLong.fccob7654 = data32b;

    return INTFLASH_FLASHCommandSequence(PROGRAM_LONGWORD_INDEX);
}

/**
 * program one section (maximum is 2048 Bytes)
 * @param  destination FLASH address
 * @param  pSource     data address
 * @param  size        data size to program
 * @return             status flag
 */
uint8_t INTFLASH_ProgramSection(uint32_t destination, uint32_t* pSource, uint32_t size)
{
    uint8_t* pProgBuff = (uint8_t*)&programbuffer[0];
    uint8_t* pSrc = (uint8_t*)pSource;
    uint32_t phases = size / FLASH_PHASE_SEZE;
    uint8_t  r = size % FLASH_PHASE_SEZE;

    // check the size of memory
    if((size > sizeof(programbuffer)) || (size == 0))
        return INTFLASH_FAIL;

    if(destination & 0x00000003)
        return INTFLASH_FAIL;

    if (r > 0)
    {
        phases++;
        r = FLASH_PHASE_SEZE - r;
    }

     /** preparing passing parameter to program the FLASH block */
    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_PROGRAM_SECTION;
    CommandObj.regs.fccob4 = (uint8_t)(phases >> 8);
    CommandObj.regs.fccob5 = (uint8_t)(phases & 0xff);

    //  copy source data to program buffer
    while(size--)
        *pProgBuff++ = *pSrc++;

    while(r--)
        *pProgBuff++ = 0xFF;

    //  call FLASH sequence
    return INTFLASH_FLASHCommandSequence(PROGRAM_SECTION_INDEX);
}


/**
 * program section phrases
 * @param  destination FLASH address
 * @param  pSource     data address
 * @param  size        data size to program
 * @return             status flag
 */
uint8_t INTFLASH_ProgramSectionPhrases(uint32_t destination, uint32_t* pSource, uint32_t size)
{
    uint8_t* pProgBuff = (uint8_t*)&programbuffer[0];
    uint8_t* pSrc = (uint8_t*)pSource;
    uint32_t phases = size / FLASH_PHASE_SEZE;
    uint8_t r = size % FLASH_PHASE_SEZE;

    // check the size of memory
    if(size >= sizeof(programbuffer) || (size == 0))
        return INTFLASH_FAIL;

    if(destination & 0x00000003)
    {
        if(size & 0x00000001)
            if(! INTFLASH_ProgramLongWord(destination, *pSource) )
                return INTFLASH_FAIL;
    }

    if(destination & 0x00000004)
    {
        if(! INTFLASH_ProgramLongWord(destination, *pSource++) )
            return INTFLASH_FAIL;
        size-=4;
        destination += 4;
    }

    if (r)
    {
        phases++;
        r = FLASH_PHASE_SEZE - r;
    }

     /** preparing passing parameter to program the FLASH block */
    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_PROGRAM_SECTION;
    CommandObj.regs.fccob4 = (uint8_t)(phases >> 8);
    CommandObj.regs.fccob5 = (uint8_t)(phases & 0xff);

    //  copy source data to program buffer
    while(size--)
        *pProgBuff++ = *pSrc++;

    while(r--)
        *pProgBuff++ = 0xFF;

    //  call FLASH sequence
    return INTFLASH_FLASHCommandSequence(PROGRAM_SECTION_INDEX);
}

/**
 * program one byte
 * @param  destination FLASH address
 * @param  data8b      byte to program
 * @return             status flag
 */
uint8_t INTFLASH_ProgramByte(uint32_t destination, uint8_t data8b)
{
    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_PROGRAM_BYTE;
    CommandObj.regs.fccob4 = data8b;

    return INTFLASH_FLASHCommandSequence(PROGRAM_BYTE_INDEX);
}

/**
 * program HW revision structure
 * @param  source HW revision structure's address
 * @return        status flag
 */
uint8_t INTFLASH_ProgramHwRev( hexiwear_hw_rev_t* source )
{
	 /** preparing passing parameter to program the FLASH block */
	CommandObj.regs.fccob0 = FLASH_PROGRAM_ONCE;
	CommandObj.regs.fccob1 = FLASH_HW_VER_RECORD;

	CommandObj.regs.fccob4 = source->hexiwear_major_ver;
	CommandObj.regs.fccob5 = source->hexiwear_minor_ver;
	CommandObj.regs.fccob6 = source->hexiwear_patch_ver;
	CommandObj.regs.fccob7 = source->hexiwear_build_ver;

	CommandObj.regs.fccob8 = source->pcb_main_ver;
	CommandObj.regs.fccob9 = source->pcb_hr_ver;
	CommandObj.regs.fccobA = source->pcb_cs_ver;
	CommandObj.regs.fccobB = source->padding;

	 /** calling FLASH command sequence function to execute the command */
	if( INTFLASH_OK != INTFLASH_FLASHCommandSequence( FCCOB_REGS ) )
	{
		return INTFLASH_FAIL;
	}

    return INTFLASH_OK;
}

/**
 * read HW revision
 * @param  dst HW revision structure to populate with info
 * @return     status flag
 */
uint8_t INTFLASH_ReadHwRev( hexiwear_hw_rev_t* dst )
{
	uint8_t
		i = 0;

	uint8_t*
		foo = (uint8_t*)dst;

	 /** preparing passing parameter to program the FLASH block */
	CommandObj.regs.fccob0 = FLASH_READ_ONCE;
	CommandObj.regs.fccob1 = FLASH_HW_VER_RECORD;

	 /** calling FLASH command sequence function to execute the command */
	if( INTFLASH_OK != INTFLASH_FLASHCommandSequence( 4 ) )
	{
		return INTFLASH_FAIL;
	}
	else
	{
		dst->hexiwear_major_ver = FLASH_BASE_PTR->FCCOB4;
		dst->hexiwear_minor_ver = FLASH_BASE_PTR->FCCOB5;
		dst->hexiwear_patch_ver = FLASH_BASE_PTR->FCCOB6;
		dst->hexiwear_build_ver = FLASH_BASE_PTR->FCCOB7;

		dst->pcb_main_ver       = FLASH_BASE_PTR->FCCOB8;
		dst->pcb_hr_ver         = FLASH_BASE_PTR->FCCOB9;
		dst->pcb_cs_ver         = FLASH_BASE_PTR->FCCOBA;
		dst->padding            = FLASH_BASE_PTR->FCCOBB;

		return INTFLASH_OK;
	}

}


/**
 * erase FLASH memory sector (0x800)
 * @param  destination FLASH address
 * @return             status flag
 */
uint8_t INTFLASH_EraseSector(uint32_t destination)
{
    CommandObj.regsLong.fccob3210 = destination;
    CommandObj.regs.fccob0 = FLASH_ERASE_SECTOR;

    return INTFLASH_FLASHCommandSequence(ERASE_BLOCK_INDEX);
}


/**
 * erase of all block of memory
 */
uint8_t INTFLASH_MassErase(void)
{
    CommandObj.regs.fccob0 = FLASH_ERASE_ALL_BLOCK;
    return INTFLASH_FLASHCommandSequence(ERASE_MASS_INDEX);
}

/**
 * enable the EERAM
 */
uint8_t INTFLASH_SetEEEEnable(uint8_t ctrl_code)
{
    CommandObj.regs.fccob0 = FLASH_SET_EERAM;
    CommandObj.regs.fccob1 = ctrl_code;
    return INTFLASH_FLASHCommandSequence(SET_EERAM_INDEX);
}


/** private functions */

/**
 * execute the FLASH command
 * @param  index register index
 * @return       status flag
 */
static uint8_t INTFLASH_FLASHCommandSequence(uint8_t index)
{
    uint8_t* ptrFccobReg = (uint8_t*)&FLASH_BASE_PTR->FCCOB3;
    uint8_t* ptrCommandObj = (uint8_t*)&CommandObj;


     /** wait till CCIF bit is set */
    while((FLASH_FSTAT&FLASH_FSTAT_CCIF_MASK) != FLASH_FSTAT_CCIF_MASK){};

     /** clear RDCOLERR & ACCERR & FPVIOL flag in FLASH status register */
    FLASH_FSTAT = FLASH_FSTAT_ACCERR_MASK|FLASH_FSTAT_FPVIOL_MASK|FLASH_FSTAT_RDCOLERR_MASK;

     /** load FCCOB registers */
    while(index--)
        *ptrFccobReg++ = *ptrCommandObj++;

    //  jump to RAM function

    OSA_EnterCritical( kCriticalDisableInt );
    ExecuteOnStack();
    OSA_ExitCritical( kCriticalDisableInt );

     /** Check error bits */
     /** Get FLASH status register value */
    if ( 0 != ( FLASH_FSTAT & (FLASH_FSTAT_ACCERR_MASK|FLASH_FSTAT_FPVIOL_MASK|FLASH_FSTAT_MGSTAT0_MASK) ) )
    {
      return INTFLASH_FAIL;
    }

    else
    {
      return INTFLASH_OK;
    }
}

/**
 * launch a FLASH command
 */
static void ExecuteOnStackStart(void)
{
    //  launch a command
    FLASH_FSTAT |= FLASH_FSTAT_CCIF_MASK;

    //  waiting for the finishing of the command
    while( FLASH_FSTAT_CCIF_MASK != ( FLASH_FSTAT & FLASH_FSTAT_CCIF_MASK ) ) {}
}
