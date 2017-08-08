/*
Example for RGB_7_SEG Click

    Date          : avg 2017.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU             : MK64
    Dev. Board      : HEXIWEAR
    SW              : mikroC PRO for ARM v7.1.0

Description :

    This simple example shows all ten numbers in different colors on 7 SEG RGB click.   	 	
    *Note If you want to work with different frequency, functions logicOne and logicZero must be set to match sequence chart from the datasheet 	
    https://download.mikroe.com/documents/datasheets/rgbdigit_datasheet_v4.pdf 	
    Function descriptions:  	 	
    setColor(uint8_t Green, uint8_t Red, uint8_t Blue) sets the color of the  LSB segment of the display      	
    setSevenSegment(uint8_t  Character, uint8_t GreenBrightness, uint8_t RedBrightness, uint8_t BlueBrightness) sets whole character and color

*/

#define ONE     0x06
#define TWO     0x5B
#define THREE   0x4F
#define FOUR    0x66
#define FIVE    0x6D
#define SIX     0x7D
#define SEVEN   0x07
#define EIGHT   0x7F
#define NINE    0x6F
#define ZERO    0x3F

#include "stdint.h"

sbit CHIP_SELECT at PTC_PDOR.B4;
sbit RGB_CONTROL_BIT at  PTA_PDOR.B10;

 void logicOne()

{
       RGB_CONTROL_BIT = 1;
       asm nop
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;             
       asm nop;             
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;             
       asm nop;             
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       asm nop;
}

void logicZero()

{
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop
       asm nop;
       RGB_CONTROL_BIT = 1;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;
       asm nop;
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;             
       asm nop;             
       RGB_CONTROL_BIT = 0;
       asm nop;
       asm nop;             
       asm nop;             
       
}

void setColor(uint8_t Green, uint8_t Red, uint8_t Blue)

{

    int counter;
    uint8_t tmp;

    for ( counter = 7; counter > -1; counter-- )
     
    {
        tmp  =  Green >> counter & 1;
        if (tmp )
        logicOne();
        
        else
        logicZero();

    }

    for ( counter = 7; counter > -1; counter--  )
    
    {
        tmp = Red >> counter & 1;
        if (tmp)
        logicOne();
        
        else
        logicZero();
    }

    for ( counter = 7; counter > -1; counter--  )
     
    {
        tmp =  Blue >> counter & 1;
        if (tmp)
        logicOne();
        
        else
        logicZero();

    }
}

void setSevenSegment(uint8_t  Character, uint8_t GreenBrightness, uint8_t RedBrightness, uint8_t BlueBrightness)

{
   
    uint8_t temp;
    uint8_t cntr;

    for ( cntr = 0; cntr < 8; cntr++ )
      
    {
       
        temp =  Character >> cntr & 1;
        
        if (temp)
        setColor(GreenBrightness,RedBrightness,BlueBrightness);
        
        else
        setColor(0,0,0);

    }

}
void systemInit()
{
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_14 );
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_10 );
}
void RGB_7_SEG_Init()
{
    RGB_CONTROL_BIT = 0;
    CHIP_SELECT  = 0;

}

void RGB_7_SEG_Task()
{
    setSevenSegment(ONE,40,0,0);

    Delay_ms(1000);

    setSevenSegment(TWO,0,40,0);

    Delay_ms(1000);

    setSevenSegment(THREE,0,0,40);

    Delay_ms(1000);

    setSevenSegment(FOUR,40,0,40);

    Delay_ms(1000);

    setSevenSegment(FIVE,0,40,40);

    Delay_ms(1000);
    
    setSevenSegment(SIX,40,40,0);

    Delay_ms(1000);

    setSevenSegment(SEVEN,40,40,20);

    Delay_ms(1000);
 
    setSevenSegment(EIGHT,40,15,31);

    Delay_ms(1000);

    setSevenSegment(NINE,20,10,30);

    Delay_ms(1000);
    
    setSevenSegment(ZERO,40,40,40);

    Delay_ms(1000);       

    RGB_CONTROL_BIT = 0;
}

void main()
{
    systemInit();
    RGB_7_SEG_Init();

    while( 1 )
    {
        RGB_7_SEG_Task();   
    }
}