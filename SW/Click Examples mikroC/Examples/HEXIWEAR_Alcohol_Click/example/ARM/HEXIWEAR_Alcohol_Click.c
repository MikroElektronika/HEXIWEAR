/****************************************************************************
* Title                 :   Alcohol click
* Filename              :   HEXIWEAR_Alcohol_Click.c
* Author                :   DJ/ML
* Origin Date           :   14/04/2016
* Notes                 :   Alcohol Click Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  14/04/16       1.0.0            DJ/ML        Interface Created.
*
*****************************************************************************/
/**
 * @file HEXIWEAR_Alcohol_Click.c
 * @brief <h2> Alcohol Click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Alcohol click board.
 */

/**
 * @page LIB_INFO Library Info
 * @date        19 Feb 2016
 * @author      DJ/ML
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 * <h3> Test configuration : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      MK64FN1M0XXX12               </li>
 * <li><b> Dev. Board    </b> :      HEXIWEAR                     </li>
 * <li><b> Oscillator    </b> :      12 MHz external              </li>
 * <li><b> Ext. Modules  </b> :      Alcohol Click on mikroBUS 1  </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1     </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Alcohol click example using HEXIWEAR </h3>
 * @par This example demonstrates usage of the Alcohol click board. Place the Alcohol click into
 * MikroBus socket 1 and observe the measured PPM value on-screen.
 *
 * <h3> Alcohol Features </h3>
 * @par Alcohol click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include "OLED_Driver.h"

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

const float
    LoadRes = 10470,           // LoadRes (Ohm) - Load resistance
    Vadc_5  = 0.001220703125,  // ADC step 5V/4096   = 1.22 mV (12-bit ADC)
    Vadc_33 = 0.0008056640625; // ADC step 3,3V/4096 = 0.8 mV  (12-bit ADC)


float
    Vrl,                                  // Output voltage
    SensorRes,                            // SensorRes (Ohm) - Sensor resistance
    ppm,                                  // ppm
    ratio;                                // SensorRes/LoadRes ratio

float
    value     = 0,
    value_old = 0;

static float
    calibValue;

static float
    RS_cal,
    RS_gas,
    RS_air;

uint16_t
    adc_rd = 1000;

uint8_t
    text[6];

static uint8_t
    ppmText[] = "ppm:";

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************
* Function InitModules(void)
* -------------------------------------------------------------------------------------------------
* Overview:
* Input: None
* Output: None
**************************************************************************************************/

void InitModules(void)
{
    uint32_t
        i;

    OLED_Init();
    OLED_DrawImage(&alcohol_bmp, 0, 0);

    OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
    OLED_WriteText( ppmText, 25, 75 );

    ADC0_Init();

    /** pause for 100ms for ADC module stabilization */
    Delay_ms(100);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************
* Function readSensor(void)
* -------------------------------------------------------------------------------------------------
* Overview: Read sensor
* Input: None
* Output: None
**************************************************************************************************/
void ReadSensor()
{
    adc_rd = ADC0_Get_Sample( 12 );

    /** pause 10ms */
    delay_ms(10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************
* Function readSensor(void)
* -------------------------------------------------------------------------------------------------
* Overview: Calculation of PPM
* Input: None
* Output: None
**************************************************************************************************/
void CalculatePPM()
{
    float
        lgPPM;
    /**
     * convert to milivolts
     * For 5V power supply, use Vadc_5 and  for 3V use Vadc_33
     */
    Vrl = (float)adc_rd * Vadc_33;

    /** calculate the voltage ratio */
    SensorRes = ( ( 5.0 - Vrl ) / Vrl ) * LoadRes;
    ratio     = SensorRes / LoadRes;

    /** calculate PPM */
    lgPPM = ( log10( ratio ) * -1.5512 ) + 2.5911;
//    lgPPM = ( log10(ratio) * (-2.6) ) + 2.7;
    ppm = pow( 10, lgPPM );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************
* Function DisplayAlcoholValue(void)
* -------------------------------------------------------------------------------------------------
* Overview:
* Input: value
* Output: None
**************************************************************************************************/
void DisplayAlcoholValue( unsigned int value )
{
    if ( value_old != value )
    {
        // clear the previous value
        OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
        OLED_WriteText( text, 50, 75 );

        WordToStr(value, text);

        OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
        OLED_WriteText( text, 50, 75 );
    }
    value_old = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
    InitModules();

    while(1)
    {
        ReadSensor();
        CalculatePPM();
        DisplayAlcoholValue( floor(ppm) );
        Delay_ms(500);
    }
}

/*************** END OF FUNCTIONS *********************************************/