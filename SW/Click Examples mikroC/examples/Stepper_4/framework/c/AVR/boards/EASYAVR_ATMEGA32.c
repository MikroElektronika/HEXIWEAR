#include "AVR/__AVR_systems.h"

#ifdef EASYAVR_V7
#ifdef ATMEGA32
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
    if( bus == MIKROBUS1 )
    {
        switch( pin ) 
        {
            case MIKROBUS_AN_PIN   : DDA7_bit  = dir; break;
            case MIKROBUS_RST_PIN  : DDA6_bit  = dir; break;
            case MIKROBUS_CS_PIN   : DDA5_bit  = dir; break;
            case MIKROBUS_SCK_PIN  : DDB7_bit = dir; break;
            case MIKROBUS_MISO_PIN : DDB6_bit  = dir; break;
            case MIKROBUS_MOSI_PIN : DDB5_bit  = dir; break;
            case MIKROBUS_PWM_PIN  : DDD4_bit  = dir; break;
            case MIKROBUS_INT_PIN  : DDD2_bit  = dir; break;
            case MIKROBUS_RX_PIN   : DDD0_bit  = dir; break;
            case MIKROBUS_TX_PIN   : DDD1_bit  = dir; break;
            case MIKROBUS_SCL_PIN  : DDC0_bit  = dir; break;
            case MIKROBUS_SDA_PIN  : DDC1_bit  = dir; break;
            default : break; 
        }
    }
    if( bus == MIKROBUS2 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : DDA0_bit  = dir; break;
            case MIKROBUS_RST_PIN  : DDA1_bit  = dir; break;
            case MIKROBUS_CS_PIN   : DDA3_bit  = dir; break;
            case MIKROBUS_SCK_PIN  : DDB7_bit = dir; break;
            case MIKROBUS_MISO_PIN : DDB6_bit  = dir; break;
            case MIKROBUS_MOSI_PIN : DDB5_bit  = dir; break;
            case MIKROBUS_PWM_PIN  : DDD5_bit  = dir; break;
            case MIKROBUS_INT_PIN  : DDD3_bit  = dir; break;
            case MIKROBUS_RX_PIN   : DDD0_bit  = dir; break;
            case MIKROBUS_TX_PIN   : DDD1_bit  = dir; break;
            case MIKROBUS_SCL_PIN  : DDC0_bit  = dir; break;
            case MIKROBUS_SDA_PIN  : DDC1_bit  = dir; break;
            default : break;
        }
    }
	if( bus == MIKROBUS3 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : DDA4_bit  = dir; break;
            case MIKROBUS_RST_PIN  : DDB0_bit  = dir; break;
            case MIKROBUS_CS_PIN   : DDB4_bit  = dir; break;
            case MIKROBUS_SCK_PIN  : DDB7_bit = dir; break;
            case MIKROBUS_MISO_PIN : DDB6_bit  = dir; break;
            case MIKROBUS_MOSI_PIN : DDB5_bit  = dir; break;
            case MIKROBUS_PWM_PIN  : DDB3_bit  = dir; break;
            case MIKROBUS_INT_PIN  : DDB2_bit  = dir; break;
            case MIKROBUS_RX_PIN   : DDD2_bit  = dir; break;
            case MIKROBUS_TX_PIN   : DDD3_bit  = dir; break;
            case MIKROBUS_SCL_PIN  : DDC0_bit  = dir; break;
            case MIKROBUS_SDA_PIN  : DDC1_bit  = dir; break;
            default : break;
        }
    }
}

