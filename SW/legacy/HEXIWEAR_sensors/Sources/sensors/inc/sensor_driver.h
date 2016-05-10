/**
 * sensors wrapper routines
 * Project HEXIWEAR, 2015
 */

#ifndef HG_SENSORS
#define HG_SENSORS

#include <stdint.h>

#include "sensor_types.h"
#include "sensor_defs.h"

#include "fsl_os_abstraction.h"

#include "HEXIWEAR_types.h"

#define registerFormatters( sensType )\
sensor_fmtDef2Float = sensType##_fmtDef2Float;\
sensor_fmtDef2Me    = sensType##_fmtDef2Me

/**
 * initialize sensor RTOS structures
 */
osa_status_t sensor_Init();

/**
 * format sensor data to other formats
 * @param sensorData data to be formatted
 * @param fmtOptions options include:
 *                   - data type
 *                   - original format
 *                   - new format
 */
void sensor_FormatData(
                          const void* src,
                                void* dst,
                        const uint8_t fmtOptions
                      );

#endif
