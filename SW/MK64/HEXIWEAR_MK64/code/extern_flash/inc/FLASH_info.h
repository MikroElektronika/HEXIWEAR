/**
 * \file FLASH_info.h
 * \version 1.00
 * \brief this file contains external FLASH-related constants
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
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
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

/**
 * designate the end of the command
 */
#define FLASH_CMD_CNT (0) // continue
#define FLASH_CMD_END (1) // end with this command

/**
 * - FLASH commands -
 *
 * every command sequence starts with a one-byte command code
 *
 * depending on the command, command code might be followed by address or data bytes, by address
 * and data bytes, or by neither address or data bytes
 *
 * for the following commands, the shifted-in command sequence is followed by a data-out sequence,
 * CS can be driven HIGH after any bit of the data-out sequence is being shifted out:
 * - READ DATA BYTES (READ)
 * - READ DATA BYTES at HIGHER SPEED
 * - READ STATUS REGISTER
 * - READ IDENTIFICATION
 * - RELEASE from DEEP POWER-DOWN
 *
 * for the following commands, CS must be driven HIGH exactly at a byte boundary,
 * that is, after an exact multiple of eight clock pulses following CS being driven LOW, CS must
 * be driven HIGH, otherwise, the command is rejected and not executed:
 * - PAGE PROGRAM
 * - SECTOR ERASE
 * - BULK ERASE
 * - WRITE STATUS REGISTER
 * - WRITE ENABLE
 * - WRITE DISABLE
 *
 * all attempts to access the memory array are ignored during
 * the command cycles for:
 * - WRITE STATUS REGISTER
 * - PROGRAM and
 * - ERASE commands
 * in addition, the internal cycle for each of these commands continues unaffected
 */

// WRITE ENABLE command must be executed before PROGRAM, ERASE, and WRITE command
#define FLASH_CMD_WRITE_ENABLE  ( 0x06 )
#define FLASH_CMD_WRITE_DISABLE ( 0x04 )
#define FLASH_CMD_WRITE_STATUS  ( 0x01 )

#define FLASH_CMD_READ_IDENTIFICATION ( 0x9F )
#define FLASH_CMD_READ_STATUS         ( 0x05 )
#define FLASH_CMD_READ_DATA_BYTES     ( 0x03 )
#define FLASH_CMD_READ_DATA_BYTES_HS  ( 0x0B )

#define FLASH_CMD_PROGRAM_PAGE ( 0x02  )
#define FLASH_PAGE_SIZE        ( 0x100 )

#define FLASH_CMD_ERASE_SECTOR ( 0xD8 )
#define FLASH_CMD_ERASE_BULK   ( 0xC7 )

#define FLASH_CMD_DEEP_PWR_DOWN     ( 0xB9 )
#define FLASH_CMD_DEEP_PWR_DOWN_RLS ( 0xAB )

/**
 * FLASH bits
 */

#define FLASH_BIT_WIP_SHIFT ( 0 )
#define FLASH_BIT_WEL_SHIFT ( 1 )

#define FLASH_BIT_WIP_MASK  ( 1 << FLASH_BIT_WIP_SHIFT )
#define FLASH_BIT_WEL_MASK  ( 1 << FLASH_BIT_WEL_SHIFT )

// #define FLASH_REG_WRITE_STATUS ( 0x )
// #define FLASH_REG_READ_STATUS  ( 0x )
// #define FLASH_REG_PROGRAM      ( 0x )
// #define FLASH_REG_ERASE        ( 0x )
