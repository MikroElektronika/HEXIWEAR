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
#line 80 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\eeprom\\Eeprom_Boot.h"












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

#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/*
** ###################################################################
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    MKW40Z160VHT4RM Rev 0.0, 5/2014
**     Version:             rev. 1.0, 2014-07-18
**     Build:               b140721
**
**     Abstract:
**         This header file implements peripheral memory map for MKW40Z4
**         processor.
**
**     Copyright (c) 1997 - 2014 Freescale Semiconductor, Inc.
**     All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2014-07-18)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file MKW40Z4.h
 * @version 1.0
 * @date 2014-07-18
 * @brief Peripheral memory map for MKW40Z4
 *
 * This header file implements peripheral memory map for MKW40Z4 processor.
 */


/* ----------------------------------------------------------------------------
   -- MCU activation
   ---------------------------------------------------------------------------- */

/* Prevention from multiple including the same memory map */


/* Check if another memory map has not been also included */





/** Memory map major version (memory maps with equal major version number are
 * compatible) */

/** Memory map minor version */



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
  INT_Reserved4                = 4,                /**< Reserved interrupt */
  INT_Reserved5                = 5,                /**< Reserved interrupt */
  INT_Reserved6                = 6,                /**< Reserved interrupt */
  INT_Reserved7                = 7,                /**< Reserved interrupt */
  INT_Reserved8                = 8,                /**< Reserved interrupt */
  INT_Reserved9                = 9,                /**< Reserved interrupt */
  INT_Reserved10               = 10,               /**< Reserved interrupt */
  INT_SVCall                   = 11,               /**< Supervisor call (SVCall) */
  INT_Reserved12               = 12,               /**< Reserved interrupt */
  INT_Reserved13               = 13,               /**< Reserved interrupt */
  INT_PendableSrvReq           = 14,               /**< Pendable request for system service (PendableSrvReq) */
  INT_SysTick                  = 15,               /**< System tick timer (SysTick) */
  INT_DMA0                     = 16,               /**< DMA channel 0 transfer complete */
  INT_DMA1                     = 17,               /**< DMA channel 1 transfer complete */
  INT_DMA2                     = 18,               /**< DMA channel 2 transfer complete */
  INT_DMA3                     = 19,               /**< DMA channel 3 transfer complete */
  INT_Reserved20               = 20,               /**< Reserved interrupt */
  INT_FTFA                     = 21,               /**< Command complete and read collision */
  INT_PMC_DCDC                 = 22,               /**< Low-voltage detect, low-voltage warning, DCDC PSWITCH interrupt */
  INT_LLWU                     = 23,               /**< Low Leakage Wakeup */
  INT_I2C0                     = 24,               /**< I2C0 interrupt */
  INT_Reserved25               = 25,               /**< Reserved interrupt */
  INT_SPI0                     = 26,               /**< SPI0 single interrupt vector for all sources */
  INT_TSI                      = 27,               /**< TSI  interrupt */
  INT_UART0                    = 28,               /**< UART0 status and error */
  INT_TRNG                     = 29,               /**< TRNG interrupt */
  INT_CMT                      = 30,               /**< CMT interrupt */
  INT_ADC0                     = 31,               /**< ADC0 interrupt */
  INT_CMP0                     = 32,               /**< CMP0 interrupt */
  INT_TPM0                     = 33,               /**< TPM0 single interrupt vector for all sources */
  INT_TPM1                     = 34,               /**< TPM1 single interrupt vector for all sources */
  INT_TPM2                     = 35,               /**< TPM2 single interrupt vector for all sources */
  INT_RTC                      = 36,               /**< Real time clock */
  INT_RTC_Seconds              = 37,               /**< Real time clock seconds */
  INT_PIT0                     = 38,               /**< Periodic interrupt timer */
  INT_AESA                     = 39,               /**< AESA interrupt */
  INT_BTLL_RSIM                = 40,               /**< Bluetooth LL interrupt and DSM exit interrupt */
  INT_DAC0                     = 41,               /**< DAC0 interrupt */
  INT_ZigBee                   = 42,               /**< ZigBee interrupt */
  INT_MCG                      = 43,               /**< MCG interrupt */
  INT_LPTMR0                   = 44,               /**< LPTMR0 interrupt */
  INT_SPI1                     = 45,               /**< SPI1 single interrupt vector for all sources */
  INT_PORTA                    = 46,               /**< GPIOA Pin detect */
  INT_PORTBC                   = 47                /**< Single interrupt vector for GPIOB; GPIOC; GPIOD; GPIOE Pin detect */
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

#line 148 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
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
  uint32_t CV[2];                                  /**< Compare Value Registers, array offset: 0x18, array step: 0x4 */
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
#line 226 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 251 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CFG1 Bit Fields */
#line 265 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CFG2 Bit Fields */
#line 275 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* R Bit Fields */



/* CV Bit Fields */



/* SC2 Bit Fields */
#line 299 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SC3 Bit Fields */
#line 311 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
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
/** Peripheral ADC base pointer */

/** Array initializer of ADC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- ADC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Accessor_Macros ADC - Register accessor macros
 * @{
 */


/* ADC - Register instance definitions */
/* ADC */
#line 430 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* ADC - Register array accessors */




/*!
 * @}
 */ /* end of group ADC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ADC_Peripheral */


/* ----------------------------------------------------------------------------
   -- BP
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Peripheral BP
 * @{
 */

