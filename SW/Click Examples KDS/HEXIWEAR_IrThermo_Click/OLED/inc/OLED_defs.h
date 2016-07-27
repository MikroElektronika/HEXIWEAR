/**
 * OLED-related structures
 * Project KWAP, 2015
 */

#include "OLED_types.h"

#ifndef HG_OLED_DEFS
#define HG_OLED_DEFS

extern handleOLED_t
  oledModule;

extern settingsOLED_t
  oledSettings;

extern mutex_t
	spiAccessMutex;

#endif
