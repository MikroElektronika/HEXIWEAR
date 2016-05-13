/**HEADER********************************************************************
* 
* Copyright (c)  2014 Freescale Semiconductor;
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
* $FileName: usb_pin_detect.h$
* $Version : 
* $Date    : 
*
* Comments:
*
*   
*
*END************************************************************************/

#ifndef __usb_pin_detect_h__
#define __usb_pin_detect_h__

typedef void(_CODE_PTR_ usb_pin_detect_service_t)(uint32_t event);


#define  USB_DEVICE_ID_CHANGE                       (1)   /*  id change from device mode*/
#define  USB_HOST_ID_CHANGE                         (2)   /* id change from host mode */

/*!
 * @brief Registers a callback function for usb device pin detect 
 *
 * The function is used to register a callback function for one specified endpoint.
 *
 * @param uint8_t USB controller id
 * @param service callback function
 * @param arg second parameter for the callback function
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_device_register_pin_detect_service(uint8_t controller_id, usb_pin_detect_service_t service, void* arg);

/*!
 * @brief Registers a callback function for usb host pin detect
 *
 * The function is used to register a callback function for one specified endpoint.
 *
 * @param uint8_t USB controller id
 * @param service callback function
 * @param arg second parameter for the callback function
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status usb_host_register_pin_detect_service(uint8_t controller_id, usb_pin_detect_service_t service, void* arg);


#endif

