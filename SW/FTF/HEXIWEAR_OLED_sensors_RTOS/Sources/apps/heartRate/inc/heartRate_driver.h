/**
 * pedometer functions
 */

#pragma once

#include "heartRate_info.h"
#include "heartRate_defs.h"
#include <string.h>
#include "fsl_os_abstraction.h"
#include "host_mcu_interface.h"

/**
 * [heartRate_Init description]
 */
void heartRate_Init();

/**
 * [heartRate_Deinit description]
 */
void heartRate_Deinit();

/**
 * resume the pedometer step detection process
 */
void heartRate_Resume();

/**
 * pause the pedometer step detection process
 */
void heartRate_Pause();

/**
 * [heartRate_Process   description]
 * @param sampleBuf   [description]
 * @param numAvailSam [description]
 * @param param       [description]
 */
void heartRate_Process  (
                              void* sampleBuf,
                            uint8_t numAvailSam,
                              void* param
                        );