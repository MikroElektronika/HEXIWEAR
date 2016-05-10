#ifndef HG_BOND
#define HG_BOND

#include "fsl_rtc_driver.h"
#include "gui_driver.h"

// screens
extern guiScreen_t bondScreen;

// task handlers

// public functions
void bond_SetPasskey(uint32_t passkey);

#endif
