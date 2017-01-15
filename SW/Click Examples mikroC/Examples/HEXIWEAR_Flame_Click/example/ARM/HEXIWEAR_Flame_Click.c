/****************************************************************************
* Title                 :   Flame click
* Filename              :   HEXIWEAR_Flame_Click.c
* Author                :   DJ
* Origin Date           :   14/04/2016
* Notes                 :   Flame Click Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  14/04/16       1.0.0            DJ/ML        Interface Created.
*
*****************************************************************************/
/**
 * @file HEXIWEAR_Flame_Click.c
 * @brief <h2> Flame Click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Flame click board.
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
 * <li><b> Ext. Modules  </b> :      Flame Click on micro BUS 1   </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1     </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Flame click example using HEXIWEAR </h3>
 * @par This example demonstrates usage of the Flame click board. Place it into MikroBus socket 1
 * and observe the ADC values on-screen. Use the potentiometer to determine the threshold for the
 * interrupt, which will indicate the flame presence
 *
 * <h3> Flame Features </h3>
 * @par Flame click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include "OLED_Driver.h"
#include "Resources.h"

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static uint8_t
    isFlameDetected = -1;

sbit FLAME_In at PTB_PDIR.B13;

uint32_t
    adc_result = -1;

static uint8_t
    sampleText[] = "ADC value:";

static uint8_t
    flameLevel[11] = {0};

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/

/**************************************************************************************************
* Function InitModules(void)
* -------------------------------------------------------------------------------------------------
* Overview:
* Input: None
* Output: None
**************************************************************************************************/

void InitModules(void)
{
    GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_13 );

    OLED_Init();
    OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
//    OLED_DrawImage( &hexiwearLogo_bmp, 0, 0 );
    OLED_DrawImage( &fire_off_bmp, 0, 0 );

    ADC0_Init();
}

void main() org 0x1000
{
    InitModules();

    EnableInterrupts();
    NVIC_IntEnable( IVT_INT_PORTB );

    /** enable interrupt at PTB13 to trigger on either of the edges */
    PORTB_PCR13bits.IRQC = 0xB;

    OLED_WriteText( sampleText, 5, 77 );

    while(1)
    {
        switch ( isFlameDetected )
        {
            case 0:
            {
                OLED_DrawImage( &fire_off_bmp, 0, 0 );
                OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
                OLED_WriteText( sampleText, 5, 77 );
                isFlameDetected = -1;
                break;
            }

            case 1:
            {
                OLED_DrawImage( &fire_on_bmp, 0, 0 );
                OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
                OLED_WriteText( sampleText, 5, 77 );
                isFlameDetected = -1;
                break;
            }

            default: {}
        }
        
        adc_result = ADC0_Get_Sample( 12 );
        LongWordToStr( adc_result, flameLevel );
        
        OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
        OLED_WriteText( flameLevel, 40, 77 );
        
        Delay_ms(500);
        
        OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
        OLED_WriteText( flameLevel, 40, 77 );
    }
}

/**
 * Port B IRQ handler
 * detect the PB13 level change to update the current state
 */
void FlameDetect() iv IVT_INT_PORTB ics ICS_AUTO
{
    PORTB_ISFR = 0xFFFFFFFF;

    if ( 1 == FLAME_In )
    {
        isFlameDetected = 1;
    }
    else
    {
        isFlameDetected = 0;
    }
}

/*************** END OF FUNCTIONS *********************************************/