#include "MIKROBUS_framework.h"

//#ifdef EASYMX_TM4C129XNCZAD
#ifdef EASY_MX_PRO_V7_TIVA
#ifdef TM4C129XNCZAD
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
    if( bus == MIKROBUS1 )
    {
        switch( pin ) 
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTE_AHB, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&GPIO_PORTE_AHB, _GPIO_PINMASK_4);  break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTE_AHB, _GPIO_PINMASK_0);  else GPIO_Digital_Output(&GPIO_PORTE_AHB, _GPIO_PINMASK_0);  break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTB_AHB, _GPIO_PINMASK_0); else GPIO_Digital_Output(&GPIO_PORTB_AHB, _GPIO_PINMASK_0); break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTA_AHB, _GPIO_PINMASK_2); else GPIO_Digital_Output(&GPIO_PORTA_AHB, _GPIO_PINMASK_2); break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTA_AHB, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORTA_AHB, _GPIO_PINMASK_4); break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTA_AHB, _GPIO_PINMASK_5); else GPIO_Digital_Output(&GPIO_PORTA_AHB, _GPIO_PINMASK_5); break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTD_AHB, _GPIO_PINMASK_0);  else GPIO_Digital_Output(&GPIO_PORTD_AHB, _GPIO_PINMASK_0);  break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTF_AHB, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORTF_AHB, _GPIO_PINMASK_4); break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTC_AHB, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&GPIO_PORTC_AHB, _GPIO_PINMASK_6);  break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTC_AHB, _GPIO_PINMASK_7);  else GPIO_Digital_Output(&GPIO_PORTC_AHB, _GPIO_PINMASK_7);  break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTB_AHB, _GPIO_PINMASK_2);  else GPIO_Digital_Output(&GPIO_PORTB_AHB, _GPIO_PINMASK_2);  break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTB_AHB, _GPIO_PINMASK_3);  else GPIO_Digital_Output(&GPIO_PORTB_AHB, _GPIO_PINMASK_3);  break;
            default : break; 
        }
    }
    if( bus == MIKROBUS2 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTE_AHB, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORTE_AHB, _GPIO_PINMASK_5);  break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTE_AHB, _GPIO_PINMASK_1);  else GPIO_Digital_Output(&GPIO_PORTE_AHB, _GPIO_PINMASK_1);  break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTB_AHB, _GPIO_PINMASK_5); else GPIO_Digital_Output(&GPIO_PORTB_AHB, _GPIO_PINMASK_5); break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTA_AHB, _GPIO_PINMASK_2); else GPIO_Digital_Output(&GPIO_PORTA_AHB, _GPIO_PINMASK_2); break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTA_AHB, _GPIO_PINMASK_4); else GPIO_Digital_Output(&GPIO_PORTA_AHB, _GPIO_PINMASK_4); break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTA_AHB, _GPIO_PINMASK_5); else GPIO_Digital_Output(&GPIO_PORTA_AHB, _GPIO_PINMASK_5); break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTD_AHB, _GPIO_PINMASK_1); else GPIO_Digital_Output(&GPIO_PORTD_AHB, _GPIO_PINMASK_1); break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTD_AHB, _GPIO_PINMASK_6); else GPIO_Digital_Output(&GPIO_PORTD_AHB, _GPIO_PINMASK_6); break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTC_AHB, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&GPIO_PORTC_AHB, _GPIO_PINMASK_4);  break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTC_AHB, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORTC_AHB, _GPIO_PINMASK_5);  break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTB_AHB, _GPIO_PINMASK_2);  else GPIO_Digital_Output(&GPIO_PORTB_AHB, _GPIO_PINMASK_2);  break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORTB_AHB, _GPIO_PINMASK_3);  else GPIO_Digital_Output(&GPIO_PORTB_AHB, _GPIO_PINMASK_3);  break;
            default : break;
        }
    }
}

