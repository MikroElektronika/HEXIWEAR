///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       12/Jan/2016  08:59:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\spi\SPI.c
//    Command line =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\spi\SPI.c
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
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\SPI.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__SystemLibrary", "DLib"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        PUBLIC spi_master_configure_bus
        PUBLIC spi_master_init
        PUBLIC spi_master_transfer
        
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
        
// C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\spi\SPI.c
//    1 /*!
//    2 * Copyright (c) 2015, Freescale Semiconductor, Inc.
//    3 * All rights reserved.
//    4 *
//    5 * \file SPI.c
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
//   39 
//   40 #include "EmbeddedTypes.h"
//   41 #include "SPI.h"
//   42 
//   43 
//   44 /*! *********************************************************************************
//   45 *************************************************************************************
//   46 * Public Functions
//   47 *************************************************************************************
//   48 ********************************************************************************** */
//   49 
//   50 /*! *********************************************************************************
//   51 * \brief   This function initialized the SPI module
//   52 *
//   53 * \param[in]  interfaceId        SPI module number
//   54 *
//   55 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function spi_master_init
          CFI NoCalls
        THUMB
//   56 void spi_master_init(uint32_t instance)
//   57 {
//   58     (void)instance;
//   59     /* Enable SPI PORT clock */
//   60     BOOT_SPI_PORT_SIM_SCG |= cSPI_PORT_SIM_SCG_Config_c;
spi_master_init:
        LDR      R1,??DataTable2  ;; 0x40048038
        LDR      R1,[R1, #+0]
        MOVS     R2,#+128
        LSLS     R2,R2,#+2        ;; #+512
        ORRS     R2,R2,R1
        LDR      R1,??DataTable2  ;; 0x40048038
        STR      R2,[R1, #+0]
//   61     /* Enable SPI clock */
//   62     BOOT_SPI_SIM_SCG |= cSPI_SIM_SCG_Config_c;
        LDR      R1,??DataTable2_1  ;; 0x4004803c
        LDR      R1,[R1, #+0]
        MOVS     R2,#+128
        LSLS     R2,R2,#+6        ;; #+8192
        ORRS     R2,R2,R1
        LDR      R1,??DataTable2_1  ;; 0x4004803c
        STR      R2,[R1, #+0]
//   63     /* Initialize SPI Pin Control registers */
//   64     BOOT_SPI_SCLK_PCR &= ~PORT_PCR_MUX_MASK;
        LDR      R1,??DataTable2_2  ;; 0x40049048
        LDR      R1,[R1, #+0]
        LDR      R2,??DataTable2_3  ;; 0xfffff8ff
        ANDS     R2,R2,R1
        LDR      R1,??DataTable2_2  ;; 0x40049048
        STR      R2,[R1, #+0]
//   65     BOOT_SPI_SCLK_PCR |= PORT_PCR_MUX(2);
        LDR      R1,??DataTable2_2  ;; 0x40049048
        LDR      R1,[R1, #+0]
        MOVS     R2,#+128
        LSLS     R2,R2,#+2        ;; #+512
        ORRS     R2,R2,R1
        LDR      R1,??DataTable2_2  ;; 0x40049048
        STR      R2,[R1, #+0]
//   66     BOOT_SPI_MOSI_PCR &= ~PORT_PCR_MUX_MASK;
        LDR      R1,??DataTable2_4  ;; 0x40049040
        LDR      R1,[R1, #+0]
        LDR      R2,??DataTable2_3  ;; 0xfffff8ff
        ANDS     R2,R2,R1
        LDR      R1,??DataTable2_4  ;; 0x40049040
        STR      R2,[R1, #+0]
//   67     BOOT_SPI_MOSI_PCR |= PORT_PCR_MUX(2);
        LDR      R1,??DataTable2_4  ;; 0x40049040
        LDR      R1,[R1, #+0]
        MOVS     R2,#+128
        LSLS     R2,R2,#+2        ;; #+512
        ORRS     R2,R2,R1
        LDR      R1,??DataTable2_4  ;; 0x40049040
        STR      R2,[R1, #+0]
//   68     BOOT_SPI_MISO_PCR &= ~PORT_PCR_MUX_MASK;
        LDR      R1,??DataTable2_5  ;; 0x40049044
        LDR      R1,[R1, #+0]
        LDR      R2,??DataTable2_3  ;; 0xfffff8ff
        ANDS     R2,R2,R1
        LDR      R1,??DataTable2_5  ;; 0x40049044
        STR      R2,[R1, #+0]
//   69     BOOT_SPI_MISO_PCR |= PORT_PCR_MUX(2);
        LDR      R1,??DataTable2_5  ;; 0x40049044
        LDR      R1,[R1, #+0]
        MOVS     R2,#+128
        LSLS     R2,R2,#+2        ;; #+512
        ORRS     R2,R2,R1
        LDR      R1,??DataTable2_5  ;; 0x40049044
        STR      R2,[R1, #+0]
//   70     //  BOOT_SPI_SSEL_PCR &= ~PORT_PCR_MUX_MASK;
//   71     //  BOOT_SPI_SSEL_PCR |= PORT_PCR_MUX(2);
//   72     /* CS is used as a GPIO */
//   73     BOOT_SPI_SSEL_PCR &= ~PORT_PCR_MUX_MASK;
        LDR      R1,??DataTable2_6  ;; 0x4004904c
        LDR      R1,[R1, #+0]
        LDR      R2,??DataTable2_3  ;; 0xfffff8ff
        ANDS     R2,R2,R1
        LDR      R1,??DataTable2_6  ;; 0x4004904c
        STR      R2,[R1, #+0]
//   74     BOOT_SPI_SSEL_PCR |= PORT_PCR_MUX(1);
        LDR      R1,??DataTable2_6  ;; 0x4004904c
        LDR      R1,[R1, #+0]
        MOVS     R2,#+128
        LSLS     R2,R2,#+1        ;; #+256
        ORRS     R2,R2,R1
        LDR      R1,??DataTable2_6  ;; 0x4004904c
        STR      R2,[R1, #+0]
//   75     BOOT_SPI_SSEL_PDDR |= 1 << BOOT_SPI_SSEL_PIN_Number_c;
        LDR      R1,??DataTable2_7  ;; 0x400ff014
        LDR      R1,[R1, #+0]
        MOVS     R2,#+128
        LSLS     R2,R2,#+12       ;; #+524288
        ORRS     R2,R2,R1
        LDR      R1,??DataTable2_7  ;; 0x400ff014
        STR      R2,[R1, #+0]
//   76     deassert_cs();
        LDR      R1,??DataTable2_8  ;; 0x400ff004
        LDR      R1,[R1, #+0]
        MOVS     R2,#+128
        LSLS     R2,R2,#+12       ;; #+524288
        ORRS     R2,R2,R1
        LDR      R1,??DataTable2_8  ;; 0x400ff004
        STR      R2,[R1, #+0]
//   77 
//   78     /* Initialize SPI module */
//   79 #if gSPI_HW_TYPE_c == gDSPI_HW_c
//   80     SPI_MCR_REG(BOOT_SPI_BaseAddr) = SPI_MCR_MSTR_MASK    |
//   81                                      SPI_MCR_ROOE_MASK    |
//   82                                      SPI_MCR_CLR_RXF_MASK |
//   83                                      SPI_MCR_CLR_TXF_MASK |
//   84                                      SPI_MCR_PCSIS(1)     |
//   85                                      SPI_MCR_SMPL_PT(2)   |
//   86                                      SPI_MCR_HALT_MASK;
        LDR      R1,??DataTable2_9  ;; 0x81010e01
        LDR      R2,??DataTable2_10  ;; 0x4002d000
        STR      R1,[R2, #+0]
//   87 #else
//   88     SPI_C1_REG(BOOT_SPI_BaseAddr) = SPI_C1_MSTR_MASK;
//   89     SPI_C2_REG(BOOT_SPI_BaseAddr) = 0x00;
//   90     SPI_C1_REG(BOOT_SPI_BaseAddr) |= SPI_C1_SPE_MASK;
//   91 #endif
//   92 }
        BX       LR               ;; return
          CFI EndBlock cfiBlock0
//   93 
//   94 /*! *********************************************************************************
//   95 * \brief   This function configures the SPI interface
//   96 *
//   97 * \param[in]  interfaceId        SPI module number
//   98 * \param[in]  device             device config strucure
//   99 *
//  100 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function spi_master_configure_bus
          CFI NoCalls
        THUMB
//  101 void spi_master_configure_bus(uint32_t instance, const spi_user_config_t * device)
//  102 {
//  103 #if gSPI_HW_TYPE_c == gDSPI_HW_c
//  104     SPI_CTAR_REG(BOOT_SPI_BaseAddr,0) = SPI_CTAR_PBR(0)    | SPI_CTAR_BR(0x01)    |
//  105                                         SPI_CTAR_PCSSCK(1) | SPI_CTAR_CSSCK(0x04) |
//  106                                         SPI_CTAR_PASC(3)   | SPI_CTAR_ASC(0x04)   |
//  107                                         SPI_CTAR_PDT(3)    | SPI_CTAR_DT(0x05)    |
//  108                                         SPI_CTAR_FMSZ(7);
spi_master_configure_bus:
        LDR      R2,??DataTable2_11  ;; 0x387c4451
        LDR      R3,??DataTable2_12  ;; 0x4002d00c
        STR      R2,[R3, #+0]
//  109 #else
//  110     SPI_BR_REG(BOOT_SPI_BaseAddr) = SPI_BR_SPPR(1) | SPI_BR_SPR(0);
//  111 #endif
//  112 }
        BX       LR               ;; return
          CFI EndBlock cfiBlock1
//  113 
//  114 
//  115 /*! *********************************************************************************
//  116 * \brief   This function transferes bytes over the SPI interface
//  117 *
//  118 * \param[in]  interfaceId        SPI module number
//  119 * \param[in]  device             device config strucure
//  120 * \param[in]  sendBuffer         location of data to be Tx. NULL if no Tx needed
//  121 * \param[out] receiveBuffer      location where Rx data is stored. NULL if no Rx needed
//  122 * \param[in]  transferByteCount  number of bytes to be transfered
//  123 *
//  124 * \return spi_status_t
//  125 *
//  126 ********************************************************************************** */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function spi_master_transfer
          CFI NoCalls
        THUMB
//  127 spi_status_t spi_master_transfer(uint32_t instance,
//  128                                  const uint8_t * sendBuffer,
//  129                                  uint8_t * receiveBuffer,
//  130                                  uint32_t transferByteCount)
//  131 {
spi_master_transfer:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
//  132     volatile uint8_t dummy = 0;
        MOVS     R0,#+0
        MOV      R5,SP
        STRB     R0,[R5, #+0]
//  133 
//  134     if( !transferByteCount )
        CMP      R3,#+0
        BNE      ??spi_master_transfer_0
//  135         return 0;
        MOVS     R0,#+0
        B        ??spi_master_transfer_1
//  136 
//  137     if( !sendBuffer && !receiveBuffer )
??spi_master_transfer_0:
        CMP      R1,#+0
        BNE      ??spi_master_transfer_2
        CMP      R2,#+0
        BNE      ??spi_master_transfer_2
//  138         return 1;
        MOVS     R0,#+1
        B        ??spi_master_transfer_1
//  139 
//  140 #if gSPI_HW_TYPE_c == gDSPI_HW_c
//  141     /* Flush SPI FIFOs */
//  142     SPI_MCR_REG(BOOT_SPI_BaseAddr) |= SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK;
??spi_master_transfer_2:
        LDR      R0,??DataTable2_10  ;; 0x4002d000
        LDR      R0,[R0, #+0]
        MOVS     R5,#+192
        LSLS     R5,R5,#+4        ;; #+3072
        ORRS     R5,R5,R0
        LDR      R0,??DataTable2_10  ;; 0x4002d000
        STR      R5,[R0, #+0]
//  143     /* Clear the EOQF, TCF and RFDF flags by writting a 1 to them */
//  144     SPI_SR_REG(BOOT_SPI_BaseAddr)  |= SPI_SR_EOQF_MASK | SPI_SR_TCF_MASK | SPI_SR_RFDF_MASK;
        LDR      R0,??DataTable2_13  ;; 0x4002d02c
        LDR      R0,[R0, #+0]
        LDR      R5,??DataTable2_14  ;; 0x90020000
        ORRS     R5,R5,R0
        LDR      R0,??DataTable2_13  ;; 0x4002d02c
        STR      R5,[R0, #+0]
//  145 #else
//  146     dummy = SPI_S_REG(BOOT_SPI_BaseAddr);
//  147 #endif
//  148 
//  149     while( transferByteCount-- )
??spi_master_transfer_3:
        MOVS     R0,R3
        SUBS     R3,R0,#+1
        CMP      R0,#+0
        BEQ      ??spi_master_transfer_4
//  150     {
//  151         if( sendBuffer )
        CMP      R1,#+0
        BEQ      ??spi_master_transfer_5
//  152         {
//  153             dummy = *sendBuffer;
        LDRB     R0,[R1, #+0]
        MOV      R5,SP
        STRB     R0,[R5, #+0]
//  154             sendBuffer++;
        ADDS     R1,R1,#+1
        B        ??spi_master_transfer_6
//  155         }
//  156         else
//  157         {
//  158             dummy = 0xFF;
??spi_master_transfer_5:
        MOVS     R0,#+255
        MOV      R5,SP
        STRB     R0,[R5, #+0]
//  159         }
//  160 
//  161 #if gSPI_HW_TYPE_c == gDSPI_HW_c
//  162         /* Write data */
//  163         SPI_PUSHR_REG(BOOT_SPI_BaseAddr) = dummy;
??spi_master_transfer_6:
        MOV      R0,SP
        LDRB     R0,[R0, #+0]
        LDR      R5,??DataTable2_15  ;; 0x4002d034
        STR      R0,[R5, #+0]
//  164         /* Start SPI Transfer */
//  165         SPI_MCR_REG(BOOT_SPI_BaseAddr) &= ~SPI_MCR_HALT_MASK;
        LDR      R0,??DataTable2_10  ;; 0x4002d000
        LDR      R0,[R0, #+0]
        MOVS     R5,#+1
        BICS     R0,R0,R5
        LDR      R5,??DataTable2_10  ;; 0x4002d000
        STR      R0,[R5, #+0]
//  166         /* Wait Transfer complete */
//  167         while( !(SPI_SR_REG(BOOT_SPI_BaseAddr) & SPI_SR_TCF_MASK) );
??spi_master_transfer_7:
        LDR      R0,??DataTable2_13  ;; 0x4002d02c
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BPL      ??spi_master_transfer_7
//  168         /* Clear Transfer complete flag */
//  169         SPI_SR_REG(BOOT_SPI_BaseAddr) |= SPI_SR_TCF_MASK;
        LDR      R0,??DataTable2_13  ;; 0x4002d02c
        LDR      R0,[R0, #+0]
        MOVS     R5,#+128
        LSLS     R5,R5,#+24       ;; #-2147483648
        ORRS     R5,R5,R0
        LDR      R0,??DataTable2_13  ;; 0x4002d02c
        STR      R5,[R0, #+0]
//  170         /* Stop SPI transfer */
//  171         SPI_MCR_REG(BOOT_SPI_BaseAddr) |= SPI_MCR_HALT_MASK;
        LDR      R0,??DataTable2_10  ;; 0x4002d000
        LDR      R0,[R0, #+0]
        MOVS     R5,#+1
        ORRS     R5,R5,R0
        LDR      R0,??DataTable2_10  ;; 0x4002d000
        STR      R5,[R0, #+0]
//  172         /* Get received datad */
//  173         dummy = SPI_POPR_REG(BOOT_SPI_BaseAddr);
        LDR      R0,??DataTable2_16  ;; 0x4002d038
        LDR      R0,[R0, #+0]
        MOV      R5,SP
        STRB     R0,[R5, #+0]
//  174 #else
//  175         /* Write data */
//  176         SPI_DL_REG(BOOT_SPI_BaseAddr) = dummy;
//  177         /* Wait for transfer complete */
//  178         //        while(!(SPI1_S & SPI_S_SPTEF_MASK));
//  179         while(!(SPI_S_REG(BOOT_SPI_BaseAddr) & SPI_S_SPRF_MASK));
//  180         /* Get received datad */
//  181         dummy = SPI_DL_REG(BOOT_SPI_BaseAddr);
//  182 #endif
//  183 
//  184         if( receiveBuffer )
        CMP      R2,#+0
        BEQ      ??spi_master_transfer_3
//  185         {
//  186             *receiveBuffer = dummy;
        MOV      R0,SP
        LDRB     R0,[R0, #+0]
        STRB     R0,[R2, #+0]
//  187             receiveBuffer++;
        ADDS     R2,R2,#+1
        B        ??spi_master_transfer_3
//  188         }
//  189     }
//  190 
//  191     (void)dummy;
??spi_master_transfer_4:
        MOV      R0,SP
        LDRB     R0,[R0, #+0]
//  192     return 0;
        MOVS     R0,#+0
??spi_master_transfer_1:
        POP      {R1,R4,R5,PC}    ;; return
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
//  193 }
          CFI EndBlock cfiBlock2

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2:
        DC32     0x40048038

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_1:
        DC32     0x4004803c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_2:
        DC32     0x40049048

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_3:
        DC32     0xfffff8ff

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_4:
        DC32     0x40049040

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_5:
        DC32     0x40049044

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_6:
        DC32     0x4004904c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_7:
        DC32     0x400ff014

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_8:
        DC32     0x400ff004

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_9:
        DC32     0x81010e01

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_10:
        DC32     0x4002d000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_11:
        DC32     0x387c4451

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_12:
        DC32     0x4002d00c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_13:
        DC32     0x4002d02c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_14:
        DC32     0x90020000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_15:
        DC32     0x4002d034

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_16:
        DC32     0x4002d038

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
// 412 bytes in section .text
// 
// 412 bytes of CODE memory
//
//Errors: none
//Warnings: none
