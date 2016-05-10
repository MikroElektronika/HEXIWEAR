/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file EEPROM_AT45DB021E.c
* This is a source file which implements the driver for the AT45DB021E memory.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "Eeprom_Boot.h"

#if gEepromType_d == gEepromDevice_AT45DB021E_c

#include "SPI.h"

/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */
#define  gEepromWriteEnable_d   0

#define  EEPROM_RDSR            0xD7
#define  EEPROM_READ            0x03
#define  EEPROM_READ_HF         0x0B

#define  EEPROM_ERASE_256B      0x81
#define  EEPROM_ERASE_2K        0x50

#define  EEPROM_WRITE_BYTES     0x02

#define  EEPROM_BUSY_FLAG_MASK  0x80
#define  EEPROM_PAGE_SIZE       (256)
#define  EEPROM_BLOCK_SIZE      (8*EEPROM_PAGE_SIZE)
#define  EEPROM_PAGE_MASK       (EEPROM_PAGE_SIZE - 1)

/* adress mask */
#define  ADDRESS_MASK 0x000000FF


/****************************** SPI MACROS ***********************************/
#define mEepromSpiInstance_c 0



/******************************************************************************
*******************************************************************************
* Private Prototypes
*******************************************************************************
******************************************************************************/
#if gEepromWriteEnable_d
static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr);
static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf);
#endif
static ee_err_t EEPROM_WaitForReady(void);
static uint16_t EEPROM_ReadStatusReq(void);
static void     EEPROM_Command(uint8_t opCode, uint32_t Addr);


/*! *********************************************************************************
*************************************************************************************
* Private Memory Declarations
*************************************************************************************
********************************************************************************** */
#if gEepromWriteEnable_d
static uint8_t mEepromEraseBitmap[64];
#endif


/*! *********************************************************************************
*************************************************************************************
* Public Functions
*************************************************************************************
********************************************************************************** */

/*****************************************************************************
*  EEPROM_Init
*
*  Initializes the EEPROM peripheral
*
*****************************************************************************/
ee_err_t EEPROM_Init(void)
{
    ee_err_t retval;
    const uint8_t cmd[] = {0x3D, 0x2A, 0x80, 0xA6};
    spi_user_config_t config;
#if gEepromWriteEnable_d
    uint32_t i;
    
    // Mark Flash as Unerased
    for(i = 0; i < 64; i++)
        mEepromEraseBitmap[i] = 0;
#endif
    
    config.busFrequencyKHz = 8000;
    config.direction = kSpiMsbFirst;
    config.phase = kSpiClockPhase_FirstEdge;
    config.polarity = kSpiClockPolarity_ActiveHigh;
    
    spi_master_init(mEepromSpiInstance_c);
    spi_master_configure_bus(mEepromSpiInstance_c, &config);
    
    retval = EEPROM_WaitForReady();
    if (retval != ee_ok)
        return retval;

    // Set page size to 512bits:
    assert_cs();
    spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
    deassert_cs();
    
    return ee_ok;
}

/*****************************************************************************
*  EEPROM_ChipErase
*
*  Erase all memory to 0xFF
*
*****************************************************************************/
ee_err_t EEPROM_ChipErase(void)
{
    const uint8_t cmd[] = {0xC7, 0x94, 0x80, 0x9A};
    while (EEPROM_isBusy());
    
    assert_cs();
    spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
    deassert_cs();

    return ee_ok;
}

/*****************************************************************************
*  EEPROM_EraseBlock
*
*  Erase a block of memory to 0xFF
*
*****************************************************************************/
ee_err_t EEPROM_EraseBlock(uint32_t Addr, uint32_t size)
{
    uint8_t cmd[4];
    
    while (EEPROM_isBusy());
    
    switch (size)
    {
    case EEPROM_BLOCK_SIZE:
        cmd[0] = EEPROM_ERASE_2K;
        break;
    case EEPROM_PAGE_SIZE:
        cmd[0] = EEPROM_ERASE_256B;
        break;
    default:
        return ee_error;
    }

    cmd[1] = (Addr >> 16) & ADDRESS_MASK;
    cmd[2] = (Addr >>  8) & ADDRESS_MASK;
    cmd[3] = (Addr >>  0) & ADDRESS_MASK;

    assert_cs();
    spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
    deassert_cs();
    
    return ee_ok;
}

