///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       12/Jan/2016  08:59:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\Eeprom_Boot_M25P80.c
//    Command line =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\Eeprom_Boot_M25P80.c
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
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\Eeprom_Boot_M25P80.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__SystemLibrary", "DLib"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        EXTERN __aeabi_uidivmod
        EXTERN spi_master_configure_bus
        EXTERN spi_master_init
        EXTERN spi_master_transfer

        PUBLIC EEPROM_ChipErase
        PUBLIC EEPROM_EraseBlock
        PUBLIC EEPROM_Init
        PUBLIC EEPROM_ReadData
        PUBLIC EEPROM_ReadStatus
        PUBLIC EEPROM_WriteData
        PUBLIC EEPROM_isBusy
        
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
        
// C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\Eeprom_Boot_M25P80.c
//    1 /*!
//    2 * Copyright (c) 2015, Freescale Semiconductor, Inc.
//    3 * All rights reserved.
//    4 *
//    5 * \file EEPROM_InternalFlash.c
//    6 * This is the Source file for the EEPROM emulated inside the MCU's FLASH
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
//   34 #include "Eeprom_Boot.h"
//   35 
//   36 #if gEepromType_d == gEepromDevice_M25P80_c
//   37 
//   38 #include "SPI.h"
//   39 
//   40 

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
//   41 static uint8_t currentStatus;
currentStatus:
        DS8 1
//   42 
//   43 /**
//   44  * macros
//   45  */
//   46 
//   47 #define EEPROM_IsWriteInProgress()    ( 0 != ( ( currentStatus & EEPROM_BIT_WIP_MASK ) >> EEPROM_BIT_WIP_SHIFT ) )
//   48 #define EEPROM_IsWriteNotInProgress() ( 0 == ( ( currentStatus & EEPROM_BIT_WIP_MASK ) >> EEPROM_BIT_WIP_SHIFT ) )
//   49 #define EEPROM_IsWriteEnabled()       ( 0 != ( ( currentStatus & EEPROM_BIT_WEL_MASK ) >> EEPROM_BIT_WEL_SHIFT ) )
//   50 #define EEPROM_IsWriteNotEnabled()    ( 0 == ( ( currentStatus & EEPROM_BIT_WEL_MASK ) >> EEPROM_BIT_WEL_SHIFT ) )
//   51 
//   52 
//   53 /*! *********************************************************************************
//   54 *************************************************************************************
//   55 * Private macros
//   56 *************************************************************************************
//   57 ********************************************************************************** */
//   58 #define  gEepromWriteEnable_d   1
//   59 
//   60 /**
//   61  * designate the end of the command
//   62  */
//   63 #define EEPROM_CMD_CNT (0) // continue
//   64 #define EEPROM_CMD_END (1) // end with this command
//   65 
//   66 // WRITE ENABLE command must be executed before PROGRAM, ERASE, and WRITE command
//   67 #define EEPROM_CMD_WRITE_ENABLE  ( 0x06 )
//   68 #define EEPROM_CMD_WRITE_DISABLE ( 0x04 )
//   69 #define EEPROM_CMD_WRITE_STATUS  ( 0x01 )
//   70 
//   71 #define EEPROM_CMD_READ_IDENTIFICATION ( 0x9F )
//   72 #define EEPROM_CMD_READ_STATUS         ( 0x05 )
//   73 #define EEPROM_CMD_READ_DATA_BYTES     ( 0x03 )
//   74 #define EEPROM_CMD_READ_DATA_BYTES_HS  ( 0x0B )
//   75 
//   76 #define EEPROM_CMD_PROGRAM_PAGE ( 0x02  )
//   77 #define EEPROM_PAGE_SIZE        (256)
//   78 #define EEPROM_PAGE_MASK        (EEPROM_PAGE_SIZE - 1)
//   79 #define EEPROM_SECTOR_SIZE      (EEPROM_PAGE_SIZE * 256)
//   80 
//   81 #define EEPROM_CMD_ERASE_SECTOR ( 0xD8 )
//   82 #define EEPROM_CMD_ERASE_BULK   ( 0xC7 )
//   83 
//   84 #define EEPROM_CMD_DEEP_PWR_DOWN     ( 0xB9 )
//   85 #define EEPROM_CMD_DEEP_PWR_DOWN_RLS ( 0xAB )
//   86 
//   87 /**
//   88  * EEPROM bits
//   89  */
//   90 
//   91 #define EEPROM_BIT_WIP_SHIFT ( 0 )
//   92 #define EEPROM_BIT_WEL_SHIFT ( 1 )
//   93 
//   94 #define EEPROM_BIT_WIP_MASK  ( 1 << EEPROM_BIT_WIP_SHIFT )
//   95 #define EEPROM_BIT_WEL_MASK  ( 1 << EEPROM_BIT_WEL_SHIFT )
//   96 
//   97 
//   98 /* SPI config */
//   99 #define gEepromSpiInstance_c  1
//  100 #define gEepromSpiCsPin_d     GPIO_MAKE_PIN(GPIOA_IDX, 19)
//  101 
//  102 #define gEepromAssertCS_d()   assert_cs()
//  103 #define gEepromDeassertCS_d() deassert_cs()
//  104 
//  105 /****************************** SPI MACROS ***********************************/
//  106 #define mEepromSpiInstance_c 1
//  107 
//  108 /******************************************************************************
//  109 *******************************************************************************
//  110 * Private Prototypes
//  111 *******************************************************************************
//  112 ******************************************************************************/
//  113 static ee_err_t EEPROM_SendCmd(const uint8_t cmdToSend, uint8_t  endFlag);
//  114 static ee_err_t EEPROM_GetWriteReady();
//  115 static ee_err_t EEPROM_SendAddress(uint32_t eepromAddress);
//  116 static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf);
//  117 static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr);
//  118 
//  119 
//  120 /*! *********************************************************************************
//  121 *************************************************************************************
//  122 * Private Memory Declarations
//  123 *************************************************************************************
//  124 ********************************************************************************** */
//  125 
//  126 #if gEepromWriteEnable_d

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//  127 static uint8_t mEepromEraseBitmap[64];
mEepromEraseBitmap:
        DS8 64
