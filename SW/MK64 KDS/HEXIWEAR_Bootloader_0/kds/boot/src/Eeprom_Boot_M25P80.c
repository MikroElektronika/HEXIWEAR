/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file EEPROM_InternalFlash.c
* This is the Source file for the EEPROM emulated inside the MCU's FLASH
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

#include "Eeprom_Boot.h"

#if gEepromType_d == gEepromDevice_M25P80_c

#include "SPI.h"


static uint8_t currentStatus;

/**
 * macros
 */

#define EEPROM_IsWriteInProgress()    ( 0 != ( ( currentStatus & EEPROM_BIT_WIP_MASK ) >> EEPROM_BIT_WIP_SHIFT ) )
#define EEPROM_IsWriteNotInProgress() ( 0 == ( ( currentStatus & EEPROM_BIT_WIP_MASK ) >> EEPROM_BIT_WIP_SHIFT ) )
#define EEPROM_IsWriteEnabled()       ( 0 != ( ( currentStatus & EEPROM_BIT_WEL_MASK ) >> EEPROM_BIT_WEL_SHIFT ) )
#define EEPROM_IsWriteNotEnabled()    ( 0 == ( ( currentStatus & EEPROM_BIT_WEL_MASK ) >> EEPROM_BIT_WEL_SHIFT ) )


/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */
#define  gEepromWriteEnable_d   1

/**
 * designate the end of the command
 */
#define EEPROM_CMD_CNT (0) // continue
#define EEPROM_CMD_END (1) // end with this command

// WRITE ENABLE command must be executed before PROGRAM, ERASE, and WRITE command
#define EEPROM_CMD_WRITE_ENABLE  ( 0x06 )
#define EEPROM_CMD_WRITE_DISABLE ( 0x04 )
#define EEPROM_CMD_WRITE_STATUS  ( 0x01 )

#define EEPROM_CMD_READ_IDENTIFICATION ( 0x9F )
#define EEPROM_CMD_READ_STATUS         ( 0x05 )
#define EEPROM_CMD_READ_DATA_BYTES     ( 0x03 )
#define EEPROM_CMD_READ_DATA_BYTES_HS  ( 0x0B )

#define EEPROM_CMD_PROGRAM_PAGE ( 0x02  )
#define EEPROM_PAGE_SIZE        (256)
#define EEPROM_PAGE_MASK        (EEPROM_PAGE_SIZE - 1)
#define EEPROM_SECTOR_SIZE      (EEPROM_PAGE_SIZE * 256)

#define EEPROM_CMD_ERASE_SECTOR ( 0xD8 )
#define EEPROM_CMD_ERASE_BULK   ( 0xC7 )

#define EEPROM_CMD_DEEP_PWR_DOWN     ( 0xB9 )
#define EEPROM_CMD_DEEP_PWR_DOWN_RLS ( 0xAB )

/**
 * EEPROM bits
 */

#define EEPROM_BIT_WIP_SHIFT ( 0 )
#define EEPROM_BIT_WEL_SHIFT ( 1 )

#define EEPROM_BIT_WIP_MASK  ( 1 << EEPROM_BIT_WIP_SHIFT )
#define EEPROM_BIT_WEL_MASK  ( 1 << EEPROM_BIT_WEL_SHIFT )


/* SPI config */
#define gEepromSpiInstance_c  1
#define gEepromSpiCsPin_d     GPIO_MAKE_PIN(GPIOD_IDX, 4 )

#define gEepromAssertCS_d()   assert_cs()
#define gEepromDeassertCS_d() deassert_cs()

/****************************** SPI MACROS ***********************************/
#define mEepromSpiInstance_c 1

/******************************************************************************
*******************************************************************************
* Private Prototypes
*******************************************************************************
******************************************************************************/
static ee_err_t EEPROM_SendCmd(const uint8_t cmdToSend, uint8_t  endFlag);
static ee_err_t EEPROM_GetWriteReady();
static ee_err_t EEPROM_SendAddress(uint32_t eepromAddress);
static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf);
static ee_err_t EEPROM_PrepareForWrite(uint32_t NoOfBytes, uint32_t Addr);


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
ee_err_t EEPROM_Init()
{
    spi_user_config_t config;

#if gEepromWriteEnable_d
    uint32_t i;

    // Mark Flash as Unerased
    for(i = 0; i < 64; i++)
        mEepromEraseBitmap[i] = 0;
#endif

    config.busFrequencyKHz = 8000;
    config.direction       = kSpiMsbFirst;
    config.phase           = kSpiClockPhase_FirstEdge;
    config.polarity        = kSpiClockPolarity_ActiveHigh;

    spi_master_init(mEepromSpiInstance_c);
    spi_master_configure_bus(mEepromSpiInstance_c, &config);

    gEepromDeassertCS_d();

    return ee_ok;
}

