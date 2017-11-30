/*

    __THERMOJ_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file         __THERMOJ_Driver.c
@brief          THERMOJ Driver Source
@addtogroup     THERMOJ
@{

*/
/* -------------------------------------------------------------------------- */

#include "__THERMOJ_Hal.h"
#include "__THERMOJ_Hal.c"
#include "__THERMOJ_Driver.h"

/* ---------------------------------------------------------------- VARIABLES */

const uint8_t _THERMOJ_ADDRESS_VDD = 0x67;
const uint8_t _THERMOJ_ADDRESS_GND = 0x60;

const uint8_t _THERMOJ_HOT_JUNCTION     = 0x00;     //2 RO
const uint8_t _THERMOJ_DELTA_TEMP       = 0x01;     //2 RO
const uint8_t _THERMOJ_COLD_JUNCTION    = 0x02;     //2 RO

const uint8_t _THERMOJ_RAW_ADC          = 0x03;     //3 RO
const uint8_t _THERMOJ_STATUS           = 0x04;     //1 RW
const uint8_t _THERMOJ_SENSOR_CFG       = 0x05;     //1 RW
const uint8_t _THERMOJ_DEVICE_CFG       = 0x06;     //1 RW

const uint8_t _THERMOJ_ALERT1_CFG       = 0x08;     //1 RW
const uint8_t _THERMOJ_ALERT2_CFG       = 0x09;     //1 RW
const uint8_t _THERMOJ_ALERT3_CFG       = 0x0A;     //1 RW
const uint8_t _THERMOJ_ALERT4_CFG       = 0x0B;     //1 RW

const uint8_t _THERMOJ_ALERT1_HYST      = 0x0C;     //1 RW
const uint8_t _THERMOJ_ALERT2_HYST      = 0x0D;     //1 RW
const uint8_t _THERMOJ_ALERT3_HYST      = 0x0E;     //1 RW
const uint8_t _THERMOJ_ALERT4_HYST      = 0x0F;     //1 RW

const uint8_t _THERMOJ_ALERT1_LIMIT     = 0x10;     //2 RW
const uint8_t _THERMOJ_ALERT2_LIMIT     = 0x11;     //2 RW
const uint8_t _THERMOJ_ALERT3_LIMIT     = 0x12;     //2 RW
const uint8_t _THERMOJ_ALERT4_LIMIT     = 0x13;     //2 RW

const uint8_t _THERMOJ_DEVICE_ID        = 0x20;     //2 RO


/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */


void THERMOJ_write_byte(uint8_t slaveAddress, uint8_t registerAddress, uint8_t value)
{
    uint8_t slvAdd;
    uint8_t tmp_data[2];
   
    slvAdd = slaveAddress;
    tmp_data[0] = registerAddress;
    tmp_data[1] = value;
    
    HAL_i2cStart();
    HAL_i2cWrite(slvAdd, tmp_data , 2, END_MODE_STOP);
    

}

uint8_t THERMOJ_read_byte(uint8_t slaveAddress, uint8_t registerAddress)

{
    uint8_t slvAdd;
    uint8_t tmp_data[1];
    uint8_t value;

    slvAdd = slaveAddress;
    tmp_data[0] = registerAddress;

    HAL_i2cStart();
    HAL_i2cWrite(slvAdd, tmp_data , 1, END_MODE_RESTART);
    Delay_50us();
    Delay_10us();
    hal_i2cRead(slvAdd,tmp_data,1,END_MODE_STOP);
    
    value = tmp_data[0];

    return value;

}

void THERMOJ_write_2byte(uint8_t slaveAddress, uint8_t registerAddress, uint16_t value)
{
    uint8_t slvAdd;
    uint8_t tmp_data[3];
    uint16_t two_byte;

    two_byte = value;
    slvAdd = slaveAddress;
    tmp_data[0] = registerAddress;
    
    tmp_data[1] = (uint8_t)(two_byte >> 8 ) ;
    tmp_data[2] = (uint8_t)(two_byte & 0xFF);
    
    HAL_i2cStart();
    HAL_i2cWrite(slvAdd, tmp_data , 3, END_MODE_STOP);
    

}


float THERMOJ_getTemperature(uint8_t slaveAddress)

