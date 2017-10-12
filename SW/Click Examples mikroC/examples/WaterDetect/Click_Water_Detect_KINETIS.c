/*
Example for Water_Detect Click

    Date          : sep 2017.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0.0

Description :

    This simple example detects water on Water Detect click.

*/

   

uint8_t getINT()          
{
    return PTB_PDIR.B13;
}
     
void systemInit()
{
    UART0_Init(9600);
    GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_13);
}

void Water_Detect_Init()
{
    HAL_WDETECT_gpioInit(&getINT);
}

void Water_Detect_Task()
{
    if (WDETECT_getStatus())
        {
            UART0_Write_text("Water Detected!");
            UART0_Write(13);
            UART0_Write(10);
        }    
}

void main()
{    
    systemInit();
    Water_Detect_Init();

    while( 1 )
    {
            Water_Detect_Task();
    }
}
