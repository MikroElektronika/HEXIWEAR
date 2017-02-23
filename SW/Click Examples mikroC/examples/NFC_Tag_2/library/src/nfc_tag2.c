/*
 * nfc_tag2.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Sep/2016) Module created                        Milos Vidojevic
 *
 * To Do List :
 * ( 0 Block / 0 Byte ) write always current I2C Address
 *
 ******************************************************************************/

#include "nfc_tag2.h"

#define _NT2_USER_MEMORY_                                   0x01
#define _NT2_CONFIG_REG_                                    0x3A
#define _NT2_SESSION_REG_                                   0xFE

#define _NT2_BLOCK_SIZE_                                    16

/*
 * Memory map type
 */
typedef uint8_t NT2_MEM_MAP[ 3 ];

/*
 * Memory map properties
 */
enum NT2_MAP_PROP
{
    MM_BLOCK, MM_OFFSET, MM_SIZE
};

/*
 * Memory map with properties mapable and accessable by NFCTAG2_REG enum.
 */
static const NT2_MEM_MAP MEMORY[ 5 ] =
{
    {   0,   0,   7 },              /*< Serial Number */
    {   0,  10,   2 },              /*< Static Lock */
    {   0,  12,   4 },              /*< Capability Container */
    {  56,   8,   3 },              /*< Dynamic Lock */
    { 248,   0,  64 }               /*< SRAM Memory */
};

static uint8_t _i2c_address;

/*
 * Private Function Prototypes
 ******************************************************************************/

static int nt2_memblock_rd( uint8_t block, uint8_t *value );

static int nt2_memblock_wr( uint8_t block, uint8_t *value );

static int nt2_memreg_rd
(
        uint8_t block,
        uint8_t offset,
        uint16_t len,
        uint8_t *out
);

static int nt2_memreg_wr
(
        uint8_t block,
        uint8_t offset,
        uint16_t len,
        uint8_t *in
);

/*
 * Private Function Definitions
 ******************************************************************************/

static int nt2_memblock_rd
(
        uint8_t block,
        uint8_t *value
)
{
    uint8_t temp[ _NT2_BLOCK_SIZE_ ] = { 0 };
    temp[ 0 ] = block;
    if( hal_nfctag2_read( _i2c_address, temp, sizeof( temp ) ) )
        return 1;
    memcpy( ( void* )value, ( void* )temp, _NT2_BLOCK_SIZE_ );
    hal_delay( 5 );
    return 0;
}

static int nt2_memblock_wr
(
        uint8_t block,
        uint8_t *value
)
{
    uint8_t temp[ _NT2_BLOCK_SIZE_ + 1 ] = { 0 };
    temp[ 0 ] = block;
    memcpy( ( void* )( temp + 1 ), ( void* )value , _NT2_BLOCK_SIZE_ );
    if( hal_nfctag2_write( _i2c_address, temp, sizeof( temp ) ) )
        return 1;
    hal_delay( 5 );
    return 0;
}

static int nt2_memreg_rd
(
        uint8_t block,
        uint8_t offset,
        uint16_t len,
        uint8_t *out
)
{
    uint8_t temp[ _NT2_BLOCK_SIZE_ ] = { 0 };

    while( ( offset + len ) > _NT2_BLOCK_SIZE_ )
    {
        if( nt2_memblock_rd( block++, temp ) )
            return 1;
        memcpy( ( void* )out,
                ( void* )( temp + offset ), _NT2_BLOCK_SIZE_ - offset );
        len -= _NT2_BLOCK_SIZE_ - offset;
        out += _NT2_BLOCK_SIZE_ - offset;
        offset = 0;
    }
    if( nt2_memblock_rd( block, temp ) )
        return 1;
    memcpy( ( void* )out, ( void* )( temp + offset ), len );
    return 0;
}

static int nt2_memreg_wr
(
        uint8_t block,
        uint8_t offset,
        uint16_t len,
        uint8_t *in
)
{
    uint8_t temp[ _NT2_BLOCK_SIZE_ ] = { 0 };

    while( ( offset + len ) > _NT2_BLOCK_SIZE_ )
    {
        if( nt2_memblock_rd( block, temp ) )
            return 1;
        memcpy( ( void* )( temp + offset ),
                ( void* )in, _NT2_BLOCK_SIZE_ - offset );
        if( nt2_memblock_wr( block++, temp ) )
            return 1;
        len -= _NT2_BLOCK_SIZE_ - offset;
        in += _NT2_BLOCK_SIZE_ - offset;
        offset = 0;
    }
    if( nt2_memblock_rd( block, temp ) )
        return 1;
    memcpy( ( void* )( temp + offset ), ( void* )in, len );
    if( nt2_memblock_wr( block, temp ) )
        return 1;
    return 0;
}

