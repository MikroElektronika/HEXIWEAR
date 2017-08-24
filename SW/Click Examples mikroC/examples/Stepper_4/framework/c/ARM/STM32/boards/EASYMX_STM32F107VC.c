#include "MIKROBUS_framework.h"

#ifdef EASYMX_STM32_V7
#ifdef STM32F107VC
void MIKROBUS_gpioDirection(T_MIKROBUS_slot bus, T_MIKROBUS_pin pin, T_GPIO_direction dir)
{
    if( bus == MIKROBUS1 )
    {
        switch( pin ) 
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOA_BASE, _GPIO_PINMASK_4);  else GPIO_Digital_Output(&GPIOA_BASE, _GPIO_PINMASK_4);  break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_2);  else GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_2);  break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_13); else GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_13); break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_10); else GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_10); break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_11); else GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_11); break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_12); else GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_12); break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOA_BASE, _GPIO_PINMASK_0);  else GPIO_Digital_Output(&GPIOA_BASE, _GPIO_PINMASK_0);  break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_10); else GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_10); break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_9);  else GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_9);  break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_8);  else GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_8);  break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOB_BASE, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&GPIOB_BASE, _GPIO_PINMASK_6);  break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOB_BASE, _GPIO_PINMASK_7);  else GPIO_Digital_Output(&GPIOB_BASE, _GPIO_PINMASK_7);  break;
            default : break; 
        }
    }
    if( bus == MIKROBUS2 )
    {
        switch( pin )
        {
            case MIKROBUS_AN_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOA_BASE, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIOA_BASE, _GPIO_PINMASK_5);  break;
            case MIKROBUS_RST_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_3);  else GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_3);  break;
            case MIKROBUS_CS_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_14); else GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_14); break;
            case MIKROBUS_SCK_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_10); else GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_10); break;
            case MIKROBUS_MISO_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_11); else GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_11); break;
            case MIKROBUS_MOSI_PIN : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_12); else GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_12); break;
            case MIKROBUS_PWM_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_12); else GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_12); break;
            case MIKROBUS_INT_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_11); else GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_11); break;
            case MIKROBUS_RX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_6);  break;
            case MIKROBUS_TX_PIN   : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_5);  else GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_5);  break;
            case MIKROBUS_SCL_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOB_BASE, _GPIO_PINMASK_6);  else GPIO_Digital_Output(&GPIOB_BASE, _GPIO_PINMASK_6);  break;
            case MIKROBUS_SDA_PIN  : if(dir == GPIO_INPUT) GPIO_Digital_Input(&GPIOB_BASE, _GPIO_PINMASK_7);  else GPIO_Digital_Output(&GPIOB_BASE, _GPIO_PINMASK_7);  break;
            default : break;
        }
    }
}

