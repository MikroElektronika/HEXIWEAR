/*

    __THERMO6_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file         __THERMO6_Driver.c
@brief          THERMO6 Driver Source
@addtogroup     THERMO6
@{

*/
/* -------------------------------------------------------------------------- */

#include "__THERMO6_Hal.h"
#include "__THERMO6_Hal.c"
#include "__THERMO6_Driver.h"

/* ---------------------------------------------------------------- VARIABLES */


///@}

/*----------------------------------------------------------------- VARIABLES */

/** Thermo_6 click slave interface address */
const uint8_t _THERMO_6_ADDRESS         = 0x48;

const uint8_t CFG_HIGH_12_BIT           = 0X00;
const uint8_t CFG_LOW_12_BIT            = 0X60;

const uint8_t CFG_HIGH_10_BIT           = 0X00;
const uint8_t CFG_LOW_10_BIT            = 0X40;

const uint8_t CFG_HIGH_9_BIT            = 0X00;
const uint8_t CFG_LOW_9_BIT             = 0X20;

const uint8_t CFG_HIGH_8_BIT            = 0X00;
const uint8_t CFG_LOW_8_BIT             = 0X00;

/**
///@}
/**
 * @name    Thermo_6 Click Read Only Register
 *//*-------------------------------------------------------------------------*/
///@{
const uint8_t _THERMO6_TEMPERATURE = 0x00;   /**< Temperature Register Address */

///@}

///@}
/**
 * @name    Thermo_6 Click Read/Write Registers
 *//*-------------------------------------------------------------------------*/
///@{
const uint8_t _THERMO6_CONFIGURE = 0x01;     /**< Temperature Configuration RegisterAddress */
const uint8_t _THERMO6_THYST     = 0x02;     /**< Temperature Hysteresis Register Address */
const uint8_t _THERMO6_TOS       = 0x03;     /**< Temperature Threshold Register Address */


///@}

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

uint8_t THERMO6_readRegTemp(uint16_t *value)
{
    uint8_t err = 0;
    uint8_t tmp[1]; 
    uint8_t val[2];

    tmp[0] = _THERMO6_TEMPERATURE;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_THERMO_6_ADDRESS, tmp, 1, END_MODE_RESTART);
    err |= HAL_i2cRead(_THERMO_6_ADDRESS, val, 2, END_MODE_STOP);

    *value = (((uint16_t)val[0]) << 8) & 0xff00;    
    *value |= ((uint16_t)val[1]) & 0x00ff;

    return err;
}

uint8_t THERMO6_writeRegCfg(uint8_t valueHi,uint8_t valueLow)
{
    int err = 0;
    uint8_t tmp[2];
    tmp[0] = _THERMO6_CONFIGURE;
    tmp[1] = valueHi;
    tmp[2] = valueLow;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_THERMO_6_ADDRESS, tmp, 3, END_MODE_STOP);

    return err;
}

uint8_t THERMO6_readRegCfg(uint16_t *value)
{
    uint8_t err = 0;
    uint8_t tmp[1]; 
    uint8_t val[2];

    tmp[0] = _THERMO6_CONFIGURE;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_THERMO_6_ADDRESS, tmp, 1, END_MODE_RESTART);
    err |= HAL_i2cRead(_THERMO_6_ADDRESS, val, 2, END_MODE_STOP);

    *value = (((uint16_t)val[0]) << 8) & 0xff00;    
    *value |= ((uint16_t)val[1]) & 0x00ff;

    return err;
}

uint8_t THERMO6_writeRegHyst(uint8_t valueHi,uint8_t valueLow)
{
    int err = 0;
    uint8_t tmp[2];
    tmp[0] = _THERMO6_THYST;
    tmp[1] = valueHi;
    tmp[2] = valueLow;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_THERMO_6_ADDRESS, tmp, 3, END_MODE_STOP);

    return err;
}

uint8_t THERMO6_readRegHyst(uint16_t *value)
{
    uint8_t err = 0;
    uint8_t tmp[1]; 
    uint8_t val[2];

    tmp[0] = _THERMO6_THYST;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_THERMO_6_ADDRESS, tmp, 1, END_MODE_RESTART);
    err |= HAL_i2cRead(_THERMO_6_ADDRESS, val, 2, END_MODE_STOP);

    *value = (((uint16_t)val[0]) << 8) & 0xff00;    
    *value |= ((uint16_t)val[1]) & 0x00ff;

    return err;
}

