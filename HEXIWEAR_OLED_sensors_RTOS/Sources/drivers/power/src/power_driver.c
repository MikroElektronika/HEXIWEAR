/**
 * Power management
 * Project HEXIWEAR, 2015
 */

#include "power_driver.h"
#include "power_info.h"

#include "OLED_driver.h"
#include "OLED_defs.h"
#include "OLED_info.h"

#include "PWR_Manager.h"

#include "error.h"
#include "GPIO.h"

/**
 * [POWER_putToSleep description]
 * @param  peripheral [description]
 * @return            [description]
 */
statusPOWER_t power_putToSleep(
                                periphPOWER_t peripheral
                              )
{
  uint8_t
    sleepStatus = 0;

  switch ( peripheral )
  {
    case POWER_OLED:    {
                          OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE );
                          break;
                        }

    case POWER_MCU:     {
                          uint8_t
                            powerMode;

                          // check the current mode
                          POWER_SYS_GetLastMode( &powerMode );

                          /**
                           * goto sleep
                           * one by one peripheral
                           */

                          if ( 0 == powerMode )
                          {
                            sleepStatus = OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE );
                            GPIO_DRV_ClearPinOutput( oledSettings.ENpin );

                            /**
                             * turn OFF power supplies
                             */

                            PWR_HR_TurnOFF();
                            PWR_SENSORS_NF_TurnOFF();

                            sleepStatus = POWER_SYS_SetMode( 1, kPowerManagerPolicyForcible );
                          }
                          break;
                        }

    case POWER_SENSORS: { break; }

    default: {}
  }

  if ( 0 == sleepStatus )
  {
    return STATUS_POWER_SUCCESS;
  }

  else
  {
    catch(6);
    return STATUS_POWER_ERROR;
  }

}
