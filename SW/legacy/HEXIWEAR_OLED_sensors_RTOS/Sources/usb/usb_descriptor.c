/**HEADER********************************************************************
* 
* Copyright (c) 2004 - 2009, 2013 - 2015 Freescale Semiconductor;
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
************************************************************************** *

*
* @file usb_descriptor.c
*
* @author
*
* @version
*
* @date 
*
* @brief The file contains USB descriptors and functions
*
*****************************************************************************/

/******************************************************************************
* Includes
*****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"    

#include "disk.h"
#include "virtual_com.h"
#include "composite_app.h"
#include "usb_descriptor.h"

#if (defined __MCF52xxx_H__)||(defined __MK_xxx_H__)
/* Put CFV2 descriptors in RAM */
#define USB_DESC_CONST
#else

#define USB_DESC_CONST    const
#endif

/*****************************************************************************
* Constant and Macro's
*****************************************************************************/
static device_lba_info_struct_t usb_msc_lba_info_struct;
/* structure containing details of all the endpoints used by this device */
usb_ep_struct_t cic_ep[CIC_ENDP_COUNT] =  {
        #if CIC_NOTIF_ELEM_SUPPORT
        {
#if HIGH_SPEED
            HS_CIC_NOTIF_ENDPOINT, 
#else
            FS_CIC_NOTIF_ENDPOINT, 
#endif
            USB_INTERRUPT_PIPE, 
            USB_SEND,
            CIC_NOTIF_ENDP_PACKET_SIZE
        }
        #endif
};

usb_ep_struct_t dic_ep[DIC_ENDP_COUNT] =  {
        #if DATA_CLASS_SUPPORT
            {
#if HIGH_SPEED
                HS_DIC_BULK_IN_ENDPOINT, 
#else
                FS_DIC_BULK_IN_ENDPOINT, 
#endif
                USB_BULK_PIPE, 
                USB_SEND,
                DIC_BULK_IN_ENDP_PACKET_SIZE
            }, 
            {
#if HIGH_SPEED
                HS_DIC_BULK_OUT_ENDPOINT, 
#else
                FS_DIC_BULK_OUT_ENDPOINT, 
#endif
                USB_BULK_PIPE, 
                USB_RECV,
                DIC_BULK_OUT_ENDP_PACKET_SIZE
            } 
        #endif
};

usb_ep_struct_t msd_ep[MSC_DESC_ENDPOINT_COUNT] = 
{  
    {
#if HIGH_SPEED
        HS_BULK_IN_ENDPOINT, 
#else
        FS_BULK_IN_ENDPOINT, 
#endif
        USB_BULK_PIPE, 
        USB_SEND,
        BULK_IN_ENDP_PACKET_SIZE
    }, 
    {
#if HIGH_SPEED
        HS_BULK_OUT_ENDPOINT, 
#else
        FS_BULK_OUT_ENDPOINT, 
#endif
        USB_BULK_PIPE, 
        USB_RECV,
        BULK_OUT_ENDP_PACKET_SIZE
    }        
};
#define USB_CDC_IF_MAX 2
#define USB_MSD_IF_MAX 1
#define USB_CDC_CFG_MAX 1
#define USB_MSD_CFG_MAX 1
#define USB_MSD_CDC_CLASS_MAX 2

/* Interfaces */
static usb_if_struct_t usb_cdc_if[USB_CDC_IF_MAX] = {
    USB_DESC_INTERFACE(0, CIC_ENDP_COUNT, cic_ep),
    USB_DESC_INTERFACE(1, DIC_ENDP_COUNT, dic_ep),
};

static usb_if_struct_t usb_msd_if[USB_MSD_IF_MAX] = {
    USB_DESC_INTERFACE(2, MSC_DESC_ENDPOINT_COUNT, msd_ep),
};

/* Configuration */
static usb_interfaces_struct_t usb_cdc_configuration[USB_CDC_CFG_MAX] = {
    USB_DESC_CONFIGURATION(USB_CDC_IF_MAX, usb_cdc_if),
};

static usb_interfaces_struct_t usb_msd_configuration[USB_MSD_CFG_MAX] = {
    USB_DESC_CONFIGURATION(USB_MSD_IF_MAX, usb_msd_if),
};

static usb_class_struct_t usb_dec_class[USB_MSD_CDC_CLASS_MAX] =
{
    {
        USB_CLASS_CDC,
        USB_DESC_CONFIGURATION(USB_CDC_IF_MAX, usb_cdc_if),
    },
    {
        USB_CLASS_MSC,
        USB_DESC_CONFIGURATION(USB_MSD_IF_MAX, usb_msd_if),
    },
};

