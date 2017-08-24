#include "PIC/__PIC_systems.h"

#ifdef EASYPIC_V7
#ifdef P18F45K22
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
    if( bus == MIKROBUS1 )
    {
        switch( pin ) 
        {
            case MIKROBUS_AN_PIN   : TRISA2_bit  = dir; ANSELA.B2 = 0; break;
            case MIKROBUS_RST_PIN  : TRISE1_bit  = dir; ANSELE.B1 = 0; break;
            case MIKROBUS_CS_PIN   : TRISE0_bit  = dir; ANSELE.B0 = 0; break;
            case MIKROBUS_SCK_PIN  : TRISC3_bit = dir; ANSELC.B3 = 0; break;
            case MIKROBUS_MISO_PIN : TRISC4_bit  = dir; ANSELC.B4 = 0; break;
            case MIKROBUS_MOSI_PIN : TRISC5_bit  = dir; ANSELC.B5 = 0; break;
            case MIKROBUS_PWM_PIN  : TRISC0_bit  = dir; ANSELC.B0 = 0; break;
            case MIKROBUS_INT_PIN  : TRISB0_bit  = dir; ANSELB.B0 = 0; break;
            case MIKROBUS_RX_PIN   : TRISC7_bit  = dir; ANSELC.B7 = 0; break;
            case MIKROBUS_TX_PIN   : TRISC6_bit  = dir; ANSELC.B6 = 0; break;
            case MIKROBUS_SCL_PIN  : TRISC3_bit  = dir; ANSELC.B3 = 0; break;
            case MIKROBUS_SDA_PIN  : TRISC4_bit  = dir; ANSELC.B4 = 0; break;
            default : break; 
        }
    }
    if( bus == MIKROBUS2 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : TRISA3_bit  = dir; ANSELA.B3 = 0; break;
            case MIKROBUS_RST_PIN  : TRISE2_bit  = dir; ANSELE.B2 = 0; break;
            case MIKROBUS_CS_PIN   : TRISA5_bit  = dir; ANSELA.B5 = 0; break;
            case MIKROBUS_SCK_PIN  : TRISC3_bit = dir; ANSELC.B3 = 0; break;
            case MIKROBUS_MISO_PIN : TRISC4_bit  = dir; ANSELC.B4 = 0; break;
            case MIKROBUS_MOSI_PIN : TRISC5_bit  = dir; ANSELC.B5 = 0; break;
            case MIKROBUS_PWM_PIN  : TRISC1_bit  = dir; ANSELC.B1 = 0; break;
            case MIKROBUS_INT_PIN  : TRISB1_bit  = dir; ANSELB.B1 = 0; break;
            case MIKROBUS_RX_PIN   : TRISC7_bit = dir; ANSELC.B7 = 0; break;
            case MIKROBUS_TX_PIN   : TRISC6_bit = dir; ANSELC.B6 = 0; break;
            case MIKROBUS_SCL_PIN  : TRISC3_bit  = dir; ANSELC.B3 = 0; break;
            case MIKROBUS_SDA_PIN  : TRISC4_bit  = dir; ANSELC.B4 = 0; break;
            default : break;
        }
    }

}

