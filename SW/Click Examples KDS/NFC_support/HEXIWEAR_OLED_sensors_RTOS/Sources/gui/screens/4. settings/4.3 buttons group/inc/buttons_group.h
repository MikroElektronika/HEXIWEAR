#pragma once

#include "gui_driver.h"

#define BUTTONS_GROUP_STACK_SIZE ( 0x500 )
#define BUTTONS_GROUP_PRIO       ( HEXIWEAR_GUI_PRIO )

typedef enum
{
	buttonsGroup_left   = 0,
	buttonsGroup_right  = 1,
}
buttonsGroup_t;

// screens
extern guiScreen_t buttonsGroupScreen;

// public function declarations
void           buttonsGroup_CreateActiveUpdateEvent(void);
void           buttonsGroup_SendGetActiveReq(void);
void           buttonsGroup_SendToggleActiveReq(void);
osa_status_t   buttonsGroup_WaitForActiveUpdate(uint32_t timeout);
osa_status_t   buttonsGroup_ActiveUpdate(buttonsGroup_t buttonsGroupActive);
buttonsGroup_t buttonsGroup_CurrnetActiveGet(void);

