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
* $FileName: usb_msc_scsi.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains USB Mass Storage SCSI layer api header function
*
*****************************************************************************/

#ifndef _USB_MSC_SCSI_H
#define _USB_MSC_SCSI_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
 #include "usb_msc.h"
/******************************************************************************
 * Constants - None
 *****************************************************************************/


/******************************************************************************
 * Macro's
 *****************************************************************************/
 /* macros for SENSE KEY Codes*/
#define NO_SENSE                     (0x00)
#define RECOVERED_ERROR              (0x01)
#define NOT_READY                    (0x02)
#define MEDIUM_ERROR                 (0x03)
#define HARDWARE_ERROR               (0x04)
#define ILLEGAL_REQUEST              (0x05)
#define UNIT_ATTENTION               (0x06)
#define DATA_PROTECT                 (0x07)
#define BLANK_CHECK                  (0x08)
#define VENDOR_SPECIFIC_ERROR        (0x09)
#define ABORTED_COMMAND              (0x0B)
#define VOLUME_OVERFLOW              (0x0D)
#define MISCOMPARE                   (0x0E)

/* macros for ADDITIONAL SENSE Codes*/
#define INVALID_COMMAND_OPCODE       (0x20)
#define WRITE_FAULT                  (0x03)
#define UNRECOVERED_READ_ERROR       (0x11)
#define UNKNOWN_ERROR                (0xFF)
#define INVALID_FIELD_IN_COMMAND_PKT (0x24)
#define LBA_OUT_OF_RANGE             (0x21)
                                        
/* other macros */
#define REQ_SENSE_VALID_ERROR_CODE      (0x70)
#define REQ_SENSE_ADDITIONAL_SENSE_LEN  (0x0A)
#define PREVENT_ALLOW_REMOVAL_MASK      (0x01)
#define LOAD_EJECT_START_MASK           (0x03)
#define FORMATTED_MEDIA                 (0x02) 
#define UNFORMATTED_MEDIA               (0x01)
#define NO_CARTRIDGE_IN_DRIVE           (0x03)
                                        
#define INQUIRY_ALLOCATION_LENGTH       (0x24) 
#define REQ_SENSE_DATA_LENGTH           (18) 
#define READ_CAPACITY_DATA_LENGTH       (0x08)
#define READ_CAPACITY16_DATA_LENGTH     (0x0C)
                                        
#define PERIPHERAL_QUALIFIER            (0)
#define PERIPHERAL_QUALIFIER_SHIFT      (5)
#define SPC_VERSION                     (4)/*SPC3 is 5; SPC2 is 4*/
#define PERIPHERAL_DEVICE_TYPE          (0x00)
#define REMOVABLE_MEDIUM_BIT            (1) 
#define REMOVABLE_MEDIUM_BIT_SHIFT      (7)
#define ADDITIONAL_LENGTH               (0x20)
#define SUPPORT_DISK_LOCKING_MECHANISM  (0) /*1: TRUE; 0:FALSE*/

#define BULK_OUT_ENDPOINT            msc_obj_ptr->bulk_out_endpoint

/* Forward Declaration */
/******************************************************************************
 * Types
 *****************************************************************************/
/**** COMMAND STRUCTURES ******/ 
typedef struct _inquiry_command
{
   uint8_t   opcode; /* operation code : 0x12H*/
   uint8_t   lun_evpd;    /* Logical Unit Number: bits 7-5, EVPD: bit 0 */
   uint8_t   page_code; 
   uint8_t   reserved1;  /* 1 bytes are reserved */
   uint8_t   alloc_length; /* allocation length : 0x24H*/
   uint8_t   reserved2[7];/* reserved and pad bits */   
}inquiry_command_struct_t, * PTR_INQUIRY_COMMAND_STRUCT;

typedef struct _request_sense_command
{
   uint8_t   opcode; /* operation code : 0x03H*/
   uint8_t   lun;    /* Logical Unit Number: bits 7-5, rest reserved */
   uint8_t   reserved1[2];  /* 2 bytes are reserved */
   uint8_t   alloc_length; /* specs say it to be 252 bytes, 
                             but windows request only 18 bytes*/
   uint8_t   reserved2[7];/* reserved and pad bits */   
}request_sense_command_struct_t;

typedef struct _read_format_capacity_command 
{
    uint8_t opcode; /* operation code : 0x23H*/
    uint8_t lun; /* LUN : bits 7-5*/
    uint8_t reserved1[5]; 
    uint16_t alloc_len; /*Allocation length (MSB) :byte 7; 
                         Allocation length (LSB) :byte 8*/
    uint8_t reserved2[3];    
}read_format_capacity_command_struct_t;

