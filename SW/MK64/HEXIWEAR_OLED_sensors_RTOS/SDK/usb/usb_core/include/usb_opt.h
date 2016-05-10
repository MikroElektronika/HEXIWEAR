/**HEADER********************************************************************
 * 
 * Copyright (c) 2008, 2013 Freescale Semiconductor;
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
 * $FileName: usb_opt.h$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 *   
 *
 *END************************************************************************/
#ifndef __usb_opt_h__
#define __usb_opt_h__ 1

#ifndef ENDIANNESS

#error ENDIANNESS should be defined, and then rebulid the project.

#endif

#define SWAP2BYTE_CONST(n) ((((n) & 0x00FF) << 8) | (((n) & 0xFF00) >> 8))
#define SWAP4BYTE_CONST(n) ((((n) & 0x000000FF) << 24) | (((n) & 0x0000FF00) << 8) | (((n) & 0x00FF0000) >> 8) | (((n) & 0xFF000000) >> 24))

#if (ENDIANNESS == BIG_ENDIAN)
#define USB_HOST_TO_BE_SHORT(n)           (n)
#define USB_HOST_TO_BE_SHORT_CONST(n)     (n)
#define USB_HOST_TO_LE_SHORT(n)           SWAP2BYTE_CONST(n)
#define USB_HOST_TO_LE_SHORT_CONST(n)     SWAP2BYTE_CONST(n)
#define USB_SHORT_BE_TO_HOST(n)           (n)
#define USB_SHORT_BE_TO_HOST_CONST(n)     (n)
#define USB_SHORT_LE_TO_HOST(n)           SWAP2BYTE_CONST(n)
#define USB_SHORT_LE_TO_HOST_CONST(n)     SWAP2BYTE_CONST(n)
#define USB_SHORT_UNALIGNED_LE_TO_HOST(n) ((n[1]<<8)|n[0])

#define USB_HOST_TO_BE_LONG(n)            (n)
#define USB_HOST_TO_BE_LONG_CONST(n)      (n)
#define USB_HOST_TO_BE_UNALIGNED_LONG(n, m)  \
    { \
       m[0]=((n>>24) & 0xFF); \
       m[1]=((n>>16) & 0xFF); \
       m[2]=((n>>8) & 0xFF); \
       m[3]=(n & 0xFF); \
    }
#define USB_HOST_TO_LE_LONG(n)            SWAP4BYTE_CONST(n)
#define USB_HOST_TO_LE_LONG_CONST(n)      SWAP4BYTE_CONST(n)
#define USB_HOST_TO_LE_UNALIGNED_LONG(n, m)  \
    { \
       m[0]=(n & 0xFF); \
       m[1]=((n>>8) & 0xFF); \
       m[2]=((n>>16) & 0xFF); \
       m[3]=((n>>24) & 0xFF); \
    }
#define USB_LONG_BE_TO_HOST(n)            (n)
#define USB_LONG_BE_TO_HOST_CONST(n)      (n)
#define USB_LONG_LE_TO_HOST(n)            SWAP4BYTE_CONST(n)
#define USB_LONG_LE_TO_HOST_CONST(n)      SWAP4BYTE_CONST(n)
#define USB_LONG_UNALIGNED_LE_TO_HOST(n)  ((n[3]<<24)|(n[2]<<16)|(n[1]<<8)|n[0])

#else /* (PSP_ENDIAN == MQX_BIG_ENDIAN) */

#define USB_HOST_TO_BE_SHORT(n)           SWAP2BYTE_CONST(n)
#define USB_HOST_TO_BE_SHORT_CONST(n)     SWAP2BYTE_CONST(n)
#define USB_HOST_TO_LE_SHORT(n)           (n)
#define USB_HOST_TO_LE_SHORT_CONST(n)     (n)
#define USB_SHORT_BE_TO_HOST(n)           SWAP2BYTE_CONST(n)
#define USB_SHORT_BE_TO_HOST_CONST(n)     SWAP2BYTE_CONST(n)
#define USB_SHORT_LE_TO_HOST(n)           (n)
#define USB_SHORT_LE_TO_HOST_CONST(n)     (n)
#define USB_SHORT_UNALIGNED_LE_TO_HOST(n) ((uint16_t)((uint16_t)n[1]<<8)|n[0])

#define USB_HOST_TO_BE_LONG(n)            SWAP4BYTE_CONST(n)
#define USB_HOST_TO_BE_LONG_CONST(n)      SWAP4BYTE_CONST(n)
#define USB_HOST_TO_BE_UNALIGNED_LONG(n, m)  \
    { \
       m[0]=((n>>24) & 0xFF); \
       m[1]=((n>>16) & 0xFF); \
       m[2]=((n>>8) & 0xFF); \
       m[3]=(n & 0xFF); \
    }
#define USB_HOST_TO_LE_LONG(n)            (n)
#define USB_HOST_TO_LE_LONG_CONST(n)      (n)
#define USB_HOST_TO_LE_UNALIGNED_LONG(n, m)  \
    { \
       m[0]=(n & 0xFF); \
       m[1]=((n>>8) & 0xFF); \
       m[2]=((n>>16) & 0xFF); \
       m[3]=((n>>24) & 0xFF); \
    }

#define USB_LONG_BE_TO_HOST(n)            SWAP4BYTE_CONST(n)
#define USB_LONG_BE_TO_HOST_CONST(n)      SWAP4BYTE_CONST(n)
#define USB_LONG_LE_TO_HOST(n)            (n)
#define USB_LONG_LE_TO_HOST_CONST(n)      (n)
#define USB_LONG_UNALIGNED_LE_TO_HOST(n)  (((uint32_t)n[3]<<24) | ((uint32_t)n[2]<<16) | ((uint32_t)n[1]<<8) | (uint32_t)n[0])
#endif /* (PSP_ENDIAN == MQX_BIG_ENDIAN) */

#endif
