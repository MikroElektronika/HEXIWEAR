/**
 * bootloader related functions
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
 * [boootloader_QueueMsgPut description]
 * @param  packet [description]
 * @return        [description]
 */
bootloader_status_t boootloader_QueueMsgPut( hostInterface_packet_t* packet );

extern guiScreen_t
  bootloaderCoverScreen;