static usb_composite_info_struct_t usb_composite_info =
{
    2,
    usb_dec_class,
};

uint8_t g_device_descriptor[DEVICE_DESCRIPTOR_SIZE] =
{
    /* "Device Descriptor Size */
    DEVICE_DESCRIPTOR_SIZE,
    /* "Device" Type of descriptor */
    USB_DEVICE_DESCRIPTOR,
    0x00, 0x02,                           /*  BCD USB version               */
    0xEF,                                 /*  Miscellaneous Device Class    */
    0x02,                                 /*  Common Class  */
    0x01,                                 /*  Interface Association Descriptor */
    /* Max Packet size */
    CONTROL_MAX_PACKET_SIZE,
    /* Vendor ID */
    /*0xA2,0x15,*/
	0x00,0x00,
    /* Product ID */
    0x00,0x10,
    /* BCD Device version */
    0x00,0x10,
    /* Manufacturer string index */
    0x01,
    /* Product string index */
    0x02,
    /*  Serial number string index */
    0x03,
    /*  Number of configurations */
    0x01
};

uint8_t g_config_descriptor[CONFIG_DESC_SIZE] =
{
    /* Configuration Descriptor Size - always 9 bytes*/
    CONFIG_ONLY_DESC_SIZE,
    /* "Configuration" type of descriptor */
    USB_CONFIG_DESCRIPTOR,
    /*  Total length of the Configuration descriptor */
    CONFIG_DESC_SIZE, 0x00,
    /*  NumInterfaces */
    (uint8_t)(3),
    /*  Configuration Value */
    0x01,
    /* Configuration Description String Index */
    0x01,
    /*  Attributes.support RemoteWakeup and self power */
    (USB_DESC_CFG_ATTRIBUTES_D7_POS) | (USBCFG_DEV_SELF_POWER << USB_DESC_CFG_ATTRIBUTES_SELF_POWERED_SHIFT) | (USBCFG_DEV_REMOTE_WAKEUP << USB_DESC_CFG_ATTRIBUTES_REMOTE_WAKEUP_SHIFT),
    /*  Current draw from bus */
    CONFIG_DESC_CURRENT_DRAWN,


/////////////////////////////////////////////////////////////////////////////
    /* Interface Association Descriptor */
    IAD_DESC_SIZE,                       /* Size of this descriptor */
    USB_IFACE_ASSOCIATION_DESCRIPTOR,    /* INTERFACE ASSOCIATION Descriptor */
    0x00,                                /* Interface number of the CDC Control
                                            interface that is associated with this function */
    0x02,                                /* Number of contiguous CDC interfaces
                                            that are associated with this function */
    CDC_CLASS,                              /* CDC_CC */
    0x03,
    0x00,                                /* Not used */
    0x02,                                /* Index to string descriptor */
/////////////////////////////////////////////////////////////////////////////

    /* Communication Interface Class Descriptor */
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,  /* Interface Descriptor */
    0x00, /* bInterfaceNumber */
    0x00, /* bAlternateSetting */
    CIC_ENDP_COUNT, /* management and notification(optional)element present */
    CDC_CLASS, /* Communication Interface Class */
    CIC_SUBCLASS_CODE,
    CIC_PROTOCOL_CODE,
    0x00, /* Interface Description String Index*/

    /* Header functional descriptor */
    0x05,             /* size of Functional Desc in bytes */
    USB_CS_INTERFACE,  /* descriptor type*/
    HEADER_FUNC_DESC, /* Header functional descriptor */
    0x10, 0x01,  /* USB Class Definitions for CDC spec release number in BCD */

	/* Call Management Functional Descriptor */
    0x05,             /* Size of this descriptor */
    USB_CS_INTERFACE, /* descriptor type*/
    CALL_MANAGEMENT_FUNC_DESC, /* Call Management Functional Descriptor */
    0x00,            /* Device doesn’t handle call management itself */
    0x01,      /* Interface used for call management (bInterfaceNumber of a data class interface in this configuration) */

	/* Abstract Control Management Functional Descriptor */
    0x04,             /* Size of this descriptor */
    USB_CS_INTERFACE, /* descriptor type*/
    ABSTRACT_CONTROL_FUNC_DESC, /* Abstract Control Management Functional Descriptor */
    0x02, /*Support for the SET_LINE_CODING, SET_CONTROL_LINE, and GET_LINE_CODING requests and the SERIAL_STATE notification */

	/* Union Functional Descriptor */
    0x05,             /* size of Functional Desc in bytes */
    USB_CS_INTERFACE,  /* descriptor type*/
    UNION_FUNC_DESC, /* Union Functional Descriptor */
    0x00,           /* The controlling interface for the union (bInterfaceNumber of a Communication or Data Class interface in this configuration) */
    0x01,            /* The controlled interface in the union (bInterfaceNumber of an interface in this configuration) */

    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
#if HIGH_SPEED
    HS_CIC_NOTIF_ENDPOINT|(USB_SEND << 7),
#else
    FS_CIC_NOTIF_ENDPOINT|(USB_SEND << 7),
#endif
    USB_INTERRUPT_PIPE,
    CIC_NOTIF_ENDP_PACKET_SIZE, CIC_NOTIF_ENDP_PACKET_SIZE >> 8,
    0x0A,

	/* Data Interface Descriptor */
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,
    (uint8_t)(0x00+DATA_CLASS_SUPPORT), /* bInterfaceNumber */
    0x00, /* bAlternateSetting */
    DIC_ENDP_COUNT, /* notification element included */
    0x0A, /* DATA Interface Class */
    0x00, /* Data Interface SubClass Code */
    DIC_PROTOCOL_CODE,
    0x05, /* Interface Description String Index*/

    /*Endpoint descriptor */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
#if HIGH_SPEED
    HS_DIC_BULK_IN_ENDPOINT|(USB_SEND << 7),
#else
    FS_DIC_BULK_IN_ENDPOINT|(USB_SEND << 7),
#endif
    USB_BULK_PIPE,
    DIC_BULK_IN_ENDP_PACKET_SIZE, 0x00,
    0x00,/* This value is ignored for Bulk ENDPOINT */

    /*Endpoint descriptor */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
#if HIGH_SPEED
    HS_DIC_BULK_OUT_ENDPOINT|(USB_RECV << 7),
#else
    FS_DIC_BULK_OUT_ENDPOINT|(USB_RECV << 7),
#endif
    USB_BULK_PIPE,
    DIC_BULK_OUT_ENDP_PACKET_SIZE, 0x00,
    0x00, /* This value is ignored for Bulk ENDPOINT */


////////////////////////////////////////////////////////////////////////////////////
	/* Mass Storage Class Interface Descriptor*/
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,
    /* bInterfaceNumber */
    0x02,
    /* bAlternateSetting */
    0x00,
    (uint8_t)MSC_DESC_ENDPOINT_COUNT,
    /* Interface Class */
    MASS_STORAGE_CLASS,
    /* Interface Subclass*/
    SCSI_TRANSPARENT_COMMAND_SET,
    /* Interface Protocol*/
    BULK_ONLY_PROTOCOL,
    /* Interface Description String Index*/
    0x00,

    /*Endpoint descriptor */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
#if HIGH_SPEED
    HS_BULK_IN_ENDPOINT|(USB_SEND << 7),
#else
    FS_BULK_IN_ENDPOINT|(USB_SEND << 7),
#endif
    USB_BULK_PIPE,
    USB_uint_16_low(BULK_IN_ENDP_PACKET_SIZE),
    USB_uint_16_high(BULK_IN_ENDP_PACKET_SIZE),
    0x00,/* This value is ignored for Bulk ENDPOINT */

    /*Endpoint descriptor */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
#if HIGH_SPEED
    HS_BULK_OUT_ENDPOINT|(USB_RECV << 7),
#else
    FS_BULK_OUT_ENDPOINT|(USB_RECV << 7),
#endif
    USB_BULK_PIPE,
    USB_uint_16_low(BULK_OUT_ENDP_PACKET_SIZE),
    USB_uint_16_high(BULK_OUT_ENDP_PACKET_SIZE),
    0x00, /* This value is ignored for Bulk ENDPOINT */

};

