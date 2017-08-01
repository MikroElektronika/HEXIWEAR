/*

    __LSM6DSL_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

--------------------------------------------------------------------------------

    Version      : 1.0.0
    Developer    : Djordje Rosic
    Date         : Jun 2017

------------------------------------------------------------------------------*/

#include <stdint.h>
#include "__LSM6DSL_Driver.h"

/*----------------------------------------------------------------------- HAL */
extern sfr sbit LSM6DSL_CS_PIN;

#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )

static void ( *fpWriteSPI )(unsigned int data_out);
static unsigned int ( *fpReadSPI )(unsigned int buffer);

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )

static void ( *fpWriteSPI )(unsigned char data_out);
static unsigned char( *fpReadSPI )(unsigned char dummy);

#elif defined( __MIKROC_PRO_FOR_PIC32__ )

static void ( *fpWriteSPI )(unsigned long data_out);
static unsigned long( *fpReadSPI )(unsigned long dummy);

#elif defined( __MIKROC_PRO_FOR_FT90x__ )

static void ( *fpWriteSPI )(unsigned char data_out);
static unsigned char ( *fpReadSPI )(unsigned char dummy);
#endif

static void halWrite(uint8_t *pBuf, uint16_t len);

static void halRead(uint8_t *pBuf, uint16_t len);

static void halTransfer(uint8_t *pIn, uint8_t *pOut, uint16_t len);

static void halWrite(uint8_t *pBuf, uint16_t len)
{
    uint8_t *ptr = pBuf;

    LSM6DSL_CS_PIN = 0;
    while( len-- )
        fpWriteSPI(*( ptr++ ));
        
    LSM6DSL_CS_PIN = 1;
}

static void halRead(uint8_t *pBuf, uint16_t len)
{
    uint8_t *ptr = pBuf;

    LSM6DSL_CS_PIN = 0;
    while( len-- )
        *ptr++ = fpReadSPI(0x00);
    LSM6DSL_CS_PIN = 1;
}

static void halTransfer(uint8_t* pIn, uint8_t* pOut, uint16_t len)
{
    uint8_t *in = pIn;
    uint8_t *out = pOut;

    LSM6DSL_CS_PIN = 0;
    while( len-- )
        *( out++ ) = fpReadSPI(*( in++ ));
    LSM6DSL_CS_PIN = 1;
}
/*------------------------------------------------------------- PREPROCESSORS */



/*--------------------------------------------------------------------- TYPES */



/*----------------------------------------------------------------- VARIABLES */



/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/*---------------------------------------------------------- PUBLIC FUNCTIONS */

void LSM6DSL_initDriver
(
    T_LSM6DSL_SPI_Write fnWrite,
    T_LSM6DSL_SPI_Read fnRead
)
{
    fpWriteSPI = fnWrite;
    fpReadSPI = fnRead;

    LSM6DSL_CS_PIN = 1;
}

/* Generic read and write functions */
uint8_t LSM6DSL_readRegister (uint8_t registerAddress)
{
    uint8_t pIn [2];
    uint8_t pOut [2];
    pIn [0] = registerAddress | 0x80;
    pIn [1] = 0;
    pOut [0] = 0;
    pOut [1] = 0;
    halTransfer (pIn, pOut, 2);
    return  pOut [1];
}
void LSM6DSL_writeRegister (uint8_t registerAddress, uint8_t writeData)
{
    uint8_t pIn [2];
    pIn [0] = registerAddress;
    pIn [1] = writeData;
    halWrite (pIn, 2);
}



void LSM6DSL_configureRead (uint8_t registerAddress, uint8_t configurationData)
{
     LSM6DSL_writeRegister (registerAddress, configurationData);
}

void LSM6DSL_readAccelerationXYZ (float * x, float * y, float * z, uint8_t fullScale)
{
    uint16_t tempValue = 0;
    float valueScaler = 0;

    if (fullScale == FULLSCALE_A_2) valueScaler = 0.061;
    if (fullScale == FULLSCALE_A_4) valueScaler = 0.122;
    if (fullScale == FULLSCALE_A_8) valueScaler = 0.244;
    if (fullScale == FULLSCALE_A_16) valueScaler = 0.488;
    
    tempValue = LSM6DSL_readRegister (0x29);
    tempValue = tempValue << 8;
    tempValue += LSM6DSL_readRegister (0x28);
    *x = tempValue;
    if (*x > 32767) *x-= 65534;
    *x = *x * valueScaler;
    
    tempValue = LSM6DSL_readRegister (0x2B);
    tempValue = tempValue << 8;
    tempValue += LSM6DSL_readRegister (0x2A);
    *y = tempValue;
    if (*y > 32767) *y-= 65534;
    *y = *y * valueScaler;
    
    tempValue = LSM6DSL_readRegister (0x2D);
    tempValue = tempValue << 8;
    tempValue += LSM6DSL_readRegister (0x2C);
    *z = tempValue;
    if (*z > 32767) *z-= 65534;
    *z = *z * valueScaler;
}

void LSM6DSL_readRotationXYZ (float * x, float * y, float * z, uint8_t fullScale)
{
    uint16_t tempValue = 0;
    float valueScaler = 0;

    if (fullScale == FULLSCALE_R_125) valueScaler = 4.375;
    if (fullScale == FULLSCALE_R_245) valueScaler = 8.75;
    if (fullScale == FULLSCALE_R_500) valueScaler = 17.50;
    if (fullScale == FULLSCALE_R_1000) valueScaler = 35;
    if (fullScale == FULLSCALE_R_2000) valueScaler = 70;

    tempValue = LSM6DSL_readRegister (0x23);
    tempValue = tempValue << 8;
    tempValue += LSM6DSL_readRegister (0x22);
    *x = tempValue;
    if (*x > 32767) *x-= 65534;
    *x = *x * valueScaler;

    tempValue = LSM6DSL_readRegister (0x25);
    tempValue = tempValue << 8;
    tempValue += LSM6DSL_readRegister (0x24);
    *y = tempValue;
    if (*y > 32767) *y-= 65534;
    *y = *y * valueScaler;

    tempValue = LSM6DSL_readRegister (0x27);
    tempValue = tempValue << 8;
    tempValue += LSM6DSL_readRegister (0x26);
    *z = tempValue;
    if (*z > 32767) *z-= 65534;
    *z = *z * valueScaler;
}

/*------------------------------------------------------------------------------

  __LSM6DSL_Driver.c

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

------------------------------------------------------------------------------*/