typedef struct _read_capacity_command 
{
    uint8_t opcode; /* operation code : 0x25H*/
    uint8_t lun_adr; /* LUN : bits 7-5, RelAdr : bit 0*/
    uint32_t lba; /* Logical Block Address : 4 bytes */
    uint8_t reserved1[2]; /* 2 bytes are reserved */
    uint8_t pmi; /* always set to zero for UFI devices */
    uint8_t reserved2[3];/* 3 bytes are reserved */
} read_capacity_command_struct_t;

typedef struct _read_write_10_command 
{
    uint8_t opcode; /* operation code : 0x28H(read), 0x2A(write)*/
    uint8_t lun_dpo_fua_adr;/*LUN:bits7-5, DPO:bit4, FUA:bit3, RelAdr:bit0*/ 
    uint32_t lba;
    uint8_t reserved1;
    uint8_t transfer_length_msb;
    uint8_t transfer_length_lsb;
    uint8_t reserved2[3];
}read_write_10_command_struct_t;


/******* COMMAND RESPONSE DATA STRUCTURES */
typedef struct _inquiry_data  /* 36 bytes structure */
{
    uint8_t peripheral;/*Bits 7..5: PERIPHERAL QUALIFIER (000 = a device is 
                        connected to this logical unit) 
                        Bits 4..0: PERIPHERAL DEVICE TYPE (PDT)  */
    uint8_t rmb;/*Bit 7: RMB (0 = non-removable media; 1 = removable media) 
                 Bits 6..0: reserved    */
    uint8_t version;/*VERSION of SPC standard (5 = SPC-3; 4 = SPC-2) */     
    uint8_t response_data_format;/*Bits 7..6: obsolete 
                                  Bit 5: NORMACA (normal ACA bit support) 
                                  Bit 4: HISUP(hierarchical addressing support)
                                  Bits 3..0: response data format (must = 2) */
    uint8_t additional_length;/*the number of additional bytes in the response).
                               Equal to (response length - 4). Set to 20h if 
                               returning 36 (24h) bytes. */
    uint8_t sccs;/*Bit 7: SCCS (0 = no embedded storage array controller 
                                   component present) 
                  Bit 6: ACC (0 = no access controls coordinator present) 
                  Bits 5..4: TPGS (0 = no support or vendor-specific support 
                                       for asymmetric logical unit access) 
                  Bit 3: 3PC ((0 = no support for third-party copy commands) 
                  Bits 2..1: reserved 
                  Bit 0: PROTECT (0 = no support for protection information)*/
    uint8_t bque;/*Bit 7: BQUE (0 = no support for basic task management) 
                  Bit 6: ENCSERV (0=no support for embedded enclosure services)
                  Bit 5: VS (vendor specific) 
                  Bit 4: MULTIP (0 = device has a single port) 
                  Bit 3: MCHNGR (0 = no support for media changer) 
                  Bits 2..1: obsolete 
                  Bit 0: ADDR16 (not used with USB interface) */
    uint8_t wbus;/*Bit 7..6: obsolete 
                  Bit 5: WBUS16 (not used with USB interface) 
                  Bit 4: SYNC (not used with USB interface) 
                  Bit 3: LINKED (0 = no support for linked commands) 
                  Bit 2: obsolete 
                  Bit 1: CMDQUE (0 = no support for full task management) 
                  Bit 0: VS (vendor specific)*/
    uint8_t vendor_info[8]; /*T10 VENDOR IDENTIFICATION, MSB first */
    uint8_t product_id[16]; /*PRODUCT IDENTIFICATION, MSB first*/
    uint8_t product_rev_level[4];/*PRODUCT REVISION LEVEL, MSB first*/
}inquiry_data_struct_t;

