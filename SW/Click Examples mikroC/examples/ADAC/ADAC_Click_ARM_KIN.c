/*
 * Example for ADAC click
 *
 * Date         May 2017
 * Author       Djordje Rosic
 *
 * Test configuration KINETIS :
 *  MCU           :        MK64
 *  Dev. Board    :        HEXIWEAR
 *  SW            :        mikroC PRO for ARM v5.0.0
 *
 * Description :
 *
 * This example initializes the module, and then demonstrates the use of this
 * click as a DAC on channel 3, and then as an ADC on channel 4.
 *
 ******************************************************************************/

#include "__ADAC_Driver.h"

/*
 * System Initialization
 */
void systemInit()
{
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    UART0_Init( 9600 );
    Delay_ms (100);
    UART0_Write_Text ("\r\n------------\r\nInitializing...");

}

void main()
{
    uint8_t * channel;
    uint16_t i;
    char uartText [20];
    uint16_t ADCValue;
    systemInit();
    ADAC_driverInit (0x10, I2C0_Start, I2C0_Write, I2C0_Read );
    Delay_ms (100);


    //Enables the Vref pin
    ADAC_setConfiguration (_ADAC_POWER_REF_CTRL, _ADAC_VREF_ON, _ADAC_NULL);
    UART0_Write_Text ("\r\nInitialized");
    Delay_ms (1000);
    while( 1 )
    {
        UART0_Write_Text ("\r\n\r\nStarting DAC Operation...");
        Delay_ms (1000);
        //Sets the IO3 pin as DAC
        ADAC_setConfiguration (_ADAC_DAC_CONFIG, _ADAC_NULL, _ADAC_IO3);
        //Rises the DAC output on IO3 from 0 to VREF
        for (i = 0; i < 0xFFF; i+=4)
        {
            ADAC_writeDAC (_ADAC_DAC_WRITE | _ADAC_PB_PIN3, i/0x100, i%0x100);
            Delay_ms (10);
        }
        UART0_Write_Text ("\r\nDAC Operation finished\r\n");
        Delay_ms (1000);
        
        
        UART0_Write_Text ("\r\nStarting ADC Operation...");
        Delay_ms (1000);
        //Sets the IO4 pin as ADC
        ADAC_setConfiguration (_ADAC_ADC_CONFIG, _ADAC_NULL, _ADAC_IO4);
        //Sets the ADC sequence repetition to enabled, and adds IO4 to sequence
        ADAC_setConfiguration (_ADAC_ADC_SEQUENCE, _ADAC_SEQUENCE_ON, _ADAC_IO4);
        //Reads the ADC input, and writes it to UART1
        for (i = 0; i < 8; i++)
        {
            ADCValue = ADAC_readADC ( _ADAC_ADC_READ, &channel );
            ShortToStr (channel, uartText);
            UART0_Write_Text ("\r\nRead value from channel");
            UART0_Write_Text (uartText);
            
            
            IntToStr (ADCValue, uartText);
            UART0_Write_Text (": ");
            UART0_Write_Text (uartText);
            Delay_ms (2000);
        }
        
        UART0_Write_Text ("\r\nADC Operation finished");
        Delay_ms (1000);
    }
}

/************************************************************ END OF FILE *****/