/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file UartBootloader.c
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


#include "OtapBootloader.h"
#include "UartBootloader.h"
#include "flash_boot_kinetis.h"
#if gSerialBootloaderEnable_c
/******************************************************************************
*******************************************************************************
* Private Macros
*******************************************************************************
******************************************************************************/
/** Bootloader commands */
#define BOOT_CMD_IDENT 'I'
#define BOOT_CMD_WRITE 'W'
#define BOOT_CMD_ERASE 'E'
#define BOOT_CMD_ACK  0xFC
#define BOOT_CMD_NACK 0x03
#define BOOT_CMD_QUIT 'Q'
#define BOOT_CMD_READ 'R'

#define UART_SBR  (unsigned char)(BOOT_BUS_CLOCK / (16*BOOT_UART_BAUD_RATE))
#define UART_BRFA (unsigned char)((((BOOT_BUS_CLOCK/(16*BOOT_UART_BAUD_RATE))- \
                          UART_SBR)*32.0)+0.5)
#define UART_IsChar() (UART_S1_REG(BOOT_UART_BASE) & UART_S1_RDRF_MASK)
#define CRC_CCITT16_SEED 0xFFFF   
#define CRC_Init()  CRC_CTRL = 0;   
#define CRC_Reset() {CRC_CTRL |= CRC_CTRL_WAS_MASK; CRC_DATAL = CRC_CCITT16_SEED; CRC_CTRL &= ~CRC_CTRL_WAS_MASK;}   
#define CRC_AddByte(x) CRC_DATALL = (x)   
#define CRC_AddLong(x) CRC_DATA = (x)   
#define CRC_GetResult() CRC_DATAL   
#define CRC_GetResultHigh() CRC_DATALU
#define CRC_GetResultLow()  CRC_DATALL   
#define ConfigRxPinAsUart()    PORT_PCR_REG(BOOT_UART_GPIO_PORT_RX, BOOT_UART_GPIO_PIN_RX) = PORT_PCR_MUX(BOOT_PIN_UART_ALTERNATIVE) 
#define ConfigTxPinAsUart()    PORT_PCR_REG(BOOT_UART_GPIO_PORT_TX, BOOT_UART_GPIO_PIN_TX) = PORT_PCR_MUX(BOOT_PIN_UART_ALTERNATIVE)  
#define ConfigRxPinAsGpio()    PORT_PCR_REG(BOOT_UART_GPIO_PORT_RX, BOOT_UART_GPIO_PIN_RX) = PORT_PCR_MUX(BOOT_PIN_GPIO_ALTERNATIVE)| 3;
#define GPIO_RX_MASK   (0x01 << BOOT_UART_GPIO_PIN_RX)    

#define VERSION_KINETIS  8   
#define BOOTLOADER_PROTOCOL_VERSION VERSION_KINETIS   
// generate the bootloader protocol id with modification flags
#if (BOOTLOADER_ENABLE_READ_CMD != 0) && (BOOTLOADER_CRC_ENABLE != 0)
  #define _BOOTLOADER_PROTOCOL_VERSION BOOTLOADER_PROTOCOL_VERSION | 0xc0
#elif (BOOTLOADER_ENABLE_READ_CMD != 0)
  #define _BOOTLOADER_PROTOCOL_VERSION BOOTLOADER_PROTOCOL_VERSION | 0x80
#elif (BOOTLOADER_CRC_ENABLE != 0)
  #define _BOOTLOADER_PROTOCOL_VERSION BOOTLOADER_PROTOCOL_VERSION | 0x40
#else
  #define _BOOTLOADER_PROTOCOL_VERSION BOOTLOADER_PROTOCOL_VERSION
#endif

   /******************************************************************************
*******************************************************************************
* Private type definitions
*******************************************************************************
******************************************************************************/

   typedef union Address 
   {
     unsigned long complete;
     struct
     {
       uint16_t low;
       uint16_t high;        
     }Words;
     struct
     {
       uint8_t ll;
       uint8_t lh;
       uint8_t hl;
       uint8_t hh;
     }Bytes;
   }AddressType;

  
/** Flash block start and end address */

typedef PACKED_STRUCT FlashBlocksDesc
{
  uint32_t startAddr;
  uint32_t endAddr; 
}FlashBlocksDescType;
  	
