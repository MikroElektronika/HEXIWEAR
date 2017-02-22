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
* $FileName: usb_audio.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains USB stack AUDIO class layer api header function.
*
*****************************************************************************/

#ifndef _USB_CLASS_AUDIO_H
#define _USB_CLASS_AUDIO_H 1


/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class.h"
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/

/* command */
/* GET CUR COMMAND */
#define GET_CUR_MUTE_CONTROL                        (0x8101)
#define GET_CUR_VOLUME_CONTROL                      (0x8102)
#define GET_CUR_BASS_CONTROL                        (0x8103)
#define GET_CUR_MID_CONTROL                         (0x8104)
#define GET_CUR_TREBLE_CONTROL                      (0x8105)
#define GET_CUR_GRAPHIC_EQUALIZER_CONTROL           (0x8106)
#define GET_CUR_AUTOMATIC_GAIN_CONTROL              (0x8107)
#define GET_CUR_DELAY_CONTROL                       (0x8108)
#define GET_CUR_BASS_BOOST_CONTROL                  (0x8109)
#define GET_CUR_LOUDNESS_CONTROL                    (0x810A)

/* GET MIN COMMAND */
#define GET_MIN_VOLUME_CONTROL                      (0x8202)
#define GET_MIN_BASS_CONTROL                        (0x8203)
#define GET_MIN_MID_CONTROL                         (0x8204)
#define GET_MIN_TREBLE_CONTROL                      (0x8205)
#define GET_MIN_GRAPHIC_EQUALIZER_CONTROL           (0x8206)
#define GET_MIN_DELAY_CONTROL                       (0x8208)

/* GET MAX COMMAND */
#define GET_MAX_VOLUME_CONTROL                      (0x8302)
#define GET_MAX_BASS_CONTROL                        (0x8303)
#define GET_MAX_MID_CONTROL                         (0x8304)
#define GET_MAX_TREBLE_CONTROL                      (0x8305)
#define GET_MAX_GRAPHIC_EQUALIZER_CONTROL           (0x8306)
#define GET_MAX_DELAY_CONTROL                       (0x8308)

/* GET RES COMMAND */
#define GET_RES_VOLUME_CONTROL                      (0x8402)
#define GET_RES_BASS_CONTROL                        (0x8403)
#define GET_RES_MID_CONTROL                         (0x8404)
#define GET_RES_TREBLE_CONTROL                      (0x8405)
#define GET_RES_GRAPHIC_EQUALIZER_CONTROL           (0x8406)
#define GET_RES_DELAY_CONTROL                       (0x8408)

/* SET CUR COMMAND */
#define SET_CUR_MUTE_CONTROL                        (0x0101)
#define SET_CUR_VOLUME_CONTROL                      (0x0102)
#define SET_CUR_BASS_CONTROL                        (0x0103)
#define SET_CUR_MID_CONTROL                         (0x0104)
#define SET_CUR_TREBLE_CONTROL                      (0x0105)
#define SET_CUR_GRAPHIC_EQUALIZER_CONTROL           (0x0106)
#define SET_CUR_AUTOMATIC_GAIN_CONTROL              (0x0107)
#define SET_CUR_DELAY_CONTROL                       (0x0108)
#define SET_CUR_BASS_BOOST_CONTROL                  (0x0109)
#define SET_CUR_LOUDNESS_CONTROL                    (0x010A)

/* SET MIN COMMAND */
#define SET_MIN_VOLUME_CONTROL                      (0x0202)
#define SET_MIN_BASS_CONTROL                        (0x0203)
#define SET_MIN_MID_CONTROL                         (0x0204)
#define SET_MIN_TREBLE_CONTROL                      (0x0205)
#define SET_MIN_GRAPHIC_EQUALIZER_CONTROL           (0x0206)
#define SET_MIN_DELAY_CONTROL                       (0x0208)

/* SET MAX COMMAND */
#define SET_MAX_VOLUME_CONTROL                      (0x0302)
#define SET_MAX_BASS_CONTROL                        (0x0303)
#define SET_MAX_MID_CONTROL                         (0x0304)
#define SET_MAX_TREBLE_CONTROL                      (0x0305)
#define SET_MAX_GRAPHIC_EQUALIZER_CONTROL           (0x0306)
#define SET_MAX_DELAY_CONTROL                       (0x0308)