#if HIGH_SPEED
uint8_t g_device_qualifier_descriptor[DEVICE_QUALIFIER_DESCRIPTOR_SIZE] =
{
    /* Device Qualifier Descriptor Size */
    DEVICE_QUALIFIER_DESCRIPTOR_SIZE,
    /* Type of Descriptor */
    USB_DEVQUAL_DESCRIPTOR,
    /*  BCD USB version  */
    USB_uint_16_low(BCD_USB_VERSION), USB_uint_16_high(BCD_USB_VERSION),
    /* bDeviceClass */
    DEVICE_DESC_DEVICE_CLASS,
    /* bDeviceSubClass */
    DEVICE_DESC_DEVICE_SUBCLASS,
    /* bDeviceProtocol */
    DEVICE_DESC_DEVICE_PROTOCOL,
    /* bMaxPacketSize0 */
    CONTROL_MAX_PACKET_SIZE,
    /* bNumConfigurations */
    DEVICE_DESC_NUM_CONFIG_SUPPOTED,
    /* Reserved : must be zero */
    0x00
};

uint8_t g_other_speed_config_descriptor[OTHER_SPEED_CONFIG_DESCRIPTOR_SIZE] =
{
    CONFIG_ONLY_DESC_SIZE,
    /* This is a Other speed config descr */
    USB_OTHER_SPEED_DESCRIPTOR,
    /*  Total length of the Configuration descriptor */
    USB_uint_16_low(CONFIG_DESC_SIZE), USB_uint_16_high(CONFIG_DESC_SIZE),
    0x03,
    /*value used to select this configuration : Configuration Value */
    1,
    /*  Configuration Description String Index*/
    0,
    /*Attributes.support RemoteWakeup and self power*/
    (USB_DESC_CFG_ATTRIBUTES_D7_POS) | (USBCFG_DEV_SELF_POWER << USB_DESC_CFG_ATTRIBUTES_SELF_POWERED_SHIFT) | (USBCFG_DEV_REMOTE_WAKEUP << USB_DESC_CFG_ATTRIBUTES_REMOTE_WAKEUP_SHIFT),
    /*  Current draw from bus */
    CONFIG_DESC_CURRENT_DRAWN,

    /* INTERFACE DESCRIPTOR */
    IFACE_ONLY_DESC_SIZE,
    USB_IFACE_DESCRIPTOR,
    /* bInterfaceNumber */
    0x00,
    /* bAlternateSetting */
    0x00,
    (uint8_t)MSC_DESC_ENDPOINT_COUNT,
    /* Interface Class */
    MASS_STORAGE_CLASS,
    /* Interface Subclass*/
    SCSI_TRANSPARENT_COMMAND_SET,
    /* Interface Protocol*/
    BULK_ONLY_PROTOCOL,
    /* Interface Description String Index*/
    0x00,

    /*Endpoint descriptor */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    BULK_IN_ENDPOINT|(USB_SEND << 7),
    USB_BULK_PIPE,
    USB_uint_16_low(BULK_IN_ENDP_PACKET_SIZE),
    USB_uint_16_high(BULK_IN_ENDP_PACKET_SIZE),
    0x00,/* This value is ignored for Bulk ENDPOINT */

    /*Endpoint descriptor */
    ENDP_ONLY_DESC_SIZE,
    USB_ENDPOINT_DESCRIPTOR,
    BULK_OUT_ENDPOINT|(USB_RECV << 7),
    USB_BULK_PIPE,
    USB_uint_16_low(BULK_OUT_ENDP_PACKET_SIZE),
    USB_uint_16_high(BULK_OUT_ENDP_PACKET_SIZE),
    0x00 /* This value is ignored for Bulk ENDPOINT */
};
#endif

