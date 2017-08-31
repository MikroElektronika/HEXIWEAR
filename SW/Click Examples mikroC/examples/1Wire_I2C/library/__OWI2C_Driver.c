/*

    __OWI2C_Driver.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

----------------------------------------------------------------------------- */

/**
@file         __OWI2C_Driver.c
@brief          OWI2C Driver Source
@addtogroup     OWI2C
@{

*/
/* -------------------------------------------------------------------------- */

#include "__OWI2C_Driver.h"

/* ---------------------------------------------------------------- VARIABLES */

uint32_t * _OWI2C_OW_PORT;
uint8_t _OWI2C_OW_PIN;


const uint8_t OWI2C_WRITE_NORMAL                                     = 0x4B;
const uint8_t OWI2C_WRITE_NORMAL_NOSTOP                              = 0x5A;
const uint8_t OWI2C_WRITE_DATA_ONLY_WITHSTOP                         = 0x78;
const uint8_t OWI2C_WRITE_DATA_ONLY_NOSTOP                           = 0x69;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint16_t _OWI2C_crc16( uint8_t *pData, uint8_t len);

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */


/*
 * CRC calculation, but returns bytes in reversed order!
 */
static uint16_t _OWI2C_crc16( uint8_t *pData, uint8_t len)
{
     uint16_t crc;
     uint8_t i;
     uint8_t j;
     uint8_t mix;
     uint8_t inByte;
     crc = 0;
     for (i = 0; i < len;i++)
     {
           inByte = pData[i];
           for (j = 0; j < 8; j++)
           {
                 mix = (crc ^ inByte) & 0x01;
                 crc = crc >> 1;
                 if (mix)
                       crc = crc ^ 0xA001;

                 inByte = inByte >> 1;
           }
     }
     crc = ~crc;
     return crc;
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

void OWI2C_pinSet (uint32_t * pOwPort, uint32_t owPin)
{
    _OWI2C_OW_PORT = pOwPort;
    _OWI2C_OW_PIN = owPin;
    
}
////////////////////////////////////////////////////////////////////////////////
/// ROM functions
////////////////////////////////////////////////////////////////////////////////

void OWI2C_readRom (uint8_t *pData)
{
    uint8_t i;
    
    Ow_Reset(_OWI2C_OW_PORT, _OWI2C_OW_PIN);
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, 0x33);
    
    for (i = 0; i < 8; i++)
    {
        pData[i] = Ow_Read (_OWI2C_OW_PORT, _OWI2C_OW_PIN);
    }
}

void OWI2C_matchRom (uint8_t *pData)
{
    uint8_t i;

    Ow_Reset(_OWI2C_OW_PORT, _OWI2C_OW_PIN);
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, 0x55);

    for (i = 0; i < 8; i++)
    {
        Ow_Write (_OWI2C_OW_PORT, _OWI2C_OW_PIN, pData[i]);
    }
}

void OWI2C_skipRom ()
{
    Ow_Reset(_OWI2C_OW_PORT, _OWI2C_OW_PIN);
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, 0xCC);
}

void OWI2C_resume ()
{
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, 0xA5);
}

void OWI2C_skipRomOverdrive ()
{
    Ow_Reset(_OWI2C_OW_PORT, _OWI2C_OW_PIN);
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, 0x3C);
}

void OWI2C_matchRomOverdrive (uint8_t *pData)
{
    uint8_t i;

    Ow_Reset(_OWI2C_OW_PORT, _OWI2C_OW_PIN);
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, 0x69);

    for (i = 0; i < 8; i++)
    {
        Ow_Write (_OWI2C_OW_PORT, _OWI2C_OW_PIN, pData[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// I2C functions
////////////////////////////////////////////////////////////////////////////////

uint8_t OWI2C_readI2C ( uint8_t i2cAddress, uint8_t readLength, uint8_t *pData)
{
    uint8_t i;
    uint8_t status;
    
// CRC calculation
    uint16_t CRCResult;
    uint8_t CRCPacket [3];

    i2cAddress <<= 1;
    i2cAddress ++;      //Address needs to be shifted before sending

    CRCPacket [0] = 0x87;
    CRCPacket [1] = i2cAddress;
    CRCPacket [2] = readLength;

    CRCResult = _OWI2C_crc16 (CRCPacket, 3);

    CRCPacket [0] = CRCResult & 0x00FF;   //bytes are in reversed order
    CRCPacket [1] = ( CRCResult >> 8 ) & 0x00FF;
// CRC calculation end

    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, 0x87);         //command
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, i2cAddress);   //i2c address
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, readLength);   //rdLength

    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, CRCPacket [0]);   //CRC
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, CRCPacket [1]);   //CRC


    status = Ow_Read(_OWI2C_OW_PORT, _OWI2C_OW_PIN);
    // <= here is intentional, one additional byte must be read. see below
    for (i = 0; i <= readLength; i++)
    {
        pData[i] = Ow_Read(_OWI2C_OW_PORT, _OWI2C_OW_PIN);    //read data
    }
    
    
    /*
     * I-wire I2C click sends one '0' bit before reading starts as a signal. This
     * byte is read by the Ow_Read function, so everything needs to be shifted by
     * one bit. This is done below. This is the reason additional byte needs to be
     * read.
     */
    status >>= 1;
    status |= ((0x01 & pData[0])*0x80);
    i = 0;
    while (i < readLength)
    {
        pData[i] >>= 1;
        pData[i] |= ((0x01 & pData[i+1])*0x80);
        i++;
    }
    return status;
}


