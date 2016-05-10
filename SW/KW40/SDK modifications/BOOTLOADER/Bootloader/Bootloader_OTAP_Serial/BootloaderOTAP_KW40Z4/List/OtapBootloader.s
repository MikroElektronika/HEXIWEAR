///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       12/Jan/2016  08:59:56
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\OtapSerialBootloader\OtapBootloader.c
//    Command line =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\OtapSerialBootloader\OtapBootloader.c
//        -D MCU_MKW40Z160 -D gEepromType_d=gEepromDevice_M25P80_c
//        --preprocess=cl
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\
//        -lC
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\
//        -lA
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\
//        --diag_suppress Pa039 -o
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\Obj\
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M0+ -e --fpu=None -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\OtapSerialBootloader\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\spi\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\flash\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\include\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\
//        -I
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\include\cfg\
//        -On --c89
//    List file    =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\OtapBootloader.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__SystemLibrary", "DLib"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        EXTERN EEPROM_Init
        EXTERN EEPROM_ReadData
        EXTERN FLASH_EraseSector
        EXTERN FLASH_Program
        EXTERN FlashInitialization
        EXTERN __BOOT_STACK_ADDRESS
        EXTERN __region_BOOT_ROM_end__
        EXTERN __region_BOOT_ROM_start__

        PUBLIC Boot_GetInternalStorageStartAddr
        PUBLIC Boot_InitExternalStorage
        PUBLIC Boot_LoadImage
        PUBLIC Boot_ReadExternalStorage
        PUBLIC Boot_ResetMCU
        PUBLIC __thumb_startup
        PUBLIC __vector_table
        PUBLIC defaultISR
        PUBLIC gBootStorageStartAddress
        PUBLIC gFlashConfig
        PUBLIC gpBootInfo
        PUBLIC main
        
          CFI Names cfiNames0
          CFI StackFrame CFA R13 DATA
          CFI Resource R0:32, R1:32, R2:32, R3:32, R4:32, R5:32, R6:32, R7:32
          CFI Resource R8:32, R9:32, R10:32, R11:32, R12:32, R13:32, R14:32
          CFI EndNames cfiNames0
        
          CFI Common cfiCommon0 Using cfiNames0
          CFI CodeAlign 2
          CFI DataAlign 4
          CFI ReturnAddress R14 CODE
          CFI CFA R13+0
          CFI R0 Undefined
          CFI R1 Undefined
          CFI R2 Undefined
          CFI R3 Undefined
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI R8 SameValue
          CFI R9 SameValue
          CFI R10 SameValue
          CFI R11 SameValue
          CFI R12 Undefined
          CFI R14 SameValue
          CFI EndCommon cfiCommon0
        
// C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\OtapSerialBootloader\OtapBootloader.c
//    1 /*!
//    2 * Copyright (c) 2015, Freescale Semiconductor, Inc.
//    3 * All rights reserved.
//    4 *
//    5 * \file OtapBootloader.c
//    6 *
//    7 * Redistribution and use in source and binary forms, with or without modification,
//    8 * are permitted provided that the following conditions are met:
//    9 *
//   10 * o Redistributions of source code must retain the above copyright notice, this list
//   11 *   of conditions and the following disclaimer.
//   12 *
//   13 * o Redistributions in binary form must reproduce the above copyright notice, this
//   14 *   list of conditions and the following disclaimer in the documentation and/or
//   15 *   other materials provided with the distribution.
//   16 *
//   17 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
//   18 *   contributors may be used to endorse or promote products derived from this
//   19 *   software without specific prior written permission.
//   20 *
//   21 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//   22 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//   23 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//   24 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
//   25 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//   26 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//   27 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//   28 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//   29 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//   30 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//   31 */
//   32 
//   33 
//   34 /*! *********************************************************************************
//   35 *************************************************************************************
//   36 * Include
//   37 *************************************************************************************
//   38 ********************************************************************************** */
//   39 #include "OtapBootloader.h"
//   40 #include "flash_boot_kinetis.h"
//   41 #include "Eeprom_Boot.h"
//   42 #include "UartBootloader.h"
//   43 
//   44 
//   45 /*! *********************************************************************************
//   46 *************************************************************************************
//   47 * Private Memory Declarations
//   48 *************************************************************************************
//   49 ********************************************************************************** */
//   50 #if defined(__IAR_SYSTEMS_ICC__)
//   51 #pragma section = "IntVectTable"
//   52 #pragma location = "IntVectTable"

        SECTION IntVectTable:CONST:REORDER:ROOT(2)
