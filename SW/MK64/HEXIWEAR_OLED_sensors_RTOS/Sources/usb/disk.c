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
 * $FileName: disk.c$
 * $Version : 
 * $Date    : 
 *
 * Comments:
 *
 * @brief  RAM Disk has been emulated via this Mass Storage Demo
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
#include <fio.h>
#else
#endif

#include "disk.h"
#include "usb_class_msc.h"
#if SD_CARD_APP
#include "SD_esdhc_kinetis.h"
#endif
#if SPI_FLASH_APP
#include "FLASH_driver.h"
#include "FLASH_defs.h"
#include "vfs.h"

#endif

/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/
/* Add all the variables needed for disk.c to this structure */
disk_struct_t* g_msc_disk_ptr;

#if SD_CARD_APP
#define USE_SDHC_PROTOCOL    (1)
#define USE_SPI_PROTOCOL     (0)
#endif

#if SPI_FLASH_APP
uint32_t msc_bulk_out_buff[MSD_RECV_BUFFER_SIZE >> 2];
uint32_t msc_bulk_in_buff[MSD_SEND_BUFFER_SIZE >> 2];
#endif
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
void Disk_USB_App_Device_Callback(uint8_t event_type, void* val, void* arg);
uint8_t Disk_USB_App_Class_Callback(uint8_t event_type, uint16_t value,
		uint8_t ** data, uint32_t* size, void* arg);
void Disk_App(void);
/*****************************************************************************
 * Local Variables 
 *****************************************************************************/
#if SD_CARD_APP

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM)
uint32_t g_msc_bulk_out_buff_temp[MSD_RECV_BUFFER_SIZE >> 2];
uint32_t g_msc_bulk_in_buff_temp[MSD_SEND_BUFFER_SIZE >> 2];
#endif
uint8_t *g_msc_bulk_out_buff;
uint8_t *g_msc_bulk_in_buff;
#endif
#if SPI_FLASH_APP
uint8_t *g_msc_bulk_out_buff = &msc_bulk_out_buff[0];
uint8_t *g_msc_bulk_in_buff = &msc_bulk_in_buff[0];
#endif

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

/******************************************************************************
 * 
 *    @name       Disk_App
 *    
 *    @brief      
 *                  
 *    @param      None
 * 
 *    @return     None
 *    
 *****************************************************************************/
void Disk_App(void) {
	/* User Code */
	return;
}

/******************************************************************************
 * 
 *    @name        Disk_USB_App_Device_Callback
 *    
 *    @brief       This function handles the callback  
 *                  
 *    @param       pointer : 
 *    @param       event_type : value of the event
 *    @param       val : gives the configuration value 
 * 
 *    @return      None
 *
 *****************************************************************************/
void Disk_USB_App_Device_Callback(uint8_t event_type, void* val, void* arg) {
	UNUSED_ARGUMENT(arg)
	UNUSED_ARGUMENT(val)
	if (event_type == USB_DEV_EVENT_BUS_RESET) {
		g_msc_disk_ptr->start_app = FALSE;
		if (USB_OK
				== USB_Class_MSC_Get_Speed(g_msc_disk_ptr->app_handle,
						&g_msc_disk_ptr->speed)) {
			USB_Desc_Set_Speed(g_msc_disk_ptr->app_handle,
					g_msc_disk_ptr->speed);
		}
	} else if (event_type == USB_DEV_EVENT_ENUM_COMPLETE) {
		g_msc_disk_ptr->start_app = TRUE;
	} else if (event_type == USB_DEV_EVENT_ERROR) {
		/* add user code for error handling */
	} else if (event_type == USB_MSC_DEVICE_GET_SEND_BUFF_INFO) {
		if (NULL != val) {
#if SD_CARD_APP
			*((uint32_t *)val) = (uint32_t)MSD_SEND_BUFFER_SIZE;
#elif RAM_DISK_APP
			*((uint32_t *)val) = (uint32_t)DISK_SIZE;
#elif SPI_FLASH_APP
			*((uint32_t *) val) = (uint32_t) MSD_SEND_BUFFER_SIZE;
#endif

		}
	} else if (event_type == USB_MSC_DEVICE_GET_RECV_BUFF_INFO) {
		if (NULL != val) {
#if SD_CARD_APP
			*((uint32_t *)val) = (uint32_t)MSD_RECV_BUFFER_SIZE;
#elif RAM_DISK_APP
			*((uint32_t *)val) = (uint32_t)DISK_SIZE;
#elif SPI_FLASH_APP
			*((uint32_t *) val) = (uint32_t) MSD_RECV_BUFFER_SIZE;
#endif
		}
	}

	return;
}

