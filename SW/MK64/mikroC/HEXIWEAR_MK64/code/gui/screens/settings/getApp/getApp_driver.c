// File: getApp_driver.c

// Definitions of main functionalities in the getApp gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "power_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

#pragma funcall GuiDriver_Init getApp_Init
// Disables power save prior to displaying the QR code.
void getApp_Init( void* param )
{
    power_DisablePowerSave();
}

#pragma funcall GuiDriver_Init getApp_Destroy
// Enables power save prior to exiting the GetApp screen.
void getApp_Destroy( void* param )
{
    power_EnablePowerSave();
}