#ifdef __SPI_CLICK
void MIKROBUS1_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI1_Init_Advanced( (unsigned char)cfg[0], (unsigned char)cfg[1],
                        (unsigned char)cfg[2] );
	fCall( SPI1_Write, SPI1_Read );					
}
void MIKROBUS2_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI1_Init_Advanced( (unsigned char)cfg[0], (unsigned char)cfg[1],
                        (unsigned char)cfg[2] );       
	fCall( SPI1_Write, SPI1_Read );					
}
void MIKROBUS3_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI1_Init_Advanced( (unsigned char)cfg[0], (unsigned char)cfg[1],
                        (unsigned char)cfg[2] );
	fCall( SPI1_Write, SPI1_Read );					
}
#endif
#ifdef __I2C_CLICK
void MIKROBUS1_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    TWI_Init( ( unsigned long)cfg[0] );
	fCall( TWI_Start, TWI_Stop, 0, TWI_Write, TWI_Read );
}
void MIKROBUS2_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    TWI_Init( ( unsigned long)cfg[0] );
	fCall( TWI_Start, TWI_Stop, 0, TWI_Write, TWI_Read );
}
void MIKROBUS3_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    TWI_Init( ( unsigned long)cfg[0] );
	fCall( TWI_Start, TWI_Stop, 0, TWI_Write, TWI_Read );
}

