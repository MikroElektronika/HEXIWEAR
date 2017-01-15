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
/** @file RW_NDEF_T3T.c
 *  @brief This module contains the
 */
/******************************************************************************
* Includes
*******************************************************************************/
#ifdef RW_SUPPORT
#include <string.h>
#include <stddef.h>
#include "RW_NDEF.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define T3T_MAGIC_NUMBER    0xE1
#define T3T_NDEF_TLV        0x03

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
typedef enum
{
    INITIAL,
    GETTING_ATTRIBUTE_INFO,
    READING_CARD_CONTENT
} rw_ndef_t3t_state_t;

typedef struct
{
    uint8_t id_m[8];
    uint8_t blk_nb;
    uint16_t record_ptr;
    uint16_t record_size;
    uint8_t *p_record;
} rw_ndef_t3t_ndef_t;

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static uint8_t T3T_CHECK[] =
{
    0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0B,
    0x00, 0x1, 0x80, 0x00
};

static rw_ndef_t3t_state_t e_rw_ndef_t3t_state = INITIAL;
static rw_ndef_t3t_ndef_t rw_ndef_t3t_ndef;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void rw_ndef_t3t_reset( void )
{
    e_rw_ndef_t3t_state = INITIAL;
    rw_ndef_t3t_ndef.p_record = ndef_buffer;
}

void rw_ndef_t3t_set_id_m( uint8_t *pIDm )
{
    memcpy( rw_ndef_t3t_ndef.id_m, pIDm, sizeof( rw_ndef_t3t_ndef.id_m ) );
    memcpy( &T3T_CHECK[2], pIDm, sizeof( rw_ndef_t3t_ndef.id_m ) );
}

void rw_ndef_t3t_read_next( uint8_t *p_rsp, uint16_t rsp_size,
                            uint8_t *p_cmd, uint16_t *p_cmd_size )
{
    /* By default no further command to be sent */
    *p_cmd_size = 0;

    switch( e_rw_ndef_t3t_state )
    {
    case INITIAL:
        /* Get AttributeInfo */
        memcpy ( p_cmd, T3T_CHECK, sizeof( T3T_CHECK ) );
        *p_cmd_size = sizeof( T3T_CHECK );
        e_rw_ndef_t3t_state = GETTING_ATTRIBUTE_INFO;
        break;

    case GETTING_ATTRIBUTE_INFO:
        /* Is Check success ?*/
        if ( ( p_rsp[rsp_size - 1] == 0x00 ) && ( p_rsp[1] == 0x07 ) &&
                ( p_rsp[10] == 0x00 ) && ( p_rsp[11] == 0x00 ) )
        {
            /* Fill File structure */
            rw_ndef_t3t_ndef.record_size = ( p_rsp[24] << 16 ) + ( p_rsp[25] << 16 ) +
                                           p_rsp[26];

            if( rw_ndef_t3t_ndef.record_size > RW_MAX_NDEF_FILE_SIZE )
            {
                /* NDEF record is too large, Abort */
            } else {
                rw_ndef_t3t_ndef.record_ptr = 0;
                rw_ndef_t3t_ndef.blk_nb = 1;

                /* Read first NDEF block */
                memcpy ( p_cmd, T3T_CHECK, sizeof( T3T_CHECK ) );
                p_cmd[15] = 0x01;
                *p_cmd_size = sizeof( T3T_CHECK );
                e_rw_ndef_t3t_state = READING_CARD_CONTENT;
            }
        }
        break;

    case READING_CARD_CONTENT:
        /* Is Check success ?*/
        if ( ( p_rsp[rsp_size - 1] == 0x00 ) && ( p_rsp[1] == 0x07 ) &&
                ( p_rsp[10] == 0x00 ) && ( p_rsp[11] == 0x00 ) )
        {
            /* Is NDEF record read completed ?*/
            if ( ( rw_ndef_t3t_ndef.record_size - rw_ndef_t3t_ndef.record_ptr ) <= 16 )
            {
                memcpy( &rw_ndef_t3t_ndef.p_record[rw_ndef_t3t_ndef.record_ptr], &p_rsp[13],
                        ( rw_ndef_t3t_ndef.record_size - rw_ndef_t3t_ndef.record_ptr ) );
                /* Notify application of the NDEF reception */
                if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t3t_ndef.p_record,
                            rw_ndef_t3t_ndef.record_size );
            } else {
                memcpy( &rw_ndef_t3t_ndef.p_record[rw_ndef_t3t_ndef.record_ptr], &p_rsp[13],
                        16 );
                rw_ndef_t3t_ndef.record_ptr += 16;
                rw_ndef_t3t_ndef.blk_nb++;

                /* Read next NDEF block */
                memcpy ( p_cmd, T3T_CHECK, sizeof( T3T_CHECK ) );
                p_cmd[15] = rw_ndef_t3t_ndef.blk_nb;
                *p_cmd_size = sizeof( T3T_CHECK );
            }
        }
        break;

    default:
        break;
    }
}
#endif


/*************** END OF FUNCTIONS ***************************************************************************/