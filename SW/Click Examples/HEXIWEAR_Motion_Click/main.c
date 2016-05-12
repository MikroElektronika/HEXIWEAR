/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
 *
 * [File Name]     main.c
 * [Platform]      MK64FN1M0VDC12
 * [Project]       HEXIWEAR_Motion_Click
 * [Version]       1.00
 * [Author]        marko.lainovic
 * [Date]          04/19/2016
 * [Language]      'C'
 * [History]       1.00 - Original Release
 *
 * [Description]   Put Motion Click into a MikroBus socket 2 on the docking station.
 * Observe the movement detection on-screen
 *
 */

//-----------------------------------------------------------------------
// Standard C/C++ Includes
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// KSDK Includes
//-----------------------------------------------------------------------
#include "main.h"
//-----------------------------------------------------------------------
// Application Includes
//-----------------------------------------------------------------------
#include "OLED_driver.h"
#include "screens_common.h"
#include "generic_spi_driver.h"

#include "OLED_defs.h"
#include "GPIO.h"
#include "OLED_SPI.h"
#include "DMA_controller.h"
#include "gui_resources.h"

//-----------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
oled_dynamic_area_t
	splashArea =
	{
		.xCrd = 0,
		.yCrd = 0
	};

//oled_dynamic_area_t
//	motionTextArea =
//	{
//		.xCrd   = 0,
//		.yCrd   = 75,
//		.width  = 96,
//		.height = 15
//	};
//
//oled_text_properties_t
//	motionTextProperties =
//	{
//		.font       = guiFont_Tahoma_8_Regular,
//		.fontColor  = GUI_COLOR_WHITE,
//		.alignParam = OLED_TEXT_ALIGN_CENTER,
//		.background = NULL
//	};

static uint8_t isMotionDetected = -1;
//static uint8_t motionText[] = "Motion!";

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define ENABLE_SENSOR()   GPIO_DRV_SetPinOutput( Motion_Sens_EN )
#define DISABLE_SENSOR()  GPIO_DRV_ClearPinOutput( Motion_Sens_EN )
#define READ_SENSOR_PIN() GPIO_DRV_ReadPinInput( Motion_Sens_PIN )

#define RED_LED_ON()  GPIO_DRV_ClearPinOutput( RED_LED )
#define RED_LED_OFF() GPIO_DRV_SetPinOutput( RED_LED )

//-----------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------

void main()
{
	CLOCK_SYS_EnablePortClock(PORTA_IDX);
	CLOCK_SYS_EnablePortClock(PORTB_IDX);
	CLOCK_SYS_EnablePortClock(PORTC_IDX);
	CLOCK_SYS_EnablePortClock(PORTD_IDX);
	CLOCK_SYS_EnablePortClock(PORTE_IDX);

    g_xtal0ClkFreq = 12000000U;
    g_xtalRtcClkFreq = 32768U;

	/** configure SPI2 pins */
    PORT_HAL_SetMuxMode( PORTB, 21UL, kPortMuxAlt2 );
    PORT_HAL_SetMuxMode( PORTB, 22UL, kPortMuxAlt2 );

	OSA_Init();

	GPIO_DRV_Init( pir_input_cfg, pir_output_cfg );
	GPIO_DRV_Init( NULL, OLED_cfg );
	GPIO_DRV_Init( NULL, PWR_cfg );
	GPIO_DRV_Init( NULL, RGB_cfg );

	EDMA_DRV_Init( &DMA_controller_State, &DMA_controller_InitConfig0 );
	DSPI_DRV_EdmaMasterInit(FSL_OLED_SPI, &OLED_SPI_MasterState, &OLED_SPI_MasterConfig, &OLED_SPI_dmaTcd);
	DSPI_DRV_EdmaMasterConfigureBus(FSL_OLED_SPI, &OLED_SPI_BusConfig, &OLED_SPI_calculatedBaudRate);

	OLED_Init( &oledModule, &oledSettings );
	OLED_GetImageDimensions( &(splashArea.width), &(splashArea.height), hexiwear_logo_bmp );
	OLED_SetDynamicArea( &splashArea );

//	OLED_SetTextProperties( &motionTextProperties );

	__enable_irq();

	/** enable motion sensor */
	ENABLE_SENSOR();

	OLED_DrawImage( motion_none_bmp );

    while (1)
    {
        if ( 1 == isMotionDetected )
        {
        	OLED_DrawImage( motion_detected_bmp );
//            RED_LED_ON();
            isMotionDetected = -1;
        }
        else if ( 0 == isMotionDetected )
        {
        	OLED_DrawImage( motion_none_bmp );
//            RED_LED_OFF();
            isMotionDetected = -1;
        }
    }
}

void MotionDetect()
{
    if ( 1 == READ_SENSOR_PIN() )
    {
        isMotionDetected = 1;
    }
    else
    {
        isMotionDetected = 0;
    }
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
