// File: sensor_driver.h

// Declarations of main functionalities in the sensors modules.

#ifndef _sensor_driver_h_
#define _sensor_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "OSA.h"

#include "HEXIWEAR.h"

#include "FXAS\FXAS_driver.h"
#include "FXOS\FXOS_driver.h"
#include "HTU\HTU_driver.h"
#include "MPL\MPL_driver.h"
#include "TSL\TSL_driver.h"
#include "MAXIM\MAXIM_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////
 
// Creates the sensor task.
osa_status_t sensor_Init();

// Resets the packet counter, to trigger reading during the next sensor loop.
void sensor_ResetPacketcounter( packet_t packetToUpdate );

// Sets targets for the particular sensor packet.
void sensor_SetPacketTargets(
                                         packet_t packetToUpdate,
                              packet_pushTarget_t newPushTarget,
                                             bool shouldToggleTask
                            );

// Retrieves a sensor's targets.
packet_pushTarget_t sensor_GetPacketTargets ( packet_t oldPushTargets );

// Assign polling delay in [ms] to the particular packet.
void sensor_RegisterPacketDelay(
                                 packet_t packetToUpdate,
                                 uint32_t delay_ms
                               );

// Sets minimum delay for the sensor loop.
void sensor_SetMinimumDelay( uint32_t delay );

// Backups all the sensors which have KW40 as its targets.
void sensor_SaveTargetsForKW40();

// Restores all the sensors which have KW40 as its targets.
void sensor_RestoreTargetsForKW40();

// Flushes the backup KW40 list.
void sensor_ResetTargetsForKW40();

// Checks if there are sensor packets with KW40 as their target.
bool sensor_CheckForKW40Targets();

// Initiates the accelerometer.
void sensor_InitAcc();

// Resets LED counter.
void sensor_ResetLEDIndicator();

// Turns LED off.
void sensor_ClearLEDIndicator();

// Stops waiting for semaphore.
void sensor_StopWait();

// Suspends the sensor task.
void sensor_Suspend();

// Resumes the sensor task.
void sensor_Resume();

#endif