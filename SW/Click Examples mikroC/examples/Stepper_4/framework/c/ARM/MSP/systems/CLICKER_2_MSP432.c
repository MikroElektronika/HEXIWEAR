#include "MIKROBUS_framework.h"

#ifdef CLICKER_2_MSP432
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
    if( bus == MIKROBUS1 )
    {
        switch( pin ) 
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P6OUT, _GPIO_PINMASK_0); else GPIO_Digital_Output(&DIO_P6IN, _GPIO_PINMASK_0); break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P5OUT, _GPIO_PINMASK_6); else GPIO_Digital_Output(&DIO_P5IN, _GPIO_PINMASK_6); break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P5OUT, _GPIO_PINMASK_0); else GPIO_Digital_Output(&DIO_P5IN, _GPIO_PINMASK_0); break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P1OUT, _GPIO_PINMASK_5); else GPIO_Digital_Output(&DIO_P1IN, _GPIO_PINMASK_5); break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P1OUT, _GPIO_PINMASK_7); else GPIO_Digital_Output(&DIO_P1IN, _GPIO_PINMASK_7); break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P1OUT, _GPIO_PINMASK_6); else GPIO_Digital_Output(&DIO_P1IN, _GPIO_PINMASK_6); break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P2OUT, _GPIO_PINMASK_7); else GPIO_Digital_Output(&DIO_P2IN, _GPIO_PINMASK_7); break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P2OUT, _GPIO_PINMASK_4); else GPIO_Digital_Output(&DIO_P2IN, _GPIO_PINMASK_4); break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P3OUT, _GPIO_PINMASK_2); else GPIO_Digital_Output(&DIO_P3IN, _GPIO_PINMASK_2); break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P3OUT, _GPIO_PINMASK_3); else GPIO_Digital_Output(&DIO_P3IN, _GPIO_PINMASK_3); break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P6OUT, _GPIO_PINMASK_5); else GPIO_Digital_Output(&DIO_P6IN, _GPIO_PINMASK_5); break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P6OUT, _GPIO_PINMASK_4); else GPIO_Digital_Output(&DIO_P6IN, _GPIO_PINMASK_4); break;
            default : break; 
        }
    }
    if( bus == MIKROBUS2 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P4OUT, _GPIO_PINMASK_3); else GPIO_Digital_Output(&DIO_P4IN, _GPIO_PINMASK_3); break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P6OUT, _GPIO_PINMASK_7); else GPIO_Digital_Output(&DIO_P6IN, _GPIO_PINMASK_7); break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P5OUT, _GPIO_PINMASK_2); else GPIO_Digital_Output(&DIO_P5IN, _GPIO_PINMASK_2); break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P1OUT, _GPIO_PINMASK_5); else GPIO_Digital_Output(&DIO_P1IN, _GPIO_PINMASK_5); break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P1OUT, _GPIO_PINMASK_7); else GPIO_Digital_Output(&DIO_P1IN, _GPIO_PINMASK_7); break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P1OUT, _GPIO_PINMASK_6); else GPIO_Digital_Output(&DIO_P1IN, _GPIO_PINMASK_6); break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P2OUT, _GPIO_PINMASK_6); else GPIO_Digital_Output(&DIO_P2IN, _GPIO_PINMASK_6); break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P6OUT, _GPIO_PINMASK_6); else GPIO_Digital_Output(&DIO_P6IN, _GPIO_PINMASK_6); break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P2OUT, _GPIO_PINMASK_2); else GPIO_Digital_Output(&DIO_P2IN, _GPIO_PINMASK_2); break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P2OUT, _GPIO_PINMASK_3); else GPIO_Digital_Output(&DIO_P2IN, _GPIO_PINMASK_3); break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P6OUT, _GPIO_PINMASK_5); else GPIO_Digital_Output(&DIO_P6IN, _GPIO_PINMASK_5); break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&DIO_P6OUT, _GPIO_PINMASK_4); else GPIO_Digital_Output(&DIO_P6IN, _GPIO_PINMASK_4); break;
            default : break;
        }
    }
}

