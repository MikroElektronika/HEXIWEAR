#include "MIKROBUS_framework.h"

#ifdef HEXIWEAR_DOCKING
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
    if( bus == MIKROBUS1 )
    {
        switch( pin ) 
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_2);  else GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_2);  break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_11); else GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11); break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);  break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_5);  break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_7);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_7);  break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_6);  break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTA_PDIR, _GPIO_PINMASK_10); else GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_10); break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_13); else GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_13); break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTD_PDIR, _GPIO_PINMASK_2);  else GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_2);  break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTD_PDIR, _GPIO_PINMASK_3);  else GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_3);  break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTD_PDIR, _GPIO_PINMASK_8);  else GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_8);  break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTD_PDIR, _GPIO_PINMASK_9);  else GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_9);  break;
            default : break; 
        }
    }
    if( bus == MIKROBUS2 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_3);  else GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_3);  break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_19); else GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_19); break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_3);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_3);  break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_5);  break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_7);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_7);  break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_6);  break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTA_PDIR, _GPIO_PINMASK_11); else GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_11); break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_8);  else GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_8);  break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_16); else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_16); break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_17); else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_17); break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTD_PDIR, _GPIO_PINMASK_8);  else GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_8);  break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTD_PDIR, _GPIO_PINMASK_9);  else GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_9);  break;
            default : break;
        }
    }
    if( bus == MIKROBUS3 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_6);  break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_10); else GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_10); break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_2);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_2);  break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_5);  break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_7);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_7);  break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_6);  break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTA_PDIR, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_4);  break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_7);  else GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_7);  break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_16); else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_16); break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTC_PDIR, _GPIO_PINMASK_17); else GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_17); break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTD_PDIR, _GPIO_PINMASK_8);  else GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_8);  break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&PTD_PDIR, _GPIO_PINMASK_9);  else GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_9);  break;
            default : break;
        }
    }
}

