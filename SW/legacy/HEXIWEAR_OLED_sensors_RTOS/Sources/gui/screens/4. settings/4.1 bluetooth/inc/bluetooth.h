#pragma once

#include "gui_driver.h"

#define BLUETOOTH_STACK_SIZE ( 0x500 )
#define BLUETOOTH_PRIO       ( HEXIWEAR_GUI_PRIO )

typedef enum
{
	bluetooth_advMode_disable  = 0,
	bluetooth_advMode_enable   = 1,
} bluetooth_advMode_t;

// screens
extern guiScreen_t bluetoothScreen;

// public function declarations
void           bluetooth_CreateAdvModeUpdateEvent(void);
void           bluetooth_SendGetAdvModeReq(void);
void           bluetooth_SendToggleAdvModeReq(void);
osa_status_t   bluetooth_WaitForAdvModeUpdate(uint32_t timeout);
osa_status_t   bluetooth_AdvModeUpdate(bluetooth_advMode_t bluetooth_advMode);
bluetooth_advMode_t bluetooth_CurrentAdvModeGet(void);
// screens

