/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file Eeprom_AT26DF081A.c
* This is the Source file for the AT26DF081A FLASH driver
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

#if gEepromType_d == gEepromDevice_AT26DF081A_c

#include "SPI.h"

/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */

#define  EEPROM_WRSR            0x01
#define  EEPROM_RDSR            0x05
#define  EEPROM_READ            0x03
#define  EEPROM_READ_HF         0x0B

#define  EEPROM_ERASE_4K        0x20
#define  EEPROM_ERASE_32K       0x52
#define  EEPROM_ERASE_64K       0xD8
#define  EEPROM_ERASE_ALL       0xC7

#define  EEPROM_WRITE_ENABLE    0x06
#define  EEPROM_WRITE_DISABLE   0x04
#define  EEPROM_WRITE_BYTES     0x02
#define  EEPROM_WRITE_SEQ       0xAD

#define  EEPROM_UNPROTECT       0x39
#define  EEPROM_READ_PROT_SECT  0x3C

#define  EEPROM_POWER_DOWN      0xB9
#define  EEPROM_WAKE_UP         0xAB

#define  EEPROM_BUSY_FLAG_MASK  0x01
#define  EEPROM_SPM_FLAG_MASK   0x40

/* adress mask */
#define  ADDRESS_MASK 0x000000FF


/****************************** SPI MACROS ***********************************/
#define mEepromSpiInstance_c 0

/******************************************************************************
*******************************************************************************
* Private Prototypes
*******************************************************************************
******************************************************************************/
#if gEepromWriteWnable_d
static ee_err_t EEPROM_WriteSR(uint8_t status);
static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr);
static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf);
#endif
static ee_err_t EEPROM_WaitForReady(void);
static uint8_t  EEPROM_ReadStatusReq(void);
static void     EEPROM_Command(uint8_t opCode, uint32_t Addr);


/*! *********************************************************************************
*************************************************************************************
* Private Memory Declarations
*************************************************************************************
********************************************************************************** */
#if gEepromWriteWnable_d
static uint8_t mEepromEraseBitmap[32];
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
    spi_user_config_t config;
#if gEepromWriteWnable_d
    uint32_t i;
    
    // Mark Flash as Unerased
    for(i = 0; i < 32; i++)
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
#if gEepromWriteWnable_d
    /* Unprotect all sectors */
    retval = EEPROM_WriteSR(0);
#endif
    return retval;
}

