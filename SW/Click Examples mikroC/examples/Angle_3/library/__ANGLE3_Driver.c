/*

    __ANGLE3_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

--------------------------------------------------------------------------------

    Version      : 1.0.0
    Developer    : Aleksandar Zecevic
    Date         : 12.05.2017.

------------------------------------------------------------------------------*/

#include <stdint.h>
#include "__ANGLE3_Driver.h"

/*----------------------------------------------------------------------- HAL */
extern sfr sbit ANGLE3_CS_PIN;
extern sfr sbit ANGLE3_ERR_PIN;

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

    while( len-- )
        fpWriteSPI(*( ptr++ ));
}

static void halRead(uint8_t *pBuf, uint16_t len)
{
    uint8_t *ptr = pBuf;

    while( len-- )
        *ptr++ = fpReadSPI(0x00);
}

static void halTransfer(uint8_t* pIn, uint8_t* pOut, uint16_t len)
{
    uint8_t *in = pIn;
    uint8_t *out = pOut;

    while( len-- )
        *( out++ ) = fpReadSPI(*( in++ ));
}
/*------------------------------------------------------------- PREPROCESSORS */



/*--------------------------------------------------------------------- TYPES */



/*----------------------------------------------------------------- VARIABLES */



/*--------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/*---------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/*---------------------------------------------------------- PUBLIC FUNCTIONS */

void ANGLE3_initDriver
(
    T_ANGLE3_SPI_Write fnWrite, 
    T_ANGLE3_SPI_Read fnRead
)
{
    fpWriteSPI = fnWrite;
    fpReadSPI = fnRead;

    ANGLE3_CS_PIN = 1;
}

void ANGLE3_writeData(uint8_t opcode, uint8_t address, uint16_t _data)
{
    uint8_t buffer[3];

    // Address must be shifted left.
    address <<= 1;

    // Prepare buffer to send via SPI.
    buffer[0] = (opcode << 4) | (address >> 4);
    buffer[1] = (address << 4) | ((_data >> 8) & 0x0F);
    buffer[2] = _data & 0xFF;

    // Write to Angle3 via SPI.
    ANGLE3_CS_PIN = 0;
    Delay_us(10);
    halWrite(buffer, 3);
    Delay_us(10);
    ANGLE3_CS_PIN = 1;
}

uint16_t ANGLE3_readData(uint8_t opcode, uint8_t address)
{
    uint8_t buffer[3];

    // Address must be shifted left.
    address <<= 1;

    // Prepare buffer to send via SPI.
    buffer[0] = (opcode << 4) | (address >> 4);
    buffer[1] = address << 4;
    buffer[2] = 0x00;

    // Read from Angle3 via SPI.
    ANGLE3_CS_PIN = 0;
    Delay_us(10);
    halTransfer(buffer, buffer, 3);
    Delay_us(10);
    ANGLE3_CS_PIN = 1;

    // Return the read value as a 16-bit integer.
    return ((uint16_t)buffer[1] << 8) | buffer[2];
}

void ANGLE3_writeEEPROM(uint8_t address, uint16_t _data)
{
    // Write data to EEPROM, using _ANGLE3_WRITE_EEPROM command.
    ANGLE3_writeData(_ANGLE3_WRITE_EEPROM, address, _data);
}

uint16_t ANGLE3_readEEPROM(uint8_t address)
{
    uint8_t _data;

    // Read data from EEPROM, using _ANGLE3_READ_EEPROM command.
    _data = ANGLE3_readData(_ANGLE3_READ_EEPROM, address);

    // Only the lower 12 bits are valid.
    return _data & 0x0FFF;
}

void ANGLE3_lockEEPROM()
{
    // Write 0x00 (lock) to _ANGLE3_E_MLK in EEPROM.
    ANGLE3_writeEEPROM(_ANGLE3_E_MLK, 0x00);
}

void ANGLE3_writeRegister(uint8_t address, uint16_t _data)
{
    // Write data to registers, using _ANGLE3_WRITE_REGISTER command.
    ANGLE3_writeData(_ANGLE3_WRITE_REGISTER, address, _data);
}

uint16_t ANGLE3_readRegister(uint8_t address)
{
    uint8_t _data;

    // Read data from registers, using _ANGLE3_READ_REGISTER command.
    _data = ANGLE3_readData(_ANGLE3_READ_REGISTER, address);

    // Only the lower 12 bits are valid.
    return _data & 0x0FFF;
}

void ANGLE3_setMode(uint16_t mode)
{
    // Write mode to _ANGLE3_R_CHMD, using _ANGLE3_CHANGE_MODE command.
    ANGLE3_writeData(_ANGLE3_CHANGE_MODE, _ANGLE3_R_CHMD, mode);
}

void ANGLE3_setNormalMode()
{
    // Set mode to _ANGLE3_NORMAL_MODE.
    ANGLE3_setMode(_ANGLE3_NORMAL_MODE);
}

void ANGLE3_setUserMode()
{
    // Set mode to _ANGLE3_USER_MODE.
    ANGLE3_setMode(_ANGLE3_USER_MODE);
}

uint16_t ANGLE3_readAngleData()
{
    // Read angle data. There is no address.
    return ANGLE3_readData(_ANGLE3_READ_ANGLE, 0x00);
}

uint32_t ANGLE3_calculateDegrees(uint16_t angle)
{
    // The sensor will return values from 0 to 4095.
    // Convert to degrees like this.
    return (360 * (uint32_t)angle) / 4096;
}

uint8_t ANGLE3_readErrorPin()
{
    return ANGLE3_ERR_PIN;
}

/*------------------------------------------------------------------------------

  __ANGLE3_Driver.c

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