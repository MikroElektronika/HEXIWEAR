///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.40.3.8902/W32 for ARM       12/Jan/2016  08:59:56
// Copyright 1999-2015 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\OtapSerialBootloader\UartBootloade.c
//    Command line =  
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\OtapSerialBootloader\UartBootloade.c
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
//        C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\BootloaderOTAP_KW40Z4\List\UartBootloade.s
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
// C:\Freescale\KW40Z_Connectivity_Software_1.0.1\ConnSw\framework\Bootloader\Bootloader_OTAP_Serial\src\OtapSerialBootloader\UartBootloade.c
//    1 /*!
//    2 * Copyright (c) 2015, Freescale Semiconductor, Inc.
//    3 * All rights reserved.
//    4 *
//    5 * \file UartBootloader.c
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
//   34 #include "OtapBootloader.h"
//   35 #include "UartBootloader.h"
//   36 #include "flash_boot_kinetis.h"
//   37 #if gSerialBootloaderEnable_c
//   38 /******************************************************************************
//   39 *******************************************************************************
//   40 * Private Macros
//   41 *******************************************************************************
//   42 ******************************************************************************/
//   43 /** Bootloader commands */
//   44 #define BOOT_CMD_IDENT 'I'
//   45 #define BOOT_CMD_WRITE 'W'
//   46 #define BOOT_CMD_ERASE 'E'
//   47 #define BOOT_CMD_ACK  0xFC
//   48 #define BOOT_CMD_NACK 0x03
//   49 #define BOOT_CMD_QUIT 'Q'
//   50 #define BOOT_CMD_READ 'R'
//   51 
//   52 #define UART_SBR  (unsigned char)(BOOT_BUS_CLOCK / (16*BOOT_UART_BAUD_RATE))
//   53 #define UART_BRFA (unsigned char)((((BOOT_BUS_CLOCK/(16*BOOT_UART_BAUD_RATE))- \ 
//   54                           UART_SBR)*32.0)+0.5)
//   55 #define UART_IsChar() (UART_S1_REG(BOOT_UART_BASE) & UART_S1_RDRF_MASK)
//   56 #define CRC_CCITT16_SEED 0xFFFF   
//   57 #define CRC_Init()  CRC_CTRL = 0;   
//   58 #define CRC_Reset() {CRC_CTRL |= CRC_CTRL_WAS_MASK; CRC_DATAL = CRC_CCITT16_SEED; CRC_CTRL &= ~CRC_CTRL_WAS_MASK;}   
//   59 #define CRC_AddByte(x) CRC_DATALL = (x)   
//   60 #define CRC_AddLong(x) CRC_DATA = (x)   
//   61 #define CRC_GetResult() CRC_DATAL   
//   62 #define CRC_GetResultHigh() CRC_DATALU
//   63 #define CRC_GetResultLow()  CRC_DATALL   
//   64 #define ConfigRxPinAsUart()    PORT_PCR_REG(BOOT_UART_GPIO_PORT_RX, BOOT_UART_GPIO_PIN_RX) = PORT_PCR_MUX(BOOT_PIN_UART_ALTERNATIVE) 
//   65 #define ConfigTxPinAsUart()    PORT_PCR_REG(BOOT_UART_GPIO_PORT_TX, BOOT_UART_GPIO_PIN_TX) = PORT_PCR_MUX(BOOT_PIN_UART_ALTERNATIVE)  
//   66 #define ConfigRxPinAsGpio()    PORT_PCR_REG(BOOT_UART_GPIO_PORT_RX, BOOT_UART_GPIO_PIN_RX) = PORT_PCR_MUX(BOOT_PIN_GPIO_ALTERNATIVE)| 3;
//   67 #define GPIO_RX_MASK   (0x01 << BOOT_UART_GPIO_PIN_RX)    
//   68 
//   69 #define VERSION_KINETIS  8   
//   70 #define BOOTLOADER_PROTOCOL_VERSION VERSION_KINETIS   
//   71 // generate the bootloader protocol id with modification flags
//   72 #if (BOOTLOADER_ENABLE_READ_CMD != 0) && (BOOTLOADER_CRC_ENABLE != 0)
//   73   #define _BOOTLOADER_PROTOCOL_VERSION BOOTLOADER_PROTOCOL_VERSION | 0xc0
//   74 #elif (BOOTLOADER_ENABLE_READ_CMD != 0)
//   75   #define _BOOTLOADER_PROTOCOL_VERSION BOOTLOADER_PROTOCOL_VERSION | 0x80
//   76 #elif (BOOTLOADER_CRC_ENABLE != 0)
//   77   #define _BOOTLOADER_PROTOCOL_VERSION BOOTLOADER_PROTOCOL_VERSION | 0x40
//   78 #else
//   79   #define _BOOTLOADER_PROTOCOL_VERSION BOOTLOADER_PROTOCOL_VERSION
//   80 #endif
//   81 
//   82    /******************************************************************************
//   83 *******************************************************************************
//   84 * Private type definitions
//   85 *******************************************************************************
//   86 ******************************************************************************/
//   87 
//   88    typedef union Address 
//   89    {
//   90      unsigned long complete;
//   91      struct
//   92      {
//   93        uint16_t low;
//   94        uint16_t high;        
//   95      }Words;
//   96      struct
//   97      {
//   98        uint8_t ll;
//   99        uint8_t lh;
//  100        uint8_t hl;
//  101        uint8_t hh;
//  102      }Bytes;
//  103    }AddressType;
//  104 
//  105   
//  106 /** Flash block start and end address */
//  107 
//  108 typedef PACKED_STRUCT FlashBlocksDesc
//  109 {
//  110   uint32_t startAddr;
//  111   uint32_t endAddr; 
//  112 }FlashBlocksDescType;
//  113   	
//  114 /** Bootloader code optimized ident structure used for bootloader protocol */
//  115 typedef PACKED_STRUCT BootloaderIdentOptimType
//  116 {
//  117   /** count of flash blocks */
//  118   uint32_t blocksCnt;
//  119   /** flash blocks descritor */
//  120   FlashBlocksDescType blockDesc[FLASH_BLOCK_CNT];
//  121   /** Relocated interrupts vestor table */
//  122   uint32_t relocatedVectors;
//  123   /** Interrupts vestor table */
//  124   uint32_t interruptsVectors;
//  125   /** Erase Block Size */
//  126   uint32_t eraseBlockSize;
//  127   /** Write Block Size */
//  128   uint32_t writeBlockSize;
//  129   /** Id string */
//  130   uint8_t idString[sizeof(KINETIS_MODEL_STR)];      
//  131 }BootloaderIdentOptimType;
//  132   
//  133 /******************************************************************************
//  134 *******************************************************************************
//  135 * Private Memory Declarations
//  136 *******************************************************************************
//  137 ******************************************************************************/	
//  138 
//  139 AddressType  crc_res;
//  140 AddressType address;
//  141 uint32_t length;
//  142 uint8_t write_buffer[256];
//  143 BootloaderIdentOptimType bootloaderIdent;   
//  144 /******************************************************************************
//  145 *******************************************************************************
//  146 * Private Prototypes
//  147 *******************************************************************************
//  148 ******************************************************************************/
//  149 unsigned char UART_GetChar(void);
//  150 
//  151 //-----------------------------------------------------------------------------
//  152 // FUNCTION:    Little2Big32
//  153 // SCOPE:       
//  154 // DESCRIPTION: self explanatory
//  155 
//  156 //              
//  157 // PARAMETERS:  none
//  158 //              
//  159 // RETURNS:     none
//  160 //----------------------------------------------------------------------------- 
//  161 
//  162   static void Little2Big32(void* pData)
//  163   {
//  164   
//  165   uint8_t* p8 = (uint8_t*)pData;
//  166   *p8 ^= *(p8 + 3);
//  167   *(p8 + 3) ^= *p8;
//  168   *p8 ^= *(p8 + 3);
//  169   *(p8 + 1) ^= *(p8 + 2);
//  170   *(p8 + 2) ^= *(p8 + 1);
//  171   *(p8 + 1) ^= *(p8 + 2);
//  172   
//  173   }
//  174 //-----------------------------------------------------------------------------
//  175 // FUNCTION:    InitIdentStruct
//  176 // SCOPE:       
//  177 // DESCRIPTION: The IAR routine that initializes Global variables is not called in this app,
//  178 //so this bootloaderIdent must be initialised explicitly. 
//  179 
//  180 //              
//  181 // PARAMETERS:  none
//  182 //              
//  183 // RETURNS:     none
//  184 //----------------------------------------------------------------------------- 
//  185 
//  186   static void InitIdentStruct(void)
//  187   {
//  188   bootloaderIdent.blocksCnt = FLASH_BLOCK_CNT;
//  189   Little2Big32(&bootloaderIdent.blocksCnt);
//  190   bootloaderIdent.blockDesc[0].startAddr = gUserFlashStart_d;
//  191   Little2Big32(&bootloaderIdent.blockDesc[0].startAddr);
//  192   bootloaderIdent.blockDesc[0].endAddr = gMcuFlashSize_c - 1;
//  193   Little2Big32(&bootloaderIdent.blockDesc[0].endAddr);
//  194 #if gMcuFlashBlocks_c == 2
//  195   bootloaderIdent.blockDesc[1].startAddr = gUserFlash2Start_d;
//  196   Little2Big32(&bootloaderIdent.blockDesc[1].startAddr);
//  197   bootloaderIdent.blockDesc[1].endAddr = gMcuFlash2End_c;
//  198   Little2Big32(&bootloaderIdent.blockDesc[1].endAddr);
//  199 #endif   
//  200   bootloaderIdent.relocatedVectors = gUserFlashStart_d;
//  201   Little2Big32(&bootloaderIdent.relocatedVectors);
//  202   bootloaderIdent.interruptsVectors = 0;
//  203   bootloaderIdent.eraseBlockSize = gFlashErasePage_c;
//  204   Little2Big32(&bootloaderIdent.eraseBlockSize);
//  205   bootloaderIdent.writeBlockSize = FLASH_WRITE_PAGE;
//  206   Little2Big32(&bootloaderIdent.writeBlockSize);
//  207   {
//  208     uint8_t i;
//  209     for (i=0;i< sizeof(bootloaderIdent.idString);i++)
//  210     {
//  211       bootloaderIdent.idString[i] = KINETIS_MODEL_STR[i];
//  212     }
//  213   }
//  214   
//  215   }
//  216 
//  217 
//  218 //-----------------------------------------------------------------------------
//  219 // FUNCTION:    ReadCrc
//  220 // SCOPE:       Bootloader application system function  
//  221 // DESCRIPTION: The functin reads the 2 bytes from IIC and store it to global crc variable
//  222 
//  223 //              
//  224 // PARAMETERS:  none
//  225 //              
//  226 // RETURNS:     none
//  227 //----------------------------------------------------------------------------- 
//  228 #if BOOTLOADER_CRC_ENABLE == 1
//  229   static void ReadCrc(void)
//  230   {
//  231     crc_res.Bytes.lh = UART_GetChar();
//  232     crc_res.Bytes.ll = UART_GetChar();
//  233   }
//  234 #endif
//  235 
//  236 //-----------------------------------------------------------------------------
//  237 // FUNCTION:    ReadAddress
//  238 // SCOPE:       Bootloader application system function  
//  239 // DESCRIPTION: The functin reads the 4 bytes from IIC and store it to global address variable
//  240 
//  241 //              
//  242 // PARAMETERS:  none
//  243 //              
//  244 // RETURNS:     none
//  245 //----------------------------------------------------------------------------- 
//  246 static void ReadAddress(void)
//  247 {
//  248   address.Bytes.hh = UART_GetChar();
//  249   address.Bytes.hl = UART_GetChar();
//  250   address.Bytes.lh = UART_GetChar();
//  251   address.Bytes.ll = UART_GetChar();
//  252 }  
//  253 // FUNCTION:    UART_PutChar
//  254 // SCOPE:       Bootloader application system function
//  255 // DESCRIPTION: 
//  256 //
//  257 // PARAMETERS:  none
//  258 //
//  259 // RETURNS:     none
//  260 //-----------------------------------------------------------------------------
//  261 void UART_PutChar(unsigned char data)
//  262 {
//  263   while((UART_S1_REG(BOOT_UART_BASE)&UART_S1_TC_MASK) == 0){};
//  264   UART_D_REG(BOOT_UART_BASE) = data;
//  265 }
//  266 
//  267 // FUNCTION:    UART_GetChar
//  268 // SCOPE:       Bootloader application system function
//  269 // DESCRIPTION: 
//  270 //
//  271 // PARAMETERS:  none
//  272 //
//  273 // RETURNS:     none
//  274 //-----------------------------------------------------------------------------
//  275 unsigned char UART_GetChar(void)
//  276 {
//  277   while(UART_IsChar() == 0)
//  278   {
//  279   }
//  280   
//  281   return UART_D_REG(BOOT_UART_BASE);
//  282 }
//  283 
//  284 // FUNCTION:    UartInitialization
//  285 // SCOPE:       
//  286 // DESCRIPTION: 
//  287 //
//  288 // PARAMETERS:  none
//  289 //
//  290 // RETURNS:     none
//  291 //-----------------------------------------------------------------------------
//  292 void UartInitialization(void)
//  293 {
//  294   BOOT_UART_SIM_SCG_REG |= BOOT_UART_SIM_SCG_MASK;
//  295   UART_BDH_REG(BOOT_UART_BASE)     = ((UART_SBR>>8)&0x1f);
//  296   UART_BDL_REG(BOOT_UART_BASE)     = (UART_SBR&0xff);
//  297   UART_C4_REG(BOOT_UART_BASE)      = (UART_BRFA&0x1f);  
//  298   UART_C2_REG(BOOT_UART_BASE)      = UART_C2_TE_MASK|UART_C2_RE_MASK;
//  299 
//  300   while(UART_IsChar())
//  301     (void)UART_GetChar();
//  302 }
//  303 //----------------------------------------------------------------------------- 
//  304 static void SendResult(unsigned long res)
//  305 { 
//  306   if(!res)
//  307     UART_PutChar(BOOT_CMD_ACK);
//  308   else
//  309     UART_PutChar(BOOT_CMD_NACK);
//  310 }
//  311 
//  312 //-----------------------------------------------------------------------------
//  313 // FUNCTION:    SendResultCRC
//  314 // SCOPE:       Bootloader application system function
//  315 // DESCRIPTION: The function send the ACk or NACK with CRC (if enabled)
//  316 //              
//  317 // PARAMETERS:  res - TRUE/FALSE to send ACK or NACK
//  318 //              
//  319 // RETURNS:     none
//  320 //----------------------------------------------------------------------------- 
//  321 static void SendResultCRC(unsigned long res)
//  322 { 
//  323   SendResult(res);
//  324   #if BOOTLOADER_CRC_ENABLE == 1
//  325   if(!res)
//  326   {
//  327     UART_PutChar(0xcf);
//  328     UART_PutChar(0x63);
//  329   }else
//  330   {
//  331     UART_PutChar(0xd1);
//  332     UART_PutChar(0x93);
//  333   }
//  334   #endif
//  335 }
//  336 //-----------------------------------------------------------------------------
//  337 // FUNCTION:    TrimmSettings
//  338 // SCOPE:       Trimming of Internal Oscilator 
//  339 // DESCRIPTION: This function measures break impulse from PC and sets correct trim value
//  340 
//  341 //              
//  342 // PARAMETERS:  none
//  343 //              
//  344 // RETURNS:     none
//  345 //----------------------------------------------------------------------------- 
//  346 
//  347 bool_t SlaveFrequencyCalibration(void)
//  348 {
//  349 
//  350   
//  351   uint32_t fSbr;
//  352   uint32_t iSbr;
//  353   uint32_t sysTiks;
//  354   uint8_t brfa;
//  355   ConfigRxPinAsGpio(); 
//  356   //  systick initialization
//  357     
//  358   SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK );
//  359   SYST_RVR = 0xFFFFFF; // full range 0.8s for standard bus clock  = 32768Hz * 640 FLL / 2^24
//  360   SYST_CVR = 0;
//  361   SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_ENABLE_MASK);
//  362   while(((GPIO_PDIR_REG(BOOT_CALIBRATION_GPIO_BASE) & GPIO_RX_MASK)) == 0)
//  363   {
//  364     if(SYST_CSR & SysTick_CSR_COUNTFLAG_MASK)
//  365     {
//  366       return FALSE;
//  367     }
//  368   }
//  369   while(((GPIO_PDIR_REG(BOOT_CALIBRATION_GPIO_BASE) & GPIO_RX_MASK)))
//  370   {
//  371      if(SYST_CSR & SysTick_CSR_COUNTFLAG_MASK)
//  372     {
//  373       return FALSE;
//  374     }
//  375   }
//  376 
//  377   //(void)SYST_CSR;
//  378    SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK );
//  379    SYST_CVR = 0;
//  380    SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_ENABLE_MASK);
//  381    while((GPIO_PDIR_REG(BOOT_CALIBRATION_GPIO_BASE) & GPIO_RX_MASK) == 0)
//  382   {
//  383     if(SYST_CSR & SysTick_CSR_COUNTFLAG_MASK)
//  384     {
//  385       return FALSE;
//  386     }
//  387   }
//  388   sysTiks = SYST_CVR;   
//  389   sysTiks = SYST_RVR - sysTiks + 10;
//  390  
//  391 
//  392 #if BOOTLOADER_SHORT_TRIM
//  393   #define BR_DIV (9*16)
//  394 #else
//  395   #define BR_DIV (10*16)
//  396 #endif
//  397   iSbr = sysTiks/BR_DIV;
//  398   fSbr = sysTiks%BR_DIV;
//  399   brfa = (unsigned char)((fSbr*32 + (BR_DIV>>1))/BR_DIV);
//  400   UART_BDH_REG(BOOT_UART_BASE)     = (unsigned char)((iSbr>>8)&0x1f);
//  401   UART_BDL_REG(BOOT_UART_BASE)     = (unsigned char)(iSbr&0xff);
//  402   UART_C4_REG(BOOT_UART_BASE)      = (brfa&0x1f);  
//  403   ConfigRxPinAsUart();
//  404   return TRUE;
//  405 }
//  406 
//  407 // FUNCTION:    CheckForUartLoader
//  408 // SCOPE:       Bootloader application system function
//  409 // DESCRIPTION: Check whether there is an UART loader available and if this is the case load the program from UART
//  410 //
//  411 // PARAMETERS:  none
//  412 //
//  413 // RETURNS:     none
//  414 //-----------------------------------------------------------------------------
//  415 
//  416 void CheckForUartLoader(void)
//  417 {
//  418   uint8_t i;
//  419   BOOT_UART_GPIO_PORT_SIM_SCG_REG |= BOOT_UART_GPIO_PORT_SIM_SCG_MASK;
//  420 #if BOOTLOADER_CRC_ENABLE
//  421   BOOT_CRC_SIM_SCG_REG |= BOOT_CRC_SIM_SCG_MASK;
//  422 #endif  
//  423   ConfigRxPinAsUart();
//  424   ConfigTxPinAsUart();
//  425   UartInitialization();
//  426   InitIdentStruct();
//  427   SYST_RVR =  0xFFFFFF; // to do add macro to define the initial timeout
//  428   SYST_CVR = 0;
//  429   SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_ENABLE_MASK);
//  430   SendResult(0);   
//  431   while(1)
//  432   {
//  433     if(UART_IsChar())
//  434     {
//  435       UART_GetChar();
//  436       if( SlaveFrequencyCalibration() == FALSE )
//  437       {
//  438         return;
//  439       }
//  440       FlashInitialization(); 
//  441 #if BOOTLOADER_CRC_ENABLE == 1
//  442       CRC_Init();    
//  443 #endif
//  444       SendResult(0);
//  445       break;
//  446     }  
//  447     if(SYST_CSR & SysTick_CSR_COUNTFLAG_MASK)
//  448     {
//  449       return;
//  450     }
//  451   }
//  452   
//  453   while(1)
//  454   {
//  455     // never ending loop - except quit commnad that disable  enableBootMode
//  456     
//  457 #if BOOTLOADER_CRC_ENABLE == 1
//  458     CRC_Reset();
//  459 #endif
//  460     
//  461     switch(UART_GetChar())
//  462     {
//  463     case BOOT_CMD_QUIT:                                 // QUIT command
//  464 #if BOOTLOADER_CRC_ENABLE == 1
//  465       CRC_AddByte(BOOT_CMD_QUIT);  
//  466       ReadCrc();
//  467       if(crc_res.Words.low != CRC_GetResult())
//  468       {            
//  469         SendResultCRC(1);
//  470         break;
//  471       }
//  472 #endif
//  473       
//  474       // send the ack
//  475       SendResultCRC(0);
//  476       // reset MCU
//  477       Boot_ResetMCU();
//  478       
//  479     case BOOT_CMD_ACK:
//  480       SendResult(0);                                   // ACK command
//  481       break;
//  482       
//  483     case BOOT_CMD_IDENT:                               // IDENT command
//  484       //and send the all data with/without CRC 
//  485 #if BOOTLOADER_CRC_ENABLE == 1
//  486       CRC_AddByte(BOOT_CMD_IDENT);  
//  487       CRC_AddByte((uint8_t)_BOOTLOADER_PROTOCOL_VERSION);
//  488 #endif
//  489       UART_PutChar((uint8_t)_BOOTLOADER_PROTOCOL_VERSION);
//  490 #if BOOTLOADER_CRC_ENABLE == 1
//  491       CRC_AddByte(SIM_SDID >> 8);
//  492 #endif
//  493       UART_PutChar(SIM_SDID >> 8); // high
//  494 #if BOOTLOADER_CRC_ENABLE == 1
//  495       CRC_AddByte(SIM_SDID);
//  496 #endif
//  497       UART_PutChar(SIM_SDID);      
//  498       
//  499       for(i=0; i < sizeof(bootloaderIdent); i++)
//  500       {
//  501 #if BOOTLOADER_CRC_ENABLE == 1
//  502         CRC_AddByte(((unsigned char*)&bootloaderIdent)[i]);
//  503 #endif              
//  504         UART_PutChar(((unsigned char*)&bootloaderIdent)[i]);
//  505       }
//  506       
//  507 #if BOOTLOADER_CRC_ENABLE == 1
//  508       UART_PutChar(CRC_GetResultHigh());         
//  509       UART_PutChar(CRC_GetResultLow());
//  510 #endif
//  511       
//  512       break;
//  513       
//  514     case BOOT_CMD_ERASE:                                // ERASE command
//  515       // Read Address
//  516       ReadAddress();
//  517       // Check the CRC
//  518 #if BOOTLOADER_CRC_ENABLE == 1
//  519       
//  520       CRC_AddByte(BOOT_CMD_ERASE);
//  521       CRC_AddLong(address.complete);
//  522       
//  523       ReadCrc();
//  524       if(crc_res.Words.low != CRC_GetResult())
//  525       {            
//  526         SendResultCRC(1);
//  527         break;
//  528       }
//  529 #endif
//  530       // Erase the flash and send result
//  531       SendResultCRC(FLASH_EraseSector(address.complete));
//  532       break;
//  533       
//  534     case BOOT_CMD_WRITE:
//  535       // Read Address                                                   // WRITE command
//  536       ReadAddress();
//  537       // Read length
//  538       length = UART_GetChar();
//  539       
//  540 #if BOOTLOADER_CRC_ENABLE == 1
//  541       CRC_AddByte(BOOT_CMD_WRITE);
//  542       CRC_AddLong(address.complete);
//  543       CRC_AddByte((unsigned char)length);
//  544 #endif
//  545       
//  546       // Load the data to write
//  547       for(i = 0;i<length; i++)
//  548       {
//  549         write_buffer[i] =  UART_GetChar(); 
//  550 #if BOOTLOADER_CRC_ENABLE == 1
//  551         CRC_AddByte(write_buffer[i]);
//  552 #endif  
//  553       }
//  554       // check the CRC of input data
//  555 #if BOOTLOADER_CRC_ENABLE == 1
//  556       ReadCrc();
//  557       if(crc_res.Words.low != CRC_GetResult())
//  558       {            
//  559         SendResultCRC(1);
//  560         break;
//  561       }
//  562 #endif
//  563       if(FLASH_Program(address.complete, (uint32_t)write_buffer, length))            
//  564       {            
//  565         SendResultCRC(1);
//  566         break;
//  567       }
//  568       
//  569       // Verify flashed data (if enabled)
//  570 #if BOOTLOADER_ENABLE_VERIFY == 1                 
//  571       for(i = 0;i<length; i++)
//  572       {              
//  573         if((write_buffer)[i] != ((uint8_t*)address.complete)[i])
//  574         {
//  575           SendResultCRC(1);
//  576           break;
//  577         }
//  578       }
//  579 #endif    
//  580       SendResultCRC(0);
//  581       break;
//  582       
//  583 #if BOOTLOADER_ENABLE_READ_CMD == 1       
//  584       
//  585     case BOOT_CMD_READ:                                   // READ comamnd    
//  586       ReadAddress();
//  587       length = UART_GetChar();
//  588       
//  589 #if BOOTLOADER_CRC_ENABLE == 1
//  590       ReadCrc();
//  591       
//  592       CRC_AddByte(BOOT_CMD_READ);
//  593       CRC_AddLong(address.complete);
//  594       CRC_AddByte((unsigned char)length);
//  595       
//  596       if(crc_res.Words.low != CRC_GetResult())
//  597       {            
//  598         SendResultCRC(1);
//  599         break;
//  600       }
//  601 #endif
//  602       
//  603 #if BOOTLOADER_CRC_ENABLE == 1
//  604       CRC_Reset();
//  605 #endif
//  606       
//  607       for(i = 0;i<length; i++)
//  608       {
//  609 #if BOOTLOADER_CRC_ENABLE == 1
//  610         CRC_AddByte(((unsigned char*)(address.complete))[i]);
//  611 #endif              
//  612         UART_PutChar(((unsigned char*)(address.complete))[i]); 
//  613         
//  614 #if BOOTLOADER_INT_WATCHDOG == 1
//  615         WDG_Refresh(); /* feeds the dog */
//  616 #endif
//  617       }
//  618       
//  619 #if BOOTLOADER_CRC_ENABLE == 1
//  620       UART_PutChar(CRC_GetResultHigh());         
//  621       UART_PutChar(CRC_GetResultLow());
//  622 #endif
//  623       
//  624       break;
//  625       
//  626 #endif    
//  627       
//  628     }      
//  629   }  
//  630   
//  631   
//  632 }
//  633 #endif// gSerialBootloaderEnable_c
// 
//
// 
//
//
//Errors: none
//Warnings: none
