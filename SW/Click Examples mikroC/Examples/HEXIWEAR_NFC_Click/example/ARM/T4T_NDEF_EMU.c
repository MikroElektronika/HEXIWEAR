/*******************************************************************************
* Title                 :   System Initialization
* Filename              :   sys_init.c
* Author                :   RBL
* Origin Date           :   04/23/2012
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  20/02/16           .1         RBL      Module Created.
*
*******************************************************************************/
/** @file T4T_NDEF_EMU.c
 *  @brief This module contains the
 */
/******************************************************************************
* Includes
*******************************************************************************/
#ifdef CARDEMU_SUPPORT
#include <string.h>
#include <stddef.h>
#include "T4T_NDEF_EMU.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
typedef enum
{
    READY_STATE,
    NDEF_APPLICATION_SELECTED,
    CC_SELECTED,
    NDEF_SELECTED,
} t4t_ndef_emu_state_t;

typedef void t4t_ndef_emu_callback_t( uint8_t *, uint16_t );

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static const uint8_t T4T_NDEF_EMU_APP_SELECT[] =
{
    0x00, 0xA4, 0x04, 0x00, 0x07, 0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01
};

static const uint8_t T4T_NDEF_EMU_CC[] =
{
    0x00, 0x0F, 0x20, 0x00, 0xFF, 0x00, 0xFF, 0x04, 0x06, 0xE1, 0x04, 0x00,
    0xFF, 0x00, 0xFF
};

static const uint8_t T4T_NDEF_EMU_CC_SELECT[] =
{
    0x00, 0xA4, 0x00, 0x0C, 0x02, 0xE1, 0x03
};

static const uint8_t T4T_NDEF_EMU_NDEF_SELECT[] =
{
    0x00, 0xA4, 0x00, 0x0C, 0x02, 0xE1, 0x04
};

static const uint8_t T4T_NDEF_EMU_READ[] = {0x00, 0xB0};
static const uint8_t T4T_NDEF_EMU_OK[] = {0x90, 0x00};
static const uint8_t T4T_NDEF_EMU_NOK[] = {0x6A, 0x82};

static uint8_t *p_t4t_ndef_record;
static uint16_t t4t_ndef_record_size = 0;

static t4t_ndef_emu_state_t e_t4t_ndef_emu_state = READY_STATE;
static t4t_ndef_emu_callback_t *p_t4t_ndef_emu_push_cb = NULL;


/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void t4t_ndef_emu_fill_rsp ( uint8_t *p_rsp, uint16_t offset,
                                    uint8_t length );

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void t4t_ndef_emu_fill_rsp ( uint8_t *p_rsp, uint16_t offset,
                                    uint8_t length )
{
    if ( offset == 0 )
    {
        p_rsp[0] = ( t4t_ndef_record_size & 0xFF00 ) >> 8;
        p_rsp[1] = ( t4t_ndef_record_size & 0x00FF );
        memcpy( &p_rsp[2], &p_t4t_ndef_record[0], length - 2 );
    }
    else if ( offset == 1 )
    {
        p_rsp[0] = ( t4t_ndef_record_size & 0x00FF );
        memcpy( &p_rsp[1], &p_t4t_ndef_record[0], length - 1 );
    }
    else
        memcpy( p_rsp, &p_t4t_ndef_record[offset - 2], length );

    /* Did we reached the end of NDEF record ?*/
    if ( ( offset + length ) >= ( t4t_ndef_record_size + 2 ) )
    {
        /* Notify application of the NDEF send */
        if( p_t4t_ndef_emu_push_cb != NULL )
            p_t4t_ndef_emu_push_cb( p_t4t_ndef_record,
                                    t4t_ndef_record_size );
    }
}

bool t4t_ndef_emu_set_record( uint8_t *p_record,
                              uint16_t record_size, void *cb )
{
    p_t4t_ndef_record = p_record;
    t4t_ndef_record_size = record_size;
    p_t4t_ndef_emu_push_cb = ( t4t_ndef_emu_callback_t * ) cb;

    return true;
}

void t4t_ndef_emu_reset( void )
{
    e_t4t_ndef_emu_state = READY_STATE;
}

void t4t_ndef_emu_next( uint8_t *p_cmd, uint16_t cmd_size,
                        uint8_t *rsp, uint16_t *p_rsp_size )
{
    bool e_status = false;

    if ( !memcmp( p_cmd, ( uint8_t * )T4T_NDEF_EMU_APP_SELECT,
                  sizeof( T4T_NDEF_EMU_APP_SELECT ) ) )
    {
        *p_rsp_size = 0;
        e_status = true;
        e_t4t_ndef_emu_state = NDEF_APPLICATION_SELECTED;
    } else if ( !memcmp( p_cmd, ( uint8_t * )T4T_NDEF_EMU_CC_SELECT,
                         sizeof( T4T_NDEF_EMU_CC_SELECT ) ) ) {
        if( e_t4t_ndef_emu_state == NDEF_APPLICATION_SELECTED )
        {
            *p_rsp_size = 0;
            e_status = true;
            e_t4t_ndef_emu_state = CC_SELECTED;
        }
    } else if( !memcmp( p_cmd, ( uint8_t * )T4T_NDEF_EMU_NDEF_SELECT,
                        sizeof( T4T_NDEF_EMU_NDEF_SELECT ) ) ) {
        *p_rsp_size = 0;
        e_status = true;
        e_t4t_ndef_emu_state = NDEF_SELECTED;
    } else if ( !memcmp( p_cmd, ( uint8_t * )T4T_NDEF_EMU_READ,
                         sizeof( T4T_NDEF_EMU_READ ) ) ) {
        if( e_t4t_ndef_emu_state == CC_SELECTED )
        {
            memcpy( rsp, ( uint8_t * )T4T_NDEF_EMU_CC, sizeof( T4T_NDEF_EMU_CC ) );
            *p_rsp_size = sizeof( T4T_NDEF_EMU_CC );
            e_status = true;
        } else if ( e_t4t_ndef_emu_state == NDEF_SELECTED ) {
            uint16_t offset = ( p_cmd[2] << 8 ) + p_cmd[3];
            uint8_t length = p_cmd[4];

            if( length <= ( t4t_ndef_record_size + offset + 2 ) )
            {
                t4t_ndef_emu_fill_rsp( rsp, offset, length );
                *p_rsp_size = length;
                e_status = true;
            }
        }
    }

    if ( e_status == true )
    {
        memcpy( &rsp[*p_rsp_size], ( uint8_t * )T4T_NDEF_EMU_OK, sizeof( T4T_NDEF_EMU_OK ) );
        *p_rsp_size += sizeof( T4T_NDEF_EMU_OK );
    } else {
        memcpy( rsp, ( uint8_t * )T4T_NDEF_EMU_NOK, sizeof( T4T_NDEF_EMU_NOK ) );
        *p_rsp_size = sizeof( T4T_NDEF_EMU_NOK );
        t4t_ndef_emu_reset();
    }
}
#endif

/*************** END OF FUNCTIONS ***************************************************************************/