/*****************************************************************************
*  EEPROM_ChipErase
*
*  Erase all memory to 0xFF
*
*****************************************************************************/
ee_err_t EEPROM_ChipErase(void)
{
    uint8_t cmd;
    
    while (EEPROM_isBusy());
    
    assert_cs();
    cmd = EEPROM_WRITE_ENABLE;
    spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
    deassert_cs();
    
    assert_cs();
    cmd = EEPROM_ERASE_ALL;
    spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
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
    case (4*1024):
        cmd[0] = EEPROM_ERASE_4K;
        break;
    case (32*1024):
        cmd[0] = EEPROM_ERASE_32K;
        break;
    case (64*1024):
        cmd[0] = EEPROM_ERASE_64K;
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
*  EEPROM_WriteData_Seq
*
*  Writes a data buffer into EEPROM, one byte at a time.
*  No address is needed because the internal address counter will be used.
*
*  EEPROM_StartWriteData_Seq must be called before using this function.
*****************************************************************************/
#if gEepromWriteWnable_d
ee_err_t EEPROM_WriteData_Seq(uint32_t NoOfBytes, uint8_t *Outbuf)
{
    
    if (!(EEPROM_ReadStatusReq() & EEPROM_SPM_FLAG_MASK))
        return ee_error;
    
    assert_cs();
    spi_master_transfer(mEepromSpiInstance_c, Outbuf, NULL, NoOfBytes);
    deassert_cs();

    return ee_ok;
}
#endif

/*****************************************************************************
*  EEPROM_StartWriteData_Seq
*
*  Writes a data buffer into EEPROM, at a given address, one byte at a time
*  This function will set the SPM bit in the EEPROM's Status Register
*
*****************************************************************************/
#if gEepromWriteWnable_d
ee_err_t EEPROM_StartWriteData_Seq(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
{
    ee_err_t retval;
    
    if (NoOfBytes == 0)
        return ee_ok;
    
    while (EEPROM_isBusy());
    
    SPI_Send_byte(EEPROM_WRITE_ENABLE,DEASSERT_CS);
    
    EEPROM_Command(EEPROM_WRITE_SEQ,Addr);
    SPI_Send_byte((uint8_t)(*Outbuf++),DEASSERT_CS);
    
    NoOfBytes--;
    
    retval = EEPROM_WriteData_Seq(NoOfBytes, Outbuf);
    
    SPI_Send_byte(EEPROM_WRITE_DISABLE,DEASSERT_CS);
    return retval;
}
#endif

/*****************************************************************************
*  EEPROM_WriteData
*
*  Writes a data buffer into EEPROM, at a given address
*
*****************************************************************************/
#if gEepromWriteWnable_d
ee_err_t EEPROM_WriteData(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
{
    ee_err_t retval;
    
    if (NoOfBytes == 0)
        return ee_ok;
    
    while (EEPROM_isBusy());
    
    retval = EEPROM_PrepareForWrite(NoOfBytes, Addr);
    if (retval != ee_ok)
        return retval;
    
    while ((Addr & 0xFF) + NoOfBytes > 0xFF)
    {
        uint32_t bytes = 0x100 - (Addr & 0xFF);
        
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
    return (EEPROM_ReadStatusReq() & EEPROM_BUSY_FLAG_MASK);
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
static uint8_t EEPROM_ReadStatusReq(void)
{
    uint8_t cmd = EEPROM_RDSR;

    assert_cs();
    spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
    spi_master_transfer(mEepromSpiInstance_c, NULL, &cmd, sizeof(cmd));
    deassert_cs();

    return cmd;
}

/*****************************************************************************
*  EEPROM_WriteData
*
*  Writes a data buffer into the External Memory, at a given address
*
*****************************************************************************/
#if gEepromWriteWnable_d
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
            ret = EEPROM_EraseBlock(i * 4096, 4096);
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
#if gEepromWriteWnable_d
static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
{
    uint8_t cmd;

    if( NoOfBytes == 0 )
        return ee_ok;
    
    while (EEPROM_isBusy());
    
    assert_cs();
    cmd = EEPROM_WRITE_ENABLE;
    spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
    deassert_cs();

    assert_cs();
    cmd = EEPROM_WRITE_BYTES;
    spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
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
    
    /* Bit   7    6    5    4   3:2   1      0
    *      SPL  SPM  EPE  WPP  SWP  WEL  RDY/BSY
    */
    
    while ((EEPROM_ReadStatusReq() & EEPROM_BUSY_FLAG_MASK) && (wait !=0) )
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
    cmd[1] = (uint8_t) ((Addr >> 16) & ADDRESS_MASK);
    cmd[2] = (uint8_t) ((Addr >>  8) & ADDRESS_MASK);
    cmd[3] = (uint8_t) ((Addr >>  0) & ADDRESS_MASK);
    assert_cs();
    spi_master_transfer(mEepromSpiInstance_c, cmd, NULL, sizeof(cmd));
    /* CS will remain asserted to be able to send the data */
}


/*****************************************************************************
*  EEPROM_WriteSR
*
*
*****************************************************************************/
#if gEepromWriteWnable_d
static ee_err_t EEPROM_WriteSR(uint8_t status)
{
    uint8_t cmd;

    while (EEPROM_isBusy());

    assert_cs();
    cmd = EEPROM_WRITE_ENABLE;
    spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
    deassert_cs();

    assert_cs();
    cmd = EEPROM_WRSR;
    spi_master_transfer(mEepromSpiInstance_c, &cmd, NULL, sizeof(cmd));
    spi_master_transfer(mEepromSpiInstance_c, &status, NULL, sizeof(status));
    deassert_cs();

    return ee_ok;
}
#endif

#endif /* gEepromDevice_AT26DF081A_c */