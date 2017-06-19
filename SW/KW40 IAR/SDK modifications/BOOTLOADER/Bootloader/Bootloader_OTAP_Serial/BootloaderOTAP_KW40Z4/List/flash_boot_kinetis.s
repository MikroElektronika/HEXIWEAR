///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       12/Jan/2016  08:59:56
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\flash\flash_boot_kinetis.c
//    Command line =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\flash\flash_boot_kinetis.c
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
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\flash_boot_kinetis.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__SystemLibrary", "DLib"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        EXTERN __aeabi_uidivmod

        PUBLIC ExecuteOnStack
        PUBLIC FLASH_EraseSector
        PUBLIC FLASH_MassErase
        PUBLIC FLASH_Program
        PUBLIC FLASH_ProgramByte
        PUBLIC FLASH_ProgramLongWord
        PUBLIC FLASH_ProgramLongWords
        PUBLIC FLASH_ProgramSection
        PUBLIC FLASH_ProgramSectionPhrases
        PUBLIC FLASH_SetEEEEnable
        PUBLIC FlashInitialization
        PUBLIC buffer
        PUBLIC pCommandArray
        PUBLIC programbuffer
        
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
        
// C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\flash\flash_boot_kinetis.c
//    1 /*!
//    2 * Copyright (c) 2015, Freescale Semiconductor, Inc.
//    3 * All rights reserved.
//    4 *
//    5 * \file filename.h
//    6 * This file brief description
//    7 *
//    8 * Redistribution and use in source and binary forms, with or without modification,
//    9 * are permitted provided that the following conditions are met:
//   10 *
//   11 * o Redistributions of source code must retain the above copyright notice, this list
//   12 *   of conditions and the following disclaimer.
//   13 *
//   14 * o Redistributions in binary form must reproduce the above copyright notice, this
//   15 *   list of conditions and the following disclaimer in the documentation and/or
//   16 *   other materials provided with the distribution.
//   17 *
//   18 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
//   19 *   contributors may be used to endorse or promote products derived from this
//   20 *   software without specific prior written permission.
//   21 *
//   22 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//   23 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//   24 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//   25 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
//   26 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//   27 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//   28 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//   29 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//   30 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//   31 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//   32 */
//   33 
//   34 
//   35 /*! *********************************************************************************
//   36 *************************************************************************************
//   37 * Include
//   38 *************************************************************************************
//   39 ********************************************************************************** */
//   40 #include "flash_boot_kinetis.h"
//   41 #include "OtapBootloader.h"
//   42 
//   43 
//   44 /*! *********************************************************************************
//   45 *************************************************************************************
//   46 * Private macros
//   47 *************************************************************************************
//   48 ********************************************************************************** */
//   49 
//   50 #if (gEepromParams_WriteAlignment_c > 4) 
//   51     #define FLASH_PGM_SIZE (gEepromParams_WriteAlignment_c)
//   52 #else
//   53     #define FLASH_PGM_SIZE (4)
//   54 #endif
//   55 
//   56 #define NoOfElements(x) (sizeof(x)/sizeof(x[0]))
//   57 
//   58 
//   59 /*! *********************************************************************************
//   60 *************************************************************************************
//   61 * Private Memory Declarations
//   62 *************************************************************************************
//   63 ********************************************************************************** */

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   64 uint8_t pCommandArray[FCCOB_REGS];
pCommandArray:
        DS8 12

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   65 static FCC0B_STR CommandObj;
CommandObj:
        DS8 12

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   66 void (*ExecuteOnStack)(void) = NULL;
ExecuteOnStack:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   67 uint8_t buffer[128];
buffer:
        DS8 128
//   68 
//   69 #if defined(__IAR_SYSTEMS_ICC__)

        ASEGN `.noinit`:DATA:NOROOT,014000000H
        SECTION_GROUP programbuffer
//   70 __no_init uint32_t programbuffer[512] @0x14000000;
programbuffer:
        DS8 2048
//   71 #elif defined(__GNUC__)
//   72 uint32_t programbuffer[512] __attribute__ ((section(".progBuffer")));
//   73 #endif
//   74 
//   75 /*! *********************************************************************************
//   76 *************************************************************************************
//   77 * Private prototypes
//   78 *************************************************************************************
//   79 ********************************************************************************** */
//   80 //  internal driver function
//   81 static uint8_t FLASH_FlashCommandSequence(uint8_t index);
//   82 static void ExecuteOnStackStart();
//   83 
//   84 
//   85 /*! *********************************************************************************
//   86 *************************************************************************************
//   87 * Public Functions
//   88 *************************************************************************************
//   89 ********************************************************************************** */
//   90 
//   91 /********************************************************
//   92 * Init Function
//   93 *
//   94 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function FlashInitialization
          CFI NoCalls
        THUMB
