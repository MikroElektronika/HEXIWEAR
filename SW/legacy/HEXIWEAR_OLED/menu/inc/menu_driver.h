
#ifndef _MENU_DRIVER
#define _MENU_DRIVER

#include <stdint.h>
#include <stddef.h>

#include "menu_defs.h"
#include "menu_screens.h"

void MenuDriver_Init(void);
menuStatus_t MenuDriver_LoadScreen(menuNavigationDir_t navigationDir, void *param);

#endif