/** Bootloader code optimized ident structure used for bootloader protocol */
typedef PACKED_STRUCT BootloaderIdentOptimType
{
  /** count of flash blocks */
  uint32_t blocksCnt;
  /** flash blocks descritor */
  FlashBlocksDescType blockDesc[FLASH_BLOCK_CNT];
  /** Relocated interrupts vestor table */
  uint32_t relocatedVectors;
  /** Interrupts vestor table */
  uint32_t interruptsVectors;
  /** Erase Block Size */
  uint32_t eraseBlockSize;
  /** Write Block Size */
  uint32_t writeBlockSize;
  /** Id string */
  uint8_t idString[sizeof(KINETIS_MODEL_STR)];      
}BootloaderIdentOptimType;
  
/******************************************************************************
*******************************************************************************
* Private Memory Declarations
*******************************************************************************
******************************************************************************/	

AddressType  crc_res;
AddressType address;
uint32_t length;
uint8_t write_buffer[256];
BootloaderIdentOptimType bootloaderIdent;   
/******************************************************************************
*******************************************************************************
* Private Prototypes
*******************************************************************************
******************************************************************************/
unsigned char UART_GetChar(void);

//-----------------------------------------------------------------------------
// FUNCTION:    Little2Big32
// SCOPE:       
// DESCRIPTION: self explanatory

//              
// PARAMETERS:  none
//              
// RETURNS:     none
//----------------------------------------------------------------------------- 

  static void Little2Big32(void* pData)
  {
  
  uint8_t* p8 = (uint8_t*)pData;
  *p8 ^= *(p8 + 3);
  *(p8 + 3) ^= *p8;
  *p8 ^= *(p8 + 3);
  *(p8 + 1) ^= *(p8 + 2);
  *(p8 + 2) ^= *(p8 + 1);
  *(p8 + 1) ^= *(p8 + 2);
  
  }
//-----------------------------------------------------------------------------
// FUNCTION:    InitIdentStruct
// SCOPE:       
// DESCRIPTION: The IAR routine that initializes Global variables is not called in this app,
//so this bootloaderIdent must be initialised explicitly. 

//              
// PARAMETERS:  none
//              
// RETURNS:     none
//----------------------------------------------------------------------------- 

  static void InitIdentStruct(void)
  {
  bootloaderIdent.blocksCnt = FLASH_BLOCK_CNT;
  Little2Big32(&bootloaderIdent.blocksCnt);
  bootloaderIdent.blockDesc[0].startAddr = gUserFlashStart_d;
  Little2Big32(&bootloaderIdent.blockDesc[0].startAddr);
  bootloaderIdent.blockDesc[0].endAddr = gMcuFlashSize_c - 1;
  Little2Big32(&bootloaderIdent.blockDesc[0].endAddr);
#if gMcuFlashBlocks_c == 2
  bootloaderIdent.blockDesc[1].startAddr = gUserFlash2Start_d;
  Little2Big32(&bootloaderIdent.blockDesc[1].startAddr);
  bootloaderIdent.blockDesc[1].endAddr = gMcuFlash2End_c;
  Little2Big32(&bootloaderIdent.blockDesc[1].endAddr);
#endif   
  bootloaderIdent.relocatedVectors = gUserFlashStart_d;
  Little2Big32(&bootloaderIdent.relocatedVectors);
  bootloaderIdent.interruptsVectors = 0;
  bootloaderIdent.eraseBlockSize = gFlashErasePage_c;
  Little2Big32(&bootloaderIdent.eraseBlockSize);
  bootloaderIdent.writeBlockSize = FLASH_WRITE_PAGE;
  Little2Big32(&bootloaderIdent.writeBlockSize);
  {
    uint8_t i;
    for (i=0;i< sizeof(bootloaderIdent.idString);i++)
    {
      bootloaderIdent.idString[i] = KINETIS_MODEL_STR[i];
    }
  }
  
  }


//-----------------------------------------------------------------------------
// FUNCTION:    ReadCrc
// SCOPE:       Bootloader application system function  
// DESCRIPTION: The functin reads the 2 bytes from IIC and store it to global crc variable

//              
// PARAMETERS:  none
//              
// RETURNS:     none
//----------------------------------------------------------------------------- 
#if BOOTLOADER_CRC_ENABLE == 1
  static void ReadCrc(void)
  {
    crc_res.Bytes.lh = UART_GetChar();
    crc_res.Bytes.ll = UART_GetChar();
  }
