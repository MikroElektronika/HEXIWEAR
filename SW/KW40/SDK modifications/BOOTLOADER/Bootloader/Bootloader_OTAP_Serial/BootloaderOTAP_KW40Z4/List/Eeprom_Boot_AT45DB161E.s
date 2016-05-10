///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       12/Jan/2016  08:59:55
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\Eeprom_Boot_AT45DB161E.c
//    Command line =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\Eeprom_Boot_AT45DB161E.c
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
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\Eeprom_Boot_AT45DB161E.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__SystemLibrary", "DLib"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1


        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\eeprom\Eeprom_Boot_AT45DB161E.c
//    1 /*!
//    2 * Copyright (c) 2015, Freescale Semiconductor, Inc.
//    3 * All rights reserved.
//    4 *
//    5 * \file EEPROM_AT45DB161E.c
//    6 * This is a source file which implements the driver for the AT45DB161E memory.
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
//   40 #include "Eeprom_Boot.h"
//   41 
//   42 #if gEepromType_d == gEepromDevice_AT45DB161E_c
//   43 
//   44 #include "SPI.h"
//   45 
//   46 /*! *********************************************************************************
//   47 *************************************************************************************
//   48 * Private macros
//   49 *************************************************************************************
//   50 ********************************************************************************** */
//   51 #define  gEepromWriteEnable_d   0
//   52 
//   53 #define  EEPROM_RDSR            0xD7
//   54 #define  EEPROM_READ            0x03
//   55 #define  EEPROM_READ_HF         0x0B
//   56 
//   57 #define  EEPROM_ERASE_512B      0x81
//   58 #define  EEPROM_ERASE_4K        0x50
//   59 
//   60 #define  EEPROM_WRITE_BYTES     0x02
//   61 
//   62 #define  EEPROM_BUSY_FLAG_MASK  0x80
//   63 #define  EEPROM_PAGE_SIZE       (512)
//   64 #define  EEPROM_BLOCK_SIZE      (8*EEPROM_PAGE_SIZE)
//   65 #define  EEPROM_PAGE_MASK       (EEPROM_PAGE_SIZE - 1)
//   66 
//   67 /* adress mask */
//   68 #define  ADDRESS_MASK 0x000000FF
//   69 
//   70 
//   71 /****************************** SPI MACROS ***********************************/
//   72 #define mEepromSpiInstance_c 0
//   73 
//   74 
//   75 /******************************************************************************
//   76 *******************************************************************************
//   77 * Private Prototypes
//   78 *******************************************************************************
//   79 ******************************************************************************/
//   80 #if gEepromWriteEnable_d
//   81 static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr);
//   82 static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf);
//   83 #endif
//   84 static ee_err_t EEPROM_WaitForReady(void);
//   85 static uint16_t EEPROM_ReadStatusReq(void);
//   86 static void     EEPROM_Command(uint8_t opCode, uint32_t Addr);
//   87 
//   88 
//   89 /*! *********************************************************************************
//   90 *************************************************************************************
//   91 * Private Memory Declarations
//   92 *************************************************************************************
//   93 ********************************************************************************** */
//   94 #if gEepromWriteEnable_d
//   95 static uint8_t mEepromEraseBitmap[64];
//   96 #endif
//   97 
//   98 
//   99 /*! *********************************************************************************
//  100 *************************************************************************************
//  101 * Public Functions
//  102 *************************************************************************************
//  103 ********************************************************************************** */
//  104 
//  105 /*****************************************************************************
//  106 *  EEPROM_Init
//  107 *
//  108 *  Initializes the EEPROM peripheral
//  109 *
//  110 *****************************************************************************/
//  111 ee_err_t EEPROM_Init(void)
//  112 {
//  113     ee_err_t retval;
//  114     uint8_t cmd[] = {0x3D, 0x2A, 0x80, 0xA6};
//  115     spi_user_config_t config;
//  116 #if gEepromWriteEnable_d
//  117     uint32_t i;
//  118     
//  119     // Mark Flash as Unerased
//  120     for(i = 0; i < 64; i++)
//  121         mEepromEraseBitmap[i] = 0;
//  122 #endif
//  123     
//  124     config.busFrequencyKHz = 8000;
//  125     config.direction = kSpiMsbFirst;
//  126     config.phase = kSpiClockPhase_FirstEdge;
//  127     config.polarity = kSpiClockPolarity_ActiveHigh;
//  128     
//  129     spi_master_init(mEepromSpiInstance_c);
//  130     spi_master_configure_bus(mEepromSpiInstance_c, &config);
//  131     
//  132     retval = EEPROM_WaitForReady();
//  133     if (retval != ee_ok)
//  134         return retval;
//  135     
//  136     // Set page size to 512bits:
//  137     assert_cs();
//  138     spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
//  139     deassert_cs();
//  140     
//  141     return ee_ok;
//  142 }
//  143 
//  144 /*****************************************************************************
//  145 *  EEPROM_ChipErase
//  146 *
//  147 *  Erase all memory to 0xFF
//  148 *
//  149 *****************************************************************************/
//  150 ee_err_t EEPROM_ChipErase(void)
//  151 {
//  152     uint8_t cmd[] = {0xC7, 0x94, 0x80, 0x9A};
//  153     while (EEPROM_isBusy());
//  154     
//  155     assert_cs();
//  156     spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
//  157     deassert_cs();
//  158 
//  159     return ee_ok;
//  160 }
//  161 
//  162 /*****************************************************************************
//  163 *  EEPROM_EraseBlock
//  164 *
//  165 *  Erase a block of memory to 0xFF
//  166 *
//  167 *****************************************************************************/
//  168 ee_err_t EEPROM_EraseBlock(uint32_t Addr, uint32_t size)
//  169 {
//  170     uint8_t cmd[4];
//  171     
//  172     while (EEPROM_isBusy());
//  173     
//  174     switch (size)
//  175     {
//  176     case EEPROM_BLOCK_SIZE:
//  177         cmd[0] = EEPROM_ERASE_4K;
//  178         break;
//  179     case EEPROM_PAGE_SIZE:
//  180         cmd[0] = EEPROM_ERASE_512B;
//  181         break;
//  182     default:
//  183         return ee_error;
//  184     }
//  185 
//  186     cmd[1] = (Addr >> 16) & ADDRESS_MASK;
//  187     cmd[2] = (Addr >>  8) & ADDRESS_MASK;
//  188     cmd[3] = (Addr >>  0) & ADDRESS_MASK;
//  189 
//  190     assert_cs();
//  191     spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
//  192     deassert_cs();
//  193     
//  194     return ee_ok;
//  195 }
//  196 
//  197 /*****************************************************************************
//  198 *  EEPROM_WriteData
//  199 *
//  200 *  Writes a data buffer into EEPROM, at a given address
//  201 *
//  202 *****************************************************************************/
//  203 #if gEepromWriteEnable_d
//  204 ee_err_t EEPROM_WriteData(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
//  205 {
//  206     ee_err_t retval;
//  207     
//  208     if (NoOfBytes == 0)
//  209         return ee_ok;
//  210     
//  211     while (EEPROM_isBusy());
//  212     
//  213     retval = EEPROM_PrepareForWrite(NoOfBytes, Addr);
//  214     if (retval != ee_ok)
//  215         return retval;
//  216     
//  217     while ((Addr & EEPROM_PAGE_MASK) + NoOfBytes > EEPROM_PAGE_MASK)
//  218     {
//  219         uint32_t bytes = EEPROM_PAGE_SIZE - (Addr & EEPROM_PAGE_MASK);
//  220         
//  221         retval = EEPROM_WritePage(bytes, Addr, Outbuf);
//  222         NoOfBytes -= bytes;
//  223         Addr += bytes;
//  224         Outbuf += bytes;
//  225         
//  226         if (retval != ee_ok)
//  227             return retval;
//  228     }
//  229     
//  230     retval = EEPROM_WritePage(NoOfBytes, Addr, Outbuf);
//  231     
//  232     return retval;
//  233 }
//  234 #endif
//  235 
//  236 /*****************************************************************************
//  237 *  EEPROM_ReadData
//  238 *
//  239 *  Reads a data buffer from EEPROM, from a given address
//  240 *
//  241 *****************************************************************************/
//  242 ee_err_t EEPROM_ReadData(uint16_t NoOfBytes, uint32_t Addr, uint8_t *inbuf)
//  243 {
//  244     
//  245     while (EEPROM_isBusy());
//  246     
//  247     EEPROM_Command(EEPROM_READ,Addr);
//  248     
//  249     spi_master_transfer(mEepromSpiInstance_c, NULL, inbuf, NoOfBytes);
//  250     deassert_cs();
//  251 
//  252     return ee_ok;
//  253 }
//  254 
//  255 /*****************************************************************************
//  256 *  EEPROM_ReadStatusReq
//  257 *
//  258 *
//  259 *****************************************************************************/
//  260 uint8_t EEPROM_isBusy(void)
//  261 {
//  262     return !(EEPROM_ReadStatusReq() & EEPROM_BUSY_FLAG_MASK);
//  263 }
//  264 
//  265 /*! *********************************************************************************
//  266 *************************************************************************************
//  267 * Private Functions
//  268 *************************************************************************************
//  269 ********************************************************************************** */
//  270 
//  271 /*****************************************************************************
//  272 *  EEPROM_ReadStatusReq
//  273 *
//  274 *
//  275 *****************************************************************************/
//  276 static uint16_t EEPROM_ReadStatusReq(void)
//  277 {
//  278     uint16_t status = EEPROM_RDSR;
//  279     
//  280     assert_cs();
//  281     spi_master_transfer(mEepromSpiInstance_c, (uint8_t*)&status, NULL, 1);
//  282     spi_master_transfer(mEepromSpiInstance_c, NULL, (uint8_t*)&status, 2);
//  283     deassert_cs();
//  284 
//  285     return status;
//  286 }
//  287 
//  288 /*****************************************************************************
//  289 *  EEPROM_WriteData
//  290 *
//  291 *  Writes a data buffer into the External Memory, at a given address
//  292 *
//  293 *****************************************************************************/
//  294 #if gEepromWriteEnable_d
//  295 static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr)
//  296 {
//  297     uint32_t i;
//  298     ee_err_t ret = ee_ok;
//  299     uint32_t startBlk, endBlk;
//  300     
//  301     // Obtain the block number
//  302     startBlk = Addr >> 12;
//  303     endBlk   = (Addr + NoOfBytes) >> 12;
//  304     
//  305     for(i = startBlk; i <= endBlk; i++)
//  306         if ( (mEepromEraseBitmap[i/8] & (1 << (i%8) ) ) == 0)
//  307         {
//  308             ret = EEPROM_EraseBlock(i * EEPROM_BLOCK_SIZE, EEPROM_BLOCK_SIZE);
//  309             if (ret != ee_ok)
//  310                 return ret;
//  311             
//  312             mEepromEraseBitmap[i/8] |= 1 << (i%8);
//  313             while (EEPROM_isBusy());
//  314         }
//  315     
//  316     return ret;
//  317 }
//  318 #endif
//  319 
//  320 /*****************************************************************************
//  321 *  EEPROM_WritePage
//  322 *
//  323 *  Writes maximum 256 bytes into a EEPROM page
//  324 *
//  325 *****************************************************************************/
//  326 #if gEepromWriteEnable_d
//  327 static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
//  328 {
//  329     
//  330     if (NoOfBytes == 0)
//  331         return ee_ok;
//  332     
//  333     while (EEPROM_isBusy());
//  334     
//  335     //SPI_Send_byte(EEPROM_WRITE_ENABLE,DEASSERT_CS);
//  336     
//  337     EEPROM_Command(EEPROM_WRITE_BYTES, Addr); //CS will remain ASSERTED
//  338 
//  339     spi_master_transfer(mEepromSpiInstance_c, Outbuf, NULL, NoOfBytes);
//  340     deassert_cs();
//  341     
//  342     return ee_ok;
//  343 }
//  344 #endif
//  345 
//  346 /*****************************************************************************
//  347 *  EEPROM_WaitForReady
//  348 *
//  349 *
//  350 *****************************************************************************/
//  351 static ee_err_t EEPROM_WaitForReady(void)
//  352 {
//  353     volatile uint16_t wait = 0x400; // near 50 ms @ 50 us/cycle
//  354     
//  355     /* Byte1 - Bit:   7       6      5:2       1         0
//  356     *             RDY/BUSY  COMP  DENSITY  PROTECT  PAGE_SIZE
//  357     *
//  358     * Byte2 - Bit:   7       6    5    4    3    2    1    0
//  359     *             RDY/BUSY  RES  EPE  RES  SLE  PS2  PS1  ES
//  360     */
//  361     
//  362     while( EEPROM_isBusy() && (wait !=0) )
//  363     {
//  364         wait--;
//  365     }
//  366     
//  367     if(wait != 0)
//  368     {
//  369         return ee_ok;
//  370     }
//  371     return ee_error;
//  372 }
//  373 
//  374 
//  375 /*****************************************************************************
//  376 *  EEPROM_Command
//  377 *
//  378 *
//  379 *****************************************************************************/
//  380 static void EEPROM_Command(uint8_t opCode, uint32_t Addr)
//  381 {
//  382     uint8_t cmd[4];
//  383     
//  384     cmd[0] = opCode;
//  385     cmd[1] = (Addr >> 16) & ADDRESS_MASK;
//  386     cmd[2] = (Addr >>  8) & ADDRESS_MASK;
//  387     cmd[3] = (Addr >>  0) & ADDRESS_MASK;
//  388     
//  389     assert_cs();
//  390     spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
//  391     /* CS will remain asserted to be able to send the data */
//  392 }
//  393 
//  394 #endif
//  395 /* EOF: Eeprom_AT45DB161E */ 
//  396 
// 
//
// 
//
//
//Errors: none
//Warnings: none