/*
 * Public Function Definitions
 ******************************************************************************/

int nfctag2_init( uint8_t i2c_address )
{
    _i2c_address = i2c_address >> 1;
    if( hal_nfctag2_init() )
        return -1;
    return NT2_OK;
}

int nfctag2_i2c_addres( uint8_t new_address )
{
    uint8_t tmp = new_address;
    if( nt2_memreg_wr( 0, 0, 1, &tmp ) )
        return NT2_BLOCK_WRITE_ERR;
    _i2c_address = tmp >> 1;
    return NT2_OK;
}

int nfctag2_get( NFCTAG2_SET reg, uint8_t *output )
{
    uint8_t *ptr = output;
    if( nt2_memreg_rd( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
                       MEMORY[ reg ][ MM_SIZE ], ptr ) )
        return NT2_BLOCK_READ_ERR;
    return NT2_OK;
}

int nfctag2_set( NFCTAG2_SET reg, uint8_t *value )
{
    uint8_t *ptr = value;
    if( nt2_memreg_wr( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
                       MEMORY[ reg ][ MM_SIZE ], ptr ) )
        return NT2_BLOCK_WRITE_ERR;
    return NT2_OK;
}

uint8_t nfctag2_config_get( NFCTAG2_CFG reg )
{
    uint8_t regdat;
    if( nt2_memreg_rd( _NT2_CONFIG_REG_, reg, 1, &regdat ) )
        return NT2_BLOCK_READ_ERR;
    return regdat;
}

int nfctag2_config_set( NFCTAG2_CFG reg, uint8_t input )
{
    if( nt2_memreg_wr( _NT2_CONFIG_REG_, reg, 1, &input ) )
        return NT2_BLOCK_WRITE_ERR;
    return NT2_OK;
}

uint8_t nfctag2_session_get( NFCTAG2_CFG reg )
{
    uint8_t regdat;
    uint8_t temp[ 2 ] = { 0 };
    temp[ 0 ] = _NT2_SESSION_REG_;
    temp[ 1 ] = reg;
    if( hal_nfctag2_transfer( _i2c_address, temp, 2, &regdat, 1 ) )
        return NT2_BLOCK_WRITE_ERR;
    hal_delay( 5 );
    return regdat;
}

int nfctag2_session_set( NFCTAG2_CFG reg, uint8_t mask, uint8_t value )
{
    uint8_t temp[ 4 ] = { 0 };
    temp[ 0 ] = _NT2_SESSION_REG_;
    temp[ 1 ] = reg;
    temp[ 2 ] = mask;
    temp[ 3 ] = value;
    if( hal_nfctag2_write( _i2c_address, temp, 4 ) )
        return NT2_BLOCK_WRITE_ERR;
    hal_delay( 5 );
    return NT2_OK;
}

int nfctag2_memory_read( uint16_t mem_offset, uint8_t *buffer, uint16_t count )
{
    uint8_t blk = ( mem_offset / _NT2_BLOCK_SIZE_ ) + _NT2_USER_MEMORY_;
    uint8_t off = mem_offset % _NT2_BLOCK_SIZE_;
    uint8_t *ptr = buffer;
    if( nt2_memreg_rd( blk, off, count, ptr ) )
        return NT2_BLOCK_READ_ERR;
    return NT2_OK;
}

int nfctag2_memory_write( uint16_t mem_offset, uint8_t *buffer, uint16_t count )
{
    uint8_t blk = ( mem_offset / _NT2_BLOCK_SIZE_ ) + _NT2_USER_MEMORY_;
    uint8_t off = mem_offset % _NT2_BLOCK_SIZE_;
    uint8_t *ptr = buffer;
    if( nt2_memreg_wr( blk, off, count, ptr ) )
        return NT2_BLOCK_WRITE_ERR;
    return NT2_OK;
}

/*
 *                                                     		End of File
 ******************************************************************************/