#ifdef __SPI_CLICK
void MIKROBUS1_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI5_Init_Advanced( (int)cfg[0], (int)cfg[1], (int)cfg[2], (int)cfg[3], 
                        (int)cfg[4], (int)cfg[5], (int)cfg[6],  );
    fCall( SPI5_Write, SPI5_Read );
};
void MIKROBUS2_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI5_Init_Advanced( (int)cfg[0], (int)cfg[1], (int)cfg[2], (int)cfg[3], 
                        (int)cfg[4], (int)cfg[5], (int)cfg[6],  );
    fCall( SPI5_Write, SPI5_Read );
};
#endif
#ifdef __I2C_CLICK
void MIKROBUS1_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2C1_Init( cfg[0], cfg[1], );   
    fCall( 0, 0, 0, I2C2_Write, I2C2_Read );
};
void MIKROBUS2_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2C1_Init( cfg[0], cfg[1], );
    fCall( 0, 0, 0, I2C2_Write, I2C2_Read );
};
#endif
#ifdef __UART_CLICK
void MIKROBUS1_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART1_Init( cfg[0] );
    fCall( UART1_Write, UART1_Read, UART1_Data_Ready );
};
void MIKROBUS2_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART5_Init( cfg[0] );
    fCall( UART5_Write, UART5_Read, UART5_Data_Ready );
};
#endif
#ifdef PLD_AN_PIN
char MIKROBUS1_getAN()          
{
    return DIO_P6IN.B0;
}
void MIKROBUS1_setAN(char set)         
{
    DIO_P6OUT.B0 = set;
}
char MIKROBUS2_getAN()          
{
    return DIO_P4IN.B3;
}
void MIKROBUS2_setAN(char set)         
{
    DIO_P4OUT.B3 = set;
}
#endif
#ifdef PLD_RST_PIN
char MIKROBUS1_getRST()         
{
    return DIO_P5IN.B6;
}
void MIKROBUS1_setRST(char set)        
{
    DIO_P5OUT.B6 = set;
}
char MIKROBUS2_getRST()         
{
    return DIO_P6IN.B7;
}
void MIKROBUS2_setRST(char set)        
{
    DIO_P6OUT.B7 = set;
}
#endif
#ifdef PLD_CS_PIN
char MIKROBUS1_getCS()          
{
    return DIO_P5IN.B0;
}
void MIKROBUS1_setCS(char set)         
{
    DIO_P5OUT.B0 = set;
}
char MIKROBUS2_getCS()          
{
    return DIO_P5IN.B2;
}
void MIKROBUS2_setCS(char set)         
{
    DIO_P5OUT.B2 = set;
}
#endif
#ifdef PLD_SCK_PIN
char MIKROBUS1_getSCK()          
{
    return DIO_P1IN.B5;
}
void MIKROBUS1_setSCK(char set)         
{
    DIO_P1OUT.B5 = set;
}
char MIKROBUS2_getSCK()          
{
    return DIO_P1IN.B5;
}
void MIKROBUS2_setSCK(char set)         
{
    DIO_P1OUT.B5 = set;
}
#endif
#ifdef PLD_MISO_PIN
char MIKROBUS1_getMISO()         
{
    return DIO_P1IN.B7;
}
void MIKROBUS1_setMISO(char set)        
{
    DIO_P1OUT.B7 = set;
}
char MIKROBUS2_getMISO()         
{
    return DIO_P1IN.B7;
}
void MIKROBUS2_setMISO(char set)        
{
    DIO_P1OUT.B7 = set;
}
#endif
#ifdef PLD_MOSI_PIN
char MIKROBUS1_getMOSI()          
{
    return DIO_P1IN.B6;
}
void MIKROBUS1_setMOSI(char set)         
{
    DIO_P1OUT.B6 = set;
}
char MIKROBUS2_getMOSI()          
{
    return DIO_P1IN.B6;
}
void MIKROBUS2_setMOSI(char set)         
{
    DIO_P1OUT.B6 = set;
}
#endif
#ifdef PLD_PWM_PIN
char MIKROBUS1_getPWM()         
{
    return DIO_P2IN.B7;
}
void MIKROBUS1_setPWM(char set)        
{
    DIO_P2OUT.B7 = set;
}
char MIKROBUS2_getPWM()         
{
    return DIO_P2IN.B6;
}
void MIKROBUS2_setPWM(char set)        
{
    DIO_P2OUT.B6 = set;
}
#endif
#ifdef PLD_INT_PIN
char MIKROBUS1_getINT()         
{
    return DIO_P2IN.B4;
}
void MIKROBUS1_setINT(char set)        
{
    DIO_P2OUT.B4 = set;
}
char MIKROBUS2_getINT()         
{
    return DIO_P6IN.B6;
}
void MIKROBUS2_setINT(char set)        
{
    DIO_P6OUT.B6 = set;
}
#endif
#ifdef PLD_RX_PIN
char MIKROBUS1_getRX()         
{
    return DIO_P3IN.B2;
}
void MIKROBUS1_setRX(char set)        
{
    DIO_P3OUT.B2 = set;
}
char MIKROBUS2_getRX()         
{
    return DIO_P2IN.B2;
}
void MIKROBUS2_setRX(char set)        
{
    DIO_P2OUT.B2 = set;
}
#endif
#ifdef PLD_TX_PIN
char MIKROBUS1_getTX()         
{
    return DIO_P3IN.B3;
}
void MIKROBUS1_setTX(char set)        
{
    DIO_P3OUT.B3 = set;
}
char MIKROBUS2_getTX()         
{
    return DIO_P2IN.B3;
}
void MIKROBUS2_setTX(char set)        
{
    DIO_P2OUT.B3 = set;
}
#endif
#ifdef PLD_SCL_PIN
char MIKROBUS1_getSCL()         
{
    return DIO_P6IN.B5;
}
void MIKROBUS1_setSCL(char set)        
{
    DIO_P6OUT.B5 = set;
}
char MIKROBUS2_getSCL()         
{
    return DIO_P6IN.B5;
}
void MIKROBUS2_setSCL(char set)        
{
    DIO_P6OUT.B5 = set;
}
#endif
#ifdef PLD_SDA_PIN
char MIKROBUS1_getSDA()         
{
    return DIO_P6IN.B4;
}
void MIKROBUS1_setSDA(char set)        
{
    DIO_P6OUT.B4 = set;
}
char MIKROBUS2_getSDA()         
{
    return DIO_P6IN.B4;
}
void MIKROBUS2_setSDA(char set)        
{
    DIO_P6OUT.B4 = set;
}
#endif
#endif