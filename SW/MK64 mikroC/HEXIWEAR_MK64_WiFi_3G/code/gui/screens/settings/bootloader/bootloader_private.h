// File: bootloader_private.h

// Declarations of resources used in the bootloader gui module.

#ifndef _bootloader_private_h_
#define _bootloader_private_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define LOAD_IMG_NUM ( 2 )

#define BOOT_IMAGE_FLAGS_ADDRESS ( 0xF0000 )
#define FLASH_WRITE_ALIGN ( 1 )

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////
 
typedef struct
{
    uint8_t  newBootImageAvailable[ FLASH_WRITE_ALIGN ];
    uint8_t  bootProcessCompleted[ FLASH_WRITE_ALIGN ];
    uint8_t  bootVersion[2];
    uint8_t  padding[4];

} bootInfo_t;

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

extern guiLabel_t bootloader_labelLoad;

extern guiLabel_t bootloader_labelTitle;

extern const uint8_t otap_coverScreen_bmp[ OLED_GRAM_SIZE + 6 ];
extern const uint8_t otap_mainScreen_bmp[ OLED_GRAM_SIZE + 6 ];

extern const uint8_t otap_select_kw40_bmp[4806];
extern const uint8_t otap_select_mk64_bmp[4806];

extern const uint8_t bootloader_failure_bmp[18438];
extern const uint8_t bootloader_success_bmp[18438];

extern const uint8_t bootloader_loadWhite_bmp[6278];
extern const uint8_t bootloader_loadBlue_bmp[6278];

extern guiImage_t bootloader_selectMK64;
extern guiImage_t bootloader_selectKW40;

extern guiImage_t bootloader_loadImg_white;
extern guiImage_t bootloader_loadImg_blue;

extern guiImage_t bootloader_success;
extern guiImage_t bootloader_failure;

#endif