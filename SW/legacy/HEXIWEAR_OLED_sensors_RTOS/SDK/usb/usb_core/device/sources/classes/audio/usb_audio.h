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

#ifndef _USB_AUDIO_H
#define _USB_AUDIO_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_class.h"
#include "usb_audio_config.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/

/* Code of bmRequest Type */
#define SET_REQUEST_ITF                   (0x21)
#define SET_REQUEST_EP                    (0x22)
#define GET_REQUEST_EP                    (0xA2)
#define GET_REQUEST_ITF                   (0xA1) 

/* class specific requests */
#define AUDIO_CONTROL_INPUT_TERMINAL      (0x02)
#define AUDIO_CONTROL_OUTPUT_TERMINAL     (0x03)
#define AUDIO_CONTROL_FEATURE_UNIT        (0x06)

#if USBCFG_AUDIO_CLASS_2_0
#define AUDIO_CONTROL_CLOCK_SOURCE_UNIT                  (0x0A)
#define AUDIO_CONTROL_CLOCK_SELECTOR_UNIT                (0x0B)
#define AUDIO_CONTROL_CLOCK_MULTIPLIER_UNIT              (0x0C)
#define AUDIO_CONTROL_SAMPLE_RATE_CONVERTER_UNIT         (0x0D)

/* Clock Source Control Selectors(A.17.1) */
#define CS_CONTROL_UNDEFINED        (0x00)
#define CS_SAM_FREQ_CONTROL         (0x01)
#define CS_CLOCK_VALID_CONTROL      (0x02)
#define REQUEST_CUR                 (0x01)
#define REQUEST_RANGE               (0x02)
#endif /* AUDIO_CLASS_2_0 */

/* Audio Class Specific Request Codes */
#define REQUEST_CODE_UNDEFINED            (0x00)
#define SET_CUR                           (0x01)
#define SET_MIN                           (0x02)
#define SET_MAX                           (0x03)
#define SET_RES                           (0x04)

#define GET_CUR                           (0x81)
#define GET_MIN                           (0x82)
#define GET_MAX                           (0x83)
#define GET_RES                           (0x84)

#define GET_STAT                          (0xFF)

/* Terminal control selector codes */
#define TE_CONTROL_UNDEFINED              (0x00)
#define COPY_PROTECT_CONTROL              (0x01)

/* feature unit control selector codes */
#define FU_CONTROL_UNDEFINED              (0x00)
/* Feature Unit Control Selector codes */
#define MUTE_CONTROL                      (0x01)
#define VOLUME_CONTROL                    (0x02)
#define BASS_CONTROL                      (0x03)
#define MID_CONTROL                       (0x04)
#define TREBLE_CONTROL                    (0x05)
#define GRAPHIC_EQUALIZER_CONTROL         (0x06)
#define AUTOMATIC_GAIN_CONTROL            (0x07)
#define DELAY_CONTROL                     (0x08)
#define BASS_BOOST_CONTROL                (0x09)
#define LOUDNESS_CONTROL                  (0x0A)

/* Endpoint control selector codes */
#define EP_CONTROL_DEFINED                (0x00)
#define SAMPLING_FREQ_CONTROL             (0x01)
#define PITCH_CONTROL                     (0x02)

#if AUDIO_IMPLEMENT_QUEUING
typedef struct _audio_queue_struct
{
    usb_device_handle handle;
    uint8_t channel;
    audio_app_data_t app_data;
}cdc_queue_struct_t;
#endif

/* USB class audio endpoint data */

typedef struct _audio_endpoint_struct
{
    uint8_t endpoint; /* endpoint num */
    uint8_t type; /* type of endpoint (interrupt, bulk or isochronous) */
#if AUDIO_IMPLEMENT_QUEUING
    uint8_t bin_consumer;/* the num of queued elements */
    uint8_t bin_producer;/* the num of de-queued elements */
    uint8_t queue_num; /* the num of queue */
    audio_queue_struct_t queue[AUDIO_MAX_QUEUE_ELEMS]; /* queue data */
#endif
} audio_endpoint_struct_t;

/* contains the endpoint data for non control endpoints */
typedef struct _audio_endpoint_data_struct
{
    audio_endpoint_struct_t ep[MAX_AUDIO_CLASS_EP_NUM];
} audio_endpoint_data_struct_t;

typedef struct _audio_ut_data_struct
{
    audio_ut_struct_t ut[MAX_AUDIO_CLASS_UT_NUM];
} audio_ut_data_struct_t;

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
void USB_Class_Audio_Event(uint8_t event, void* val, void* arg);
usb_status USB_Audio_Requests(usb_setup_struct_t * setup_packet, uint8_t * *data, uint32_t *size, void* arg);

/******************************************************************************
 Types
 ****************************************************************************/
/* Structure holding AUDIO class state information*/
typedef struct audio_device_struct
{
    audio_handle_t                              audio_handle;
    class_handle_t                              class_handle;
    uint32_t                                    user_handle;
    usb_device_handle                           handle;
    usb_endpoints_t*                            usb_ep_data;
    audio_units_struct_t*                       usb_ut_data;
    audio_ut_data_struct_t                      audio_ut_data;
    audio_endpoint_data_struct_t                audio_endpoint_data;
    usb_application_callback_struct_t           audio_application_callback;
    usb_vendor_req_callback_struct_t            vendor_req_callback;
    usb_class_specific_callback_struct_t        class_specific_callback;
    usb_desc_request_notify_struct_t            desc_callback;
    uint8_t                                     current_interface;
}audio_device_struct_t; 
#endif

/* EOF */
