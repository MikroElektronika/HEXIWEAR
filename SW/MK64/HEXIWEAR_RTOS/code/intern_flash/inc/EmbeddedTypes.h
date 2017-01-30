/*!
* Copyright (c) 2015, NXP Semiconductor, Inc.
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
* o Neither the name of NXP Semiconductor, Inc. nor the names of its
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


#ifndef _EMBEDDEDTYPES_H_
#define _EMBEDDEDTYPES_H_

#ifdef __cplusplus
    extern "C" {
#endif

/**
*
*       TYPE DEFINITIONS
*
 * */
#if defined(__GNUC__)
#define PACKED_STRUCT struct __attribute__ ((__packed__))
#define PACKED_UNION  union __attribute__ ((__packed__))
#elif defined(__IAR_SYSTEMS_ICC__)
#define PACKED_STRUCT __packed struct
#define PACKED_UNION __packed union
#else
#define PACKED_STRUCT struct
#define PACKED_UNION union
#endif


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

 /** boolean types */
typedef uint8_t   bool_t;
typedef uintn8_t  booln_t;
 /** used for indexing into an array in the most efficient manner for the platform */
typedef uint8_t   index_t;

#define TRUE 1
#define FALSE 0

#ifndef NULL
#define NULL (( void * )( 0 ))
#endif

 /** If parameters of CONCAT() are macros, a second level of indirection is required to get them to expand */
#define _CONCAT(t1, t2) t1 ## t2
#define CONCAT(t1, t2) _CONCAT(t1,t2)


#ifdef __cplusplus
}
#endif

#endif /* _EMBEDDEDTYPES_H_ */
