#include "MIKROBUS_framework.h"

#ifdef EASYPIC_FUSION_V7
#ifdef P32MX460F512L
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
    if( bus == MIKROBUS1 )
    {
        switch( pin ) 
        {
            case MIKROBUS_AN_PIN   : TRISB8_bit  = dir; break;
            case MIKROBUS_RST_PIN  : TRISC1_bit  = dir; break;
            case MIKROBUS_CS_PIN   : TRISC2_bit  = dir; break;
            case MIKROBUS_SCK_PIN  : TRISD15_bit = dir; break;
            case MIKROBUS_MISO_PIN : TRISF2_bit  = dir; break;
            case MIKROBUS_MOSI_PIN : TRISF8_bit  = dir; break;
            case MIKROBUS_PWM_PIN  : TRISD0_bit  = dir; break;
            case MIKROBUS_INT_PIN  : TRISE8_bit  = dir; break;
            case MIKROBUS_RX_PIN   : TRISF4_bit  = dir; break;
            case MIKROBUS_TX_PIN   : TRISF5_bit  = dir; break;
            case MIKROBUS_SCL_PIN  : TRISA2_bit  = dir; break;
            case MIKROBUS_SDA_PIN  : TRISA3_bit  = dir; break;
            default : break; 
        }
    }
    if( bus == MIKROBUS2 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : TRISB9_bit  = dir; break;
            case MIKROBUS_RST_PIN  : TRISC3_bit  = dir; break;
            case MIKROBUS_CS_PIN   : TRISC4_bit  = dir; break;
            case MIKROBUS_SCK_PIN  : TRISD15_bit = dir; break;
            case MIKROBUS_MISO_PIN : TRISF2_bit  = dir; break;
            case MIKROBUS_MOSI_PIN : TRISF8_bit  = dir; break;
            case MIKROBUS_PWM_PIN  : TRISD1_bit  = dir; break;
            case MIKROBUS_INT_PIN  : TRISE9_bit  = dir; break;
            case MIKROBUS_RX_PIN   : TRISF12_bit = dir; break;
            case MIKROBUS_TX_PIN   : TRISF13_bit = dir; break;
            case MIKROBUS_SCL_PIN  : TRISA2_bit  = dir; break;
            case MIKROBUS_SDA_PIN  : TRISA3_bit  = dir; break;
            default : break;
        }
    }
}

