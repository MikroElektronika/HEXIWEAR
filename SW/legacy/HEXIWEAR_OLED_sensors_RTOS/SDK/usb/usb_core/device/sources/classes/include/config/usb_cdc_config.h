/**HEADER********************************************************************
*
* Copyright (c) 2015 Freescale Semiconductor;
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
* $FileName: usb_cdc_config.h$
* $Version :
* $Date    :
*
* Comments:
*
* @brief The file contains USB stack CDC class layer api header function.
*
*****************************************************************************/

#ifndef _USB_CDC_CONFIG_H
#define _USB_CDC__CONFIG_H 1

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
/* other macros */
#define PSTN_SUBCLASS_NOTIF_SUPPORT      (1)/*TRUE*/

/* if RNDIS  supported
 * 1 supported
 * 0 not supported
 */
#define CDC_RNDIS_SUPPORT                (0)

/* if CDC queue feature supported
 * 1 supported
 * 0 not supported
 */
#define CDC_IMPLEMENT_QUEUING            (0)

#if CDC_IMPLEMENT_QUEUING
/* macros for queuing */
#define CDC_MAX_QUEUE_ELEMS              (4)
#endif
#define MAX_CDC_DEVICE                   (0x01)
#define MAX_CDC_EP_NUM                   (4)


#endif

