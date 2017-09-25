/*
Example for MIC23099 Click

    Date          : Aug 2017.
    Author        : Djordje Rosic

Test configuration KINETIS :
    
    MCU             : MK64
    Dev. Board      : HEXIWEAR
    SW              : mikroC PRO for ARM v5.1.0

Description :

    This example sets the EN pin to high, to enable operation of this click.

*/
sbit MIC23099_EN_PIN at PTC_PDOR.B4;
void systemInit()
{
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
}

void MIC23099_Click_Init()
{
    MIC23099_EN_PIN = 1;
}

void main()
{
    systemInit();
    MIC23099_Click_Init();
}