#ifdef __SPI_CLICK
void MIKROBUS1_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    ANSELC.B3 = 0;
	ANSELC.B4 = 0;
	ANSELC.B5 = 0;
	SPI1_Init_Advanced( (unsigned short)cfg[0], (unsigned short)cfg[1],
                        (unsigned short)cfg[2], (unsigned short)cfg[3] );
	fCall( SPI1_Write, SPI1_Read );					
}
void MIKROBUS2_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    ANSELC.B3 = 0;
	ANSELC.B4 = 0;
	ANSELC.B5 = 0;
	SPI1_Init_Advanced( (unsigned short)cfg[0], (unsigned short)cfg[1],
                        (unsigned short)cfg[2], (unsigned short)cfg[3] );
	fCall( SPI1_Write, SPI1_Read );					
}
#endif
#ifdef __I2C_CLICK
void MIKROBUS1_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
	unsigned long br = *cfg;
	
	
    ANSELC.B3 = 0;
    ANSELC.B4 = 0;
	if( *cfg == 100000 )
	I2C1_Init( 100000 );
	fCall( I2C1_Start, I2C1_Stop, I2C1_Repeated_Start, I2C1_Wr, I2C1_Rd );
}
void MIKROBUS2_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    ANSELC.B3 = 0;
    ANSELC.B4 = 0;
	//I2C1_Init( cfg[0] );
	fCall( I2C1_Start, I2C1_Stop, I2C1_Repeated_Start, I2C1_Wr, I2C1_Rd );
}
#endif
#ifdef __UART_CLICK
void MIKROBUS1_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
	ANSELC.B7 = 0;
	ANSELC.B6 = 0; 
    UART1_Init( (const unsigned long)cfg[0] );
	fCall( UART1_Write, UART1_Read, UART1_Data_Ready );
}
void MIKROBUS2_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    ANSELC.B7 = 0;
	ANSELC.B6 = 0; 
	UART1_Init( (const unsigned long)cfg[0] );
	fCall( UART1_Write, UART1_Read, UART1_Data_Ready );
}
#endif
#ifdef PLD_AN_PIN
char MIKROBUS1_getAN()          
{
    return RA2_bit;
}
void MIKROBUS1_setAN(char set)         
{
    LATA2_bit = set;
}
char MIKROBUS2_getAN()          
{
    return RA3_bit;
}
void MIKROBUS2_setAN(char set)         
{
    LATA3_bit = set;
}
#endif
#ifdef PLD_RST_PIN
char MIKROBUS1_getRST()         
{
    return RE1_bit;
}
void MIKROBUS1_setRST(char set)        
{
    LATE1_bit = set;
}
char MIKROBUS2_getRST()         
{
    return RE2_bit;
}
void MIKROBUS2_setRST(char set)        
{
    LATE2_bit = set;
}
#endif
#ifdef PLD_CS_PIN
char MIKROBUS1_getCS()          
{
    return RE0_bit;
}
void MIKROBUS1_setCS(char set)         
{
    LATE0_bit = set;
}
char MIKROBUS2_getCS()          
{
    return RA5_bit;
}
void MIKROBUS2_setCS(char set)         
{
    LATA5_bit = set;
}
#endif
#ifdef PLD_SCK_PIN
char MIKROBUS1_getSCK()          
{
    return RC3_bit;
}
void MIKROBUS1_setSCK(char set)         
{
    LATC3_bit = set;
}
char MIKROBUS2_getSCK()          
{
    return RC3_bit;
}
void MIKROBUS2_setSCK(char set)         
{
    LATC3_bit = set;
}
#endif
#ifdef PLD_MISO_PIN
char MIKROBUS1_getMISO()         
{
    return RC4_bit;
}
void MIKROBUS1_setMISO(char set)        
{
    LATC4_bit = set;
}
char MIKROBUS2_getMISO()         
{
    return RC4_bit;
}
void MIKROBUS2_setMISO(char set)        
{
    LATC4_bit = set;
}
#endif
#ifdef PLD_MOSI_PIN
char MIKROBUS1_getMOSI()          
{
    return RC5_bit;
}
void MIKROBUS1_setMOSI(char set)         
{
    LATC5_bit = set;
}
char MIKROBUS2_getMOSI()          
{
    return RC5_bit;
}
void MIKROBUS2_setMOSI(char set)         
{
    LATC5_bit = set;
}
#endif
#ifdef PLD_PWM_PIN
char MIKROBUS1_getPWM()         
{
    return RC0_bit;
}
void MIKROBUS1_setPWM(char set)        
{
    LATC0_bit = set;
}
char MIKROBUS2_getPWM()         
{
    return RC1_bit;
}
void MIKROBUS2_setPWM(char set)        
{
    LATC1_bit = set;
}
#endif
#ifdef PLD_INT_PIN
char MIKROBUS1_getINT()         
{
    return RB0_bit;
}
void MIKROBUS1_setINT(char set)        
{
    LATB0_bit = set;
}
char MIKROBUS2_getINT()         
{
    return RB1_bit;
}
void MIKROBUS2_setINT(char set)        
{
    LATB1_bit = set;
}
#endif
#ifdef PLD_RX_PIN
char MIKROBUS1_getRX()         
{
    return RC7_bit;
}
void MIKROBUS1_setRX(char set)        
{
    LATC7_bit = set;
}
char MIKROBUS2_getRX()         
{
    return RC7_bit;
}
void MIKROBUS2_setRX(char set)        
{
    LATC7_bit = set;
}
#endif
#ifdef PLD_TX_PIN
char MIKROBUS1_getTX()         
{
    return RC6_bit;
}
void MIKROBUS1_setTX(char set)        
{
    LATC6_bit = set;
}
char MIKROBUS2_getTX()         
{
    return RC6_bit;
}
void MIKROBUS2_setTX(char set)        
{
    LATC6_bit = set;
}
#endif
#ifdef PLD_SCL_PIN
char MIKROBUS1_getSCL()         
{
    return RC3_bit;
}
void MIKROBUS1_setSCL(char set)        
{
    LATC3_bit = set;
}
char MIKROBUS2_getSCL()         
{
    return RC3_bit;
}
void MIKROBUS2_setSCL(char set)        
{
    LATC3_bit = set;
}
#endif
#ifdef PLD_SDA_PIN
char MIKROBUS1_getSDA()         
{
    return RC4_bit;
}
void MIKROBUS1_setSDA(char set)        
{
    LATC4_bit = set;
}
char MIKROBUS2_getSDA()         
{
    return RC4_bit;
}
void MIKROBUS2_setSDA(char set)        
{
    LATC4_bit = set;
}
#endif
#endif
#endif