uint16_t OWI2C_writeI2C ( uint8_t commandByte, uint8_t i2cAddress,
                    uint8_t writeLength, uint8_t *pData)
{
    uint8_t i;
    uint8_t status;
    uint8_t writeStatus;

// CRC calculation
    uint16_t CRCResult;
    uint8_t CRCPacket [255];
    
    i2cAddress <<= 1;    //Address needs to be shifted before sending
    
    CRCPacket [0] = commandByte;
    if ( (commandByte == 0x4B) || (commandByte == 0x5A) )
    {
        CRCPacket [1] = i2cAddress;
        CRCPacket [2] = writeLength;
        for (i = 0; i < writeLength; i++)
        {
            CRCPacket [i+3] = pData [i];
        }
        CRCResult = _OWI2C_crc16 (CRCPacket, writeLength + 3);
    }
    else
    if ( (commandByte == 0x69) || (commandByte == 0x78) )
    {
        CRCPacket [1] = writeLength;
        for (i = 0; i < writeLength; i++)
        {
            CRCPacket [i+2] = pData [i];
        }
        CRCResult = _OWI2C_crc16 (CRCPacket, writeLength + 2);
    }
   
    CRCPacket [0] = CRCResult & 0x00FF;   //bytes are in reversed order
    CRCPacket [1] = ( CRCResult >> 8 ) & 0x00FF;
// CRC calculation end

    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, commandByte);      //command
    
    if ( (commandByte == 0x4B) || (commandByte == 0x5A) )
    {
        Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, i2cAddress);   //i2c address
    }
    
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, writeLength);      //wrlength

    for (i = 0; i < writeLength; i++)
    {
        Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, pData [i]);    //write data
    }
    
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, CRCPacket [0]);   //CRC
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, CRCPacket [1]);   //CRC
    
    
    
/*
 * I-wire I2C click sends one '0' bit before reading starts as a signal. This
 * byte is read by the Ow_Read function, so everything needs to be shifted by
 * one bit. This is done below. This is the reason additional byte needs to be
 * read.
 */
    status = Ow_Read(_OWI2C_OW_PORT, _OWI2C_OW_PIN);
    status >>= 1;
    writeStatus = Ow_Read(_OWI2C_OW_PORT, _OWI2C_OW_PIN);
    writeStatus >>= 1;
    
    if (Ow_Read(_OWI2C_OW_PORT, _OWI2C_OW_PIN) & 0x01)
        writeStatus |= 0x80;
    
    return ((uint16_t)status << 8) || writeStatus;
}

void OWI2C_transferI2C (char *pdata)
{
    uint8_t i;
    uint8_t length;
    uint16_t check;
    length = pdata[2];                        //length is write length


    check = _OWI2C_crc16 (pdata, length+4);
    pdata [length+4] = check & 0x00FF;
    pdata [length+5] = ( check >> 8 ) & 0x00FF;

    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, pdata [0]);     //Device command
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, pdata [1]);     //I2C address
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, pdata [2]);     //Write length

    i=0;
    while (i < length)
    {
        Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, pdata [i+3]);    //Wr data
        i++;
    }
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, pdata [length+3]);   //Read length
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, pdata [length+4]);   //CRC
    Ow_Write(_OWI2C_OW_PORT, _OWI2C_OW_PIN, pdata [length+5]);   //CRC


    length = pdata [length+3];                    //length becomes read length

    pdata [0] = Ow_Read(_OWI2C_OW_PORT, _OWI2C_OW_PIN);         //First status byte
    pdata [1] = Ow_Read(_OWI2C_OW_PORT, _OWI2C_OW_PIN);         //Second status byte
    pdata [2] = Ow_Read(_OWI2C_OW_PORT, _OWI2C_OW_PIN);         //Additional byte, see below
    i=0;
    while (i < length)
    {
        pdata [i+3] = Ow_Read(_OWI2C_OW_PORT, _OWI2C_OW_PIN);    //Wr data
        i++;
    }

    /*
     * I-wire I2C click sends one '0' bit before reading starts as a signal. This
     * byte is read by the Ow_Read function, so everything needs to be shifted by
     * one bit. This is done below. This is the reason additional byte needs to be
     * read.
     */
    i = 0;
    while (i < length+2)
    {
        pdata[i] >>= 1;
        pdata[i] |= ((0x01 & pdata[i+1])*0x80);
        i++;
    }
}


/// @}
/* -------------------------------------------------------------------------- */
/*
  __OWI2C_Driver.c

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