#endif
#ifdef __UART_CLICK
void MIKROBUS1_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART1_Init( (unsigned long)cfg[0] );
	fCall( UART1_Write, UART1_Read, UART1_Data_Ready );
}
void MIKROBUS2_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART1_Init( (unsigned long)cfg[0] );
	fCall( UART1_Write, UART1_Read, UART1_Data_Ready );
}
void MIKROBUS3_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
  /*   T_UART_initializer fCall = fpInit;
    UART2_Init( (unsigned long)cfg[0] );
	fCall( UART2_Write, UART2_Read, UART2_Data_Ready ); */
}
#endif
#ifdef PLD_AN_PIN
char MIKROBUS1_getAN()          
{
    return PINA7_bit;
}
void MIKROBUS1_setAN(char set)         
{
    PORTA7_bit = set;
}
char MIKROBUS2_getAN()          
{
    return PINA0_bit;
}
void MIKROBUS2_setAN(char set)         
{
    PORTA0_bit = set;
}
char MIKROBUS3_getAN()          
{
    return PINA4_bit;
}
void MIKROBUS3_setAN(char set)         
{
    PORTA4_bit = set;
}
#endif
#ifdef PLD_RST_PIN
char MIKROBUS1_getRST()         
{
    return PINA6_bit;
}
void MIKROBUS1_setRST(char set)        
{
    PORTA6_bit = set;
}
char MIKROBUS2_getRST()         
{
    return PINA1_bit;
}
void MIKROBUS2_setRST(char set)        
{
    PORTA1_bit = set;
}
char MIKROBUS3_getRST()         
{
    return PINB0_bit;
}
void MIKROBUS3_setRST(char set)        
{
    PORTB0_bit = set;
}
#endif
#ifdef PLD_CS_PIN
char MIKROBUS1_getCS()          
{
    return PINA5_bit;
}
void MIKROBUS1_setCS(char set)         
{
    PORTA5_bit = set;
}
char MIKROBUS2_getCS()          
{
    return PINA3_bit;
}
void MIKROBUS2_setCS(char set)         
{
    PORTA3_bit = set;
}
char MIKROBUS3_getCS()          
{
    return PINB4_bit;
}
void MIKROBUS3_setCS(char set)         
{
    PORTB4_bit = set;
}
#endif
#ifdef PLD_SCK_PIN
char MIKROBUS1_getSCK()          
{
    return PINB7_bit;
}
void MIKROBUS1_setSCK(char set)         
{
    PORTB7_bit = set;
}
char MIKROBUS2_getSCK()          
{
    return PINB7_bit;
}
void MIKROBUS2_setSCK(char set)         
{
    PORTB7_bit = set;
}
char MIKROBUS3_getSCK()          
{
    return PINB7_bit;
}
void MIKROBUS3_setSCK(char set)         
{
    PORTB7_bit = set;
}
#endif
#ifdef PLD_MISO_PIN
char MIKROBUS1_getMISO()         
{
    return PINB6_bit;
}
void MIKROBUS1_setMISO(char set)        
{
    PORTB6_bit = set;
}
char MIKROBUS2_getMISO()         
{
    return PINB6_bit;
}
void MIKROBUS2_setMISO(char set)        
{
    PORTB6_bit = set;
}
char MIKROBUS3_getMISO()         
{
    return PINB6_bit;
}
void MIKROBUS3_setMISO(char set)        
{
    PORTB6_bit = set;
}
#endif
#ifdef PLD_MOSI_PIN
char MIKROBUS1_getMOSI()          
{
    return PINB5_bit;
}
void MIKROBUS1_setMOSI(char set)         
{
    PORTB5_bit = set;
}
char MIKROBUS2_getMOSI()          
{
    return PINB5_bit;
}
void MIKROBUS2_setMOSI(char set)         
{
    PORTB5_bit = set;
}
char MIKROBUS3_getMOSI()          
{
    return PINB5_bit;
}
void MIKROBUS3_setMOSI(char set)         
{
    PORTB5_bit = set;
}
#endif
#ifdef PLD_PWM_PIN
char MIKROBUS1_getPWM()         
{
    return PIND4_bit;
}
void MIKROBUS1_setPWM(char set)        
{
    PORTD4_bit = set;
}
char MIKROBUS2_getPWM()         
{
    return PIND5_bit;
}
void MIKROBUS2_setPWM(char set)        
{
    PORTD5_bit = set;
}
char MIKROBUS3_getPWM()         
{
    return PINB3_bit;
}
void MIKROBUS3_setPWM(char set)        
{
    PORTB3_bit = set;
}
#endif
#ifdef PLD_INT_PIN
char MIKROBUS1_getINT()         
{
    return PIND2_bit;
}
void MIKROBUS1_setINT(char set)        
{
    PORTD2_bit = set;
}
char MIKROBUS2_getINT()         
{
    return PIND3_bit;
}
void MIKROBUS2_setINT(char set)        
{
    PORTD3_bit = set;
}
char MIKROBUS3_getINT()         
{
    return PINB2_bit;
}
void MIKROBUS3_setINT(char set)        
{
    PORTB2_bit = set;
}
#endif
#ifdef PLD_RX_PIN
char MIKROBUS1_getRX()         
{
    return PIND0_bit;
}
void MIKROBUS1_setRX(char set)        
{
    PORTD0_bit = set;
}
char MIKROBUS2_getRX()         
{
    return PIND0_bit;
}
void MIKROBUS2_setRX(char set)        
{
    PORTD0_bit = set;
}
char MIKROBUS3_getRX()         
{
    return PIND2_bit;
}
void MIKROBUS3_setRX(char set)        
{
    PORTD2_bit = set;
}
#endif
#ifdef PLD_TX_PIN
char MIKROBUS1_getTX()         
{
    return PIND1_bit;
}
void MIKROBUS1_setTX(char set)        
{
    PORTD1_bit = set;
}
char MIKROBUS2_getTX()         
{
    return PIND1_bit;
}
void MIKROBUS2_setTX(char set)        
{
    PORTD1_bit = set;
}
char MIKROBUS3_getTX()         
{
    return PIND3_bit;
}
void MIKROBUS3_setTX(char set)        
{
    PORTD3_bit = set;
}
#endif
#ifdef PLD_SCL_PIN
char MIKROBUS1_getSCL()         
{
    return PINC0_bit;
}
void MIKROBUS1_setSCL(char set)        
{
    PORTC0_bit = set;
}
char MIKROBUS2_getSCL()         
{
    return PINC0_bit;
}
void MIKROBUS2_setSCL(char set)        
{
    PORTC0_bit = set;
}
char MIKROBUS3_getSCL()         
{
    return PINC0_bit;
}
void MIKROBUS3_setSCL(char set)        
{
    PORTC0_bit = set;
}
#endif
#ifdef PLD_SDA_PIN
char MIKROBUS1_getSDA()         
{
    return PINC1_bit;
}
void MIKROBUS1_setSDA(char set)        
{
    PORTC1_bit = set;
}
char MIKROBUS2_getSDA()         
{
    return PINC1_bit;
}
void MIKROBUS2_setSDA(char set)        
{
    PORTC1_bit = set;
}
char MIKROBUS3_getSDA()         
{
    return PINC1_bit;
}
void MIKROBUS3_setSDA(char set)        
{
    PORTC1_bit = set;
}
#endif
#endif
#endif