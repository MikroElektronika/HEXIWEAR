/*
 * Example for MIC24045 click
 *
 * Date         Apr 2017
 * Author       Djordje Rosic
 * Copyright    GNU Public License v2
 *
 * Test configuration Hexiwear :
 *  MCU           :        MK64FN1M0XXX12
 *  Dev. Board    :        Hexiwear docking station
 *  SW            :        mikroC PRO for ARM v4.7.0
 *
 * NOTES:
 *   - Put MIC24045 into slot one on Hexiwear docking station
 *   - Provide 6V to 19V supply to VIN
 *   - Measure output voltage on VOUT
 *   - Do NOT change VOUT while EN pin is set to 1, exept as specified by
 *     the device datasheet
 ******************************************************************************/


/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_driver.h"
#include "OLED_resources.h"
#include "UART_Messaging.h"
#include "mic_24045_click.h"
#include <stdint.h>
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define OLED_X_DISP 7
#define OLED_Y_DISP 25

sbit MIC24045_EN_PIN at PTB_PDOR.B11;
char read_value;
char write_text [15];
uint8_t i;
float write_1;
float read_2;

static void system_init( void )
{

    Delay_ms (100);
// Set SPI1 to the Master Mode, data length is 8-bit, clock = 16 MHz,
    SPI0_Init_Advanced( 16000000, _SPI_CFG_MASTER       |
                      _SPI_CFG_FRAME_SIZE_8BITS       |
                      _SPI_CFG_CLK_IDLE_LOW          |
                      _SPI_CFG_CLK_PHASE_CHG_LEADING  |
                      _SPI_CFG_MSB_FIRST,
                      &_GPIO_Module_SPI0_PC5_7_6);

// I2C Initialization
    I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9  );
    Delay_ms (100);
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
}

void main()
{
    memset (write_text, 0, 15);
    system_init();
    mic_24045_init(0x50);
    Delay_ms (100);

//OLED Initialization
    OLED_init();
    OLED_SetFont( guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 0 );
    OLED_FillScreen( OLED_COLOR_BLACK );
    OLED_WriteText("Initialized", 20, 8 );
    Delay_ms (2000);
    i = 21;
// System will slowly decrement vout in 0.25 V steps
    while (i)
    {
            write_1 = i*0.25;
            mic_24045_write_vout (write_1);
            MIC24045_EN_PIN = 1;     /* Sets EN pin to 1 */
            Delay_ms (1000);
            
            read_2 = mic_24045_read_vout ();
            FloatToStr (read_2, &write_text);
            
            if (read_2 > 1)
               write_text [5] = 0;
            

            if (i == 18)
            {
              //Values between 3.420V and 4.750V are rounded down
               i-=3;
            }
            OLED_FillScreen( OLED_COLOR_BLACK );
            OLED_WriteText("Current voltage:", 1, 8 );
            strcat (write_text, " V");
            OLED_WriteText(write_text, 20, 28 );
            Delay_ms (1000);
            
            
/*
 * While EN pin is high, it is not recommended to change vout,
 * exept as specified in device datasheet, so the pin is pulled low
 * before the next change.
 */
            MIC24045_EN_PIN = 0;
            Delay_ms (1000);
            i--;
    }

}

/************************************************************ END OF FILE *****/