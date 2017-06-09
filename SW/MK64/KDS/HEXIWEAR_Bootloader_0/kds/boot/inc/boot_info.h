/**
 * boot info
 */

#include "Eeprom_Boot.h"

#ifndef HG_BOOT_INFO
#define HG_BOOT_INFO

#define FLASH_WRITE_ALIGN ( 1 )
#define FLASH_INVALID_ADDRESS ( 0xFFFFFFFF )
#define YES ( 0x00 )
#define NO  ( 0xFF )

#define FLASH_APP_START_ADDRESS ( (uint32_t)__region_BOOT_ROM_end__ + 1 )
#define BOOT_IMAGE_FLAGS_ADDRESS ( 0xF0000 )
#define BOOT_FIRST_TIME_IMAGE_FLAGS_ADDRESS ( 0xF1000 )
#define BOOT_NEW_IMAGE_FLAG   ( 0x01010101 )
#define BOOT_FIRST_TIME_IMAGE_FLAG ( 0xFFFFFFFF )

/* Init value for the mask used to look through each byte in the bitmap that
indicates which Flash sectors are write protected and should not be updated */

#define gBitMaskInit_c                       0x01
#define gBootData_ImageLength_Offset_c       0x00
#define gBootData_ImageLength_Size_c         0x04
#define gBootData_SectorsBitmap_Offset_c     gEepromAlignAddr_d( gBootData_ImageLength_Offset_c + gBootData_ImageLength_Size_c )

#define gBootData_SectorsBitmap_Size_c       (32)
#define gBootData_Image_Offset_c             gEepromAlignAddr_d( gBootData_SectorsBitmap_Offset_c + gBootData_SectorsBitmap_Size_c )

/*
 * Name: gFlashProtection_c
 * Description: The value for FPROT register. By default the Flash is not Protected
 */
#define FLASH_PROTECTION ( 0xFFFFFFFF ) // by default, Flash is not write protected

/*
 * The product info is located in the last sector of the flash
 */
//#define PRODUCT_INFO_ADDRESS ( KINETIS_FLASH - FLASH_ERASE_PAGE )

/**
 * the start address of the internal storage
 */
//#define INTERNAL_STORAGE_START_ADDRESS_OFFSET (0x44)

#endif
