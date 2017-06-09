// File: power_manager.c

// Definitions of supporting functionalities in the power module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "power_manager.h"
#include "power_driver.h"

#include "OSA.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define POWER_VLPR_MAX_CLK 4000000UL
#define POWER_VLPR_MCG_LITE 0

#define POWER_VLPR_MAX_FLASH_BLPE_CLK 1000000UL
#define POWER_VLPR_MAX_FLASH_BLPI_CLK 1000000UL

// Timeout used for waiting to set new mode.
#define POWER_SET_MODE_TIMEOUT 1000U

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Power manager internal structure.
static power_manager_state_t gPowerManagerState;

// Power manager internal structure lock.
mutex_t gPowerManagerStateSync;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static power_manager_error_code_t POWER_SYS_CheckClocks(
    power_manager_modes_t mode )
{
    return kPowerManagerSuccess;
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the power manager.
power_manager_error_code_t POWER_SYS_Init()
{
    // Initialise internal structure lock.
    OSA_MutexCreate( &gPowerManagerStateSync );
    
    return kPowerManagerSuccess;
}

// Deinitialises the power manager.
power_manager_error_code_t POWER_SYS_Deinit()
{
    // Deinitialise internal structure lock.
    OSA_MutexDestroy( &gPowerManagerStateSync );
    
    return kPowerManagerSuccess;
}

// Configures the power mode.
power_manager_error_code_t POWER_SYS_SetMode(
    uint8_t powerModeIndex, power_manager_policy_t policy )
{
    volatile uint8_t dummyRead;
    power_manager_error_code_t returnCode;
    power_manager_error_code_t clockCheckRetCode;

    OSA_MutexLock( &gPowerManagerStateSync, OSA_WAIT_FOREVER );
    
    // Check that requested power mode is not protected.
    if( ( SMC_PMPROT & 0x02 ) == 0 ) //if( AVLLS_bit == 0 )
    {
        OSA_MutexUnlock( &gPowerManagerStateSync );
        return kPowerManagerError;
    }
    
    returnCode = power_CallBeforeSleep();
    
    OSA_MutexUnlock( &gPowerManagerStateSync );
    
    // Clocks should be in desired range. Some registered callback
    // can change the clock so check clock after callbacks.
    clockCheckRetCode = POWER_SYS_CheckClocks( kPowerManagerVlps );
    
    if( ( returnCode == kPowerManagerSuccess )
        && ( clockCheckRetCode == kPowerManagerSuccess ) )
    {

        SLEEPONEXIT_bit = 0;
        PORPO_bit = 0;
        SMC_PMCTRL = 0x02;
        SLEEPDEEP_bit = 1;
        dummyRead = SMC_PMCTRL;
        ENABLE_bit = 0;
        asm WFI;
        ENABLE_bit = 1;
        
        OSA_MutexLock( &gPowerManagerStateSync, OSA_WAIT_FOREVER );

        power_CallAfterSleep();

        OSA_MutexUnlock( &gPowerManagerStateSync );
    }
    else
    {
        if( returnCode == kPowerManagerSuccess )
            returnCode = clockCheckRetCode;

         power_CallBeforeSleep();
    }

    return returnCode;
}