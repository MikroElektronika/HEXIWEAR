// File: FreeRTOS.h

// Some redefinitions of functions and macros
// to allow for backward compatibility and such.

#ifndef _FreeRTOS_h_
#define _FreeRTOS_h_

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "projdefs.h"
#include "FreeRTOSConfig.h"
#include "portable.h"
#include "task.h"

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

#define portPRIVILEGE_BIT 0x00

#define portYIELD_WITHIN_API portYIELD

#define pvPortMallocAligned( x, puxStackBuffer )                               \
    ( ( ( puxStackBuffer ) == NULL )                                           \
        ? ( pvPortMalloc( x ) )                                                \
        : ( puxStackBuffer ) )
        
#define vPortFreeAligned( pvBlockToFree, xSize )                               \
    vPortFree( pvBlockToFree, xSize )

// Definitions to allow backward compatibility
// with FreeRTOS versions prior to V8.

#define eTaskStateGet eTaskGetState
#define portTickType TickType_t
#define xTaskHandle TaskHandle_t
#define xQueueHandle QueueHandle_t
#define xSemaphoreHandle SemaphoreHandle_t
#define xQueueSetHandle QueueSetHandle_t
#define xQueueSetMemberHandle QueueSetMemberHandle_t
#define xTimeOutType TimeOut_t
#define xMemoryRegion MemoryRegion_t
#define xTaskParameters TaskParameters_t
#define xTaskStatusType TaskStatus_t
#define xTimerHandle TimerHandle_t
#define xCoRoutineHandle CoRoutineHandle_t
#define pdTASK_HOOK_CODE TaskHookFunction_t
#define portTICK_RATE_MS portTICK_PERIOD_MS

#define tmrTIMER_CALLBACK TimerCallbackFunction_t
#define pdTASK_CODE TaskFunction_t
#define xListItem ListItem_t
#define xList List_t

#endif