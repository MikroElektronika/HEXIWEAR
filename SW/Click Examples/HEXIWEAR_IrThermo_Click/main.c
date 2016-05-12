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
 * [Project]       HEXIWEAR_IrThermo_Click
 * [Version]       1.00
 * [Author]        marko.lainovic
 * [Date]          04/19/2016
 * [Language]      'C'
 * [History]       1.00 - Original Release
 *
 * [Description]   Put IrThermo Click into any MikroBus socket on the docking station.
 * Observe the detected temperature in fahrenheit
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
#include "board.h"
#include "Cpu.h"

#include "GPIO.h"

#include "FS_I2C.h"
#include "OLED_SPI.h"

#include "OLED_driver.h"

#include "screens_common.h"
#include "gui_resources.h"

//-----------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------
static float ReadSensor( uint8_t tempSource );
static float ReadTemperature( uint8_t source );

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
#define AMB_TEMP   ( 0x06 )
#define OBJ_TEMP   ( 0x07 )
#define FAHRENHEIT ( 0x01 )
#define CELSIUS    ( 0x02 )

//-----------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
static uint8_t
	temp_format = FAHRENHEIT;

oled_dynamic_area_t
	splashArea =
	{
		.xCrd = 0,
		.yCrd = 0
	};

oled_dynamic_area_t
	tempTextArea =
	{
		.xCrd   = 5,
		.yCrd   = 75,
		.width  = 64,
		.height = 15
	};

oled_dynamic_area_t
	tempValArea =
	{
		.xCrd   = 75,
		.yCrd   = 75,
		.width  = 20,
		.height = 15
	};

oled_text_properties_t
	tempTextProperties =
	{
		.font       = guiFont_Tahoma_8_Regular,
		.fontColor  = GUI_COLOR_WHITE,
		.alignParam = OLED_TEXT_ALIGN_CENTER,
		.background = NULL
	};

static uint8_t tempText[] = "Temperature:";
static uint8_t tempValText[] = "000";

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------

void main()
{
	hardware_init();

	GPIO_DRV_Init( NULL, OLED_cfg );
	GPIO_DRV_Init( NULL, RGB_cfg );
	GPIO_DRV_Init( NULL, PWR_cfg );

	OSA_Init();

	Components_Init();

	OLED_GetImageDimensions( &(splashArea.width), &(splashArea.height), hexiwear_logo_bmp );
	OLED_SetDynamicArea( &splashArea );
	OLED_DrawImage( irthermo_logo_bmp );

	OLED_SetTextProperties( &tempTextProperties );

	OLED_SetDynamicArea( &tempTextArea );
    OLED_DrawText( tempText );

	while (1)
	{
		float
			tempValue = ReadTemperature( OBJ_TEMP );

		if ( 0 != tempValue )
		{
			volatile int16_t
				tempIntVal = (int16_t)tempValue;

			snprintf( (char*)tempValText, 4, "%3d", tempIntVal );
			OLED_SetDynamicArea( &tempValArea );
			OLED_DrawText( tempValText );
		}

		OSA_TimeDelay(500);
	}
}

static float ReadSensor( uint8_t tempSource )
{
	uint8_t
		tempVal[2];

    i2c_status_t
		status = I2C_DRV_MasterReceiveDataBlocking	(
														FSL_FS_I2C,
														&( FS_I2C_MasterConfig ),
														&tempSource,
														sizeof(tempSource),
														&( tempVal[0] ),
														sizeof(tempVal) / sizeof( tempVal[0] ),
														100
													);

    if ( kStatus_I2C_Success != status )
    {
    	return (float)-1;
    }
    else
    {
    	return (float)( ( (uint16_t)tempVal[1] << 8 ) | tempVal[0] );
    }
}

static float ReadTemperature( uint8_t source )
{
	// read ambient temperature
	float
		temp = ReadSensor( source );

	if ( (float)-1 != temp )
	{
		if ( FAHRENHEIT == temp_format )
		{
			temp = ( (temp * 0.02) - 273.15) * 9.0/5 + 32; // Convert result in FAHRENHEIT degrees
		}
		else if ( CELSIUS == temp_format )
		{
			temp = (temp * 0.02) - 273.15;       // Convert result in Celsius degrees
		}
		else
		{
			temp = 0;
		}
	}

	return temp;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