/******************************************************************************
 * 
 *    @name        Disk_USB_App_Class_Callback
 *    
 *    @brief       This function handles the callback  
 *                  
 *    @param       pointer : 
 *    @param       event_type : value of the event
 *    @param       val : gives the configuration value 
 * 
 *    @return      None
 *
 *****************************************************************************/
uint8_t Disk_USB_App_Class_Callback(uint8_t event_type, uint16_t value,
		uint8_t ** data, uint32_t* size, void* arg) {
	lba_app_struct_t* lba_data_ptr;
	uint8_t * prevent_removal_ptr;
	//uint8_t * load_eject_start_ptr = NULL;
	device_lba_info_struct_t* device_lba_info_ptr;
	uint8_t error = USB_OK;

	//UNUSED_ARGUMENT (arg)

	switch (event_type) {
	case USB_DEV_EVENT_DATA_RECEIVED:
		/* Add User defined code -- if required*/
		lba_data_ptr = (lba_app_struct_t*) size;

#if RAM_DISK_APP
#elif SD_CARD_APP
		SD_Write_Block(lba_data_ptr);
#elif SPI_FLASH_APP
		Flash_Write_Block(lba_data_ptr);
#endif
		break;
	case USB_DEV_EVENT_SEND_COMPLETE:
		/* Add User defined code -- if required*/
		lba_data_ptr = (lba_app_struct_t*) size;
		/* read data from mass storage device to driver buffer */
#if RAM_DISK_APP
		if(data != NULL)
		{
			*data = g_msc_disk_ptr->storage_disk + lba_data_ptr->offset;
		}
#elif SD_CARD_APP
#elif SPI_FLASH_APP
#endif
		break;
	case USB_MSC_START_STOP_EJECT_MEDIA:
		/*    Code to be added by user for starting, stopping or
		 ejecting the disk drive. e.g. starting/stopping the motor in
		 case of CD/DVD*/
		break;
	case USB_MSC_DEVICE_READ_REQUEST:
		/* copy data from storage device before sending it on USB Bus
		 (Called before calling send_data on BULK IN endpoints)*/
		lba_data_ptr = (lba_app_struct_t*) size;
		/* read data from mass storage device to driver buffer */
#if RAM_DISK_APP
		if(data != NULL)
		{
			*data = g_msc_disk_ptr->storage_disk + lba_data_ptr->offset;
		}
#elif SD_CARD_APP
		if(data != NULL)
		{
			*data = g_msc_bulk_in_buff;
		}
		lba_data_ptr->buff_ptr = g_msc_bulk_in_buff;
		SD_Read_Block(lba_data_ptr);
#elif SPI_FLASH_APP
		if (data != NULL) {
			*data = g_msc_bulk_in_buff;
		}
		lba_data_ptr->buff_ptr = g_msc_bulk_in_buff;
		Flash_Read_Block(lba_data_ptr);
#endif         
		break;
	case USB_MSC_DEVICE_WRITE_REQUEST:
		/* copy data from USb buffer to Storage device
		 (Called before after recv_data on BULK OUT endpoints)*/
		lba_data_ptr = (lba_app_struct_t*) size;
		/* read data from driver buffer to mass storage device */
#if RAM_DISK_APP
		if(data != NULL)
		{
			*data = g_msc_disk_ptr->storage_disk + lba_data_ptr->offset;
		}
#elif SD_CARD_APP
		if(data != NULL)
		{
			*data = g_msc_bulk_out_buff;
		}
#elif SPI_FLASH_APP
		if (data != NULL) {
			*data = g_msc_bulk_out_buff;
		}
#endif                          
		break;
	case USB_MSC_DEVICE_FORMAT_COMPLETE:
		break;
	case USB_MSC_DEVICE_REMOVAL_REQUEST:
		prevent_removal_ptr = (uint8_t *) size;
		if (SUPPORT_DISK_LOCKING_MECHANISM) {
			g_msc_disk_ptr->disk_lock = *prevent_removal_ptr;
		} else if ((!SUPPORT_DISK_LOCKING_MECHANISM)
				&& (!(*prevent_removal_ptr))) {
			/*there is no support for disk locking and removal of medium is enabled*/
			/* code to be added here for this condition, if required */
		}
		break;
	case USB_MSC_DEVICE_GET_INFO:
		device_lba_info_ptr = (device_lba_info_struct_t*) size;
#if RAM_DISK_APP
		device_lba_info_ptr->total_lba_device_supports = TOTAL_LOGICAL_ADDRESS_BLOCKS;
		device_lba_info_ptr->length_of_each_lab_of_device = LENGTH_OF_EACH_LAB;
#elif SD_CARD_APP
		SD_Card_Info(&device_lba_info_ptr->total_lba_device_supports,
				&device_lba_info_ptr->length_of_each_lab_of_device);
#elif SPI_FLASH_APP
		device_lba_info_ptr->total_lba_device_supports =
		TOTAL_LOGICAL_ADDRESS_BLOCKS;
		device_lba_info_ptr->length_of_each_lab_of_device = LENGTH_OF_EACH_LAB;
#endif
		device_lba_info_ptr->num_lun_supported = LOGICAL_UNIT_SUPPORTED;
		break;
	default:
		break;
	}

	return error;
}