//   53 __root const vector_entry __vector_table[16] =
__vector_table:
        DATA
        DC32 __BOOT_STACK_ADDRESS, __thumb_startup, defaultISR, defaultISR
        DC32 defaultISR, defaultISR, defaultISR, defaultISR, defaultISR
        DC32 defaultISR, defaultISR, defaultISR, defaultISR, defaultISR
        DC32 defaultISR, defaultISR

        SECTION IntVectTable:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0
//   54 {
//   55     (pointer*)__BOOT_STACK_ADDRESS,  /* Initial SP           */
//   56 
//   57 #elif defined(__GNUC__)
//   58 const vector_entry __vector_table[16] __attribute__ ((section(".vectortable"))) =
//   59 {
//   60     (pointer*)__SP_INIT,  /* Initial SP           */
//   61 #endif
//   62 
//   63     __thumb_startup, /* Initial PC           */
//   64     defaultISR,      /* Non-maskable Interrupt (NMI) */
//   65     defaultISR,      /* Hard Fault */
//   66     defaultISR,      /* MemManage Fault */
//   67     defaultISR,      /* Bus Fault */
//   68     defaultISR,      /* Usage Fault */
//   69     defaultISR,      /* Usage Fault */
//   70     defaultISR,      /* Usage Fault */
//   71     defaultISR,      /* Usage Fault */
//   72     defaultISR,      /* Usage Fault */
//   73     defaultISR,      /* Usage Fault */
//   74     defaultISR,      /* Usage Fault */
//   75     defaultISR,      /* Usage Fault */
//   76     defaultISR,      /* Usage Fault */
//   77     defaultISR       /* Usage Fault */
//   78 };
//   79 
//   80 #if defined(__IAR_SYSTEMS_ICC__)
//   81 #pragma location = "FlashConfig"

        SECTION FlashConfig:CONST:REORDER:ROOT(2)
//   82 __root const FlashConfig_t gFlashConfig @ "FlashConfig" =
gFlashConfig:
        DATA
        DC32 4294967295, 4294967295, 4294967295, 4294967294
//   83 #elif defined(__GNUC__)
//   84 const FlashConfig_t gFlashConfig __attribute__ ((section(".cfmconfig"))) =
//   85 #endif
//   86 {
//   87     {0xFFFFFFFF, 0xFFFFFFFF, gFlashProtection_c, 0xFFFFFFFE}
//   88 };
//   89 
//   90 /* Variables used by the Bootloader */

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   91 volatile bootInfo_t *gpBootInfo;
gpBootInfo:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   92 volatile uint32_t gBootStorageStartAddress;
gBootStorageStartAddress:
        DS8 4
//   93 
//   94 
//   95 /*! *********************************************************************************
//   96 *************************************************************************************
//   97 * Public Functions
//   98 *************************************************************************************
//   99 ********************************************************************************** */
//  100 
//  101 /*! *********************************************************************************
//  102 * \brief   This function determines the start address of the internal sorage.
//  103 *          If value is 0xFFFFFFFF then external storage should be used!
//  104 *
//  105 * \return the start address of the internal storage
//  106 *
//  107 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function Boot_GetInternalStorageStartAddr
          CFI NoCalls
        THUMB