uint8_t THERMO6_writeRegOs(uint8_t valueHi,uint8_t valueLow)
{
    int err = 0;
    uint8_t tmp[2];
    tmp[0] = _THERMO6_TOS;
    tmp[1] = valueHi;
    tmp[2] = valueLow;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_THERMO_6_ADDRESS, tmp, 3, END_MODE_STOP);

    return err;
}

uint8_t THERMO6_readRegOs(uint16_t *value)
{
    uint8_t err = 0;
    uint8_t tmp[1]; 
    uint8_t val[2];

    tmp[0] = _THERMO6_TOS;

    err |= HAL_i2cStart();
    err |= HAL_i2cWrite(_THERMO_6_ADDRESS, tmp, 1, END_MODE_RESTART);
    err |= HAL_i2cRead(_THERMO_6_ADDRESS, val, 2, END_MODE_STOP);

    *value = (((uint16_t)val[0]) << 8) & 0xff00;    
    *value |= ((uint16_t)val[1]) & 0x00ff;

    return err;
}

float THERMO6_getTemperature()
{
    float temperature;
    uint16_t result;
    uint16_t  value;
    result = 0;
    value =  0;
    THERMO6_readRegTemp(&value);

    if ((result & 0x8000) == 0)
        {
            result = value >> 4;
            temperature = (float)result * 0.0625;
            return temperature;
        }
   else 
        { 
            result = value >> 4;
            temperature = (float)result *(-0.0625);
            return temperature;
        }
}

/* ----------------------------------------------------- HAL PUBLIC FUNCTIONS */

#ifdef __THERMO6_GPIO

