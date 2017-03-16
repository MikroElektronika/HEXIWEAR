// File: port.c

// Implementation of parts of FreeRTOS
// that represent the port to this microcontroller and compiler.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "portmacro.h"
#include "FreeRTOS.h"
#include "task.h"

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

#define ENABLE_TICK_COUNTER()                                                  \
    CLKSOURCE_bit = 1;                                                         \
    TICKINT_bit   = 1;                                                         \
    ENABLE_bit    = 1
    
#define DISABLE_TICK_COUNTER()                                                 \
    CLKSOURCE_bit = 1;                                                         \
    TICKINT_bit   = 1;                                                         \
    ENABLE_bit    = 0
    
#define RESET_TICK_COUNTER_VAL()                                               \
    STK_VAL = 0

#define ACKNOWLEDGE_TICK_ISR() // not needed

#define TICK_NOF_BITS                24
#define COUNTS_UP                    0
#define SET_TICK_DURATION( val )     STK_LOAD = val
#define GET_TICK_DURATION( val )     STK_LOAD
#define GET_TICK_CURRENT_VAL( addr ) *( addr ) = STK_VAL

#define TIMER_COUNTS_FOR_ONE_TICK                                              \
    ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ )

// Constants required to manipulate the NVIC.
#define portNVIC_PENDSVSET_BIT ( 0x1 << 28 )

#define portNVIC_SYSTICK_PRI ( configKERNEL_INTERRUPT_PRIORITY << 24 )
#define portNVIC_PENDSV_PRI  ( configKERNEL_INTERRUPT_PRIORITY << 16 )

// Constants required to set up the initial stack.
#define portINITIAL_XPSR        0x01000000
#define portINITIAL_EXEC_RETURN 0xfffffffd

// Constants required to manipulate the VFP.
// Floating point context control register.
#define portFPCCR                0xe000ef34
#define portASPEN_AND_LSPEN_BITS ( 0x3 << 30 )

#define USE_FPU 1


/******************************************************************************
 * Type definitions.                                                          *
 ******************************************************************************/

typedef unsigned long TickCounter_t;

/******************************************************************************
 * Static variable definitions.                                               *
 ******************************************************************************/
 
// Used to keep track of the number of nested calls to taskENTER_CRITICAL().
// This will be set to 0 prior to the first task being started.
// Each task maintains its own interrupt status in this variable.
static unsigned portBASE_TYPE uxCriticalNesting = 0xaaaaaaaa;

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/

// Initialises the stack of a new task so it is ready to be executed.
// The registers have to be placed on the stack in the correct order.
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack,
    pdTASK_CODE pxCode, void *pvParameters )
{
    // Offset to account for the way MCU uses the stack
    // on entry/exit of interrupts.
    pxTopOfStack -= 1;

    *pxTopOfStack = portINITIAL_XPSR;             // xPSR
    pxTopOfStack--;
    *pxTopOfStack = (StackType_t)pxCode;          // PC
    pxTopOfStack--;
    *pxTopOfStack = 0;                            // LR

    // Skip register initalization.
    pxTopOfStack -= 5;                           // R12, R3, R2, R1
    *pxTopOfStack = (StackType_t)pvParameters;   // R0

    // Each task has to maintain its own exec return value.
    pxTopOfStack--;
    *pxTopOfStack = portINITIAL_EXEC_RETURN;

    pxTopOfStack -= 8; // R11, R10, R9, R8, R7, R6, R5, R4

    return pxTopOfStack;
}

// Tick timer initialisation.
void vPortInitTickTimer()
{
    // Set priority of SysTick interrupt.
    SCB_SHPR3 |= portNVIC_SYSTICK_PRI;
    // Set tick duration.
    SET_TICK_DURATION( TIMER_COUNTS_FOR_ONE_TICK - 1 );
    // Reset tick counter.
    RESET_TICK_COUNTER_VAL();
    // Enable tick counter.
    ENABLE_TICK_COUNTER();
}

// Starts the tick timer.
void vPortStartTickTimer()
{
    ENABLE_TICK_COUNTER();
}

// Stops the tick timer.
void vPortStopTickTimer()
{
    DISABLE_TICK_COUNTER();
}

// Enables floating point support in the CPU.
void vPortEnableVFP()
{
    asm {
        // The FPU enable bits are in the CPACR.
        LDR R0, =0xE000ED88
        LDR R1, [R0]
        // Enable CP10 and CP11 coprocessors, then save back.
        ORR R1, R1, #0x00F00000
    }
}

