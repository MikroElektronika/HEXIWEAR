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
 * $FileName: compiler.h$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 *   This file defines compiler related MACRO
 *
 *END************************************************************************/
#ifndef __compiler_h__
#define __compiler_h__ 1

#ifdef __cplusplus
extern "C"
{
#endif
#if ((defined __CWCC__)||(defined __GNUC__))
#ifndef PACKED_STRUCT_BEGIN
#define PACKED_STRUCT_BEGIN
#endif

#ifndef PACKED_STRUCT_END
#define PACKED_STRUCT_END     __attribute__((__packed__))
#endif

#ifndef PACKED_UNION_BEGIN
#define PACKED_UNION_BEGIN
#endif

#ifndef PACKED_UNION_END
#define PACKED_UNION_END      __attribute__((__packed__))
#endif

#ifndef _WEAK_FUNCTION
#define _WEAK_FUNCTION(x)     __attribute__((weak)) x
#endif

#ifndef _WEAK_SYMBOL
#define _WEAK_SYMBOL(x)     x __attribute__((weak))
#endif

#elif (defined __IAR_SYSTEMS_ICC__)

#ifndef PACKED_STRUCT_BEGIN
#define PACKED_STRUCT_BEGIN   __packed
#endif

#ifndef PACKED_STRUCT_END
#define PACKED_STRUCT_END
#endif

#ifndef PACKED_UNION_BEGIN
#define PACKED_UNION_BEGIN
#endif

#ifndef PACKED_UNION_END
#define PACKED_UNION_END      __packed
#endif

#ifndef _WEAK_FUNCTION
#define _WEAK_FUNCTION(x)     __weak x
#endif

#ifndef _WEAK_SYMBOL
#define _WEAK_SYMBOL(x)     __weak x
#endif
    
#elif (defined __CC_ARM)

#ifndef PACKED_STRUCT_BEGIN
#define PACKED_STRUCT_BEGIN   _Pragma("pack(1)")
#endif

#ifndef PACKED_STRUCT_END
#define PACKED_STRUCT_END    _Pragma("pack()")
#endif

#ifndef PACKED_UNION_BEGIN
#define PACKED_UNION_BEGIN    _Pragma("pack()")
#endif

#ifndef PACKED_UNION_END
#define PACKED_UNION_END    _Pragma("pack()")
#endif

#ifndef _WEAK_FUNCTION
#define _WEAK_FUNCTION(x)     __weak x
#endif

#ifndef _WEAK_SYMBOL
#define _WEAK_SYMBOL(x)     __weak x
#endif
    
#endif  

#ifdef __cplusplus
}
#endif

#endif
