/**
 * Power management
 * Project HEXIWEAR, 2015
 */

#ifndef HG_POWER_DRIVER
#define HG_POWER_DRIVER

#include "power_types.h"
#include "power.h"

/**
  * [power_Init description]
  * @return [description]
  */
power_status_t power_Init();

/**
 * [power_Init description]
 * @return [description]
 */
void power_SensorManagement();

/**
 * [power_TurnON  description]
 * @param  peripheral [description]
 * @return            [description]
 */
power_status_t power_TurnON ( power_peripheral_t peripheral );

/**
 * [power_TurnOFF description]
 * @param  peripheral [description]
 * @return            [description]
 */
power_status_t power_TurnOFF( power_peripheral_t peripheral );

void power_StandbyInit( void* param );
void power_StandbyDestroyTasks( void* param );


/**
 * [power_ResetKW40 description]
 */
void power_ResetKW40();

/**
 * return power flags
 */
bool power_IsActive( power_peripheral_t peripheral );

/**
 * enable the power save feature:
 *   enable OLED
 *   enable current sensor subscriptions
 */
void power_EnablePowerSave();
/**
 * disable the power save feature:
 *   disable OLED
 *   disable current sensor subscriptions
 */
void power_DisablePowerSave();

/**
 * set sleep source
 * @param sleepSrc entity which will put the MCU to sleep
 */
void power_SetSleepSource( power_sleep_src_t sleepSrc );

/**
 * get sleep source
 * @return current entity which will put the MCU to sleep
 */
power_sleep_src_t power_GetSleepSource();

/**
 * set wakeup source
 * @param wakeupSrc entity which wake up the MCU
 */
power_status_t power_SetWakeSource( power_wake_src_t wakeSrc );

/**
 * get wakeup source
 * @return current entity which will wake up the MCU
 */
power_wake_src_t power_GetWakeSource();

/**
 * [power_IsActiveSleep description]
 * @return [description]
 */
bool power_HasJustExitSleep();

/**
 * put HEXIWEAR into standby mode ( i.e. total or partial sleep )
 */
void power_GotoSleep();

/**
 * [power_SetCurrentMode description]
 * @param newMode [description]
 */
void power_SetCurrentMode( power_current_mode_t newMode );

/**
 * [power_GetCurrentMode description]
 * @return [description]
 */
power_current_mode_t power_GetCurrentMode();

/**
 * set new power mode
 * @param new desired power mode
 */
void power_SetSleepMode( power_sleep_mode_t newMode );

/**
 * [power_GetNewMode description]
 * @return [description]
 */
power_sleep_mode_t power_GetSleepMode();

/**
 * [power_TurnScreenOff description]
 */
void power_TurnScreenOFF();

/**
 * [power_TurnScreenOn description]
 */
void power_TurnScreenON();

power_status_t power_PostToSTSema();
power_status_t power_TakeFromSTSema();

/**
 * send sleep ON/OFF packet to KW40
 */
power_status_t power_AlertKW40( power_sleepState_t sleepState );

/**
 * call before entering sleep mode
 * @param notify
 * @param callbackData
 * @return
 */
power_manager_error_code_t power_CallBeforeSleep(
													power_manager_notify_struct_t* notify,
													power_manager_callback_data_t* callbackData
												);

/**
 * call after exiting sleep mode
 * @param notify
 * @param callbackData
 * @return
 */
power_manager_error_code_t power_CallAfterSleep (
													power_manager_notify_struct_t* notify,
													power_manager_callback_data_t* callbackData
												);

/**
 * check for battery status
 * @return status flag
 */
bool power_IsBatteryLow();

/**
 * set battery status as low
 */
void power_SetBatteryLow();

/**
 * unset battery status as low
 */
void power_UnsetBatteryLow();

#endif