{
    
    uint8_t slaveAdd;
    uint8_t tmp_data[2];
    uint16_t temperature_raw;
    float tempValue;
     
    slaveAdd = slaveAddress;
     
    temperature_raw =  THERMOJ_read_2byte(slaveAdd, 0x00);

    tmp_data[0] = (uint8_t)(temperature_raw >> 8 ) ;
    tmp_data[1] = (uint8_t)(temperature_raw & 0xFF);

    if((tmp_data[0] & 0x80) == 0x80)                                                // TA < 0�C
    {                                             
    
        tmp_data[0] = tmp_data[0] & 0x7F;                                           // Clear SIGN
        tempValue = 1024 - (tmp_data[0]*16 + tmp_data[1] / 16);
    
    }
    
    else                                                                              // TA > 0�C
    
        tempValue = (tmp_data[0] * 16 + (float)tmp_data[1] / 16);      

    return tempValue; 
}

uint16_t THERMOJ_read_2byte(uint8_t slaveAddress, uint8_t registerAddress)

{
    uint8_t slvAdd;
    uint8_t tmp_data[2];
    uint16_t value;

    slvAdd = slaveAddress;
    tmp_data[0] = registerAddress;

    HAL_i2cStart();
    HAL_i2cWrite(slvAdd, tmp_data , 1, END_MODE_RESTART);
    Delay_50us();
    Delay_10us();
    hal_i2cRead(slvAdd,tmp_data,2,END_MODE_STOP);
    
    value = (tmp_data[0] << 8) | tmp_data[1];
    return value;

    

}
/* ----------------------------------------------------- HAL PUBLIC FUNCTIONS */

#ifdef __THERMOJ_GPIO

void 
HAL_THERMOJ_gpioInit
( 
        T_THERMOJ_GPIO_Set      ctlAN, 
        T_THERMOJ_GPIO_Get      ctlRST 
)
{
    fpAN   = ctlAN;      // Just an example
    fpRST  = ctlRST;     // Just an example
}

#ifdef __OBJECT_HAL__

#define _AN_PIN   0
#define _RST_PIN  1
#define _CS_PIN   2
#define _SCK_PIN  3
#define _MISO_PIN 4
#define _MOSI_PIN 5
#define _PWM_PIN  6
#define _INT_PIN  7
#define _RX_PIN   8
#define _TX_PIN   9
#define _SCL_PIN  10
#define _SDA_PIN  11

void HAL_THERMOJ_gpioMap(T_HAL_GPIO_OBJ gpioObj)
{
    T_THERMOJ_gpioObj const *tmp = (const T_THERMOJ_gpioObj*)gpioObj;

    fpAN   = tmp->gpioSet[ _AN_PIN ];
    fpRST  = tmp->gpioGet[ _RST_PIN ];
}

#undef _AN_PIN   
#undef _RST_PIN  
#undef _CS_PIN   
#undef _SCK_PIN  
#undef _MISO_PIN 
#undef _MOSI_PIN 
#undef _PWM_PIN  
#undef _INT_PIN  
#undef _RX_PIN   
#undef _TX_PIN   
#undef _SCL_PIN  
#undef _SDA_PIN  

#endif
#endif
#ifdef __THERMOJ_SPI
void HAL_THERMOJ_spiInit
( 
        T_THERMOJ_SPI_Write     fnWrite,
        T_THERMOJ_SPI_Read      fnRead 
)
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
}

#ifdef __OBJECT_HAL__
void HAL_THERMOJ_spiMap(T_HAL_SPI_OBJ spiObj)
{
    T_THERMOJ_spiObj const *tmp = (const T_THERMOJ_spiObj*)spiObj;

    fpWriteSPI = tmp->spiWrite;
    fpReadSPI  = tmp->spiRead;
}

#endif
#endif
#ifdef __THERMOJ_I2C
void HAL_THERMOJ_i2cInit
( 
        T_THERMOJ_I2C_Start     fnStart,
        T_THERMOJ_I2C_Stop      fnStop,
        T_THERMOJ_I2C_Restart   fnRestart,
        T_THERMOJ_I2C_Write     fnWrite,
        T_THERMOJ_I2C_Read      fnRead 
)
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}

#ifdef __OBJECT_HAL__
void HAL_THERMOJ_i2cMap(T_HAL_I2C_OBJ i2cObj)
{
    T_THERMOJ_i2cObj const *tmp = (const T_THERMOJ_i2cObj*)i2cObj;

    fpStartI2C    = tmp->i2cStart;
    fpStopI2C     = tmp->i2cStop;
    fpRestartI2C  = tmp->i2cRestart;
    fpWriteI2C    = tmp->i2cWrite;
    fpReadI2C     = tmp->i2cRead;
}

#endif
#endif
#ifdef __THERMOJ_UART
void HAL_THERMOJ_uartInit
( 
        T_THERMOJ_UART_Write   fnWrite,
        T_THERMOJ_UART_Read    fnRead,
        T_THERMOJ_UART_Ready   fnReady 
)
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}

