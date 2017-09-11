/*
Example for Keylock Click

    Date          : jul 2017.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU             : MK64
    Dev. Board      : HEXIWEAR
    SW              : mikroC PRO for ARM v5.1.0

Description :

   This is a simple example of how Keylock click works, depending on the state of the Keylock click the appropriate position will be detected.

*/

#include "stdint.h"

sbit KEYLOCK_STATE_1 at PTB_PDIR.B2;
sbit KEYLOCK_STATE_2 at PTA_PDIR.B10;
sbit KEYLOCK_STATE_3 at PTB_PDIR.B13;

uint8_t state;
char text[20];

void systemInit()
{ 
    UART0_Init(9600);
}

void Keylock_Init()
{   
    GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_2);
    GPIO_Digital_Input(&PTA_PDIR, _GPIO_PINMASK_10);
    GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_13);
}

void Keylock_Task()
{
    state =  KEYLOCK_STATE_1*1 + KEYLOCK_STATE_2*2 + KEYLOCK_STATE_3*3;
    UART0_Write_text("Keylock is in state:");
    IntToStr(state,text) ;
    UART0_Write_Text(text);
    UART0_Write_Text( "\r\n" );
    delay_ms(500);
}

void main()
{
    systemInit();
    Keylock_Init();

    while( 1 )
    {
            Keylock_Task();
    }
}