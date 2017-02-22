/* ###################################################################
**     Filename    : Events.c
**     Project     : HEXIWEAR_OLED_sensors_RTOS
**     Processor   : MK64FN1M0VDC12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-12-03, 12:23, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "rtc_driver.h"
#include "fxos_driver.h"
#include "sensor_driver.h"
#include "watch.h"
#include "haptic.h"
#include "flashlight.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "power_driver.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

void LLWU_IRQHandler(void)
{
  /* Write your code here. For example clear LLWU wake up flags ... */
}

/*! FLASH_SPI IRQ handler */
void SPI1_IRQHandler(void)
{
#if FLASH_SPI_DMA_MODE
  DSPI_DRV_EdmaIRQHandler(FSL_FLASH_SPI);
#else
  DSPI_DRV_IRQHandler(FSL_FLASH_SPI);
#endif
  /* Write your code here ... */
}

/*! OLED_SPI IRQ handler */
void SPI2_IRQHandler(void)
{
#if OLED_SPI_DMA_MODE
  DSPI_DRV_EdmaIRQHandler(FSL_OLED_SPI);
#else
  DSPI_DRV_IRQHandler(FSL_OLED_SPI);
#endif
  /* Write your code here ... */
}

void RTC_IRQHandler(void)
{
  RTC_AlarmCallback();
}

void RTC_Seconds_IRQHandler(void)
{
  /* Write your code here ... */
}

/*! BATTERY_ADC IRQ handler */
void ADC0_IRQHandler(void)
{
  /* Write your code here ... */
}

void LPTMR0_IRQHandler(void)
{
  LPTMR_DRV_IRQHandler( FSL_SENSOR_TIMER );
}

void PORTC_IRQHandler(void)
{
	PORT_HAL_ClearPortIntFlag(PORTC_BASE_PTR);

	watch_CheckBatteryStatus();

	RTC_UpdateAlarm();

	if ( true == FXOS_IsTapEnabled() )
	{
		switch ( power_GetCurrentMode() )
		{
			case POWER_CURRENT_MODE_NORMAL:
			{
				// regular work mode, do nothing
				break;
			}

			// if we were in shallow sleep mode, just turn the OLED ON
			case POWER_CURRENT_MODE_SLEEP_SHALLOW:
			{
				HostInterface_SetWakingTouch();
				power_SetCurrentMode( POWER_CURRENT_MODE_NORMAL );
				break;
			}

			case POWER_CURRENT_MODE_SLEEP_TOTAL:
			{
				HostInterface_SetWakingTouch();
				power_SetCurrentMode( POWER_CURRENT_MODE_NORMAL );

				if ( POWER_STATUS_SUCCESS != power_SetWakeSource( POWER_WAKE_SRC_USER ) )
				{
					asm("nop");
				}
				break;
			}

			/**
			 * special consideration is also required for the sensor tag sleep mode,
			 * since we might not be actually sleeping when UART interrupt occurs
			 */

			case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
			{
				HostInterface_SetWakingTouch();
				power_SetCurrentMode( POWER_CURRENT_MODE_NORMAL );

				if ( POWER_STATUS_SUCCESS == power_SetWakeSource( POWER_WAKE_SRC_USER ) )
				{
				}
				else
				{
					asm("nop");
				}
				break;
			}
		}
	}
}

void PORTD_IRQHandler(void)
{
  PORT_HAL_ClearPortIntFlag(PORTD_BASE_PTR);

  if(haptic_MutexLock(0) == kStatus_OSA_Success)
  {
	  GPIO_DRV_ClearPinOutput( KW40_GPIO );
	  OSA_TimeDelay(1);
	  GPIO_DRV_SetPinOutput( KW40_GPIO );
	  haptic_MutexUnlock();
  }
}

void PIT0_IRQHandler(void)
{
  /* Clear interrupt flag.*/
//  PIT_HAL_ClearIntFlag(g_pitBase[FSL_PIT_SENSOR_TIMER], FSL_PIT_SENSOR_TIMER_CHANNEL);
//  TimerCallback();
}

extern void NXPNCI_IRQHandler (void);

void PORTB_IRQHandler(void)
{
  PORT_HAL_ClearPortIntFlag(PORTB_BASE_PTR);
  NXPNCI_IRQHandler();
}

void test_uart_RxCallback(uint32_t instance, void * uartState)
{
  /* Write your code here ... */
}

void test_uart_TxCallback(uint32_t instance, void * uartState)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
