/****************************************************************************
* Title                 :   8x8 click
* Filename              :   HEXIWEAR_8x8_Click.c
* Author                :   DJ
* Origin Date           :   14/04/2016
* Notes                 :   8x8 Click Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  14/04/16       1.0.0            DJ        Interface Created.
*
*****************************************************************************/
/**
 * @file HEXIWEAR_8x8_Click.c
 * @brief <h2> 8x8 Click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * 8x8 click board.
 */

/**
 * @page LIB_INFO Library Info
 * @date        19 Feb 2016
 * @author      DJ
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 * <h3> Test configuration : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      MK64FN1M0XXX12              </li>
 * <li><b> Dev. Board    </b> :      HEXIWEAR                    </li>
 * <li><b> Oscillator    </b> :      12 MHz external             </li>
 * <li><b> Ext. Modules  </b> :      8x8 Click on mikroBUS 1     </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> 8x8 click example using HEXIWEAR </h3>
 * @par Simple example which demonstrates working with 8x8 click boards.
 *
 * <h3> 8x8 Features </h3>
 * @par 8x8 click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "eight_x_eight_hw.h"
#include "OLED_Driver.h"

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

sbit LED_EIGHT_CS at PTC_PDOR.B4;


/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/
uint8_t text_1[] = "HEXIWEAR ";
uint8_t text_2[] = "NXP ";
uint8_t text_3[] = "MIKROE ";
void main()
{
    OLED_Init();
    OLED_DrawImage( &RGB8x8_bmp, 0, 0 );

    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
    SPI0_Init_Advanced(5000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
                             _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);

    Delay_ms(400);

    led_eight_init();
    
    while(1)
    {
        led_eight_scroll_text(text_1, 10);
        led_eight_scroll_text(text_2, 10);
        led_eight_scroll_text(text_3, 10);
    }
}

/*************** END OF FUNCTIONS *********************************************/