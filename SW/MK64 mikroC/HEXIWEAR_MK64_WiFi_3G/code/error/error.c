// File: error.c

// Definitions of functionalities in the error module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////
 
#include "error.h"
#include "HEXIWEAR_driver.h"
#include "apps/flashlight/flashlight.h"

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Catches common errors.
void error_catch( uint8_t errorCode )
{
    asm NOP;

    if( errorCode == CATCH_MEM_ALLOC )
    {
        asm NOP;
    }
}

void vApplicationMallocFailedHook()
{
    asm NOP;
}

void vApplicationStackOverflowHook(TaskHandle_t handle, uint8_t *name)
{
    asm NOP;
}

void UsageFault_Handler()
{
    asm NOP;
}

void HardFault_Handler()
{
    asm NOP;
    RED_LED_ON();
    HEXIWEAR_ResetMCU();
}

void MemManage_Handler()
{
    asm NOP;
}

void DefaultISR()
{
    asm NOP;
    RED_LED_ON();
    HEXIWEAR_ResetMCU();
}

void BusFault_Handler()
{
    asm NOP;
    RED_LED_ON();
    HEXIWEAR_ResetMCU();
}

void NMI_Handler()
{
    asm NOP;
    RED_LED_ON();
    HEXIWEAR_ResetMCU();
}

void GenExcept()
{
    HEXIWEAR_ResetMCU();

    while( 1 ) {}
}