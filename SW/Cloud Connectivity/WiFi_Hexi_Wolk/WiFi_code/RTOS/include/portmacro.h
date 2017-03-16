// File: portmacro.h

// Port specific definitions.
// These settings will configure FreeRTOS for this hardware and compiler.

#ifndef _portmacro_h_
#define _portmacro_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "FreeRTOSConfig.h"

extern void vPortEnterCritical();
extern void vPortExitCritical();

extern void vPortYieldFromISR();

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/

#define portCHAR   char
#define portFLOAT  float
#define portDOUBLE double
#define portLONG   long
#define portSHORT  short

#define portSTACK_TYPE unsigned long
#define portBASE_TYPE  long

#define portMAX_DELAY 0xffffffff

// Hardware specifics.

#define portBYTE_ALIGNMENT 8
#define portSTACK_GROWTH   -1

#define portTICK_PERIOD_MS ( 1000 / configTICK_RATE_HZ )

// Critical section management.

#define portPOST_ENABLE_DISABLE_INTERRUPTS() // Nothing special needed.

// Set basepri to configMAX_SYSCALL_INTERRUPT_PRIORITY using R0.
#define portSET_INTERRUPT_MASK()                                               \
        CPU_REG_SET( CPU_BASEPRI, configMAX_SYSCALL_INTERRUPT_PRIORITY )

// Set basepri back to 0 using R0.
#define portCLEAR_INTERRUPT_MASK()                                             \
        CPU_REG_SET( CPU_BASEPRI, 0 )

#define portSET_INTERRUPT_MASK_FROM_ISR()      0; portSET_INTERRUPT_MASK()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x ) portCLEAR_INTERRUPT_MASK()

#define portDISABLE_ALL_INTERRUPTS() asm { cpsid i }
#define portDISABLE_INTERRUPTS()     portSET_INTERRUPT_MASK()
#define portENABLE_INTERRUPTS()      portCLEAR_INTERRUPT_MASK()
#define portENTER_CRITICAL()         vPortEnterCritical()
#define portEXIT_CRITICAL()          vPortExitCritical()

// Scheduler utilities.

#define portYIELD() vPortYieldFromISR()
#define portEND_SWITCHING_ISR( xSwitchRequired )                               \
    if( xSwitchRequired ) vPortYieldFromISR()

// Task function macros as described on the FreeRTOS.org website.
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )                     \
    void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )                           \
    void vFunction( void *pvParameters )

/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/
 
typedef portSTACK_TYPE StackType_t;
typedef long           BaseType_t;
typedef unsigned long  UBaseType_t;
typedef unsigned long  TickType_t;

/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/

// Starts the first task. Called from xPortStartScheduler().
void vPortStartFirstTask();

// Handler for the SWI interrupt.
void vPortYieldHandler();

// Enables floating point support in the CPU.
void vPortEnableVFP();

// Prototypes for interrupt service handlers.

// SVC interrupt handler.
void SVC_Handler();

// PendSV interrupt handler.
void PendSV_Handler();

// SysTick interrupt handler.
void SysTick_Handler();

#endif