void 
HAL_THERMO6_gpioInit
( 
        T_THERMO6_GPIO_Set      ctlAN, 
        T_THERMO6_GPIO_Get      ctlRST 
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

void HAL_THERMO6_gpioMap(T_HAL_GPIO_OBJ gpioObj)
{
    T_THERMO6_gpioObj const *tmp = (const T_THERMO6_gpioObj*)gpioObj;

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
#ifdef __THERMO6_SPI
void HAL_THERMO6_spiInit
( 
        T_THERMO6_SPI_Write     fnWrite,
        T_THERMO6_SPI_Read      fnRead 
)
{
    fpWriteSPI = fnWrite;
    fpReadSPI  = fnRead;
}

#ifdef __OBJECT_HAL__
void HAL_THERMO6_spiMap(T_HAL_SPI_OBJ spiObj)
{
    T_THERMO6_spiObj const *tmp = (const T_THERMO6_spiObj*)spiObj;

    fpWriteSPI = tmp->spiWrite;
    fpReadSPI  = tmp->spiRead;
}

#endif
#endif
#ifdef __THERMO6_I2C
void HAL_THERMO6_i2cInit
( 
        T_THERMO6_I2C_Start     fnStart,
        T_THERMO6_I2C_Stop      fnStop,
        T_THERMO6_I2C_Restart   fnRestart,
        T_THERMO6_I2C_Write     fnWrite,
        T_THERMO6_I2C_Read      fnRead 
)
{
    fpStartI2C    = fnStart;
    fpStopI2C     = fnStop;
    fpRestartI2C  = fnRestart;
    fpWriteI2C    = fnWrite;
    fpReadI2C     = fnRead;
}

#ifdef __OBJECT_HAL__
void HAL_THERMO6_i2cMap(T_HAL_I2C_OBJ i2cObj)
{
    T_THERMO6_i2cObj const *tmp = (const T_THERMO6_i2cObj*)i2cObj;

    fpStartI2C    = tmp->i2cStart;
    fpStopI2C     = tmp->i2cStop;
    fpRestartI2C  = tmp->i2cRestart;
    fpWriteI2C    = tmp->i2cWrite;
    fpReadI2C     = tmp->i2cRead;
}

#endif
#endif
#ifdef __THERMO6_UART
void HAL_THERMO6_uartInit
( 
        T_THERMO6_UART_Write   fnWrite,
        T_THERMO6_UART_Read    fnRead,
        T_THERMO6_UART_Ready   fnReady 
)
{
    fpWriteUART = fnWrite;
    fpReadUART  = fnRead;
    fpReadyUART = fnReady;
}

#ifdef __OBJECT_HAL__
void HAL_THERMO6_uartMap(T_HAL_UART_OBJ uartObj)
{
    T_THERMO6_uartObj const *tmp = (const T_THERMO6_uartObj*)uartObj;

    fpWriteUART = tmp->uartWrite;
    fpReadUART  = tmp->uartRead;
    fpReadyUART = tmp->uartReady;
}

#endif
#endif

/// @}
/* --------------------------------------------- MIKROC PERIPHERAL PARAMETERS */

#ifdef  __MIKROC__
#ifdef  __THERMO6_SPI
#ifdef  __MIKROC_PRO_FOR_ARM__
#ifdef  __STM32__ 
const uint32_t _THERMO6_SPI_CFG[ 2 ] = 
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
const uint32_t _THERMO6_SPI_CFG[ 2 ] = 
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
const uint32_t _THERMO6_SPI_CFG[ 3 ] = 
{ 
    1000000,  
    _SPI_MSB_FIRST, 
    _SPI_CLK_IDLE_LOW | 
    _SPI_SAMPLE_DATA_RISING_EDGE 
};
#endif
#ifdef __TI__
#ifdef __MSP__
const uint32_t _THERMO6_SPI_CFG[ 7 ] = 
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
const uint32_t _THERMO6_SPI_CFG[ 3 ] = 
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
const uint32_t _THERMO6_SPI_CFG[ 4 ] = 
{ 
    _SPI_MASTER_OSC_DIV64, 
    _SPI_DATA_SAMPLE_MIDDLE, 
    _SPI_CLK_IDLE_LOW, 
    _SPI_LOW_2_HIGH 
};
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
const uint32_t _THERMO6_SPI_CFG[ 7 ] = 
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
const uint32_t _THERMO6_SPI_CFG[ 8 ] = 
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
const uint32_t _THERMO6_SPI_CFG[ 3 ] = 
{ 
    _SPI_MASTER, 
    _SPI_FCY_DIV32, 
    _SPI_CLK_LO_LEADING 
};
#endif
#ifdef  __MIKROC_PRO_FOR_FT90x__   
const uint32_t _THERMO6_SPI_CFG[ 3 ] = 
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

#ifdef  __THERMO6_I2C
#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef  __STM32__
const uint32_t _THERMO6_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __KINETIS__
const uint32_t _THERMO6_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MCHP__
const uint32_t _THERMO6_I2C_CFG[ 1 ] = 
{ 
    _I2C_100KHZ 
};
#endif
#ifdef __TI__
#ifndef __MSP__
const uint32_t _THERMO6_I2C_CFG[ 1 ] = 
{ 
    _I2C_BITRATE_STANDARD_MODE
};
#else
const uint32_t _THERMO6_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#endif
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
const uint32_t _THERMO6_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
const uint32_t _THERMO6_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
const uint32_t _THERMO6_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
const uint32_t _THERMO6_I2C_CFG[ 1 ] = 
{
    100000
};
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
const uint32_t _THERMO6_I2C_CFG[ 2 ] =  
{
    _I2CM_SPEED_MODE_STANDARD, 
    _I2CM_SWAP_DISABLE
};
#endif
#endif

#ifdef __THERMO6_UART
#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __STM32__
const uint32_t _THERMO6_UART_CFG [ 4 ] = 
{
    9600, 
    _UART_8_BIT_DATA, 
    _UART_NOPARITY, 
    _UART_ONE_STOPBIT
};
#endif
#ifdef __TI__
#ifdef __MSP__
const uint32_t _THERMO6_UART_CFG[ 1 ] = 
{
    9600
};
#else
const uint32_t _THERMO6_UART_CFG[ 6 ] = 
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
const uint32_t _THERMO6_UART_CFG [ 4 ] = 
{
    9600,  
    _UART_8_BIT_DATA, 
    _UART_NOPARITY, 
    _UART_ONE_STOPBIT
};
#endif
#ifdef __MCHP__
const uint32_t _THERMO6_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#endif
#ifdef __MIKROC_PRO_FOR_PIC__
const uint32_t _THERMO6_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#ifdef __MIKROC_PRO_FOR_PIC32__
const uint32_t _THERMO6_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#ifdef __MIKROC_PRO_FOR_DSPIC__
const uint32_t _THERMO6_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#ifdef __MIKROC_PRO_FOR_AVR__
const uint32_t _THERMO6_UART_CFG [ 3 ] = 
{
    9600, 
    _UART_NOPARITY, 
    _UART_ONE_STOPBIT
};
#endif
#ifdef __MIKROC_PRO_FOR_FT90x__
const uint32_t _THERMO6_UART_CFG[ 1 ] = 
{
    9600
};
#endif
#endif
#endif
/* -------------------------------------------------------------------------- */
/*
  __THERMO6_Driver.c

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