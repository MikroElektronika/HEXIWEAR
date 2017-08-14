/*
Example for Buck Click

    Date          : jul 2017.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU             : MK64
    Dev. Board      : HEXIWEAR
    SW              : mikroC PRO for ARM v5.1.0

Description :

    A simple example of using Buck click, to set Vout to 3.3V or 5V just set the jumper on the appropriate place on the click.      
    The switching frequency  is regulated by MUX 4634 by setting pins A0 and A1 in following way:      
    A0 = 0 and A1 = 0 for 0.4 MHz	  	 
    A0 = 0 and A1 = 1 for 1.2 MHz	 	 
    A0 = 1 and A1 = 0 for 0.8 MHz	 	 
    A0 = 1 and A1 = 1 for 1.6 MHz	

*/

sbit MUX_A0_PIN at PTB_PDOR.B11;

sbit BUCK_ENABLE_PIN at PTC_PDOR.B4;

sbit MUX_A1_PIN at PTA_PDOR.B10; 

sbit PG_PIN at PTB_PDIR.B13; 

void systemInit()
{
    UART0_Init(9600);
}
void Buck_Init()
{
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
    GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_10);
    GPIO_Digital_Input (&PTB_PDIR, _GPIO_PINMASK_13);
    BUCK_ENABLE_PIN = 1;
    MUX_A0_PIN = 0;
    MUX_A1_PIN = 0;   
}


void Buck_Task()
{
    if (PG_PIN == 1)
    {
        UART0_Write_text("Vout is within the final 8.4% of final regulation voltage");
        UART0_Write_Text( "\r\n" );
        delay_ms(1000);
    }

}

void main()
{
    systemInit();
    Buck_Init();

    while( 1 )
    {
            Buck_Task();
    }
}