/*****************************************************************************
*  EEPROM_ChipErase
*
*  Erase all memory to 0xFF
*
*****************************************************************************/
ee_err_t EEPROM_ChipErase()
{
    // make sure the write process is ready
    while(EEPROM_GetWriteReady() != ee_ok);

    return EEPROM_SendCmd(EEPROM_CMD_ERASE_BULK, EEPROM_CMD_END);
}

/*****************************************************************************
*  EEPROM_EraseBlock
*
*  Erase a block of memory to 0xFF
*
*****************************************************************************/
ee_err_t EEPROM_EraseBlock(uint32_t Addr, uint32_t size)
{
    ee_err_t status = ee_ok;

    if(size != EEPROM_SECTOR_SIZE)
    {
        return ee_error;
    }

    // make sure the write process is ready
    while(EEPROM_GetWriteReady() != ee_ok);

    // send the command
    status |= EEPROM_SendCmd( EEPROM_CMD_ERASE_SECTOR, EEPROM_CMD_CNT );

    // send the address
    status |= EEPROM_SendAddress(Addr);

    if (status == ee_ok)
    {
        gEepromDeassertCS_d();
        return ee_ok;
    }
    else
    {
        return ee_error;
    }
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
    ee_err_t status = ee_ok;

    if (NoOfBytes == 0)
    {
        return status;
    }

    // make sure the write process is ready
    while(EEPROM_GetWriteReady() != ee_ok);

    status = EEPROM_PrepareForWrite(NoOfBytes, Addr);
    if (status != ee_ok)
    {
        return status;
    }

    while ((Addr & EEPROM_PAGE_MASK) + NoOfBytes > EEPROM_PAGE_MASK)
    {
        uint32_t bytes = EEPROM_PAGE_SIZE - (Addr & EEPROM_PAGE_MASK);

        status = EEPROM_WritePage(bytes, Addr, Outbuf);
        NoOfBytes -= bytes;
        Addr += bytes;
        Outbuf += bytes;

        if (status != ee_ok)
            return status;
    }

    status = EEPROM_WritePage(NoOfBytes, Addr, Outbuf);

    return status;
}
#endif

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
    startBlk = Addr / EEPROM_SECTOR_SIZE;
    endBlk   = (Addr + NoOfBytes) / EEPROM_SECTOR_SIZE + 1;

    for(i = startBlk; i <= endBlk; i++)
    {
        if ( (mEepromEraseBitmap[i/8] & (1 << (i%8) ) ) == 0)
        {
            ret = EEPROM_EraseBlock(i * EEPROM_SECTOR_SIZE, EEPROM_SECTOR_SIZE);
            if (ret != ee_ok)
                return ret;

            mEepromEraseBitmap[i/8] |= 1 << (i%8);
            while (EEPROM_isBusy());
        }
    }

    return ret;
}
#endif

#if gEepromWriteEnable_d
static ee_err_t EEPROM_WritePage(uint32_t NoOfBytes, uint32_t Addr, uint8_t *Outbuf)
{
    ee_err_t status = ee_ok;

    if (NoOfBytes == 0)
    {
        return ee_ok;
    }

    // make sure the write process is ready
    while(EEPROM_GetWriteReady() != ee_ok);

    /**
   * write data
   */
    if (NoOfBytes > EEPROM_PAGE_SIZE)
    {
        return ee_too_big;
    }

    // send the PAGE_PROGRAM command
    status |= EEPROM_SendCmd(EEPROM_CMD_PROGRAM_PAGE, EEPROM_CMD_CNT );
    // send the address
    status |= EEPROM_SendAddress(Addr);

    /**
     * send data
     */
    gEepromAssertCS_d();

    if(spi_master_transfer(mEepromSpiInstance_c, Outbuf, NULL, NoOfBytes) != 0)
    {
        status = ee_error;
    }
    gEepromDeassertCS_d();

    if(status == ee_ok)
    {
        return status;
    }
    else
    {
        return ee_error;
    }
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
    ee_err_t status = ee_ok;

    // make sure the write process is ready
    while(EEPROM_GetWriteReady() != ee_ok);

    // send the PAGE_PROGRAM command
    status |= EEPROM_SendCmd(EEPROM_CMD_READ_DATA_BYTES, EEPROM_CMD_CNT );
    // send the address
    status |= EEPROM_SendAddress(Addr);

    if(status != ee_ok)
    {
        status = ee_error;
    }

    else
    {
        gEepromAssertCS_d();
        status |= spi_master_transfer(mEepromSpiInstance_c, NULL, inbuf, NoOfBytes);
        gEepromDeassertCS_d();
    }

    if(status == ee_ok)
    {
        return status;
    }
    else
    {
        return ee_error;
    }
}

