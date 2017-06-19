// File: FreeRTOSConfig.h

// Serves as a configuration file for the FreeRTOS implementation.

#ifndef _FreeRTOSConfig_h_
#define _FreeRTOSConfig_h_

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// Miscellaneous settings

// 1: pre-emptive mode; 0: cooperative mode
#define configUSE_PREEMPTION                   1
// 1: use Idle hook; 0: no idle hook
#define configUSE_IDLE_HOOK                    0 // 1
// 1: use Tick hook; 0: no tick hook
#define configUSE_TICK_HOOK                    0
// 1: use MallocFailed hook; 0: no MallocFailed hook
#define configUSE_MALLOC_FAILED_HOOK           1
// Frequency of tick interrupt.
#define configTICK_RATE_HZ                     200
// Using Kinetis Low Power Timer (LPTMR) instead of SysTick timer.
#define configSYSTICK_USE_LOW_POWER_TIMER      0
// 1 kHz LPO Timer. Set to 1 if not used.
#define configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ 1

// CPU core clock frequency (in Hz).
#define configCPU_CLOCK_HZ                     Clock_kHz() * 1000     // 120 MHz
// Bus clock frequency (in Hz).
#define configBUS_CLOCK_HZ                     Clock_kHz() * 1000 / 2 // 60 MHz

// System Tick is using core clock.
#define configSYSTICK_USE_CORE_CLOCK           1
// No divider.
#define configSYSTICK_CLOCK_DIVIDER            1
// Frequency of system tick counter.
#define configSYSTICK_CLOCK_HZ                                                 \
    ( ( configCPU_CLOCK_HZ ) / configSYSTICK_CLOCK_DIVIDER )
// Stack size in addressable stack units.
#define configMINIMAL_STACK_SIZE               200

#define configMAX_TASK_NAME_LEN                60
#define configUSE_TRACE_FACILITY               0
#define configUSE_STATS_FORMATTING_FUNCTIONS   0
#define configUSE_16_BIT_TICKS                 0
#define configIDLE_SHOULD_YIELD                1
#define configUSE_CO_ROUTINES                  0
#define configUSE_MUTEXES                      1
#define configCHECK_FOR_STACK_OVERFLOW         1
#define configUSE_RECURSIVE_MUTEXES            1
#define configQUEUE_REGISTRY_SIZE              10
#define configUSE_QUEUE_SETS                   0
#define configUSE_COUNTING_SEMAPHORES          1
#define configUSE_APPLICATION_TASK_TAG         0

#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0

#define configMAX_PRIORITIES                   64
#define configMAX_CO_ROUTINE_PRIORITIES        2

// Software timer definitions.
#define configUSE_TIMERS                       1
#define configTIMER_TASK_PRIORITY              63
#define configTIMER_QUEUE_LENGTH               10
#define configTIMER_TASK_STACK_DEPTH           400

// Set the following definitions to 1 to include the API function,
// or zero to exclude the API function.

#define INCLUDE_vTaskPrioritySet                 1
#define INCLUDE_uxTaskPriorityGet                1
#define INCLUDE_vTaskDelete                      1
#define INCLUDE_vTaskSuspend                     1
#define INCLUDE_vTaskDelayUntil                  1
#define INCLUDE_vTaskDelay                       1
#define INCLUDE_uxTaskGetStackHighWaterMark      1
#define INCLUDE_xTaskGetSchedulerState           1
#define INCLUDE_xQueueGetMutexHolder             1
#define INCLUDE_xTaskGetCurrentTaskHandle        0
#define INCLUDE_xTaskGetIdleTaskHandle           0
#define INCLUDE_eTaskGetState                    0
#define INCLUDE_pcTaskGetTaskName                0
#define INCLUDE_xEventGroupSetBitFromISR         1
#define INCLUDE_xTimerPendFunctionCall           1

// Kernel interrupt priority - should be set to the lowest priority
#define configKERNEL_INTERRUPT_PRIORITY        0xF0

// Highest interrupt priority 
// from which interrupt safe FreeRTOS API functions can be called.
#define configMAX_SYSCALL_INTERRUPT_PRIORITY   0x10

// Normal assert() mechanics without relying on assert.h header file.
#define configASSERT( x )                                                      \
    if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); while( 1 ); }

#endif