#ifdef __SPI_CLICK
void MIKROBUS1_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI3_Init_Advanced( (unsigned char)cfg[0], (long)cfg[1], &_GPIO_MODULE_SPI3_PC10_11_12 );
    fCall( SPI3_Write, SPI3_Read );
}
void MIKROBUS2_spiDriverMap( T_SPI_initializer fpInit, const uint32_t *cfg ) 
{
    T_SPI_initializer fCall = fpInit;
    SPI3_Init_Advanced( (unsigned char)cfg[0], (long)cfg[1], &_GPIO_MODULE_SPI3_PC10_11_12 );
    fCall( SPI3_Write, SPI3_Read );
}
#endif
#ifdef __I2C_CLICK
void MIKROBUS1_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2C1_Init_Advanced( cfg[0], &_GPIO_MODULE_I2C1_PB67 );
    fCall( I2C1_Start, 0, 0, I2C1_Write, I2C1_Read );
}
void MIKROBUS2_i2cDriverMap( T_I2C_initializer fpInit, const uint32_t *cfg )
{
    T_I2C_initializer fCall = fpInit;
    I2C1_Init_Advanced( cfg[0], &_GPIO_MODULE_I2C1_PB67 );
    fCall( I2C1_Start, 0, 0, I2C1_Write, I2C1_Read );
}
#endif
#ifdef __UART_CLICK
void MIKROBUS1_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART3_Init_Advanced( cfg[0] );
    fCall( UART3_Write, UART3_Read, UART3_Data_Ready );
}
void MIKROBUS2_uartDriverMap( T_UART_initializer fpInit, const uint32_t *cfg )
{
    T_UART_initializer fCall = fpInit;
    UART2_Init( cfg[0] );
    fCall( UART2_Write, UART2_Read, UART2_Data_Ready );
}
#endif
#ifdef PLD_AN_PIN
char MIKROBUS1_getAN()          
{
    return GPIOA_IDR.B4;
}
void MIKROBUS1_setAN(char set)         
{
    GPIOA_ODR.B4 = set;
}
char MIKROBUS2_getAN()          
{
    return GPIOA_IDR.B5;
}
void MIKROBUS2_setAN(char set)         
{
    GPIOA_ODR.B5 = set;
}
#endif
#ifdef PLD_RST_PIN
char MIKROBUS1_getRST()         
{
    return GPIOC_IDR.B2;
}
void MIKROBUS1_setRST(char set)        
{
    GPIOC_ODR.B2 = set;
}
char MIKROBUS2_getRST()         
{
    return GPIOC_IDR.B3;
}
void MIKROBUS2_setRST(char set)        
{
    GPIOC_ODR.B3 = set;
}
#endif
#ifdef PLD_CS_PIN
char MIKROBUS1_getCS()          
{
    return GPIOD_IDR.B13;
}
void MIKROBUS1_setCS(char set)         
{
    GPIOD_ODR.B13 = set;
}
char MIKROBUS2_getCS()          
{
    return GPIOD_IDR.B14;
}
void MIKROBUS2_setCS(char set)         
{
    GPIOD_ODR.B14 = set;
}
#endif
#ifdef PLD_SCK_PIN
char MIKROBUS1_getSCK()          
{
    return GPIOC_IDR.B10;
}
void MIKROBUS1_setSCK(char set)         
{
    GPIOC_ODR.B10 = set;
}
char MIKROBUS2_getSCK()          
{
    return GPIOC_IDR.B10;
}
void MIKROBUS2_setSCK(char set)         
{
    GPIOC_ODR.B10 = set;
}
#endif
#ifdef PLD_MISO_PIN
char MIKROBUS1_getMISO()         
{
    return GPIOC_IDR.B11;
}
void MIKROBUS1_setMISO(char set)        
{
    GPIOC_ODR.B11 = set;
}
char MIKROBUS2_getMISO()         
{
    return GPIOC_IDR.B11;
}
void MIKROBUS2_setMISO(char set)        
{
    GPIOC_ODR.B11 = set;
}
#endif
#ifdef PLD_MOSI_PIN
char MIKROBUS1_getMOSI()          
{
    return GPIOC_IDR.B12;
}
void MIKROBUS1_setMOSI(char set)         
{
    GPIOC_ODR.B12 = set;
}
char MIKROBUS2_getMOSI()          
{
    return GPIOC_IDR.B12;
}
void MIKROBUS2_setMOSI(char set)         
{
    GPIOC_ODR.B12 = set;
}
#endif
#ifdef PLD_PWM_PIN
char MIKROBUS1_getPWM()         
{
    return GPIOA_IDR.B0;
}
void MIKROBUS1_setPWM(char set)        
{
    GPIOA_ODR.B0 = set;
}
char MIKROBUS2_getPWM()         
{
    return GPIOD_IDR.B12;
}
void MIKROBUS2_setPWM(char set)        
{
    GPIOD_ODR.B12 = set;
}
#endif
#ifdef PLD_INT_PIN
char MIKROBUS1_getINT()         
{
    return GPIOD_IDR.B10;
}
void MIKROBUS1_setINT(char set)        
{
    GPIOD_ODR.B10 = set;
}
char MIKROBUS2_getINT()         
{
    return GPIOD_IDR.B12;
}
void MIKROBUS2_setINT(char set)        
{
    GPIOD_ODR.B12 = set;
}
#endif
#ifdef PLD_RX_PIN
char MIKROBUS1_getRX()         
{
    return GPIOD_IDR.B9;
}
void MIKROBUS1_setRX(char set)        
{
    GPIOD_ODR.B9 = set;
}
char MIKROBUS2_getRX()         
{
    return GPIOD_IDR.B6;
}
void MIKROBUS2_setRX(char set)        
{
    GPIOD_ODR.B6 = set;
}
#endif
#ifdef PLD_TX_PIN
char MIKROBUS1_getTX()         
{
    return GPIOD_IDR.B8;
}
void MIKROBUS1_setTX(char set)        
{
    GPIOD_ODR.B8 = set;
}
char MIKROBUS2_getTX()         
{
    return GPIOD_IDR.B5;
}
void MIKROBUS2_setTX(char set)        
{
    GPIOD_ODR.B5 = set;
}
#endif
#ifdef PLD_SCL_PIN
char MIKROBUS1_getSCL()         
{
    return GPIOB_IDR.B6;
}
void MIKROBUS1_setSCL(char set)        
{
    GPIOB_ODR.B6 = set;
}
char MIKROBUS2_getSCL()         
{
    return GPIOB_IDR.B6;
}
void MIKROBUS2_setSCL(char set)        
{
    GPIOB_ODR.B6 = set;
}
#endif
#ifdef PLD_SDA_PIN
char MIKROBUS1_getSDA()         
{
    return GPIOB_IDR.B7;
}
void MIKROBUS1_setSDA(char set)        
{
    GPIOB_ODR.B7 = set;
}
char MIKROBUS2_getSDA()         
{
    return GPIOB_IDR.B7;
}
void MIKROBUS2_setSDA(char set)        
{
    GPIOB_ODR.B7 = set;
}
#endif
#endif
#endif