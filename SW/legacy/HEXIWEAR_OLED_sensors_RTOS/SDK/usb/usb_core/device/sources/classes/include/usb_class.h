/**HEADER********************************************************************
* 
* Copyright (c) 2008, 2013 - 2014 Freescale Semiconductor;
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
* $FileName: usb_class.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains USB stack class layer api header function.
*
*****************************************************************************/

#ifndef _USB_CLASS_H
#define _USB_CLASS_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/



/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
 /*#define DELAYED_PROCESSING  1 This define is used to delay the control 
                                processing and not have it executed as part
                                of the interrupt routine */

//#define UNINITIALISED_VAL        (0xffffffff)  
/* Events to the Application */
/*
#define USB_APP_BUS_RESET           (0)
#define USB_APP_CONFIG_CHANGED      (1)
#define USB_APP_ENUM_COMPLETE       (2)
#define USB_APP_SEND_COMPLETE       (3)
#define USB_APP_DATA_RECEIVED       (4) 
#define USB_APP_ERROR               (5)
#define USB_APP_GET_DATA_BUFF       (6)
#define USB_APP_EP_STALLED          (7)
#define USB_APP_EP_UNSTALLED        (8) 
#define USB_APP_GET_TRANSFER_SIZE   (9)
*/

/******************************************************************************
 * Types
 *****************************************************************************/
typedef uint32_t class_handle_t;

/*callback function pointer structure for application to provide class params*/
typedef uint8_t (_CODE_PTR_ usb_class_specific_handler_func)(
                           uint8_t event,
                           uint16_t value, 
                           uint8_t **data,
                           uint32_t* size,
                           void* arg);


typedef struct usb_class_specific_handler_callback_struct
{
    usb_class_specific_handler_func  callback;
    void*                            arg;
}usb_class_specific_callback_struct_t;


/******************************************************************************
 * Global Functions
 *****************************************************************************/
#if defined(__cplusplus)
    extern "C" {
#endif
/**************************************************************************//*!
 *
 * @name   USB_Class_Periodic_Task
 *
 * @brief  The function calls for periodic tasks
 *
 * @param  None
 *
 * @return None
 *
 *****************************************************************************/
extern void USB_Class_Periodic_Task(void);

#if defined(__cplusplus)
    }
#endif

#endif

/* EOF */
