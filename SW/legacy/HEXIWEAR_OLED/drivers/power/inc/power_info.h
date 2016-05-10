/**
 * Power management, related constants
 * Project HEXIWEAR, 2015
 */

#ifndef HG_POWER_INFO
#define HG_POWER_INFO

//#define SLEEP_TEST
#define SLEEP_TEST_MCU

#define PWR_HR_TurnOFF()         GPIO_DRV_ClearPinOutput( PWR_HR )
#define PWR_SENSORS_NF_TurnOFF() GPIO_DRV_SetPinOutput( PWR_SENSORS_NF )

#endif