//  108 uint32_t Boot_GetInternalStorageStartAddr(void)
//  109 {
//  110     return *((uint32_t*)(gBootProductInfoAddress_c + gInternalStorageStartAddressOffset_c));
Boot_GetInternalStorageStartAddr:
        LDR      R0,??DataTable5  ;; 0x27c44
        LDR      R0,[R0, #+0]
        BX       LR               ;; return
//  111 }
          CFI EndBlock cfiBlock0
//  112 
//  113 
//  114 /*! *********************************************************************************
//  115 * \brief   The function resets the MCU
//  116 *
//  117 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function Boot_ResetMCU
          CFI NoCalls
        THUMB
//  118 void Boot_ResetMCU(void)
//  119 {
Boot_ResetMCU:
        PUSH     {LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+4
//  120     SCB_AIRCR = SCB_AIRCR_VECTKEY(0x5FA) | SCB_AIRCR_SYSRESETREQ_MASK;
        LDR      R0,??DataTable5_1  ;; 0x5fa0004
        LDR      R1,??DataTable5_2  ;; 0xe000ed0c
        STR      R0,[R1, #+0]
//  121     while(1);
??Boot_ResetMCU_0:
        B        ??Boot_ResetMCU_0
//  122 }
          CFI EndBlock cfiBlock1
//  123 
//  124 
//  125 /*! *********************************************************************************
//  126 * \brief   Start the user application
//  127 *
//  128 * \param[in] userStartup  Address of the application's interrupt vector
//  129 *
//  130 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(2)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function JumpToApplication
          CFI NoCalls
        THUMB
//  131 static void JumpToApplication(volatile uint32_t userStartup)
//  132 {
JumpToApplication:
        PUSH     {R0}
          CFI CFA R13+4
//  133     /* Enable ALL interrupts */
//  134     asm("     cpsie   i       ");
        cpsie   i       
//  135 
//  136     /* set up stack pointer */
//  137     asm("LDR      r1,  [r0]");
        LDR      r1,  [r0]
//  138     asm("MSR      MSP, r1");
        MSR      MSP, r1
//  139 
//  140     /* jump to application reset vector */
//  141     asm("ADDS     r0,r0,#0x04 ");
        ADDS     r0,r0,#0x04 
//  142     asm("LDR      r0, [r0]");
        LDR      r0, [r0]
//  143     asm("BX       r0");
        BX       r0
//  144 }
        ADD      SP,SP,#+4
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock2
//  145 
//  146 
//  147 /*! *********************************************************************************
//  148 * \brief   Initialize the external storage
//  149 *
//  150 * \return status
//  151 *
//  152 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function Boot_InitExternalStorage
        THUMB
//  153 uint8_t Boot_InitExternalStorage(void)
//  154 {
Boot_InitExternalStorage:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  155     if (gBootInvalidAddress_c == gBootStorageStartAddress)
        LDR      R0,??DataTable5_3
        LDR      R0,[R0, #+0]
        MOVS     R1,#+0
        MVNS     R1,R1            ;; #-1
        CMP      R0,R1
        BNE      ??Boot_InitExternalStorage_0
//  156         return EEPROM_Init();
        BL       EEPROM_Init
          CFI FunCall EEPROM_Init
        B        ??Boot_InitExternalStorage_1
//  157 
//  158     return 0;
??Boot_InitExternalStorage_0:
        MOVS     R0,#+0
??Boot_InitExternalStorage_1:
        POP      {R1,PC}          ;; return
          CFI CFA R13+0
//  159 }
          CFI EndBlock cfiBlock3
//  160 
//  161 
//  162 /*! *********************************************************************************
//  163 * \brief   Read data from the external stoage
//  164 *
//  165 * \param[in]  NoOfBytes  number of byter to read
//  166 * \param[in]  Addr       read memory address
//  167 * \param[out] outbuf     location where read data is stored
//  168 *
//  169 * \return error code. 0 if success
//  170 *
//  171 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function Boot_ReadExternalStorage
        THUMB
//  172 uint8_t Boot_ReadExternalStorage(uint16_t NoOfBytes, uint32_t Addr, uint8_t *outbuf)
//  173 {
Boot_ReadExternalStorage:
        PUSH     {R4-R6,LR}
          CFI R14 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//  174     if (gBootInvalidAddress_c == gBootStorageStartAddress)
        LDR      R0,??DataTable5_3
        LDR      R0,[R0, #+0]
        MOVS     R1,#+0
        MVNS     R1,R1            ;; #-1
        CMP      R0,R1
        BNE      ??Boot_ReadExternalStorage_0
//  175     {
//  176         return EEPROM_ReadData(NoOfBytes, Addr, outbuf);
        MOVS     R2,R6
        MOVS     R1,R5
        MOVS     R0,R4
        UXTH     R0,R0
        BL       EEPROM_ReadData
          CFI FunCall EEPROM_ReadData
        B        ??Boot_ReadExternalStorage_1
//  177     }
//  178     else
//  179     {
//  180         Addr += gBootStorageStartAddress;
??Boot_ReadExternalStorage_0:
        LDR      R0,??DataTable5_3
        LDR      R0,[R0, #+0]
        ADDS     R5,R5,R0
//  181         while(NoOfBytes--)
??Boot_ReadExternalStorage_2:
        MOVS     R0,R4
        SUBS     R4,R0,#+1
        UXTH     R0,R0
        CMP      R0,#+0
        BEQ      ??Boot_ReadExternalStorage_3
//  182         {
//  183             *outbuf++ = *((uint8_t*)Addr++);
        LDRB     R0,[R5, #+0]
        STRB     R0,[R6, #+0]
        ADDS     R5,R5,#+1
        ADDS     R6,R6,#+1
        B        ??Boot_ReadExternalStorage_2
//  184         }
//  185 
//  186         return 0;
??Boot_ReadExternalStorage_3:
        MOVS     R0,#+0
??Boot_ReadExternalStorage_1:
        POP      {R4-R6,PC}       ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI CFA R13+0
//  187     }
//  188 }
          CFI EndBlock cfiBlock4
//  189 
//  190 
//  191 /*! *********************************************************************************
//  192 * \brief   This function will copy the User Application from the external memory
//  193 *          into the program Flash
//  194 *
//  195 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function Boot_LoadImage
        THUMB
//  196 void Boot_LoadImage (void)
//  197 {
Boot_LoadImage:
        PUSH     {R4-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+20
        LDR      R4,??DataTable5_4  ;; 0xfffffbec
        ADD      SP,SP,R4
          CFI CFA R13+1064
//  198     static uint8_t bitmapBuffer[gBootData_SectorsBitmap_Size_c];
//  199     bootInfo_t flags;
//  200     uint8_t  buffer[gFlashErasePage_c];
//  201     uint32_t remaingImgSize, len;
//  202     uint32_t flashAddr      = 0;
        MOVS     R5,#+0
//  203     uint8_t  bitMask        = gBitMaskInit_c;
        MOVS     R7,#+1
//  204     uint8_t *pBitmap        = bitmapBuffer;
        LDR      R0,??DataTable5_5
        STR      R0,[SP, #+12]
//  205 #if defined(MCU_MK21DX256)
//  206     vuint8_t* pFlexRamAddress;
//  207     uint8_t  EEEDataSetSize;
//  208     uint16_t size;
//  209 #endif
//  210 
//  211     /* Check if we have a valid internal storage start address. */
//  212     gBootStorageStartAddress = Boot_GetInternalStorageStartAddr();
        BL       Boot_GetInternalStorageStartAddr
          CFI FunCall Boot_GetInternalStorageStartAddr
        LDR      R1,??DataTable5_3
        STR      R0,[R1, #+0]
//  213 
//  214     /* Init the flash module */
//  215     FlashInitialization();
        BL       FlashInitialization
//  216 
//  217     /* Init the external storage */
//  218     Boot_InitExternalStorage();
          CFI FunCall FlashInitialization
        BL       Boot_InitExternalStorage
//  219 
//  220     /* Read image size */
//  221     if (Boot_ReadExternalStorage(gBootData_ImageLength_Size_c,gBootData_ImageLength_Offset_c, (uint8_t*)(&remaingImgSize)))
          CFI FunCall Boot_InitExternalStorage
        ADD      R2,SP,#+4
        MOVS     R1,#+0
        MOVS     R0,#+4
        BL       Boot_ReadExternalStorage
          CFI FunCall Boot_ReadExternalStorage
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_0
//  222         gHandleBootError_d();
        BL       Boot_ResetMCU
//  223 
//  224     /* Read sector bitmap */
//  225     if (Boot_ReadExternalStorage(gBootData_SectorsBitmap_Size_c, gBootData_SectorsBitmap_Offset_c, bitmapBuffer))
??Boot_LoadImage_0:
          CFI FunCall Boot_ResetMCU
        LDR      R2,??DataTable5_5
        MOVS     R1,#+4
        MOVS     R0,#+32
        BL       Boot_ReadExternalStorage
          CFI FunCall Boot_ReadExternalStorage
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_1
//  226         gHandleBootError_d();
        BL       Boot_ResetMCU
//  227 
//  228     /* Start writing the image. Do not alter the last sector which contains HW specific data! */
//  229     while (flashAddr < (gMcuFlashSize_c - gFlashErasePage_c))
??Boot_LoadImage_1:
          CFI FunCall Boot_ResetMCU
        MOVS     R0,#+159
        LSLS     R0,R0,#+10       ;; #+162816
        CMP      R5,R0
        BCS      ??Boot_LoadImage_2
//  230     {
//  231         if (remaingImgSize > gFlashErasePage_c)
        LDR      R0,[SP, #+4]
        LDR      R1,??DataTable5_6  ;; 0x401
        CMP      R0,R1
        BCC      ??Boot_LoadImage_3
//  232             len = gFlashErasePage_c;
        MOVS     R0,#+128
        LSLS     R0,R0,#+3        ;; #+1024
        STR      R0,[SP, #+0]
        B        ??Boot_LoadImage_4
//  233         else
//  234             len = remaingImgSize;
??Boot_LoadImage_3:
        LDR      R0,[SP, #+4]
        STR      R0,[SP, #+0]
//  235 
//  236         /* Check if bitmap indicates that this sector is write protected and shouldn't be updated */
//  237         if ((*pBitmap & bitMask) && (flashAddr >= gUserFlashStart_d))
??Boot_LoadImage_4:
        LDR      R0,[SP, #+12]
        LDRB     R0,[R0, #+0]
        TST      R0,R7
        BEQ      ??Boot_LoadImage_5
        LDR      R0,??DataTable5_7
        CMP      R5,R0
        BCC      ??Boot_LoadImage_5
//  238         {
//  239             /* Erase Flash sector */
//  240             if (FLASH_OK != FLASH_EraseSector(flashAddr))
        MOVS     R0,R5
        BL       FLASH_EraseSector
          CFI FunCall FLASH_EraseSector
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_6
//  241                 gHandleBootError_d();
        BL       Boot_ResetMCU
//  242 
//  243             if (len)
??Boot_LoadImage_6:
          CFI FunCall Boot_ResetMCU
        LDR      R0,[SP, #+0]
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_5
//  244             {
//  245                 /* Read a new image block */
//  246                 if (Boot_ReadExternalStorage(len, flashAddr + gBootData_Image_Offset_c, buffer))
        ADD      R2,SP,#+16
        MOVS     R1,R5
        ADDS     R1,R1,#+36
        LDR      R0,[SP, #+0]
        UXTH     R0,R0
        BL       Boot_ReadExternalStorage
          CFI FunCall Boot_ReadExternalStorage
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_7
//  247                     gHandleBootError_d();
        BL       Boot_ResetMCU
//  248 
//  249 
//  250                 if( (flashAddr <= gBootImageFlagsAddress_c) && (flashAddr + len > gBootImageFlagsAddress_c) )
??Boot_LoadImage_7:
          CFI FunCall Boot_ResetMCU
        LDR      R0,??DataTable5_8
        CMP      R0,R5
        BCC      ??Boot_LoadImage_8
        LDR      R0,??DataTable5_8
        LDR      R1,[SP, #+0]
        ADDS     R1,R5,R1
        CMP      R0,R1
        BCS      ??Boot_LoadImage_8
//  251                 {
//  252                     uint32_t i, offset = gBootImageFlagsAddress_c - flashAddr;
        LDR      R0,??DataTable5_8
        SUBS     R6,R0,R5
//  253                     /* Program the Flash before boot flags */
//  254                     if(FLASH_OK != FLASH_Program(flashAddr, (uint32_t)buffer, offset))
        MOVS     R2,R6
        ADD      R1,SP,#+16
        MOVS     R0,R5
        BL       FLASH_Program
          CFI FunCall FLASH_Program
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_9
//  255                         gHandleBootError_d();
        BL       Boot_ResetMCU
//  256 
//  257                     /* Keep the boot flags set  until the all image is downloaded */
//  258                     for( i=0; i<gEepromParams_WriteAlignment_c; i++ )
??Boot_LoadImage_9:
          CFI FunCall Boot_ResetMCU
        MOVS     R0,#+0
        MOVS     R4,R0
??Boot_LoadImage_10:
        CMP      R4,#+0
        BNE      ??Boot_LoadImage_11
//  259                     {
//  260                         flags.newBootImageAvailable[i] = gBootValueForFALSE_c;
        MOVS     R0,#+255
        ADD      R1,SP,#+8
        STRB     R0,[R1, R4]
//  261                         flags.bootProcessCompleted[i] = gBootValueForTRUE_c;
        MOVS     R0,#+0
        ADD      R1,SP,#+8
        ADDS     R1,R1,R4
        STRB     R0,[R1, #+1]
//  262                     }
        ADDS     R4,R4,#+1
        B        ??Boot_LoadImage_10
//  263                     i = offset + 2 * gEepromParams_WriteAlignment_c;
??Boot_LoadImage_11:
        MOVS     R0,R6
        ADDS     R0,R0,#+2
        MOVS     R4,R0
//  264                     flags.bootVersion[0] = buffer[i++];
        ADD      R0,SP,#+16
        LDRB     R0,[R0, R4]
        ADD      R1,SP,#+8
        STRB     R0,[R1, #+2]
        ADDS     R4,R4,#+1
//  265                     flags.bootVersion[1] = buffer[i];
        ADD      R0,SP,#+16
        LDRB     R0,[R0, R4]
        ADD      R1,SP,#+8
        STRB     R0,[R1, #+3]
//  266                     offset += gEepromAlignAddr_d(sizeof(bootInfo_t));
        ADDS     R6,R6,#+4
//  267 
//  268                     /* Program the Flash after the boot flags*/
//  269                     if(FLASH_OK != FLASH_Program(flashAddr + offset, (uint32_t)(&buffer[offset]), len - offset))
        LDR      R0,[SP, #+0]
        SUBS     R2,R0,R6
        ADD      R0,SP,#+16
        ADDS     R1,R0,R6
        ADDS     R0,R5,R6
        BL       FLASH_Program
          CFI FunCall FLASH_Program
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_5
//  270                         gHandleBootError_d();
        BL       Boot_ResetMCU
          CFI FunCall Boot_ResetMCU
        B        ??Boot_LoadImage_5
//  271                 }
//  272                 else
//  273                 {
//  274                     /* Program the image block to Flash */
//  275                     if(FLASH_OK != FLASH_Program(flashAddr, (uint32_t)buffer, len))
??Boot_LoadImage_8:
        LDR      R2,[SP, #+0]
        ADD      R1,SP,#+16
        MOVS     R0,R5
        BL       FLASH_Program
          CFI FunCall FLASH_Program
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_5
//  276                         gHandleBootError_d();
        BL       Boot_ResetMCU
//  277                 }
//  278             }
//  279         }
//  280 
//  281         /* Update Bitmask */
//  282         bitMask <<= 1;
??Boot_LoadImage_5:
          CFI FunCall Boot_ResetMCU
        LSLS     R7,R7,#+1
//  283         if (bitMask == 0)
        UXTB     R7,R7
        CMP      R7,#+0
        BNE      ??Boot_LoadImage_12
//  284         {
//  285             /* This was last bit in the current bitmap byte. Move to next bitmap byte */
//  286             bitMask = gBitMaskInit_c;
        MOVS     R0,#+1
        MOVS     R7,R0
//  287             pBitmap++;
        LDR      R0,[SP, #+12]
        ADDS     R0,R0,#+1
        STR      R0,[SP, #+12]
//  288         }
//  289 
//  290         /* Update the current flash address */
//  291         flashAddr += gFlashErasePage_c;
??Boot_LoadImage_12:
        MOVS     R0,#+128
        LSLS     R0,R0,#+3        ;; #+1024
        ADDS     R5,R5,R0
//  292 
//  293         /* Update the remaining bytes*/
//  294         if (remaingImgSize)
        LDR      R0,[SP, #+4]
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_1
//  295             remaingImgSize -= len;
        LDR      R0,[SP, #+4]
        LDR      R1,[SP, #+0]
        SUBS     R0,R0,R1
        STR      R0,[SP, #+4]
        B        ??Boot_LoadImage_1
//  296     } /* while */
//  297 
//  298 #if defined(MCU_MK21DX256)
//  299 
//  300     while((FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK) != FTFL_FSTAT_CCIF_MASK)
//  301     {
//  302         /* wait till CCIF bit is set */
//  303     }
//  304 
//  305     /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
//  306     FTFL_FSTAT = (FTFL_FSTAT_RDCOLERR_MASK | FTFL_FSTAT_ACCERR_MASK |
//  307                   FTFL_FSTAT_FPVIOL_MASK);
//  308 
//  309     /* Write Command Code to FCCOB0 */
//  310     FTFL_FCCOB0 = FLASH_READ_RESOURCE;
//  311     /* Write address to FCCOB1/2/3 */
//  312     FTFL_FCCOB1 = ((uint8_t)(FLASH_DFLASH_IFR_READRESOURCE_ADDRESS >> 16));
//  313     FTFL_FCCOB2 = ((uint8_t)((FLASH_DFLASH_IFR_READRESOURCE_ADDRESS >> 8) & 0xFF));
//  314     FTFL_FCCOB3 = ((uint8_t)(FLASH_DFLASH_IFR_READRESOURCE_ADDRESS & 0xFF));
//  315 
//  316     /* Write Resource Select Code of 0 to FCCOB8 to select IFR. Without this, */
//  317     /* an access error may occur if the register contains data from a previous command. */
//  318     FTFL_FCCOB8 = 0;
//  319 
//  320     /* clear CCIF bit */
//  321     FTFL_FSTAT |= FTFL_FSTAT_CCIF_MASK;
//  322 
//  323     /* check CCIF bit */
//  324     while((FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK) != FTFL_FSTAT_CCIF_MASK)
//  325     {
//  326         /* wait till CCIF bit is set */
//  327     }
//  328 
//  329     /* read the FlexRAM window size */
//  330     EEEDataSetSize = FTFL_FCCOB6;
//  331     EEEDataSetSize &= 0x0F;
//  332 
//  333     if((EEEDataSetSize == 2) || (EEEDataSetSize == 3)) /* FlexRAM size is 4KB or 2KB */
//  334     {
//  335         /* Enable EEE */
//  336         FLASH_SetEEEEnable(FLASH_FLEXRAM_FNC_CTRL_CODE);
//  337 
//  338         pBitmap = &bitmapBuffer[0] + (uint32_t)((gMcuFlashSize_c/gFlashErasePage_c)/8);
//  339 
//  340         if(EEEDataSetSize == 2) /* 4KB */
//  341         {
//  342             if(*pBitmap & 0x01)
//  343             {
//  344                 size = gBootFlexRam_4K_Size_c/2;
//  345                 pFlexRamAddress = (vuint8_t*)((uint32_t)gBootFlexRAMBaseAddress_c);
//  346                 while(size--)
//  347                 {
//  348                     /* wait for EEPROM system to be ready */
//  349                     while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//  350                     *pFlexRamAddress = 0xFF;
//  351                     pFlexRamAddress ++;
//  352                 }
//  353             }
//  354             if(*pBitmap & 0x02)
//  355             {
//  356                 size = gBootFlexRam_4K_Size_c/2;
//  357                 pFlexRamAddress = (vuint8_t*)((uint32_t)(gBootFlexRAMBaseAddress_c + size));
//  358                 while(size--)
//  359                 {
//  360                     /* wait for EEPROM system to be ready */
//  361                     while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//  362                     *pFlexRamAddress = 0xFF;
//  363                     pFlexRamAddress ++;
//  364                 }
//  365             }
//  366         }
//  367         else if (EEEDataSetSize == 3) /* 2K */
//  368         {
//  369             if(*pBitmap & 0x01)
//  370             {
//  371                 size = gBootFlexRam_2K_Size_c/2;
//  372                 pFlexRamAddress = (vuint8_t*)((uint32_t)gBootFlexRAMBaseAddress_c);
//  373                 while(size--)
//  374                 {
//  375                     /* wait for EEPROM system to be ready */
//  376                     while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//  377                     *pFlexRamAddress = 0xFF;
//  378                     pFlexRamAddress ++;
//  379                 }
//  380             }
//  381             if(*pBitmap & 0x02)
//  382             {
//  383                 size = gBootFlexRam_2K_Size_c/2;
//  384                 pFlexRamAddress = (vuint8_t*)((uint32_t)(gBootFlexRAMBaseAddress_c + size));
//  385                 while(size--)
//  386                 {
//  387                     /* wait for EEPROM system to be ready */
//  388                     while(!(FTFL_FCNFG & FTFL_FCNFG_EEERDY_MASK));
//  389                     *pFlexRamAddress = 0xFF;
//  390                     pFlexRamAddress ++;
//  391                 }
//  392             }
//  393         }
//  394     }
//  395 #endif
//  396 
//  397 
//  398     /* Set the bBootProcessCompleted Flag */
//  399     if( FLASH_OK != FLASH_Program((uint32_t)gBootImageFlagsAddress_c, (uint32_t)&flags, sizeof(flags)) )
??Boot_LoadImage_2:
        MOVS     R2,#+4
        ADD      R1,SP,#+8
        LDR      R0,??DataTable5_8
        BL       FLASH_Program
          CFI FunCall FLASH_Program
        CMP      R0,#+0
        BEQ      ??Boot_LoadImage_13
//  400         gHandleBootError_d();
        BL       Boot_ResetMCU
//  401 
//  402     /* Reseting MCU */
//  403     Boot_ResetMCU();
??Boot_LoadImage_13:
          CFI FunCall Boot_ResetMCU
        BL       Boot_ResetMCU
//  404 }
          CFI FunCall Boot_ResetMCU
        LDR      R0,??DataTable5_9  ;; 0x414
        ADD      SP,SP,R0
          CFI CFA R13+20
        POP      {R4-R7,PC}       ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
          CFI EndBlock cfiBlock5

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
??bitmapBuffer:
        DS8 32
//  405 
//  406 /*! *********************************************************************************
//  407 * \brief   This is the Bootloader's entry point
//  408 *
//  409 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function __thumb_startup
        THUMB
//  410 void __thumb_startup(void)
//  411 {
__thumb_startup:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  412     (void)main(0, 0);
        MOVS     R1,#+0
        MOVS     R0,#+0
        BL       main
//  413 }
          CFI FunCall main
        POP      {R0,PC}          ;; return
          CFI CFA R13+0
          CFI EndBlock cfiBlock6
//  414 
//  415 /*! *********************************************************************************
//  416 * \brief   This is the main Bootloader function.
//  417 *          It decides if it will load a new image or jump to the application
//  418 *
//  419 * \param[in] argc
//  420 * \param[in] argv
//  421 *
//  422 * \return int
//  423 *
//  424 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(2)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function main
        THUMB
//  425 int main(int argc, char **argv)
//  426 {
main:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R5,R0
        MOVS     R4,R1
//  427     /* Disable interrupt by default */
//  428     asm("     CPSID   i       ");
        CPSID   i       
//  429 
//  430     /* Set the start address of the interrupt vector*/
//  431     SCB_VTOR = (uint32_t)__region_BOOT_ROM_start__;
        LDR      R0,??DataTable5_10
        LDR      R1,??DataTable5_11  ;; 0xe000ed08
        STR      R0,[R1, #+0]
//  432 
//  433     /* Disable watchdog */
//  434 #if defined(MCU_MK21DN512) || defined(MCU_MK21DX256) || defined(MCU_MK64FN1M)
//  435     WDOG_UNLOCK = 0xC520;
//  436     WDOG_UNLOCK = 0xD928;
//  437     WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
//  438 #elif defined(MCU_MKL46Z256) || defined(MCU_MKW40Z160)
//  439     SIM_COPC = SIM_COPC_COPT(0);
        MOVS     R0,#+0
        LDR      R1,??DataTable5_12  ;; 0x40048100
        STR      R0,[R1, #+0]
//  440 #endif
//  441 #if gSerialBootloaderEnable_c
//  442     BOOT_PIN_ENABLE_SIM_SCG_REG |= BOOT_PIN_ENABLE_SIM_SCG_MASK;
//  443     PORT_PCR_REG(BOOT_PIN_ENABLE_PORT_BASE,BOOT_PIN_ENABLE_NUM) = PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
//  444     {
//  445         vuint32_t delay;
//  446         delay = 5;
//  447         while(--delay);
//  448     }
//  449     if((GPIO_PDIR_REG(BOOT_PIN_ENABLE_GPIO_BASE) & (1 << BOOT_PIN_ENABLE_NUM)) == 0)
//  450     {
//  451         CheckForUartLoader();
//  452     }
//  453 #endif
//  454     /* Check if there is no boot image available in the external EEPROM and if eventually
//  455     the booting of the previous one has been completed. If both conditions are met, start
//  456     running the application in the internal Flash. Else, start the process of booting from
//  457     external EEPROM */
//  458     gpBootInfo = (bootInfo_t*)gBootImageFlagsAddress_c;
        LDR      R0,??DataTable5_8
        LDR      R1,??DataTable5_13
        STR      R0,[R1, #+0]
//  459     /*
//  460     if( (gpBootInfo->newBootImageAvailable == gBootValueForTRUE_c) &&
//  461     (gpBootInfo->bootProcessCompleted ==  gBootValueForFALSE_c) )
//  462     */
//  463     if ((gpBootInfo->newBootImageAvailable[0] != gBootValueForTRUE_c) &&
//  464         (gpBootInfo->bootProcessCompleted[0] ==  gBootValueForTRUE_c))
        LDR      R0,??DataTable5_13
        LDR      R0,[R0, #+0]
        LDRB     R0,[R0, #+0]
        CMP      R0,#+0
        BEQ      ??main_0
        LDR      R0,??DataTable5_13
        LDR      R0,[R0, #+0]
        LDRB     R0,[R0, #+1]
        CMP      R0,#+0
        BNE      ??main_0
//  465     {
//  466         /* Set the start address of the interrupt vector*/
//  467         SCB_VTOR = gUserFlashStart_d;
        LDR      R0,??DataTable5_7
        LDR      R1,??DataTable5_11  ;; 0xe000ed08
        STR      R0,[R1, #+0]
//  468         JumpToApplication(gUserFlashStart_d);
        LDR      R0,??DataTable5_7
        BL       JumpToApplication
          CFI FunCall JumpToApplication
        B        ??main_1
//  469     }
//  470     else
//  471     {
//  472         /* Write the new image */
//  473         Boot_LoadImage();
??main_0:
        BL       Boot_LoadImage
//  474     }
//  475 
//  476     return 0;
??main_1:
          CFI FunCall Boot_LoadImage
        MOVS     R0,#+0
        POP      {R1,R4,R5,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
//  477 }
          CFI EndBlock cfiBlock7

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5:
        DC32     0x27c44

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_1:
        DC32     0x5fa0004

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_2:
        DC32     0xe000ed0c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_3:
        DC32     gBootStorageStartAddress

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_4:
        DC32     0xfffffbec

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_5:
        DC32     ??bitmapBuffer

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_6:
        DC32     0x401

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_7:
        DC32     __region_BOOT_ROM_end__+0x1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_8:
        DC32     __region_BOOT_ROM_end__+0xC1

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_9:
        DC32     0x414

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_10:
        DC32     __region_BOOT_ROM_start__

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_11:
        DC32     0xe000ed08

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_12:
        DC32     0x40048100

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5_13:
        DC32     gpBootInfo
//  478 
//  479 /*! *********************************************************************************
//  480 * \brief   Default ISR handler
//  481 *
//  482 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function defaultISR
        THUMB
//  483 void defaultISR(void)
//  484 {
defaultISR:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  485     /* ISR code */
//  486     gHandleBootError_d();
        BL       Boot_ResetMCU
//  487 }
          CFI FunCall Boot_ResetMCU
        POP      {R0,PC}          ;; return
          CFI CFA R13+0
          CFI EndBlock cfiBlock8

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//  488 //-----------------------------------------------------------------------------
// 
//  40 bytes in section .bss
// 618 bytes in section .text
//  16 bytes in section FlashConfig
//  64 bytes in section IntVectTable
// 
// 618 bytes of CODE  memory
//  80 bytes of CONST memory
//  40 bytes of DATA  memory
//
//Errors: none
//Warnings: none