#ifdef __SPI_CLICK
void MIKROBUS1_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg) 
{
    T_SPI_initializer fCall = fpInit;
    SPI3_Init_Advanced( (unsigned int)cfg[0], (unsigned int)cfg[1],
                        (unsigned int)cfg[2], (unsigned int)cfg[3],
                        (unsigned int)cfg[4], (unsigned int)cfg[5],
                        (unsigned int)cfg[6] );
    fCall( SPI3_Write, SPI3_Read );
}
void MIKROBUS2_spiDriverMap(T_SPI_initializer fpInit, const uint32_t *cfg) 
{
    T_SPI_initializer fCall = fpInit;
    SPI3_Init_Advanced( (unsigned int)cfg[0], (unsigned int)cfg[1],
                        (unsigned int)cfg[2], (unsigned int)cfg[3],
                        (unsigned int)cfg[4], (unsigned int)cfg[5],
                        (unsigned int)cfg[6] );
    fCall( SPI3_Write, SPI3_Read );
}
#endif
#ifdef __I2C_CLICK
void MIKROBUS1_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg)
{
    T_I2C_initializer fCall = fpInit;
    I2C2_Init( cfg[0] );
    fCall( I2C2_Start, I2C2_Stop, I2C2_Restart, I2C2_Write, I2C2_Read );
}
void MIKROBUS2_i2cDriverMap(T_I2C_initializer fpInit, const uint32_t *cfg)
{
    T_I2C_initializer fCall = fpInit;
    I2C2_Init( cfg[0] );
    fCall( I2C2_Start, I2C2_Stop, I2C2_Restart, I2C2_Write, I2C2_Read );
}
#endif
#ifdef __UART_CLICK
void MIKROBUS1_uartDriverMap(T_UART_initializer fpInit, const uint32_t *cfg)
{
    T_UART_initializer fCall = fpInit;
    UART2_Init( cfg[0] );
    fCall( UART2_Write, UART2_Read, UART2_Data_Ready );
}
void MIKROBUS2_uartDriverMap(T_UART_initializer fpInit, const uint32_t *cfg)
{
    T_UART_initializer fCall = fpInit;
    UART5_Init( cfg[0] );
    fCall( UART5_Write, UART5_Read, UART5_Data_Ready );
}
#endif
#ifdef PLD_AN_PIN
char MIKROBUS1_getAN()          
{
    return RB8_bit;
}
void MIKROBUS1_setAN(char set)         
{
    LATB8_bit = set;
}
char MIKROBUS2_getAN()          
{
    return RB9_bit;
}
void MIKROBUS2_setAN(char set)         
{
    LATB9_bit = set;
}
#endif
#ifdef PLD_RST_PIN
char MIKROBUS1_getRST()         
{
    return RC1_bit;
}
void MIKROBUS1_setRST(char set)        
{
    LATC1_bit = set;
}
char MIKROBUS2_getRST()         
{
    return RC3_bit;
}
void MIKROBUS2_setRST(char set)        
{
    LATC3_bit = set;
}
#endif
#ifdef PLD_CS_PIN
char MIKROBUS1_getCS()          
{
    return RC2_bit;
}
void MIKROBUS1_setCS(char set)         
{
    LATC2_bit = set;
}
char MIKROBUS2_getCS()          
{
    return RC4_bit;
}
void MIKROBUS2_setCS(char set)         
{
    LATC4_bit = set;
}
#endif
#ifdef PLD_SCK_PIN
char MIKROBUS1_getSCK()          
{
    return RD15_bit;
}
void MIKROBUS1_setSCK(char set)         
{
    LATD15_bit = set;
}
char MIKROBUS2_getSCK()          
{
    return RD15_bit;
}
void MIKROBUS2_setSCK(char set)         
{
    LATD15_bit = set;
}
#endif
#ifdef PLD_MISO_PIN
char MIKROBUS1_getMISO()         
{
    return RF2_bit;
}
void MIKROBUS1_setMISO(char set)        
{
    LATF2_bit = set;
}
char MIKROBUS2_getMISO()         
{
    return RF2_bit;
}
void MIKROBUS2_setMISO(char set)        
{
    LATF2_bit = set;
}
#endif
#ifdef PLD_MOSI_PIN
char MIKROBUS1_getMOSI()          
{
    return RF8_bit;
}
void MIKROBUS1_setMOSI(char set)         
{
    LATF8_bit = set;
}
char MIKROBUS2_getMOSI()          
{
    return RF8_bit;
}
void MIKROBUS2_setMOSI(char set)         
{
    LATF8_bit = set;
}
#endif
#ifdef PLD_PWM_PIN
char MIKROBUS1_getPWM()         
{
    return RD0_bit;
}
void MIKROBUS1_setPWM(char set)        
{
    LATD0_bit = set;
}
char MIKROBUS2_getPWM()         
{
    return RD1_bit;
}
void MIKROBUS2_setPWM(char set)        
{
    LATD1_bit = set;
}
#endif
#ifdef PLD_INT_PIN
char MIKROBUS1_getINT()         
{
    return RE8_bit;
}
void MIKROBUS1_setINT(char set)        
{
    LATE8_bit = set;
}
char MIKROBUS2_getINT()         
{
    return RE9_bit;
}
void MIKROBUS2_setINT(char set)        
{
    LATE9_bit = set;
}
#endif
#ifdef PLD_RX_PIN
char MIKROBUS1_getRX()         
{
    return RF4_bit;
}
void MIKROBUS1_setRX(char set)        
{
    LATF4_bit = set;
}
char MIKROBUS2_getRX()         
{
    return RF12_bit;
}
void MIKROBUS2_setRX(char set)        
{
    LATF12_bit = set;
}
#endif
#ifdef PLD_TX_PIN
char MIKROBUS1_getTX()         
{
    return RF5_bit;
}
void MIKROBUS1_setTX(char set)        
{
    LATF5_bit = set;
}
char MIKROBUS2_getTX()         
{
    return RF13_bit;
}
void MIKROBUS2_setTX(char set)        
{
    LATF13_bit = set;
}
#endif
#ifdef PLD_SCL_PIN
char MIKROBUS1_getSCL()         
{
    return RA2_bit;
}
void MIKROBUS1_setSCL(char set)        
{
    LATA2_bit = set;
}
char MIKROBUS2_getSCL()         
{
    return RA2_bit;
}
void MIKROBUS2_setSCL(char set)        
{
    LATA2_bit = set;
}
#endif
#ifdef PLD_SDA_PIN
char MIKROBUS1_getSDA()         
{
    return RA3_bit;
}
void MIKROBUS1_setSDA(char set)        
{
    LATA3_bit = set;
}
char MIKROBUS2_getSDA()         
{
    return RA3_bit;
}
void MIKROBUS2_setSDA(char set)        
{
    LATA3_bit = set;
}
#endif

#endif
#endif