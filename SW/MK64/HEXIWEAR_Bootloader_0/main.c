/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
 * [Platform]      FRDM-K64F
 * [Project]       HEXIWEAR_Bootloader_0
 * [Version]       1.00
 * [Author]        marko.lainovic
 * [Date]          12/21/2015
 * [Language]      'C'
 * [History]       1.00 - Original Release
 *
 */

//-----------------------------------------------------------------------
// Standard C/C++ Includes
//-----------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "error.h"

//-----------------------------------------------------------------------
// KSDK Includes
//-----------------------------------------------------------------------
#include "main.h"
//-----------------------------------------------------------------------
// Application Includes
//-----------------------------------------------------------------------
#include "boot.h"
#include "SPI.h"

#include "flash_boot_kinetis.h"

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
volatile bootInfo_t*
  bootInfo;

const vector_entry __vector_table[16] __attribute__ ((section(".vectortable"))) =
{
    (vector_entry)0x20000000, /* Initial SP */
//    (pointer*)__SP_INIT, /* Initial SP */
    __thumb_startup,     /* Initial PC */
    defaultISR,          /* Non-maskable Interrupt (NMI) */
    defaultISR,          /* Hard Fault */
    defaultISR,          /* MemManage Fault */
    defaultISR,          /* Bus Fault */
    defaultISR,          /* Usage Fault */
    defaultISR,          /* Usage Fault */
    defaultISR,          /* Usage Fault */
    defaultISR,          /* Usage Fault */
    defaultISR,          /* Usage Fault */
    defaultISR,          /* Usage Fault */
    defaultISR,          /* Usage Fault */
    defaultISR,          /* Usage Fault */
    defaultISR,          /* Usage Fault */
    defaultISR           /* Usage Fault */
};

const flash_config_t gFlashConfig __attribute__ ( ( section(".cfmconfig") ) ) =
{
  { 0x0FFFFFFF, 0xFFFFFFFF, FLASH_PROTECTION, 0xFFFFFFFE }
};

uint32_t* const
  firstTimeBoot = (uint32_t*)BOOT_FIRST_TIME_IMAGE_FLAGS_ADDRESS;

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------

/**
 * bootloader's entry point
 */
void __thumb_startup(void)
{
  main();
}

/**
 * HEXIWEAR_Bootloader
 */
void main()
{
  // Disable interrupt by default
  __asm("     CPSID   i       ");

  /**
  * disable write buffering end enable exceptions,
  * for debugging purposes
  */
  SCB->SHCSR |= 0x00070000;
  SCnSCB->ACTLR |= SCnSCB_ACTLR_DISDEFWBUF_Msk;

  // set the start address of the interrupt vector
  SCB_VTOR = (uint32_t)( __region_BOOT_ROM_start__ );

  WDOG_UNLOCK = 0xC520;
  WDOG_UNLOCK = 0xD928;
  WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;

  /**
   * Check if there is no boot image available in the external EEPROM and if eventually
   * the booting of the previous one has been completed. If both conditions are met, start
   * external EEPROM
  */

  bootInfo = (bootInfo_t*)BOOT_IMAGE_FLAGS_ADDRESS;

  if  (
            ( BOOT_NEW_IMAGE_FLAG == bootInfo->newBootImageAvailable[0] )
//        ||  ( BOOT_FIRST_TIME_IMAGE_FLAG == *firstTimeBoot )
      )
  {
    /* Write the new image */
    Boot_LoadImage();
  }

  else
  {
    /* Set the start address of the interrupt vector*/
    SCB_VTOR = FLASH_APP_START_ADDRESS;
    Boot_JumpToApplication( FLASH_APP_START_ADDRESS );
  }
}
