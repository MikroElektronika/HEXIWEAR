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
* $FileName: osadapter_cfg.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains OS adapter configuration inf.
*
*****************************************************************************/

#ifndef _OSADAPTER_CFG_H
#define _OSADAPTER_CFG_H 1

#define OS_ADAPTER_MQX                       1
#define OS_ADAPTER_BM                        2
#define OS_ADAPTER_SDK                       3
#define OS_ADAPTER_UCOSIII                   4
/*#define OS_ADAPTER_ACTIVE_OS                 OS_ADAPTER_UCOSIII*/
#define OS_ADAPTER_ACTIVE_OS                 OS_ADAPTER_SDK

#endif


