/**
 * \file bootloader.h
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

#include "fsl_os_abstraction.h"
#include "gui_driver.h"
#include "HEXIWEAR_driver.h"

#define BOOTLOADER_QUEUE_SIZE ( 1 )
#define BOOTLOADER_STACK_SIZE ( 0x400 )
#define BOOTLOADER_PRIO       ( HEXIWEAR_GUI_PRIO )

void bootloader_Init         ( task_param_t param );
void bootloader_CreateTasks  ( task_param_t param );
void bootloader_DestroyTasks ( task_param_t param );

typedef enum
{
  BOOTLOADER_STATUS_SUCCESS,
  BOOTLOADER_STATUS_ERROR

} bootloader_status_t;

/**
 * put the packet into the designated bootloader's queue
 * @param  packet data to put
 * @return        status flag
 */
bootloader_status_t boootloader_QueueMsgPut( hostInterface_packet_t* packet );

extern guiScreen_t
  bootloaderCoverScreen;
