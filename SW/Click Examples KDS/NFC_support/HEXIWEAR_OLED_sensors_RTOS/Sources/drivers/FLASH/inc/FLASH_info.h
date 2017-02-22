/**
 * FLASH-related constants
 * Project HEXIWEAR, 2015
 */

#ifndef HG_FLASH_INFO
#define HG_FLASH_INFO

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

/**
 * macros
 */


// #define FLASH_REG_WRITE_STATUS ( 0x )
// #define FLASH_REG_READ_STATUS  ( 0x )
// #define FLASH_REG_PROGRAM      ( 0x )
// #define FLASH_REG_ERASE        ( 0x )

#endif