#ifdef __SPI_CLICK
void MIKROBUS1_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI0_Init_Advanced( (unsigned long)cfg[0], (unsigned)cfg[1], (unsigned)cfg[2] , &_GPIO_MODULE_SPI0_A245_AHB );
    fCall( SPI0_Write, SPI0_Read );
}
void MIKROBUS2_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI0_Init_Advanced( (unsigned long)cfg[0], (unsigned)cfg[1], (unsigned)cfg[2] , &_GPIO_MODULE_SPI0_A245_AHB );
    fCall( SPI0_Write, SPI0_Read );
}
#endif
#ifdef __I2C_CLICK
void MIKROBUS1_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2C0_Init_Advanced( cfg[0], &_GPIO_MODULE_I2C0_B23_AHB );
    fCall( I2C0_Master_Slave_Addr_Set, 0, 0, I2C0_Write, I2C0_Read );	
}
void MIKROBUS2_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2C0_Init_Advanced( cfg[0], &_GPIO_MODULE_I2C0_B23_AHB );
    fCall( I2C0_Master_Slave_Addr_Set, 0, 0, I2C0_Write, I2C0_Read );
}
#endif
#ifdef __UART_CLICK
void MIKROBUS1_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART5_Init_Advanced( (unsigned long)cfg[0], (unsigned long)cfg[1], (unsigned int)cfg[2] , 
						 (unsigned int)cfg[3], (unsigned int)cfg[4], (unsigned int)cfg[5] , 
                        &_GPIO_MODULE_UART5_C67_AHB );
    fCall( UART5_Write, UART5_Read, UART5_Data_Ready );	
}
void MIKROBUS2_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART7_Init_Advanced( (unsigned long)cfg[0], (unsigned long)cfg[1], (unsigned int)cfg[2] , 
						 (unsigned int)cfg[3], (unsigned int)cfg[4], (unsigned int)cfg[5] , 
                        &_GPIO_MODULE_UART7_C45_AHB );
    fCall( UART7_Write, UART7_Read, UART7_Data_Ready );	
}
#endif
#ifdef PLD_AN_PIN
char MIKROBUS1_getAN()          
{
    return GPIO_PORTE_AHB_DATA.B4;
}
void MIKROBUS1_setAN(char set)         
{
    GPIO_PORTE_AHB_DATA.B4 = set;
}
char MIKROBUS2_getAN()          
{
    return GPIO_PORTE_AHB_DATA.B5;
}
void MIKROBUS2_setAN(char set)         
{
    GPIO_PORTE_AHB_DATA.B5 = set;
}
#endif
#ifdef PLD_RST_PIN
char MIKROBUS1_getRST()         
{
    return GPIO_PORTE_AHB_DATA.B0;
}
void MIKROBUS1_setRST(char set)        
{
    GPIO_PORTE_AHB_DATA.B0 = set;
}
char MIKROBUS2_getRST()         
{
    return GPIO_PORTE_AHB_DATA.B1;
}
void MIKROBUS2_setRST(char set)        
{
    GPIO_PORTE_AHB_DATA.B1 = set;
}
#endif
#ifdef PLD_CS_PIN
char MIKROBUS1_getCS()          
{
    return GPIO_PORTB_AHB_DATA.B0;
}
void MIKROBUS1_setCS(char set)         
{
    GPIO_PORTB_AHB_DATA.B0 = set;
}
char MIKROBUS2_getCS()          
{
    return GPIO_PORTB_AHB_DATA.B5;
}
void MIKROBUS2_setCS(char set)         
{
    GPIO_PORTB_AHB_DATA.B5 = set;
}
#endif
#ifdef PLD_SCK_PIN
char MIKROBUS1_getSCK()          
{
    return GPIO_PORTA_AHB_DATA.B2;
}
void MIKROBUS1_setSCK(char set)         
{
    GPIO_PORTA_AHB_DATA.B2;
}
char MIKROBUS2_getSCK()          
{
    return GPIO_PORTA_AHB_DATA.B2;
}
void MIKROBUS2_setSCK(char set)         
{
    GPIO_PORTA_AHB_DATA.B2 = set;
}
#endif
#ifdef PLD_MISO_PIN
char MIKROBUS1_getMISO()         
{
    return GPIO_PORTA_AHB_DATA.B4;
}
void MIKROBUS1_setMISO(char set)        
{
    GPIO_PORTA_AHB_DATA.B4 = set;
}
char MIKROBUS2_getMISO()         
{
    return GPIO_PORTA_AHB_DATA.B4;
}
void MIKROBUS2_setMISO(char set)        
{
    GPIO_PORTA_AHB_DATA.B4 = set;
}
#endif
#ifdef PLD_MOSI_PIN
char MIKROBUS1_getMOSI()          
{
    return GPIO_PORTA_AHB_DATA.B5;
}
void MIKROBUS1_setMOSI(char set)         
{
    GPIO_PORTA_AHB_DATA.B5 = set;
}
char MIKROBUS2_getMOSI()          
{
    return GPIO_PORTA_AHB_DATA.B5;
}
void MIKROBUS2_setMOSI(char set)         
{
    GPIO_PORTA_AHB_DATA.B5 = set;
}
#endif
#ifdef PLD_PWM_PIN
char MIKROBUS1_getPWM()         
{
    return GPIO_PORTD_AHB_DATA.B0;
}
void MIKROBUS1_setPWM(char set)        
{
    GPIO_PORTD_AHB_DATA.B0 = set;
}
char MIKROBUS2_getPWM()         
{
    return GPIO_PORTD_AHB_DATA.B1;
}
void MIKROBUS2_setPWM(char set)        
{
    GPIO_PORTD_AHB_DATA.B1 = set;
}
#endif
#ifdef PLD_INT_PIN
char MIKROBUS1_getINT()         
{
    return GPIO_PORTF_AHB_DATA.B4;
}
void MIKROBUS1_setINT(char set)        
{
    GPIO_PORTF_AHB_DATA.B4 = set;
}
char MIKROBUS2_getINT()         
{
    return GPIO_PORTD_AHB_DATA.B6;
}
void MIKROBUS2_setINT(char set)        
{
    GPIO_PORTD_AHB_DATA.B6 = set;
}
#endif
#ifdef PLD_RX_PIN
char MIKROBUS1_getRX()         
{
    return GPIO_PORTC_AHB_DATA.B6;
}
void MIKROBUS1_setRX(char set)        
{
    GPIO_PORTC_AHB_DATA.B6 = set;
}
char MIKROBUS2_getRX()         
{
    return GPIO_PORTC_AHB_DATA.B4;
}
void MIKROBUS2_setRX(char set)        
{
    GPIO_PORTC_AHB_DATA.B4 = set;
}
#endif
#ifdef PLD_TX_PIN
char MIKROBUS1_getTX()         
{
    return GPIO_PORTC_AHB_DATA.B7;
}
void MIKROBUS1_setTX(char set)        
{
    GPIO_PORTC_AHB_DATA.B7 = set;
}
char MIKROBUS2_getTX()         
{
    return GPIO_PORTC_AHB_DATA.B5;
}
void MIKROBUS2_setTX(char set)        
{
    GPIO_PORTC_AHB_DATA.B5 = set;
}
#endif
#ifdef PLD_SCL_PIN
char MIKROBUS1_getSCL()         
{
    return GPIO_PORTB_AHB_DATA.B2;
}
void MIKROBUS1_setSCL(char set)        
{
    GPIO_PORTB_AHB_DATA.B2 = set;
}
char MIKROBUS2_getSCL()         
{
    return GPIO_PORTB_AHB_DATA.B2;
}
void MIKROBUS2_setSCL(char set)        
{
    GPIO_PORTB_AHB_DATA.B2 = set;
}
#endif
#ifdef PLD_SDA_PIN
char MIKROBUS1_getSDA()         
{
    return GPIO_PORTB_AHB_DATA.B3;
}
void MIKROBUS1_setSDA(char set)        
{
    GPIO_PORTB_AHB_DATA.B3 = set;
}
char MIKROBUS2_getSDA()         
{
    return GPIO_PORTB_AHB_DATA.B3;
}
void MIKROBUS2_setSDA(char set)        
{
    GPIO_PORTB_AHB_DATA.B3 = set;
}
#endif
#endif
#endif
