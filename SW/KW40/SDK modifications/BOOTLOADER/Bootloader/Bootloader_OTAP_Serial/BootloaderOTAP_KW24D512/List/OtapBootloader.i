#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.c"
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
#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file OtapBootloader.h
* OTAP Bootloader interface file
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
#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\EmbeddedTypes.h"
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file EmbeddedTypes.h
* This file contains basic types definition
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









/************************************************************************************
*
*       TYPE DEFINITIONS
*
************************************************************************************/
#line 57 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\EmbeddedTypes.h"


typedef signed    char  int8_t;
typedef unsigned  char  uint8_t;
typedef signed    short int16_t;
typedef unsigned  short uint16_t;
typedef signed    long  int32_t;
typedef unsigned  long  uint32_t;
typedef signed    long long int64_t;
typedef unsigned  long long uint64_t;

typedef signed    char  intn8_t;
typedef unsigned  char  uintn8_t;
typedef signed    short intn16_t;
typedef unsigned  short uintn16_t;
typedef signed    long  intn32_t;
typedef unsigned  long  uintn32_t;
typedef signed    long long intn64_t;
typedef unsigned  long long uintn64_t;

typedef volatile signed char vint8_t;
typedef volatile unsigned char vuint8_t;
typedef volatile signed short vint16_t;
typedef volatile unsigned short vuint16_t;
typedef volatile signed long vint32_t;
typedef volatile unsigned long vuint32_t;

/* boolean types */
typedef uint8_t   bool_t;
typedef uintn8_t  booln_t;
/* used for indexing into an array in the most efficient manner for the platform */
typedef uint8_t   index_t;








/* If parameters of CONCAT() are macros, a second level of indirection is required to get them to expand */








#line 44 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"
#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\eeprom\\Eeprom_Boot.h"
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file Eeprom.h
* This is the header file for the Eeprom driver.
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






/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */


/* List of the EEPROM devices used on each of the FSL development boards */






/* Default EEPROM type used */




/* Characteristics of the EEPROM device */





  















/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
typedef enum
{
  ee_ok,
  ee_too_big,
  ee_not_aligned,
  ee_busy,
  ee_error
} ee_err_t;


/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */

/******************************************************************************
*  This function initialises the port pins and the EEPROM
*
* Interface assumptions:
*
*
* Return value: ee_err_t
*
******************************************************************************/
ee_err_t EEPROM_Init
(
  void /*IN: No Input Parameters*/
);


/******************************************************************************
*  This function Reads x bytes from the EEPROM
*
* Interface assumptions:
*
*
* Return value: ee_err_t
*
******************************************************************************/
ee_err_t EEPROM_ReadData
(
  uint16_t NoOfBytes,/* IN: No of bytes to read */
  uint32_t Addr,		 /* IN: EEPROM address to start reading from */
  uint8_t  *inbuf		 /* OUT:Pointer to read buffer */
);

/******************************************************************************
*  This function writes x bytes to the EEPROM
*
* Interface assumptions:
*
*
* Return value: ee_err_t
*
******************************************************************************/
ee_err_t EEPROM_WriteData
(
  uint32_t  NoOfBytes,/* IN: No of bytes to write */
  uint32_t Addr,		 /* IN: EEPROM address to start writing at. */
  uint8_t  *Outbuf	 /* IN: Pointer to data to write to EEPROM  */
);

/******************************************************************************
*  This function tests if the EEPROM is busy.
*
* Interface assumptions:
*
*
* Return value: TRUE if EEPROM is busy or FALSE if EEPROM is ready(idle)
*
******************************************************************************/
uint8_t EEPROM_isBusy
(
  void /*IN: No Input Parameters*/
);


/******************************************************************************
*  This function erase 4Kbytes of memory
*
* Interface assumptions:
*
*
* Return value: ee_err_t
*
******************************************************************************/
ee_err_t EEPROM_EraseBlock
(
  uint32_t Addr, /* IN: EEPROM address within the 4Kbyte block to be erased. */
  uint32_t size
);


/******************************************************************************
*  This function erase all memory
*
* Interface assumptions:
*
*
* Return value: ee_err_t
*
******************************************************************************/
ee_err_t EEPROM_ChipErase
(
  void /*IN: No Input Parameters*/
);









#line 45 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"

#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/*
** ###################################################################
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    K21RM, Rev.4, Feb 2013
**     Version:             rev. 1.6, 2013-06-24
**
**     Abstract:
**         This header file implements peripheral memory map for MK21D5
**         processor.
**
**     Copyright: 1997 - 2013 Freescale, Inc. All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2012-06-06)
**         Initial public version.
**     - rev. 1.1 (2012-07-31)
**         Fixed address of SIM_SDID register.
**     - rev. 1.2 (2012-08-29)
**         Update to Rev. 3 of reference manual.
**         Updated UART0 and CRC register definition.
**         VREF module definition removed.
**     - rev. 1.3 (2012-10-11)
**         PDB module update - PDB0_PO1DLY register added.
**     - rev. 1.4 (2013-01-24)
**         Update to Rev. 4 of reference manual.
**         ETB registers removed.
**     - rev. 1.5 (2013-04-05)
**         Changed start of doxygen comment.
**     - rev. 1.6 (2013-06-24)
**         NV_FOPT register - NMI_DIS bit added.
**
** ###################################################################
*/

/*!
 * @file MK21D5.h
 * @version 1.6
 * @date 2013-06-24
 * @brief Peripheral memory map for MK21D5
 *
 * This header file implements peripheral memory map for MK21D5 processor.
 */


/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */



/* Check if another memory map has not been also included */







/** Memory map major version (memory maps with equal major version number are
 * compatible) */

/** Memory map minor version */