/** BP - Peripheral register structure */
typedef struct BP_MemMap {
  uint32_t CTRL;                                   /**< FlashPatch Control Register, offset: 0x0 */
  uint8_t RESERVED_0[4];
  uint32_t COMP[2];                                /**< FlashPatch Comparator Register 0..FlashPatch Comparator Register 1, array offset: 0x8, array step: 0x4 */
  uint8_t RESERVED_1[4032];
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
} volatile *BP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register accessors */
#line 500 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- BP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Masks BP Register Masks
 * @{
 */


/*!
 * @}
 */ /* end of group BP_Register_Masks */


/* BP - Peripheral instance base addresses */
/** Peripheral BP base pointer */

/** Array initializer of BP peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- BP - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BP_Register_Accessor_Macros BP - Register accessor macros
 * @{
 */


/* BP - Register instance definitions */
/* BP */
#line 554 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* BP - Register array accessors */


/*!
 * @}
 */ /* end of group BP_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group BP_Peripheral */


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
#line 604 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 626 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CR1 Bit Fields */
#line 643 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FPR Bit Fields */



/* SCR Bit Fields */
#line 660 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* DACCR Bit Fields */
#line 668 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* MUXCR Bit Fields */
#line 677 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group CMP_Register_Masks */


/* CMP - Peripheral instance base addresses */
/** Peripheral CMP0 base pointer */

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
#line 707 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 766 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 804 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* MSC Bit Fields */
#line 820 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
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
#line 879 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group CMT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group CMT_Peripheral */


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
  } DAT[2];
  uint8_t RESERVED_0[28];
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
#line 1020 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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




/* C0 Bit Fields */
#line 1063 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* C1 Bit Fields */
#line 1070 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* C2 Bit Fields */





/*!
 * @}
 */ /* end of group DAC_Register_Masks */


/* DAC - Peripheral instance base addresses */
/** Peripheral DAC base pointer */

/** Array initializer of DAC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- DAC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DAC_Register_Accessor_Macros DAC - Register accessor macros
 * @{
 */


/* DAC - Register instance definitions */
/* DAC */
#line 1107 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* DAC - Register array accessors */



/*!
 * @}
 */ /* end of group DAC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DAC_Peripheral */


/* ----------------------------------------------------------------------------
   -- DCDC
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DCDC_Peripheral DCDC
 * @{
 */

