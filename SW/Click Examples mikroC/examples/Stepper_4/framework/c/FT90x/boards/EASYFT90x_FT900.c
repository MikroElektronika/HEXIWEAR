#include "MIKROBUS_framework.h"

#ifdef EASY_FT90x_V7
#ifdef FT900
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
    if( bus == MIKROBUS1 )
    {
        switch( pin ) 
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_08_15, _GPIO_PINMASK_1);  else GPIO_Digital_Output(&GPIO_PORT_08_15, _GPIO_PINMASK_1);  break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_00_07, _GPIO_PINMASK_1);  else GPIO_Digital_Output(&GPIO_PORT_00_07, _GPIO_PINMASK_1);  break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_24_31, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&GPIO_PORT_24_31, _GPIO_PINMASK_4);  break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_24_31, _GPIO_PINMASK_3);  else GPIO_Digital_Output(&GPIO_PORT_24_31, _GPIO_PINMASK_3);  break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_24_31, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&GPIO_PORT_24_31, _GPIO_PINMASK_6);  break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_24_31, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORT_24_31, _GPIO_PINMASK_5);  break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_56_63, _GPIO_PINMASK_0);  else GPIO_Digital_Output(&GPIO_PORT_56_63, _GPIO_PINMASK_0);  break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_00_07, _GPIO_PINMASK_3);  else GPIO_Digital_Output(&GPIO_PORT_00_07, _GPIO_PINMASK_3);  break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_48_55, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORT_48_55, _GPIO_PINMASK_5);  break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_48_55, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&GPIO_PORT_48_55, _GPIO_PINMASK_4);  break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_40_47, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&GPIO_PORT_40_47, _GPIO_PINMASK_4);  break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_40_47, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORT_40_47, _GPIO_PINMASK_5);  break;
            default : break; 
        }
    }
    if( bus == MIKROBUS2 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_48_55, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&GPIO_PORT_48_55, _GPIO_PINMASK_6);  break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_00_07, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&GPIO_PORT_00_07, _GPIO_PINMASK_4);  break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_56_63, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORT_56_63, _GPIO_PINMASK_5);  break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_24_31, _GPIO_PINMASK_3);  else GPIO_Digital_Output(&GPIO_PORT_24_31, _GPIO_PINMASK_3);  break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_24_31, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&GPIO_PORT_24_31, _GPIO_PINMASK_6);  break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_24_31, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORT_24_31, _GPIO_PINMASK_5);  break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_56_63, _GPIO_PINMASK_1);  else GPIO_Digital_Output(&GPIO_PORT_56_63, _GPIO_PINMASK_1);  break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_00_07, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORT_00_07, _GPIO_PINMASK_5);  break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_48_55, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORT_48_55, _GPIO_PINMASK_5);  break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_48_55, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&GPIO_PORT_48_55, _GPIO_PINMASK_4);  break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_40_47, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&GPIO_PORT_40_47, _GPIO_PINMASK_4);  break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIO_PORT_40_47, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIO_PORT_40_47, _GPIO_PINMASK_5);  break;
            default : break;
        }
    }
}