uint8_t USB_STR_0[USB_STR_0_SIZE+USB_STR_DESC_SIZE] =
{ sizeof(USB_STR_0),
    USB_STRING_DESCRIPTOR,
    0x09,
    0x04/*equivalent to 0x0409*/
};

/*  Manufacturer string */
uint8_t USB_STR_1[USB_STR_1_SIZE+USB_STR_DESC_SIZE] =
{  sizeof(USB_STR_1),
    USB_STRING_DESCRIPTOR,
    'F',0,
    'R',0,
    'E',0,
    'E',0,
    'S',0,
    'C',0,
    'A',0,
    'L',0,
    'E',0,
    ' ',0,
    'S',0,
    'E',0,
    'M',0,
    'I',0,
    'C',0,
    'O',0,
    'N',0,
    'D',0,
    'U',0,
    'C',0,
    'T',0,
    'O',0,
    'R',0,
    ' ',0,
    'I',0,
    'N',0,
    'C',0,
    '.',0
};

/*  Product string */
uint8_t USB_STR_2[USB_STR_2_SIZE+USB_STR_DESC_SIZE] =
{  sizeof(USB_STR_2),
    USB_STRING_DESCRIPTOR,
    'M',0,
    'S',0,
    'D',0,
    '_',0,
    'C',0,
    'D',0,
    'C',0,
    ' ',0,
    'D',0,
    'E',0,
    'V',0,
    'I',0,
    'C',0,
    'E',0,
};
/*  Serial number string */
uint8_t USB_STR_3[USB_STR_3_SIZE+USB_STR_DESC_SIZE] =
{  sizeof(USB_STR_3),
    USB_STRING_DESCRIPTOR,
    '0',0,
    '1',0,
    '2',0,
    '3',0,
    '4',0,
    '5',0,
    '6',0,
    '7',0,
    '8',0,
    '9',0,
    'A',0,
    'B',0,
    'C',0,
    'D',0,
    'E',0,
    'F',0
};

