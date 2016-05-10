/**
 * Project HEXIWEAR, 2015
 * sensors wrapper routines
 */

#ifndef HG_SENSORS
#define HG_SENSORS

#include "fsl_os_abstraction.h"

#include "sensor_defs.h"
#include "HEXIWEAR_types.h"

#include "FXAS_driver.h"
#include "FXOS_driver.h"
#include "HTU_driver.h"
#include "MPL_driver.h"
#include "TSL_driver.h"
#include "MAXIM_driver.h"

/**
 * create the sensor task
 */
osa_status_t sensor_Init();

/**
 * reset the packet counter, to trigger reading during the
 * next sensor loop
 * @param packetToUpdate packet to reset
 */
void sensor_ResetPacketcounter( packet_t packetToUpdate );


/**
 * [sensor_SetPushTargets description]
 * @param packetToUpdate [description]
 * @param newPushTarget  [description]
 * @param shouldToggleTask  [description]
 */
void sensor_SetPacketTargets(
									   packet_t packetToUpdate,
                            packet_pushTarget_t newPushTarget,
										   bool shouldToggleTask
                          );

/**
 * [sensor_SetPushTargets  description]
 * @param  sensorToUpdate [description]
 * @return                [description]
 */
packet_pushTarget_t sensor_GetPacketTargets (
												packet_t sensorToUpdate
                                          	);

/**
 * timer related
 */

/**
 * assign delay in [ms] to the particular packet
 */
void sensor_RegisterPacketDelay (
                                  packet_t packetToUpdate,
                                  uint32_t delay_ms
                                );

/**
 * set minimum delay for the sensor loop
 */
void sensor_SetMinimumDelay (
                              uint32_t delay
                            );
/**
 * [sensor_SaveCurrentTargetsForKW40 description]
 */
void sensor_SaveTargetsForKW40();

/**
 * [sensor_RestoreCurrentTargetsForKW40 description]
 */
void sensor_RestoreTargetsForKW40();

/**
 * [sensor_SaveCurrentTargetsForKW40 description]
 */
void sensor_ResetTargetsForKW40();

/**
 * [sensor_CheckTargetsForKW40() description]
 */
bool sensor_CheckForKW40Targets();

/**
 * initiate the accelerometer
 */
void sensor_InitAcc();

/**
 * [sensor_ResetLedIndicator description]
 */
void sensor_ResetLEDIndicator();

/**
 * [sensor_ClearLEDIndicator description]
 */
void sensor_ClearLEDIndicator();

/**
 * stop with waiting
 */
void sensor_StopWait();

/**
 * suspend the sensor task
 */
void sensor_Suspend();

/**
 * resume the sensor task
 */
void sensor_Resume();

#endif
