/**
 * pedometer functions
 */

#pragma once

#include "pedometer_info.h"
#include "pedometer_defs.h"
#include <string.h>
#include "fsl_os_abstraction.h"
#include "host_mcu_interface.h"

/**
 * reset the handle values to their default
 */
pedometer_status_t pedometer_Reset();

/**
 * debounce counter
 * @param  dbcntm    [description]
 * @param  condition [description]
 * @param  count     [description]
 * @param  threshold [description]
 * @return           [description]
 */
bool debounce_count (
                                   bool dbcntm,
                                   bool condition,
                      debounce_count_t* count,
                       debounce_count_t threshold
                    );

/**
 * [pedometer_Init description]
 */
void pedometer_Init();

/**
 * [pedometer_CreateTask description]
 */
void pedometer_CreateTask();

/**
 * [pedometer_Deinit description]
 */
void pedometer_Deinit();

/**
 * [fitness_pedometer_QueueMsgPut description]
 * @param  packet [description]
 * @return        [description]
 */
pedo_process_status_t pedometer_QueueMsgPut (
                                              hostInterface_packet_t* packet
                                            );

/**
 * get steps
 */
uint16_t pedometer_GetStepCounter();

/**
 * resume the pedometer step detection process
 */
void pedometer_Resume();

/**
 * pause the pedometer step detection process
 */
void pedometer_Pause();