#endif

//-----------------------------------------------------------------------------
// FUNCTION:    ReadAddress
// SCOPE:       Bootloader application system function  
// DESCRIPTION: The functin reads the 4 bytes from IIC and store it to global address variable

//              
// PARAMETERS:  none
//              
// RETURNS:     none
//----------------------------------------------------------------------------- 
static void ReadAddress(void)
{
  address.Bytes.hh = UART_GetChar();
  address.Bytes.hl = UART_GetChar();
  address.Bytes.lh = UART_GetChar();
  address.Bytes.ll = UART_GetChar();
}  
// FUNCTION:    UART_PutChar
// SCOPE:       Bootloader application system function
// DESCRIPTION: 
//
// PARAMETERS:  none
//
// RETURNS:     none
//-----------------------------------------------------------------------------
void UART_PutChar(unsigned char data)
{
  while((UART_S1_REG(BOOT_UART_BASE)&UART_S1_TC_MASK) == 0){};
  UART_D_REG(BOOT_UART_BASE) = data;
}

// FUNCTION:    UART_GetChar
// SCOPE:       Bootloader application system function
// DESCRIPTION: 
//
// PARAMETERS:  none
//
// RETURNS:     none
//-----------------------------------------------------------------------------
unsigned char UART_GetChar(void)
{
  while(UART_IsChar() == 0)
  {
  }
  
  return UART_D_REG(BOOT_UART_BASE);
}

// FUNCTION:    UartInitialization
// SCOPE:       
// DESCRIPTION: 
//
// PARAMETERS:  none
//
// RETURNS:     none
//-----------------------------------------------------------------------------
void UartInitialization(void)
{
  BOOT_UART_SIM_SCG_REG |= BOOT_UART_SIM_SCG_MASK;
  UART_BDH_REG(BOOT_UART_BASE)     = ((UART_SBR>>8)&0x1f);
  UART_BDL_REG(BOOT_UART_BASE)     = (UART_SBR&0xff);
  UART_C4_REG(BOOT_UART_BASE)      = (UART_BRFA&0x1f);  
  UART_C2_REG(BOOT_UART_BASE)      = UART_C2_TE_MASK|UART_C2_RE_MASK;

  while(UART_IsChar())
    (void)UART_GetChar();
}
//----------------------------------------------------------------------------- 
static void SendResult(unsigned long res)
{ 
  if(!res)
    UART_PutChar(BOOT_CMD_ACK);
  else
    UART_PutChar(BOOT_CMD_NACK);
}

//-----------------------------------------------------------------------------
// FUNCTION:    SendResultCRC
// SCOPE:       Bootloader application system function
// DESCRIPTION: The function send the ACk or NACK with CRC (if enabled)
//              
// PARAMETERS:  res - TRUE/FALSE to send ACK or NACK
//              
// RETURNS:     none
//----------------------------------------------------------------------------- 
static void SendResultCRC(unsigned long res)
{ 
  SendResult(res);
  #if BOOTLOADER_CRC_ENABLE == 1
  if(!res)
  {
    UART_PutChar(0xcf);
    UART_PutChar(0x63);
  }else
  {
    UART_PutChar(0xd1);
    UART_PutChar(0x93);
  }
  #endif
}
//-----------------------------------------------------------------------------
// FUNCTION:    TrimmSettings
// SCOPE:       Trimming of Internal Oscilator 
// DESCRIPTION: This function measures break impulse from PC and sets correct trim value

//              
// PARAMETERS:  none
//              
// RETURNS:     none
//----------------------------------------------------------------------------- 

