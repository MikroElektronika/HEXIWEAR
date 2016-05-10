/**HEADER********************************************************************
* 
* Copyright (c) 2013 - 2015 Freescale Semiconductor;
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
* $FileName: usb_device_config.h$
* $Version : 
* $Date    : 
*
* Comments:
*
*   
*
*END************************************************************************/

#ifndef __usb_dev_config_h__
#define __usb_dev_config_h__

/* if KHCI device supported 
 * 1 supported
 * 0 not supported
 */
#define USBCFG_DEV_KHCI                   1

/* if EHCI device supported 
 * 1 supported
 * 0 not supported
 */
#define USBCFG_DEV_EHCI                   0

/* how many device KHCI instance supported */
#if USBCFG_DEV_KHCI
#define USBCFG_DEV_KHCI_NUM               1
#else
#define USBCFG_DEV_KHCI_NUM               0
#endif

/* how many device EHCI instance supported */
#if USBCFG_DEV_EHCI
#define USBCFG_DEV_EHCI_NUM               0
#else
#define USBCFG_DEV_EHCI_NUM               0
#endif

/* how many device instance supported */
#define USBCFG_DEV_NUM                    (USBCFG_DEV_KHCI_NUM + USBCFG_DEV_EHCI_NUM)

/* if HID device supported 
 * 1 supported
 * 0 not supported
 */
#define USBCFG_DEV_HID                    1

/* if PHDC device supported 
 * 1 supported
 * 0 not supported
 */
#define USBCFG_DEV_PHDC                   0

/* if AUDIO device supported 
 * 1 supported
 * 0 not supported
 */
#define USBCFG_DEV_AUDIO                  0

/* if CDC device supported 
 * 1 supported
 * 0 not supported
 */
#define USBCFG_DEV_CDC                    1

/* if MSC device supported 
 * 1 supported
 * 0 not supported
 */
#define USBCFG_DEV_MSC                    1

/* if composite device supported 
 * 1 supported
 * 0 not supported
 */
#define USBCFG_DEV_COMPOSITE              1

/* if device is self powered 
 * 1 self power
 * 0 bus power
 */
#define USBCFG_DEV_SELF_POWER             0

/* if device remote wakeup supported 
 * 1 supported
 * 0 not supported
 */
#define USBCFG_DEV_REMOTE_WAKEUP          0

/* how many endpoints are supported */
#define USBCFG_DEV_MAX_ENDPOINTS          (6)

/* how many XDs are supported at most */
#define USBCFG_DEV_MAX_XDS                (12)

/* how many instance should be supported for one class type device */
#define USBCFG_DEV_MAX_CLASS_OBJECT       (1)

#if USBCFG_DEV_KHCI
    /* 
    ** Allow workaround for bug in the peripheral when unaligned buffer @4B address is used
    */
    #define USBCFG_KHCI_4BYTE_ALIGN_FIX                (1)

    #if USBCFG_KHCI_4BYTE_ALIGN_FIX
    /*
    ** The aligned buffer size for IN transactions, active when USBCFG_KHCI_4BYTE_ALIGN_FIX is defined
    */
    #define USBCFG_DEV_KHCI_SWAP_BUF_MAX               (64)
    #endif

    #define USBCFG_DEV_KHCI_ADVANCED_ERROR_HANDLING    (0)
#endif

/* if USB Keep Alive is enabled 
 * 1 enabled
 * 0 not enabled
 */
#define USBCFG_DEV_KEEP_ALIVE_MODE            (0)

/* If the buffer provided by APP is cacheable
* 1 cacheable, buffer cache maintenance is needed
* 0 uncacheable, buffer cache maintenance is not needed
*/
#define USBCFG_DEV_BUFF_PROPERTY_CACHEABLE    (0)

#define USBCFG_DEV_ADVANCED_SUSPEND_RESUME    (0)

#define USBCFG_DEV_ADVANCED_CANCEL_ENABLE     (1)

#define USBCFG_DEV_DETACH_ENABLE              (0)

#define USBCFG_DEV_IO_DETACH_ENABLE           (0)

#endif

