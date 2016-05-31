/**HEADER********************************************************************
 * 
 * Copyright (c) 2013 Freescale Semiconductor;
 * All Rights Reserved
 *
 *
 *************************************************************************** 
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************
 *
 * $FileName: types.h$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 *   
 *
 *END************************************************************************/
#ifndef _types_h__
#define _types_h__

/*--------------------------------------------------------------------------*/
/*
 **                            STANDARD TYPES
 */

/*
 **  The following typedefs allow us to minimize portability problems
 **  due to the various C compilers (even for the same processor) not
 **  agreeing on the sizes of "int"s and "short int"s and "longs".
 */

//#define *      *
#define _CODE_PTR_ *

typedef char * char_ptr; /* signed character       */

typedef unsigned char uchar; /* unsigned character     */

typedef signed char int8_t, *int_8_ptr; /* 8-bit signed integer   */
typedef unsigned char uint8_t; /* 8-bit signed integer   */

typedef short int16_t, *int_16_ptr; /* 16-bit signed integer  */
typedef unsigned short uint16_t, *uint_16_ptr; /* 16-bit unsigned integer*/

typedef long int32_t, *int_32_ptr; /* 32-bit signed integer  */
typedef unsigned long uint32_t, *uint_32_ptr; /* 32-bit unsigned integer*/

typedef long long int_64, *int_64_ptr; /* 64-bit signed   */
typedef unsigned long long uint64_t, *uint_64_ptr; /* 64-bit unsigned */

typedef unsigned long bool; /* Machine representation of a bool */

//typedef void *     void*;  /* Machine representation of a pointer */
//typedef unsigned char uint8_t;
//typedef unsigned short uint16_t;
//typedef unsigned long  uint32_t;
#ifdef  FALSE
#undef  FALSE
#endif
#define FALSE ((uint8_t)0)

#ifdef  TRUE
#undef  TRUE
#endif
#define TRUE ((uint8_t)1)

#define UNUSED(x)   (void)x;
#endif