#ifdef __OBJECT_HAL__
void HAL_THERMOJ_uartMap(T_HAL_UART_OBJ uartObj)
{
    T_THERMOJ_uartObj const *tmp = (const T_THERMOJ_uartObj*)uartObj;

    fpWriteUART = tmp->uartWrite;
    fpReadUART  = tmp->uartRead;
    fpReadyUART = tmp->uartReady;
}

#endif
#endif

/// @}
/* --------------------------------------------- MIKROC PERIPHERAL PARAMETERS */

#ifdef  __MIKROC__
#ifdef  __THERMOJ_SPI
#ifdef  __MIKROC_PRO_FOR_ARM__
#ifdef  __STM32__ 
const uint32_t _THERMOJ_SPI_CFG[ 2 ] = 
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
const uint32_t _THERMOJ_SPI_CFG[ 2 ] = 
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
const uint32_t _THERMOJ_SPI_CFG[ 3 ] = 
{ 
    1000000,  
    _SPI_MSB_FIRST, 
    _SPI_CLK_IDLE_LOW | 
    _SPI_SAMPLE_DATA_RISING_EDGE 
};
#endif
#ifdef __TI__
#ifdef __MSP__
const uint32_t _THERMOJ_SPI_CFG[ 7 ] = 
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
const uint32_t _THERMOJ_SPI_CFG[ 3 ] = 
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
const uint32_t _THERMOJ_SPI_CFG[ 4 ] = 
{ 
    _SPI_MASTER_OSC_DIV64, 
    _SPI_DATA_SAMPLE_MIDDLE, 
    _SPI_CLK_IDLE_LOW, 
    _SPI_LOW_2_HIGH 
};
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
const uint32_t _THERMOJ_SPI_CFG[ 7 ] = 
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
const uint32_t _THERMOJ_SPI_CFG[ 8 ] = 
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
const uint32_t _THERMOJ_SPI_CFG[ 3 ] = 
{ 
    _SPI_MASTER, 
    _SPI_FCY_DIV32, 
    _SPI_CLK_LO_LEADING 
};
#endif
#ifdef  __MIKROC_PRO_FOR_FT90x__   
const uint32_t _THERMOJ_SPI_CFG[ 3 ] = 
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

#ifdef  __THERMOJ_I2C
#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef  __STM32__
const uint32_t _THERMOJ_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __KINETIS__
const uint32_t _THERMOJ_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MCHP__
const uint32_t _THERMOJ_I2C_CFG[ 1 ] = 
{ 
    _I2C_100KHZ 
};
#endif
#ifdef __TI__
#ifndef __MSP__
const uint32_t _THERMOJ_I2C_CFG[ 1 ] = 
{ 
    _I2C_BITRATE_STANDARD_MODE 
};
#else
const uint32_t _THERMOJ_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#endif
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
const uint32_t _THERMOJ_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
const uint32_t _THERMOJ_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
const uint32_t _THERMOJ_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
const uint32_t _THERMOJ_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
const uint32_t _THERMOJ_I2C_CFG[ 2 ] =  
{
    _I2CM_SPEED_MODE_STANDARD, 
    _I2CM_SWAP_DISABLE
};
#endif
#endif

#ifdef __THERMOJ_UART
#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __STM32__
const uint32_t _THERMOJ_UART_CFG [ 4 ] = 
{
    9600, 
    _UART_8_BIT_DATA, 
    _UART_NOPARITY, 
    _UART_ONE_STOPBIT
};
#endif
#ifdef __TI__
#ifdef __MSP__
const uint32_t _THERMOJ_UART_CFG[ 1 ] = 
{
    9600
};
#else
const uint32_t _THERMOJ_UART_CFG[ 6 ] = 
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
const uint32_t _THERMOJ_UART_CFG [ 4 ] = 
{
    9600,  
    _UART_8_BIT_DATA, 
    _UART_NOPARITY, 
    _UART_ONE_STOPBIT
};
#endif
#ifdef __MCHP__
const uint32_t _THERMOJ_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
const uint32_t _THERMOJ_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
const uint32_t _THERMOJ_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
const uint32_t _THERMOJ_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
const uint32_t _THERMOJ_UART_CFG [ 3 ] = 
{
    9600, 
    _UART_NOPARITY, 
    _UART_ONE_STOPBIT
};
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
const uint32_t _THERMOJ_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#endif
#endif
/* -------------------------------------------------------------------------- */
/*
  __THERMOJ_Driver.c

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

    This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

----------------------------------------------------------------------------- */