//  128 #endif
//  129 
//  130 
//  131 /*! *********************************************************************************
//  132 *************************************************************************************
//  133 * Public Functions
//  134 *************************************************************************************
//  135 ********************************************************************************** */
//  136 
//  137 /*****************************************************************************
//  138 *  EEPROM_Init
//  139 *
//  140 *  Initializes the EEPROM peripheral
//  141 *
//  142 *****************************************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function EEPROM_Init
        THUMB
//  143 ee_err_t EEPROM_Init(void)
//  144 {   
EEPROM_Init:
        PUSH     {R2-R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+16
//  145     spi_user_config_t config;
//  146     
//  147 #if gEepromWriteEnable_d
//  148     uint32_t i;
//  149 
//  150     // Mark Flash as Unerased
//  151     for(i = 0; i < 64; i++)
        MOVS     R0,#+0
        MOVS     R4,R0
??EEPROM_Init_0:
        CMP      R4,#+64
        BCS      ??EEPROM_Init_1
//  152         mEepromEraseBitmap[i] = 0;
        MOVS     R0,#+0
        LDR      R1,??DataTable6
        STRB     R0,[R1, R4]
        ADDS     R4,R4,#+1
        B        ??EEPROM_Init_0
//  153 #endif
//  154 
//  155     config.busFrequencyKHz = 8000;
??EEPROM_Init_1:
        MOVS     R0,#+250
        LSLS     R0,R0,#+5        ;; #+8000
        STR      R0,[SP, #+0]
//  156     config.direction = kSpiMsbFirst;
        MOVS     R0,#+0
        MOV      R1,SP
        STRB     R0,[R1, #+6]
//  157     config.phase = kSpiClockPhase_FirstEdge;
        MOVS     R0,#+0
        MOV      R1,SP
        STRB     R0,[R1, #+5]
//  158     config.polarity = kSpiClockPolarity_ActiveHigh;
        MOVS     R0,#+0
        MOV      R1,SP
        STRB     R0,[R1, #+4]
//  159     
//  160     spi_master_init(mEepromSpiInstance_c);
        MOVS     R0,#+1
        BL       spi_master_init
//  161     spi_master_configure_bus(mEepromSpiInstance_c, &config);
          CFI FunCall spi_master_init
        MOV      R1,SP
        MOVS     R0,#+1
        BL       spi_master_configure_bus
//  162     
//  163     gEepromDeassertCS_d(); 
          CFI FunCall spi_master_configure_bus
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        LDR      R0,[R0, #+0]
        MOVS     R1,#+128
        LSLS     R1,R1,#+12       ;; #+524288
        ORRS     R1,R1,R0
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        STR      R1,[R0, #+0]
//  164     
//  165     return ee_ok;
        MOVS     R0,#+0
        POP      {R1,R2,R4,PC}    ;; return
          CFI R4 SameValue
          CFI CFA R13+0
//  166 }
          CFI EndBlock cfiBlock0
//  167 
//  168 /*****************************************************************************
//  169 *  EEPROM_ChipErase
//  170 *
//  171 *  Erase all memory to 0xFF
//  172 *
//  173 *****************************************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function EEPROM_ChipErase
        THUMB
//  174 ee_err_t EEPROM_ChipErase(void)
//  175 {
EEPROM_ChipErase:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//  176     // make sure the write process is ready
//  177     while(EEPROM_GetWriteReady() != ee_ok);
??EEPROM_ChipErase_0:
        BL       EEPROM_GetWriteReady
          CFI FunCall EEPROM_GetWriteReady
        CMP      R0,#+0
        BNE      ??EEPROM_ChipErase_0
//  178     
//  179     return EEPROM_SendCmd(EEPROM_CMD_ERASE_BULK, EEPROM_CMD_END);
        MOVS     R1,#+1
        MOVS     R0,#+199
        BL       EEPROM_SendCmd
          CFI FunCall EEPROM_SendCmd
        POP      {R1,PC}          ;; return
          CFI CFA R13+0
//  180 }
          CFI EndBlock cfiBlock1
//  181 
//  182 /*****************************************************************************
//  183 *  EEPROM_EraseBlock
//  184 *
//  185 *  Erase a block of memory to 0xFF
//  186 *
//  187 *****************************************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function EEPROM_EraseBlock
        THUMB
//  188 ee_err_t EEPROM_EraseBlock(uint32_t Addr, uint32_t size)
//  189 {
EEPROM_EraseBlock:
        PUSH     {R4-R6,LR}
          CFI R14 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+16
        MOVS     R6,R0
        MOVS     R4,R1
//  190     ee_err_t status = ee_ok;
        MOVS     R5,#+0
//  191     
//  192     if(size != EEPROM_SECTOR_SIZE)
        MOVS     R0,#+128
        LSLS     R0,R0,#+9        ;; #+65536
        CMP      R4,R0
        BEQ      ??EEPROM_EraseBlock_0
//  193     {
//  194         return ee_error;
        MOVS     R0,#+4
        B        ??EEPROM_EraseBlock_1
//  195     }
//  196     
//  197     // make sure the write process is ready
//  198     while(EEPROM_GetWriteReady() != ee_ok);
??EEPROM_EraseBlock_0:
        BL       EEPROM_GetWriteReady
          CFI FunCall EEPROM_GetWriteReady
        CMP      R0,#+0
        BNE      ??EEPROM_EraseBlock_0
//  199     
//  200     // send the command
//  201     status |= EEPROM_SendCmd( EEPROM_CMD_ERASE_SECTOR, EEPROM_CMD_CNT );
        MOVS     R1,#+0
        MOVS     R0,#+216
        BL       EEPROM_SendCmd
          CFI FunCall EEPROM_SendCmd
        ORRS     R0,R0,R5
        MOVS     R5,R0
//  202     
//  203     // send the address
//  204     status |= EEPROM_SendAddress(Addr);
        MOVS     R0,R6
        BL       EEPROM_SendAddress
          CFI FunCall EEPROM_SendAddress
        ORRS     R0,R0,R5
        MOVS     R5,R0
//  205 
//  206     if (status == ee_ok)
        UXTB     R5,R5
        CMP      R5,#+0
        BNE      ??EEPROM_EraseBlock_2
//  207     {
//  208         gEepromDeassertCS_d();
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        LDR      R0,[R0, #+0]
        MOVS     R1,#+128
        LSLS     R1,R1,#+12       ;; #+524288
        ORRS     R1,R1,R0
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        STR      R1,[R0, #+0]
//  209         return ee_ok;
        MOVS     R0,#+0
        B        ??EEPROM_EraseBlock_1
//  210     }
//  211     else
//  212     {
//  213         return ee_error;
??EEPROM_EraseBlock_2:
        MOVS     R0,#+4
??EEPROM_EraseBlock_1:
        POP      {R4-R6,PC}       ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI CFA R13+0
//  214     }
//  215 }
          CFI EndBlock cfiBlock2
//  216 
//  217 /*****************************************************************************
//  218 *  EEPROM_WriteData
//  219 *
//  220 *  Writes a data buffer into EEPROM, at a given address
//  221 *
//  222 *****************************************************************************/
//  223 #if gEepromWriteEnable_d

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function EEPROM_WriteData
        THUMB
//  224 ee_err_t EEPROM_WriteData(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
//  225 {
EEPROM_WriteData:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//  226     ee_err_t status = ee_ok;
        MOVS     R7,#+0
//  227     
//  228     if (NoOfBytes == 0)
        CMP      R4,#+0
        BNE      ??EEPROM_WriteData_0
//  229     {
//  230         return status;
        MOVS     R0,R7
        UXTB     R0,R0
        B        ??EEPROM_WriteData_1
//  231     }
//  232     
//  233     // make sure the write process is ready
//  234     while(EEPROM_GetWriteReady() != ee_ok);
??EEPROM_WriteData_0:
        BL       EEPROM_GetWriteReady
          CFI FunCall EEPROM_GetWriteReady
        CMP      R0,#+0
        BNE      ??EEPROM_WriteData_0
//  235     
//  236     status = EEPROM_PrepareForWrite(NoOfBytes, Addr);
        MOVS     R1,R5
        MOVS     R0,R4
        BL       EEPROM_PrepareForWrite
          CFI FunCall EEPROM_PrepareForWrite
        MOVS     R7,R0
//  237     if (status != ee_ok)
        UXTB     R7,R7
        CMP      R7,#+0
        BEQ      ??EEPROM_WriteData_2
//  238     {
//  239         return status;
        MOVS     R0,R7
        UXTB     R0,R0
        B        ??EEPROM_WriteData_1
//  240     }
//  241     
//  242     while ((Addr & EEPROM_PAGE_MASK) + NoOfBytes > EEPROM_PAGE_MASK)
??EEPROM_WriteData_2:
        UXTB     R0,R5
        ADDS     R0,R0,R4
        CMP      R0,#+255
        BLS      ??EEPROM_WriteData_3
//  243     {
//  244         uint32_t bytes = EEPROM_PAGE_SIZE - (Addr & EEPROM_PAGE_MASK);
        MOVS     R0,#+128
        LSLS     R0,R0,#+1        ;; #+256
        UXTB     R1,R5
        SUBS     R0,R0,R1
        STR      R0,[SP, #+0]
//  245         
//  246         status = EEPROM_WritePage(bytes, Addr, Outbuf);
        MOVS     R2,R6
        MOVS     R1,R5
        LDR      R0,[SP, #+0]
        BL       EEPROM_WritePage
          CFI FunCall EEPROM_WritePage
        MOVS     R7,R0
//  247         NoOfBytes -= bytes;
        LDR      R0,[SP, #+0]
        SUBS     R4,R4,R0
//  248         Addr += bytes;
        LDR      R0,[SP, #+0]
        ADDS     R5,R5,R0
//  249         Outbuf += bytes;
        LDR      R0,[SP, #+0]
        ADDS     R6,R6,R0
//  250         
//  251         if (status != ee_ok)
        UXTB     R7,R7
        CMP      R7,#+0
        BEQ      ??EEPROM_WriteData_2
//  252             return status;
        MOVS     R0,R7
        UXTB     R0,R0
        B        ??EEPROM_WriteData_1
//  253     }
//  254     
//  255     status = EEPROM_WritePage(NoOfBytes, Addr, Outbuf);
??EEPROM_WriteData_3:
        MOVS     R2,R6
        MOVS     R1,R5
        MOVS     R0,R4
        BL       EEPROM_WritePage
          CFI FunCall EEPROM_WritePage
        MOVS     R7,R0
//  256     
//  257     return status;
        MOVS     R0,R7
        UXTB     R0,R0
??EEPROM_WriteData_1:
        POP      {R1,R4-R7,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
//  258 }
          CFI EndBlock cfiBlock3
//  259 #endif
//  260 
//  261 /*****************************************************************************
//  262 *  EEPROM_WriteData
//  263 *
//  264 *  Writes a data buffer into the External Memory, at a given address
//  265 *
//  266 *****************************************************************************/
//  267 #if gEepromWriteEnable_d

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function EEPROM_PrepareForWrite
        THUMB
//  268 static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr)
//  269 {
EEPROM_PrepareForWrite:
        PUSH     {R4-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+20
        SUB      SP,SP,#+20
          CFI CFA R13+40
        MOVS     R7,R0
        MOVS     R6,R1
//  270     uint32_t i;
//  271     ee_err_t ret = ee_ok;
        MOVS     R5,#+0
//  272     uint32_t startBlk, endBlk;
//  273     
//  274     // Obtain the block number
//  275     startBlk = Addr / EEPROM_SECTOR_SIZE;
        MOVS     R0,R6
        LSRS     R0,R0,#+16
        STR      R0,[SP, #+12]
//  276     endBlk   = (Addr + NoOfBytes) / EEPROM_SECTOR_SIZE + 1;
        ADDS     R0,R6,R7
        LSRS     R0,R0,#+16
        ADDS     R0,R0,#+1
        STR      R0,[SP, #+8]
//  277     
//  278     for(i = startBlk; i <= endBlk; i++)
        LDR      R0,[SP, #+12]
        MOVS     R4,R0
??EEPROM_PrepareForWrite_0:
        LDR      R0,[SP, #+8]
        CMP      R0,R4
        BCC      ??EEPROM_PrepareForWrite_1
//  279     {
//  280         if ( (mEepromEraseBitmap[i/8] & (1 << (i%8) ) ) == 0)
        LDR      R0,??DataTable6
        MOVS     R1,R4
        LSRS     R1,R1,#+3
        LDRB     R1,[R0, R1]
        STR      R1,[SP, #+4]
        MOVS     R0,#+1
        STR      R0,[SP, #+0]
        MOVS     R0,R4
        MOVS     R1,#+8
        BL       __aeabi_uidivmod
          CFI FunCall __aeabi_uidivmod
        LDR      R0,[SP, #+0]
        LSLS     R0,R0,R1
        LDR      R1,[SP, #+4]
        TST      R1,R0
        BNE      ??EEPROM_PrepareForWrite_2
//  281         {
//  282             ret = EEPROM_EraseBlock(i * EEPROM_SECTOR_SIZE, EEPROM_SECTOR_SIZE);
        MOVS     R1,#+128
        LSLS     R1,R1,#+9        ;; #+65536
        MOVS     R0,#+128
        LSLS     R0,R0,#+9        ;; #+65536
        MULS     R0,R4,R0
        BL       EEPROM_EraseBlock
          CFI FunCall EEPROM_EraseBlock
        MOVS     R5,R0
//  283             if (ret != ee_ok)
        UXTB     R5,R5
        CMP      R5,#+0
        BEQ      ??EEPROM_PrepareForWrite_3
//  284                 return ret;
        MOVS     R0,R5
        UXTB     R0,R0
        B        ??EEPROM_PrepareForWrite_4
//  285             
//  286             mEepromEraseBitmap[i/8] |= 1 << (i%8);
??EEPROM_PrepareForWrite_3:
        LDR      R0,??DataTable6
        MOVS     R1,R4
        LSRS     R1,R1,#+3
        LDRB     R1,[R0, R1]
        STR      R1,[SP, #+4]
        MOVS     R0,#+1
        STR      R0,[SP, #+0]
        MOVS     R0,R4
        MOVS     R1,#+8
        BL       __aeabi_uidivmod
          CFI FunCall __aeabi_uidivmod
        LDR      R0,[SP, #+0]
        LSLS     R0,R0,R1
        LDR      R1,[SP, #+4]
        ORRS     R0,R0,R1
        LDR      R1,??DataTable6
        MOVS     R2,R4
        LSRS     R2,R2,#+3
        STRB     R0,[R1, R2]
//  287             while (EEPROM_isBusy());
??EEPROM_PrepareForWrite_5:
        BL       EEPROM_isBusy
          CFI FunCall EEPROM_isBusy
        CMP      R0,#+0
        BNE      ??EEPROM_PrepareForWrite_5
//  288         }
//  289     }
??EEPROM_PrepareForWrite_2:
        ADDS     R4,R4,#+1
        B        ??EEPROM_PrepareForWrite_0
//  290 
//  291     return ret;
??EEPROM_PrepareForWrite_1:
        MOVS     R0,R5
        UXTB     R0,R0
??EEPROM_PrepareForWrite_4:
        ADD      SP,SP,#+20
          CFI CFA R13+20
        POP      {R4-R7,PC}       ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
//  292 }
          CFI EndBlock cfiBlock4
//  293 #endif
//  294 
//  295 #if gEepromWriteEnable_d

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function EEPROM_WritePage
        THUMB
//  296 static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
//  297 {
EEPROM_WritePage:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R5,R0
        MOVS     R7,R1
        MOVS     R6,R2
//  298     ee_err_t status = ee_ok;
        MOVS     R4,#+0
//  299     
//  300     if (NoOfBytes == 0)
        CMP      R5,#+0
        BNE      ??EEPROM_WritePage_0
//  301     {
//  302         return ee_ok;
        MOVS     R0,#+0
        B        ??EEPROM_WritePage_1
//  303     }
//  304     
//  305     // make sure the write process is ready
//  306     while(EEPROM_GetWriteReady() != ee_ok);
??EEPROM_WritePage_0:
        BL       EEPROM_GetWriteReady
          CFI FunCall EEPROM_GetWriteReady
        CMP      R0,#+0
        BNE      ??EEPROM_WritePage_0
//  307     
//  308     /**
//  309    * write data
//  310    */
//  311     if (NoOfBytes > EEPROM_PAGE_SIZE)
        MOVS     R0,#+255
        ADDS     R0,R0,#+2        ;; #+257
        CMP      R5,R0
        BCC      ??EEPROM_WritePage_2
//  312     {
//  313         return ee_too_big;
        MOVS     R0,#+1
        B        ??EEPROM_WritePage_1
//  314     }
//  315     
//  316     // send the PAGE_PROGRAM command
//  317     status |= EEPROM_SendCmd(EEPROM_CMD_PROGRAM_PAGE, EEPROM_CMD_CNT );
??EEPROM_WritePage_2:
        MOVS     R1,#+0
        MOVS     R0,#+2
        BL       EEPROM_SendCmd
          CFI FunCall EEPROM_SendCmd
        ORRS     R0,R0,R4
        MOVS     R4,R0
//  318     // send the address
//  319     status |= EEPROM_SendAddress(Addr);
        MOVS     R0,R7
        BL       EEPROM_SendAddress
          CFI FunCall EEPROM_SendAddress
        ORRS     R0,R0,R4
        MOVS     R4,R0
//  320     
//  321     /**
//  322      * send data
//  323      */
//  324     gEepromAssertCS_d();
        LDR      R0,??DataTable8  ;; 0x400ff008
        LDR      R0,[R0, #+0]
        MOVS     R1,#+128
        LSLS     R1,R1,#+12       ;; #+524288
        ORRS     R1,R1,R0
        LDR      R0,??DataTable8  ;; 0x400ff008
        STR      R1,[R0, #+0]
//  325     
//  326     if(spi_master_transfer(mEepromSpiInstance_c, Outbuf, NULL, NoOfBytes) != 0)
        MOVS     R3,R5
        MOVS     R2,#+0
        MOVS     R1,R6
        MOVS     R0,#+1
        BL       spi_master_transfer
          CFI FunCall spi_master_transfer
        CMP      R0,#+0
        BEQ      ??EEPROM_WritePage_3
//  327     {
//  328         status = ee_error;
        MOVS     R0,#+4
        MOVS     R4,R0
//  329     }
//  330     gEepromDeassertCS_d();
??EEPROM_WritePage_3:
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        LDR      R0,[R0, #+0]
        MOVS     R1,#+128
        LSLS     R1,R1,#+12       ;; #+524288
        ORRS     R1,R1,R0
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        STR      R1,[R0, #+0]
//  331     
//  332     if(status == ee_ok) 
        UXTB     R4,R4
        CMP      R4,#+0
        BNE      ??EEPROM_WritePage_4
//  333     {
//  334         return status;
        MOVS     R0,R4
        UXTB     R0,R0
        B        ??EEPROM_WritePage_1
//  335     }
//  336     else
//  337     {
//  338         return ee_error;
??EEPROM_WritePage_4:
        MOVS     R0,#+4
??EEPROM_WritePage_1:
        POP      {R1,R4-R7,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
//  339     }
//  340 }
          CFI EndBlock cfiBlock5
//  341 #endif
//  342 
//  343 /*****************************************************************************
//  344 *  EEPROM_ReadData
//  345 *
//  346 *  Reads a data buffer from EEPROM, from a given address
//  347 *
//  348 *****************************************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function EEPROM_ReadData
        THUMB
//  349 ee_err_t EEPROM_ReadData(uint16_t NoOfBytes, uint32_t Addr, uint8_t *inbuf)
//  350 {
EEPROM_ReadData:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R5,R0
        MOVS     R6,R1
        MOVS     R7,R2
//  351     ee_err_t status = ee_ok;
        MOVS     R4,#+0
//  352     
//  353     // make sure the write process is ready
//  354     while(EEPROM_GetWriteReady() != ee_ok);
??EEPROM_ReadData_0:
        BL       EEPROM_GetWriteReady
          CFI FunCall EEPROM_GetWriteReady
        CMP      R0,#+0
        BNE      ??EEPROM_ReadData_0
//  355     
//  356     // send the PAGE_PROGRAM command
//  357     status |= EEPROM_SendCmd(EEPROM_CMD_READ_DATA_BYTES, EEPROM_CMD_CNT );
        MOVS     R1,#+0
        MOVS     R0,#+3
        BL       EEPROM_SendCmd
          CFI FunCall EEPROM_SendCmd
        ORRS     R0,R0,R4
        MOVS     R4,R0
//  358     // send the address
//  359     status |= EEPROM_SendAddress(Addr);
        MOVS     R0,R6
        BL       EEPROM_SendAddress
          CFI FunCall EEPROM_SendAddress
        ORRS     R0,R0,R4
        MOVS     R4,R0
//  360     
//  361     if(status != ee_ok)
        UXTB     R4,R4
        CMP      R4,#+0
        BEQ      ??EEPROM_ReadData_1
//  362     {
//  363         status = ee_error;
        MOVS     R0,#+4
        MOVS     R4,R0
        B        ??EEPROM_ReadData_2
//  364     }
//  365     
//  366     else
//  367     {
//  368         gEepromAssertCS_d();
??EEPROM_ReadData_1:
        LDR      R0,??DataTable8  ;; 0x400ff008
        LDR      R0,[R0, #+0]
        MOVS     R1,#+128
        LSLS     R1,R1,#+12       ;; #+524288
        ORRS     R1,R1,R0
        LDR      R0,??DataTable8  ;; 0x400ff008
        STR      R1,[R0, #+0]
//  369         status |= spi_master_transfer(mEepromSpiInstance_c, NULL, inbuf, NoOfBytes);
        UXTH     R5,R5
        MOVS     R3,R5
        MOVS     R2,R7
        MOVS     R1,#+0
        MOVS     R0,#+1
        BL       spi_master_transfer
          CFI FunCall spi_master_transfer
        ORRS     R0,R0,R4
        MOVS     R4,R0
//  370         gEepromDeassertCS_d();
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        LDR      R0,[R0, #+0]
        MOVS     R1,#+128
        LSLS     R1,R1,#+12       ;; #+524288
        ORRS     R1,R1,R0
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        STR      R1,[R0, #+0]
//  371     }
//  372     
//  373     if(status == ee_ok) 
??EEPROM_ReadData_2:
        UXTB     R4,R4
        CMP      R4,#+0
        BNE      ??EEPROM_ReadData_3
//  374     {
//  375         return status;
        MOVS     R0,R4
        UXTB     R0,R0
        B        ??EEPROM_ReadData_4
//  376     }
//  377     else
//  378     {
//  379         return ee_error;
??EEPROM_ReadData_3:
        MOVS     R0,#+4
??EEPROM_ReadData_4:
        POP      {R1,R4-R7,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
//  380     }
//  381 }
          CFI EndBlock cfiBlock6
//  382 
//  383 /*****************************************************************************
//  384 *  EEPROM_ReadStatusReq
//  385 *
//  386 *
//  387 *****************************************************************************/

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function EEPROM_isBusy
          CFI NoCalls
        THUMB
//  388 uint8_t EEPROM_isBusy(void)
//  389 {
EEPROM_isBusy:
        PUSH     {LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+4
//  390     if(EEPROM_IsWriteInProgress() != 0)
        LDR      R0,??DataTable8_1
        LDRB     R0,[R0, #+0]
        LSLS     R0,R0,#+31
        BPL      ??EEPROM_isBusy_0
//  391     {
//  392         return 1;
        MOVS     R0,#+1
        B        ??EEPROM_isBusy_1
//  393     }
//  394     return 0;
??EEPROM_isBusy_0:
        MOVS     R0,#+0
??EEPROM_isBusy_1:
        POP      {PC}             ;; return
          CFI CFA R13+0
//  395 }
          CFI EndBlock cfiBlock7
//  396 
//  397 /*! *********************************************************************************
//  398 * \brief        
//  399 *
//  400 * \param[in]    
//  401 * \param[in]    
//  402 ********************************************************************************** */
//  403 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function EEPROM_ReadStatus
        THUMB
//  404 ee_err_t EEPROM_ReadStatus(uint8_t* flashStatus)
//  405 {
EEPROM_ReadStatus:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R5,R0
//  406     ee_err_t status = ee_ok;
        MOVS     R4,#+0
//  407     
//  408     status |= EEPROM_SendCmd( EEPROM_CMD_READ_STATUS, EEPROM_CMD_CNT );
        MOVS     R1,#+0
        MOVS     R0,#+5
        BL       EEPROM_SendCmd
          CFI FunCall EEPROM_SendCmd
        ORRS     R0,R0,R4
        MOVS     R4,R0
//  409     
//  410     if(status == ee_ok) 
        UXTB     R4,R4
        CMP      R4,#+0
        BNE      ??EEPROM_ReadStatus_0
//  411     {
//  412         if(spi_master_transfer(mEepromSpiInstance_c, NULL, &currentStatus, sizeof(currentStatus)) != 0)
        MOVS     R3,#+1
        LDR      R2,??DataTable8_1
        MOVS     R1,#+0
        MOVS     R0,#+1
        BL       spi_master_transfer
          CFI FunCall spi_master_transfer
        CMP      R0,#+0
        BEQ      ??EEPROM_ReadStatus_1
//  413         {
//  414             status |= ee_error;
        MOVS     R0,R4
        MOVS     R4,#+4
        ORRS     R4,R4,R0
//  415         }
//  416         
//  417         gEepromDeassertCS_d();
??EEPROM_ReadStatus_1:
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        LDR      R0,[R0, #+0]
        MOVS     R1,#+128
        LSLS     R1,R1,#+12       ;; #+524288
        ORRS     R1,R1,R0
        LDR      R0,??DataTable6_1  ;; 0x400ff004
        STR      R1,[R0, #+0]
//  418     }
//  419     
//  420     if(status != ee_ok) 
??EEPROM_ReadStatus_0:
        UXTB     R4,R4
        CMP      R4,#+0
        BEQ      ??EEPROM_ReadStatus_2
//  421     {
//  422        status = ee_error; 
        MOVS     R0,#+4
        MOVS     R4,R0
        B        ??EEPROM_ReadStatus_3
//  423     }
//  424     else
//  425     {
//  426         if ( NULL != flashStatus )
??EEPROM_ReadStatus_2:
        CMP      R5,#+0
        BEQ      ??EEPROM_ReadStatus_3
//  427         {
//  428             *flashStatus = currentStatus;
        LDR      R0,??DataTable8_1
        LDRB     R0,[R0, #+0]
        STRB     R0,[R5, #+0]
//  429         }
//  430     }
//  431     
//  432     return status;
??EEPROM_ReadStatus_3:
        MOVS     R0,R4
        UXTB     R0,R0
        POP      {R1,R4,R5,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
//  433 }
          CFI EndBlock cfiBlock8

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable6:
        DC32     mEepromEraseBitmap

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable6_1:
        DC32     0x400ff004
//  434 
//  435 /*! *********************************************************************************
//  436 *************************************************************************************
//  437 * Private Functions
//  438 *************************************************************************************
//  439 ********************************************************************************** */
//  440 
//  441 /*! *********************************************************************************
//  442 * \brief        
//  443 *
//  444 * \param[in]    
//  445 * \param[in]    
//  446 ********************************************************************************** */
//  447 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function EEPROM_SendCmd
        THUMB
//  448 static ee_err_t EEPROM_SendCmd(const uint8_t cmdToSend, uint8_t  endFlag)
//  449 {
EEPROM_SendCmd:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R7,R0
        MOVS     R6,R1
//  450     ee_err_t status = ee_ok;
        MOVS     R4,#+0
//  451     uint8_t txSize = 1, cmdBuf[1];
        MOVS     R5,#+1
//  452     
//  453     cmdBuf[0] = cmdToSend;
        MOV      R0,SP
        STRB     R7,[R0, #+0]
//  454     
//  455     gEepromAssertCS_d();
        LDR      R0,??DataTable8  ;; 0x400ff008
        LDR      R0,[R0, #+0]
        MOVS     R1,#+128
        LSLS     R1,R1,#+12       ;; #+524288
        ORRS     R1,R1,R0
        LDR      R0,??DataTable8  ;; 0x400ff008
        STR      R1,[R0, #+0]
//  456     
//  457     if(spi_master_transfer(mEepromSpiInstance_c, cmdBuf, NULL, txSize) != 0)
        UXTB     R5,R5
        MOVS     R3,R5
        MOVS     R2,#+0
        MOV      R1,SP
        MOVS     R0,#+1
        BL       spi_master_transfer
          CFI FunCall spi_master_transfer
        CMP      R0,#+0
        BEQ      ??EEPROM_SendCmd_0
//  458     {
//  459         status = ee_error;
        MOVS     R0,#+4
        MOVS     R4,R0
//  460     }
//  461     
//  462     if ( EEPROM_CMD_END == endFlag )
??EEPROM_SendCmd_0:
        UXTB     R6,R6
        CMP      R6,#+1
        BNE      ??EEPROM_SendCmd_1
//  463     {
//  464         gEepromDeassertCS_d();
        LDR      R0,??DataTable8_2  ;; 0x400ff004
        LDR      R0,[R0, #+0]
        MOVS     R1,#+128
        LSLS     R1,R1,#+12       ;; #+524288
        ORRS     R1,R1,R0
        LDR      R0,??DataTable8_2  ;; 0x400ff004
        STR      R1,[R0, #+0]
//  465     }
//  466         
//  467     return status;
??EEPROM_SendCmd_1:
        MOVS     R0,R4
        UXTB     R0,R0
        POP      {R1,R4-R7,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
//  468 }
          CFI EndBlock cfiBlock9
//  469 
//  470 /*! *********************************************************************************
//  471 * \brief        
//  472 *
//  473 * \param[in]    
//  474 * \param[in]    
//  475 ********************************************************************************** */
//  476 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function EEPROM_GetWriteReady
        THUMB
//  477 static ee_err_t EEPROM_GetWriteReady()
//  478 {
EEPROM_GetWriteReady:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//  479     ee_err_t status = ee_ok;
        MOVS     R4,#+0
//  480     
//  481     /**
//  482     * make sure there is no other writing in progress
//  483     */
//  484     status = EEPROM_ReadStatus( NULL );
        MOVS     R0,#+0
        BL       EEPROM_ReadStatus
          CFI FunCall EEPROM_ReadStatus
        MOVS     R4,R0
//  485     
//  486     if(status != ee_ok) 
        UXTB     R4,R4
        CMP      R4,#+0
        BEQ      ??EEPROM_GetWriteReady_0
//  487     {
//  488         return ee_error;
        MOVS     R0,#+4
        B        ??EEPROM_GetWriteReady_1
//  489     }
//  490     
//  491     if (EEPROM_IsWriteInProgress())
??EEPROM_GetWriteReady_0:
        LDR      R0,??DataTable8_1
        LDRB     R0,[R0, #+0]
        LSLS     R0,R0,#+31
        BPL      ??EEPROM_GetWriteReady_2
//  492     {
//  493         /**
//  494          * poll untill the writing is enabled
//  495         */
//  496         while (1)
//  497         {
//  498             status = EEPROM_ReadStatus( NULL );
??EEPROM_GetWriteReady_3:
        MOVS     R0,#+0
        BL       EEPROM_ReadStatus
          CFI FunCall EEPROM_ReadStatus
        MOVS     R4,R0
//  499             if (status != ee_ok)
        UXTB     R4,R4
        CMP      R4,#+0
        BEQ      ??EEPROM_GetWriteReady_4
//  500             {
//  501                 return ee_error;
        MOVS     R0,#+4
        B        ??EEPROM_GetWriteReady_1
//  502             }
//  503 
//  504             if (EEPROM_IsWriteNotInProgress())
??EEPROM_GetWriteReady_4:
        LDR      R0,??DataTable8_1
        LDRB     R0,[R0, #+0]
        LSLS     R0,R0,#+31
        BMI      ??EEPROM_GetWriteReady_3
//  505             {
//  506                 break;
//  507             }
//  508         }
//  509     }
//  510     
//  511     /**
//  512    * make sure WEL bit is HIGH (writing is enabled)
//  513    */
//  514     while (1)
//  515     {
//  516         status = EEPROM_ReadStatus( NULL );
??EEPROM_GetWriteReady_2:
        MOVS     R0,#+0
        BL       EEPROM_ReadStatus
          CFI FunCall EEPROM_ReadStatus
        MOVS     R4,R0
//  517         if (status != ee_ok)
        UXTB     R4,R4
        CMP      R4,#+0
        BEQ      ??EEPROM_GetWriteReady_5
//  518         {
//  519             return ee_error;
        MOVS     R0,#+4
        B        ??EEPROM_GetWriteReady_1
//  520         }
//  521         else
//  522         {
//  523             if (EEPROM_IsWriteEnabled())
??EEPROM_GetWriteReady_5:
        LDR      R0,??DataTable8_1
        LDRB     R0,[R0, #+0]
        ASRS     R0,R0,#+1
        LSLS     R0,R0,#+31
        BPL      ??EEPROM_GetWriteReady_6
//  524             {
//  525                 break;
//  526             }
//  527 
//  528             else
//  529             {
//  530                 status = EEPROM_SendCmd( EEPROM_CMD_WRITE_ENABLE, EEPROM_CMD_END );
//  531                 if (status != ee_ok)
//  532                 {
//  533                     return ee_error;
//  534                 }
//  535             }
//  536         }
//  537     }
//  538     
//  539     return ee_ok;
        MOVS     R0,#+0
        B        ??EEPROM_GetWriteReady_1
??EEPROM_GetWriteReady_6:
        MOVS     R1,#+1
        MOVS     R0,#+6
        BL       EEPROM_SendCmd
          CFI FunCall EEPROM_SendCmd
        MOVS     R4,R0
        UXTB     R4,R4
        CMP      R4,#+0
        BEQ      ??EEPROM_GetWriteReady_2
        MOVS     R0,#+4
??EEPROM_GetWriteReady_1:
        POP      {R4,PC}          ;; return
          CFI R4 SameValue
          CFI CFA R13+0
//  540 }
          CFI EndBlock cfiBlock10

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8:
        DC32     0x400ff008

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_1:
        DC32     currentStatus

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_2:
        DC32     0x400ff004
//  541 
//  542 /*! *********************************************************************************
//  543 * \brief        
//  544 *
//  545 * \param[in]    
//  546 * \param[in]    
//  547 ********************************************************************************** */
//  548 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function EEPROM_SendAddress
        THUMB
//  549 static ee_err_t EEPROM_SendAddress(uint32_t eepromAddress)
//  550 {
EEPROM_SendAddress:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
//  551     ee_err_t status = ee_ok;
        MOVS     R5,#+0
//  552     uint32_t fmtAddr = 0;
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
//  553     
//  554     // if the address is bigger than 24 bytes, exit
//  555     if ( eepromAddress > 0x00FFFFFF)
        MOVS     R0,#+128
        LSLS     R0,R0,#+17       ;; #+16777216
        CMP      R4,R0
        BCC      ??EEPROM_SendAddress_0
//  556     {
//  557         return ee_error;
        MOVS     R0,#+4
        B        ??EEPROM_SendAddress_1
//  558     }
//  559 
//  560     // arrange bytes
//  561     fmtAddr |= ( eepromAddress & 0xFF0000 ) >> 16;
??EEPROM_SendAddress_0:
        LDR      R0,[SP, #+0]
        MOVS     R1,R4
        LSRS     R1,R1,#+16
        UXTB     R1,R1
        ORRS     R1,R1,R0
        STR      R1,[SP, #+0]
//  562     fmtAddr |= ( eepromAddress & 0x00FF00 );
        LDR      R0,[SP, #+0]
        MOVS     R1,#+255
        LSLS     R1,R1,#+8        ;; #+65280
        ANDS     R1,R1,R4
        ORRS     R1,R1,R0
        STR      R1,[SP, #+0]
//  563     fmtAddr |= ( eepromAddress & 0x0000FF ) << 16;
        LDR      R0,[SP, #+0]
        UXTB     R1,R4
        LSLS     R1,R1,#+16
        ORRS     R1,R1,R0
        STR      R1,[SP, #+0]
//  564     
//  565     if(spi_master_transfer(mEepromSpiInstance_c, (uint8_t*)&fmtAddr, NULL, 3) != 0)
        MOVS     R3,#+3
        MOVS     R2,#+0
        MOV      R1,SP
        MOVS     R0,#+1
        BL       spi_master_transfer
          CFI FunCall spi_master_transfer
        CMP      R0,#+0
        BEQ      ??EEPROM_SendAddress_2
//  566     {
//  567         status = ee_error;
        MOVS     R0,#+4
        MOVS     R5,R0
//  568     }
//  569   
//  570   
//  571     return status;
??EEPROM_SendAddress_2:
        MOVS     R0,R5
        UXTB     R0,R0
??EEPROM_SendAddress_1:
        POP      {R1,R4,R5,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
//  572 }
          CFI EndBlock cfiBlock11

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//  573 
//  574 
//  575 
//  576 #endif /* gEepromDevice_M25P80_c */
// 
//    65 bytes in section .bss
// 1 078 bytes in section .text
// 
// 1 078 bytes of CODE memory
//    65 bytes of DATA memory
//
//Errors: none
//Warnings: none