bool_t SlaveFrequencyCalibration(void)
{

  
  uint32_t fSbr;
  uint32_t iSbr;
  uint32_t sysTiks;
  uint8_t brfa;
  ConfigRxPinAsGpio(); 
  //  systick initialization
    
  SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK );
  SYST_RVR = 0xFFFFFF; // full range 0.8s for standard bus clock  = 32768Hz * 640 FLL / 2^24
  SYST_CVR = 0;
  SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_ENABLE_MASK);
  while(((GPIO_PDIR_REG(BOOT_CALIBRATION_GPIO_BASE) & GPIO_RX_MASK)) == 0)
  {
    if(SYST_CSR & SysTick_CSR_COUNTFLAG_MASK)
    {
      return FALSE;
    }
  }
  while(((GPIO_PDIR_REG(BOOT_CALIBRATION_GPIO_BASE) & GPIO_RX_MASK)))
  {
     if(SYST_CSR & SysTick_CSR_COUNTFLAG_MASK)
    {
      return FALSE;
    }
  }

  //(void)SYST_CSR;
   SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK );
   SYST_CVR = 0;
   SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_ENABLE_MASK);
   while((GPIO_PDIR_REG(BOOT_CALIBRATION_GPIO_BASE) & GPIO_RX_MASK) == 0)
  {
    if(SYST_CSR & SysTick_CSR_COUNTFLAG_MASK)
    {
      return FALSE;
    }
  }
  sysTiks = SYST_CVR;   
  sysTiks = SYST_RVR - sysTiks + 10;
 

#if BOOTLOADER_SHORT_TRIM
  #define BR_DIV (9*16)
#else
  #define BR_DIV (10*16)
#endif
  iSbr = sysTiks/BR_DIV;
  fSbr = sysTiks%BR_DIV;
  brfa = (unsigned char)((fSbr*32 + (BR_DIV>>1))/BR_DIV);
  UART_BDH_REG(BOOT_UART_BASE)     = (unsigned char)((iSbr>>8)&0x1f);
  UART_BDL_REG(BOOT_UART_BASE)     = (unsigned char)(iSbr&0xff);
  UART_C4_REG(BOOT_UART_BASE)      = (brfa&0x1f);  
  ConfigRxPinAsUart();
  return TRUE;
}

// FUNCTION:    CheckForUartLoader
// SCOPE:       Bootloader application system function
// DESCRIPTION: Check whether there is an UART loader available and if this is the case load the program from UART
//
// PARAMETERS:  none
//
// RETURNS:     none
//-----------------------------------------------------------------------------

