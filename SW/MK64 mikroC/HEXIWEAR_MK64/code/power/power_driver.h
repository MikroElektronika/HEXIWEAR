// File: power_driver.h

// Declarations of main functionalities in the power module.

#ifndef _power_driver_h_
#define _power_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>

#include "power_types.h"
#include "power_manager.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the power task and relevant power objects.
power_status_t power_Init();

// Activates/deactivates power supplies for sensors.
void power_SensorManagement();

// Turns the selected peripheral ON.
power_status_t power_TurnON( power_peripheral_t peripheral );

// Turns the selected peripheral OFF.
power_status_t power_TurnOFF( power_peripheral_t peripheral );

// Sets BLE_RST pin to 0 and then releases it.
void power_ResetKW40();

// Returns power flags.
bool power_IsActive( power_peripheral_t peripheral );

// Enables the power save feature: OLED and current sensor subscriptions.
void power_EnablePowerSave();

// Disables the power save feature: OLED and current sensor subscriptions.
void power_DisablePowerSave();

// Sets sleep source.
void power_SetSleepSource( power_sleep_src_t sleepSrc );

// Gets sleep source.
power_sleep_src_t power_GetSleepSource();

// Sets wakeup source.
power_status_t power_SetWakeSource( power_wake_src_t wakeSrc );

// Gets wakeup source.
power_wake_src_t power_GetWakeSource();

// Check if this was the touch that woke the MCU.
bool power_HasJustExitSleep();

// Puts HEXIWEAR to sleep.
void power_GoToSleep();

// Sets current HEXIWEAR mode.
void power_SetCurrentMode( power_current_mode_t newMode );

// Gets current HEXIWEAR mode.
power_current_mode_t power_GetCurrentMode();

// Sets new power mode.
void power_SetSleepMode( power_sleep_mode_t newMode );

// Gets currently selected sleep mode.
power_sleep_mode_t power_GetSleepMode();

// Turns the screen off by sending the command
// and turning off the power supply.
void power_TurnScreenOFF();

// Turn the screen on by switching on the power supply
// and sending the command.
void power_TurnScreenON();

// Fills the semaphore for wake-up sources to take.
power_status_t power_PostToSTSema();

// Takes semaphore to signalize the wake-up happened.
power_status_t power_TakeFromSTSema();

// Sends sleep ON/OFF packet to KW40.
power_status_t power_AlertKW40( power_sleepState_t sleepState );

// Called before entering sleep mode.
power_manager_error_code_t power_CallBeforeSleep();

// Called after exiting sleep mode.
power_manager_error_code_t power_CallAfterSleep();

// Checks for battery status.
bool power_IsBatteryLow();

// Sets battery status as low.
void power_SetBatteryLow();

// Unsets battery status as low.
void power_UnsetBatteryLow();

#endif