#ifdef __SPI_CLICK
void MIKROBUS1_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI0_Init_Advanced( cfg[0], cfg[1], &_GPIO_Module_SPI0_PC5_7_6 );
    fCall( SPI0_Write, SPI0_Read );
}
void MIKROBUS2_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI0_Init_Advanced( cfg[0], cfg[1], &_GPIO_Module_SPI0_PC5_7_6 );
    fCall( SPI0_Write, SPI0_Read );
}
void MIKROBUS3_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI0_Init_Advanced( cfg[0], cfg[1], &_GPIO_Module_SPI0_PC5_7_6 );
    fCall( SPI0_Write, SPI0_Read );
}
#endif
#ifdef __I2C_CLICK
void MIKROBUS1_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    fCall( I2C0_Start, 0, 0, I2C0_Write, I2C0_Read );
    I2C0_Init( cfg[0], &_GPIO_Module_I2C0_PD8_9 );
}
void MIKROBUS2_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    fCall( I2C0_Start, 0, 0, I2C0_Write, I2C0_Read );
    I2C0_Init( cfg[0], &_GPIO_Module_I2C0_PD8_9 );
}
void MIKROBUS3_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    fCall( I2C0_Start, 0, 0, I2C0_Write, I2C0_Read );
    I2C0_Init( cfg[0], &_GPIO_Module_I2C0_PD8_9 );
}
#endif
#ifdef __UART_CLICK
void MIKROBUS1_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    fCall( UART2_Write, UART2_Read, UART2_Data_Ready );
    UART2_Init( cfg[0], cfg[1], cfg[2], cfg[3], &_GPIO_Module_UART2_PD3_2 );
}
void MIKROBUS2_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    fCall( UART0_Write, UART0_Read, UART0_Data_Ready );
    UART0_Init( cfg[0], cfg[1], cfg[2], cfg[3], &_GPIO_Module_UART0_PB16_17 );
}
void MIKROBUS3_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    fCall( UART0_Write, UART0_Read, UART0_Data_Ready );
    UART0_Init( cfg[0], cfg[1], cfg[2], cfg[3], &_GPIO_Module_UART0_PB16_17 );
}
#endif
#ifdef PLD_AN_PIN
char MIKROBUS1_getAN()          
{
    return PTB_PDIR.B2;
}
void MIKROBUS1_setAN(char set)         
{
    PTB_PDOR.B2 = set;
}
char MIKROBUS2_getAN()          
{
    return PTB_PDIR.B3;
}
void MIKROBUS2_setAN(char set)         
{
    PTB_PDOR.B3 = set;
}
char MIKROBUS3_getAN()          
{
    return PTB_PDIR.B6;
}
void MIKROBUS3_setAN(char set)         
{
    PTB_PDOR.B6 = set;
}
#endif
#ifdef PLD_RST_PIN
char MIKROBUS1_getRST()         
{
    return PTB_PDIR.B11;
}
void MIKROBUS1_setRST(char set)        
{
    PTB_PDOR.B11 = set;
}
char MIKROBUS2_getRST()         
{
    return PTB_PDIR.B19;
}
void MIKROBUS2_setRST(char set)        
{
    PTB_PDOR.B19 = set;
}
char MIKROBUS3_getRST()         
{
    return PTB_PDIR.B10;
}
void MIKROBUS3_setRST(char set)        
{
    PTB_PDOR.B10 = set;
}
#endif
#ifdef PLD_CS_PIN
char MIKROBUS1_getCS()          
{
    return PTC_PDIR.B4;
}
void MIKROBUS1_setCS(char set)         
{
    PTC_PDOR.B4 = set;
}
char MIKROBUS2_getCS()          
{
    return PTC_PDIR.B3;
}
void MIKROBUS2_setCS(char set)         
{
    PTC_PDOR.B3 = set;
}
char MIKROBUS3_getCS()          
{
    return PTC_PDIR.B2;
}
void MIKROBUS3_setCS(char set)         
{
    PTC_PDOR.B2 = set;
}
#endif
#ifdef PLD_SCK_PIN
char MIKROBUS1_getSCK()          
{
    return PTC_PDIR.B5;
}
void MIKROBUS1_setSCK(char set)         
{
    PTC_PDOR.B5 = set;
}
char MIKROBUS2_getSCK()          
{
    return PTC_PDIR.B5;
}
void MIKROBUS2_setSCK(char set)         
{
    PTC_PDOR.B5 = set;
}
char MIKROBUS3_getSCK()          
{
    return PTC_PDIR.B5;
}
void MIKROBUS3_setSCK(char set)         
{
    PTC_PDOR.B5 = set;
}
#endif
#ifdef PLD_MISO_PIN
char MIKROBUS1_getMISO()         
{
    return PTC_PDIR.B7;
}
void MIKROBUS1_setMISO(char set)        
{
    PTC_PDOR.B7 = set;
}
char MIKROBUS2_getMISO()         
{
    return PTC_PDIR.B7;
}
void MIKROBUS2_setMISO(char set)        
{
    PTC_PDOR.B7 = set;
}
char MIKROBUS3_getMISO()         
{
    return PTC_PDIR.B7;
}
void MIKROBUS3_setMISO(char set)        
{
    PTC_PDOR.B7 = set;
}
#endif
#ifdef PLD_MOSI_PIN
char MIKROBUS1_getMOSI()          
{
    return PTC_PDIR.B6;
}
void MIKROBUS1_setMOSI(char set)         
{
    PTC_PDOR.B6 = set;
}
char MIKROBUS2_getMOSI()          
{
    return PTC_PDIR.B6;
}
void MIKROBUS2_setMOSI(char set)         
{
    PTC_PDOR.B6 = set;
}
char MIKROBUS3_getMOSI()          
{
    return PTC_PDIR.B6;
}
void MIKROBUS3_setMOSI(char set)         
{
    PTC_PDOR.B6 = set;
}
#endif
#ifdef PLD_PWM_PIN
char MIKROBUS1_getPWM()         
{
    return PTA_PDIR.B10;
}
void MIKROBUS1_setPWM(char set)        
{
    PTA_PDOR.B10 = set;
}
char MIKROBUS2_getPWM()         
{
    return PTA_PDIR.B11;
}
void MIKROBUS2_setPWM(char set)        
{
    PTA_PDOR.B11 = set;
}
char MIKROBUS3_getPWM()         
{
    return PTA_PDIR.B4;
}
void MIKROBUS3_setPWM(char set)        
{
    PTA_PDOR.B4 = set;
}
#endif
#ifdef PLD_INT_PIN
char MIKROBUS1_getINT()         
{
    return PTB_PDIR.B13;
}
void MIKROBUS1_setINT(char set)        
{
    PTB_PDOR.B13 = set;
}
char MIKROBUS2_getINT()         
{
    return PTB_PDIR.B8;
}
void MIKROBUS2_setINT(char set)        
{
    PTB_PDOR.B8 = set;
}
char MIKROBUS3_getINT()         
{
    return PTB_PDIR.B7;
}
void MIKROBUS3_setINT(char set)        
{
    PTB_PDOR.B7 = set;
}
#endif
#ifdef PLD_RX_PIN
char MIKROBUS1_getRX()         
{
    return PTD_PDIR.B2;
}
void MIKROBUS1_setRX(char set)        
{
    PTD_PDOR.B2 = set;
}
char MIKROBUS2_getRX()         
{
    return PTC_PDIR.B16;
}
void MIKROBUS2_setRX(char set)        
{
    PTC_PDOR.B16 = set;
}
char MIKROBUS3_getRX()         
{
    return PTC_PDIR.B16;
}
void MIKROBUS3_setRX(char set)        
{
    PTC_PDOR.B16 = set;
}
#endif
#ifdef PLD_TX_PIN
char MIKROBUS1_getTX()         
{
    return PTD_PDIR.B3;
}
void MIKROBUS1_setTX(char set)        
{
    PTD_PDOR.B3 = set;
}
char MIKROBUS2_getTX()         
{
    return PTC_PDIR.B17;
}
void MIKROBUS2_setTX(char set)        
{
    PTC_PDOR.B17 = set;
}
char MIKROBUS3_getTX()         
{
    return PTC_PDIR.B17;
}
void MIKROBUS3_setTX(char set)        
{
    PTC_PDOR.B17 = set;
}
#endif
#ifdef PLD_SCL_PIN
char MIKROBUS1_getSCL()         
{
    return PTD_PDIR.B8;
}
void MIKROBUS1_setSCL(char set)        
{
    PTD_PDOR.B8 = set;
}
char MIKROBUS2_getSCL()         
{
    return PTD_PDIR.B8;
}
void MIKROBUS2_setSCL(char set)        
{
    PTD_PDOR.B8 = set;
}
char MIKROBUS3_getSCL()         
{
    return PTD_PDIR.B8;
}
void MIKROBUS3_setSCL(char set)        
{
    PTD_PDOR.B8 = set;
}
#endif
#ifdef PLD_SDA_PIN
char MIKROBUS1_getSDA()         
{
    return PTD_PDIR.B9;
}
void MIKROBUS1_setSDA(char set)        
{
    PTD_PDOR.B9 = set;
}
char MIKROBUS2_getSDA()         
{
    return PTD_PDIR.B9;
}
void MIKROBUS2_setSDA(char set)        
{
    PTD_PDOR.B9 = set;
}
char MIKROBUS3_getSDA()         
{
    return PTD_PDIR.B9;
}
void MIKROBUS3_setSDA(char set)        
{
    PTD_PDOR.B9 = set;
}
#endif
#endif