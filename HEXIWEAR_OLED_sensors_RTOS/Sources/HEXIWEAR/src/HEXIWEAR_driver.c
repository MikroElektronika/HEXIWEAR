/**
 * global device functions
 * Project HEXIWEAR, 2015
 */

#include "HEXIWEAR_driver.h"
#include "HEXIWEAR_defs.h"
#include "HEXIWEAR_info.h"

#include "sensor_driver.h"
#include "sensor_defs.h"

#include "host_mcu_interface.h"
#include "menu_driver.h"

#include "CLOCK.h"

#include "error.h"
#include "error_types.h"

void HEXIWEAR_startup( task_param_t param )
{
  uint8_t
    status = 0;

  GPIO_DRV_Init( NULL, OLED_cfg );
  GPIO_DRV_Init( NULL, FLASH_cfg );
  GPIO_DRV_Init( NULL, PWR_cfg );
  GPIO_DRV_Init( NULL, VIBRO_cfg );

#if defined( HEXIWEAR_DEBUG )
  GPIO_DRV_Init( NULL, DEBUG_cfg );
#endif

  RTC_DRV_Init( FSL_CLOCK );

  /**
   * create basic tasks
   */

  status |= HostInterface_Init();
  status |= MenuDriver_Init();
  status |= sensor_Init();

  if ( HEXIWEAR_STATUS_SUCCESS != status )
  {
    catch( CATCH_INIT );
  }

  while (1) {}
}

/**
 * initialize the tasks
 * @return status flag
 */
hexiwear_status_t HEXIWEAR_Init()
{
  osa_status_t
    status = OSA_TaskCreate (
                              HEXIWEAR_startup,
                              (uint8_t*)"HEXIWEAR startup",
                              HEXIWEAR_STARTUP_STACK_SIZE,
                              NULL,
                              HEXIWEAR_STARTUP_PRIO,
                              (task_param_t)0,
                              false,
                              &hexiwear_startup_handler
                            );

  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_INIT );
    return HEXIWEAR_STATUS_INIT_ERROR;
  }

  else
  {
    return HEXIWEAR_STATUS_SUCCESS;
  }
}