/**
 * @brief Macro to access a single bit of a peripheral register (bit band region
 *        0x40000000 to 0x400FFFFF) using the bit-band alias region access.
 * @param Reg Register to access.
 * @param Bit Bit number to access.
 * @return Value of the targeted bit in the bit band region.
 */


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
typedef enum {
  INT_Initial_Stack_Pointer    = 0,                /**< Initial Stack Pointer */
  INT_Initial_Program_Counter  = 1,                /**< Initial Program Counter */
  INT_NMI                      = 2,                /**< Non-maskable Interrupt (NMI) */
  INT_Hard_Fault               = 3,                /**< Hard Fault */
  INT_Mem_Manage_Fault         = 4,                /**< MemManage Fault */
  INT_Bus_Fault                = 5,                /**< Bus Fault */
  INT_Usage_Fault              = 6,                /**< Usage Fault */
  INT_Reserved7                = 7,                /**< Reserved interrupt 7 */
  INT_Reserved8                = 8,                /**< Reserved interrupt 8 */
  INT_Reserved9                = 9,                /**< Reserved interrupt 9 */
  INT_Reserved10               = 10,               /**< Reserved interrupt 10 */
  INT_SVCall                   = 11,               /**< Supervisor call (SVCall) */
  INT_DebugMonitor             = 12,               /**< Debug Monitor */
  INT_Reserved13               = 13,               /**< Reserved interrupt 13 */
  INT_PendableSrvReq           = 14,               /**< Pendable request for system service (PendableSrvReq) */
  INT_SysTick                  = 15,               /**< SysTick Interrupt */
  INT_DMA0                     = 16,               /**< DMA Channel 0 Transfer Complete */
  INT_DMA1                     = 17,               /**< DMA Channel 1 Transfer Complete */
  INT_DMA2                     = 18,               /**< DMA Channel 2 Transfer Complete */
  INT_DMA3                     = 19,               /**< DMA Channel 3 Transfer Complete */
  INT_DMA4                     = 20,               /**< DMA Channel 4 Transfer Complete */
  INT_DMA5                     = 21,               /**< DMA Channel 5 Transfer Complete */
  INT_DMA6                     = 22,               /**< DMA Channel 6 Transfer Complete */
  INT_DMA7                     = 23,               /**< DMA Channel 7 Transfer Complete */
  INT_DMA8                     = 24,               /**< DMA Channel 8 Transfer Complete */
  INT_DMA9                     = 25,               /**< DMA Channel 9 Transfer Complete */
  INT_DMA10                    = 26,               /**< DMA Channel 10 Transfer Complete */
  INT_DMA11                    = 27,               /**< DMA Channel 11 Transfer Complete */
  INT_DMA12                    = 28,               /**< DMA Channel 12 Transfer Complete */
  INT_DMA13                    = 29,               /**< DMA Channel 13 Transfer Complete */
  INT_DMA14                    = 30,               /**< DMA Channel 14 Transfer Complete */
  INT_DMA15                    = 31,               /**< DMA Channel 15 Transfer Complete */
  INT_DMA_Error                = 32,               /**< DMA Error Interrupt */
  INT_MCM                      = 33,               /**< Normal Interrupt */
  INT_FTFL                     = 34,               /**< FTFL Command complete interrupt */
  INT_Read_Collision           = 35,               /**< Read Collision Interrupt */
  INT_LVD_LVW                  = 36,               /**< Low Voltage Detect, Low Voltage Warning */
  INT_LLW                      = 37,               /**< Low Leakage Wakeup */
  INT_Watchdog                 = 38,               /**< WDOG Interrupt */
  INT_RNG                      = 39,               /**< RNG Interrupt */
  INT_I2C0                     = 40,               /**< I2C0 interrupt */
  INT_I2C1                     = 41,               /**< I2C1 interrupt */
  INT_SPI0                     = 42,               /**< SPI0 Interrupt */
  INT_SPI1                     = 43,               /**< SPI1 Interrupt */
  INT_I2S0_Tx                  = 44,               /**< I2S0 transmit interrupt */
  INT_I2S0_Rx                  = 45,               /**< I2S0 receive interrupt */
  INT_UART0_LON                = 46,               /**< UART0 LON interrupt */
  INT_UART0_RX_TX              = 47,               /**< UART0 Receive/Transmit interrupt */
  INT_UART0_ERR                = 48,               /**< UART0 Error interrupt */
  INT_UART1_RX_TX              = 49,               /**< UART1 Receive/Transmit interrupt */
  INT_UART1_ERR                = 50,               /**< UART1 Error interrupt */
  INT_UART2_RX_TX              = 51,               /**< UART2 Receive/Transmit interrupt */
  INT_UART2_ERR                = 52,               /**< UART2 Error interrupt */
  INT_UART3_RX_TX              = 53,               /**< UART3 Receive/Transmit interrupt */
  INT_UART3_ERR                = 54,               /**< UART3 Error interrupt */
  INT_ADC0                     = 55,               /**< ADC0 interrupt */
  INT_CMP0                     = 56,               /**< CMP0 interrupt */
  INT_CMP1                     = 57,               /**< CMP1 interrupt */
  INT_FTM0                     = 58,               /**< FTM0 fault, overflow and channels interrupt */
  INT_FTM1                     = 59,               /**< FTM1 fault, overflow and channels interrupt */
  INT_FTM2                     = 60,               /**< FTM2 fault, overflow and channels interrupt */
  INT_CMT                      = 61,               /**< CMT interrupt */
  INT_RTC                      = 62,               /**< RTC interrupt */
  INT_RTC_Seconds              = 63,               /**< RTC seconds interrupt */
  INT_PIT0                     = 64,               /**< PIT timer channel 0 interrupt */
  INT_PIT1                     = 65,               /**< PIT timer channel 1 interrupt */
  INT_PIT2                     = 66,               /**< PIT timer channel 2 interrupt */
  INT_PIT3                     = 67,               /**< PIT timer channel 3 interrupt */
  INT_PDB0                     = 68,               /**< PDB0 Interrupt */
  INT_USB0                     = 69,               /**< USB0 interrupt */
  INT_USBDCD                   = 70,               /**< USBDCD Interrupt */
  INT_Reserved71               = 71,               /**< Reserved interrupt 71 */
  INT_DAC0                     = 72,               /**< DAC0 interrupt */
  INT_MCG                      = 73,               /**< MCG Interrupt */
  INT_LPTimer                  = 74,               /**< LPTimer interrupt */
  INT_PORTA                    = 75,               /**< Port A interrupt */
  INT_PORTB                    = 76,               /**< Port B interrupt */
  INT_PORTC                    = 77,               /**< Port C interrupt */
  INT_PORTD                    = 78,               /**< Port D interrupt */
  INT_PORTE                    = 79,               /**< Port E interrupt */
  INT_SWI                      = 80                /**< Software interrupt */
} IRQInterruptIndex;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Peripheral type defines
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_defines Peripheral type defines
 * @{
 */


/*
** Start of section using anonymous unions
*/

#line 205 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
  #pragma language=extended




/* ----------------------------------------------------------------------------
   -- ADC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral ADC
 * @{
 */

/** ADC - Peripheral register structure */
typedef struct ADC_MemMap {
  uint32_t SC1[2];                                 /**< ADC Status and Control Registers 1, array offset: 0x0, array step: 0x4 */
  uint32_t CFG1;                                   /**< ADC Configuration Register 1, offset: 0x8 */
  uint32_t CFG2;                                   /**< ADC Configuration Register 2, offset: 0xC */
  uint32_t R[2];                                   /**< ADC Data Result Register, array offset: 0x10, array step: 0x4 */
  uint32_t CV1;                                    /**< Compare Value Registers, offset: 0x18 */
  uint32_t CV2;                                    /**< Compare Value Registers, offset: 0x1C */
  uint32_t SC2;                                    /**< Status and Control Register 2, offset: 0x20 */
  uint32_t SC3;                                    /**< Status and Control Register 3, offset: 0x24 */
  uint32_t OFS;                                    /**< ADC Offset Correction Register, offset: 0x28 */
  uint32_t PG;                                     /**< ADC Plus-Side Gain Register, offset: 0x2C */
  uint32_t MG;                                     /**< ADC Minus-Side Gain Register, offset: 0x30 */
  uint32_t CLPD;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x34 */
  uint32_t CLPS;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x38 */
  uint32_t CLP4;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x3C */
  uint32_t CLP3;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x40 */
  uint32_t CLP2;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x44 */
  uint32_t CLP1;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x48 */
  uint32_t CLP0;                                   /**< ADC Plus-Side General Calibration Value Register, offset: 0x4C */
  uint8_t RESERVED_0[4];
  uint32_t CLMD;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x54 */
  uint32_t CLMS;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x58 */
  uint32_t CLM4;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x5C */
  uint32_t CLM3;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x60 */
  uint32_t CLM2;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x64 */
  uint32_t CLM1;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x68 */
  uint32_t CLM0;                                   /**< ADC Minus-Side General Calibration Value Register, offset: 0x6C */
} volatile *ADC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register accessors */
#line 285 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/* SC1 Bit Fields */
#line 310 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CFG1 Bit Fields */
#line 324 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CFG2 Bit Fields */
#line 334 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* R Bit Fields */



/* CV1 Bit Fields */



/* CV2 Bit Fields */



/* SC2 Bit Fields */
#line 362 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SC3 Bit Fields */
#line 374 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* OFS Bit Fields */



/* PG Bit Fields */



/* MG Bit Fields */



/* CLPD Bit Fields */



/* CLPS Bit Fields */



/* CLP4 Bit Fields */



/* CLP3 Bit Fields */



/* CLP2 Bit Fields */



/* CLP1 Bit Fields */



/* CLP0 Bit Fields */



/* CLMD Bit Fields */



/* CLMS Bit Fields */



/* CLM4 Bit Fields */



/* CLM3 Bit Fields */



/* CLM2 Bit Fields */



/* CLM1 Bit Fields */



/* CLM0 Bit Fields */




/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base pointer */

/** Array initializer of ADC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register instance definitions */
/* ADC0 */
#line 493 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* ADC - Register array accessors */



/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ADC_Peripheral */


/* ----------------------------------------------------------------------------
   -- AIPS
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Peripheral AIPS
 * @{
 */

/** AIPS - Peripheral register structure */
typedef struct AIPS_MemMap {
  uint32_t MPRA;                                   /**< Master Privilege Register A, offset: 0x0 */
  uint8_t RESERVED_0[28];
  uint32_t PACRA;                                  /**< Peripheral Access Control Register, offset: 0x20 */
  uint32_t PACRB;                                  /**< Peripheral Access Control Register, offset: 0x24 */
  uint32_t PACRC;                                  /**< Peripheral Access Control Register, offset: 0x28 */
  uint32_t PACRD;                                  /**< Peripheral Access Control Register, offset: 0x2C */
  uint8_t RESERVED_1[16];
  uint32_t PACRE;                                  /**< Peripheral Access Control Register, offset: 0x40 */
  uint32_t PACRF;                                  /**< Peripheral Access Control Register, offset: 0x44 */
  uint32_t PACRG;                                  /**< Peripheral Access Control Register, offset: 0x48 */
  uint32_t PACRH;                                  /**< Peripheral Access Control Register, offset: 0x4C */
  uint32_t PACRI;                                  /**< Peripheral Access Control Register, offset: 0x50 */
  uint32_t PACRJ;                                  /**< Peripheral Access Control Register, offset: 0x54 */
  uint32_t PACRK;                                  /**< Peripheral Access Control Register, offset: 0x58 */
  uint32_t PACRL;                                  /**< Peripheral Access Control Register, offset: 0x5C */
  uint32_t PACRM;                                  /**< Peripheral Access Control Register, offset: 0x60 */
  uint32_t PACRN;                                  /**< Peripheral Access Control Register, offset: 0x64 */
  uint32_t PACRO;                                  /**< Peripheral Access Control Register, offset: 0x68 */
  uint32_t PACRP;                                  /**< Peripheral Access Control Register, offset: 0x6C */
} volatile *AIPS_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- AIPS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Register_Accessor_Macros AIPS - Register accessor macros
 * @{
 */


/* AIPS - Register accessors */
#line 568 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group AIPS_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- AIPS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Register_Masks AIPS Register Masks
 * @{
 */

/* PACRA Bit Fields */
#line 632 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRB Bit Fields */
#line 681 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRC Bit Fields */
#line 730 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRD Bit Fields */
#line 779 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRE Bit Fields */
#line 828 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRF Bit Fields */
#line 877 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRG Bit Fields */
#line 926 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRH Bit Fields */
#line 975 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRI Bit Fields */
#line 1024 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRJ Bit Fields */
#line 1073 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRK Bit Fields */
#line 1122 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRL Bit Fields */
#line 1171 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRM Bit Fields */
#line 1220 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRN Bit Fields */
#line 1269 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRO Bit Fields */
#line 1318 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PACRP Bit Fields */
#line 1367 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group AIPS_Register_Masks */


/* AIPS - Peripheral instance base addresses */
/** Peripheral AIPS0 base pointer */

/** Array initializer of AIPS peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- AIPS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Register_Accessor_Macros AIPS - Register accessor macros
 * @{
 */


/* AIPS - Register instance definitions */
/* AIPS0 */
#line 1408 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group AIPS_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group AIPS_Peripheral */


/* ----------------------------------------------------------------------------
   -- CAU
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Peripheral CAU
 * @{
 */

/** CAU - Peripheral register structure */
typedef struct CAU_MemMap {
  uint32_t DIRECT[16];                             /**< Direct access register 0..Direct access register 15, array offset: 0x0, array step: 0x4 */
  uint8_t RESERVED_0[2048];
  uint32_t LDR_CASR;                               /**< Status register  - Load Register command, offset: 0x840 */
  uint32_t LDR_CAA;                                /**< Accumulator register - Load Register command, offset: 0x844 */
  uint32_t LDR_CA[9];                              /**< General Purpose Register 0 - Load Register command..General Purpose Register 8 - Load Register command, array offset: 0x848, array step: 0x4 */
  uint8_t RESERVED_1[20];
  uint32_t STR_CASR;                               /**< Status register  - Store Register command, offset: 0x880 */
  uint32_t STR_CAA;                                /**< Accumulator register - Store Register command, offset: 0x884 */
  uint32_t STR_CA[9];                              /**< General Purpose Register 0 - Store Register command..General Purpose Register 8 - Store Register command, array offset: 0x888, array step: 0x4 */
  uint8_t RESERVED_2[20];
  uint32_t ADR_CASR;                               /**< Status register  - Add Register command, offset: 0x8C0 */
  uint32_t ADR_CAA;                                /**< Accumulator register - Add to register command, offset: 0x8C4 */
  uint32_t ADR_CA[9];                              /**< General Purpose Register 0 - Add to register command..General Purpose Register 8 - Add to register command, array offset: 0x8C8, array step: 0x4 */
  uint8_t RESERVED_3[20];
  uint32_t RADR_CASR;                              /**< Status register  - Reverse and Add to Register command, offset: 0x900 */
  uint32_t RADR_CAA;                               /**< Accumulator register - Reverse and Add to Register command, offset: 0x904 */
  uint32_t RADR_CA[9];                             /**< General Purpose Register 0 - Reverse and Add to Register command..General Purpose Register 8 - Reverse and Add to Register command, array offset: 0x908, array step: 0x4 */
  uint8_t RESERVED_4[84];
  uint32_t XOR_CASR;                               /**< Status register  - Exclusive Or command, offset: 0x980 */
  uint32_t XOR_CAA;                                /**< Accumulator register - Exclusive Or command, offset: 0x984 */
  uint32_t XOR_CA[9];                              /**< General Purpose Register 0 - Exclusive Or command..General Purpose Register 8 - Exclusive Or command, array offset: 0x988, array step: 0x4 */
  uint8_t RESERVED_5[20];
  uint32_t ROTL_CASR;                              /**< Status register  - Rotate Left command, offset: 0x9C0 */
  uint32_t ROTL_CAA;                               /**< Accumulator register - Rotate Left command, offset: 0x9C4 */
  uint32_t ROTL_CA[9];                             /**< General Purpose Register 0 - Rotate Left command..General Purpose Register 8 - Rotate Left command, array offset: 0x9C8, array step: 0x4 */
  uint8_t RESERVED_6[276];
  uint32_t AESC_CASR;                              /**< Status register  - AES Column Operation command, offset: 0xB00 */
  uint32_t AESC_CAA;                               /**< Accumulator register - AES Column Operation command, offset: 0xB04 */
  uint32_t AESC_CA[9];                             /**< General Purpose Register 0 - AES Column Operation command..General Purpose Register 8 - AES Column Operation command, array offset: 0xB08, array step: 0x4 */
  uint8_t RESERVED_7[20];
  uint32_t AESIC_CASR;                             /**< Status register  - AES Inverse Column Operation command, offset: 0xB40 */
  uint32_t AESIC_CAA;                              /**< Accumulator register - AES Inverse Column Operation command, offset: 0xB44 */
  uint32_t AESIC_CA[9];                            /**< General Purpose Register 0 - AES Inverse Column Operation command..General Purpose Register 8 - AES Inverse Column Operation command, array offset: 0xB48, array step: 0x4 */
} volatile *CAU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CAU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Register_Accessor_Macros CAU - Register accessor macros
 * @{
 */


/* CAU - Register accessors */
#line 1501 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CAU_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CAU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Register_Masks CAU Register Masks
 * @{
 */

/* LDR_CASR Bit Fields */
#line 1524 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* STR_CASR Bit Fields */
#line 1532 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ADR_CASR Bit Fields */
#line 1540 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RADR_CASR Bit Fields */
#line 1548 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* XOR_CASR Bit Fields */
#line 1556 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ROTL_CASR Bit Fields */
#line 1564 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* AESC_CASR Bit Fields */
#line 1572 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* AESIC_CASR Bit Fields */
#line 1580 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CAU_Register_Masks */


/* CAU - Peripheral instance base addresses */
/** Peripheral CAU base pointer */

/** Array initializer of CAU peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- CAU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAU_Register_Accessor_Macros CAU - Register accessor macros
 * @{
 */


/* CAU - Register instance definitions */
/* CAU */
#line 1708 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* CAU - Register array accessors */
#line 1719 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CAU_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CAU_Peripheral */


/* ----------------------------------------------------------------------------
   -- CMP
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Peripheral CMP
 * @{
 */

/** CMP - Peripheral register structure */
typedef struct CMP_MemMap {
  uint8_t CR0;                                     /**< CMP Control Register 0, offset: 0x0 */
  uint8_t CR1;                                     /**< CMP Control Register 1, offset: 0x1 */
  uint8_t FPR;                                     /**< CMP Filter Period Register, offset: 0x2 */
  uint8_t SCR;                                     /**< CMP Status and Control Register, offset: 0x3 */
  uint8_t DACCR;                                   /**< DAC Control Register, offset: 0x4 */
  uint8_t MUXCR;                                   /**< MUX Control Register, offset: 0x5 */
} volatile *CMP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Accessor_Macros CMP - Register accessor macros
 * @{
 */


/* CMP - Register accessors */
#line 1766 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CMP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Masks CMP Register Masks
 * @{
 */

/* CR0 Bit Fields */
#line 1788 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CR1 Bit Fields */
#line 1803 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FPR Bit Fields */



/* SCR Bit Fields */
#line 1820 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DACCR Bit Fields */
#line 1828 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* MUXCR Bit Fields */
#line 1837 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CMP_Register_Masks */


/* CMP - Peripheral instance base addresses */
/** Peripheral CMP0 base pointer */

/** Peripheral CMP1 base pointer */

/** Array initializer of CMP peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- CMP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Accessor_Macros CMP - Register accessor macros
 * @{
 */


/* CMP - Register instance definitions */
/* CMP0 */
#line 1869 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CMP1 */
#line 1876 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CMP_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CMP_Peripheral */


/* ----------------------------------------------------------------------------
   -- CMT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMT_Peripheral CMT
 * @{
 */

/** CMT - Peripheral register structure */
typedef struct CMT_MemMap {
  uint8_t CGH1;                                    /**< CMT Carrier Generator High Data Register 1, offset: 0x0 */
  uint8_t CGL1;                                    /**< CMT Carrier Generator Low Data Register 1, offset: 0x1 */
  uint8_t CGH2;                                    /**< CMT Carrier Generator High Data Register 2, offset: 0x2 */
  uint8_t CGL2;                                    /**< CMT Carrier Generator Low Data Register 2, offset: 0x3 */
  uint8_t OC;                                      /**< CMT Output Control Register, offset: 0x4 */
  uint8_t MSC;                                     /**< CMT Modulator Status and Control Register, offset: 0x5 */
  uint8_t CMD1;                                    /**< CMT Modulator Data Register Mark High, offset: 0x6 */
  uint8_t CMD2;                                    /**< CMT Modulator Data Register Mark Low, offset: 0x7 */
  uint8_t CMD3;                                    /**< CMT Modulator Data Register Space High, offset: 0x8 */
  uint8_t CMD4;                                    /**< CMT Modulator Data Register Space Low, offset: 0x9 */
  uint8_t PPS;                                     /**< CMT Primary Prescaler Register, offset: 0xA */
  uint8_t DMA;                                     /**< CMT Direct Memory Access Register, offset: 0xB */
} volatile *CMT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CMT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMT_Register_Accessor_Macros CMT - Register accessor macros
 * @{
 */


/* CMT - Register accessors */
#line 1935 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CMT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CMT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMT_Register_Masks CMT Register Masks
 * @{
 */

/* CGH1 Bit Fields */



/* CGL1 Bit Fields */



/* CGH2 Bit Fields */



/* CGL2 Bit Fields */



/* OC Bit Fields */
#line 1973 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* MSC Bit Fields */
#line 1989 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CMD1 Bit Fields */



/* CMD2 Bit Fields */



/* CMD3 Bit Fields */



/* CMD4 Bit Fields */



/* PPS Bit Fields */



/* DMA Bit Fields */



/*!
 * @}
 */ /* end of group CMT_Register_Masks */


/* CMT - Peripheral instance base addresses */
/** Peripheral CMT base pointer */

/** Array initializer of CMT peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- CMT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMT_Register_Accessor_Macros CMT - Register accessor macros
 * @{
 */


/* CMT - Register instance definitions */
/* CMT */
#line 2048 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CMT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CMT_Peripheral */


/* ----------------------------------------------------------------------------
   -- CRC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Peripheral CRC
 * @{
 */

/** CRC - Peripheral register structure */
typedef struct CRC_MemMap {
  union {                                          /* offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      uint16_t DATAL;                                  /**< CRC_DATAL register., offset: 0x0 */
      uint16_t DATAH;                                  /**< CRC_DATAH register., offset: 0x2 */
    } ACCESS16BIT;
    uint32_t DATA;                                   /**< CRC Data register, offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      uint8_t DATALL;                                  /**< CRC_DATALL register., offset: 0x0 */
      uint8_t DATALU;                                  /**< CRC_DATALU register., offset: 0x1 */
      uint8_t DATAHL;                                  /**< CRC_DATAHL register., offset: 0x2 */
      uint8_t DATAHU;                                  /**< CRC_DATAHU register., offset: 0x3 */
    } ACCESS8BIT;
  };
  union {                                          /* offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint16_t GPOLYL;                                 /**< CRC_GPOLYL register., offset: 0x4 */
      uint16_t GPOLYH;                                 /**< CRC_GPOLYH register., offset: 0x6 */
    } GPOLY_ACCESS16BIT;
    uint32_t GPOLY;                                  /**< CRC Polynomial register, offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      uint8_t GPOLYLL;                                 /**< CRC_GPOLYLL register., offset: 0x4 */
      uint8_t GPOLYLU;                                 /**< CRC_GPOLYLU register., offset: 0x5 */
      uint8_t GPOLYHL;                                 /**< CRC_GPOLYHL register., offset: 0x6 */
      uint8_t GPOLYHU;                                 /**< CRC_GPOLYHU register., offset: 0x7 */
    } GPOLY_ACCESS8BIT;
  };
  union {                                          /* offset: 0x8 */
    uint32_t CTRL;                                   /**< CRC Control register, offset: 0x8 */
    struct {                                         /* offset: 0x8 */
      uint8_t RESERVED_0[3];
      uint8_t CTRLHU;                                  /**< CRC_CTRLHU register., offset: 0xB */
    } CTRL_ACCESS8BIT;
  };
} volatile *CRC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register accessors */
#line 2132 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */

/* DATAL Bit Fields */



/* DATAH Bit Fields */



/* DATA Bit Fields */
#line 2168 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DATALL Bit Fields */



/* DATALU Bit Fields */



/* DATAHL Bit Fields */



/* DATAHU Bit Fields */



/* GPOLYL Bit Fields */



/* GPOLYH Bit Fields */



/* GPOLY Bit Fields */
#line 2199 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* GPOLYLL Bit Fields */



/* GPOLYLU Bit Fields */



/* GPOLYHL Bit Fields */



/* GPOLYHU Bit Fields */



/* CTRL Bit Fields */
#line 2228 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CTRLHU Bit Fields */
#line 2241 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CRC_Register_Masks */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base pointer */

/** Array initializer of CRC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- CRC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Accessor_Macros CRC - Register accessor macros
 * @{
 */


/* CRC - Register instance definitions */
/* CRC */
#line 2281 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group CRC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CRC_Peripheral */


/* ----------------------------------------------------------------------------
   -- CoreDebug
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Peripheral CoreDebug
 * @{
 */

/** CoreDebug - Peripheral register structure */
typedef struct CoreDebug_MemMap {
  union {                                          /* offset: 0x0 */
    uint32_t base_DHCSR_Read;                        /**< Debug Halting Control and Status Register, offset: 0x0 */
    uint32_t base_DHCSR_Write;                       /**< Debug Halting Control and Status Register, offset: 0x0 */
  };
  uint32_t base_DCRSR;                             /**< Debug Core Register Selector Register, offset: 0x4 */
  uint32_t base_DCRDR;                             /**< Debug Core Register Data Register, offset: 0x8 */
  uint32_t base_DEMCR;                             /**< Debug Exception and Monitor Control Register, offset: 0xC */
} volatile *CoreDebug_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register accessors */






/*!
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- CoreDebug Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Masks CoreDebug Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group CoreDebug_Register_Masks */


/* CoreDebug - Peripheral instance base addresses */
/** Peripheral CoreDebug base pointer */

/** Array initializer of CoreDebug peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- CoreDebug - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CoreDebug_Register_Accessor_Macros CoreDebug - Register accessor macros
 * @{
 */


/* CoreDebug - Register instance definitions */
/* CoreDebug */






/*!
 * @}
 */ /* end of group CoreDebug_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CoreDebug_Peripheral */


/* ----------------------------------------------------------------------------
   -- DAC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Peripheral DAC
 * @{
 */

/** DAC - Peripheral register structure */
typedef struct DAC_MemMap {
  struct {                                         /* offset: 0x0, array step: 0x2 */
    uint8_t DATL;                                    /**< DAC Data Low Register, array offset: 0x0, array step: 0x2 */
    uint8_t DATH;                                    /**< DAC Data High Register, array offset: 0x1, array step: 0x2 */
  } DAT[16];
  uint8_t SR;                                      /**< DAC Status Register, offset: 0x20 */
  uint8_t C0;                                      /**< DAC Control Register, offset: 0x21 */
  uint8_t C1;                                      /**< DAC Control Register 1, offset: 0x22 */
  uint8_t C2;                                      /**< DAC Control Register 2, offset: 0x23 */
} volatile *DAC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DAC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Register_Accessor_Macros DAC - Register accessor macros
 * @{
 */


/* DAC - Register accessors */
#line 2421 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group DAC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DAC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Register_Masks DAC Register Masks
 * @{
 */

/* DATL Bit Fields */



/* DATH Bit Fields */



/* SR Bit Fields */
#line 2451 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C0 Bit Fields */
#line 2468 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C1 Bit Fields */
#line 2479 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C2 Bit Fields */
#line 2486 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group DAC_Register_Masks */


/* DAC - Peripheral instance base addresses */
/** Peripheral DAC0 base pointer */

/** Array initializer of DAC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- DAC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Register_Accessor_Macros DAC - Register accessor macros
 * @{
 */


/* DAC - Register instance definitions */
/* DAC0 */
#line 2546 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* DAC - Register array accessors */



/*!
 * @}
 */ /* end of group DAC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DAC_Peripheral */


/* ----------------------------------------------------------------------------
   -- DMA
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral DMA
 * @{
 */

/** DMA - Peripheral register structure */
typedef struct DMA_MemMap {
  uint32_t CR;                                     /**< Control Register, offset: 0x0 */
  uint32_t ES;                                     /**< Error Status Register, offset: 0x4 */
  uint8_t RESERVED_0[4];
  uint32_t ERQ;                                    /**< Enable Request Register, offset: 0xC */
  uint8_t RESERVED_1[4];
  uint32_t EEI;                                    /**< Enable Error Interrupt Register, offset: 0x14 */
  uint8_t CEEI;                                    /**< Clear Enable Error Interrupt Register, offset: 0x18 */
  uint8_t SEEI;                                    /**< Set Enable Error Interrupt Register, offset: 0x19 */
  uint8_t CERQ;                                    /**< Clear Enable Request Register, offset: 0x1A */
  uint8_t SERQ;                                    /**< Set Enable Request Register, offset: 0x1B */
  uint8_t CDNE;                                    /**< Clear DONE Status Bit Register, offset: 0x1C */
  uint8_t SSRT;                                    /**< Set START Bit Register, offset: 0x1D */
  uint8_t CERR;                                    /**< Clear Error Register, offset: 0x1E */
  uint8_t CINT;                                    /**< Clear Interrupt Request Register, offset: 0x1F */
  uint8_t RESERVED_2[4];
  uint32_t INT;                                    /**< Interrupt Request Register, offset: 0x24 */
  uint8_t RESERVED_3[4];
  uint32_t ERR;                                    /**< Error Register, offset: 0x2C */
  uint8_t RESERVED_4[4];
  uint32_t HRS;                                    /**< Hardware Request Status Register, offset: 0x34 */
  uint8_t RESERVED_5[200];
  uint8_t DCHPRI3;                                 /**< Channel n Priority Register, offset: 0x100 */
  uint8_t DCHPRI2;                                 /**< Channel n Priority Register, offset: 0x101 */
  uint8_t DCHPRI1;                                 /**< Channel n Priority Register, offset: 0x102 */
  uint8_t DCHPRI0;                                 /**< Channel n Priority Register, offset: 0x103 */
  uint8_t DCHPRI7;                                 /**< Channel n Priority Register, offset: 0x104 */
  uint8_t DCHPRI6;                                 /**< Channel n Priority Register, offset: 0x105 */
  uint8_t DCHPRI5;                                 /**< Channel n Priority Register, offset: 0x106 */
  uint8_t DCHPRI4;                                 /**< Channel n Priority Register, offset: 0x107 */
  uint8_t DCHPRI11;                                /**< Channel n Priority Register, offset: 0x108 */
  uint8_t DCHPRI10;                                /**< Channel n Priority Register, offset: 0x109 */
  uint8_t DCHPRI9;                                 /**< Channel n Priority Register, offset: 0x10A */
  uint8_t DCHPRI8;                                 /**< Channel n Priority Register, offset: 0x10B */
  uint8_t DCHPRI15;                                /**< Channel n Priority Register, offset: 0x10C */
  uint8_t DCHPRI14;                                /**< Channel n Priority Register, offset: 0x10D */
  uint8_t DCHPRI13;                                /**< Channel n Priority Register, offset: 0x10E */
  uint8_t DCHPRI12;                                /**< Channel n Priority Register, offset: 0x10F */
  uint8_t RESERVED_6[3824];
  struct {                                         /* offset: 0x1000, array step: 0x20 */
    uint32_t SADDR;                                  /**< TCD Source Address, array offset: 0x1000, array step: 0x20 */
    uint16_t SOFF;                                   /**< TCD Signed Source Address Offset, array offset: 0x1004, array step: 0x20 */
    uint16_t ATTR;                                   /**< TCD Transfer Attributes, array offset: 0x1006, array step: 0x20 */
    union {                                          /* offset: 0x1008, array step: 0x20 */
      uint32_t NBYTES_MLNO;                            /**< TCD Minor Byte Count (Minor Loop Disabled), array offset: 0x1008, array step: 0x20 */
      uint32_t NBYTES_MLOFFNO;                         /**< TCD Signed Minor Loop Offset (Minor Loop Enabled and Offset Disabled), array offset: 0x1008, array step: 0x20 */
      uint32_t NBYTES_MLOFFYES;                        /**< TCD Signed Minor Loop Offset (Minor Loop and Offset Enabled), array offset: 0x1008, array step: 0x20 */
    };
    uint32_t SLAST;                                  /**< TCD Last Source Address Adjustment, array offset: 0x100C, array step: 0x20 */
    uint32_t DADDR;                                  /**< TCD Destination Address, array offset: 0x1010, array step: 0x20 */
    uint16_t DOFF;                                   /**< TCD Signed Destination Address Offset, array offset: 0x1014, array step: 0x20 */
    union {                                          /* offset: 0x1016, array step: 0x20 */
      uint16_t CITER_ELINKNO;                          /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x1016, array step: 0x20 */
      uint16_t CITER_ELINKYES;                         /**< TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x1016, array step: 0x20 */
    };
    uint32_t DLAST_SGA;                              /**< TCD Last Destination Address Adjustment/Scatter Gather Address, array offset: 0x1018, array step: 0x20 */
    uint16_t CSR;                                    /**< TCD Control and Status, array offset: 0x101C, array step: 0x20 */
    union {                                          /* offset: 0x101E, array step: 0x20 */
      uint16_t BITER_ELINKNO;                          /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled), array offset: 0x101E, array step: 0x20 */
      uint16_t BITER_ELINKYES;                         /**< TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled), array offset: 0x101E, array step: 0x20 */
    };
  } TCD[16];
} volatile *DMA_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DMA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Accessor_Macros DMA - Register accessor macros
 * @{
 */


/* DMA - Register accessors */
#line 2692 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group DMA_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/* CR Bit Fields */
#line 2724 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ES Bit Fields */
#line 2750 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ERQ Bit Fields */
#line 2783 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* EEI Bit Fields */
#line 2816 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CEEI Bit Fields */
#line 2824 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SEEI Bit Fields */
#line 2832 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CERQ Bit Fields */
#line 2840 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SERQ Bit Fields */
#line 2848 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CDNE Bit Fields */
#line 2856 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SSRT Bit Fields */
#line 2864 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CERR Bit Fields */
#line 2872 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CINT Bit Fields */
#line 2880 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* INT Bit Fields */
#line 2913 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ERR Bit Fields */
#line 2946 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* HRS Bit Fields */
#line 2979 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI3 Bit Fields */
#line 2987 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI2 Bit Fields */
#line 2995 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI1 Bit Fields */
#line 3003 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI0 Bit Fields */
#line 3011 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI7 Bit Fields */
#line 3019 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI6 Bit Fields */
#line 3027 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI5 Bit Fields */
#line 3035 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI4 Bit Fields */
#line 3043 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI11 Bit Fields */
#line 3051 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI10 Bit Fields */
#line 3059 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI9 Bit Fields */
#line 3067 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI8 Bit Fields */
#line 3075 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI15 Bit Fields */
#line 3083 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI14 Bit Fields */
#line 3091 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI13 Bit Fields */
#line 3099 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DCHPRI12 Bit Fields */
#line 3107 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SADDR Bit Fields */



/* SOFF Bit Fields */



/* ATTR Bit Fields */
#line 3128 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* NBYTES_MLNO Bit Fields */



/* NBYTES_MLOFFNO Bit Fields */
#line 3140 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* NBYTES_MLOFFYES Bit Fields */
#line 3151 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SLAST Bit Fields */



/* DADDR Bit Fields */



/* DOFF Bit Fields */



/* CITER_ELINKNO Bit Fields */





/* CITER_ELINKYES Bit Fields */
#line 3178 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DLAST_SGA Bit Fields */



/* CSR Bit Fields */
#line 3205 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* BITER_ELINKNO Bit Fields */





/* BITER_ELINKYES Bit Fields */
#line 3220 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/* DMA - Peripheral instance base addresses */
/** Peripheral DMA base pointer */

/** Array initializer of DMA peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- DMA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Accessor_Macros DMA - Register accessor macros
 * @{
 */


/* DMA - Register instance definitions */
/* DMA */
#line 3515 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* DMA - Register array accessors */
#line 3532 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group DMA_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DMA_Peripheral */


/* ----------------------------------------------------------------------------
   -- DMAMUX
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Peripheral DMAMUX
 * @{
 */

/** DMAMUX - Peripheral register structure */
typedef struct DMAMUX_MemMap {
  uint8_t CHCFG[16];                               /**< Channel Configuration register, array offset: 0x0, array step: 0x1 */
} volatile *DMAMUX_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DMAMUX - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Accessor_Macros DMAMUX - Register accessor macros
 * @{
 */


/* DMAMUX - Register accessors */


/*!
 * @}
 */ /* end of group DMAMUX_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DMAMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Masks DMAMUX Register Masks
 * @{
 */

/* CHCFG Bit Fields */
#line 3592 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group DMAMUX_Register_Masks */


/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX base pointer */

/** Array initializer of DMAMUX peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- DMAMUX - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Accessor_Macros DMAMUX - Register accessor macros
 * @{
 */


/* DMAMUX - Register instance definitions */
/* DMAMUX */
#line 3632 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* DMAMUX - Register array accessors */


/*!
 * @}
 */ /* end of group DMAMUX_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DMAMUX_Peripheral */


/* ----------------------------------------------------------------------------
   -- DWT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Peripheral DWT
 * @{
 */

/** DWT - Peripheral register structure */
typedef struct DWT_MemMap {
  uint32_t CTRL;                                   /**< Control Register, offset: 0x0 */
  uint32_t CYCCNT;                                 /**< Cycle Count Register, offset: 0x4 */
  uint32_t CPICNT;                                 /**< CPI Count Register, offset: 0x8 */
  uint32_t EXCCNT;                                 /**< Exception Overhead Count Register, offset: 0xC */
  uint32_t SLEEPCNT;                               /**< Sleep Count Register, offset: 0x10 */
  uint32_t LSUCNT;                                 /**< LSU Count Register, offset: 0x14 */
  uint32_t FOLDCNT;                                /**< Folded-instruction Count Register, offset: 0x18 */
  uint32_t PCSR;                                   /**< Program Counter Sample Register, offset: 0x1C */
  struct {                                         /* offset: 0x20, array step: 0x10 */
    uint32_t COMP;                                   /**< Comparator Register 0..Comparator Register 3, array offset: 0x20, array step: 0x10 */
    uint32_t MASK;                                   /**< Mask Register 0..Mask Register 3, array offset: 0x24, array step: 0x10 */
    uint32_t FUNCTION;                               /**< Function Register 0..Function Register 3, array offset: 0x28, array step: 0x10 */
    uint8_t RESERVED_0[4];
  } COMPARATOR[4];
  uint8_t RESERVED_0[3952];
  uint32_t PID4;                                   /**< Peripheral Identification Register 4., offset: 0xFD0 */
  uint32_t PID5;                                   /**< Peripheral Identification Register 5., offset: 0xFD4 */
  uint32_t PID6;                                   /**< Peripheral Identification Register 6., offset: 0xFD8 */
  uint32_t PID7;                                   /**< Peripheral Identification Register 7., offset: 0xFDC */
  uint32_t PID0;                                   /**< Peripheral Identification Register 0., offset: 0xFE0 */
  uint32_t PID1;                                   /**< Peripheral Identification Register 1., offset: 0xFE4 */
  uint32_t PID2;                                   /**< Peripheral Identification Register 2., offset: 0xFE8 */
  uint32_t PID3;                                   /**< Peripheral Identification Register 3., offset: 0xFEC */
  uint32_t CID0;                                   /**< Component Identification Register 0., offset: 0xFF0 */
  uint32_t CID1;                                   /**< Component Identification Register 1., offset: 0xFF4 */
  uint32_t CID2;                                   /**< Component Identification Register 2., offset: 0xFF8 */
  uint32_t CID3;                                   /**< Component Identification Register 3., offset: 0xFFC */
} volatile *DWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register accessors */
#line 3720 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Masks DWT Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group DWT_Register_Masks */


/* DWT - Peripheral instance base addresses */
/** Peripheral DWT base pointer */

/** Array initializer of DWT peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register instance definitions */
/* DWT */
#line 3791 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* DWT - Register array accessors */




/*!
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DWT_Peripheral */


/* ----------------------------------------------------------------------------
   -- ETF
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ETF_Peripheral ETF
 * @{
 */

/** ETF - Peripheral register structure */
typedef struct ETF_MemMap {
  uint32_t FCR;                                    /**< Funnel Control Register, offset: 0x0 */
  uint32_t PCR;                                    /**< Priority Control Register, offset: 0x4 */
  uint8_t RESERVED_0[3812];
  uint32_t ITATBDATA0;                             /**< Integration Register, ITATBDATA0, offset: 0xEEC */
  uint32_t ITATBCTR2;                              /**< Integration Register, ITATBCTR2, offset: 0xEF0 */
  uint32_t ITATBCTR1;                              /**< Integration Register, ITATBCTR1, offset: 0xEF4 */
  uint32_t ITATBCTR0;                              /**< Integration Register, ITATBCTR0, offset: 0xEF8 */
  uint8_t RESERVED_1[4];
  uint32_t ITCTRL;                                 /**< Integration Mode Control Register, offset: 0xF00 */
  uint8_t RESERVED_2[156];
  uint32_t CLAIMSET;                               /**< Claim Tag Set Register, offset: 0xFA0 */
  uint32_t CLAIMCLR;                               /**< Claim Tag Clear Register, offset: 0xFA4 */
  uint8_t RESERVED_3[8];
  uint32_t LAR;                                    /**< Lock Access Register, offset: 0xFB0 */
  uint32_t LSR;                                    /**< Lock Status Register, offset: 0xFB4 */
  uint32_t AUTHSTATUS;                             /**< Authentication Status Register, offset: 0xFB8 */
  uint8_t RESERVED_4[12];
  uint32_t DEVID;                                  /**< Device ID Register, offset: 0xFC8 */
  uint32_t DEVTYPE;                                /**< Device Type Identifier Register, offset: 0xFCC */
  uint32_t PIDR4;                                  /**< Peripheral Identification Register 4, offset: 0xFD0 */
  uint32_t PIDR5;                                  /**< Peripheral Identification Register 5, offset: 0xFD4 */
  uint32_t PIDR6;                                  /**< Peripheral Identification Register 6, offset: 0xFD8 */
  uint32_t PIDR7;                                  /**< Peripheral Identification Register 7, offset: 0xFDC */
  uint32_t PIDR0;                                  /**< Peripheral Identification Register 0, offset: 0xFE0 */
  uint32_t PIDR1;                                  /**< Peripheral Identification Register 1, offset: 0xFE4 */
  uint32_t PIDR2;                                  /**< Peripheral Identification Register 2, offset: 0xFE8 */
  uint32_t PIDR3;                                  /**< Peripheral Identification Register 3, offset: 0xFEC */
  uint32_t CIDR0;                                  /**< Component Identification Register 0, offset: 0xFF0 */
  uint32_t CIDR1;                                  /**< Component Identification Register 1, offset: 0xFF4 */
  uint32_t CIDR2;                                  /**< Component Identification Register 2, offset: 0xFF8 */
  uint32_t CIDR3;                                  /**< Component Identification Register 3, offset: 0xFFC */
} volatile *ETF_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ETF - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ETF_Register_Accessor_Macros ETF - Register accessor macros
 * @{
 */


/* ETF - Register accessors */
#line 3888 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group ETF_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ETF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ETF_Register_Masks ETF Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group ETF_Register_Masks */


/* ETF - Peripheral instance base addresses */
/** Peripheral ETF base pointer */

/** Array initializer of ETF peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- ETF - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ETF_Register_Accessor_Macros ETF - Register accessor macros
 * @{
 */


/* ETF - Register instance definitions */
/* ETF */
#line 3953 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group ETF_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ETF_Peripheral */


/* ----------------------------------------------------------------------------
   -- ETM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ETM_Peripheral ETM
 * @{
 */

/** ETM - Peripheral register structure */
typedef struct ETM_MemMap {
  uint32_t CR;                                     /**< Main Control Register, offset: 0x0 */
  uint32_t CCR;                                    /**< Configuration Code Register, offset: 0x4 */
  uint32_t TRIGGER;                                /**< Trigger Event Register, offset: 0x8 */
  uint8_t RESERVED_0[4];
  uint32_t SR;                                     /**< ETM Status Register, offset: 0x10 */
  uint32_t SCR;                                    /**< System Configuration Register, offset: 0x14 */
  uint8_t RESERVED_1[8];
  uint32_t EEVR;                                   /**< Trace Enable Event Register, offset: 0x20 */
  uint32_t TECR1;                                  /**< Trace Enable Control 1 Register, offset: 0x24 */
  uint32_t FFLR;                                   /**< FIFOFULL Level Register, offset: 0x28 */
  uint8_t RESERVED_2[276];
  uint32_t CNTRLDVR1;                              /**< Free-running counter reload value, offset: 0x140 */
  uint8_t RESERVED_3[156];
  uint32_t SYNCFR;                                 /**< Synchronization Frequency Register, offset: 0x1E0 */
  uint32_t IDR;                                    /**< ID Register, offset: 0x1E4 */
  uint32_t CCER;                                   /**< Configuration Code Extension Register, offset: 0x1E8 */
  uint8_t RESERVED_4[4];
  uint32_t TESSEICR;                               /**< TraceEnable Start/Stop EmbeddedICE Control Register, offset: 0x1F0 */
  uint8_t RESERVED_5[4];
  uint32_t TSEVR;                                  /**< Timestamp Event Register, offset: 0x1F8 */
  uint8_t RESERVED_6[4];
  uint32_t TRACEIDR;                               /**< CoreSight Trace ID Register, offset: 0x200 */
  uint8_t RESERVED_7[4];
  uint32_t IDR2;                                   /**< ETM ID Register 2, offset: 0x208 */
  uint8_t RESERVED_8[264];
  uint32_t PDSR;                                   /**< Device Power-Down Status Register, offset: 0x314 */
  uint8_t RESERVED_9[3016];
  uint32_t ITMISCIN;                               /**< Integration Test Miscelaneous Inputs Register, offset: 0xEE0 */
  uint8_t RESERVED_10[4];
  uint32_t ITTRIGOUT;                              /**< Integration Test Trigger Out Register, offset: 0xEE8 */
  uint8_t RESERVED_11[4];
  uint32_t ITATBCTR2;                              /**< ETM Integration Test ATB Control 2 Register, offset: 0xEF0 */
  uint8_t RESERVED_12[4];
  uint32_t ITATBCTR0;                              /**< ETM Integration Test ATB Control 0 Register, offset: 0xEF8 */
  uint8_t RESERVED_13[4];
  uint32_t ITCTRL;                                 /**< Integration Mode Control Register, offset: 0xF00 */
  uint8_t RESERVED_14[156];
  uint32_t CLAIMSET;                               /**< Claim Tag Set Register, offset: 0xFA0 */
  uint32_t CLAIMCLR;                               /**< Claim Tag Clear Register, offset: 0xFA4 */
  uint8_t RESERVED_15[8];
  uint32_t LAR;                                    /**< Lock Access Register, offset: 0xFB0 */
  uint32_t LSR;                                    /**< Lock Status Register, offset: 0xFB4 */
  uint32_t AUTHSTATUS;                             /**< Authentication Status Register, offset: 0xFB8 */
  uint8_t RESERVED_16[16];
  uint32_t DEVTYPE;                                /**< CoreSight Device Type Register, offset: 0xFCC */
  uint32_t PIDR4;                                  /**< Peripheral Identification Register 4, offset: 0xFD0 */
  uint32_t PIDR5;                                  /**< Peripheral Identification Register 5, offset: 0xFD4 */
  uint32_t PIDR6;                                  /**< Peripheral Identification Register 6, offset: 0xFD8 */
  uint32_t PIDR7;                                  /**< Peripheral Identification Register 7, offset: 0xFDC */
  uint32_t PIDR0;                                  /**< Peripheral Identification Register 0, offset: 0xFE0 */
  uint32_t PIDR1;                                  /**< Peripheral Identification Register 1, offset: 0xFE4 */
  uint32_t PIDR2;                                  /**< Peripheral Identification Register 2, offset: 0xFE8 */
  uint32_t PIDR3;                                  /**< Peripheral Identification Register 3, offset: 0xFEC */
  uint32_t CIDR0;                                  /**< Component Identification Register 0, offset: 0xFF0 */
  uint32_t CIDR1;                                  /**< Component Identification Register 1, offset: 0xFF4 */
  uint32_t CIDR2;                                  /**< Component Identification Register 2, offset: 0xFF8 */
  uint32_t CIDR3;                                  /**< Component Identification Register 3, offset: 0xFFC */
} volatile *ETM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ETM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ETM_Register_Accessor_Macros ETM - Register accessor macros
 * @{
 */


/* ETM - Register accessors */
#line 4085 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group ETM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ETM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ETM_Register_Masks ETM Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group ETM_Register_Masks */


/* ETM - Peripheral instance base addresses */
/** Peripheral ETM base pointer */

/** Array initializer of ETM peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- ETM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ETM_Register_Accessor_Macros ETM - Register accessor macros
 * @{
 */


/* ETM - Register instance definitions */
/* ETM */
#line 4164 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group ETM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ETM_Peripheral */


/* ----------------------------------------------------------------------------
   -- EWM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Peripheral EWM
 * @{
 */

/** EWM - Peripheral register structure */
typedef struct EWM_MemMap {
  uint8_t CTRL;                                    /**< Control Register, offset: 0x0 */
  uint8_t SERV;                                    /**< Service Register, offset: 0x1 */
  uint8_t CMPL;                                    /**< Compare Low Register, offset: 0x2 */
  uint8_t CMPH;                                    /**< Compare High Register, offset: 0x3 */
} volatile *EWM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- EWM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Register_Accessor_Macros EWM - Register accessor macros
 * @{
 */


/* EWM - Register accessors */





/*!
 * @}
 */ /* end of group EWM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- EWM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Register_Masks EWM Register Masks
 * @{
 */

/* CTRL Bit Fields */
#line 4231 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SERV Bit Fields */



/* CMPL Bit Fields */



/* CMPH Bit Fields */




/*!
 * @}
 */ /* end of group EWM_Register_Masks */


/* EWM - Peripheral instance base addresses */
/** Peripheral EWM base pointer */

/** Array initializer of EWM peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- EWM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Register_Accessor_Macros EWM - Register accessor macros
 * @{
 */


/* EWM - Register instance definitions */
/* EWM */





/*!
 * @}
 */ /* end of group EWM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group EWM_Peripheral */


/* ----------------------------------------------------------------------------
   -- FMC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Peripheral FMC
 * @{
 */

/** FMC - Peripheral register structure */
typedef struct FMC_MemMap {
  uint32_t PFAPR;                                  /**< Flash Access Protection Register, offset: 0x0 */
  uint32_t PFB0CR;                                 /**< Flash Bank 0 Control Register, offset: 0x4 */
  uint32_t PFB1CR;                                 /**< Flash Bank 1 Control Register, offset: 0x8 */
  uint8_t RESERVED_0[244];
  uint32_t TAGVD[4][2];                            /**< Cache Tag Storage, array offset: 0x100, array step: index*0x8, index2*0x4 */
  uint8_t RESERVED_1[224];
  struct {                                         /* offset: 0x200, array step: index*0x10, index2*0x8 */
    uint32_t DATA_U;                                 /**< Cache Data Storage (upper word), array offset: 0x200, array step: index*0x10, index2*0x8 */
    uint32_t DATA_L;                                 /**< Cache Data Storage (lower word), array offset: 0x204, array step: index*0x10, index2*0x8 */
  } SET[4][2];
} volatile *FMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Register_Accessor_Macros FMC - Register accessor macros
 * @{
 */


/* FMC - Register accessors */
#line 4322 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group FMC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Register_Masks FMC Register Masks
 * @{
 */

/* PFAPR Bit Fields */
#line 4378 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PFB0CR Bit Fields */
#line 4406 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PFB1CR Bit Fields */
#line 4423 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TAGVD Bit Fields */





/* DATA_U Bit Fields */



/* DATA_L Bit Fields */




/*!
 * @}
 */ /* end of group FMC_Register_Masks */


/* FMC - Peripheral instance base addresses */
/** Peripheral FMC base pointer */

/** Array initializer of FMC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- FMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Register_Accessor_Macros FMC - Register accessor macros
 * @{
 */


/* FMC - Register instance definitions */
/* FMC */
#line 4488 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* FMC - Register array accessors */




/*!
 * @}
 */ /* end of group FMC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FMC_Peripheral */


/* ----------------------------------------------------------------------------
   -- FPB
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FPB_Peripheral FPB
 * @{
 */

/** FPB - Peripheral register structure */
typedef struct FPB_MemMap {
  uint32_t CTRL;                                   /**< FlashPatch Control Register, offset: 0x0 */
  uint32_t REMAP;                                  /**< FlashPatch Remap Register, offset: 0x4 */
  uint32_t COMP[8];                                /**< FlashPatch Comparator Register 0..FlashPatch Comparator Register 7, array offset: 0x8, array step: 0x4 */
  uint8_t RESERVED_0[4008];
  uint32_t PID4;                                   /**< Peripheral Identification Register 4., offset: 0xFD0 */
  uint32_t PID5;                                   /**< Peripheral Identification Register 5., offset: 0xFD4 */
  uint32_t PID6;                                   /**< Peripheral Identification Register 6., offset: 0xFD8 */
  uint32_t PID7;                                   /**< Peripheral Identification Register 7., offset: 0xFDC */
  uint32_t PID0;                                   /**< Peripheral Identification Register 0., offset: 0xFE0 */
  uint32_t PID1;                                   /**< Peripheral Identification Register 1., offset: 0xFE4 */
  uint32_t PID2;                                   /**< Peripheral Identification Register 2., offset: 0xFE8 */
  uint32_t PID3;                                   /**< Peripheral Identification Register 3., offset: 0xFEC */
  uint32_t CID0;                                   /**< Component Identification Register 0., offset: 0xFF0 */
  uint32_t CID1;                                   /**< Component Identification Register 1., offset: 0xFF4 */
  uint32_t CID2;                                   /**< Component Identification Register 2., offset: 0xFF8 */
  uint32_t CID3;                                   /**< Component Identification Register 3., offset: 0xFFC */
} volatile *FPB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FPB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FPB_Register_Accessor_Macros FPB - Register accessor macros
 * @{
 */


/* FPB - Register accessors */
#line 4559 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group FPB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FPB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FPB_Register_Masks FPB Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group FPB_Register_Masks */


/* FPB - Peripheral instance base addresses */
/** Peripheral FPB base pointer */

/** Array initializer of FPB peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- FPB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FPB_Register_Accessor_Macros FPB - Register accessor macros
 * @{
 */


/* FPB - Register instance definitions */
/* FPB */
#line 4620 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* FPB - Register array accessors */


/*!
 * @}
 */ /* end of group FPB_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FPB_Peripheral */


/* ----------------------------------------------------------------------------
   -- FTFL
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFL_Peripheral FTFL
 * @{
 */

/** FTFL - Peripheral register structure */
typedef struct FTFL_MemMap {
  uint8_t FSTAT;                                   /**< Flash Status Register, offset: 0x0 */
  uint8_t FCNFG;                                   /**< Flash Configuration Register, offset: 0x1 */
  uint8_t FSEC;                                    /**< Flash Security Register, offset: 0x2 */
  uint8_t FOPT;                                    /**< Flash Option Register, offset: 0x3 */
  uint8_t FCCOB3;                                  /**< Flash Common Command Object Registers, offset: 0x4 */
  uint8_t FCCOB2;                                  /**< Flash Common Command Object Registers, offset: 0x5 */
  uint8_t FCCOB1;                                  /**< Flash Common Command Object Registers, offset: 0x6 */
  uint8_t FCCOB0;                                  /**< Flash Common Command Object Registers, offset: 0x7 */
  uint8_t FCCOB7;                                  /**< Flash Common Command Object Registers, offset: 0x8 */
  uint8_t FCCOB6;                                  /**< Flash Common Command Object Registers, offset: 0x9 */
  uint8_t FCCOB5;                                  /**< Flash Common Command Object Registers, offset: 0xA */
  uint8_t FCCOB4;                                  /**< Flash Common Command Object Registers, offset: 0xB */
  uint8_t FCCOBB;                                  /**< Flash Common Command Object Registers, offset: 0xC */
  uint8_t FCCOBA;                                  /**< Flash Common Command Object Registers, offset: 0xD */
  uint8_t FCCOB9;                                  /**< Flash Common Command Object Registers, offset: 0xE */
  uint8_t FCCOB8;                                  /**< Flash Common Command Object Registers, offset: 0xF */
  uint8_t FPROT3;                                  /**< Program Flash Protection Registers, offset: 0x10 */
  uint8_t FPROT2;                                  /**< Program Flash Protection Registers, offset: 0x11 */
  uint8_t FPROT1;                                  /**< Program Flash Protection Registers, offset: 0x12 */
  uint8_t FPROT0;                                  /**< Program Flash Protection Registers, offset: 0x13 */
  uint8_t RESERVED_0[2];
  uint8_t FEPROT;                                  /**< EEPROM Protection Register, offset: 0x16 */
  uint8_t FDPROT;                                  /**< Data Flash Protection Register, offset: 0x17 */
} volatile *FTFL_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTFL - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFL_Register_Accessor_Macros FTFL - Register accessor macros
 * @{
 */


/* FTFL - Register accessors */
#line 4703 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group FTFL_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTFL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFL_Register_Masks FTFL Register Masks
 * @{
 */

/* FSTAT Bit Fields */
#line 4729 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FCNFG Bit Fields */
#line 4746 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FSEC Bit Fields */
#line 4759 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FOPT Bit Fields */



/* FCCOB3 Bit Fields */



/* FCCOB2 Bit Fields */



/* FCCOB1 Bit Fields */



/* FCCOB0 Bit Fields */



/* FCCOB7 Bit Fields */



/* FCCOB6 Bit Fields */



/* FCCOB5 Bit Fields */



/* FCCOB4 Bit Fields */



/* FCCOBB Bit Fields */



/* FCCOBA Bit Fields */



/* FCCOB9 Bit Fields */



/* FCCOB8 Bit Fields */



/* FPROT3 Bit Fields */



/* FPROT2 Bit Fields */



/* FPROT1 Bit Fields */



/* FPROT0 Bit Fields */



/* FEPROT Bit Fields */



/* FDPROT Bit Fields */




/*!
 * @}
 */ /* end of group FTFL_Register_Masks */


/* FTFL - Peripheral instance base addresses */
/** Peripheral FTFL base pointer */

/** Array initializer of FTFL peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- FTFL - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFL_Register_Accessor_Macros FTFL - Register accessor macros
 * @{
 */


/* FTFL - Register instance definitions */
/* FTFL */
#line 4881 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group FTFL_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FTFL_Peripheral */


/* ----------------------------------------------------------------------------
   -- FTM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Peripheral FTM
 * @{
 */

/** FTM - Peripheral register structure */
typedef struct FTM_MemMap {
  uint32_t SC;                                     /**< Status And Control, offset: 0x0 */
  uint32_t CNT;                                    /**< Counter, offset: 0x4 */
  uint32_t MOD;                                    /**< Modulo, offset: 0x8 */
  struct {                                         /* offset: 0xC, array step: 0x8 */
    uint32_t CnSC;                                   /**< Channel (n) Status And Control, array offset: 0xC, array step: 0x8 */
    uint32_t CnV;                                    /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
  } CONTROLS[8];
  uint32_t CNTIN;                                  /**< Counter Initial Value, offset: 0x4C */
  uint32_t STATUS;                                 /**< Capture And Compare Status, offset: 0x50 */
  uint32_t MODE;                                   /**< Features Mode Selection, offset: 0x54 */
  uint32_t SYNC;                                   /**< Synchronization, offset: 0x58 */
  uint32_t OUTINIT;                                /**< Initial State For Channels Output, offset: 0x5C */
  uint32_t OUTMASK;                                /**< Output Mask, offset: 0x60 */
  uint32_t COMBINE;                                /**< Function For Linked Channels, offset: 0x64 */
  uint32_t DEADTIME;                               /**< Deadtime Insertion Control, offset: 0x68 */
  uint32_t EXTTRIG;                                /**< FTM External Trigger, offset: 0x6C */
  uint32_t POL;                                    /**< Channels Polarity, offset: 0x70 */
  uint32_t FMS;                                    /**< Fault Mode Status, offset: 0x74 */
  uint32_t FILTER;                                 /**< Input Capture Filter Control, offset: 0x78 */
  uint32_t FLTCTRL;                                /**< Fault Control, offset: 0x7C */
  uint32_t QDCTRL;                                 /**< Quadrature Decoder Control And Status, offset: 0x80 */
  uint32_t CONF;                                   /**< Configuration, offset: 0x84 */
  uint32_t FLTPOL;                                 /**< FTM Fault Input Polarity, offset: 0x88 */
  uint32_t SYNCONF;                                /**< Synchronization Configuration, offset: 0x8C */
  uint32_t INVCTRL;                                /**< FTM Inverting Control, offset: 0x90 */
  uint32_t SWOCTRL;                                /**< FTM Software Output Control, offset: 0x94 */
  uint32_t PWMLOAD;                                /**< FTM PWM Load, offset: 0x98 */
} volatile *FTM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Accessor_Macros FTM - Register accessor macros
 * @{
 */


/* FTM - Register accessors */
#line 4968 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group FTM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Masks FTM Register Masks
 * @{
 */

/* SC Bit Fields */
#line 4996 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CNT Bit Fields */



/* MOD Bit Fields */



/* CnSC Bit Fields */
#line 5019 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CnV Bit Fields */



/* CNTIN Bit Fields */



/* STATUS Bit Fields */
#line 5044 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* MODE Bit Fields */
#line 5060 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SYNC Bit Fields */
#line 5077 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* OUTINIT Bit Fields */
#line 5094 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* OUTMASK Bit Fields */
#line 5111 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* COMBINE Bit Fields */
#line 5168 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DEADTIME Bit Fields */
#line 5175 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* EXTTRIG Bit Fields */
#line 5192 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* POL Bit Fields */
#line 5209 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FMS Bit Fields */
#line 5224 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FILTER Bit Fields */
#line 5237 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FLTCTRL Bit Fields */
#line 5257 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* QDCTRL Bit Fields */
#line 5274 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CONF Bit Fields */
#line 5285 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FLTPOL Bit Fields */
#line 5294 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SYNCONF Bit Fields */
#line 5325 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* INVCTRL Bit Fields */
#line 5334 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SWOCTRL Bit Fields */
#line 5367 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PWMLOAD Bit Fields */
#line 5386 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group FTM_Register_Masks */


/* FTM - Peripheral instance base addresses */
/** Peripheral FTM0 base pointer */

/** Peripheral FTM1 base pointer */

/** Peripheral FTM2 base pointer */

/** Array initializer of FTM peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- FTM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Accessor_Macros FTM - Register accessor macros
 * @{
 */


/* FTM - Register instance definitions */
/* FTM0 */
#line 5453 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FTM1 */
#line 5481 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FTM2 */
#line 5509 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* FTM - Register array accessors */
#line 5517 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group FTM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FTM_Peripheral */


/* ----------------------------------------------------------------------------
   -- GPIO
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral GPIO
 * @{
 */

/** GPIO - Peripheral register structure */
typedef struct GPIO_MemMap {
  uint32_t PDOR;                                   /**< Port Data Output Register, offset: 0x0 */
  uint32_t PSOR;                                   /**< Port Set Output Register, offset: 0x4 */
  uint32_t PCOR;                                   /**< Port Clear Output Register, offset: 0x8 */
  uint32_t PTOR;                                   /**< Port Toggle Output Register, offset: 0xC */
  uint32_t PDIR;                                   /**< Port Data Input Register, offset: 0x10 */
  uint32_t PDDR;                                   /**< Port Data Direction Register, offset: 0x14 */
} volatile *GPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register accessors */
#line 5564 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/* PDOR Bit Fields */



/* PSOR Bit Fields */



/* PCOR Bit Fields */



/* PTOR Bit Fields */



/* PDIR Bit Fields */



/* PDDR Bit Fields */




/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral PTA base pointer */

/** Peripheral PTB base pointer */

/** Peripheral PTC base pointer */

/** Peripheral PTD base pointer */

/** Peripheral PTE base pointer */

/** Array initializer of GPIO peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- GPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Accessor_Macros GPIO - Register accessor macros
 * @{
 */


/* GPIO - Register instance definitions */
/* PTA */
#line 5641 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PTB */
#line 5648 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PTC */
#line 5655 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PTD */
#line 5662 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PTE */
#line 5669 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group GPIO_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group GPIO_Peripheral */


/* ----------------------------------------------------------------------------
   -- I2C
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Peripheral I2C
 * @{
 */

/** I2C - Peripheral register structure */
typedef struct I2C_MemMap {
  uint8_t A1;                                      /**< I2C Address Register 1, offset: 0x0 */
  uint8_t F;                                       /**< I2C Frequency Divider register, offset: 0x1 */
  uint8_t C1;                                      /**< I2C Control Register 1, offset: 0x2 */
  uint8_t S;                                       /**< I2C Status register, offset: 0x3 */
  uint8_t D;                                       /**< I2C Data I/O register, offset: 0x4 */
  uint8_t C2;                                      /**< I2C Control Register 2, offset: 0x5 */
  uint8_t FLT;                                     /**< I2C Programmable Input Glitch Filter register, offset: 0x6 */
  uint8_t RA;                                      /**< I2C Range Address register, offset: 0x7 */
  uint8_t SMB;                                     /**< I2C SMBus Control and Status register, offset: 0x8 */
  uint8_t A2;                                      /**< I2C Address Register 2, offset: 0x9 */
  uint8_t SLTH;                                    /**< I2C SCL Low Timeout Register High, offset: 0xA */
  uint8_t SLTL;                                    /**< I2C SCL Low Timeout Register Low, offset: 0xB */
} volatile *I2C_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register accessors */
#line 5728 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/* A1 Bit Fields */



/* F Bit Fields */
#line 5754 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C1 Bit Fields */
#line 5771 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* S Bit Fields */
#line 5788 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* D Bit Fields */



/* C2 Bit Fields */
#line 5806 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FLT Bit Fields */



/* RA Bit Fields */



/* SMB Bit Fields */
#line 5831 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* A2 Bit Fields */



/* SLTH Bit Fields */



/* SLTL Bit Fields */




/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base pointer */

/** Peripheral I2C1 base pointer */

/** Array initializer of I2C peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register instance definitions */
/* I2C0 */
#line 5881 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* I2C1 */
#line 5894 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group I2C_Peripheral */


/* ----------------------------------------------------------------------------
   -- I2S
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Peripheral I2S
 * @{
 */

/** I2S - Peripheral register structure */
typedef struct I2S_MemMap {
  uint32_t TCSR;                                   /**< SAI Transmit Control Register, offset: 0x0 */
  uint32_t TCR1;                                   /**< SAI Transmit Configuration 1 Register, offset: 0x4 */
  uint32_t TCR2;                                   /**< SAI Transmit Configuration 2 Register, offset: 0x8 */
  uint32_t TCR3;                                   /**< SAI Transmit Configuration 3 Register, offset: 0xC */
  uint32_t TCR4;                                   /**< SAI Transmit Configuration 4 Register, offset: 0x10 */
  uint32_t TCR5;                                   /**< SAI Transmit Configuration 5 Register, offset: 0x14 */
  uint8_t RESERVED_0[8];
  uint32_t TDR[1];                                 /**< SAI Transmit Data Register, array offset: 0x20, array step: 0x4 */
  uint8_t RESERVED_1[28];
  uint32_t TFR[1];                                 /**< SAI Transmit FIFO Register, array offset: 0x40, array step: 0x4 */
  uint8_t RESERVED_2[28];
  uint32_t TMR;                                    /**< SAI Transmit Mask Register, offset: 0x60 */
  uint8_t RESERVED_3[28];
  uint32_t RCSR;                                   /**< SAI Receive Control Register, offset: 0x80 */
  uint32_t RCR1;                                   /**< SAI Receive Configuration 1 Register, offset: 0x84 */
  uint32_t RCR2;                                   /**< SAI Receive Configuration 2 Register, offset: 0x88 */
  uint32_t RCR3;                                   /**< SAI Receive Configuration 3 Register, offset: 0x8C */
  uint32_t RCR4;                                   /**< SAI Receive Configuration 4 Register, offset: 0x90 */
  uint32_t RCR5;                                   /**< SAI Receive Configuration 5 Register, offset: 0x94 */
  uint8_t RESERVED_4[8];
  uint32_t RDR[1];                                 /**< SAI Receive Data Register, array offset: 0xA0, array step: 0x4 */
  uint8_t RESERVED_5[28];
  uint32_t RFR[1];                                 /**< SAI Receive FIFO Register, array offset: 0xC0, array step: 0x4 */
  uint8_t RESERVED_6[28];
  uint32_t RMR;                                    /**< SAI Receive Mask Register, offset: 0xE0 */
  uint8_t RESERVED_7[28];
  uint32_t MCR;                                    /**< SAI MCLK Control Register, offset: 0x100 */
  uint32_t MDR;                                    /**< SAI MCLK Divide Register, offset: 0x104 */
} volatile *I2S_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- I2S - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Register_Accessor_Macros I2S - Register accessor macros
 * @{
 */


/* I2S - Register accessors */
#line 5977 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group I2S_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- I2S Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Register_Masks I2S Register Masks
 * @{
 */

/* TCSR Bit Fields */
#line 6029 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TCR1 Bit Fields */



/* TCR2 Bit Fields */
#line 6051 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TCR3 Bit Fields */





/* TCR4 Bit Fields */
#line 6072 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TCR5 Bit Fields */
#line 6082 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TDR Bit Fields */



/* TFR Bit Fields */
#line 6093 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TMR Bit Fields */



/* RCSR Bit Fields */
#line 6134 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RCR1 Bit Fields */



/* RCR2 Bit Fields */
#line 6156 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RCR3 Bit Fields */





/* RCR4 Bit Fields */
#line 6177 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RCR5 Bit Fields */
#line 6187 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RDR Bit Fields */



/* RFR Bit Fields */
#line 6198 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RMR Bit Fields */



/* MCR Bit Fields */
#line 6210 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* MDR Bit Fields */
#line 6217 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group I2S_Register_Masks */


/* I2S - Peripheral instance base addresses */
/** Peripheral I2S0 base pointer */

/** Array initializer of I2S peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- I2S - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Register_Accessor_Macros I2S - Register accessor macros
 * @{
 */


/* I2S - Register instance definitions */
/* I2S0 */
#line 6261 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* I2S - Register array accessors */





/*!
 * @}
 */ /* end of group I2S_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group I2S_Peripheral */


/* ----------------------------------------------------------------------------
   -- ITM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ITM_Peripheral ITM
 * @{
 */

/** ITM - Peripheral register structure */
typedef struct ITM_MemMap {
  union {                                          /* offset: 0x0 */
    uint32_t STIM_READ[32];                          /**< Stimulus Port Register 0 (for reading)..Stimulus Port Register 31 (for reading), array offset: 0x0, array step: 0x4 */
    uint32_t STIM_WRITE[32];                         /**< Stimulus Port Register 0 (for writing)..Stimulus Port Register 31 (for writing), array offset: 0x0, array step: 0x4 */
  };
  uint8_t RESERVED_0[3456];
  uint32_t TER;                                    /**< Trace Enable Register, offset: 0xE00 */
  uint8_t RESERVED_1[60];
  uint32_t TPR;                                    /**< Trace Privilege Register, offset: 0xE40 */
  uint8_t RESERVED_2[60];
  uint32_t TCR;                                    /**< Trace Control Register, offset: 0xE80 */
  uint8_t RESERVED_3[300];
  uint32_t LAR;                                    /**< Lock Access Register, offset: 0xFB0 */
  uint32_t LSR;                                    /**< Lock Status Register, offset: 0xFB4 */
  uint8_t RESERVED_4[24];
  uint32_t PID4;                                   /**< Peripheral Identification Register 4., offset: 0xFD0 */
  uint32_t PID5;                                   /**< Peripheral Identification Register 5., offset: 0xFD4 */
  uint32_t PID6;                                   /**< Peripheral Identification Register 6., offset: 0xFD8 */
  uint32_t PID7;                                   /**< Peripheral Identification Register 7., offset: 0xFDC */
  uint32_t PID0;                                   /**< Peripheral Identification Register 0., offset: 0xFE0 */
  uint32_t PID1;                                   /**< Peripheral Identification Register 1., offset: 0xFE4 */
  uint32_t PID2;                                   /**< Peripheral Identification Register 2., offset: 0xFE8 */
  uint32_t PID3;                                   /**< Peripheral Identification Register 3., offset: 0xFEC */
  uint32_t CID0;                                   /**< Component Identification Register 0., offset: 0xFF0 */
  uint32_t CID1;                                   /**< Component Identification Register 1., offset: 0xFF4 */
  uint32_t CID2;                                   /**< Component Identification Register 2., offset: 0xFF8 */
  uint32_t CID3;                                   /**< Component Identification Register 3., offset: 0xFFC */
} volatile *ITM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ITM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ITM_Register_Accessor_Macros ITM - Register accessor macros
 * @{
 */


/* ITM - Register accessors */
#line 6347 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group ITM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ITM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ITM_Register_Masks ITM Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group ITM_Register_Masks */


/* ITM - Peripheral instance base addresses */
/** Peripheral ITM base pointer */

/** Array initializer of ITM peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- ITM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ITM_Register_Accessor_Macros ITM - Register accessor macros
 * @{
 */


/* ITM - Register instance definitions */
/* ITM */
#line 6467 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* ITM - Register array accessors */



/*!
 * @}
 */ /* end of group ITM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ITM_Peripheral */


/* ----------------------------------------------------------------------------
   -- LLWU
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Peripheral LLWU
 * @{
 */

/** LLWU - Peripheral register structure */
typedef struct LLWU_MemMap {
  uint8_t PE1;                                     /**< LLWU Pin Enable 1 register, offset: 0x0 */
  uint8_t PE2;                                     /**< LLWU Pin Enable 2 register, offset: 0x1 */
  uint8_t PE3;                                     /**< LLWU Pin Enable 3 register, offset: 0x2 */
  uint8_t PE4;                                     /**< LLWU Pin Enable 4 register, offset: 0x3 */
  uint8_t ME;                                      /**< LLWU Module Enable register, offset: 0x4 */
  uint8_t F1;                                      /**< LLWU Flag 1 register, offset: 0x5 */
  uint8_t F2;                                      /**< LLWU Flag 2 register, offset: 0x6 */
  uint8_t F3;                                      /**< LLWU Flag 3 register, offset: 0x7 */
  uint8_t FILT1;                                   /**< LLWU Pin Filter 1 register, offset: 0x8 */
  uint8_t FILT2;                                   /**< LLWU Pin Filter 2 register, offset: 0x9 */
  uint8_t RST;                                     /**< LLWU Reset Enable register, offset: 0xA */
} volatile *LLWU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LLWU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Accessor_Macros LLWU - Register accessor macros
 * @{
 */


/* LLWU - Register accessors */
#line 6528 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group LLWU_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- LLWU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Masks LLWU Register Masks
 * @{
 */

/* PE1 Bit Fields */
#line 6556 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PE2 Bit Fields */
#line 6569 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PE3 Bit Fields */
#line 6582 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PE4 Bit Fields */
#line 6595 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ME Bit Fields */
#line 6612 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* F1 Bit Fields */
#line 6629 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* F2 Bit Fields */
#line 6646 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* F3 Bit Fields */
#line 6663 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FILT1 Bit Fields */
#line 6672 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FILT2 Bit Fields */
#line 6681 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RST Bit Fields */





/*!
 * @}
 */ /* end of group LLWU_Register_Masks */


/* LLWU - Peripheral instance base addresses */
/** Peripheral LLWU base pointer */

/** Array initializer of LLWU peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- LLWU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Accessor_Macros LLWU - Register accessor macros
 * @{
 */


/* LLWU - Register instance definitions */
/* LLWU */
#line 6721 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group LLWU_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group LLWU_Peripheral */


/* ----------------------------------------------------------------------------
   -- LPTMR
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Peripheral LPTMR
 * @{
 */

/** LPTMR - Peripheral register structure */
typedef struct LPTMR_MemMap {
  uint32_t CSR;                                    /**< Low Power Timer Control Status Register, offset: 0x0 */
  uint32_t PSR;                                    /**< Low Power Timer Prescale Register, offset: 0x4 */
  uint32_t CMR;                                    /**< Low Power Timer Compare Register, offset: 0x8 */
  uint32_t CNR;                                    /**< Low Power Timer Counter Register, offset: 0xC */
} volatile *LPTMR_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LPTMR - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Accessor_Macros LPTMR - Register accessor macros
 * @{
 */


/* LPTMR - Register accessors */





/*!
 * @}
 */ /* end of group LPTMR_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- LPTMR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Masks LPTMR Register Masks
 * @{
 */

/* CSR Bit Fields */
#line 6795 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PSR Bit Fields */
#line 6804 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CMR Bit Fields */



/* CNR Bit Fields */




/*!
 * @}
 */ /* end of group LPTMR_Register_Masks */


/* LPTMR - Peripheral instance base addresses */
/** Peripheral LPTMR0 base pointer */

/** Array initializer of LPTMR peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- LPTMR - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Accessor_Macros LPTMR - Register accessor macros
 * @{
 */


/* LPTMR - Register instance definitions */
/* LPTMR0 */





/*!
 * @}
 */ /* end of group LPTMR_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group LPTMR_Peripheral */


/* ----------------------------------------------------------------------------
   -- MCG
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Peripheral MCG
 * @{
 */

/** MCG - Peripheral register structure */
typedef struct MCG_MemMap {
  uint8_t C1;                                      /**< MCG Control 1 Register, offset: 0x0 */
  uint8_t C2;                                      /**< MCG Control 2 Register, offset: 0x1 */
  uint8_t C3;                                      /**< MCG Control 3 Register, offset: 0x2 */
  uint8_t C4;                                      /**< MCG Control 4 Register, offset: 0x3 */
  uint8_t C5;                                      /**< MCG Control 5 Register, offset: 0x4 */
  uint8_t C6;                                      /**< MCG Control 6 Register, offset: 0x5 */
  uint8_t S;                                       /**< MCG Status Register, offset: 0x6 */
  uint8_t RESERVED_0[1];
  uint8_t SC;                                      /**< MCG Status and Control Register, offset: 0x8 */
  uint8_t RESERVED_1[1];
  uint8_t ATCVH;                                   /**< MCG Auto Trim Compare Value High Register, offset: 0xA */
  uint8_t ATCVL;                                   /**< MCG Auto Trim Compare Value Low Register, offset: 0xB */
  uint8_t C7;                                      /**< MCG Control 7 Register, offset: 0xC */
  uint8_t C8;                                      /**< MCG Control 8 Register, offset: 0xD */
  uint8_t C9;                                      /**< MCG Control 9 Register, offset: 0xE */
  uint8_t C10;                                     /**< MCG Control 10 Register, offset: 0xF */
} volatile *MCG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Accessor_Macros MCG - Register accessor macros
 * @{
 */


/* MCG - Register accessors */
#line 6905 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group MCG_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MCG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Masks MCG Register Masks
 * @{
 */

/* C1 Bit Fields */
#line 6933 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C2 Bit Fields */
#line 6947 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C3 Bit Fields */



/* C4 Bit Fields */
#line 6962 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C5 Bit Fields */
#line 6970 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C6 Bit Fields */
#line 6980 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* S Bit Fields */
#line 6996 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SC Bit Fields */
#line 7010 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ATCVH Bit Fields */



/* ATCVL Bit Fields */



/* C7 Bit Fields */


/* C8 Bit Fields */
#line 7030 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group MCG_Register_Masks */


/* MCG - Peripheral instance base addresses */
/** Peripheral MCG base pointer */

/** Array initializer of MCG peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- MCG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Accessor_Macros MCG - Register accessor macros
 * @{
 */


/* MCG - Register instance definitions */
/* MCG */
#line 7068 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group MCG_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MCG_Peripheral */


/* ----------------------------------------------------------------------------
   -- MCM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Peripheral MCM
 * @{
 */

/** MCM - Peripheral register structure */
typedef struct MCM_MemMap {
  uint8_t RESERVED_0[8];
  uint16_t PLASC;                                  /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8 */
  uint16_t PLAMC;                                  /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA */
  uint32_t PLACR;                                  /**< Crossbar Switch (AXBS) Control Register, offset: 0xC */
} volatile *MCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register accessors */




/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */

/* PLASC Bit Fields */



/* PLAMC Bit Fields */



/* PLACR Bit Fields */



/*!
 * @}
 */ /* end of group MCM_Register_Masks */


/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base pointer */

/** Array initializer of MCM peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- MCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Accessor_Macros MCM - Register accessor macros
 * @{
 */


/* MCM - Register instance definitions */
/* MCM */




/*!
 * @}
 */ /* end of group MCM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MCM_Peripheral */


/* ----------------------------------------------------------------------------
   -- NV
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Peripheral NV
 * @{
 */

/** NV - Peripheral register structure */
typedef struct NV_MemMap {
  uint8_t BACKKEY3;                                /**< Backdoor Comparison Key 3., offset: 0x0 */
  uint8_t BACKKEY2;                                /**< Backdoor Comparison Key 2., offset: 0x1 */
  uint8_t BACKKEY1;                                /**< Backdoor Comparison Key 1., offset: 0x2 */
  uint8_t BACKKEY0;                                /**< Backdoor Comparison Key 0., offset: 0x3 */
  uint8_t BACKKEY7;                                /**< Backdoor Comparison Key 7., offset: 0x4 */
  uint8_t BACKKEY6;                                /**< Backdoor Comparison Key 6., offset: 0x5 */
  uint8_t BACKKEY5;                                /**< Backdoor Comparison Key 5., offset: 0x6 */
  uint8_t BACKKEY4;                                /**< Backdoor Comparison Key 4., offset: 0x7 */
  uint8_t FPROT3;                                  /**< Non-volatile P-Flash Protection 1 - Low Register, offset: 0x8 */
  uint8_t FPROT2;                                  /**< Non-volatile P-Flash Protection 1 - High Register, offset: 0x9 */
  uint8_t FPROT1;                                  /**< Non-volatile P-Flash Protection 0 - Low Register, offset: 0xA */
  uint8_t FPROT0;                                  /**< Non-volatile P-Flash Protection 0 - High Register, offset: 0xB */
  uint8_t FSEC;                                    /**< Non-volatile Flash Security Register, offset: 0xC */
  uint8_t FOPT;                                    /**< Non-volatile Flash Option Register, offset: 0xD */
  uint8_t FEPROT;                                  /**< Non-volatile EERAM Protection Register, offset: 0xE */
  uint8_t FDPROT;                                  /**< Non-volatile D-Flash Protection Register, offset: 0xF */
} volatile *NV_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register accessors */
#line 7230 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- NV Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Masks NV Register Masks
 * @{
 */

/* BACKKEY3 Bit Fields */



/* BACKKEY2 Bit Fields */



/* BACKKEY1 Bit Fields */



/* BACKKEY0 Bit Fields */



/* BACKKEY7 Bit Fields */



/* BACKKEY6 Bit Fields */



/* BACKKEY5 Bit Fields */



/* BACKKEY4 Bit Fields */



/* FPROT3 Bit Fields */



/* FPROT2 Bit Fields */



/* FPROT1 Bit Fields */



/* FPROT0 Bit Fields */



/* FSEC Bit Fields */
#line 7306 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FOPT Bit Fields */
#line 7313 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FEPROT Bit Fields */



/* FDPROT Bit Fields */




/*!
 * @}
 */ /* end of group NV_Register_Masks */


/* NV - Peripheral instance base addresses */
/** Peripheral FTFL_FlashConfig base pointer */

/** Array initializer of NV peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register instance definitions */
/* FTFL_FlashConfig */
#line 7361 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group NV_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group NV_Peripheral */


/* ----------------------------------------------------------------------------
   -- NVIC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Peripheral NVIC
 * @{
 */

/** NVIC - Peripheral register structure */
typedef struct NVIC_MemMap {
  uint32_t ISER[4];                                /**< Interrupt Set Enable Register n, array offset: 0x0, array step: 0x4 */
  uint8_t RESERVED_0[112];
  uint32_t ICER[4];                                /**< Interrupt Clear Enable Register n, array offset: 0x80, array step: 0x4 */
  uint8_t RESERVED_1[112];
  uint32_t ISPR[4];                                /**< Interrupt Set Pending Register n, array offset: 0x100, array step: 0x4 */
  uint8_t RESERVED_2[112];
  uint32_t ICPR[4];                                /**< Interrupt Clear Pending Register n, array offset: 0x180, array step: 0x4 */
  uint8_t RESERVED_3[112];
  uint32_t IABR[4];                                /**< Interrupt Active bit Register n, array offset: 0x200, array step: 0x4 */
  uint8_t RESERVED_4[240];
  uint8_t IP[106];                                 /**< Interrupt Priority Register n, array offset: 0x300, array step: 0x1 */
  uint8_t RESERVED_5[2710];
  uint32_t STIR[1];                                /**< Software Trigger Interrupt Register, array offset: 0xE00, array step: 0x4 */
} volatile *NVIC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register accessors */
#line 7416 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- NVIC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Masks NVIC Register Masks
 * @{
 */

/* ISER Bit Fields */



/* ICER Bit Fields */



/* ISPR Bit Fields */



/* ICPR Bit Fields */



/* IABR Bit Fields */



/* IP Bit Fields */
#line 7770 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* STIR Bit Fields */




/*!
 * @}
 */ /* end of group NVIC_Register_Masks */


/* NVIC - Peripheral instance base addresses */
/** Peripheral NVIC base pointer */

/** Array initializer of NVIC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register instance definitions */
/* NVIC */
#line 7925 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* NVIC - Register array accessors */
#line 7934 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group NVIC_Peripheral */


/* ----------------------------------------------------------------------------
   -- OSC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Peripheral OSC
 * @{
 */

/** OSC - Peripheral register structure */
typedef struct OSC_MemMap {
  uint8_t CR;                                      /**< OSC Control Register, offset: 0x0 */
} volatile *OSC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register accessors */


/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- OSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Masks OSC Register Masks
 * @{
 */

/* CR Bit Fields */
#line 7999 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group OSC_Register_Masks */


/* OSC - Peripheral instance base addresses */
/** Peripheral OSC base pointer */

/** Array initializer of OSC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- OSC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Accessor_Macros OSC - Register accessor macros
 * @{
 */


/* OSC - Register instance definitions */
/* OSC */


/*!
 * @}
 */ /* end of group OSC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group OSC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PDB
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Peripheral PDB
 * @{
 */

/** PDB - Peripheral register structure */
typedef struct PDB_MemMap {
  uint32_t SC;                                     /**< Status and Control Register, offset: 0x0 */
  uint32_t MOD;                                    /**< Modulus Register, offset: 0x4 */
  uint32_t CNT;                                    /**< Counter Register, offset: 0x8 */
  uint32_t IDLY;                                   /**< Interrupt Delay Register, offset: 0xC */
  struct {                                         /* offset: 0x10, array step: 0x28 */
    uint32_t C1;                                     /**< Channel n Control Register 1, array offset: 0x10, array step: 0x28 */
    uint32_t S;                                      /**< Channel n Status Register, array offset: 0x14, array step: 0x28 */
    uint32_t DLY[2];                                 /**< Channel n Delay 0 Register..Channel n Delay 1 Register, array offset: 0x18, array step: index*0x28, index2*0x4 */
    uint8_t RESERVED_0[24];
  } CH[2];
  uint8_t RESERVED_0[240];
  struct {                                         /* offset: 0x150, array step: 0x8 */
    uint32_t INTC;                                   /**< DAC Interval Trigger n Control Register, array offset: 0x150, array step: 0x8 */
    uint32_t INT;                                    /**< DAC Interval n Register, array offset: 0x154, array step: 0x8 */
  } DAC[1];
  uint8_t RESERVED_1[56];
  uint32_t POEN;                                   /**< Pulse-Out n Enable Register, offset: 0x190 */
  uint32_t PODLY[2];                               /**< Pulse-Out n Delay Register, array offset: 0x194, array step: 0x4 */
} volatile *PDB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PDB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Register_Accessor_Macros PDB - Register accessor macros
 * @{
 */


/* PDB - Register accessors */
#line 8088 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group PDB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PDB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Register_Masks PDB Register Masks
 * @{
 */

/* SC Bit Fields */
#line 8132 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* MOD Bit Fields */



/* CNT Bit Fields */



/* IDLY Bit Fields */



/* C1 Bit Fields */
#line 8154 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* S Bit Fields */
#line 8161 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DLY Bit Fields */



/* INTC Bit Fields */




/* INT Bit Fields */



/* POEN Bit Fields */



/* PODLY Bit Fields */
#line 8185 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group PDB_Register_Masks */


/* PDB - Peripheral instance base addresses */
/** Peripheral PDB0 base pointer */

/** Array initializer of PDB peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- PDB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PDB_Register_Accessor_Macros PDB - Register accessor macros
 * @{
 */


/* PDB - Register instance definitions */
/* PDB0 */
#line 8226 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* PDB - Register array accessors */
#line 8234 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group PDB_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PDB_Peripheral */


/* ----------------------------------------------------------------------------
   -- PIT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Peripheral PIT
 * @{
 */

/** PIT - Peripheral register structure */
typedef struct PIT_MemMap {
  uint32_t MCR;                                    /**< PIT Module Control Register, offset: 0x0 */
  uint8_t RESERVED_0[252];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    uint32_t LDVAL;                                  /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    uint32_t CVAL;                                   /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    uint32_t TCTRL;                                  /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    uint32_t TFLG;                                   /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[4];
} volatile *PIT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register accessors */






/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Masks PIT Register Masks
 * @{
 */

/* MCR Bit Fields */




/* LDVAL Bit Fields */



/* CVAL Bit Fields */



/* TCTRL Bit Fields */
#line 8317 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TFLG Bit Fields */



/*!
 * @}
 */ /* end of group PIT_Register_Masks */


/* PIT - Peripheral instance base addresses */
/** Peripheral PIT base pointer */

/** Array initializer of PIT peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register instance definitions */
/* PIT */
#line 8361 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* PIT - Register array accessors */





/*!
 * @}
 */ /* end of group PIT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PIT_Peripheral */


/* ----------------------------------------------------------------------------
   -- PMC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Peripheral PMC
 * @{
 */

/** PMC - Peripheral register structure */
typedef struct PMC_MemMap {
  uint8_t LVDSC1;                                  /**< Low Voltage Detect Status And Control 1 register, offset: 0x0 */
  uint8_t LVDSC2;                                  /**< Low Voltage Detect Status And Control 2 register, offset: 0x1 */
  uint8_t REGSC;                                   /**< Regulator Status And Control register, offset: 0x2 */
} volatile *PMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register accessors */




/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/* LVDSC1 Bit Fields */
#line 8435 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* LVDSC2 Bit Fields */
#line 8445 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* REGSC Bit Fields */
#line 8454 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group PMC_Register_Masks */


/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base pointer */

/** Array initializer of PMC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- PMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Accessor_Macros PMC - Register accessor macros
 * @{
 */


/* PMC - Register instance definitions */
/* PMC */




/*!
 * @}
 */ /* end of group PMC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PMC_Peripheral */


/* ----------------------------------------------------------------------------
   -- PORT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Peripheral PORT
 * @{
 */

/** PORT - Peripheral register structure */
typedef struct PORT_MemMap {
  uint32_t PCR[32];                                /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
  uint32_t GPCLR;                                  /**< Global Pin Control Low Register, offset: 0x80 */
  uint32_t GPCHR;                                  /**< Global Pin Control High Register, offset: 0x84 */
  uint8_t RESERVED_0[24];
  uint32_t ISFR;                                   /**< Interrupt Status Flag Register, offset: 0xA0 */
  uint8_t RESERVED_1[28];
  uint32_t DFER;                                   /**< Digital Filter Enable Register, offset: 0xC0 */
  uint32_t DFCR;                                   /**< Digital Filter Clock Register, offset: 0xC4 */
  uint32_t DFWR;                                   /**< Digital Filter Width Register, offset: 0xC8 */
} volatile *PORT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register accessors */
#line 8532 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/* PCR Bit Fields */
#line 8570 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* GPCLR Bit Fields */
#line 8577 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* GPCHR Bit Fields */
#line 8584 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ISFR Bit Fields */



/* DFER Bit Fields */



/* DFCR Bit Fields */


/* DFWR Bit Fields */




/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base pointer */

/** Peripheral PORTB base pointer */

/** Peripheral PORTC base pointer */

/** Peripheral PORTD base pointer */

/** Peripheral PORTE base pointer */

/** Array initializer of PORT peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register instance definitions */
/* PORTA */
#line 8669 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PORTB */
#line 8708 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PORTC */
#line 8747 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PORTD */
#line 8786 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PORTE */
#line 8825 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* PORT - Register array accessors */






/*!
 * @}
 */ /* end of group PORT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group PORT_Peripheral */


/* ----------------------------------------------------------------------------
   -- RCM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Peripheral RCM
 * @{
 */

/** RCM - Peripheral register structure */
typedef struct RCM_MemMap {
  uint8_t SRS0;                                    /**< System Reset Status Register 0, offset: 0x0 */
  uint8_t SRS1;                                    /**< System Reset Status Register 1, offset: 0x1 */
  uint8_t RESERVED_0[2];
  uint8_t RPFC;                                    /**< Reset Pin Filter Control register, offset: 0x4 */
  uint8_t RPFW;                                    /**< Reset Pin Filter Width register, offset: 0x5 */
  uint8_t RESERVED_1[1];
  uint8_t MR;                                      /**< Mode Register, offset: 0x7 */
} volatile *RCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Accessor_Macros RCM - Register accessor macros
 * @{
 */


/* RCM - Register accessors */






/*!
 * @}
 */ /* end of group RCM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Masks RCM Register Masks
 * @{
 */

/* SRS0 Bit Fields */
#line 8909 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SRS1 Bit Fields */
#line 8924 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RPFC Bit Fields */





/* RPFW Bit Fields */



/* MR Bit Fields */



/*!
 * @}
 */ /* end of group RCM_Register_Masks */


/* RCM - Peripheral instance base addresses */
/** Peripheral RCM base pointer */

/** Array initializer of RCM peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- RCM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Accessor_Macros RCM - Register accessor macros
 * @{
 */


/* RCM - Register instance definitions */
/* RCM */






/*!
 * @}
 */ /* end of group RCM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RCM_Peripheral */


/* ----------------------------------------------------------------------------
   -- RFSYS
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Peripheral RFSYS
 * @{
 */

/** RFSYS - Peripheral register structure */
typedef struct RFSYS_MemMap {
  uint32_t REG[8];                                 /**< Register file register, array offset: 0x0, array step: 0x4 */
} volatile *RFSYS_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RFSYS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Register_Accessor_Macros RFSYS - Register accessor macros
 * @{
 */


/* RFSYS - Register accessors */


/*!
 * @}
 */ /* end of group RFSYS_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RFSYS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Register_Masks RFSYS Register Masks
 * @{
 */

/* REG Bit Fields */
#line 9031 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group RFSYS_Register_Masks */


/* RFSYS - Peripheral instance base addresses */
/** Peripheral RFSYS base pointer */

/** Array initializer of RFSYS peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- RFSYS - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFSYS_Register_Accessor_Macros RFSYS - Register accessor macros
 * @{
 */


/* RFSYS - Register instance definitions */
/* RFSYS */
#line 9063 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* RFSYS - Register array accessors */


/*!
 * @}
 */ /* end of group RFSYS_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RFSYS_Peripheral */


/* ----------------------------------------------------------------------------
   -- RFVBAT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFVBAT_Peripheral RFVBAT
 * @{
 */

/** RFVBAT - Peripheral register structure */
typedef struct RFVBAT_MemMap {
  uint32_t REG[8];                                 /**< VBAT register file register, array offset: 0x0, array step: 0x4 */
} volatile *RFVBAT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RFVBAT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFVBAT_Register_Accessor_Macros RFVBAT - Register accessor macros
 * @{
 */


/* RFVBAT - Register accessors */


/*!
 * @}
 */ /* end of group RFVBAT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RFVBAT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFVBAT_Register_Masks RFVBAT Register Masks
 * @{
 */

/* REG Bit Fields */
#line 9131 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group RFVBAT_Register_Masks */


/* RFVBAT - Peripheral instance base addresses */
/** Peripheral RFVBAT base pointer */

/** Array initializer of RFVBAT peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- RFVBAT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RFVBAT_Register_Accessor_Macros RFVBAT - Register accessor macros
 * @{
 */


/* RFVBAT - Register instance definitions */
/* RFVBAT */
#line 9163 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* RFVBAT - Register array accessors */


/*!
 * @}
 */ /* end of group RFVBAT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RFVBAT_Peripheral */


/* ----------------------------------------------------------------------------
   -- RNG
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Peripheral RNG
 * @{
 */

/** RNG - Peripheral register structure */
typedef struct RNG_MemMap {
  uint32_t CR;                                     /**< RNGA Control Register, offset: 0x0 */
  uint32_t SR;                                     /**< RNGA Status Register, offset: 0x4 */
  uint32_t ER;                                     /**< RNGA Entropy Register, offset: 0x8 */
  uint32_t OR;                                     /**< RNGA Output Register, offset: 0xC */
} volatile *RNG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RNG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Register_Accessor_Macros RNG - Register accessor macros
 * @{
 */


/* RNG - Register accessors */





/*!
 * @}
 */ /* end of group RNG_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RNG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Register_Masks RNG Register Masks
 * @{
 */

/* CR Bit Fields */
#line 9235 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SR Bit Fields */
#line 9252 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ER Bit Fields */



/* OR Bit Fields */




/*!
 * @}
 */ /* end of group RNG_Register_Masks */


/* RNG - Peripheral instance base addresses */
/** Peripheral RNG base pointer */

/** Array initializer of RNG peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- RNG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Register_Accessor_Macros RNG - Register accessor macros
 * @{
 */


/* RNG - Register instance definitions */
/* RNG */





/*!
 * @}
 */ /* end of group RNG_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RNG_Peripheral */


/* ----------------------------------------------------------------------------
   -- RTC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral RTC
 * @{
 */

/** RTC - Peripheral register structure */
typedef struct RTC_MemMap {
  uint32_t TSR;                                    /**< RTC Time Seconds Register, offset: 0x0 */
  uint32_t TPR;                                    /**< RTC Time Prescaler Register, offset: 0x4 */
  uint32_t TAR;                                    /**< RTC Time Alarm Register, offset: 0x8 */
  uint32_t TCR;                                    /**< RTC Time Compensation Register, offset: 0xC */
  uint32_t CR;                                     /**< RTC Control Register, offset: 0x10 */
  uint32_t SR;                                     /**< RTC Status Register, offset: 0x14 */
  uint32_t LR;                                     /**< RTC Lock Register, offset: 0x18 */
  uint32_t IER;                                    /**< RTC Interrupt Enable Register, offset: 0x1C */
  uint32_t TTSR;                                   /**< RTC Tamper Time Seconds Register, offset: 0x20 */
  uint32_t MER;                                    /**< RTC Monotonic Enable Register, offset: 0x24 */
  uint32_t MCLR;                                   /**< RTC Monotonic Counter Low Register, offset: 0x28 */
  uint32_t MCHR;                                   /**< RTC Monotonic Counter High Register, offset: 0x2C */
  uint8_t RESERVED_0[2000];
  uint32_t WAR;                                    /**< RTC Write Access Register, offset: 0x800 */
  uint32_t RAR;                                    /**< RTC Read Access Register, offset: 0x804 */
} volatile *RTC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register accessors */
#line 9352 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/* TSR Bit Fields */



/* TPR Bit Fields */



/* TAR Bit Fields */



/* TCR Bit Fields */
#line 9392 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CR Bit Fields */
#line 9413 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SR Bit Fields */
#line 9424 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* LR Bit Fields */
#line 9441 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* IER Bit Fields */
#line 9454 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TTSR Bit Fields */



/* MER Bit Fields */


/* MCLR Bit Fields */



/* MCHR Bit Fields */



/* WAR Bit Fields */
#line 9494 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RAR Bit Fields */
#line 9519 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base pointer */

/** Array initializer of RTC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register instance definitions */
/* RTC */
#line 9557 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group RTC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group RTC_Peripheral */


/* ----------------------------------------------------------------------------
   -- SCB
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Peripheral SCB
 * @{
 */

/** SCB - Peripheral register structure */
typedef struct SCB_MemMap {
  uint8_t RESERVED_0[8];
  uint32_t ACTLR;                                  /**< Auxiliary Control Register,, offset: 0x8 */
  uint8_t RESERVED_1[3316];
  uint32_t CPUID;                                  /**< CPUID Base Register, offset: 0xD00 */
  uint32_t ICSR;                                   /**< Interrupt Control and State Register, offset: 0xD04 */
  uint32_t VTOR;                                   /**< Vector Table Offset Register, offset: 0xD08 */
  uint32_t AIRCR;                                  /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
  uint32_t SCR;                                    /**< System Control Register, offset: 0xD10 */
  uint32_t CCR;                                    /**< Configuration and Control Register, offset: 0xD14 */
  uint32_t SHPR1;                                  /**< System Handler Priority Register 1, offset: 0xD18 */
  uint32_t SHPR2;                                  /**< System Handler Priority Register 2, offset: 0xD1C */
  uint32_t SHPR3;                                  /**< System Handler Priority Register 3, offset: 0xD20 */
  uint32_t SHCSR;                                  /**< System Handler Control and State Register, offset: 0xD24 */
  uint32_t CFSR;                                   /**< Configurable Fault Status Registers, offset: 0xD28 */
  uint32_t HFSR;                                   /**< HardFault Status register, offset: 0xD2C */
  uint32_t DFSR;                                   /**< Debug Fault Status Register, offset: 0xD30 */
  uint32_t MMFAR;                                  /**< MemManage Address Register, offset: 0xD34 */
  uint32_t BFAR;                                   /**< BusFault Address Register, offset: 0xD38 */
  uint32_t AFSR;                                   /**< Auxiliary Fault Status Register, offset: 0xD3C */
} volatile *SCB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register accessors */
#line 9628 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SCB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Masks SCB Register Masks
 * @{
 */

/* ACTLR Bit Fields */
#line 9650 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CPUID Bit Fields */
#line 9663 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ICSR Bit Fields */
#line 9686 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* VTOR Bit Fields */



/* AIRCR Bit Fields */
#line 9705 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SCR Bit Fields */
#line 9712 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CCR Bit Fields */
#line 9725 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SHPR1 Bit Fields */
#line 9735 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SHPR2 Bit Fields */



/* SHPR3 Bit Fields */
#line 9746 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SHCSR Bit Fields */
#line 9775 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CFSR Bit Fields */
#line 9814 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* HFSR Bit Fields */
#line 9821 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* DFSR Bit Fields */
#line 9832 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* MMFAR Bit Fields */



/* BFAR Bit Fields */



/* AFSR Bit Fields */




/*!
 * @}
 */ /* end of group SCB_Register_Masks */


/* SCB - Peripheral instance base addresses */
/** Peripheral SystemControl base pointer */

/** Array initializer of SCB peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register instance definitions */
/* SystemControl */
#line 9885 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group SCB_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SCB_Peripheral */


/* ----------------------------------------------------------------------------
   -- SIM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Peripheral SIM
 * @{
 */

/** SIM - Peripheral register structure */
typedef struct SIM_MemMap {
  uint32_t SOPT1;                                  /**< System Options Register 1, offset: 0x0 */
  uint32_t SOPT1CFG;                               /**< SOPT1 Configuration Register, offset: 0x4 */
  uint8_t RESERVED_0[4092];
  uint32_t SOPT2;                                  /**< System Options Register 2, offset: 0x1004 */
  uint8_t RESERVED_1[4];
  uint32_t SOPT4;                                  /**< System Options Register 4, offset: 0x100C */
  uint32_t SOPT5;                                  /**< System Options Register 5, offset: 0x1010 */
  uint8_t RESERVED_2[4];
  uint32_t SOPT7;                                  /**< System Options Register 7, offset: 0x1018 */
  uint8_t RESERVED_3[8];
  uint32_t SDID;                                   /**< System Device Identification Register, offset: 0x1024 */
  uint8_t RESERVED_4[12];
  uint32_t SCGC4;                                  /**< System Clock Gating Control Register 4, offset: 0x1034 */
  uint32_t SCGC5;                                  /**< System Clock Gating Control Register 5, offset: 0x1038 */
  uint32_t SCGC6;                                  /**< System Clock Gating Control Register 6, offset: 0x103C */
  uint32_t SCGC7;                                  /**< System Clock Gating Control Register 7, offset: 0x1040 */
  uint32_t CLKDIV1;                                /**< System Clock Divider Register 1, offset: 0x1044 */
  uint32_t CLKDIV2;                                /**< System Clock Divider Register 2, offset: 0x1048 */
  uint32_t FCFG1;                                  /**< Flash Configuration Register 1, offset: 0x104C */
  uint32_t FCFG2;                                  /**< Flash Configuration Register 2, offset: 0x1050 */
  uint32_t UIDH;                                   /**< Unique Identification Register High, offset: 0x1054 */
  uint32_t UIDMH;                                  /**< Unique Identification Register Mid-High, offset: 0x1058 */
  uint32_t UIDML;                                  /**< Unique Identification Register Mid Low, offset: 0x105C */
  uint32_t UIDL;                                   /**< Unique Identification Register Low, offset: 0x1060 */
} volatile *SIM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register accessors */
#line 9963 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Masks SIM Register Masks
 * @{
 */

/* SOPT1 Bit Fields */
#line 9991 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SOPT1CFG Bit Fields */
#line 9998 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SOPT2 Bit Fields */
#line 10012 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SOPT4 Bit Fields */
#line 10037 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SOPT5 Bit Fields */
#line 10050 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SOPT7 Bit Fields */
#line 10058 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SDID Bit Fields */
#line 10071 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SCGC4 Bit Fields */
#line 10094 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SCGC5 Bit Fields */
#line 10107 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SCGC6 Bit Fields */
#line 10140 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SCGC7 Bit Fields */


/* CLKDIV1 Bit Fields */
#line 10153 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CLKDIV2 Bit Fields */





/* FCFG1 Bit Fields */
#line 10176 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* FCFG2 Bit Fields */
#line 10187 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* UIDH Bit Fields */



/* UIDMH Bit Fields */



/* UIDML Bit Fields */



/* UIDL Bit Fields */




/*!
 * @}
 */ /* end of group SIM_Register_Masks */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base pointer */

/** Array initializer of SIM peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register instance definitions */
/* SIM */
#line 10246 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group SIM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SIM_Peripheral */


/* ----------------------------------------------------------------------------
   -- SMC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Peripheral SMC
 * @{
 */

/** SMC - Peripheral register structure */
typedef struct SMC_MemMap {
  uint8_t PMPROT;                                  /**< Power Mode Protection register, offset: 0x0 */
  uint8_t PMCTRL;                                  /**< Power Mode Control register, offset: 0x1 */
  uint8_t VLLSCTRL;                                /**< VLLS Control register, offset: 0x2 */
  uint8_t PMSTAT;                                  /**< Power Mode Status register, offset: 0x3 */
} volatile *SMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Accessor_Macros SMC - Register accessor macros
 * @{
 */


/* SMC - Register accessors */





/*!
 * @}
 */ /* end of group SMC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Masks SMC Register Masks
 * @{
 */

/* PMPROT Bit Fields */
#line 10311 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PMCTRL Bit Fields */
#line 10322 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* VLLSCTRL Bit Fields */
#line 10330 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PMSTAT Bit Fields */




/*!
 * @}
 */ /* end of group SMC_Register_Masks */


/* SMC - Peripheral instance base addresses */
/** Peripheral SMC base pointer */

/** Array initializer of SMC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- SMC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Accessor_Macros SMC - Register accessor macros
 * @{
 */


/* SMC - Register instance definitions */
/* SMC */





/*!
 * @}
 */ /* end of group SMC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SMC_Peripheral */


/* ----------------------------------------------------------------------------
   -- SPI
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral SPI
 * @{
 */

/** SPI - Peripheral register structure */
typedef struct SPI_MemMap {
  uint32_t MCR;                                    /**< Module Configuration Register, offset: 0x0 */
  uint8_t RESERVED_0[4];
  uint32_t TCR;                                    /**< Transfer Count Register, offset: 0x8 */
  union {                                          /* offset: 0xC */
    uint32_t CTAR[2];                                /**< Clock and Transfer Attributes Register (In Master Mode), array offset: 0xC, array step: 0x4 */
    uint32_t CTAR_SLAVE[1];                          /**< Clock and Transfer Attributes Register (In Slave Mode), array offset: 0xC, array step: 0x4 */
  };
  uint8_t RESERVED_1[24];
  uint32_t SR;                                     /**< DSPI Status Register, offset: 0x2C */
  uint32_t RSER;                                   /**< DMA/Interrupt Request Select and Enable Register, offset: 0x30 */
  union {                                          /* offset: 0x34 */
    uint32_t PUSHR;                                  /**< PUSH TX FIFO Register In Master Mode, offset: 0x34 */
    uint32_t PUSHR_SLAVE;                            /**< PUSH TX FIFO Register In Slave Mode, offset: 0x34 */
  };
  uint32_t POPR;                                   /**< POP RX FIFO Register, offset: 0x38 */
  uint32_t TXFR0;                                  /**< DSPI Transmit FIFO Registers, offset: 0x3C */
  uint32_t TXFR1;                                  /**< DSPI Transmit FIFO Registers, offset: 0x40 */
  uint32_t TXFR2;                                  /**< DSPI Transmit FIFO Registers, offset: 0x44 */
  uint32_t TXFR3;                                  /**< DSPI Transmit FIFO Registers, offset: 0x48 */
  uint8_t RESERVED_2[48];
  uint32_t RXFR0;                                  /**< DSPI Receive FIFO Registers, offset: 0x7C */
  uint32_t RXFR1;                                  /**< DSPI Receive FIFO Registers, offset: 0x80 */
  uint32_t RXFR2;                                  /**< DSPI Receive FIFO Registers, offset: 0x84 */
  uint32_t RXFR3;                                  /**< DSPI Receive FIFO Registers, offset: 0x88 */
} volatile *SPI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register accessors */
#line 10438 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/* MCR Bit Fields */
#line 10487 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TCR Bit Fields */



/* CTAR Bit Fields */
#line 10527 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CTAR_SLAVE Bit Fields */
#line 10535 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SR Bit Fields */
#line 10562 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RSER Bit Fields */
#line 10579 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PUSHR Bit Fields */
#line 10595 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* PUSHR_SLAVE Bit Fields */



/* POPR Bit Fields */



/* TXFR0 Bit Fields */
#line 10610 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TXFR1 Bit Fields */
#line 10617 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TXFR2 Bit Fields */
#line 10624 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TXFR3 Bit Fields */
#line 10631 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RXFR0 Bit Fields */



/* RXFR1 Bit Fields */



/* RXFR2 Bit Fields */



/* RXFR3 Bit Fields */




/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base pointer */

/** Peripheral SPI1 base pointer */

/** Array initializer of SPI peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register instance definitions */
/* SPI0 */
#line 10691 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SPI1 */
#line 10710 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* SPI - Register array accessors */





/*!
 * @}
 */ /* end of group SPI_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SPI_Peripheral */


/* ----------------------------------------------------------------------------
   -- SysTick
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Peripheral SysTick
 * @{
 */

/** SysTick - Peripheral register structure */
typedef struct SysTick_MemMap {
  uint32_t CSR;                                    /**< SysTick Control and Status Register, offset: 0x0 */
  uint32_t RVR;                                    /**< SysTick Reload Value Register, offset: 0x4 */
  uint32_t CVR;                                    /**< SysTick Current Value Register, offset: 0x8 */
  uint32_t CALIB;                                  /**< SysTick Calibration Value Register, offset: 0xC */
} volatile *SysTick_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register accessors */





/*!
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SysTick Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Masks SysTick Register Masks
 * @{
 */

/* CSR Bit Fields */
#line 10783 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* RVR Bit Fields */



/* CVR Bit Fields */



/* CALIB Bit Fields */
#line 10799 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group SysTick_Register_Masks */


/* SysTick - Peripheral instance base addresses */
/** Peripheral SysTick base pointer */

/** Array initializer of SysTick peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- SysTick - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SysTick_Register_Accessor_Macros SysTick - Register accessor macros
 * @{
 */


/* SysTick - Register instance definitions */
/* SysTick */





/*!
 * @}
 */ /* end of group SysTick_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group SysTick_Peripheral */


/* ----------------------------------------------------------------------------
   -- TPIU
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPIU_Peripheral TPIU
 * @{
 */

/** TPIU - Peripheral register structure */
typedef struct TPIU_MemMap {
  uint32_t SSPSR;                                  /**< Supported Parallel Port Size Register, offset: 0x0 */
  uint32_t CSPSR;                                  /**< Current Parallel Port Size Register, offset: 0x4 */
  uint8_t RESERVED_0[8];
  uint32_t ACPR;                                   /**< Asynchronous Clock Prescaler Register, offset: 0x10 */
  uint8_t RESERVED_1[220];
  uint32_t SPPR;                                   /**< Selected Pin Protocol Register, offset: 0xF0 */
  uint8_t RESERVED_2[524];
  uint32_t FFSR;                                   /**< Formatter and Flush Status Register, offset: 0x300 */
  uint32_t FFCR;                                   /**< Formatter and Flush Control Register, offset: 0x304 */
  uint32_t FSCR;                                   /**< Formatter Synchronization Counter Register, offset: 0x308 */
  uint8_t RESERVED_3[3036];
  uint32_t TRIGGER;                                /**< Trigger Register, offset: 0xEE8 */
  uint32_t FIFODATA0;                              /**< FIFODATA0 Register, offset: 0xEEC */
  uint32_t ITATBCTR2;                              /**< Integration Test ATB Control 2 Register, offset: 0xEF0 */
  uint8_t RESERVED_4[4];
  uint32_t ITATBCTR0;                              /**< Integration Test ATB Control 0 Register, offset: 0xEF8 */
  uint32_t FIFODATA1;                              /**< FIFODATA1 Register, offset: 0xEFC */
  uint32_t ITCTRL;                                 /**< Integration Mode Control Register, offset: 0xF00 */
  uint8_t RESERVED_5[156];
  uint32_t CLAIMSET;                               /**< Claim Tag Set Register, offset: 0xFA0 */
  uint32_t CLAIMCLR;                               /**< Claim Tag Clear Register, offset: 0xFA4 */
  uint8_t RESERVED_6[32];
  uint32_t DEVID;                                  /**< TPIU_DEVID Register, offset: 0xFC8 */
  uint8_t RESERVED_7[4];
  uint32_t PID4;                                   /**< Peripheral Identification Register 4., offset: 0xFD0 */
  uint32_t PID5;                                   /**< Peripheral Identification Register 5., offset: 0xFD4 */
  uint32_t PID6;                                   /**< Peripheral Identification Register 6., offset: 0xFD8 */
  uint32_t PID7;                                   /**< Peripheral Identification Register 7., offset: 0xFDC */
  uint32_t PID0;                                   /**< Peripheral Identification Register 0., offset: 0xFE0 */
  uint32_t PID1;                                   /**< Peripheral Identification Register 1., offset: 0xFE4 */
  uint32_t PID2;                                   /**< Peripheral Identification Register 2., offset: 0xFE8 */
  uint32_t PID3;                                   /**< Peripheral Identification Register 3., offset: 0xFEC */
  uint32_t CID0;                                   /**< Component Identification Register 0., offset: 0xFF0 */
  uint32_t CID1;                                   /**< Component Identification Register 1., offset: 0xFF4 */
  uint32_t CID2;                                   /**< Component Identification Register 2., offset: 0xFF8 */
  uint32_t CID4;                                   /**< Component Identification Register 3., offset: 0xFFC */
} volatile *TPIU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- TPIU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPIU_Register_Accessor_Macros TPIU - Register accessor macros
 * @{
 */


/* TPIU - Register accessors */
#line 10926 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group TPIU_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- TPIU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPIU_Register_Masks TPIU Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group TPIU_Register_Masks */


/* TPIU - Peripheral instance base addresses */
/** Peripheral TPIU base pointer */

/** Array initializer of TPIU peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- TPIU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPIU_Register_Accessor_Macros TPIU - Register accessor macros
 * @{
 */


/* TPIU - Register instance definitions */
/* TPIU */
#line 10993 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group TPIU_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group TPIU_Peripheral */


/* ----------------------------------------------------------------------------
   -- UART
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Peripheral UART
 * @{
 */

/** UART - Peripheral register structure */
typedef struct UART_MemMap {
  uint8_t BDH;                                     /**< UART Baud Rate Registers: High, offset: 0x0 */
  uint8_t BDL;                                     /**< UART Baud Rate Registers: Low, offset: 0x1 */
  uint8_t C1;                                      /**< UART Control Register 1, offset: 0x2 */
  uint8_t C2;                                      /**< UART Control Register 2, offset: 0x3 */
  uint8_t S1;                                      /**< UART Status Register 1, offset: 0x4 */
  uint8_t S2;                                      /**< UART Status Register 2, offset: 0x5 */
  uint8_t C3;                                      /**< UART Control Register 3, offset: 0x6 */
  uint8_t D;                                       /**< UART Data Register, offset: 0x7 */
  uint8_t MA1;                                     /**< UART Match Address Registers 1, offset: 0x8 */
  uint8_t MA2;                                     /**< UART Match Address Registers 2, offset: 0x9 */
  uint8_t C4;                                      /**< UART Control Register 4, offset: 0xA */
  uint8_t C5;                                      /**< UART Control Register 5, offset: 0xB */
  uint8_t ED;                                      /**< UART Extended Data Register, offset: 0xC */
  uint8_t MODEM;                                   /**< UART Modem Register, offset: 0xD */
  uint8_t IR;                                      /**< UART Infrared Register, offset: 0xE */
  uint8_t RESERVED_0[1];
  uint8_t PFIFO;                                   /**< UART FIFO Parameters, offset: 0x10 */
  uint8_t CFIFO;                                   /**< UART FIFO Control Register, offset: 0x11 */
  uint8_t SFIFO;                                   /**< UART FIFO Status Register, offset: 0x12 */
  uint8_t TWFIFO;                                  /**< UART FIFO Transmit Watermark, offset: 0x13 */
  uint8_t TCFIFO;                                  /**< UART FIFO Transmit Count, offset: 0x14 */
  uint8_t RWFIFO;                                  /**< UART FIFO Receive Watermark, offset: 0x15 */
  uint8_t RCFIFO;                                  /**< UART FIFO Receive Count, offset: 0x16 */
  uint8_t RESERVED_1[1];
  uint8_t C7816;                                   /**< UART 7816 Control Register, offset: 0x18 */
  uint8_t IE7816;                                  /**< UART 7816 Interrupt Enable Register, offset: 0x19 */
  uint8_t IS7816;                                  /**< UART 7816 Interrupt Status Register, offset: 0x1A */
  union {                                          /* offset: 0x1B */
    uint8_t WP7816_T_TYPE0;                          /**< UART 7816 Wait Parameter Register, offset: 0x1B */
    uint8_t WP7816_T_TYPE1;                          /**< UART 7816 Wait Parameter Register, offset: 0x1B */
  };
  uint8_t WN7816;                                  /**< UART 7816 Wait N Register, offset: 0x1C */
  uint8_t WF7816;                                  /**< UART 7816 Wait FD Register, offset: 0x1D */
  uint8_t ET7816;                                  /**< UART 7816 Error Threshold Register, offset: 0x1E */
  uint8_t TL7816;                                  /**< UART 7816 Transmit Length Register, offset: 0x1F */
} volatile *UART_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register accessors */
#line 11094 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- UART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Masks UART Register Masks
 * @{
 */

/* BDH Bit Fields */
#line 11117 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* BDL Bit Fields */



/* C1 Bit Fields */
#line 11138 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C2 Bit Fields */
#line 11155 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* S1 Bit Fields */
#line 11172 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* S2 Bit Fields */
#line 11189 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C3 Bit Fields */
#line 11206 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* D Bit Fields */



/* MA1 Bit Fields */



/* MA2 Bit Fields */



/* C4 Bit Fields */
#line 11228 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* C5 Bit Fields */




/* ED Bit Fields */




/* MODEM Bit Fields */
#line 11247 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* IR Bit Fields */





/* PFIFO Bit Fields */
#line 11264 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CFIFO Bit Fields */
#line 11275 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SFIFO Bit Fields */
#line 11286 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TWFIFO Bit Fields */



/* TCFIFO Bit Fields */



/* RWFIFO Bit Fields */



/* RCFIFO Bit Fields */



/* C7816 Bit Fields */
#line 11313 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* IE7816 Bit Fields */
#line 11328 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* IS7816 Bit Fields */
#line 11343 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* WP7816_T_TYPE0 Bit Fields */



/* WP7816_T_TYPE1 Bit Fields */
#line 11354 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* WN7816 Bit Fields */



/* WF7816 Bit Fields */



/* ET7816 Bit Fields */
#line 11369 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TL7816 Bit Fields */




/*!
 * @}
 */ /* end of group UART_Register_Masks */


/* UART - Peripheral instance base addresses */
/** Peripheral UART0 base pointer */

/** Peripheral UART1 base pointer */

/** Peripheral UART2 base pointer */

/** Peripheral UART3 base pointer */

/** Array initializer of UART peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- UART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Accessor_Macros UART - Register accessor macros
 * @{
 */


/* UART - Register instance definitions */
/* UART0 */
#line 11434 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* UART1 */
#line 11457 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* UART2 */
#line 11480 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* UART3 */
#line 11503 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group UART_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group UART_Peripheral */


/* ----------------------------------------------------------------------------
   -- USB
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Peripheral USB
 * @{
 */

/** USB - Peripheral register structure */
typedef struct USB_MemMap {
  uint8_t PERID;                                   /**< Peripheral ID register, offset: 0x0 */
  uint8_t RESERVED_0[3];
  uint8_t IDCOMP;                                  /**< Peripheral ID Complement register, offset: 0x4 */
  uint8_t RESERVED_1[3];
  uint8_t REV;                                     /**< Peripheral Revision register, offset: 0x8 */
  uint8_t RESERVED_2[3];
  uint8_t ADDINFO;                                 /**< Peripheral Additional Info register, offset: 0xC */
  uint8_t RESERVED_3[3];
  uint8_t OTGISTAT;                                /**< OTG Interrupt Status register, offset: 0x10 */
  uint8_t RESERVED_4[3];
  uint8_t OTGICR;                                  /**< OTG Interrupt Control Register, offset: 0x14 */
  uint8_t RESERVED_5[3];
  uint8_t OTGSTAT;                                 /**< OTG Status register, offset: 0x18 */
  uint8_t RESERVED_6[3];
  uint8_t OTGCTL;                                  /**< OTG Control register, offset: 0x1C */
  uint8_t RESERVED_7[99];
  uint8_t ISTAT;                                   /**< Interrupt Status register, offset: 0x80 */
  uint8_t RESERVED_8[3];
  uint8_t INTEN;                                   /**< Interrupt Enable register, offset: 0x84 */
  uint8_t RESERVED_9[3];
  uint8_t ERRSTAT;                                 /**< Error Interrupt Status register, offset: 0x88 */
  uint8_t RESERVED_10[3];
  uint8_t ERREN;                                   /**< Error Interrupt Enable register, offset: 0x8C */
  uint8_t RESERVED_11[3];
  uint8_t STAT;                                    /**< Status register, offset: 0x90 */
  uint8_t RESERVED_12[3];
  uint8_t CTL;                                     /**< Control register, offset: 0x94 */
  uint8_t RESERVED_13[3];
  uint8_t ADDR;                                    /**< Address register, offset: 0x98 */
  uint8_t RESERVED_14[3];
  uint8_t BDTPAGE1;                                /**< BDT Page Register 1, offset: 0x9C */
  uint8_t RESERVED_15[3];
  uint8_t FRMNUML;                                 /**< Frame Number Register Low, offset: 0xA0 */
  uint8_t RESERVED_16[3];
  uint8_t FRMNUMH;                                 /**< Frame Number Register High, offset: 0xA4 */
  uint8_t RESERVED_17[3];
  uint8_t TOKEN;                                   /**< Token register, offset: 0xA8 */
  uint8_t RESERVED_18[3];
  uint8_t SOFTHLD;                                 /**< SOF Threshold Register, offset: 0xAC */
  uint8_t RESERVED_19[3];
  uint8_t BDTPAGE2;                                /**< BDT Page Register 2, offset: 0xB0 */
  uint8_t RESERVED_20[3];
  uint8_t BDTPAGE3;                                /**< BDT Page Register 3, offset: 0xB4 */
  uint8_t RESERVED_21[11];
  struct {                                         /* offset: 0xC0, array step: 0x4 */
    uint8_t ENDPT;                                   /**< Endpoint Control register, array offset: 0xC0, array step: 0x4 */
    uint8_t RESERVED_0[3];
  } ENDPOINT[16];
  uint8_t USBCTRL;                                 /**< USB Control register, offset: 0x100 */
  uint8_t RESERVED_22[3];
  uint8_t OBSERVE;                                 /**< USB OTG Observe register, offset: 0x104 */
  uint8_t RESERVED_23[3];
  uint8_t CONTROL;                                 /**< USB OTG Control register, offset: 0x108 */
  uint8_t RESERVED_24[3];
  uint8_t USBTRC0;                                 /**< USB Transceiver Control Register 0, offset: 0x10C */
  uint8_t RESERVED_25[7];
  uint8_t USBFRMADJUST;                            /**< Frame Adjust Register, offset: 0x114 */
} volatile *USB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- USB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Accessor_Macros USB - Register accessor macros
 * @{
 */


/* USB - Register accessors */
#line 11623 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group USB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- USB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Masks USB Register Masks
 * @{
 */

/* PERID Bit Fields */



/* IDCOMP Bit Fields */



/* REV Bit Fields */



/* ADDINFO Bit Fields */





/* OTGISTAT Bit Fields */
#line 11669 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* OTGICR Bit Fields */
#line 11682 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* OTGSTAT Bit Fields */
#line 11695 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* OTGCTL Bit Fields */
#line 11704 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ISTAT Bit Fields */
#line 11721 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* INTEN Bit Fields */
#line 11738 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ERRSTAT Bit Fields */
#line 11753 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ERREN Bit Fields */
#line 11768 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* STAT Bit Fields */
#line 11776 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CTL Bit Fields */
#line 11793 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* ADDR Bit Fields */





/* BDTPAGE1 Bit Fields */



/* FRMNUML Bit Fields */



/* FRMNUMH Bit Fields */



/* TOKEN Bit Fields */
#line 11818 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* SOFTHLD Bit Fields */



/* BDTPAGE2 Bit Fields */



/* BDTPAGE3 Bit Fields */



/* ENDPT Bit Fields */
#line 11845 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* USBCTRL Bit Fields */




/* OBSERVE Bit Fields */
#line 11857 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CONTROL Bit Fields */


/* USBTRC0 Bit Fields */
#line 11869 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* USBFRMADJUST Bit Fields */




/*!
 * @}
 */ /* end of group USB_Register_Masks */


/* USB - Peripheral instance base addresses */
/** Peripheral USB0 base pointer */

/** Array initializer of USB peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- USB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Accessor_Macros USB - Register accessor macros
 * @{
 */


/* USB - Register instance definitions */
/* USB0 */
#line 11940 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* USB - Register array accessors */


/*!
 * @}
 */ /* end of group USB_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group USB_Peripheral */


/* ----------------------------------------------------------------------------
   -- USBDCD
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBDCD_Peripheral USBDCD
 * @{
 */

/** USBDCD - Peripheral register structure */
typedef struct USBDCD_MemMap {
  uint32_t CONTROL;                                /**< Control register, offset: 0x0 */
  uint32_t CLOCK;                                  /**< Clock register, offset: 0x4 */
  uint32_t STATUS;                                 /**< Status register, offset: 0x8 */
  uint8_t RESERVED_0[4];
  uint32_t TIMER0;                                 /**< TIMER0 register, offset: 0x10 */
  uint32_t TIMER1;                                 /**< TIMER1 register, offset: 0x14 */
  uint32_t TIMER2;                                 /**< TIMER2 register, offset: 0x18 */
} volatile *USBDCD_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- USBDCD - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBDCD_Register_Accessor_Macros USBDCD - Register accessor macros
 * @{
 */


/* USBDCD - Register accessors */
#line 11991 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group USBDCD_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- USBDCD Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBDCD_Register_Masks USBDCD Register Masks
 * @{
 */

/* CONTROL Bit Fields */
#line 12017 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* CLOCK Bit Fields */





/* STATUS Bit Fields */
#line 12036 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TIMER0 Bit Fields */
#line 12043 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TIMER1 Bit Fields */
#line 12050 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* TIMER2 Bit Fields */
#line 12057 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group USBDCD_Register_Masks */


/* USBDCD - Peripheral instance base addresses */
/** Peripheral USBDCD base pointer */

/** Array initializer of USBDCD peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- USBDCD - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USBDCD_Register_Accessor_Macros USBDCD - Register accessor macros
 * @{
 */


/* USBDCD - Register instance definitions */
/* USBDCD */
#line 12087 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group USBDCD_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group USBDCD_Peripheral */


/* ----------------------------------------------------------------------------
   -- VREF
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Peripheral VREF
 * @{
 */

/** VREF - Peripheral register structure */
typedef struct VREF_MemMap {
  uint8_t TRM;                                     /**< VREF Trim Register, offset: 0x0 */
  uint8_t SC;                                      /**< VREF Status and Control Register, offset: 0x1 */
} volatile *VREF_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- VREF - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Register_Accessor_Macros VREF - Register accessor macros
 * @{
 */


/* VREF - Register accessors */



/*!
 * @}
 */ /* end of group VREF_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- VREF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Register_Masks VREF Register Masks
 * @{
 */

/* TRM Bit Fields */





/* SC Bit Fields */
#line 12159 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group VREF_Register_Masks */


/* VREF - Peripheral instance base addresses */
/** Peripheral VREF base pointer */

/** Array initializer of VREF peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- VREF - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Register_Accessor_Macros VREF - Register accessor macros
 * @{
 */


/* VREF - Register instance definitions */
/* VREF */



/*!
 * @}
 */ /* end of group VREF_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group VREF_Peripheral */


/* ----------------------------------------------------------------------------
   -- WDOG
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Peripheral WDOG
 * @{
 */

/** WDOG - Peripheral register structure */
typedef struct WDOG_MemMap {
  uint16_t STCTRLH;                                /**< Watchdog Status and Control Register High, offset: 0x0 */
  uint16_t STCTRLL;                                /**< Watchdog Status and Control Register Low, offset: 0x2 */
  uint16_t TOVALH;                                 /**< Watchdog Time-out Value Register High, offset: 0x4 */
  uint16_t TOVALL;                                 /**< Watchdog Time-out Value Register Low, offset: 0x6 */
  uint16_t WINH;                                   /**< Watchdog Window Register High, offset: 0x8 */
  uint16_t WINL;                                   /**< Watchdog Window Register Low, offset: 0xA */
  uint16_t REFRESH;                                /**< Watchdog Refresh register, offset: 0xC */
  uint16_t UNLOCK;                                 /**< Watchdog Unlock register, offset: 0xE */
  uint16_t TMROUTH;                                /**< Watchdog Timer Output Register High, offset: 0x10 */
  uint16_t TMROUTL;                                /**< Watchdog Timer Output Register Low, offset: 0x12 */
  uint16_t RSTCNT;                                 /**< Watchdog Reset Count register, offset: 0x14 */
  uint16_t PRESC;                                  /**< Watchdog Prescaler register, offset: 0x16 */
} volatile *WDOG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register accessors */
#line 12244 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */

/* STCTRLH Bit Fields */
#line 12285 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
/* STCTRLL Bit Fields */


/* TOVALH Bit Fields */



/* TOVALL Bit Fields */



/* WINH Bit Fields */



/* WINL Bit Fields */



/* REFRESH Bit Fields */



/* UNLOCK Bit Fields */



/* TMROUTH Bit Fields */



/* TMROUTL Bit Fields */



/* RSTCNT Bit Fields */



/* PRESC Bit Fields */




/*!
 * @}
 */ /* end of group WDOG_Register_Masks */


/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG base pointer */

/** Array initializer of WDOG peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- WDOG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Accessor_Macros WDOG - Register accessor macros
 * @{
 */


/* WDOG - Register instance definitions */
/* WDOG */
#line 12364 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group WDOG_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group WDOG_Peripheral */


/*
** End of section using anonymous unions
*/

#line 12386 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"
  #pragma language=default




/*!
 * @}
 */ /* end of group Peripheral_defines */


/* ----------------------------------------------------------------------------
   -- Backward Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Backward_Compatibility_Symbols Backward Compatibility
 * @{
 */

#line 12551 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/*!
 * @}
 */ /* end of group Backward_Compatibility_Symbols */


#line 12565 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MK21D5.h"

/* MK21D5.h, eof. */
#line 48 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"
#line 57 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"


#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\cfg\\MK21D512_cfg.h"
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file MK21D512.h
* This file contains configuration options for the above processor
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

/**************************************************/
/** USER SETTINGS OF KINETIS MCU */
/**  Kinetis ARM Cortex-M4 model */








/*  in the case of using USB VIRTUAL SERIAL LINK you must activate No break TRIM CHECKBOX in the master AN2295 PC Application  */
/*  the break impulse is replaced by using only 9 bits zero impulse  */
//  BREAK IMPULSE       |START| |0| |0| |0| |0| |0| |0| |0| |0| |0| |0| STOP|
//  ZERO IMPULSE        |START| |0| |0| |0| |0| |0| |0| |0| |0| |0| |STOP|



/** Kinetis Flash memory size */



/** Bootloader flash protection */


/** Boot timeout after POR (Power On Reset) for wait to connect Master **/
/** BOOT_WAITING_TIMEOUT * 10ms **/


/**************************************************/
/* Actual used UART module */




/* Actual used UART module */
/* A range of UART baudrates is (9600 - 115200) */
//#define BOOT_UART_BAUD_RATE  9600 
//#define BOOT_UART_BAUD_RATE    14400
//#define BOOT_UART_BAUD_RATE    19200 
//#define BOOT_UART_BAUD_RATE  38400 

//#define BOOT_UART_BAUD_RATE  76800 
//#define BOOT_UART_BAUD_RATE  115200 
//#define BOOT_UART_BAUD_RATE  128000 
/** GPIO & UART pins initialization */






/*  setting of multiplexer for UART alternative of pin */


/*  setting of multiplexer for GPIO alternative of pin */






/**************************************************/
/* Actual used PIN reset setting */








/* CRC module clock gating info */


/**************************************************/
/** BOOTLOADER FEATURES SETTINGS */











/**************************************************/
/** CALIBRATION OF BOOTLOADER TRIM SETTINGS */

/******************************************************************************
*
*
*     Advanced detail settings for non standard settings
*
*
******************************************************************************/



/* Flash block count of this MCU */


/* Start address of interrupt vector table */ 


/* Start address of relocated interrutp vector table */


/* Flash start address */


/* Flash end address */
//#define USER_FLASH_END 0x0003FFFF

/* Flash2 start address */
//#define USER_FLASH_START_2 0x00040000

/* Flash2 end address */
//#define USER_FLASH_END_2 0x0005FFFF

/* Size of write block */


/* Size of erase block */


/* Maximal length of ID_STRING */
//#define ID_STRING_MAX 5

/* Description string */
#line 61 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"
#line 72 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"





/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */

/*
 * Name: gFlashProtection_c
 * Description: The value for FPROT register. By default the Flash is not Protected
 */





/*
 * Name: gFlashProtection_c
 * Description: The value for FPROT register. By default the Flash is not Protected
 */

// #define gFlashProtection_c 0xFFFFFFFE /* The first Flash region is write protected */


/*
 * Name: gMcuFlashBlocks_c
 * Description: The number of the internal flash blocks
 */


/*
 * Name: gMcuFlashSize_c
 * Description: The size of the internal FLASH
 */


/*
 * Name: gFlashErasePage_c
 * Description: The minimum amount of FLASH that can be erased
 */



/*
 * Name: gUserFlashStart_d
 * Description: Starting point of the application
 */


#line 137 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"
/*
 * Name: gBootImageFlagsAddress_c
 * Description: The flasg are located after the interrupt vector!
 */


/*
 * Name: gBootProductInfoAddress_c
 * Description: Address of the ProductInfo
 *              The Product info is located in the last sector of the FLASH
 */


/*
 * Name: gInternalStorageStartAddress_c
 * Description: The start address of the internal storage
 */


/* Defines how the bootloader should handle errors */






/* Defines used for implementing the boolean types when working with Flash */




/* Init value for the mask used to look through each byte in the bitmap that
indicates which Flash sectors are write protected and should not be updated */
#line 178 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"








/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
/*
 * Name: FlashConfig_t
 * Description: Structure used to access Flash Configuration
 */
typedef union _FlashConfig_t
{
  uint32_t Data[4];
  struct {
    uint32_t BackDoorKey[2];
    uint32_t Protection;
    uint32_t Config;
  };
} FlashConfig_t;

/*
 * Name: bootFlags_t
 * Description: Structure used to inform the Bootloader if a new Image needs
 *              to be loaded.
 */
typedef __packed struct
{
  uint8_t  newBootImageAvailable[1];
  uint8_t  bootProcessCompleted[1];
  uint8_t  bootVersion[2];
}bootInfo_t;

typedef void (*vector_entry)(void);
typedef void pointer(void);

/******************************************************************************
 *******************************************************************************
 * Public memory declarations
 *******************************************************************************
 ******************************************************************************/

    extern uint32_t __BOOT_STACK_ADDRESS[];




extern uint32_t __region_BOOT_ROM_start__[];
extern uint32_t __region_BOOT_ROM_end__[];

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
void __thumb_startup(void);
int main(int argc, char **argv);
void defaultISR(void);
void Boot_ResetMCU(void);





#line 40 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.c"
#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\flash\\flash_boot_kinetis.h"
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file filename.h
* This file brief description
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






/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
//  Flash hardware algorithm operation commands
#line 65 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\flash\\flash_boot_kinetis.h"










        
#line 82 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\flash\\flash_boot_kinetis.h"




/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
//  FCOOB register structure
typedef union
{
  uint8_t all[12];
  struct
  {
    uint8_t fccob3;
    uint8_t fccob2;
    uint8_t fccob1;
    uint8_t fccob0;
    uint8_t fccob7;
    uint8_t fccob6;
    uint8_t fccob5;
    uint8_t fccob4;
    uint8_t fccobB;
    uint8_t fccobA;
    uint8_t fccob9;
    uint8_t fccob8;
  }regs;

  struct
  {
    uint32_t fccob3210;
    uint32_t fccob7654;
    uint32_t fccobBA98;
  }regsLong;
}FCC0B_STR;


/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */

//  API FUNCTION FOR KINETIS FLASH DRIVER
void FlashInitialization(void);
uint8_t FLASH_EraseSector(uint32_t destination);
uint8_t FLASH_Program(uint32_t dest, uint32_t source, uint32_t size);
uint8_t FLASH_ProgramLongWords(uint32_t destination, uint32_t source, uint32_t size);
uint8_t FLASH_ProgramLongWord(uint32_t destination, uint32_t data);
uint8_t FLASH_ProgramSection(uint32_t destination, uint32_t* pSource, uint32_t size);
uint8_t FLASH_ProgramSectionPhrases(uint32_t destination, uint32_t* pSource, uint32_t size);
uint8_t FLASH_ProgramSectionDoublePhrases(uint32_t destination, uint32_t* pSource, uint32_t size);
uint8_t FLASH_MassErase(void);
uint8_t FLASH_SetEEEEnable(uint8_t ctrl_code);





#line 41 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.c"
#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\UartBootloader.h"
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
* \file UartBootloader.h
* UART Bootloader Interface file
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






/******************************************************************************
 *******************************************************************************
 * Public macros
 *******************************************************************************
 ******************************************************************************/





/******************************************************************************
 *******************************************************************************
 * Public type definitions
 *******************************************************************************
 ******************************************************************************/




/******************************************************************************
 *******************************************************************************
 * Public memory declarations
 *******************************************************************************
 ******************************************************************************/


/******************************************************************************
 *******************************************************************************
 * Public function prototypes
 *******************************************************************************
 ******************************************************************************/
extern void CheckForUartLoader(void);





#line 43 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.c"


/*! *********************************************************************************
*************************************************************************************
* Private Memory Declarations
*************************************************************************************
********************************************************************************** */

#pragma section = "IntVectTable"
#pragma location = "IntVectTable"
__root const vector_entry __vector_table[16] =
{
    (pointer*)__BOOT_STACK_ADDRESS,  /* Initial SP           */







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


#pragma location = "FlashConfig"
__root const FlashConfig_t gFlashConfig @ "FlashConfig" =



{
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE}
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
    return *((uint32_t*)(((1<<19) - 2048) + (0x44)));
}


/*! *********************************************************************************
* \brief   The function resets the MCU
*
********************************************************************************** */
void Boot_ResetMCU(void)
{
    ((((SCB_MemMapPtr)0xE000E000u))->AIRCR) = (((uint32_t)(((uint32_t)(0x5FA))<<16))&0xFFFF0000u) | 0x4u;
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
    if (0xFFFFFFFF == gBootStorageStartAddress)
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
    if (0xFFFFFFFF == gBootStorageStartAddress)
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
    static uint8_t bitmapBuffer[(32)];
    bootInfo_t flags;
    uint8_t  buffer[2048];
    uint32_t remaingImgSize, len;
    uint32_t flashAddr      = 0;
    uint8_t  bitMask        = 0x01;
    uint8_t *pBitmap        = bitmapBuffer;






    /* Check if we have a valid internal storage start address. */
    gBootStorageStartAddress = Boot_GetInternalStorageStartAddr();

    /* Init the flash module */
    FlashInitialization();

    /* Init the external storage */
    Boot_InitExternalStorage();

    /* Read image size */
    if (Boot_ReadExternalStorage(0x04,0x00, (uint8_t*)(&remaingImgSize)))
        Boot_ResetMCU();;

    /* Read sector bitmap */
    if (Boot_ReadExternalStorage((32), (0x00 + 0x04), bitmapBuffer))
        Boot_ResetMCU();;

    /* Start writing the image. Do not alter the last sector which contains HW specific data! */
    while (flashAddr < ((1<<19) - 2048))
    {
        if (remaingImgSize > 2048)
            len = 2048;
        else
            len = remaingImgSize;

        /* Check if bitmap indicates that this sector is write protected and shouldn't be updated */
        if ((*pBitmap & bitMask) && (flashAddr >= ((uint32_t)(__region_BOOT_ROM_end__) + 1)))
        {
            /* Erase Flash sector */
            if (0 != FLASH_EraseSector(flashAddr))
                Boot_ResetMCU();;

            if (len)
            {
                /* Read a new image block */
                if (Boot_ReadExternalStorage(len, flashAddr + ((0x00 + 0x04) + (32)), buffer))
                    Boot_ResetMCU();;


                if( (flashAddr <= (((uint32_t)(__region_BOOT_ROM_end__) + 1) + (256*4))) && (flashAddr + len > (((uint32_t)(__region_BOOT_ROM_end__) + 1) + (256*4))) )
                {
                    uint32_t i, offset = (((uint32_t)(__region_BOOT_ROM_end__) + 1) + (256*4)) - flashAddr;
                    /* Program the Flash before boot flags */
                    if(0 != FLASH_Program(flashAddr, (uint32_t)buffer, offset))
                        Boot_ResetMCU();;

                    /* Keep the boot flags set  until the all image is downloaded */
                    for( i=0; i<1; i++ )
                    {
                        flags.newBootImageAvailable[i] = 0xFF;
                        flags.bootProcessCompleted[i] = 0x00;
                    }
                    i = offset + 2 * 1;
                    flags.bootVersion[0] = buffer[i++];
                    flags.bootVersion[1] = buffer[i];
                    offset += (sizeof(bootInfo_t));

                    /* Program the Flash after the boot flags*/
                    if(0 != FLASH_Program(flashAddr + offset, (uint32_t)(&buffer[offset]), len - offset))
                        Boot_ResetMCU();;
                }
                else
                {
                    /* Program the image block to Flash */
                    if(0 != FLASH_Program(flashAddr, (uint32_t)buffer, len))
                        Boot_ResetMCU();;
                }
            }
        }

        /* Update Bitmask */
        bitMask <<= 1;
        if (bitMask == 0)
        {
            /* This was last bit in the current bitmap byte. Move to next bitmap byte */
            bitMask = 0x01;
            pBitmap++;
        }

        /* Update the current flash address */
        flashAddr += 2048;

        /* Update the remaining bytes*/
        if (remaingImgSize)
            remaingImgSize -= len;
    } /* while */

#line 396 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.c"


    /* Set the bBootProcessCompleted Flag */
    if( 0 != FLASH_Program((uint32_t)(((uint32_t)(__region_BOOT_ROM_end__) + 1) + (256*4)), (uint32_t)&flags, sizeof(flags)) )
        Boot_ResetMCU();;

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
    ((((SCB_MemMapPtr)0xE000E000u))->VTOR) = (uint32_t)__region_BOOT_ROM_start__;

    /* Disable watchdog */

    ((((WDOG_MemMapPtr)0x40052000u))->UNLOCK) = 0xC520;
    ((((WDOG_MemMapPtr)0x40052000u))->UNLOCK) = 0xD928;
    ((((WDOG_MemMapPtr)0x40052000u))->STCTRLH) &= ~0x1u;
#line 454 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.c"
    /* Check if there is no boot image available in the external EEPROM and if eventually
    the booting of the previous one has been completed. If both conditions are met, start
    running the application in the internal Flash. Else, start the process of booting from
    external EEPROM */
    gpBootInfo = (bootInfo_t*)(((uint32_t)(__region_BOOT_ROM_end__) + 1) + (256*4));
    /*
    if( (gpBootInfo->newBootImageAvailable == gBootValueForTRUE_c) &&
    (gpBootInfo->bootProcessCompleted ==  gBootValueForFALSE_c) )
    */
    if ((gpBootInfo->newBootImageAvailable[0] != 0x00) &&
        (gpBootInfo->bootProcessCompleted[0] ==  0x00))
    {
        /* Set the start address of the interrupt vector*/
        ((((SCB_MemMapPtr)0xE000E000u))->VTOR) = ((uint32_t)(__region_BOOT_ROM_end__) + 1);
        JumpToApplication(((uint32_t)(__region_BOOT_ROM_end__) + 1));
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
    Boot_ResetMCU();;
}
//-----------------------------------------------------------------------------
