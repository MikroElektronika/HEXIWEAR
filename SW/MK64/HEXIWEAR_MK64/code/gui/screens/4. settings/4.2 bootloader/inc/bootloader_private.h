/**
 * \file bootloader_private.h
 * \version 1.00
 * \brief this file contains bootloader related constants, prototypes and objects
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

#include <stdint.h>
#include "gui_driver.h"

extern guiLabel_t
  bootloader_labelLoad;

extern guiLabel_t
	bootloader_labelTitle;

extern const uint8_t
  otap_coverScreen_bmp[ OLED_GRAM_SIZE+6 ],
  otap_mainScreen_bmp[ OLED_GRAM_SIZE+6 ],

  otap_select_kw40_bmp[4806],
  otap_select_mk64_bmp[4806],

  bootloader_failure_bmp[18438],
  bootloader_success_bmp[18438],

  bootloader_loadWhite_bmp[6278],
  bootloader_loadBlue_bmp[6278];

#define LOAD_IMG_NUM ( 2 )

extern guiImage_t
  bootloader_selectMK64,
  bootloader_selectKW40,

  bootloader_loadImg_white,
  bootloader_loadImg_blue,

  bootloader_success,
  bootloader_failure;

#define BOOT_IMAGE_FLAGS_ADDRESS ( 0xF0000 )
#define FLASH_WRITE_ALIGN ( 1 )

typedef struct __attribute__ ((__packed__))
{
  uint8_t  newBootImageAvailable[ FLASH_WRITE_ALIGN ];
  uint8_t  bootProcessCompleted[ FLASH_WRITE_ALIGN ];
  uint8_t  bootVersion[2];
  uint8_t  padding[4];

} bootInfo_t;