/* SET RES COMMAND */
#define SET_RES_VOLUME_CONTROL                      (0x0402)
#define SET_RES_BASS_CONTROL                        (0x0403)
#define SET_RES_MID_CONTROL                         (0x0404)
#define SET_RES_TREBLE_CONTROL                      (0x0405)
#define SET_RES_GRAPHIC_EQUALIZER_CONTROL           (0x0406)
#define SET_RES_DELAY_CONTROL                       (0x0408)

#if USBCFG_AUDIO_CLASS_2_0
/* Clock Source Control Selectors(A.17.1) */
#define SET_CUR_SAM_FREQ_CONTROL                    (0x0501)
#define SET_CUR_CLOCK_VALID_CONTROL                 (0x0502)
#define GET_CUR_SAM_FREQ_CONTROL                    (0x8501)
#define GET_RANGE_SAM_FREQ_CONTROL                  (0x9501)
#define GET_CUR_CLOCK_VALID_CONTROL                 (0x8502)
#endif


#define GET_CUR_COPY_PROTECT_CONTROL                (0x810B)

#define GET_CUR_SAMPLING_FREQ_CONTROL               (0x810C)
#define GET_MIN_SAMPLING_FREQ_CONTROL               (0x820C)
#define GET_MAX_SAMPLING_FREQ_CONTROL               (0x830C)
#define GET_RES_SAMPLING_FREQ_CONTROL               (0x840C)

#define GET_CUR_PITCH_CONTROL                       (0x810D)
#define GET_MIN_PITCH_CONTROL                       (0x820D)
#define GET_MAX_PITCH_CONTROL                       (0x830D)
#define GET_RES_PITCH_CONTROL                       (0x840D)

#define SET_CUR_COPY_PROTECT_CONTROL                (0x010B)

#define SET_CUR_SAMPLING_FREQ_CONTROL               (0x010C)
#define SET_MIN_SAMPLING_FREQ_CONTROL               (0x020C)
#define SET_MAX_SAMPLING_FREQ_CONTROL               (0x030C)
#define SET_RES_SAMPLING_FREQ_CONTROL               (0x040C)

#define SET_CUR_PITCH_CONTROL                       (0x010D)

#define SET_MEM                           (0x05)
#define GET_MEM                           (0x85)

#define USB_REQ_VAL_INVALID              (0xFFFF)

#if USBCFG_AUDIO_CLASS_2_0
PACKED_STRUCT_BEGIN
struct _usb_cntrl_range {
 uint16_t    numranges;
 uint32_t    min;
 uint32_t    max;
 uint32_t    res;
}
PACKED_STRUCT_END;
typedef struct _usb_cntrl_range usb_cntrl_range;
#endif

 /*!
  * @brief structure to hold the information of audio app data struct.
  *
  * Define the structure of the audio app data. 
  *
  */
typedef struct _audio_app_data_struct
{
    uint8_t*      data_ptr;    /*!< pointer to buffer       */     
    uint32_t      data_size;   /*!< buffer size of endpoint */
}audio_app_data_t;

/*!
 * @brief structure to hold the information of endpoint feature unit type.
 *
 * Define the structure of the endpoint feature unit type. 
 *
 */
typedef struct _audio_ut_struct
{
  uint8_t         unit_id;     /*!< endpoint number         */
  uint8_t         type;        /*!< type of endpoint        */
}audio_ut_struct_t;

/*!
 * @brief structure to hold the information of endpoint unit struct.
 *
 * Define the structure of the endpoint unit struct. 
 *
 */