/*  Mass Storage Interface String */
uint8_t USB_STR_4[USB_STR_4_SIZE+USB_STR_DESC_SIZE] =
{  sizeof(USB_STR_4),
    USB_STRING_DESCRIPTOR,
    'M',0,
    'a',0,
    's',0,
    's',0,
    ' ',0,
    'S',0,
    't',0,
    'o',0,
    'r',0,
    'a',0,
    'g',0,
    'e',0
};

/*  Mass Storage Interface String */
uint8_t USB_STR_5[USB_STR_5_SIZE+USB_STR_DESC_SIZE] =
{  sizeof(USB_STR_5),
    USB_STRING_DESCRIPTOR,
    'C',0,
    'D',0,
    'C',0,
    ' ',0,
    'I',0,
    'n',0,
    't',0,
    'e',0,
    'r',0,
    'f',0,
    'a',0,
    'c',0,
    'e',0
};

uint8_t USB_STR_n[USB_STR_n_SIZE+USB_STR_DESC_SIZE] =
{  sizeof(USB_STR_n),
    USB_STRING_DESCRIPTOR,
    'B',0,
    'A',0,
    'D',0,
    ' ',0,
    'S',0,
    'T',0,
    'R',0,
    'I',0,
    'N',0,
    'G',0,
    ' ',0,
    'I',0,
    'N',0,
    'D',0,
    'E',0,
    'X',0
};


uint32_t g_std_desc_size[USB_MAX_STD_DESCRIPTORS+1] =
{ 0,
    DEVICE_DESCRIPTOR_SIZE,
    CONFIG_DESC_SIZE,
    0, /* string */
    0, /* Interface */
    0, /* Endpoint */
    #if HIGH_SPEED
    DEVICE_QUALIFIER_DESCRIPTOR_SIZE,
    OTHER_SPEED_CONFIG_DESCRIPTOR_SIZE
    #else
    0, /* Device Qualifier */
    0 /* other speed config */
    #endif
};

uint8_t * g_std_descriptors[USB_MAX_STD_DESCRIPTORS+1] =
{
    NULL,
    (uint8_t *)g_device_descriptor,
    (uint8_t *)g_config_descriptor,
    NULL, /* string */
    NULL, /* Interface */
    NULL, /* Endpoint */
    #if HIGH_SPEED
    g_device_qualifier_descriptor,
    g_other_speed_config_descriptor
    #else
    NULL, /* Device Qualifier */
    NULL /* other speed config*/
    #endif
};

uint8_t g_string_desc_size[USB_MAX_STRING_DESCRIPTORS+1] =
{ sizeof(USB_STR_0),
    sizeof(USB_STR_1),
    sizeof(USB_STR_2),
    sizeof(USB_STR_3),
    sizeof(USB_STR_n)
};

uint8_t * g_string_descriptors[USB_MAX_STRING_DESCRIPTORS+1] =
{
    (uint8_t *)USB_STR_0,
    (uint8_t *)USB_STR_1,
    (uint8_t *)USB_STR_2,
    (uint8_t *)USB_STR_3,
    (uint8_t *)USB_STR_4,
    (uint8_t *)USB_STR_5,
    (uint8_t *)USB_STR_n
};

usb_language_t    usb_lang[USB_MAX_LANGUAGES_SUPPORTED] = 
                                  {
                                      {
                                          (uint16_t)0x0409,
                                          g_string_descriptors,
                                          g_string_desc_size,
                                      },
                                  };                                                                                              
usb_all_languages_t g_languages = { USB_STR_0, sizeof(USB_STR_0),
                                  USB_MAX_LANGUAGES_SUPPORTED,
                                  usb_lang
                                };

uint8_t const g_valid_config_values[USB_MAX_CONFIG_SUPPORTED+1] = {0,1};

/****************************************************************************
* Global Variables
****************************************************************************/
#ifdef _MC9S08JS16_H
#pragma DATA_SEG APP_DATA
#endif

static uint8_t g_alternate_interface[USB_MAX_SUPPORTED_INTERFACES];

/*****************************************************************************
* Local Types - None
*****************************************************************************/

/*****************************************************************************
* Local Functions Prototypes
*****************************************************************************/

/*****************************************************************************
* Local Variables - None
*****************************************************************************/


/*****************************************************************************
* Local Functions - None
*****************************************************************************/