/******************************************************************************
 *  
 *   @name        msc_disk_preinit
 * 
 *   @brief       This function pre-initializes the App.
 * 
 *   @param       None
 * 
 *   @return      None
 **                
 *****************************************************************************/

void msc_disk_preinit(void) {
	statusFLASH_t status;
#if SD_CARD_APP

#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_BM)
	g_msc_bulk_in_buff = (uint8_t*)g_msc_bulk_in_buff_temp;
	g_msc_bulk_out_buff = (uint8_t*)g_msc_bulk_out_buff_temp;
#elif (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
	g_msc_bulk_in_buff = (uint8_t*)OS_Mem_alloc_uncached_align(MSD_SEND_BUFFER_SIZE, 32);
	g_msc_bulk_out_buff = (uint8_t*)OS_Mem_alloc_uncached_align(MSD_SEND_BUFFER_SIZE, 32);
#endif

#endif

#if SD_CARD_APP
#if (defined _MK_xxx_H_)
#if USE_SDHC_PROTOCOL
	GPIOE_PDIR |= 1 << 28;
	PORTE_PCR28 |= PORT_PCR_MUX(1);
	GPIOE_PDDR &= ~((uint32_t)1 << 28);
	PORTE_PCR28 |= PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
#endif // USE_SDHC_PROTOCOL	_SD_DE; /* Card detection */
#endif
#if (defined _MK_xxx_H_) ||  defined(MCU_mcf51jf128)
	while(SD_DE&kSD_Desert)
	{
	} /* SD Card inserted */
#else
	while(SD_DE == kSD_Desert)
	{
	} /* SD Card inserted */
#endif
	if(!SD_Init()) return; /* Initialize SD_CARD and SPI Interface */
#endif

#if SPI_FLASH_APP
//	memset(&ErasedBlocks512[0], 0, TOTAL_LOGICAL_ADDRESS_BLOCKS);
//	status = FLASH_Init(&flashModule, &flashSettings);
//	status |= FLASH_EraseBulk();
//    if (status != STATUS_FLASH_SUCCESS)
//    		while(1);
	usbd_msc_init();
#endif

}

/******************************************************************************
 *  
 *   @name        msc_disk_init
 * 
 *   @brief       This function initializes the App.
 * 
 *   @param       None
 * 
 *   @return      None
 **                
 *****************************************************************************/

void msc_disk_init(void *param) {
	g_msc_disk_ptr = (disk_struct_t*) param;
	g_msc_disk_ptr->speed = USB_SPEED_FULL;
}
/******************************************************************************
 *  
 *   @name        Disk_TestApp_Task
 * 
 *   @brief       This function runs the App task.
 * 
 *   @param       None
 * 
 *   @return      None
 **                
 *****************************************************************************/