/*****************************************************************************
*  EEPROM_ReadStatusReq
*
*
*****************************************************************************/
uint8_t EEPROM_isBusy()
{
    if(EEPROM_IsWriteInProgress() != 0)
    {
        return 1;
    }
    return 0;
}

/*! *********************************************************************************
* \brief
*
* \param[in]
* \param[in]
********************************************************************************** */

ee_err_t EEPROM_ReadStatus(uint8_t* flashStatus)
{
    ee_err_t status = ee_ok;

    status |= EEPROM_SendCmd( EEPROM_CMD_READ_STATUS, EEPROM_CMD_CNT );

    if(status == ee_ok)
    {
        if(spi_master_transfer(mEepromSpiInstance_c, NULL, &currentStatus, sizeof(currentStatus)) != 0)
        {
            status |= ee_error;
        }

        gEepromDeassertCS_d();
    }

    if(status != ee_ok)
    {
       status = ee_error;
    }
    else
    {
        if ( NULL != flashStatus )
        {
            *flashStatus = currentStatus;
        }
    }

    return status;
}

/*! *********************************************************************************
*************************************************************************************
* Private Functions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
* \brief
*
* \param[in]
* \param[in]
********************************************************************************** */

static ee_err_t EEPROM_SendCmd(const uint8_t cmdToSend, uint8_t  endFlag)
{
    ee_err_t status = ee_ok;
    uint8_t txSize = 1, cmdBuf[1];

    cmdBuf[0] = cmdToSend;

    gEepromAssertCS_d();

    if(spi_master_transfer(mEepromSpiInstance_c, cmdBuf, NULL, txSize) != 0)
    {
        status = ee_error;
    }

    if ( EEPROM_CMD_END == endFlag )
    {
        gEepromDeassertCS_d();
    }

    return status;
}

/*! *********************************************************************************
* \brief
*
* \param[in]
* \param[in]
********************************************************************************** */

static ee_err_t EEPROM_GetWriteReady()
{
    ee_err_t status = ee_ok;

    /**
    * make sure there is no other writing in progress
    */
    status = EEPROM_ReadStatus( NULL );

    if(status != ee_ok)
    {
        return ee_error;
    }

    if (EEPROM_IsWriteInProgress())
    {
        /**
         * poll untill the writing is enabled
        */
        while (1)
        {
            status = EEPROM_ReadStatus( NULL );
            if (status != ee_ok)
            {
                return ee_error;
            }

            if (EEPROM_IsWriteNotInProgress())
            {
                break;
            }
        }
    }

    /**
   * make sure WEL bit is HIGH (writing is enabled)
   */
    while (1)
    {
        status = EEPROM_ReadStatus( NULL );
        if (status != ee_ok)
        {
            return ee_error;
        }
        else
        {
            if (EEPROM_IsWriteEnabled())
            {
                break;
            }

            else
            {
                status = EEPROM_SendCmd( EEPROM_CMD_WRITE_ENABLE, EEPROM_CMD_END );
                if (status != ee_ok)
                {
                    return ee_error;
                }
            }
        }
    }

    return ee_ok;
}

/*! *********************************************************************************
* \brief
*
* \param[in]
* \param[in]
********************************************************************************** */

static ee_err_t EEPROM_SendAddress(uint32_t eepromAddress)
{
    ee_err_t status = ee_ok;
    uint32_t fmtAddr = 0;

    // if the address is bigger than 24 bytes, exit
    if ( eepromAddress > 0x00FFFFFF)
    {
        return ee_error;
    }

    // arrange bytes
    fmtAddr |= ( eepromAddress & 0xFF0000 ) >> 16;
    fmtAddr |= ( eepromAddress & 0x00FF00 );
    fmtAddr |= ( eepromAddress & 0x0000FF ) << 16;

    if(spi_master_transfer(mEepromSpiInstance_c, (uint8_t*)&fmtAddr, NULL, 3) != 0)
    {
        status = ee_error;
    }


    return status;
}



#endif /* gEepromDevice_M25P80_c */
