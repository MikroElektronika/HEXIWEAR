/**HEADER********************************************************************
* 
* Copyright (c) 2008, 2013 Freescale Semiconductor;
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
* $FileName: virtual_com.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains Macro's and functions needed by the virtual com 
*        application
*
*****************************************************************************/

#ifndef _VIRTUAL_COM_H
#define _VIRTUAL_COM_H  1

#include "usb_descriptor.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
/* Implementation Specific Macros */
#define LINE_CODING_SIZE              (0x07)
#define COMM_FEATURE_DATA_SIZE        (0x02)

#define LINE_CODE_DTERATE_IFACE0      (115200) /*e.g 9600 is 0x00002580 */
#define LINE_CODE_CHARFORMAT_IFACE0   (0x00)   /* 1 stop bit */
#define LINE_CODE_PARITYTYPE_IFACE0   (0x00)   /* No Parity */
#define LINE_CODE_DATABITS_IFACE0     (0x08)   /* Data Bits Format */

#define LINE_CODE_DTERATE_IFACE1      (9600)   /*e.g. 115200 is 0x0001C200*/
#define LINE_CODE_CHARFORMAT_IFACE1   (0x00)   /* 1 stop bit */
#define LINE_CODE_PARITYTYPE_IFACE1   (0x00)   /* No Parity */
#define LINE_CODE_DATABITS_IFACE1     (0x08)   /* Data Bits Format */

#define STATUS_ABSTRACT_STATE_IFACE0  (0x0000) /* Disable Multiplexing
                                                ENDP in this interface will
                                                continue to accept/offer data*/
#define STATUS_ABSTRACT_STATE_IFACE1  (0x0000) /* Disable Multiplexing
                                                ENDP in this interface will
                                                continue to accept/offer data*/
#define COUNTRY_SETTING_IFACE0        (0x0000) /* Country Code in the format as
                                                defined in [ISO3166] */
#define COUNTRY_SETTING_IFACE1        (0x0000) /* Country Code in the format as
                                                defined in [ISO3166] */
/*****************************************************************************
 * Global variables
 *****************************************************************************/
   
/*****************************************************************************
 * Global Functions
 *****************************************************************************/
void cdc_vcom_init(void *param);
void cdc_vcom_preinit(void);
uint8_t VCom_USB_App_Class_Callback(uint8_t event, uint16_t value, uint8_t ** data, uint32_t* size, void* arg);
void VCom_USB_App_Device_Callback(uint8_t event_type, void* val,void* arg);
void cdc_vcom_task(void);
#endif 


/* EOF */
