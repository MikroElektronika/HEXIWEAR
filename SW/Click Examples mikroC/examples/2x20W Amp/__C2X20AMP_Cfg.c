#include "__C2X20AMP_Hal.h"
#ifdef  __MIKROC__

#ifdef  __C2X20AMP_SPI
#ifdef  __MIKROC_PRO_FOR_ARM__
#ifdef  __STM32__ 
const uint32_t _C2X20AMP_SPI_CFG[ 2 ] = 
{ 
	_SPI_FPCLK_DIV256, 
	_SPI_FIRST_CLK_EDGE_TRANSITION | 
	_SPI_CLK_IDLE_LOW | 
	_SPI_MASTER | 
	_SPI_MSB_FIRST |
	_SPI_8_BIT | 
	_SPI_SSM_ENABLE | 
	_SPI_SS_DISABLE | 
	_SPI_SSI_1
};
#endif
#ifdef __KINETIS__
const uint32_t _C2X20AMP_SPI_CFG[ 2 ] = 
{ 
	1000000,
	_SPI_CFG_CLK_PHASE_CAPT_LEADING | 
	_SPI_CFG_CLK_IDLE_LOW |
	_SPI_CFG_MASTER | 
	_SPI_CFG_MSB_FIRST |
	_SPI_CFG_FRAME_SIZE_8BITS | 
	_SPI_CFG_SELECT_CTAR0
};
#endif
#ifdef __MCHP__ 
const uint32_t _C2X20AMP_SPI_CFG[ 3 ] = 
{ 
	1000000,  
	_SPI_MSB_FIRST, 
	_SPI_CLK_IDLE_LOW | 
	_SPI_SAMPLE_DATA_RISING_EDGE 
};
#endif
#ifdef __TI__
#ifdef __MSP__
const uint32_t _C2X20AMP_SPI_CFG[ 7 ] = 
{ 
	_SPI_MASTER, 
	64, 
	_SPI_CLOCKSOURCE_SMCLK, 
	_SPI_MSB_FIRST, 
	_SPI_PHASE_DATA_CHANGE_FIRST_CAPTURE_NEXT, 
	_SPI_CLK_IDLE_HIGH, 
	_SPI_3PIN 
};
#else
const uint32_t _C2X20AMP_SPI_CFG[ 3 ] = 
{ 
	1000000, 
	_SPI_MASTER, 
	_SPI_8_BIT | 
	_SPI_CLK_IDLE_HIGH |
	_SPI_SECOND_CLK_EDGE_TRANSITION 
};
#endif
#endif
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
const uint32_t _C2X20AMP_SPI_CFG[ 4 ] = 
{ 
	_SPI_MASTER_OSC_DIV64, 
	_SPI_DATA_SAMPLE_MIDDLE, 
	_SPI_CLK_IDLE_LOW, 
	_SPI_LOW_2_HIGH 
};
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
const uint32_t _C2X20AMP_SPI_CFG[ 7 ] = 
{ 
	_SPI_MASTER, 
	_SPI_8_BIT, 
	80, 
	_SPI_SS_DISABLE, 
	_SPI_DATA_SAMPLE_MIDDLE, 
	_SPI_CLK_IDLE_LOW, 
	_SPI_IDLE_2_ACTIVE 
};
#endif
#ifdef  __MIKROC_PRO_FOR_DSPIC__ 
const uint32_t _C2X20AMP_SPI_CFG[ 8 ] = 
{ 
	_SPI_MASTER,
	_SPI_8_BIT, 
	_SPI_PRESCALE_SEC_4, 
	_SPI_PRESCALE_PRI_4, 
	_SPI_SS_DISABLE, 
	_SPI_DATA_SAMPLE_MIDDLE, 
	_SPI_CLK_IDLE_LOW, 
	_SPI_IDLE_2_ACTIVE 
};
#endif
#ifdef __MIKROC_PRO_FOR_AVR__ 
const uint32_t _C2X20AMP_SPI_CFG[ 3 ] = 
{ 
	_SPI_MASTER, 
	_SPI_FCY_DIV32, 
	_SPI_CLK_LO_LEADING 
};
#endif
#ifdef  __MIKROC_PRO_FOR_FT90x__   
const uint32_t _C2X20AMP_SPI_CFG[ 3 ] = 
{ 
	_SPI_MASTER_CLK_RATIO_256,
	_SPI_CFG_POLARITY_IDLE_HIGH |
	_SPI_CFG_PHASE_CAPTURE_RISING | 
	_SPI_CFG_SS_AUTO_DISABLE | 
	_SPI_CFG_FIFO_DISABLE, 
	_SPI_SS_LINE_NONE 
};
#endif
#endif