#ifdef __SPI_CLICK
void MIKROBUS1_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPIM1_Init_Advanced ( (char)cfg[0], (unsigned int)cfg[1],
                        (unsigned int)cfg[2] );
        fCall( SPIM1_Write, SPIM1_Read );                                        
}
void MIKROBUS2_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPIM1_Init_Advanced ( (char)cfg[0], (unsigned int)cfg[1],
                        (unsigned int)cfg[2] );
        fCall( SPIM1_Write, SPIM1_Read );                                        
}
#endif
#ifdef __I2C_CLICK
void MIKROBUS1_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2CM1_Init( (char)cfg[0], (char)cfg[0] );
        fCall( I2CM1_Set_Slave_Address, 0, 0, I2CM1_Write_Bytes, I2CM1_Read_Bytes );
}
void MIKROBUS2_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2CM1_Init( (char)cfg[0], (char)cfg[0] );
        fCall( I2CM1_Set_Slave_Address, 0, 0, I2CM1_Write_Bytes, I2CM1_Read_Bytes );
}
#endif
#ifdef __UART_CLICK
void MIKROBUS1_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART2_Init( (const unsigned long)cfg[0] );
        fCall( UART2_Write, UART2_Read, UART2_Data_Ready );
}
void MIKROBUS2_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART2_Init( (const unsigned long)cfg[0] );
        fCall( UART2_Write, UART2_Read, UART2_Data_Ready );
}
#endif
#ifdef PLD_AN_PIN
char MIKROBUS1_getAN()          
{
    return GPIO_PIN9_bit;
}
void MIKROBUS1_setAN(char set)         
{
    GPIO_PIN9_bit = set;
}
char MIKROBUS2_getAN()          
{
    return GPIO_PIN54_bit;
}
void MIKROBUS2_setAN(char set)         
{
    GPIO_PIN54_bit = set;
}
#endif
#ifdef PLD_RST_PIN
char MIKROBUS1_getRST()         
{
    return GPIO_PIN1_bit;
}
void MIKROBUS1_setRST(char set)        
{
    GPIO_PIN1_bit = set;
}
char MIKROBUS2_getRST()         
{
    return GPIO_PIN4_bit;
}
void MIKROBUS2_setRST(char set)        
{
    GPIO_PIN4_bit = set;
}
#endif
#ifdef PLD_CS_PIN
char MIKROBUS1_getCS()          
{
    return GPIO_PIN28_bit;
}
void MIKROBUS1_setCS(char set)         
{
    GPIO_PIN28_bit = set;
}
char MIKROBUS2_getCS()          
{
    return GPIO_PIN61_bit;
}
void MIKROBUS2_setCS(char set)         
{
    GPIO_PIN61_bit = set;
}
#endif
#ifdef PLD_SCK_PIN
char MIKROBUS1_getSCK()          
{
    return GPIO_PIN27_bit;
}
void MIKROBUS1_setSCK(char set)         
{
    GPIO_PIN27_bit = set;
}
char MIKROBUS2_getSCK()          
{
    return GPIO_PIN27_bit;
}
void MIKROBUS2_setSCK(char set)         
{
    GPIO_PIN27_bit = set;
}
#endif
#ifdef PLD_MISO_PIN
char MIKROBUS1_getMISO()         
{
    return GPIO_PIN30_bit;
}
void MIKROBUS1_setMISO(char set)        
{
    GPIO_PIN30_bit = set;
}
char MIKROBUS2_getMISO()         
{
    return GPIO_PIN30_bit;
}
void MIKROBUS2_setMISO(char set)        
{
    GPIO_PIN30_bit = set;
}
#endif
#ifdef PLD_MOSI_PIN
char MIKROBUS1_getMOSI()          
{
    return GPIO_PIN29_bit;
}
void MIKROBUS1_setMOSI(char set)         
{
    GPIO_PIN29_bit = set;
}
char MIKROBUS2_getMOSI()          
{
    return GPIO_PIN29_bit;
}
void MIKROBUS2_setMOSI(char set)         
{
    GPIO_PIN29_bit = set;
}
#endif
#ifdef PLD_PWM_PIN
char MIKROBUS1_getPWM()         
{
    return GPIO_PIN56_bit;
}
void MIKROBUS1_setPWM(char set)        
{
    GPIO_PIN56_bit = set;
}
char MIKROBUS2_getPWM()         
{
    return GPIO_PIN57_bit;
}
void MIKROBUS2_setPWM(char set)        
{
    GPIO_PIN57_bit = set;
}
#endif
#ifdef PLD_INT_PIN
char MIKROBUS1_getINT()         
{
    return GPIO_PIN3_bit;
}
void MIKROBUS1_setINT(char set)        
{
    GPIO_PIN3_bit = set;
}
char MIKROBUS2_getINT()         
{
    return GPIO_PIN5_bit;
}
void MIKROBUS2_setINT(char set)        
{
    GPIO_PIN5_bit = set;
}
#endif
#ifdef PLD_RX_PIN
char MIKROBUS1_getRX()         
{
    return GPIO_PIN53_bit;
}
void MIKROBUS1_setRX(char set)        
{
    GPIO_PIN53_bit = set;
}
char MIKROBUS2_getRX()         
{
    return GPIO_PIN53_bit;
}
void MIKROBUS2_setRX(char set)        
{
    GPIO_PIN53_bit = set;
}
#endif
#ifdef PLD_TX_PIN
char MIKROBUS1_getTX()         
{
    return GPIO_PIN52_bit;
}
void MIKROBUS1_setTX(char set)        
{
    GPIO_PIN52_bit = set;
}
char MIKROBUS2_getTX()         
{
    return GPIO_PIN52_bit;
}
void MIKROBUS2_setTX(char set)        
{
    GPIO_PIN52_bit = set;
}
#endif
#ifdef PLD_SCL_PIN
char MIKROBUS1_getSCL()         
{
    return GPIO_PIN44_bit;
}
void MIKROBUS1_setSCL(char set)        
{
    GPIO_PIN44_bit = set;
}
char MIKROBUS2_getSCL()         
{
    return GPIO_PIN44_bit;
}
void MIKROBUS2_setSCL(char set)        
{
    GPIO_PIN44_bit = set;
}
#endif
#ifdef PLD_SDA_PIN
char MIKROBUS1_getSDA()         
{
    return GPIO_PIN45_bit;
}
void MIKROBUS1_setSDA(char set)        
{
    GPIO_PIN45_bit = set;
}
char MIKROBUS2_getSDA()         
{
    return GPIO_PIN45_bit;
}
void MIKROBUS2_setSDA(char set)        
{
    GPIO_PIN45_bit = set;
}
#endif
#endif
#endif