/*****************************************************************************
* Global Functions
*****************************************************************************/
/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Descriptor
 *
 * @brief The function returns the corresponding descriptor
 *
 * @param handle:         handle     
 * @param type:          type of descriptor requested      
 * @param str_num:         string index for string descriptor     
 * @param index:         string descriptor language Id       
 * @param descriptor:     output descriptor pointer
 * @param size:          size of descriptor returned
 *
 * @return USB_OK                               When Success
 *           USBERR_INVALID_REQ_TYPE               when Error
 *****************************************************************************/
uint8_t USB_Desc_Get_Descriptor(
     uint32_t handle, 
     uint8_t type,
     uint8_t str_num, 
     uint16_t index,
     uint8_t * *descriptor,
     uint32_t *size) 
{
     UNUSED_ARGUMENT(handle)

    /* string descriptors are handled separately */
    if (type == USB_STRING_DESCRIPTOR)
    { 
        if(index == 0) 
        {  
            /* return the string and size of all languages */       
            *descriptor = (uint8_t *)g_languages.languages_supported_string;
            *size = g_languages.languages_supported_size;             
        } 
        else 
        {
            uint8_t lang_id=0;
            uint8_t lang_index=USB_MAX_LANGUAGES_SUPPORTED;
            
            for(;lang_id< USB_MAX_LANGUAGES_SUPPORTED;lang_id++) 
            {
                /* check whether we have a string for this language */
                if(index == g_languages.usb_language[lang_id].language_id) 
                {    /* check for max descriptors */
                    if(str_num < USB_MAX_STRING_DESCRIPTORS) 
                    {    /* setup index for the string to be returned */
                        lang_index=str_num;                 
                    }                     
                    break;                      
                }                 
            }

            /* set return val for descriptor and size */
            *descriptor = 
              (uint8_t *)g_languages.usb_language[lang_id].lang_desc[str_num];
            *size = 
                  g_languages.usb_language[lang_id].lang_desc_size[lang_index];
        }         
    }
    else if (type < USB_MAX_STD_DESCRIPTORS+1)
    {
        /* set return val for descriptor and size*/
        *descriptor = (uint8_t *)g_std_descriptors [type];
       
        /* if there is no descriptor then return error */
        if(*descriptor == NULL) 
        {
            return USBERR_INVALID_REQ_TYPE;
        }         
        *size = g_std_desc_size[type];                  
    }
    else /* invalid descriptor */
    {
        return USBERR_INVALID_REQ_TYPE;
    }
    return USB_OK;    
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Interface
 *
 * @brief The function returns the alternate interface
 *
 * @param handle:          handle     
 * @param interface:      interface number       
 * @param alt_interface:  output alternate interface     
 *
 * @return USB_OK                               When Success
 *           USBERR_INVALID_REQ_TYPE               when Error
 *****************************************************************************/
uint8_t USB_Desc_Get_Interface(uint32_t handle, 
                              uint8_t interface, 
                              uint8_t * alt_interface)
{    
    UNUSED_ARGUMENT(handle)
    
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get alternate interface*/
        *alt_interface = g_alternate_interface[interface];
        return USB_OK;    
    }
    
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Interface
 *
 * @brief The function sets the alternate interface
 *
 * @param handle:          handle     
 * @param interface:      interface number       
 * @param alt_interface:  input alternate interface     
 *
 * @return USB_OK                               When Success
 *           USBERR_INVALID_REQ_TYPE               when Error
 *****************************************************************************/
uint8_t USB_Desc_Set_Interface(uint32_t handle, 
                              uint8_t interface, 
                              uint8_t alt_interface)
{
    UNUSED_ARGUMENT(handle)
    
    /* if interface valid */
    if(interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* set alternate interface*/
        g_alternate_interface[interface]=alt_interface;
        return USB_OK;    
    }
    
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Valid_Configation
 *
 * @brief The function checks whether the configuration parameter 
 *          input is valid or not
 *
 * @param handle          handle    
 * @param config_val      configuration value      
 *
 * @return TRUE           When Valid
 *           FALSE          When Error
 *****************************************************************************/
bool USB_Desc_Valid_Configation(uint32_t handle,
                                   uint16_t config_val)
{
    uint8_t loop_index=0;
 
    UNUSED_ARGUMENT(handle)
 
    /* check with only supported val right now */
    while(loop_index < (USB_MAX_CONFIG_SUPPORTED+1)) 
    {
        if(config_val == g_valid_config_values[loop_index]) 
        {           
            return TRUE;
        }
        loop_index++;
    }     
    return FALSE;     
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Remote_Wakeup
 *
 * @brief The function checks whether the remote wakeup is supported or not
 *
 * @param handle:         handle     
 *
 * @return USBCFG_DEV_REMOTE_WAKEUP (TRUE) - if remote wakeup supported
 *****************************************************************************/
bool USB_Desc_Remote_Wakeup(uint32_t handle) 
{
    UNUSED_ARGUMENT(handle)
    return USBCFG_DEV_REMOTE_WAKEUP;    
}            

/**************************************************************************//*!
 *
 * @name  USB_Set_Configuration
 *
 * @brief The function set the configuration value of device
 *         
 *
 * @param handle          handle
 * @param config_val      configuration value
 *
 * @return TRUE           When Valid
 *           FALSE          When Error
 *****************************************************************************/
uint8_t USB_Set_Configuration
(
    cdc_handle_t handle, uint8_t config

)
{
    UNUSED_ARGUMENT (handle)
    uint32_t i;
    for(i = 0; i < usb_composite_info.count; i++)
    {
        switch(usb_composite_info.class_handle[i].type)
        {
            case USB_CLASS_CDC:
                usb_dec_class[i].interfaces = usb_cdc_configuration[config - 1];
                break;
            case USB_CLASS_MSC:
                usb_dec_class[i].interfaces = usb_msd_configuration[config - 1];
                break;
            default:
                break;
        }
    }
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Desc_Get_Entity
 *
 * @brief The function retrieves the entity specified by type.
 *
 * @param handle            handle
 *
 * @return USB_OK  - if success
 *****************************************************************************/
uint8_t USB_Desc_Get_Entity(cdc_handle_t handle,entity_type type, uint32_t * object)
{
    switch(type)
    {
        case USB_CLASS_INFO:
            break;
        case USB_CLASS_INTERFACE_INDEX_INFO:
            *object = 0xff;
            for (int i = 0;i < 2;i++)
            {
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
                if (handle == (uint32_t)g_composite_device->cdc_vcom)
                {
                    *object = (uint32_t)CDC_VCOM_INTERFACE_INDEX;
                    break;
                }
                else if (handle == (uint32_t)g_composite_device->msc_disk.app_handle)
                {
                    *object = (uint32_t)MSC_DISK_INTERFACE_INDEX;
                    break;
                }
#else
                if (handle == (uint32_t)g_composite_device.cdc_vcom)
                {
                    *object = (uint32_t)CDC_VCOM_INTERFACE_INDEX;
                    break;
                }
                else if (handle == (uint32_t)g_composite_device.msc_disk.app_handle)
                {
                    *object = (uint32_t)MSC_DISK_INTERFACE_INDEX;
                    break;
                }
#endif
            }
            break;
        case USB_COMPOSITE_INFO:
            *object = (uint32_t)&usb_composite_info;
            break;
        case USB_MSC_LBA_INFO:
        {
            Disk_USB_App_Class_Callback(USB_MSC_DEVICE_GET_INFO,USB_REQ_VAL_INVALID,NULL,(uint32_t *)&usb_msc_lba_info_struct,NULL);
            *object = (unsigned long)&usb_msc_lba_info_struct;
            break;
        }

        default :
            break;
    }/* End Switch */
    return USB_OK;
}


/**************************************************************************//*!
 *
 * @name  USB_Desc_Set_Speed
 *
 * @brief The function is used to set device speed
 *
 * @param handle:         handle     
 * @param speed:          speed    
 *
 * @return USB_OK                              When Success
 *         USBERR_INVALID_REQ_TYPE             when Error
 *****************************************************************************/
uint8_t USB_Desc_Set_Speed
(
    uint32_t handle,
    uint16_t speed
)
{
    descriptor_union_t ptr1, ptr2;
#if DATA_CLASS_SUPPORT
    uint16_t           bulk_in = 0;
    uint16_t           bulk_out = 0;
#endif
#if CIC_NOTIF_ELEM_SUPPORT
    uint16_t           interrupt_size = 0;
    uint8_t            interrupt_interval = 0;
#endif
    uint16_t           msd_bulk_in = 0;
    uint16_t           msd_bulk_out = 0;
    UNUSED_ARGUMENT (handle);
    
    if (USB_SPEED_HIGH == speed)
    {
#if DATA_CLASS_SUPPORT
        bulk_in = HS_DIC_BULK_IN_ENDP_PACKET_SIZE;
        bulk_out = HS_DIC_BULK_OUT_ENDP_PACKET_SIZE;
#endif
#if CIC_NOTIF_ELEM_SUPPORT
        interrupt_size = HS_CIC_NOTIF_ENDP_PACKET_SIZE;
        interrupt_interval = HS_CIC_NOTIF_ENDP_INTERVAL;
#endif
        msd_bulk_in = HS_BULK_IN_ENDP_PACKET_SIZE;
        msd_bulk_out = HS_BULK_OUT_ENDP_PACKET_SIZE;
    }
    else
    {
#if DATA_CLASS_SUPPORT
        bulk_in = FS_DIC_BULK_IN_ENDP_PACKET_SIZE;
        bulk_out = FS_DIC_BULK_OUT_ENDP_PACKET_SIZE;
#endif
#if CIC_NOTIF_ELEM_SUPPORT
        interrupt_size = FS_CIC_NOTIF_ENDP_PACKET_SIZE;
        interrupt_interval = FS_CIC_NOTIF_ENDP_INTERVAL;
#endif
        msd_bulk_in = FS_BULK_IN_ENDP_PACKET_SIZE;
        msd_bulk_out = FS_BULK_OUT_ENDP_PACKET_SIZE;
    }
    
    ptr1.pntr = g_config_descriptor;
    ptr2.pntr = g_config_descriptor + CONFIG_DESC_SIZE;
    
    while (ptr1.word < ptr2.word)
    {
        if (ptr1.common->bDescriptorType == USB_DESC_TYPE_EP)
        {
            if (CIC_NOTIF_ENDPOINT == (ptr1.ndpt->bEndpointAddress & 0x7F))
            {
#if CIC_NOTIF_ELEM_SUPPORT
                    ptr1.ndpt->wMaxPacketSize[0] = USB_uint_16_low(interrupt_size);
                    ptr1.ndpt->wMaxPacketSize[1] = USB_uint_16_high(interrupt_size);
                    ptr1.ndpt->iInterval = interrupt_interval;
#endif
            }
            else if ((DIC_BULK_IN_ENDPOINT == (ptr1.ndpt->bEndpointAddress & 0x7F)) &&
                     (ptr1.ndpt->bEndpointAddress & 0x80))
            {
#if DATA_CLASS_SUPPORT
                ptr1.ndpt->wMaxPacketSize[0] = USB_uint_16_low(bulk_in);
                ptr1.ndpt->wMaxPacketSize[1] = USB_uint_16_high(bulk_in);
#endif
            }
            else if ((DIC_BULK_OUT_ENDPOINT == (ptr1.ndpt->bEndpointAddress & 0x7F)) &&
                     (!(ptr1.ndpt->bEndpointAddress & 0x80)))
            {
#if DATA_CLASS_SUPPORT
                ptr1.ndpt->wMaxPacketSize[0] = USB_uint_16_low(bulk_out);
                ptr1.ndpt->wMaxPacketSize[1] = USB_uint_16_high(bulk_out);
#endif
            }    
            else if ((BULK_IN_ENDPOINT == (ptr1.ndpt->bEndpointAddress & 0x7F)) &&
                     (ptr1.ndpt->bEndpointAddress & 0x80))
            {
                ptr1.ndpt->wMaxPacketSize[0] = USB_uint_16_low(msd_bulk_in);
                ptr1.ndpt->wMaxPacketSize[1] = USB_uint_16_high(msd_bulk_in);           
            }
            else if ((BULK_OUT_ENDPOINT == (ptr1.ndpt->bEndpointAddress & 0x7F)) &&
                     (!(ptr1.ndpt->bEndpointAddress & 0x80)))
            {
                ptr1.ndpt->wMaxPacketSize[0] = USB_uint_16_low(msd_bulk_out);
                ptr1.ndpt->wMaxPacketSize[1] = USB_uint_16_high(msd_bulk_out);     
            }
        }
        ptr1.word += ptr1.common->bLength;
    }
#if CIC_NOTIF_ELEM_SUPPORT
    cic_ep[0].size = interrupt_size;
#endif
    
#if DATA_CLASS_SUPPORT
    for (int i =0; i < DIC_ENDP_COUNT;i++)
    {
        if (USB_SEND == dic_ep[i].direction)
        {
            dic_ep[i].size = bulk_in;
        }
        else
        {
            dic_ep[i].size = bulk_out;
        }
    }
#endif
#if DATA_CLASS_SUPPORT
    for (int i =0; i < MSC_DESC_ENDPOINT_COUNT;i++)
    {
        if (USB_SEND == msd_ep[i].direction)
        {
            msd_ep[i].size = msd_bulk_in;
        }
        else
        {
            msd_ep[i].size = msd_bulk_out;
        }
    }
#endif    
    return USB_OK;
}

usb_desc_request_notify_struct_t    desc_callback =
{
   USB_Desc_Get_Descriptor,
   USB_Desc_Get_Interface,
   USB_Desc_Set_Interface,
   USB_Set_Configuration,
   USB_Desc_Get_Entity
};
/* EOF */
