/**
 * \file Events.h
 * \version 1.00
 * \brief various events' handlers should be placed here, such as interrupts' handlers, etc.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#include "Cpu.h"
#include "Events.h"
#include "rtc_driver.h"
#include "sensor.h"
#include "watch.h"
#include "haptic.h"
#include "flashlight.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "power_driver.h"

 /** User includes (#include below this line is not maintained by Processor Expert) */
void LLWU_IRQHandler(void)
{
   /** Write your code here. For example clear LLWU wake up flags ... */
}

/*! NFS_I2C IRQ handler */
void I2C0_IRQHandler(void)
{
  I2C_DRV_IRQHandler(FSL_NFS_I2C);
}

/*! FS_I2C IRQ handler */
void I2C1_IRQHandler(void)
{
  I2C_DRV_IRQHandler(FSL_FS_I2C);
}

/*! FLASH_SPI IRQ handler */
void SPI1_IRQHandler(void)
{
#if FLASH_SPI_DMA_MODE
  DSPI_DRV_EdmaIRQHandler(FSL_FLASH_SPI);
#else
  DSPI_DRV_IRQHandler(FSL_FLASH_SPI);
#endif
   /** Write your code here ... */
}

/*! OLED_SPI IRQ handler */
void SPI2_IRQHandler(void)
{
#if OLED_SPI_DMA_MODE
  DSPI_DRV_EdmaIRQHandler(FSL_OLED_SPI);
#else
  DSPI_DRV_IRQHandler(FSL_OLED_SPI);
#endif
   /** Write your code here ... */
}

void RTC_IRQHandler(void)
{
  RTC_AlarmCallback();
}

void RTC_Seconds_IRQHandler(void)
{
   /** Write your code here ... */
}

/*! BATTERY_ADC IRQ handler */
void ADC0_IRQHandler(void)
{
   /** Write your code here ... */
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

void PORTB_IRQHandler(void)
{
  PORT_HAL_ClearPortIntFlag(PORTB_BASE_PTR);
   /** Write your code here ... */
}

#ifdef __cplusplus
}   /** extern "C" */
#endif