//   95 void FlashInitialization(void)
//   96 {
FlashInitialization:
        PUSH     {LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+4
//   97     uint16_t i, size;
//   98     
//   99     //  RAM function should have the same alignment as one from ROM
//  100     if( ((uint32_t)ExecuteOnStackStart - 1) & 0x03 )
        LDR      R2,??DataTable5
        LSLS     R2,R2,#+30
        BEQ      ??FlashInitialization_0
//  101         i = 2;
        MOVS     R2,#+2
        MOVS     R0,R2
        B        ??FlashInitialization_1
//  102     else
//  103         i = 0;
??FlashInitialization_0:
        MOVS     R2,#+0
        MOVS     R0,R2
//  104     
//  105     size = sizeof(buffer) - i;
??FlashInitialization_1:
        MOVS     R2,#+128
        SUBS     R2,R2,R0
        MOVS     R1,R2
//  106     
//  107     //  initialize pointer to ram function
//  108     ExecuteOnStack = (void(*)(void))&buffer[i+1];
        LDR      R2,??DataTable7
        UXTH     R0,R0
        ADDS     R2,R2,R0
        ADDS     R2,R2,#+1
        LDR      R3,??DataTable7_1
        STR      R2,[R3, #+0]
//  109     
//  110     //  copy function from ROM to RAM
//  111     for( ; i<size; i++ )
??FlashInitialization_2:
        UXTH     R0,R0
        UXTH     R1,R1
        CMP      R0,R1
        BCS      ??FlashInitialization_3
//  112         buffer[i] = ((uint8_t*)ExecuteOnStackStart)[i-1];
        LDR      R2,??DataTable7_2
        UXTH     R0,R0
        ADDS     R2,R2,R0
        SUBS     R2,R2,#+1
        LDRB     R2,[R2, #+0]
        LDR      R3,??DataTable7
        UXTH     R0,R0
        STRB     R2,[R3, R0]
        ADDS     R0,R0,#+1
        B        ??FlashInitialization_2
//  113     
//  114     //  inititalization of flash clock module
//  115     FLASH_INIT_FLASH_CLOCK;
??FlashInitialization_3:
        LDR      R2,??DataTable8  ;; 0x4004803c
        LDR      R2,[R2, #+0]
        MOVS     R3,#+1
        ORRS     R3,R3,R2
        LDR      R2,??DataTable8  ;; 0x4004803c
        STR      R3,[R2, #+0]
//  116 }
        POP      {PC}             ;; return
          CFI CFA R13+0
          CFI EndBlock cfiBlock0
//  117 
//  118 /********************************************************
//  119 * Generic FLASH programing function
//  120 *
//  121 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function FLASH_Program
        THUMB
//  122 uint8_t FLASH_Program(uint32_t dest, uint32_t source, uint32_t size)
//  123 {
FLASH_Program:
        PUSH     {R1,R4-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        SUB      SP,SP,#+8
          CFI CFA R13+32
        MOVS     R7,R0
        MOVS     R4,R2
//  124     uint32_t i;
//  125     uint8_t* pSource = (uint8_t*)source;
        LDR      R6,[SP, #+8]
//  126     uint8_t temp[FLASH_PGM_SIZE];
//  127 
//  128     /* Check for unaligned destination address */
//  129     if (dest & (FLASH_PGM_SIZE - 0x01U))
        LSLS     R0,R7,#+30       ;; ZeroExtS R0,R7,#+30,#+30
        LSRS     R0,R0,#+30
        CMP      R0,#+0
        BEQ      ??FLASH_Program_0
//  130     {
//  131        return FLASH_FAIL;
        MOVS     R0,#+1
        B        ??FLASH_Program_1
//  132     }
//  133     
//  134     while( size )
??FLASH_Program_0:
        CMP      R4,#+0
        BEQ      ??FLASH_Program_2
//  135     {
//  136         /* data must be multiple of FLASH_PGM_SIZE */
//  137         if( size > 0 && size < FLASH_PGM_SIZE  )
        CMP      R4,#+0
        BEQ      ??FLASH_Program_3
        CMP      R4,#+4
        BCS      ??FLASH_Program_3
//  138         {
//  139             for( i=0; i<size; i++ )
        MOVS     R0,#+0
        MOVS     R5,R0
??FLASH_Program_4:
        CMP      R5,R4
        BCS      ??FLASH_Program_5
//  140             {
//  141                 temp[i] = *pSource++;
        LDRB     R0,[R6, #+0]
        MOV      R1,SP
        STRB     R0,[R1, R5]
        ADDS     R6,R6,#+1
//  142             }
        ADDS     R5,R5,#+1
        B        ??FLASH_Program_4
//  143                 
//  144             for( i=size; i<FLASH_PGM_SIZE; i++ )
??FLASH_Program_5:
        MOVS     R5,R4
??FLASH_Program_6:
        CMP      R5,#+4
        BCS      ??FLASH_Program_7
//  145             {
//  146                 temp[i] = 0xFF;
        MOVS     R0,#+255
        MOV      R1,SP
        STRB     R0,[R1, R5]
//  147             }
        ADDS     R5,R5,#+1
        B        ??FLASH_Program_6
//  148                 
//  149             pSource = temp;
??FLASH_Program_7:
        MOV      R0,SP
        MOVS     R6,R0
//  150             size = FLASH_PGM_SIZE;
        MOVS     R0,#+4
        MOVS     R4,R0
//  151         }
//  152             
//  153         /* preparing passing parameter to program the flash block */
//  154         CommandObj.regsLong.fccob3210 = dest;
??FLASH_Program_3:
        LDR      R0,??DataTable10
        STR      R7,[R0, #+0]
//  155 #if (FLASH_PGM_SIZE==8)
//  156         CommandObj.regs.fccob0 = FLASH_PROGRAM_PHRASE;
//  157         
//  158 #else
//  159         CommandObj.regs.fccob0 = FLASH_PROGRAM_LONGWORD;
        MOVS     R0,#+6
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+3]
//  160 #endif
//  161         for( i=4; i<FLASH_PGM_SIZE+4; i++ )
        MOVS     R0,#+4
        MOVS     R5,R0
??FLASH_Program_8:
        CMP      R5,#+8
        BCS      ??FLASH_Program_9
//  162         {
//  163             CommandObj.all[i] = *pSource++;
        LDRB     R0,[R6, #+0]
        LDR      R1,??DataTable10
        STRB     R0,[R1, R5]
        ADDS     R6,R6,#+1
//  164         }
        ADDS     R5,R5,#+1
        B        ??FLASH_Program_8
//  165 
//  166         /* calling flash command sequence function to execute the command */
//  167         if( FLASH_OK != FLASH_FlashCommandSequence(i) )
??FLASH_Program_9:
        MOVS     R0,R5
        UXTB     R0,R0
        BL       FLASH_FlashCommandSequence
          CFI FunCall FLASH_FlashCommandSequence
        CMP      R0,#+0
        BEQ      ??FLASH_Program_10
//  168             return FLASH_FAIL;
        MOVS     R0,#+1
        B        ??FLASH_Program_1
//  169     
//  170         /* update destination address for next iteration */
//  171         dest += FLASH_PGM_SIZE;
??FLASH_Program_10:
        ADDS     R7,R7,#+4
//  172         /* update size for next iteration */
//  173         size -= FLASH_PGM_SIZE;
        SUBS     R4,R4,#+4
        B        ??FLASH_Program_0
//  174     }
//  175 
//  176     return FLASH_OK;
??FLASH_Program_2:
        MOVS     R0,#+0
??FLASH_Program_1:
        POP      {R1-R7,PC}       ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
//  177 }
          CFI EndBlock cfiBlock1
//  178 
//  179 /********************************************************
//  180 * Function for Programming multiple Long Word
//  181 *
//  182 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function FLASH_ProgramLongWords
        THUMB
//  183 uint8_t FLASH_ProgramLongWords(uint32_t destination, uint32_t source, uint32_t size)
//  184 {
FLASH_ProgramLongWords:
        PUSH     {R1,R4-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        SUB      SP,SP,#+8
          CFI CFA R13+32
        MOVS     R4,R0
        MOVS     R6,R2
//  185     uint8_t ret = FLASH_OK;
        MOVS     R0,#+0
        MOV      R1,SP
        STRB     R0,[R1, #+4]
//  186     uint8_t bytes;
//  187     uint32_t alignedWord;
//  188     uint8_t* pbSource = (uint8_t*)source;
        LDR      R7,[SP, #+8]
//  189     
//  190     bytes = destination & 0x03;
        MOVS     R0,R4
        LSLS     R0,R0,#+30       ;; ZeroExtS R0,R0,#+30,#+30
        LSRS     R0,R0,#+30
        MOVS     R5,R0
//  191     destination &= ~((uint32_t)0x03);
        MOVS     R0,#+3
        BICS     R4,R4,R0
//  192     if( bytes )
        UXTB     R5,R5
        CMP      R5,#+0
        BEQ      ??FLASH_ProgramLongWords_0
//  193     {
//  194         /* Go to previous aligned address */
//  195         alignedWord = *((uint32_t*)destination);
        LDR      R0,[R4, #+0]
        STR      R0,[SP, #+0]
//  196         
//  197     }
//  198     while(size)
??FLASH_ProgramLongWords_0:
        CMP      R6,#+0
        BEQ      ??FLASH_ProgramLongWords_1
//  199     {
//  200         ((uint8_t*)&alignedWord)[bytes] = *pbSource++;
        LDRB     R0,[R7, #+0]
        MOV      R1,SP
        UXTB     R5,R5
        STRB     R0,[R1, R5]
        ADDS     R7,R7,#+1
//  201         size--;
        SUBS     R6,R6,#+1
//  202         if((bytes == 3)||(size == 0))
        UXTB     R5,R5
        CMP      R5,#+3
        BEQ      ??FLASH_ProgramLongWords_2
        CMP      R6,#+0
        BNE      ??FLASH_ProgramLongWords_3
//  203         {
//  204             ret = FLASH_ProgramLongWord(destination, alignedWord);
??FLASH_ProgramLongWords_2:
        LDR      R1,[SP, #+0]
        MOVS     R0,R4
        BL       FLASH_ProgramLongWord
          CFI FunCall FLASH_ProgramLongWord
        MOV      R1,SP
        STRB     R0,[R1, #+4]
//  205             if(FLASH_OK != ret )
        MOV      R0,SP
        LDRB     R0,[R0, #+4]
        CMP      R0,#+0
        BEQ      ??FLASH_ProgramLongWords_4
//  206             {
//  207                 return ret;
        MOV      R0,SP
        LDRB     R0,[R0, #+4]
        B        ??FLASH_ProgramLongWords_5
//  208             }
//  209             if(size)
??FLASH_ProgramLongWords_4:
        CMP      R6,#+0
        BEQ      ??FLASH_ProgramLongWords_3
//  210             {
//  211                 destination += 4;
        ADDS     R4,R4,#+4
//  212                 if(size < 4)
        CMP      R6,#+4
        BCS      ??FLASH_ProgramLongWords_3
//  213                 {
//  214                     alignedWord = *((uint32_t*)destination);
        LDR      R0,[R4, #+0]
        STR      R0,[SP, #+0]
//  215                 }
//  216             }
//  217         }  
//  218         bytes = (bytes+1) & 0x3;
??FLASH_ProgramLongWords_3:
        ADDS     R5,R5,#+1
        LSLS     R5,R5,#+30       ;; ZeroExtS R5,R5,#+30,#+30
        LSRS     R5,R5,#+30
        B        ??FLASH_ProgramLongWords_0
//  219     }
//  220     
//  221     
//  222     return FLASH_OK;
??FLASH_ProgramLongWords_1:
        MOVS     R0,#+0
??FLASH_ProgramLongWords_5:
        POP      {R1-R7,PC}       ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
//  223 }
          CFI EndBlock cfiBlock2
//  224 /********************************************************
//  225 * Function for Programming of one Long Word
//  226 *
//  227 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function FLASH_ProgramLongWord
        THUMB
//  228 uint8_t FLASH_ProgramLongWord(uint32_t destination, uint32_t data32b)
//  229 {
FLASH_ProgramLongWord:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R5,R0
        MOVS     R4,R1
//  230     /* preparing passing parameter to program the flash block */
//  231     
//  232     CommandObj.regsLong.fccob3210 = destination;
        LDR      R0,??DataTable10
        STR      R5,[R0, #+0]
//  233     CommandObj.regs.fccob0 = FLASH_PROGRAM_LONGWORD;
        MOVS     R0,#+6
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+3]
//  234     CommandObj.regsLong.fccob7654 = data32b;
        LDR      R0,??DataTable10
        STR      R4,[R0, #+4]
//  235     
//  236     return FLASH_FlashCommandSequence(PROGRAM_LONGWORD_INDEX);
        MOVS     R0,#+8
        BL       FLASH_FlashCommandSequence
          CFI FunCall FLASH_FlashCommandSequence
        POP      {R1,R4,R5,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
//  237 }
          CFI EndBlock cfiBlock3
//  238 
//  239 /********************************************************
//  240 * Function for Programming of one section (maximum is 2048 Bytes)
//  241 *
//  242 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function FLASH_ProgramSection
        THUMB
//  243 uint8_t FLASH_ProgramSection(uint32_t destination, uint32_t* pSource, uint32_t size)
//  244 {
FLASH_ProgramSection:
        PUSH     {R0,R1,R4-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+28
        SUB      SP,SP,#+4
          CFI CFA R13+32
        MOVS     R5,R2
//  245     uint8_t* pProgBuff = (uint8_t*)&programbuffer[0];
        MOVS     R4,#+160
        LSLS     R4,R4,#+21       ;; #+335544320
//  246     uint8_t* pSrc = (uint8_t*)pSource;
        LDR      R7,[SP, #+8]
//  247     uint32_t phases = size / FLASH_PHASE_SEZE;
        MOVS     R0,R5
        LSRS     R0,R0,#+3
        STR      R0,[SP, #+0]
//  248     uint8_t  r = size % FLASH_PHASE_SEZE;
        MOVS     R0,R5
        MOVS     R1,#+8
        BL       __aeabi_uidivmod
          CFI FunCall __aeabi_uidivmod
        MOVS     R6,R1
//  249     
//  250     // check the size of memory
//  251     if((size > sizeof(programbuffer)) || (size == 0))
        LDR      R0,??DataTable10_1  ;; 0x801
        CMP      R5,R0
        BCS      ??FLASH_ProgramSection_0
        CMP      R5,#+0
        BNE      ??FLASH_ProgramSection_1
//  252         return FLASH_FAIL;
??FLASH_ProgramSection_0:
        MOVS     R0,#+1
        B        ??FLASH_ProgramSection_2
//  253     
//  254     if(destination & 0x00000003)
??FLASH_ProgramSection_1:
        LDR      R0,[SP, #+4]
        LSLS     R0,R0,#+30       ;; ZeroExtS R0,R0,#+30,#+30
        LSRS     R0,R0,#+30
        CMP      R0,#+0
        BEQ      ??FLASH_ProgramSection_3
//  255         return FLASH_FAIL;
        MOVS     R0,#+1
        B        ??FLASH_ProgramSection_2
//  256     
//  257     if (r > 0)
??FLASH_ProgramSection_3:
        UXTB     R6,R6
        CMP      R6,#+0
        BEQ      ??FLASH_ProgramSection_4
//  258     {
//  259         phases++;
        LDR      R0,[SP, #+0]
        ADDS     R0,R0,#+1
        STR      R0,[SP, #+0]
//  260         r = FLASH_PHASE_SEZE - r;
        MOVS     R0,#+8
        SUBS     R6,R0,R6
//  261     }
//  262     
//  263     /* preparing passing parameter to program the flash block */
//  264     CommandObj.regsLong.fccob3210 = destination;
??FLASH_ProgramSection_4:
        LDR      R0,[SP, #+4]
        LDR      R1,??DataTable10
        STR      R0,[R1, #+0]
//  265     CommandObj.regs.fccob0 = FLASH_PROGRAM_SECTION;
        MOVS     R0,#+11
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+3]
//  266     CommandObj.regs.fccob4 = (uint8_t)(phases >> 8);
        LDR      R0,[SP, #+0]
        LSRS     R0,R0,#+8
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+7]
//  267     CommandObj.regs.fccob5 = (uint8_t)(phases & 0xff);
        LDR      R0,[SP, #+0]
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+6]
//  268     
//  269     //  copy source data to program buffer
//  270     while(size--)
??FLASH_ProgramSection_5:
        MOVS     R0,R5
        SUBS     R5,R0,#+1
        CMP      R0,#+0
        BEQ      ??FLASH_ProgramSection_6
//  271         *pProgBuff++ = *pSrc++;
        LDRB     R0,[R7, #+0]
        STRB     R0,[R4, #+0]
        ADDS     R7,R7,#+1
        ADDS     R4,R4,#+1
        B        ??FLASH_ProgramSection_5
//  272     
//  273     while(r--)
??FLASH_ProgramSection_6:
        MOVS     R0,R6
        SUBS     R6,R0,#+1
        UXTB     R0,R0
        CMP      R0,#+0
        BEQ      ??FLASH_ProgramSection_7
//  274         *pProgBuff++ = 0xFF;
        MOVS     R0,#+255
        STRB     R0,[R4, #+0]
        ADDS     R4,R4,#+1
        B        ??FLASH_ProgramSection_6
//  275     
//  276     //  call flash sequence
//  277     return FLASH_FlashCommandSequence(PROGRAM_SECTION_INDEX);
??FLASH_ProgramSection_7:
        MOVS     R0,#+7
        BL       FLASH_FlashCommandSequence
??FLASH_ProgramSection_2:
          CFI FunCall FLASH_FlashCommandSequence
        POP      {R1-R7,PC}       ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
          CFI EndBlock cfiBlock4
        REQUIRE programbuffer
//  278 }
//  279 
//  280 
//  281 /********************************************************
//  282 * Function for Programming of one section (maximum is 2048 Bytes)
//  283 *
//  284 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function FLASH_ProgramSectionPhrases
        THUMB
//  285 uint8_t FLASH_ProgramSectionPhrases(uint32_t destination, uint32_t* pSource, uint32_t size)
//  286 {
FLASH_ProgramSectionPhrases:
        PUSH     {R1,R4-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        SUB      SP,SP,#+8
          CFI CFA R13+32
        MOVS     R7,R0
        MOVS     R5,R2
//  287     uint8_t* pProgBuff = (uint8_t*)&programbuffer[0];
        MOVS     R4,#+160
        LSLS     R4,R4,#+21       ;; #+335544320
//  288     uint8_t* pSrc = (uint8_t*)pSource;
        LDR      R0,[SP, #+8]
        STR      R0,[SP, #+4]
//  289     uint32_t phases = size / FLASH_PHASE_SEZE;
        MOVS     R0,R5
        LSRS     R0,R0,#+3
        STR      R0,[SP, #+0]
//  290     uint8_t r = size % FLASH_PHASE_SEZE;
        MOVS     R0,R5
        MOVS     R1,#+8
        BL       __aeabi_uidivmod
          CFI FunCall __aeabi_uidivmod
        MOVS     R6,R1
//  291     
//  292     // check the size of memory
//  293     if(size >= sizeof(programbuffer) || (size == 0))
        MOVS     R0,#+128
        LSLS     R0,R0,#+4        ;; #+2048
        CMP      R5,R0
        BCS      ??FLASH_ProgramSectionPhrases_0
        CMP      R5,#+0
        BNE      ??FLASH_ProgramSectionPhrases_1
//  294         return FLASH_FAIL;
??FLASH_ProgramSectionPhrases_0:
        MOVS     R0,#+1
        B        ??FLASH_ProgramSectionPhrases_2
//  295     
//  296     if(destination & 0x00000003)
??FLASH_ProgramSectionPhrases_1:
        LSLS     R0,R7,#+30       ;; ZeroExtS R0,R7,#+30,#+30
        LSRS     R0,R0,#+30
        CMP      R0,#+0
        BEQ      ??FLASH_ProgramSectionPhrases_3
//  297     {
//  298         if(size & 0x00000001)
        LSLS     R0,R5,#+31
        BPL      ??FLASH_ProgramSectionPhrases_3
//  299             if(!FLASH_ProgramLongWord(destination, *pSource))
        LDR      R0,[SP, #+8]
        LDR      R1,[R0, #+0]
        MOVS     R0,R7
        BL       FLASH_ProgramLongWord
          CFI FunCall FLASH_ProgramLongWord
        CMP      R0,#+0
        BNE      ??FLASH_ProgramSectionPhrases_3
//  300                 return FLASH_FAIL;
        MOVS     R0,#+1
        B        ??FLASH_ProgramSectionPhrases_2
//  301     }
//  302     
//  303     if(destination & 0x00000004)
??FLASH_ProgramSectionPhrases_3:
        LSLS     R0,R7,#+29
        BPL      ??FLASH_ProgramSectionPhrases_4
//  304     {
//  305         if(!FLASH_ProgramLongWord(destination, *pSource++))
        LDR      R0,[SP, #+8]
        LDR      R1,[R0, #+0]
        MOVS     R0,R7
        BL       FLASH_ProgramLongWord
          CFI FunCall FLASH_ProgramLongWord
        LDR      R1,[SP, #+8]
        ADDS     R1,R1,#+4
        STR      R1,[SP, #+8]
        UXTB     R0,R0
        CMP      R0,#+0
        BNE      ??FLASH_ProgramSectionPhrases_5
//  306             return FLASH_FAIL;
        MOVS     R0,#+1
        B        ??FLASH_ProgramSectionPhrases_2
//  307         size-=4;
??FLASH_ProgramSectionPhrases_5:
        SUBS     R5,R5,#+4
//  308         destination += 4;
        ADDS     R7,R7,#+4
//  309     }
//  310     
//  311     if (r)
??FLASH_ProgramSectionPhrases_4:
        UXTB     R6,R6
        CMP      R6,#+0
        BEQ      ??FLASH_ProgramSectionPhrases_6
//  312     {
//  313         phases++;
        LDR      R0,[SP, #+0]
        ADDS     R0,R0,#+1
        STR      R0,[SP, #+0]
//  314         r = FLASH_PHASE_SEZE - r;
        MOVS     R0,#+8
        SUBS     R6,R0,R6
//  315     }
//  316     
//  317     /* preparing passing parameter to program the flash block */
//  318     CommandObj.regsLong.fccob3210 = destination;
??FLASH_ProgramSectionPhrases_6:
        LDR      R0,??DataTable10
        STR      R7,[R0, #+0]
//  319     CommandObj.regs.fccob0 = FLASH_PROGRAM_SECTION;
        MOVS     R0,#+11
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+3]
//  320     CommandObj.regs.fccob4 = (uint8_t)(phases >> 8);
        LDR      R0,[SP, #+0]
        LSRS     R0,R0,#+8
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+7]
//  321     CommandObj.regs.fccob5 = (uint8_t)(phases & 0xff);
        LDR      R0,[SP, #+0]
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+6]
//  322     
//  323     //  copy source data to program buffer
//  324     while(size--)
??FLASH_ProgramSectionPhrases_7:
        MOVS     R0,R5
        SUBS     R5,R0,#+1
        CMP      R0,#+0
        BEQ      ??FLASH_ProgramSectionPhrases_8
//  325         *pProgBuff++ = *pSrc++;
        LDR      R0,[SP, #+4]
        LDRB     R0,[R0, #+0]
        STRB     R0,[R4, #+0]
        LDR      R0,[SP, #+4]
        ADDS     R0,R0,#+1
        STR      R0,[SP, #+4]
        ADDS     R4,R4,#+1
        B        ??FLASH_ProgramSectionPhrases_7
//  326     
//  327     while(r--)
??FLASH_ProgramSectionPhrases_8:
        MOVS     R0,R6
        SUBS     R6,R0,#+1
        UXTB     R0,R0
        CMP      R0,#+0
        BEQ      ??FLASH_ProgramSectionPhrases_9
//  328         *pProgBuff++ = 0xFF;
        MOVS     R0,#+255
        STRB     R0,[R4, #+0]
        ADDS     R4,R4,#+1
        B        ??FLASH_ProgramSectionPhrases_8
//  329     
//  330     //  call flash sequence
//  331     return FLASH_FlashCommandSequence(PROGRAM_SECTION_INDEX);
??FLASH_ProgramSectionPhrases_9:
        MOVS     R0,#+7
        BL       FLASH_FlashCommandSequence
??FLASH_ProgramSectionPhrases_2:
          CFI FunCall FLASH_FlashCommandSequence
        POP      {R1-R7,PC}       ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
          CFI EndBlock cfiBlock5
        REQUIRE programbuffer
//  332 }
//  333 
//  334 /********************************************************
//  335 *
//  336 *
//  337 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function FLASH_ProgramByte
        THUMB
//  338 uint8_t FLASH_ProgramByte(uint32_t destination, uint8_t data8b)
//  339 {
FLASH_ProgramByte:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R5,R0
        MOVS     R4,R1
//  340     CommandObj.regsLong.fccob3210 = destination;
        LDR      R0,??DataTable10
        STR      R5,[R0, #+0]
//  341     CommandObj.regs.fccob0 = FLASH_PROGRAM_BYTE;
        MOVS     R0,#+4
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+3]
//  342     CommandObj.regs.fccob4 = data8b;
        LDR      R0,??DataTable10
        STRB     R4,[R0, #+7]
//  343     
//  344     return FLASH_FlashCommandSequence(PROGRAM_BYTE_INDEX);
        MOVS     R0,#+5
        BL       FLASH_FlashCommandSequence
          CFI FunCall FLASH_FlashCommandSequence
        POP      {R1,R4,R5,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
//  345 }
          CFI EndBlock cfiBlock6

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable5:
        DC32     ExecuteOnStackStart+0xFFFFFFFF
//  346 
//  347 /********************************************************
//  348 * Function for erasing of flash memory sector (0x800)
//  349 *
//  350 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function FLASH_EraseSector
        THUMB
//  351 uint8_t FLASH_EraseSector(uint32_t destination)
//  352 {
FLASH_EraseSector:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  353     CommandObj.regsLong.fccob3210 = destination;
        LDR      R0,??DataTable10
        STR      R4,[R0, #+0]
//  354     CommandObj.regs.fccob0 = FLASH_ERASE_SECTOR;
        MOVS     R0,#+9
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+3]
//  355     
//  356     return FLASH_FlashCommandSequence(ERASE_BLOCK_INDEX);
        MOVS     R0,#+4
        BL       FLASH_FlashCommandSequence
          CFI FunCall FLASH_FlashCommandSequence
        POP      {R4,PC}          ;; return
          CFI R4 SameValue
          CFI CFA R13+0
//  357 }
          CFI EndBlock cfiBlock7
//  358 
//  359 
//  360 /********************************************************
//  361 * Function for erasing of all block of memory
//  362 *
//  363 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function FLASH_MassErase
        THUMB
//  364 uint8_t FLASH_MassErase(void)
//  365 {
FLASH_MassErase:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  366     CommandObj.regs.fccob0 = FLASH_ERASE_ALL_BLOCK;
        MOVS     R0,#+68
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+3]
//  367     return FLASH_FlashCommandSequence(ERASE_MASS_INDEX);
        MOVS     R0,#+4
        BL       FLASH_FlashCommandSequence
          CFI FunCall FLASH_FlashCommandSequence
        POP      {R1,PC}          ;; return
          CFI CFA R13+0
//  368 }
          CFI EndBlock cfiBlock8

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7:
        DC32     buffer

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_1:
        DC32     ExecuteOnStack

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_2:
        DC32     ExecuteOnStackStart
//  369 
//  370 /********************************************************
//  371 * Function for enabling the EERAM
//  372 *
//  373 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function FLASH_SetEEEEnable
        THUMB
//  374 uint8_t FLASH_SetEEEEnable(uint8_t ctrl_code)
//  375 {
FLASH_SetEEEEnable:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  376     CommandObj.regs.fccob0 = FLASH_SET_EERAM;
        MOVS     R0,#+129
        LDR      R1,??DataTable10
        STRB     R0,[R1, #+3]
//  377     CommandObj.regs.fccob1 = ctrl_code;
        LDR      R0,??DataTable10
        STRB     R4,[R0, #+2]
//  378     return FLASH_FlashCommandSequence(SET_EERAM_INDEX);
        MOVS     R0,#+4
        BL       FLASH_FlashCommandSequence
          CFI FunCall FLASH_FlashCommandSequence
        POP      {R4,PC}          ;; return
          CFI R4 SameValue
          CFI CFA R13+0
//  379 }
          CFI EndBlock cfiBlock9

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8:
        DC32     0x4004803c
//  380 
//  381 
//  382 /*! *********************************************************************************
//  383 *************************************************************************************
//  384 * Private Functions
//  385 *************************************************************************************
//  386 ********************************************************************************** */
//  387 
//  388 /********************************************************
//  389 * Function for executing of the flash command
//  390 *
//  391 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function FLASH_FlashCommandSequence
        THUMB
//  392 static uint8_t FLASH_FlashCommandSequence(uint8_t index)
//  393 {
FLASH_FlashCommandSequence:
        PUSH     {R4-R6,LR}
          CFI R14 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+16
        MOVS     R6,R0
//  394     uint8_t* ptrFccobReg = (uint8_t*)&FLASH_BASE_PTR->FCCOB3;
        LDR      R4,??DataTable10_2  ;; 0x40020004
//  395     uint8_t* ptrCommandObj = (uint8_t*)&CommandObj;
        LDR      R5,??DataTable10
//  396     
//  397     
//  398     /* wait till CCIF bit is set */
//  399     while((FLASH_FSTAT&FLASH_FSTAT_CCIF_MASK) != FLASH_FSTAT_CCIF_MASK){};
??FLASH_FlashCommandSequence_0:
        LDR      R0,??DataTable10_3  ;; 0x40020000
        LDRB     R0,[R0, #+0]
        UXTB     R0,R0
        LSLS     R0,R0,#+24
        BPL      ??FLASH_FlashCommandSequence_0
//  400     
//  401     /* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
//  402     FLASH_FSTAT = FLASH_FSTAT_ACCERR_MASK|FLASH_FSTAT_FPVIOL_MASK|FLASH_FSTAT_RDCOLERR_MASK;
        MOVS     R0,#+112
        LDR      R1,??DataTable10_3  ;; 0x40020000
        STRB     R0,[R1, #+0]
//  403     
//  404     /* load FCCOB registers */
//  405     while(index--)
??FLASH_FlashCommandSequence_1:
        MOVS     R0,R6
        SUBS     R6,R0,#+1
        UXTB     R0,R0
        CMP      R0,#+0
        BEQ      ??FLASH_FlashCommandSequence_2
//  406         *ptrFccobReg++ = *ptrCommandObj++;
        LDRB     R0,[R5, #+0]
        STRB     R0,[R4, #+0]
        ADDS     R5,R5,#+1
        ADDS     R4,R4,#+1
        B        ??FLASH_FlashCommandSequence_1
//  407     
//  408     //  jump to RAM function
//  409     ExecuteOnStack();
??FLASH_FlashCommandSequence_2:
        LDR      R0,??DataTable10_4
        LDR      R0,[R0, #+0]
        BLX      R0
//  410     
//  411     /* Check error bits */
//  412     /* Get flash status register value */
//  413     if(FLASH_FSTAT & (FLASH_FSTAT_ACCERR_MASK|FLASH_FSTAT_FPVIOL_MASK|FLASH_FSTAT_MGSTAT0_MASK))
          CFI FunCall
        LDR      R0,??DataTable10_3  ;; 0x40020000
        LDRB     R0,[R0, #+0]
        MOVS     R1,#+49
        TST      R0,R1
        BEQ      ??FLASH_FlashCommandSequence_3
//  414         return FLASH_FAIL;
        MOVS     R0,#+1
        B        ??FLASH_FlashCommandSequence_4
//  415     
//  416     return FLASH_OK;
??FLASH_FlashCommandSequence_3:
        MOVS     R0,#+0
??FLASH_FlashCommandSequence_4:
        POP      {R4-R6,PC}       ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI CFA R13+0
//  417 }
          CFI EndBlock cfiBlock10
//  418 
//  419 /********************************************************
//  420 * Function for lounching a FLASH command: will run from RAM
//  421 *
//  422 ********************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function ExecuteOnStackStart
          CFI NoCalls
        THUMB
//  423 static void ExecuteOnStackStart(void)
//  424 {
ExecuteOnStackStart:
        PUSH     {LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+4
//  425     //  launch a command
//  426     FLASH_FSTAT |= FLASH_FSTAT_CCIF_MASK;
        LDR      R0,??DataTable10_3  ;; 0x40020000
        LDRB     R0,[R0, #+0]
        MOVS     R1,#+128
        ORRS     R1,R1,R0
        LDR      R0,??DataTable10_3  ;; 0x40020000
        STRB     R1,[R0, #+0]
//  427     
//  428     //  waiting for the finishing of the command
//  429     while((FLASH_FSTAT&FLASH_FSTAT_CCIF_MASK) != FLASH_FSTAT_CCIF_MASK){};
??ExecuteOnStackStart_0:
        LDR      R0,??DataTable10_3  ;; 0x40020000
        LDRB     R0,[R0, #+0]
        UXTB     R0,R0
        LSLS     R0,R0,#+24
        BPL      ??ExecuteOnStackStart_0
//  430 }
        POP      {PC}             ;; return
          CFI CFA R13+0
          CFI EndBlock cfiBlock11

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10:
        DC32     CommandObj

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_1:
        DC32     0x801

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_2:
        DC32     0x40020004

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_3:
        DC32     0x40020000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable10_4:
        DC32     ExecuteOnStack

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
//   156 bytes in section .bss
// 2 048 bytes in section .noinit (abs)
//   922 bytes in section .text
// 
// 922 bytes of CODE memory
// 156 bytes of DATA memory (+ 2 048 bytes shared)
//
//Errors: none
//Warnings: none
