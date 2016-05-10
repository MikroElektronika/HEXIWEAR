/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010, 2013 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
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
 **************************************************************************//*!
 *
 * @file usb_composite.h
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains USB stack Video class layer API header function.
 *
 *****************************************************************************/


#ifndef _USB_CLASS_COMPOSITE_H
#define _USB_CLASS_COMPOSITE_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "usb_class.h"


/******************************************************************************
 * Macro's
 *****************************************************************************/
/* Composite class type */ 

 /*!
  * @brief Represents the composite class handle..
  *
  * This structure represents the composite class handle.. 
  *
  */
 typedef uint32_t composite_handle_t;
/******************************************************************************
 * Types
 *****************************************************************************/

 /*!
  * @brief Structure used to configure composite class by APP.
  *
  * Define the structure of the composite class configuration. 
  *
  */
 typedef struct _class_config_struct
 {
     usb_application_callback_struct_t          composite_application_callback;           /*!< application callback function to handle the Device status related event for the specified type of class*/
     usb_vendor_req_callback_struct_t           vendor_req_callback;                      /*!< application callback function to handle the vendor request related event, reserved for future use*/
     usb_class_specific_callback_struct_t       class_specific_callback;                  /*!< application callback function to handle all the class related event for the specified type of class*/
     usb_desc_request_notify_struct_t*          desc_callback_ptr;                        /*!< related callback function data structure for the specified type of class*/
     uint32_t                                   class_handle;                             /*!< the handle of the class*/
     class_type                                 type;                                     /*!< class type*/
 }class_config_struct_t;


 /*!
  * @brief Structure used to hold the detailed information about the composite class configuration.
  *
  * Define the structure of detailed information of the composite class.
  *
  */
 typedef struct _composite_config_struct
 {
     uint8_t                                    count;               /*!< Number of class support */   
     class_config_struct_t*                     class_app_callback;  /*!< Array of Endpoints Structures */
 }composite_config_struct_t;
 
/******************************************************************************
 * Global function prototypes
 *****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif 
 /*!
 * @brief The function initializes the Device and Controller layer
 *
 * This function initializes the Composite Class layer and layers it is dependent on 
 *
 * @param controller_id             [in] - controller ID, like USB_CONTROLLER_KHCI_0
 * @param composite_callback_ptr    [in] - composite configuration structure, refer to composite_config_struct_t
 * @param compositeHandle           [out] - pointer point to the initialized composite class, refer to composite_handle_t    
 *
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Composite_Init(
    uint8_t                    controller_id,                /* [IN] Controller ID */
    composite_config_struct_t* composite_callback_ptr,       /* [IN] Pointer to class info */
    composite_handle_t*         compositeHandle   
);

/*!
* @brief The function de-initializes the Device and Controller layer
*
* This function de-initializes the Composite Class layer and layers it is dependent on
*
* @param compositeHandle   [in] - pointer point to the initialized composite class, refer to composite_handle_t    
*
* @return USB_OK-Success/Others-Fail
*/
extern usb_status USB_Composite_DeInit(
    composite_handle_t          handle               /* [IN] Controller ID */
);

/**************************************************************************//*!
 *
 * @name  USB_Composite_Get_Speed
 *
 * @brief This functions get speed from Host.
 *
 * @param handle          :   handle returned by USB_Composite_Init
 * @param speed           :   speed
 *
 * @return status       
 *         USB_OK         : When Successfull 
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Composite_Get_Speed
(
    composite_handle_t   handle,
    uint16_t *           speed/* [OUT] the requested error */
);
#ifdef __cplusplus
}
#endif
#endif
/* EOF */
