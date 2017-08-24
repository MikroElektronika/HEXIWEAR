#include "MIKROBUS_framework.h"

#ifdef CLICKER_2_CEC1702
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
    if( bus == MIKROBUS1 )
    {
        switch( pin ) 
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_200_207, _GPIO_PINMASK_0); else GPIO_Digital_Output(&GPIO_PORT_200_207, _GPIO_PINMASK_0); break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_040_047, _GPIO_PINMASK_5); else GPIO_Digital_Output(&GPIO_PORT_040_047, _GPIO_PINMASK_5); break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_000_007, _GPIO_PINMASK_3); else GPIO_Digital_Output(&GPIO_PORT_000_007, _GPIO_PINMASK_3); break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_030_037, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORT_030_037, _GPIO_PINMASK_4); break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_030_037, _GPIO_PINMASK_6); else GPIO_Digital_Output(&GPIO_PORT_030_037, _GPIO_PINMASK_6); break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_000_007, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORT_000_007, _GPIO_PINMASK_4); break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_130_137, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORT_130_137, _GPIO_PINMASK_4); break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_030_037, _GPIO_PINMASK_0); else GPIO_Digital_Output(&GPIO_PORT_030_037, _GPIO_PINMASK_0); break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_100_107, _GPIO_PINMASK_5); else GPIO_Digital_Output(&GPIO_PORT_100_107, _GPIO_PINMASK_5); break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_100_107, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORT_100_107, _GPIO_PINMASK_4); break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_010_017, _GPIO_PINMASK_0); else GPIO_Digital_Output(&GPIO_PORT_010_017, _GPIO_PINMASK_0); break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_000_007, _GPIO_PINMASK_7); else GPIO_Digital_Output(&GPIO_PORT_000_007, _GPIO_PINMASK_7); break;
            default : break; 
        }
    }
    if( bus == MIKROBUS2 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_200_207, _GPIO_PINMASK_1); else GPIO_Digital_Output(&GPIO_PORT_200_207, _GPIO_PINMASK_1); break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_040_047, _GPIO_PINMASK_5); else GPIO_Digital_Output(&GPIO_PORT_040_047, _GPIO_PINMASK_5); break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_000_007, _GPIO_PINMASK_3); else GPIO_Digital_Output(&GPIO_PORT_000_007, _GPIO_PINMASK_3); break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_030_037, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORT_030_037, _GPIO_PINMASK_4); break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_030_037, _GPIO_PINMASK_6); else GPIO_Digital_Output(&GPIO_PORT_030_037, _GPIO_PINMASK_6); break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_000_007, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORT_000_007, _GPIO_PINMASK_4); break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_000_007, _GPIO_PINMASK_2); else GPIO_Digital_Output(&GPIO_PORT_000_007, _GPIO_PINMASK_2); break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_110_117, _GPIO_PINMASK_2); else GPIO_Digital_Output(&GPIO_PORT_110_117, _GPIO_PINMASK_2); break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_100_107, _GPIO_PINMASK_5); else GPIO_Digital_Output(&GPIO_PORT_100_107, _GPIO_PINMASK_5); break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_100_107, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORT_100_107, _GPIO_PINMASK_4); break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_010_017, _GPIO_PINMASK_0); else GPIO_Digital_Output(&GPIO_PORT_010_017, _GPIO_PINMASK_0); break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_000_007, _GPIO_PINMASK_7); else GPIO_Digital_Output(&GPIO_PORT_000_007, _GPIO_PINMASK_7); break;
            default : break;
        }
    }
} 
/*
#ifdef __SPI_CLICK
void MIKROBUS1_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI0_Init_Advanced( (unsigned long)cfg[0], (unsigned int)cfg[1], 
                        (unsigned char)cfg[2] );
    fCall( SPI0_Write, SPI0_Read );
}
void MIKROBUS2_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI0_Init_Advanced( (unsigned long)cfg[0], (unsigned int)cfg[1], 
                        (unsigned char)cfg[2] );
    fCall( SPI0_Write, SPI0_Read );
}
#endif
#ifdef __I2C_CLICK
void MIKROBUS1_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2C0_Init_Advanced( cfg[0], &_GPIO_MODULE_I2C_port03_P010_P007 ); 
    fCall( I2C0_Start, 0, 0, I2C0_Write, I2C0_Read );  
};
void MIKROBUS2_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2C0_Init_Advanced( cfg[0], &_GPIO_MODULE_I2C_port03_P010_P007 ); 
    fCall( I2C0_Start, 0, 0, I2C0_Write, I2C0_Read ); 
};
#endif

 
#ifdef __UART_CLICK
void MIKROBUS1_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART1_Init( cfg[0], cfg[1], cfg[2], cfg[3] );
    fCall( UART1_Write, UART1_Read, UART1_Data_Ready );
};
void MIKROBUS2_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART1_Init( cfg[0], cfg[1], cfg[2], cfg[3] );
    fCall( UART1_Write, UART5_Read, UART5_Data_Ready );
};
#endif
#ifdef PLD_AN_PIN
char MIKROBUS1_getAN()          
{
    return GPIO_INPUT_200_207.B0;
}
void MIKROBUS1_setAN(char set)         
{
    GPIO_OUTPUT_200_207.B0 = set;
}
char MIKROBUS2_getAN()          
{
    return GPIO_INPUT_200_207.B1;
}
void MIKROBUS2_setAN(char set)
{
    GPIO_OUTPUT_200_207.B1 = set;
}
#endif
#ifdef PLD_RST_PIN
char MIKROBUS1_getRST()         
{
    return GPIO_INPUT_040_047.B5;
}
void MIKROBUS1_setRST(char set)        
{
    GPIO_OUTPUT_040_047.B5 = set;
}
char MIKROBUS2_getRST()         
{
    return GPIO_INPUT_040_047.B7;
}
void MIKROBUS2_setRST(char set)        
{
    GPIO_OUTPUT_040_047.B7 = set;
}
#endif
#ifdef PLD_CS_PIN
char MIKROBUS1_getCS()          
{
    return GPIO_INPUT_000_007.B3;
}
void MIKROBUS1_setCS(char set)         
{
    GPIO_OUTPUT_000_007.B3 = set;
}
char MIKROBUS2_getCS()          
{
    return GPIO_INPUT_160_167.B5;
}
void MIKROBUS2_setCS(char set)         
{
    GPIO_OUTPUT_160_167.B5 = set;
}
#endif
#ifdef PLD_SCK_PIN
char MIKROBUS1_getSCK()          
{
    return GPIO_INPUT_030_037.B4;
}
void MIKROBUS1_setSCK(char set)         
{
    GPIO_OUTPUT_030_037.B4 = set;
}
char MIKROBUS2_getSCK()          
{
    return GPIO_INPUT_030_037.B4;
}
void MIKROBUS2_setSCK(char set)         
{
    GPIO_OUTPUT_030_037.B4 = set;
}
#endif
#ifdef PLD_MISO_PIN
char MIKROBUS1_getMISO()         
{
    return GPIO_INPUT_030_037.B6;
}
void MIKROBUS1_setMISO(char set)        
{
    GPIO_OUTPUT_030_037.B6 = set;
}
char MIKROBUS2_getMISO()         
{
    return GPIO_INPUT_030_037.B6;
}
void MIKROBUS2_setMISO(char set)        
{
    GPIO_OUTPUT_030_037.B6 = set;
}
#endif
#ifdef PLD_MOSI_PIN
char MIKROBUS1_getMOSI()          
{
    return GPIO_INPUT_000_007.B4;
}
void MIKROBUS1_setMOSI(char set)         
{
    GPIO_OUTPUT_000_007.B4 = set;
}
char MIKROBUS2_getMOSI()          
{
    return GPIO_INPUT_000_007.B4;
}
void MIKROBUS2_setMOSI(char set)         
{
    GPIO_OUTPUT_000_007.B4 = set;
}
#endif
#ifdef PLD_PWM_PIN
char MIKROBUS1_getPWM()         
{
    return GPIO_INPUT_130_137.B4;
}
void MIKROBUS1_setPWM(char set)        
{
    GPIO_OUTPUT_130_137.B4 = set;
}
char MIKROBUS2_getPWM()         
{
    return GPIO_INPUT_000_007.B2;
}
void MIKROBUS2_setPWM(char set)        
{
    GPIO_OUTPUT_000_007.B2 = set;
}
#endif
#ifdef PLD_INT_PIN
char MIKROBUS1_getINT()         
{
    return GPIO_INPUT_030_037.B0;
}
void MIKROBUS1_setINT(char set)        
{
    GPIO_OUTPUT_030_037.B0 = set;
}
char MIKROBUS2_getINT()         
{
    return GPIO_INPUT_110_117.B2;
}
void MIKROBUS2_setINT(char set)        
{
    GPIO_OUTPUT_110_117.B2 = set;
}
#endif
#ifdef PLD_RX_PIN
char MIKROBUS1_getRX()         
{
    return GPIO_INPUT_100_107.B5;
}
void MIKROBUS1_setRX(char set)        
{
    GPIO_OUTPUT_100_107.B5 = set;
}
char MIKROBUS2_getRX()         
{
    return GPIO_INPUT_100_107.B5;
}
void MIKROBUS2_setRX(char set)        
{
    GPIO_OUTPUT_100_107.B5 = set;
}
#endif
#ifdef PLD_TX_PIN
char MIKROBUS1_getTX()         
{
    return GPIO_INPUT_100_107.B4;
}
void MIKROBUS1_setTX(char set)        
{
    GPIO_OUTPUT_100_107.B4 = set;
}
char MIKROBUS2_getTX()         
{
    return GPIO_INPUT_100_107.B4;
}
void MIKROBUS2_setTX(char set)        
{
    GPIO_OUTPUT_100_107.B4 = set;
}
#endif
#ifdef PLD_SCL_PIN
char MIKROBUS1_getSCL()         
{
    return GPIO_INPUT_010_017.B0;
}
void MIKROBUS1_setSCL(char set)        
{
    GPIO_OUTPUT_010_017.B0 = set;
}
char MIKROBUS2_getSCL()         
{
    return GPIO_INPUT_010_017.B0;
}
void MIKROBUS2_setSCL(char set)        
{
    GPIO_OUTPUT_010_017.B0 = set;
}
#endif
#ifdef PLD_SDA_PIN
char MIKROBUS1_getSDA()         
{
    return GPIO_INPUT_000_007.B7;
}
void MIKROBUS1_setSDA(char set)        
{
    GPIO_OUTPUT_000_007.B7 = set;
}
char MIKROBUS2_getSDA()         
{
    return GPIO_INPUT_000_007.B7;
}
void MIKROBUS2_setSDA(char set)        
{
    GPIO_OUTPUT_000_007.B7 = set;
}
#endif */
#endif