// Setup the hardware so that scheduler can take control.
// This generally sets up a tick interrupt and sets timers.
BaseType_t xPortStartScheduler()
{
    // Set priority of PendSV interrupt.
    SCB_SHPR3 |= portNVIC_PENDSV_PRI;
    // Initialise critical nesting counter.
    uxCriticalNesting = 0;
    // Initialise tick timer.
    vPortInitTickTimer();
    // Start tick timer.
    vPortStartTickTimer();
    // Enable the floating point unit.
    vPortEnableVFP();
    // Lazy register save always.
    *( ( unsigned long * ) portFPCCR ) |= portASPEN_AND_LSPEN_BITS;
    // Start the first task.
    vPortStartFirstTask();
    
    // Should not get here, unless vTaskEndScheduler() is called.
    return pdFALSE;
}

// Enters a critical region.
void vPortEnterCritical()
{
    // Disable interrupts and increment the count of critical section nesting.
    // Nesting count will let us know when interrupts need to be re-enabled.
    portDISABLE_INTERRUPTS();
    portPOST_ENABLE_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
    asm dsb;
    asm isb;
}

// Exits a critical region.
void vPortExitCritical()
{
    // If the nesting count is zero, interrupts should be enabled again.
    uxCriticalNesting--;
    if( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
        portPOST_ENABLE_DISABLE_INTERRUPTS();
    }
}

// Yield the processor, can be called from an ISR.
void vPortYieldFromISR()
{
    // Set a PendSV to request a context switch.
    SCB_ICSRbits.PENDSVSET = 1;
    // Barriers are normally not required but do ensure
    // the code is completely within specified behavior for the architecture.
    asm dsb;
    asm isb;
}

// Returns the current tick counter value.
portLONG uxGetTickCounterValue()
{
    portLONG val;
    
    GET_TICK_CURRENT_VAL( &val );
    
    return val;
}

// SysTick interrupt handler.
void SysTick_Handler() iv IVT_INT_SysTick
{
    ACKNOWLEDGE_TICK_ISR();
    
    // Disable interrupts.
    portSET_INTERRUPT_MASK();

    // If context switch should be performed, call taskYIELD().
    if( xTaskIncrementTick() != pdFALSE )
        taskYIELD();

    // Enable interrupts again.
    taskENABLE_INTERRUPTS();
}

// Starts the first task. Called from xPortStartScheduler().
void vPortStartFirstTask()
{
    asm {
        // Use the NVIC offset register to locate the stack.
        LDR R0, =0xE000ED08
        // Load address of vector table.
        LDR R0, [R0]
        // Load first entry of vector table which is the reset stack pointer.
        LDR R0, [R0]
        // Set the MSP back to the start of the stack.
        MSR #CPU_MSP, R0
        // Globally enable interrupts.
        CPSIE I
//        cpsie f
//        dsb
//        isb
        // System call to start first task.
        SVC #0
        // Filler instruction.
        NOP
    }
}

// SVC interrupt handler.
static void SVC_Handler() iv IVT_INT_SVCall ics ICS_OFF
{
    asm {
        // Get the location of the current TCB and its stack.
        LDR R3, =_pxCurrentTCB
        LDR R1, [R3]
        LDR R0, [R1]

        // Pop the core registers.
        LDM R0!, (R4-R11, R14)
        MSR #CPU_PSP, R0
//        isb

        MOV R0, #0
        MSR #CPU_BASEPRI, R0

        BX R14
    }
}

// PendSV interrupt handler.
static void PendSV_Handler() iv IVT_INT_PendableSrvReq ics ICS_OFF
{
    asm {
        // Have to do this, otherwise the stack will overflow.
        ADD SP, SP, #4

        MRS R0, #CPU_PSP
//        isb

         // Get the location of the current TCB.
        LDR R3, =_pxCurrentTCB
        LDR R2, [R3]

        // If the task is using FPU context, push high vfp regs.
        TST R14, #0x10
        IT EQ
        VSTMDBEQ R0!, (S16-S31)

        // Push the core registers.
        STMDB R0!, (R4-R11, R14)
        // Save the new top of stack into the current TCB.
        STR R0, [R2]

        STMDB SP!, (R3)
        MOV R0, # configMAX_SYSCALL_INTERRUPT_PRIORITY
        MSR #CPU_BASEPRI, R0

//        dsb
//        isb

        // Perform a context switch.
        //BL _vTaskSwitchContext
    }
         vTaskSwitchContext();
    asm {
        MOV R0, #0
        MSR #CPU_BASEPRI, R0
        LDM SP!, (R3)

        // Get the new top of stack from the current TCB.
        LDR R1, [R3]
        LDR R0, [R1]
        // Pop the core registers.
        LDM R0!, (R4-R11, R14)

        // If the task is using FPU context, restore vfp regs.
        TST R14, #0x10
        IT EQ
        VLDMIAEQ R0!, (S16-S31)

        MSR #CPU_PSP, R0
//        isb
        BX R14
    }
}