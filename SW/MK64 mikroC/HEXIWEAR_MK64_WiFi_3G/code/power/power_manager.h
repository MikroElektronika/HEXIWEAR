// File: power_manager.h

// Declarations of supporting functionalities in the power module.

#ifndef _power_manager_h_
#define _power_manager_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// Power modes enumeration.
typedef enum _power_manager_modes {
    kPowerManagerRun,              // Run mode.
    kPowerManagerVlpr,             // Very low power run mode.
    kPowerManagerWait,             // Wait mode.
    kPowerManagerVlpw,             // Very low power wait mode.
    kPowerManagerStop,             // Stop mode.
    kPowerManagerVlps,             // Very low power stop mode.
    kPowerManagerLls,              // Low leakage stop mode.
    kPowerManagerVlls0,            // Very low leakage stop 0 mode.
    kPowerManagerVlls1,            // Very low leakage stop 1 mode.
    kPowerManagerVlls2,            // Very low leakage stop 2 mode.
    kPowerManagerVlls3,            // Very low leakage stop 3 mode.
    kPowerManagerMax
} power_manager_modes_t;

// Power manager success code and error codes.
typedef enum _power_manager_error_code {
    // Success.
    kPowerManagerSuccess,
    // Some error occurs.
    kPowerManagerError,
    // Configuration index out of range.
    kPowerManagerErrorOutOfRange,
    // Error occurs during mode switch.
    kPowerManagerErrorSwitch,
    // Error occurs during send "BEFORE" notification.
    kPowerManagerErrorNotificationBefore,
    // Error occurs during send "AFTER" notification.
    kPowerManagerErrorNotificationAfter,
    // Error occurs due to wrong clock setup for power modes.
    kPowerManagerErrorClock
} power_manager_error_code_t;

// Power manager policies.
typedef enum _power_manager_policy {
    // POWER_SYS_SetMode() method is exited
    // when any of the callbacks returns error code.
    kPowerManagerPolicyAgreement,
    // Power mode is changed regardless of the results.
    kPowerManagerPolicyForcible
} power_manager_policy_t;

// The PM notification type. Used to notify registered callbacks.
typedef enum _power_manager_notify
{
    // Notify IP to recover to previous work state.
    kPowerManagerNotifyRecover = 0x00U,
    // Notify IP that system will change power setting.
    kPowerManagerNotifyBefore  = 0x01U,
    // Notify IP that have changed to new power setting.
    kPowerManagerNotifyAfter   = 0x02U,
} power_manager_notify_t;

// The callback type.
typedef enum _power_manager_callback_type {
    kPowerManagerCallbackBefore      = 0x01U, // Before callback.
    kPowerManagerCallbackAfter       = 0x02U, // After callback.
    kPowerManagerCallbackBeforeAfter = 0x03U, // Before-After callback.
} power_manager_callback_type_t;

// Callback-specific data.
typedef void power_manager_callback_data_t;

// Power mode user configuration structure.
typedef struct _power_manager_mode_user_config {
    // Power mode.
    power_manager_modes_t mode;
    // Sleep or deep sleep after interrupt service finished.
    bool sleepOnExitValue;
    // Wake-up on interrupt from Very low power run,
    // Very low power wait or Very low power stop mode.
//     smc_lpwui_option_t lowPowerWakeUpOnInterruptValue;
    // Power on reset detection circuit is enabled
    // in Very low leakage stop 0 mode.
//     smc_por_option_t powerOnResetDetectionValue;
} power_manager_user_config_t;

// Power notification structure passed to registered callback function.
typedef struct _power_notify_struct {
    //Target power configuration index.
    uint8_t targetPowerConfigIndex;
    // Pointer to target power configuration.
    power_manager_user_config_t const *targetPowerConfigPtr;
    // Clock transition policy.
    power_manager_policy_t policy;
    // Clock notification type.
    power_manager_notify_t notifyType;
} power_manager_notify_struct_t;

// Callback prototype.
typedef power_manager_error_code_t (* power_manager_callback_t)(
    power_manager_notify_struct_t * notify,
    power_manager_callback_data_t * dataPtr
);

// Callback configuration structure.
typedef struct _power_manager_callback_user_config {
    power_manager_callback_t callback;
    power_manager_callback_type_t callbackType;
    power_manager_callback_data_t * callbackData;
} power_manager_callback_user_config_t;

// Power manager internal state structure.
typedef struct _power_manager_state {
    // Pointer to power configure table.
    power_manager_user_config_t const ** configs;
    // Number of power configurations.
    uint8_t configsNumber;
    // Pointer to callback table.
    power_manager_callback_user_config_t ** staticCallbacks;
    // Max. number of callback configurations.
    uint8_t staticCallbacksNumber;
    // Index of callback returns error.
    uint8_t errorCallbackIndex;
    // Index of current configuration.
    uint8_t currentConfig;
} power_manager_state_t;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the power manager.
power_manager_error_code_t POWER_SYS_Init();

// Deinitialises the power manager.
power_manager_error_code_t POWER_SYS_Deinit();

// Configures the power mode.
power_manager_error_code_t POWER_SYS_SetMode(
    uint8_t powerModeIndex, power_manager_policy_t policy );

#endif