/****************************************************************************
* Title                 :   Methane click
* Filename              :   HEXIWEAR_Methane_Click.c
* Author                :   DJ/ML
* Origin Date           :   14/04/2016
* Notes                 :   Methane Click Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  14/04/16       1.0.0            DJ/ML        Interface Created.
*
*****************************************************************************/
/**
 * @file HEXIWEAR_Methane_Click.c
 * @brief <h2> Methane Click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Methane click board.
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
 * <li><b> Ext. Modules  </b> :      Methane Click on mikroBUS 3  </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1     </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Methane click example using HEXIWEAR </h3>
 * @par This example demonstrates usage of the Methane click board. Place the Methane click into
 * MikroBus socket 3 and observe the measured PPM value on-screen.
 *
 * <h3> Methane Features </h3>
 * @par Methane click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include "OLED_Driver.h"

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

const float
    LoadRes = 10470,          // LoadRes (Ohm) - Load resistance
    Vadc_5  = 0.001220703125,  // ADC step 5V/4096   = 1.22 mV (12-bit ADC)
    Vadc_33 = 0.0008056640625; // ADC step 3,3V/4096 = 0.8 mV  (12-bit ADC)

double Vrl;                                  // Output voltage
double SensRes;                              // SensRes (Ohm) - Sensor resistance
double ppm;                                  // ppm
double ratio;                                // SensRes/LoadRes ratio

double value = 0, value_old = 0;
uint16_t adc_rd;
uint8_t text[16];

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
* Function CalculatePPM()
* -------------------------------------------------------------------------------------------------
* Overview: Calculation of PPM.
* Input: None
* Output: None
**************************************************************************************************/

void CalculatePPM()
{
    double lgPPM;
    Vrl = (double)adc_rd * Vadc_33;              // For 5V Vcc use Vadc_5  and  for 3V Vcc use Vadc_33
    SensRes = LoadRes * (5 - Vrl)/Vrl;           // Calculate sensor resistance
    ratio = SensRes/LoadRes;                     // Calculate ratio
    lgPPM = (log10(ratio) * -0.8 ) + 0.9;        // Calculate ppm
    ppm = pow(10,lgPPM);                         // Calculate ppm
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************
* Function DisplayMethaneValue(()
* -------------------------------------------------------------------------------------------------
* Overview:
* Input: None
* Output: None
**************************************************************************************************/

void DisplayMethaneValue( uint16_t value )
{
    if (value_old != value)                              // If old value and current value are not equal
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
/**************************************************************************************************
* Function ReadSensor()
* -------------------------------------------------------------------------------------------------
* Overview: Read sensor.
* Input: None
* Output: None
**************************************************************************************************/

void ReadSensor()
{
    adc_rd = ADC1_Get_Sample( 12 );
    Delay_ms(10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************
* Function InitModules()
* -------------------------------------------------------------------------------------------------
* Overview:
* Input: None
* Output: None
**************************************************************************************************/

void InitModules()
{
    OLED_Init();
    OLED_DrawImage( &methane_bmp, 0, 0 );

    OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
    OLED_WriteText( ppmText, 25, 75 );

    /** initialize ADC */
    ADC1_Init();

    /** pause for 100ms for ADC module stabilization */
    Delay_ms(100);
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
        DisplayMethaneValue( ppm );
        Delay_ms(500);
    }
}

/*************** END OF FUNCTIONS *********************************************/