typedef  struct _audio_units_struct 
{
   uint8_t            count;       /*!< Number of terminal or Feature Unit End point */
   audio_ut_struct_t* put;         /*!< Array of terminal or Feature Unit */
}audio_units_struct_t; 

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

 /******************************************************************************
 * Types
 *****************************************************************************/
 /* struct represents the AUDIO class handle */
 typedef uint32_t audio_handle_t;

 /*!
  * @brief structure used to configure Audio class by APP.
  *
  * Define the structure of the audio class configuration. 
  *
  */
 typedef struct audio_config_struct
 {
    usb_application_callback_struct_t       audio_application_callback;        /*!< application callback function to handle the Device status related event*/      
    usb_vendor_req_callback_struct_t        vendor_req_callback;               /*!< application callback function to handle the vendor request related event, reserved for future use*/ 
    usb_class_specific_callback_struct_t    class_specific_callback;           /*!< application callback function to handle all the class related event*/
    usb_desc_request_notify_struct_t*       desc_callback_ptr;                 /*!< descriptor related callback function data structure*/
 }audio_config_struct_t;
/******************************************************************************
 * Global Functions
 *****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*!
 * @brief The function initializes the Device and Controller layer
 *
 * This function initializes the Audio Class layer and layers it is dependent on 
 *
 * @param controller_id       [in] - controller ID, such as USB_CONTROLLER_KHCI_0
 * @param audio_config_ptr    [in] - AUDIO configuration structure, refer to audio_config_struct_t
 * @param audioHandle         [out] - pointer point to the initialized AUDIO class, refer to audio_handle_t
 *
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_Audio_Init
(
    uint8_t                 controller_id,
    audio_config_struct_t*  audio_config_ptr,
    audio_handle_t*         audioHandle
);

/*!
 * @brief The function de-initializes the Device and Controller layer
 *
 * This function initializes the Audio Class layer and layers it is dependent on 
 *
 * @param handle          :   handle returned by USB_Class_HID_Init   
 *
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_Audio_Deinit
(
    audio_handle_t  handle
);

/*!
 * @brief This function is used to send data to the host
 *
 * The function calls this API function to send data specified by buff_ptr and size. 
 *
 * @param handle          :   handle returned by USB_Class_Audio_Send_Data
 * @param ep_num          :   endpoint num 
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer   
 *
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_Audio_Send_Data
(
    audio_handle_t       handle,        /* [IN]*/
    uint8_t              ep_num,        /* [IN]*/
    uint8_t*             app_buff,      /* [IN] buffer to send */      
    uint32_t             size           /* [IN] length of the transfer */
);

/*!
 * @brief This function receives Data from Host.
 *
 * The function calls this API function to receive data from host.
 *
 * @param handle          :   handle returned by USB_Class_Audio_Recv_Data
 * @param ep_num          :   endpoint num 
 * @param app_buff        :   buffer to send
 * @param size            :   length of the transfer   
 *
 * @return USB_OK-Success/Others-Fail
 */
extern usb_status USB_Class_Audio_Recv_Data
(
    audio_handle_t       audio_handle,
    uint8_t              ep_num,
    uint8_t*             buff_ptr,      /* [IN] buffer to recv */      
    uint32_t             size           /* [IN] length of the transfer */
);

#if USBCFG_DEV_ADVANCED_CANCEL_ENABLE
/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Cancel
 *
 * @brief 
 *
 * @param handle          :   handle returned by USB_Class_HID_Init
 * @param ep_num          :   endpoint num 
 * @param direction        :   direction of the endpoint 
 *
 * @return status       
 *         USB_OK           : When Successfull 
 *         Others           : Errors
 *****************************************************************************/

extern usb_status USB_Class_Audio_Cancel
(
    audio_handle_t handle,/*[IN]*/
    uint8_t ep_num,/*[IN]*/
    uint8_t direction
);
#endif

/**************************************************************************//*!
 *
 * @name  USB_Class_Audio_Get_Speed
 *
 * @brief This functions get speed from Host.
 *
 * @param handle          :   handle returned by USB_Class_Audio_Init
 * @param speed           :   speed
 *
 * @return status       
 *         USB_OK         : When Successfull 
 *         Others         : Errors
 *****************************************************************************/
usb_status USB_Class_Audio_Get_Speed
(
    audio_handle_t       audio_handle,
    uint16_t *           speed/* [OUT] the requested error */
);
#ifdef __cplusplus
}
#endif

#endif

/* EOF */
