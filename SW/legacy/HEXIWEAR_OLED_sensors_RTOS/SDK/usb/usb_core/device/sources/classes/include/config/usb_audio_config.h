/**HEADER********************************************************************
* 
* Copyright (c) 2014 Freescale Semiconductor;
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
* $FileName: usb_audio_config.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains USB stack AUDIO class layer api header function.
*
*****************************************************************************/

#ifndef _USB_AUDIO_CONFIG_H
#define _USB_AUDIO_CONFIG_H 1


/******************************************************************************
 * Macro's
 *****************************************************************************/
/* if Audio class 2.0  supported 
 * 1 supported
 * 0 not supported
 */
#if USBCFG_DEV_AUDIO
#define USBCFG_AUDIO_CLASS_2_0            0
#endif

#define AUDIO_IMPLEMENT_QUEUING           (0)
#define AUDIO_MAX_QUEUE_ELEMS             (4)
#define MAX_AUDIO_CLASS_EP_NUM            (0x01)
#define MAX_AUDIO_CLASS_UT_NUM            (0x08)

#define MAX_AUDIO_DEVICE                  (0x01)


#endif

