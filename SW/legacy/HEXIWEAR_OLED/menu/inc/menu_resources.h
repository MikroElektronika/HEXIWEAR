
#ifndef _MENU_RESOURCES
#define _MENU_RESOURCES

#include "menu_defs.h"

#define img_SkipHeader( imgPtr ) ( (const uint8_t*)(imgPtr) + 6 )

extern const uint8_t menuItem_main_bmp[MENU_IMAGE_SIZE];
extern const uint8_t menuItem_apps_bmp[MENU_IMAGE_SIZE];
extern const uint8_t menuItem_settings_bmp[MENU_IMAGE_SIZE];

#endif
