/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file OtapBootloader.c
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
#include "OtapBootloader.h"
#include "flash_boot_kinetis.h"
#include "Eeprom_Boot.h"
#include "UartBootloader.h"


/*! *********************************************************************************
*************************************************************************************
* Private Memory Declarations
*************************************************************************************
********************************************************************************** */
#if defined(__IAR_SYSTEMS_ICC__)
#pragma section = "IntVectTable"
#pragma location = "IntVectTable"
__root const vector_entry __vector_table[16] =
{
    (pointer*)__BOOT_STACK_ADDRESS,  /* Initial SP           */

#elif defined(__GNUC__)
const vector_entry __vector_table[16] __attribute__ ((section(".vectortable"))) =
{
    (pointer*)__SP_INIT,  /* Initial SP           */
#endif

    __thumb_startup, /* Initial PC           */
    defaultISR,      /* Non-maskable Interrupt (NMI) */
    defaultISR,      /* Hard Fault */
    defaultISR,      /* MemManage Fault */
    defaultISR,      /* Bus Fault */
    defaultISR,      /* Usage Fault */
    defaultISR,      /* Usage Fault */
    defaultISR,      /* Usage Fault */
    defaultISR,      /* Usage Fault */
    defaultISR,      /* Usage Fault */
    defaultISR,      /* Usage Fault */
    defaultISR,      /* Usage Fault */
    defaultISR,      /* Usage Fault */
    defaultISR,      /* Usage Fault */
    defaultISR       /* Usage Fault */
};

#if defined(__IAR_SYSTEMS_ICC__)
#pragma location = "FlashConfig"
__root const FlashConfig_t gFlashConfig @ "FlashConfig" =
#elif defined(__GNUC__)
const FlashConfig_t gFlashConfig __attribute__ ((section(".cfmconfig"))) =
#endif
{
    {0xFFFFFFFF, 0xFFFFFFFF, gFlashProtection_c, 0xFFFFFFFE}
};

/* Variables used by the Bootloader */
volatile bootInfo_t *gpBootInfo;
volatile uint32_t gBootStorageStartAddress;


/*! *********************************************************************************
*************************************************************************************
* Public Functions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
* \brief   This function determines the start address of the internal sorage.
*          If value is 0xFFFFFFFF then external storage should be used!
*
* \return the start address of the internal storage
*
********************************************************************************** */
uint32_t Boot_GetInternalStorageStartAddr(void)
{
    return *((uint32_t*)(gBootProductInfoAddress_c + gInternalStorageStartAddressOffset_c));
}


/*! *********************************************************************************
* \brief   The function resets the MCU
*
********************************************************************************** */
void Boot_ResetMCU(void)
{
    SCB_AIRCR = SCB_AIRCR_VECTKEY(0x5FA) | SCB_AIRCR_SYSRESETREQ_MASK;
    while(1);
}


/*! *********************************************************************************
* \brief   Start the user application
*
* \param[in] userStartup  Address of the application's interrupt vector
*
********************************************************************************** */
static void JumpToApplication(volatile uint32_t userStartup)
{
    /* Enable ALL interrupts */
    asm("     cpsie   i       ");

    /* set up stack pointer */
    asm("LDR      r1,  [r0]");
    asm("MSR      MSP, r1");

    /* jump to application reset vector */
    asm("ADDS     r0,r0,#0x04 ");
    asm("LDR      r0, [r0]");
    asm("BX       r0");
}


/*! *********************************************************************************
* \brief   Initialize the external storage
*
* \return status
*
********************************************************************************** */
uint8_t Boot_InitExternalStorage(void)
{
    if (gBootInvalidAddress_c == gBootStorageStartAddress)
        return EEPROM_Init();

    return 0;
}


/*! *********************************************************************************
* \brief   Read data from the external stoage
*
* \param[in]  NoOfBytes  number of byter to read
* \param[in]  Addr       read memory address
* \param[out] outbuf     location where read data is stored
*
* \return error code. 0 if success
*
********************************************************************************** */
uint8_t Boot_ReadExternalStorage(uint16_t NoOfBytes, uint32_t Addr, uint8_t *outbuf)
{
    if (gBootInvalidAddress_c == gBootStorageStartAddress)
    {
        return EEPROM_ReadData(NoOfBytes, Addr, outbuf);
    }
    else
    {
        Addr += gBootStorageStartAddress;
        while(NoOfBytes--)
        {
            *outbuf++ = *((uint8_t*)Addr++);
        }

        return 0;
    }
}


/*! *********************************************************************************
* \brief   This function will copy the User Application from the external memory
*          into the program Flash
*
********************************************************************************** */
void Boot_LoadImage (void)
{
    static uint8_t bitmapBuffer[gBootData_SectorsBitmap_Size_c];
    bootInfo_t flags;
    uint8_t  buffer[gFlashErasePage_c];
    uint32_t remaingImgSize, len;
    uint32_t flashAddr      = 0;
    uint8_t  bitMask        = gBitMaskInit_c;
    uint8_t *pBitmap        = bitmapBuffer;
#if defined(MCU_MK21DX256)
    vuint8_t* pFlexRamAddress;
    uint8_t  EEEDataSetSize;
    uint16_t size;
#endif

    /* Check if we have a valid internal storage start address. */
    gBootStorageStartAddress = Boot_GetInternalStorageStartAddr();

    /* Init the flash module */
    FlashInitialization();

    /* Init the external storage */
    Boot_InitExternalStorage();

    /* Read image size */
    if (Boot_ReadExternalStorage(gBootData_ImageLength_Size_c,gBootData_ImageLength_Offset_c, (uint8_t*)(&remaingImgSize)))
        gHandleBootError_d();

    /* Read sector bitmap */
    if (Boot_ReadExternalStorage(gBootData_SectorsBitmap_Size_c, gBootData_SectorsBitmap_Offset_c, bitmapBuffer))
        gHandleBootError_d();

    /* Start writing the image. Do not alter the last sector which contains HW specific data! */
    while (flashAddr < (gMcuFlashSize_c - gFlashErasePage_c))
    {
        if (remaingImgSize > gFlashErasePage_c)
            len = gFlashErasePage_c;
        else
            len = remaingImgSize;

        /* Check if bitmap indicates that this sector is write protected and shouldn't be updated */
        if ((*pBitmap & bitMask) && (flashAddr >= gUserFlashStart_d))
        {
            /* Erase Flash sector */
            if (FLASH_OK != FLASH_EraseSector(flashAddr))
                gHandleBootError_d();

            if (len)
            {
                /* Read a new image block */
                if (Boot_ReadExternalStorage(len, flashAddr + gBootData_Image_Offset_c, buffer))
                    gHandleBootError_d();


                if( (flashAddr <= gBootImageFlagsAddress_c) && (flashAddr + len > gBootImageFlagsAddress_c) )
                {
                    uint32_t i, offset = gBootImageFlagsAddress_c - flashAddr;
                    /* Program the Flash before boot flags */
                    if(FLASH_OK != FLASH_Program(flashAddr, (uint32_t)buffer, offset))
                        gHandleBootError_d();

                    /* Keep the boot flags set  until the all image is downloaded */
                    for( i=0; i<gEepromParams_WriteAlignment_c; i++ )
                    {
                        flags.newBootImageAvailable[i] = gBootValueForFALSE_c;
                        flags.bootProcessCompleted[i] = gBootValueForTRUE_c;
                    }
                    i = offset + 2 * gEepromParams_WriteAlignment_c;
                    flags.bootVersion[0] = buffer[i++];
                    flags.bootVersion[1] = buffer[i];
                    offset += gEepromAlignAddr_d(sizeof(bootInfo_t));

                    /* Program the Flash after the boot flags*/
                    if(FLASH_OK != FLASH_Program(flashAddr + offset, (uint32_t)(&buffer[offset]), len - offset))
                        gHandleBootError_d();
                }
                else
                {
                    /* Program the image block to Flash */
                    if(FLASH_OK != FLASH_Program(flashAddr, (uint32_t)buffer, len))
                        gHandleBootError_d();
                }
            }
        }

        /* Update Bitmask */
        bitMask <<= 1;
        if (bitMask == 0)
        {
            /* This was last bit in the current bitmap byte. Move to next bitmap byte */
            bitMask = gBitMaskInit_c;
            pBitmap++;
        }

        /* Update the current flash address */
        flashAddr += gFlashErasePage_c;

        /* Update the remaining bytes*/
        if (remaingImgSize)
            remaingImgSize -= len;
    } /* while */

#if defined(MCU_MK21DX256)

    while((FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK) != FTFL_FSTAT_CCIF_MASK)
    {
        /* wait till CCIF bit is set */
    }

    /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
    FTFL_FSTAT = (FTFL_FSTAT_RDCOLERR_MASK | FTFL_FSTAT_ACCERR_MASK |
                  FTFL_FSTAT_FPVIOL_MASK);

    /* Write Command Code to FCCOB0 */
    FTFL_FCCOB0 = FLASH_READ_RESOURCE;
    /* Write address to FCCOB1/2/3 */
    FTFL_FCCOB1 = ((uint8_t)(FLASH_DFLASH_IFR_READRESOURCE_ADDRESS >> 16));
    FTFL_FCCOB2 = ((uint8_t)((FLASH_DFLASH_IFR_READRESOURCE_ADDRESS >> 8) & 0xFF));
    FTFL_FCCOB3 = ((uint8_t)(FLASH_DFLASH_IFR_READRESOURCE_ADDRESS & 0xFF));

    /* Write Resource Select Code of 0 to FCCOB8 to select IFR. Without this, */
    /* an access error may occur if the register contains data from a previous command. */
    FTFL_FCCOB8 = 0;

    /* clear CCIF bit */
    FTFL_FSTAT |= FTFL_FSTAT_CCIF_MASK;

    /* check CCIF bit */
    while((FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK) != FTFL_FSTAT_CCIF_MASK)
    {
        /* wait till CCIF bit is set */
    }

    /* read the FlexRAM window size */
    EEEDataSetSize = FTFL_FCCOB6;
    EEEDataSetSize &= 0x0F;

    if((EEEDataSetSize == 2) || (EEEDataSetSize == 3)) /* FlexRAM size is 4KB or 2KB */
    {
        /* Enable EEE */
        FLASH_SetEEEEnable(FLASH_FLEXRAM_FNC_CTRL_CODE);

        pBitmap = &bitmapBuffer[0] + (uint32_t)((gMcuFlashSize_c/gFlashErasePage_c)/8);

        if(EEEDataSetSize == 2) /* 4KB */
        {
            if(*pBitmap & 0x01)
            {
                size = gBootFlexRam_4K_Size_c/2;
                pFlexRamAddress = (vuint8_t*)((uint32_t)gBootFlexRAMBaseAddress_c);
                while(size--)
                {
                    /* wait for EEPROM system to be ready */
                    while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
                    *pFlexRamAddress = 0xFF;
                    pFlexRamAddress ++;
                }
            }
            if(*pBitmap & 0x02)
            {
                size = gBootFlexRam_4K_Size_c/2;
                pFlexRamAddress = (vuint8_t*)((uint32_t)(gBootFlexRAMBaseAddress_c + size));
                while(size--)
                {
                    /* wait for EEPROM system to be ready */
                    while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
                    *pFlexRamAddress = 0xFF;
                    pFlexRamAddress ++;
                }
            }
        }
        else if (EEEDataSetSize == 3) /* 2K */
        {
            if(*pBitmap & 0x01)
            {
                size = gBootFlexRam_2K_Size_c/2;
                pFlexRamAddress = (vuint8_t*)((uint32_t)gBootFlexRAMBaseAddress_c);
                while(size--)
                {
                    /* wait for EEPROM system to be ready */
                    while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
                    *pFlexRamAddress = 0xFF;
                    pFlexRamAddress ++;
                }
            }
            if(*pBitmap & 0x02)
            {
                size = gBootFlexRam_2K_Size_c/2;
                pFlexRamAddress = (vuint8_t*)((uint32_t)(gBootFlexRAMBaseAddress_c + size));
                while(size--)
                {
                    /* wait for EEPROM system to be ready */
                    while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
                    *pFlexRamAddress = 0xFF;
                    pFlexRamAddress ++;
                }
            }
        }
    }
#endif


    /* Set the bBootProcessCompleted Flag */
    if( FLASH_OK != FLASH_Program((uint32_t)gBootImageFlagsAddress_c, (uint32_t)&flags, sizeof(flags)) )
        gHandleBootError_d();

    /* Reseting MCU */
    Boot_ResetMCU();
}

/*! *********************************************************************************
* \brief   This is the Bootloader's entry point
*
********************************************************************************** */
void __thumb_startup(void)
{
    (void)main(0, 0);
}

/*! *********************************************************************************
* \brief   This is the main Bootloader function.
*          It decides if it will load a new image or jump to the application
*
* \param[in] argc
* \param[in] argv
*
* \return int
*
********************************************************************************** */
int main(int argc, char **argv)
{
    /* Disable interrupt by default */
    asm("     CPSID   i       ");

    /* Set the start address of the interrupt vector*/
    SCB_VTOR = (uint32_t)__region_BOOT_ROM_start__;

    /* Disable watchdog */
#if defined(MCU_MK21DN512) || defined(MCU_MK21DX256) || defined(MCU_MK64FN1M)
    WDOG_UNLOCK = 0xC520;
    WDOG_UNLOCK = 0xD928;
    WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
#elif defined(MCU_MKL46Z256) || defined(MCU_MKW40Z160)
    SIM_COPC = SIM_COPC_COPT(0);
#endif
#if gSerialBootloaderEnable_c
    BOOT_PIN_ENABLE_SIM_SCG_REG |= BOOT_PIN_ENABLE_SIM_SCG_MASK;
    PORT_PCR_REG(BOOT_PIN_ENABLE_PORT_BASE,BOOT_PIN_ENABLE_NUM) = PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
    {
        vuint32_t delay;
        delay = 5;
        while(--delay);
    }
    if((GPIO_PDIR_REG(BOOT_PIN_ENABLE_GPIO_BASE) & (1 << BOOT_PIN_ENABLE_NUM)) == 0)
    {
        CheckForUartLoader();
    }
#endif
    /* Check if there is no boot image available in the external EEPROM and if eventually
    the booting of the previous one has been completed. If both conditions are met, start
    running the application in the internal Flash. Else, start the process of booting from
    external EEPROM */
    gpBootInfo = (bootInfo_t*)gBootImageFlagsAddress_c;
    /*
    if( (gpBootInfo->newBootImageAvailable == gBootValueForTRUE_c) &&
    (gpBootInfo->bootProcessCompleted ==  gBootValueForFALSE_c) )
    */
    if ((gpBootInfo->newBootImageAvailable[0] != gBootValueForTRUE_c) &&
        (gpBootInfo->bootProcessCompleted[0] ==  gBootValueForTRUE_c))
    {
        /* Set the start address of the interrupt vector*/
        SCB_VTOR = gUserFlashStart_d;
        JumpToApplication(gUserFlashStart_d);
    }
    else
    {
        /* Write the new image */
        Boot_LoadImage();
    }

    return 0;
}

/*! *********************************************************************************
* \brief   Default ISR handler
*
********************************************************************************** */
void defaultISR(void)
{
    /* ISR code */
    gHandleBootError_d();
}
//-----------------------------------------------------------------------------
