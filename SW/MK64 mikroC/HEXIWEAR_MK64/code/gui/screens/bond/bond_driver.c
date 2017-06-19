// File: bond_driver.c

// Definitions of main functionalities in the bond gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "bond.h"
#include "gui_driver.h"
#include "screens_common.h"
#include "bond_private.h"
#include "power_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// Converts milliseconds to ticks.
#define MSEC_TO_TICK( msec )                                                   \
    ( ( ( uint32_t )( msec ) + 500uL / ( uint32_t )configTICK_RATE_HZ )        \
    * ( uint32_t )configTICK_RATE_HZ / 1000uL )

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static uint32_t bond_passkey;

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the Bond Screen.
void bond_Init( void *param )
{
    if( ( guiScreen_t* )param != &bondScreen )
    {
        bondScreen.navigation.left = ( guiScreen_t* )param;
    }

    GuiDriver_LabelCreate( &bond_label );

    sprintf( ( char* )bond_label.caption, "%lu", bond_passkey );
    GuiDriver_LabelAddToScr( &bond_label );

    // disable power save
    power_DisablePowerSave();
}

// Destroys the Bond Screen.
void bond_DestroyTasks( void *param )
{
    OLED_DestroyDynamicArea();
    GuiDriver_LabelDestroy( &bond_label );

    // enable power save
    power_EnablePowerSave();
}

// Saves the passkey.
void bond_SetPasskey( uint32_t passkey )
{
    bond_passkey = passkey;
}