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

#ifndef _EEPROM_H_
#define _EEPROM_H_

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "EmbeddedTypes.h"

#ifdef __cplusplus
    extern "C" {
#endif

/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */


/* List of the EEPROM devices used on each of the FSL development boards */
#define gEepromDevice_None_c          0
#define gEepromDevice_InternalFlash_c 1
#define gEepromDevice_AT45DB161E_c    2 /* TWR-KW2x */
#define gEepromDevice_AT26DF081A_c    3 /* TWR-MEM */
#define gEepromDevice_AT45DB021E_c    4 /* TWR-KW4x*/

/* Default EEPROM type used */
#ifndef gEepromType_d
#define gEepromType_d gEepromDevice_M25P80_c
#endif

/* Characteristics of the EEPROM device */
#if (gEepromType_d == gEepromDevice_AT26DF081A_c)
  #define gEepromParams_TotalSize_c           0x00100000 /* 1 MBytes */
  
#elif (gEepromType_d == gEepromDevice_AT45DB161E_c)
  #define gEepromParams_TotalSize_c           0x00200000 /* 2 MBytes */
  
#elif (gEepromType_d == gEepromDevice_AT45DB021E_c)
  #define gEepromParams_TotalSize_c           0x00040000 /* 256 KBytes */
#endif

#ifndef gEepromParams_WriteAlignment_c
#define gEepromParams_WriteAlignment_c         1 /* bytes */
#endif

#if (gEepromParams_WriteAlignment_c > 1)
#define gEepromAlignAddr_d(x) ((((x)+gEepromParams_WriteAlignment_c-1)/gEepromParams_WriteAlignment_c)*gEepromParams_WriteAlignment_c)
#else
#define gEepromAlignAddr_d(x) (x)
#endif


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
#if gEepromType_d != gEepromDevice_InternalFlash_c
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
#else
  #define EEPROM_Init() 0
  #define EEPROM_ReadData(NoOfBytes,Addr,outbuf) 0
#endif

#ifdef __cplusplus
}
#endif

#endif /* _EEPROM_H_ */