/*****************************************************************************
*  EEPROM_WriteData
*
*  Writes a data buffer into EEPROM, at a given address
*
*****************************************************************************/
#if gEepromWriteEnable_d
ee_err_t EEPROM_WriteData(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
{
    ee_err_t retval;
    
    if (NoOfBytes == 0)
        return ee_ok;
    
    while (EEPROM_isBusy());
    
    retval = EEPROM_PrepareForWrite(NoOfBytes, Addr);
    if (retval != ee_ok)
        return retval;
    
    while ((Addr & EEPROM_PAGE_MASK) + NoOfBytes > EEPROM_PAGE_MASK)
    {
        uint32_t bytes = EEPROM_PAGE_SIZE - (Addr & EEPROM_PAGE_MASK);
        
        retval = EEPROM_WritePage(bytes, Addr, Outbuf);
        NoOfBytes -= bytes;
        Addr += bytes;
        Outbuf += bytes;
        
        if (retval != ee_ok)
            return retval;
    }
    
    retval = EEPROM_WritePage(NoOfBytes, Addr, Outbuf);
    
    return retval;
}
#endif

/*****************************************************************************
*  EEPROM_ReadData
*
*  Reads a data buffer from EEPROM, from a given address
*
*****************************************************************************/
ee_err_t EEPROM_ReadData(uint16_t NoOfBytes, uint32_t Addr, uint8_t *inbuf)
{
    
    while (EEPROM_isBusy());
    
    EEPROM_Command(EEPROM_READ,Addr);
    
    spi_master_transfer(mEepromSpiInstance_c, NULL, inbuf, NoOfBytes);
    deassert_cs();

    return ee_ok;
}

/*****************************************************************************
*  EEPROM_ReadStatusReq
*
*
*****************************************************************************/
uint8_t EEPROM_isBusy(void)
{
    return !(EEPROM_ReadStatusReq() & EEPROM_BUSY_FLAG_MASK);
}

/*! *********************************************************************************
*************************************************************************************
* Private Functions
*************************************************************************************
********************************************************************************** */

/*****************************************************************************
*  EEPROM_ReadStatusReq
*
*
*****************************************************************************/
static uint16_t EEPROM_ReadStatusReq(void)
{
    uint16_t status = EEPROM_RDSR;
    
    assert_cs();
    spi_master_transfer(mEepromSpiInstance_c, (uint8_t*)&status, NULL, 1);
    spi_master_transfer(mEepromSpiInstance_c, NULL, (uint8_t*)&status, 2);
    deassert_cs();

    return status;
}

/*****************************************************************************
*  EEPROM_WriteData
*
*  Writes a data buffer into the External Memory, at a given address
*
*****************************************************************************/
#if gEepromWriteEnable_d
static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr)
{
    uint32_t i;
    ee_err_t ret = ee_ok;
    uint32_t startBlk, endBlk;
    
    // Obtain the block number
    startBlk = Addr >> 12;
    endBlk   = (Addr + NoOfBytes) >> 12;
    
    for(i = startBlk; i <= endBlk; i++)
        if ( (mEepromEraseBitmap[i/8] & (1 << (i%8) ) ) == 0)
        {
            ret = EEPROM_EraseBlock(i * EEPROM_BLOCK_SIZE, EEPROM_BLOCK_SIZE);
            if (ret != ee_ok)
                return ret;
            
            mEepromEraseBitmap[i/8] |= 1 << (i%8);
            while (EEPROM_isBusy());
        }
    
    return ret;
}
#endif

/*****************************************************************************
*  EEPROM_WritePage
*
*  Writes maximum 256 bytes into a EEPROM page
*
*****************************************************************************/
#if gEepromWriteEnable_d
static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
{
    
    if (NoOfBytes == 0)
        return ee_ok;
    
    while (EEPROM_isBusy());
    
    //SPI_Send_byte(EEPROM_WRITE_ENABLE,DEASSERT_CS);
    
    EEPROM_Command(EEPROM_WRITE_BYTES, Addr); //CS will remain ASSERTED

    spi_master_transfer(mEepromSpiInstance_c, Outbuf, NULL, NoOfBytes);
    deassert_cs();
    
    return ee_ok;
}
#endif

/*****************************************************************************
*  EEPROM_WaitForReady
*
*
*****************************************************************************/
static ee_err_t EEPROM_WaitForReady(void)
{
    volatile uint16_t wait = 0x400; // near 50 ms @ 50 us/cycle
    
    /* Byte1 - Bit:   7       6      5:2       1         0
    *             RDY/BUSY  COMP  DENSITY  PROTECT  PAGE_SIZE
    *
    * Byte2 - Bit:   7       6    5    4    3    2    1    0
    *             RDY/BUSY  RES  EPE  RES  SLE  PS2  PS1  ES
    */
    
    while( EEPROM_isBusy() && (wait !=0) )
    {
        wait--;
    }
    
    if(wait != 0)
    {
        return ee_ok;
    }
    return ee_error;
}


/*****************************************************************************
*  EEPROM_Command
*
*
*****************************************************************************/
static void EEPROM_Command(uint8_t opCode, uint32_t Addr)
{
    uint8_t cmd[4];
    
    cmd[0] = opCode;
    cmd[1] = (Addr >> 16) & ADDRESS_MASK;
    cmd[2] = (Addr >>  8) & ADDRESS_MASK;
    cmd[3] = (Addr >>  0) & ADDRESS_MASK;

    assert_cs();
    spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
    /* CS will remain asserted to be able to send the data */
}

#endif
/* EOF: Eeprom_AT45DB021E */ 

