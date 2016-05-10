#line 1 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\eeprom\\Eeprom_Boot_AT45DB161E.c"
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file EEPROM_AT45DB161E.c
* This is a source file which implements the driver for the AT45DB161E memory.
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








#line 43 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\eeprom\\Eeprom_Boot.h"





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









#line 41 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\eeprom\\Eeprom_Boot_AT45DB161E.c"

#line 395 "C:\\Freescale\\KW40Z_Connectivity_Software_1.0.1\\ConnSw\\framework\\Bootloader\\Bootloader_OTAP_Serial\\src\\eeprom\\Eeprom_Boot_AT45DB161E.c"
/* EOF: Eeprom_AT45DB161E */ 

