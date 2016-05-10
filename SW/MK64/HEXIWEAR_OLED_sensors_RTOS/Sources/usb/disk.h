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
 * $FileName: disk.h$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief The file contains Macro's and functions needed by the disk 
 *        application
 *
 *****************************************************************************/

#ifndef _DISK_H
#define _DISK_H  1

#include "usb_descriptor.h"
#include "FLASH_types.h"
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define SPI_FLASH_APP         (1)
#define RAM_DISK_APP         (0)
#define SD_CARD_APP             (0)

#if RAM_DISK_APP
/* Length of Each Logical Address Block */
#define LENGTH_OF_EACH_LAB              (512)    
/* total number of logical blocks present */
#define TOTAL_LOGICAL_ADDRESS_BLOCKS    (32)
/* Net Disk Size */
#define DISK_SIZE                       (LENGTH_OF_EACH_LAB * TOTAL_LOGICAL_ADDRESS_BLOCKS)
#endif

#if SPI_FLASH_APP
#define SPI_FLASH_SECTOR_SIZE (64*1024)
#define SPI_FLASH_NUMBER_OF_SECTORS (16)
#define SPI_FLASH_ERASE_SECTOR_MASK (0xFFFF0000)
#define SPI_FLASH_LAST_SECTOR_ADDR ((SPI_FLASH_SECTOR_SIZE*(SPI_FLASH_NUMBER_OF_SECTORS-1)) & SPI_FLASH_ERASE_SECTOR_MASK)
/* Length of Each Logical Address Block */
#define LENGTH_OF_EACH_LAB              (512)
/* total number of logical blocks present */
#define TOTAL_LOGICAL_ADDRESS_BLOCKS    ((SPI_FLASH_SECTOR_SIZE*(SPI_FLASH_NUMBER_OF_SECTORS-1))/LENGTH_OF_EACH_LAB)
/* Net Disk Size */
#define SPI_FLASH_DISK_SIZE (LENGTH_OF_EACH_LAB * TOTAL_LOGICAL_ADDRESS_BLOCKS)
#endif

#define LOGICAL_UNIT_SUPPORTED          (1)

#define SUPPORT_DISK_LOCKING_MECHANISM  (0) /*1: TRUE; 0:FALSE*/
/* If Implementing Disk Drive then configure the macro below as TRUE,
 otherwise keep it False(say for Hard Disk)*/
#define IMPLEMENTING_DISK_DRIVE         (0) /*1: TRUE; 0:FALSE*/

//#define MSD_RECV_BUFFER_SIZE            (BULK_OUT_ENDP_PACKET_SIZE)
//#define MSD_SEND_BUFFER_SIZE            (BULK_IN_ENDP_PACKET_SIZE)

#define MSD_RECV_BUFFER_SIZE            (512)
#define MSD_SEND_BUFFER_SIZE            (512)
/******************************************************************************
 * Types
 *****************************************************************************/
typedef struct _disk_variable_struct
{
    msd_handle_t app_handle;
    uint32_t start_app;
    uint16_t speed;
    #if RAM_DISK_APP
    /* disk space reserved */
    uint8_t storage_disk[DISK_SIZE];
    #endif  
    uint8_t disk_lock;
} disk_struct_t;

/*****************************************************************************
 * Global variables
 *****************************************************************************/
extern uint8_t ErasedBlocks512[TOTAL_LOGICAL_ADDRESS_BLOCKS];


/*****************************************************************************
 * Global Functions
 *****************************************************************************/
void msc_disk_preinit(void);
void msc_disk_init(void *param);
uint8_t Disk_USB_App_Class_Callback
(uint8_t event_type,
    uint16_t value,
    uint8_t ** data,
    uint32_t* size,
    void* arg
) ;
void Disk_USB_App_Device_Callback(uint8_t event_type, void* val, void* arg);
void msc_disk_task(void);

#if SPI_FLASH_APP
statusFLASH_t Flash_Read_Block(lba_app_struct_t* ptr);
statusFLASH_t Flash_Write_Block(lba_app_struct_t* ptr);
#endif

#endif

/* EOF */