/** DCDC - Peripheral register structure */
typedef struct DCDC_MemMap {
  uint32_t REG0;                                   /**< DCDC REGISTER 0, offset: 0x0 */
  uint32_t REG1;                                   /**< DCDC REGISTER 1, offset: 0x4 */
  uint32_t REG2;                                   /**< DCDC REGISTER 2, offset: 0x8 */
  uint32_t REG3;                                   /**< DCDC REGISTER 3, offset: 0xC */
  uint32_t REG4;                                   /**< DCDC REGISTER 4, offset: 0x10 */
  uint8_t RESERVED_0[4];
  uint32_t REG6;                                   /**< DCDC REGISTER 6, offset: 0x18 */
  uint32_t REG7;                                   /**< DCDC REGISTER 7, offset: 0x1C */
} volatile *DCDC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DCDC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DCDC_Register_Accessor_Macros DCDC - Register accessor macros
 * @{
 */


/* DCDC - Register accessors */
#line 1161 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group DCDC_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- DCDC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DCDC_Register_Masks DCDC Register Masks
 * @{
 */

/* REG0 Bit Fields */
#line 1216 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* REG1 Bit Fields */
#line 1231 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* REG2 Bit Fields */
#line 1247 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* REG3 Bit Fields */
#line 1276 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* REG4 Bit Fields */





/* REG6 Bit Fields */
#line 1293 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* REG7 Bit Fields */
#line 1301 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group DCDC_Register_Masks */


/* DCDC - Peripheral instance base addresses */
/** Peripheral DCDC base pointer */

/** Array initializer of DCDC peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- DCDC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DCDC_Register_Accessor_Macros DCDC - Register accessor macros
 * @{
 */


/* DCDC - Register instance definitions */
/* DCDC */
#line 1332 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group DCDC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DCDC_Peripheral */


/* ----------------------------------------------------------------------------
   -- DMA
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral DMA
 * @{
 */

/** DMA - Peripheral register structure */
typedef struct DMA_MemMap {
  uint8_t RESERVED_0[256];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    uint32_t SAR;                                    /**< Source Address Register, array offset: 0x100, array step: 0x10 */
    uint32_t DAR;                                    /**< Destination Address Register, array offset: 0x104, array step: 0x10 */
    union {                                          /* offset: 0x108, array step: 0x10 */
      uint32_t DSR_BCR;                                /**< DMA Status Register / Byte Count Register, array offset: 0x108, array step: 0x10 */
    };
    uint32_t DCR;                                    /**< DMA Control Register, array offset: 0x10C, array step: 0x10 */
  } DMA[4];
} volatile *DMA_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DMA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Accessor_Macros DMA - Register accessor macros
 * @{
 */


/* DMA - Register accessors */





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

/* SAR Bit Fields */



/* DAR Bit Fields */



/* DSR_BCR Bit Fields */
#line 1419 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* DCR Bit Fields */
#line 1459 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 1499 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* DMA - Register array accessors */





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
  uint8_t CHCFG[4];                                /**< Channel Configuration register, array offset: 0x0, array step: 0x1 */
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
#line 1565 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
  uint8_t RESERVED_0[24];
  uint32_t PCSR;                                   /**< Program Counter Sample Register, offset: 0x1C */
  struct {                                         /* offset: 0x20, array step: 0x10 */
    uint32_t COMP;                                   /**< Comparator Register 0..Comparator Register 1, array offset: 0x20, array step: 0x10 */
    uint32_t MASK;                                   /**< Mask Register 0..Mask Register 1, array offset: 0x24, array step: 0x10 */
    uint32_t FUNCTION;                               /**< Function Register 0..Function Register 1, array offset: 0x28, array step: 0x10 */
    uint8_t RESERVED_0[4];
  } COMPARATOR[2];
} volatile *DWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DWT_Register_Accessor_Macros DWT - Register accessor macros
 * @{
 */


/* DWT - Register accessors */






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
#line 1692 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* DWT - Register array accessors */




/*!
 * @}
 */ /* end of group DWT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group DWT_Peripheral */


/* ----------------------------------------------------------------------------
   -- FGPIO
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Peripheral FGPIO
 * @{
 */

/** FGPIO - Peripheral register structure */
typedef struct FGPIO_MemMap {
  uint32_t PDOR;                                   /**< Port Data Output Register, offset: 0x0 */
  uint32_t PSOR;                                   /**< Port Set Output Register, offset: 0x4 */
  uint32_t PCOR;                                   /**< Port Clear Output Register, offset: 0x8 */
  uint32_t PTOR;                                   /**< Port Toggle Output Register, offset: 0xC */
  uint32_t PDIR;                                   /**< Port Data Input Register, offset: 0x10 */
  uint32_t PDDR;                                   /**< Port Data Direction Register, offset: 0x14 */
} volatile *FGPIO_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FGPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Accessor_Macros FGPIO - Register accessor macros
 * @{
 */


/* FGPIO - Register accessors */
#line 1744 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group FGPIO_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FGPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Masks FGPIO Register Masks
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
 */ /* end of group FGPIO_Register_Masks */


/* FGPIO - Peripheral instance base addresses */
/** Peripheral FPTA base pointer */

/** Peripheral FPTB base pointer */

/** Peripheral FPTC base pointer */

/** Array initializer of FGPIO peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- FGPIO - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FGPIO_Register_Accessor_Macros FGPIO - Register accessor macros
 * @{
 */


/* FGPIO - Register instance definitions */
/* FPTA */
#line 1817 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FPTB */
#line 1824 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FPTC */
#line 1831 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group FGPIO_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FGPIO_Peripheral */


/* ----------------------------------------------------------------------------
   -- FTFA
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Peripheral FTFA
 * @{
 */

/** FTFA - Peripheral register structure */
typedef struct FTFA_MemMap {
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
  uint8_t RESERVED_0[4];
  uint8_t XACC[8];                                 /**< Execute-only Access Registers, array offset: 0x18, array step: 0x1 */
  uint8_t SACC[8];                                 /**< Supervisor-only Access Registers, array offset: 0x20, array step: 0x1 */
  uint8_t FACSS;                                   /**< Flash Access Segment Size Register, offset: 0x28 */
  uint8_t RESERVED_1[2];
  uint8_t FACSN;                                   /**< Flash Access Segment Number Register, offset: 0x2B */
} volatile *FTFA_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FTFA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Register_Accessor_Macros FTFA - Register accessor macros
 * @{
 */


/* FTFA - Register accessors */
#line 1902 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group FTFA_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- FTFA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Register_Masks FTFA Register Masks
 * @{
 */

/* FSTAT Bit Fields */
#line 1928 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FCNFG Bit Fields */
#line 1937 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FSEC Bit Fields */
#line 1950 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FOPT Bit Fields */



/* FCCOB Bit Fields */



/* FPROT Bit Fields */



/* XACC Bit Fields */



/* SACC Bit Fields */



/* FACSS Bit Fields */



/* FACSN Bit Fields */




/*!
 * @}
 */ /* end of group FTFA_Register_Masks */


/* FTFA - Peripheral instance base addresses */
/** Peripheral FTFA base pointer */

/** Array initializer of FTFA peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- FTFA - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Register_Accessor_Macros FTFA - Register accessor macros
 * @{
 */


/* FTFA - Register instance definitions */
/* FTFA */
#line 2040 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* FTFA - Register array accessors */





/*!
 * @}
 */ /* end of group FTFA_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group FTFA_Peripheral */


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
#line 2093 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 2166 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PTB */
#line 2173 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PTC */
#line 2180 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
  uint8_t FLT;                                     /**< I2C Programmable Input Glitch Filter Register, offset: 0x6 */
  uint8_t RA;                                      /**< I2C Range Address register, offset: 0x7 */
  uint8_t SMB;                                     /**< I2C SMBus Control and Status register, offset: 0x8 */
  uint8_t A2;                                      /**< I2C Address Register 2, offset: 0x9 */
  uint8_t SLTH;                                    /**< I2C SCL Low Timeout Register High, offset: 0xA */
  uint8_t SLTL;                                    /**< I2C SCL Low Timeout Register Low, offset: 0xB */
  uint8_t S2;                                      /**< I2C Status register 2, offset: 0xC */
} volatile *I2C_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- I2C - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Accessor_Macros I2C - Register accessor macros
 * @{
 */


/* I2C - Register accessors */
#line 2241 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 2267 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* C1 Bit Fields */
#line 2284 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* S Bit Fields */
#line 2301 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* D Bit Fields */



/* C2 Bit Fields */
#line 2319 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FLT Bit Fields */
#line 2329 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* RA Bit Fields */



/* SMB Bit Fields */
#line 2350 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* A2 Bit Fields */



/* SLTH Bit Fields */



/* SLTL Bit Fields */



/* S2 Bit Fields */





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
#line 2406 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* I2C1 */
#line 2420 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group I2C_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group I2C_Peripheral */


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
} volatile *LLWU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LLWU - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Accessor_Macros LLWU - Register accessor macros
 * @{
 */


/* LLWU - Register accessors */
#line 2475 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 2503 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PE2 Bit Fields */
#line 2516 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PE3 Bit Fields */
#line 2529 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PE4 Bit Fields */
#line 2542 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* ME Bit Fields */
#line 2559 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* F1 Bit Fields */
#line 2576 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* F2 Bit Fields */
#line 2593 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* F3 Bit Fields */
#line 2610 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FILT1 Bit Fields */
#line 2619 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FILT2 Bit Fields */
#line 2628 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 2662 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 2736 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PSR Bit Fields */
#line 2745 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CMR Bit Fields */



/* CNR Bit Fields */




/*!
 * @}
 */ /* end of group LPTMR_Register_Masks */


/* LPTMR - Peripheral instance base addresses */
/** Peripheral LPTMR base pointer */

/** Array initializer of LPTMR peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- LPTMR - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Accessor_Macros LPTMR - Register accessor macros
 * @{
 */


/* LPTMR - Register instance definitions */
/* LPTMR */





/*!
 * @}
 */ /* end of group LPTMR_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group LPTMR_Peripheral */


/* ----------------------------------------------------------------------------
   -- LPUART
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Peripheral LPUART
 * @{
 */

/** LPUART - Peripheral register structure */
typedef struct LPUART_MemMap {
  uint32_t BAUD;                                   /**< LPUART Baud Rate Register, offset: 0x0 */
  uint32_t STAT;                                   /**< LPUART Status Register, offset: 0x4 */
  uint32_t CTRL;                                   /**< LPUART Control Register, offset: 0x8 */
  uint32_t DATA;                                   /**< LPUART Data Register, offset: 0xC */
  uint32_t MATCH;                                  /**< LPUART Match Address Register, offset: 0x10 */
  uint32_t MODIR;                                  /**< LPUART Modem IrDA Register, offset: 0x14 */
  uint32_t FIFO;                                   /**< LPUART FIFO Register, offset: 0x18 */
  uint32_t WATER;                                  /**< LPUART Watermark Register, offset: 0x1C */
} volatile *LPUART_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LPUART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Register_Accessor_Macros LPUART - Register accessor macros
 * @{
 */


/* LPUART - Register accessors */
#line 2832 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group LPUART_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- LPUART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Register_Masks LPUART Register Masks
 * @{
 */

/* BAUD Bit Fields */
#line 2877 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* STAT Bit Fields */
#line 2914 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CTRL Bit Fields */
#line 2970 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* DATA Bit Fields */
#line 3001 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* MATCH Bit Fields */
#line 3008 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* MODIR Bit Fields */
#line 3029 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FIFO Bit Fields */
#line 3059 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* WATER Bit Fields */
#line 3072 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group LPUART_Register_Masks */


/* LPUART - Peripheral instance base addresses */
/** Peripheral LPUART0 base pointer */

/** Array initializer of LPUART peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- LPUART - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPUART_Register_Accessor_Macros LPUART - Register accessor macros
 * @{
 */


/* LPUART - Register instance definitions */
/* LPUART0 */
#line 3104 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group LPUART_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group LPUART_Peripheral */


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
  uint8_t RESERVED_2[3];
  uint8_t C12;                                     /**< MCG Control 12 Register, offset: 0x11 */
  uint8_t S2;                                      /**< MCG Status 2 Register, offset: 0x12 */
  uint8_t T3;                                      /**< MCG Test 3 Register, offset: 0x13 */
} volatile *MCG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCG - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Accessor_Macros MCG - Register accessor macros
 * @{
 */


/* MCG - Register accessors */
#line 3172 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 3200 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* C2 Bit Fields */
#line 3216 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* C3 Bit Fields */



/* C4 Bit Fields */
#line 3231 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* C6 Bit Fields */


/* S Bit Fields */
#line 3244 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SC Bit Fields */
#line 3258 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* ATCVH Bit Fields */



/* ATCVL Bit Fields */



/* C7 Bit Fields */


/* C8 Bit Fields */
#line 3276 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 3315 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
  uint32_t PLACR;                                  /**< Platform Control Register, offset: 0xC */
  uint8_t RESERVED_1[48];
  uint32_t CPO;                                    /**< Compute Operation Control Register, offset: 0x40 */
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
#line 3400 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CPO Bit Fields */
#line 3407 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
   -- MTB
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Peripheral MTB
 * @{
 */

/** MTB - Peripheral register structure */
typedef struct MTB_MemMap {
  uint32_t POSITION;                               /**< MTB Position Register, offset: 0x0 */
  uint32_t MASTER;                                 /**< MTB Master Register, offset: 0x4 */
  uint32_t FLOW;                                   /**< MTB Flow Register, offset: 0x8 */
  uint32_t BASE;                                   /**< MTB Base Register, offset: 0xC */
  uint8_t RESERVED_0[3824];
  uint32_t MODECTRL;                               /**< Integration Mode Control Register, offset: 0xF00 */
  uint8_t RESERVED_1[156];
  uint32_t TAGSET;                                 /**< Claim TAG Set Register, offset: 0xFA0 */
  uint32_t TAGCLEAR;                               /**< Claim TAG Clear Register, offset: 0xFA4 */
  uint8_t RESERVED_2[8];
  uint32_t LOCKACCESS;                             /**< Lock Access Register, offset: 0xFB0 */
  uint32_t LOCKSTAT;                               /**< Lock Status Register, offset: 0xFB4 */
  uint32_t AUTHSTAT;                               /**< Authentication Status Register, offset: 0xFB8 */
  uint32_t DEVICEARCH;                             /**< Device Architecture Register, offset: 0xFBC */
  uint8_t RESERVED_3[8];
  uint32_t DEVICECFG;                              /**< Device Configuration Register, offset: 0xFC8 */
  uint32_t DEVICETYPID;                            /**< Device Type Identifier Register, offset: 0xFCC */
  uint32_t PERIPHID[8];                            /**< Peripheral ID Register, array offset: 0xFD0, array step: 0x4 */
  uint32_t COMPID[4];                              /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} volatile *MTB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MTB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Register_Accessor_Macros MTB - Register accessor macros
 * @{
 */


/* MTB - Register accessors */
#line 3504 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group MTB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MTB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Register_Masks MTB Register Masks
 * @{
 */

/* POSITION Bit Fields */





/* MASTER Bit Fields */
#line 3541 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FLOW Bit Fields */
#line 3549 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* BASE Bit Fields */



/* MODECTRL Bit Fields */



/* TAGSET Bit Fields */



/* TAGCLEAR Bit Fields */



/* LOCKACCESS Bit Fields */



/* LOCKSTAT Bit Fields */



/* AUTHSTAT Bit Fields */
#line 3582 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* DEVICEARCH Bit Fields */



/* DEVICECFG Bit Fields */



/* DEVICETYPID Bit Fields */



/* PERIPHID Bit Fields */



/* COMPID Bit Fields */




/*!
 * @}
 */ /* end of group MTB_Register_Masks */


/* MTB - Peripheral instance base addresses */
/** Peripheral MTB base pointer */

/** Array initializer of MTB peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- MTB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Register_Accessor_Macros MTB - Register accessor macros
 * @{
 */


/* MTB - Register instance definitions */
/* MTB */
#line 3651 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* MTB - Register array accessors */



/*!
 * @}
 */ /* end of group MTB_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MTB_Peripheral */


/* ----------------------------------------------------------------------------
   -- MTBDWT
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Peripheral MTBDWT
 * @{
 */

/** MTBDWT - Peripheral register structure */
typedef struct MTBDWT_MemMap {
  uint32_t CTRL;                                   /**< MTB DWT Control Register, offset: 0x0 */
  uint8_t RESERVED_0[28];
  struct {                                         /* offset: 0x20, array step: 0x10 */
    uint32_t COMP;                                   /**< MTB_DWT Comparator Register, array offset: 0x20, array step: 0x10 */
    uint32_t MASK;                                   /**< MTB_DWT Comparator Mask Register, array offset: 0x24, array step: 0x10 */
    uint32_t FCT;                                    /**< MTB_DWT Comparator Function Register 0..MTB_DWT Comparator Function Register 1, array offset: 0x28, array step: 0x10 */
    uint8_t RESERVED_0[4];
  } COMPARATOR[2];
  uint8_t RESERVED_1[448];
  uint32_t TBCTRL;                                 /**< MTB_DWT Trace Buffer Control Register, offset: 0x200 */
  uint8_t RESERVED_2[3524];
  uint32_t DEVICECFG;                              /**< Device Configuration Register, offset: 0xFC8 */
  uint32_t DEVICETYPID;                            /**< Device Type Identifier Register, offset: 0xFCC */
  uint32_t PERIPHID[8];                            /**< Peripheral ID Register, array offset: 0xFD0, array step: 0x4 */
  uint32_t COMPID[4];                              /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} volatile *MTBDWT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MTBDWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Register_Accessor_Macros MTBDWT - Register accessor macros
 * @{
 */


/* MTBDWT - Register accessors */
#line 3714 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group MTBDWT_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- MTBDWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Register_Masks MTBDWT Register Masks
 * @{
 */

/* CTRL Bit Fields */
#line 3736 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* COMP Bit Fields */



/* MASK Bit Fields */



/* FCT Bit Fields */
#line 3758 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* TBCTRL Bit Fields */
#line 3766 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* DEVICECFG Bit Fields */



/* DEVICETYPID Bit Fields */



/* PERIPHID Bit Fields */



/* COMPID Bit Fields */




/*!
 * @}
 */ /* end of group MTBDWT_Register_Masks */


/* MTBDWT - Peripheral instance base addresses */
/** Peripheral MTBDWT base pointer */

/** Array initializer of MTBDWT peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- MTBDWT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Register_Accessor_Macros MTBDWT - Register accessor macros
 * @{
 */


/* MTBDWT - Register instance definitions */
/* MTBDWT */
#line 3828 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* MTBDWT - Register array accessors */






/*!
 * @}
 */ /* end of group MTBDWT_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group MTBDWT_Peripheral */


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
} volatile *NV_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register accessors */
#line 3898 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 3974 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FOPT Bit Fields */
#line 3985 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group NV_Register_Masks */


/* NV - Peripheral instance base addresses */
/** Peripheral FTFA_FlashConfig base pointer */

/** Array initializer of NV peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- NV - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Accessor_Macros NV - Register accessor macros
 * @{
 */


/* NV - Register instance definitions */
/* FTFA_FlashConfig */
#line 4023 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
  uint32_t ISER;                                   /**< Interrupt Set Enable Register, offset: 0x0 */
  uint8_t RESERVED_0[124];
  uint32_t ICER;                                   /**< Interrupt Clear Enable Register, offset: 0x80 */
  uint8_t RESERVED_1[124];
  uint32_t ISPR;                                   /**< Interrupt Set Pending Register, offset: 0x100 */
  uint8_t RESERVED_2[124];
  uint32_t ICPR;                                   /**< Interrupt Clear Pending Register, offset: 0x180 */
  uint8_t RESERVED_3[380];
  uint32_t IP[8];                                  /**< Interrupt Priority Register 0..Interrupt Priority Register 7, array offset: 0x300, array step: 0x4 */
} volatile *NVIC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- NVIC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NVIC_Register_Accessor_Macros NVIC - Register accessor macros
 * @{
 */


/* NVIC - Register accessors */






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
#line 4155 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* ICER Bit Fields */
#line 4220 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* ISPR Bit Fields */
#line 4285 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* ICPR Bit Fields */
#line 4350 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* IP Bit Fields */
#line 4447 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 4483 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* NVIC - Register array accessors */


/*!
 * @}
 */ /* end of group NVIC_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group NVIC_Peripheral */


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
  uint8_t RESERVED_0[220];
  uint32_t LTMR64H;                                /**< PIT Upper Lifetime Timer Register, offset: 0xE0 */
  uint32_t LTMR64L;                                /**< PIT Lower Lifetime Timer Register, offset: 0xE4 */
  uint8_t RESERVED_1[24];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    uint32_t LDVAL;                                  /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    uint32_t CVAL;                                   /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    uint32_t TCTRL;                                  /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    uint32_t TFLG;                                   /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[2];
} volatile *PIT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PIT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Accessor_Macros PIT - Register accessor macros
 * @{
 */


/* PIT - Register accessors */
#line 4539 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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




/* LTMR64H Bit Fields */



/* LTMR64L Bit Fields */



/* LDVAL Bit Fields */



/* CVAL Bit Fields */



/* TCTRL Bit Fields */
#line 4582 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
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
#line 4620 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 4694 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* LVDSC2 Bit Fields */
#line 4704 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* REGSC Bit Fields */
#line 4713 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
} volatile *PORT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PORT - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Accessor_Macros PORT - Register accessor macros
 * @{
 */


/* PORT - Register accessors */





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
#line 4818 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* GPCLR Bit Fields */
#line 4825 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* GPCHR Bit Fields */
#line 4832 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* ISFR Bit Fields */




/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base pointer */

/** Peripheral PORTB base pointer */

/** Peripheral PORTC base pointer */

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
#line 4899 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PORTB */
#line 4935 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PORTC */
#line 4971 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 5048 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SRS1 Bit Fields */
#line 5057 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* RPFC Bit Fields */





/* RPFW Bit Fields */




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
   -- ROM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Peripheral ROM
 * @{
 */

/** ROM - Peripheral register structure */
typedef struct ROM_MemMap {
  uint32_t ENTRY[3];                               /**< Entry, array offset: 0x0, array step: 0x4 */
  uint32_t TABLEMARK;                              /**< End of Table Marker Register, offset: 0xC */
  uint8_t RESERVED_0[4028];
  uint32_t SYSACCESS;                              /**< System Access Register, offset: 0xFCC */
  uint32_t PERIPHID[8];                            /**< Peripheral ID Register, array offset: 0xFD0, array step: 0x4 */
  uint32_t COMPID[4];                              /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} volatile *ROM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register accessors */






/*!
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- ROM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Masks ROM Register Masks
 * @{
 */

/* ENTRY Bit Fields */



/* TABLEMARK Bit Fields */



/* SYSACCESS Bit Fields */



/* PERIPHID Bit Fields */



/* COMPID Bit Fields */




/*!
 * @}
 */ /* end of group ROM_Register_Masks */


/* ROM - Peripheral instance base addresses */
/** Peripheral ROM base pointer */

/** Array initializer of ROM peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- ROM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Accessor_Macros ROM - Register accessor macros
 * @{
 */


/* ROM - Register instance definitions */
/* ROM */
#line 5217 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* ROM - Register array accessors */




/*!
 * @}
 */ /* end of group ROM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group ROM_Peripheral */


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
} volatile *RTC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RTC - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Accessor_Macros RTC - Register accessor macros
 * @{
 */


/* RTC - Register accessors */
#line 5273 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 5313 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CR Bit Fields */
#line 5336 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SR Bit Fields */
#line 5345 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* LR Bit Fields */
#line 5354 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* IER Bit Fields */
#line 5365 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 5397 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
  uint8_t RESERVED_2[4];
  uint32_t SHPR2;                                  /**< System Handler Priority Register 2, offset: 0xD1C */
  uint32_t SHPR3;                                  /**< System Handler Priority Register 3, offset: 0xD20 */
  uint32_t SHCSR;                                  /**< System Handler Control and State Register, offset: 0xD24 */
  uint8_t RESERVED_3[8];
  uint32_t DFSR;                                   /**< Debug Fault Status Register, offset: 0xD30 */
} volatile *SCB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


/* SCB - Register accessors */
#line 5458 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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

/* CPUID Bit Fields */
#line 5486 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* ICSR Bit Fields */
#line 5500 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* VTOR Bit Fields */



/* AIRCR Bit Fields */
#line 5514 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SCR Bit Fields */
#line 5521 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CCR Bit Fields */




/* SHPR2 Bit Fields */



/* SHPR3 Bit Fields */
#line 5537 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SHCSR Bit Fields */


/* DFSR Bit Fields */
#line 5551 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 5586 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
  uint8_t RESERVED_0[4096];
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
  uint8_t RESERVED_5[4];
  uint32_t FCFG1;                                  /**< Flash Configuration Register 1, offset: 0x104C */
  uint32_t FCFG2;                                  /**< Flash Configuration Register 2, offset: 0x1050 */
  uint8_t RESERVED_6[4];
  uint32_t UIDMH;                                  /**< Unique Identification Register Mid-High, offset: 0x1058 */
  uint32_t UIDML;                                  /**< Unique Identification Register Mid Low, offset: 0x105C */
  uint32_t UIDL;                                   /**< Unique Identification Register Low, offset: 0x1060 */
  uint8_t RESERVED_7[156];
  uint32_t COPC;                                   /**< COP Control Register, offset: 0x1100 */
  uint32_t SRVCOP;                                 /**< Service COP, offset: 0x1104 */
} volatile *SIM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SIM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Accessor_Macros SIM - Register accessor macros
 * @{
 */


/* SIM - Register accessors */
#line 5665 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 5687 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SOPT2 Bit Fields */
#line 5697 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SOPT4 Bit Fields */
#line 5708 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SOPT5 Bit Fields */
#line 5716 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SOPT7 Bit Fields */
#line 5724 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SDID Bit Fields */
#line 5746 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SCGC4 Bit Fields */
#line 5755 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SCGC5 Bit Fields */
#line 5780 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SCGC6 Bit Fields */
#line 5805 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SCGC7 Bit Fields */


/* CLKDIV1 Bit Fields */
#line 5815 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FCFG1 Bit Fields */
#line 5823 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FCFG2 Bit Fields */
#line 5830 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* UIDMH Bit Fields */



/* UIDML Bit Fields */



/* UIDL Bit Fields */



/* COPC Bit Fields */
#line 5857 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SRVCOP Bit Fields */




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
#line 5903 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
  uint8_t STOPCTRL;                                /**< Stop Control Register, offset: 0x2 */
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
#line 5968 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PMCTRL Bit Fields */
#line 5977 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* STOPCTRL Bit Fields */
#line 5988 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
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
  uint32_t SR;                                     /**< Status Register, offset: 0x2C */
  uint32_t RSER;                                   /**< DMA/Interrupt Request Select and Enable Register, offset: 0x30 */
  union {                                          /* offset: 0x34 */
    uint32_t PUSHR;                                  /**< PUSH TX FIFO Register In Master Mode, offset: 0x34 */
    uint32_t PUSHR_SLAVE;                            /**< PUSH TX FIFO Register In Slave Mode, offset: 0x34 */
  };
  uint32_t POPR;                                   /**< POP RX FIFO Register, offset: 0x38 */
  uint32_t TXFR[4];                                /**< Transmit FIFO Registers, array offset: 0x3C, array step: 0x4 */
  uint8_t RESERVED_2[48];
  uint32_t RXFR[4];                                /**< Receive FIFO Registers, array offset: 0x7C, array step: 0x4 */
} volatile *SPI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SPI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Accessor_Macros SPI - Register accessor macros
 * @{
 */


/* SPI - Register accessors */
#line 6084 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 6133 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* TCR Bit Fields */



/* CTAR Bit Fields */
#line 6173 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CTAR_SLAVE Bit Fields */
#line 6181 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SR Bit Fields */
#line 6208 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* RSER Bit Fields */
#line 6225 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PUSHR Bit Fields */
#line 6241 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* PUSHR_SLAVE Bit Fields */



/* POPR Bit Fields */



/* TXFR Bit Fields */
#line 6256 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* RXFR Bit Fields */




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
#line 6304 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* SPI1 */
#line 6323 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* SPI - Register array accessors */
#line 6333 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
#line 6400 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* RVR Bit Fields */



/* CVR Bit Fields */



/* CALIB Bit Fields */
#line 6416 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

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
   -- TPM
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPM_Peripheral TPM
 * @{
 */

/** TPM - Peripheral register structure */
typedef struct TPM_MemMap {
  uint32_t SC;                                     /**< Status and Control, offset: 0x0 */
  uint32_t CNT;                                    /**< Counter, offset: 0x4 */
  uint32_t MOD;                                    /**< Modulo, offset: 0x8 */
  struct {                                         /* offset: 0xC, array step: 0x8 */
    uint32_t CnSC;                                   /**< Channel (n) Status and Control, array offset: 0xC, array step: 0x8 */
    uint32_t CnV;                                    /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
  } CONTROLS[4];
  uint8_t RESERVED_0[36];
  uint32_t STATUS;                                 /**< Capture and Compare Status, offset: 0x50 */
  uint8_t RESERVED_1[16];
  uint32_t COMBINE;                                /**< Combine Channel Register, offset: 0x64 */
  uint8_t RESERVED_2[16];
  uint32_t FILTER;                                 /**< Filter Control, offset: 0x78 */
  uint8_t RESERVED_3[4];
  uint32_t QDCTRL;                                 /**< Quadrature Decoder Control and Status, offset: 0x80 */
  uint32_t CONF;                                   /**< Configuration, offset: 0x84 */
} volatile *TPM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- TPM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPM_Register_Accessor_Macros TPM - Register accessor macros
 * @{
 */


/* TPM - Register accessors */
#line 6505 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group TPM_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- TPM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPM_Register_Masks TPM Register Masks
 * @{
 */

/* SC Bit Fields */
#line 6535 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CNT Bit Fields */



/* MOD Bit Fields */



/* CnSC Bit Fields */
#line 6558 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CnV Bit Fields */



/* STATUS Bit Fields */
#line 6573 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* COMBINE Bit Fields */
#line 6582 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* FILTER Bit Fields */
#line 6595 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* QDCTRL Bit Fields */
#line 6604 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* CONF Bit Fields */
#line 6621 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group TPM_Register_Masks */


/* TPM - Peripheral instance base addresses */
/** Peripheral TPM0 base pointer */

/** Peripheral TPM1 base pointer */

/** Peripheral TPM2 base pointer */

/** Array initializer of TPM peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- TPM - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TPM_Register_Accessor_Macros TPM - Register accessor macros
 * @{
 */


/* TPM - Register instance definitions */
/* TPM0 */
#line 6665 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* TPM1 */
#line 6682 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* TPM2 */
#line 6699 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* TPM - Register array accessors */
#line 6707 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group TPM_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group TPM_Peripheral */


/* ----------------------------------------------------------------------------
   -- TSI
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSI_Peripheral TSI
 * @{
 */

/** TSI - Peripheral register structure */
typedef struct TSI_MemMap {
  uint32_t GENCS;                                  /**< TSI General Control and Status Register, offset: 0x0 */
  uint32_t DATA;                                   /**< TSI DATA Register, offset: 0x4 */
  uint32_t TSHD;                                   /**< TSI Threshold Register, offset: 0x8 */
} volatile *TSI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- TSI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSI_Register_Accessor_Macros TSI - Register accessor macros
 * @{
 */


/* TSI - Register accessors */




/*!
 * @}
 */ /* end of group TSI_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- TSI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSI_Register_Masks TSI Register Masks
 * @{
 */

/* GENCS Bit Fields */
#line 6800 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* DATA Bit Fields */
#line 6811 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
/* TSHD Bit Fields */
#line 6818 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/*!
 * @}
 */ /* end of group TSI_Register_Masks */


/* TSI - Peripheral instance base addresses */
/** Peripheral TSI base pointer */

/** Array initializer of TSI peripheral base pointers */


/* ----------------------------------------------------------------------------
   -- TSI - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSI_Register_Accessor_Macros TSI - Register accessor macros
 * @{
 */


/* TSI - Register instance definitions */
/* TSI */




/*!
 * @}
 */ /* end of group TSI_Register_Accessor_Macros */


/*!
 * @}
 */ /* end of group TSI_Peripheral */


/*
** End of section using anonymous unions
*/

#line 6867 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"
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

/* No backward compatibility issues. */

/*!
 * @}
 */ /* end of group Backward_Compatibility_Symbols */


#line 6901 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\MKW40Z4.h"

/* MKW40Z4.h, eof. */
#line 52 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"







#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\include\\cfg\\MKW40Z160_cfg.h"
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file MKW40Z160.h
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
#line 67 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.h"










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
    return *((uint32_t*)(((160*1024) - 1024) + (0x44)));
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
    uint8_t  buffer[1024];
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
    while (flashAddr < ((160*1024) - 1024))
    {
        if (remaingImgSize > 1024)
            len = 1024;
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


                if( (flashAddr <= (((uint32_t)(__region_BOOT_ROM_end__) + 1) + (48*4))) && (flashAddr + len > (((uint32_t)(__region_BOOT_ROM_end__) + 1) + (48*4))) )
                {
                    uint32_t i, offset = (((uint32_t)(__region_BOOT_ROM_end__) + 1) + (48*4)) - flashAddr;
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
        flashAddr += 1024;

        /* Update the remaining bytes*/
        if (remaingImgSize)
            remaingImgSize -= len;
    } /* while */

#line 396 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.c"


    /* Set the bBootProcessCompleted Flag */
    if( 0 != FLASH_Program((uint32_t)(((uint32_t)(__region_BOOT_ROM_end__) + 1) + (48*4)), (uint32_t)&flags, sizeof(flags)) )
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





    ((((SIM_MemMapPtr)0x40047000u))->COPC) = (((uint32_t)(((uint32_t)(0))<<2))&0xCu);
#line 454 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\OtapSerialBootloader\\OtapBootloader.c"
    /* Check if there is no boot image available in the external EEPROM and if eventually
    the booting of the previous one has been completed. If both conditions are met, start
    running the application in the internal Flash. Else, start the process of booting from
    external EEPROM */
    gpBootInfo = (bootInfo_t*)(((uint32_t)(__region_BOOT_ROM_end__) + 1) + (48*4));
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