typedef struct _request_sense_data /* 18 bytes structure */
{
    uint8_t valid_error_code;/*bit 7: VALID. Set to 1 if the INFORMATION field
                                     contains valid information. 
                              bits 6..0: RESPONSE CODE. Set to 70h for info on
                                         current errors. Set to 71h for info on
                                         deferred errors (used with commands 
                                         that use caching).*/
    uint8_t reserved1; /* obsolete */
    uint8_t sense_key;/*Bit7: FILEMARK. Used by streaming devices. 
                       Bit6: EOM. End of medium. Used by streaming devices. 
                       Bit5: ILI: Incorrect length indicator. Used with READ 
                                  LONG, WRITE LONG, and stream READ commands. 
                       Bit4: Reserved 
                       Bits3:0: SENSE KEY. Contains info describing the error*/
    uint8_t information[4];/*Device-specific or command-specific info*/
    uint8_t add_sense_len;/*number of additional sense bytes that follow this 
                           field. Maximum is 244*/
    uint8_t command_specific_info[4];
    uint8_t add_sense_code;/*Provides additional information about the 
                            error. Set to zero if unused */
    uint8_t add_sense_code_qual;/*Provides additional info related to additional
                                  sense code. Set to zero if unused */
    uint8_t field_rep_uint_code;/*Identifies a failed component. Set to zero if 
                                 there is no component to identify */
    uint8_t sense_key_specific[3];/*If byte 15, bit7(SKSV) equals 1,remainder of
                                   the field contains SENSE KEY SPECIFIC info*/
}request_sense_data_struct_t;

typedef struct _read_capacity_data  /* 8 bytes structure */
{
   uint32_t last_logical_block_address;/*last LBA number*/
   uint32_t block_size; /* in bytes */
}read_capacity_data_struct_t; 

typedef struct _read_capacity16_data  /* 8 bytes structure */
{
   uint32_t last_logical_block_address0;/*last LBA number*/
   uint32_t last_logical_block_address1;/*last LBA number*/
   uint32_t block_size; /* in bytes */
}read_capacity16_data_struct_t; 

typedef struct _capacity_list_header
{
    uint8_t reserved1[3];
    uint8_t capacity_list_len;/*specifies the length in bytes of the Capacity 
                               Descriptor that follow. Each capacity descriptor
                               is eight bytes in length, making the capacity 
                               list length equal to eight times the number of 
                               descriptors */
}capacity_list_header_struct_t;

typedef struct _curr_max_capacity_desc
{
    uint32_t num_blocks; /*byte 0-3 = total number of addressable blocks for the 
                          descriptor's media type */
    uint32_t desc_code_and_block_len;
    /*byte 4: specifies the type of descriptor returned to host :
    01b : unformattable media - max formattable capacity for this cartridge
    10b : formatted media - current media capacity
    11b : no cartridge in drive - max formattable capacity for any cartridge*/
    /* byte 5-7 : specifies the length in bytes of each logical block 
       Note: byte 5 holds most significant byteS*/  
}curr_max_capacity_desc_struct_t;

typedef struct _formattable_cap_desc
{
    uint32_t num_blocks;/*byte 0-3 : fields indicates the number of addressable 
    blocks for the given capacity descriptor*/
    uint32_t block_len;/*byte 4 : reserved; 
    byte5-7: specifies the length in bytes of each logical block for the given
    capacity descriptor */
}formattable_cap_desc_t;

typedef struct _mode_parameter_header
{
    uint16_t mode_data_len;/*for MODE SELECT command, the mode data length field
                            should always be set to zero.
                            for MODE SENSE command, the mode data length field 
                            specifies the length in bytes of the following data
                            that is available to be transfered(not including
                            itself)*/
    uint8_t medium_type_code;/*specifies the inserted medium type. The value in 
                              this field are vendor specific. 
                              default value should be 0x00*/
    uint8_t wp_dpofua;/* bit7:wp:write protect(ignored for mode select command)
                        bit4:dpofua; rest of the bits are reserved */
    uint8_t reserved1[4];                        
}mode_parameter_header_struct_t;

typedef struct _msc_scsi_variable_struct
{
    /* disk space reserved . This Disk Space is reserved by the App.*/
    uint32_t total_logical_add_block;
    uint32_t length_of_each_lab;
    uint32_t implementing_disk_drive;
    /* structure to store request sense data for every 
       command received by device */
    request_sense_data_struct_t request_sense;
     /* flag to track if the msd device is formatted or not */
    msc_thirteen_case_struct_t thirteen_case;
    usb_class_specific_callback_struct_t scsi_callback;
    read_capacity_data_struct_t read_capacity;
    read_capacity16_data_struct_t read_capacity16;
    uint8_t format_capacity_response_data[sizeof(capacity_list_header_struct_t) + sizeof(curr_max_capacity_desc_struct_t) + sizeof(formattable_cap_desc_t) * 3];
    bool formatted_disk;
    uint8_t is_used;
}msc_scsi_struct_t; 

#endif

/* EOF */
