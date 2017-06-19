// File: HEXIWEAR_driver.h

// Declarations of main functionalities in the HEXIWEAR module.

#ifndef _HEXIWEAR_driver_h_
#define _HEXIWEAR_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "HEXIWEAR_types.h"
#include "sensor_types.h"

#include "OSA.h"
#include "host_mcu_interface.h"
#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the tasks.
hexiwear_status_t HEXIWEAR_Init();

// Resets the MCU.
void HEXIWEAR_ResetMCU();

// Returns the app backup list.
void *HEXIWEAR_GetAppBackupList();

// Returns target to the current app.
packet_pushTarget_t HEXIWEAR_GetAppTarget();

// Sets the backup list.
void HEXIWEAR_SetBackupList( packet_pushTarget_t* currentBackupList );

// Sets the current app target.
void HEXIWEAR_SetTargetApp( packet_pushTarget_t currentApp );

// Sets flags in the internal flash.
hexiwear_status_t HEXIWEAR_SetFlags (
    uint32_t flashAddress,
       void* flags,
    uint32_t flagSize );

// Creates the HEXIWEAR version event.
void HEXIWEAR_CreateVersionEvent();

// Sends the version info via MKW40.
void HEXIWEAR_SendVersionReq();

// Waits for HEXIWEAR version update.
osa_status_t HEXIWEAR_WaitForVersionUpdate( uint32_t timeout );

// Updates the HEXIWEAR version.
osa_status_t HEXIWEAR_UpdateVersion();

//----------

// Sets interrupt priority.
void HEXIWEAR_SetIntPriority(uint8_t ivt, uint8_t priority);

#endif