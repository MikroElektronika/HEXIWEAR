/*
 * Example for Step-up click
 *
 * Date         Apr 2017
 * Author       Djordje Rosic
 *
 * Test configuration KINETIS :
 *  MCU           :        MK64
 *  Dev. Board    :        HEXIWEAR docking station
 *  SW            :        mikroC PRO for ARM v5.0.0
 *
 * Description :
 *
 *    Connect the click to the input power supply (2.5V - 4.5V). This example
 *    shows how to set the desired output voltage, by cycling through a couple
 *    of predefined voltage values.
 *
 ******************************************************************************/
sbit CS_PIN at PTC_PDOR.B4;
/*
 * System Initialization
 */
void systemInit()
{
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
    SPI0_Init_Advanced( 5000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 |
                         _SPI_CFG_FRAME_SIZE_8BITS | _SPI_CFG_CLK_IDLE_LOW |
                         _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST,
                         &_GPIO_Module_SPI0_PC5_7_6);

}
void main() 
{
    systemInit();

    while (1)
    {
        delay_ms(3000);
        //Sets the voltage to VOUTmax, ~5.25 V
        CS_PIN = 0;       //Sets chip select to active
        Spi0_Write(0b01110000);
        Spi0_Write(0b00000000);
        CS_PIN = 1;       //Sets chip select to inactive

        delay_ms(3000);
        //Sets the voltage to VOUTmin, which depends on VIN, but cannot
        //be lower than 2.50 V
        CS_PIN = 0;       //Sets chip select to active
        Spi0_Write(0b01111111);
        Spi0_Write(0b11111111);
        CS_PIN = 1;       //Sets chip select to inactive
        
        delay_ms(3000);
        //Sets the voltage ~4.0 V
        CS_PIN = 0;       //Sets chip select to active
        Spi0_Write(0b01110111);
        Spi0_Write(0b01000000);
        CS_PIN = 1;       //Sets chip select to inactive

        delay_ms(3000);
        //Sets the voltage ~4.5 V
        CS_PIN = 0;       //Sets chip select to active
        Spi0_Write(0b01110100);
        Spi0_Write(0b00011111);
        CS_PIN = 1;       //Sets chip select to inactive
    }
}

/************************************************************ END OF FILE *****/