void CheckForUartLoader(void)
{
  uint8_t i;
  BOOT_UART_GPIO_PORT_SIM_SCG_REG |= BOOT_UART_GPIO_PORT_SIM_SCG_MASK;
#if BOOTLOADER_CRC_ENABLE
  BOOT_CRC_SIM_SCG_REG |= BOOT_CRC_SIM_SCG_MASK;
#endif  
  ConfigRxPinAsUart();
  ConfigTxPinAsUart();
  UartInitialization();
  InitIdentStruct();
  SYST_RVR =  0xFFFFFF; // to do add macro to define the initial timeout
  SYST_CVR = 0;
  SYST_CSR = (SysTick_CSR_CLKSOURCE_MASK | SysTick_CSR_ENABLE_MASK);
  SendResult(0);   
  while(1)
  {
    if(UART_IsChar())
    {
      UART_GetChar();
      if( SlaveFrequencyCalibration() == FALSE )
      {
        return;
      }
      FlashInitialization(); 
#if BOOTLOADER_CRC_ENABLE == 1
      CRC_Init();    
#endif
      SendResult(0);
      break;
    }  
    if(SYST_CSR & SysTick_CSR_COUNTFLAG_MASK)
    {
      return;
    }
  }
  
  while(1)
  {
    // never ending loop - except quit commnad that disable  enableBootMode
    
#if BOOTLOADER_CRC_ENABLE == 1
    CRC_Reset();
#endif
    
    switch(UART_GetChar())
    {
    case BOOT_CMD_QUIT:                                 // QUIT command
#if BOOTLOADER_CRC_ENABLE == 1
      CRC_AddByte(BOOT_CMD_QUIT);  
      ReadCrc();
      if(crc_res.Words.low != CRC_GetResult())
      {            
        SendResultCRC(1);
        break;
      }
#endif
      
      // send the ack
      SendResultCRC(0);
      // reset MCU
      Boot_ResetMCU();
      
    case BOOT_CMD_ACK:
      SendResult(0);                                   // ACK command
      break;
      
    case BOOT_CMD_IDENT:                               // IDENT command
      //and send the all data with/without CRC 
#if BOOTLOADER_CRC_ENABLE == 1
      CRC_AddByte(BOOT_CMD_IDENT);  
      CRC_AddByte((uint8_t)_BOOTLOADER_PROTOCOL_VERSION);
#endif
      UART_PutChar((uint8_t)_BOOTLOADER_PROTOCOL_VERSION);
#if BOOTLOADER_CRC_ENABLE == 1
      CRC_AddByte(SIM_SDID >> 8);
#endif
      UART_PutChar(SIM_SDID >> 8); // high
#if BOOTLOADER_CRC_ENABLE == 1
      CRC_AddByte(SIM_SDID);
#endif
      UART_PutChar(SIM_SDID);      
      
      for(i=0; i < sizeof(bootloaderIdent); i++)
      {
#if BOOTLOADER_CRC_ENABLE == 1
        CRC_AddByte(((unsigned char*)&bootloaderIdent)[i]);
#endif              
        UART_PutChar(((unsigned char*)&bootloaderIdent)[i]);
      }
      
#if BOOTLOADER_CRC_ENABLE == 1
      UART_PutChar(CRC_GetResultHigh());         
      UART_PutChar(CRC_GetResultLow());
#endif
      
      break;
      
    case BOOT_CMD_ERASE:                                // ERASE command
      // Read Address
      ReadAddress();
      // Check the CRC
#if BOOTLOADER_CRC_ENABLE == 1
      
      CRC_AddByte(BOOT_CMD_ERASE);
      CRC_AddLong(address.complete);
      
      ReadCrc();
      if(crc_res.Words.low != CRC_GetResult())
      {            
        SendResultCRC(1);
        break;
      }
#endif
      // Erase the flash and send result
      SendResultCRC(FLASH_EraseSector(address.complete));
      break;
      
    case BOOT_CMD_WRITE:
      // Read Address                                                   // WRITE command
      ReadAddress();
      // Read length
      length = UART_GetChar();
      
#if BOOTLOADER_CRC_ENABLE == 1
      CRC_AddByte(BOOT_CMD_WRITE);
      CRC_AddLong(address.complete);
      CRC_AddByte((unsigned char)length);
#endif
      
      // Load the data to write
      for(i = 0;i<length; i++)
      {
        write_buffer[i] =  UART_GetChar(); 
#if BOOTLOADER_CRC_ENABLE == 1
        CRC_AddByte(write_buffer[i]);
#endif  
      }
      // check the CRC of input data
#if BOOTLOADER_CRC_ENABLE == 1
      ReadCrc();
      if(crc_res.Words.low != CRC_GetResult())
      {            
        SendResultCRC(1);
        break;
      }
#endif
      if(FLASH_Program(address.complete, (uint32_t)write_buffer, length))            
      {            
        SendResultCRC(1);
        break;
      }
      
      // Verify flashed data (if enabled)
#if BOOTLOADER_ENABLE_VERIFY == 1                 
      for(i = 0;i<length; i++)
      {              
        if((write_buffer)[i] != ((uint8_t*)address.complete)[i])
        {
          SendResultCRC(1);
          break;
        }
      }
#endif    
      SendResultCRC(0);
      break;
      
#if BOOTLOADER_ENABLE_READ_CMD == 1       
      
    case BOOT_CMD_READ:                                   // READ comamnd    
      ReadAddress();
      length = UART_GetChar();
      
#if BOOTLOADER_CRC_ENABLE == 1
      ReadCrc();
      
      CRC_AddByte(BOOT_CMD_READ);
      CRC_AddLong(address.complete);
      CRC_AddByte((unsigned char)length);
      
      if(crc_res.Words.low != CRC_GetResult())
      {            
        SendResultCRC(1);
        break;
      }
#endif
      
#if BOOTLOADER_CRC_ENABLE == 1
      CRC_Reset();
#endif
      
      for(i = 0;i<length; i++)
      {
#if BOOTLOADER_CRC_ENABLE == 1
        CRC_AddByte(((unsigned char*)(address.complete))[i]);
#endif              
        UART_PutChar(((unsigned char*)(address.complete))[i]); 
        
#if BOOTLOADER_INT_WATCHDOG == 1
        WDG_Refresh(); /* feeds the dog */
#endif
      }
      
#if BOOTLOADER_CRC_ENABLE == 1
      UART_PutChar(CRC_GetResultHigh());         
      UART_PutChar(CRC_GetResultLow());
#endif
      
      break;
      
#endif    
      
    }      
  }  
  
  
}
#endif// gSerialBootloaderEnable_c