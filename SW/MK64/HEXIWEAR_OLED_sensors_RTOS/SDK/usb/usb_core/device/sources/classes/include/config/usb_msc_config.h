/**HEADER********************************************************************
* 
* Copyright (c) 2014-2015 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
* All Rights Reserved
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
* $FileName: usb_msc_config.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains USB stack MSC class layer api header function.
*
*****************************************************************************/

#ifndef _USB_MSC_CONFIG_H
#define _USB_MSC_CONFIG_H 1

/******************************************************************************
 * Macro's
 *****************************************************************************/

/* If Implementing Disk Drive then configure the macro below as TRUE,
   otherwise keep it False(say for Hard Disk)*/
#define IMPLEMENTING_DISK_DRIVE         (0) /*1: TRUE; 0:FALSE*/

#define MSD_RECV_MAX_TRANS_LENGTH       (65536)
#define MSD_SEND_MAX_TRANS_LENGTH       (65536)

#define MAX_MSC_DEVICE                     (0x01)
#define MAX_MSC_SUPPORTED_INTERFACES       (0x01)


#endif

