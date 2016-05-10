#pragma once

#include "gui_driver.h"

#define HAPTIC_STACK_SIZE ( 0x500 )
#define HAPTIC_PRIO       ( HEXIWEAR_GUI_PRIO )

typedef enum
{
	hapticState_disable  = 0,
	hapticState_enable   = 1,
} hapticState_t;

// screens
extern guiScreen_t hapticScreen;

hapticState_t haptic_CurrentStateGet(void);

osa_status_t haptic_MutexCreate(void);
osa_status_t haptic_MutexLock(uint32_t timeout);
osa_status_t haptic_MutexUnlock(void);
void haptic_Vibrate(void);
void haptic_Run(void);

/**
 * check if haptic feedback should be enabled at startup
 */
void haptic_CheckAtStartup();
