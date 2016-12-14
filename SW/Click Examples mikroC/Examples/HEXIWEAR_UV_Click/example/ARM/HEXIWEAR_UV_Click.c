/****************************************************************************
* Title                 :   UV click
* Filename              :   HEXIWEAR_UV_Click.c
* Author                :   DJ
* Origin Date           :   14/04/2016
* Notes                 :   UV Click Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  14/04/16       1.0.0            DJ/ML        Interface Created.
*
*****************************************************************************/
/**
 * @file HEXIWEAR_UV_Click.c
 * @brief <h2> UV Click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * UV click board.
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
 * <li><b> Ext. Modules  </b> :      UV Click on mikroBUS 2       </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1     </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> UV click example using HEXIWEAR </h3>
 * @par This example demonstrates usage of the UV click board. Place UV click into
 * MikroBus socket 2 and observe the value in [mV] proportional to the UV light exposure
 *
 * <h3> UV Features </h3>
 * @par UV click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include "OLED_Driver.h"

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

// UV Click connections
sbit UV_Enable  at PTB_PDOR.B19;
sbit UV_Input   at PTB_PDOR.B3;

static uint8_t
    uvText[] = "UV ~ ",
    uvUnit[] = "mV";

static uint8_t
    uvLevel[6] = {0};

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static uint16_t GetADC();
static void ProcessValue( uint16_t valueTemp );
static void InitModules();

/******************************************************************************
* Public Function Definitions
*******************************************************************************/
void main() org 0x1000
{
    uint16_t
        measurement = 0;

    // init hardware
    InitModules();

    while(1)
    {
        // get ADC result
        measurement = GetADC();

        // display UV sensor values on-screen
        ProcessValue( measurement );

        // wait
        Delay_ms(500);
    }
}

/******************************************************************************
* Static Functions' Definitions
*******************************************************************************/

/**************************************************************************************************
* Function InitModules(void)
* -------------------------------------------------------------------------------------------------
* Overview: initialize the peripherals
* Input: None
* Output: None
**************************************************************************************************/
static void InitModules()
{
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_19 );
                             
    OLED_Init();
    OLED_DrawImage( &uv_bmp, 0, 0 );

    OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
    OLED_WriteText( uvText, 20, 75 );
    OLED_WriteText( uvUnit, 72, 75 );

    /** initialize ADC */
    ADC0_Init();

    Delay_ms(100);

    /** enable UV click */
    UV_Enable  = 1;
}

/**************************************************************************************************
* Get ADC values(void)
* -------------------------------------------------------------------------------------------------
* Overview: get value from ADC
* Input: None
* Output: None
**************************************************************************************************/
static uint16_t GetADC()
{
    uint32_t
        i,
        adcVal = 0,
        avrg   = 0;

    for ( i = 0; i < 16; i++ )
    {
        adcVal = ADC0_Get_Sample( 13 );
        avrg  += adcVal;
    }

    return ( avrg >> 4 );
}

/**************************************************************************************************
* Process and display current value
* -------------------------------------------------------------------------------------------------
* Overview: display the value if it's within reasonable limits
* Input: valueTemp
* Output: None
**************************************************************************************************/
static void ProcessValue( uint16_t valueTemp )
{
    float
        UV_val;

    if ((valueTemp > 1100) && (valueTemp < 4095))
    {
        // clear the previous value
        OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
        OLED_WriteText( uvLevel, 42, 75 );

        // Vref = 3300 mV, 12-bit res = 4096 lvls
        UV_val = valueTemp * 3300.0 / 4096.0;
        WordToStr( (uint16_t)UV_val, uvLevel );
        OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
        OLED_WriteText( uvLevel, 42, 75 );
    }
    else
    {
        UV_val = -1;
    }
}

/*************** END OF FUNCTIONS *********************************************/