/*
Example for C2X20W_Amp Click

    Date          : Aug 2017.
    Author        : Djordje Rosic

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0.0

Description :

    This example demonstrates the use of 2X20W Amp click. It will set the
    volume to an initial value, and then periodically increase or decrease it.

*/
#include "__C2X20AMP_Driver.h"

uint8_t getAD1 ()
{
    return PTA_PDIR.B10;
}

uint8_t getAD2 ()
{
    return PTB_PDIR.B13;
}

void setMT (uint8_t setValue)
{
    PTC_PDOR.B4 = setValue;
}

void systemInit()
{
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
    HAL_C2X20AMP_gpioInit ( &getAD1, &getAD2, &setMT);
    HAL_C2X20AMP_i2cInit ( &I2C0_Start, 0, 0, &I2C0_Write, &I2C0_Read);

    GPIO_Digital_Input( &PTA_PDIR, _GPIO_PINMASK_10);
    GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_13);
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
}

void C2X20W_Amp_Init()
{
    C2X20AMP_init ();
    C2X20AMP_setVolume (0x15);
}

void C2X20W_Amp_Task()
{
    C2X20AMP_decreaseVolume ();
    C2X20AMP_decreaseVolume ();
    C2X20AMP_decreaseVolume ();
    delay_ms (5000);
    C2X20AMP_increaseVolume ();
    C2X20AMP_increaseVolume ();
    C2X20AMP_increaseVolume ();
    delay_ms (5000);
}

void main()
{
    systemInit();
    C2X20W_Amp_Init();

    while( 1 )
    {
        C2X20W_Amp_Task();
    }
}