void msc_disk_task(void) {
	/* call the periodic task function */
	USB_MSC_Periodic_Task();

	/*check whether enumeration is complete or not */
	if (g_msc_disk_ptr->start_app == (uint32_t) TRUE) {
		Disk_App();
	}
}

#if SPI_FLASH_APP

uint8_t ErasedBlocks512[TOTAL_LOGICAL_ADDRESS_BLOCKS];

int32_t IsBuffAll0xFF(uint8_t* buff, uint32_t size) {
	uint8_t result = 0xFF;

	for (int i = 0; i < size; i++) {
		result &= *buff;
		buff++;
		if (result != 0xFF)
			return 0;
	}

	return 1;
}

statusFLASH_t Flash_Read_Block512(uint32_t addr, uint8_t* buff) {
	statusFLASH_t status;

	status = STATUS_FLASH_SUCCESS;

	for (int i = 0; i < 512 / 256; i++) {
		status |= FLASH_ReadData(addr, buff, 256);
		buff += 256;
		addr += 256;
	}
	return status;
}

statusFLASH_t Flash_Write_Block512(uint32_t addr, uint8_t* buff) {
	statusFLASH_t status;

	status = STATUS_FLASH_SUCCESS;

	for (int i = 0; i < 512 / 256; i++) {
		if (!IsBuffAll0xFF(buff, 256))
			status |= FLASH_WriteData(addr, buff, 256);
		buff += 256;
		addr += 256;
	}
	return status;
}

statusFLASH_t Flash_Copy_Sector(uint32_t srcAddr, uint32_t destAddr,
		uint32_t block512Addr, uint8_t *block512Buff) {

	statusFLASH_t status;
	uint32_t buffer[512];
	uint8_t *ptr;

	status = STATUS_FLASH_SUCCESS;

	ptr = &buffer[0];

	for (int i = 0; i < (SPI_FLASH_SECTOR_SIZE / 512); i++) {
		if ((block512Buff != NULL) && (srcAddr == block512Addr))
			status |= Flash_Write_Block512(destAddr, block512Buff);
		else {
			status |= Flash_Read_Block512(srcAddr, ptr);
			status |= Flash_Write_Block512(destAddr, ptr);
		}

		if(block512Buff == NULL){
			ErasedBlocks512[destAddr/512] = 0;
		}

		srcAddr += 512;
		destAddr += 512;
	}
	return status;
}

statusFLASH_t Flash_Read_Block(lba_app_struct_t* lbaPtr) {
	statusFLASH_t status;

	status = 0;

//	status = Flash_Read_Block512(lbaPtr->offset, lbaPtr->buff_ptr);
	usbd_msc_read_sect (lbaPtr->offset / 512, lbaPtr->buff_ptr, 1);

	return status;
}

statusFLASH_t Flash_Write_Block(lba_app_struct_t* lbaPtr) {
	statusFLASH_t status;

	status = STATUS_FLASH_SUCCESS;

//	if (ErasedBlocks512[lbaPtr->offset / 512]) {
//		status |= Flash_Write_Block512(lbaPtr->offset, lbaPtr->buff_ptr);
//		ErasedBlocks512[lbaPtr->offset / 512] = 0;
//	} else {
//
//		status |= FLASH_EraseSector(SPI_FLASH_LAST_SECTOR_ADDR);
//
//		status |= Flash_Copy_Sector(
//				(lbaPtr->offset & SPI_FLASH_ERASE_SECTOR_MASK),
//				SPI_FLASH_LAST_SECTOR_ADDR, lbaPtr->offset, lbaPtr->buff_ptr);
//
//		status |= FLASH_EraseSector(
//				lbaPtr->offset & SPI_FLASH_ERASE_SECTOR_MASK);
//
//		for (int i = 0; i < 128; i++) {
//			ErasedBlocks512[(lbaPtr->offset & SPI_FLASH_ERASE_SECTOR_MASK) / 512 + i] = 1;
//		}
//
//		status |= Flash_Copy_Sector(SPI_FLASH_LAST_SECTOR_ADDR,
//				(lbaPtr->offset & SPI_FLASH_ERASE_SECTOR_MASK), 0, NULL);
//
//	}
	usbd_msc_write_sect(lbaPtr->offset / 512, lbaPtr->buff_ptr, 1);

	return status;
}

#endif

/* EOF */