#ifdef  __C2X20AMP_I2C
#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef  __STM32__
const uint32_t _C2X20AMP_I2C_CFG[ 1 ] = 
{
	100000
};
#endif
#ifdef __KINETIS__
const uint32_t _C2X20AMP_I2C_CFG[ 1 ] = 
{
	100000
};
#endif
#ifdef __MCHP__
const uint32_t _C2X20AMP_I2C_CFG[ 1 ] = 
{ 
	_I2C_100KHZ 
};
#endif
#ifdef __TI__
#ifndef __MSP__
const uint32_t _C2X20AMP_I2C_CFG[ 1 ] = 
{ 
	_I2C_BITRATE_STANDARD_MODE 
};
#else
const uint32_t _C2X20AMP_I2C_CFG[ 1 ] = 
{
	100000
};
#endif
#endif
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
const uint32_t _C2X20AMP_I2C_CFG[ 1 ] = 
{
	100000
};
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
const uint32_t _C2X20AMP_I2C_CFG[ 1 ] = 
{
	100000
};
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
const uint32_t _C2X20AMP_I2C_CFG[ 1 ] = 
{
	100000
};
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
const uint32_t _C2X20AMP_I2C_CFG[ 1 ] = 
{
	100000
};
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
const uint32_t _C2X20AMP_I2C_CFG[ 2 ] =  
{
	_I2CM_SPEED_MODE_STANDARD, 
	_I2CM_SWAP_DISABLE
};
#endif
#endif

#ifdef __C2X20AMP_UART
#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __STM32__
const uint32_t _C2X20AMP_UART_CFG [ 4 ] = 
{
	9600, 
	_UART_8_BIT_DATA, 
    _UART_NOPARITY, 
    _UART_ONE_STOPBIT
};
#endif
#ifdef __TI__
#ifdef __MSP__
const uint32_t _C2X20AMP_UART_CFG[ 1 ] = 
{
	9600
};
#else
const uint32_t _C2X20AMP_UART_CFG[ 6 ] = 
{
	9600, 
	9600, 
	_UART_8_BIT_DATA, 
	_UART_NOPARITY,
    _UART_ONE_STOPBIT, 
    _UART_HIGH_SPEED
};
#endif
#endif
#ifdef __KINETIS__
const uint32_t _C2X20AMP_UART_CFG [ 4 ] = 
{
	9600,  
	_UART_8_BIT_DATA, 
	_UART_NOPARITY, 
	_UART_ONE_STOPBIT
};
#endif
#ifdef __MCHP__
const uint32_t _C2X20AMP_UART_CFG[ 1 ] = 
{
	9600
};
#endif
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
const uint32_t _C2X20AMP_UART_CFG[ 1 ] = 
{
	9600
};
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
const uint32_t _C2X20AMP_UART_CFG[ 1 ] = 
{
	9600
};
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
const uint32_t _C2X20AMP_UART_CFG[ 1 ] = 
{
	9600
};
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
const uint32_t _C2X20AMP_UART_CFG [ 3 ] = 
{
	9600, 
	_UART_NOPARITY, 
	_UART_ONE_STOPBIT
};
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
const uint32_t _C2X20AMP_UART_CFG[ 1 ] = 
{
	9600
};
#endif
#endif

#endif
